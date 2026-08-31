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

#include <chrono>
#include <cstdint>
#include <string>

#include "bluetooth_hal/bqr/bqr_event.h"
#include "bluetooth_hal/hal_packet.h"

namespace bluetooth_hal::bqr {

//------------------------------------------------------//
// Synchronization Timestamp BQR Event
//------------------------------------------------------//
// parameter             | format | content
// event                 | 1 byte | 0x04
// event code            | 1 byte | 0xFF (Vendor Specific Event)
// length                | 1 byte | 0x0B
// event sub-code        | 1 byte | 0x58 (BQR)
// vendor report id      | 1 byte | 0xF0 (New: BQR Timestamp Event)
// sub id                | 1 byte | 0x00 (Synchronization)
// timestamp             | 8 byte | <offload processor timestamp>
//------------------------------------------------------//
// Offload timestamp event packet
//------------------------------------------------------//
// parameter             | format | content
// event                 | 1 byte | 0x04
// event code            | 1 byte | 0xFF (Vendor Specific Event)
// length                | 1 byte | 0x0C
// event sub-code        | 1 byte | 0x58 (BQR)
// vendor report id      | 1 byte | 0xF0 (New: BQR Timestamp Event)
// sub id                | 1 byte | 0x01 (Offload Event)
// timestamp             | 8 byte | <offload processor timestamp>
// target sub event      | 1 byte | <target offload event sub event_id>

enum class BqrOffloadOffset : uint8_t {
    kStart = 5,
    kSubId = kStart,               // 1 byte
    kTimestamp = kStart + 1,       // 8 bytes
    kTargetSubEvent = kStart + 9,  // 1 byte
    kEnd = kStart + 10,
};

enum class BqrOffloadSubId : uint8_t {
    kSynchronizationTimestamp = 0x00,
    kOffloadEventTimestamp = 0x01,
};

class BqrOffloadEvent : public BqrEvent {
  public:
    explicit BqrOffloadEvent(const ::bluetooth_hal::hci::HalPacket& packet);

    // Calculates and returns the real time of the offload event.
    std::chrono::system_clock::time_point GetOffloadEventRealTime() const;

    // Rerun Offload event real time for matched sub id
    std::chrono::system_clock::time_point GetOffloadEventRealTimeBySubId(uint8_t sub_id) const;

    // Converts a time_point to a string representation.
    static std::string TimePointToString(std::chrono::system_clock::time_point tp);

    // Returns a string representation of the vendor specific part of the event.
    std::string ToString() const;

  protected:
    void ParseData();
    std::string ToVendorBqrString() const;

  private:
    uint8_t sub_id_ = 0;
    mutable uint64_t timestamp_ = 0;
    uint8_t target_sub_event_ = 0;

    // Recorded device real time at parsing
    std::chrono::system_clock::time_point device_real_time_;

    // Synchronization points (static to persist across instances)
    static inline uint64_t last_sync_offload_timestamp_ = 0;
    static inline std::chrono::system_clock::time_point last_sync_device_real_time_ =
            std::chrono::system_clock::time_point();
};

}  // namespace bluetooth_hal::bqr
