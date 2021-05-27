//
// Created by Oliver on 27.05.21.
//

#pragma once
#include "../../debris/Debris.h"
#include "../Constants.h"

namespace Acceleration {

/**
 * @namespace Acceleration::J2Component
 *
 * @brief Encapsulates functionality to calculate acceleration for
 * Acceleration::J2
 */
namespace J2Component {
namespace {

/**
 * @brief Constant factor for the first J2 term
 *
 * @return
 * (std::sqrt(5)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::C20)/2
 */
inline const double getFactor_fst();
} // namespace
  /**
   * @brief Calculates acceleration due to earth gravity. Taking in account the
   * earth is neither a point mass nor  a homogenous spherical mass
   *
   * @param d Reference to the Debris::Debris object to apply the acceleration to
   * @param acc_j2 Reference to an 3D vector to write the result for this
   * Acceleration::AccelerationComponent.
   * @param acc_total Reference to an 3D vector to accumulate the accelerations
   * for all applied Acceleration::AccelerationComponent.
   */
void apply(Debris::Debris &d, std::array<double, 3> &acc_j2,
           std::array<double, 3> &acc_total);
} // namespace J2Component
} // namespace Acceleration