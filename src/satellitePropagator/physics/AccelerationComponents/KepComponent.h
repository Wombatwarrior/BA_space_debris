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
template <class D>
auto apply(const D& d);

template <class D>
auto apply(const D& d)
{
    auto acc_kep = d.getPosition();
    // Eq 3
    double divisor = std::inner_product(acc_kep.cbegin(), acc_kep.cend(), acc_kep.cbegin(), 0.0);
    divisor = divisor * divisor * divisor;
    divisor = 1 / std::sqrt(divisor);
    // Eq 4
    acc_kep[0] *= Physics::GM_EARTH;
    acc_kep[1] *= Physics::GM_EARTH;
    acc_kep[2] *= Physics::GM_EARTH;
    acc_kep[0] *= -divisor;
    acc_kep[1] *= -divisor;
    acc_kep[2] *= -divisor;
    return acc_kep;
}
} // namespace Acceleration