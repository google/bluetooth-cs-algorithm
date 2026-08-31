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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/ChannelSoundingSingleSideData.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/ChannelSoundingSingleSideData.aidl
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
#include <aidl/android/hardware/bluetooth/ranging/ComplexNumber.h>
#include <aidl/android/hardware/bluetooth/ranging/Nadm.h>
#include <aidl/android/hardware/bluetooth/ranging/StepTonePct.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::bluetooth::ranging {
class ComplexNumber;
class StepTonePct;
}  // namespace aidl::android::hardware::bluetooth::ranging
namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
class ChannelSoundingSingleSideData {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::ranging::StepTonePct>>> stepTonePcts;
  std::optional<std::vector<uint8_t>> packetQuality;
  std::optional<std::vector<uint8_t>> packetRssiDbm;
  std::optional<std::vector<::aidl::android::hardware::bluetooth::ranging::Nadm>> packetNadm;
  std::optional<std::vector<int32_t>> measuredFreqOffset;
  std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::ranging::ComplexNumber>>> packetPct1;
  std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::ranging::ComplexNumber>>> packetPct2;
  int8_t referencePowerDbm = 0;
  std::optional<std::vector<uint8_t>> vendorSpecificCsSingleSidedata;

  // binder_status_t readFromParcel(const AParcel* parcel);
  // binder_status_t writeToParcel(AParcel* parcel) const;

  inline bool operator==(const ChannelSoundingSingleSideData& _rhs) const {
    return std::tie(stepTonePcts, packetQuality, packetRssiDbm, packetNadm, measuredFreqOffset, packetPct1, packetPct2, referencePowerDbm, vendorSpecificCsSingleSidedata) == std::tie(_rhs.stepTonePcts, _rhs.packetQuality, _rhs.packetRssiDbm, _rhs.packetNadm, _rhs.measuredFreqOffset, _rhs.packetPct1, _rhs.packetPct2, _rhs.referencePowerDbm, _rhs.vendorSpecificCsSingleSidedata);
  }
  inline bool operator<(const ChannelSoundingSingleSideData& _rhs) const {
    return std::tie(stepTonePcts, packetQuality, packetRssiDbm, packetNadm, measuredFreqOffset, packetPct1, packetPct2, referencePowerDbm, vendorSpecificCsSingleSidedata) < std::tie(_rhs.stepTonePcts, _rhs.packetQuality, _rhs.packetRssiDbm, _rhs.packetNadm, _rhs.measuredFreqOffset, _rhs.packetPct1, _rhs.packetPct2, _rhs.referencePowerDbm, _rhs.vendorSpecificCsSingleSidedata);
  }
  inline bool operator!=(const ChannelSoundingSingleSideData& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const ChannelSoundingSingleSideData& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const ChannelSoundingSingleSideData& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const ChannelSoundingSingleSideData& _rhs) const {
    return !(_rhs < *this);
  }

  // static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  // inline std::string toString() const {
  //   std::ostringstream _aidl_os;
  //   _aidl_os << "ChannelSoundingSingleSideData{";
  //   _aidl_os << "stepTonePcts: " << ::android::internal::ToString(stepTonePcts);
  //   _aidl_os << ", packetQuality: " << ::android::internal::ToString(packetQuality);
  //   _aidl_os << ", packetRssiDbm: " << ::android::internal::ToString(packetRssiDbm);
  //   _aidl_os << ", packetNadm: " << ::android::internal::ToString(packetNadm);
  //   _aidl_os << ", measuredFreqOffset: " << ::android::internal::ToString(measuredFreqOffset);
  //   _aidl_os << ", packetPct1: " << ::android::internal::ToString(packetPct1);
  //   _aidl_os << ", packetPct2: " << ::android::internal::ToString(packetPct2);
  //   _aidl_os << ", referencePowerDbm: " << ::android::internal::ToString(referencePowerDbm);
  //   _aidl_os << ", vendorSpecificCsSingleSidedata: " << ::android::internal::ToString(vendorSpecificCsSingleSidedata);
  //   _aidl_os << "}";
  //   return _aidl_os.str();
  // }
};
}  // namespace ranging
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
