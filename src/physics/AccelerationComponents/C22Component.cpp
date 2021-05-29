//
// Created by Oliver on 27.05.21.
//

#include "C22Component.h"

namespace Acceleration {
namespace C22Component {
    namespace {
        inline double getFC22_x(double x, double y, double z)
        {
            double x2 = x * x;
            double y2 = y * y;
            const double n = getFactor_fst() * x * (y2 - x2);
            // x2 = (x^2 + y^2 + z^2)
            x2 = x2 + y2 + z * z;
            double fst = x2;
            // y2 = (x^2 + y^2 +z^2)^2
            y2 = x2 * x2;
            // x2 = (x^2 + y^2 +z^2)^3
            x2 = x2 * y2;
            // y2 = (x^2 + y^2 +z^2)^4
            y2 = y2 * y2;
            const double snd = (getFactor_snd() * x) / std::sqrt(y2 * fst);
            fst = n / std::sqrt(y2 * x2);
            return fst + snd;
        }
        inline double getFC22_y(double x, double y, double z)
        {
            double x2 = x * x;
            double y2 = y * y;
            const double n = getFactor_fst() * y * (y2 - x2);
            // x2 = (x^2 + y^2 + z^2)
            x2 = x2 + y2 + z * z;
            double fst = x2;
            // y2 = (x^2 + y^2 +z^2)^2
            y2 = x2 * x2;
            // x2 = (x^2 + y^2 +z^2)^3
            x2 = x2 * y2;
            // y2 = (x^2 + y^2 +z^2)^4
            y2 = y2 * y2;
            const double snd = (getFactor_snd() * y) / std::sqrt(y2 * fst);
            fst = n / std::sqrt(y2 * x2);
            return fst - snd;
        }
        inline double getFC22_z(double x, double y, double z)
        {
            double x2 = x * x;
            double y2 = y * y;
            const double n = getFactor_fst() * z * (y2 - x2);
            // x2 = x^2 + y^2 +z^2
            x2 = x2 + y2 + z * z;
            // y2 = (x^2 + y^2 +z^2)^2
            y2 = x2 * x2;
            // x2 = (x^2 + y^2 +z^2)^3
            x2 = x2 * y2;
            // y2 = (x^2 + y^2 +z^2)^4
            y2 = y2 * y2;
            // y2 = (x^2 + y^2 +z^2)^(7/2)
            y2 = std::sqrt(y2 * x2);
            return n / y2;
        }
        // Eq 13
        inline constexpr double getFactor_fst()
        {
            return 2.5 * getFactor_snd();
        }
        // Eq 13
        inline constexpr double getFactor_snd()
        {
            return std::sqrt(15) * Physics::GM_EARTH * Physics::R_EARTH * Physics::R_EARTH * Physics::C_22;
        }
    } // namespace
    void apply(Debris::Debris& d,
        double c_term,
        double s_term,
        std::array<double, 3>& acc_c22,
        std::array<double, 3>& acc_total)
    {
        acc_c22 = d.getPosition();
        // EQ 16
        const double x = acc_c22[0] * c_term + acc_c22[1] * s_term;
        const double y = -acc_c22[0] * s_term + acc_c22[1] * c_term;
        const double z = acc_c22[2];
        double x2 = x * x;
        double y2 = y * y;
        // EQ 17
        const double n = getFactor_fst() * (y2 - x2);
        // x2 = (x^2 + y^2 + z^2)
        x2 = x2 + y2 + z * z;
        // x2y2z2 = (x^2 + y^2 + z^2)
        const double x2y2z2 = x2;
        // y2 = (x^2 + y^2 +z^2)^2
        y2 = x2 * x2;
        // x2 = (x^2 + y^2 +z^2)^3
        x2 = x2 * y2;
        // y2 = (x^2 + y^2 +z^2)^4
        y2 = y2 * y2;
        // d1 = (x^2 + y^2 +z^2)^(7/2)
        // EQ 18
        const double d1 = 1 / std::sqrt(y2 * x2);
        // d2 = (x^2 + y^2 +z^2)^(5/2)
        // EQ 18
        const double d2 = 1 / std::sqrt(y2 * x2y2z2);
        // x2 = f_c22_x(x,y,z)
        x2 = (n * x) * d1 + (getFactor_snd() * x) * d2;
        // y2 = f_c22_y(x,y,z)
        y2 = (n * y) * d1 - (getFactor_snd() * y) * d2;
        // EQ 19
        acc_c22[0] = x2 * c_term - y2 * s_term;
        acc_c22[1] = x2 * s_term + y2 * c_term;
        acc_c22[2] = (n * z) * d1;
        acc_total[0] += acc_c22[0];
        acc_total[1] += acc_c22[1];
        acc_total[2] += acc_c22[2];
    }
} // namespace C22Component
} // namespace Acceleration