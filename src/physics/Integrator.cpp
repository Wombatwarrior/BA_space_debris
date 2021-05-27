//
// Created by Oliver on 13.05.21.
//

#include "Integrator.h"

Integrator::~Integrator() {}
void Integrator::integrate() {
  calculateAcceleration();
  calculatePosition();
  calculateVelocity();
}

void Integrator::calculatePosition() {
  double factor = delta_t * delta_t * 0.5;
  std::array<double, 3> new_pos;
  for (auto &d : debris->getDebrisVector()) {
    new_pos = d.getPosition();
    new_pos[0] =
        new_pos[0] + delta_t * d.getVelocity()[0] + factor * d.getAccT0()[0];
    new_pos[1] =
        new_pos[1] + delta_t * d.getVelocity()[1] + factor * d.getAccT0()[1];
    new_pos[2] =
        new_pos[2] + delta_t * d.getVelocity()[2] + factor * d.getAccT0()[2];
    d.setPosition(new_pos);
  }
}

void Integrator::calculateVelocity() {
  double factor = delta_t * 0.5;
  std::array<double, 3> new_velocity;
  for (auto &d : debris->getDebrisVector()) {
    new_velocity = d.getVelocity();
    new_velocity[0] =
        new_velocity[0] + factor * (d.getAccT0()[0] + d.getAccT1()[0]);
    new_velocity[1] =
        new_velocity[1] + factor * (d.getAccT0()[1] + d.getAccT1()[1]);
    new_velocity[2] =
        new_velocity[2] + factor * (d.getAccT0()[2] + d.getAccT1()[2]);
    d.setVelocity(new_velocity);
  }
}

void Integrator::calculateAcceleration() { accumulator.applyComponents(); }

double Integrator::getDeltaT() { return delta_t; }

void Integrator::setDeltaT(double deltaT) { delta_t = deltaT; }

Debris::DebrisContainer &Integrator::getDebris() { return *debris; }

void Integrator::setDebris(Debris::DebrisContainer &debris) {
  Integrator::debris = &debris;
}

Acceleration::AccelerationAccumulator &Integrator::getAccumulator() {
  return accumulator;
}

void Integrator::setAccumulator(
    Acceleration::AccelerationAccumulator &accumulator) {
  Integrator::accumulator = accumulator;
}
