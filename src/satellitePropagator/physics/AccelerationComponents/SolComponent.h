//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "satellitePropagator/debris/Debris.h"
#include "satellitePropagator/physics/Constants.h"

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
template <class D>
void apply(const D& d,
    double& d_ref,
    const std::array<double, 6>& sun_params,
    std::array<double, 3>& acc_sol,
    std::array<double, 3>& acc_total);
template <class D>
void apply(const D& d,
    double& d_ref,
    const std::array<double, 6>& sun_params,
    std::array<double, 3>& acc_sol,
    std::array<double, 3>& acc_total)
{
    acc_sol = d.getPosition();
    acc_sol[0] -= sun_params[0];
    acc_sol[1] -= sun_params[1];
    acc_sol[2] -= sun_params[2];
    // Eq 29
    d_ref = std::inner_product(acc_sol.begin(), acc_sol.end(), acc_sol.begin(), .0);
    d_ref = 1 / std::sqrt(d_ref * d_ref * d_ref);
    // Eq 30
    acc_sol[0] = -Physics::GM_SUN * (acc_sol[0] * d_ref + sun_params[3]);
    acc_sol[1] = -Physics::GM_SUN * (acc_sol[1] * d_ref + sun_params[4]);
    acc_sol[2] = -Physics::GM_SUN * (acc_sol[2] * d_ref + sun_params[5]);
    acc_total[0] += acc_sol[0];
    acc_total[1] += acc_sol[1];
    acc_total[2] += acc_sol[2];
}
} // namespace Acceleration