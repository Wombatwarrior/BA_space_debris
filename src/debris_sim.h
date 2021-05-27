//
// Created by ubuntu on 18.05.21.
//

#pragma once
// logging imports
#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/patternlayout.h"
#include "log4cxx/consoleappender.h"
#include "log4cxx/helpers/properties.h"
// project imports
#include "debris/include.h"
#include "physics/include.h"
#include "io/include.h"

#include <memory>

log4cxx::LoggerPtr logger;

std::shared_ptr<Debris::DebrisContainer> debris;
std::shared_ptr<CommandLineInput> command_line;
std::shared_ptr<FileInput> file_input;
std::shared_ptr<FileOutput> file_output;
std::shared_ptr<Acceleration::AccelerationAccumulator> accumulator;
std::shared_ptr<Integrator> integrator;


int main(int argc, char **argv);

void initLoggeer();

void initSimulation(int argc, char **argv);

void runSimulation();
