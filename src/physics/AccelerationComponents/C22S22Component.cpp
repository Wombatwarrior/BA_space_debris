//
// Created by Oliver on 27.05.21.
//

#include "C22S22Component.h"

namespace Acceleration {
namespace C22S22Component {
    namespace {
        // EQ 12
        inline constexpr double getFactor()
        {
            return std::sqrt(15) * Physics::GM_EARTH * Physics::R_EARTH * Physics::R_EARTH;
        }
        // EQ 13
        inline constexpr double getFactorC22_snd()
        {
            return getFactor() * Physics::C_22;
        }
        // EQ 13
        inline constexpr double getFactorC22_fst()
        {
            return getFactorC22_snd() * 2.5;
        }
        // EQ 14
        inline constexpr double getFactorS22_snd()
        {
            return getFactor() * Physics::S_22;
        }
        // EQ 14
        inline constexpr double getFactorS22_fst()
        {
            return getFactorS22_snd() * -5;
        }
    } // namespace
    void apply(Debris::Debris& d,
        double c_term,
        double s_term,
        std::array<double, 3>& acc_c22s22,
        std::array<double, 3>& acc_total)
    {
        acc_c22s22 = d.getPosition();
        // EQ 16
        const double x = acc_c22s22[0] * c_term + acc_c22s22[1] * s_term;
        const double y = -acc_c22s22[0] * s_term + acc_c22s22[1] * c_term;
        const double z = acc_c22s22[2];
        // c22
        // EQ 17
        double n = getFactorC22_fst() * (y * y - x * x);
        // pow_3 = (x^2 + y^2 + z^2)
        double pow_3 = x * x + y * y + z * z;
        // pow_1 = (x^2 + y^2 + z^2)
        const double pow_1 = pow_3;
        // pow_4 = (x^2 + y^2 +z^2)^2
        double pow_4 = pow_3 * pow_3;
        // pow_3 = (x^2 + y^2 +z^2)^3
        pow_3 = pow_3 * pow_4;
        // pow_4 = (x^2 + y^2 +z^2)^4
        pow_4 = pow_4 * pow_4;
        // EQ 18
        const double d2 = 1 / std::sqrt(pow_4 * pow_1);
        const double d1 = 1 / std::sqrt(pow_4 * pow_3);
        // EQ 19
        double f_x = ((n * x) * d1) + ((getFactorC22_snd() * x) * d2);
        double f_y = ((n * y) * d1) - ((getFactorC22_snd() * y) * d2);
        // EQ 20
        acc_c22s22[0] = f_x * c_term - f_y * s_term;
        acc_c22s22[1] = f_x * s_term + f_y * c_term;
        acc_c22s22[2] = ((n * z) * d1);
        // s22
        // EQ 17
        n = getFactorS22_fst() * x * y;
        // EQ 19
        f_x = ((n * x) * d1) + ((getFactorS22_snd() * y) * d2);
        f_y = ((n * y) * d1) + ((getFactorS22_snd() * x) * d2);
        // EQ 20
        acc_c22s22[0] += f_x * c_term - f_y * s_term;
        acc_c22s22[1] += f_x * s_term + f_y * c_term;
        acc_c22s22[2] += ((n * z) * d1);
        acc_total[0] += acc_c22s22[0];
        acc_total[1] += acc_c22s22[1];
        acc_total[2] += acc_c22s22[2];
    }
} // namespace C22S22Component
} // namespace Acceleration