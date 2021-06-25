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