//
// Created by Oliver on 13.05.21.
//

#pragma once

// Define global constants
namespace Physics {
    inline const double GM_EARTH = 3.986004407799724e+5;
    inline const double GM_SUN = 1.32712440018e+11;
    inline const double GM_MOON = 4.9028e+3;
    inline const double R_EARTH = 6378.1363;
    inline const double C_20 = -4.84165371736e-4;
    inline const double C_22 = 2.43914352398e-6;
    inline const double S_22 = -1.40016683654e-6;
    inline const double THETA_EARTH = 280.4606;
    inline const double NU_EARTH = 4.178074622024230e-3;
    inline const double NU_SUN = 1.146046798147175e-5;
    inline const double NU_MOON_A = 1.519185226843672e-4;
    inline const double NU_MOON_P = 1.295389698040527e-6;
    inline const double NU_MOON_S = 6.157419543797653e-7;
    inline const double AU = 1.49619e+8;
    inline const double EPSILON = 23.4392911;
    inline const double PHI_SUN_0 = 357.5256;
    inline const double P_SRP = 4.56e-6;
}