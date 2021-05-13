//
// Created by ubuntu on 13.05.21.
//

#pragma once
#include "Debris.h"
#include <vector>
namespace Debris {
    class DebrisContainer {
    public:
        DebrisContainer();

        virtual ~DebrisContainer();

        void addDebris(Debris &debris);
        void cleanDebrisVector();
    private:
        std::vector<Debris> debris_vector;
    public:
        std::vector<Debris> &getDebrisVector();
    };
}

