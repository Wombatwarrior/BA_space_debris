//
// Created by Oliver on 13.05.21.
//

#include "Integrator_test.h"

// setup taylor integrator and print it to check if the state etc. are correct
TEST_F(CompareWithHeyokaTests, showTaylorIntegrator)
{
    std::cout << *ta_total << std::endl;

    for(int i = 0; i < 8; ++i){
        std::cout << *ta_components[i] << std::endl;
    }
}

// compare calculated values of KepComponent
TEST_F(CompareWithHeyokaTests, compareKep) {
    // set some test debris values and add them to the Integrators
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        i_components[Acceleration::KEP]->getDebris().addDebris(d);
    }
}
// compare calculated values of J2Component
TEST_F(CompareWithHeyokaTests, compareJ2)
{
    // set some test debris values
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        i_components[Acceleration::KEP]->getDebris().addDebris(d);
    }

}
// compare calculated values of C22Component
TEST_F(CompareWithHeyokaTests, compareC22)
{
    // set some test debris values
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        i_components[Acceleration::KEP]->getDebris().addDebris(d);
    }

}
// compare calculated values of S22Component
TEST_F(CompareWithHeyokaTests, compareS22)
{
    // set some test debris values
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        i_components[Acceleration::KEP]->getDebris().addDebris(d);
    }

}
// compare calculated values of LunComponent
TEST_F(CompareWithHeyokaTests, compareLun)
{
    // set some test debris values
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        i_components[Acceleration::KEP]->getDebris().addDebris(d);
        i_components[Acceleration::KEP]->getDebris().addDebris(d);
    }

}
// compare calculated values of SolComponent
TEST_F(CompareWithHeyokaTests, compareSol)
{
    // set some test debris values
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        i_components[Acceleration::KEP]->getDebris().addDebris(d);
    }

}
// compare calculated values of SRPComponent
TEST_F(CompareWithHeyokaTests, compareSRP)
{
    // set some test debris values
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        i_components[Acceleration::KEP]->getDebris().addDebris(d);
    }

}
// compare calculated values of DragComponent
TEST_F(CompareWithHeyokaTests, compareDrag)
{
    // set some test debris values
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        i_components[Acceleration::KEP]->getDebris().addDebris(d);
    }

}
// compare calculated values of all Components
TEST_F(CompareWithHeyokaTests, compareTotal)
{
    // set some test debris values
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        i_components[Acceleration::KEP]->getDebris().addDebris(d);
    }

}
