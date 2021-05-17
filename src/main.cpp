//
// Created by Oliver on 12.05.21.
//

#include "debris/include.h"
#include "physics/include.h"
#include "io/include.h"

int main(int argc, char **argv){
    std::cout << "start" << std::endl;
    std::cout << "debris..." << std::endl;
    Debris::DebrisContainer debris;
    std::cout << "command line..." << std::endl;
    CommandLineInput command_line(argc,argv);
    std::cout << "file input..." << std::endl;
    FileInput file_input(debris, command_line.getInputFileName(), command_line.getInputFileType());
    std::cout << "accumulator..." << std::endl;
    Acceleration::AccelerationAccumulator accumulator(file_input.getAccConfig(), debris);
    std::cout << "integrator..." << std::endl;
    Integrator integrator(debris, accumulator, file_input.getDeltaT());
    double current_time=file_input.getStartT();
    for (auto &d : debris.getDebrisVector()){
        std::cout << d.toString() << std::endl;
    }
    int iteration = 0;
    while (current_time <= file_input.getEndT()){
        iteration++;
        if (iteration % 3000 == 0){
            for (auto &d : debris.getDebrisVector()){
                std::cout << iteration << ": " << d.toString() << std::endl;
            }
        }
        integrator.integrate();
        current_time += file_input.getDeltaT();
    }
    for (auto &d : debris.getDebrisVector()){
        std::cout << d.toString() << std::endl;
    }
    std::cout << "end" << std::endl;
    return 0;
}