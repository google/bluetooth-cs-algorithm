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

#include <string>

#include "android-base/logging.h"

/*
 * Helper mecro for LogHelper to print system log with a specific tag.
 */
#define LOG_WITH_TAG(severity, tag) \
    ::android::base::LogMessage(__FILE__, __LINE__, SEVERITY_LAMBDA(severity), tag, -1).stream()

namespace bluetooth_hal::util {

class Logger {
  public:
    /**
     * @brief Generates a timestamp string suitable for log messages.
     *
     * The timestamp is formatted as MM-DD HH:MM:SS.sss L (month, day, hours,
     * minutes, seconds, milliseconds, log level). It represents the current
     * local time with millisecond precision.
     *
     * @param severity The log severity level.
     * @return A string representing the current local time and log level.
     *
     */
    static std::string GetLogFormatTimestamp(::android::base::LogSeverity severity);

    /**
     * @brief Generates a timestamp string suitable for log messages without log
     * level.
     *
     * The timestamp is formatted as MM-DD HH:MM:SS.sss. It represents the current
     * local time with millisecond precision.
     *
     * @return A string representing the current local time.
     *
     */
    static std::string GetLogFormatTimestamp();

    /**
     * @brief Generates a timestamp string suitable for record creation.
     *
     * The timestamp is formatted as YYYY-MM-DD_HH-MM-SS (year, month, day, hours,
     * minutes, seconds). It represents the current local time.
     *
     * @return A string representing the current local time in the format
     * YYYY-MM-DD_HH-MM-SS.
     *
     */
    static std::string GetFileFormatTimestamp();

    /**
     * @brief Writes a message to the kernel log (/dev/kmsg).
     *
     * @param message The message to write.
     *
     */
    static void WriteToKernelLog(const std::string& message);
};

}  // namespace bluetooth_hal::util
