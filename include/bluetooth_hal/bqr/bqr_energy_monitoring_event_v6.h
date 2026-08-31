/*
 * Copyright 2026 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cstdint>
#include <string>

#include "bluetooth_hal/bqr/bqr_energy_monitoring_event.h"
#include "bluetooth_hal/hal_packet.h"

namespace bluetooth_hal::bqr {

enum class EnergyMonitoringOffsetV6 : uint8_t {
    kReportTimeDuration = static_cast<uint8_t>(EnergyMonitoringOffset::kEnd),  // 4 bytes
    kRxActiveOneChainTime = kReportTimeDuration + 4,                           // 4 bytes
    kRxActiveTwoChainTime = kRxActiveOneChainTime + 4,                         // 4 bytes
    kTxIpaActiveOneChainTime = kRxActiveTwoChainTime + 4,                      // 4 bytes
    kTxIpaActiveTwoChainTime = kTxIpaActiveOneChainTime + 4,                   // 4 bytes
    kTxXpaActiveOneChainTime = kTxIpaActiveTwoChainTime + 4,                   // 4 bytes
    kTxXpaActiveTwoChainTime = kTxXpaActiveOneChainTime + 4,                   // 4 bytes
    kEnd = kTxXpaActiveTwoChainTime + 4,
};

// BQR Energy Monitoring event V6.
class BqrEnergyMonitoringEventV6 : public BqrEnergyMonitoringEvent {
  public:
    explicit BqrEnergyMonitoringEventV6(const ::bluetooth_hal::hci::HalPacket& packet);
    virtual ~BqrEnergyMonitoringEventV6() = default;

    bool IsValid() const override;

    uint32_t GetReportTimeDuration() const;
    uint32_t GetRxActiveOneChainTime() const;
    uint32_t GetRxActiveTwoChainTime() const;
    uint32_t GetTxIpaActiveOneChainTime() const;
    uint32_t GetTxIpaActiveTwoChainTime() const;
    uint32_t GetTxXpaActiveOneChainTime() const;
    uint32_t GetTxXpaActiveTwoChainTime() const;

    // Returns a string representation of the event.
    std::string ToString() const;

  protected:
    void ParseData();
    std::string ToBqrString() const;

  private:
    bool is_valid_;
    uint32_t report_time_duration_ = 0;
    uint32_t rx_active_one_chain_time_ = 0;
    uint32_t rx_active_two_chain_time_ = 0;
    uint32_t tx_ipa_active_one_chain_time_ = 0;
    uint32_t tx_ipa_active_two_chain_time_ = 0;
    uint32_t tx_xpa_active_one_chain_time_ = 0;
    uint32_t tx_xpa_active_two_chain_time_ = 0;
};

}  // namespace bluetooth_hal::bqr
