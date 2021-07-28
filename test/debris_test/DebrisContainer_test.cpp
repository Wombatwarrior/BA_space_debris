//
// Created by Oliver on 13.05.21.
//

#include "DebrisContainer_test.h"


TEST_F(GenericDebrisTests, RunSimulationWithDummyDebris)
{
    double current_time = file_input->getStartT();
    int iteration = 0;
    double time_till_write = file_input->getWriteDeltaT();
    // write starting conditions
    file_output->writeDebrisData(file_input->getStartT());
    while (current_time <= file_input->getEndT()) {
        iteration++;
        time_till_write -= file_input->getDeltaT();
        if (time_till_write <= 0) {
            integrator->integrate(true);
            file_output->writeDebrisData(current_time);
            time_till_write = file_input->getWriteDeltaT();
        } else {
            integrator->integrate();
        }
        current_time += file_input->getDeltaT();
    }
    // save end configuration
    file_output->writeDebrisData(file_input->getEndT());
}

