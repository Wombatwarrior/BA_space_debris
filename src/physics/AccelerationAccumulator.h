//
// Created by Oliver on 12.05.21.
//

#pragma once
#include <cmath>

#include <array>
#include <numeric>

#include "AccelerationComponents/include.h"
#include "Constants.h"
#include "debris/DebrisContainer.h"
#include "io/FileOutput.h"

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
 * @brief Enumerates the different components of the total acceleration
 */
enum AccelerationComponent {
    KEP, /**< Kepler: %Acceleration due to earth gravity. Assuming the earth as a
        point mass <a href="Math.pdf#page=1"> math reference subsection 1.1</a>*/
    J2, /**< J2: %Acceleration due to earth gravity. Taking in account the earth
         is neither a point mass nor a homogenous spherical mass <a href="Math.pdf#page=2"> math reference subsection 1.2</a>*/
    C22, /**< C22: %Acceleration due to earth gravity. Taking in account the
        earth is neither a point mass nor not a homogenous spherical mass <a href="Math.pdf#page=3"> math reference subsection 1.3</a>*/
    S22, /**< S22: %Acceleration due to earth gravity. Taking in account the
        earth is neither a point mass nor not a homogenous spherical mass <a href="Math.pdf#page=3"> math reference subsection 1.3</a>*/
    SOL, /**< Solar tide: %Acceleration due to tidal forces caused by the sun <a href="Math.pdf#page=4"> math reference subsection 1.4</a>*/
    LUN, /**< Lunar tide: %Acceleration due to tidal forces caused by the moon <a href="Math.pdf#page=5"> math reference subsection 1.5</a>*/
    SRP, /**< Solar radiation pressure: %Acceleration due to pressure of the suns
        radiation <a href="Math.pdf#page=8"> math reference subsection 1.6</a>*/
    DRAG /**< Drag: %Acceleration due to the friction between the object and the
        earths atmosphere <a href="Math.pdf#page=8"> math reference subsection 1.7</a>*/
};

/**
 * @class AccelerationAccumulator
 *
 * @brief Accumulates all accelerations of the
 * Acceleration::AccelerationComponent specified by the #config vector
 */
class AccelerationAccumulator {
public:
    /**
     * @brief Default constructor
     *
     * creates ann AccelerationAccumulator object wit all value zero initialized
     */
     AccelerationAccumulator();
    /**
     * @brief Constructor creates a new Acceleration::AcceleratorAccumulator
     * object
     *
     * @param config_arg The 8D bool vector encoding the
     * Acceleration::AccelerationComponent to apply in the simulation. The Order
     * of flags is [::KEP, ::J2, ::C22, ::S22, ::SOL, ::LUN, ::SRP, ::DRAG]
     * @param debris_arg Reference to the Debris::DebrisContainer object holding
     * the Debris::Debris objects to apply acceleration to
     * @param t_arg Current time
     * @param file_output_arg Reference to the FileOutput object used for output of the acceleration values during computation
     */
    AccelerationAccumulator(const std::array<bool, 8>& config_arg,
        Debris::DebrisContainer& debris_arg,
        double t_arg,
        FileOutput& file_output_arg)
        : config(config_arg)
        , debris(&debris_arg)
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
    std::array<bool, 8> config{};
    Debris::DebrisContainer*
        debris = nullptr; /**< Reference to the Debris::DebrisContainer object holding the
             Debris::Debris objects to apply acceleration to*/
    double t = 0; /**< current time*/
    FileOutput* file_output = nullptr; /**< used to write detailed output data during calculations */
public:
    /**
     * @brief Getter function for #config
     *
     * @return Value of #config
     */
    [[nodiscard]] const std::array<bool, 8>& getConfig() const;
    std::array<bool, 8>& getConfig() ;

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
    [[nodiscard]] const Debris::DebrisContainer& getDebris() const;
    Debris::DebrisContainer& getDebris();

    /**
     * @brief Setter function for #debris
     *
     * @param debris New value of #debris
     */
    void setDebris(Debris::DebrisContainer& debris);

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
    [[nodiscard]] const FileOutput& getFileOutput() const;
    FileOutput& getFileOutput();

    /**
     * @brief Setter function for #file_output
     *
     * @param fileOutput New value of #file_output
     */
    void setFileOutput(FileOutput& fileOutput);
};
} // namespace Acceleration
