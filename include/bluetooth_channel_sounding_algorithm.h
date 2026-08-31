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

#pragma once

#include <any>
#include <complex>
#include <cstdint>
#include <memory>
#include <tuple>
#include <vector>

#include "Eigen/Dense"
#include "aidl/android/hardware/bluetooth/ranging/ChannelSoudingRawData.h"
#include "aidl/android/hardware/bluetooth/ranging/ChannelSoundingProcedureData.h"
#include "aidl/android/hardware/bluetooth/ranging/Config.h"
#include "aidl/android/hardware/bluetooth/ranging/ProcedureEnableConfig.h"
#include "bluetooth_hal/extensions/cs/bluetooth_channel_sounding_distance_estimator_interface.h"

class ChannelSoundingAlgorithm : public ::bluetooth_hal::extensions::cs::
                                     ChannelSoundingDistanceEstimatorInterface {
 public:
  static std::unique_ptr<ChannelSoundingDistanceEstimatorInterface> Create() {
    return std::make_unique<ChannelSoundingAlgorithm>();
  }

  ChannelSoundingAlgorithm() = default;

  // ChannelSoundingDistanceEstimatorInterface implementation
  void ResetVariables() override;
  void SetInlinePCT(bool is_enabled) override { inline_pct_ = is_enabled; }
  double EstimateDistanceImpl(const std::any& data) override;
  double GetConfidenceLevel() override { return confidence_level_; }
  void UpdateChannelSoundingConfig(
      const ::aidl::android::hardware::bluetooth::ranging::Config& in_config)
      override;
  void UpdateProcedureEnableConfig(
      const ::aidl::android::hardware::bluetooth::ranging::
          ProcedureEnableConfig& in_procedureEnableConfig) override;
  double GetVelocity() override { return velocity_; }

  // Testbench accessors
  const ::aidl::android::hardware::bluetooth::ranging::Config& GetCsConfig()
      const {
    return cs_config_;
  }
  const ::aidl::android::hardware::bluetooth::ranging::ProcedureEnableConfig&
  GetProcedureEnableConfig() const {
    return procedure_enable_config_;
  }
  void SetSelectedAp(uint8_t selected_ap) { selected_ap_ = selected_ap; }
  double GetRawDistance() { return raw_distance_; }

 private:
  enum class AlgoType : int {
    kZpIfft = 0,
    kMusic = 1,
  };

  enum class WindowingFunction : int { kHamming };

  void ParseRawData(const ::aidl::android::hardware::bluetooth::ranging::
                        ChannelSoudingRawData& channel_souding_raw_data);
  void ChangeAlgoConfig();
  void ParseProcedureData(const ::aidl::android::hardware::bluetooth::ranging::
                              ChannelSoundingProcedureData&);
  inline int16_t ConvertToSigned(uint16_t num, uint8_t BITS) {
    unsigned msb_mask = 1 << (BITS - 1);
    int16_t num_signed = num;
    if ((num_signed & msb_mask) != 0) {
      num_signed |= ~(msb_mask - 1);
    }
    return num_signed;
  }
  inline std::complex<double> PctToComplex(
      const ::aidl::android::hardware::bluetooth::ranging::PctIQSample&
          pctIQSample) {
    int16_t signed_iSample = this->ConvertToSigned(pctIQSample.iSample, 12);
    int16_t signed_qSample = this->ConvertToSigned(pctIQSample.qSample, 12);
    std::complex<double> cn(1.0 * signed_iSample / 2048,
                            1.0 * signed_qSample / 2048);
    return cn;
  }
  const std::vector<uint8_t>& GetStepChannelCleaned() const {
    return step_channel_cleaned_;
  }
  const std::vector<std::vector<std::complex<double>>>& GetPctCleaned() const {
    return pct_cleaned_;
  }
  bool CheckPCTSize() const;

  class DataCleaning {
   public:
    DataCleaning() = default;

    void Run(ChannelSoundingAlgorithm& cs_algo);

   private:
    void MultiplyPCT(ChannelSoundingAlgorithm& cs_algo);

    void SortPCT(ChannelSoundingAlgorithm& cs_algo);

    void FixDoppler(ChannelSoundingAlgorithm& cs_algo);

    void FixDopplerFragmented(ChannelSoundingAlgorithm& cs_algo);

    void UpdateDeltaF(ChannelSoundingAlgorithm& cs_algo);

    void CalculateAutocorr(ChannelSoundingAlgorithm& cs_algo);

    void CalculateCovarianceMatrix(ChannelSoundingAlgorithm& cs_algo);

    static std::vector<uint8_t> SortPermutation(
        const std::vector<uint8_t>& vec);
  };

  class RangingAlgorithm {
   public:
    class Fft {
     public:
      bool Init(const size_t);

      void ComputeComplexIfft(const std::vector<std::complex<double>>& input,
                              std::vector<std::complex<double>>& output);

     private:
      int size_;
      int log2_size_;
    };

    RangingAlgorithm() { fft_.Init(fft_size_); }

    void Run(ChannelSoundingAlgorithm& cs_algo);

   private:
    friend class ChannelSoundingAlgorithm;

    size_t fft_size_ = 4096;
    Fft fft_;
    double noise_est_interval_ = 20;           // in meters
    double threshold_zp_ifft_ = 20;            // in dB
    double shift_distance_ = 1.0;              // in meters
    size_t music_size_ = 2048;
    double threshold_music_svd_ = 2.3;   // in dB
    double threshold_music_peak_ = 3.5;  // in dB
    double drop_rate_penalty_ = 0.8;

    void ApplyWindowing(ChannelSoundingAlgorithm& cs_algo);

    double EstimateDistanceZpIfft(ChannelSoundingAlgorithm& cs_algo);

    double EstimateDistanceMusic(ChannelSoundingAlgorithm& cs_algo);

    double PostCombiningChooseMin(ChannelSoundingAlgorithm& cs_algo);

    std::vector<std::pair<int, double>> FindPeaksInDb(
        std::vector<double> input, bool& valid,
        const double threshold_dB = -100, size_t cir_shift_size = 0);

    std::vector<std::tuple<int, double, double>> FindPeaksInDbWithConfidence(
        std::vector<double> input, bool& valid, double threshold,
        double steepness, size_t cir_shift_size, bool filter_by_threshold,
        double valid_peak_threshold);
  };

  // Objects.
  DataCleaning dataCleaning;
  RangingAlgorithm rangingAlgorithm;

  // Variables.
  std::vector<uint8_t> step_channel_;
  std::vector<uint8_t> step_channel_cleaned_;
  int reference_power_level_initiator_ = 0;  // dBm
  int reference_power_level_reflector_ = 0;  // dBm
  size_t n_ap_ = 1;
  size_t n_subevent_ = 1;
  std::vector<uint32_t> n_step_subevent_;
  std::vector<std::vector<std::complex<double>>> pct_initiator_;
  std::vector<std::vector<std::complex<double>>> pct_reflector_;
  std::vector<std::vector<std::complex<double>>> pct_cleaned_;
  std::vector<std::vector<std::complex<double>>> pct_autocorr_;
  std::vector<Eigen::MatrixXcd> pct_covmat_;
  uint8_t delta_f_ = 1;  // minimum channel space (MHz)
  std::vector<double> raw_distance_collection_;
  std::vector<double> confidence_level_collection_;
  double doppler_shift_step_ = 0.0;
  double t_mode2_step_us_ = 230;

  // Output.
  double raw_distance_ = 999.0;
  double delay_spread_ = 0.0;
  double confidence_level_ = 0.0;
  double velocity_ = 0.0;
  int rssi_ = 0;

  // Algo Configs: default is kMusic covmat and choose min.
  AlgoType algo_type_ = AlgoType::kMusic;
  WindowingFunction window_func_ = WindowingFunction::kHamming;
  bool apply_windowing_ = false;
  bool use_post_combining_ = true;
  uint8_t selected_ap_ = 0;
  uint8_t autocorr_K_ = 48;
  bool fix_doppler_ = true;
  bool inline_pct_ = false;

  // CS Configs
  ::aidl::android::hardware::bluetooth::ranging::Config cs_config_;
  ::aidl::android::hardware::bluetooth::ranging::ProcedureEnableConfig
      procedure_enable_config_;
};
