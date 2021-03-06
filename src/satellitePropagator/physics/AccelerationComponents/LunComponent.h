//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "satellitePropagator/debris/Debris.h"
#include "satellitePropagator/physics/Constants.h"

namespace Acceleration::LunComponent {
/**
     * @brief Precalculates values needed for Acceleration::LunComponent::apply()
     *
     * Calculates time dependent position of the moon and terms only depending on
     * those position values i.e. constant for the whole time step.
     *
     * @return 6D vector
     * [X_moon,Y_moon,Z_moon,X_moon/||POS_moon||,Y_moon/||POS_moon||,Z_moon/||POS_moon||]
     */
std::array<double, 6> setUp(double t);
/**
     * @brief Calculates acceleration due to tidal forces caused by the moon
     *
     * @param d Reference to the Debris::Debris object to apply the acceleration to
     * @param moon_params 6D array with precalculated values:
     * [X_moon,Y_moon,Z_moon,X_moon/||POS_moon||,Y_moon/||POS_moon||,Z_moon/||POS_moon||]
     * @param acc_lun Reference to an 3D vector to write the result for this
     * Acceleration::AccelerationComponent.
     * @param acc_total Reference to an 3D vector to accumulate the accelerations
     * for all applied Acceleration::AccelerationComponent.
     */
void apply(const Debris::Debris& d,
    const std::array<double, 6>& moon_params,
    std::array<double, 3>& acc_lun,
    std::array<double, 3>& acc_total);
} // namespace Acceleration
