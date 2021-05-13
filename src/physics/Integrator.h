//
// Created by ubuntu on 13.05.21.
//

#pragma once
#include "../debris/DebrisContainer.h"

class Integrator {
public:
    Integrator(Debris::DebrisContainer &debris_arg)
    : debris (debris_arg)
    {};
    virtual ~Integrator();

    void integrate();
    void calculatePosition();
    void calculateVelocity();
    void calculateAccelaration();
private:
    double delta_t;
    Debris::DebrisContainer &debris;
public:
    double getDeltaT();
    void setDeltaT(double deltaT);
    Debris::DebrisContainer &getDebris();
    void setDebris(Debris::DebrisContainer &debris);
};