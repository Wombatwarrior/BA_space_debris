//
// Created by Oliver on 12.05.21.
//

#pragma once
#include "debris/DebrisContainer.h"
#include <array>
#include "Constants.h"
#include <math.h>

namespace Acceleration {
    enum AccelerationComponent {KEP, J2, C22, S22, SOL, LUN, SRP, DRAG};
    class AccelerationAccumulator {
    public:
        AccelerationAccumulator(std::array<bool,8> &config_arg, Debris::DebrisContainer &debris_arg)
        : config (config_arg), debris (debris_arg)
        {};
        ~AccelerationAccumulator();

        void applyComponents();
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
        void apply(Debris::Debris &d, std::array<double,3> &acc_kep, std::array<double,3> &acc);
    }

    namespace J2Component {
        void apply(Debris::Debris &d, std::array<double,3> &acc_j2, std::array<double,3> &acc);
    }

    namespace C22Component {
        void apply(Debris::Debris &d, std::array<double,3> &acc_c22, std::array<double,3> &acc);
    }

    namespace S22Component {
        void apply(Debris::Debris &d, std::array<double,3> &acc_s22, std::array<double,3> &acc);
    }

    namespace SolComponent {
        void apply(Debris::Debris &d, std::array<double,3> &acc_sol, std::array<double,3> &acc);
    }

    namespace LunComponent {
        void apply(Debris::Debris &d, std::array<double,3> &acc_lun, std::array<double,3> &acc);
    }

    namespace SRPComponent {
        void apply(Debris::Debris &d, std::array<double,3> &acc_srp, std::array<double,3> &acc);
    }

    namespace DragComponent  {
        void apply(Debris::Debris &d, std::array<double,3> &acc_drag, std::array<double,3> &acc);
    }
}
