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

#include "bluetooth_hal/bqr/bqr_advance_rf_stats_event.h"
#include "bluetooth_hal/hal_packet.h"

namespace bluetooth_hal::bqr {

enum class AdvanceRfStatsOffsetV7 : uint8_t {
    kAntSwitchCount = static_cast<uint8_t>(AdvanceRfStatsOffset::kEnd),  // 4 bytes
    kReTxIpaBf = kAntSwitchCount + 4,                                    // 4 bytes
    kReTxEpaBf = kReTxIpaBf + 4,                                         // 4 bytes
    kReTxIpaDiv = kReTxEpaBf + 4,                                        // 4 bytes
    kReTxEpaDiv = kReTxIpaDiv + 4,                                       // 4 bytes
    kChCountGood = kReTxEpaDiv + 4,                                      // 1 byte
    kChCountOk = kChCountGood + 1,                                       // 1 byte
    kChCountBad = kChCountOk + 1,                                        // 1 byte
    kChCountVeryBad = kChCountBad + 1,                                   // 1 byte
    kTxBufQueueCount = kChCountVeryBad + 1,                              // 4 bytes
    kEnd = kTxBufQueueCount + 4,
};

// BQR Advance RF Stats event V7.
class BqrAdvanceRfStatsEventV7 : public BqrAdvanceRfStatsEvent {
  public:
    explicit BqrAdvanceRfStatsEventV7(const ::bluetooth_hal::hci::HalPacket& packet);
    virtual ~BqrAdvanceRfStatsEventV7() = default;

    bool IsValid() const override;

    uint32_t GetAntSwitchCount() const;
    uint32_t GetReTxIpaBf() const;
    uint32_t GetReTxEpaBf() const;
    uint32_t GetReTxIpaDiv() const;
    uint32_t GetReTxEpaDiv() const;
    uint8_t GetChCountGood() const;
    uint8_t GetChCountOk() const;
    uint8_t GetChCountBad() const;
    uint8_t GetChCountVeryBad() const;
    uint32_t GetTxBufQueueCount() const;

    // Returns a string representation of the event.
    std::string ToString() const;

  protected:
    void ParseData();
    std::string ToBqrString() const;

  private:
    bool is_valid_;
    uint32_t ant_switch_count_ = 0;
    uint32_t re_tx_ipa_bf_ = 0;
    uint32_t re_tx_epa_bf_ = 0;
    uint32_t re_tx_ipa_div_ = 0;
    uint32_t re_tx_epa_div_ = 0;
    uint8_t ch_count_good_ = 0;
    uint8_t ch_count_ok_ = 0;
    uint8_t ch_count_bad_ = 0;
    uint8_t ch_count_verybad_ = 0;
    uint32_t tx_buf_queue_count_ = 0;
};

}  // namespace bluetooth_hal::bqr
