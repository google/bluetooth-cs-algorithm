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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/SubeventAbortReason.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/SubeventAbortReason.aidl
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
enum class SubeventAbortReason : int8_t {
  SUCCESS = 0,
  LOCAL_OR_REMOTE_REQUEST = 1,
  NO_CS_SYNC_RECEIVED = 2,
  SCHEDULING_CONFLICTS_OR_LIMITED_RESOURCES = 3,
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
[[nodiscard]] static inline std::string toString(SubeventAbortReason val) {
  switch(val) {
  case SubeventAbortReason::SUCCESS:
    return "SUCCESS";
  case SubeventAbortReason::LOCAL_OR_REMOTE_REQUEST:
    return "LOCAL_OR_REMOTE_REQUEST";
  case SubeventAbortReason::NO_CS_SYNC_RECEIVED:
    return "NO_CS_SYNC_RECEIVED";
  case SubeventAbortReason::SCHEDULING_CONFLICTS_OR_LIMITED_RESOURCES:
    return "SCHEDULING_CONFLICTS_OR_LIMITED_RESOURCES";
  case SubeventAbortReason::UNSPECIFIED:
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
// constexpr inline std::array<aidl::android::hardware::bluetooth::ranging::SubeventAbortReason, 5> enum_values<aidl::android::hardware::bluetooth::ranging::SubeventAbortReason> = {
//   aidl::android::hardware::bluetooth::ranging::SubeventAbortReason::SUCCESS,
//   aidl::android::hardware::bluetooth::ranging::SubeventAbortReason::LOCAL_OR_REMOTE_REQUEST,
//   aidl::android::hardware::bluetooth::ranging::SubeventAbortReason::NO_CS_SYNC_RECEIVED,
//   aidl::android::hardware::bluetooth::ranging::SubeventAbortReason::SCHEDULING_CONFLICTS_OR_LIMITED_RESOURCES,
//   aidl::android::hardware::bluetooth::ranging::SubeventAbortReason::UNSPECIFIED,
// };
// #pragma clang diagnostic pop
// }  // namespace internal
// }  // namespace ndk
