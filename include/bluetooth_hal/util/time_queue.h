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
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <deque>
#include <optional>
#include <string>
#include <utility>

namespace bluetooth_hal::util {

template <typename T>
class TimeQueue;

/**
 * @class TimeSlot
 * @brief Holds the element and its associated time range.
 */
template <typename T>
class TimeSlot {
  public:
    TimeSlot(T data, std::chrono::system_clock::time_point start_time)
        : data(std::move(data)), start_time_(start_time) {}

    T data;

    /**
     * @brief Formats the time range to "MM-DD HH:MM:SS.MMM to [MM-DD HH:MM:SS.MMM
     * | Current]".
     */
    std::string TimePeriodToString() const {
        auto format_time = [](std::chrono::system_clock::time_point tp) {
            auto t = std::chrono::system_clock::to_time_t(tp);
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()) %
                      1000;
            std::tm tm_buf;
            localtime_r(&t, &tm_buf);
            char buf[64];
            std::strftime(buf, sizeof(buf), "%m-%d %H:%M:%S", &tm_buf);
            char final_buf[128];
            snprintf(final_buf, sizeof(final_buf), "%s.%03d", buf, static_cast<int>(ms.count()));
            return std::string(final_buf);
        };

        std::string result = format_time(start_time_) + " to ";
        if (end_time_.has_value()) {
            result += format_time(end_time_.value());
        } else {
            result += "Current";
        }
        return result;
    }

  private:
    std::chrono::system_clock::time_point start_time_;
    std::optional<std::chrono::system_clock::time_point> end_time_;

    template <typename U>
    friend class TimeQueue;
};

/**
 * @class TimeQueue
 * @brief A deque-based queue that automatically allocates new nodes
 * based on time intervals.
 *
 * This class ensures a fresh node exists and returns a reference to the latest
 * T. It extends std::deque<TimeSlot<T>> to support standard iteration and
 * access.
 *
 * @note This class is **not thread-safe**. Users are responsible for
 * synchronizing access to the queue if it's used across multiple threads.
 *
 * @tparam T The type of elements stored in the queue.
 */
template <typename T>
class TimeQueue : public std::deque<TimeSlot<T>> {
  public:
    static constexpr std::chrono::minutes kDefaultTimeGap{30};
    static constexpr size_t kDefaultMaxSize = 48;

    /**
     * @brief Constructs a TimeQueue.
     *
     * @param time_gap The duration that must elapse before a new node is
     * allocated. Defaults to 30 minutes.
     * @param max_size The maximum number of elements to keep in the queue.
     *                 Defaults to 48.
     */
    explicit TimeQueue(std::chrono::milliseconds time_gap = kDefaultTimeGap,
                       size_t max_size = kDefaultMaxSize)
        : time_gap_(time_gap), max_size_(max_size) {}

    /**
     * @brief Ensures a fresh node is available and returns a reference to the
     * latest member.
     *
     * This method calls SynchronizeTimeSlot() and then returns the
     * reference to the last element in the queue.
     *
     * @return A reference to the latest T in the queue.
     */
    T& current() {
        SynchronizeTimeSlot();
        return this->back().data;
    }

  private:
    /**
     * @brief Internal implementation of SynchronizeTimeSlot.
     */
    bool SynchronizeTimeSlot() {
        auto now = std::chrono::system_clock::now();
        if (this->empty()) {
            this->emplace_back(T(), now);
            last_alloc_time_ = now;
            return true;
        }

        if ((now - last_alloc_time_) >= time_gap_) {
            // Update the previous tail with its end time
            this->back().end_time_ = last_alloc_time_ + time_gap_;

            if (this->size() >= max_size_) {
                this->pop_front();
            }
            this->emplace_back(T(), now);
            last_alloc_time_ = now;
            return true;
        }

        return false;
    }

    std::chrono::milliseconds time_gap_;
    size_t max_size_;
    std::chrono::system_clock::time_point last_alloc_time_;
};

}  // namespace bluetooth_hal::util
