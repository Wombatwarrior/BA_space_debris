//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "../../debris/Debris.h"
#include "../Constants.h"

namespace Acceleration {

/**
 * @namespace Acceleration::SRPComponent
 *
 * @brief Encapsulates functionality to calculate acceleration for
 * Acceleration::SRP
 */
namespace SRPComponent {
    namespace {
    }
    /**
     * @brief Calculates acceleration due to pressure of the suns radiation
     *
     * @param d Reference to the Debris::Debris object to apply the acceleration to
     * @param acc_srp Reference to an 3D vector to write the result for this
     * Acceleration::AccelerationComponent.
     * @param acc_total Reference to an 3D vector to accumulate the accelerations
     * for all applied Acceleration::AccelerationComponent.
     */
    void apply(Debris::Debris& d,
        std::array<double, 3>& acc_srp,
        std::array<double, 3>& acc_total);
} // namespace SRPComponent
} // namespace Acceleration