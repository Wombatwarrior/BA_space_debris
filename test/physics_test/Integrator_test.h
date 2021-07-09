//
// Created by Oliver on 13.05.21.
//

#pragma once
#ifdef HEYOKA_IS_PRESENT
#include "heyoka/heyoka.hpp"
#include "physics/Constants.h"
#include "physics/Integrator.h"
#include "gtest/gtest.h"

class CompareWithHeyokaTests : public ::testing::Test {
protected:
    //constants
    inline static constexpr double GMe = 3.986004407799724e+5;
    inline static constexpr double GMo = 1.32712440018e+11;
    inline static constexpr double GMm = 4.9028e+3;
    inline static constexpr double Re = 6378.1363;
    inline static constexpr double C20 = -4.84165371736e-4;
    inline static constexpr double C22 = 2.43914352398e-6;
    inline static constexpr double S22 = -1.40016683654e-6;
    inline static constexpr double theta_g = Physics::RAD_FACTOR * 280.4606;
    inline static constexpr double nu_e = Physics::RAD_FACTOR * (4.178074622024230e-3);
    inline static constexpr double nu_o = Physics::RAD_FACTOR * (1.1407410259335311e-5);
    inline static constexpr double nu_ma = Physics::RAD_FACTOR * (1.512151961904581e-4);
    inline static constexpr double nu_mp = Physics::RAD_FACTOR * (1.2893925235125941e-6);
    inline static constexpr double nu_ms = Physics::RAD_FACTOR * (6.128913003523574e-7);
    inline static constexpr double alpha_o = 1.49619e+8;
    inline static constexpr double epsilon = Physics::RAD_FACTOR * 23.4392911;
    inline static constexpr double phi_o = Physics::RAD_FACTOR * 357.5256;
    inline static constexpr double Omega_plus_w = Physics::RAD_FACTOR * 282.94;
    inline static constexpr double PSRP = 4.56e-3;
    inline static constexpr double p0 = 1.3;
    inline static constexpr double omega_e = 7.292115e-5;
    inline static constexpr double h = 8.5;

    // delta t
    inline static double delta_t = .001;
    inline static constexpr double start_t = 0.;
    inline static constexpr double end_t = 1000;

    //heyoka variables
    inline static std::array<heyoka::expression, 3> pos;
    inline static std::array<heyoka::expression, 3> vel;
    inline static heyoka::taylor_adaptive<double>* ta_total;
    inline static std::array<heyoka::taylor_adaptive<double>*, 8> ta_components;

    // won integrators
    inline static Integrator* i_total;
    inline static Acceleration::AccelerationAccumulator* aa_total;
    inline static std::array<Integrator*, 8> i_components;
    inline static std::array<Acceleration::AccelerationAccumulator*, 8> aa_components;
    inline static void SetUpTestSuite()
    {
        //create heyoka variables
        pos = heyoka::make_vars("X", "Y", "Z");
        vel = heyoka::make_vars("VX", "VY", "VZ");

        //Sun's position
        auto lo = phi_o + nu_o * heyoka::time;
        auto lambda_o = Omega_plus_w + lo + Physics::RAD_FACTOR * ((6892. / 3600) * heyoka::sin(lo) + (72. / 3600) * heyoka::sin(2. * lo));
        auto ro = (149.619 - 2.499 * heyoka::cos(lo) - 0.021 * heyoka::cos(2. * lo)) * (1e6);

        auto Xo = ro * heyoka::cos(lambda_o);
        auto Yo = ro * heyoka::sin(lambda_o) * std::cos(epsilon);
        auto Zo = ro * heyoka::sin(lambda_o) * std::sin(epsilon);

        //Moon's position
        auto phi_m = nu_o * heyoka::time;
        auto phi_ma = nu_ma * heyoka::time;
        auto phi_mp = nu_mp * heyoka::time;
        auto phi_ms = nu_ms * heyoka::time;
        auto L0 = phi_mp + phi_ma + Physics::RAD_FACTOR * 218.31617;
        auto lm = phi_ma + Physics::RAD_FACTOR * 134.96292;
        auto llm = phi_m + Physics::RAD_FACTOR * 357.5256;
        auto Fm = phi_mp + phi_ma + phi_ms + Physics::RAD_FACTOR * 93.27283;
        auto Dm = phi_mp + phi_ma - phi_m + Physics::RAD_FACTOR * 297.85027;

        auto rm = 385000. - 20905. * heyoka::cos(lm) - 3699. * heyoka::cos(2. * Dm - lm) - 2956. * heyoka::cos(2. * Dm) - 570. * heyoka::cos(2. * lm) + 246. * heyoka::cos(2. * lm - 2. * Dm) - 205. * heyoka::cos(llm - 2. * Dm) - 171. * heyoka::cos(lm + 2. * Dm) - 152. * heyoka::cos(lm + llm - 2. * Dm);

        auto lambda_m = L0 + Physics::RAD_FACTOR * ((22640. / 3600) * heyoka::sin(lm) + (769. / 3600) * heyoka::sin(2. * lm) - (4856. / 3600) * heyoka::sin(lm - 2. * Dm) + (2370. / 3600) * heyoka::sin(2. * Dm) - (668. / 3600) * heyoka::sin(llm) - (412. / 3600) * heyoka::sin(2. * Fm) - (212. / 3600) * heyoka::sin(2. * lm - 2. * Dm) - (206. / 3600) * heyoka::sin(lm + llm - 2. * Dm) + (192. / 3600) * heyoka::sin(lm + 2. * Dm) - (165. / 3600) * heyoka::sin(llm - 2. * Dm) + (148. / 3600) * heyoka::sin(lm - llm) - (125. / 3600) * heyoka::sin(Dm) - (110. / 3600) * heyoka::sin(lm + llm) - (55. / 3600) * heyoka::sin(2. * Fm - 2. * Dm));

        auto Bm = Physics::RAD_FACTOR * ((18520. / 3600) * heyoka::sin(Fm + lambda_m - L0 + Physics::RAD_FACTOR * ((412. / 3600) * heyoka::sin(2. * Fm) + (541. / 3600) * heyoka::sin(llm))) - (526. / 3600) * heyoka::sin(Fm - 2. * Dm) + (44. / 3600) * heyoka::sin(lm + Fm - 2. * Dm) - (31. / 3600) * heyoka::sin(-lm + Fm - 2. * Dm) - (25. / 3600) * heyoka::sin(-2. * lm + Fm) - (23. / 3600) * heyoka::sin(llm + Fm - 2. * Dm) + (21. / 3600) * heyoka::sin(-lm + Fm) + (11. / 3600) * heyoka::sin(-llm + Fm - 2. * Dm));

        auto Xm = heyoka::cos(Bm) * heyoka::cos(lambda_m) * rm;
        auto Ym = -std::sin(epsilon) * heyoka::sin(Bm) * rm + std::cos(epsilon) * heyoka::cos(Bm) * heyoka::sin(lambda_m) * rm;
        auto Zm = std::cos(epsilon) * heyoka::sin(Bm) * rm + heyoka::cos(Bm) * std::sin(epsilon) * heyoka::sin(lambda_m) * rm;

        // distance to earth center
        auto magR2 = heyoka::pow(pos[0], 2.) + heyoka::pow(pos[1], 2.) + heyoka::pow(pos[2], 2.);

        //Earth's Keplerian terms
        auto fKepX = -GMe * pos[0] / (heyoka::pow(magR2, (3. / 2)));
        auto fKepY = -GMe * pos[1] / (heyoka::pow(magR2, (3. / 2)));
        auto fKepZ = -GMe * pos[2] / (heyoka::pow(magR2, (3. / 2)));

        //Earth's J2 terms
        auto J2term1 = GMe * (std::pow(Re, 2)) * std::sqrt(5) * C20 / (2. * heyoka::pow(magR2, (1. / 2)));
        auto J2term2 = 3. / (heyoka::pow(magR2, 2.));
        auto J2term3 = 15. * (heyoka::pow(pos[2], 2.)) / (heyoka::pow(magR2, 3.));
        auto fJ2X = J2term1 * pos[0] * (J2term2 - J2term3);
        auto fJ2Y = J2term1 * pos[1] * (J2term2 - J2term3);
        auto fJ2Z = J2term1 * pos[2] * (3. * J2term2 - J2term3);

        //Earth's C22 and S22 terms
        auto x = pos[0] * heyoka::cos(theta_g + nu_e * heyoka::time) + pos[1] * heyoka::sin(theta_g + nu_e * heyoka::time);
        auto y = -pos[0] * heyoka::sin(theta_g + nu_e * heyoka::time) + pos[1] * heyoka::cos(theta_g + nu_e * heyoka::time);
        auto z = pos[2];
        auto magr2 = heyoka::pow(x, 2.) + heyoka::pow(y, 2.) + heyoka::pow(z, 2.);

        auto C22term1 = 5 * GMe * (std::pow(Re, 2)) * std::sqrt(15) * C22 / (2. * heyoka::pow(magr2, (7. / 2)));
        auto C22term2 = GMe * (std::pow(Re, 2)) * std::sqrt(15) * C22 / (heyoka::pow(magr2, (5. / 2)));
        auto fC22x = C22term1 * x * (heyoka::pow(y, 2.) - heyoka::pow(x, 2.)) + C22term2 * x;
        auto fC22y = C22term1 * y * (heyoka::pow(y, 2.) - heyoka::pow(x, 2.)) - C22term2 * y;
        auto fC22z = C22term1 * z * (heyoka::pow(y, 2.) - heyoka::pow(x, 2.));

        auto S22term1 = 5 * GMe * (std::pow(Re, 2)) * std::sqrt(15) * S22 / (heyoka::pow(magr2, (7. / 2)));
        auto S22term2 = GMe * (std::pow(Re, 2)) * std::sqrt(15) * S22 / (heyoka::pow(magr2, (5. / 2)));
        auto fS22x = -S22term1 * (heyoka::pow(x, 2.)) * y + S22term2 * y;
        auto fS22y = -S22term1 * x * (heyoka::pow(y, 2.)) + S22term2 * x;
        auto fS22z = -S22term1 * x * y * z;

        auto fC22X = fC22x * heyoka::cos(theta_g + nu_e * heyoka::time) - fC22y * heyoka::sin(theta_g + nu_e * heyoka::time);
        auto fC22Y = fC22x * heyoka::sin(theta_g + nu_e * heyoka::time) + fC22y * heyoka::cos(theta_g + nu_e * heyoka::time);
        auto fC22Z = fC22z;

        auto fS22X = fS22x * heyoka::cos(theta_g + nu_e * heyoka::time) - fS22y * heyoka::sin(theta_g + nu_e * heyoka::time);
        auto fS22Y = fS22x * heyoka::sin(theta_g + nu_e * heyoka::time) + fS22y * heyoka::cos(theta_g + nu_e * heyoka::time);
        auto fS22Z = fS22z;

        //Sun's gravity
        auto magRo2 = heyoka::pow(Xo, 2.) + heyoka::pow(Yo, 2.) + heyoka::pow(Zo, 2.);
        auto magRRo2 = heyoka::pow((pos[0] - Xo), 2.) + heyoka::pow((pos[1] - Yo), 2.) + heyoka::pow((pos[2] - Zo), 2.);
        auto fSunX = -GMo * ((pos[0] - Xo) / (heyoka::pow(magRRo2, (3. / 2))) + Xo / (heyoka::pow(magRo2, (3. / 2))));
        auto fSunY = -GMo * ((pos[1] - Yo) / (heyoka::pow(magRRo2, (3. / 2))) + Yo / (heyoka::pow(magRo2, (3. / 2))));
        auto fSunZ = -GMo * ((pos[2] - Zo) / (heyoka::pow(magRRo2, (3. / 2))) + Zo / (heyoka::pow(magRo2, (3. / 2))));

        //Moon's gravity
        auto magRm2 = heyoka::pow(Xm, 2.) + heyoka::pow(Ym, 2.) + heyoka::pow(Zm, 2.);
        auto magRRm2 = heyoka::pow((pos[0] - Xm), 2.) + heyoka::pow((pos[1] - Ym), 2.) + heyoka::pow((pos[2] - Zm), 2.);
        auto fMoonX = -GMm * ((pos[0] - Xm) / (heyoka::pow(magRRm2, (3. / 2))) + Xm / (heyoka::pow(magRm2, (3. / 2))));
        auto fMoonY = -GMm * ((pos[1] - Ym) / (heyoka::pow(magRRm2, (3. / 2))) + Ym / (heyoka::pow(magRm2, (3. / 2))));
        auto fMoonZ = -GMm * ((pos[2] - Zm) / (heyoka::pow(magRRm2, (3. / 2))) + Zm / (heyoka::pow(magRm2, (3. / 2))));

        //Sun's radiation pressure (AOM is a heyoka parameter hy.par[0]. We
        //will be able to set it later without recompiling the integartor)
        auto SRPterm = heyoka::par[0] * PSRP * (std::pow(alpha_o, 2)) / (heyoka::pow(magRRo2, (3. / 2)));
        auto fSRPX = SRPterm * (pos[0] - Xo);
        auto fSRPY = SRPterm * (pos[1] - Yo);
        auto fSRPZ = SRPterm * (pos[2] - Zo);

        // atmospheric drag
        auto p = p0 * heyoka::exp(-(heyoka::sqrt(magR2) - Re) / h);
        auto v_rel_x = vel[0] + omega_e * pos[1];
        auto v_rel_y = vel[1] - omega_e * pos[0];
        auto v_rel_z = vel[2];
        // Drag due to the earths atmosphere (BCINV is a heyoka parameter hy.par[1])
        auto DragTerm = (heyoka::par[1] * p) / 2.;
        auto fDragX = -DragTerm * heyoka::pow(v_rel_x, 2.);
        auto fDragY = -DragTerm * heyoka::pow(v_rel_y, 2.);
        auto fDragZ = -DragTerm * heyoka::pow(v_rel_z, 2.);
        // EOM
        auto dXdt = vel[0];
        auto dYdt = vel[1];
        auto dZdt = vel[2];
        auto dVXdt = fKepX + fJ2X + fC22X + fS22X + fSunX + fMoonX + fSRPX + fDragX;
        auto dVYdt = fKepY + fJ2Y + fC22Y + fS22Y + fSunY + fMoonY + fSRPY + fDragY;
        auto dVZdt = fKepZ + fJ2Z + fC22Z + fS22Z + fSunZ + fMoonZ + fSRPZ + fDragZ;

        // set output accuracy
        std::cout << std::setprecision(std::numeric_limits<double>::digits10 + 1);

        // Initial conditions (ic) -  can be changed later
        auto x0 = 0.;
        auto y0 = 0.;
        auto z0 = 0.;
        auto vx0 = 0.;
        auto vy0 = 0.;
        auto vz0 = 0.;

        auto t0 = 0.0;

        std::cout << "Compiling the Taylor integrator ... (this is done only once)" << std::endl;

        ta_total = new heyoka::taylor_adaptive<double> {
            { heyoka::prime(pos[0]) = dXdt, heyoka::prime(pos[1]) = dYdt, heyoka::prime(pos[2]) = dZdt, heyoka::prime(vel[0]) = dVXdt, heyoka::prime(vel[1]) = dVYdt, heyoka::prime(vel[2]) = dVZdt },
            { x0, y0, z0, vx0, vy0, vz0 },
            heyoka::kw::time = t0,
            heyoka::kw::tol = 1e-16,
            heyoka::kw::compact_mode = true
        };

        ta_components[Acceleration::KEP] = new heyoka::taylor_adaptive<double> {
            { heyoka::prime(pos[0]) = dXdt, heyoka::prime(pos[1]) = dYdt, heyoka::prime(pos[2]) = dZdt, heyoka::prime(vel[0]) = fKepX, heyoka::prime(vel[1]) = fKepY, heyoka::prime(vel[2]) = fKepZ },
            { x0, y0, z0, vx0, vy0, vz0 },
            heyoka::kw::time = t0,
            heyoka::kw::tol = 1e-16,
            heyoka::kw::compact_mode = true
        };
        ta_components[Acceleration::J2] = new heyoka::taylor_adaptive<double> {
            { heyoka::prime(pos[0]) = dXdt, heyoka::prime(pos[1]) = dYdt, heyoka::prime(pos[2]) = dZdt, heyoka::prime(vel[0]) = fJ2X, heyoka::prime(vel[1]) = fJ2Y, heyoka::prime(vel[2]) = fJ2Z },
            { x0, y0, z0, vx0, vy0, vz0 },
            heyoka::kw::time = t0,
            heyoka::kw::tol = 1e-16,
            heyoka::kw::compact_mode = true
        };
        ta_components[Acceleration::C22] = new heyoka::taylor_adaptive<double> {
            { heyoka::prime(pos[0]) = dXdt, heyoka::prime(pos[1]) = dYdt, heyoka::prime(pos[2]) = dZdt, heyoka::prime(vel[0]) = fC22X, heyoka::prime(vel[1]) = fC22Y, heyoka::prime(vel[2]) = fC22Z },
            { x0, y0, z0, vx0, vy0, vz0 },
            heyoka::kw::time = t0,
            heyoka::kw::tol = 1e-16,
            heyoka::kw::compact_mode = true
        };
        ta_components[Acceleration::S22] = new heyoka::taylor_adaptive<double> {
            { heyoka::prime(pos[0]) = dXdt, heyoka::prime(pos[1]) = dYdt, heyoka::prime(pos[2]) = dZdt, heyoka::prime(vel[0]) = fS22X, heyoka::prime(vel[1]) = fS22Y, heyoka::prime(vel[2]) = fS22Z },
            { x0, y0, z0, vx0, vy0, vz0 },
            heyoka::kw::time = t0,
            heyoka::kw::tol = 1e-16,
            heyoka::kw::compact_mode = true
        };
        ta_components[Acceleration::SOL] = new heyoka::taylor_adaptive<double> {
            { heyoka::prime(pos[0]) = dXdt, heyoka::prime(pos[1]) = dYdt, heyoka::prime(pos[2]) = dZdt, heyoka::prime(vel[0]) = fSunX, heyoka::prime(vel[1]) = fSunY, heyoka::prime(vel[2]) = fSunZ },
            { x0, y0, z0, vx0, vy0, vz0 },
            heyoka::kw::time = t0,
            heyoka::kw::tol = 1e-16,
            heyoka::kw::compact_mode = true
        };
        ta_components[Acceleration::LUN] = new heyoka::taylor_adaptive<double> {
            { heyoka::prime(pos[0]) = dXdt, heyoka::prime(pos[1]) = dYdt, heyoka::prime(pos[2]) = dZdt, heyoka::prime(vel[0]) = fMoonX, heyoka::prime(vel[1]) = fMoonY, heyoka::prime(vel[2]) = fMoonZ },
            { x0, y0, z0, vx0, vy0, vz0 },
            heyoka::kw::time = t0,
            heyoka::kw::tol = 1e-16,
            heyoka::kw::compact_mode = true
        };
        ta_components[Acceleration::SRP] = new heyoka::taylor_adaptive<double> {
            { heyoka::prime(pos[0]) = dXdt, heyoka::prime(pos[1]) = dYdt, heyoka::prime(pos[2]) = dZdt, heyoka::prime(vel[0]) = fSRPX, heyoka::prime(vel[1]) = fSRPY, heyoka::prime(vel[2]) = fSRPZ },
            { x0, y0, z0, vx0, vy0, vz0 },
            heyoka::kw::time = t0,
            heyoka::kw::tol = 1e-16,
            heyoka::kw::compact_mode = true
        };
        ta_components[Acceleration::DRAG] = new heyoka::taylor_adaptive<double> {
            { heyoka::prime(pos[0]) = dXdt, heyoka::prime(pos[1]) = dYdt, heyoka::prime(pos[2]) = dZdt, heyoka::prime(vel[0]) = fDragX, heyoka::prime(vel[1]) = fDragY, heyoka::prime(vel[2]) = fDragZ },
            { x0, y0, z0, vx0, vy0, vz0 },
            heyoka::kw::time = t0,
            heyoka::kw::tol = 1e-16,
            heyoka::kw::compact_mode = true
        };

        // setup own integrator for all components
        auto* debris = new Debris::DebrisContainer;
        std::array<bool, 8> config { true, true, true, true, true, true, true, true };

        aa_total = new Acceleration::AccelerationAccumulator;
        aa_total->setConfig(config);
        aa_total->setDebris(*debris);
        i_total = new Integrator;
        i_total->setAccumulator(*aa_total);
        i_total->setDebris(*debris);

        debris = new Debris::DebrisContainer;
        config = { false, false, false, false, false, false, false, false };
        aa_components[Acceleration::KEP] = new Acceleration::AccelerationAccumulator;
        config[Acceleration::KEP] = true;
        aa_components[Acceleration::KEP]->setConfig(config);
        aa_components[Acceleration::KEP]->setDebris(*debris);
        config[Acceleration::KEP] = false;
        i_components[Acceleration::KEP] = new Integrator;
        i_components[Acceleration::KEP]->setAccumulator(*aa_components[Acceleration::KEP]);
        i_components[Acceleration::KEP]->setDebris(*debris);

        debris = new Debris::DebrisContainer;
        aa_components[Acceleration::J2] = new Acceleration::AccelerationAccumulator;
        config[Acceleration::J2] = true;
        aa_components[Acceleration::J2]->setConfig(config);
        aa_components[Acceleration::J2]->setDebris(*debris);
        config[Acceleration::J2] = false;
        i_components[Acceleration::J2] = new Integrator;
        i_components[Acceleration::J2]->setAccumulator(*aa_components[Acceleration::J2]);
        i_components[Acceleration::J2]->setDebris(*debris);

        debris = new Debris::DebrisContainer;
        aa_components[Acceleration::C22] = new Acceleration::AccelerationAccumulator;
        config[Acceleration::C22] = true;
        aa_components[Acceleration::C22]->setConfig(config);
        aa_components[Acceleration::C22]->setDebris(*debris);
        config[Acceleration::C22] = false;
        i_components[Acceleration::C22] = new Integrator;
        i_components[Acceleration::C22]->setAccumulator(*aa_components[Acceleration::C22]);
        i_components[Acceleration::C22]->setDebris(*debris);

        debris = new Debris::DebrisContainer;
        aa_components[Acceleration::S22] = new Acceleration::AccelerationAccumulator;
        config[Acceleration::S22] = true;
        aa_components[Acceleration::S22]->setConfig(config);
        aa_components[Acceleration::S22]->setDebris(*debris);
        config[Acceleration::S22] = false;
        i_components[Acceleration::S22] = new Integrator;
        i_components[Acceleration::S22]->setAccumulator(*aa_components[Acceleration::S22]);
        i_components[Acceleration::S22]->setDebris(*debris);

        debris = new Debris::DebrisContainer;
        aa_components[Acceleration::LUN] = new Acceleration::AccelerationAccumulator;
        config[Acceleration::LUN] = true;
        aa_components[Acceleration::LUN]->setConfig(config);
        aa_components[Acceleration::LUN]->setDebris(*debris);
        config[Acceleration::LUN] = false;
        i_components[Acceleration::LUN] = new Integrator;
        i_components[Acceleration::LUN]->setAccumulator(*aa_components[Acceleration::LUN]);
        i_components[Acceleration::LUN]->setDebris(*debris);

        debris = new Debris::DebrisContainer;
        aa_components[Acceleration::SOL] = new Acceleration::AccelerationAccumulator;
        config[Acceleration::SOL] = true;
        aa_components[Acceleration::SOL]->setConfig(config);
        aa_components[Acceleration::SOL]->setDebris(*debris);
        config[Acceleration::SOL] = false;
        i_components[Acceleration::SOL] = new Integrator;
        i_components[Acceleration::SOL]->setAccumulator(*aa_components[Acceleration::SOL]);
        i_components[Acceleration::SOL]->setDebris(*debris);

        debris = new Debris::DebrisContainer;
        aa_components[Acceleration::SRP] = new Acceleration::AccelerationAccumulator;
        config[Acceleration::SRP] = true;
        aa_components[Acceleration::SRP]->setConfig(config);
        aa_components[Acceleration::SRP]->setDebris(*debris);
        config[Acceleration::SRP] = false;
        i_components[Acceleration::SRP] = new Integrator;
        i_components[Acceleration::SRP]->setAccumulator(*aa_components[Acceleration::SRP]);
        i_components[Acceleration::SRP]->setDebris(*debris);

        debris = new Debris::DebrisContainer;
        aa_components[Acceleration::DRAG] = new Acceleration::AccelerationAccumulator;
        config[Acceleration::DRAG] = true;
        aa_components[Acceleration::DRAG]->setConfig(config);
        aa_components[Acceleration::DRAG]->setDebris(*debris);
        config[Acceleration::DRAG] = false;
        i_components[Acceleration::DRAG] = new Integrator;
        i_components[Acceleration::DRAG]->setAccumulator(*aa_components[Acceleration::DRAG]);
        i_components[Acceleration::DRAG]->setDebris(*debris);
    }

    void prepareRun(Integrator& i, heyoka::taylor_adaptive<double>& ta, Debris::Debris& d)
    {
        i.getDebris().cleanDebrisVector();
        i.getDebris().addDebris(d);
        ta.get_state_data()[0] = d.getPosition()[0];
        ta.get_state_data()[1] = d.getPosition()[1];
        ta.get_state_data()[2] = d.getPosition()[2];
        ta.get_state_data()[3] = d.getVelocity()[0];
        ta.get_state_data()[4] = d.getVelocity()[1];
        ta.get_state_data()[5] = d.getVelocity()[2];
        // reset time values
        i.setDeltaT(delta_t);
        i.getAccumulator().setT(start_t);
        ta.set_time(start_t);
    }

    void showErrors(Integrator& i, heyoka::taylor_adaptive<double>& ta)
    {
        std::array<double, 3> pos_i = i.getDebris().getDebrisVector()[0].getPosition();
        std::array<double, 3> vel_i = i.getDebris().getDebrisVector()[0].getVelocity();
        std::array<double, 3> pos_ta { ta.get_state()[0],
                                       ta.get_state()[1],
                                       ta.get_state()[2] };
        std::array<double, 3> vel_ta { ta.get_state()[3],
                                       ta.get_state()[4],
                                       ta.get_state()[5] };
        IOUtils::to_ostream(pos_i, std::cout, ",", { "position integrator[", "]\n" });
        IOUtils::to_ostream(pos_ta, std::cout, ",", { "position heyoka[", "]\n" });
        IOUtils::to_ostream(std::array<double, 1> { MathUtils::cosSimilarity(pos_ta, pos_i) }, std::cout, "",
            { "cosine similarity: ", "\n" });
        IOUtils::to_ostream(std::array<double, 1> { MathUtils::euclideanDistance(pos_ta, pos_i) }, std::cout, "",
            { "euclidean distance: ", "\n" });
        IOUtils::to_ostream(MathUtils::absoluteError(pos_i,pos_ta), std::cout, ",", { "absolute error[", "]\n" });
        IOUtils::to_ostream(MathUtils::relativeError(pos_i,pos_ta), std::cout, ",", { "relative error[", "]\n" });
        IOUtils::to_ostream(vel_i, std::cout, ",", { "velocity integrator[", "]\n" });
        IOUtils::to_ostream(vel_ta, std::cout, ",", { "velocity heyoka[", "]\n" });
        IOUtils::to_ostream(std::array<double, 1> { MathUtils::cosSimilarity(vel_ta, vel_i) }, std::cout, "",
            { "cosine similarity: ", "\n" });
        IOUtils::to_ostream(std::array<double, 1> { MathUtils::euclideanDistance(vel_ta, vel_i) }, std::cout, "",
            { "euclidean distance: ", "\n" });
        IOUtils::to_ostream(MathUtils::absoluteError(vel_i,vel_ta), std::cout, ",", { "absolute error[", "]\n" });
        IOUtils::to_ostream(MathUtils::relativeError(vel_i,vel_ta), std::cout, ",", { "relative error[", "]\n" });
    }
};
#endif
