#ifndef DATA_HPP
#define DATA_HPP

#include "outgauge.hpp"
#include "display.hpp"

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
        bool impUnits;
        Display::DisplayState displayState;
    };

    void set(const Tick &tick);
    Tick get();
}

#endif