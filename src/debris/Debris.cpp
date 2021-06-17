//
// Created by Oliver on 12.05.21.
//

#include "Debris.h"
namespace Debris {

Debris::Debris()
= default;

Debris::Debris(const Debris& other)
{
    position = other.position;
    velocity = other.velocity;
    acc_t0 = other.acc_t0;
    acc_t1 = other.acc_t1;
    aom = other.aom;
    bc_inv = other.bc_inv;
}

Debris::~Debris() = default;
std::string Debris::toString()
{
    std::stringstream stream;
    stream << "Debris: X:" << IOUtils::to_string(position)
           << " ||X||: " << getHeight()
           << " v:" << IOUtils::to_string(velocity)
           << " ||v||: " << getSpeed()
           << " a0:" << IOUtils::to_string(acc_t0)
           << " ||a0||: " << getAccT0Norm()
           << " a1:" << IOUtils::to_string(acc_t1)
           << " ||X||: " << getHeight()
           << " ||v||: " << getSpeed();
    return stream.str();
}

double Debris::getHeight()
{
    return MathUtils::euclideanNorm(position);
}

double Debris::getSpeed()
{
    return MathUtils::euclideanNorm(velocity);
}

double Debris::getAccT0Norm()
{
    return MathUtils::euclideanNorm(acc_t0);
}

double Debris::getAccT1Norm()
{
    return MathUtils::euclideanNorm(acc_t1);
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

double Debris::getAom()
{
    return aom;
}

void Debris::setAom(double aom)
{
    Debris::aom = aom;
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