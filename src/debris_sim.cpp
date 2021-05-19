//
// Created by Oliver on 12.05.21.
//

#include "debris_sim.h"

int main(int argc, char **argv){
    initLoggeer();
    initSimulation(argc, argv);
    runSimulation();
    return 0;
}

void initLoggeer(){
    log4cxx::helpers::Properties logging_properties;
    logging_properties.setProperty("log4j.rootLogger", "INFO, A1");
    logging_properties.setProperty("log4j.appender.A1", "org.apache.log4j.ConsoleAppender");
    logging_properties.setProperty("log4j.appender.A1.layout.ConversionPattern", "%-5p %c - %m%n");
    logging_properties.setProperty("log4j.appender.A1.layout", "org.apache.log4j.PatternLayout");
    log4cxx::PropertyConfigurator::configure(logging_properties);
    logger = logger = log4cxx::Logger::getLogger("DebrisMainLogger");
}

void initSimulation(int argc, char **argv){
    command_line = std::make_shared<CommandLineInput>(argc,argv);
    debris = std::make_shared<Debris::DebrisContainer>();
    file_input = std::make_shared<FileInput>(*debris, command_line->getInputFileName(), command_line->getInputFileType());
    accumulator = std::make_shared<Acceleration::AccelerationAccumulator>(file_input->getAccConfig(), *debris);
    integrator = std::make_shared<Integrator>(*debris, *accumulator, file_input->getDeltaT());
}

void runSimulation(){
    double current_time=file_input->getStartT();
    for (auto &d : debris->getDebrisVector()){
        LOG4CXX_INFO(logger, d.toString());
    }
    int iteration = 0;
    while (current_time <= file_input->getEndT()){
        iteration++;
        if (iteration % 3000 == 0){
            for (auto &d : debris->getDebrisVector()){
                LOG4CXX_DEBUG(logger, iteration << d.toString());
            }
        }
        integrator->integrate();
        current_time += file_input->getDeltaT();
    }
    for (auto &d : debris->getDebrisVector()){
        LOG4CXX_INFO(logger, d.toString());
    }
}
