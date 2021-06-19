//
// Created by Oliver on 27.05.21.
//

#include "SRPComponent.h"

namespace Acceleration::SRPComponent {
    namespace {
        inline constexpr double getFactor()
        {
            return Physics::P_SRP * Physics::AU * Physics::AU;
        }
    }
    std::array<double, 6> setUp(double t)
    {
        // calculation are the same as in the SolComponent setUp() function
        return Acceleration::SolComponent::setUp(t);
    }

    void apply(const Debris::Debris& d,
        double d_srp,
        const std::array<double, 6>& sun_params,
        std::array<double, 3>& acc_srp,
        std::array<double, 3>& acc_total)
    {
        acc_srp = d.getPosition();
        acc_srp[0] -= sun_params[0];
        acc_srp[1] -= sun_params[1];
        acc_srp[2] -= sun_params[2];
        // check if we have a precalculated value for d_srp and calculate it if needed
        if (d_srp == 0.0) {
            d_srp = std::inner_product(acc_srp.begin(), acc_srp.end(), acc_srp.begin(), .0);
            d_srp = 1 / std::sqrt(d_srp * d_srp * d_srp);
        }
        // Eq 50
        acc_srp[0] = d.getAom() * (getFactor()*d_srp*acc_srp[0]);
        acc_srp[1] = d.getAom() * (getFactor()*d_srp*acc_srp[1]);
        acc_srp[2] = d.getAom() * (getFactor()*d_srp*acc_srp[2]);
        acc_total[0] += acc_srp[0];
        acc_total[1] += acc_srp[1];
        acc_total[2] += acc_srp[2];
    }
} // namespace Acceleration