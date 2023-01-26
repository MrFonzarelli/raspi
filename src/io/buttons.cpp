#include "buttons.hpp"
#include "data.hpp"
#include "io.hpp"
#include "pins.hpp"
#include "timers.hpp"
#include "oled_display.hpp"
#include <chrono>
#include <mutex>
#include <wiringPi.h>

namespace IO::Buttons
{

    void doScreenScrollRightButtonWork()
    {
        int des_RightbuttonState = 0;
        int last_RightbuttonState = 0;
        while (true)
        {
            des_RightbuttonState = digitalRead(PIN_SCROLL_RIGHT_BUTTON);
            if (last_RightbuttonState != des_RightbuttonState)
            {
                if (last_RightbuttonState == 0)
                {
                    nextDisplayState();
                }
                last_RightbuttonState = des_RightbuttonState;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void doScreenScrollLeftButtonWork()
    {
        int des_LeftbuttonState = 0;
        int last_LeftbuttonState = 0;
        while (true)
        {
            des_LeftbuttonState = digitalRead(PIN_SCROLL_LEFT_BUTTON);
            if (last_LeftbuttonState != des_LeftbuttonState)
            {
                if (last_LeftbuttonState == 0)
                {
                    previousDisplayState();
                }
                last_LeftbuttonState = des_LeftbuttonState;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void doResetStatButtonWork()
    {
        int des_ResetStatButtonState = 0;
        int last_ResetStatButtonState = 0;
        while (true)
        {
            des_ResetStatButtonState = digitalRead(PIN_RESET_STAT);
            if (last_ResetStatButtonState != des_ResetStatButtonState)
            {
                if (last_ResetStatButtonState == 0)
                {
                    switch (IO::getDisplayState())
                    {
                    case DisplayState::AverageFuelConsumption:
                    {
                        Data::resetAvgFuelConsumption();
                        break;
                    }
                    case DisplayState::TripOdometer:
                    {
                        Data::resetTripOdometer();
                        break;
                    }
                    case DisplayState::ZeroTo100:
                    case DisplayState::ZeroTo200:
                    case DisplayState::ZeroTo300:
                    case DisplayState::QuarterMile:
                    case DisplayState::HundredTo200:
                    case DisplayState::HundredTo300:
                    case DisplayState::TwoHundredTo300:
                    {
                        Timers::reset();
                        break;
                    }
                    case DisplayState::CustomTimer:
                    {
                        if (IO::Timers::timerCustomIsRunning())
                        {
                            IO::OLED::staticMessageOLED("Finish", 3, 500);
                            IO::Timers::stopTimerCustom();
                        }
                        else
                        {
                            IO::OLED::staticMessageOLED("Start", 3, 500);
                            IO::Timers::resetTimerCustom();
                            IO::Timers::startTimerCustom();
                        }
                        break;
                    }
                    }
                }
                last_ResetStatButtonState = des_ResetStatButtonState;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void doMultiButtonWork()
    {
        int des_MultiButtonState = 0;
        int last_MultiButtonState = 0;
        while (true)
        {
            des_MultiButtonState = digitalRead(PIN_MULTI_BUTTON);
            if (last_MultiButtonState != des_MultiButtonState)
            {
                if (last_MultiButtonState == 0)
                {
                    switch (IO::getDisplayState())
                    {
                    case DisplayState::CustomTimer:
                    {
                        if (IO::Timers::timerCustomIsRunning())
                        {
                            IO::Timers::splitTimerCustom();
                            IO::OLED::staticMessageOLED("Split", 3, 2500);
                            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                            IO::Timers::unsplitTimerCustom();
                        }
                        break;
                    }
                    default:
                        previousDisplayState();
                        break;
                    }
                }
                last_MultiButtonState = des_MultiButtonState;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    std::thread *startScreenScrollLeftButtonThread()
    {
        return new std::thread(doScreenScrollLeftButtonWork);
    }

    std::thread *startScreenScrollRightButtonThread()
    {
        return new std::thread(doScreenScrollRightButtonWork);
    }

    std::thread *startMultiButtonThread()
    {
        return new std::thread(doMultiButtonWork);
    }

    std::thread *startResetStatButtonThread()
    {
        return new std::thread(doResetStatButtonWork);
    }

}