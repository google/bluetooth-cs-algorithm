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
#include <limits>

namespace android {
namespace base {

bool GetBoolProperty(const std::string& key, bool default_value);

template <typename T>
T GetIntProperty(const std::string& key, T default_value, T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max());

std::string GetProperty(const std::string& key, const std::string& default_value);

}  // namespace base
}  // namespace android
