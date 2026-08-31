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
#include <memory>
#include <vector>

#include "aidl/android/hardware/bluetooth/lmp_event/BnBluetoothLmpEvent.h"
#include "aidl/android/hardware/bluetooth/lmp_event/IBluetoothLmpEventCallback.h"
#include "bluetooth_hal/extensions/ccc/bluetooth_ccc_handler.h"

namespace bluetooth_hal::extensions::ccc {

using ::aidl::android::hardware::bluetooth::lmp_event::BnBluetoothLmpEvent;
using ::aidl::android::hardware::bluetooth::lmp_event::IBluetoothLmpEventCallback;
using ::aidl::android::hardware::bluetooth::lmp_event::LmpEventId;
using ::bluetooth_hal::extensions::ccc::BluetoothCccHandler;

class BluetoothLmpEvent : public BnBluetoothLmpEvent {
  public:
    BluetoothLmpEvent();

    ::ndk::ScopedAStatus registerForLmpEvents(
            const std::shared_ptr<IBluetoothLmpEventCallback>& callback,
            const ::aidl::android::hardware::bluetooth::lmp_event::AddressType addressType,
            const std::array<uint8_t, 6>& address,
            const std::vector<LmpEventId>& lmpEventIds) override;

    ::ndk::ScopedAStatus unregisterLmpEvents(
            const ::aidl::android::hardware::bluetooth::lmp_event::AddressType addressType,
            const std::array<uint8_t, 6>& address) override;

  private:
    BluetoothCccHandler& handler_;
};

}  // namespace bluetooth_hal::extensions::ccc
