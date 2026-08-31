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

#include <functional>
#include <memory>
#include <string>

#include "android-base/logging.h"
#include "android/binder_manager.h"
#include "android/binder_status.h"

namespace bluetooth_hal::extensions {

// An initializer function for a HAL extension.
using BluetoothHalExtensionInitializer = std::function<void()>;

/**
 * Each extension should call this function, typically from a static
 * constructor, to register its initialization logic with the core HAL.
 *
 * @param init_func the extension's initializer function.
 */
void BluetoothHalRegisterExtension(BluetoothHalExtensionInitializer init_func);

/**
 * Registers a HAL service with the Android Service Manager.
 *
 * @tparam T The type of the service, which must have a `descriptor` field.
 * @param service The service instance to register.
 */
template <typename T>
void RegisterHalService(const std::shared_ptr<T>& service) {
    std::string instance = std::string() + T::descriptor + "/default";
    int status = AServiceManager_addService(service->asBinder().get(), instance.c_str());
    if (status != STATUS_OK) {
        LOG(ERROR) << "Could not register " << T::descriptor << " as a service!";
    }
}

}  // namespace bluetooth_hal::extensions
