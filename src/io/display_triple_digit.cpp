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
        digitalWrite(PIN_TRIPLE_DIG_A, LOW);
        digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_D, LOW);
        digitalWrite(PIN_TRIPLE_DIG_E, LOW);
        digitalWrite(PIN_TRIPLE_DIG_F, LOW);
        digitalWrite(PIN_TRIPLE_DIG_G, LOW);
        return 1;
    }

    int secondHandlerTri(void)
    {
        digitalWrite(PIN_TRIPLE_DIG_A, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_C, LOW);
        digitalWrite(PIN_TRIPLE_DIG_D, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_E, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_F, LOW);
        digitalWrite(PIN_TRIPLE_DIG_G, HIGH);
        return 2;
    }

    int thirdHandlerTri(void)
    {
        digitalWrite(PIN_TRIPLE_DIG_A, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_D, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_E, LOW);
        digitalWrite(PIN_TRIPLE_DIG_F, LOW);
        digitalWrite(PIN_TRIPLE_DIG_G, HIGH);
        return 3;
    }

    int fourthHandlerTri(void)
    {
        digitalWrite(PIN_TRIPLE_DIG_A, LOW);
        digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_D, LOW);
        digitalWrite(PIN_TRIPLE_DIG_E, LOW);
        digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_G, HIGH);
        return 4;
    }

    int fifthHandlerTri(void)
    {
        digitalWrite(PIN_TRIPLE_DIG_A, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_B, LOW);
        digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_D, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_E, LOW);
        digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_G, HIGH);
        return 5;
    }

    int sixthHandlerTri(void)
    {
        digitalWrite(PIN_TRIPLE_DIG_A, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_B, LOW);
        digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_D, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_E, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_G, HIGH);
        return 6;
    }

    int seventhHandlerTri(void)
    {
        digitalWrite(PIN_TRIPLE_DIG_A, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_D, LOW);
        digitalWrite(PIN_TRIPLE_DIG_E, LOW);
        digitalWrite(PIN_TRIPLE_DIG_F, LOW);
        digitalWrite(PIN_TRIPLE_DIG_G, LOW);
        return 7;
    }

    int eighthHandlerTri(void)
    {
        digitalWrite(PIN_TRIPLE_DIG_A, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_D, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_E, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_G, HIGH);
        return 8;
    }

    int ninethHandlerTri(void)
    {
        digitalWrite(PIN_TRIPLE_DIG_A, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_D, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_E, LOW);
        digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_G, HIGH);
        return 9;
    }

    int zeroHandlerTri(void)
    {
        digitalWrite(PIN_TRIPLE_DIG_A, HIGH); // A
        digitalWrite(PIN_TRIPLE_DIG_B, HIGH); // B
        digitalWrite(PIN_TRIPLE_DIG_C, HIGH); // C
        digitalWrite(PIN_TRIPLE_DIG_D, HIGH); // D
        digitalWrite(PIN_TRIPLE_DIG_E, HIGH); // E
        digitalWrite(PIN_TRIPLE_DIG_F, HIGH); // F
        digitalWrite(PIN_TRIPLE_DIG_G, LOW);  // G
        return 0;
    }

    int minusHandlerTri(void)
    {
        digitalWrite(PIN_TRIPLE_DIG_A, LOW);
        digitalWrite(PIN_TRIPLE_DIG_B, LOW);
        digitalWrite(PIN_TRIPLE_DIG_C, LOW);
        digitalWrite(PIN_TRIPLE_DIG_D, LOW);
        digitalWrite(PIN_TRIPLE_DIG_E, LOW);
        digitalWrite(PIN_TRIPLE_DIG_F, LOW);
        digitalWrite(PIN_TRIPLE_DIG_G, HIGH);
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

    void renderTripleDigitFrame(int dig1, int dig2, int dig3, bool dp1, bool dp2, bool neg) // Frame with disappearing zeros
    {
        if (neg)
        {
            if (dp1)
            {
                digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
                if (dp2)
                {
                    digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                    digitSelect(dig2);
                    digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);

                    digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
                    digitSelect(dig1);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
                    digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
                }
                else
                {
                    digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                    digitSelect(dig2);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);

                    digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
                    digitSelect(dig1);
                    digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
                    digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
                }
            }
            else
            {
                if (dp2)
                {
                    if (dig1 == 0)
                    {
                        digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
                        digitSelect(dig3);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);

                        digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                        digitSelect(dig2);
                        digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
                        digitalWrite(PIN_TRIPLE_DIG_DP, LOW);

                        digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
                        digitSelect(10);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
                    }
                    else
                    {
                        digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
                        digitSelect(dig2);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);

                        digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                        digitSelect(dig1);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);

                        digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
                        digitSelect(10);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
                    }
                }
                else
                {
                    if (dig1 == 0)
                    {
                        if (dig2 == 0)
                        {
                            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
                            digitSelect(dig3);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);

                            digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                            digitSelect(10);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                            digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);

                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        }
                        else
                        {
                            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
                            digitSelect(dig3);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);

                            digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                            digitSelect(dig2);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                            digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);

                            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
                            digitSelect(10);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
                        }
                    }
                    else
                    {
                        digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
                        digitSelect(dig2);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);

                        digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                        digitSelect(dig1);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);

                        digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
                        digitSelect(10);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
                    }
                }
            }
        }
        else
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
            digitSelect(dig3);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);

            if (dp1)
            {
                if (dp2)
                {
                    digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                    digitSelect(dig2);
                    digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);

                    digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
                    digitSelect(dig1);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
                    digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
                }
                else
                {
                    digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                    digitSelect(dig2);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);

                    digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
                    digitSelect(dig1);
                    digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
                    digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
                }
            }
            else
            {
                if (dp2)
                {
                    if (dig1 == 0)
                    {
                        digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                        digitSelect(dig2);
                        digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
                        digitalWrite(PIN_TRIPLE_DIG_DP, LOW);

                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    }
                    else
                    {
                        digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                        digitSelect(dig2);
                        digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
                        digitalWrite(PIN_TRIPLE_DIG_DP, LOW);

                        digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
                        digitSelect(dig1);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
                    }
                }
                else
                {
                    if (dig1 == 0)
                    {
                        if (dig2 == 0)
                        {
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT * 2));
                        }
                        else
                        {
                            digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                            digitSelect(dig2);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                            digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);

                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        }
                    }
                    else
                    {
                        digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                        digitSelect(dig2);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);

                        digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
                        digitSelect(dig1);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
                    }
                }
            }
        }
    }

    void renderTripleDigitFullFrame(int dig1, int dig2, int dig3, bool dp1, bool dp2) // Frame with non disappearing zeros
    {
        digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
        digitSelect(dig3);
        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
        digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);

        if (dp2)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
            digitSelect(dig2);
            digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
        }
        else
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
            digitSelect(dig2);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
        }

        if (dp1)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
            digitSelect(dig1);
            digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
        }
        else
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
            digitSelect(dig1);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
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
        int dig1;
        int dig2;
        int dig3;
        bool dp1 = false;
        bool dp2 = false;
        Data::Tick tick = Data::get();

        DisplayState displayState = getDisplayState();

        int numberToDisplay = getValueToDisplay(tick, displayState);

        switch (displayTypeOf(displayState)) // Set up the digits to be displayed
        {
        case DisplayStateType::Time:
        {
            if (numberToDisplay / 100 >= 10) // True for times longer than 10s
            {
                if (numberToDisplay / 100 >= 60) // True for times longer than 1 minute
                {
                    if (numberToDisplay / 100 >= 600) // True for times longer than 10 minutes
                    {
                        numberToDisplay /= 100;
                        dig1 = (numberToDisplay / 60) / 10 % 10;
                        dig2 = numberToDisplay / 60 % 10;
                        dig3 = (numberToDisplay % 60) / 10 % 10;
                        dp2 = true;
                    }
                    else
                    {
                        numberToDisplay /= 100;
                        dig1 = numberToDisplay / 60 % 10;
                        dig2 = (numberToDisplay % 60) / 10 % 10;
                        dig3 = (numberToDisplay % 60) % 10;
                        dp1 = true;
                    }
                }
                else
                {
                    numberToDisplay /= 10;
                    dig1 = numberToDisplay / 100 % 10;
                    dig2 = numberToDisplay / 10 % 10;
                    dig3 = numberToDisplay % 10;
                    dp2 = true;
                }
            }
            else
            {
                dig1 = numberToDisplay / 100 % 10;
                dig2 = numberToDisplay / 10 % 10;
                dig3 = numberToDisplay % 10;
                dp1 = true;
            }
            break;
        }
        default: // Sofar everything else
        {
            dig1 = numberToDisplay / 100 % 10;
            dig2 = numberToDisplay / 10 % 10;
            dig3 = numberToDisplay % 10;
            break;
        }
        }

        switch (displayTypeOf(displayState)) // Render frame on the display
        {
        case DisplayStateType::Decimal_OnePlace:
        {
            renderTripleDigitFrame(dig1, dig2, dig3, false, true, numberToDisplay < 0);
            break;
        }
        case DisplayStateType::Decimal_TwoPlaces:
        {
            renderTripleDigitFrame(dig1, dig2, dig3, true, false, numberToDisplay < 0);
            break;
        }
        case DisplayStateType::Time:
        {
            renderTripleDigitFullFrame(dig1, dig2, dig3, dp1, dp2);
            break;
        }
        default:
        {
            renderTripleDigitFrame(dig1, dig2, dig3, false, false, false);
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