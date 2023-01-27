#include "io.hpp"
#include "animations.hpp"
#include "buttons.hpp"
#include "display_single_digit.hpp"
#include "display_triple_digit.hpp"
#include "oled_display.hpp"
#include "lights.hpp"
#include "pins.hpp"
#include "settings.hpp"
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

    int g_CurrentDisplayStateIdx;
    std::vector<DisplayState> g_ActiveDisplayStates;
    CombinedDisplayType g_CombinedDisplay1;
    CombinedDisplayType g_CombinedDisplay2;
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
        pinMode(PIN_MULTI_BUTTON, INPUT);
        pinMode(PIN_RESET_STAT, INPUT);
        pinMode(PIN_DASHLIGHT_LED1, INPUT);
        pinMode(PIN_DASHLIGHT_LED2, INPUT);
        pinMode(PIN_DASHLIGHT_LED3, INPUT);
        pinMode(PIN_DASHLIGHT_LED4, INPUT);

        auto ioSettings = Settings::getIOSettings();

        if (ioSettings.doWelcomeAnimation)
            Animations::welcome();

        g_CurrentDisplayStateIdx = 0;
        g_ActiveDisplayStates = ioSettings.activeDisplayStates;
        g_CombinedDisplay1.displayStateLeft = DisplayState::TurboPressure;
        g_CombinedDisplay1.displayStateRight = DisplayState::Speed;
        g_CombinedDisplay2.displayStateLeft = DisplayState::RPM;
        g_CombinedDisplay2.displayStateRight = DisplayState::Speed;

        if (ioSettings.singleDigitDisplaySettings.enabled)
        {
            g_SingleDigitThread.reset(SingleDigit::startThread());
        }
        g_TripleDigitThread.reset(TripleDigit::startThread());
        g_ScreenScrollRightButtonThread.reset(Buttons::startButtonThread(PIN_SCROLL_RIGHT_BUTTON, nextDisplayState));
        g_ScreenScrollLeftButtonThread.reset(Buttons::startButtonThread(PIN_SCROLL_LEFT_BUTTON, previousDisplayState));
        g_MultiButtonThread.reset(Buttons::startButtonThread(PIN_MULTI_BUTTON, Buttons::buttonMultiAction));
        g_ResetStatButtonThread.reset(Buttons::startButtonThread(PIN_RESET_STAT, Buttons::buttonResetStatAction));
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
        DisplayState result = g_ActiveDisplayStates[g_CurrentDisplayStateIdx];
        g_DisplayStateMutex.unlock();
        return result;
    }

    int getDisplayStateCount()
    {
        g_DisplayStateMutex.lock();
        int result = g_ActiveDisplayStates.size();
        g_DisplayStateMutex.unlock();
        return result;
    }

    int getCurrentDisplayStateIndex()
    {
        g_DisplayStateMutex.lock();
        int result = g_CurrentDisplayStateIdx;
        g_DisplayStateMutex.unlock();
        return result;
    }

    void nextDisplayState()
    {
        g_DisplayStateMutex.lock();
        g_CurrentDisplayStateIdx = ((int)g_CurrentDisplayStateIdx + 1) % g_ActiveDisplayStates.size();
        g_DisplayStateMutex.unlock();
    }

    void previousDisplayState()
    {
        g_DisplayStateMutex.lock();
        g_CurrentDisplayStateIdx = ((int)g_CurrentDisplayStateIdx + g_ActiveDisplayStates.size() - 1) % g_ActiveDisplayStates.size();
        g_DisplayStateMutex.unlock();
    }

    CombinedDisplayType getCombinedDisplayState()
    {
        g_DisplayStateMutex.lock();
        CombinedDisplayType result;
        switch (g_DisplayState)
        {
        case DisplayState::Combined1:
        {
            result = g_CombinedDisplay1;
            break;
        }
        case DisplayState::Combined2:
        {
            result = g_CombinedDisplay2;
            break;
        }
        }
        g_DisplayStateMutex.unlock();
        return result;
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
            return DisplayStateType::Decimal;
        case DisplayState::Combined1:
        case DisplayState::Combined2:
            return DisplayStateType::Combined;
        default:
            return DisplayStateType::Integer;
        }
    }

}