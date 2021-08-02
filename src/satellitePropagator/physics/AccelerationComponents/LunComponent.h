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
template <class D>
void apply(const D& d,
    const std::array<double, 6>& moon_params,
    std::array<double, 3>& acc_lun,
    std::array<double, 3>& acc_total);

template <class D>
void apply(const D& d,
    const std::array<double, 6>& moon_params,
    std::array<double, 3>& acc_lun,
    std::array<double, 3>& acc_total)
{
    acc_lun = d.getPosition();
    acc_lun[0] -= moon_params[0];
    acc_lun[1] -= moon_params[1];
    acc_lun[2] -= moon_params[2];
    // Eq 45
    double d1 = std::inner_product(acc_lun.begin(), acc_lun.end(), acc_lun.begin(), 0.);
    d1 = 1 / std::sqrt(d1 * d1 * d1);
    // Eq 46
    acc_lun[0] = -Physics::GM_MOON * (acc_lun[0] * d1 + moon_params[3]);
    acc_lun[1] = -Physics::GM_MOON * (acc_lun[1] * d1 + moon_params[4]);
    acc_lun[2] = -Physics::GM_MOON * (acc_lun[2] * d1 + moon_params[5]);
    acc_total[0] += acc_lun[0];
    acc_total[1] += acc_lun[1];
    acc_total[2] += acc_lun[2];
}
} // namespace Acceleration
