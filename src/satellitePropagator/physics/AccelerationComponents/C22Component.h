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
    template<class D>
void apply(const D& d,
    double c_term,
    double s_term,
    std::array<double, 3>& acc_c22,
    std::array<double, 3>& acc_total);

    namespace {
        // Eq 13
        inline constexpr double getFactor_first()
        {
            return 2.5 * getFactor_snd();
        }
        // Eq 13
        inline constexpr double getFactor_snd()
        {
            return std::sqrt(15) * Physics::GM_EARTH * Physics::R_EARTH * Physics::R_EARTH * Physics::C_22;
        }
    } // namespace
    template<class D>
    void apply(const D& d,
               double c_term,
               double s_term,
               std::array<double, 3>& acc_c22,
               std::array<double, 3>& acc_total)
    {
        acc_c22 = d.getPosition();
        // EQ 16
        const double x = acc_c22[0] * c_term + acc_c22[1] * s_term;
        const double y = -acc_c22[0] * s_term + acc_c22[1] * c_term;
        const double z = acc_c22[2];
        double x2 = x * x;
        double y2 = y * y;
        // EQ 17
        const double n = getFactor_first() * (y2 - x2);
        // x2 = (x^2 + y^2 + z^2)
        x2 = x2 + y2 + z * z;
        // x2y2z2 = (x^2 + y^2 + z^2)
        const double x2y2z2 = x2;
        // y2 = (x^2 + y^2 +z^2)^2
        y2 = x2 * x2;
        // x2 = (x^2 + y^2 +z^2)^3
        x2 = x2 * y2;
        // y2 = (x^2 + y^2 +z^2)^4
        y2 = y2 * y2;
        // d1 = (x^2 + y^2 +z^2)^(7/2)
        // EQ 18
        const double d1 = 1 / std::sqrt(y2 * x2);
        // d2 = (x^2 + y^2 +z^2)^(5/2)
        // EQ 18
        const double d2 = 1 / std::sqrt(y2 * x2y2z2);
        // x2 = f_c22_x(x,y,z)
        x2 = (n * x) * d1 + (getFactor_snd() * x) * d2;
        // y2 = f_c22_y(x,y,z)
        y2 = (n * y) * d1 - (getFactor_snd() * y) * d2;
        // EQ 19
        acc_c22[0] = x2 * c_term - y2 * s_term;
        acc_c22[1] = x2 * s_term + y2 * c_term;
        acc_c22[2] = (n * z) * d1;
        acc_total[0] += acc_c22[0];
        acc_total[1] += acc_c22[1];
        acc_total[2] += acc_c22[2];
    }
} // namespace Acceleration