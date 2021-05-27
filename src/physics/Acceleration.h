//
// Created by Oliver on 12.05.21.
//

#pragma once
#include "debris/DebrisContainer.h"
#include <array>
#include "Constants.h"
#include <math.h>
#include <numeric>

/**
 * @namespace Acceleration
 *
 * @brief Contains classes and functions to calculate accelerations for Debris::Debris objects
 */
namespace Acceleration {
    /**
     * @brief Enumerates the different components of the total acceleration
     */
    enum AccelerationComponent {
        KEP, /**< Kepler: %Acceleration due to earth gravity. Assuming the earth as a point mass*/
        J2, /**< J2: %Acceleration due to earth gravity. Taking in account the earth is neither a point mass nor  a homogenous spherical mass*/
        C22, /**< C22: %Acceleration due to earth gravity. Taking in account the earth is neither a point mass nor not a homogenous spherical mass*/
        S22, /**< S22: %Acceleration due to earth gravity. Taking in account the earth is neither a point mass nor not a homogenous spherical mass*/
        SOL, /**< Solar tide: %Acceleration due to tidal forces caused by the sun*/
        LUN, /**< Lunar tide: %Acceleration due to tidal forces caused by the moon*/
        SRP, /**< Solar radiation pressure: %Acceleration due to pressure of the suns radiation*/
        DRAG /**< Drag: %Acceleration due to the friction between the object and the earths atmosphere*/
    };

    /**
     * @class AccelerationAccumulator
     *
     * @brief Accumulates all accelerations of the Acceleration::AccelerationComponent specified by the #config vector
     */
    class AccelerationAccumulator {
    public:

        /**
         * @brief Constructor creates a new Acceleration::AcceleratorAccumulator object and sets #config vector and #debris members
         *
         * @param config_arg The 8D bool vector encoding the Acceleration::AccelerationComponent to apply in the simulation.
         * The Order of flags is [::KEP, ::J2, ::C22, ::S22, ::SOL, ::LUN, ::SRP, ::DRAG]
         * @param debris_arg Reference to the Debris::DebrisContainer object holding the Debris::Debris objects to apply acceleration to
         * @param t_arg Current time
         */
        AccelerationAccumulator(const std::array<bool,8> &config_arg, Debris::DebrisContainer &debris_arg, double t_arg)
        : config (config_arg), debris (&debris_arg), t(t_arg)
        {};

        /**
         * @brief Default destructor
         *
         * Destroys the Acceleration::AccelerationAccumulator object
         */
        ~AccelerationAccumulator();

        /**
         * @brief Applies all Acceleration::AccelerationComponent specified by #config
         *
         * Loops over all Debris::Debris objects in #debris.
         * Checks if the corresponding flag in the #config vector is set to true and calls the apply() functions.
         * Sets the #Debris::Debris::acc_t1 value of every Debris::Debris object.
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
        void applyComponents();
    private:

        /**
         * @brief 8D bool vector encoding the Acceleration::AccelerationComponent to apply in the simulation.
         *
         * 8D bool vector encoding the Acceleration::AccelerationComponent to apply in the simulation.
         * The Order of flags is
         * - #Acceleration::KEP
         * - #Acceleration::J2
         * - #Acceleration::C22
         * - #Acceleration::S22
         * - #Acceleration::SOL
         * - #Acceleration::LUN
         * - #Acceleration::SRP
         * - #Acceleration::DRAG
         */
        std::array<bool,8> config;
        Debris::DebrisContainer *debris; /**< Reference to the Debris::DebrisContainer object holding the Debris::Debris objects to apply acceleration to*/
        double t;/**< current time*/
    public:
        /**
         * @brief Getter function for #config
         *
         * @return Value of #config
         */
        std::array<bool, 8> &getConfig() ;

        /**
         * @brief Setter function for #config
         *
         * @param config New value of #config
         */
        void setConfig( std::array<bool, 8> &config);

        /**
         * @brief Getter function for #debris
         *
         * @return Value of #debris
         */
        Debris::DebrisContainer &getDebris() ;

        /**
         * @brief Setter function for #debris
         *
         * @param debris New value of #debris
         */
        void setDebris(Debris::DebrisContainer &debris);

        /**
         * @brief Getter function for #t
         *
         * @return Value of #t
         */
        double getT();

        /**
          * @brief Setter function for #t
          *
          * @param t New value of #t
          */
        void setT(double t);
    };

    /**
     * @namespace Acceleration::KepComponent
     *
     * @brief Encapsulates functionality to calculate acceleration for Acceleration::KEP
     */
    namespace KepComponent {
        /**
         * @brief Calculates acceleration due to earth gravity. Assuming the earth as a point mass
         *
         * @param d Reference to the Debris::Debris object to apply the acceleration to
         * @param acc_kep Reference to an 3D vector to write the result for this Acceleration::AccelerationComponent.
         * @param acc_total Reference to an 3D vector to accumulate the accelerations for all applied Acceleration::AccelerationComponent.
         */
        void apply( Debris::Debris &d, std::array<double,3> &acc_kep, std::array<double,3> &acc_total);
    }

    /**
     * @namespace Acceleration::J2Component
     *
     * @brief Encapsulates functionality to calculate acceleration for Acceleration::J2
     */
    namespace J2Component {
        namespace {

            /**
             * @brief Constant factor for the first J2 term
             *
             * @return (std::sqrt(5)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::C20)/2
             */
            inline const double getFactor_fst();
        }
        /**
         * @brief Calculates acceleration due to earth gravity. Taking in account the earth is neither a point mass nor  a homogenous spherical mass
         *
         * @param d Reference to the Debris::Debris object to apply the acceleration to
         * @param acc_j2 Reference to an 3D vector to write the result for this Acceleration::AccelerationComponent.
         * @param acc_total Reference to an 3D vector to accumulate the accelerations for all applied Acceleration::AccelerationComponent.
         */
        void apply( Debris::Debris &d, std::array<double,3> &acc_j2, std::array<double,3> &acc_total);
    }

    /**
     * @namespace Acceleration::C22Component
     *
     * @brief Encapsulates functionality to calculate acceleration for Acceleration::C22
     */
    namespace C22Component {
        namespace {
            /**
             * @brief Calculate terms for the x component of C22
             * @deprecated
             * @param x
             * @param y
             * @param z
             * @return
             */
            inline double getFC22_x(double x, double y, double z);

            /**
             * @brief Calculate terms for the y component of C22
             * @deprecated
             * @param x
             * @param y
             * @param z
             * @return
             */
            inline double getFC22_y(double x, double y, double z);

            /**
             * @brief Calculate terms for the z component of C22
             * @deprecated
             * @param x
             * @param y
             * @param z
             * @return
             */
            inline double getFC22_z(double x, double y, double z);

            /**
             * @brief Constant factor for the first C22 term
             *
             * @return (5*std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::C22)/2
             */
            inline constexpr double getFactor_fst();

            /**
             * @brief Constant factor for the second C22 term
             *
             * @return std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::C22
             */
            inline constexpr double getFactor_snd();
        }
        /**
         * @brief Calculates acceleration due to earth gravity. Taking in account the earth is neither a point mass nor not a homogenous spherical mass
         *
         * @param d Reference to the Debris::Debris object to apply the acceleration to
         * @param c_term Time dependent cos value
         * @param s_term Time dependent sin value
         * @param acc_c22 Reference to an 3D vector to write the result for this Acceleration::AccelerationComponent.
         * @param acc_total Reference to an 3D vector to accumulate the accelerations for all applied Acceleration::AccelerationComponent.
         */
        void apply( Debris::Debris &d, double c_term, double s_term, std::array<double,3> &acc_c22, std::array<double,3> &acc_total);
    }

    /**
     * @namespace Acceleration::S22Component
     *
     * @brief Encapsulates functionality to calculate acceleration for Acceleration::S22
     */
    namespace S22Component {
        namespace {
            /**
             * @brief Calculate terms for the x component of S22
             * @deprecated
             * @param x
             * @param y
             * @param z
             * @return
             */
            inline double getFS22_x(double x, double y, double z);
            /**
             * @brief Calculate terms for the y component of S22
             * @deprecated
             * @param x
             * @param y
             * @param z
             * @return
             */
            inline double getFS22_y(double x, double y, double z);
            /**
             * @brief Calculate terms for the z component of S22
             * @deprecated
             * @param x
             * @param y
             * @param z
             * @return
             */
            inline double getFS22_z(double x, double y, double z);

            /**
             * @brief Constant factor for the first S22 term
             *
             * @return -5*std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::S22
             */
            inline constexpr double getFactor_fst();

            /**
             * @brief Constant factor for the second S22 term
             *
             * @return std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::S22
             */
            inline constexpr double getFactor_snd();
        }
        /**
         * @brief Calculates acceleration due to earth gravity. Taking in account the earth is neither a point mass nor not a homogenous spherical mass
         *
         * @param d Reference to the Debris::Debris object to apply the acceleration to
         * @param c_term Time dependent cos value
         * @param s_term Time dependent sin value
         * @param acc_s22 Reference to an 3D vector to write the result for this Acceleration::AccelerationComponent.
         * @param acc_total Reference to an 3D vector to accumulate the accelerations for all applied Acceleration::AccelerationComponent.
         */
        void apply( Debris::Debris &d, double c_term, double s_term, std::array<double,3> &acc_s22, std::array<double,3> &acc_total);
    }

    /**
     * @namespace Acceleration::C22S22Component
     *
     * @brief Encapsulates functionality to calculate acceleration for Acceleration::C22 and Acceleration::S22 at once
     *
     * Encapsulates functionality to calculate acceleration for Acceleration::C22 and Acceleration::S22 at once,
     * because many terms are shared between the two calculations.
     * If both Components are both set active use this.
     *
     */
    namespace C22S22Component{
        namespace {
            /**
             * @brief  Calculates factor of the calculations consisting only on constants
             *
             * This term is part of all nominator terms for the C22 and S22 calculations
             *
             * @return std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH
             */
            inline constexpr double getFactor();

            /**
             * @brief Constant factor for the second C22 term
             *
             * @return std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::C22
             */
            inline constexpr double getFactorC22_snd();

            /**
             * @brief Constant factor for the first C22 term
             *
             * @return (5*std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::C22)/2
             */
            inline constexpr double getFactorC22_fst();

            /**
             * @brief Constant factor for the second S22 term
             *
             * @return std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::S22
             */
            inline constexpr double getFactorS22_snd();

            /**
             * @brief Constant factor for the first S22 term
             *
             * @return -5*std::sqrt(15)*Physics::GM_EARTH*Physics::R_EARTH*Physics::R_EARTH*Physics::S22
             */
            inline constexpr double getFactorS22_fst();
        }
        /**
         * @brief Calculates acceleration due to earth gravity. Taking in account the earth is neither a point mass nor not a homogenous spherical mass
         *
         * @param d Reference to the Debris::Debris object to apply the acceleration to
         * @param c_term Time dependent cos value
         * @param s_term Time dependent sin value
         * @param acc_c22s22 Reference to an 3D vector to write the result for this Acceleration::AccelerationComponent.
         * @param acc_total Reference to an 3D vector to accumulate the accelerations for all applied Acceleration::AccelerationComponent.
         */
        void apply( Debris::Debris &d, double c_term, double s_term, std::array<double,3> &acc_c22s22, std::array<double,3> &acc_total);
    }

    /**
     * @namespace Acceleration::SolComponent
     *
     * @brief Encapsulates functionality to calculate acceleration for Acceleration::SOL
     */
    namespace SolComponent {
        /**
         * @brief Precalculates values needed for Acceleration::SolComponent::apply()
         *
         * Calculates time dependent position of the sun and terms only depending on those position values
         * i.e. constant for the whole time step.
         *
         * @return 6D vector [X_sun,Y_sun,Z_sun,X_sun/||POS_sunY||,Y_sun/||POS_sun||,Z_sun/||POS_sun||]
         */
        const std::array<double,6> setUp(double t);
        /**
         * @brief Calculates acceleration due to tidal forces caused by the sun
         *
         * @param d Reference to the Debris::Debris object to apply the acceleration to
         * @param sun_params 6D array with precalculated values: [X_sun, Y_sun, Z_sun, X_sun/||POS_sun||, Y_sun/||POS_sun||, Z_sun/||POS_sun||]
         * @param acc_sol Reference to an 3D vector to write the result for this Acceleration::AccelerationComponent.
         * @param acc_total Reference to an 3D vector to accumulate the accelerations for all applied Acceleration::AccelerationComponent.
         */
        void apply( Debris::Debris &d, const std::array<double,6> &sun_params, std::array<double,3> &acc_sol, std::array<double,3> &acc_total);
    }

    /**
     * @namespace Acceleration::LunComponent
     *
     * @brief Encapsulates functionality to calculate acceleration for Acceleration::LUN
     */
    namespace LunComponent {
        /**
         * @brief Precalculates values needed for Acceleration::LunComponent::apply()
         *
         * Calculates time dependent position of the moon and terms only depending on those position values
         * i.e. constant for the whole time step.
         *
         * @return 6D vector [X_moon,Y_moon,Z_moon,X_moon/||POS_moon||,Y_moon/||POS_moon||,Z_moon/||POS_moon||]
         */
        const std::array<double,6> setUp(double t);
        /**
         * @brief Calculates acceleration due to tidal forces caused by the moon
         *
         * @param d Reference to the Debris::Debris object to apply the acceleration to
         * @param moon_params 6D array with precalculated values: [X_moon,Y_moon,Z_moon,X_moon/||POS_moon||,Y_moon/||POS_moon||,Z_moon/||POS_moon||]
         * @param acc_lun Reference to an 3D vector to write the result for this Acceleration::AccelerationComponent.
         * @param acc_total Reference to an 3D vector to accumulate the accelerations for all applied Acceleration::AccelerationComponent.
         */
        void apply( Debris::Debris &d, const std::array<double,6> &moon_params, std::array<double,3> &acc_lun, std::array<double,3> &acc_total);
    }

    /**
     * @namespace Acceleration::SRPComponent
     *
     * @brief Encapsulates functionality to calculate acceleration for Acceleration::SRP
     */
    namespace SRPComponent {
        namespace {

        }
        /**
         * @brief Calculates acceleration due to pressure of the suns radiation
         *
         * @param d Reference to the Debris::Debris object to apply the acceleration to
         * @param acc_srp Reference to an 3D vector to write the result for this Acceleration::AccelerationComponent.
         * @param acc_total Reference to an 3D vector to accumulate the accelerations for all applied Acceleration::AccelerationComponent.
         */
        void apply( Debris::Debris &d, std::array<double,3> &acc_srp, std::array<double,3> &acc_total);
    }

    /**
     * @namespace Acceleration::DragComponent
     *
     * @brief Encapsulates functionality to calculate acceleration for Acceleration::DRAG
     */
    namespace DragComponent  {
        namespace {

        }
        /**
         * @brief Calculates acceleration due to the friction between the object and the earths atmosphere
         *
         * @param d Reference to the Debris::Debris object to apply the acceleration to
         * @param acc_drag Reference to an 3D vector to write the result for this Acceleration::AccelerationComponent.
         * @param acc_total Reference to an 3D vector to accumulate the accelerations for all applied Acceleration::AccelerationComponent.
         */
        void apply( Debris::Debris &d, std::array<double,3> &acc_drag, std::array<double,3> &acc_total);
    }
}
