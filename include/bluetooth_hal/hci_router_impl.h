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

#include "bluetooth_hal/hal_packet.h"
#include "bluetooth_hal/hal_types.h"
#include "bluetooth_hal/hci_router.h"
#include "bluetooth_hal/hci_router_async.h"
#include "bluetooth_hal/hci_router_callback.h"
#include "bluetooth_hal/transport/transport_instance.h"

namespace bluetooth_hal::hci {

class HciRouterImpl : public HciRouter,
                      public ::bluetooth_hal::transport::TransportInstanceCallback {
  public:
    explicit HciRouterImpl();

    // HciRouter overrides
    bool Initialize(const std::shared_ptr<HciRouterCallback>& callback) override;
    void Close() override;
    void Cleanup() override;
    bool Send(const HalPacket& packet) override;
    bool SendCommand(const HalPacket& packet, const HalPacketCallback& callback) override;
    bool SendCommandNoAck(const HalPacket& packet) override;
    ::bluetooth_hal::HalState GetHalState() override;
    void UpdateHalState(::bluetooth_hal::HalState state) override;
    void SendPacketToStack(const HalPacket& packet) override;

    // TransportInstanceCallback overrides
    void OnTransportClosed() override;
    void OnTransportPacketReady(const ::bluetooth_hal::hci::HalPacket& packet) override;

  protected:
    explicit HciRouterImpl(std::shared_ptr<HciRouterAsync> hci_router_async);
    std::shared_ptr<HciRouterAsync> hci_router_async_;

  private:
    bool DoInRouterThread(std::function<void()> task);
    bool SynchronousDoInRouterThread(std::function<void()> task);
};

}  // namespace bluetooth_hal::hci
