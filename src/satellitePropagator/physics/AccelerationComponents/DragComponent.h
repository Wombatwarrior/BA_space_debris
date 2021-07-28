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

    // calculate atmospheric density
    const double p = Physics::P_GROUND * std::exp(-(d.getHeight() - Physics::R_EARTH) / Physics::H_ATMOSPHERE);
    const double f = -0.5 * p * d.getBcInv();
    // calculate velocity relative to atmosphere
    auto acc_drag = d.getVelocity();
    acc_drag[0] += Physics::ROT_ATMOSPHERE * d.getPosition()[1];
    acc_drag[1] -= Physics::ROT_ATMOSPHERE * d.getPosition()[0];
    // actual drag
    acc_drag[0] = f * acc_drag[0] * acc_drag[0];
    acc_drag[1] = f * acc_drag[1] * acc_drag[1];
    acc_drag[2] = f * acc_drag[2] * acc_drag[2];
    return acc_drag;
}
} // namespace Acceleration