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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/Reason.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/Reason.aidl
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
enum class Reason : int32_t {
  LOCAL_STACK_REQUEST = 0,
  HAL_INITIATED = 1,
  HARDWARE_INITIATED = 2,
  ERROR_INVALID_PARAMETER = 3,
  ERROR_UNKNOWN = 4,
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
[[nodiscard]] static inline std::string toString(Reason val) {
  switch(val) {
  case Reason::LOCAL_STACK_REQUEST:
    return "LOCAL_STACK_REQUEST";
  case Reason::HAL_INITIATED:
    return "HAL_INITIATED";
  case Reason::HARDWARE_INITIATED:
    return "HARDWARE_INITIATED";
  case Reason::ERROR_INVALID_PARAMETER:
    return "ERROR_INVALID_PARAMETER";
  case Reason::ERROR_UNKNOWN:
    return "ERROR_UNKNOWN";
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
// constexpr inline std::array<aidl::android::hardware::bluetooth::ranging::Reason, 5> enum_values<aidl::android::hardware::bluetooth::ranging::Reason> = {
//   aidl::android::hardware::bluetooth::ranging::Reason::LOCAL_STACK_REQUEST,
//   aidl::android::hardware::bluetooth::ranging::Reason::HAL_INITIATED,
//   aidl::android::hardware::bluetooth::ranging::Reason::HARDWARE_INITIATED,
//   aidl::android::hardware::bluetooth::ranging::Reason::ERROR_INVALID_PARAMETER,
//   aidl::android::hardware::bluetooth::ranging::Reason::ERROR_UNKNOWN,
// };
// #pragma clang diagnostic pop
// }  // namespace internal
// }  // namespace ndk
