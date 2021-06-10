//
// Created by Oliver on 13.05.21.
//

#pragma once
#include "../debris/DebrisContainer.h"
#include "../physics/AccelerationAccumulator.h"

/**
 * @class Integrator
 *
 * @brief Calculates status of Debris::Debris objects for next time step
 */
class Integrator {
public:
    /**
     * @brief Creates a Integrator object and sets the private #debris and
     * #delta_t member variables
     *
     * @param debris_arg Reference to the Debris::DebrisContainer object holding
     * the Debris::Debris objects to integrate for
     * @param accumulator_arg Reference to the
     * Acceleration::AccelerationAccumulator object to calculate acceleration for
     * the current time step
     * @param delta_t_arg Time step to Integrate over
     */
    Integrator(Debris::DebrisContainer& debris_arg,
        Acceleration::AccelerationAccumulator& accumulator_arg,
        double delta_t_arg)
        : debris(&debris_arg)
        , accumulator(accumulator_arg)
        , delta_t(delta_t_arg) {};

    /**
     * @brief Default destructor
     *
     * Destroys the Integrator object
     */
    virtual ~Integrator();

    /**
     * @brief Calculates a complete time step
     *
     * Integrator::calculateAcceleration() is called first.
     * Because the Integrator::calculatePosition() function needs the
     * Debris::Debris::velocity vector of the last time step of the
     * Debris::Debris objects of the Debris::DebrisContainer #debris it is called
     * before Integrator::calculateVelocity()
     *
     * @param write_time_step if true all calculated acceleration components are writen to a file
     */
    void integrate(bool write_time_step=false);

    /**
     * @brief Calculates the new position
     *
     * Calculates the Debris::Debris::position vector for all Debris::Debris
     * objects of the Debris::DebrisContainer #debris Uses leapfrog integration
     * with Debris::Debris::velocity and Debris::Debris::acc_t0
     *
     */
    void calculatePosition();

    /**
     * @brief Calculates the new velocities
     *
     * Calculates the Debris::Debris::velocity vector for all Debris::Debris
     * objects of the Debris::DebrisContainer #debris Uses leapfrog integration
     * with Debris::Debris::acc_t0 and Debris::Debris::acc_t1
     *
     */
    void calculateVelocity();

    /**
     * @brief Calculates te acceleration for the current time step
     *
     * Calls the Acceleration::AccelerationAccumulator::applyComponents()
     * function of the Acceleration::AccelerationAccumulator object #accumulator
     * After this function is called the Debris::Debris objects of the
     * Debris::DebrisContainer #debris are ready for integrating
     *
     * @param write_time_step if true all calculated acceleration components are writen to a file
     */
    void calculateAcceleration(bool write_time_step);

private:
    Debris::DebrisContainer*
        debris; /**< Reference to the Debris::DebrisContainer object holding the
             Debris::Debris objects to integrate for*/
    Acceleration::AccelerationAccumulator&
        accumulator; /**< Reference to the Acceleration::AccelerationAccumulator
                   object to calculate acceleration for the current time
                   step*/
    double delta_t; /**< Time step to Integrate over */
public:
    /**
     * @brief Getter function for #delta_t
     *
     * @return Value of #delta_t
     */
    double getDeltaT();

    /**
     * @brief Setter function for #delta_t
     *
     * @param deltaT New value of #delta_t
     */
    void setDeltaT(double deltaT);

    /**
     * @brief Getter function for #accumulator
     *
     * @return Value of #accumulator
     */
    Acceleration::AccelerationAccumulator& getAccumulator();

    /**
     * @brief Setter function for #accumulator
     *
     * @param accumulator New value of #accumulator
     */
    void setAccumulator(Acceleration::AccelerationAccumulator& accumulator);

    /**
     * @brief Getter function for #debris
     *
     * @return Value of #debris
     */
    Debris::DebrisContainer& getDebris();

    /**
     * @brief Setter function for #delta_t
     *
     * @param debris New value of #delta_t
     */
    void setDebris(Debris::DebrisContainer& debris);
};