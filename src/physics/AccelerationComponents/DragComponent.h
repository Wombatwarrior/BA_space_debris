//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "../../debris/Debris.h"
#include "../Constants.h"

namespace Acceleration::DragComponent {
    namespace {
    }
    /**
     * @brief Calculates acceleration due to the friction between the object and
     * the earths atmosphere
     *
     * @param d Reference to the Debris::Debris object to apply the acceleration to
     * @param acc_drag Reference to an 3D vector to write the result for this
     * Acceleration::AccelerationComponent.
     * @param acc_total Reference to an 3D vector to accumulate the accelerations
     * for all applied Acceleration::AccelerationComponent.
     */
    void apply(const Debris::Debris& d,
        std::array<double, 3>& acc_drag,
        std::array<double, 3>& acc_total);
} // namespace Acceleration