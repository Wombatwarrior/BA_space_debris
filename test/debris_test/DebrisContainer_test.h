//
// Created by Oliver on 13.05.21.
//

#pragma once
#include "gtest/gtest.h"
#include "satellitePropagator/debris/include.h"
#include "satellitePropagator/io/include.h"
#include "satellitePropagator/physics/include.h"
#include <memory>




class GenericDebrisTests : public ::testing::Test {
protected:
    class DummyDebris{
    private:
        std::array<double, 3> position {};
        std::array<double, 3> velocity {};
        std::array<double, 3> acc_t0 {};
        std::array<double, 3> acc_t1 {};
        double bc_inv = 0;
        double aom = 0;
    public:
        DummyDebris()=default;

        DummyDebris(const DummyDebris& other)
        {
            position = other.position;
            velocity = other.velocity;
            acc_t0 = other.acc_t0;
            acc_t1 = other.acc_t1;
            aom = other.aom;
            bc_inv = other.bc_inv;
        }

        ~DummyDebris() = default;

        std::string toString() const
        {
            std::stringstream stream;
            stream << "DummyDebris: X:" << IOUtils::to_string(position)
                   << " ||X||: " << getHeight()
                   << " v:" << IOUtils::to_string(velocity)
                   << " ||v||: " << getSpeed()
                   << " a0:" << IOUtils::to_string(acc_t0)
                   << " ||a0||: " << getAccT0Norm()
                   << " a1:" << IOUtils::to_string(acc_t1)
                   << " ||X||: " << getHeight()
                   << " ||v||: " << getSpeed();
            return stream.str();
        }

        double getHeight() const
        {
            return MathUtils::euclideanNorm(position);
        }

        double getSpeed() const
        {
            return MathUtils::euclideanNorm(velocity);
        }

        double getAccT0Norm() const
        {
            return MathUtils::euclideanNorm(acc_t0);
        }

        double getAccT1Norm() const
        {
            return MathUtils::euclideanNorm(acc_t1);
        }

        const std::array<double, 3>& getPosition() const
        {
            return position;
        }

        std::array<double, 3>& getPosition()
        {
            return position;
        }

        void setPosition(const std::array<double, 3>& position)
        {
            DummyDebris::position = position;
        }

        const std::array<double, 3>& getVelocity() const
        {
            return velocity;
        }

        std::array<double, 3>& getVelocity()
        {
            return velocity;
        }

        void setVelocity(const std::array<double, 3>& velocity)
        {
            DummyDebris::velocity = velocity;
        }

        const std::array<double, 3>& getAccT0() const
        {
            return acc_t0;
        }

        std::array<double, 3>& getAccT0()
        {
            return acc_t0;
        }

        void setAccT0(const std::array<double, 3>& accT0)
        {
            acc_t0 = accT0;
        }

        const std::array<double, 3>& getAccT1() const
        {
            return acc_t1;
        }

        std::array<double, 3>& getAccT1()
        {
            return acc_t1;
        }

        void setAccT1(const std::array<double, 3>& accT1)
        {
            acc_t1 = accT1;
        }

        double getAom() const
        {
            return aom;
        }

        void setAom(const double aom)
        {
            DummyDebris::aom = aom;
        }

        double getBcInv() const
        {
            return bc_inv;
        }

        void setBcInv(const double bcInv)
        {
            bc_inv = bcInv;
        }

    };
    std::shared_ptr<Debris::DebrisContainer<DummyDebris>> container;
    std::shared_ptr<CommandLineInput> command_line;
    std::shared_ptr<FileInput<Debris::DebrisContainer<DummyDebris>>> file_input;
    std::shared_ptr<FileOutput<Debris::DebrisContainer<DummyDebris>>> file_output;
    std::shared_ptr<Acceleration::AccelerationAccumulator<Debris::DebrisContainer<DummyDebris>>> accumulator;
    std::shared_ptr<Integrator<Debris::DebrisContainer<DummyDebris>>> integrator;

    virtual void SetUp()
    {
        char *argv[] ={
                (char*)"test",
                (char*)"../test_files/test_input.txt",
                (char*)"-o",
                (char*)"../test_files/test_output.csv",
                nullptr
        };
        command_line = std::make_shared<CommandLineInput>(4, argv);
        container = std::make_shared<Debris::DebrisContainer<DummyDebris>>();
        file_input = std::make_shared<FileInput<Debris::DebrisContainer<DummyDebris>>>(*container, command_line->getInputFilePath(),
                command_line->getInputFileType());
        file_output = std::make_shared<FileOutput<Debris::DebrisContainer<DummyDebris>>>(*container, command_line->getOutputFilePath(),
                command_line->getOutputFileType(), file_input->getAccConfig());
        accumulator = std::make_shared<Acceleration::AccelerationAccumulator<Debris::DebrisContainer<DummyDebris>>>(
                file_input->getAccConfig(), *container, file_input->getStartT(), *file_output);
        integrator = std::make_shared<Integrator<Debris::DebrisContainer<DummyDebris>>>(*container, *accumulator,
                file_input->getDeltaT());


        double current_time = file_input->getStartT();
        int iteration = 0;
        double time_till_write = file_input->getWriteDeltaT();
        // write starting conditions
        file_output->writeDebrisData(file_input->getStartT());
        std::cout << "Starting simulation" << std::endl;
        for (auto& d : container->getDebrisVector()) {
            std::cout << d.toString() << std::endl;
        }
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
        std::cout << "Simulation completed" << std::endl;
        for (auto& d : container->getDebrisVector()) {
            std::cout << d.toString() << std::endl;
        }
    }
};
