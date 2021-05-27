//
// Created by Oliver on 13.05.21.
//

#include "DebrisContainer.h"
namespace Debris {
DebrisContainer::DebrisContainer() { }

DebrisContainer::~DebrisContainer() { }

void DebrisContainer::addDebris(Debris& debris)
{
    debris_vector.push_back(debris);
}

void DebrisContainer::cleanDebrisVector() { }

void DebrisContainer::shiftAcceleration()
{
    std::array<double, 3> new_acc { 0, 0, 0 };
    for (auto& d : debris_vector) {
        d.setAccT0(d.getAccT1());
        d.setAccT1(new_acc);
    }
}

std::vector<Debris>& DebrisContainer::getDebrisVector()
{
    return debris_vector;
}

void DebrisContainer::setDebrisVector(std::vector<Debris>& debrisVector)
{
    debris_vector = debrisVector;
}
} // namespace Debris