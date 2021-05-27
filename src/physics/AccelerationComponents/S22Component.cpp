//
// Created by ubuntu on 27.05.21.
//

#include "S22Component.h"

namespace Acceleration {
namespace S22Component {
namespace {
inline double getFS22_x(double x, double y, double z) {
  double x2 = x * x;
  double y2 = y * y;
  const double n = getFactor_fst() * x2 * y;
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
  return fst + snd;
}
inline double getFS22_y(double x, double y, double z) {
  double x2 = x * x;
  double y2 = y * y;
  const double n = getFactor_fst() * x * y2;
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
inline double getFS22_z(double x, double y, double z) {
  const double n = getFactor_fst() * x * y * z;
  // x2 = x^2 + y^2 +z^2
  double x2 = x * x + y * y + z * z;
  // y2 = (x^2 + y^2 +z^2)^2
  double y2 = x2 * x2;
  // x2 = (x^2 + y^2 +z^2)^3
  x2 = x2 * y2;
  // y2 = (x^2 + y^2 +z^2)^4
  y2 = y2 * y2;
  // y2 = (x^2 + y^2 +z^2)^(7/2)
  y2 = std::sqrt(y2 * x2);
  return n / y2;
}
inline constexpr double getFactor_fst() { return -5 * getFactor_snd(); }
inline constexpr double getFactor_snd() {
  return std::sqrt(15) * Physics::GM_EARTH * Physics::R_EARTH *
         Physics::R_EARTH * Physics::S_22;
}
} // namespace
void apply(Debris::Debris &d, double c_term, double s_term,
           std::array<double, 3> &acc_s22, std::array<double, 3> &acc_total) {
  acc_s22 = d.getPosition();
  const double x = acc_s22[0] * c_term + acc_s22[1] * s_term;
  const double y = -acc_s22[0] * s_term + acc_s22[1] * c_term;
  const double z = acc_s22[2];
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
  const double d2 = 1 / std::sqrt(pow_4 * pow_1);
  const double d1 = 1 / std::sqrt(pow_4 * pow_3);
  pow_1 = ((n * x) * d1) + ((getFactor_snd() * y) * d2);
  pow_3 = ((n * y) * d1) + ((getFactor_snd() * x) * d2);
  acc_s22[0] = pow_1 * c_term - pow_3 * s_term;
  acc_s22[1] = pow_1 * s_term + pow_3 * c_term;
  acc_s22[2] = ((n * z) * d1);
  acc_total[0] += acc_s22[0];
  acc_total[1] += acc_s22[1];
  acc_total[2] += acc_s22[2];
}
} // namespace S22Component
} // namespace Acceleration