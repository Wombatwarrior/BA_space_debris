//
// Created by Oliver on 12.05.21.
//

#include "Debris.h"
namespace Debris {

    Debris::Debris() {
        position={0,0,0};
        velocity={0,0,0};
        acc_t0={0, 0, 0};
        acc_t1={0,0,0};
    }

    Debris::Debris(const Debris &other) {
        position=other.position;
        velocity=other.velocity;
        acc_t0=other.acc_t0;
        acc_t1=other.acc_t1;
    }

    Debris::~Debris() {

    }
    std::array<double, 3> &Debris::getPosition()  {
        return position;
    }

    void Debris::setPosition( const std::array<double, 3> &position) {
        Debris::position = position;
    }

     std::array<double, 3> &Debris::getVelocity()  {
        return velocity;
    }

    void Debris::setVelocity( const std::array<double, 3> &velocity) {
        Debris::velocity = velocity;
    }

     std::array<double, 3> &Debris::getAccT0()  {
        return acc_t0;
    }

    void Debris::setAccT0(const std::array<double, 3> &accT0) {
        acc_t0 = accT0;
    }

     std::array<double, 3> &Debris::getAccT1() {
        return acc_t1;
    }

    void Debris::setAccT1( const std::array<double, 3> &AccT1) {
        acc_t1 = AccT1;
    }
}