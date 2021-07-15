//
// Created by Oliver on 15.07.21.
//

#pragma once
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

}