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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/BluetoothChannelSoundingParameters.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/BluetoothChannelSoundingParameters.aidl
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
#include <android/binder_interface_utils.h>
#include <android/binder_parcelable_utils.h>
#include <android/binder_to_string.h>
#include <aidl/android/hardware/bluetooth/ranging/Config.h>
#include <aidl/android/hardware/bluetooth/ranging/DeviceAddress.h>
#include <aidl/android/hardware/bluetooth/ranging/LocationType.h>
#include <aidl/android/hardware/bluetooth/ranging/Role.h>
#include <aidl/android/hardware/bluetooth/ranging/SessionType.h>
#include <aidl/android/hardware/bluetooth/ranging/SightType.h>
#include <aidl/android/hardware/bluetooth/ranging/VendorSpecificData.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::bluetooth::ranging {
class Config;
class DeviceAddress;
class VendorSpecificData;
}  // namespace aidl::android::hardware::bluetooth::ranging
namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
class BluetoothChannelSoundingParameters {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  ::aidl::android::hardware::bluetooth::ranging::SessionType sessionType = ::aidl::android::hardware::bluetooth::ranging::SessionType(0);
  int32_t aclHandle = 0;
  int32_t l2capCid = 0;
  int32_t realTimeProcedureDataAttHandle = 0;
  ::aidl::android::hardware::bluetooth::ranging::Role __attribute__((deprecated("use the role in Config.aidl"))) role = ::aidl::android::hardware::bluetooth::ranging::Role(0);
  bool localSupportsSoundingPhaseBasedRanging = false;
  bool remoteSupportsSoundingPhaseBaseRanging = false;
  ::aidl::android::hardware::bluetooth::ranging::Config config;
  ::aidl::android::hardware::bluetooth::ranging::DeviceAddress address;
  std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::ranging::VendorSpecificData>>> vendorSpecificData;
  ::aidl::android::hardware::bluetooth::ranging::LocationType locationType = ::aidl::android::hardware::bluetooth::ranging::LocationType(0);
  ::aidl::android::hardware::bluetooth::ranging::SightType sightType = ::aidl::android::hardware::bluetooth::ranging::SightType(0);

  binder_status_t readFromParcel(const AParcel* parcel);
  binder_status_t writeToParcel(AParcel* parcel) const;

  inline bool operator==(const BluetoothChannelSoundingParameters& _rhs) const {
    return std::tie(sessionType, aclHandle, l2capCid, realTimeProcedureDataAttHandle, role, localSupportsSoundingPhaseBasedRanging, remoteSupportsSoundingPhaseBaseRanging, config, address, vendorSpecificData, locationType, sightType) == std::tie(_rhs.sessionType, _rhs.aclHandle, _rhs.l2capCid, _rhs.realTimeProcedureDataAttHandle, _rhs.role, _rhs.localSupportsSoundingPhaseBasedRanging, _rhs.remoteSupportsSoundingPhaseBaseRanging, _rhs.config, _rhs.address, _rhs.vendorSpecificData, _rhs.locationType, _rhs.sightType);
  }
  inline bool operator<(const BluetoothChannelSoundingParameters& _rhs) const {
    return std::tie(sessionType, aclHandle, l2capCid, realTimeProcedureDataAttHandle, role, localSupportsSoundingPhaseBasedRanging, remoteSupportsSoundingPhaseBaseRanging, config, address, vendorSpecificData, locationType, sightType) < std::tie(_rhs.sessionType, _rhs.aclHandle, _rhs.l2capCid, _rhs.realTimeProcedureDataAttHandle, _rhs.role, _rhs.localSupportsSoundingPhaseBasedRanging, _rhs.remoteSupportsSoundingPhaseBaseRanging, _rhs.config, _rhs.address, _rhs.vendorSpecificData, _rhs.locationType, _rhs.sightType);
  }
  inline bool operator!=(const BluetoothChannelSoundingParameters& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const BluetoothChannelSoundingParameters& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const BluetoothChannelSoundingParameters& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const BluetoothChannelSoundingParameters& _rhs) const {
    return !(_rhs < *this);
  }

  static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  inline std::string toString() const {
    std::ostringstream _aidl_os;
    _aidl_os << "BluetoothChannelSoundingParameters{";
    _aidl_os << "sessionType: " << ::android::internal::ToString(sessionType);
    _aidl_os << ", aclHandle: " << ::android::internal::ToString(aclHandle);
    _aidl_os << ", l2capCid: " << ::android::internal::ToString(l2capCid);
    _aidl_os << ", realTimeProcedureDataAttHandle: " << ::android::internal::ToString(realTimeProcedureDataAttHandle);
    _aidl_os << ", role: " << ::android::internal::ToString(role);
    _aidl_os << ", localSupportsSoundingPhaseBasedRanging: " << ::android::internal::ToString(localSupportsSoundingPhaseBasedRanging);
    _aidl_os << ", remoteSupportsSoundingPhaseBaseRanging: " << ::android::internal::ToString(remoteSupportsSoundingPhaseBaseRanging);
    _aidl_os << ", config: " << ::android::internal::ToString(config);
    _aidl_os << ", address: " << ::android::internal::ToString(address);
    _aidl_os << ", vendorSpecificData: " << ::android::internal::ToString(vendorSpecificData);
    _aidl_os << ", locationType: " << ::android::internal::ToString(locationType);
    _aidl_os << ", sightType: " << ::android::internal::ToString(sightType);
    _aidl_os << "}";
    return _aidl_os.str();
  }
};
#pragma clang diagnostic pop
}  // namespace ranging
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
