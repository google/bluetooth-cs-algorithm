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

#include "bluetooth_hal/hal_packet.h"
#include "bluetooth_hal/hal_types.h"
#include "bluetooth_hal/transport/transport_instance.h"
#include "gmock/gmock.h"

namespace bluetooth_hal::transport {

class MockTransportInstance : public TransportInstance {
  public:
    MOCK_METHOD(bool, Initialize, (TransportInstanceCallback * transport_instance_callback),
                (override));
    MOCK_METHOD(void, Cleanup, (), (override));
    MOCK_METHOD(bool, IsTransportActive, (), (const, override));
    MOCK_METHOD(bool, Send, (const ::bluetooth_hal::hci::HalPacket& packet), (override));
    MOCK_METHOD(TransportType, GetInstanceTransportType, (), (const, override));
    MOCK_METHOD(void, SetHciRouterBusy, (bool is_busy), (override));

    static void SetMockTransport(MockTransportInstance* transport);
    static inline MockTransportInstance* mock_transport_instance_{nullptr};
};

}  // namespace bluetooth_hal::transport
