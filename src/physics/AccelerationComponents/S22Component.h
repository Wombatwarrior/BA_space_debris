//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "../../debris/Debris.h"
#include "../Constants.h"

namespace Acceleration {

/**
 * @namespace Acceleration::S22Component
 *
 * @brief Encapsulates functionality to calculate acceleration for
 * Acceleration::S22
 */
namespace S22Component {
    namespace {
        /**
         * @brief Calculate terms for the x component of S22
         * @deprecated
         * @param x
         * @param y
         * @param z
         * @return
         */
        inline double getFS22_x(double x, double y, double z);
        /**
         * @brief Calculate terms for the y component of S22
         * @deprecated
         * @param x
         * @param y
         * @param z
         * @return
         */
        inline double getFS22_y(double x, double y, double z);
        /**
         * @brief Calculate terms for the z component of S22
         * @deprecated
         * @param x
         * @param y
         * @param z
         * @return
         */
        inline double getFS22_z(double x, double y, double z);

        /**
         * @brief Constant factor for the first S22 term
         *
         * @return
         * -5*std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::S22
         */
        inline constexpr double getFactor_fst();

        /**
         * @brief Constant factor for the second S22 term
         *
         * @return
         * std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::S22
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
     * @param acc_s22 Reference to an 3D vector to write the result for this
     * Acceleration::AccelerationComponent.
     * @param acc_total Reference to an 3D vector to accumulate the accelerations
     * for all applied Acceleration::AccelerationComponent.
     */
    void apply(Debris::Debris& d,
        double c_term,
        double s_term,
        std::array<double, 3>& acc_s22,
        std::array<double, 3>& acc_total);
} // namespace S22Component
} // namespace Acceleration
