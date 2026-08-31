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

#include "bluetooth_hal/bqr/bqr_event.h"
#include "bluetooth_hal/bqr/bqr_types.h"
#include "bluetooth_hal/hal_packet.h"
#include "bluetooth_hal/hal_types.h"
#include "bluetooth_hal/hci_monitor.h"
#include "bluetooth_hal/hci_router_client.h"
#include "bluetooth_hal/util/provider_factory.h"

namespace bluetooth_hal::bqr {

class BqrHandler : public ::bluetooth_hal::hci::HciRouterClient {
  public:
    using VendorFactory = ::bluetooth_hal::util::ProviderFactory<BqrHandler, BqrHandler>;
    using FactoryFn = VendorFactory::FactoryFn;

    static bool RegisterBqrHandler(FactoryFn factory);

    BqrHandler();
    static void Start();
    static void Stop();

  protected:
    void OnCommandCallback(
            [[maybe_unused]] const ::bluetooth_hal::hci::HalPacket& packet) override {};
    void OnMonitorPacketCallback(::bluetooth_hal::hci::MonitorMode mode,
                                 const ::bluetooth_hal::hci::HalPacket& packet) override;
    void OnBluetoothChipReady() override {};
    void OnBluetoothChipClosed() override {};
    void OnBluetoothEnabled() override;
    void OnBluetoothDisabled() override;

    BqrVersion GetLocalSupportedBqrVersion();

    virtual void HandleVendorCapabilityEvent(const ::bluetooth_hal::hci::HalPacket& packet);
    virtual void HandleRootInflammationEvent(const BqrEvent& event);
    virtual void HandleLinkQualityEvent(const BqrEvent& bqr_event);
    virtual void HandleAdvancedRfStatEvent(const BqrEvent& bqr_event);
    virtual void HandleEnergyMonitoringEvent(const BqrEvent& bqr_event);
    virtual void HandleOffloadEvent(const BqrEvent& bqr_event);
    virtual void HandleUnspecifiedVendorEvent(const BqrEvent& bqr_event);

    BqrVersion local_supported_bqr_version_;
    ::bluetooth_hal::hci::HciCommandCompleteEventMonitor vendor_capability_monitor_;
    ::bluetooth_hal::hci::HciBqrEventMonitor bqr_event_monitor_;
    ::bluetooth_hal::hci::HciBqrEventMonitor bqr_offload_event_monitor_;

  private:
    static std::unique_ptr<BqrHandler> handler_ptr_;
};

}  // namespace bluetooth_hal::bqr
