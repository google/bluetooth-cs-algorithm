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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/ChannelSoundingProcedureData.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/ChannelSoundingProcedureData.aidl
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
#include <aidl/android/hardware/bluetooth/ranging/ProcedureAbortReason.h>
#include <aidl/android/hardware/bluetooth/ranging/SubeventResultData.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::bluetooth::ranging {
class SubeventResultData;
}  // namespace aidl::android::hardware::bluetooth::ranging
namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
class ChannelSoundingProcedureData {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  int32_t procedureCounter = 0;
  int32_t procedureSequence = 0;
  int8_t initiatorSelectedTxPower = 127;
  int8_t reflectorSelectedTxPower = 127;
  std::vector<::aidl::android::hardware::bluetooth::ranging::SubeventResultData> initiatorSubeventResultData;
  ::aidl::android::hardware::bluetooth::ranging::ProcedureAbortReason initiatorProcedureAbortReason = ::aidl::android::hardware::bluetooth::ranging::ProcedureAbortReason(0);
  std::vector<::aidl::android::hardware::bluetooth::ranging::SubeventResultData> reflectorSubeventResultData;
  ::aidl::android::hardware::bluetooth::ranging::ProcedureAbortReason reflectorProcedureAbortReason = ::aidl::android::hardware::bluetooth::ranging::ProcedureAbortReason(0);

  // binder_status_t readFromParcel(const AParcel* parcel);
  // binder_status_t writeToParcel(AParcel* parcel) const;

  inline bool operator==(const ChannelSoundingProcedureData& _rhs) const {
    return std::tie(procedureCounter, procedureSequence, initiatorSelectedTxPower, reflectorSelectedTxPower, initiatorSubeventResultData, initiatorProcedureAbortReason, reflectorSubeventResultData, reflectorProcedureAbortReason) == std::tie(_rhs.procedureCounter, _rhs.procedureSequence, _rhs.initiatorSelectedTxPower, _rhs.reflectorSelectedTxPower, _rhs.initiatorSubeventResultData, _rhs.initiatorProcedureAbortReason, _rhs.reflectorSubeventResultData, _rhs.reflectorProcedureAbortReason);
  }
  inline bool operator<(const ChannelSoundingProcedureData& _rhs) const {
    return std::tie(procedureCounter, procedureSequence, initiatorSelectedTxPower, reflectorSelectedTxPower, initiatorSubeventResultData, initiatorProcedureAbortReason, reflectorSubeventResultData, reflectorProcedureAbortReason) < std::tie(_rhs.procedureCounter, _rhs.procedureSequence, _rhs.initiatorSelectedTxPower, _rhs.reflectorSelectedTxPower, _rhs.initiatorSubeventResultData, _rhs.initiatorProcedureAbortReason, _rhs.reflectorSubeventResultData, _rhs.reflectorProcedureAbortReason);
  }
  inline bool operator!=(const ChannelSoundingProcedureData& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const ChannelSoundingProcedureData& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const ChannelSoundingProcedureData& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const ChannelSoundingProcedureData& _rhs) const {
    return !(_rhs < *this);
  }

  // static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  // enum : int8_t { SELECTED_TX_POWER_UNAVAILABLE = 127 };
  // inline std::string toString() const {
  //   std::ostringstream _aidl_os;
  //   _aidl_os << "ChannelSoundingProcedureData{";
  //   _aidl_os << "procedureCounter: " << ::android::internal::ToString(procedureCounter);
  //   _aidl_os << ", procedureSequence: " << ::android::internal::ToString(procedureSequence);
  //   _aidl_os << ", initiatorSelectedTxPower: " << ::android::internal::ToString(initiatorSelectedTxPower);
  //   _aidl_os << ", reflectorSelectedTxPower: " << ::android::internal::ToString(reflectorSelectedTxPower);
  //   _aidl_os << ", initiatorSubeventResultData: " << ::android::internal::ToString(initiatorSubeventResultData);
  //   _aidl_os << ", initiatorProcedureAbortReason: " << ::android::internal::ToString(initiatorProcedureAbortReason);
  //   _aidl_os << ", reflectorSubeventResultData: " << ::android::internal::ToString(reflectorSubeventResultData);
  //   _aidl_os << ", reflectorProcedureAbortReason: " << ::android::internal::ToString(reflectorProcedureAbortReason);
  //   _aidl_os << "}";
  //   return _aidl_os.str();
  // }
};
}  // namespace ranging
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
