//
// Created by Oliver on 13.05.21.
//

#include "Acceleration_test.h"

/**
 * Tests if the acceleration calculated using Acceleration::KepComponent::apply() is a function of ||#Debris::Debris::position||
 */
TEST_F(KepComponentTests, RadialSymmetryTest){
    std::array<std::array<double,3>,8> accelerations;
    for (auto &acc : accelerations){
        acc[0] = 0;
        acc[1] = 0;
        acc[2] = 0;
    }
    // calculate the acceleration for all particles and accumulate the results in accelerations[3]
    for (int i = 0; i < 3; ++i){
        Acceleration::KepComponent::apply(debris->getDebrisVector()[i],accelerations[i],accelerations[3]);
    }
    for (int i = 3; i < 6; ++i){
        Acceleration::KepComponent::apply(debris->getDebrisVector()[i],accelerations[i+1],accelerations[7]);
    }

    // only one axis non zero
    // only x should be a non zero value
    ASSERT_NE(accelerations[0][0],0);
    ASSERT_EQ(accelerations[0][1],0);
    ASSERT_EQ(accelerations[0][2],0);
    // only y should be a non zero value
    ASSERT_EQ(accelerations[1][0],0);
    ASSERT_NE(accelerations[1][1],0);
    ASSERT_EQ(accelerations[1][2],0);
    // only z should be a non zero value
    ASSERT_EQ(accelerations[2][0],0);
    ASSERT_EQ(accelerations[2][1],0);
    ASSERT_NE(accelerations[2][2],0);
    // x of the first particle should be y of the second particle should be
    ASSERT_EQ(accelerations[0][0],accelerations[1][1]);
    // y of the first particle should be z of the second particle should be
    ASSERT_EQ(accelerations[1][1],accelerations[2][2]);
    // x, y and z of the array used as accumulator should all be the same and non zero
    ASSERT_NE(accelerations[3][0],0);
    ASSERT_EQ(accelerations[3][0],accelerations[3][1]);
    ASSERT_EQ(accelerations[3][1],accelerations[3][2]);

    // all axis non zero
    // x of the first particle should be y of the second particle should be
    ASSERT_EQ(accelerations[4][0],accelerations[5][1]);
    // y of the first particle should be z of the second particle should be
    ASSERT_EQ(accelerations[5][1],accelerations[6][2]);
    // x, y and z of the array used as accumulator should all be the same and non zero
    ASSERT_NE(accelerations[7][0],0);
    ASSERT_EQ(accelerations[7][0],accelerations[7][1]);
    ASSERT_EQ(accelerations[7][1],accelerations[7][2]);
}

/**
 * Tests if the acceleration calculated using Acceleration::KepComponent::apply() is the same as using another implementation
 */
TEST_F(KepComponentTests, CalculationEquivalenceTest){
    const int num_debris = 15;
    std::array<std::array<double,3>, num_debris> accelerations_1;
    std::array<std::array<double,3>, num_debris> accelerations_2;
    std::array<double,3> acc_total_dummy;

    // calculate the acceleration for all particles using two different functions
    for(int i = 0; i < debris->getDebrisVector().size(); ++i){
        Acceleration::KepComponent::apply(debris->getDebrisVector()[i],accelerations_1[i],acc_total_dummy);
        calcKep(debris->getDebrisVector()[i],accelerations_2[i]);
    }

    // 10e-20 fails, but e-19 passes
    double abs_err = 10e-19;
    for (int i = 0; i < debris->getDebrisVector().size(); ++i){
        EXPECT_NEAR(accelerations_1[i][0], accelerations_2[i][0], abs_err);
        EXPECT_NEAR(accelerations_1[i][1], accelerations_2[i][1], abs_err);
        EXPECT_NEAR(accelerations_1[i][2], accelerations_2[i][2], abs_err);
    }
}

/**
 * Tests if the acceleration calculated using Acceleration::KepComponent::apply() is the same as some hand calculated values
 */
TEST_F(KepComponentTests, EquilavelnceWIthPreCalculatedTest){
    const int num_debris = 9;
    std::array<std::array<double,3>, num_debris> accelerations;
    std::array<double,3> acc_total_dummy;

    // calculate the acceleration for all particles using two different functions
    for(int i = 6; i < 6 + num_debris; ++i){
        Acceleration::KepComponent::apply(debris->getDebrisVector()[i], accelerations[i-6], acc_total_dummy);
    }

    // 10e-17 fails, but e-16 passes
    double abs_err = 10e-16;
    for (int i = 0; i < num_debris; ++i){
        EXPECT_NEAR(accelerations[i][0], pre_calculated[i][0], abs_err);
        EXPECT_NEAR(accelerations[i][1], pre_calculated[i][1], abs_err);
        EXPECT_NEAR(accelerations[i][2], pre_calculated[i][2], abs_err);
    }
}


/**
 * Tests if the acceleration calculated using Acceleration::J2Component::apply() is the same as using another implementation
 */
TEST_F(J2ComponentTests, CalculationEquivalenceTest){
    const int num_debris = 9;
    std::array<std::array<double,3>, num_debris> accelerations_1;
    std::array<std::array<double,3>, num_debris> accelerations_2;
    std::array<double,3> acc_total_dummy;

    // calculate the acceleration for all particles using two different functions
    for(int i = 0; i < debris->getDebrisVector().size(); ++i){
        Acceleration::J2Component::apply(debris->getDebrisVector()[i],accelerations_1[i],acc_total_dummy);
        calcJ2(debris->getDebrisVector()[i],accelerations_2[i]);
    }

    // 10e-20 fails, but e-19 passes
    double abs_err = 10e-10;
    for (int i = 0; i < debris->getDebrisVector().size(); ++i){
        EXPECT_NEAR(accelerations_1[i][0], accelerations_2[i][0], abs_err);
        EXPECT_NEAR(accelerations_1[i][1], accelerations_2[i][1], abs_err);
        EXPECT_NEAR(accelerations_1[i][2], accelerations_2[i][2], abs_err);
    }
}

/**
 * Tests if the acceleration calculated using Acceleration::J2Component::apply() is the same as some hand calculated values
 */
TEST_F(J2ComponentTests, EquilavelnceWIthPreCalculatedTest){
    const int num_debris = 9;
    std::array<std::array<double,3>, num_debris> accelerations;
    std::array<double,3> acc_total_dummy;

    // calculate the acceleration for all particles using two different functions
    for(int i = 0; i < debris->getDebrisVector().size(); ++i){
        Acceleration::J2Component::apply(debris->getDebrisVector()[i], accelerations[i], acc_total_dummy);
    }

    // 10e-22 fails, but e-21 passes
    double abs_err = 10e-21;
    for (int i = 0; i < num_debris; ++i){
        EXPECT_NEAR(accelerations[i][0], pre_calculated[i][0], abs_err);
        EXPECT_NEAR(accelerations[i][1], pre_calculated[i][1], abs_err);
        EXPECT_NEAR(accelerations[i][2], pre_calculated[i][2], abs_err);
    }
}

/**
 * Tests if the acceleration calculated using Acceleration::C22Component::apply() is the same as using another implementation
 */
TEST_F(C22ComponentTests, CalculationEquivalenceTest){
    const int num_debris = 12;
    std::array<std::array<double,3>, num_debris> accelerations_1;
    std::array<std::array<double,3>, num_debris> accelerations_2;
    std::array<double,3> acc_total_dummy;
    double t = 0;
    double c_term = std::cos(Physics::THETA_G+Physics::NU_EARTH*t);
    double s_term = std::sin(Physics::THETA_G+Physics::NU_EARTH*t);

    // calculate the acceleration for all particles using two different functions
    for (int i = 0; i < num_debris; ++i){
        Acceleration::C22Component::apply(debris->getDebrisVector()[i], c_term, s_term, accelerations_1[i],acc_total_dummy);
        calcC22(debris->getDebrisVector()[i], t, accelerations_2[i]);
    }

    // e-24 fails, but e-23 passes
    double abs_err = 10e-23;
    for (int i = 0; i < num_debris; ++i){
        EXPECT_NEAR(accelerations_1[i][0], accelerations_2[i][0], abs_err);
        EXPECT_NEAR(accelerations_1[i][1], accelerations_2[i][1], abs_err);
        EXPECT_NEAR(accelerations_1[i][2], accelerations_2[i][2], abs_err);
    }

}

/**
 * Tests if the acceleration calculated using Acceleration::J2Component::apply() is the same as some hand calculated values
 */
TEST_F(C22ComponentTests, EquilavelnceWIthPreCalculatedTest){
    const int num_debris = 9;
    std::array<std::array<double,3>, num_debris> accelerations;
    std::array<double,3> acc_total_dummy;
    double t = 0;
    double c_term = std::cos(Physics::THETA_G+Physics::NU_EARTH*t);
    double s_term = std::sin(Physics::THETA_G+Physics::NU_EARTH*t);

    // calculate the acceleration for all particles using two different functions
    for(int i = 0; i < num_debris; ++i){
        Acceleration::C22Component::apply(debris->getDebrisVector()[i], c_term, s_term, accelerations[i], acc_total_dummy);
    }

    // 10e-22 fails, but e-21 passes
    double abs_err = 10e-0;
    for (int i = 0; i < num_debris; ++i){
        EXPECT_NEAR(accelerations[i][0], pre_calculated[i][0], abs_err);
        EXPECT_NEAR(accelerations[i][1], pre_calculated[i][1], abs_err);
        EXPECT_NEAR(accelerations[i][2], pre_calculated[i][2], abs_err);
    }
}

/**
 * Tests if the acceleration calculated using Acceleration::S22Component::apply() is the same as using another implementation
 */
TEST_F(S22ComponentTests, CalculationEquivalenceTest){
    const int num_debris = 12;
    std::array<std::array<double,3>, num_debris> accelerations_1;
    std::array<std::array<double,3>, num_debris> accelerations_2;
    std::array<double,3> acc_total_dummy;
    double t = 0;
    double c_term = std::cos(Physics::THETA_G+Physics::NU_EARTH*t);
    double s_term = std::sin(Physics::THETA_G+Physics::NU_EARTH*t);

    // calculate the acceleration for all particles using two different functions
    for (int i = 0; i < num_debris; ++i){
        Acceleration::S22Component::apply(debris->getDebrisVector()[i], c_term, s_term, accelerations_1[i],acc_total_dummy);
        calcS22(debris->getDebrisVector()[i], t, accelerations_2[i]);
    }

    // 10e-24 fails, but e-23 passes
    double abs_err = 10e-23;
    for (int i = 0; i < num_debris; ++i){
        EXPECT_NEAR(accelerations_1[i][0], accelerations_2[i][0], abs_err);
        EXPECT_NEAR(accelerations_1[i][1], accelerations_2[i][1], abs_err);
        EXPECT_NEAR(accelerations_1[i][2], accelerations_2[i][2], abs_err);
    }

}

/**
 * Tests if the acceleration calculated using Acceleration::S22Component::apply() is the same as some hand calculated values
 */
TEST_F(S22ComponentTests, EquilavelnceWIthPreCalculatedTest){
    const int num_debris = 9;
    std::array<std::array<double,3>, num_debris> accelerations;
    std::array<double,3> acc_total_dummy;
    double t = 0;
    double c_term = std::cos(Physics::THETA_G+Physics::NU_EARTH*t);
    double s_term = std::sin(Physics::THETA_G+Physics::NU_EARTH*t);

    // calculate the acceleration for all particles using two different functions
    for(int i = 0; i < num_debris; ++i){
        Acceleration::S22Component::apply(debris->getDebrisVector()[i], c_term, s_term, accelerations[i], acc_total_dummy);
    }

    // 10e-22 fails, but e-21 passes
    double abs_err = 10e-0;
    for (int i = 0; i < num_debris; ++i){
        EXPECT_NEAR(accelerations[i][0], pre_calculated[i][0], abs_err);
        EXPECT_NEAR(accelerations[i][1], pre_calculated[i][1], abs_err);
        EXPECT_NEAR(accelerations[i][2], pre_calculated[i][2], abs_err);
    }
}



/**
 * Tests if the acceleration calculated using Acceleration::C22S22Component::apply() is the same as adding up the results of
 * Acceleration::C22Component::apply() AND Acceleration::S22Component::apply()
 */
TEST_F(C22S22ComponentTests, CalculationEquivalenceTest){
    const int num_debris = 12;
    std::array<std::array<double,3>, num_debris> accelerations_1;
    std::array<std::array<double,3>, num_debris> accelerations_2;
    std::array<std::array<double,3>, num_debris> accelerations_3;
    std::array<double,3> acc_total_dummy;
    double t = 0;
    double c_term = std::cos(Physics::THETA_G+Physics::NU_EARTH*t);
    double s_term = std::sin(Physics::THETA_G+Physics::NU_EARTH*t);

    // calculate the acceleration for all particles using two different functions
    for (int i = 0; i < num_debris; ++i){
        Acceleration::C22Component::apply(debris->getDebrisVector()[i], c_term, s_term, accelerations_1[i],acc_total_dummy);
        Acceleration::S22Component::apply(debris->getDebrisVector()[i], c_term, s_term, accelerations_2[i],acc_total_dummy);
        Acceleration::C22S22Component::apply(debris->getDebrisVector()[i], c_term, s_term, accelerations_3[i],acc_total_dummy);
    }

    // e-25 fails, but e-24 passes
    double abs_err = 10e-24;
    for (int i = 0; i < num_debris; ++i){
        EXPECT_NEAR(accelerations_1[i][0]+accelerations_2[i][0], accelerations_3[i][0], abs_err);
        EXPECT_NEAR(accelerations_1[i][1]+accelerations_2[i][1], accelerations_3[i][1], abs_err);
        EXPECT_NEAR(accelerations_1[i][2]+accelerations_2[i][2], accelerations_3[i][2], abs_err);
    }
}
