//
// Created by ubuntu on 12.05.21.
//

#pragma once
#include <array>
namespace Debris {
    class Debris {

    private:
        std::array<double,3> position;
        std::array<double,3> velocity;
        std::array<double,3> force_t0;
        std::array<double,3> force_t1;
    public:
    std::array<double, 3> &getPosition() ;
    void setPosition( std::array<double, 3> &position);
    std::array<double, 3> &getVelocity() ;
    void setVelocity( std::array<double, 3> &velocity);
    std::array<double, 3> &getForceT0() ;
    void setForceT0( std::array<double, 3> &forceT0);
    std::array<double, 3> &getForceT1() ;
    void setForceT1( std::array<double, 3> &forceT1);
    };
}