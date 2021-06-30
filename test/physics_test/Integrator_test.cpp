//
// Created by Oliver on 13.05.21.
//

#include "Integrator_test.h"

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
    // time step in seconds
    double delta_t = 0.1;
    // set some test debris values and add them to the Integrators
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({10.,0,0});
        ds.push_back(d);
    }
    // loop over the debris data and compare calculations
    for (auto d : ds){
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
        i_components[Acceleration::KEP]->getAccumulator().setT(0.);
        ta_components[Acceleration::KEP]->set_time(0.);
        // integrate time step
        i_components[Acceleration::KEP]->integrate();
        ta_components[Acceleration::KEP]->step(delta_t);
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
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
    }
}
// compare calculated values of J2Component
TEST_F(CompareWithHeyokaTests, compareJ2)
{
    // time step in seconds
    double delta_t = 0.1;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({10.,0,0});
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
        i_components[Acceleration::J2]->getAccumulator().setT(0.);
        ta_components[Acceleration::J2]->set_time(0.);
        // integrate time step
        i_components[Acceleration::J2]->integrate();
        ta_components[Acceleration::J2]->step(delta_t);
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
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
    }
}
// compare calculated values of C22Component
TEST_F(CompareWithHeyokaTests, compareC22)
{
    // time step in seconds
    double delta_t = 0.1;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({10.,0,0});
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
        i_components[Acceleration::C22]->getAccumulator().setT(0.);
        ta_components[Acceleration::C22]->set_time(0.);
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
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
    }
}
// compare calculated values of S22Component
TEST_F(CompareWithHeyokaTests, compareS22)
{
    // time step in seconds
    double delta_t = 0.1;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({10.,0,0});
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
        i_components[Acceleration::S22]->getAccumulator().setT(0.);
        ta_components[Acceleration::S22]->set_time(0.);
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
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
    }
}
// compare calculated values of LunComponent
TEST_F(CompareWithHeyokaTests, compareLun)
{
    // time step in seconds
    double delta_t = 0.1;
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({10.,0,0});
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
        i_components[Acceleration::LUN]->getAccumulator().setT(0.);
        ta_components[Acceleration::LUN]->set_time(0.);
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
        IOUtils::to_ostream(vel_i, std::cout, ",", {"velocity integrator[","]\n"});
        IOUtils::to_ostream(vel_ta, std::cout, ",", {"velocity heyoka[","]\n"});
    }
}
// compare calculated values of SolComponent
TEST_F(CompareWithHeyokaTests, compareSol)
{
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({10.,0,0});
        ds.push_back(d);
    }

}
// compare calculated values of SRPComponent
TEST_F(CompareWithHeyokaTests, compareSRP)
{
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({10.,0,0});
        d.setAom(0.5);
        ds.push_back(d);
    }

}
// compare calculated values of DragComponent
TEST_F(CompareWithHeyokaTests, compareDrag)
{
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({10.,0,0});
        d.setBcInv(0.5);
        ds.push_back(d);
    }

}
// compare calculated values of all Components
TEST_F(CompareWithHeyokaTests, compareTotal)
{
    // set some test debris values
    std::vector<Debris::Debris> ds;
    Debris::Debris d;
    for (int i = 0; i < 3; ++i){
        d.setPosition({3500.*(i+2),0,0});
        d.setVelocity({10.,0,0});
        d.setAom(0.5);
        d.setBcInv(0.5);
        ds.push_back(d);
    }

}
