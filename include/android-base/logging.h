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
#include <iostream>
#include <string>

namespace android {
namespace base {

enum LogSeverity {
    VERBOSE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL_WITHOUT_ABORT,
    FATAL,
};

class LogMessage {
public:
    LogMessage(const char* file, unsigned int line, LogSeverity severity, const char* tag, int error);
    ~LogMessage();
    std::ostream& stream();
};

bool ShouldLog(LogSeverity severity, const char* tag);

} // namespace base
} // namespace android

#ifndef LOG_TAG
#define LOG_TAG "TAG"
#endif

#define LOG(severity)                                                        \
  if (::android::base::ShouldLog(::android::base::severity, LOG_TAG))        \
  ::android::base::LogMessage(__FILE__, __LINE__, ::android::base::severity, \
                              LOG_TAG, -1)                                   \
      .stream()
