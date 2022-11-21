#ifndef DISPLAY_HPP
#define DISPLAY_HPP

namespace Display
{

    const int DISPLAY_STATE_COUNT = 8;

    enum class DisplayState
    {
        Speed,
        TurboPressure,
        CurrentFuelConsumption,
        AverageFuelConsumption,
        TripOdometer,
        Odometer,
        EngineTemp,
        OilTemp
    };

    void initialize();

}

#endif