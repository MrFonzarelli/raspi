#ifndef IO_HPP
#define IO_HPP

namespace IO
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
        OilTemp,

        // TODO: Not yet implemented
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

}

#endif