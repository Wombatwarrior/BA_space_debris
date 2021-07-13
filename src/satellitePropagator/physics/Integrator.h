//
// Created by Oliver on 13.05.21.
//

#pragma once
#include "AccelerationAccumulator.h"
#include "satellitePropagator/debris/AccelerationUpdate.h"

/**
 * @class Integrator
 *
 * @brief Calculates status of Debris::Debris objects for next time step
 */
template <class Container>
class Integrator {
public:
    /**
     * @brief Default constructor
     *
     * Creates a new Integrator object with all values zero initialized
     */
    Integrator();

    /**
     * @brief Creates a Integrator object and sets the private #debris and
     * #delta_t member variables
     *
     * @param container Reference to the Container object holding
     * the Debris::Debris objects to integrate for
     * @param accumulator_arg Reference to the
     * Acceleration::AccelerationAccumulator object to calculate acceleration for
     * the current time step
     * @param delta_t_arg Time step to Integrate over
     */
    Integrator(Container& container,
        Acceleration::AccelerationAccumulator<Container>& accumulator_arg,
        double delta_t_arg)
        : debris(&container)
        , accumulator(&accumulator_arg)
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
     * Debris::Debris objects of the Container #debris it is called
     * before Integrator::calculateVelocity()
     *
     * @param write_time_step if true all calculated acceleration components are writen to a file
     */
    void integrate(bool write_time_step = false) const;

    /**
     * @brief Calculates the new position
     *
     * Calculates the Debris::Debris::position vector for all Debris::Debris
     * objects of the Container #debris Uses leapfrog integration
     * with Debris::Debris::velocity and Debris::Debris::acc_t0
     *
     */
    void calculatePosition() const;

    /**
     * @brief Calculates the new velocities
     *
     * Calculates the Debris::Debris::velocity vector for all Debris::Debris
     * objects of the Container #debris Uses leapfrog integration
     * with Debris::Debris::acc_t0 and Debris::Debris::acc_t1
     *
     */
    void calculateVelocity() const;

    /**
     * @brief Calculates te acceleration for the current time step
     *
     * Calls the Acceleration::AccelerationAccumulator::applyComponents()
     * function of the Acceleration::AccelerationAccumulator object #accumulator
     * After this function is called the Debris::Debris objects of the
     * Container #debris are ready for integrating
     *
     * @param write_time_step if true all calculated acceleration components are writen to a file
     */
    void calculateAcceleration(bool write_time_step) const;

private:
    Container*
        debris
        = nullptr; /**< Reference to the Container object holding the
             Debris::Debris objects to integrate for*/
    Acceleration::AccelerationAccumulator<Container>*
        accumulator
        = nullptr; /**< Reference to the Acceleration::AccelerationAccumulator
                   object to calculate acceleration for the current time
                   step*/
    double delta_t = 0; /**< Time step to Integrate over */
public:
    /**
     * @brief Getter function for #delta_t
     *
     * @return Value of #delta_t
     */
    [[nodiscard]] double getDeltaT() const;

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
    [[nodiscard]] const Acceleration::AccelerationAccumulator<Container>& getAccumulator() const;
    Acceleration::AccelerationAccumulator<Container>& getAccumulator();

    /**
     * @brief Setter function for #accumulator
     *
     * @param accumulator New value of #accumulator
     */
    void setAccumulator(Acceleration::AccelerationAccumulator<Container>& accumulator);

    /**
     * @brief Getter function for #debris
     *
     * @return Value of #debris
     */
    [[nodiscard]] const Container& getDebris() const;
    Container& getDebris();

    /**
     * @brief Setter function for #delta_t
     *
     * @param debris New value of #delta_t
     */
    void setDebris(Container& debris);
};

template <class Container>
Integrator<Container>::Integrator() = default;

template <class Container>
Integrator<Container>::~Integrator() = default;

template <class Container>
void Integrator<Container>::integrate(bool write_time_step) const
{
    AccelerationUpdate::accelerationUpdate(debris);
    calculateAcceleration(write_time_step);
    calculatePosition();
    calculateVelocity();
    // update time
    accumulator->setT(accumulator->getT() + delta_t);
}

template <class Container>
void Integrator<Container>::calculatePosition() const
{
    double factor = delta_t * delta_t * 0.5;
    std::array<double, 3> new_pos {};
    for (auto& d : *debris) {
        new_pos = d.getPosition();
        new_pos[0] = new_pos[0] + delta_t * d.getVelocity()[0] + factor * d.getAccT0()[0];
        new_pos[1] = new_pos[1] + delta_t * d.getVelocity()[1] + factor * d.getAccT0()[1];
        new_pos[2] = new_pos[2] + delta_t * d.getVelocity()[2] + factor * d.getAccT0()[2];
        d.setPosition(new_pos);
    }
}

template <class Container>
void Integrator<Container>::calculateVelocity() const
{
    const double factor = delta_t * 0.5;
    std::array<double, 3> new_velocity {};
    for (auto& d : *debris) {
        new_velocity = d.getVelocity();
        new_velocity[0] = new_velocity[0] + factor * (d.getAccT0()[0] + d.getAccT1()[0]);
        new_velocity[1] = new_velocity[1] + factor * (d.getAccT0()[1] + d.getAccT1()[1]);
        new_velocity[2] = new_velocity[2] + factor * (d.getAccT0()[2] + d.getAccT1()[2]);
        d.setVelocity(new_velocity);
    }
}

template <class Container>
void Integrator<Container>::calculateAcceleration(bool write_time_step) const
{
    if (write_time_step) {
        accumulator->applyAmdWriteComponents();
    } else {
        accumulator->applyComponents();
    }
}

template <class Container>
double Integrator<Container>::getDeltaT() const
{
    return delta_t;
}

template <class Container>
void Integrator<Container>::setDeltaT(double deltaT)
{
    delta_t = deltaT;
}

template <class Container>
const Container& Integrator<Container>::getDebris() const
{
    return *debris;
}

template <class Container>
Container& Integrator<Container>::getDebris()
{
    return *debris;
}

template <class Container>
void Integrator<Container>::setDebris(Container& debris)
{
    Integrator<Container>::debris = &debris;
}

template <class Container>
const Acceleration::AccelerationAccumulator<Container>& Integrator<Container>::getAccumulator() const
{
    return *accumulator;
}

template <class Container>
Acceleration::AccelerationAccumulator<Container>& Integrator<Container>::getAccumulator()
{
    return *accumulator;
}

template <class Container>
void Integrator<Container>::setAccumulator(Acceleration::AccelerationAccumulator<Container>& accumulator)
{
    Integrator<Container>::accumulator = &accumulator;
}
