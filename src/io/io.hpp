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

    enum class DisplayStateType
    {
        Integer,           // Integers without the DP
        Decimal_OnePlace,  // Decimals with 1 decimal place of precision
        Decimal_TwoPlaces, // Decimals with 2 decimal places of precision
        Time               // Time numbers needing conversion to render with max precision
    };

    void initialize();

    DisplayState getDisplayState();

    void nextDisplayState();
    void previousDisplayState();

    DisplayStateType displayTypeOf(DisplayState displayState);

}

#endif