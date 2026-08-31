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

#include "bluetooth_hal/bqr/bqr_energy_monitoring_event_v6.h"
#include "bluetooth_hal/hal_packet.h"

namespace bluetooth_hal::bqr {

enum class EnergyMonitoringOffsetV7 : uint8_t {
    kBredrRxActiveScanTotaltime = static_cast<uint8_t>(EnergyMonitoringOffsetV6::kEnd),  // 4 bytes
    kLeRxActiveScanTotaltime = kBredrRxActiveScanTotaltime + 4,                          // 4 bytes
    kEnd = kLeRxActiveScanTotaltime + 4,
};

// BQR Energy Monitoring event V7.
class BqrEnergyMonitoringEventV7 : public BqrEnergyMonitoringEventV6 {
  public:
    explicit BqrEnergyMonitoringEventV7(const ::bluetooth_hal::hci::HalPacket& packet);
    virtual ~BqrEnergyMonitoringEventV7() = default;

    bool IsValid() const override;

    uint32_t GetBredrRxActiveScanTotaltime() const;
    uint32_t GetLeRxActiveScanTotaltime() const;

    // Returns a string representation of the event.
    std::string ToString() const;

  protected:
    void ParseData();
    std::string ToBqrString() const;

  private:
    bool is_valid_;
    uint32_t bredr_rx_active_scan_totaltime_;
    uint32_t le_rx_active_scan_totaltime_;
};

}  // namespace bluetooth_hal::bqr
