#ifndef IO_HPP
#define IO_HPP

namespace IO
{

    const int DISPLAY_STATE_COUNT = 15;

    enum class DisplayState
    {
        Speed,
        TurboPressure,
        CurrentFuelConsumption,
        AverageFuelConsumption,
        TripOdometer,
        Odometer,
        EngineTemp,
        OilTemp,
        ZeroTo100,
        ZeroTo200,
        ZeroTo300,
        HundredTo200,
        HundredTo300,
        TwoHundredTo300,
        QuarterMile
    };

    void initialize();

    DisplayState getDisplayState();

    void nextDisplayState();
    void previousDisplayState();

}

#endif