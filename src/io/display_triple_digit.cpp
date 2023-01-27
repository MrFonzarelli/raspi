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

    int firstHandlerTri()
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

    int secondHandlerTri()
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

    int thirdHandlerTri()
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

    int fourthHandlerTri()
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

    int fifthHandlerTri()
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

    int sixthHandlerTri()
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

    int seventhHandlerTri()
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

    int eighthHandlerTri()
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

    int ninethHandlerTri()
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

    int zeroHandlerTri()
    {
        digitalWrite(PIN_TRIPLE_DIG_A, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_D, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_E, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_G, LOW);
        return 0;
    }

    int minusHandlerTri()
    {
        digitalWrite(PIN_TRIPLE_DIG_A, LOW);
        digitalWrite(PIN_TRIPLE_DIG_B, LOW);
        digitalWrite(PIN_TRIPLE_DIG_C, LOW);
        digitalWrite(PIN_TRIPLE_DIG_D, LOW);
        digitalWrite(PIN_TRIPLE_DIG_E, LOW);
        digitalWrite(PIN_TRIPLE_DIG_F, LOW);
        digitalWrite(PIN_TRIPLE_DIG_G, HIGH);
        return -1;
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

    void setDigit(int hwDigit, int digit, bool decimalPoint)
    {
        if (decimalPoint)
            digitalWrite(PIN_TRIPLE_DIG_DP, HIGH);
        switch (hwDigit)
        {
        case 1:
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
            digitSelect(digit);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
            break;
        }
        case 2:
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
            digitSelect(digit);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
            break;
        }
        case 3:
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitSelect(digit);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
            break;
        }
        case 4:
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG4, HIGH);
            digitSelect(digit);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG4, LOW);
            break;
        }
        case 5:
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG5, HIGH);
            digitSelect(digit);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG5, LOW);
            break;
        }
        case 6:
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG6, HIGH);
            digitSelect(digit);
            std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_RENDER_WAIT));
            digitalWrite(PIN_TRIPLE_DIG_DIG6, LOW);
            break;
        }
        }
        if (decimalPoint)
            digitalWrite(PIN_TRIPLE_DIG_DP, LOW);
    }

    void renderFrame(std::vector<int> digitsToDisplay, int decimalSpaces, int decimalPoints, bool hideDecimalPoints, bool isNegative)
    {
        std::vector<bool> decimalPointsToDisplay;
        for (int i = 0; i < digitsToDisplay.size() - 1; i++)
        {
            if (digitsToDisplay[i] == 0)
            {
                digitsToDisplay.erase(digitsToDisplay.begin());
                i--;
            }
            else
            {
                break; // break when we hit a non-zero
            }
        }

        if (decimalPoints > 0) // This block only runs when we're supposed to display a decimal point
        {
            if (hideDecimalPoints)
            {
                if (decimalSpaces + 1 > digitsToDisplay.size())
                {
                    int diff = (decimalSpaces + 1) - digitsToDisplay.size();
                    digitsToDisplay.insert(digitsToDisplay.begin(), diff, 0);
                }
            }
            else
            {
                if (decimalPoints * decimalSpaces + 1 > digitsToDisplay.size())
                {
                    int diff = (decimalPoints * decimalSpaces + 1) - digitsToDisplay.size();
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
        else
        {
            decimalPointsToDisplay.insert(decimalPointsToDisplay.begin(), digitsToDisplay.size(), false);
        }

        if (isNegative)
        {
            decimalPointsToDisplay.insert(decimalPointsToDisplay.begin(), 1, false);
            digitsToDisplay.insert(digitsToDisplay.begin(), 1, -1);
        }

        int count = 0;
        int iterations = (digitsToDisplay.size() > 6) ? 6 : digitsToDisplay.size(); // This shit does the displaying
        for (int i = iterations; i > 0; i--)
        {
            setDigit(6 - count, digitsToDisplay[i - 1], decimalPointsToDisplay[i - 1]);
            count++;
        }
    }

    void renderFrame(std::vector<int> digitsToDisplay, std::vector<int> digitsToDisplay2, bool decimalPoint, bool decimalPoint2, bool isNegative, bool isNegative2)
    {
        for (int i = 0; i < digitsToDisplay.size() - 1; i++)
        {
            if (digitsToDisplay[i] == 0)
            {
                digitsToDisplay.erase(digitsToDisplay.begin());
                i--;
            }
            else
            {
                break; // break when we hit a non-zero
            }
        }

        if (decimalPoint)
        {
            if (digitsToDisplay.size() < 2)
            {
                digitsToDisplay.insert(digitsToDisplay.begin(), 1, 0);
            }
        }

        for (int i = 0; i < digitsToDisplay2.size() - 1; i++)
        {
            if (digitsToDisplay2[i] == 0)
            {
                digitsToDisplay2.erase(digitsToDisplay2.begin());
                i--;
            }
            else
            {
                break;
            }
        }

        if (decimalPoint2)
        {
            if (digitsToDisplay2.size() < 2)
            {
                digitsToDisplay2.insert(digitsToDisplay2.begin(), 1, 0);
            }
        }

        if (isNegative)
        {
            if (digitsToDisplay.size() == 3)
            {
                digitsToDisplay.erase(digitsToDisplay.begin());
                digitsToDisplay.insert(digitsToDisplay.begin(), 1, -1);
            }
            else
            {
                digitsToDisplay.insert(digitsToDisplay.begin(), 1, -1);
            }
        }

        if (isNegative2)
        {
            if (digitsToDisplay2.size() == 3)
            {
                digitsToDisplay2.erase(digitsToDisplay2.begin());
                digitsToDisplay2.insert(digitsToDisplay2.begin(), 1, -1);
            }
            else
            {
                digitsToDisplay2.insert(digitsToDisplay2.begin(), 1, -1);
            }
        }

        int count = 1;
        if (decimalPoint)
        {
            for (int i = digitsToDisplay.size(); i > 0; i--)
            {
                setDigit(7 - count, digitsToDisplay[i - 1], count % 2 == 0);
                count++;
            }
        }
        else
        {
            for (int i = digitsToDisplay.size(); i > 0; i--)
            {
                setDigit(7 - count, digitsToDisplay[i - 1], false);
                count++;
            }
        }

        count = 1;
        int offset = (digitsToDisplay2.size() >= 3) ? 1 : 0;
        if (decimalPoint2)
        {
            for (int i = digitsToDisplay2.size(); i > 0; i--)
            {
                setDigit((3 + offset) - count, digitsToDisplay2[i - 1], count == 2);
                count++;
            }
        }
        else
        {
            for (int i = digitsToDisplay2.size(); i > 0; i--)
            {
                setDigit((3 + offset) - count, digitsToDisplay2[i - 1], false);
                count++;
            }
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

    bool isDecimalState(DisplayState displayState)
    {
        switch (displayState)
        {
        case DisplayState::TurboPressure:
        case DisplayState::TripOdometer:
        case DisplayState::Odometer:
        case DisplayState::CurrentFuelConsumption:
        case DisplayState::AverageFuelConsumption:
        case DisplayState::RPM:
            return true;
        }
        return false;
    }

    void tripleDigitOutput()
    {
        int dig1;
        int dig2;
        int dig3;
        int dig4;
        int dig5;
        int dig6;
        bool negativeCheck1 = false;
        bool negativeCheck2 = false;
        std::vector<int> vec1;
        std::vector<int> vec2;
        Data::Tick tick = Data::get();

        CombinedDisplayType displayStateCombined;

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
            vec1 = {dig1, dig2, dig3, dig4, dig5, dig6};
            break;
        }
        case DisplayStateType::Combined:
        {
            displayStateCombined = getCombinedDisplayState();
            int numberToDisplay = getValueToDisplay(tick, displayStateCombined.displayStateRight);
            int numberToDisplay2 = getValueToDisplay(tick, displayStateCombined.displayStateLeft);
            switch (displayStateCombined.displayStateLeft)
            {
            case DisplayState::RPM:
            {
                numberToDisplay2 /= 100;
                break;
            }
            }
            negativeCheck1 = numberToDisplay < 0;
            negativeCheck2 = numberToDisplay2 < 0;
            dig1 = abs(numberToDisplay2) / 100 % 10;
            dig2 = abs(numberToDisplay2) / 10 % 10;
            dig3 = abs(numberToDisplay2) % 10;
            dig4 = abs(numberToDisplay) / 100 % 10;
            dig5 = abs(numberToDisplay) / 10 % 10;
            dig6 = abs(numberToDisplay) % 10;
            vec1 = {dig4, dig5, dig6};
            vec2 = {dig1, dig2, dig3};
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
            vec1 = {dig1, dig2, dig3, dig4, dig5, dig6};
            break;
        }
        }

        switch (displayTypeOf(displayState)) // Render frame on the display
        {
        case DisplayStateType::Decimal:
        {
            renderFrame(vec1, 1, 1, false, negativeCheck1);
            break;
        }
        case DisplayStateType::Time:
        {
            renderFrame(vec1, 2, 2, true, false);
            break;
        }
        case DisplayStateType::Combined:
        {
            renderFrame(vec1, vec2, isDecimalState(displayStateCombined.displayStateRight), isDecimalState(displayStateCombined.displayStateLeft), negativeCheck1, negativeCheck2);
            break;
        }
        default:
        {
            renderFrame(vec1, 0, 0, false, negativeCheck1);
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