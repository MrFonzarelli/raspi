#include "buttons.hpp"
#include "data.hpp"
#include "io.hpp"
#include "pins.hpp"
#include "timers.hpp"
#include "oled_display.hpp"
#include <chrono>
#include <functional>
#include <mutex>
#include <wiringPi.h>

namespace IO::Buttons
{
    void doButtonWork(int buttonPin, std::function<void()> callback)
    {
        int desButtonState = 0;
        int lastButtonState = 0;
        while (true)
        {
            desButtonState = digitalRead(buttonPin);
            if (lastButtonState != desButtonState)
            {
                if (lastButtonState == 0)
                {
                    callback();
                }
                lastButtonState = desButtonState;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void buttonResetStatAction()
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

    void buttonMultiAction()
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

    std::thread *startButtonThread(int buttonPin, std::function<void()> callback)
    {
        return new std::thread(doButtonWork, buttonPin, callback);
    }

}