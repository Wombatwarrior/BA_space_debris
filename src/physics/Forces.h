//
// Created by ubuntu on 12.05.21.
//

#pragma once
#include "debris/DebrisContainer.h"
#include <array>

namespace Forces {
    enum ForceComponent {KEP, J2, C22, S22, SOL, LUN, SRP, DRAG};
    class ForceAccumulator {
    public:
        ForceAccumulator(std::array<bool,8> &config_arg, Debris::DebrisContainer &debris_arg)
        : config (config_arg), debris (debris_arg)
        {};
        ~ForceAccumulator();

        void addForces();
    private:
        std::array<bool,8> config;
        Debris::DebrisContainer &debris;
    public:
        void setConfig(std::array<bool,8> &config);
        std::array<bool,8> getConfig();
        void setDebris(Debris::DebrisContainer &debris);
        Debris::DebrisContainer &getDebris();
    };

    namespace KepComponent {
        void apply(Debris::DebrisContainer &debris);
    }

    namespace J2Component {
        void apply(Debris::DebrisContainer &debris);
    }

    namespace C22Component {
        void apply(Debris::DebrisContainer &debris);
    }

    namespace S22Component {
        void apply(Debris::DebrisContainer &debris);
    }

    namespace SolComponent {
        void apply(Debris::DebrisContainer &debris);
    }

    namespace LunComponent {
        void apply(Debris::DebrisContainer &debris);
    }

    namespace SRPComponent {
        void apply(Debris::DebrisContainer &debris);
    }

    namespace DragComponent  {
        void apply(Debris::DebrisContainer &debris);
    }
}
