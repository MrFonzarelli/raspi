#ifndef DATA_HPP
#define DATA_HPP

#include "outgauge.hpp"
#include "io/io.hpp"

namespace Data
{

    const int ACCESS_DELAY_MS = 10;

    struct Odometer
    {
        double trip;
        double total; // Only stores the previous (loaded from file) total value and only updated when trip odo is reset
    };

    struct Tick
    {
        // Set by caller of set()
        OutGauge outGauge;
        long long tickCounter;
        double tickTime;

        // Set inside set()
        Odometer odometer;
        double fuelCons;
        double fuelConsAvg;
    };

    void
    set(const Tick &tick);
    Tick get();

    Odometer getOdometer();
    void setTotalOdometer(double value);

    void resetTripOdometer();
    void resetAvgFuelConsumption();
    void toggleUnits();

}

#endif