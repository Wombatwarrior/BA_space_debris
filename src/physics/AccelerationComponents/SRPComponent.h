//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "../../debris/Debris.h"
#include "../Constants.h"
#include "SolComponent.h"

namespace Acceleration {

/**
 * @namespace Acceleration::SRPComponent
 *
 * @brief Encapsulates functionality to calculate acceleration for
 * Acceleration::SRP
 *
 * <a href="Math.pdf#page=2"> math reference subsection 1.3</a> *
 */
namespace SRPComponent {
    namespace {
        /**
         * @brief Constant factor
         *
         * @return Physics::
         */
        inline constexpr double getFactor();
    }
    /**
     * @brief Precalculates values needed for Acceleration::SolComponent::apply()
     *
     * Calculates time dependent position of the sun and terms only depending on
     * those position values i.e. constant for the whole time step.
     *
     * @return 6D vector
     * [X_sun,Y_sun,Z_sun,X_sun/||POS_sunY||,Y_sun/||POS_sun||,Z_sun/||POS_sun||]
     */
    const std::array<double, 6> setUp(double t);

    /**
     * @brief Calculates acceleration due to pressure of the suns radiation
     *
     * @param d Reference to the Debris::Debris object to apply the acceleration to
     * @param d_srp 1/(sqrt((X-X_sun)^2+(Y-Y_sun)^2+(Z-Z_sun)^2)^3)
     * @param sun_params 6D array with precalculated values: [X_sun, Y_sun, Z_sun,
     * X_sun/||POS_sun||, Y_sun/||POS_sun||, Z_sun/||POS_sun||]
     * @param acc_srp Reference to an 3D vector to write the result for this
     * Acceleration::AccelerationComponent.
     * @param acc_total Reference to an 3D vector to accumulate the accelerations
     * for all applied Acceleration::AccelerationComponent.
     */
    void apply(Debris::Debris& d,
        double d_srp,
        std::array<double, 6>& sun_params,
        std::array<double, 3>& acc_srp,
        std::array<double, 3>& acc_total);
} // namespace SRPComponent
} // namespace Acceleration