#include "io.hpp"
#include "animations.hpp"
#include "buttons.hpp"
#include "display_single_digit.hpp"
#include "display_triple_digit.hpp"
#include "oled_display.hpp"
#include "lights.hpp"
#include "pins.hpp"
#include "timers.hpp"
#include <chrono>
#include <memory>
#include <thread>
#include <wiringPi.h>

namespace IO
{

    std::unique_ptr<std::thread> g_SingleDigitThread;
    std::unique_ptr<std::thread> g_TripleDigitThread;
    std::unique_ptr<std::thread> g_ScreenScrollRightButtonThread;
    std::unique_ptr<std::thread> g_ScreenScrollLeftButtonThread;
    std::unique_ptr<std::thread> g_MultiButtonThread;
    std::unique_ptr<std::thread> g_ResetStatButtonThread;
    std::unique_ptr<std::thread> g_TimerThread;
    std::unique_ptr<std::thread> g_LightsThread;
    std::unique_ptr<std::thread> g_OLEDThread;

    DisplayState g_DisplayState = DisplayState::CustomTimer;
    std::mutex g_DisplayStateMutex;

    void initialize()
    {
        wiringPiSetup();
        pinMode(PIN_SINGLE_DIGIT_A, OUTPUT);
        pinMode(PIN_SINGLE_DIGIT_B, OUTPUT);
        pinMode(PIN_SINGLE_DIGIT_C, OUTPUT);
        pinMode(PIN_SINGLE_DIGIT_D, OUTPUT);
        pinMode(PIN_SINGLE_DIGIT_E, OUTPUT);
        pinMode(PIN_SINGLE_DIGIT_F, OUTPUT);
        pinMode(PIN_SINGLE_DIGIT_G, OUTPUT);
        pinMode(PIN_SINGLE_DIGIT_DP, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_A, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_B, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_C, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_D, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_E, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_F, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_G, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_DP, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_DIG1, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_DIG2, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_DIG3, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_DIG4, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_DIG5, OUTPUT);
        pinMode(PIN_TRIPLE_DIG_DIG6, OUTPUT);
        pinMode(PIN_SCROLL_RIGHT_BUTTON, INPUT);
        pinMode(PIN_SCROLL_LEFT_BUTTON, INPUT);
        pinMode(PIN_CHANGE_UNITS_BUTTON, INPUT);
        pinMode(PIN_RESET_STAT, INPUT);
        pinMode(PIN_DASHLIGHT_LED1, INPUT);
        pinMode(PIN_DASHLIGHT_LED2, INPUT);
        pinMode(PIN_DASHLIGHT_LED3, INPUT);
        pinMode(PIN_DASHLIGHT_LED4, INPUT);

        Animations::welcome();

        g_SingleDigitThread.reset(SingleDigit::startThread());
        g_TripleDigitThread.reset(TripleDigit::startThread());
        g_ScreenScrollRightButtonThread.reset(Buttons::startScreenScrollRightButtonThread());
        g_ScreenScrollLeftButtonThread.reset(Buttons::startScreenScrollLeftButtonThread());
        g_MultiButtonThread.reset(Buttons::startMultiButtonThread());
        g_ResetStatButtonThread.reset(Buttons::startResetStatButtonThread());
        g_TimerThread.reset(Timers::startThread());
        g_LightsThread.reset(Lights::startThread());
        g_OLEDThread.reset(OLED::startThread());
    }

    void terminate()
    {
        OLED::clearAndStop();
        TripleDigit::clearAndStop();
        SingleDigit::clearAndStop();
    }

    DisplayState getDisplayState()
    {
        g_DisplayStateMutex.lock();
        DisplayState result = g_DisplayState;
        g_DisplayStateMutex.unlock();
        return result;
    }

    void nextDisplayState()
    {
        g_DisplayStateMutex.lock();
        g_DisplayState = (DisplayState)(((int)g_DisplayState + 1) % IO::DISPLAY_STATE_COUNT);
        g_DisplayStateMutex.unlock();
    }

    void previousDisplayState()
    {
        g_DisplayStateMutex.lock();
        g_DisplayState = (DisplayState)(((int)g_DisplayState + IO::DISPLAY_STATE_COUNT - 1) % IO::DISPLAY_STATE_COUNT);
        g_DisplayStateMutex.unlock();
    }

    DisplayStateType displayTypeOf(DisplayState displayState)
    {
        switch (displayState)
        {
        case DisplayState::ZeroTo100:
        case DisplayState::ZeroTo200:
        case DisplayState::ZeroTo300:
        case DisplayState::QuarterMile:
        case DisplayState::HundredTo200:
        case DisplayState::HundredTo300:
        case DisplayState::TwoHundredTo300:
        case DisplayState::CustomTimer:
            return DisplayStateType::Time;
        case DisplayState::TripOdometer:
        case DisplayState::Odometer:
        case DisplayState::CurrentFuelConsumption:
        case DisplayState::AverageFuelConsumption:
        case DisplayState::TurboPressure:
            return DisplayStateType::Decimal_OnePlace;
        default:
            return DisplayStateType::Integer;
        }
    }

}