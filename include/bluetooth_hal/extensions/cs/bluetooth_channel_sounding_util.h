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

#include <array>
#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <vector>

#include "aidl/android/hardware/bluetooth/ranging/BluetoothChannelSoundingParameters.h"
#include "aidl/android/hardware/bluetooth/ranging/VendorSpecificData.h"
#include "bluetooth_hal/hal_packet.h"
#include "bluetooth_hal/hal_types.h"

namespace bluetooth_hal::extensions::cs {

inline constexpr std::array<uint8_t, 16> kUuidSpecialRangingSettingCapability = {
        0x00, 0x00, 0x8f, 0x01, 0x00, 0x00, 0x10, 0x00,
        0x80, 0x00, 0x00, 0x80, 0x5f, 0x9c, 0x35, 0xf1};

inline constexpr std::array<uint8_t, 16> kUuidSpecialRangingSettingCommand = {
        0x00, 0x00, 0x8f, 0x02, 0x00, 0x00, 0x10, 0x00,
        0x80, 0x00, 0x00, 0x80, 0x5f, 0x9c, 0x35, 0xf1};

inline constexpr uint8_t kMinNumUuid = 0x02;
inline constexpr uint8_t kDataTypeData = 0x00;
inline constexpr uint8_t kDataTypeReply = 0x01;
inline constexpr uint8_t kCommandValueDisable = 0x00;
inline constexpr uint8_t kCommandValueEnable = 0x01;
inline constexpr uint8_t kCommandValueIgnore = 0x02;
inline constexpr uint8_t kCommandValueAddToList = 0x00;
inline constexpr uint8_t kCommandValueDeleteFromList = 0x01;

inline constexpr uint8_t kCommandCompleteSubOpcodeOffset =
        ::bluetooth_hal::hci::HciConstants::kHciCommandCompleteResultOffset + 1;

inline constexpr uint16_t kHciVscSpecialRangingSettingOpcode = 0xff0b;

inline constexpr uint8_t kHciVscReadLocalCapabilityParamLength = 0x01;
inline constexpr uint8_t kHciVscReadLocalCapabilitySubOpCode = 0x01;
inline constexpr uint8_t kCommandCompleteReadLocalCapabilityOffset =
        kCommandCompleteSubOpcodeOffset + 1;
inline constexpr uint8_t kCommandCompleteReadLocalCapabilityValueLength = 4;

inline constexpr uint8_t kHciVscEnableInlinePctParamLength = 0x02;
inline constexpr uint8_t kHciVscEnableInlinePctSubOpCode = 0x02;

inline constexpr uint8_t kHciVscSetEventMaskForConnectionSubOpCode = 0x03;
inline constexpr uint8_t kHciVscSetEventMaskForConnectionParamLength = 0x07;

inline constexpr uint8_t kHciVscEnableMode0ChannelMapSubOpCode = 0x04;
inline constexpr uint8_t kHciVscEnableMode0ChannelMapParamLength = 0x04;

inline constexpr uint8_t kHciVscEnablePreferredConnectionIntervalForHandleSubOpCode = 0x07;
inline constexpr uint8_t kHciVscEnablePreferredConnectionIntervalForHandleParamLength = 0x04;

inline constexpr uint8_t kLeCsProcedureEnableCompleteCode = 0x30;
inline constexpr uint8_t kLeCsSubEventResultCode = 0x31;

// Used for RAS notification.
inline constexpr uint16_t kFlagFirstAutomaticallyFlushablePacket = 0x2000;
inline constexpr uint8_t kFakeRasDataLen = 0x18;
inline constexpr uint8_t kGattNotification = 0x1b;

inline constexpr uint16_t kInitialProcedureCounter = 0xffff;

//   Although we support new data format, we still want to backport the old data
//   format. Otherwise some builds on the phone might fail to run CS.
//
//   Example of old format: 01010001
//    01  ,         01         ,     00     ,           01
//    Type, Enable 1-sided PCT , Event Mask , Enable mode-0 channel map
//
//   When got the event mask (0x00) => Disable all event report
inline constexpr uint8_t kOldLengthDataFormat = 4;
inline constexpr uint8_t kOldIdxRangingSettingCommandType = 0;
inline constexpr uint8_t kOldIdxRangingSettingCommandInlinePct = 1;
inline constexpr uint8_t kOldIdxRangingSettingCommandCSSubeventReport = 2;
inline constexpr uint8_t kOldIdxRangingSettingCommandMode0ChannelMap = 3;

//   Example of new format: 01010000000001
//     01 ,         01         , 00 00 00 00 ,           01
//    Type, Enable 1-sided PCT ,  Event Mask , Enable mode-0 channel map
//
//   The event mask (0x00000000) implies
//      Bit 0: LE CS Subevent Result event
//      Bit 1: LE CS Subevent Result Continue event
//      Bit 2: LE CS Procedure Enable Complete event
//      Bit 3 ~ 31: Reserved for future use
inline constexpr uint8_t kLengthDataFormat = 7;
inline constexpr uint8_t kLenRangingSettingCommandType = 1;
inline constexpr uint8_t kLenRangingSettingCommandInlinePct = 1;
inline constexpr uint8_t kLenRangingSettingCommandEventMask = 4;
inline constexpr uint8_t kLenRangingSettingCommandMode0ChannelMap = 1;

enum class CsFeature : uint8_t {
    kInlinePct = 0x01,
    kMode0ChannelMap = 0x02,
    kPreferredConnectionInterval = 0x04,
    kPreferredSniffInterval = 0x08,
    kPreferredConnectionIntervalForHandle = 0x10,
};

std::string ToHex(const std::span<const uint8_t> data);

bool IsUuidMatched(
        const std::optional<std::vector<
                std::optional<::aidl::android::hardware::bluetooth::ranging::VendorSpecificData>>>
                vendor_specific_data);

::bluetooth_hal::hci::HalPacket BuildReadLocalCapabilityCommand();

::bluetooth_hal::hci::HalPacket BuildEnableInlinePctCommand(uint8_t enable);

::bluetooth_hal::hci::HalPacket BuildSetEventMaskForConnectionCommand(uint16_t connection_handle,
                                                                      uint32_t event_mask);

::bluetooth_hal::hci::HalPacket BuildEnableMode0ChannelMapCommand(uint16_t connection_handle,
                                                                  uint8_t enable);

::bluetooth_hal::hci::HalPacket BuildEnablePreferredConnectionIntervalForHandleCommand(
        uint16_t connection_handle, uint8_t action);

::bluetooth_hal::hci::HalPacket BuildRasNotification(
        const ::aidl::android::hardware::bluetooth::ranging::BluetoothChannelSoundingParameters&
                parameters,
        int procedure_counter);

}  // namespace bluetooth_hal::extensions::cs
