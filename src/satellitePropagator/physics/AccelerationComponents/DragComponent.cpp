//
// Created by Oliver on 27.05.21.
//

#include "DragComponent.h"

namespace Acceleration::DragComponent {
namespace {
}
void apply(const Debris::Debris& d,
    std::array<double, 3>& acc_drag,
    std::array<double, 3>& acc_total)
{

    // calculate atmospheric density
    const double p = Physics::P_GROUND * std::exp(-(d.getHeight() - Physics::R_EARTH) / Physics::H_ATMOSPHERE);
    const double f = -0.5 * p * d.getBcInv();
    // calculate velocity relative to atmosphere
    acc_drag = d.getVelocity();
    acc_drag[0] += Physics::ROT_ATMOSPHERE * d.getPosition()[1];
    acc_drag[1] -= Physics::ROT_ATMOSPHERE * d.getPosition()[0];
    // actual drag
    acc_drag[0] = f * acc_drag[0] * acc_drag[0];
    acc_drag[1] = f * acc_drag[1] * acc_drag[1];
    acc_drag[2] = f * acc_drag[2] * acc_drag[2];
    acc_total[0] += acc_drag[0];
    acc_total[1] += acc_drag[1];
    acc_total[2] += acc_drag[2];
}
} // namespace Acceleration