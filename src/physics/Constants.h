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
    inline const double GM_EARTH = 3.986004407799724e+5;
    /**
     * @brief Gravitational constant * sun mass
     *
     * Used in:
     * - Acceleration::SolComponent
     */
    inline const double GM_SUN = 1.32712440018e+11;
    /**
     * @brief Gravitational constant * moon mass
     *
     * Used in:
     * - Acceleration::LunComponent
     */
    inline const double GM_MOON = 4.9028e+3;
    /**
     * @brief Radius of earth
     *
     * Used in:
     * - Acceleration::J2Component
     * - Acceleration::C22Component
     * - Acceleration::S22Component
     */
    inline const double R_EARTH = 6378.1363;
    /**
     * @brief Constant scalar factor
     *
     * Used in:
     * - Acceleration::J2Component
     */
    inline const double C_20 = -4.84165371736e-4;
    /**
     * @brief Constant scalar factor
     *
     * Used in:
     * - Acceleration::C22Component
     */
    inline const double C_22 = 2.43914352398e-6;
    /**
     * @brief Constant scalar factor
     *
     * Used in:
     * - Acceleration::S22Component
     */
    inline const double S_22 = -1.40016683654e-6;
    /**
     * @brief Constant angle
     *
     * Used in:
     * - Acceleration::C22Component
     * - Acceleration::S22Component
     */
    inline const double THETA_G = 280.4606;
    /**
     * @brief Angular velocity of earth
     *
     * Used in:
     * - Acceleration::C22Component
     * - Acceleration::S22Component
     */
    inline const double NU_EARTH = 4.178074622024230e-3;
    /**
     * @brief Angular velocity of sun
     *
     * Used in:
     * - Acceleration::SolComponent
     * - Acceleration::LunComponent
     */
    inline const double NU_SUN = 1.146046798147175e-5;
    /**
     * @brief Angular velocity of moon at point a
     *
     * Used in:
     * - Acceleration::LunComponent
     */
    inline const double NU_MOON_A = 1.519185226843672e-4;
    /**
     * @brief Angular velocity of moon at point p
     *
     * Used in:
     * - Acceleration::LunComponent
     */
    inline const double NU_MOON_P = 1.295389698040527e-6;
    /**
     * @brief Angular velocity of moon at point s
     *
     * Used in:
     * - Acceleration::LunComponent
     */
    inline const double NU_MOON_S = 6.157419543797653e-7;
    /**
     * @brief Astronomical unit
     *
     * Used in:
     * - Acceleration::SolComponent
     * - Acceleration::SRPComponent
     */
    inline const double AU = 1.49619e+8;
    /**
     * @brief Constant angle
     *
     * Used in:
     * - Acceleration::SolComponent
     * - Acceleration::LunComponent
     */
    inline const double EPSILON = 23.4392911;
    /**
     * @brief Constant angle
     *
     * Used in:
     * - Acceleration::SolComponent
     */
    inline const double PHI_SUN_0 = 357.5256;
    /**
     * @brief Pressure of the radiation of the sun
     *
     * Used in:
     * - Acceleration::SRPComponent
     */
    inline const double P_SRP = 4.56e-6;
}