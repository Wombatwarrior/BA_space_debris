//
// Created by ubuntu on 12.05.21.
//

#include "Accelaration.h"

namespace Accelaration{
    void KepComponent::apply(Debris::DebrisContainer &debris) {
        std::array<double,3> acc_kep;
        double divisor;
        for (auto &d : debris.getDebrisVector()){
            acc_kep=d.getPosition();
            divisor = acc_kep[0]*acc_kep[0]+acc_kep[1]*acc_kep[1]+acc_kep[2]*acc_kep[2];
            divisor = divisor*divisor*divisor;
            divisor = std::sqrt(divisor);
            acc_kep[0] = Physics::GM_EARTH*acc_kep[0];
            acc_kep[1] = Physics::GM_EARTH*acc_kep[1];
            acc_kep[2] = Physics::GM_EARTH*acc_kep[2];
            acc_kep[0] = acc_kep[0]/divisor;
            acc_kep[1] = acc_kep[1]/divisor;
            acc_kep[2] = acc_kep[2]/divisor;
            d.setAccT0(acc_kep);
        }
    }
}