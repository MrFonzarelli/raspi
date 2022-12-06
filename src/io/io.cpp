#include "io.hpp"
#include "animations.hpp"
#include "buttons.hpp"
#include "display_single_digit.hpp"
#include "display_triple_digit.hpp"
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
    std::unique_ptr<std::thread> g_ChangeUnitsToGayButton;
    std::unique_ptr<std::thread> g_ResetStatButtonThread;
    std::unique_ptr<std::thread> g_TimerThread;

    DisplayState g_DisplayState = DisplayState::Speed;
    std::mutex g_DisplayStateMutex;

    void initialize()
    {
        wiringPiSetup();
        pinMode(PIN1, OUTPUT);
        pinMode(PIN2, OUTPUT);
        pinMode(PIN3, OUTPUT);
        pinMode(PIN4, OUTPUT);
        pinMode(PIN5, OUTPUT);
        pinMode(PIN6, OUTPUT);
        pinMode(PIN7, OUTPUT);
        pinMode(PIN8, OUTPUT);
        pinMode(PIN9, OUTPUT);
        pinMode(PIN10, OUTPUT);
        pinMode(PIN11, OUTPUT);
        pinMode(PIN12, OUTPUT);
        pinMode(PIN13, OUTPUT);
        pinMode(PIN14, OUTPUT);
        pinMode(PIN15, OUTPUT);
        pinMode(PIN16, OUTPUT);
        pinMode(PIN_DIG1, OUTPUT);
        pinMode(PIN_DIG2, OUTPUT);
        pinMode(PIN_DIG3, OUTPUT);
        pinMode(PIN_SCROLL_RIGHT_BUTTON, INPUT);
        pinMode(PIN_SCROLL_LEFT_BUTTON, INPUT);
        pinMode(PIN_CHANGE_UNITS_BUTTON, INPUT);
        pinMode(PIN_RESET_STAT, INPUT);

        Animations::welcome();

        g_SingleDigitThread.reset(SingleDigit::startThread());
        g_TripleDigitThread.reset(TripleDigit::startThread());
        g_ScreenScrollRightButtonThread.reset(Buttons::startScreenScrollRightButtonThread());
        g_ScreenScrollLeftButtonThread.reset(Buttons::startScreenScrollLeftButtonThread());
        g_ChangeUnitsToGayButton.reset(Buttons::startChangeUnitsToGayThread());
        g_ResetStatButtonThread.reset(Buttons::startResetStatButtonThread());
        g_TimerThread.reset(Timers::startThread());
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

}