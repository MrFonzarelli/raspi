#include "display_triple_digit.hpp"
#include "io.hpp"
#include "data.hpp"
#include "pins.hpp"
#include "timers.hpp"
#include <chrono>
#include <cmath>
#include <mutex>
#include <vector>
#include <wiringPi.h>

namespace IO::TripleDigit
{

    std::mutex g_IsStoppedMutex;
    bool g_IsStopped = false;

    bool isStopped()
    {
        std::lock_guard<std::mutex> lock(g_IsStoppedMutex);
        return g_IsStopped;
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

    void digitSelect(int num)
    {
        switch (num)
        {
        case 0:
        {
            zeroHandlerTri();
            break;
        }
        case 1:
        {
            firstHandlerTri();
            break;
        }
        case 2:
        {
            secondHandlerTri();
            break;
        }
        case 3:
        {
            thirdHandlerTri();
            break;
        }
        case 4:
        {
            fourthHandlerTri();
            break;
        }
        case 5:
        {
            fifthHandlerTri();
            break;
        }
        case 6:
        {
            sixthHandlerTri();
            break;
        }
        case 7:
        {
            seventhHandlerTri();
            break;
        }
        case 8:
        {
            eighthHandlerTri();
            break;
        }
        case 9:
        {
            ninethHandlerTri();
            break;
        }
        case -1:
        {
            minusHandlerTri();
            break;
        }
        default:
        {
            ninethHandlerTri();
            break;
        }
        }
    }

    void renderTwoIntegers(int dig1, int dig2, int dig3, int dig4, int dig5, int dig6)
    {
        if (dig1 != 0)
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
        else if (dig2 != 0)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitSelect(dig3);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
            digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
            digitSelect(dig2);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
        }
        else
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitSelect(dig3);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
        }

        if (dig4 != 0)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
            digitSelect(dig6);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
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
            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
            digitSelect(dig6);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
            digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
            digitSelect(dig5);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
        }
        else
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
            digitSelect(dig6);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
        }
    }

    void renderTwoIntegersSeparated(int dig1, int dig2, int dig3, int dig4, int dig5, int dig6)
    {
        digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
        digitSelect(dig2);
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
                digitsToDisplay.erase(digitsToDisplay.begin() + i);
                i--;
            }
            else
            {
                break; // break when we hit a non-zero
            }
        }

        if (decimalPoints > 0) // This block only runs when we're supposed to display a decimal point
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
                if (decimalSpaces + 1 > digitsToDisplay.size())
                {
                    int diff = (decimalSpaces + 1) - digitsToDisplay.size();
                    digitsToDisplay.insert(digitsToDisplay.begin(), diff, 0);
                }
            }
            else
            {
                if (decimalPoints * decimalSpaces + 1 > digitsToDisplay.size())              // This condition makes sure all the decimal points are rendered by comparing the number of elements
                {                                                                            // in a vector with the minimum number of digits neccessary to display all decimal points fixing the
                    int diff = (decimalPoints * decimalSpaces + 1) - digitsToDisplay.size(); // difference by adding zeros to the beginning of the digitsToDisplay vector
                    digitsToDisplay.insert(digitsToDisplay.begin(), diff, 0);
                }
            }

            int dpCount = 0;
            for (int i = 1; i < digitsToDisplay.size() + 1; i++)                         // This adds the decimal points to the decimalPointsToDisplay vector accounting for the fact that
            {                                                                            // the decimal points are hardwarewise connected to the digits themselves
                if ((i + dpCount) % (decimalSpaces + 1) == 0 && dpCount < decimalPoints) // It checks whether or not its supposed to place a decimal point at this location and whether or
                {                                                                        // not it has already placed all decimal points
                    decimalPointsToDisplay.insert(decimalPointsToDisplay.begin(), 1, true);
                    dpCount += 1;
                }
                else
                {
                    decimalPointsToDisplay.insert(decimalPointsToDisplay.begin(), 1, false);
                }
            }
        }
        else // If no decimal points are to be displayed the decimalPointsToDisplay vector gets filled with all elements being false
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

    void renderTwoIntegers(int dig1, int dig2, int dig3, int dig4, int dig5, int dig6)
    {
        if (dig1 != 0)
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
        else if (dig2 != 0)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitSelect(dig3);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
            digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
            digitSelect(dig2);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
        }
        else
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitSelect(dig3);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
        }

        if (dig4 != 0)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
            digitSelect(dig6);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
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
            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
            digitSelect(dig6);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
            digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
            digitSelect(dig5);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
        }
        else
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
            digitSelect(dig6);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
        }
    }

    void renderTwoIntegersSeparated(int dig1, int dig2, int dig3, int dig4, int dig5, int dig6)
    {
        digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
        digitSelect(dig2);
        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
        digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
        digitSelect(dig1);
        digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
        digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DP, LOW);

        if (dig4 != 0)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
            digitSelect(dig6);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
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
            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
            digitSelect(dig6);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
            digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
            digitSelect(dig5);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
        }
        else
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
            digitSelect(dig6);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
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
        bool negativeCheck1;
        bool negativeCheck2;
        Data::Tick tick = Data::get();

        DisplayState displayState = getDisplayState();

        switch (displayTypeOf(displayState)) // Set up the digits to be displayed
        {
        case DisplayStateType::Time:
        {
            int numberToDisplay = getValueToDisplay(tick, displayState);
            auto milliseconds = std::chrono::milliseconds(numberToDisplay);
            auto hours = std::chrono::duration_cast<std::chrono::hours>(milliseconds).count();
            auto minutes = std::chrono::duration_cast<std::chrono::minutes>(milliseconds).count() % 60;
            auto seconds = std::chrono::duration_cast<std::chrono::seconds>(milliseconds).count() % 60;
            auto centiseconds = milliseconds.count() / 10 % 100;
            negativeCheck1 = numberToDisplay < 0;
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
        case DisplayStateType::TwoIntegers:
        {

            int numberToDisplay = getValueToDisplay(tick, DisplayState::Speed);
            int numberToDisplay2 = lround(getValueToDisplay(tick, DisplayState::RPM) / 10);
            negativeCheck1 = numberToDisplay < 0;
            negativeCheck2 = numberToDisplay2 < 0;
            dig1 = abs(numberToDisplay2) / 100 % 10;
            dig2 = abs(numberToDisplay2) / 10 % 10;
            dig3 = abs(numberToDisplay2) % 10;
            dig4 = abs(numberToDisplay) / 100 % 10;
            dig5 = abs(numberToDisplay) / 10 % 10;
            dig6 = abs(numberToDisplay) % 10;
            break;
        }
        case DisplayStateType::TwoIntegersSeparated:
        {
            int numberToDisplay = getValueToDisplay(tick, DisplayState::Speed);
            int numberToDisplay2 = lround(getValueToDisplay(tick, DisplayState::RPM) / 100);
            negativeCheck1 = numberToDisplay < 0;
            negativeCheck2 = numberToDisplay2 < 0;
            dig1 = abs(numberToDisplay2) / 10 % 10;
            dig2 = abs(numberToDisplay2) % 10;
            dig3 = 0;
            dig4 = abs(numberToDisplay) / 100 % 10;
            dig5 = abs(numberToDisplay) / 10 % 10;
            dig6 = abs(numberToDisplay) % 10;
            break;
        }
        default: // Sofar everything else
        {
            int numberToDisplay = getValueToDisplay(tick, displayState);
            negativeCheck1 = numberToDisplay < 0;
            dig1 = abs(numberToDisplay) / 100000 % 10;
            dig2 = abs(numberToDisplay) / 10000 % 10;
            dig3 = abs(numberToDisplay) / 1000 % 10;
            dig4 = abs(numberToDisplay) / 100 % 10;
            dig5 = abs(numberToDisplay) / 10 % 10;
            dig6 = abs(numberToDisplay) % 10;
            break;
        }
        }

        std::vector<int> vec{dig1, dig2, dig3, dig4, dig5, dig6};

        switch (displayTypeOf(displayState)) // Render frame on the display
        {
        case DisplayStateType::Decimal_OnePlace:
        {
            renderFrame(vec, 1, 1, false, negativeCheck1);
            break;
        }
        case DisplayStateType::Decimal_TwoPlaces:
        {
            renderFrame(vec, 2, 1, false, negativeCheck1);
            break;
        }
        case DisplayStateType::Time:
        {
            renderFrame(vec, 2, 2, true, false);
            break;
        }
        case DisplayStateType::TwoIntegers:
            renderTwoIntegers(dig1, dig2, dig3, dig4, dig5, dig6);
            break;
        case DisplayStateType::TwoIntegersSeparated:
            renderTwoIntegersSeparated(dig1, dig2, dig3, dig4, dig5, dig6);
            break;
        default:
        {
            renderFrame(vec, 0, 0, false, negativeCheck1);
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
        g_IsStoppedMutex.lock();
        g_IsStopped = true;
        g_IsStoppedMutex.unlock();
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