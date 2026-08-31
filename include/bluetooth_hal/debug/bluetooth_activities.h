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

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>

#include "bluetooth_hal/hal_packet.h"
#include "bluetooth_hal/hal_types.h"

namespace bluetooth_hal::debug {

class BluetoothActivities {
  public:
    virtual ~BluetoothActivities() = default;

    using ConnectionCountChangedCallback = std::function<void(int new_connected_device_count)>;

    class [[nodiscard]] ConnectionCallbackSubscription {
      public:
        ConnectionCallbackSubscription(std::function<void()> unregister_func)
            : unregister_(std::move(unregister_func)) {}

        ~ConnectionCallbackSubscription() {
            if (unregister_) {
                unregister_();
            }
        }

        ConnectionCallbackSubscription(ConnectionCallbackSubscription&&) = default;
        ConnectionCallbackSubscription& operator=(ConnectionCallbackSubscription&&) = default;

      private:
        std::function<void()> unregister_;
    };

    /**
     * @brief Start the activities monitoring process.
     *
     * This function should be called before any other functions in this class are
     * used.
     */
    static void Start();

    /**
     * @brief Get the singleton instance of BluetoothActivities.
     *
     * @return The singleton instance of BluetoothActivities.
     */
    static BluetoothActivities& Get();

    /**
     * @brief Stop the activities monitoring process, and clear the connections.
     *
     * After calling this function, all of the current connections and the
     * connection history will be cleared. The instance will be reset.
     */
    static void Stop();

    /**
     * @brief Checks if there are any connected Bluetooth devices.
     *
     * @return true if there is at least one connected device, false otherwise.
     */
    virtual bool HasConnectedDevice() const = 0;

    /**
     * @brief Checks if a specific Bluetooth device is connected.
     *
     * @param connection_handle The handle of the Bluetooth connection to check.
     * @return true if the device with the given connection handle is connected,
     * false otherwise.
     */
    virtual bool IsConnected(uint16_t connection_handle) const = 0;

    /**
     * @brief Gets the number of connected devices.
     *
     * @return The number of connected devices.
     */
    virtual size_t GetConnectionHandleCount() const = 0;

    /**
     * @brief Registers a callback to be invoked when the number of connected
     * devices changes.
     *
     * @param callback The callback function to register. It takes an integer
     * representing the new count of connected devices as an argument.
     * @return A ConnectionCallbackSubscription object. When this object is
     * destroyed, the registered callback will be automatically unregistered.
     */
    virtual ConnectionCallbackSubscription RegisterConnectionCountChangedCallback(
            ConnectionCountChangedCallback callback) = 0;

    virtual void OnMonitorPacketCallback(::bluetooth_hal::hci::MonitorMode mode,
                                         const ::bluetooth_hal::hci::HalPacket& packet) = 0;

    virtual void OnBluetoothChipClosed() = 0;

  protected:
    BluetoothActivities() = default;

  private:
    static inline std::mutex mutex_;
    static std::unique_ptr<BluetoothActivities> instance_;
};

}  // namespace bluetooth_hal::debug
