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

std::string Debris::toString() const
{
    std::stringstream stream;
    stream << "Debris: X:" << IOUtils::to_string(position)
           << ", ||X||: " << getHeight()
           << ", v:" << IOUtils::to_string(velocity)
           << ", ||v||: " << getSpeed()
           << ", a0:" << IOUtils::to_string(acc_t0)
           << ", ||a0||: " << getAccT0Norm()
           << ", a1:" << IOUtils::to_string(acc_t1)
           << ", ||a!||: " << getAccT1Norm()
           << ", aom: " << aom
           << ", bc_inv: " << bc_inv;
    return stream.str();
}

double Debris::getHeight() const
{
    return MathUtils::euclideanNorm(position);
}

double Debris::getSpeed() const
{
    return MathUtils::euclideanNorm(velocity);
}

double Debris::getAccT0Norm() const
{
    return MathUtils::euclideanNorm(acc_t0);
}

double Debris::getAccT1Norm() const
{
    return MathUtils::euclideanNorm(acc_t1);
}

const std::array<double, 3>& Debris::getPosition() const
{
    return position;
}

std::array<double, 3>& Debris::getPosition()
{
    return position;
}

void Debris::setPosition(const std::array<double, 3>& position)
{
    Debris::position = position;
}

const std::array<double, 3>& Debris::getVelocity() const
{
    return velocity;
}

std::array<double, 3>& Debris::getVelocity()
{
    return velocity;
}

void Debris::setVelocity(const std::array<double, 3>& velocity)
{
    Debris::velocity = velocity;
}

const std::array<double, 3>& Debris::getAccT0() const
{
    return acc_t0;
}

std::array<double, 3>& Debris::getAccT0()
{
    return acc_t0;
}

void Debris::setAccT0(const std::array<double, 3>& accT0)
{
    acc_t0 = accT0;
}

const std::array<double, 3>& Debris::getAccT1() const
{
    return acc_t1;
}

std::array<double, 3>& Debris::getAccT1()
{
    return acc_t1;
}

void Debris::setAccT1(const std::array<double, 3>& accT1)
{
    acc_t1 = accT1;
}

double Debris::getAom() const
{
    return aom;
}

void Debris::setAom(const double aom)
{
    Debris::aom = aom;
}

double Debris::getBcInv() const
{
    return bc_inv;
}

void Debris::setBcInv(const double bcInv)
{
    bc_inv = bcInv;
}

} // namespace Debris