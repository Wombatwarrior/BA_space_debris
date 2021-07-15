//
// Created by Oliver on 12.05.21.
//

#pragma once
#include <cmath>

#include "satellitePropagator/utils/MathUtils.h"
#include <array>
#include <memory>
#include <numeric>
#include <sstream>

#include "../io/IOUtils.h"

/**
 * @namespace Debris
 * @brief Namespace holding the DebrisContainer and Debris
 */
namespace Debris {
/**
 * @class Debris::Debris
 * @brief Represents a single peace of debris
 */
class Debris {
public:
    /**
     * @brief Default constructor
     *
     * Creates a new Debris object and initializes all member variables with zero
     * values
     */
    Debris();

    /**
     * @brief Copy constructor
     *
     * Creates a new Debris object and copies all member variables
     *
     * @param other Reference to the Debris object to copy
     */
    Debris(const Debris& other);

    /**
     * @brief Default destructor
     *
     * Destroys the Debris object
     */
    virtual ~Debris();

    /**
     * @brief String representation
     *
     * Creates a std::string representation of the state of the debris
     *
     * @return The string "Debris: X:#position v:#velocity a0:#acc_t0 a1:#acc_t1"
     */
    [[nodiscard]] std::string toString() const;

    /**
     * @brief Calculates distance from the origin of the coordinate frame
     *
     * @return Euclidean norm of the #position vector
     */
    [[nodiscard]] double getHeight() const;

    /**
     * @brief Calculates speed of the debris
     *
     * @return Euclidean norm of the #velocity vector
     */
    [[nodiscard]] double getSpeed() const;

    /**
     * @brief Calculates the euclidean norm of the #acc_t0
     *
     * @return Calculates the euclidean norm of the #acc_t0
     */
    [[nodiscard]] double getAccT0Norm() const;

    /**
     * @brief Calculates the euclidean norm of the #acc_t1
     *
     * @return Calculates the euclidean norm of the #acc_t1
     */
    [[nodiscard]] double getAccT1Norm() const;

private:
    std::array<double, 3>
        position {}; /**< 3D vector representation of the debris position*/
    std::array<double, 3>
        velocity {}; /**< 3D vector representation of the debris velocity*/
    std::array<double, 3> acc_t0 {}; /**< 3D vector representation of the debris
                                 acceleration at the last time step*/
    std::array<double, 3> acc_t1 {}; /**< 3D vector representation of the debris
                                 acceleration at the current time step*/
    double bc_inv = 0; /**< (C_cA)/m is the inverse of the ballistic coefficient. Used for Acceleration::DragComponent::apply()*/
    double aom = 0; /**< Area to mass ration*/
public:
    /**
     * @brief Getter function for #position vector
     *
     * @return 3D vector representation of the debris #position
     */
    [[nodiscard]] const std::array<double, 3>& getPosition() const;
    std::array<double, 3>& getPosition();

    /**
     * @brief Setter function for #position vector
     *
     * @param position 3D vector representation of the debris #position
     */
    void setPosition(const std::array<double, 3>& position);

    /**
     * @brief Getter function for #velocity vector
     *
     * @return 3D vector representation of the debris #velocity
     */
    [[nodiscard]] const std::array<double, 3>& getVelocity() const;
    std::array<double, 3>& getVelocity();

    /**
     * @brief Setter function for #velocity vector
     *
     * @param velocity 3D vector representation of the debris #velocity
     */
    void setVelocity(const std::array<double, 3>& velocity);

    /**
     * @brief Getter function for #acc_t0 vector
     *
     * @return 3D vector representation of the debris #acc_t0
     */
    [[nodiscard]] const std::array<double, 3>& getAccT0() const;
    std::array<double, 3>& getAccT0();

    /**
     * @brief Setter function for #acc_t0 vector
     *
     * @param accT0 3D vector representation of the debris #acc_t0
     */
    void setAccT0(const std::array<double, 3>& accT0);

    /**
     * @brief Getter function for #acc_t1 vector
     *
     * @return 3D vector representation of the debris #acc_t1
     */
    [[nodiscard]] const std::array<double, 3>& getAccT1() const;
    std::array<double, 3>& getAccT1();

    /**
     * @brief Setter function for #acc_t1 vector
     *
     * @param accT1 3D vector representation of the debris #acc_t1
     */
    void setAccT1(const std::array<double, 3>& accT1);

    /**
     * @brief Getter function for #aom
     *
     * @return value of #aom
     */
    [[nodiscard]] double getAom() const;

    /**
     * @brief Setter function for #aom
     *
     * @param aom New value #aom
     */
    void setAom(double aom);

    /**
     * @brief Getter function for #bc_inv
     *
     * @return Value of #bc_inv
     */
    [[nodiscard]] double getBcInv() const;

    /**
     * @brief Setter function for #bc_inv
     *
     * @param bcInv New value of#bc_inv
     */
    void setBcInv(double bcInv);

};
} // namespace Debris