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

#include "bluetooth_hal/hal_packet.h"
#include "bluetooth_hal/hal_types.h"

namespace bluetooth_hal::transport {

/**
 * @brief Class for handling transport-related events.
 *
 * This Class defines callbacks for handling transport events such as
 * connection closure and packet readiness. Implementations of this class
 * should provide concrete behaviors for these events.
 */
class TransportInstanceCallback {
  public:
    virtual ~TransportInstanceCallback() = default;

    /**
     * @brief Called when the transport connection is closed.
     *
     * Implementations should handle any necessary cleanup or state updates when
     * the transport is closed.
     *
     */
    virtual void OnTransportClosed() = 0;

    /**
     * @brief Called when a packet is ready to be processed.
     *
     * @param packet The received packet that needs to be processed.
     *
     * Implementations should process the given packet accordingly. This method
     * does not return a callback, meaning the implementation is expected to
     * handle the packet directly within this function.
     *
     */
    virtual void OnTransportPacketReady(const ::bluetooth_hal::hci::HalPacket& packet) = 0;
};

/**
 * @brief Abstracts the transport layer for devices, providing interfaces for
 * control and data management.
 */
class TransportInstance {
  public:
    virtual ~TransportInstance() = default;

    /**
     * @brief Initializes the transport instance with a transport callback.
     *
     * @param transport_instance_callback A pointer to a
     * `TransportInstanceCallback` responsible for handling transport layer
     * events such as packet reception, connection closure, etc.
     *
     * @return True if initialization succeeds, false otherwise.
     *
     */
    virtual bool Initialize(TransportInstanceCallback* transport_instance_callback) = 0;

    /**
     * @brief Cleans up resources and disconnects the transport instance.
     *
     */
    virtual void Cleanup() = 0;

    /**
     * @brief Checks if the current transport is active and operational.
     *
     * @return `true` if the transport is active and communication is operational,
     * `false` otherwise.
     *
     */
    virtual bool IsTransportActive() const = 0;

    /**
     * @brief Sends a single packet with the specified type.
     *
     * @param packet The content of the packet to be transmitted.
     *
     * @return `true` if packet is sent successfully, `false` otherwise.
     *
     */
    virtual bool Send(const ::bluetooth_hal::hci::HalPacket& packet) = 0;

    /**
     * @brief Retrieves the specific transport type of this instance.
     *
     * @return The TransportType of this concrete transport instance.
     *
     */
    virtual TransportType GetInstanceTransportType() const = 0;

    /**
     * @brief Updates the busy state of the hci router.
     *
     * This function is called to indicate whether the hci router is currently
     * busy. The base implementation does nothing. Derived classes can override
     * this to handle the busy state change. This should be called by hci router.
     *
     * @param is_busy A boolean indicating the new busy state of the hci router.
     * Pass true if the hci router is busy, or false otherwise.
     *
     */
    virtual void SetHciRouterBusy(bool /*is_busy*/) {}
};

}  // namespace bluetooth_hal::transport
