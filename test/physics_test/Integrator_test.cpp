//
// Created by Oliver on 13.05.21.
//

#include "Integrator_test.h"
#include <stdlib.h>
#include <time.h>

// setup taylor integrator and print it to check if the state etc. are correct
TEST_F(CompareWithHeyokaTests, showTaylorIntegrator)
{
    std::cout << *ta_total << std::endl;

    for(int i = 0; i < 8; ++i){
        std::cout << *ta_components[i] << std::endl;
    }
}

// compare calculated values of KepComponent
TEST_F(CompareWithHeyokaTests, compareKep) {
    std::cout << "\nKepler" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({1.,0,0});
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds) {
        // setup integrators
        i_components[Acceleration::KEP]->getDebris().cleanDebrisVector();
        i_components[Acceleration::KEP]->getDebris().addDebris(d);
        ta_components[Acceleration::KEP]->get_state_data()[0] = d.getPosition()[0];
        ta_components[Acceleration::KEP]->get_state_data()[1] = d.getPosition()[1];
        ta_components[Acceleration::KEP]->get_state_data()[2] = d.getPosition()[2];
        ta_components[Acceleration::KEP]->get_state_data()[3] = d.getVelocity()[0];
        ta_components[Acceleration::KEP]->get_state_data()[4] = d.getVelocity()[1];
        ta_components[Acceleration::KEP]->get_state_data()[5] = d.getVelocity()[2];
        // reset time values
        i_components[Acceleration::KEP]->setDeltaT(delta_t);
        i_components[Acceleration::KEP]->getAccumulator().setT(start_t);
        ta_components[Acceleration::KEP]->set_time(start_t);
        // integrate over time
        for (double t = start_t; t <= end_t; t += delta_t){
            // integrate time step
            i_components[Acceleration::KEP]->integrate();
            ta_components[Acceleration::KEP]->step(delta_t);
        }
        // compare result
        std::array<double,3> pos_i = i_components[Acceleration::KEP]->getDebris().getDebrisVector()[0].getPosition();
        std::array<double,3> vel_i = i_components[Acceleration::KEP]->getDebris().getDebrisVector()[0].getVelocity();
        std::array<double,3> pos_ta{ta_components[Acceleration::KEP]->get_state()[0],
                                    ta_components[Acceleration::KEP]->get_state()[1],
                                    ta_components[Acceleration::KEP]->get_state()[2]};
        std::array<double,3> vel_ta{ta_components[Acceleration::KEP]->get_state()[3],
                                    ta_components[Acceleration::KEP]->get_state()[4],
                                    ta_components[Acceleration::KEP]->get_state()[5]};
        IOUtils::to_ostream(pos_i, std::cout, ",", {"position integrator[","]\n"});
        IOUtils::to_ostream(pos_ta, std::cout, ",", {"position heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(pos_ta,pos_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(pos_ta,pos_i)},std::cout,"",{"euclidean distance: ","\n"});
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(vel_ta,vel_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(vel_ta,vel_i)},std::cout,"",{"euclidean distance: ","\n\n"});
    }
}
// compare calculated values of J2Component
TEST_F(CompareWithHeyokaTests, compareJ2)
{
    std::cout << "\nJ2" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({1.,0,0});
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds){
        // setup integrators
        i_components[Acceleration::J2]->getDebris().cleanDebrisVector();
        i_components[Acceleration::J2]->getDebris().addDebris(d);
        ta_components[Acceleration::J2]->get_state_data()[0] = d.getPosition()[0];
        ta_components[Acceleration::J2]->get_state_data()[1] = d.getPosition()[1];
        ta_components[Acceleration::J2]->get_state_data()[2] = d.getPosition()[2];
        ta_components[Acceleration::J2]->get_state_data()[3] = d.getVelocity()[0];
        ta_components[Acceleration::J2]->get_state_data()[4] = d.getVelocity()[1];
        ta_components[Acceleration::J2]->get_state_data()[5] = d.getVelocity()[2];
        // reset time values
        i_components[Acceleration::J2]->setDeltaT(delta_t);
        i_components[Acceleration::J2]->getAccumulator().setT(start_t);
        ta_components[Acceleration::J2]->set_time(start_t);
        // integrate over time
        for (double t = start_t; t <= end_t; t += delta_t){
            // integrate time step
            i_components[Acceleration::J2]->integrate();
            ta_components[Acceleration::J2]->step(delta_t);
        }
        // compare result
        std::array<double,3> pos_i = i_components[Acceleration::J2]->getDebris().getDebrisVector()[0].getPosition();
        std::array<double,3> vel_i = i_components[Acceleration::J2]->getDebris().getDebrisVector()[0].getVelocity();
        std::array<double,3> pos_ta{ta_components[Acceleration::J2]->get_state()[0],
                                    ta_components[Acceleration::J2]->get_state()[1],
                                    ta_components[Acceleration::J2]->get_state()[2]};
        std::array<double,3> vel_ta{ta_components[Acceleration::J2]->get_state()[3],
                                    ta_components[Acceleration::J2]->get_state()[4],
                                    ta_components[Acceleration::J2]->get_state()[5]};
        IOUtils::to_ostream(pos_i, std::cout, ",", {"position integrator[","]\n"});
        IOUtils::to_ostream(pos_ta, std::cout, ",", {"position heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(pos_ta,pos_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(pos_ta,pos_i)},std::cout,"",{"euclidean distance: ","\n"});
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(vel_ta,vel_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(vel_ta,vel_i)},std::cout,"",{"euclidean distance: ","\n\n"});
    }
}
// compare calculated values of C22Component
TEST_F(CompareWithHeyokaTests, compareC22)
{
    std::cout << "\nC22" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({1.,0,0});
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds){
        // setup integrators
        i_components[Acceleration::C22]->getDebris().cleanDebrisVector();
        i_components[Acceleration::C22]->getDebris().addDebris(d);
        ta_components[Acceleration::C22]->get_state_data()[0] = d.getPosition()[0];
        ta_components[Acceleration::C22]->get_state_data()[1] = d.getPosition()[1];
        ta_components[Acceleration::C22]->get_state_data()[2] = d.getPosition()[2];
        ta_components[Acceleration::C22]->get_state_data()[3] = d.getVelocity()[0];
        ta_components[Acceleration::C22]->get_state_data()[4] = d.getVelocity()[1];
        ta_components[Acceleration::C22]->get_state_data()[5] = d.getVelocity()[2];
        // reset time values
        i_components[Acceleration::C22]->setDeltaT(delta_t);
        i_components[Acceleration::C22]->getAccumulator().setT(start_t);
        ta_components[Acceleration::C22]->set_time(start_t);
        // integrate over time
        for (double t = start_t; t <= end_t; t += delta_t){
            // integrate time step
            i_components[Acceleration::C22]->integrate();
            ta_components[Acceleration::C22]->step(delta_t);
        }
        // integrate time step
        i_components[Acceleration::C22]->integrate();
        ta_components[Acceleration::C22]->step(delta_t);
        // compare result
        std::array<double,3> pos_i = i_components[Acceleration::C22]->getDebris().getDebrisVector()[0].getPosition();
        std::array<double,3> vel_i = i_components[Acceleration::C22]->getDebris().getDebrisVector()[0].getVelocity();
        std::array<double,3> pos_ta{ta_components[Acceleration::C22]->get_state()[0],
                                    ta_components[Acceleration::C22]->get_state()[1],
                                    ta_components[Acceleration::C22]->get_state()[2]};
        std::array<double,3> vel_ta{ta_components[Acceleration::C22]->get_state()[3],
                                    ta_components[Acceleration::C22]->get_state()[4],
                                    ta_components[Acceleration::C22]->get_state()[5]};
        IOUtils::to_ostream(pos_i, std::cout, ",", {"position integrator[","]\n"});
        IOUtils::to_ostream(pos_ta, std::cout, ",", {"position heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(pos_ta,pos_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(pos_ta,pos_i)},std::cout,"",{"euclidean distance: ","\n"});
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(vel_ta,vel_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(vel_ta,vel_i)},std::cout,"",{"euclidean distance: ","\n\n"});
    }
}
// compare calculated values of S22Component
TEST_F(CompareWithHeyokaTests, compareS22)
{
    std::cout << "\nS22" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({1.,0,0});
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds){
        // setup integrators
        i_components[Acceleration::S22]->getDebris().cleanDebrisVector();
        i_components[Acceleration::S22]->getDebris().addDebris(d);
        ta_components[Acceleration::S22]->get_state_data()[0] = d.getPosition()[0];
        ta_components[Acceleration::S22]->get_state_data()[1] = d.getPosition()[1];
        ta_components[Acceleration::S22]->get_state_data()[2] = d.getPosition()[2];
        ta_components[Acceleration::S22]->get_state_data()[3] = d.getVelocity()[0];
        ta_components[Acceleration::S22]->get_state_data()[4] = d.getVelocity()[1];
        ta_components[Acceleration::S22]->get_state_data()[5] = d.getVelocity()[2];
        // reset time values
        i_components[Acceleration::S22]->setDeltaT(delta_t);
        i_components[Acceleration::S22]->getAccumulator().setT(start_t);
        ta_components[Acceleration::S22]->set_time(start_t);
        // integrate over time
        for (double t = start_t; t <= end_t; t += delta_t){
            // integrate time step
            i_components[Acceleration::S22]->integrate();
            ta_components[Acceleration::S22]->step(delta_t);
        }
        // integrate time step
        i_components[Acceleration::S22]->integrate();
        ta_components[Acceleration::S22]->step(delta_t);
        // compare result
        std::array<double,3> pos_i = i_components[Acceleration::S22]->getDebris().getDebrisVector()[0].getPosition();
        std::array<double,3> vel_i = i_components[Acceleration::S22]->getDebris().getDebrisVector()[0].getVelocity();
        std::array<double,3> pos_ta{ta_components[Acceleration::S22]->get_state()[0],
                                    ta_components[Acceleration::S22]->get_state()[1],
                                    ta_components[Acceleration::S22]->get_state()[2]};
        std::array<double,3> vel_ta{ta_components[Acceleration::S22]->get_state()[3],
                                    ta_components[Acceleration::S22]->get_state()[4],
                                    ta_components[Acceleration::S22]->get_state()[5]};
        IOUtils::to_ostream(pos_i, std::cout, ",", {"position integrator[","]\n"});
        IOUtils::to_ostream(pos_ta, std::cout, ",", {"position heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(pos_ta,pos_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(pos_ta,pos_i)},std::cout,"",{"euclidean distance: ","\n"});
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(vel_ta,vel_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(vel_ta,vel_i)},std::cout,"",{"euclidean distance: ","\n\n"});
    }
}
// compare calculated values of LunComponent
TEST_F(CompareWithHeyokaTests, compareLun)
{
    std::cout << "\nLunar Tide" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({1.,0,0});
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds){
        // setup integrators
        i_components[Acceleration::LUN]->getDebris().cleanDebrisVector();
        i_components[Acceleration::LUN]->getDebris().addDebris(d);
        ta_components[Acceleration::LUN]->get_state_data()[0] = d.getPosition()[0];
        ta_components[Acceleration::LUN]->get_state_data()[1] = d.getPosition()[1];
        ta_components[Acceleration::LUN]->get_state_data()[2] = d.getPosition()[2];
        ta_components[Acceleration::LUN]->get_state_data()[3] = d.getVelocity()[0];
        ta_components[Acceleration::LUN]->get_state_data()[4] = d.getVelocity()[1];
        ta_components[Acceleration::LUN]->get_state_data()[5] = d.getVelocity()[2];
        // reset time values
        i_components[Acceleration::LUN]->setDeltaT(delta_t);
        i_components[Acceleration::LUN]->getAccumulator().setT(start_t);
        ta_components[Acceleration::LUN]->set_time(start_t);
        // integrate over time
        for (double t = start_t; t <= end_t; t += delta_t){
            // integrate time step
            i_components[Acceleration::LUN]->integrate();
            ta_components[Acceleration::LUN]->step(delta_t);
        }
        // integrate time step
        i_components[Acceleration::LUN]->integrate();
        ta_components[Acceleration::LUN]->step(delta_t);
        // compare result
        std::array<double,3> pos_i = i_components[Acceleration::LUN]->getDebris().getDebrisVector()[0].getPosition();
        std::array<double,3> vel_i = i_components[Acceleration::LUN]->getDebris().getDebrisVector()[0].getVelocity();
        std::array<double,3> pos_ta{ta_components[Acceleration::LUN]->get_state()[0],
                                    ta_components[Acceleration::LUN]->get_state()[1],
                                    ta_components[Acceleration::LUN]->get_state()[2]};
        std::array<double,3> vel_ta{ta_components[Acceleration::LUN]->get_state()[3],
                                    ta_components[Acceleration::LUN]->get_state()[4],
                                    ta_components[Acceleration::LUN]->get_state()[5]};
        IOUtils::to_ostream(pos_i, std::cout, ",", {"position integrator[","]\n"});
        IOUtils::to_ostream(pos_ta, std::cout, ",", {"position heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(pos_ta,pos_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(pos_ta,pos_i)},std::cout,"",{"euclidean distance: ","\n"});
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(vel_ta,vel_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(vel_ta,vel_i)},std::cout,"",{"euclidean distance: ","\n\n"});
    }
}
// compare calculated values of SolComponent
TEST_F(CompareWithHeyokaTests, compareSol)
{
    std::cout << "\nSolar tide" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({1.,0,0});
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds){
        // setup integrators
        i_components[Acceleration::SOL]->getDebris().cleanDebrisVector();
        i_components[Acceleration::SOL]->getDebris().addDebris(d);
        ta_components[Acceleration::SOL]->get_state_data()[0] = d.getPosition()[0];
        ta_components[Acceleration::SOL]->get_state_data()[1] = d.getPosition()[1];
        ta_components[Acceleration::SOL]->get_state_data()[2] = d.getPosition()[2];
        ta_components[Acceleration::SOL]->get_state_data()[3] = d.getVelocity()[0];
        ta_components[Acceleration::SOL]->get_state_data()[4] = d.getVelocity()[1];
        ta_components[Acceleration::SOL]->get_state_data()[5] = d.getVelocity()[2];
        // reset time values
        i_components[Acceleration::SOL]->setDeltaT(delta_t);
        i_components[Acceleration::SOL]->getAccumulator().setT(start_t);
        ta_components[Acceleration::SOL]->set_time(start_t);
        // integrate over time
        for (double t = start_t; t <= end_t; t += delta_t){
            // integrate time step
            i_components[Acceleration::SOL]->integrate();
            ta_components[Acceleration::SOL]->propagate_for(delta_t);
        }
        // integrate time step
        i_components[Acceleration::SOL]->integrate();
        ta_components[Acceleration::SOL]->step(delta_t);
        // compare result
        std::array<double,3> pos_i = i_components[Acceleration::SOL]->getDebris().getDebrisVector()[0].getPosition();
        std::array<double,3> vel_i = i_components[Acceleration::SOL]->getDebris().getDebrisVector()[0].getVelocity();
        std::array<double,3> pos_ta{ta_components[Acceleration::SOL]->get_state()[0],
                                    ta_components[Acceleration::SOL]->get_state()[1],
                                    ta_components[Acceleration::SOL]->get_state()[2]};
        std::array<double,3> vel_ta{ta_components[Acceleration::SOL]->get_state()[3],
                                    ta_components[Acceleration::SOL]->get_state()[4],
                                    ta_components[Acceleration::SOL]->get_state()[5]};
        IOUtils::to_ostream(pos_i, std::cout, ",", {"position integrator[","]\n"});
        IOUtils::to_ostream(pos_ta, std::cout, ",", {"position heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(pos_ta,pos_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(pos_ta,pos_i)},std::cout,"",{"euclidean distance: ","\n"});
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(vel_ta,vel_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(vel_ta,vel_i)},std::cout,"",{"euclidean distance: ","\n\n"});
    }
}
// compare calculated values of SRPComponent
TEST_F(CompareWithHeyokaTests, compareSRP)
{
    std::cout << "\nSolar Radiation Pressure" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({1.,0,0});
        d.setAom(0.5);
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds){
        // setup integrators
        i_components[Acceleration::SRP]->getDebris().cleanDebrisVector();
        i_components[Acceleration::SRP]->getDebris().addDebris(d);
        ta_components[Acceleration::SRP]->get_state_data()[0] = d.getPosition()[0];
        ta_components[Acceleration::SRP]->get_state_data()[1] = d.getPosition()[1];
        ta_components[Acceleration::SRP]->get_state_data()[2] = d.getPosition()[2];
        ta_components[Acceleration::SRP]->get_state_data()[3] = d.getVelocity()[0];
        ta_components[Acceleration::SRP]->get_state_data()[4] = d.getVelocity()[1];
        ta_components[Acceleration::SRP]->get_state_data()[5] = d.getVelocity()[2];
        ta_components[Acceleration::SRP]->get_pars_data()[0] = d.getAom();
        // reset time values
        i_components[Acceleration::SRP]->setDeltaT(delta_t);
        i_components[Acceleration::SRP]->getAccumulator().setT(start_t);
        ta_components[Acceleration::SRP]->set_time(start_t);
        std::cout << *ta_components[Acceleration::SRP] << std::endl;
        // integrate over time
        for (double t = start_t; t <= end_t; t += delta_t){
            // integrate time step
            i_components[Acceleration::SRP]->integrate();
            ta_components[Acceleration::SRP]->step(delta_t);
        }
        // integrate time step
        i_components[Acceleration::SRP]->integrate();
        ta_components[Acceleration::SRP]->step(delta_t);
        // compare result
        std::array<double,3> pos_i = i_components[Acceleration::SRP]->getDebris().getDebrisVector()[0].getPosition();
        std::array<double,3> vel_i = i_components[Acceleration::SRP]->getDebris().getDebrisVector()[0].getVelocity();
        std::array<double,3> pos_ta{ta_components[Acceleration::SRP]->get_state()[0],
                                    ta_components[Acceleration::SRP]->get_state()[1],
                                    ta_components[Acceleration::SRP]->get_state()[2]};
        std::array<double,3> vel_ta{ta_components[Acceleration::SRP]->get_state()[3],
                                    ta_components[Acceleration::SRP]->get_state()[4],
                                    ta_components[Acceleration::SRP]->get_state()[5]};
        IOUtils::to_ostream(pos_i, std::cout, ",", {"position integrator[","]\n"});
        IOUtils::to_ostream(pos_ta, std::cout, ",", {"position heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(pos_ta,pos_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(pos_ta,pos_i)},std::cout,"",{"euclidean distance: ","\n"});
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(vel_ta,vel_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(vel_ta,vel_i)},std::cout,"",{"euclidean distance: ","\n\n"});
    }
}
// compare calculated values of DragComponent
TEST_F(CompareWithHeyokaTests, compareDrag)
{
    std::cout << "\nAtmospheric Drag" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({1.,0,0});
        d.setBcInv(0.5);
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds){
        // setup integrators
        i_components[Acceleration::DRAG]->getDebris().cleanDebrisVector();
        i_components[Acceleration::DRAG]->getDebris().addDebris(d);
        ta_components[Acceleration::DRAG]->get_state_data()[0] = d.getPosition()[0];
        ta_components[Acceleration::DRAG]->get_state_data()[1] = d.getPosition()[1];
        ta_components[Acceleration::DRAG]->get_state_data()[2] = d.getPosition()[2];
        ta_components[Acceleration::DRAG]->get_state_data()[3] = d.getVelocity()[0];
        ta_components[Acceleration::DRAG]->get_state_data()[4] = d.getVelocity()[1];
        ta_components[Acceleration::DRAG]->get_state_data()[5] = d.getVelocity()[2];
        ta_components[Acceleration::DRAG]->get_pars_data()[1] = d.getBcInv();
        // reset time values
        i_components[Acceleration::DRAG]->setDeltaT(delta_t);
        i_components[Acceleration::DRAG]->getAccumulator().setT(start_t);
        ta_components[Acceleration::DRAG]->set_time(start_t);
        // integrate over time
        for (double t = start_t; t <= end_t; t += delta_t){
            // integrate time step
            i_components[Acceleration::DRAG]->integrate();
            ta_components[Acceleration::DRAG]->step(delta_t);
        }
        // integrate time step
        i_components[Acceleration::DRAG]->integrate();
        ta_components[Acceleration::DRAG]->step(delta_t);
        // compare result
        std::array<double,3> pos_i = i_components[Acceleration::DRAG]->getDebris().getDebrisVector()[0].getPosition();
        std::array<double,3> vel_i = i_components[Acceleration::DRAG]->getDebris().getDebrisVector()[0].getVelocity();
        std::array<double,3> pos_ta{ta_components[Acceleration::DRAG]->get_state()[0],
                                    ta_components[Acceleration::DRAG]->get_state()[1],
                                    ta_components[Acceleration::DRAG]->get_state()[2]};
        std::array<double,3> vel_ta{ta_components[Acceleration::DRAG]->get_state()[3],
                                    ta_components[Acceleration::DRAG]->get_state()[4],
                                    ta_components[Acceleration::DRAG]->get_state()[5]};
        IOUtils::to_ostream(pos_i, std::cout, ",", {"position integrator[","]\n"});
        IOUtils::to_ostream(pos_ta, std::cout, ",", {"position heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(pos_ta,pos_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(pos_ta,pos_i)},std::cout,"",{"euclidean distance: ","\n"});
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(vel_ta,vel_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(vel_ta,vel_i)},std::cout,"",{"euclidean distance: ","\n\n"});
    }
}
// compare calculated values of all Components
TEST_F(CompareWithHeyokaTests, compareTotal)
{
    std::cout << "\nAll Components" << std::endl;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({1.,0,0});
        d.setAom(0.5);
        d.setBcInv(0.5);
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds){
        // setup integrators
        i_total->getDebris().cleanDebrisVector();
        i_total->getDebris().addDebris(d);
        ta_total->get_state_data()[0] = d.getPosition()[0];
        ta_total->get_state_data()[1] = d.getPosition()[1];
        ta_total->get_state_data()[2] = d.getPosition()[2];
        ta_total->get_state_data()[3] = d.getVelocity()[0];
        ta_total->get_state_data()[4] = d.getVelocity()[1];
        ta_total->get_state_data()[5] = d.getVelocity()[2];
        ta_total->get_pars_data()[0] = d.getAom();
        ta_total->get_pars_data()[1] = d.getBcInv();
        // reset time values
        i_total->setDeltaT(delta_t);
        i_total->getAccumulator().setT(start_t);
        ta_total->set_time(start_t);
        // integrate over time
        for (double t = start_t; t <= end_t; t += delta_t){
            // integrate time step
            i_total->integrate();
            ta_total->step(delta_t);
        }
        // integrate time step
        i_total->integrate();
        ta_total->step(delta_t);
        // compare result
        std::array<double,3> pos_i = i_total->getDebris().getDebrisVector()[0].getPosition();
        std::array<double,3> vel_i = i_total->getDebris().getDebrisVector()[0].getVelocity();
        std::array<double,3> pos_ta{ta_total->get_state()[0],
                                    ta_total->get_state()[1],
                                    ta_total->get_state()[2]};
        std::array<double,3> vel_ta{ta_total->get_state()[3],
                                    ta_total->get_state()[4],
                                    ta_total->get_state()[5]};
        IOUtils::to_ostream(pos_i, std::cout, ",", {"position integrator[","]\n"});
        IOUtils::to_ostream(pos_ta, std::cout, ",", {"position heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(pos_ta,pos_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(pos_ta,pos_i)},std::cout,"",{"euclidean distance: ","\n"});
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(vel_ta,vel_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(vel_ta,vel_i)},std::cout,"",{"euclidean distance: ","\n\n"});
    }
}
// compare calculated values of all Components with random debris
TEST_F(CompareWithHeyokaTests, compareTotalRandom)
{
    std::cout << "\nAll Components Random" << std::endl;
    // random number generator
    srand (time(NULL));
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        // use values between 50 km above ground and 30000 km above that
        d.setPosition({Physics::R_EARTH+50+(.5*(rand() % 60000)),Physics::R_EARTH+50+(.5*(rand() % 60000)),Physics::R_EARTH+50+(.5*(rand() % 60000))});
        // use values between 0 and 50 km/s
        d.setVelocity({0.1*(rand() % 500),0.1*(rand() % 500),0.1*(rand() % 500)});
        d.setAom(0.5);
        d.setBcInv(0.5);
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds){
        // setup integrators
        i_total->getDebris().cleanDebrisVector();
        i_total->getDebris().addDebris(d);
        ta_total->get_state_data()[0] = d.getPosition()[0];
        ta_total->get_state_data()[1] = d.getPosition()[1];
        ta_total->get_state_data()[2] = d.getPosition()[2];
        ta_total->get_state_data()[3] = d.getVelocity()[0];
        ta_total->get_state_data()[4] = d.getVelocity()[1];
        ta_total->get_state_data()[5] = d.getVelocity()[2];
        ta_total->get_pars_data()[0] = d.getAom();
        ta_total->get_pars_data()[1] = d.getBcInv();
        // reset time values
        i_total->setDeltaT(delta_t);
        i_total->getAccumulator().setT(start_t);
        ta_total->set_time(start_t);
        // integrate over time
        for (double t = start_t; t <= end_t; t += delta_t){
            // integrate time step
            i_total->integrate();
            ta_total->step(delta_t);
        }
        // integrate time step
        i_total->integrate();
        ta_total->step(delta_t);
        // compare result
        std::array<double,3> pos_i = i_total->getDebris().getDebrisVector()[0].getPosition();
        std::array<double,3> vel_i = i_total->getDebris().getDebrisVector()[0].getVelocity();
        std::array<double,3> pos_ta{ta_total->get_state()[0],
                                    ta_total->get_state()[1],
                                    ta_total->get_state()[2]};
        std::array<double,3> vel_ta{ta_total->get_state()[3],
                                    ta_total->get_state()[4],
                                    ta_total->get_state()[5]};
        IOUtils::to_ostream(pos_i, std::cout, ",", {"position integrator[","]\n"});
        IOUtils::to_ostream(pos_ta, std::cout, ",", {"position heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(pos_ta,pos_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(pos_ta,pos_i)},std::cout,"",{"euclidean distance: ","\n"});
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::cosSimilarity(vel_ta,vel_i)},std::cout,"",{"cosine similarity: ","\n"});
        IOUtils::to_ostream(std::array<double,1>{MathUtils::euclideanDistance(vel_ta,vel_i)},std::cout,"",{"euclidean distance: ","\n\n"});
    }
}
