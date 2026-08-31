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
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/IBluetoothChannelSoundingSessionCallback.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/IBluetoothChannelSoundingSessionCallback.aidl
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
#include <aidl/android/hardware/bluetooth/ranging/RangingResult.h>
#include <aidl/android/hardware/bluetooth/ranging/Reason.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

namespace aidl::android::hardware::bluetooth::ranging {
class RangingResult;
}  // namespace aidl::android::hardware::bluetooth::ranging
namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
class IBluetoothChannelSoundingSessionCallbackDelegator;

class IBluetoothChannelSoundingSessionCallback : public ::ndk::ICInterface {
public:
  typedef IBluetoothChannelSoundingSessionCallbackDelegator DefaultDelegator;
  static const char* descriptor;
  IBluetoothChannelSoundingSessionCallback();
  virtual ~IBluetoothChannelSoundingSessionCallback();

  static inline const int32_t version = 2;
  static inline const std::string hash = "1ce66c3f521da97079f169b56452be7371c4a61f";
  static constexpr uint32_t TRANSACTION_onOpened = FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_onOpenFailed = FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_onResult = FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_onClose = FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_onCloseFailed = FIRST_CALL_TRANSACTION + 4;

  static std::shared_ptr<IBluetoothChannelSoundingSessionCallback> fromBinder(const ::ndk::SpAIBinder& binder);
  static binder_status_t writeToParcel(AParcel* parcel, const std::shared_ptr<IBluetoothChannelSoundingSessionCallback>& instance);
  static binder_status_t readFromParcel(const AParcel* parcel, std::shared_ptr<IBluetoothChannelSoundingSessionCallback>* instance);
  static bool setDefaultImpl(const std::shared_ptr<IBluetoothChannelSoundingSessionCallback>& impl);
  static const std::shared_ptr<IBluetoothChannelSoundingSessionCallback>& getDefaultImpl();
  virtual ::ndk::ScopedAStatus onOpened(::aidl::android::hardware::bluetooth::ranging::Reason in_reason) = 0;
  virtual ::ndk::ScopedAStatus onOpenFailed(::aidl::android::hardware::bluetooth::ranging::Reason in_reason) = 0;
  virtual ::ndk::ScopedAStatus onResult(const ::aidl::android::hardware::bluetooth::ranging::RangingResult& in_result) = 0;
  virtual ::ndk::ScopedAStatus onClose(::aidl::android::hardware::bluetooth::ranging::Reason in_reason) = 0;
  virtual ::ndk::ScopedAStatus onCloseFailed(::aidl::android::hardware::bluetooth::ranging::Reason in_reason) = 0;
  virtual ::ndk::ScopedAStatus getInterfaceVersion(int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getInterfaceHash(std::string* _aidl_return) = 0;
private:
  static std::shared_ptr<IBluetoothChannelSoundingSessionCallback> default_impl;
};
class IBluetoothChannelSoundingSessionCallbackDefault : public IBluetoothChannelSoundingSessionCallback {
public:
  ::ndk::ScopedAStatus onOpened(::aidl::android::hardware::bluetooth::ranging::Reason in_reason) override;
  ::ndk::ScopedAStatus onOpenFailed(::aidl::android::hardware::bluetooth::ranging::Reason in_reason) override;
  ::ndk::ScopedAStatus onResult(const ::aidl::android::hardware::bluetooth::ranging::RangingResult& in_result) override;
  ::ndk::ScopedAStatus onClose(::aidl::android::hardware::bluetooth::ranging::Reason in_reason) override;
  ::ndk::ScopedAStatus onCloseFailed(::aidl::android::hardware::bluetooth::ranging::Reason in_reason) override;
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
