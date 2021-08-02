//
// Created by Oliver on 13.05.21.
//

#include "DebrisContainer.h"
namespace Debris {
DebrisContainer::DebrisContainer() = default;

DebrisContainer::~DebrisContainer() = default;

void DebrisContainer::addDebris(const Debris& debris)
{
    debris_vector.push_back(debris);
}

void DebrisContainer::cleanDebrisVector()
{
    debris_vector.clear();
}

const std::vector<Debris>& DebrisContainer::getDebrisVector() const
{
    return debris_vector;
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