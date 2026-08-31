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

#include <any>

#include "bluetooth_hal/util/provider_factory.h"

namespace aidl::android::hardware::bluetooth::ranging {
class Config;
class ProcedureEnableConfig;
}  // namespace aidl::android::hardware::bluetooth::ranging

namespace bluetooth_hal::extensions::cs {

class ChannelSoundingDistanceEstimator;

class ChannelSoundingDistanceEstimatorInterface
    : public ::bluetooth_hal::util::ProviderFactory<ChannelSoundingDistanceEstimatorInterface,
                                                    ChannelSoundingDistanceEstimator> {
  public:
    /**
     * @brief Registers a vendor-specific factory for creating
     * ChannelSoundingDistanceEstimatorInterface instances.
     *
     * @param factory The factory function to register.
     */
    static void RegisterVendorChannelSoundingDistanceEstimator(FactoryFn factory) {
        RegisterProviderFactory(std::move(factory));
    }

    /**
     * @brief Unregisters the vendor-specific factory.
     *
     */
    static void UnregisterVendorhannelSoundingDistanceEstimator() { UnregisterProviderFactory(); }

    virtual ~ChannelSoundingDistanceEstimatorInterface() = default;

    /**
     * @brief Resets the internal state of the estimator.
     */
    virtual void ResetVariables() = 0;

    /**
     * @brief Estimates the distance based on the provided raw data.
     *
     * This template function uses type erasure to provide a virtual dispatch
     * mechanism.
     *
     * @param data The data from the channel sounding procedure.
     * @return The estimated distance.
     */
    template <typename T>
    double EstimateDistance(const T& data) {
        return EstimateDistanceImpl(std::any(data));
    }

    /**
     * @brief Gets the confidence level of the last estimation.
     *
     * @return The confidence level.
     */
    virtual double GetConfidenceLevel() = 0;

    /**
     * @brief Gets the velocity of the last estimation.
     *
     * @return The velocity.
     */
    virtual double GetVelocity() = 0;

    /**
     * @brief Enable Inline PCT.
     *
     * @param is_enabled True to enable Inline PCT, false otherwise.
     */
    virtual void SetInlinePCT(bool is_enabled) = 0;

    /**
     * @brief Updates the CS configuration.
     *
     * @param config The CS configuration.
     */
    virtual void UpdateChannelSoundingConfig(
            const ::aidl::android::hardware::bluetooth::ranging::Config& config) = 0;

    /**
     * @brief Updates the procedure enable configuration.
     *
     * @param config The procedure enable configuration.
     */
    virtual void UpdateProcedureEnableConfig(
            const ::aidl::android::hardware::bluetooth::ranging::ProcedureEnableConfig& config) = 0;

  protected:
    virtual double EstimateDistanceImpl(const std::any& data) = 0;
};

}  // namespace bluetooth_hal::extensions::cs
