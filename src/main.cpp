//
// Created by Oliver on 12.05.21.
//

#include "debris/DebrisContainer.h"
#include "physics/Acceleration.h"
#include "physics/Integrator.h"
#include "io/IOUtils.h"

int main(){
    Debris::DebrisContainer c;
    Debris::Debris d;
    d.setPosition({1,2,3});
    c.addDebris(d);
    Debris::Debris &dr=c.getDebrisVector()[0];
    std::array<bool,8> config{true,false,false,false,false,false,false,false};
    std::cout << "start" << std::endl;
    std::cout << Output::array3DToString(dr.getPosition()) << std::endl;
    std::cout << Output::array3DToString(dr.getVelocity()) << std::endl;
    std::cout << Output::array3DToString(dr.getAccT0()) << std::endl;
    Acceleration::AccelerationAccumulator ac(config, c);
    ac.applyComponents();
    std::cout << "acc" << std::endl;
    std::cout << Output::array3DToString(dr.getPosition()) << std::endl;
    std::cout << Output::array3DToString(dr.getVelocity()) << std::endl;
    std::cout << Output::array3DToString(dr.getAccT0()) << std::endl;
    Integrator i(c);
    i.setDeltaT(0.5);
    i.integrate();
    std::cout << "end" << std::endl;
    std::cout << Output::array3DToString(dr.getPosition()) << std::endl;
    std::cout << Output::array3DToString(dr.getVelocity()) << std::endl;
    std::cout << Output::array3DToString(dr.getAccT0()) << std::endl;
}