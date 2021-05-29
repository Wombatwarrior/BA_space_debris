//
// Created by Oliver on 12.05.21.
// based on https://www.overleaf.com/project/608918003323352d4d3ceb55
// equations. for reference
//

#include "AccelerationAccumulator.h"

#include <iostream>

namespace Acceleration {
AccelerationAccumulator::~AccelerationAccumulator() { }

void AccelerationAccumulator::applyComponents()
{
    std::array<double, 3> new_acc_total { 0, 0, 0 };
    std::array<double, 3> new_acc_component { 0, 0, 0 };
    // Eq 15
    const double c_term = std::cos((Physics::THETA_G + Physics::NU_EARTH * t) * Physics::RAD_FACTOR);
    const double s_term = std::sin((Physics::THETA_G + Physics::NU_EARTH * t) * Physics::RAD_FACTOR);
    debris->shiftAcceleration();
    for (auto& d : debris->getDebrisVector()) {
        new_acc_total[0] = 0;
        new_acc_total[1] = 0;
        new_acc_total[2] = 0;
        new_acc_component[0] = 0;
        new_acc_component[1] = 0;
        new_acc_component[2] = 0;
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
            std::array<double, 6> sun_params = SolComponent::setUp(t);
            SolComponent::apply(d, sun_params, new_acc_component, new_acc_total);
        }
        if (config[LUN]) {
            const std::array<double, 6> moon_params = LunComponent::setUp(t);
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

std::array<bool, 8>& AccelerationAccumulator::getConfig()
{
    return config;
}

void AccelerationAccumulator::setConfig(std::array<bool, 8>& config)
{
    AccelerationAccumulator::config = config;
}

Debris::DebrisContainer& AccelerationAccumulator::getDebris()
{
    return *debris;
}

void AccelerationAccumulator::setDebris(Debris::DebrisContainer& debris)
{
    AccelerationAccumulator::debris = &debris;
}

double AccelerationAccumulator::getT()
{
    return t;
}

void AccelerationAccumulator::setT(double t)
{
    AccelerationAccumulator::t = t;
}
} // namespace Acceleration