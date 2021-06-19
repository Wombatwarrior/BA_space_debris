//
// Created by Oliver on 27.05.21.
//

#include "KepComponent.h"

namespace Acceleration::KepComponent {
    void apply(const Debris::Debris& d,
        std::array<double, 3>& acc_kep,
        std::array<double, 3>& acc_total)
    {
        acc_kep = d.getPosition();
        // Eq 3
        double divisor = std::inner_product(acc_kep.cbegin(), acc_kep.cend(), acc_kep.cbegin(), 0.0);
        divisor = divisor * divisor * divisor;
        divisor = 1 / std::sqrt(divisor);
        // Eq 4
        acc_kep[0] *= Physics::GM_EARTH;
        acc_kep[1] *= Physics::GM_EARTH;
        acc_kep[2] *= Physics::GM_EARTH;
        acc_kep[0] *= -divisor;
        acc_kep[1] *= -divisor;
        acc_kep[2] *= -divisor;
        acc_total[0] += acc_kep[0];
        acc_total[1] += acc_kep[1];
        acc_total[2] += acc_kep[2];
    }
} // namespace Acceleration