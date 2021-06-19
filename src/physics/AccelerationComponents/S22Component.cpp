//
// Created by ubuntu on 27.05.21.
//

#include "S22Component.h"

namespace Acceleration::S22Component {
    namespace {
        // Eq 14
        inline constexpr double getFactor_fst()
        {
            return -5 * getFactor_snd();
        }
        // Eq 14
        inline constexpr double getFactor_snd()
        {
            return std::sqrt(15) * Physics::GM_EARTH * Physics::R_EARTH * Physics::R_EARTH * Physics::S_22;
        }
    } // namespace
    void apply(const Debris::Debris& d,
        double c_term,
        double s_term,
        std::array<double, 3>& acc_s22,
        std::array<double, 3>& acc_total)
    {
        acc_s22 = d.getPosition();
        // Eq 16
        const double x = acc_s22[0] * c_term + acc_s22[1] * s_term;
        const double y = -acc_s22[0] * s_term + acc_s22[1] * c_term;
        const double z = acc_s22[2];
        // Eq 17
        const double n = getFactor_fst() * x * y;
        // pow_3 = (x^2 + y^2 + z^2)
        double pow_3 = x * x + y * y + z * z;
        // pow_1 = (x^2 + y^2 + z^2)
        double pow_1 = pow_3;
        // pow_4 = (x^2 + y^2 +z^2)^2
        double pow_4 = pow_3 * pow_3;
        // pow_3 = (x^2 + y^2 +z^2)^3
        pow_3 = pow_3 * pow_4;
        // pow_4 = (x^2 + y^2 +z^2)^4
        pow_4 = pow_4 * pow_4;
        // Eq 18
        const double d2 = 1 / std::sqrt(pow_4 * pow_1);
        const double d1 = 1 / std::sqrt(pow_4 * pow_3);
        // Eq 19
        pow_1 = ((n * x) * d1) + ((getFactor_snd() * y) * d2);
        pow_3 = ((n * y) * d1) + ((getFactor_snd() * x) * d2);
        // Eq 20
        acc_s22[0] = pow_1 * c_term - pow_3 * s_term;
        acc_s22[1] = pow_1 * s_term + pow_3 * c_term;
        acc_s22[2] = ((n * z) * d1);
        acc_total[0] += acc_s22[0];
        acc_total[1] += acc_s22[1];
        acc_total[2] += acc_s22[2];
    }
} // namespace Acceleration