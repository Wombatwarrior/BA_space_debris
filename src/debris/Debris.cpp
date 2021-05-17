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
    std::string Debris::toString() {
        std::stringstream stream;
        stream << "Debris: X:" << IOUtils::array3DToString(position)
               << " v:" << IOUtils::array3DToString(velocity)
               << " a0:" << IOUtils::array3DToString(acc_t0)
               << " a1:" << IOUtils::array3DToString(acc_t1)
               << " ||X||: " << getHeight()
               << " ||v||: " << getSpeed();
        return stream.str();
    }

    double Debris::getHeight() {
        return std::sqrt(position[0]*position[0]+position[1]*position[1]+position[2]*position[2]);
    }

    double Debris::getSpeed() {
        return std::sqrt(velocity[0]*velocity[0]+velocity[1]*velocity[1]+velocity[2]*velocity[2]);
    }

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

     std::array<double, 3> &Debris::getAccT0()  {
        return acc_t0;
    }

    void Debris::setAccT0( std::array<double, 3> &accT0) {
        acc_t0 = accT0;
    }

    std::array<double, 3> &Debris::getAccT1()  {
        return acc_t1;
    }

    void Debris::setAccT1( std::array<double, 3> &accT1) {
        acc_t1 = accT1;
    }

}