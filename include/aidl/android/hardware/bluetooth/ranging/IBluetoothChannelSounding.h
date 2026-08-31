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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/IBluetoothChannelSounding.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/IBluetoothChannelSounding.aidl
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
#include <aidl/android/hardware/bluetooth/ranging/BluetoothChannelSoundingParameters.h>
#include <aidl/android/hardware/bluetooth/ranging/CsSecurityLevel.h>
#include <aidl/android/hardware/bluetooth/ranging/IBluetoothChannelSoundingSession.h>
#include <aidl/android/hardware/bluetooth/ranging/IBluetoothChannelSoundingSessionCallback.h>
#include <aidl/android/hardware/bluetooth/ranging/SessionType.h>
#include <aidl/android/hardware/bluetooth/ranging/VendorSpecificData.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::bluetooth::ranging {
class BluetoothChannelSoundingParameters;
class IBluetoothChannelSoundingSession;
class IBluetoothChannelSoundingSessionCallback;
class VendorSpecificData;
}  // namespace aidl::android::hardware::bluetooth::ranging
namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
class IBluetoothChannelSoundingDelegator;

class IBluetoothChannelSounding : public ::ndk::ICInterface {
public:
  typedef IBluetoothChannelSoundingDelegator DefaultDelegator;
  static const char* descriptor;
  IBluetoothChannelSounding();
  virtual ~IBluetoothChannelSounding();

  static inline const int32_t version = 2;
  static inline const std::string hash = "1ce66c3f521da97079f169b56452be7371c4a61f";
  static constexpr uint32_t TRANSACTION_getVendorSpecificData = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_getSupportedSessionTypes = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_getMaxSupportedCsSecurityLevel = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_openSession = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getSupportedCsSecurityLevels = FIRST_CALL_TRANSACTION + 4;

  static std::shared_ptr<IBluetoothChannelSounding> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IBluetoothChannelSounding>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IBluetoothChannelSounding>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IBluetoothChannelSounding>& impl);
  static const std::shared_ptr<IBluetoothChannelSounding>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus getVendorSpecificData(std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::ranging::VendorSpecificData>>>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getSupportedSessionTypes(std::optional<std::vector<::aidl::android::hardware::bluetooth::ranging::SessionType>>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getMaxSupportedCsSecurityLevel(::aidl::android::hardware::bluetooth::ranging::CsSecurityLevel* _aidl_return) __attribute__((deprecated("use getSupportedCsSecurityLevels() instead"))) = 0;
  virtual ::ndk::ScopedAStatus openSession(const ::aidl::android::hardware::bluetooth::ranging::BluetoothChannelSoundingParameters& in_params, const std::shared_ptr<::aidl::android::hardware::bluetooth::ranging::IBluetoothChannelSoundingSessionCallback>& in_callback, std::shared_ptr<::aidl::android::hardware::bluetooth::ranging::IBluetoothChannelSoundingSession>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getSupportedCsSecurityLevels(std::vector<::aidl::android::hardware::bluetooth::ranging::CsSecurityLevel>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getInterfaceVersion(int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getInterfaceHash(std::string* _aidl_return) = 0;
private:
  static std::shared_ptr<IBluetoothChannelSounding> default_impl;
};
class IBluetoothChannelSoundingDefault : public IBluetoothChannelSounding {
public:
  ::ndk::ScopedAStatus getVendorSpecificData(std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::ranging::VendorSpecificData>>>* _aidl_return) override;
  ::ndk::ScopedAStatus getSupportedSessionTypes(std::optional<std::vector<::aidl::android::hardware::bluetooth::ranging::SessionType>>* _aidl_return) override;
  ::ndk::ScopedAStatus getMaxSupportedCsSecurityLevel(::aidl::android::hardware::bluetooth::ranging::CsSecurityLevel* _aidl_return) override __attribute__((deprecated("use getSupportedCsSecurityLevels() instead")));
  ::ndk::ScopedAStatus openSession(const ::aidl::android::hardware::bluetooth::ranging::BluetoothChannelSoundingParameters& in_params, const std::shared_ptr<::aidl::android::hardware::bluetooth::ranging::IBluetoothChannelSoundingSessionCallback>& in_callback, std::shared_ptr<::aidl::android::hardware::bluetooth::ranging::IBluetoothChannelSoundingSession>* _aidl_return) override;
  ::ndk::ScopedAStatus getSupportedCsSecurityLevels(std::vector<::aidl::android::hardware::bluetooth::ranging::CsSecurityLevel>* _aidl_return) override;
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
