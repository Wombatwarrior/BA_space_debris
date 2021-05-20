//
// Created by Oliver on 13.05.21.
//

#pragma once
#include "gtest/gtest.h"

#include "../../src/debris/include.h"
#include "../../src/physics/include.h"
#include "../../src/io/include.h"
#include <iostream>


class KepComponentTests : public ::testing::Test {
protected:
    std::shared_ptr<Debris::DebrisContainer> debris;
    std::array<std::array<double,3>,9> pre_calculated;

    virtual void SetUp() {
        debris = std::make_shared<Debris::DebrisContainer>();
        Debris::Debris d;
        // only one axis
        for (int i = 0; i <3; ++i) {
            std::array<double,3> pos{0,0,0};
            pos[i] = 10000;
            d.setPosition(pos);
            debris->addDebris(d);
        }
        // all axis
        for (int i = 0; i < 3; ++i){
            std::array<double,3> pos{0,0,0};
            pos[i] = 5000;
            pos[(i+1)%3] = 4321;
            pos[(i+2)%3] = 3210;
            d.setPosition(pos);
            debris->addDebris(d);
        }
        // 10 to 10e+6 at one axis
        for (int i = 1; i < 7; ++i) {
            std::array<double,3> pos{0,0,0};
            pos[0] = std::pow(10, i);
            d.setPosition(pos);
            debris->addDebris(d);
        }
        // 10 to 10e+3
        for (int i = 1; i < 4; ++i) {
            std::array<double,3> pos{0,0,0};
            pos[0] = std::pow(10, i);
            pos[1] = std::pow(10, i);
            pos[2] = std::pow(10, i);
            d.setPosition(pos);
            debris->addDebris(d);
        }
        pre_calculated[0] = {-0.01*Physics::GM_EARTH,
                             0,
                             0
        };
        pre_calculated[1] = {-0.0001*Physics::GM_EARTH,
                             0,
                             0
        };
        pre_calculated[2] = {-0.000001*Physics::GM_EARTH,
                             0,
                             0
        };
        pre_calculated[3] = {-0.00000001*Physics::GM_EARTH,
                             0,
                             0
        };
        pre_calculated[4] = {-0.0000000001*Physics::GM_EARTH,
                             0,
                             0
        };
        pre_calculated[5] = {-0.000000000001*Physics::GM_EARTH,
                             0,
                             0
        };
        pre_calculated[6] = {-(1/(std::sqrt(3)*300))*Physics::GM_EARTH,
                             -(1/(std::sqrt(3)*300))*Physics::GM_EARTH,
                             -(1/(std::sqrt(3)*300))*Physics::GM_EARTH
        };
        pre_calculated[7] = {-(1/(std::sqrt(3)*30000))*Physics::GM_EARTH,

                             -(1/(std::sqrt(3)*30000))*Physics::GM_EARTH,
                             -(1/(std::sqrt(3)*30000))*Physics::GM_EARTH
        };
        pre_calculated[8] = {-(1/(std::sqrt(3)*3000000))*Physics::GM_EARTH,
                             -(1/(std::sqrt(3)*3000000))*Physics::GM_EARTH,
                             -(1/(std::sqrt(3)*3000000))*Physics::GM_EARTH
        };
    }

    void calcKep(Debris::Debris &d, std::array<double,3> &acc_kep){
        double gme=3.986004407799724e+5;
        double x = d.getPosition()[0];
        double y = d.getPosition()[1];
        double z = d.getPosition()[2];
        double d1 = std::pow((x*x+y*y+z*z), 1.5);
        acc_kep[0] =-((gme*x)/d1);
        acc_kep[1] =-((gme*y)/d1);
        acc_kep[2] =-((gme*z)/d1);
    }
};

class J2ComponentTests : public ::testing::Test {
protected:
    std::shared_ptr<Debris::DebrisContainer> debris;
    std::array<std::array<double,3>,9> pre_calculated;

    virtual void SetUp() {
        debris = std::make_shared<Debris::DebrisContainer>();
        Debris::Debris d;

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::array<double, 3> pos{0, 0, 0};
                pos[j] = (i+2)*3.5e3;
                d.setPosition(pos);
                debris->addDebris(d);
            }
        }
        // calculated with wolfram alpha
        pre_calculated[0] = {-0.000010967387600710096587782776206071373077501857198479655576780,
                             0,
                             0
        };
        pre_calculated[1] = {0,
                             -0.000010967387600710096587782776206071373077501857198479655576780,
                             0
        };
        pre_calculated[2] = {0,
                             0,
                             0.0000219347752014201931755655524121427461550037143969593111535607
        };
        pre_calculated[3] = {-2.166397550757549943265733571569653941234934755255240607759e-6,
                             0,
                             0
        };
        pre_calculated[4] = {0,
                             -2.166397550757549943265733571569653941234934755255240607759e-6,
                             0
        };
        pre_calculated[5] = {0,
                             0,
                             4.3327951015150998865314671431393078824698695105104812155181e-6
        };
        pre_calculated[6] = {-6.854617250443810367364235128794608173438660749049784735487e-7,
                             0,
                             0
        };
        pre_calculated[7] = {0,
                             -6.854617250443810367364235128794608173438660749049784735487e-7,
                             0
        };
        pre_calculated[8] = {0,
                             0,
                             1.3709234500887620734728470257589216346877321498099569470975e-6
        };

    }

    void calcJ2(Debris::Debris &d, std::array<double,3> &acc_j2){
        double gme = 3.986004407799724e+5;
        double re = 6378.1363;
        double c20 = -4.84165371736e-4;

        double x = d.getPosition()[0];
        double y = d.getPosition()[1];
        double z = d.getPosition()[2];
        double n1 = gme*re*re*std::sqrt(5)*c20;
        double d1 = 2*std::sqrt(x*x+y*y+z*z);
        double d2 = (x*x+y*y+z*z)*(x*x+y*y+z*z);
        double n3 = 15*(z*z);
        double d3 = (x*x+y*y+z*z)*(x*x+y*y+z*z)*(x*x+y*y+z*z);
        acc_j2[0] = ((n1*x)/d1)*((3/d2)-(n3/d3));
        acc_j2[1] = ((n1*y)/d1)*((3/d2)-(n3/d3));
        acc_j2[2] = ((n1*z)/d1)*((9/d2)-(n3/d3));
    }
};

