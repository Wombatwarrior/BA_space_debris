//
// Created by Oliver on 27.05.21.
//

#include "SolComponent.h"

namespace Acceleration::SolComponent {
    std::array<double, 6> setUp(double t)
    {
        // Eq 24
        const double l = Physics::PHI_SUN_0 + Physics::NU_SUN * t;
        const double r = Physics::AU_SCALED - 2.499 * std::cos(l * Physics::RAD_FACTOR) - 0.021 * std::cos(2 * l * Physics::RAD_FACTOR);
        const double lambda = Physics::OMEGA + l + (6892.0 / 3600) * std::sin(l * Physics::RAD_FACTOR) + (72.0 / 3600) * std::sin((2 * l) * Physics::RAD_FACTOR);
        // contains the x,y,z position of the sun and 3 needed terms only depending
        // on those coordinates
        // Eq 25
        std::array<double, 6> sun_params = {
            std::cos(lambda * Physics::RAD_FACTOR),
            std::sin(lambda * Physics::RAD_FACTOR) * std::cos(Physics::EPSILON * Physics::RAD_FACTOR),
            std::sin(lambda * Physics::RAD_FACTOR) * std::sin(Physics::EPSILON * Physics::RAD_FACTOR),
            0,
            0,
            0
        };
        // Eq 26
        sun_params[0] = (r * sun_params[0]) * 1e+6;
        sun_params[1] = (r * sun_params[1]) * 1e+6;
        sun_params[2] = (r * sun_params[2]) * 1e+6;
        // Eq 27
        double d = std::inner_product(sun_params.begin(), sun_params.end(),
            sun_params.begin(), .0);
        d = 1 / std::sqrt(d * d * d);
        // Eq 28
        sun_params[3] = sun_params[0] * d;
        sun_params[4] = sun_params[1] * d;
        sun_params[5] = sun_params[2] * d;
        return sun_params;
    }

    void apply(const Debris::Debris& d,
        double& d_ref,
        const std::array<double, 6>& sun_params,
        std::array<double, 3>& acc_sol,
        std::array<double, 3>& acc_total)
    {
        acc_sol = d.getPosition();
        acc_sol[0] -= sun_params[0];
        acc_sol[1] -= sun_params[1];
        acc_sol[2] -= sun_params[2];
        // Eq 29
        d_ref = std::inner_product(acc_sol.begin(), acc_sol.end(), acc_sol.begin(), .0);
        d_ref = 1 / std::sqrt(d_ref * d_ref * d_ref);
        // Eq 30
        acc_sol[0] = -Physics::GM_SUN * (acc_sol[0] * d_ref + sun_params[3]);
        acc_sol[1] = -Physics::GM_SUN * (acc_sol[1] * d_ref + sun_params[4]);
        acc_sol[2] = -Physics::GM_SUN * (acc_sol[2] * d_ref + sun_params[5]);
        acc_total[0] += acc_sol[0];
        acc_total[1] += acc_sol[1];
        acc_total[2] += acc_sol[2];
    }
} // namespace Acceleration