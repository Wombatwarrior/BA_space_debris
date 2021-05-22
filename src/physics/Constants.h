//
// Created by Oliver on 13.05.21.
//

#pragma once

// Define global constants
/**
 * @namespace Physics
 *
 * @brief Encapsulates global constants for calculations used in Acceleration namespace
 */
namespace Physics {
    /**
     * @brief Gravitational constant * earth mass
     *
     * Used in:
     * - Acceleration::KepComponent
     * - Acceleration::J2Component
     * - Acceleration::C22Component
     * - Acceleration::S22Component
     */
    inline constexpr double GM_EARTH = 3.986004407799724e+5;
    /**
     * @brief Gravitational constant * sun mass
     *
     * Used in:
     * - Acceleration::SolComponent
     */
    inline constexpr double GM_SUN = 1.32712440018e+11;
    /**
     * @brief Gravitational constant * moon mass
     *
     * Used in:
     * - Acceleration::LunComponent
     */
    inline constexpr double GM_MOON = 4.9028e+3;
    /**
     * @brief Radius of earth
     *
     * Used in:
     * - Acceleration::J2Component
     * - Acceleration::C22Component
     * - Acceleration::S22Component
     */
    inline constexpr double R_EARTH = 6378.1363;
    /**
     * @brief Constant scalar factor
     *
     * Used in:
     * - Acceleration::J2Component
     */
    inline constexpr double C_20 = -4.84165371736e-4;
    /**
     * @brief Constant scalar factor
     *
     * Used in:
     * - Acceleration::C22Component
     */
    inline constexpr double C_22 = 2.43914352398e-6;
    /**
     * @brief Constant scalar factor
     *
     * Used in:
     * - Acceleration::S22Component
     */
    inline constexpr double S_22 = -1.40016683654e-6;
    /**
     * @brief Constant angle
     *
     * Used in:
     * - Acceleration::C22Component
     * - Acceleration::S22Component
     */
    inline constexpr double THETA_G = 280.4606;
    /**
     * @brief Angular velocity of earth
     *
     * Used in:
     * - Acceleration::C22Component
     * - Acceleration::S22Component
     */
    inline constexpr double NU_EARTH = 4.178074622024230e-3;
    /**
     * @brief Angular velocity of sun
     *
     * Used in:
     * - Acceleration::SolComponent
     * - Acceleration::LunComponent
     */
    inline constexpr double NU_SUN = 1.1407410259335311e-5;
    /**
     * @brief Angular velocity of moon at point a
     *
     * Used in:
     * - Acceleration::LunComponent
     */
    inline constexpr double NU_MOON_A = 1.519185226843672e-4;
    /**
     * @brief Angular velocity of moon at point p
     *
     * Used in:
     * - Acceleration::LunComponent
     */
    inline constexpr double NU_MOON_P = 1.295389698040527e-6;
    /**
     * @brief Angular velocity of moon at point s
     *
     * Used in:
     * - Acceleration::LunComponent
     */
    inline constexpr double NU_MOON_S = 6.157419543797653e-7;
    /**
     * @brief Astronomical unit
     *
     * Used in:
     * - Acceleration::SolComponent
     * - Acceleration::SRPComponent
     */
    inline constexpr double AU = 1.49619e+8;
    /**
     * @brief Constant angle
     *
     * Used in:
     * - Acceleration::SolComponent
     * - Acceleration::LunComponent
     */
    inline constexpr double EPSILON = 23.4392911;
    /**
     * @brief Constant angle
     *
     * Used in:
     * - Acceleration::SolComponent
     */
    inline constexpr double PHI_SUN_0 = 357.5256;
    /**
     * @brief Pressure of the radiation of the sun
     *
     * Used in:
     * - Acceleration::SRPComponent
     */
    inline constexpr double P_SRP = 4.56e-6;
    /**
     * @brief Longitude of the ascending node
     *
     * Used in:
     * - Acceleration::SolComponent
     */
    inline constexpr double LONG_ASC = -11.26064;
    /**
     * @brief Omega_2 of sun
     *
     * Used in:
     * - Acceleration::SolComponent
     */
    //TODO concrete value
    inline constexpr double ARG_PERIAPSIS = 102.94719;
}