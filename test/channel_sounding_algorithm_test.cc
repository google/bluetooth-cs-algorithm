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

// ./testbench_bluetooth_channel_sounding_algorithm_v2.out <filename>.json

#include <aidl/android/hardware/bluetooth/ranging/ChannelSoundingProcedureData.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "bluetooth_channel_sounding_algorithm.h"  // Channel Sounding related algorithms (no class)

using namespace aidl::android::hardware::bluetooth::ranging;
using json = nlohmann::json;

// 1. Config Struct: Holds configuration from command-line arguments.
struct TestbenchConfig {
  std::string input_filename;
  std::string output_json_filename = "ranging_results.json";

  static TestbenchConfig from_args(int argc, char* argv[]) {
    TestbenchConfig cfg;
    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];
      if ((arg == "-i" || arg == "--input") && i + 1 < argc) {
        cfg.input_filename = argv[++i];
      } else if ((arg == "-o" || arg == "--output") && i + 1 < argc) {
        cfg.output_json_filename = argv[++i];
      } else if (arg == "-h" || arg == "--help") {
        std::cout << "Usage: " << argv[0]
                  << " -i <input.json> [-o <output.json>]" << std::endl;
        exit(0);
      } else if (cfg.input_filename.empty() && arg[0] != '-') {
        // Fallback for positional first argument as input
        cfg.input_filename = arg;
      } else if (!cfg.input_filename.empty() &&
                 cfg.output_json_filename == "ranging_results.json" &&
                 arg[0] != '-') {
        // Fallback for positional second argument as output
        cfg.output_json_filename = arg;
      }
    }

    if (cfg.input_filename.empty()) {
      std::cerr << "Error: Input filename is mandatory." << std::endl;
      std::cerr << "Usage: " << argv[0] << " -i <input.json> [-o <output.json>]"
                << std::endl;
      exit(1);
    }
    return cfg;
  }
};

// 2. DataLoader Class: Handles all JSON parsing logic.
class DataLoader {
 public:
  static ChannelSoundingProcedureData parse_procedure_data(const json& item) {
    ChannelSoundingProcedureData procedure;
    if (item.contains("procedureCounter")) {
      procedure.procedureCounter = item["procedureCounter"];
    }
    if (item.contains("procedureSequence")) {
      procedure.procedureSequence = item["procedureSequence"];
    }
    if (item.contains("initiatorSelectedTxPower")) {
      procedure.initiatorSelectedTxPower = item["initiatorSelectedTxPower"];
    }
    if (item.contains("reflectorSelectedTxPower")) {
      procedure.reflectorSelectedTxPower = item["reflectorSelectedTxPower"];
    }

    // Initiator
    if (item.contains("initiatorSubeventResultData")) {
      procedure.initiatorSubeventResultData =
          parse_subevent_data(item["initiatorSubeventResultData"]);
    }
    if (item.contains("initiatorProcedureAbortReason")) {
      if (item["initiatorProcedureAbortReason"].is_string()) {
        std::string reason = item["initiatorProcedureAbortReason"];
        if (reason == "SUCCESS") {
          procedure.initiatorProcedureAbortReason = ProcedureAbortReason::SUCCESS;
        } else {
          procedure.initiatorProcedureAbortReason = ProcedureAbortReason::UNSPECIFIED;
        }
      } else {
        procedure.initiatorProcedureAbortReason =
            item["initiatorProcedureAbortReason"] == 0
                ? ProcedureAbortReason::SUCCESS
                : ProcedureAbortReason::UNSPECIFIED;
      }
    }

    // Reflector
    if (item.contains("reflectorSubeventResultData")) {
      procedure.reflectorSubeventResultData =
          parse_subevent_data(item["reflectorSubeventResultData"]);
    }
    if (item.contains("reflectorProcedureAbortReason")) {
      if (item["reflectorProcedureAbortReason"].is_string()) {
        std::string reason = item["reflectorProcedureAbortReason"];
        if (reason == "SUCCESS") {
          procedure.reflectorProcedureAbortReason = ProcedureAbortReason::SUCCESS;
        } else {
          procedure.reflectorProcedureAbortReason = ProcedureAbortReason::UNSPECIFIED;
        }
      } else {
        procedure.reflectorProcedureAbortReason =
            item["reflectorProcedureAbortReason"] == 0
                ? ProcedureAbortReason::SUCCESS
                : ProcedureAbortReason::UNSPECIFIED;
      }
    }

    return procedure;
  }

 private:
  static std::vector<SubeventResultData> parse_subevent_data(
      const json& subevent_json) {
    std::vector<SubeventResultData> subevent_results;
    for (const auto& subevent_dict : subevent_json) {
      SubeventResultData subevent;
      subevent.numAntennaPaths = subevent_dict["numAntennaPaths"];
      subevent.frequencyCompensation = subevent_dict["frequencyCompensation"];
      subevent.referencePowerLevelDbm = subevent_dict["referencePowerLevelDbm"];
      if (subevent_dict.contains("subeventAbortReason")) {
        if (subevent_dict["subeventAbortReason"].is_string()) {
          std::string reason = subevent_dict["subeventAbortReason"];
          if (reason == "SUCCESS")
            subevent.subeventAbortReason = SubeventAbortReason::SUCCESS;
          else
            subevent.subeventAbortReason = SubeventAbortReason::UNSPECIFIED;
        } else {
          subevent.subeventAbortReason =
              subevent_dict["subeventAbortReason"] == 0
                  ? SubeventAbortReason::SUCCESS
                  : SubeventAbortReason::UNSPECIFIED;
        }
      } else {
        subevent.subeventAbortReason = SubeventAbortReason::UNSPECIFIED;
      }

      if (subevent_dict.contains("stepData")) {
        subevent.stepData = parse_step_data(subevent_dict["stepData"],
                                            subevent.numAntennaPaths);
      }
      subevent_results.push_back(subevent);
    }
    return subevent_results;
  }

  static std::vector<StepData> parse_step_data(const json& step_data_json,
                                               int8_t num_antenna_paths) {
    std::vector<StepData> step_data_vector;
    for (const auto& stepData_dict : step_data_json) {
      StepData stepData;
      stepData.stepChannel = stepData_dict["stepChannel"];
      if (stepData_dict["stepMode"].is_string()) {
        std::string mode = stepData_dict["stepMode"];
        if (mode == "TWO")
          stepData.stepMode = ModeType::TWO;
        else if (mode == "ZERO")
          stepData.stepMode = ModeType::ZERO;
        else if (mode == "ONE")
          stepData.stepMode = ModeType::ONE;
        else if (mode == "THREE")
          stepData.stepMode = ModeType::THREE;
        // Add other modes if needed
      } else {
        stepData.stepMode = stepData_dict["stepMode"];
      }
      json stepModeData_dict = stepData_dict["stepModeData"];

      switch (stepData.stepMode) {
        case ModeType::TWO: {
          ModeTwoData mode_two_data;
          mode_two_data.antennaPermutationIndex =
              stepModeData_dict["antennaPermutationIndex"];
          size_t json_ap_limit = 0;
          if (stepModeData_dict.contains("tonePctIQSamples") &&
              stepModeData_dict.contains("toneQualityIndicators") &&
              stepModeData_dict["tonePctIQSamples"].is_array() &&
              stepModeData_dict["toneQualityIndicators"].is_array()) {
            json_ap_limit =
                std::min(stepModeData_dict["tonePctIQSamples"].size(),
                         stepModeData_dict["toneQualityIndicators"].size());
          }
          size_t loop_limit =
              std::min((size_t)num_antenna_paths + 1, json_ap_limit);

          for (size_t ap = 0; ap < loop_limit; ap++) {
            PctIQSample pct;
            pct.iSample = stepModeData_dict["tonePctIQSamples"][ap]["iSample"];
            pct.qSample = stepModeData_dict["tonePctIQSamples"][ap]["qSample"];
            mode_two_data.tonePctIQSamples.push_back(pct);
            mode_two_data.toneQualityIndicators.push_back(
                stepModeData_dict["toneQualityIndicators"][ap]);
          }
          stepData.stepModeData = mode_two_data;
          break;
        }
        // Other modes can be added here if needed.
        default:
          break;
      }
      step_data_vector.push_back(stepData);
    }
    return step_data_vector;
  }

 public:
  static Config parse_config(const json& config_json) {
    Config config;
    if (config_json.contains("modeType")) {
      if (config_json["modeType"].is_string()) {
        std::string val = config_json["modeType"];
        if (val == "ZERO")
          config.modeType = ModeType::ZERO;
        else if (val == "ONE")
          config.modeType = ModeType::ONE;
        else if (val == "TWO")
          config.modeType = ModeType::TWO;
        else if (val == "THREE")
          config.modeType = ModeType::THREE;
      } else {
        config.modeType =
            static_cast<ModeType>(config_json["modeType"].get<int>());
      }
    }
    if (config_json.contains("subModeType")) {
      if (config_json["subModeType"].is_string()) {
        std::string val = config_json["subModeType"];
        if (val == "ONE")
          config.subModeType = SubModeType::ONE;
        else if (val == "TWO")
          config.subModeType = SubModeType::TWO;
        else if (val == "THREE")
          config.subModeType = SubModeType::THREE;
        else if (val == "UNUSED")
          config.subModeType = SubModeType::UNUSED;
      } else {
        config.subModeType =
            static_cast<SubModeType>(config_json["subModeType"].get<int>());
      }
    }
    if (config_json.contains("rttType")) {
      if (config_json["rttType"].is_string()) {
        std::string val = config_json["rttType"];
        if (val == "AA_COARSE")
          config.rttType = RttType::AA_COARSE;
        else if (val == "WITH_32_BIT_SOUNDING_SEQUENCE")
          config.rttType = RttType::WITH_32_BIT_SOUNDING_SEQUENCE;
        else if (val == "WITH_96_BIT_SOUNDING_SEQUENCE")
          config.rttType = RttType::WITH_96_BIT_SOUNDING_SEQUENCE;
        else if (val == "WITH_32_BIT_RANDOM_SEQUENCE")
          config.rttType = RttType::WITH_32_BIT_RANDOM_SEQUENCE;
        else if (val == "WITH_64_BIT_RANDOM_SEQUENCE")
          config.rttType = RttType::WITH_64_BIT_RANDOM_SEQUENCE;
        else if (val == "WITH_96_BIT_RANDOM_SEQUENCE")
          config.rttType = RttType::WITH_96_BIT_RANDOM_SEQUENCE;
        else if (val == "WITH_128_BIT_RANDOM_SEQUENCE")
          config.rttType = RttType::WITH_128_BIT_RANDOM_SEQUENCE;
      } else {
        config.rttType =
            static_cast<RttType>(config_json["rttType"].get<int>());
      }
    }
    if (config_json.contains("channelMap") &&
        config_json["channelMap"].is_array()) {
      for (size_t i = 0; i < std::min(config.channelMap.size(),
                                      config_json["channelMap"].size());
           ++i) {
        config.channelMap[i] = config_json["channelMap"][i];
      }
    }
    if (config_json.contains("minMainModeSteps"))
      config.minMainModeSteps = config_json["minMainModeSteps"];
    if (config_json.contains("maxMainModeSteps"))
      config.maxMainModeSteps = config_json["maxMainModeSteps"];
    if (config_json.contains("mainModeRepetition"))
      config.mainModeRepetition = config_json["mainModeRepetition"];
    if (config_json.contains("mode0Steps"))
      config.mode0Steps = config_json["mode0Steps"];
    if (config_json.contains("role")) {
      if (config_json["role"].is_string()) {
        std::string val = config_json["role"];
        if (val == "INITIATOR")
          config.role = Role::INITIATOR;
        else if (val == "REFLECTOR")
          config.role = Role::REFLECTOR;
      } else {
        config.role = static_cast<Role>(config_json["role"].get<int>());
      }
    }
    if (config_json.contains("csSyncPhyType")) {
      if (config_json["csSyncPhyType"].is_string()) {
        std::string val = config_json["csSyncPhyType"];
        if (val == "NOT_VALID_PHY")
          config.csSyncPhyType = CsSyncPhyType::NOT_VALID_PHY;
        else if (val == "LE_1M_PHY")
          config.csSyncPhyType = CsSyncPhyType::LE_1M_PHY;
        else if (val == "LE_2M_PHY")
          config.csSyncPhyType = CsSyncPhyType::LE_2M_PHY;
        else if (val == "LE_2M_2BT_PHY")
          config.csSyncPhyType = CsSyncPhyType::LE_2M_2BT_PHY;
      } else {
        config.csSyncPhyType =
            static_cast<CsSyncPhyType>(config_json["csSyncPhyType"].get<int>());
      }
    }
    if (config_json.contains("channelSelectionType")) {
      if (config_json["channelSelectionType"].is_string()) {
        std::string val = config_json["channelSelectionType"];
        if (val == "ALOGRITHM_3B")
          config.channelSelectionType = ChannelSelectionType::ALOGRITHM_3B;
        else if (val == "ALOGRITHM_3C")
          config.channelSelectionType = ChannelSelectionType::ALOGRITHM_3C;
      } else {
        config.channelSelectionType = static_cast<ChannelSelectionType>(
            config_json["channelSelectionType"].get<int>());
      }
    }
    if (config_json.contains("ch3cShapeType")) {
      if (config_json["ch3cShapeType"].is_string()) {
        std::string val = config_json["ch3cShapeType"];
        if (val == "HAT_SHAPE")
          config.ch3cShapeType = Ch3cShapeType::HAT_SHAPE;
        else if (val == "X_SHAPE")
          config.ch3cShapeType = Ch3cShapeType::X_SHAPE;
      } else {
        config.ch3cShapeType =
            static_cast<Ch3cShapeType>(config_json["ch3cShapeType"].get<int>());
      }
    }
    if (config_json.contains("ch3cJump"))
      config.ch3cJump = config_json["ch3cJump"];
    if (config_json.contains("channelMapRepetition"))
      config.channelMapRepetition = config_json["channelMapRepetition"];
    if (config_json.contains("tIp1TimeUs"))
      config.tIp1TimeUs = config_json["tIp1TimeUs"];
    if (config_json.contains("tIp2TimeUs"))
      config.tIp2TimeUs = config_json["tIp2TimeUs"];
    if (config_json.contains("tFcsTimeUs"))
      config.tFcsTimeUs = config_json["tFcsTimeUs"];
    if (config_json.contains("tPmTimeUs"))
      config.tPmTimeUs = config_json["tPmTimeUs"];
    if (config_json.contains("tSwTimeUsSupportedByLocal"))
      config.tSwTimeUsSupportedByLocal =
          config_json["tSwTimeUsSupportedByLocal"];
    if (config_json.contains("tSwTimeUsSupportedByRemote"))
      config.tSwTimeUsSupportedByRemote =
          config_json["tSwTimeUsSupportedByRemote"];
    if (config_json.contains("bleConnInterval"))
      config.bleConnInterval = config_json["bleConnInterval"];

    return config;
  }

  static ProcedureEnableConfig parse_procedure_enable_config(
      const json& config_json) {
    ProcedureEnableConfig config;
    if (config_json.contains("toneAntennaConfigSelection"))
      config.toneAntennaConfigSelection =
          config_json["toneAntennaConfigSelection"];
    if (config_json.contains("subeventLenUs"))
      config.subeventLenUs = config_json["subeventLenUs"];
    if (config_json.contains("subeventsPerEvent"))
      config.subeventsPerEvent = config_json["subeventsPerEvent"];
    if (config_json.contains("subeventInterval"))
      config.subeventInterval = config_json["subeventInterval"];
    if (config_json.contains("eventInterval"))
      config.eventInterval = config_json["eventInterval"];
    if (config_json.contains("procedureInterval"))
      config.procedureInterval = config_json["procedureInterval"];
    if (config_json.contains("procedureCount"))
      config.procedureCount = config_json["procedureCount"];
    if (config_json.contains("maxProcedureLen"))
      config.maxProcedureLen = config_json["maxProcedureLen"];
    return config;
  }
};

// 3. ResultsWriter Class: Handles writing all output files.
class ResultsWriter {
 public:
  ResultsWriter(const std::string& json_filename)
      : json_filename_(json_filename) {}

  void save_debug_json(const nlohmann::ordered_json& data) {
    std::ofstream file(json_filename_);
    if (file.is_open()) {
      file << std::setw(4) << data << std::endl;
    } else {
      std::cerr << "Error: Unable to open file for writing: " << json_filename_
                << std::endl;
    }
  }

 private:
  std::string json_filename_;
};

// 4. TestRunner Class: Orchestrates the test run.
class TestRunner {
 public:
  TestRunner(const TestbenchConfig& config) : config_(config) {}

  void run() {
    std::ifstream f(config_.input_filename);
    if (!f.is_open()) {
      std::cerr << "Error: Could not open input file: "
                << config_.input_filename << std::endl;
      return;
    }
    if (f.peek() == std::ifstream::traits_type::eof()) {
      std::cerr << "Error: Input file is empty: " << config_.input_filename
                << std::endl;
      return;
    }
    json data = json::parse(f);
    f.close();

    if (data.empty()) {
      return;
    }

    ChannelSoundingAlgorithm channelSoundingAlgorithm;

    ResultsWriter writer(config_.output_json_filename);
    nlohmann::ordered_json data_array = nlohmann::ordered_json::array();

    auto process_procedure = [&](const json& item_full) {
      ChannelSoundingProcedureData procedure =
          DataLoader::parse_procedure_data(item_full["content"]);
      channelSoundingAlgorithm.ResetVariables();
      double distance = channelSoundingAlgorithm.EstimateDistance(procedure);

      distance = channelSoundingAlgorithm.GetRawDistance();
      int confidence = static_cast<int>(
          std::round(channelSoundingAlgorithm.GetConfidenceLevel() * 100));
      double velocity = channelSoundingAlgorithm.GetVelocity();

      nlohmann::ordered_json ranging_result;
      ranging_result["type"] = "RangingResult";
      if (item_full.contains("timestamp")) {
        ranging_result["timestamp"] = item_full["timestamp"];
      }

      nlohmann::ordered_json content;
      content["resultMeters"] = distance;
      content["errorMeters"] = 0;
      content["azimuthDegrees"] = 0;
      content["errorAzimuthDegrees"] = 0;
      content["altitudeDegrees"] = 0;
      content["errorAltitudeDegrees"] = 0;
      content["delaySpreadMeters"] = 0;
      content["confidenceLevel"] = confidence;
      content["detectedAttackLevel"] = "ATTACK_IS_EXTREMELY_UNLIKELY";
      content["velocityMetersPerSecond"] = velocity;
      content["vendorSpecificCsRangingResultsData"] = nullptr;
      content["rangingResultStatus"] = "SUCCESS";
      content["timestampNanos"] = 0;
      if (item_full.contains("content") &&
          item_full["content"].contains("timestampNanos")) {
        content["timestampNanos"] = item_full["content"]["timestampNanos"];
      }

      ranging_result["content"] = content;
      data_array.push_back(ranging_result);
    };

    int total_procedures = 0;
    for (const auto& item : data) {
      if (item.contains("type") &&
          item["type"] == "ChannelSoundingProcedureData") {
        total_procedures++;
      }
    }
    int processed_procedures = 0;

    for (const auto& item : data) {
      if (!item.contains("type")) {
        std::cerr << "Error: Input item missing 'type' field" << std::endl;
        continue;
      }
      std::string type = item["type"];

      if (type == "ChannelSoundingProcedureData") {
        if (item.contains("content")) {
          process_procedure(item);
          processed_procedures++;
          if (total_procedures > 0) {
            int bar_width = 50;
            float progress = (float)processed_procedures / total_procedures;
            int pos = bar_width * progress;
            std::cout << "\r[";
            for (int i = 0; i < bar_width; ++i) {
              if (i < pos)
                std::cout << "=";
              else if (i == pos)
                std::cout << ">";
              else
                std::cout << " ";
            }
            std::cout << "] " << int(progress * 100.0) << "% ("
                      << processed_procedures << "/" << total_procedures << ")"
                      << std::flush;
          }
        }
      } else if (type == "Config") {
        channelSoundingAlgorithm.UpdateChannelSoundingConfig(
            DataLoader::parse_config(item["content"]));
      } else if (type == "ProcedureEnableConfig") {
        channelSoundingAlgorithm.UpdateProcedureEnableConfig(
            DataLoader::parse_procedure_enable_config(item["content"]));
      } else if (type == "RangingResult") {
      } else if (type == "BluetoothChannelSoundingParameters") {
      } else {
        std::cerr << "Error: Unknown type: " << type << std::endl;
      }
    }

    std::cout << std::endl;

    writer.save_debug_json(data_array);
    std::cout << "Results saved to: " << config_.output_json_filename
              << std::endl;
  }

 private:
  TestbenchConfig config_;
};

// 5. main function: Entry point of the testbench.
int main(int argc, char* argv[]) {
  std::cout << std::fixed << std::setprecision(6);
  TestbenchConfig config = TestbenchConfig::from_args(argc, argv);
  TestRunner runner(config);
  runner.run();
  return 0;
}
