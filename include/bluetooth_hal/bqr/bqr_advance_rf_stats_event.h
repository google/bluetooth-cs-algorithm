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

enum class AdvanceRfStatsOffset : uint8_t {
    // After H4 type(1) + event code(1) + length(1) + sub event(1) + report id(1)
    kExtInfo = 5,                         // 1 byte
    kTmPeriod = kExtInfo + 1,             // 4 bytes
    kTxPwIpaBf = kTmPeriod + 4,           // 4 bytes
    kTxPwEpaBf = kTxPwIpaBf + 4,          // 4 bytes
    kTxPwIpaDiv = kTxPwEpaBf + 4,         // 4 bytes
    kTxPwEpaDiv = kTxPwIpaDiv + 4,        // 4 bytes
    kRssiCh50 = kTxPwEpaDiv + 4,          // 4 bytes
    kRssiCh50_55 = kRssiCh50 + 4,         // 4 bytes
    kRssiCh55_60 = kRssiCh50_55 + 4,      // 4 bytes
    kRssiCh60_65 = kRssiCh55_60 + 4,      // 4 bytes
    kRssiCh65_70 = kRssiCh60_65 + 4,      // 4 bytes
    kRssiCh70_75 = kRssiCh65_70 + 4,      // 4 bytes
    kRssiCh75_80 = kRssiCh70_75 + 4,      // 4 bytes
    kRssiCh80_85 = kRssiCh75_80 + 4,      // 4 bytes
    kRssiCh85_90 = kRssiCh80_85 + 4,      // 4 bytes
    kRssiCh90 = kRssiCh85_90 + 4,         // 4 bytes
    kRssiDelta2Down = kRssiCh90 + 4,      // 4 bytes
    kRssiDelta2_5 = kRssiDelta2Down + 4,  // 4 bytes
    kRssiDelta5_8 = kRssiDelta2_5 + 4,    // 4 bytes
    kRssiDelta8_11 = kRssiDelta5_8 + 4,   // 4 bytes
    kRssiDelta11Up = kRssiDelta8_11 + 4,  // 4 bytes
    kEnd = kRssiDelta11Up + 4,
};

// BQR Advance RF Stats event.
class BqrAdvanceRfStatsEvent : public BqrEvent {
  public:
    explicit BqrAdvanceRfStatsEvent(const ::bluetooth_hal::hci::HalPacket& packet);
    virtual ~BqrAdvanceRfStatsEvent() = default;

    bool IsValid() const override;

    uint8_t GetExtInfo() const;
    uint32_t GetTmPeriod() const;
    uint32_t GetTxPwIpaBf() const;
    uint32_t GetTxPwEpaBf() const;
    uint32_t GetTxPwIpaDiv() const;
    uint32_t GetTxPwEpaDiv() const;
    uint32_t GetRssiCh50() const;
    uint32_t GetRssiCh50_55() const;
    uint32_t GetRssiCh55_60() const;
    uint32_t GetRssiCh60_65() const;
    uint32_t GetRssiCh65_70() const;
    uint32_t GetRssiCh70_75() const;
    uint32_t GetRssiCh75_80() const;
    uint32_t GetRssiCh80_85() const;
    uint32_t GetRssiCh85_90() const;
    uint32_t GetRssiCh90() const;
    uint32_t GetRssiDelta2Down() const;
    uint32_t GetRssiDelta2_5() const;
    uint32_t GetRssiDelta5_8() const;
    uint32_t GetRssiDelta8_11() const;
    uint32_t GetRssiDelta11Up() const;

    // Returns a string representation of the event.
    std::string ToString() const;

  protected:
    void ParseData();
    std::string ToBqrString() const;

  private:
    bool is_valid_;
    uint8_t ext_info_ = 0;
    uint32_t tm_period_ = 0;
    uint32_t tx_pw_ipa_bf_ = 0;
    uint32_t tx_pw_epa_bf_ = 0;
    uint32_t tx_pw_ipa_div_ = 0;
    uint32_t tx_pw_epa_div_ = 0;
    uint32_t rssi_ch_50_ = 0;
    uint32_t rssi_ch_50_55_ = 0;
    uint32_t rssi_ch_55_60_ = 0;
    uint32_t rssi_ch_60_65_ = 0;
    uint32_t rssi_ch_65_70_ = 0;
    uint32_t rssi_ch_70_75_ = 0;
    uint32_t rssi_ch_75_80_ = 0;
    uint32_t rssi_ch_80_85_ = 0;
    uint32_t rssi_ch_85_90_ = 0;
    uint32_t rssi_ch_90_ = 0;
    uint32_t rssi_delta_2_down_ = 0;
    uint32_t rssi_delta_2_5_ = 0;
    uint32_t rssi_delta_5_8_ = 0;
    uint32_t rssi_delta_8_11_ = 0;
    uint32_t rssi_delta_11_up_ = 0;
};

}  // namespace bluetooth_hal::bqr
