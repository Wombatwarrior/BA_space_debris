//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "satellitePropagator/debris/Debris.h"
#include "satellitePropagator/physics/Constants.h"

namespace Acceleration::C22S22Component {
namespace {
    /**
         * @brief  Calculates factor of the calculations consisting only on constants
         *
         * This term is part of all nominator terms for the C22 and S22 calculations
         *
         * @return std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH
         */
    inline constexpr double getFactor();

    /**
         * @brief Constant factor for the second C22 term
         *
         * @return
         * std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::C22
         */
    inline constexpr double getFactorC22_snd();

    /**
         * @brief Constant factor for the first C22 term
         *
         * @return
         * (5*std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::C22)/2
         */
    inline constexpr double getFactorC22_first();

    /**
         * @brief Constant factor for the second S22 term
         *
         * @return
         * std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::S22
         */
    inline constexpr double getFactorS22_snd();

    /**
         * @brief Constant factor for the first S22 term
         *
         * @return
         * -5*std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::S22
         */
    inline constexpr double getFactorS22_first();
} // namespace
/**
     * @brief Calculates acceleration due to earth gravity. Taking in account the
     * earth is neither a point mass nor not a homogenous spherical mass
     *
     * @param d Reference to the Debris::Debris object to apply the acceleration to
     * @param c_term Time dependent cos value
     * @param s_term Time dependent sin value
     * @param acc_c22s22 Reference to an 3D vector to write the result for this
     * Acceleration::AccelerationComponent.
     * @param acc_total Reference to an 3D vector to accumulate the accelerations
     * for all applied Acceleration::AccelerationComponent.
     */
template <class D>
void apply(const D& d,
    double c_term,
    double s_term,
    std::array<double, 3>& acc_c22s22,
    std::array<double, 3>& acc_total);

namespace {
    // EQ 12
    inline constexpr double getFactor()
    {
        return std::sqrt(15) * Physics::GM_EARTH * Physics::R_EARTH * Physics::R_EARTH;
    }
    // EQ 13
    inline constexpr double getFactorC22_snd()
    {
        return getFactor() * Physics::C_22;
    }
    // EQ 13
    inline constexpr double getFactorC22_first()
    {
        return getFactorC22_snd() * 2.5;
    }
    // EQ 14
    inline constexpr double getFactorS22_snd()
    {
        return getFactor() * Physics::S_22;
    }
    // EQ 14
    inline constexpr double getFactorS22_first()
    {
        return getFactorS22_snd() * -5;
    }
} // namespace
template <class D>
void apply(const D& d,
    double c_term,
    double s_term,
    std::array<double, 3>& acc_c22s22,
    std::array<double, 3>& acc_total)
{
    acc_c22s22 = d.getPosition();
    // EQ 16
    const double x = acc_c22s22[0] * c_term + acc_c22s22[1] * s_term;
    const double y = -acc_c22s22[0] * s_term + acc_c22s22[1] * c_term;
    const double z = acc_c22s22[2];
    // c22
    // EQ 17
    double n = getFactorC22_first() * (y * y - x * x);
    // pow_3 = (x^2 + y^2 + z^2)
    double pow_3 = x * x + y * y + z * z;
    // pow_1 = (x^2 + y^2 + z^2)
    const double pow_1 = pow_3;
    // pow_4 = (x^2 + y^2 +z^2)^2
    double pow_4 = pow_3 * pow_3;
    // pow_3 = (x^2 + y^2 +z^2)^3
    pow_3 = pow_3 * pow_4;
    // pow_4 = (x^2 + y^2 +z^2)^4
    pow_4 = pow_4 * pow_4;
    // EQ 18
    const double d2 = 1 / std::sqrt(pow_4 * pow_1);
    const double d1 = 1 / std::sqrt(pow_4 * pow_3);
    // EQ 19
    double f_x = ((n * x) * d1) + ((getFactorC22_snd() * x) * d2);
    double f_y = ((n * y) * d1) - ((getFactorC22_snd() * y) * d2);
    // EQ 20
    acc_c22s22[0] = f_x * c_term - f_y * s_term;
    acc_c22s22[1] = f_x * s_term + f_y * c_term;
    acc_c22s22[2] = ((n * z) * d1);
    // s22
    // EQ 17
    n = getFactorS22_first() * x * y;
    // EQ 19
    f_x = ((n * x) * d1) + ((getFactorS22_snd() * y) * d2);
    f_y = ((n * y) * d1) + ((getFactorS22_snd() * x) * d2);
    // EQ 20
    acc_c22s22[0] += f_x * c_term - f_y * s_term;
    acc_c22s22[1] += f_x * s_term + f_y * c_term;
    acc_c22s22[2] += ((n * z) * d1);
    acc_total[0] += acc_c22s22[0];
    acc_total[1] += acc_c22s22[1];
    acc_total[2] += acc_c22s22[2];
}
} // namespace Acceleration