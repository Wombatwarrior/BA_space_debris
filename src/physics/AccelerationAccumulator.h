//
// Created by Oliver on 12.05.21.
//

#pragma once
#include "AccelerationComponents/include.h"
#include "Constants.h"
#include "debris/DebrisContainer.h"
#include <array>
#include <math.h>
#include <numeric>

/**
 * @namespace Acceleration
 *
 * @brief Contains classes and functions to calculate accelerations for
 * Debris::Debris objects
 */
namespace Acceleration {
/**
 * @brief Enumerates the different components of the total acceleration
 */
enum AccelerationComponent {
  KEP, /**< Kepler: %Acceleration due to earth gravity. Assuming the earth as a
          point mass*/
  J2,  /**< J2: %Acceleration due to earth gravity. Taking in account the earth
          is neither a point mass nor  a homogenous spherical mass*/
  C22, /**< C22: %Acceleration due to earth gravity. Taking in account the earth
          is neither a point mass nor not a homogenous spherical mass*/
  S22, /**< S22: %Acceleration due to earth gravity. Taking in account the earth
          is neither a point mass nor not a homogenous spherical mass*/
  SOL, /**< Solar tide: %Acceleration due to tidal forces caused by the sun*/
  LUN, /**< Lunar tide: %Acceleration due to tidal forces caused by the moon*/
  SRP, /**< Solar radiation pressure: %Acceleration due to pressure of the suns
          radiation*/
  DRAG /**< Drag: %Acceleration due to the friction between the object and the
          earths atmosphere*/
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
   * @brief Constructor creates a new Acceleration::AcceleratorAccumulator
   * object and sets #config vector and #debris members
   *
   * @param config_arg The 8D bool vector encoding the
   * Acceleration::AccelerationComponent to apply in the simulation. The Order
   * of flags is [::KEP, ::J2, ::C22, ::S22, ::SOL, ::LUN, ::SRP, ::DRAG]
   * @param debris_arg Reference to the Debris::DebrisContainer object holding
   * the Debris::Debris objects to apply acceleration to
   * @param t_arg Current time
   */
  AccelerationAccumulator(const std::array<bool, 8> &config_arg,
                          Debris::DebrisContainer &debris_arg, double t_arg)
      : config(config_arg), debris(&debris_arg), t(t_arg){};

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
  void applyComponents();

private:
  /**
   * @brief 8D bool vector encoding the Acceleration::AccelerationComponent to
   * apply in the simulation.
   *
   * 8D bool vector encoding the Acceleration::AccelerationComponent to apply in
   * the simulation. The Order of flags is
   * - #Acceleration::KEP
   * - #Acceleration::J2
   * - #Acceleration::C22
   * - #Acceleration::S22
   * - #Acceleration::SOL
   * - #Acceleration::LUN
   * - #Acceleration::SRP
   * - #Acceleration::DRAG
   */
  std::array<bool, 8> config;
  Debris::DebrisContainer
      *debris; /**< Reference to the Debris::DebrisContainer object holding the
                  Debris::Debris objects to apply acceleration to*/
  double t;    /**< current time*/
public:
  /**
   * @brief Getter function for #config
   *
   * @return Value of #config
   */
  std::array<bool, 8> &getConfig();

  /**
   * @brief Setter function for #config
   *
   * @param config New value of #config
   */
  void setConfig(std::array<bool, 8> &config);

  /**
   * @brief Getter function for #debris
   *
   * @return Value of #debris
   */
  Debris::DebrisContainer &getDebris();

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
} // namespace Acceleration
