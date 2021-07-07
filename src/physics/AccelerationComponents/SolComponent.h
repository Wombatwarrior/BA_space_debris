//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "../../debris/Debris.h"
#include "../Constants.h"

namespace Acceleration::SolComponent {
/**
     * @brief Precalculates values needed for Acceleration::SolComponent::apply()
     *
     * Calculates time dependent position of the sun and terms only depending on
     * those position values i.e. constant for the whole time step.
     *
     * @return 6D vector
     * [X_sun,Y_sun,Z_sun,X_sun/||POS_sunY||,Y_sun/||POS_sun||,Z_sun/||POS_sun||]
     */
std::array<double, 6> setUp(double t);
/**
     * @brief Calculates acceleration due to tidal forces caused by the sun
     *
     * @param d Reference to the Debris::Debris object to apply the acceleration to
     * @param d_ref Acceleration::SRPComponent::apply() can use this value to avoid calculations per particle
     * @param sun_params 6D array with precalculated values: [X_sun, Y_sun, Z_sun,
     * X_sun/||POS_sun||, Y_sun/||POS_sun||, Z_sun/||POS_sun||]
     * @param acc_sol Reference to an 3D vector to write the result for this
     * Acceleration::AccelerationComponent.
     * @param acc_total Reference to an 3D vector to accumulate the accelerations
     * for all applied Acceleration::AccelerationComponent.
     */
void apply(const Debris::Debris& d,
    double& d_ref,
    const std::array<double, 6>& sun_params,
    std::array<double, 3>& acc_sol,
    std::array<double, 3>& acc_total);
} // namespace Acceleration