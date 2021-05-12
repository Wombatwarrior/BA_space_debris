//
// Created by ubuntu on 12.05.21.
//

#include "gtest/gtest.h"
#include "SetupDummy.h"

TEST(getOneTest, test1){
    EXPECT_EQ(SetupDummy::getOne(),1);
}

TEST(getTwoTest, test1){
    EXPECT_EQ(SetupDummy::getTwo(),2);
}

TEST(twoTimesOneIsTwo, test1){
    EXPECT_EQ(SetupDummy::getOne()+SetupDummy::getOne(),SetupDummy::getTwo());
}
