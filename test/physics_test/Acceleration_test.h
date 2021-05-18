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
        pre_calculated[0] = {-0.01*Physics::GM_EARTH,0,0};
        pre_calculated[1] = {-0.0001*Physics::GM_EARTH,0,0};
        pre_calculated[2] = {-0.000001*Physics::GM_EARTH,0,0};
        pre_calculated[3] = {-0.00000001*Physics::GM_EARTH,0,0};
        pre_calculated[4] = {-0.0000000001*Physics::GM_EARTH,0,0};
        pre_calculated[5] = {-0.000000000001*Physics::GM_EARTH,0,0};
        pre_calculated[6] = {-(1/(std::sqrt(3)*300))*Physics::GM_EARTH,-(1/(std::sqrt(3)*300))*Physics::GM_EARTH,-(1/(std::sqrt(3)*300))*Physics::GM_EARTH};
        pre_calculated[7] = {-(1/(std::sqrt(3)*30000))*Physics::GM_EARTH,-(1/(std::sqrt(3)*30000))*Physics::GM_EARTH,-(1/(std::sqrt(3)*30000))*Physics::GM_EARTH};
        pre_calculated[8] = {-(1/(std::sqrt(3)*3000000))*Physics::GM_EARTH,-(1/(std::sqrt(3)*3000000))*Physics::GM_EARTH,-(1/(std::sqrt(3)*3000000))*Physics::GM_EARTH};
    }

    void calcKep(Debris::Debris &d, std::array<double,3> &acc_kep){
        double gme=3.986004407799724e+5;
        acc_kep[0] = -(gme*d.getPosition()[0])/std::pow((std::pow(d.getPosition()[0],2)+std::pow(d.getPosition()[1],2)+std::pow(d.getPosition()[2],2)),1.5);
        acc_kep[1] = -(gme*d.getPosition()[1])/std::pow((std::pow(d.getPosition()[0],2)+std::pow(d.getPosition()[1],2)+std::pow(d.getPosition()[2],2)),1.5);
        acc_kep[2] = -(gme*d.getPosition()[2])/std::pow((std::pow(d.getPosition()[0],2)+std::pow(d.getPosition()[1],2)+std::pow(d.getPosition()[2],2)),1.5);
    }
};

class J2ComponentTests : public ::testing::Test {
protected:
    virtual void SetUp() {

    }
};
