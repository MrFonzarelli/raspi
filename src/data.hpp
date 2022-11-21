#ifndef DATA_HPP
#define DATA_HPP

#include "outgauge.hpp"

namespace Data
{

    struct Tick
    {
        OutGauge outGauge;
        long long tickCounter;
        double tickTime;
    };

    void set(const Tick &tick);
    Tick get();
}

#endif