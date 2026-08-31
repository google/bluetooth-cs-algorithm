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

/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/ProcedureAbortReason.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/ProcedureAbortReason.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
// #include <android/binder_enums.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
enum class ProcedureAbortReason : int8_t {
  SUCCESS = 0,
  LOCAL_OR_REMOTE_REQUEST = 1,
  FILTERED_CHANNEL_MAP_LESS_THAN_15 = 2,
  CHANNEL_MAP_UPDATE_INSTANT_PASSED = 3,
  UNSPECIFIED = 15,
};

}  // namespace ranging
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
[[nodiscard]] static inline std::string toString(ProcedureAbortReason val) {
  switch(val) {
  case ProcedureAbortReason::SUCCESS:
    return "SUCCESS";
  case ProcedureAbortReason::LOCAL_OR_REMOTE_REQUEST:
    return "LOCAL_OR_REMOTE_REQUEST";
  case ProcedureAbortReason::FILTERED_CHANNEL_MAP_LESS_THAN_15:
    return "FILTERED_CHANNEL_MAP_LESS_THAN_15";
  case ProcedureAbortReason::CHANNEL_MAP_UPDATE_INSTANT_PASSED:
    return "CHANNEL_MAP_UPDATE_INSTANT_PASSED";
  case ProcedureAbortReason::UNSPECIFIED:
    return "UNSPECIFIED";
  default:
    return std::to_string(static_cast<int8_t>(val));
  }
}
}  // namespace ranging
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
// namespace ndk {
// namespace internal {
// #pragma clang diagnostic push
// #pragma clang diagnostic ignored "-Wc++17-extensions"
// template <>
// constexpr inline std::array<aidl::android::hardware::bluetooth::ranging::ProcedureAbortReason, 5> enum_values<aidl::android::hardware::bluetooth::ranging::ProcedureAbortReason> = {
//   aidl::android::hardware::bluetooth::ranging::ProcedureAbortReason::SUCCESS,
//   aidl::android::hardware::bluetooth::ranging::ProcedureAbortReason::LOCAL_OR_REMOTE_REQUEST,
//   aidl::android::hardware::bluetooth::ranging::ProcedureAbortReason::FILTERED_CHANNEL_MAP_LESS_THAN_15,
//   aidl::android::hardware::bluetooth::ranging::ProcedureAbortReason::CHANNEL_MAP_UPDATE_INSTANT_PASSED,
//   aidl::android::hardware::bluetooth::ranging::ProcedureAbortReason::UNSPECIFIED,
// };
// #pragma clang diagnostic pop
// }  // namespace internal
// }  // namespace ndk
