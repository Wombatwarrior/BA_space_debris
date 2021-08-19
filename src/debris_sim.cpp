//
// Created by Oliver on 12.05.21.
//

#include "debris_sim.h"

int main(int argc, char** argv)
{
    initSimulation(argc, argv);
    if (command_line->getRunThesisCalculations()){
        runThesisCalculations();
    }else{
        runSimulation();
    }
    return 0;
}


void initSimulation(int argc, char** argv)
{
    try {
        command_line = std::make_shared<CommandLineInput>(argc, argv);
        container = std::make_shared<Debris::DebrisContainer<Debris::Debris>>();
        file_input = std::make_shared<FileInput<Debris::DebrisContainer<Debris::Debris>>>(*container, command_line->getInputFilePath(),
            command_line->getInputFileType());
        file_output = std::make_shared<FileOutput<Debris::DebrisContainer<Debris::Debris>>>(*container, command_line->getOutputFilePath(),
            command_line->getOutputFileType(), file_input->getAccConfig());
        accumulator = std::make_shared<Acceleration::AccelerationAccumulator<Debris::DebrisContainer<Debris::Debris>>>(
            file_input->getAccConfig(), *container, file_input->getStartT(), *file_output);
        integrator = std::make_shared<Integrator<Debris::DebrisContainer<Debris::Debris>>>(*container, *accumulator,
            file_input->getDeltaT());
    }
    // if something went wrong with the command line parsing
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

void runSimulation()
{
    double current_time = file_input->getStartT();
    for (auto& d : container->getDebrisVector()) {
        std::cout << d.toString() << std::endl;
    }
    int iteration = 0;
    double time_till_write = file_input->getWriteDeltaT();
    // write starting conditions
    file_output->writeDebrisData(file_input->getStartT());
    while (current_time <= file_input->getEndT()) {
        iteration++;
        if (iteration % 3000 == 0) {
            for (auto& d : container->getDebrisVector()) {
                std::cout << iteration << " " << d.toString() << std::endl;
            }
        }
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
    for (auto& d : container->getDebrisVector()) {
        std::cout << d.toString() << std::endl;
    }
}



void runThesisCalculations(){
    std::cout << "Starting thesis calculations" << std::endl;
    std::cout << "Run delta t comparisons" << std::endl;
    // read the delta t input file
    file_input->setInputFilePath("input/delta_t.txt");
    file_input->setInputFileType(InputFile::TXT);
    file_input->readDebrisData();
    // used to keep track of current delta t
    double delta_t = file_input->getDeltaT();
    // set accumulator values that won't change for the delta t simulations
    accumulator->setConfig(file_input->getAccConfig());
    for (int i = 1; delta_t > 0.000001; ++i){
        std::cout << "Delta t: " << delta_t << std::endl << std::endl;
        // for each delta t we need new output files
        file_output = std::make_shared<FileOutput<Debris::DebrisContainer<Debris::Debris>>>(*container, "output/raw/delta_t" + std::to_string(i) + ".csv",
                                                                                            OutputFile::CSV, file_input->getAccConfig());
        // set values for this delta t simulation
        container->cleanDebrisVector();
        file_input->readDebrisData();
        file_input->setDeltaT(delta_t);
        accumulator->setFileOutput(*file_output);
        accumulator->setT(file_input->getStartT());
        integrator->setDeltaT(delta_t);
        //run the simulation for the current delta t
        runSimulation();
        // update delta t to halt of it's value
        file_input->setDeltaT(delta_t/2);
        delta_t=file_input->getDeltaT();
    }

    std::cout << "Calculations done" << std::endl;
}
