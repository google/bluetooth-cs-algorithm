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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/RttType.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/RttType.aidl
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
enum class RttType : int32_t {
  AA_COARSE = 0,
  WITH_32_BIT_SOUNDING_SEQUENCE = 1,
  WITH_96_BIT_SOUNDING_SEQUENCE = 2,
  WITH_32_BIT_RANDOM_SEQUENCE = 3,
  WITH_64_BIT_RANDOM_SEQUENCE = 4,
  WITH_96_BIT_RANDOM_SEQUENCE = 5,
  WITH_128_BIT_RANDOM_SEQUENCE = 6,
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
[[nodiscard]] static inline std::string toString(RttType val) {
  switch(val) {
  case RttType::AA_COARSE:
    return "AA_COARSE";
  case RttType::WITH_32_BIT_SOUNDING_SEQUENCE:
    return "WITH_32_BIT_SOUNDING_SEQUENCE";
  case RttType::WITH_96_BIT_SOUNDING_SEQUENCE:
    return "WITH_96_BIT_SOUNDING_SEQUENCE";
  case RttType::WITH_32_BIT_RANDOM_SEQUENCE:
    return "WITH_32_BIT_RANDOM_SEQUENCE";
  case RttType::WITH_64_BIT_RANDOM_SEQUENCE:
    return "WITH_64_BIT_RANDOM_SEQUENCE";
  case RttType::WITH_96_BIT_RANDOM_SEQUENCE:
    return "WITH_96_BIT_RANDOM_SEQUENCE";
  case RttType::WITH_128_BIT_RANDOM_SEQUENCE:
    return "WITH_128_BIT_RANDOM_SEQUENCE";
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
// constexpr inline std::array<aidl::android::hardware::bluetooth::ranging::RttType, 7> enum_values<aidl::android::hardware::bluetooth::ranging::RttType> = {
//   aidl::android::hardware::bluetooth::ranging::RttType::AA_COARSE,
//   aidl::android::hardware::bluetooth::ranging::RttType::WITH_32_BIT_SOUNDING_SEQUENCE,
//   aidl::android::hardware::bluetooth::ranging::RttType::WITH_96_BIT_SOUNDING_SEQUENCE,
//   aidl::android::hardware::bluetooth::ranging::RttType::WITH_32_BIT_RANDOM_SEQUENCE,
//   aidl::android::hardware::bluetooth::ranging::RttType::WITH_64_BIT_RANDOM_SEQUENCE,
//   aidl::android::hardware::bluetooth::ranging::RttType::WITH_96_BIT_RANDOM_SEQUENCE,
//   aidl::android::hardware::bluetooth::ranging::RttType::WITH_128_BIT_RANDOM_SEQUENCE,
// };
// #pragma clang diagnostic pop
// }  // namespace internal
// }  // namespace ndk
