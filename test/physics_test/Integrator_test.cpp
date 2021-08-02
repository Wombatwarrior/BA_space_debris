//
// Created by Oliver on 13.05.21.
//

#include "Integrator_test.h"
#ifdef HEYOKA_IS_PRESENT
#include <stdlib.h>
#include <time.h>

// setup taylor integrator and print it to check if the state etc. are correct
TEST_F(CompareWithHeyokaTests, showTaylorIntegrator)
{
    std::cout << *ta_total << std::endl;

    for (int i = 0; i < 8; ++i) {
        std::cout << *ta_components[i] << std::endl;
    }

    std::cout << *ta_split << std::endl;
}

// compare calculated values of KepComponent
TEST_F(CompareWithHeyokaTests, compareKep)
{
    std::cout << "\nKepler" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i) {
        d.setPosition({ 3500. * (i + 2), 0, 0 });
        d.setVelocity({ 0, 0, 0 });
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        prepareRun(*i_components[Acceleration::KEP], *ta_components[Acceleration::KEP], d);
        // integrate over time
        bool crash_i = false;
        bool crash_ta = false;
        for (double t = start_t; t <= end_t; t += delta_t) {
            std::array<double, 3> pos_i = i_components[Acceleration::KEP]->getDebris().getDebrisVector()[0].getPosition();
            std::array<double, 3> pos_ta { ta_components[Acceleration::KEP]->get_state()[0],
                ta_components[Acceleration::KEP]->get_state()[1],
                ta_components[Acceleration::KEP]->get_state()[2] };
            if (MathUtils::euclideanNorm(pos_i) <= Physics::R_EARTH) {
                if (!crash_i)
                    std::cout << "integrator hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::KEP], *ta_components[Acceleration::KEP]);
                }
                crash_i = true;
                if (crash_ta && crash_i)
                    break;
            }
            if (MathUtils::euclideanNorm(pos_ta) <= Physics::R_EARTH) {
                if (!crash_ta)
                    std::cout << "heyoka hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::KEP], *ta_components[Acceleration::KEP]);
                }
                crash_ta = true;
            }
            if (crash_i && crash_ta)
                break;
            // integrate time step
            if (!crash_i)
                i_components[Acceleration::KEP]->integrate();
            if (!crash_ta)
                ta_components[Acceleration::KEP]->propagate_for(delta_t);
        }
        if (!(crash_i || crash_ta))
            // compare result
            showErrors(*i_components[Acceleration::KEP], *ta_components[Acceleration::KEP]);
        std::cout << std::endl;
    }
}
// compare calculated values of J2Component
TEST_F(CompareWithHeyokaTests, compareJ2)
{
    std::cout << "\nJ2" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i) {
        d.setPosition({ 3500. * (i + 2), 0, 0 });
        d.setVelocity({ 0, 0, 0 });
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        prepareRun(*i_components[Acceleration::J2], *ta_components[Acceleration::J2], d);
        // integrate over time
        bool crash_i = false;
        bool crash_ta = false;
        for (double t = start_t; t <= end_t; t += delta_t) {
            std::array<double, 3> pos_i = i_components[Acceleration::J2]->getDebris().getDebrisVector()[0].getPosition();
            std::array<double, 3> pos_ta { ta_components[Acceleration::J2]->get_state()[0],
                ta_components[Acceleration::J2]->get_state()[1],
                ta_components[Acceleration::J2]->get_state()[2] };
            if (MathUtils::euclideanNorm(pos_i) <= Physics::R_EARTH) {
                if (!crash_i)
                    std::cout << "integrator hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::J2], *ta_components[Acceleration::J2]);
                }
                crash_i = true;
                if (crash_ta && crash_i)
                    break;
            }
            if (MathUtils::euclideanNorm(pos_ta) <= Physics::R_EARTH) {
                if (!crash_ta)
                    std::cout << "heyoka hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::J2], *ta_components[Acceleration::J2]);
                }
                crash_ta = true;
            }
            if (crash_i && crash_ta)
                break;
            // integrate time step
            if (!crash_i)
                i_components[Acceleration::J2]->integrate();
            if (!crash_ta)
                ta_components[Acceleration::J2]->propagate_for(delta_t);
        }
        if (!(crash_i || crash_ta))
            // compare result
            showErrors(*i_components[Acceleration::J2], *ta_components[Acceleration::J2]);
        std::cout << std::endl;
    }
}
// compare calculated values of C22Component
TEST_F(CompareWithHeyokaTests, compareC22)
{
    std::cout << "\nC22" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i) {
        d.setPosition({ 3500. * (i + 2), 0, 0 });
        d.setVelocity({ 0, 0, 0 });
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        prepareRun(*i_components[Acceleration::C22], *ta_components[Acceleration::C22], d);
        // integrate over time
        bool crash_i = false;
        bool crash_ta = false;
        for (double t = start_t; t <= end_t; t += delta_t) {
            std::array<double, 3> pos_i = i_components[Acceleration::C22]->getDebris().getDebrisVector()[0].getPosition();
            std::array<double, 3> pos_ta { ta_components[Acceleration::C22]->get_state()[0],
                ta_components[Acceleration::C22]->get_state()[1],
                ta_components[Acceleration::C22]->get_state()[2] };
            if (MathUtils::euclideanNorm(pos_i) <= Physics::R_EARTH) {
                if (!crash_i)
                    std::cout << "integrator hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::C22], *ta_components[Acceleration::C22]);
                }
                crash_i = true;
                if (crash_ta && crash_i)
                    break;
            }
            if (MathUtils::euclideanNorm(pos_ta) <= Physics::R_EARTH) {
                if (!crash_ta)
                    std::cout << "heyoka hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::C22], *ta_components[Acceleration::C22]);
                }
                crash_ta = true;
            }
            if (crash_i && crash_ta)
                break;
            // integrate time step
            if (!crash_i)
                i_components[Acceleration::C22]->integrate();
            if (!crash_ta)
                ta_components[Acceleration::C22]->propagate_for(delta_t);
        }
        if (!(crash_i || crash_ta))
            // compare result
            showErrors(*i_components[Acceleration::C22], *ta_components[Acceleration::C22]);
        std::cout << std::endl;
    }
}
// compare calculated values of S22Component
TEST_F(CompareWithHeyokaTests, compareS22)
{
    std::cout << "\nS22" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i) {
        d.setPosition({ 3500. * (i + 2), 0, 0 });
        d.setVelocity({ 0, 0, 0 });
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        prepareRun(*i_components[Acceleration::S22], *ta_components[Acceleration::S22], d);
        // integrate over time
        bool crash_i = false;
        bool crash_ta = false;
        for (double t = start_t; t <= end_t; t += delta_t) {
            std::array<double, 3> pos_i = i_components[Acceleration::S22]->getDebris().getDebrisVector()[0].getPosition();
            std::array<double, 3> pos_ta { ta_components[Acceleration::S22]->get_state()[0],
                ta_components[Acceleration::S22]->get_state()[1],
                ta_components[Acceleration::S22]->get_state()[2] };
            if (MathUtils::euclideanNorm(pos_i) <= Physics::R_EARTH) {
                if (!crash_i)
                    std::cout << "integrator hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::S22], *ta_components[Acceleration::S22]);
                }
                crash_i = true;
                if (crash_ta && crash_i)
                    break;
            }
            if (MathUtils::euclideanNorm(pos_ta) <= Physics::R_EARTH) {
                if (!crash_ta)
                    std::cout << "heyoka hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::S22], *ta_components[Acceleration::S22]);
                }
                crash_ta = true;
            }
            if (crash_i && crash_ta)
                break;
            // integrate time step
            if (!crash_i)
                i_components[Acceleration::S22]->integrate();
            if (!crash_ta)
                ta_components[Acceleration::S22]->propagate_for(delta_t);
        }
        if (!(crash_i || crash_ta))
            // compare result
            showErrors(*i_components[Acceleration::S22], *ta_components[Acceleration::S22]);
        std::cout << std::endl;
    }
}
// compare calculated values of LunComponent
TEST_F(CompareWithHeyokaTests, compareLun)
{
    std::cout << "\nLunar Tide" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i) {
        d.setPosition({ 3500. * (i + 2), 0, 0 });
        d.setVelocity({ 0, 0, 0 });
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        prepareRun(*i_components[Acceleration::LUN], *ta_components[Acceleration::LUN], d);
        // integrate over time
        bool crash_i = false;
        bool crash_ta = false;
        for (double t = start_t; t <= end_t; t += delta_t) {
            std::array<double, 3> pos_i = i_components[Acceleration::LUN]->getDebris().getDebrisVector()[0].getPosition();
            std::array<double, 3> pos_ta { ta_components[Acceleration::LUN]->get_state()[0],
                ta_components[Acceleration::LUN]->get_state()[1],
                ta_components[Acceleration::LUN]->get_state()[2] };
            if (MathUtils::euclideanNorm(pos_i) <= Physics::R_EARTH) {
                if (!crash_i)
                    std::cout << "integrator hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::LUN], *ta_components[Acceleration::LUN]);
                }
                crash_i = true;
                if (crash_ta && crash_i)
                    break;
            }
            if (MathUtils::euclideanNorm(pos_ta) <= Physics::R_EARTH) {
                if (!crash_ta)
                    std::cout << "heyoka hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::LUN], *ta_components[Acceleration::LUN]);
                }
                crash_ta = true;
            }
            if (crash_i && crash_ta)
                break;
            // integrate time step
            if (!crash_i)
                i_components[Acceleration::LUN]->integrate();
            if (!crash_ta)
                ta_components[Acceleration::LUN]->propagate_for(delta_t);
        }
        if (!(crash_i || crash_ta))
            // compare result
            showErrors(*i_components[Acceleration::LUN], *ta_components[Acceleration::LUN]);
        std::cout << std::endl;
    }
}
// compare calculated values of SolComponent
TEST_F(CompareWithHeyokaTests, compareSol)
{
    std::cout << "\nSolar tide" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i) {
        d.setPosition({ 3500. * (i + 2), 0, 0 });
        d.setVelocity({ 0, 0, 0 });
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        prepareRun(*i_components[Acceleration::SOL], *ta_components[Acceleration::SOL], d);
        // integrate over time
        bool crash_i = false;
        bool crash_ta = false;
        for (double t = start_t; t <= end_t; t += delta_t) {
            std::array<double, 3> pos_i = i_components[Acceleration::SOL]->getDebris().getDebrisVector()[0].getPosition();
            std::array<double, 3> pos_ta { ta_components[Acceleration::SOL]->get_state()[0],
                ta_components[Acceleration::SOL]->get_state()[1],
                ta_components[Acceleration::SOL]->get_state()[2] };
            if (MathUtils::euclideanNorm(pos_i) <= Physics::R_EARTH) {
                if (!crash_i)
                    std::cout << "integrator hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::SOL], *ta_components[Acceleration::SOL]);
                }
                crash_i = true;
                if (crash_ta && crash_i)
                    break;
            }
            if (MathUtils::euclideanNorm(pos_ta) <= Physics::R_EARTH) {
                if (!crash_ta)
                    std::cout << "heyoka hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::SOL], *ta_components[Acceleration::SOL]);
                }
                crash_ta = true;
            }
            if (crash_i && crash_ta)
                break;
            // integrate time step
            if (!crash_i)
                i_components[Acceleration::SOL]->integrate();
            if (!crash_ta)
                ta_components[Acceleration::SOL]->propagate_for(delta_t);
        }
        if (!(crash_i || crash_ta))
            // compare result
            showErrors(*i_components[Acceleration::SOL], *ta_components[Acceleration::SOL]);
        std::cout << std::endl;
    }
}
// compare calculated values of SRPComponent
TEST_F(CompareWithHeyokaTests, compareSRP)
{
    std::cout << "\nSolar Radiation Pressure" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i) {
        d.setPosition({ 3500. * (i + 2), 0, 0 });
        d.setVelocity({ 0, 0, 0 });
        d.setAom(2e-5);
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        prepareRun(*i_components[Acceleration::SRP], *ta_components[Acceleration::SRP], d);
        // set heyoka parameters
        ta_components[Acceleration::SRP]->get_pars_data()[0] = d.getAom();
        // integrate over time
        bool crash_i = false;
        bool crash_ta = false;
        for (double t = start_t; t <= end_t; t += delta_t) {
            std::array<double, 3> pos_i = i_components[Acceleration::SRP]->getDebris().getDebrisVector()[0].getPosition();
            std::array<double, 3> pos_ta { ta_components[Acceleration::SRP]->get_state()[0],
                ta_components[Acceleration::SRP]->get_state()[1],
                ta_components[Acceleration::SRP]->get_state()[2] };
            if (MathUtils::euclideanNorm(pos_i) <= Physics::R_EARTH) {
                if (!crash_i)
                    std::cout << "integrator hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::SRP], *ta_components[Acceleration::SRP]);
                }
                crash_i = true;
                if (crash_ta && crash_i)
                    break;
            }
            if (MathUtils::euclideanNorm(pos_ta) <= Physics::R_EARTH) {
                if (!crash_ta)
                    std::cout << "heyoka hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::SRP], *ta_components[Acceleration::SRP]);
                }
                crash_ta = true;
            }
            if (crash_i && crash_ta)
                break;
            // integrate time step
            if (!crash_i)
                i_components[Acceleration::SRP]->integrate();
            if (!crash_ta)
                ta_components[Acceleration::SRP]->propagate_for(delta_t);
        }
        if (!(crash_i || crash_ta))
            // compare result
            showErrors(*i_components[Acceleration::SRP], *ta_components[Acceleration::SRP]);
        std::cout << std::endl;
    }
}
// compare calculated values of DragComponent
TEST_F(CompareWithHeyokaTests, compareDrag)
{
    std::cout << "\nAtmospheric Drag" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i) {
        d.setPosition({ (Physics::R_EARTH + ((i + 1) * 20)), 0, 0 });
        d.setVelocity({ 1., 1., 1. });
        d.setBcInv(0.05);
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        prepareRun(*i_components[Acceleration::DRAG], *ta_components[Acceleration::DRAG], d);
        // set heyoka parameters
        ta_components[Acceleration::DRAG]->get_pars_data()[1] = d.getBcInv();
        // integrate over time
        bool crash_i = false;
        bool crash_ta = false;
        for (double t = start_t; t <= end_t; t += delta_t) {
            std::array<double, 3> pos_i = i_components[Acceleration::DRAG]->getDebris().getDebrisVector()[0].getPosition();
            std::array<double, 3> pos_ta { ta_components[Acceleration::DRAG]->get_state()[0],
                ta_components[Acceleration::DRAG]->get_state()[1],
                ta_components[Acceleration::DRAG]->get_state()[2] };
            if (MathUtils::euclideanNorm(pos_i) <= Physics::R_EARTH) {
                if (!crash_i)
                    std::cout << "integrator hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::DRAG], *ta_components[Acceleration::DRAG]);
                }
                crash_i = true;
                if (crash_ta && crash_i)
                    break;
            }
            if (MathUtils::euclideanNorm(pos_ta) <= Physics::R_EARTH) {
                if (!crash_ta)
                    std::cout << "heyoka hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_components[Acceleration::DRAG], *ta_components[Acceleration::DRAG]);
                }
                crash_ta = true;
            }
            if (crash_i && crash_ta)
                break;
            // integrate time step
            if (!crash_i)
                i_components[Acceleration::DRAG]->integrate();
            if (!crash_ta)
                ta_components[Acceleration::DRAG]->propagate_for(delta_t);
        }
        if (!(crash_i || crash_ta))
            // compare result
            showErrors(*i_components[Acceleration::DRAG], *ta_components[Acceleration::DRAG]);
        std::cout << std::endl;
    }
}
// compare calculated values of all Components
TEST_F(CompareWithHeyokaTests, compareTotal)
{
    std::cout << "\nAll Components" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i) {
        d.setPosition({ 3500. * (i + 2), 0, 0 });
        d.setVelocity({ 5., 5., 5. });
        d.setAom(2e-5);
        d.setBcInv(0.05);
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        prepareRun(*i_total, *ta_total, d);
        // set heyoka parameters
        ta_total->get_pars_data()[0] = d.getAom();
        ta_total->get_pars_data()[1] = d.getBcInv();
        // integrate over time
        bool crash_i = false;
        bool crash_ta = false;
        for (double t = start_t; t <= end_t; t += delta_t) {
            std::array<double, 3> pos_i = i_total->getDebris().getDebrisVector()[0].getPosition();
            std::array<double, 3> pos_ta { ta_total->get_state()[0],
                ta_total->get_state()[1],
                ta_total->get_state()[2] };
            if (MathUtils::euclideanNorm(pos_i) <= Physics::R_EARTH) {
                if (!crash_i)
                    std::cout << "integrator hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_total, *ta_total);
                }
                crash_i = true;
                if (crash_ta && crash_i)
                    break;
            }
            if (MathUtils::euclideanNorm(pos_ta) <= Physics::R_EARTH) {
                if (!crash_ta)
                    std::cout << "heyoka hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_total, *ta_total);
                }
                crash_ta = true;
            }
            if (crash_i && crash_ta)
                break;
            // integrate time step
            if (!crash_i)
                i_total->integrate();
            if (!crash_ta)
                ta_total->propagate_for(delta_t);
        }
        if (!(crash_i || crash_ta))
            // compare result
            showErrors(*i_total, *ta_total);
        std::cout << std::endl;
    }
}
// compare calculated values of all Components with random debris
TEST_F(CompareWithHeyokaTests, compareTotalRandom)
{
    std::cout << "\nAll Components Random" << std::endl;
    // random number generator
    auto seed = time(NULL);
    srand(seed);
    std::cout << "Seed: " << seed << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i) {
        // use values between 50 km above ground and 30000 km above that
        d.setPosition({ Physics::R_EARTH + 50 + (.5 * (rand() % 60000)), Physics::R_EARTH + 50 + (.5 * (rand() % 60000)), Physics::R_EARTH + 50 + (.5 * (rand() % 60000)) });
        // use values between 0 and 5 km/s
        d.setVelocity({ 0.05 * (rand() % 100), 0.05 * (rand() % 100), 0.05 * (rand() % 100) });
        d.setAom(2e-5);
        d.setBcInv(0.05);
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        prepareRun(*i_total, *ta_total, d);
        // set heyoka parameters
        ta_total->get_pars_data()[0] = d.getAom();
        ta_total->get_pars_data()[1] = d.getBcInv();
        // integrate over time
        bool crash_i = false;
        bool crash_ta = false;
        for (double t = start_t; t <= end_t; t += delta_t) {
            std::array<double, 3> pos_i = i_total->getDebris().getDebrisVector()[0].getPosition();
            std::array<double, 3> pos_ta { ta_total->get_state()[0],
                ta_total->get_state()[1],
                ta_total->get_state()[2] };
            if (MathUtils::euclideanNorm(pos_i) <= Physics::R_EARTH) {
                if (!crash_i)
                    std::cout << "integrator hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_total, *ta_total);
                }
                crash_i = true;
                if (crash_ta && crash_i)
                    break;
            }
            if (MathUtils::euclideanNorm(pos_ta) <= Physics::R_EARTH) {
                if (!crash_ta)
                    std::cout << "heyoka hit the ground at t=" << t << std::endl;
                if (crash_ta == crash_i) {
                    showErrors(*i_total, *ta_total);
                }
                crash_ta = true;
            }
            if (crash_i && crash_ta)
                break;
            // integrate time step
            if (!crash_i)
                i_total->integrate();
            if (!crash_ta)
                ta_total->propagate_for(delta_t);
        }
        if (!(crash_i || crash_ta))
            // compare result
            showErrors(*i_total, *ta_total);
        std::cout << std::endl;
    }
}
// compare calculated values of all Components between the two complete heyoka integrators
TEST_F(CompareWithHeyokaTests, compareComleteHeyokas)
{
    std::cout << "\nCompare heyokas" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i) {
        d.setPosition({ 3500. * (i + 2), 0, 0 });
        d.setVelocity({ 5., 5., 5. });
        d.setAom(2e-5);
        d.setBcInv(0.05);
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        prepareRun<Debris::Debris>(*ta_split, *ta_total, d);
        // set heyoka parameters
        ta_total->get_pars_data()[0] = d.getAom();
        ta_total->get_pars_data()[1] = d.getBcInv();
        ta_split->get_pars_data()[0] = d.getAom();
        ta_split->get_pars_data()[1] = d.getBcInv();
        // integrate over time
        bool crash_split = false;
        bool crash_total = false;
        for (double t = start_t; t <= end_t; t += delta_t) {
            std::array<double, 3> pos_split { ta_split->get_state()[0],
                ta_split->get_state()[1],
                ta_split->get_state()[2] };
            std::array<double, 3> pos_total { ta_total->get_state()[0],
                ta_total->get_state()[1],
                ta_total->get_state()[2] };
            if (MathUtils::euclideanNorm(pos_split) <= Physics::R_EARTH) {
                if (!crash_split)
                    std::cout << "split hit the ground at t=" << t << std::endl;
                if (crash_total == crash_split) {
                    showErrors(*ta_split, *ta_total);
                }
                crash_split = true;
                if (crash_total && crash_split)
                    break;
            }
            if (MathUtils::euclideanNorm(pos_total) <= Physics::R_EARTH) {
                if (!crash_total)
                    std::cout << "total hit the ground at t=" << t << std::endl;
                if (crash_total == crash_split) {
                    showErrors(*ta_split, *ta_total);
                }
                crash_total = true;
            }
            if (crash_split && crash_total)
                break;
            // integrate time step
            if (!crash_split)
                ta_split->propagate_for(delta_t);
            if (!crash_total)
                ta_total->propagate_for(delta_t);
        }
        if (!(crash_split || crash_total))
            // compare result
            showErrors(*ta_split, *ta_total);
        std::cout << std::endl;
    }
}

// compare calculation time of all Components with random debris
TEST_F(CompareWithHeyokaTests, compareTotalRuntimeRandom)
{
    std::cout << "\nAll Components Runtime" << std::endl;
    // random number generator
    auto seed = time(NULL);
    srand(seed);
    std::cout << "Seed: " << seed << std::endl
              << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i) {
        // use values between 50 km above ground and 30000 km above that
        d.setPosition({ Physics::R_EARTH + 50 + (.5 * (rand() % 60000)), Physics::R_EARTH + 50 + (.5 * (rand() % 60000)), Physics::R_EARTH + 50 + (.5 * (rand() % 60000)) });
        // use values between 0 and 5 km/s
        d.setVelocity({ 0.05 * (rand() % 100), 0.05 * (rand() % 100), 0.05 * (rand() % 100) });
        d.setAom(2e-5);
        d.setBcInv(0.05);
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        prepareRun(*i_total, *ta_total, d);
        // set heyoka parameters
        ta_total->get_pars_data()[0] = d.getAom();
        ta_total->get_pars_data()[1] = d.getBcInv();
        // integrate over time
        // own integrator
        auto i_t1 = std::chrono::high_resolution_clock::now();
        for (double t = start_t; t <= end_t; t += delta_t) {
            i_total->integrate();
        }
        auto i_t2 = std::chrono::high_resolution_clock::now();
        auto i_ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(i_t2 - i_t1);

        // heyoka integrator
        auto ta_t1 = std::chrono::high_resolution_clock::now();
        for (double t = start_t; t <= end_t; t += delta_t) {
            ta_total->propagate_for(delta_t);
        }
        auto ta_t2 = std::chrono::high_resolution_clock::now();
        auto ta_ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(ta_t2 - ta_t1);

        std::cout << "Integrator runtime: " << i_ms_int.count() << " ms" << std::endl;
        std::cout << "Heyoka runtime: " << ta_ms_int.count() << " ms" << std::endl;
        std::cout << "Time difference: " << i_ms_int.count() - ta_ms_int.count() << " ms\n"
                  << std::endl;
    }
}
#endif