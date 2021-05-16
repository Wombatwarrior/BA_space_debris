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

        debris.shiftAcceleration();
        for (auto &d : debris.getDebrisVector()) {
            if (config[KEP]) {
                KepComponent::apply(d, new_acc_component, new_acc_total);
            }
            if (config[J2]) {
                J2Component::apply(d, new_acc_component, new_acc_total);
            }
            if (config[C22]) {
                C22Component::apply(d, new_acc_component, new_acc_total);
            }
            if (config[S22]) {
                S22Component::apply(d, new_acc_component, new_acc_total);
            }
            if (config[SOL]) {
                SolComponent::apply(d, new_acc_component, new_acc_total);
            }
            if (config[LUN]) {
                LunComponent::apply(d, new_acc_component, new_acc_total);
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
        return debris;
    }

    void AccelerationAccumulator::setDebris(Debris::DebrisContainer &debris) {
        AccelerationAccumulator::debris = debris;
    }

    namespace KepComponent {
        void apply( Debris::Debris &d, std::array<double,3> &acc_kep, std::array<double,3> &acc) {
            acc_kep = d.getPosition();
            double divisor = acc_kep[0] * acc_kep[0] + acc_kep[1] * acc_kep[1] + acc_kep[2] * acc_kep[2];
            divisor = divisor * divisor * divisor;
            divisor = std::sqrt(divisor);
            acc_kep[0] = Physics::GM_EARTH * acc_kep[0];
            acc_kep[1] = Physics::GM_EARTH * acc_kep[1];
            acc_kep[2] = Physics::GM_EARTH * acc_kep[2];
            acc_kep[0] = acc_kep[0] / divisor;
            acc_kep[1] = acc_kep[1] / divisor;
            acc_kep[2] = acc_kep[2] / divisor;
            acc[0] = acc[0] - acc_kep[0];
            acc[1] = acc[1] - acc_kep[1];
            acc[2] = acc[2] - acc_kep[2];
        }
    }


    namespace J2Component {
        void apply( Debris::Debris &d, std::array<double,3> &acc_j2, std::array<double,3> &acc){

        }
    }

    namespace C22Component {
        void apply( Debris::Debris &d, std::array<double,3> &acc_c22, std::array<double,3> &acc){

        }
    }

    namespace S22Component {
        void apply( Debris::Debris &d, std::array<double,3> &acc_s22, std::array<double,3> &acc){

        }
    }

    namespace SolComponent {
        void apply( Debris::Debris &d, std::array<double,3> &acc_sol, std::array<double,3> &acc){

        }
    }

    namespace LunComponent {
        void apply( Debris::Debris &d, std::array<double,3> &acc_lun, std::array<double,3> &acc){

        }
    }

    namespace SRPComponent {
        void apply( Debris::Debris &d, std::array<double,3> &acc_srp, std::array<double,3> &acc){

        }
    }

    namespace DragComponent  {
        void apply( Debris::Debris &d, std::array<double,3> &acc_drag, std::array<double,3> &acc){

        }
    }
}