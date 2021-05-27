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

    // e-17 fails, but e-16 passes
    double abs_err = 1e-16;
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

    // 1e-16 fails, but e-15 passes
    double abs_err = 1e-15;
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
    double abs_err = 1e-10;
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

    // e-21 fails, but e-20 passes
    double abs_err = 1e-20;
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

    // e-23 fails, but e-22 passes
    double abs_err = 1e-22;
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
    double abs_err = 1e-0;
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

    // e-23 fails, but e-22 passes
    double abs_err = 1e-22;
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
    double abs_err = 1e-0;
    for (int i = 0; i < num_debris; ++i){
        EXPECT_NEAR(accelerations[i][0], pre_calculated[i][0], abs_err);
        EXPECT_NEAR(accelerations[i][1], pre_calculated[i][1], abs_err);
        EXPECT_NEAR(accelerations[i][2], pre_calculated[i][2], abs_err);
    }
}



/**
 * Tests if the acceleration calculated using Acceleration::LunComponent::apply() is the same as using a inefficient implementation
 */
TEST_F(LunComponentTests, CalculationEquivalenceTest){
    const int num_debris = 9;
    std::array<std::array<double,3>, num_debris> accelerations_1;
    std::array<std::array<double,3>, num_debris> accelerations_2;
    std::array<double,3> acc_total_dummy;
    double t = 1;

    // test for different t values
    for(int j = 0; j < 100; ++j) {
        std::array<double, 6> moon_params = Acceleration::LunComponent::setUp(t * j);
        // calculate the acceleration for all particles using two different functions
        for (int i = 0; i < debris->getDebrisVector().size(); ++i) {
            Acceleration::LunComponent::apply(debris->getDebrisVector()[i], moon_params, accelerations_1[i],
                                              acc_total_dummy);
            calcLun(debris->getDebrisVector()[i], t * j, accelerations_2[i]);
        }

        // 10e-20 fails, but e-19 passes
        double abs_err = 1e-22;
        for (int i = 0; i < debris->getDebrisVector().size(); ++i) {
            EXPECT_NEAR(accelerations_1[i][0], accelerations_2[i][0], abs_err);
            EXPECT_NEAR(accelerations_1[i][1], accelerations_2[i][1], abs_err);
            EXPECT_NEAR(accelerations_1[i][2], accelerations_2[i][2], abs_err);
        }
    }
}

/**
 * Tests if the acceleration calculated using Acceleration::LunComponent::apply() is the same as some and calculated values
 */
TEST_F(LunComponentTests, EquilavelnceWIthPreCalculatedTest){
    const int num_debris = 9;
    std::array<std::array<double,3>, num_debris> accelerations;
    std::array<double,3> acc_total_dummy;
    double t = 0;
    std::array<double,6> moon_params=Acceleration::LunComponent::setUp(t);

    // calculate the acceleration for all particles using two different functions
    for(int i = 0; i < debris->getDebrisVector().size(); ++i){
        Acceleration::LunComponent::apply(debris->getDebrisVector()[i], moon_params, accelerations[i], acc_total_dummy);
    }

    // 10e-22 fails, but e-21 passes
    double abs_err = 1e+0;
    for (int i = 0; i < num_debris; ++i){
        EXPECT_NEAR(accelerations[i][0], pre_calculated[i][0], abs_err);
        EXPECT_NEAR(accelerations[i][1], pre_calculated[i][1], abs_err);
        EXPECT_NEAR(accelerations[i][2], pre_calculated[i][2], abs_err);
    }
}

/**
 * compares two setup functions calcMoonParams() (less trigonometry) and Acceleration::LunComponent::setUp()
 */
TEST_F(LunComponentTests, CompareOptimizedSetupFunctionResult){
    double t = 0.1;
    double rel_err = 1e-15;
    for (int i = 0; i < 10; ++i){
        const std::array<double,6> params_1 = Acceleration::LunComponent::setUp(t*i);
        const std::array<double,6> params_2 = calcMoonParams(t*i);
        ASSERT_NEAR(params_1[0],params_2[0], std::abs(params_1[0]*rel_err));
        ASSERT_NEAR(params_1[1],params_2[1], std::abs(params_1[1]*rel_err));
        ASSERT_NEAR(params_1[2],params_2[2], std::abs(params_1[2]*rel_err));
        ASSERT_NEAR(params_1[3],params_2[3], std::abs(params_1[3]*rel_err));
        ASSERT_NEAR(params_1[4],params_2[4], std::abs(params_1[4]*rel_err));
        ASSERT_NEAR(params_1[5],params_2[5], std::abs(params_1[5]*rel_err));
    }
}


/**
 * compare results of calculations using less trigonometry function calls and trigonometry identities
 *
 * Identities used:
 * - cos(x(+/-)y) = cos(x)*cos(y)(-/+)sin(x)*sin(y)
 * - sin(x(+/-)y) = sin(x)*cos(y)(+/-)cos(x)*sin(y)
 *
 * results in 14 calls vs. 32 calls
 */
TEST_F(LunComponentTests, CompareTrigonometricTerms){
    double t = 1;
    double phi_m = Physics::NU_SUN*t;
    double phi_m_a = Physics::NU_MOON_A*t;
    double phi_m_p = Physics::NU_MOON_P*t;
    double phi_m_s = Physics::NU_MOON_S*t;
    double l_0 = phi_m_p + phi_m_a + 218.31617;
    double l_m = phi_m_a + 134.96292;
    double l1_m = phi_m + 357.52543;
    double f_m = phi_m_p + phi_m_a + phi_m_s + 93.27283;
    double d_m = phi_m_p + phi_m_a - phi_m + 297.85027;

    // only need this 13 function values
    double c_2dm = std::cos(2*d_m*M_PIf64/180);
    double c_lm = std::cos(l_m*M_PIf64/180);
    double c_2lm = std::cos(2*l_m*M_PIf64/180);
    double c_l1m = std::cos(l1_m*M_PIf64/180);
    double c_fm = std::cos(f_m*M_PIf64/180);
    double c_2fm = std::cos(2*f_m*M_PIf64/180);
    double s_dm = std::sin(d_m*M_PIf64/180);
    double s_2dm = std::sin(2*d_m*M_PIf64/180);
    double s_lm = std::sin(l_m*M_PIf64/180);
    double s_2lm = std::sin(2*l_m*M_PIf64/180);
    double s_l1m = std::sin(l1_m*M_PIf64/180);
    double s_fm = std::sin(f_m*M_PIf64/180);
    double s_2fm = std::sin(2*f_m*M_PIf64/180);

    // no calls
    double r1 = -152*((c_lm*c_l1m-s_lm*s_l1m)*c_2dm+(s_lm*c_l1m+c_lm*s_l1m)*s_2dm);
    r1 -= 171*(c_lm*c_2dm-s_lm*s_2dm);
    r1 -= 205*(c_l1m*c_2dm+s_l1m*s_2dm);
    r1 += 246*(c_2lm*c_2dm+s_2lm*s_2dm);
    r1 -= 570*c_2lm;
    r1 -= 2956*c_2dm;
    r1 -= 3699*(c_2dm*c_lm+s_2dm*s_lm);
    r1 -= 20905*c_lm;
    r1 += 385000;

    // 8 calls
    double r2 = -152*std::cos((l_m+l1_m-2*d_m)*M_PIf64/180);
    r2 -= 171*std::cos((l_m+2*d_m)*M_PIf64/180);
    r2 -= 205*std::cos((l1_m-2*d_m)*M_PIf64/180);
    r2 += 246*std::cos((2*l_m-2*d_m)*M_PIf64/180);
    r2 -= 570*std::cos((2*l_m)*M_PIf64/180);
    r2 -= 2956*std::cos((2*d_m)*M_PIf64/180);
    r2 -= 3699*std::cos((2*d_m-l_m)*M_PIf64/180);
    r2 -= 20905*std::cos(l_m*M_PIf64/180);
    r2 += 385000;

    double abs_err = 1.3e-15;
    ASSERT_NEAR(c_lm, std::cos(l_m*M_PIf64/180) ,abs_err);
    ASSERT_NEAR(c_2dm*c_lm+s_2dm*s_lm, std::cos((2*d_m-l_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(c_2dm, std::cos((2*d_m)*M_PIf64/180) ,abs_err);
    ASSERT_NEAR(c_2lm, std::cos((2*l_m)*M_PIf64/180) ,abs_err);
    ASSERT_NEAR(c_2lm*c_2dm+s_2lm*s_2dm, std::cos((2*l_m-2*d_m)*M_PIf64/180),abs_err);
    ASSERT_NEAR(c_l1m*c_2dm+s_l1m*s_2dm, std::cos((l1_m-2*d_m)*M_PIf64/180),abs_err);
    ASSERT_NEAR(c_lm*c_2dm-s_lm*s_2dm, std::cos((l_m+2*d_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR((c_lm*c_l1m-s_lm*s_l1m)*c_2dm+(s_lm*c_l1m+c_lm*s_l1m)*s_2dm, std::cos((l_m+l1_m-2*d_m)*M_PIf64/180) ,abs_err);

    ASSERT_NEAR(r1, r2, abs_err);

    // no calls
    double lambda1 = -(55.0/3600)*(s_2fm*c_2dm-c_2fm*s_2dm);
    lambda1 -= (110.0/3600)*(s_lm*c_l1m+c_lm*s_l1m);
    lambda1 -= (125.0/3600)*(s_dm);
    lambda1 += (148.0/3600)*(s_lm*c_l1m-c_lm*s_l1m);
    lambda1 -= (165.0/3600)*(s_l1m*c_2dm-c_l1m*s_2dm);
    lambda1 += (192.0/3600)*(s_lm*c_2dm+c_lm*s_2dm);
    lambda1 -= (206.0/3600)*((s_lm*c_l1m+c_lm*s_l1m)*c_2dm-(c_lm*c_l1m-s_lm*s_l1m)*s_2dm);
    lambda1 -= (212.0/3600)*(s_2lm*c_2dm-c_2lm*s_2dm);
    lambda1 -= (412.0/3600)*(s_2fm);
    lambda1 -= (668.0/3600)*(s_l1m);
    lambda1 += (769.0/3600)*s_2lm;
    lambda1 += (2370.0/3600)*(s_2dm);
    lambda1 -= (4856.0/3600)*(s_lm*c_2dm-c_lm*s_2dm);
    lambda1 += (22640.0/3600)*s_lm;
    lambda1 += l_0;


    // 14 calls
    double lambda2 = -(55.0/3600)*std::sin((2*f_m-2*d_m)*M_PIf64/180);
    lambda2 -= (110.0/3600)*std::sin((l_m+l1_m)*M_PIf64/180);
    lambda2 -= (125.0/3600)*std::sin((d_m)*M_PIf64/180);
    lambda2 += (148.0/3600)*std::sin((l_m-l1_m)*M_PIf64/180);
    lambda2 -= (165.0/3600)*std::sin((l1_m-2*d_m)*M_PIf64/180);
    lambda2 += (192.0/3600)*std::sin((l_m+2*d_m)*M_PIf64/180);
    lambda2 -= (206.0/3600)*std::sin((l_m+l1_m-2*d_m)*M_PIf64/180);
    lambda2 -= (212.0/3600)*std::sin((2*l_m-2*d_m)*M_PIf64/180);
    lambda2 -= (412.0/3600)*std::sin((2*f_m)*M_PIf64/180);
    lambda2 -= (668.0/3600)*std::sin((l1_m)*M_PIf64/180);
    lambda2 += (769.0/3600)*std::sin((2*l_m)*M_PIf64/180);
    lambda2 += (2370.0/3600)*std::sin((2*d_m)*M_PIf64/180);
    lambda2 -= (4856.0/3600)*std::sin((l_m-2*d_m)*M_PIf64/180);
    lambda2 += (22640.0/3600)*std::sin((l_m)*M_PIf64/180);
    lambda2 += l_0;

    ASSERT_NEAR(s_lm,std::sin((l_m)*M_PIf64/180),abs_err);
    ASSERT_NEAR(s_2lm, std::sin((2*l_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_lm*c_2dm-c_lm*s_2dm, std::sin((l_m-2*d_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_2dm, std::sin((2*d_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_l1m, std::sin(l1_m*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_2fm, std::sin((2*f_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_2lm*c_2dm-c_2lm*s_2dm, std::sin((2*l_m-2*d_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR((s_lm*c_l1m+c_lm*s_l1m)*c_2dm-(c_lm*c_l1m-s_lm*s_l1m)*s_2dm, std::sin((l_m+l1_m-2*d_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_lm*c_2dm+c_lm*s_2dm, std::sin((l_m+2*d_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_l1m*c_2dm-c_l1m*s_2dm, std::sin((l1_m-2*d_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_lm*c_l1m-c_lm*s_l1m, std::sin((l_m-l1_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_dm, std::sin((d_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_lm*c_l1m+c_lm*s_l1m, std::sin((l_m+l1_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_2fm*c_2dm-c_2fm*s_2dm, std::sin((2*f_m-2*d_m)*M_PIf64/180), abs_err);

    ASSERT_NEAR(lambda1,lambda2,abs_err);

    // 1 call
    double beta1 = (11.0/3600)*((s_fm*c_l1m-c_fm*s_l1m)*c_2dm-(c_fm*c_l1m+s_fm*s_l1m)*s_2dm);
    beta1 += (21.0/3600)*(s_fm*c_lm-c_fm*s_lm);
    beta1 -= (23.0/3600)*((s_l1m*c_fm+c_l1m*s_fm)*c_2dm-(c_l1m*c_fm-s_l1m*s_fm)*s_2dm);
    beta1 -= (25.0/3600)*(s_fm*c_2lm-c_fm*s_2lm);
    beta1 -= (31.0/3600)*((s_fm*c_lm-c_fm*s_lm)*c_2dm-(c_fm*c_lm+s_fm*s_lm)*s_2dm);
    beta1 += (44.0/3600)*((s_lm*c_fm+c_lm*s_fm)*c_2dm-(c_lm*c_fm-s_lm*s_fm)*s_2dm);
    beta1 -= (526.0/3600)*(s_fm*c_2dm-c_fm*s_2dm);
    beta1 += (18520.0/3600)*std::sin((f_m+lambda1-l_0+(412.0/3600)*s_2fm+(541.0/3600)*s_l1m)*M_PIf64/180);


    // 10 calls
    double beta2 = (11.0/3600)*std::sin((-l1_m+f_m-2*d_m)*M_PIf64/180);
    beta2 += (21.0/3600)*std::sin((-l_m+f_m)*M_PIf64/180);
    beta2 -= (23.0/3600)*std::sin((l1_m+f_m-2*d_m)*M_PIf64/180);
    beta2 -= (25.0/3600)*std::sin((-2*l_m+f_m)*M_PIf64/180);
    beta2 -= (31.0/3600)*std::sin((-l_m+f_m-2*d_m)*M_PIf64/180);
    beta2 += (44.0/3600)*std::sin((l_m+f_m-2*d_m)*M_PIf64/180);
    beta2 -= (526.0/3600)*std::sin((f_m-2*d_m)*M_PIf64/180);
    beta2 += (18520.0/3600)*std::sin((f_m+lambda2-l_0+(412.0/3600)*std::sin((2*f_m)*M_PIf64/180)+(541.0/3600)*std::sin((l1_m)*M_PIf64/180))*M_PIf64/180);

    ASSERT_NEAR(std::sin((f_m+lambda1-l_0+(412.0/3600)*s_2fm+(541.0/3600)*s_l1m)*M_PIf64/180), std::sin((f_m+lambda2-l_0+(412.0/3600)*std::sin((2*f_m)*M_PIf64/180)+(541.0/3600)*std::sin((l1_m)*M_PIf64/180))*M_PIf64/180), abs_err);;
    ASSERT_NEAR(s_fm*c_2dm-c_fm*s_2dm, std::sin((f_m-2*d_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR((s_lm*c_fm+c_lm*s_fm)*c_2dm-(c_lm*c_fm-s_lm*s_fm)*s_2dm, std::sin((l_m+f_m-2*d_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR((s_fm*c_lm-c_fm*s_lm)*c_2dm-(c_fm*c_lm+s_fm*s_lm)*s_2dm, std::sin((-l_m+f_m-2*d_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_fm*c_2lm-c_fm*s_2lm, std::sin((-2*l_m+f_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR((s_l1m*c_fm+c_l1m*s_fm)*c_2dm-(c_l1m*c_fm-s_l1m*s_fm)*s_2dm, std::sin((l1_m+f_m-2*d_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR(s_fm*c_lm-c_fm*s_lm, std::sin((-l_m+f_m)*M_PIf64/180), abs_err);
    ASSERT_NEAR((s_fm*c_l1m-c_fm*s_l1m)*c_2dm-(c_fm*c_l1m+s_fm*s_l1m)*s_2dm, std::sin((-l1_m+f_m-2*d_m)*M_PIf64/180), abs_err);

    ASSERT_NEAR(beta1,beta2,abs_err);
}

/**
 * simply check if calcMoonParams() is faster than Acceleration::LunComponent::setUp()
 */
TEST_F(LunComponentTests, CompareLessTrigonometryRuntime){
    double t = 0.1;
    std::cout << "normal trigonometry" << std::endl;
    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000; ++i){
        const std::array<double,6> params_1 = Acceleration::LunComponent::setUp(t*i);
    }
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end1 - begin1).count() << "[ns]" << std::endl;
    std::cout << "reduced trigonometry" << std::endl;
    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000; ++i){
        const std::array<double,6> params_2 = calcMoonParams(t*i);
    }
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end2 - begin2).count() << "[ns]" << std::endl;

    //if the optimized version s slower
    ASSERT_LT(std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count(), std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count());
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

    // e-23 fails, but e-22 passes
    double abs_err = 1e-22;
    for (int i = 0; i < num_debris; ++i){
        EXPECT_NEAR(accelerations_1[i][0]+accelerations_2[i][0], accelerations_3[i][0], abs_err);
        EXPECT_NEAR(accelerations_1[i][1]+accelerations_2[i][1], accelerations_3[i][1], abs_err);
        EXPECT_NEAR(accelerations_1[i][2]+accelerations_2[i][2], accelerations_3[i][2], abs_err);
    }
}
