//
// Created by Oliver on 12.05.21.
//

#include "Debris.h"
namespace Debris {

Debris::Debris()
{
    position = { 0, 0, 0 };
    velocity = { 0, 0, 0 };
    acc_t0 = { 0, 0, 0 };
    acc_t1 = { 0, 0, 0 };
    bc_inv = 0;
}

Debris::Debris(const Debris& other)
{
    position = other.position;
    velocity = other.velocity;
    acc_t0 = other.acc_t0;
    acc_t1 = other.acc_t1;
    bc_inv = other.bc_inv;
}

Debris::~Debris() { }
std::string Debris::toString()
{
    std::stringstream stream;
    stream << "Debris: X:" << IOUtils::to_string(position)
           << " v:" << IOUtils::to_string(velocity)
           << " a0:" << IOUtils::to_string(acc_t0)
           << " a1:" << IOUtils::to_string(acc_t1)
           << " ||X||: " << getHeight()
           << " ||v||: " << getSpeed();
    return stream.str();
}

double Debris::getHeight()
{
    return std::sqrt(std::inner_product(position.begin(), position.end(),
        position.begin(), .0));
}

double Debris::getSpeed()
{
    return std::sqrt(std::inner_product(velocity.begin(), velocity.end(),
        velocity.begin(), .0));
}

double Debris::getAccT0Norm()
{
    return std::sqrt(
        std::inner_product(acc_t0.begin(), acc_t0.end(), acc_t0.begin(), .0));
}

double Debris::getAccT1Norm()
{
    return std::sqrt(
        std::inner_product(acc_t1.begin(), acc_t1.end(), acc_t1.begin(), .0));
}

std::array<double, 3>& Debris::getPosition()
{
    return position;
}

void Debris::setPosition(std::array<double, 3>& position)
{
    Debris::position = position;
}

std::array<double, 3>& Debris::getVelocity()
{
    return velocity;
}

void Debris::setVelocity(std::array<double, 3>& velocity)
{
    Debris::velocity = velocity;
}

std::array<double, 3>& Debris::getAccT0()
{
    return acc_t0;
}

void Debris::setAccT0(std::array<double, 3>& accT0)
{
    acc_t0 = accT0;
}

std::array<double, 3>& Debris::getAccT1()
{
    return acc_t1;
}

void Debris::setAccT1(std::array<double, 3>& accT1)
{
    acc_t1 = accT1;
}

double Debris::getBcInv()
{
    return bc_inv;
}

void Debris::setBcInv(double bcInv)
{
    bc_inv = bcInv;
}

} // namespace Debris