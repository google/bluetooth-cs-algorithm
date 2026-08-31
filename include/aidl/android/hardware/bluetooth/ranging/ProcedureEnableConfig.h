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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/ProcedureEnableConfig.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/ProcedureEnableConfig.aidl
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
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
class ProcedureEnableConfig {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  int8_t toneAntennaConfigSelection = 0;
  int32_t subeventLenUs = 0;
  int8_t subeventsPerEvent = 0;
  int32_t subeventInterval = 0;
  int32_t eventInterval = 0;
  int32_t procedureInterval = 0;
  int32_t procedureCount = 0;
  int32_t maxProcedureLen = 0;

  // binder_status_t readFromParcel(const AParcel* parcel);
  // binder_status_t writeToParcel(AParcel* parcel) const;

  inline bool operator==(const ProcedureEnableConfig& _rhs) const {
    return std::tie(toneAntennaConfigSelection, subeventLenUs, subeventsPerEvent, subeventInterval, eventInterval, procedureInterval, procedureCount, maxProcedureLen) == std::tie(_rhs.toneAntennaConfigSelection, _rhs.subeventLenUs, _rhs.subeventsPerEvent, _rhs.subeventInterval, _rhs.eventInterval, _rhs.procedureInterval, _rhs.procedureCount, _rhs.maxProcedureLen);
  }
  inline bool operator<(const ProcedureEnableConfig& _rhs) const {
    return std::tie(toneAntennaConfigSelection, subeventLenUs, subeventsPerEvent, subeventInterval, eventInterval, procedureInterval, procedureCount, maxProcedureLen) < std::tie(_rhs.toneAntennaConfigSelection, _rhs.subeventLenUs, _rhs.subeventsPerEvent, _rhs.subeventInterval, _rhs.eventInterval, _rhs.procedureInterval, _rhs.procedureCount, _rhs.maxProcedureLen);
  }
  inline bool operator!=(const ProcedureEnableConfig& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const ProcedureEnableConfig& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const ProcedureEnableConfig& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const ProcedureEnableConfig& _rhs) const {
    return !(_rhs < *this);
  }

  // static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  // inline std::string toString() const {
  //   std::ostringstream _aidl_os;
  //   _aidl_os << "ProcedureEnableConfig{";
  //   _aidl_os << "toneAntennaConfigSelection: " << ::android::internal::ToString(toneAntennaConfigSelection);
  //   _aidl_os << ", subeventLenUs: " << ::android::internal::ToString(subeventLenUs);
  //   _aidl_os << ", subeventsPerEvent: " << ::android::internal::ToString(subeventsPerEvent);
  //   _aidl_os << ", subeventInterval: " << ::android::internal::ToString(subeventInterval);
  //   _aidl_os << ", eventInterval: " << ::android::internal::ToString(eventInterval);
  //   _aidl_os << ", procedureInterval: " << ::android::internal::ToString(procedureInterval);
  //   _aidl_os << ", procedureCount: " << ::android::internal::ToString(procedureCount);
  //   _aidl_os << ", maxProcedureLen: " << ::android::internal::ToString(maxProcedureLen);
  //   _aidl_os << "}";
  //   return _aidl_os.str();
  // }
};
}  // namespace ranging
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
