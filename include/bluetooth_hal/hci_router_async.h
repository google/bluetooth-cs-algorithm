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

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <utility>

#include "bluetooth_hal/hal_packet.h"
#include "bluetooth_hal/hal_types.h"
#include "bluetooth_hal/hci_router_callback.h"
#include "bluetooth_hal/transport/transport_instance.h"
#include "bluetooth_hal/util/timer_manager.h"
#include "bluetooth_hal/util/worker.h"

namespace bluetooth_hal::hci {

class RouterTask {
  public:
    RouterTask(std::function<void()> task) : task_(std::move(task)) {};
    void Run() { task_(); }

  private:
    std::function<void()> task_;
};

class HciRouterAsync : public ::bluetooth_hal::util::Worker<RouterTask> {
  public:
    HciRouterAsync();
    virtual ~HciRouterAsync() = default;

    virtual bool DoInRouterThread(std::function<void()> task);
    virtual bool SynchronousDoInRouterThread(std::function<void()> task);
    virtual ::bluetooth_hal::HalState GetHalState();

    // Internal handlers meant to be called by the router thread
    virtual bool InitializeModules(
            ::bluetooth_hal::transport::TransportInstanceCallback* transport_callback);
    virtual bool Initialize(
            const std::shared_ptr<HciRouterCallback>& callback,
            ::bluetooth_hal::transport::TransportInstanceCallback* transport_callback);
    virtual void Close();
    virtual void Cleanup();
    virtual bool Send(const HalPacket& packet);
    virtual bool SendCommand(const HalPacket& packet,
                             const std::shared_ptr<HalPacketCallback>& callback);
    virtual bool SendCommandNoAck(const HalPacket& packet);
    virtual void UpdateHalState(::bluetooth_hal::HalState state);
    virtual void SendPacketToStack(const HalPacket& packet);
    virtual void OnTransportPacketReady(const HalPacket& packet);

  private:
    struct QueuedHciCommand {
        HalPacket command;
        std::shared_ptr<HalPacketCallback> callback;
    };

    void TaskHandler(RouterTask task);
    void VoteRouterTaskWakelock();
    void UnvoteRouterTaskWakelock();

    bool SendToTransport(const HalPacket& packet);
    void HandleCommandCompleteOrCommandStatusEvent(const HalPacket& event);
    bool InitializeTransport();
    bool RetryInitializeModules(
            ::bluetooth_hal::transport::TransportInstanceCallback* transport_callback);
    bool IsHalStateValid(::bluetooth_hal::HalState new_state);
    void HandleReceivedPacket(const HalPacket& packet);
    bool SendOrQueueCommand(const HalPacket& packet,
                            const std::shared_ptr<HalPacketCallback> callback);
    void OnCommandCallbackCompleted();
    void SetBusy(bool busy);

    std::shared_ptr<HciRouterCallback> hci_callback_;
    ::bluetooth_hal::transport::TransportInstanceCallback* transport_callback_;
    ::bluetooth_hal::HalState hal_state_{::bluetooth_hal::HalState::kShutdown};
    std::atomic<bool> is_cleaning_up_{false};
    std::queue<QueuedHciCommand> hci_cmd_queue_;
    std::atomic<bool> is_busy_{false};

    std::mutex task_wakelock_mutex_;
    int wake_lock_votes_{0};

    int initialize_retry_count_{0};
    ::bluetooth_hal::util::Timer initialize_timer_;
};

}  // namespace bluetooth_hal::hci
