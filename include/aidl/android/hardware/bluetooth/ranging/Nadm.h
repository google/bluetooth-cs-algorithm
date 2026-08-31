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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/Nadm.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/Nadm.aidl
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
enum class Nadm : int8_t {
  ATTACK_IS_EXTREMELY_UNLIKELY = 0,
  ATTACK_IS_VERY_UNLIKELY = 1,
  ATTACK_IS_UNLIKELY = 2,
  ATTACK_IS_POSSIBLE = 3,
  ATTACK_IS_LIKELY = 4,
  ATTACK_IS_VERY_LIKELY = 5,
  ATTACK_IS_EXTREMELY_LIKELY = 6,
  UNKNOWN = -1,
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
[[nodiscard]] static inline std::string toString(Nadm val) {
  switch(val) {
  case Nadm::ATTACK_IS_EXTREMELY_UNLIKELY:
    return "ATTACK_IS_EXTREMELY_UNLIKELY";
  case Nadm::ATTACK_IS_VERY_UNLIKELY:
    return "ATTACK_IS_VERY_UNLIKELY";
  case Nadm::ATTACK_IS_UNLIKELY:
    return "ATTACK_IS_UNLIKELY";
  case Nadm::ATTACK_IS_POSSIBLE:
    return "ATTACK_IS_POSSIBLE";
  case Nadm::ATTACK_IS_LIKELY:
    return "ATTACK_IS_LIKELY";
  case Nadm::ATTACK_IS_VERY_LIKELY:
    return "ATTACK_IS_VERY_LIKELY";
  case Nadm::ATTACK_IS_EXTREMELY_LIKELY:
    return "ATTACK_IS_EXTREMELY_LIKELY";
  case Nadm::UNKNOWN:
    return "UNKNOWN";
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
// constexpr inline std::array<aidl::android::hardware::bluetooth::ranging::Nadm, 8> enum_values<aidl::android::hardware::bluetooth::ranging::Nadm> = {
//   aidl::android::hardware::bluetooth::ranging::Nadm::ATTACK_IS_EXTREMELY_UNLIKELY,
//   aidl::android::hardware::bluetooth::ranging::Nadm::ATTACK_IS_VERY_UNLIKELY,
//   aidl::android::hardware::bluetooth::ranging::Nadm::ATTACK_IS_UNLIKELY,
//   aidl::android::hardware::bluetooth::ranging::Nadm::ATTACK_IS_POSSIBLE,
//   aidl::android::hardware::bluetooth::ranging::Nadm::ATTACK_IS_LIKELY,
//   aidl::android::hardware::bluetooth::ranging::Nadm::ATTACK_IS_VERY_LIKELY,
//   aidl::android::hardware::bluetooth::ranging::Nadm::ATTACK_IS_EXTREMELY_LIKELY,
//   aidl::android::hardware::bluetooth::ranging::Nadm::UNKNOWN,
// };
// #pragma clang diagnostic pop
// }  // namespace internal
// }  // namespace ndk
