//
// Created by ubuntu on 12.05.21.
//

#include "Debris.h"

namespace Debris {
    std::array<double, 3> &Debris::getPosition()  {
        return position;
    }

    void Debris::setPosition( std::array<double, 3> &position) {
        Debris::position = position;
    }

     std::array<double, 3> &Debris::getVelocity()  {
        return velocity;
    }

    void Debris::setVelocity( std::array<double, 3> &velocity) {
        Debris::velocity = velocity;
    }

     std::array<double, 3> &Debris::getForceT0()  {
        return force_t0;
    }

    void Debris::setForceT0( std::array<double, 3> &forceT0) {
        force_t0 = forceT0;
    }

     std::array<double, 3> &Debris::getForceT1() {
        return force_t1;
    }

    void Debris::setForceT1(std::array<double, 3> &forceT1) {
        force_t1 = forceT1;
    }
}