//
// Created by Oliver on 12.05.21.
//

#pragma once
#include <array>
#include <sstream>
#include "../io/IOUtils.h"
/**
 * @namespace Debris
 * @brief Namespace holding the DebrisContainer and Debris
 */
namespace Debris {
    /**
     * @class Debris
     * @brief Represents a single peace of debris
     */
    class Debris {
    public:
        /**
         * @brief Default constructor
         *
         * Creates a new Debris object and initializes all member variables with zero values
         */
        Debris();

        /**
         * @brief Copy constructor
         *
         * Creates a new Debris object and copies all member variables
         *
         * @param other Reference to the Debris object to copy
         */
        Debris(const Debris &other);

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
        std::string toString();
    private:
        std::array<double,3> position;/**< 3D vector representation of the debris position*/
        std::array<double,3> velocity;/**< 3D vector representation of the debris velocity*/
        std::array<double,3> acc_t0;/**< 3D vector representation of the debris acceleration at the last time step*/
        std::array<double,3> acc_t1;/**< 3D vector representation of the debris acceleration at the current time step*/
    public:
        /**
         * @brief Getter function for #position vector
         *
         * @return 3D vector representation of the debris #position
         */
        std::array<double, 3> &getPosition() ;

        /**
         * @brief Setter function for #position vector
         *
         * @param position 3D vector representation of the debris #position
         */
        void setPosition( std::array<double, 3> &position);

        /**
         * @brief Getter function for #velocity vector
         *
         * @return 3D vector representation of the debris #velocity
         */
        std::array<double, 3> &getVelocity() ;

        /**
         * @brief Setter function for #velocity vector
         *
         * @param velocity 3D vector representation of the debris #velocity
         */
        void setVelocity( std::array<double, 3> &velocity);

        /**
         * @brief Getter function for #acc_t0 vector
         *
         * @return 3D vector representation of the debris #acc_t0
         */
        std::array<double, 3> &getAccT0() ;

        /**
         * @brief Setter function for #acc_t0 vector
         *
         * @param accT0 3D vector representation of the debris #acc_t0
         */
        void setAccT0( std::array<double, 3> &accT0);

        /**
         * @brief Getter function for #acc_t1 vector
         *
         * @return 3D vector representation of the debris #acc_t1
         */
        std::array<double, 3> &getAccT1() ;

        /**
         * @brief Setter function for #acc_t1 vector
         *
         * @param accT1 3D vector representation of the debris #acc_t1
         */
        void setAccT1( std::array<double, 3> &accT1);
    };
}