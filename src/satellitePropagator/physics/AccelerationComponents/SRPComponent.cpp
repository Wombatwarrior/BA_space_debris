//
// Created by Oliver on 27.05.21.
//

#include "SRPComponent.h"

namespace Acceleration::SRPComponent {
std::array<double, 6> setUp(double t)
{
    // calculation are the same as in the SolComponent setUp() function
    return Acceleration::SolComponent::setUp(t);
}
} // namespace Acceleration