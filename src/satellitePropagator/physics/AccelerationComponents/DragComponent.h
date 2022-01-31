//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "satellitePropagator/debris/Debris.h"
#include "satellitePropagator/physics/Constants.h"

namespace Acceleration::DragComponent {
namespace {
}
/**
     * @brief Calculates acceleration due to the friction between the object and
     * the earths atmosphere
     *
     * @note Model source: https://farside.ph.utexas.edu/teaching/celestial/Celestial/node94.html
     *
     * @param d Reference to the Debris::Debris object to apply the acceleration to
     * @param acc_drag Reference to an 3D vector to write the result for this
     * Acceleration::AccelerationComponent.
     * @param acc_total Reference to an 3D vector to accumulate the accelerations
     * for all applied Acceleration::AccelerationComponent.
     */
template <class D>
auto apply(const D& d);

namespace {
}
template <class D>
auto apply(const D& d)
{
    // aliases
    const auto &vObj = d.getVelocity();
    const auto &pObj = d.getPosition();

    // Thesis Equation 2.31
    const std::array<double, 3> vRel{
        vObj[0] + Physics::ROT_ATMOSPHERE * pObj[1],
        vObj[1] - Physics::ROT_ATMOSPHERE * pObj[0],
        vObj[2],
    };

    const auto vNorm = MathUtils::euclideanNorm(vRel);
    // calculate atmospheric density. Equation 10.131 / Thesis Equation 2.33
    constexpr auto H_ATMOSPHERE_inv = 1. / Physics::H_ATMOSPHERE;
    const double p = Physics::P_GROUND * std::exp(-(d.getHeight() - Physics::R_EARTH) * H_ATMOSPHERE_inv);
    // Equation 10.130 / Thesis Equation 2.30
    const auto factor = -0.5 * p * d.getBcInv() * vNorm;
    return std::array<double, 3>{
        vRel[0] * factor,
        vRel[1] * factor,
        vRel[2] * factor,
    };
}
} // namespace Acceleration