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

    std::mutex g_isStoppedMutex;
    bool g_isStopped = false;

    bool isStopped()
    {
        std::lock_guard<std::mutex> lock(g_isStoppedMutex);
        return g_isStopped;
    }

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
                digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
                if (dp2)
                {
                    digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                    digitSelect(dig2);
                    digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);

                    digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                    digitSelect(dig1);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
                    digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
                }
                else
                {
                    digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                    digitSelect(dig2);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);

                    digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                    digitSelect(dig1);
                    digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
                    digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
                }
            }
            else
            {
                if (dp2)
                {
                    if (dig1 == 0)
                    {
                        digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
                        digitSelect(dig3);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);

                        digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                        digitSelect(dig2);
                        digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
                        digitalWrite(PIN_TRIPLE_DIG_DP, LOW);

                        digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                        digitSelect(10);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
                    }
                    else
                    {
                        digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
                        digitSelect(dig2);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);

                        digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                        digitSelect(dig1);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);

                        digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                        digitSelect(10);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
                    }
                }
                else
                {
                    if (dig1 == 0)
                    {
                        if (dig2 == 0)
                        {
                            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
                            digitSelect(dig3);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);

                            digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                            digitSelect(10);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                            digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);

                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        }
                        else
                        {
                            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
                            digitSelect(dig3);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);

                            digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                            digitSelect(dig2);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                            digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);

                            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
                            digitSelect(10);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
                        }
                    }
                    else
                    {
                        digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
                        digitSelect(dig2);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);

                        digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                        digitSelect(dig1);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);

                        digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                        digitSelect(10);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
                    }
                }
            }
        }
        else
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
            digitSelect(dig3);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);

            if (dp1)
            {
                if (dp2)
                {
                    digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                    digitSelect(dig2);
                    digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);

                    digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                    digitSelect(dig1);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
                    digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
                }
                else
                {
                    digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                    digitSelect(dig2);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);

                    digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                    digitSelect(dig1);
                    digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
                    digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
                }
            }
            else
            {
                if (dp2)
                {
                    if (dig1 == 0)
                    {
                        digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                        digitSelect(dig2);
                        digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
                        digitalWrite(PIN_TRIPLE_DIG_DP, LOW);

                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                    }
                    else
                    {
                        digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                        digitSelect(dig2);
                        digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
                        digitalWrite(PIN_TRIPLE_DIG_DP, LOW);

                        digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                        digitSelect(dig1);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
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
                            digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                            digitSelect(dig2);
                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                            digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);

                            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        }
                    }
                    else
                    {
                        digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                        digitSelect(dig2);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);

                        digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                        digitSelect(dig1);
                        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                        digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
                    }
                }
            }
        }
    }

    void renderTripleDigitTwoDPFrame(int dig1, int dig2, int dig3, int dig4, int dig5, int dig6, bool dp1, bool dp2) // Frame with non disappearing zeros
    {
        digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
        digitSelect(dig6);
        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
        digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);

        if (dig1 != 0)
        {
            if (dp2)
            {
                digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                digitSelect(dig5);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                digitSelect(dig4);
                digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
            }
            else
            {
                digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                digitSelect(dig5);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                digitSelect(dig4);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
            }
            if (dp1)
            {
                digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
                digitSelect(dig2);
                digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
                digitSelect(dig1);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
            }
            else
            {
                digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
                digitSelect(dig2);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
                digitSelect(dig1);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
            }
        }
        else if (dig2 != 0)
        {
            if (dp2)
            {
                digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                digitSelect(dig5);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                digitSelect(dig4);
                digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
            }
            else
            {
                digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                digitSelect(dig5);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                digitSelect(dig4);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
            }
            if (dp1)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
                digitSelect(dig2);
                digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
                digitSelect(dig3);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
                digitSelect(dig2);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
            }
        }
        else if (dig3 != 0)
        {
            if (dp2)
            {
                digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                digitSelect(dig5);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                digitSelect(dig4);
                digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
            }
            else
            {
                digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
                digitSelect(dig5);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
                digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
                digitSelect(dig4);
                std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
                digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitSelect(dig3);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
        }
        else if (dp2)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
            digitSelect(dig5);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
            digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
            digitSelect(dig4);
            digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
            digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
        }
        else if (dig4 != 0)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
            digitSelect(dig5);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
            digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
            digitSelect(dig4);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
        }
        else if (dig5 != 0)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
            digitSelect(dig5);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
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
        case DisplayState::RPM:
            return lround(tick.outGauge.rpm);
        case DisplayState::ZeroTo100:
        case DisplayState::ZeroTo200:
        case DisplayState::ZeroTo300:
        case DisplayState::QuarterMile:
        case DisplayState::HundredTo200:
        case DisplayState::HundredTo300:
        case DisplayState::TwoHundredTo300:
        case DisplayState::CustomTimer:
            return lround(IO::Timers::getTime(displayState));
        }

        return 0;
    }

    void tripleDigitOutput()
    {
        int dig1;
        int dig2;
        int dig3;
        int dig4;
        int dig5;
        int dig6;
        Data::Tick tick = Data::get();

        DisplayState displayState = getDisplayState();

        int numberToDisplay = getValueToDisplay(tick, displayState);

        switch (displayTypeOf(displayState)) // Set up the digits to be displayed
        {
        case DisplayStateType::Time:
        {
            auto milliseconds = std::chrono::milliseconds(numberToDisplay);
            auto hours = std::chrono::duration_cast<std::chrono::hours>(milliseconds).count();
            auto minutes = std::chrono::duration_cast<std::chrono::minutes>(milliseconds).count() % 60;
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(milliseconds).count() % 60;
            auto centiseconds = milliseconds.count() / 10 % 100;
            if (hours >= 1)
            {
                dig1 = (hours % 24) / 10;
                dig2 = (hours % 24) % 10;
                dig3 = minutes / 10;
                dig4 = minutes % 10;
                dig5 = seconds / 10;
                dig6 = seconds % 10;
            }
            else
            {
                dig1 = minutes / 10;
                dig2 = minutes % 10;
                dig3 = seconds / 10;
                dig4 = seconds % 10;
                dig5 = centiseconds / 10;
                dig6 = centiseconds % 10;
            }
            break;
        }
        default: // Sofar everything else
        {
            dig1 = abs(numberToDisplay) / 100000 % 10;
            dig2 = abs(numberToDisplay) / 10000 % 10;
            dig3 = abs(numberToDisplay) / 1000 % 10;
            dig4 = abs(numberToDisplay) / 100 % 10;
            dig5 = abs(numberToDisplay) / 10 % 10;
            dig6 = abs(numberToDisplay) % 10;
            break;
        }
        }

        switch (displayTypeOf(displayState)) // Render frame on the display
        {
        case DisplayStateType::Decimal_OnePlace:
        {
            renderTripleDigitFrame(dig4, dig5, dig6, false, true, numberToDisplay < 0);
            break;
        }
        case DisplayStateType::Decimal_TwoPlaces:
        {
            renderTripleDigitFrame(dig4, dig5, dig6, true, false, numberToDisplay < 0);
            break;
        }
        case DisplayStateType::Time:
        {
            renderTripleDigitTwoDPFrame(dig1, dig2, dig3, dig4, dig5, dig6, true, true);
            break;
        }
        default:
        {
            renderTripleDigitTwoDPFrame(dig1, dig2, dig3, dig4, dig5, dig6, false, false);
            break;
        }
        }
    }

    void doTripleDigitWork()
    {
        while (!isStopped())
        {
            tripleDigitOutput();
            std::this_thread::sleep_for(std::chrono::milliseconds(Data::ACCESS_DELAY_MS));
        }
    }

    std::thread *startThread()
    {
        return new std::thread(doTripleDigitWork);
    }

    void clearAndStop()
    {
        g_isStoppedMutex.lock();
        g_isStopped = true;
        g_isStoppedMutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        digitalWrite(PIN_TRIPLE_DIG_A, LOW);
        digitalWrite(PIN_TRIPLE_DIG_B, LOW);
        digitalWrite(PIN_TRIPLE_DIG_C, LOW);
        digitalWrite(PIN_TRIPLE_DIG_D, LOW);
        digitalWrite(PIN_TRIPLE_DIG_E, LOW);
        digitalWrite(PIN_TRIPLE_DIG_F, LOW);
        digitalWrite(PIN_TRIPLE_DIG_G, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
    }
}