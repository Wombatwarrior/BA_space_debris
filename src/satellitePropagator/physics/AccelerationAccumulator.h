//
// Created by Oliver on 12.05.21.
//

#pragma once
#include <cmath>

#include <array>
#include <numeric>

#include "Constants.h"
#include "satellitePropagator/debris/DebrisContainer.h"
#include "satellitePropagator/io/FileOutput.h"
#include "satellitePropagator/physics/AccelerationComponents/include.h"

/**
 * @namespace Acceleration
 *
 * @brief Contains classes and functions to calculate accelerations for
 * Debris::Debris objects
 *
 * The implementations are following the equations in <a href="Math.pdf"> math reference</a>
 *
 */
namespace Acceleration {
/**
 * @class AccelerationAccumulator
 *
 * @brief Accumulates all accelerations of the
 * Acceleration::AccelerationComponent specified by the #config vector
 */
template <class Container,class D>
class AccelerationAccumulator {
public:
    /**
     * @brief Default constructor
     *
     * creates ann AccelerationAccumulator object with all values initialized to zero
     */
    AccelerationAccumulator();
    /**
     * @brief Constructor creates a new Acceleration::AcceleratorAccumulator
     * object
     *
     * @param config_arg The 8D bool vector encoding the
     * Acceleration::AccelerationComponent to apply in the simulation. The Order
     * of flags is [::KEP, ::J2, ::C22, ::S22, ::SOL, ::LUN, ::SRP, ::DRAG]
     * @param container Reference to the Container object holding
     * the Debris::Debris objects to apply acceleration to
     * @param t_arg Current time
     * @param file_output_arg Reference to the FileOutput object used for output of the acceleration values during computation
     */
    AccelerationAccumulator(const std::array<bool, 8>& config_arg,
        Container& container,
        double t_arg,
        FileOutput<Container, D>& file_output_arg)
        : config(config_arg)
        , debris(&container)
        , t(t_arg)
        , file_output(&file_output_arg) {};

    /**
     * @brief Default destructor
     *
     * Destroys the Acceleration::AccelerationAccumulator object
     */
    ~AccelerationAccumulator();

    /**
     * @brief Applies all Acceleration::AccelerationComponent specified by
     * #config
     *
     * Loops over all Debris::Debris objects in #debris.
     * Checks if the corresponding flag in the #config vector is set to true and
     * calls the apply() functions. Sets the #Debris::Debris::acc_t1 value of
     * every Debris::Debris object.
     *
     * The possible apply() functions are:
     * - Acceleration::KepComponent::apply() if #config[Acceleration::KEP]
     * - Acceleration::J2Component::apply() if #config[Acceleration::J2]
     * - Acceleration::C22Component::apply() if #config[Acceleration::C22]
     * - Acceleration::S22Component::apply() if #config[Acceleration::S22]
     * - Acceleration::SolComponent::apply() if #config[Acceleration::SOL]
     * - Acceleration::LunComponent::apply() if #config[Acceleration::LUN]
     * - Acceleration::SRPComponent::apply() if #config[Acceleration::SRP]
     * - Acceleration::DragComponent::apply() if #config[Acceleration::DRAG]
     *
     */
    void applyComponents() const;

    /**
     * @brief does the same as #applyComponents() plus output
     *
     * Calculates the needed acceleration components and writes the value for each one to a csv file
     */
    void applyAmdWriteComponents() const;

private:
    /**
     * @brief 8D bool vector encoding the Acceleration::AccelerationComponent to
     * apply in the simulation.
     *
     * 8D bool vector encoding the Acceleration::AccelerationComponent to apply
     * in the simulation. The Order of flags is
     * - #Acceleration::KEP
     * - #Acceleration::J2
     * - #Acceleration::C22
     * - #Acceleration::S22
     * - #Acceleration::SOL
     * - #Acceleration::LUN
     * - #Acceleration::SRP
     * - #Acceleration::DRAG
     */
    std::array<bool, 8> config {};
    Container*
        debris
        = nullptr; /**< Reference to the Container object holding the
             Debris::Debris objects to apply acceleration to*/
    double t = 0; /**< current time*/
    FileOutput<Container, D>* file_output = nullptr; /**< used to write detailed output data during calculations */
public:
    /**
     * @brief Getter function for #config
     *
     * @return Value of #config
     */
    [[nodiscard]] const std::array<bool, 8>& getConfig() const;
    std::array<bool, 8>& getConfig();

    /**
     * @brief Setter function for #config
     *
     * @param config New value of #config
     */
    void setConfig(const std::array<bool, 8>& config);

    /**
     * @brief Getter function for #debris
     *
     * @return Value of #debris
     */
    [[nodiscard]] const Container& getDebris() const;
    Container& getDebris();

    /**
     * @brief Setter function for #debris
     *
     * @param debris New value of #debris
     */
    void setDebris(Container& debris);

    /**
     * @brief Getter function for #t
     *
     * @return Value of #t
     */
    [[nodiscard]] double getT() const;

    /**
     * @brief Setter function for #t
     *
     * @param t New value of #t
     */
    void setT(double t);

    /**
     * @brief Getter function for #file_output
     *
     * @return Value of #file_output
     */
    [[nodiscard]] const FileOutput<Container, D>& getFileOutput() const;
    FileOutput<Container, D>& getFileOutput();

    /**
     * @brief Setter function for #file_output
     *
     * @param fileOutput New value of #file_output
     */
    void setFileOutput(FileOutput<Container, D>& fileOutput);
};
} // namespace Acceleration

//
// Created by Oliver on 12.05.21.
// based on https://www.overleaf.com/project/608918003323352d4d3ceb55
// equations. for reference
namespace Acceleration {

template <class Container,class D>
AccelerationAccumulator<Container, D>::AccelerationAccumulator() = default;

template <class Container, class D>
AccelerationAccumulator<Container, D>::~AccelerationAccumulator() = default;

template <class Container, class D>
void AccelerationAccumulator<Container, D>::applyComponents() const
{
    // will be modified by the apply functions
    std::array<double, 3> new_acc_total { 0, 0, 0 };
    std::array<double, 3> new_acc_component { 0, 0, 0 };
    double d_srp = 0;
    // are constant for this time step
    double c_term;
    double s_term;
    std::array<double, 6> sun_params {};
    // setup only needed for SolComponent and SRPComponent
    if (config[SOL] || config[SRP]) {
        sun_params = SolComponent::setUp(t);
    }
    std::array<double, 6> moon_params {};
    // setup only needed for LunComponent
    if (config[LUN]) {
        moon_params = LunComponent::setUp(t);
    }
    // setup only needed for C22Component and S22Component
    if (config[C22] || config[S22]) {
        // Eq 15
        c_term = std::cos((Physics::THETA_G + Physics::NU_EARTH * t) * Physics::RAD_FACTOR);
        s_term = std::sin((Physics::THETA_G + Physics::NU_EARTH * t) * Physics::RAD_FACTOR);
    }

    for (auto &d : *debris) {
        new_acc_total[0] = 0;
        new_acc_total[1] = 0;
        new_acc_total[2] = 0;
        new_acc_component[0] = 0;
        new_acc_component[1] = 0;
        new_acc_component[2] = 0;
        d_srp = 0;
        // Eq 1
        if (config[KEP]) {
            KepComponent::apply(d, new_acc_component, new_acc_total);
        }
        if (config[J2]) {
            J2Component::apply(d, new_acc_component, new_acc_total);
        }
        // if we want to calculate both C22 and S22 we can share many of the
        // calculation steps
        if (config[C22] && config[S22]) {
            C22S22Component::apply(d, c_term, s_term, new_acc_component,
                new_acc_total);
        } // if only one of the two should be calculated we only calculate the
        // needed one
        else {
            if (config[C22]) {
                C22Component::apply(d, c_term, s_term, new_acc_component,
                    new_acc_total);
            }
            if (config[S22]) {
                S22Component::apply(d, c_term, s_term, new_acc_component,
                    new_acc_total);
            }
        }
        if (config[SOL]) {
            SolComponent::apply(d, d_srp, sun_params, new_acc_component, new_acc_total);
        }
        if (config[LUN]) {
            LunComponent::apply(d, moon_params, new_acc_component, new_acc_total);
        }
        if (config[SRP]) {
            SRPComponent::apply(d, d_srp, sun_params, new_acc_component, new_acc_total);
        }
        if (config[DRAG]) {
            DragComponent::apply(d, new_acc_component, new_acc_total);
        }
        d.setAccT1(new_acc_total);
    }
}

template <class Container, class D>
void AccelerationAccumulator<Container, D>::applyAmdWriteComponents() const
{
    // will be modified by the apply functions
    std::array<double, 3> new_acc_total { 0, 0, 0 };
    std::array<double, 3> new_acc_component { 0, 0, 0 };
    double d_srp = 0;
    // are constant for this time step
    double c_term;
    double s_term;
    std::array<double, 6> sun_params {};
    // setup only needed for SolComponent and SRPComponent
    if (config[SOL] || config[SRP]) {
        sun_params = SolComponent::setUp(t);
    }
    std::array<double, 6> moon_params {};
    // setup only needed for LunComponent
    if (config[LUN]) {
        moon_params = LunComponent::setUp(t);
    }
    // setup only needed for C22Component and S22Component
    if (config[C22] || config[S22]) {
        // Eq 15
        c_term = std::cos((Physics::THETA_G + Physics::NU_EARTH * t) * Physics::RAD_FACTOR);
        s_term = std::sin((Physics::THETA_G + Physics::NU_EARTH * t) * Physics::RAD_FACTOR);
    }

    for (auto &d : *debris) {
        // start a new line o data for each particle
        file_output->writeAcc_start(t);
        new_acc_total[0] = 0;
        new_acc_total[1] = 0;
        new_acc_total[2] = 0;
        new_acc_component[0] = 0;
        new_acc_component[1] = 0;
        new_acc_component[2] = 0;
        // Eq 1
        if (config[KEP]) {
            KepComponent::apply(d, new_acc_component, new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[J2]) {
            J2Component::apply(d, new_acc_component, new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[C22]) {
            C22Component::apply(d, c_term, s_term, new_acc_component,
                new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[S22]) {
            S22Component::apply(d, c_term, s_term, new_acc_component,
                new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[SOL]) {
            SolComponent::apply(d, d_srp, sun_params, new_acc_component, new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[LUN]) {
            LunComponent::apply(d, moon_params, new_acc_component, new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[SRP]) {
            SRPComponent::apply(d, d_srp, sun_params, new_acc_component, new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        if (config[DRAG]) {
            DragComponent::apply(d, new_acc_component, new_acc_total);
            file_output->writeAcc_value(new_acc_component);
        }
        d.setAccT1(new_acc_total);
        file_output->writeAcc_end(new_acc_total);
    }
}

template <class Container, class D>
const std::array<bool, 8>& AccelerationAccumulator<Container, D>::getConfig() const
{
    return config;
}

template <class Container, class D>
std::array<bool, 8>& AccelerationAccumulator<Container, D>::getConfig()
{
    return config;
}
template <class Container, class D>
void AccelerationAccumulator<Container, D>::setConfig(const std::array<bool, 8>& config)
{
    AccelerationAccumulator<Container, D>::config = config;
}

template <class Container, class D>
const Container& AccelerationAccumulator<Container, D>::getDebris() const
{
    return *debris;
}

template <class Container, class D>
Container& AccelerationAccumulator<Container, D>::getDebris()
{
    return *debris;
}
template <class Container, class D>
void AccelerationAccumulator<Container, D>::setDebris(Container& debris)
{
    AccelerationAccumulator<Container, D>::debris = &debris;
}

template <class Container, class D>
double AccelerationAccumulator<Container, D>::getT() const
{
    return t;
}

template <class Container, class D>
void AccelerationAccumulator<Container, D>::setT(double t)
{
    AccelerationAccumulator<Container, D>::t = t;
}

template <class Container, class D>
const FileOutput<Container, D>& AccelerationAccumulator<Container, D>::getFileOutput() const
{
    return *file_output;
}

template <class Container, class D>
FileOutput<Container, D>& AccelerationAccumulator<Container, D>::getFileOutput()
{
    return *file_output;
}

template <class Container, class D>
void AccelerationAccumulator<Container, D>::setFileOutput(FileOutput<Container, D>& fileOutput)
{
    file_output = &fileOutput;
}

} // namespace Acceleration