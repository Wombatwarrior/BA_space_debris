# OrbitPropagator
This repository is a successor-fork of the Bachelor thesis on ["Efficient trajectory modelling for space debris evolution"](https://mediatum.ub.tum.de/node?id=1624605) at [TUM](https://www.in.tum.de/) in collaboration with [ESA](https://www.esa.int/gsp/ACT/).

It is part of the [LADDS](https://www.esa.int/gsp/ACT/projects/debris_hpc/) project and acts as the central engine for calculating the trajectory updates on all simulated particles.

## Dependencies

* C++17 Compiler
* CMake (>= 3.10)

## Build
build instructions for make:
```bash
mkdir build && cd build
cmake ..
make
