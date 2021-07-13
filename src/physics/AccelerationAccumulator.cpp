//
// Created by Oliver on 12.05.21.
// based on https://www.overleaf.com/project/608918003323352d4d3ceb55
// equations. for reference
//

#include "AccelerationAccumulator.h"

namespace Acceleration {

AccelerationAccumulator::AccelerationAccumulator() = default;

AccelerationAccumulator::~AccelerationAccumulator() = default;

void AccelerationAccumulator::applyComponents() const
{
    // will be modified by the apply functions
    std::array<double, 3> new_acc_total { 0, 0, 0 };
    std::array<double, 3> new_acc_component { 0, 0, 0 };
    double d_srp = 0;
    // are constant for this time step
    double c_term;
    double s_term;
    std::array<double, 6> sun_params {};
    // setup only needed for SolComponent and SRPComponent
    if (config[SOL] || config[SRP]) {
        sun_params = SolComponent::setUp(t);
    }
    std::array<double, 6> moon_params {};
    // setup only needed for LunComponent
    if (config[LUN]) {
        moon_params = LunComponent::setUp(t);
    }
    // setup only needed for C22Component and S22Component
    if (config[C22] || config[S22]) {
        // Eq 15
        c_term = std::cos((Physics::THETA_G + Physics::NU_EARTH * t) * Physics::RAD_FACTOR);
        s_term = std::sin((Physics::THETA_G + Physics::NU_EARTH * t) * Physics::RAD_FACTOR);
    }

    for (auto &d : *debris) {
        new_acc_total[0] = 0;
        new_acc_total[1] = 0;
        new_acc_total[2] = 0;
        new_acc_component[0] = 0;
        new_acc_component[1] = 0;
        new_acc_component[2] = 0;
        d_srp = 0;
        // Eq 1
        if (config[KEP]) {
            KepComponent::apply(d, new_acc_component, new_acc_total);
        }
        if (config[J2]) {
            J2Component::apply(d, new_acc_component, new_acc_total);
        }
        // if we want to calculate both C22 and S22 we can share many of the
        // calculation steps
        if (config[C22] && config[S22]) {
            C22S22Component::apply(d, c_term, s_term, new_acc_component,
                new_acc_total);
        } // if only one of the two should be calculated we only calculate the
        // needed one
        else {
            if (config[C22]) {
                C22Component::apply(d, c_term, s_term, new_acc_component,
                    new_acc_total);
            }
            if (config[S22]) {
                S22Component::apply(d, c_term, s_term, new_acc_component,
                    new_acc_total);
            }
        }
        if (config[SOL]) {
            SolComponent::apply(d, d_srp, sun_params, new_acc_component, new_acc_total);
        }
        if (config[LUN]) {
            LunComponent::apply(d, moon_params, new_acc_component, new_acc_total);
        }
        if (config[SRP]) {
            SRPComponent::apply(d, d_srp, sun_params, new_acc_component, new_acc_total);
        }
        if (config[DRAG]) {
            DragComponent::apply(d, new_acc_component, new_acc_total);
        }
        d.setAccT1(new_acc_total);
    }
}

void AccelerationAccumulator::applyAmdWriteComponents() const
{
    // will be modified by the apply functions
    std::array<double, 3> new_acc_total { 0, 0, 0 };
    std::array<double, 3> new_acc_component { 0, 0, 0 };
    double d_srp = 0;
    // are constant for this time step
    double c_term;
    double s_term;
    std::array<double, 6> sun_params {};
    // setup only needed for SolComponent and SRPComponent
    if (config[SOL] || config[SRP]) {
        sun_params = SolComponent::setUp(t);
    }
    std::array<double, 6> moon_params {};
    // setup only needed for LunComponent
    if (config[LUN]) {
        moon_params = LunComponent::setUp(t);
    }
    // setup only needed for C22Component and S22Component
    if (config[C22] || config[S22]) {
        // Eq 15
        c_term = std::cos((Physics::THETA_G + Physics::NU_EARTH * t) * Physics::RAD_FACTOR);
        s_term = std::sin((Physics::THETA_G + Physics::NU_EARTH * t) * Physics::RAD_FACTOR);
    }

    for (auto &d : *debris) {
        // start a new line o data for each particle
        file_output->writeAcc_start(t);
        new_acc_total[0] = 0;
        new_acc_total[1] = 0;
        new_acc_total[2] = 0;
        new_acc_component[0] = 0;
        new_acc_component[1] = 0;
        new_acc_component[2] = 0;
        // Eq 1
        if (config[KEP]) {
            KepComponent::apply(d, new_acc_component, new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[J2]) {
            J2Component::apply(d, new_acc_component, new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[C22]) {
            C22Component::apply(d, c_term, s_term, new_acc_component,
                new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[S22]) {
            S22Component::apply(d, c_term, s_term, new_acc_component,
                new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[SOL]) {
            SolComponent::apply(d, d_srp, sun_params, new_acc_component, new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[LUN]) {
            LunComponent::apply(d, moon_params, new_acc_component, new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[SRP]) {
            SRPComponent::apply(d, d_srp, sun_params, new_acc_component, new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[DRAG]) {
            DragComponent::apply(d, new_acc_component, new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        d.setAccT1(new_acc_total);
        file_output->writeAcc_end(new_acc_total);
    }
}

const std::array<bool, 8>& AccelerationAccumulator::getConfig() const
{
    return config;
}

std::array<bool, 8>& AccelerationAccumulator::getConfig()
{
    return config;
}

void AccelerationAccumulator::setConfig(const std::array<bool, 8>& config)
{
    AccelerationAccumulator::config = config;
}

const Debris::DebrisContainer& AccelerationAccumulator::getDebris() const
{
    return *debris;
}

Debris::DebrisContainer& AccelerationAccumulator::getDebris()
{
    return *debris;
}

void AccelerationAccumulator::setDebris(Debris::DebrisContainer& debris)
{
    AccelerationAccumulator::debris = &debris;
}

double AccelerationAccumulator::getT() const
{
    return t;
}

void AccelerationAccumulator::setT(double t)
{
    AccelerationAccumulator::t = t;
}

const FileOutput& AccelerationAccumulator::getFileOutput() const
{
    return *file_output;
}

FileOutput& AccelerationAccumulator::getFileOutput()
{
    return *file_output;
}

void AccelerationAccumulator::setFileOutput(FileOutput& fileOutput)
{
    file_output = &fileOutput;
}
} // namespace Acceleration