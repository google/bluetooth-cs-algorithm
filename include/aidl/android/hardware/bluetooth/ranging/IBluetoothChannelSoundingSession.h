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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/IBluetoothChannelSoundingSession.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/IBluetoothChannelSoundingSession.aidl
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
#include <aidl/android/hardware/bluetooth/ranging/ChannelSoudingRawData.h>
#include <aidl/android/hardware/bluetooth/ranging/ChannelSoundingProcedureData.h>
#include <aidl/android/hardware/bluetooth/ranging/Config.h>
#include <aidl/android/hardware/bluetooth/ranging/ProcedureEnableConfig.h>
#include <aidl/android/hardware/bluetooth/ranging/Reason.h>
#include <aidl/android/hardware/bluetooth/ranging/ResultType.h>
#include <aidl/android/hardware/bluetooth/ranging/VendorSpecificData.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::bluetooth::ranging {
class ChannelSoudingRawData;
class ChannelSoundingProcedureData;
class Config;
class ProcedureEnableConfig;
class VendorSpecificData;
}  // namespace aidl::android::hardware::bluetooth::ranging
namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
class IBluetoothChannelSoundingSessionDelegator;

class IBluetoothChannelSoundingSession : public ::ndk::ICInterface {
public:
  typedef IBluetoothChannelSoundingSessionDelegator DefaultDelegator;
  static const char* descriptor;
  IBluetoothChannelSoundingSession();
  virtual ~IBluetoothChannelSoundingSession();

  static inline const int32_t version = 2;
  static inline const std::string hash = "1ce66c3f521da97079f169b56452be7371c4a61f";
  static constexpr uint32_t TRANSACTION_getVendorSpecificReplies = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getSupportedResultTypes = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_isAbortedProcedureRequired = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_writeRawData = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_close = FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_writeProcedureData = FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_updateChannelSoundingConfig = FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_updateProcedureEnableConfig = FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_updateBleConnInterval = FIRST_CALL_TRANSACTION + 8;

  static std::shared_ptr<IBluetoothChannelSoundingSession> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IBluetoothChannelSoundingSession>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IBluetoothChannelSoundingSession>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IBluetoothChannelSoundingSession>& impl);
  static const std::shared_ptr<IBluetoothChannelSoundingSession>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus getVendorSpecificReplies(std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::ranging::VendorSpecificData>>>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getSupportedResultTypes(std::vector<::aidl::android::hardware::bluetooth::ranging::ResultType>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus isAbortedProcedureRequired(bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus writeRawData(const ::aidl::android::hardware::bluetooth::ranging::ChannelSoudingRawData& in_rawData) = 0;
  virtual ::ndk::ScopedAStatus close(::aidl::android::hardware::bluetooth::ranging::Reason in_reason) = 0;
  virtual ::ndk::ScopedAStatus writeProcedureData(const ::aidl::android::hardware::bluetooth::ranging::ChannelSoundingProcedureData& in_procedureData) = 0;
  virtual ::ndk::ScopedAStatus updateChannelSoundingConfig(const ::aidl::android::hardware::bluetooth::ranging::Config& in_conifg) = 0;
  virtual ::ndk::ScopedAStatus updateProcedureEnableConfig(const ::aidl::android::hardware::bluetooth::ranging::ProcedureEnableConfig& in_procedureEnableConfig) = 0;
  virtual ::ndk::ScopedAStatus updateBleConnInterval(int32_t in_bleConnInterval) = 0;
  virtual ::ndk::ScopedAStatus getInterfaceVersion(int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getInterfaceHash(std::string* _aidl_return) = 0;
private:
  static std::shared_ptr<IBluetoothChannelSoundingSession> default_impl;
};
class IBluetoothChannelSoundingSessionDefault : public IBluetoothChannelSoundingSession {
public:
  ::ndk::ScopedAStatus getVendorSpecificReplies(std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::ranging::VendorSpecificData>>>* _aidl_return) override;
  ::ndk::ScopedAStatus getSupportedResultTypes(std::vector<::aidl::android::hardware::bluetooth::ranging::ResultType>* _aidl_return) override;
  ::ndk::ScopedAStatus isAbortedProcedureRequired(bool* _aidl_return) override;
  ::ndk::ScopedAStatus writeRawData(const ::aidl::android::hardware::bluetooth::ranging::ChannelSoudingRawData& in_rawData) override;
  ::ndk::ScopedAStatus close(::aidl::android::hardware::bluetooth::ranging::Reason in_reason) override;
  ::ndk::ScopedAStatus writeProcedureData(const ::aidl::android::hardware::bluetooth::ranging::ChannelSoundingProcedureData& in_procedureData) override;
  ::ndk::ScopedAStatus updateChannelSoundingConfig(const ::aidl::android::hardware::bluetooth::ranging::Config& in_conifg) override;
  ::ndk::ScopedAStatus updateProcedureEnableConfig(const ::aidl::android::hardware::bluetooth::ranging::ProcedureEnableConfig& in_procedureEnableConfig) override;
  ::ndk::ScopedAStatus updateBleConnInterval(int32_t in_bleConnInterval) override;
  ::ndk::ScopedAStatus getInterfaceVersion(int32_t* _aidl_return) override;
  ::ndk::ScopedAStatus getInterfaceHash(std::string* _aidl_return) override;
  ::ndk::SpAIBinder asBinder() override;
  bool isRemote() override;
};
}  // namespace ranging
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
