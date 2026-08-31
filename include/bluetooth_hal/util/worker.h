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
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include "android-base/logging.h"
#include "bluetooth_hal/util/system_call_wrapper.h"

namespace bluetooth_hal::util {

enum class QueueMode {
    kBlock,
    kEvict,
};

constexpr size_t kDefaultMaxQueueSize = 10;
constexpr std::chrono::seconds kPostTimeout{10};

template <typename Message>
class Worker {
  public:
    explicit Worker(std::function<void(Message)> handler,
                    size_t max_queue_size = kDefaultMaxQueueSize,
                    QueueMode queue_mode = QueueMode::kBlock)
        : handler_(std::move(handler)),
          kMaxQueueSize(max_queue_size),
          queue_mode_(queue_mode),
          running_(true) {
        worker_thread_ = std::thread(&Worker::RunWorkerLoop, this);
    };

    ~Worker() {
        Stop();
        if (worker_thread_.joinable()) {
            worker_thread_.join();
        }
    };

    /**
     * @brief Posts a message to the queue. Blocks if the queue is full.
     *
     * Waits until the queue has space available or the worker is stopped.
     * If the worker is stopped, the message will not be posted.
     *
     * @param message The message to post.
     * @return True if the message was successfully posted, false if timeout or
     * the worker has been stopped.
     */
    bool Post(Message message) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!running_) {
            return false;
        }

        auto is_full = [&] { return message_queue_.size() >= kMaxQueueSize; };

        switch (queue_mode_) {
            case QueueMode::kBlock: {
                if (is_full()) {
                    bool is_worker_thread_ = std::this_thread::get_id() == GetThreadId();
                    bool wait_success = producer_cv_.wait_for(lock, kPostTimeout, [&] {
                        return !is_full() || !running_ || is_worker_thread_;
                    });
                    if (!running_) {
                        return false;
                    }
                    if (!wait_success) {
                        LOG(FATAL) << __func__ << ": Timeout, no space in the message queue.";
                        return false;
                    }
                    if (is_worker_thread_) {
                        // Allow self-posts to exceed the queue size to prevent deadlock.
                        LOG(INFO) << __func__
                                  << ": Queue is full, but allowing self-post to prevent deadlock. "
                                     "Size: "
                                  << message_queue_.size();
                    }
                }
                break;
            }
            case QueueMode::kEvict: {
                if (is_full()) {
                    LOG(WARNING) << __func__
                                 << ": Queue is full, evicting the oldest message. Size: "
                                 << message_queue_.size();
                    message_queue_.pop();
                }
                break;
            }
        }
        message_queue_.push(std::move(message));
        consumer_cv_.notify_one();
        return true;
    }

    /**
     * @brief Stops the worker loop and discards messages in the message queue.
     */
    void Stop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (running_) {
            running_ = false;
            if (!message_queue_.empty()) {
                std::queue<Message>().swap(message_queue_);
            }
            consumer_cv_.notify_one();
            producer_cv_.notify_one();
        }
    }

    bool EnableRealTimePriority() {
        std::lock_guard<std::mutex> lock(mutex_);
        sched_param rt_params;
        rt_params.sched_priority = 1;  // The most relaxed Realtime priority.

        int result = SystemCallWrapper::GetWrapper().PthreadSetschedparam(
                worker_thread_.native_handle(), SCHED_FIFO, &rt_params);
        if (result) {
            LOG(ERROR) << __func__ << ": unable to set SCHED_FIFO: " << std::strerror(result);
        }
        return result == 0;
    }

    /**
     * @brief Gets the current number of messages in the queue.
     *
     * @return The number of messages currently in the queue.
     */
    size_t GetQueuedMessageSize() {
        std::lock_guard<std::mutex> lock(mutex_);
        return message_queue_.size();
    }

    std::thread::id GetThreadId() { return worker_thread_.get_id(); }

  private:
    void RunWorkerLoop() {
        while (running_) {
            std::unique_lock<std::mutex> lock(mutex_);
            consumer_cv_.wait(lock, [&] { return !message_queue_.empty() || !running_; });

            if (!message_queue_.empty() && running_) {
                Message task = std::move(message_queue_.front());
                message_queue_.pop();
                lock.unlock();
                handler_(std::move(task));
                producer_cv_.notify_one();
            }
        }
    };

    std::queue<Message> message_queue_;
    std::mutex mutex_;
    std::condition_variable producer_cv_;
    std::condition_variable consumer_cv_;
    std::thread worker_thread_;
    std::function<void(Message)> handler_;
    const size_t kMaxQueueSize;
    const QueueMode queue_mode_;
    bool running_;
};

}  // namespace bluetooth_hal::util
