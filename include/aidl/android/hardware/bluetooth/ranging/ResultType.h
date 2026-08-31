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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/ResultType.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/ResultType.aidl
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
enum class ResultType : int32_t {
  RESULT_METERS = 0,
  ERROR_METERS = 1,
  AZIMUTH_DEGREES = 2,
  ERROR_AZIMUTH_DEGREES = 3,
  ALTITUDE_DEGREES = 4,
  ERROR_ALTITUDE_DEGREES = 5,
  DELAY_SPREAD_METERS = 6,
  CONFIDENCE_LEVEL = 7,
  SECURITY_LEVEL = 8,
  VELOCITY = 9,
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
[[nodiscard]] static inline std::string toString(ResultType val) {
  switch(val) {
  case ResultType::RESULT_METERS:
    return "RESULT_METERS";
  case ResultType::ERROR_METERS:
    return "ERROR_METERS";
  case ResultType::AZIMUTH_DEGREES:
    return "AZIMUTH_DEGREES";
  case ResultType::ERROR_AZIMUTH_DEGREES:
    return "ERROR_AZIMUTH_DEGREES";
  case ResultType::ALTITUDE_DEGREES:
    return "ALTITUDE_DEGREES";
  case ResultType::ERROR_ALTITUDE_DEGREES:
    return "ERROR_ALTITUDE_DEGREES";
  case ResultType::DELAY_SPREAD_METERS:
    return "DELAY_SPREAD_METERS";
  case ResultType::CONFIDENCE_LEVEL:
    return "CONFIDENCE_LEVEL";
  case ResultType::SECURITY_LEVEL:
    return "SECURITY_LEVEL";
  case ResultType::VELOCITY:
    return "VELOCITY";
  default:
    return std::to_string(static_cast<int32_t>(val));
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
// constexpr inline std::array<aidl::android::hardware::bluetooth::ranging::ResultType, 10> enum_values<aidl::android::hardware::bluetooth::ranging::ResultType> = {
//   aidl::android::hardware::bluetooth::ranging::ResultType::RESULT_METERS,
//   aidl::android::hardware::bluetooth::ranging::ResultType::ERROR_METERS,
//   aidl::android::hardware::bluetooth::ranging::ResultType::AZIMUTH_DEGREES,
//   aidl::android::hardware::bluetooth::ranging::ResultType::ERROR_AZIMUTH_DEGREES,
//   aidl::android::hardware::bluetooth::ranging::ResultType::ALTITUDE_DEGREES,
//   aidl::android::hardware::bluetooth::ranging::ResultType::ERROR_ALTITUDE_DEGREES,
//   aidl::android::hardware::bluetooth::ranging::ResultType::DELAY_SPREAD_METERS,
//   aidl::android::hardware::bluetooth::ranging::ResultType::CONFIDENCE_LEVEL,
//   aidl::android::hardware::bluetooth::ranging::ResultType::SECURITY_LEVEL,
//   aidl::android::hardware::bluetooth::ranging::ResultType::VELOCITY,
// };
// #pragma clang diagnostic pop
// }  // namespace internal
// }  // namespace ndk
