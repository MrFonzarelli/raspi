#ifndef IO_HPP
#define IO_HPP

namespace IO
{
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
        QuarterMile,
        CustomTimer,
        RPM,
        Combined1, // RPM and Speed without an empty digit between them (RPM / 10)
        Combined2  // RPM and Speed with a "separator" consisting of an empty digit

    };

    enum class DisplayStateType
    {
        Integer,  // Integers without the DP
        Combined, // Two integers each on one of the two Triple Digit Displays
        Decimal,  // Decimals with 1 decimal place of precision
        Time      // Time numbers needing conversion to render with max precision
    };

    struct CombinedDisplayType
    {
        DisplayState displayStateRight;
        DisplayState displayStateLeft;
    };

    void initialize();

    void terminate();

    DisplayState getDisplayState();
    int getDisplayStateCount();
    int getCurrentDisplayStateIndex();

    void nextDisplayState();
    void previousDisplayState();

    DisplayStateType displayTypeOf(DisplayState displayState);

    CombinedDisplayType getCombinedDisplayState();

}

#endif