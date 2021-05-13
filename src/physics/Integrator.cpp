//
// Created by ubuntu on 13.05.21.
//

#include "Integrator.h"

Integrator::~Integrator() {

}
void Integrator::integrate(){

}

void Integrator::integrateLocation(){

}

void Integrator::integrateVelocity(){

}

void Integrator::integrateForce(){

}

double Integrator::getDeltaT()  {
    return delta_t;
}

void Integrator::setDeltaT(double deltaT) {
    delta_t = deltaT;
}

Debris::DebrisContainer &Integrator::getDebris(){
    return debris;
}

void Integrator::setDebris(Debris::DebrisContainer &debris) {
    Integrator::debris = debris;
}
