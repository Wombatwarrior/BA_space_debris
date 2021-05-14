//
// Created by Oliver on 12.05.21.
//

#include "debris/DebrisContainer.h"
#include "physics/Acceleration.h"
#include "physics/Integrator.h"

int main(){
    Debris::DebrisContainer c;
    Debris::Debris d;
    d.setPosition({1,2,3});
    c.addDebris(d);
    std::array<bool,8> config{true,false,false,false,false,false,false,false};
    Acceleration::AccelerationAccumulator ac(config, c);
    ac.applyComponents();
    Integrator i(c);
    i.setDeltaT(0.5);
    i.integrate();
}