//
// Created by ubuntu on 27.05.21.
//

#pragma once
#include "satellitePropagator/debris/Debris.h"
#include "satellitePropagator/physics/Constants.h"

namespace Acceleration::C22Component {
namespace {
    /**
         * @brief Constant factor for the first C22 term
         *
         * @return
         * (5*std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::C22)/2
         */
    inline constexpr double getFactor_first();

    /**
         * @brief Constant factor for the second C22 term
         *
         * @return
         * std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::C22
         */
    inline constexpr double getFactor_snd();
} // namespace
/**
     * @brief Calculates acceleration due to earth gravity. Taking in account the
     * earth is neither a point mass nor not a homogenous spherical mass
     *
     * @param d Reference to the Debris::Debris object to apply the acceleration to
     * @param c_term Time dependent cos value
     * @param s_term Time dependent sin value
     * @param acc_c22 Reference to an 3D vector to write the result for this
     * Acceleration::AccelerationComponent.
     * @param acc_total Reference to an 3D vector to accumulate the accelerations
     * for all applied Acceleration::AccelerationComponent.
     */
void apply(const Debris::Debris& d,
    double c_term,
    double s_term,
    std::array<double, 3>& acc_c22,
    std::array<double, 3>& acc_total);
} // namespace Acceleration