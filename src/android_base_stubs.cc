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

#include "android-base/properties.h"
#include "android-base/logging.h"
#include <iostream>

// A dummy stream to discard all log output
class NullStream : public std::ostream {
public:
    NullStream() : std::ostream(nullptr) {}
};

template <class T>
NullStream& operator<<(NullStream& s, const T&) {
    return s;
}

static NullStream g_null_stream;


// Stubs for android-base/properties.h
namespace android {
namespace base {

bool GetBoolProperty(const std::string& key, bool default_value) {
    (void)key; // suppress unused parameter warning
    return default_value;
}

template <typename T>
T GetIntProperty(const std::string& key, T default_value, T min, T max) {
    (void)key; (void)min; (void)max; // suppress unused parameter warning
    return default_value;
}
// Explicitly instantiate the template for the types that are used.
template int GetIntProperty<int>(const std::string&, int, int, int);


std::string GetProperty(const std::string& key, const std::string& default_value) {
    (void)key; // suppress unused parameter warning
    return default_value;
}

// Stubs for android-base/logging.h
LogMessage::LogMessage(const char* file, unsigned int line, LogSeverity severity, const char* tag, int error) {
    (void)file; (void)line; (void)severity; (void)tag; (void)error;
}

LogMessage::~LogMessage() {}

std::ostream& LogMessage::stream() {
    return g_null_stream;
}

bool ShouldLog(LogSeverity severity, const char* tag) {
    (void)severity; (void)tag;
    return false;
}

} // namespace base
} // namespace android