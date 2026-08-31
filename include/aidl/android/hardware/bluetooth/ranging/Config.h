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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/Config.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/Config.aidl
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
#include <aidl/android/hardware/bluetooth/ranging/Ch3cShapeType.h>
#include <aidl/android/hardware/bluetooth/ranging/ChannelSelectionType.h>
#include <aidl/android/hardware/bluetooth/ranging/CsSyncPhyType.h>
#include <aidl/android/hardware/bluetooth/ranging/ModeType.h>
#include <aidl/android/hardware/bluetooth/ranging/Role.h>
#include <aidl/android/hardware/bluetooth/ranging/RttType.h>
#include <aidl/android/hardware/bluetooth/ranging/SubModeType.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
class Config {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  ::aidl::android::hardware::bluetooth::ranging::ModeType modeType = ::aidl::android::hardware::bluetooth::ranging::ModeType(0);
  ::aidl::android::hardware::bluetooth::ranging::SubModeType subModeType = ::aidl::android::hardware::bluetooth::ranging::SubModeType(0);
  ::aidl::android::hardware::bluetooth::ranging::RttType rttType = ::aidl::android::hardware::bluetooth::ranging::RttType(0);
  std::array<uint8_t, 10> channelMap = {{}};
  int32_t minMainModeSteps = 0;
  int32_t maxMainModeSteps = 0;
  int8_t mainModeRepetition = 0;
  int8_t mode0Steps = 0;
  ::aidl::android::hardware::bluetooth::ranging::Role role = ::aidl::android::hardware::bluetooth::ranging::Role(0);
  ::aidl::android::hardware::bluetooth::ranging::CsSyncPhyType csSyncPhyType = ::aidl::android::hardware::bluetooth::ranging::CsSyncPhyType(0);
  ::aidl::android::hardware::bluetooth::ranging::ChannelSelectionType channelSelectionType = ::aidl::android::hardware::bluetooth::ranging::ChannelSelectionType(0);
  ::aidl::android::hardware::bluetooth::ranging::Ch3cShapeType ch3cShapeType = ::aidl::android::hardware::bluetooth::ranging::Ch3cShapeType(0);
  int8_t ch3cJump = 0;
  int32_t channelMapRepetition = 0;
  int32_t tIp1TimeUs = 0;
  int32_t tIp2TimeUs = 0;
  int32_t tFcsTimeUs = 0;
  int8_t tPmTimeUs = 0;
  int8_t tSwTimeUsSupportedByLocal = 0;
  int8_t tSwTimeUsSupportedByRemote = 0;
  int32_t bleConnInterval = 0;

  // binder_status_t readFromParcel(const AParcel* parcel);
  // binder_status_t writeToParcel(AParcel* parcel) const;

  inline bool operator==(const Config& _rhs) const {
    return std::tie(modeType, subModeType, rttType, channelMap, minMainModeSteps, maxMainModeSteps, mainModeRepetition, mode0Steps, role, csSyncPhyType, channelSelectionType, ch3cShapeType, ch3cJump, channelMapRepetition, tIp1TimeUs, tIp2TimeUs, tFcsTimeUs, tPmTimeUs, tSwTimeUsSupportedByLocal, tSwTimeUsSupportedByRemote, bleConnInterval) == std::tie(_rhs.modeType, _rhs.subModeType, _rhs.rttType, _rhs.channelMap, _rhs.minMainModeSteps, _rhs.maxMainModeSteps, _rhs.mainModeRepetition, _rhs.mode0Steps, _rhs.role, _rhs.csSyncPhyType, _rhs.channelSelectionType, _rhs.ch3cShapeType, _rhs.ch3cJump, _rhs.channelMapRepetition, _rhs.tIp1TimeUs, _rhs.tIp2TimeUs, _rhs.tFcsTimeUs, _rhs.tPmTimeUs, _rhs.tSwTimeUsSupportedByLocal, _rhs.tSwTimeUsSupportedByRemote, _rhs.bleConnInterval);
  }
  inline bool operator<(const Config& _rhs) const {
    return std::tie(modeType, subModeType, rttType, channelMap, minMainModeSteps, maxMainModeSteps, mainModeRepetition, mode0Steps, role, csSyncPhyType, channelSelectionType, ch3cShapeType, ch3cJump, channelMapRepetition, tIp1TimeUs, tIp2TimeUs, tFcsTimeUs, tPmTimeUs, tSwTimeUsSupportedByLocal, tSwTimeUsSupportedByRemote, bleConnInterval) < std::tie(_rhs.modeType, _rhs.subModeType, _rhs.rttType, _rhs.channelMap, _rhs.minMainModeSteps, _rhs.maxMainModeSteps, _rhs.mainModeRepetition, _rhs.mode0Steps, _rhs.role, _rhs.csSyncPhyType, _rhs.channelSelectionType, _rhs.ch3cShapeType, _rhs.ch3cJump, _rhs.channelMapRepetition, _rhs.tIp1TimeUs, _rhs.tIp2TimeUs, _rhs.tFcsTimeUs, _rhs.tPmTimeUs, _rhs.tSwTimeUsSupportedByLocal, _rhs.tSwTimeUsSupportedByRemote, _rhs.bleConnInterval);
  }
  inline bool operator!=(const Config& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const Config& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const Config& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const Config& _rhs) const {
    return !(_rhs < *this);
  }

  // static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  // enum : int32_t { BLE_CONN_INTERVAL_UNAVAILABLE = 0 };
  // inline std::string toString() const {
  //   std::ostringstream _aidl_os;
  //   _aidl_os << "Config{";
  //   _aidl_os << "modeType: " << ::android::internal::ToString(modeType);
  //   _aidl_os << ", subModeType: " << ::android::internal::ToString(subModeType);
  //   _aidl_os << ", rttType: " << ::android::internal::ToString(rttType);
  //   _aidl_os << ", channelMap: " << ::android::internal::ToString(channelMap);
  //   _aidl_os << ", minMainModeSteps: " << ::android::internal::ToString(minMainModeSteps);
  //   _aidl_os << ", maxMainModeSteps: " << ::android::internal::ToString(maxMainModeSteps);
  //   _aidl_os << ", mainModeRepetition: " << ::android::internal::ToString(mainModeRepetition);
  //   _aidl_os << ", mode0Steps: " << ::android::internal::ToString(mode0Steps);
  //   _aidl_os << ", role: " << ::android::internal::ToString(role);
  //   _aidl_os << ", csSyncPhyType: " << ::android::internal::ToString(csSyncPhyType);
  //   _aidl_os << ", channelSelectionType: " << ::android::internal::ToString(channelSelectionType);
  //   _aidl_os << ", ch3cShapeType: " << ::android::internal::ToString(ch3cShapeType);
  //   _aidl_os << ", ch3cJump: " << ::android::internal::ToString(ch3cJump);
  //   _aidl_os << ", channelMapRepetition: " << ::android::internal::ToString(channelMapRepetition);
  //   _aidl_os << ", tIp1TimeUs: " << ::android::internal::ToString(tIp1TimeUs);
  //   _aidl_os << ", tIp2TimeUs: " << ::android::internal::ToString(tIp2TimeUs);
  //   _aidl_os << ", tFcsTimeUs: " << ::android::internal::ToString(tFcsTimeUs);
  //   _aidl_os << ", tPmTimeUs: " << ::android::internal::ToString(tPmTimeUs);
  //   _aidl_os << ", tSwTimeUsSupportedByLocal: " << ::android::internal::ToString(tSwTimeUsSupportedByLocal);
  //   _aidl_os << ", tSwTimeUsSupportedByRemote: " << ::android::internal::ToString(tSwTimeUsSupportedByRemote);
  //   _aidl_os << ", bleConnInterval: " << ::android::internal::ToString(bleConnInterval);
  //   _aidl_os << "}";
  //   return _aidl_os.str();
  // }
};
}  // namespace ranging
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
