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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/ModeOneData.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/ModeOneData.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
// #include <android/binder_interface_utils.h>
// #include <android/binder_parcelable_utils.h>
// #include <android/binder_to_string.h>
#include <aidl/android/hardware/bluetooth/ranging/Nadm.h>
#include <aidl/android/hardware/bluetooth/ranging/PctIQSample.h>
#include <aidl/android/hardware/bluetooth/ranging/RttToaTodData.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::bluetooth::ranging {
class PctIQSample;
}  // namespace aidl::android::hardware::bluetooth::ranging
namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
class ModeOneData {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  int8_t packetQuality = 0;
  ::aidl::android::hardware::bluetooth::ranging::Nadm packetNadm = ::aidl::android::hardware::bluetooth::ranging::Nadm(0);
  int8_t packetRssiDbm = 127;
  ::aidl::android::hardware::bluetooth::ranging::RttToaTodData rttToaTodData;
  int8_t packetAntenna = 0;
  std::optional<::aidl::android::hardware::bluetooth::ranging::PctIQSample> packetPct1;
  std::optional<::aidl::android::hardware::bluetooth::ranging::PctIQSample> packetPct2;

  // binder_status_t readFromParcel(const AParcel* parcel);
  // binder_status_t writeToParcel(AParcel* parcel) const;

  inline bool operator==(const ModeOneData& _rhs) const {
    return std::tie(packetQuality, packetNadm, packetRssiDbm, rttToaTodData, packetAntenna, packetPct1, packetPct2) == std::tie(_rhs.packetQuality, _rhs.packetNadm, _rhs.packetRssiDbm, _rhs.rttToaTodData, _rhs.packetAntenna, _rhs.packetPct1, _rhs.packetPct2);
  }
  inline bool operator<(const ModeOneData& _rhs) const {
    return std::tie(packetQuality, packetNadm, packetRssiDbm, rttToaTodData, packetAntenna, packetPct1, packetPct2) < std::tie(_rhs.packetQuality, _rhs.packetNadm, _rhs.packetRssiDbm, _rhs.rttToaTodData, _rhs.packetAntenna, _rhs.packetPct1, _rhs.packetPct2);
  }
  inline bool operator!=(const ModeOneData& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const ModeOneData& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const ModeOneData& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const ModeOneData& _rhs) const {
    return !(_rhs < *this);
  }

  // static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  enum : int8_t { FLAG_CS_ACCESS_ADDR_SUCCESS = 0 };
  enum : int8_t { FLAG_CS_ACCESS_ADDR_ERRORS = 1 };
  enum : int8_t { FLAG_CS_ACCESS_ADDR_NOT_FOUND = 2 };
  enum : int8_t { FLAG_CS_ACCESS_ADDR_MASK = 15 };
  enum : int8_t { RANDOM_OR_SOUNDING_SEQUENCE_ERROR_COUNT_SHIFT = 4 };
  enum : int8_t { PACKET_RSSI_UNAVAILABLE = 127 };
  // inline std::string toString() const {
  //   std::ostringstream _aidl_os;
  //   _aidl_os << "ModeOneData{";
  //   _aidl_os << "packetQuality: " << ::android::internal::ToString(packetQuality);
  //   _aidl_os << ", packetNadm: " << ::android::internal::ToString(packetNadm);
  //   _aidl_os << ", packetRssiDbm: " << ::android::internal::ToString(packetRssiDbm);
  //   _aidl_os << ", rttToaTodData: " << ::android::internal::ToString(rttToaTodData);
  //   _aidl_os << ", packetAntenna: " << ::android::internal::ToString(packetAntenna);
  //   _aidl_os << ", packetPct1: " << ::android::internal::ToString(packetPct1);
  //   _aidl_os << ", packetPct2: " << ::android::internal::ToString(packetPct2);
  //   _aidl_os << "}";
  //   return _aidl_os.str();
  // }
};
}  // namespace ranging
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
