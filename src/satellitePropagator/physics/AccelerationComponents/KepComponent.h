//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "satellitePropagator/debris/Debris.h"
#include "satellitePropagator/physics/Constants.h"

namespace Acceleration::KepComponent {
/**
     * @brief Calculates acceleration due to earth gravity. Assuming the earth as a
     * point mass
     *
     * @param d Reference to the Debris::Debris object to apply the acceleration to
     * @param acc_kep Reference to an 3D vector to write the result for this
     * Acceleration::AccelerationComponent.
     * @param acc_total Reference to an 3D vector to accumulate the accelerations
     * for all applied Acceleration::AccelerationComponent.
     */
void apply(const Debris::Debris& d,
    std::array<double, 3>& acc_kep,
    std::array<double, 3>& acc_total);
} // namespace Acceleration