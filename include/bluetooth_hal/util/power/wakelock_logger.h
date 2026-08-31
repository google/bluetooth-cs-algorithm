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
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <utility>
#include <vector>

#include "bluetooth_hal/debug/debug_client.h"
#include "bluetooth_hal/hal_types.h"
#include "bluetooth_hal/util/power/wakelock.h"
#include "bluetooth_hal/util/time_queue.h"

namespace bluetooth_hal::util::power {

enum class TimeUnit : uint8_t {
    kTwoFiftyMs = 0,
    kFiveHundredMs,
    kOneSec,
    kTwoSec,
    kFourSec,
    kEightSec,
    kSixteenSec,
    kThirtySec,
    kOneMin,
    kFiveMin,
    kTenMin,
    kTwentyMin,
    kTwentyMinPlus,
    kTimeUnitMax
};

struct WakelockTimeSlot {
    std::array<int, static_cast<size_t>(TimeUnit::kTimeUnitMax)> acl_tx = {0};
    std::array<int, static_cast<size_t>(TimeUnit::kTimeUnitMax)> acl_rx = {0};
    std::array<int, static_cast<size_t>(TimeUnit::kTimeUnitMax)> commands = {0};
    std::array<int, static_cast<size_t>(TimeUnit::kTimeUnitMax)> events = {0};
};

class WakelockLogger : public ::bluetooth_hal::debug::DebugClient {
  public:
    WakelockLogger();
    virtual ~WakelockLogger() = default;

    void StartSession();
    void RecordActivity(WakeSource source, ::bluetooth_hal::hci::HciPacketType type);
    void EndSession();

    std::vector<::bluetooth_hal::debug::Coredump> Dump() override;

  private:
    std::mutex mutex_;
    bool is_session_active_ = false;
    std::chrono::steady_clock::time_point session_start_time_;
    int tx_count_ = 0;
    int rx_count_ = 0;
    int command_count_ = 0;
    int event_count_ = 0;
    ::bluetooth_hal::util::TimeQueue<WakelockTimeSlot> history_;
};

}  // namespace bluetooth_hal::util::power
