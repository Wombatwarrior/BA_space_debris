//
// Created by Oliver on 27.05.21.
//

#include "SolComponent.h"

namespace Acceleration {
namespace SolComponent {
    const std::array<double, 6> setUp(double t)
    {
        const double l = Physics::PHI_SUN_0 + Physics::NU_SUN * t;
        const double r = Physics::AU_SCALED - 2.499 * std::cos(l * M_PIf64 / 180) - 0.021 * std::cos(2 * l * M_PIf64 / 180);
        const double lambda = Physics::LONG_ASC + Physics::ARG_PERIAPSIS + l + (6892.0 / 3600) * std::sin(l * M_PIf64 / 180) + (72.0 / 3600) * std::sin((2 * l) * M_PIf64 / 180);
        // contains the x,y,z position of the sun and 3 needed terms only depending
        // on those coordinates
        std::array<double, 6> sun_params = {
            std::cos(lambda * M_PIf64 / 180),
            std::sin(lambda * M_PIf64 / 180) * std::cos(Physics::EPSILON * M_PIf64 / 180),
            std::sin(lambda * M_PIf64 / 180) * std::sin(Physics::EPSILON * M_PIf64 / 180),
            0,
            0,
            0
        };
        sun_params[0] = (r * sun_params[0]) * 1e+6;
        sun_params[1] = (r * sun_params[1]) * 1e+6;
        sun_params[2] = (r * sun_params[2]) * 1e+6;
        double d2 = std::inner_product(sun_params.begin(), sun_params.end(),
            sun_params.begin(), .0);
        d2 = 1 / std::sqrt(d2 * d2 * d2);
        sun_params[3] = sun_params[0] * d2;
        sun_params[4] = sun_params[1] * d2;
        sun_params[5] = sun_params[2] * d2;
        return sun_params;
    }

    void apply(Debris::Debris& d,
        const std::array<double, 6>& sun_params,
        std::array<double, 3>& acc_sol,
        std::array<double, 3>& acc_total)
    {
        acc_sol = d.getPosition();
        acc_sol[0] -= sun_params[0];
        acc_sol[1] -= sun_params[1];
        acc_sol[2] -= sun_params[2];
        double d1 = std::inner_product(acc_sol.begin(), acc_sol.end(), acc_sol.begin(), .0);
        d1 = 1 / std::sqrt(d1 * d1 * d1);
        acc_sol[0] = -Physics::GM_SUN * (acc_sol[0] * d1 + sun_params[3]);
        acc_sol[1] = -Physics::GM_SUN * (acc_sol[1] * d1 + sun_params[4]);
        acc_sol[2] = -Physics::GM_SUN * (acc_sol[2] * d1 + sun_params[5]);
        acc_total[0] += acc_sol[0];
        acc_total[1] += acc_sol[1];
        acc_total[2] += acc_sol[2];
    }
} // namespace SolComponent
} // namespace Acceleration