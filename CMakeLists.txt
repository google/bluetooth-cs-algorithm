# Copyright 2026 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.14)
if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(BluetoothChannelSoundingAlgorithm CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Suppress offline_testing define since we are standalone
add_definitions(-Doffline_testing)

include(FetchContent)

# Fetch Eigen
FetchContent_Declare(
    eigen
    URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
)
FetchContent_MakeAvailable(eigen)

# Fetch nlohmann_json header only
include(ExternalProject)
set(JSON_HEADER_DIR ${CMAKE_BINARY_DIR}/json_header)
file(DOWNLOAD https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp ${JSON_HEADER_DIR}/nlohmann/json.hpp)
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE ${JSON_HEADER_DIR})

# Add include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# Create the testbench executable
add_executable(channel_sounding_algorithm_test
    src/bluetooth_channel_sounding_algorithm.cc
    src/android_base_stubs.cc
    test/channel_sounding_algorithm_test.cc
)

# Link dependencies
target_link_libraries(channel_sounding_algorithm_test
    PRIVATE
    Eigen3::Eigen
    nlohmann_json
)
