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

#include "bluetooth_hal/bqr/bqr_event.h"
#include "bluetooth_hal/hal_packet.h"

namespace bluetooth_hal::bqr {

enum class EnergyMonitoringOffset : uint8_t {
    // After H4 type(1) + event code(1) + length(1) + sub event(1) + report id(1)
    kAverageCurrentConsumption = 5,                           // 2 bytes
    kIdleTotalTime = kAverageCurrentConsumption + 2,          // 4 bytes
    kIdleStateEnterCount = kIdleTotalTime + 4,                // 4 bytes
    kActiveTotalTime = kIdleStateEnterCount + 4,              // 4 bytes
    kActiveStateEnterCount = kActiveTotalTime + 4,            // 4 bytes
    kBrEdrTxTotalTime = kActiveStateEnterCount + 4,           // 4 bytes
    kBrEdrTxStateEnterCount = kBrEdrTxTotalTime + 4,          // 4 bytes
    kBrEdrTxAveragePowerLevel = kBrEdrTxStateEnterCount + 4,  // 1 byte
    kBrEdrRxTotalTime = kBrEdrTxAveragePowerLevel + 1,        // 4 bytes
    kBrEdrRxStateEnterCount = kBrEdrRxTotalTime + 4,          // 4 bytes
    kLeTxTotalTime = kBrEdrRxStateEnterCount + 4,             // 4 bytes
    kLeTxStateEnterCount = kLeTxTotalTime + 4,                // 4 bytes
    kLeTxAveragePowerLevel = kLeTxStateEnterCount + 4,        // 1 byte
    kLeRxTotalTime = kLeTxAveragePowerLevel + 1,              // 4 bytes
    kLeRxStateEnterCount = kLeRxTotalTime + 4,                // 4 bytes
    kEnd = kLeRxStateEnterCount + 4,
};

// BQR Energy Monitoring event.
class BqrEnergyMonitoringEvent : public BqrEvent {
  public:
    explicit BqrEnergyMonitoringEvent(const ::bluetooth_hal::hci::HalPacket& packet);
    virtual ~BqrEnergyMonitoringEvent() = default;

    bool IsValid() const override;

    uint16_t GetAverageCurrentConsumption() const;
    uint32_t GetIdleTotalTime() const;
    uint32_t GetIdleStateEnterCount() const;
    uint32_t GetActiveTotalTime() const;
    uint32_t GetActiveStateEnterCount() const;
    uint32_t GetBrEdrTxTotalTime() const;
    uint32_t GetBrEdrTxStateEnterCount() const;
    int8_t GetBrEdrTxAveragePowerLevel() const;
    uint32_t GetBrEdrRxTotalTime() const;
    uint32_t GetBrEdrRxStateEnterCount() const;
    uint32_t GetLeTxTotalTime() const;
    uint32_t GetLeTxStateEnterCount() const;
    int8_t GetLeTxAveragePowerLevel() const;
    uint32_t GetLeRxTotalTime() const;
    uint32_t GetLeRxStateEnterCount() const;

    // Returns a string representation of the event.
    std::string ToString() const;

  protected:
    void ParseData();
    std::string ToBqrString() const;

  private:
    bool is_valid_;
    uint16_t average_current_consumption_ = 0;
    uint32_t idle_total_time_ = 0;
    uint32_t idle_state_enter_count_ = 0;
    uint32_t active_total_time_ = 0;
    uint32_t active_state_enter_count_ = 0;
    uint32_t br_edr_tx_total_time_ = 0;
    uint32_t br_edr_tx_state_enter_count_ = 0;
    int8_t br_edr_tx_average_power_level_ = 0;
    uint32_t br_edr_rx_total_time_ = 0;
    uint32_t br_edr_rx_state_enter_count_ = 0;
    uint32_t le_tx_total_time_ = 0;
    uint32_t le_tx_state_enter_count_ = 0;
    int8_t le_tx_average_power_level_ = 0;
    uint32_t le_rx_total_time_ = 0;
    uint32_t le_rx_state_enter_count_ = 0;
};

}  // namespace bluetooth_hal::bqr
