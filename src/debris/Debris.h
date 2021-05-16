//
// Created by Oliver on 12.05.21.
//

#pragma once
#include <array>
#include <sstream>
#include "../io/IOUtils.h"
namespace Debris {
    class Debris {
    public:
        Debris();

        Debris(const Debris &other);

        virtual ~Debris();

        std::string toString();
    private:
        std::array<double,3> position;
        std::array<double,3> velocity;
        std::array<double,3> acc_t0;
        std::array<double,3> acc_t1;
    public:
        std::array<double, 3> &getPosition() ;
        void setPosition( std::array<double, 3> &position);
        std::array<double, 3> &getVelocity() ;
        void setVelocity( std::array<double, 3> &velocity);
        std::array<double, 3> &getAccT0() ;
        void setAccT0( std::array<double, 3> &accT0);
        std::array<double, 3> &getAccT1() ;
        void setAccT1( std::array<double, 3> &accT1);
    };
}