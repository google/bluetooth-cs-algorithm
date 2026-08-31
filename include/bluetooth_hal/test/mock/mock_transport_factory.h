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

#include "bluetooth_hal/hal_types.h"
#include "bluetooth_hal/transport/subscriber.h"
#include "bluetooth_hal/transport/transport_factory.h"
#include "bluetooth_hal/transport/transport_instance.h"
#include "gmock/gmock.h"

namespace bluetooth_hal::transport {

/**
 * @brief Mock class for TransportFactory static methods.
 */
class MockTransportFactory {
  public:
    MOCK_METHOD(TransportInstance&, GetMainTransport, (), ());
    MOCK_METHOD(TransportInstance&, GetTransport, (TransportType type), ());
    MOCK_METHOD(bool, UpdateMainTransport, (TransportType requested_type), ());
    MOCK_METHOD(TransportType, GetMainTransportType, (), ());
    MOCK_METHOD(void, CleanupTransports, (), ());
    MOCK_METHOD(bool, RegisterVendorTransport,
                (TransportType type, TransportFactory::FactoryFn factory), ());
    MOCK_METHOD(bool, UnregisterVendorTransport, (TransportType type), ());
    MOCK_METHOD(void, NotifyHalStateChange, (::bluetooth_hal::HalState hal_state));
    MOCK_METHOD(::bluetooth_hal::HalState, GetHalState, ());
    MOCK_METHOD(void, Subscribe, (Subscriber & subscriber));
    MOCK_METHOD(void, Unsubscribe, (Subscriber & subscriber));
    MOCK_METHOD(void, Reset, ());

    static void SetMockFactory(MockTransportFactory* factory) { mock_transport_factory_ = factory; }
    static MockTransportFactory* GetFactory() { return mock_transport_factory_; }

  private:
    static inline MockTransportFactory* mock_transport_factory_ = nullptr;
};

}  // namespace bluetooth_hal::transport
