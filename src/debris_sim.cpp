//
// Created by Oliver on 12.05.21.
//

#include "debris_sim.h"

int main(int argc, char** argv)
{
    initLoggeer();
    initSimulation(argc, argv);
    runSimulation();
    return 0;
}

void initLoggeer()
{
    log4cxx::helpers::Properties logging_properties;
    logging_properties.setProperty("log4j.rootLogger", "INFO, A1");
    logging_properties.setProperty("log4j.appender.A1",
        "org.apache.log4j.ConsoleAppender");
    logging_properties.setProperty("log4j.appender.A1.layout.ConversionPattern",
        "%-5p %c - %m%n");
    logging_properties.setProperty("log4j.appender.A1.layout",
        "org.apache.log4j.PatternLayout");
    log4cxx::PropertyConfigurator::configure(logging_properties);
    logger = logger = log4cxx::Logger::getLogger("DebrisMainLogger");
}

void initSimulation(int argc, char** argv)
{
    try {
        command_line = std::make_shared<CommandLineInput>(argc, argv);
        debris = std::make_shared<Debris::DebrisContainer>();
        file_input = std::make_shared<FileInput>(*debris, command_line->getInputFileName(),
            command_line->getInputFileType());
        file_output = std::make_shared<FileOutput>(*debris, command_line->getOutputFileName(),
            command_line->getOutputFileType());
        accumulator = std::make_shared<Acceleration::AccelerationAccumulator>(
            file_input->getAccConfig(), *debris, file_input->getStartT());
        integrator = std::make_shared<Integrator>(*debris, *accumulator,
            file_input->getDeltaT());
    }
    // if something went wrong with the command line parsing
    catch (std::invalid_argument& e) {
        LOG4CXX_FATAL(logger, e.what());
        exit(1);
    }
}

void runSimulation()
{
    double current_time = file_input->getStartT();
    for (auto& d : debris->getDebrisVector()) {
        LOG4CXX_INFO(logger, d.toString());
    }
    int iteration = 0;
    double time_till_write = file_input->getWriteDeltaT();
    // write starting conditions
    file_output->writeDebrisData(file_input->getStartT());
    while (current_time <= file_input->getEndT()) {
        iteration++;
        if (iteration % 3000 == 0) {
            for (auto& d : debris->getDebrisVector()) {
                LOG4CXX_DEBUG(logger, iteration << d.toString());
            }
        }
        integrator->integrate();
        time_till_write -= file_input->getDeltaT();
        if (time_till_write <= 0) {
            file_output->writeDebrisData(current_time);
            time_till_write = file_input->getWriteDeltaT();
        }
        current_time += file_input->getDeltaT();
    }
    // save end configuration
    file_output->writeDebrisData(file_input->getEndT());
    for (auto& d : debris->getDebrisVector()) {
        LOG4CXX_INFO(logger, d.toString());
    }
}
