//
// Created by ubuntu on 18.05.21.
//

#pragma once
// logging imports
#include "log4cxx/consoleappender.h"
#include "log4cxx/helpers/properties.h"
#include "log4cxx/logger.h"
#include "log4cxx/patternlayout.h"
#include "log4cxx/propertyconfigurator.h"
// project imports
#include <memory>

#include "satellitePropagator/debris/include.h"
#include "satellitePropagator/io/include.h"
#include "satellitePropagator/physics/include.h"

log4cxx::LoggerPtr logger;

std::shared_ptr<Debris::DebrisContainer<Debris::Debris>> debris;
std::shared_ptr<CommandLineInput<Debris::Debris>> command_line;
std::shared_ptr<FileInput<Debris::DebrisContainer<Debris::Debris>,Debris::Debris>> file_input;
std::shared_ptr<FileOutput<Debris::DebrisContainer<Debris::Debris>,Debris::Debris>> file_output;
std::shared_ptr<Acceleration::AccelerationAccumulator<Debris::DebrisContainer<Debris::Debris>,Debris::Debris>> accumulator;
std::shared_ptr<Integrator<Debris::DebrisContainer<Debris::Debris>,Debris::Debris>> integrator;

int main(int argc, char** argv);

void initLogger();

void initSimulation(int argc, char** argv);

void runSimulation();
