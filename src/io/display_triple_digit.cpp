#include "display_triple_digit.hpp"
#include "io.hpp"
#include "data.hpp"
#include "pins.hpp"
#include "timers.hpp"
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

    void setPinInstrNumberWDecimalWNegative(double val, int dig1, int dig2, int dig3)
    {
        if (val < 0) // This can display small negative numbers with a minus sign
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
    }

    void setPinInstrTimeFormat(double val)
    {
        if (val / 100 >= 10) // True for times longer than 10s
        {
            if (val / 100 >= 60) // True for times longer than 1 minute
            {
                if (val / 100 >= 600) // True for times longer than 10 minutes
                {
                    val /= 100;
                    int dig1 = (val / 60) / 10 % 10;
                    int dig2 = val / 60 % 10;
                    int dig2 = (val - (val / 60)) / 10 % 10;
                    printf("Time : %i%im %is\n", dig1, dig2, dig3);
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
                else
                {
                    val /= 100;
                    int dig1 = val / 60 % 10;
                    int dig2 = (val - (val % 60)) / 10 % 10;
                    int dig3 = (val - ((val % 60) * ) % 10;
                    printf("Time : %im %i%is\n", dig1, dig2, dig3);
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
                    digitalWrite(PIN16, HIGH);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_DIG1, HIGH);
                    digitalWrite(PIN16, LOW);
                }
            }
            else
            {
                val /= 10;
                int dig1 = val / 100 % 10;
                int dig2 = val / 10 % 10;
                int dig3 = val % 10;
                printf("Time : %i%i.%is\n", dig1, dig2, dig3);
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
        else
        {
            int dig1 = val / 100 % 10;
            int dig2 = val / 10 % 10;
            int dig3 = val % 10;
            printf("Time : %i.%i%is\n", dig1, dig2, dig3);
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
            digitalWrite(PIN16, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_DIG1, HIGH);
            digitalWrite(PIN16, LOW);
        }
    }

    void setPinInstrNumber(int dig1, int dig2, int dig3)
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
    }

    int getValueToDisplay(const Data::Tick &tick, DisplayState displayState)
    {
        switch (displayState)
        {
        case DisplayState::Speed:
            return lround(tick.outGauge.speed * 3.6);
        case DisplayState::TurboPressure:
            return lround(tick.outGauge.turbo * 10);
        case DisplayState::TripOdometer:
            return lround(tick.odometer.trip * 10);
        case DisplayState::Odometer:
            return lround((tick.odometer.total + tick.odometer.trip) * 10);
        case DisplayState::EngineTemp:
            return lround(tick.outGauge.engTemp);
        case DisplayState::OilTemp:
            return lround(tick.outGauge.oilTemp);
        case DisplayState::CurrentFuelConsumption:
            return lround(tick.fuelCons * 10);
        case DisplayState::AverageFuelConsumption:
            return lround(tick.fuelConsAvg * 10);
        case DisplayState::ZeroTo100:
        case DisplayState::ZeroTo200:
        case DisplayState::ZeroTo300:
        case DisplayState::QuarterMile:
        case DisplayState::HundredTo200:
        case DisplayState::HundredTo300:
        case DisplayState::TwoHundredTo300:
            return lround(IO::Timers::getTime(displayState));
        }

        return 0;
    }

    void tripleDigitOutput()
    {
        Data::Tick tick = Data::get();

        DisplayState displayState = getDisplayState();

        int numberToDisplay = getValueToDisplay(tick, displayState);

        int dig1 = numberToDisplay / 100 % 10;
        int dig2 = numberToDisplay / 10 % 10;
        int dig3 = numberToDisplay % 10;

        switch (displayState)
        {
        case DisplayState::TripOdometer:
        case DisplayState::Odometer:
        case DisplayState::CurrentFuelConsumption:
        case DisplayState::AverageFuelConsumption:
        case DisplayState::TurboPressure:
        {
            setPinInstrNumberWDecimalWNegative(numberToDisplay, dig1, dig2, dig3);
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
            setPinInstrTimeFormat(numberToDisplay);
            break;
        }
        default:
        {
            setPinInstrNumber(dig1, dig2, dig3);
            break;
        }
        }
    }

    void doTripleDigitWork()
    {
        while (true)
        {
            tripleDigitOutput();
            std::this_thread::sleep_for(std::chrono::milliseconds(Data::ACCESS_DELAY_MS));
        }
    }

    std::thread *startThread()
    {
        return new std::thread(doTripleDigitWork);
    }

}