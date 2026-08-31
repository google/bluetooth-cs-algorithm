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

#include "bluetooth_hal/util/provider_factory.h"

namespace bluetooth_hal::util::power {

class PowerInterface {
  public:
    using VendorFactory = ::bluetooth_hal::util::ProviderFactory<PowerInterface, PowerInterface>;
    using FactoryFn = VendorFactory::FactoryFn;

    static bool RegisterPowerInterface(FactoryFn factory);

    virtual ~PowerInterface() = default;

    /**
     * @brief Acquire a partial system wakelock from hardware_legacy.
     *
     * @return true if the wakelock is acquired, otherwise false.
     *
     */
    virtual bool AcquireWakelock();

    /**
     * @brief Release the system wakelock acquired from hardware_legacy.
     *
     * @return true if the wakelock is acquired, otherwise false.
     *
     */
    virtual bool ReleaseWakelock();

    static PowerInterface& GetInterface();
};

}  // namespace bluetooth_hal::util::power
