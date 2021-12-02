#pragma once

#include <array>

namespace AccelerationUpdate {

/**
     * @brief Move the acceleration values of the Debris objects by one time step
     *
     * Sets the new Debris::acc_t0 value to be the old Debris::acc_t1 value.
     * Sets the new Debris::acc_t1 value to be a zero vector
     */
template <class Container>
void accelerationUpdate(const Container& container)
{
    std::array<double, 3> new_acc { 0, 0, 0 };
    for (auto iter = container->begin(); iter != container->end(); ++iter) {
        iter->setAccT0(iter->getAccT1());
        iter->setAccT1(new_acc);
    }
}
}