//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "SolComponent.h"
#include "satellitePropagator/debris/Debris.h"
#include "satellitePropagator/physics/Constants.h"

namespace Acceleration::SRPComponent {
namespace {
    /**
         * @brief Constant factor
         *
         * @return Physics::
         */
    inline constexpr double getFactor()
    {
        return Physics::P_SRP * Physics::AU * Physics::AU;
    }
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
std::array<double, 6> setUp(double t);

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
template<class D>
void
apply(const D& d,
    double d_srp,
    const std::array<double, 6>& sun_params,
    std::array<double, 3>& acc_srp,
    std::array<double, 3>& acc_total);

    template<class D>
    void
    apply(const D& d,
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
        acc_srp[0] = d.getAom() * (getFactor() * d_srp * acc_srp[0]);
        acc_srp[1] = d.getAom() * (getFactor() * d_srp * acc_srp[1]);
        acc_srp[2] = d.getAom() * (getFactor() * d_srp * acc_srp[2]);
        acc_total[0] += acc_srp[0];
        acc_total[1] += acc_srp[1];
        acc_total[2] += acc_srp[2];
    }
} // namespace Acceleration