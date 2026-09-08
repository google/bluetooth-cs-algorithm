# Bluetooth Channel Sounding Ranging Algorithm

This is a standalone, open-source C++ implementation and testbench for a Bluetooth Channel Sounding distance estimation algorithm.

## Prerequisites
* C++20 compatible compiler (e.g., GCC or Clang)
* CMake (v3.14+)

*(Dependencies like Eigen and nlohmann_json will be fetched automatically by CMake during the build process).*

## Directory Structure
* `src/`: Core algorithm implementation (`bluetooth_channel_sounding_algorithm.cc`) and Android stubs.
* `include/`: Public headers (`bluetooth_channel_sounding_algorithm.h`), including stubbed AIDL and HAL headers to decouple from the Android source tree.
* `test/`: Testbench for validating the algorithm against test vectors.
* `test_data/`: Sample JSON files to run through the testbench.

## Build Instructions
1. Create a build directory and run CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   ```
2. Build the project:
   ```bash
   make
   ```

## Running the Testbench
After building, you can run the testbench executable and provide a test vector JSON file using the `-i` flag (an optional output file can be specified with `-o`):
```bash
./channel_sounding_algorithm_test -i ../test_data/<sample_file>.json
```
The testbench will process the data and generate a JSON file (defaulting to `ranging_results.json`) containing the algorithm's calculated distance, confidence level, and velocity.


Eligibility for the [Google Open Source Software Vulnerability Rewards
Program](https://bughunters.google.com/open-source-security) is determined by the [Google Open Source Software Vulnerability Reward Program Rules](https://bughunters.google.com/about/rules/open-source/google-open-source-software-vulnerability-reward-program-rules).
