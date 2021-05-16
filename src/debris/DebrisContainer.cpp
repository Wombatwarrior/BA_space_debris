//
// Created by Oliver on 13.05.21.
//

#include "DebrisContainer.h"
namespace Debris {
    DebrisContainer::DebrisContainer() {}

    DebrisContainer::~DebrisContainer() {

    }

    void DebrisContainer::addDebris(Debris &debris) {
        debris_vector.push_back(debris);
    }

    void DebrisContainer::cleanDebrisVector() {

    }

    std::vector<Debris> &DebrisContainer::getDebrisVector() {
        return debris_vector;
    }
}