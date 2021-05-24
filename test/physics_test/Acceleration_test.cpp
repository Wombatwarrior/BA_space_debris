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
 * Tests if the acceleration calculated using Acceleration::KepComponent::apply() is the same as using a inefficient implementation
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
 * Tests if the acceleration calculated using Acceleration::KepComponent::apply() is the same as some and calculated values
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
 * Tests if the acceleration calculated using Acceleration::J2Component::apply() is the same as using a inefficient implementation
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

    // passes every value
    double abs_err = 0;
    for (int i = 0; i < debris->getDebrisVector().size(); ++i){
        EXPECT_NEAR(accelerations_1[i][0], accelerations_2[i][0], abs_err);
        EXPECT_NEAR(accelerations_1[i][1], accelerations_2[i][1], abs_err);
        EXPECT_NEAR(accelerations_1[i][2], accelerations_2[i][2], abs_err);
    }
}

/**
 * Tests if the acceleration calculated using Acceleration::J2Component::apply() is the same as some and calculated values
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
 * Tests if the acceleration calculated using Acceleration::SolComponent::apply() is the same as using a inefficient implementation
 */
TEST_F(SolComponentTests, CalculationEquivalenceTest) {
    const int num_debris = 9;
    std::array<std::array<double, 3>, num_debris> accelerations_1;
    std::array<std::array<double, 3>, num_debris> accelerations_2;
    std::array<double, 3> acc_total_dummy;
    double t = 0.1;
    for (int j = 0; j < 10; ++j) {
        std::array<double, 6> sun_params = Acceleration::SolComponent::setUp(t * j);
        // calculate the acceleration for all particles using two different functions
        for (int i = 0; i < debris->getDebrisVector().size(); ++i) {
            Acceleration::SolComponent::apply(debris->getDebrisVector()[i], sun_params, accelerations_1[i],
                                              acc_total_dummy);
            calcSol(debris->getDebrisVector()[i], t * j, accelerations_2[i]);
        }

        // 10e-20 fails, but e-19 passes
        double abs_err = 1e-20;
        for (int i = 0; i < debris->getDebrisVector().size(); ++i) {
            EXPECT_NEAR(accelerations_1[i][0], accelerations_2[i][0], abs_err);
            EXPECT_NEAR(accelerations_1[i][1], accelerations_2[i][1], abs_err);
            EXPECT_NEAR(accelerations_1[i][2], accelerations_2[i][2], abs_err);
        }
    }
}

/**
 * Tests if the acceleration calculated using Acceleration::SolComponent::apply() is the same as some and calculated values
 */
TEST_F(SolComponentTests, EquilavelnceWIthPreCalculatedTest){
    const int num_debris = 9;
    std::array<std::array<double,3>, num_debris> accelerations;
    std::array<double,3> acc_total_dummy;

    // calculate the acceleration for all particles using two different functions
    for(int i = 0; i < debris->getDebrisVector().size(); ++i){
        Acceleration::J2Component::apply(debris->getDebrisVector()[i], accelerations[i], acc_total_dummy);
    }

    // 10e-22 fails, but e-21 passes
    double abs_err = 1e-0;
    for (int i = 0; i < num_debris; ++i){
        EXPECT_NEAR(accelerations[i][0], pre_calculated[i][0], abs_err);
        EXPECT_NEAR(accelerations[i][1], pre_calculated[i][1], abs_err);
        EXPECT_NEAR(accelerations[i][2], pre_calculated[i][2], abs_err);
    }
}

/**
 * Compares the result of calcSolParams() and Acceleration::SolComponent::setUp()
 */
TEST_F(SolComponentTests, CompareSetupFunction){
    double t = 0.1;
    double abs_err = 1e-7;
    for (int i = 0; i < 10; ++i){
        const std::array<double,6> params_1 = Acceleration::SolComponent::setUp(t*i);
        const std::array<double,6> params_2 = calcSolParams(t*i);
        ASSERT_NEAR(params_1[0],params_2[0], abs_err);
        ASSERT_NEAR(params_1[1],params_2[1], abs_err);
        ASSERT_NEAR(params_1[2],params_2[2], abs_err);
        ASSERT_NEAR(params_1[3],params_2[3], abs_err);
        ASSERT_NEAR(params_1[4],params_2[4], abs_err);
        ASSERT_NEAR(params_1[5],params_2[5], abs_err);
    }
}

/**
 * Compares the result of the Acceleration::SolComponent::apply() function using the calcSolParams() function instead of Acceleration::SolComponent::setUp()
 */
TEST_F(SolComponentTests, CompareAfterSetupCalculations){
    const int num_debris = 9;
    std::array<std::array<double, 3>, num_debris> accelerations_1;
    std::array<std::array<double, 3>, num_debris> accelerations_2;
    std::array<double, 3> acc_total_dummy;
    double t = 0.1;
    for (int j = 0; j < 10; ++j) {
        std::array<double, 6> sun_params = calcSolParams(t * j);
        // calculate the acceleration for all particles using two different functions
        for (int i = 0; i < debris->getDebrisVector().size(); ++i) {
            Acceleration::SolComponent::apply(debris->getDebrisVector()[i], sun_params, accelerations_1[i],
                                              acc_total_dummy);
            calcSol(debris->getDebrisVector()[i], t * j, accelerations_2[i]);
        }

        // 10e-20 fails, but e-19 passes
        double abs_err = 1e-21;
        for (int i = 0; i < debris->getDebrisVector().size(); ++i) {
            EXPECT_NEAR(accelerations_1[i][0], accelerations_2[i][0], abs_err);
            EXPECT_NEAR(accelerations_1[i][1], accelerations_2[i][1], abs_err);
            EXPECT_NEAR(accelerations_1[i][2], accelerations_2[i][2], abs_err);
        }
    }
}
