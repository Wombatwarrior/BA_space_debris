//
// Created by Oliver on 12.05.21.
//

#include "Acceleration.h"
#include <iostream>

namespace Acceleration{
    AccelerationAccumulator::~AccelerationAccumulator(){

    }

    void AccelerationAccumulator::applyComponents(){
        std::array<double,3> new_acc_total{0,0,0};
        std::array<double,3> new_acc_component{0,0,0};
        double t = 1;
        debris->shiftAcceleration();
        for (auto &d : debris->getDebrisVector()) {
            new_acc_total[0] = 0;
            new_acc_total[1] = 0;
            new_acc_total[2] = 0;
            new_acc_component[0] = 0;
            new_acc_component[1] = 0;
            new_acc_component[2] = 0;
            if (config[KEP]) {
                KepComponent::apply(d, new_acc_component, new_acc_total);
            }
            if (config[J2]) {
                J2Component::apply(d, new_acc_component, new_acc_total);
            }
            if (config[C22]) {
                C22Component::apply(d, t, new_acc_component, new_acc_total);
            }
            if (config[S22]) {
                S22Component::apply(d, t, new_acc_component, new_acc_total);
            }
            if (config[SOL]) {
                SolComponent::apply(d, new_acc_component, new_acc_total);
            }
            if (config[LUN]) {
                const std::array<double,6> moon_params=LunComponent::setUp(t);
                LunComponent::apply(d, moon_params, new_acc_component, new_acc_total);
            }
            if (config[SRP]) {
                SRPComponent::apply(d, new_acc_component, new_acc_total);
            }
            if (config[DRAG]) {
                DragComponent::apply(d, new_acc_component, new_acc_total);
            }
            d.setAccT1(new_acc_total);
        }
    }

    std::array<bool, 8> &AccelerationAccumulator::getConfig()  {
        return config;
    }

    void AccelerationAccumulator::setConfig( std::array<bool, 8> &config) {
        AccelerationAccumulator::config = config;
    }

    Debris::DebrisContainer &AccelerationAccumulator::getDebris()  {
        return *debris;
    }

    void AccelerationAccumulator::setDebris(Debris::DebrisContainer &debris) {
        AccelerationAccumulator::debris = &debris;
    }

    namespace KepComponent {
        void apply( Debris::Debris &d, std::array<double,3> &acc_kep, std::array<double,3> &acc_total) {
            acc_kep = d.getPosition();
            double divisor = acc_kep[0] * acc_kep[0] + acc_kep[1] * acc_kep[1] + acc_kep[2] * acc_kep[2];
            divisor = divisor * divisor * divisor;
            divisor = std::sqrt(divisor);
            acc_kep[0] = Physics::GM_EARTH * acc_kep[0];
            acc_kep[1] = Physics::GM_EARTH * acc_kep[1];
            acc_kep[2] = Physics::GM_EARTH * acc_kep[2];
            acc_kep[0] = -acc_kep[0] / divisor;
            acc_kep[1] = -acc_kep[1] / divisor;
            acc_kep[2] = -acc_kep[2] / divisor;
            acc_total[0] = acc_total[0] + acc_kep[0];
            acc_total[1] = acc_total[1] + acc_kep[1];
            acc_total[2] = acc_total[2] + acc_kep[2];
        }
    }


    namespace J2Component {
        namespace {
            inline constexpr double getFactor_fst(){
                return 0.5*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*std::sqrt(5.0)*Physics::C_20;
            }
        }
        void apply( Debris::Debris &d, std::array<double,3> &acc_j2, std::array<double,3> &acc_total){
            acc_j2 = d.getPosition();
            double x2y2z2 = acc_j2[0] * acc_j2[0] + acc_j2[1] * acc_j2[1] + acc_j2[2] * acc_j2[2];
            double divisor_1 = std::sqrt(x2y2z2);
            double divisor_2 = x2y2z2*x2y2z2;
            double z2_15 = (15*(acc_j2[2]*acc_j2[2]))/(divisor_2*x2y2z2);
            double factor_snd = 3/divisor_2 - z2_15;
            acc_j2[0] = (acc_j2[0]/divisor_1)*getFactor_fst();
            acc_j2[1] = (acc_j2[1]/divisor_1)*getFactor_fst();
            acc_j2[2] = (acc_j2[2]/divisor_1)*getFactor_fst();
            acc_j2[0] = acc_j2[0] * factor_snd;
            acc_j2[1] = acc_j2[1] * factor_snd;
            factor_snd = 9/divisor_2 - z2_15;
            acc_j2[2] = acc_j2[2] * factor_snd;
            acc_total[0] = acc_total[0] + acc_j2[0];
            acc_total[1] = acc_total[1] + acc_j2[1];
            acc_total[2] = acc_total[2] + acc_j2[2];
        }
    }

    namespace C22Component {
        namespace {
            inline double getFC22_x(double x, double y, double z){
                double x2 = x*x;
                double y2 = y*y;
                double n = getFactor_fst()*x*(y2-x2);
                // x2 = (x^2 + y^2 + z^2)
                x2 = x2 + y2 + z*z;
                double fst = x2;
                // y2 = (x^2 + y^2 +z^2)^2
                y2 = x2*x2;
                // x2 = (x^2 + y^2 +z^2)^3
                x2 = x2*y2;
                // y2 = (x^2 + y^2 +z^2)^4
                y2 = y2*y2;
                double snd = (getFactor_snd()*x)/std::sqrt(y2*fst);
                fst = n/std::sqrt(y2*x2);
                return fst + snd;
            }
            inline double getFC22_y(double x, double y, double z){
                double x2 = x*x;
                double y2 = y*y;
                double n = getFactor_fst()*y*(y2-x2);
                // x2 = (x^2 + y^2 + z^2)
                x2 = x2 + y2 + z*z;
                double fst = x2;
                // y2 = (x^2 + y^2 +z^2)^2
                y2 = x2*x2;
                // x2 = (x^2 + y^2 +z^2)^3
                x2 = x2*y2;
                // y2 = (x^2 + y^2 +z^2)^4
                y2 = y2*y2;
                double snd = (getFactor_snd()*y)/std::sqrt(y2*fst);
                fst = n/std::sqrt(y2*x2);
                return fst - snd;
            }
            inline double getFC22_z(double x, double y, double z){
                double x2 = x*x;
                double y2 = y*y;
                double n = getFactor_fst()*z*(y2-x2);
                // x2 = x^2 + y^2 +z^2
                x2 = x2 + y2 + z*z;
                // y2 = (x^2 + y^2 +z^2)^2
                y2 = x2*x2;
                // x2 = (x^2 + y^2 +z^2)^3
                x2 = x2*y2;
                // y2 = (x^2 + y^2 +z^2)^4
                y2 = y2*y2;
                // y2 = (x^2 + y^2 +z^2)^(7/2)
                y2 = std::sqrt(y2*x2);
                return n/y2;
            }
            inline constexpr double getFactor_fst(){
                return 2.5*getFactor_snd();
            }
            inline constexpr double getFactor_snd(){
                return std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::C_22;
            }
        }
        void apply(Debris::Debris &d, double t, std::array<double,3> &acc_c22, std::array<double,3> &acc_total){
            acc_c22 = d.getPosition();
            double trig_arg = (Physics::THETA_G + Physics::NU_EARTH*t)*M_PIf64/180;
            double c_term = std::cos(trig_arg);
            double s_term = std::sin(trig_arg);
            double x = acc_c22[0]*c_term + acc_c22[1]*s_term;
            double y = -acc_c22[0]*s_term + acc_c22[1]*c_term;
            double z = acc_c22[2];
            double f_x = getFC22_x(x,y,z);
            double f_y = getFC22_y(x,y,z);
            acc_c22[0] = f_x*c_term - f_y*s_term;
            acc_c22[1] = f_x*s_term + f_y*c_term;
            acc_c22[2] = getFC22_z(x,y,z);
            acc_total[0] = acc_total[0] + acc_c22[0];
            acc_total[1] = acc_total[1] + acc_c22[1];
            acc_total[2] = acc_total[2] + acc_c22[2];
        }
    }

    namespace S22Component {
        namespace {
            inline double getFS22_x(double x, double y, double z){
                double x2 = x*x;
                double y2 = y*y;
                double n = getFactor_fst()*x2*y;
                // x2 = (x^2 + y^2 + z^2)
                x2 = x2 + y2 + z*z;
                double fst = x2;
                // y2 = (x^2 + y^2 +z^2)^2
                y2 = x2*x2;
                // x2 = (x^2 + y^2 +z^2)^3
                x2 = x2*y2;
                // y2 = (x^2 + y^2 +z^2)^4
                y2 = y2*y2;
                double snd = (getFactor_snd()*y)/std::sqrt(y2*fst);
                fst = n/std::sqrt(y2*x2);
                return fst + snd;
            }
            inline double getFS22_y(double x, double y, double z){
                double x2 = x*x;
                double y2 = y*y;
                double n = getFactor_fst()*x*y2;
                // x2 = (x^2 + y^2 + z^2)
                x2 = x2 + y2 + z*z;
                double fst = x2;
                // y2 = (x^2 + y^2 +z^2)^2
                y2 = x2*x2;
                // x2 = (x^2 + y^2 +z^2)^3
                x2 = x2*y2;
                // y2 = (x^2 + y^2 +z^2)^4
                y2 = y2*y2;
                double snd = (getFactor_snd()*x)/std::sqrt(y2*fst);
                fst = n/std::sqrt(y2*x2);
                return fst + snd;
            }
            inline double getFS22_z(double x, double y, double z){
                double n = getFactor_fst()*x*y*z;
                // x2 = x^2 + y^2 +z^2
                double x2 = x*x + y*y + z*z;
                // y2 = (x^2 + y^2 +z^2)^2
                double y2 = x2*x2;
                // x2 = (x^2 + y^2 +z^2)^3
                x2 = x2*y2;
                // y2 = (x^2 + y^2 +z^2)^4
                y2 = y2*y2;
                // y2 = (x^2 + y^2 +z^2)^(7/2)
                y2 = std::sqrt(y2*x2);
                return n/y2;
            }
            inline constexpr double getFactor_fst(){
                return -5*getFactor_snd();
            }
            inline constexpr double getFactor_snd(){
                return std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::S_22;
            }
        }
        void apply( Debris::Debris &d, double t, std::array<double,3> &acc_s22, std::array<double,3> &acc_total){
            acc_s22 = d.getPosition();
            double trig_arg = (Physics::THETA_G + Physics::NU_EARTH*t)*M_PIf64/180;
            double c_term = std::cos(trig_arg);
            double s_term = std::sin(trig_arg);
            double x = acc_s22[0]*c_term + acc_s22[1]*s_term;
            double y = -acc_s22[0]*s_term + acc_s22[1]*c_term;
            double z = acc_s22[2];
            double f_x = getFS22_x(x,y,z);
            double f_y = getFS22_y(x,y,z);
            acc_s22[0] = f_x*c_term - f_y*s_term;
            acc_s22[1] = f_x*s_term + f_y*c_term;
            acc_s22[2] = getFS22_z(x,y,z);
            acc_total[0] = acc_total[0] + acc_s22[0];
            acc_total[1] = acc_total[1] + acc_s22[1];
            acc_total[2] = acc_total[2] + acc_s22[2];
        }
    }

    namespace SolComponent {
        namespace {

        }
        void apply( Debris::Debris &d, std::array<double,3> &acc_sol, std::array<double,3> &acc_total){

        }
    }

    namespace LunComponent{
        const std::array<double,6> setUp(double t) {
            const double phi_m = Physics::NU_SUN*t;
            const double phi_m_a = Physics::NU_MOON_A*t;
            const double phi_m_p = Physics::NU_MOON_P*t;
            const double phi_m_s = Physics::NU_MOON_S*t;
            const double l_0 = phi_m_p + phi_m_a + 218.31617;
            const double l_m = phi_m_a + 134.96292;
            const double l1_m = phi_m + 357.52543;
            const double f_m = phi_m_p + phi_m_a + phi_m_s + 93.27283;
            const double d_m = phi_m_p + phi_m_a - phi_m + 297.85027;

            // add up small terms first, to avoid floating point errors when adding small to big values
            double r_m = -152*std::cos((l_m+l1_m-2*d_m)*M_PIf64/180);
            r_m -= 171*std::cos((l_m+2*d_m)*M_PIf64/180);
            r_m -= 205*std::cos((l1_m-2*d_m)*M_PIf64/180);
            r_m += 246*std::cos((2*l_m-2*d_m)*M_PIf64/180);
            r_m -= 570*std::cos((2*l_m)*M_PIf64/180);
            r_m -= 2956*std::cos((2*d_m)*M_PIf64/180);
            r_m -= 3699*std::cos((2*d_m-l_m)*M_PIf64/180);
            r_m -= 20905*std::cos(l_m*M_PIf64/180);
            r_m += 385000;

            // add up small terms first, to avoid floating point errors when adding small to big values
            double lambda_m = -(55.0/3600)*std::sin((2*f_m-2*d_m)*M_PIf64/180);
            lambda_m -= (110.0/3600)*std::sin((l_m+l1_m)*M_PIf64/180);
            lambda_m -= (125.0/3600)*std::sin((d_m)*M_PIf64/180);
            lambda_m += (148.0/3600)*std::sin((l_m-l1_m)*M_PIf64/180);
            lambda_m -= (165.0/3600)*std::sin((l1_m-2*d_m)*M_PIf64/180);
            lambda_m += (192.0/3600)*std::sin((l_m+2*d_m)*M_PIf64/180);
            lambda_m -= (206.0/3600)*std::sin((l_m+l1_m-2*d_m)*M_PIf64/180);
            lambda_m -= (212.0/3600)*std::sin((2*l_m-2*d_m)*M_PIf64/180);
            lambda_m -= (412.0/3600)*std::sin((2*f_m)*M_PIf64/180);
            lambda_m -= (668.0/3600)*std::sin((l1_m)*M_PIf64/180);
            lambda_m += (769.0/3600)*std::sin((2*l_m)*M_PIf64/180);
            lambda_m += (2370.0/3600)*std::sin((2*d_m)*M_PIf64/180);
            lambda_m -= (4856.0/3600)*std::sin((l_m-2*d_m)*M_PIf64/180);
            lambda_m += (22640.0/3600)*std::sin((l_m)*M_PIf64/180);
            lambda_m += l_0;

            // add up small terms first, to avoid floating point errors when adding small to big values
            double beta_m = (11.0/3600)*std::sin((-l1_m+f_m-2*d_m)*M_PIf64/180);
            beta_m += (21.0/3600)*std::sin((-l_m+f_m)*M_PIf64/180);
            beta_m -= (23.0/3600)*std::sin((l1_m+f_m-2*d_m)*M_PIf64/180);
            beta_m -= (25.0/3600)*std::sin((-2*l_m+f_m)*M_PIf64/180);
            beta_m -= (31.0/3600)*std::sin((-l_m+f_m-2*d_m)*M_PIf64/180);
            beta_m += (44.0/3600)*std::sin((l_m+f_m-2*d_m)*M_PIf64/180);
            beta_m -= (526.0/3600)*std::sin((f_m-2*d_m)*M_PIf64/180);
            beta_m += (18520.0/3600)*std::sin((f_m+lambda_m-l_0+(412.0/3600)*std::sin((2*f_m)*M_PIf64/180)+(541.0/3600)*std::sin((l1_m)*M_PIf64/180))*M_PIf64/180);

            // all the sin and cos terms have similar in [-1,1], so multiply them before multiplying BIG r_m value of ~380000
            std::array<double,3> moon_pos;
            double c_term = std::cos(lambda_m*M_PIf64/180);
            double s_term = std::sin(lambda_m*M_PIf64/180);
            moon_pos[0] = c_term;
            moon_pos[1] = s_term;
            c_term = std::cos(beta_m*M_PIf64/180);
            s_term = std::sin(beta_m*M_PIf64/180);
            moon_pos[0] = moon_pos[0]*c_term;
            moon_pos[1] = moon_pos[1]*c_term;
            moon_pos[2] = s_term;
            c_term = std::cos(Physics::EPSILON*M_PIf64/180);
            s_term = std::sin(Physics::EPSILON*M_PIf64/180);

            std::array<double,6> moon_params = {moon_pos[0],
                                                c_term*moon_pos[1] - s_term*moon_pos[2],
                                                s_term*moon_pos[1] + c_term*moon_pos[2],
                                                0,
                                                0,
                                                0
            };
            // multiplied small terms first, to avoid floating point errors when multiplying small with big values
            moon_params[0] = r_m*moon_params[0];
            moon_params[1] = r_m*moon_params[1];
            moon_params[2] = r_m*moon_params[2];
            double d2 = moon_params[0] * moon_params[0] + moon_params[1] * moon_params[1] + moon_params[2] * moon_params[2];
            d2 = 1/std::sqrt(d2*d2*d2);
            moon_params[3] = moon_params[0] * d2;
            moon_params[4] = moon_params[1] * d2;
            moon_params[5] = moon_params[2] * d2;
            return moon_params;
        }
        void apply( Debris::Debris &d, const std::array<double,6> &moon_params, std::array<double,3> &acc_lun, std::array<double,3> &acc_total){
            acc_lun = d.getPosition();
            acc_lun[0] = acc_lun[0] - moon_params[0];
            acc_lun[1] = acc_lun[1] - moon_params[1];
            acc_lun[2] = acc_lun[2] - moon_params[2];
            double d1 = acc_lun[0]*acc_lun[0]+acc_lun[1]*acc_lun[1]+acc_lun[2]*acc_lun[2];
            d1 = 1/std::sqrt(d1*d1*d1);
            acc_lun[0] = -Physics::GM_MOON * (acc_lun[0]*d1 + moon_params[3]);
            acc_lun[1] = -Physics::GM_MOON * (acc_lun[1]*d1 + moon_params[4]);
            acc_lun[2] = -Physics::GM_MOON * (acc_lun[2]*d1 + moon_params[5]);
            acc_total[0] = acc_total[0] + acc_lun[0];
            acc_total[1] = acc_total[1] + acc_lun[1];
            acc_total[2] = acc_total[2] + acc_lun[2];

        }
    }

    namespace SRPComponent {
        namespace {

        }
        void apply( Debris::Debris &d, std::array<double,3> &acc_srp, std::array<double,3> &acc_total){

        }
    }

    namespace DragComponent  {
        namespace {

        }
        void apply( Debris::Debris &d, std::array<double,3> &acc_drag, std::array<double,3> &acc_total){

        }
    }
}