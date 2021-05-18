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

    virtual void SetUp() {
        debris = std::make_shared<Debris::DebrisContainer>();
        Debris::Debris d;
        for (int i = 0; i <3; ++i) {
            std::array<double,3> pos{0,0,0};
            pos[i] = 10000;
            d.setPosition(pos);
            debris->addDebris(d);
        }
        for (int i = 0; i < 3; ++i){
            std::array<double,3> pos{0,0,0};
            pos[i] = 5000;
            pos[(i+1)%3] = 4321;
            pos[(i+2)%3] = 3210;
            d.setPosition(pos);
            debris->addDebris(d);
        }
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
