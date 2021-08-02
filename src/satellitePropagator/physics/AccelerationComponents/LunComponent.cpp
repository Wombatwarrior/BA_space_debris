//
// Created by Oliver on 27.05.21.
//

#include "LunComponent.h"

namespace Acceleration::LunComponent {
std::array<double, 6> setUp(double t)
{
    // Eq 37
    const double phi_m = Physics::NU_SUN * t;
    const double phi_m_a = Physics::NU_MOON_A * t;
    const double phi_m_p = Physics::NU_MOON_P * t;
    const double phi_m_s = Physics::NU_MOON_S * t;
    const double l_0 = phi_m_p + phi_m_a + 218.31617;
    const double l_m = phi_m_a + 134.96292;
    const double l1_m = phi_m + 357.52543;
    const double f_m = phi_m_p + phi_m_a + phi_m_s + 93.27283;
    const double d_m = phi_m_p + phi_m_a - phi_m + 297.85027;

    // add up small terms first, to avoid floating point errors when adding small
    // to big values
    // Eq 38
    double r_m = -152 * std::cos((l_m + l1_m - 2 * d_m) * Physics::RAD_FACTOR);
    r_m -= 171 * std::cos((l_m + 2 * d_m) * Physics::RAD_FACTOR);
    r_m -= 205 * std::cos((l1_m - 2 * d_m) * Physics::RAD_FACTOR);
    r_m += 246 * std::cos((2 * l_m - 2 * d_m) * Physics::RAD_FACTOR);
    r_m -= 570 * std::cos((2 * l_m) * Physics::RAD_FACTOR);
    r_m -= 2956 * std::cos((2 * d_m) * Physics::RAD_FACTOR);
    r_m -= 3699 * std::cos((2 * d_m - l_m) * Physics::RAD_FACTOR);
    r_m -= 20905 * std::cos(l_m * Physics::RAD_FACTOR);
    r_m += 385000;

    // add up small terms first, to avoid floating point errors when adding small
    // to big values
    // Eq 39
    double lambda_m = -(55.0 / 3600) * std::sin((2 * f_m - 2 * d_m) * Physics::RAD_FACTOR);
    lambda_m -= (110.0 / 3600) * std::sin((l_m + l1_m) * Physics::RAD_FACTOR);
    lambda_m -= (125.0 / 3600) * std::sin((d_m)*Physics::RAD_FACTOR);
    lambda_m += (148.0 / 3600) * std::sin((l_m - l1_m) * Physics::RAD_FACTOR);
    lambda_m -= (165.0 / 3600) * std::sin((l1_m - 2 * d_m) * Physics::RAD_FACTOR);
    lambda_m += (192.0 / 3600) * std::sin((l_m + 2 * d_m) * Physics::RAD_FACTOR);
    lambda_m -= (206.0 / 3600) * std::sin((l_m + l1_m - 2 * d_m) * Physics::RAD_FACTOR);
    lambda_m -= (212.0 / 3600) * std::sin((2 * l_m - 2 * d_m) * Physics::RAD_FACTOR);
    lambda_m -= (412.0 / 3600) * std::sin((2 * f_m) * Physics::RAD_FACTOR);
    lambda_m -= (668.0 / 3600) * std::sin((l1_m)*Physics::RAD_FACTOR);
    lambda_m += (769.0 / 3600) * std::sin((2 * l_m) * Physics::RAD_FACTOR);
    lambda_m += (2370.0 / 3600) * std::sin((2 * d_m) * Physics::RAD_FACTOR);
    lambda_m -= (4856.0 / 3600) * std::sin((l_m - 2 * d_m) * Physics::RAD_FACTOR);
    lambda_m += (22640.0 / 3600) * std::sin((l_m)*Physics::RAD_FACTOR);
    lambda_m += l_0;

    // add up small terms first, to avoid floating point errors when adding small
    // to big values
    // Eq 40
    double beta_m = (11.0 / 3600) * std::sin((-l1_m + f_m - 2 * d_m) * Physics::RAD_FACTOR);
    beta_m += (21.0 / 3600) * std::sin((-l_m + f_m) * Physics::RAD_FACTOR);
    beta_m -= (23.0 / 3600) * std::sin((l1_m + f_m - 2 * d_m) * Physics::RAD_FACTOR);
    beta_m -= (25.0 / 3600) * std::sin((-2 * l_m + f_m) * Physics::RAD_FACTOR);
    beta_m -= (31.0 / 3600) * std::sin((-l_m + f_m - 2 * d_m) * Physics::RAD_FACTOR);
    beta_m += (44.0 / 3600) * std::sin((l_m + f_m - 2 * d_m) * Physics::RAD_FACTOR);
    beta_m -= (526.0 / 3600) * std::sin((f_m - 2 * d_m) * Physics::RAD_FACTOR);
    beta_m += (18520.0 / 3600) * std::sin((f_m + lambda_m - l_0 + (412.0 / 3600) * std::sin((2 * f_m) * Physics::RAD_FACTOR) + (541.0 / 3600) * std::sin((l1_m)*Physics::RAD_FACTOR)) * Physics::RAD_FACTOR);

    // all the sin and cos terms have similar in [-1,1], so multiply them before
    // multiplying BIG r_m value of ~380000
    // Eq 47
    std::array<double, 3> moon_pos {};
    double c_term = std::cos(lambda_m * Physics::RAD_FACTOR);
    double s_term = std::sin(lambda_m * Physics::RAD_FACTOR);
    moon_pos[0] = c_term;
    moon_pos[1] = s_term;
    c_term = std::cos(beta_m * Physics::RAD_FACTOR);
    s_term = std::sin(beta_m * Physics::RAD_FACTOR);
    moon_pos[0] *= c_term;
    moon_pos[1] *= c_term;
    moon_pos[2] = s_term;
    c_term = std::cos(Physics::EPSILON * Physics::RAD_FACTOR);
    s_term = std::sin(Physics::EPSILON * Physics::RAD_FACTOR);

    // contains the x,y,z position of the moon and 3 needed terms only depending
    // on those coordinates
    std::array<double, 6> moon_params = {
        moon_pos[0],
        c_term * moon_pos[1] - s_term * moon_pos[2],
        s_term * moon_pos[1] + c_term * moon_pos[2],
        0,
        0,
        0
    };
    // multiplied small terms first, to avoid floating point errors when
    // multiplying small with big values
    // Eq 42
    moon_params[0] *= r_m;
    moon_params[1] *= r_m;
    moon_params[2] *= r_m;
    // Eq 43
    double d2 = std::inner_product(moon_params.begin(), moon_params.end(),
        moon_params.begin(), 0.);
    d2 = 1 / std::sqrt(d2 * d2 * d2);
    // Eq 44
    moon_params[3] = moon_params[0] * d2;
    moon_params[4] = moon_params[1] * d2;
    moon_params[5] = moon_params[2] * d2;
    return moon_params;
}
void apply(const Debris::Debris& d,
    const std::array<double, 6>& moon_params,
    std::array<double, 3>& acc_lun,
    std::array<double, 3>& acc_total)
{
    acc_lun = d.getPosition();
    acc_lun[0] -= moon_params[0];
    acc_lun[1] -= moon_params[1];
    acc_lun[2] -= moon_params[2];
    // Eq 45
    double d1 = std::inner_product(acc_lun.begin(), acc_lun.end(), acc_lun.begin(), 0.);
    d1 = 1 / std::sqrt(d1 * d1 * d1);
    // Eq 46
    acc_lun[0] = -Physics::GM_MOON * (acc_lun[0] * d1 + moon_params[3]);
    acc_lun[1] = -Physics::GM_MOON * (acc_lun[1] * d1 + moon_params[4]);
    acc_lun[2] = -Physics::GM_MOON * (acc_lun[2] * d1 + moon_params[5]);
    acc_total[0] += acc_lun[0];
    acc_total[1] += acc_lun[1];
    acc_total[2] += acc_lun[2];
}
} // namespace Acceleration