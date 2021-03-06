//
// Created by Oliver on 27.05.21.
//

#include "J2Component.h"

namespace Acceleration::J2Component {
namespace {
    // Eq 6
    inline constexpr double getFactor_first()
    {
        return 0.5 * Physics::GM_EARTH * Physics::R_EARTH * Physics::R_EARTH * std::sqrt(5) * Physics::C_20;
    }
} // namespace
void apply(const Debris::Debris& d,
    std::array<double, 3>& acc_j2,
    std::array<double, 3>& acc_total)
{
    acc_j2 = d.getPosition();
    const double x2y2z2 = std::inner_product(acc_j2.cbegin(), acc_j2.cend(), acc_j2.cbegin(), 0.0);
    // Eq 7
    const double divisor_1 = getFactor_first() / std::sqrt(x2y2z2);
    const double divisor_2 = 1 / (x2y2z2 * x2y2z2);
    const double z2_15 = (15 * (acc_j2[2] * acc_j2[2])) * divisor_2 / x2y2z2;
    double factor_snd = 3 * divisor_2 - z2_15;
    // Eq 8
    acc_j2[0] *= divisor_1;
    acc_j2[1] *= divisor_1;
    acc_j2[2] *= divisor_1;
    acc_j2[0] *= factor_snd;
    acc_j2[1] *= factor_snd;
    factor_snd = 9 * divisor_2 - z2_15;
    acc_j2[2] *= factor_snd;
    acc_total[0] += acc_j2[0];
    acc_total[1] += acc_j2[1];
    acc_total[2] += acc_j2[2];
}
} // namespace Acceleration