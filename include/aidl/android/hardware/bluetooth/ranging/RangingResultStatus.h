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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/RangingResultStatus.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/RangingResultStatus.aidl
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
enum class RangingResultStatus : int8_t {
  SUCCESS = 0,
  FAIL_INITIATOR_ABORT = 1,
  FAIL_REFLECTOR_ABORT = 2,
  FAIL_BOTH_ABORT = 3,
  FAIL_UNSPECIFIED = -1,
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
[[nodiscard]] static inline std::string toString(RangingResultStatus val) {
  switch(val) {
  case RangingResultStatus::SUCCESS:
    return "SUCCESS";
  case RangingResultStatus::FAIL_INITIATOR_ABORT:
    return "FAIL_INITIATOR_ABORT";
  case RangingResultStatus::FAIL_REFLECTOR_ABORT:
    return "FAIL_REFLECTOR_ABORT";
  case RangingResultStatus::FAIL_BOTH_ABORT:
    return "FAIL_BOTH_ABORT";
  case RangingResultStatus::FAIL_UNSPECIFIED:
    return "FAIL_UNSPECIFIED";
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
// constexpr inline std::array<aidl::android::hardware::bluetooth::ranging::RangingResultStatus, 5> enum_values<aidl::android::hardware::bluetooth::ranging::RangingResultStatus> = {
//   aidl::android::hardware::bluetooth::ranging::RangingResultStatus::SUCCESS,
//   aidl::android::hardware::bluetooth::ranging::RangingResultStatus::FAIL_INITIATOR_ABORT,
//   aidl::android::hardware::bluetooth::ranging::RangingResultStatus::FAIL_REFLECTOR_ABORT,
//   aidl::android::hardware::bluetooth::ranging::RangingResultStatus::FAIL_BOTH_ABORT,
//   aidl::android::hardware::bluetooth::ranging::RangingResultStatus::FAIL_UNSPECIFIED,
// };
// #pragma clang diagnostic pop
// }  // namespace internal
// }  // namespace ndk
