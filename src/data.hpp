#ifndef DATA_HPP
#define DATA_HPP

#include "outgauge.hpp"
#include "io/io.hpp"

namespace Data
{
    const int ACCESS_DELAY_MS = 10;

    struct Tick
    {
        OutGauge outGauge;
        long long tickCounter;
        double tickTime;
        double tripOdometer;
        double odometer;
        double fuelCons;
        double fuelConsAvg;
    };

    void set(const Tick &tick);
    Tick get();
}

#endif