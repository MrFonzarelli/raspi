#include "buttons.hpp"
#include "pins.hpp"
#include "data.hpp"
#include "io.hpp"
#include <chrono>
#include <mutex>
#include <wiringPi.h>

namespace IO::Buttons
{

    void doScreenScrollRightButtonWork(DisplayState &displayStateRef, std::mutex &displayStateMutex)
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
                    displayStateMutex.lock();
                    DisplayState displayState = displayStateRef;
                    displayStateRef = (DisplayState)(((int)displayState + 1) % DISPLAY_STATE_COUNT);
                    displayStateMutex.unlock();
                }
                last_RightbuttonState = des_RightbuttonState;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void doScreenScrollLeftButtonWork(DisplayState &displayStateRef, std::mutex &displayStateMutex)
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
                    displayStateMutex.lock();
                    DisplayState displayState = displayStateRef;
                    displayStateRef = (DisplayState)(((int)displayState + IO::DISPLAY_STATE_COUNT - 1) % IO::DISPLAY_STATE_COUNT);
                    displayStateMutex.unlock();
                }
                last_LeftbuttonState = des_LeftbuttonState;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void doResetStatButtonWork()
    {
        DisplayState displayState = IO::getDisplayState();
        int des_ResetStatButtonState = 0;
        int last_ResetStatButtonState = 0;
        while (true)
        {
            des_ResetStatButtonState = digitalRead(PIN_RESET_STAT);
            if (last_ResetStatButtonState != des_ResetStatButtonState)
            {
                if (last_ResetStatButtonState == 0)
                {
                    switch (displayState)
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
                    }
                }
                last_ResetStatButtonState = des_ResetStatButtonState;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void doExtremelyGayButtonWork()
    {
        int des_ExtremelyGayButtonState = 0;
        int last_ExtremelyGayButtonState = 0;
        while (true)
        {
            des_ExtremelyGayButtonState = digitalRead(PIN_CHANGE_UNITS_BUTTON);
            if (last_ExtremelyGayButtonState != des_ExtremelyGayButtonState)
            {
                if (last_ExtremelyGayButtonState == 0)
                {
                    Data::toggleUnits();
                }
                last_ExtremelyGayButtonState = des_ExtremelyGayButtonState;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    std::thread *startScreenScrollLeftButtonThread(DisplayState &displayStateRef, std::mutex &displayStateMutex)
    {
        return new std::thread(doScreenScrollLeftButtonWork, std::ref(displayStateRef), std::ref(displayStateMutex));
    }

    std::thread *startScreenScrollRightButtonThread(DisplayState &displayStateRef, std::mutex &displayStateMutex)
    {
        return new std::thread(doScreenScrollRightButtonWork, std::ref(displayStateRef), std::ref(displayStateMutex));
    }

    std::thread *startChangeUnitsToGayThread()
    {
        return new std::thread(doExtremelyGayButtonWork);
    }

    std::thread *startResetStatButtonThread()
    {
        return new std::thread(doResetStatButtonWork);
    }

}