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

#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "aidl/android/hardware/bluetooth/ranging/BluetoothChannelSoundingParameters.h"
#include "aidl/android/hardware/bluetooth/ranging/BnBluetoothChannelSoundingSession.h"
#include "aidl/android/hardware/bluetooth/ranging/ChannelSoundingProcedureData.h"
#include "aidl/android/hardware/bluetooth/ranging/Config.h"
#include "aidl/android/hardware/bluetooth/ranging/IBluetoothChannelSoundingSessionCallback.h"
#include "aidl/android/hardware/bluetooth/ranging/ProcedureEnableConfig.h"
#include "aidl/android/hardware/bluetooth/ranging/Reason.h"
#include "aidl/android/hardware/bluetooth/ranging/ResultType.h"
#include "aidl/android/hardware/bluetooth/ranging/VendorSpecificData.h"
#include "android/binder_auto_utils.h"
#include "bluetooth_hal/extensions/cs/bluetooth_channel_sounding_distance_estimator_interface.h"
#include "bluetooth_hal/extensions/cs/bluetooth_channel_sounding_session_interface.h"

namespace bluetooth_hal::extensions::cs {

class BluetoothChannelSoundingSessionV2
    : public BluetoothChannelSoundingSessionInterface,
      public ::aidl::android::hardware::bluetooth::ranging::BnBluetoothChannelSoundingSession {
  public:
    explicit BluetoothChannelSoundingSessionV2(
            std::shared_ptr<::aidl::android::hardware::bluetooth::ranging::
                                    IBluetoothChannelSoundingSessionCallback>
                    callback,
            ::aidl::android::hardware::bluetooth::ranging::Reason reason);

    ::ndk::ScopedAStatus getVendorSpecificReplies(
            std::optional<std::vector<std::optional<
                    ::aidl::android::hardware::bluetooth::ranging::VendorSpecificData>>>*
                    _aidl_return);

    ::ndk::ScopedAStatus getSupportedResultTypes(
            std::vector<::aidl::android::hardware::bluetooth::ranging::ResultType>* _aidl_return);

    ::ndk::ScopedAStatus isAbortedProcedureRequired(bool* _aidl_return) override;

    ::ndk::ScopedAStatus writeProcedureData(
            const ::aidl::android::hardware::bluetooth::ranging::ChannelSoundingProcedureData&
                    in_procedureData);

    ::ndk::ScopedAStatus writeRawData(
            const ::aidl::android::hardware::bluetooth::ranging::ChannelSoudingRawData& in_rawData)
            override;

    ::ndk::ScopedAStatus close(::aidl::android::hardware::bluetooth::ranging::Reason in_reason);

    ::ndk::ScopedAStatus updateChannelSoundingConfig(
            const ::aidl::android::hardware::bluetooth::ranging::Config& in_config);

    ::ndk::ScopedAStatus updateProcedureEnableConfig(
            const ::aidl::android::hardware::bluetooth::ranging::ProcedureEnableConfig&
                    in_procedureEnableConfig);

    ::ndk::ScopedAStatus updateBleConnInterval(int in_bleConnInterval);

    void HandleVendorSpecificData(
            const std::optional<std::vector<std::optional<
                    ::aidl::android::hardware::bluetooth::ranging::VendorSpecificData>>>
                    vendor_specific_data) override;
    bool ShouldEnableFakeNotification() override;
    bool ShouldEnableMode0ChannelMap() override;
    void CsCreateNewLog(
            const ::aidl::android::hardware::bluetooth::ranging::BluetoothChannelSoundingParameters&
                    in_params);

  private:
    std::shared_ptr<
            ::aidl::android::hardware::bluetooth::ranging::IBluetoothChannelSoundingSessionCallback>
            callback_;
    bool uuid_matched_ = false;
    bool enable_fake_notification_ = false;
    bool enable_mode_0_channel_map_ = false;

    std::unique_ptr<ChannelSoundingDistanceEstimatorInterface> distance_estimator_;
};

}  // namespace bluetooth_hal::extensions::cs
