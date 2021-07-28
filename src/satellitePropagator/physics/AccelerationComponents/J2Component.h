//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "satellitePropagator/debris/Debris.h"
#include "satellitePropagator/physics/Constants.h"

namespace Acceleration::J2Component {
namespace {
    /**
         * @brief Constant factor for the first J2 term
         *
         * @return
         * (std::sqrt(5)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::C20)/2
         */
    inline constexpr double getFactor_first();
} // namespace
/**
     * @brief Calculates acceleration due to earth gravity. Taking in account the
     * earth is neither a point mass nor  a homogenous spherical mass
     *
     * @param d Reference to the Debris::Debris object to apply the acceleration to
     * @param acc_j2 Reference to an 3D vector to write the result for this
     * Acceleration::AccelerationComponent.
     * @param acc_total Reference to an 3D vector to accumulate the accelerations
     * for all applied Acceleration::AccelerationComponent.
     */
template <class D>
auto apply(const D& d);

namespace {
    // Eq 6
    inline constexpr double getFactor_first()
    {
        return 0.5 * Physics::GM_EARTH * Physics::R_EARTH * Physics::R_EARTH * std::sqrt(5) * Physics::C_20;
    }
} // namespace
template <class D>
auto apply(const D& d)
{
    auto acc_j2 = d.getPosition();
    const double x2y2z2 = std::inner_product(acc_j2.cbegin(), acc_j2.cend(), acc_j2.cbegin(), 0.0);
    // Eq 7
    const double divisor_1 = getFactor_first() / std::sqrt(x2y2z2);
    const double divisor_2 = 1 / (x2y2z2 * x2y2z2);
    const double z2_15 = (15 * (acc_j2[2] * acc_j2[2])) * divisor_2 / x2y2z2;
    double factor_snd = 3 * divisor_2 - z2_15;
    // Eq 8
    acc_j2[0] *= divisor_1;
    acc_j2[1] *= divisor_1;
    acc_j2[2] *= divisor_1;
    acc_j2[0] *= factor_snd;
    acc_j2[1] *= factor_snd;
    factor_snd = 9 * divisor_2 - z2_15;
    acc_j2[2] *= factor_snd;
    return acc_j2;
}

} // namespace Acceleration