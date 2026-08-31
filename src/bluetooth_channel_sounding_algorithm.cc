/*
 * Copyright 2026 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "bthal.aidl.ranging.cs.algo"

#include "bluetooth_channel_sounding_algorithm.h"

#include <algorithm>
#include <any>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <string>
#include <utility>

#include "Eigen/Dense"
#include "aidl/android/hardware/bluetooth/ranging/ChannelSoudingRawData.h"
#include "android-base/logging.h"
#include "android-base/properties.h"

using ::aidl::android::hardware::bluetooth::ranging::ChannelSoudingRawData;
using ::aidl::android::hardware::bluetooth::ranging::
    ChannelSoundingProcedureData;
using ::aidl::android::hardware::bluetooth::ranging::Config;
using ::aidl::android::hardware::bluetooth::ranging::ModeData;
using ::aidl::android::hardware::bluetooth::ranging::ModeType;
using ::aidl::android::hardware::bluetooth::ranging::PctIQSample;
using ::aidl::android::hardware::bluetooth::ranging::ProcedureEnableConfig;
using ::android::base::GetBoolProperty;
using ::android::base::GetIntProperty;
using ::android::base::GetProperty;

constexpr double kSpeedOfLight = 299792458;
constexpr size_t kMinStepChannelSize = 15;
constexpr int8_t kTRdTimeUs = 5;
static constexpr uint8_t kMaxValidPermutationIndexTable[4] = {0, 1, 5, 23};
// Antenna path permutations. See Channel Sounding CR_PR for the details.
static constexpr uint8_t kCsAntennaPermutationArray[24][4] = {
    {1, 2, 3, 4}, {2, 1, 3, 4}, {1, 3, 2, 4}, {3, 1, 2, 4}, {3, 2, 1, 4},
    {2, 3, 1, 4}, {1, 2, 4, 3}, {2, 1, 4, 3}, {1, 4, 2, 3}, {4, 1, 2, 3},
    {4, 2, 1, 3}, {2, 4, 1, 3}, {1, 4, 3, 2}, {4, 1, 3, 2}, {1, 3, 4, 2},
    {3, 1, 4, 2}, {3, 4, 1, 2}, {4, 3, 1, 2}, {4, 2, 3, 1}, {2, 4, 3, 1},
    {4, 3, 2, 1}, {3, 4, 2, 1}, {3, 2, 4, 1}, {2, 3, 4, 1}};

namespace {

template <typename T>
inline Eigen::Vector<T, Eigen::Dynamic> select_by_mask(
    const Eigen::Vector<T, Eigen::Dynamic>& data,
    const Eigen::Vector<bool, Eigen::Dynamic>& mask) {
  std::vector<T> result;
  for (int i = 0; i < data.size(); ++i) {
    if (mask(i)) {
      result.push_back(data(i));
    }
  }
  return Eigen::Map<Eigen::Vector<T, Eigen::Dynamic>>(result.data(),
                                                      result.size());
}

template <typename T>
inline std::vector<T> select_by_mask(const std::vector<T>& data,
                                     const std::vector<bool>& mask) {
  std::vector<T> result;
  for (size_t i = 0; i < data.size(); ++i) {
    if (mask[i]) {
      result.push_back(data[i]);
    }
  }
  return result;
}

inline Eigen::VectorXd diff(const Eigen::VectorXd& vec) {
  if (vec.size() <= 1) {
    return Eigen::VectorXd(0);
  }
  return vec.tail(vec.size() - 1) - vec.head(vec.size() - 1);
}

inline Eigen::VectorXd unwrap(const Eigen::VectorXd& phase) {
  if (phase.size() == 0) {
    return Eigen::VectorXd(0);
  }
  Eigen::VectorXd unwrapped_phase = phase;
  double offset = 0.0;
  for (int i = 1; i < phase.size(); ++i) {
    double diff = phase(i) - phase(i - 1);
    if (diff > M_PI) {
      offset -= 2 * M_PI;
    } else if (diff < -M_PI) {
      offset += 2 * M_PI;
    }
    unwrapped_phase(i) += offset;
  }
  return unwrapped_phase;
}

inline int BitReverse(const int in, const int num_bits) {
  int out = 0;
  for (int ix = 0; ix < num_bits; ++ix) {
    out |= (((in >> ix) & 1) << (num_bits - ix - 1));
  }
  return out;
}

}  // namespace

// ChannelSoundingAlgorithm

void ChannelSoundingAlgorithm::ResetVariables() {
  bool change_algo_config =
      GetBoolProperty("bluetooth.vendor.cs.change_algo_config", false);
  if (change_algo_config) {
    ChangeAlgoConfig();
  }

  step_channel_.clear();
  step_channel_cleaned_.clear();
  pct_initiator_.clear();
  pct_reflector_.clear();
  pct_cleaned_.clear();
  pct_autocorr_.clear();
  pct_covmat_.clear();
  raw_distance_collection_.clear();
  confidence_level_collection_.clear();
  delta_f_ = 1;

  raw_distance_ = 999.0;
  delay_spread_ = 0.0;
  confidence_level_ = 0.0;
}

double ChannelSoundingAlgorithm::EstimateDistanceImpl(const std::any& data) {
  const auto* raw_data = std::any_cast<ChannelSoudingRawData>(&data);

  if (raw_data) {
    // mode-1 has no PCT (check initiator)
    if (raw_data->initiatorData.stepTonePcts.value()[0]
            .value()
            .tonePcts.empty()) {
      return raw_distance_;
    }

    this->ParseRawData(*raw_data);
    dataCleaning.Run(*this);
    rangingAlgorithm.Run(*this);
    return raw_distance_ > 0 ? raw_distance_ : 0.0;
  }

  const auto* procedure_data =
      std::any_cast<ChannelSoundingProcedureData>(&data);
  if (procedure_data) {
    this->ParseProcedureData(*procedure_data);
    if (step_channel_.size() < kMinStepChannelSize) {
      return raw_distance_ > 0 ? raw_distance_ : 0.0;
    }
    if (!this->CheckPCTSize()) {
      LOG(WARNING) << __func__ << " checkPCTSize fail";
      return raw_distance_;
    }
    dataCleaning.Run(*this);
    rangingAlgorithm.Run(*this);
    return raw_distance_ > 0 ? raw_distance_ : 0.0;
  }

  LOG(ERROR) << __func__ << ": Data type is not right.";

  return -1;
}

void ChannelSoundingAlgorithm::UpdateChannelSoundingConfig(
    const ::aidl::android::hardware::bluetooth::ranging::Config& in_config) {
  cs_config_ = in_config;
  int tSwTimeUs = std::min(cs_config_.tSwTimeUsSupportedByLocal,
                           cs_config_.tSwTimeUsSupportedByRemote);

  // mode-2 step duration = T_FCS+(T_SW+T_PM)*(N_AP+1)+T_RD+ T_IP2 +
  // (T_SW+T_PM)*(N_AP+1)+T_RD
  this->t_mode2_step_us_ =
      cs_config_.tFcsTimeUs + (tSwTimeUs + cs_config_.tPmTimeUs) * (n_ap_ + 1) +
      kTRdTimeUs + cs_config_.tIp2TimeUs +
      (tSwTimeUs + cs_config_.tPmTimeUs) * (n_ap_ + 1) + kTRdTimeUs;
}

void ChannelSoundingAlgorithm::UpdateProcedureEnableConfig(
    const ::aidl::android::hardware::bluetooth::ranging::ProcedureEnableConfig&
        in_procedureEnableConfig) {
  procedure_enable_config_ = in_procedureEnableConfig;
  switch (procedure_enable_config_.toneAntennaConfigSelection) {
    case 0:
      n_ap_ = 1;
      break;
    case 1:
      n_ap_ = 2;
      break;
    case 2:
      n_ap_ = 3;
      break;
    case 3:
      n_ap_ = 4;
      break;
    case 4:
      n_ap_ = 2;
      break;
    case 5:
      n_ap_ = 3;
      break;
    case 6:
      n_ap_ = 4;
      break;
    case 7:
      n_ap_ = 4;
      break;
    default:
      n_ap_ = 1;
  }

  int tSwTimeUs = std::min(cs_config_.tSwTimeUsSupportedByLocal,
                           cs_config_.tSwTimeUsSupportedByRemote);
  this->t_mode2_step_us_ =
      cs_config_.tFcsTimeUs + (tSwTimeUs + cs_config_.tPmTimeUs) * (n_ap_ + 1) +
      kTRdTimeUs + cs_config_.tIp2TimeUs +
      (tSwTimeUs + cs_config_.tPmTimeUs) * (n_ap_ + 1) + kTRdTimeUs;
}

void ChannelSoundingAlgorithm::ParseRawData(
    const ChannelSoudingRawData& channel_souding_raw_data) {
  size_t num_steps = channel_souding_raw_data.stepChannels.size();
  n_subevent_ = 1;
  n_step_subevent_.push_back(num_steps);
  n_ap_ = channel_souding_raw_data.initiatorData.stepTonePcts->size() - 1;
  reference_power_level_initiator_ =
      channel_souding_raw_data.initiatorData.referencePowerDbm;
  reference_power_level_reflector_ =
      channel_souding_raw_data.reflectorData.referencePowerDbm;
  for (size_t ap = 0; ap < n_ap_; ap++) {
    pct_initiator_.emplace_back(std::vector<std::complex<double>>());
    pct_reflector_.emplace_back(std::vector<std::complex<double>>());
  }
  for (size_t step = 0; step < num_steps; step++) {
    step_channel_.push_back(channel_souding_raw_data.stepChannels[step]);
    for (size_t ap = 0; ap < n_ap_; ap++) {
      pct_initiator_[ap].push_back(std::complex<double>(
          channel_souding_raw_data.initiatorData.stepTonePcts.value()[ap]
              .value()
              .tonePcts[step]
              .real,
          channel_souding_raw_data.initiatorData.stepTonePcts.value()[ap]
              .value()
              .tonePcts[step]
              .imaginary));
    }
    for (size_t ap = 0; ap < n_ap_; ap++) {
      if (!channel_souding_raw_data.reflectorData.stepTonePcts.value()[ap]
               .value()
               .tonePcts.empty()) {
        pct_reflector_[ap].push_back(std::complex<double>(
            channel_souding_raw_data.reflectorData.stepTonePcts.value()[ap]
                .value()
                .tonePcts[step]
                .real,
            channel_souding_raw_data.reflectorData.stepTonePcts.value()[ap]
                .value()
                .tonePcts[step]
                .imaginary));
      }
      // 1-side PCT
      else {
        pct_reflector_[ap].push_back(
            std::complex<double>(std::abs(pct_initiator_[ap][step]), 0.0));
      }
    }
  }
}

void ChannelSoundingAlgorithm::ChangeAlgoConfig() {
  // // change config on the fly
  std::string algo_type = GetProperty("bluetooth.vendor.cs.algo_type", "MUSIC");

  uint8_t selected_ap = GetIntProperty("bluetooth.vendor.cs.selected_ap", 0);
  bool apply_windowing =
      GetBoolProperty("bluetooth.vendor.cs.apply_windowing", false);
  bool use_post_combining =
      GetBoolProperty("bluetooth.vendor.cs.use_post_combining", true);
  uint8_t autocorr_K = GetIntProperty("bluetooth.vendor.cs.autocorr_K", 48);

  uint16_t ranging_algorithm_fft_size =
      GetIntProperty("bluetooth.vendor.cs.ranging_algorithm_fft_size", 4096);
  double ranging_algorithm_noise_est_interval = (double)GetIntProperty(
      "bluetooth.vendor.cs.ranging_algorithm_noise_est_interval", 20);
  double ranging_algorithm_shift_distance = (double)GetIntProperty(
      "bluetooth.vendor.cs.ranging_algorithm_shift_distance", 1);
  double ranging_algorithm_threshold_zp_ifft = (double)GetIntProperty(
      "bluetooth.vendor.cs.ranging_algorithm_threshold_zp_ifft", 20);
  uint16_t ranging_algorithm_music_size =
      GetIntProperty("bluetooth.vendor.cs.ranging_algorithm_music_size", 2048);
  double ranging_algorithm_threshold_music_svd = (double)GetIntProperty(
      "bluetooth.vendor.cs.ranging_algorithm_threshold_music_svd", 3);
  double ranging_algorithm_threshold_music_peak = (double)GetIntProperty(
      "bluetooth.vendor.cs.ranging_algorithm_threshold_music_peak", 4);

  if (algo_type == "ZP_IFFT") {
    this->algo_type_ = AlgoType::kZpIfft;
  } else if (algo_type == "MUSIC") {
    this->algo_type_ = AlgoType::kMusic;
  }

  this->selected_ap_ = selected_ap;
  this->apply_windowing_ = apply_windowing;
  this->use_post_combining_ = use_post_combining;
  this->autocorr_K_ = autocorr_K;

  this->rangingAlgorithm.fft_size_ = ranging_algorithm_fft_size;
  this->rangingAlgorithm.noise_est_interval_ =
      ranging_algorithm_noise_est_interval;
  this->rangingAlgorithm.shift_distance_ = ranging_algorithm_shift_distance;
  this->rangingAlgorithm.threshold_zp_ifft_ =
      ranging_algorithm_threshold_zp_ifft;
  this->rangingAlgorithm.music_size_ = ranging_algorithm_music_size;
  this->rangingAlgorithm.threshold_music_svd_ =
      ranging_algorithm_threshold_music_svd;
  this->rangingAlgorithm.threshold_music_peak_ =
      ranging_algorithm_threshold_music_peak;
}

void ChannelSoundingAlgorithm::ParseProcedureData(
    const ChannelSoundingProcedureData& procedure_data) {
  if (procedure_data.initiatorSubeventResultData.size() == 0) {
    LOG(WARNING) << __func__
                 << ": invalid, initiatorSubeventResultData is empty";
    return;
  }
  n_ap_ = procedure_data.initiatorSubeventResultData[0].numAntennaPaths;
  reference_power_level_initiator_ =
      procedure_data.initiatorSubeventResultData[0].referencePowerLevelDbm;

  if (procedure_data.reflectorSubeventResultData.size() != 0) {
    reference_power_level_reflector_ =
        procedure_data.reflectorSubeventResultData[0].referencePowerLevelDbm;
  }

  // Initiator
  pct_initiator_.resize(n_ap_ + 1);
  n_subevent_ = procedure_data.initiatorSubeventResultData.size();
  n_step_subevent_.resize(n_subevent_);
  size_t subevent_idx = 0;
  for (const auto& subevent : procedure_data.initiatorSubeventResultData) {
    int power_adjustment_dB =
        subevent.referencePowerLevelDbm - reference_power_level_initiator_;
    double amplitude_adjustment_linear =
        std::pow(10.0, static_cast<double>(power_adjustment_dB) / 20.0);
    n_step_subevent_.at(subevent_idx) = 0;
    for (const auto& step : subevent.stepData) {
      switch (step.stepMode) {
        case ModeType::ZERO: {
          break;
        }
        case ModeType::ONE: {
          break;
        }
        case ModeType::TWO: {
          const auto& data =
              step.stepModeData.get<ModeData::Tag::modeTwoData>();
          uint8_t permutation_index = data.antennaPermutationIndex;
          uint16_t num_tone_data = data.tonePctIQSamples.size();
          for (uint16_t k = 0; k < num_tone_data; k++) {
            uint8_t ap =
                (k == n_ap_)
                    ? n_ap_
                    : kCsAntennaPermutationArray[permutation_index][k] -
                          1;  // -1 for 0-based index
            pct_initiator_.at(ap).push_back(
                this->PctToComplex(data.tonePctIQSamples[k]) *
                amplitude_adjustment_linear);
          }
          step_channel_.push_back(step.stepChannel);
          n_step_subevent_.at(subevent_idx)++;
          break;
        }
        case ModeType::THREE: {
          step_channel_.push_back(step.stepChannel);
          break;
        }
      }
    }
    subevent_idx++;
  }

  // Reflector
  pct_reflector_.resize(n_ap_ + 1);
  subevent_idx = 0;
  if (inline_pct_) {
    size_t num_steps = step_channel_.size();
    for (size_t ap = 0; ap < n_ap_ + 1; ap++) {
      for (size_t step = 0; step < num_steps; step++) {
        pct_reflector_[ap].push_back(
            std::complex<double>(std::abs(pct_initiator_[ap][step]), 0.0));
      }
    }
  } else {
    for (const auto& subevent : procedure_data.reflectorSubeventResultData) {
      int power_adjustment_dB =
          subevent.referencePowerLevelDbm - reference_power_level_initiator_;
      double amplitude_adjustment_linear =
          std::pow(10.0, static_cast<double>(power_adjustment_dB) / 20.0);
      for (const auto& step : subevent.stepData) {
        switch (step.stepMode) {
          case ModeType::ZERO: {
            break;
          }
          case ModeType::ONE: {
            break;
          }
          case ModeType::TWO: {
            const auto& data =
                step.stepModeData.get<ModeData::Tag::modeTwoData>();
            uint8_t permutation_index = data.antennaPermutationIndex;
            uint16_t num_tone_data = data.tonePctIQSamples.size();
            for (uint16_t k = 0; k < num_tone_data; k++) {
              uint8_t ap =
                  (k == n_ap_)
                      ? n_ap_
                      : kCsAntennaPermutationArray[permutation_index][k] -
                            1;  // -1 for 0-based index
              pct_reflector_.at(ap).push_back(
                  this->PctToComplex(data.tonePctIQSamples[k]) *
                  amplitude_adjustment_linear);
            }
            break;
          }
          case ModeType::THREE: {
            break;
          }
        }
      }
    }
  }
}

bool ChannelSoundingAlgorithm::CheckPCTSize() const {
  if (pct_initiator_.size() == 0) {
    LOG(WARNING) << __func__ << " empty pct_initiator_";
    return false;
  }

  if (pct_reflector_.size() == 0) {
    LOG(WARNING) << __func__ << " empty pct_reflector_";
    return false;
  }

  if (pct_initiator_.size() != pct_reflector_.size()) {
    LOG(WARNING) << __func__
                 << " pct_initiator_ and pct_reflector_ AP size mismatch";
    return false;
  }

  for (size_t ap = 0; ap < pct_initiator_.size(); ap++) {
    if (step_channel_.size() != pct_initiator_[ap].size()) {
      LOG(WARNING) << __func__
                   << " step_channel_.size() != pct_initiator_.size() at AP "
                   << ap;
      return false;
    }
  }

  for (size_t ap = 0; ap < pct_reflector_.size(); ap++) {
    if (step_channel_.size() != pct_reflector_[ap].size()) {
      LOG(WARNING) << __func__
                   << " step_channel_.size() != pct_reflector_.size() at AP "
                   << ap;
      return false;
    }
  }

  for (size_t ap = 0; ap < pct_initiator_.size(); ap++) {
    if (pct_initiator_[ap].size() != pct_reflector_[ap].size()) {
      LOG(WARNING) << __func__
                   << " pct_initiator_[ap].size().size() != "
                      "pct_reflector_.size() at AP "
                   << ap;
      return false;
    }
  }

  return true;
}

void ChannelSoundingAlgorithm::DataCleaning::Run(
    ChannelSoundingAlgorithm& cs_algo) {
  ChannelSoundingAlgorithm::DataCleaning::MultiplyPCT(cs_algo);
  if (cs_algo.fix_doppler_) {
    ChannelSoundingAlgorithm::DataCleaning::FixDoppler(cs_algo);
  }
  ChannelSoundingAlgorithm::DataCleaning::SortPCT(cs_algo);

  ChannelSoundingAlgorithm::DataCleaning::UpdateDeltaF(cs_algo);
  if (cs_algo.algo_type_ == AlgoType::kZpIfft) {
    ChannelSoundingAlgorithm::DataCleaning::CalculateAutocorr(cs_algo);
  } else if (cs_algo.algo_type_ == AlgoType::kMusic) {
    ChannelSoundingAlgorithm::DataCleaning::CalculateCovarianceMatrix(cs_algo);
  }
}

void ChannelSoundingAlgorithm::DataCleaning::MultiplyPCT(
    ChannelSoundingAlgorithm& cs_algo) {
  size_t num_steps = cs_algo.step_channel_.size();
  // cs_algo.pct_cleaned_
  for (size_t ap = 0; ap < cs_algo.pct_initiator_.size(); ap++) {
    cs_algo.pct_cleaned_.emplace_back(std::vector<std::complex<double>>());
  }
  // multiply
  for (size_t step = 0; step < num_steps; step++) {
    for (size_t ap = 0; ap < cs_algo.pct_initiator_.size(); ap++) {
      cs_algo.pct_cleaned_[ap].push_back(cs_algo.pct_initiator_[ap][step] *
                                         cs_algo.pct_reflector_[ap][step]);
    }
  }
}

void ChannelSoundingAlgorithm::DataCleaning::SortPCT(
    ChannelSoundingAlgorithm& cs_algo) {
  // sort
  std::vector<uint8_t> perm;
  cs_algo.step_channel_cleaned_ = cs_algo.step_channel_;
  std::vector<std::vector<std::complex<double>>> pct_mult =
      cs_algo.pct_cleaned_;
  perm = ChannelSoundingAlgorithm::DataCleaning::SortPermutation(
      cs_algo.step_channel_);
  for (uint16_t step = 0; step < perm.size(); step++) {
    cs_algo.step_channel_cleaned_[step] = cs_algo.step_channel_[perm[step]];
    for (size_t ap = 0; ap < cs_algo.pct_initiator_.size(); ap++) {
      cs_algo.pct_cleaned_[ap][step] = pct_mult[ap][perm[step]];
    }
  }

  // remove repeated
  std::vector<uint8_t> remove_idx;
  for (size_t i = 1; i < cs_algo.step_channel_cleaned_.size(); i++) {
    if (cs_algo.step_channel_cleaned_[i] ==
        cs_algo.step_channel_cleaned_[i - 1]) {
      remove_idx.push_back(i);
    }
  }
  std::sort(remove_idx.begin(), remove_idx.end(), std::greater<size_t>());
  for (size_t idx = 0; idx < remove_idx.size(); idx++) {
    cs_algo.step_channel_cleaned_.erase(cs_algo.step_channel_cleaned_.begin() +
                                        remove_idx[idx]);
    for (size_t ap = 0; ap < cs_algo.pct_initiator_.size(); ap++) {
      cs_algo.pct_cleaned_[ap].erase(cs_algo.pct_cleaned_[ap].begin() +
                                     remove_idx[idx]);
    }
  }
}

void ChannelSoundingAlgorithm::DataCleaning::FixDoppler(
    ChannelSoundingAlgorithm& cs_algo) {
  if (cs_algo.n_subevent_ > 1) {
    ChannelSoundingAlgorithm::DataCleaning::FixDopplerFragmented(cs_algo);
    return;
  }
  // Common setup from old FixDoppler and FixDopplerFragmented
  std::vector<uint8_t> perm;
  perm = ChannelSoundingAlgorithm::DataCleaning::SortPermutation(
      cs_algo.step_channel_);

  std::vector<uint8_t> step_channel_ordered_vec(cs_algo.step_channel_.size());
  for (uint16_t step = 0; step < perm.size(); step++) {
    step_channel_ordered_vec[step] = cs_algo.step_channel_[perm[step]];
  }

  Eigen::Map<Eigen::Matrix<uint8_t, Eigen::Dynamic, 1>>
      step_channel_ordered_tmp(step_channel_ordered_vec.data(),
                               step_channel_ordered_vec.size());
  Eigen::VectorXd step_channel_ordered_eigen =
      step_channel_ordered_tmp.cast<double>();

  Eigen::Map<Eigen::Matrix<uint8_t, Eigen::Dynamic, 1>> perm_map(perm.data(),
                                                                 perm.size());
  Eigen::VectorXi perm_eigen = perm_map.cast<int>();

  // Multi-stage algorithm
  std::vector<double> doppler_est;
  for (uint8_t ap = 0; ap < cs_algo.n_ap_; ap++) {
    // Stage 1: Estimate distance slope
    Eigen::VectorXd distance_try = Eigen::VectorXd::LinSpaced(150, 0, 150);
    Eigen::VectorXd slope_corr = Eigen::VectorXd::Zero(150);

    Eigen::Map<Eigen::VectorXcd, Eigen::Unaligned> pct_cleaned_ap_tmp(
        cs_algo.pct_cleaned_[ap].data(), cs_algo.pct_cleaned_[ap].size());
    Eigen::VectorXcd pct_cleaned_ap_eigen =
        pct_cleaned_ap_tmp.cast<std::complex<double>>();

    Eigen::VectorXcd phase_in_complex_sub = pct_cleaned_ap_eigen(perm_eigen);
    phase_in_complex_sub =
        (std::complex<double>(0, 1) * phase_in_complex_sub.array().arg()).exp();

    Eigen::MatrixXcd slope_matrix_sub(distance_try.size(),
                                      step_channel_ordered_eigen.size());
    Eigen::VectorXcd term1 =
        (std::complex<double>(0, 1) * 2.0 * M_PI * 2.0 / kSpeedOfLight) *
        distance_try.cast<std::complex<double>>();
    Eigen::VectorXcd term2 = (1e6 * step_channel_ordered_eigen.transpose())
                                 .cast<std::complex<double>>();
    slope_matrix_sub = (term1 * term2.transpose()).array().exp();

    Eigen::VectorXcd slope_corr_sub = slope_matrix_sub * phase_in_complex_sub;
    slope_corr = slope_corr_sub.array().abs().matrix();

    Eigen::MatrixXf::Index slope_idx;
    slope_corr.maxCoeff(&slope_idx);
    double slope_est =
        -2.0 * M_PI * 2.0 * distance_try(slope_idx) / kSpeedOfLight * 1e6;

    // stage 2: estimate doppler from each subevent
    Eigen::VectorXcd corrected_phase =
        pct_cleaned_ap_eigen(perm_eigen).array() *
        (std::complex<double>(0, -1) * slope_est *
         step_channel_ordered_eigen.array())
            .exp();

    Eigen::VectorXd phase_delta_sub(corrected_phase.size() - 1);
    for (int i = 0; i < corrected_phase.size() - 1; ++i) {
      double p1 = std::arg(corrected_phase(i));
      double p2 = std::arg(corrected_phase(i + 1));
      double diff = p2 - p1;
      if (diff > M_PI) diff -= 2 * M_PI;
      if (diff < -M_PI) diff += 2 * M_PI;
      phase_delta_sub(i) = diff;
    }

    std::vector<int> df_vec;
    std::vector<int> dt_vec;
    for (uint16_t step = 0; step < cs_algo.step_channel_.size() - 1; step++) {
      df_vec.push_back(step_channel_ordered_vec[step + 1] -
                       step_channel_ordered_vec[step]);
      dt_vec.push_back(static_cast<int>(perm[step + 1]) -
                       static_cast<int>(perm[step]));
    }

    Eigen::MatrixXd A_sub(df_vec.size(), 2);
    for (size_t i = 0; i < df_vec.size(); ++i) {
      A_sub(i, 0) = df_vec[i];
      A_sub(i, 1) = dt_vec[i];
    }

    Eigen::VectorXd x = A_sub.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV)
                            .solve(phase_delta_sub);
    doppler_est.push_back(x(1));
  }
  double dopp_mean =
      std::accumulate(doppler_est.begin(), doppler_est.end(), 0.0) /
      doppler_est.size();

  cs_algo.doppler_shift_step_ = dopp_mean;
  cs_algo.velocity_ = -cs_algo.doppler_shift_step_ * kSpeedOfLight /
                      (2 * M_PI * 2.44e9 * cs_algo.t_mode2_step_us_ * 1e-6) / 2;

  // fix steps
  for (int ap = 0; ap < cs_algo.n_ap_; ++ap) {
    for (size_t i = 0; i < cs_algo.step_channel_.size(); ++i) {
      std::complex<double> exponent =
          std::complex<double>(0.0, -dopp_mean * static_cast<double>(i));
      cs_algo.pct_cleaned_[ap][i] *= std::exp(exponent);
    }
  }
}

void ChannelSoundingAlgorithm::DataCleaning::FixDopplerFragmented(
    ChannelSoundingAlgorithm& cs_algo) {
  // declare eigen version of cs_algo.value
  Eigen::Map<Eigen::Matrix<uint8_t, Eigen::Dynamic, 1>> step_channel_tmp(
      cs_algo.step_channel_.data(), cs_algo.step_channel_.size());
  Eigen::VectorXd step_channel_eigen = step_channel_tmp.cast<double>();

  // Create subevent_idx
  size_t num_subevent = cs_algo.n_step_subevent_.size();
  Eigen::VectorXd subevent_idx_eigen =
      Eigen::VectorXd::Zero(cs_algo.step_channel_.size());
  int cumulative_steps = 0;
  for (size_t m = 0; m < num_subevent; ++m) {
    cumulative_steps += cs_algo.n_step_subevent_[m];
    for (int i = 0; i < subevent_idx_eigen.size(); i++) {
      if (i >= cumulative_steps) {
        subevent_idx_eigen(i)++;
      }
    }
  }

  // Create ts_all
  std::vector<double> ts_all;
  for (size_t i = 0; i < cs_algo.n_step_subevent_.size(); ++i) {
    for (int j = 0; j < cs_algo.n_step_subevent_[i]; ++j) {
      ts_all.push_back(j);
    }
  }
  Eigen::Map<Eigen::VectorXd> ts_all_eigen(ts_all.data(), ts_all.size());

  // Create A_frag matrix
  std::vector<uint8_t> perm;
  auto step_channel_ordered = cs_algo.step_channel_;
  perm = ChannelSoundingAlgorithm::DataCleaning::SortPermutation(
      cs_algo.step_channel_);
  Eigen::Map<Eigen::Matrix<uint8_t, Eigen::Dynamic, 1>> perm_map(perm.data(),
                                                                 perm.size());
  Eigen::VectorXi perm_eigen = perm_map.cast<int>();
  for (uint16_t step = 0; step < perm.size(); step++) {
    step_channel_ordered[step] = cs_algo.step_channel_[perm[step]];
  }
  Eigen::Map<Eigen::Matrix<uint8_t, Eigen::Dynamic, 1>>
      step_channel_ordered_tmp(step_channel_ordered.data(),
                               step_channel_ordered.size());
  Eigen::VectorXd step_channel_ordered_eigen =
      step_channel_ordered_tmp.cast<double>();

  std::vector<double> df;
  for (uint16_t step = 0; step < cs_algo.step_channel_.size() - 1; step++) {
    df.push_back(step_channel_ordered[step + 1] - step_channel_ordered[step]);
  }

  Eigen::MatrixXd A_frag = Eigen::MatrixXd::Zero(
      df.size(),
      2 + num_subevent - 1);  // (df, dts, subevent_ind1, subevent_ind2, ...)
  for (int idx = 0; idx < A_frag.rows(); ++idx) {
    A_frag(idx, 0) = df[idx];
    long t1 = perm[idx];
    long t2 = perm[idx + 1];

    long ts1 = t1;
    int subevent1 = 0;
    while (ts1 >= cs_algo.n_step_subevent_[subevent1]) {
      ts1 -= cs_algo.n_step_subevent_[subevent1];
      subevent1++;
    }

    long ts2 = t2;
    int subevent2 = 0;
    while (ts2 >= cs_algo.n_step_subevent_[subevent2]) {
      ts2 -= cs_algo.n_step_subevent_[subevent2];
      subevent2++;
    }

    int dm = subevent2 - subevent1;
    double dts = static_cast<double>(ts2 - ts1);
    A_frag(idx, 1) = dts;

    for (int m = 1; m < num_subevent; ++m) {
      if (dm == m) A_frag(idx, 1 + m) = 1.0;
      if (dm == -m) A_frag(idx, 1 + m) = -1.0;
    }
  }

  // Multi-stage algorithm
  std::vector<double> doppler_est;
  std::vector<Eigen::VectorXd> phi_sub_est;
  for (uint8_t ap = 0; ap < cs_algo.n_ap_; ap++) {
    // Stage 1: Estimate distance slope
    Eigen::VectorXd distance_try = Eigen::VectorXd::LinSpaced(150, 0, 150);
    Eigen::VectorXd slope_corr = Eigen::VectorXd::Zero(150);

    Eigen::Map<Eigen::VectorXcd, Eigen::Unaligned> pct_cleaned_ap_tmp(
        cs_algo.pct_cleaned_[ap].data(), cs_algo.pct_cleaned_[ap].size());
    Eigen::VectorXcd pct_cleaned_ap_eigen =
        pct_cleaned_ap_tmp.cast<std::complex<double>>();

    for (int m = 0; m < num_subevent; ++m) {
      if (cs_algo.n_step_subevent_[m] == 0) continue;
      Eigen::Vector<bool, Eigen::Dynamic> mask =
          (subevent_idx_eigen.array() == m).matrix();
      Eigen::Vector<bool, Eigen::Dynamic> perm_mask(mask.size());
      for (int i = 0; i < mask.size(); ++i) {
        perm_mask(i) = mask(perm_eigen(i));
      }

      Eigen::VectorXcd phase_in_complex_sub = pct_cleaned_ap_eigen(perm_eigen);
      phase_in_complex_sub = select_by_mask(phase_in_complex_sub, perm_mask);
      phase_in_complex_sub =
          (std::complex<double>(0, 1) * phase_in_complex_sub.array().arg())
              .exp();
      Eigen::VectorXcd step_channel_sub =
          select_by_mask(step_channel_ordered_eigen, perm_mask);

      Eigen::MatrixXcd slope_matrix_sub(distance_try.size(),
                                        step_channel_sub.size());
      Eigen::VectorXcd term1 =
          (std::complex<double>(0, 1) * 2.0 * M_PI * 2.0 / kSpeedOfLight) *
          distance_try.cast<std::complex<double>>();
      Eigen::VectorXcd term2 =
          (1e6 * step_channel_sub.transpose()).cast<std::complex<double>>();
      slope_matrix_sub = (term1 * term2.transpose()).array().exp();

      Eigen::VectorXcd slope_corr_sub = slope_matrix_sub * phase_in_complex_sub;
      slope_corr += slope_corr_sub.array().abs().matrix();
    }

    Eigen::MatrixXf::Index slope_idx;
    slope_corr.maxCoeff(&slope_idx);
    double slope_est =
        -2.0 * M_PI * 2.0 * distance_try(slope_idx) / kSpeedOfLight * 1e6;

    // stage 2: estimate doppler from each subevent
    std::vector<double> doppler_est_coarse_vec;
    for (int m = 0; m < num_subevent; ++m) {
      if (cs_algo.n_step_subevent_[m] <= 1) continue;
      Eigen::Vector<bool, Eigen::Dynamic> mask =
          (subevent_idx_eigen.array() == m).matrix();
      Eigen::Vector<bool, Eigen::Dynamic> perm_mask(mask.size());
      for (int i = 0; i < mask.size(); ++i) {
        perm_mask(i) = mask(perm_eigen(i));
      }
      Eigen::VectorXd step_channel_ordered_eigen(perm.size());
      for (uint16_t step = 0; step < perm.size(); step++) {
        step_channel_ordered_eigen(step) = cs_algo.step_channel_[perm[step]];
      }

      Eigen::VectorXcd phase_in_complex_sub = pct_cleaned_ap_eigen(perm_eigen);
      phase_in_complex_sub = select_by_mask(phase_in_complex_sub, perm_mask);
      phase_in_complex_sub =
          (std::complex<double>(0, 1) * phase_in_complex_sub.array().arg())
              .exp();
      Eigen::VectorXcd step_channel_sub =
          select_by_mask(step_channel_ordered_eigen, perm_mask);
      Eigen::VectorXcd corrected_phase =
          phase_in_complex_sub.array() *
          (std::complex<double>(0, -1) * slope_est * step_channel_sub.array())
              .exp();
      Eigen::VectorXd phase_unwrap_detrend_sub =
          unwrap(corrected_phase.array().arg());

      Eigen::VectorXd phase_delta_sub = diff(phase_unwrap_detrend_sub);
      Eigen::VectorXd df_sub =
          diff(select_by_mask(step_channel_ordered_eigen, perm_mask));
      Eigen::VectorXd dt_sub =
          diff(select_by_mask(perm_eigen, perm_mask).cast<double>());

      Eigen::MatrixXd A_sub(df_sub.size(), 2);
      A_sub.col(0) = df_sub;
      A_sub.col(1) = dt_sub;

      Eigen::VectorXd x =
          A_sub.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV)
              .solve(phase_delta_sub);
      doppler_est_coarse_vec.push_back(x(1));
    }
    double doppler_est_coarse =
        std::accumulate(doppler_est_coarse_vec.begin(),
                        doppler_est_coarse_vec.end(), 0.0) /
        doppler_est_coarse_vec.size();

    // stage 3: estimate coarse phase rotation for each subevent
    Eigen::VectorXcd term_dopp = (std::complex<double>(0, -1) *
                                  doppler_est_coarse * ts_all_eigen.array())
                                     .exp();
    Eigen::VectorXcd term_slope =
        (std::complex<double>(0, -1) * slope_est * step_channel_eigen.array())
            .exp();
    Eigen::VectorXcd corrected_total =
        pct_cleaned_ap_eigen(perm_eigen).array() *
        term_slope(perm_eigen).array() * term_dopp(perm_eigen).array();

    Eigen::VectorXd phase_unwrap_detrend =
        unwrap(corrected_total.array().arg());
    Eigen::VectorXd phase_delta = diff(phase_unwrap_detrend);

    Eigen::VectorXd phi_sub_coarse = Eigen::VectorXd::Zero(num_subevent);
    for (int m = 1; m < num_subevent; ++m) {
      if (cs_algo.n_step_subevent_[m] == 0) continue;
      Eigen::VectorXd a_sub = A_frag.col(m + 1);
      Eigen::Vector<bool, Eigen::Dynamic> mask = (a_sub.array() != 0);
      Eigen::VectorXd phase_delta_masked = select_by_mask(phase_delta, mask);
      Eigen::VectorXd a_sub_masked = select_by_mask(a_sub, mask);
      if (a_sub_masked.size() == 0) continue;
      std::complex<double> mean_val =
          (std::complex<double>(0, 1) *
           (a_sub_masked.array() * phase_delta_masked.array()))
              .exp()
              .mean();
      phi_sub_coarse(m) = std::arg(mean_val);
    }

    // stage 4: use all consecutive channels after detrend
    Eigen::VectorXd phi_apply =
        Eigen::VectorXd::Zero(cs_algo.step_channel_.size());
    for (int m = 0; m < num_subevent; ++m) {
      if (cs_algo.n_step_subevent_[m] == 0) continue;
      Eigen::Vector<bool, Eigen::Dynamic> mask =
          (subevent_idx_eigen.array() == m);
      for (int i = 0; i < mask.size(); ++i) {
        if (mask(i)) phi_apply(i) = phi_sub_coarse(m);
      }
    }

    Eigen::VectorXcd term_phi =
        (std::complex<double>(0, -1) * phi_apply.array()).exp();
    corrected_total = pct_cleaned_ap_eigen(perm_eigen).array() *
                      term_slope(perm_eigen).array() *
                      term_dopp(perm_eigen).array() *
                      term_phi(perm_eigen).array();
    phase_unwrap_detrend = unwrap(corrected_total.array().arg());
    phase_delta = diff(phase_unwrap_detrend);

    Eigen::VectorXd x = A_frag.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV)
                            .solve(phase_delta);
    double doppler_est_fine = x(1);
    Eigen::VectorXd phi_sub_fine = x.tail(x.size() - 2);

    doppler_est.push_back(doppler_est_coarse + doppler_est_fine);
    phi_sub_est.push_back(phi_sub_coarse.tail(phi_sub_coarse.size() - 1) +
                          phi_sub_fine);

  }  // end AP for loop

  // estimate doppler
  double dopp_mean =
      std::accumulate(doppler_est.begin(), doppler_est.end(), 0.0) /
      doppler_est.size();
  Eigen::VectorXd phi_sub_mean = Eigen::VectorXd::Zero(num_subevent - 1);
  for (const auto& v : phi_sub_est) {
    phi_sub_mean += v;
  }
  phi_sub_mean /= phi_sub_est.size();

  cs_algo.doppler_shift_step_ = dopp_mean;
  cs_algo.velocity_ = -cs_algo.doppler_shift_step_ * kSpeedOfLight /
                      (2 * M_PI * 2.44e9 * cs_algo.t_mode2_step_us_ * 1e-6) / 2;

  // fix steps
  for (int ap = 0; ap < cs_algo.n_ap_; ++ap) {
    Eigen::Map<Eigen::VectorXcd, Eigen::Unaligned> pct_cleaned_ap_tmp(
        cs_algo.pct_cleaned_[ap].data(), cs_algo.pct_cleaned_[ap].size());
    Eigen::VectorXcd pct_cleaned_ap_eigen =
        pct_cleaned_ap_tmp.cast<std::complex<double>>();
    pct_cleaned_ap_eigen =
        pct_cleaned_ap_eigen.array() *
        (std::complex<double>(0, -1) * dopp_mean * ts_all_eigen.array()).exp();
    for (int m = 1; m < num_subevent; ++m) {
      Eigen::Vector<bool, Eigen::Dynamic> mask =
          (subevent_idx_eigen.array() == m);
      Eigen::VectorXcd correction =
          Eigen::VectorXcd::Ones(cs_algo.pct_cleaned_[ap].size());
      for (int i = 0; i < mask.size(); ++i) {
        if (mask(i)) {
          correction(i) =
              std::exp(std::complex<double>(0, -1) * phi_sub_mean(m - 1));
        }
      }
      pct_cleaned_ap_eigen = pct_cleaned_ap_eigen.array() * correction.array();
    }
    cs_algo.pct_cleaned_[ap].assign(
        pct_cleaned_ap_eigen.data(),
        pct_cleaned_ap_eigen.data() + pct_cleaned_ap_eigen.size());
  }
}

void ChannelSoundingAlgorithm::DataCleaning::UpdateDeltaF(
    ChannelSoundingAlgorithm& cs_algo) {
  uint8_t df =
      cs_algo.step_channel_cleaned_[cs_algo.step_channel_cleaned_.size() - 1] -
      cs_algo.step_channel_cleaned_[0];
  for (size_t i = 1; i < cs_algo.step_channel_cleaned_.size(); i++) {
    if (cs_algo.step_channel_cleaned_[i] -
            cs_algo.step_channel_cleaned_[i - 1] <
        df) {
      df = cs_algo.step_channel_cleaned_[i] -
           cs_algo.step_channel_cleaned_[i - 1];
    }
  }
  cs_algo.delta_f_ = df;
}

void ChannelSoundingAlgorithm::DataCleaning::CalculateAutocorr(
    ChannelSoundingAlgorithm& cs_algo) {
  size_t K = cs_algo.autocorr_K_ / cs_algo.delta_f_;
  double k_count;
  std::vector<std::vector<std::complex<double>>> R_k(
      cs_algo.n_ap_, std::vector<std::complex<double>>(K));
  for (size_t ap = 0; ap < cs_algo.n_ap_; ap++) {
    for (size_t k = 0; k < K; k++) {
      k_count = 0;
      for (size_t i = 0; i < cs_algo.step_channel_cleaned_.size(); i++) {
        for (size_t j = 0; j < cs_algo.step_channel_cleaned_.size(); j++) {
          if (cs_algo.step_channel_cleaned_[j] -
                  cs_algo.step_channel_cleaned_[i] ==
              k * cs_algo.delta_f_) {
            R_k[ap][k] += std::conj(cs_algo.pct_cleaned_[ap][i]) *
                          cs_algo.pct_cleaned_[ap][j];
            k_count++;
          }
        }
      }
      R_k[ap][k] /= k_count;
    }
  }
  cs_algo.pct_autocorr_ = R_k;
}

void ChannelSoundingAlgorithm::DataCleaning::CalculateCovarianceMatrix(
    ChannelSoundingAlgorithm& cs_algo) {
  size_t K = cs_algo.autocorr_K_ / cs_algo.delta_f_;
  std::vector<Eigen::MatrixXcd> R_k(cs_algo.n_ap_, Eigen::MatrixXcd(K, K));
  Eigen::MatrixXcd R_tmp(K, K);
  Eigen::MatrixXd add_count(K, K);
  Eigen::VectorXcd pct_segment(K);
  Eigen::VectorXd add_segment(K);
  for (size_t ap = 0; ap < cs_algo.n_ap_; ap++) {
    R_tmp = Eigen::MatrixXcd::Zero(K, K);
    add_count = Eigen::MatrixXd::Zero(K, K);

    int channel_min = static_cast<int>(cs_algo.step_channel_cleaned_.front());
    int channel_max = static_cast<int>(cs_algo.step_channel_cleaned_.back());
    int df = static_cast<int>(cs_algo.delta_f_);

    for (int ch_first = channel_min - static_cast<int>(K) * df;
         ch_first <= channel_max; ch_first += df) {
      auto it = std::lower_bound(cs_algo.step_channel_cleaned_.begin(),
                                 cs_algo.step_channel_cleaned_.end(), ch_first);
      size_t cur_pos = std::distance(cs_algo.step_channel_cleaned_.begin(), it);
      pct_segment = Eigen::VectorXcd::Zero(K);
      add_segment = Eigen::VectorXd::Zero(K);

      for (int m = 0; m < K; m++) {
        int target_channel = ch_first + m * df;
        if (cur_pos < cs_algo.step_channel_cleaned_.size() &&
            static_cast<int>(cs_algo.step_channel_cleaned_[cur_pos]) ==
                target_channel) {
          pct_segment[m] = cs_algo.pct_cleaned_[ap][cur_pos];
          add_segment[m] = 1.0;
          cur_pos++;
        } else {
          pct_segment[m] = 0.0;
          add_segment[m] = 0.0;
        }
      }
      R_tmp += pct_segment * pct_segment.adjoint();
      add_count += add_segment * add_segment.transpose();
    }
    // normalize
    for (size_t i = 0; i < K; i++) {
      for (size_t j = 0; j < K; j++) {
        if (add_count(i, j) > 0)
          R_tmp(i, j) = R_tmp(i, j) / add_count(i, j);
        else
          R_tmp(i, j) = 0;
      }
    }
    // forward backward averaging
    for (size_t i = 0; i < K; i++) {
      for (size_t j = 0; j < K; j++) {
        R_k[ap](i, j) =
            0.5 * (R_tmp(i, j) + std::conj(R_tmp(K - i - 1, K - j - 1)));
      }
    }
  }
  cs_algo.pct_covmat_ = R_k;
}

std::vector<uint8_t> ChannelSoundingAlgorithm::DataCleaning::SortPermutation(
    const std::vector<uint8_t>& vec) {
  std::vector<uint8_t> p(vec.size());
  std::iota(p.begin(), p.end(), 0);
  std::sort(p.begin(), p.end(),
            [&](std::size_t i, std::size_t j) { return (vec[i] < vec[j]); });
  return p;
}

bool ChannelSoundingAlgorithm::RangingAlgorithm::Fft::Init(size_t size) {
  size_ = size;
  log2_size_ = log2(size_);
  return true;
}

void ChannelSoundingAlgorithm::RangingAlgorithm::Fft::ComputeComplexIfft(
    const std::vector<std::complex<double>>& input,
    std::vector<std::complex<double>>& output) {
  for (int i = 0; i < size_; i++) {
    output[BitReverse(i, log2_size_)] = input[i];
  }
  int m;
  std::complex<double> t, u, omega, omega_m;
  for (int stage = 1; stage <= log2_size_; stage++) {
    m = pow(2, stage);
    omega_m = std::exp(std::complex<double>(0, 2 * M_PI / double(m)));
    for (int k = 0; k < size_; k += m) {
      omega = 1;
      for (int j = 0; j < m / 2; j++) {
        t = omega * output[k + j + m / 2];
        u = output[k + j];
        output[k + j] = u + t;
        output[k + j + m / 2] = u - t;
        omega *= omega_m;
      }
    }
  }
  for (int i = 0; i < size_; i++) {
    output[i] /= size_;
  }
}

void ChannelSoundingAlgorithm::RangingAlgorithm::Run(
    ChannelSoundingAlgorithm& cs_algo) {
  double distance_report;
  this->fft_.Init(this->fft_size_);
  if (cs_algo.apply_windowing_)
    ChannelSoundingAlgorithm::RangingAlgorithm::ApplyWindowing(cs_algo);

  if (!cs_algo.use_post_combining_) {
    switch (cs_algo.algo_type_) {
      case AlgoType::kZpIfft:
        distance_report =
            ChannelSoundingAlgorithm::RangingAlgorithm::EstimateDistanceZpIfft(
                cs_algo);
        break;
      case AlgoType::kMusic:
        distance_report =
            ChannelSoundingAlgorithm::RangingAlgorithm::EstimateDistanceMusic(
                cs_algo);
        break;
      default:
        cs_algo.raw_distance_ = 999.0;
    }
  } else {
    uint8_t ap_tmp = cs_algo.selected_ap_;

    for (size_t ap = 0; ap < cs_algo.n_ap_; ap++) {
      cs_algo.selected_ap_ = ap;
      switch (cs_algo.algo_type_) {
        case AlgoType::kZpIfft:
          distance_report = ChannelSoundingAlgorithm::RangingAlgorithm::
              EstimateDistanceZpIfft(cs_algo);
          break;
        case AlgoType::kMusic:
          distance_report =
              ChannelSoundingAlgorithm::RangingAlgorithm::EstimateDistanceMusic(
                  cs_algo);
          break;
        default:
          cs_algo.raw_distance_ = 999.0;
      }
    }
    distance_report =
        ChannelSoundingAlgorithm::RangingAlgorithm::PostCombiningChooseMin(
            cs_algo);
    cs_algo.selected_ap_ = ap_tmp;
  }
}

void ChannelSoundingAlgorithm::RangingAlgorithm::ApplyWindowing(
    ChannelSoundingAlgorithm& cs_algo) {
  std::vector<std::complex<double>> windowing(
      cs_algo.step_channel_cleaned_.size());
  for (size_t i = 0; i < windowing.size(); i++) {
    switch (cs_algo.window_func_) {
      case WindowingFunction::kHamming:
        windowing[i] = (0.54 - 0.46 * cos(2 * M_PI * i / windowing.size()));
        break;
      default:
        windowing[i] = 1;
    }
  }
  for (size_t i = 0; i < windowing.size(); i++) {
    for (size_t ap = 0; ap < cs_algo.pct_cleaned_.size(); ap++) {
      cs_algo.pct_cleaned_[ap][i] *= windowing[i];
    }
  }

  if (!cs_algo.pct_autocorr_.empty()) {
    std::vector<std::complex<double>> windowing2(cs_algo.autocorr_K_ /
                                                 cs_algo.delta_f_);
    for (size_t i = 0; i < windowing2.size(); i++) {
      switch (cs_algo.window_func_) {
        case WindowingFunction::kHamming:
          windowing2[i] =
              (0.54 - 0.46 * cos(2 * M_PI * (windowing2.size() + i) /
                                 (2 * windowing2.size() + 1)));
          break;
        default:
          windowing2[i] = 1;
      }
    }
    for (size_t i = 0; i < windowing2.size(); i++) {
      for (size_t ap = 0; ap < cs_algo.pct_autocorr_.size(); ap++) {
        cs_algo.pct_autocorr_[ap][i] *= windowing2[i];
      }
    }
  }
}

/**
 * EstimateDistanceZpIfft uses Zero-Padded Inverse Fast Fourier Transform
 * (ZP-IFFT) to estimate the channel impulse response and identify the first
 * arrival path. It is computationally efficient and robust for many typical
 * environments.
 */
double ChannelSoundingAlgorithm::RangingAlgorithm::EstimateDistanceZpIfft(
    ChannelSoundingAlgorithm& cs_algo) {
  std::vector<std::complex<double>> CFR_ZP;
  size_t CFR_size;
  std::vector<std::complex<double>> CFR;
  CFR = cs_algo.pct_autocorr_[cs_algo.selected_ap_];
  size_t K = CFR.size();
  CFR_ZP.push_back(CFR[0]);
  for (size_t k = 1; k < K; k++) {
    CFR_ZP.push_back(CFR[k]);
    CFR_ZP.insert(CFR_ZP.begin(), std::conj(CFR[k]));
  }
  CFR_size = 2 * K - 1;
  for (uint16_t i = 0; i < this->fft_size_ - CFR_size; i++)
    CFR_ZP.push_back(std::complex(0.0, 0.0));
  std::rotate(CFR_ZP.rbegin(),
              CFR_ZP.rbegin() + (this->fft_size_ - CFR_size) / 2,
              CFR_ZP.rend());
  std::vector<std::complex<double>> ifft_output(this->fft_size_);
  fft_.ComputeComplexIfft(CFR_ZP, ifft_output);

  // estimate noise level (in dB)
  std::vector<double> ifft_output_dB(this->fft_size_),
      ifft_output_power(this->fft_size_);

  for (size_t i = 0; i < fft_size_; i++) {
    ifft_output_dB[i] = 20 * log10(abs(ifft_output[i]));
    ifft_output_power[i] = std::pow(abs(ifft_output[i]), 2);
  }

  double dt = 1 / double(cs_algo.delta_f_ * 1e6 * this->fft_size_);
  size_t cir_shift_size = static_cast<size_t>(
      std::round(this->shift_distance_ * 2 * this->fft_size_ *
                 cs_algo.delta_f_ * 1e6 / kSpeedOfLight));
  double actual_shift_distance = (double)cir_shift_size / 2 /
                                 (double)this->fft_size_ /
                                 (cs_algo.delta_f_ * 1e6) * kSpeedOfLight;

  size_t noise_interval_size = (size_t)noise_est_interval_ * 2 *
                               (double)this->fft_size_ *
                               (cs_algo.delta_f_ * 1e6) / kSpeedOfLight;
  double noise_level =
      10 *
      log10(static_cast<double>(std::accumulate(
                ifft_output_power.end() - cir_shift_size - noise_interval_size,
                ifft_output_power.end() - cir_shift_size, 0.0)) /
            noise_interval_size);

  bool valid_peak;
  auto peaks = ChannelSoundingAlgorithm::RangingAlgorithm::FindPeaksInDb(
      ifft_output_dB, valid_peak, noise_level + threshold_zp_ifft_,
      cir_shift_size);
  double distance_report =
      kSpeedOfLight * dt * peaks[0].first / 2 - actual_shift_distance;

  for (size_t i = 0; i < peaks.size(); i++) {
    double peak_distance =
        static_cast<double>(peaks[i].first) * kSpeedOfLight * dt / 2 -
        this->shift_distance_;
  }
  double confidence_report;
  if (valid_peak) {
    confidence_report = 1.0;
  } else {
    confidence_report = 0.0;
  }

  cs_algo.raw_distance_ = distance_report;
  cs_algo.confidence_level_ = confidence_report;
  cs_algo.raw_distance_collection_.push_back(distance_report);
  cs_algo.confidence_level_collection_.push_back(confidence_report);

  return cs_algo.raw_distance_;
}

/**
 * EstimateDistanceMusic applies the MUltiple SIgnal Classification (MUSIC)
 * algorithm. It uses an eigendecomposition of the PCT covariance matrix to
 * achieve high-resolution time-of-flight estimation, resolving multipath
 * arrivals that are closely spaced.
 */
double ChannelSoundingAlgorithm::RangingAlgorithm::EstimateDistanceMusic(
    ChannelSoundingAlgorithm& cs_algo) {
  Eigen::MatrixXcd pct_covmat = cs_algo.pct_covmat_[cs_algo.selected_ap_];

  // new algo change: covarinace matrix calculation
  size_t K = pct_covmat.rows();
  size_t K_used = K;
  double N = std::ceil(75.0 / cs_algo.delta_f_);
  double drop_rate =
      1.0 - static_cast<double>(cs_algo.step_channel_cleaned_.size()) / N;
  if (drop_rate >= 1.0) {
    drop_rate = 1.0 - 1e-10;
  }
  size_t K_val = std::max(K_used, (size_t)1);
  double threshold_music_svd_used =
      5 * std::log10(K_val) + 5 * std::log10(N - K_used + 1) +
      this->drop_rate_penalty_ * 10 * std::log10(1.0 - drop_rate) +
      this->threshold_music_svd_;
  double threshold_music_peak_used =
      10 * std::log10(N - K_used + 1) +
      this->drop_rate_penalty_ * 20 * std::log10(1.0 - drop_rate) +
      this->threshold_music_peak_;

  std::vector<double> lambdas(K, 0.0);
  Eigen::BDCSVD<Eigen::MatrixXcd> svd(
      pct_covmat, Eigen::ComputeFullU | Eigen::ComputeFullV);
  for (size_t i = 0; i < K; i++) {
    lambdas[i] += svd.singularValues()[i];
  }
  auto U_full = svd.matrixU();

  size_t num_path = 0;
  double noise_level = 0.0;
  for (size_t i = lambdas.size() / 2; i < lambdas.size() * 3 / 4; i++) {
    noise_level += lambdas[i];
  }
  noise_level /= (lambdas.size() / 4);
  noise_level = 10 * log10(noise_level);
  double threshold_2 = 10 * log10(lambdas[0]) - 30;
  for (size_t i = 0; i < lambdas.size(); i++) {
    if (10 * log10(lambdas[i]) - noise_level > threshold_music_svd_used &&
        10 * log10(lambdas[i]) > threshold_2) {
      num_path++;
    }
  }
  bool no_path_found = false;
  if (num_path == 0) {
    no_path_found = true;
  }
  num_path = std::max(num_path, (size_t)1);
  num_path = std::min(num_path, (size_t)10);  // limit number of path to 10 only
  auto U_null = U_full(Eigen::all, Eigen::seq(num_path, U_full.cols() - 1));

  std::vector<double> J(this->music_size_, 0.0);
  Eigen::VectorXcd phi_w(K);
  double tau;
  for (size_t t = 0; t < J.size(); t++) {
    tau = t * 1e-6 / this->music_size_;
    for (int m = 0; m < K; m++) {
      phi_w(m) =
          std::exp(std::complex<double>(0, -2 * M_PI * double(m) * 1e6 * tau));
    }
    J[t] = abs(1.0 / pow((U_null.adjoint() * phi_w).norm(), 2));
  }
  for (size_t t = 0; t < J.size(); t++) {
    J[t] = 10 * log10(J[t]);
  }

  // new algo change: peak finding in MUSIC metrics
  double dt = 1 / double(cs_algo.delta_f_ * 1e6 * this->music_size_);
  size_t cir_shift_size = static_cast<size_t>(
      std::round(this->shift_distance_ * 2 * this->music_size_ *
                 cs_algo.delta_f_ * 1e6 / kSpeedOfLight));
  double actual_shift_distance = (double)cir_shift_size / 2 /
                                 (double)this->music_size_ /
                                 (cs_algo.delta_f_ * 1e6) * kSpeedOfLight;
  bool valid_peak;
  double J_noise_level = 10 * log10(1 / (double)K);
  auto peaks =
      ChannelSoundingAlgorithm::RangingAlgorithm::FindPeaksInDbWithConfidence(
          J, valid_peak, J_noise_level + threshold_music_peak_used,
          /*steepness=*/0.2, cir_shift_size, /*filter_by_threshold=*/true,
          /*valid_peak_threshold=*/7.0);
  double distance_report =
      kSpeedOfLight * dt * std::get<0>(peaks[0]) / 2 - actual_shift_distance;

  double confidence_report;
  if (no_path_found) {
    confidence_report = 0.0;
  } else {
    confidence_report = std::get<2>(peaks[0]);
  }

  cs_algo.raw_distance_ = distance_report;
  cs_algo.confidence_level_ = confidence_report;
  cs_algo.raw_distance_collection_.push_back(distance_report);
  cs_algo.confidence_level_collection_.push_back(confidence_report);

  return cs_algo.raw_distance_;
}

double ChannelSoundingAlgorithm::RangingAlgorithm::PostCombiningChooseMin(
    ChannelSoundingAlgorithm& cs_algo) {
  double distance_report = 999.0;
  double confidence_report = 0.0;

  for (size_t ap = 0; ap < cs_algo.raw_distance_collection_.size(); ap++) {
    if (cs_algo.confidence_level_collection_[ap] > 0.0) {
      if (cs_algo.raw_distance_collection_[ap] < distance_report) {
        distance_report = cs_algo.raw_distance_collection_[ap];
        confidence_report = cs_algo.confidence_level_collection_[ap];
      }
    }
  }
  if (confidence_report > 0.0) {
    cs_algo.raw_distance_ = distance_report;
    cs_algo.confidence_level_ = confidence_report;
  } else {
    cs_algo.raw_distance_ = cs_algo.raw_distance_collection_[0];
    cs_algo.confidence_level_ = 0.0;
  }

  return distance_report;
}

std::vector<std::pair<int, double>>
ChannelSoundingAlgorithm::RangingAlgorithm::FindPeaksInDb(
    std::vector<double> input, bool& valid, const double threshold,
    size_t cir_shift_size) {
  valid = true;
  std::vector<std::pair<int, double>> peaks;
  // circular shift end to begin
  rotate(input.begin(), input.end() - cir_shift_size, input.end());
  auto maxIt = std::max_element(input.begin(), input.end());
  int argmax = std::distance(input.begin(), maxIt);
  // 0
  if (input[0] > input[input.size() - 1] && input[0] > input[1] &&
      input[0] >= threshold) {
    peaks.push_back(std::make_pair(0, input[0]));
  }
  // 1 ~ N-2
  for (size_t i = 1; i < input.size() - 1; i++) {
    if (input[i] > input[i - 1] && input[i] > input[i + 1] &&
        input[i] >= threshold) {
      peaks.push_back(std::make_pair(i, input[i]));
    }
  }
  // N-1
  if (input[input.size() - 1] > input[input.size() - 2] &&
      input[input.size() - 1] > input[0] &&
      input[input.size() - 1] >= threshold) {
    peaks.push_back(std::make_pair(input.size() - 1, input[input.size() - 1]));
  }
  if (peaks.size() == 0) {
    valid = false;
    peaks.push_back(std::make_pair(argmax, *maxIt));
  }

  return peaks;
}

std::vector<std::tuple<int, double, double>>
ChannelSoundingAlgorithm::RangingAlgorithm::FindPeaksInDbWithConfidence(
    std::vector<double> input, bool& valid, double threshold, double steepness,
    size_t cir_shift_size, bool filter_by_threshold,
    double valid_peak_threshold) {
  valid = false;
  std::vector<std::tuple<int, double, double>> peaks;

  size_t n = input.size();
  if (n == 0) {
    return peaks;
  }

  if (cir_shift_size != 0) {
    std::rotate(input.begin(), input.end() - cir_shift_size, input.end());
  }

  std::vector<std::pair<int, double>> local_maxima;

  if (n == 1) {
    local_maxima.push_back(std::make_pair(0, input[0]));
  } else {
    // 0
    if (input[0] > input[n - 1] && input[0] > input[1]) {
      local_maxima.push_back(std::make_pair(0, input[0]));
    }
    // 1 ~ N-2
    for (size_t i = 1; i < n - 1; i++) {
      if (input[i] > input[i - 1] && input[i] > input[i + 1]) {
        local_maxima.push_back(std::make_pair(i, input[i]));
      }
    }
    // N-1
    if (input[n - 1] > input[n - 2] && input[n - 1] > input[0]) {
      local_maxima.push_back(std::make_pair(n - 1, input[n - 1]));
    }
  }

  for (const auto& max_pair : local_maxima) {
    int idx = max_pair.first;
    double val = max_pair.second;
    double conf = 1.0 / (1.0 + std::exp(-steepness * (val - threshold)));
    if (!filter_by_threshold || val >= (threshold - valid_peak_threshold)) {
      peaks.push_back(std::make_tuple(idx, val, conf));
      valid = true;
    }
  }

  if (peaks.empty()) {
    auto maxIt = std::max_element(input.begin(), input.end());
    int max_idx = std::distance(input.begin(), maxIt);
    double val = *maxIt;
    peaks.push_back(std::make_tuple(max_idx, val, 0.0));
    valid = false;
  }

  return peaks;
}
