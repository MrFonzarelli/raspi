#include "display_triple_digit.hpp"
#include "io.hpp"
#include "data.hpp"
#include "pins.hpp"
#include <chrono>
#include <cmath>
#include <mutex>
#include <wiringPi.h>

namespace IO::TripleDigit
{

    int firstHandlerTri(void)
    {
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, LOW);
        return 1;
    }

    int secondHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, LOW);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, HIGH);
        return 2;
    }

    int thirdHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, HIGH);
        return 3;
    }

    int fourthHandlerTri(void)
    {
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        return 4;
    }

    int fifthHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        return 5;
    }

    int sixthHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        return 6;
    }

    int seventhHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, LOW);
        return 7;
    }

    int eighthHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        return 8;
    }

    int ninethHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        return 9;
    }

    int zeroHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);  // A
        digitalWrite(PIN10, HIGH); // B
        digitalWrite(PIN11, HIGH); // C
        digitalWrite(PIN12, HIGH); // D
        digitalWrite(PIN13, HIGH); // E
        digitalWrite(PIN14, HIGH); // F
        digitalWrite(PIN15, LOW);  // G
        return 0;
    }

    int minusHandlerTri(void)
    {
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, LOW);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, HIGH);
        return 0;
    }

    int digitSelect(int num)
    {
        switch (num)
        {
        case 0:
        {
            num = zeroHandlerTri();
            break;
        }
        case 1:
        {
            num = firstHandlerTri();
            break;
        }
        case 2:
        {
            num = secondHandlerTri();
            break;
        }
        case 3:
        {
            num = thirdHandlerTri();
            break;
        }
        case 4:
        {
            num = fourthHandlerTri();
            break;
        }
        case 5:
        {
            num = fifthHandlerTri();
            break;
        }
        case 6:
        {
            num = sixthHandlerTri();
            break;
        }
        case 7:
        {
            num = seventhHandlerTri();
            break;
        }
        case 8:
        {
            num = eighthHandlerTri();
            break;
        }
        case 9:
        {
            num = ninethHandlerTri();
            break;
        }
        case 10:
        {
            num = minusHandlerTri();
            break;
        }
        default:
        {
            num = ninethHandlerTri();
            break;
        }
        }
        return num;
    }

    int digParser(int num, Data::Tick tick, DisplayState displayState)
    {
        int dig;
        switch (displayState)
        {
        case DisplayState::Speed:
        {
            dig = lround(tick.outGauge.speed * 3.6); // km/h
            break;
        }
        case DisplayState::TurboPressure:
        {
            dig = lround(tick.outGauge.turbo * 10); // bar
            break;
        }
        case DisplayState::TripOdometer:
        {
            dig = lround(tick.odometer.trip * 10); // km
            break;
        }
        case DisplayState::Odometer:
        {
            dig = lround((tick.odometer.total + tick.odometer.trip) * 10);
            break;
        }
        case DisplayState::EngineTemp:
        {
            dig = lround(tick.outGauge.engTemp);
            break;
        }
        case DisplayState::OilTemp:
        {
            dig = lround(tick.outGauge.oilTemp);
            break;
        }
        case DisplayState::CurrentFuelConsumption:
        {
            dig = lround(tick.fuelCons * 10);
            break;
        }
        case DisplayState::AverageFuelConsumption:
        {
            dig = lround(tick.fuelConsAvg * 10);
            break;
        }
        }

        switch (num)
        {
        case 1:
        {
            int dig1;
            dig1 = abs(dig) / 100 % 10;
            return dig1;
            break;
        }
        case 2:
        {
            int dig2;
            dig2 = abs(dig) / 10 % 10;
            return dig2;
            break;
        }
        case 3:
        {
            int dig3;
            dig3 = abs(dig) % 10;
            return dig3;
            break;
        }
        }
        return 0;
    }

    void tripleDigitOutput(DisplayState &displayStateRef, std::mutex &displayStateMutex)
    {
        Data::Tick tick = Data::get();
        int dig1;
        int dig2;
        int dig3;

        displayStateMutex.lock();
        DisplayState displayState = displayStateRef;
        displayStateMutex.unlock();

        dig1 = digParser(1, tick, displayState);
        dig2 = digParser(2, tick, displayState);
        dig3 = digParser(3, tick, displayState);

        switch (displayState)
        {                                 // This decribes how to display each different displayState i.e. whether or not to use pin16(DP)
        case DisplayState::TurboPressure: // These describe the specific behaviour i.e. if the first digit going from the left is 0 skip displaying that digit
        {
            if (tick.outGauge.turbo < 0) // This can display small negative numbers with a minus sign
            {
                digitalWrite(PIN_DIG3, LOW);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_DIG3, HIGH);
                digitalWrite(PIN_DIG2, LOW);
                digitSelect(dig2);
                digitalWrite(PIN16, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_DIG2, HIGH);
                digitalWrite(PIN16, LOW);
                digitalWrite(PIN_DIG1, LOW);
                digitSelect(10);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_DIG1, HIGH);
            }
            else
            {
                if (dig1 == 0)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_DIG3, LOW);
                    digitSelect(dig3);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_DIG3, HIGH);
                    digitalWrite(PIN_DIG2, LOW);
                    digitSelect(dig2);
                    digitalWrite(PIN16, HIGH);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_DIG2, HIGH);
                    digitalWrite(PIN16, LOW);
                }
                else
                {
                    digitalWrite(PIN_DIG3, LOW);
                    digitSelect(dig3);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_DIG3, HIGH);
                    digitalWrite(PIN_DIG2, LOW);
                    digitSelect(dig2);
                    digitalWrite(PIN16, HIGH);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_DIG2, HIGH);
                    digitalWrite(PIN16, LOW);
                    digitalWrite(PIN_DIG1, LOW);
                    digitSelect(dig1);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_DIG1, HIGH);
                }
            }
            break;
        }
        case DisplayState::TripOdometer:
        case DisplayState::Odometer:
        case DisplayState::CurrentFuelConsumption:
        case DisplayState::AverageFuelConsumption:
        {
            if (dig1 == 0) // This displays two digits (up to 99) and the DP
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_DIG3, LOW);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_DIG3, HIGH);
                digitalWrite(PIN_DIG2, LOW);
                digitSelect(dig2);
                digitalWrite(PIN16, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_DIG2, HIGH);
                digitalWrite(PIN16, LOW);
            }
            else
            {
                digitalWrite(PIN_DIG3, LOW);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_DIG3, HIGH);
                digitalWrite(PIN_DIG2, LOW);
                digitSelect(dig2);
                digitalWrite(PIN16, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_DIG2, HIGH);
                digitalWrite(PIN16, LOW);
                digitalWrite(PIN_DIG1, LOW);
                digitSelect(dig1);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_DIG1, HIGH);
            }
            break;
        }
        default: // Anything that will be using all three digits without the DP pin should stay on default
        {
            if (dig1 == 0)
            {
                if (dig2 == 0)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_DIG3, LOW);
                    digitSelect(dig3);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_DIG3, HIGH);
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_DIG3, LOW);
                    digitSelect(dig3);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_DIG3, HIGH);
                    digitalWrite(PIN_DIG2, LOW);
                    digitSelect(dig2);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_DIG2, HIGH);
                }
            }
            else
            {
                digitalWrite(PIN_DIG3, LOW);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_DIG3, HIGH);
                digitalWrite(PIN_DIG2, LOW);
                digitSelect(dig2);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_DIG2, HIGH);
                digitalWrite(PIN_DIG1, LOW);
                digitSelect(dig1);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_DIG1, HIGH);
            }
            break;
        }
        }
    }

    void doTripleDigitWork(DisplayState &displayState, std::mutex &displayStateMutex, bool &gayUnits, std::mutex &gayUnitsMutex)
    {
        while (true)
        {
            tripleDigitOutput(displayState, displayStateMutex, gayUnits, gayUnitsMutex);
            std::this_thread::sleep_for(std::chrono::milliseconds(Data::ACCESS_DELAY_MS));
        }
    }

    std::thread *startThread(DisplayState &displayState, std::mutex &displayStateMutex, bool &gayUnits, std::mutex &gayUnitsMutex)
    {
        return new std::thread(doTripleDigitWork, std::ref(displayState), std::ref(displayStateMutex), std::ref(gayUnits), std::ref(gayUnitsMutex));
    }

}