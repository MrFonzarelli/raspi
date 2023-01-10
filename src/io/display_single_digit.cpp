#include "data.hpp"
#include "display_single_digit.hpp"
#include "pins.hpp"
#include <chrono>
#include <wiringPi.h>
#include <mutex>

namespace IO::SingleDigit
{

    std::mutex g_isStoppedMutex;
    bool g_isStopped = false;

    bool isStopped()
    {
        std::lock_guard<std::mutex> lock(g_isStoppedMutex);
        return g_isStopped;
    }

    int reverseHandler(void)
    {
        digitalWrite(PIN_SINGLE_DIGIT_A, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_B, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_C, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_D, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_E, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_F, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_G, HIGH);
        return 0;
    }

    int neutralHandler(void)
    {
        digitalWrite(PIN_SINGLE_DIGIT_A, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_B, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_C, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_D, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_E, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_F, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_G, HIGH);
        return 1;
    }

    int firstHandler(void)
    {
        digitalWrite(PIN_SINGLE_DIGIT_A, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_B, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_C, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_D, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_E, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_F, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_G, LOW);
        return 2;
    }

    int secondHandler(void)
    {
        digitalWrite(PIN_SINGLE_DIGIT_A, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_B, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_C, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_D, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_E, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_F, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_G, HIGH);
        return 3;
    }

    int thirdHandler(void)
    {
        digitalWrite(PIN_SINGLE_DIGIT_A, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_B, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_C, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_D, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_E, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_F, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_G, HIGH);
        return 4;
    }

    int fourthHandler(void)
    {
        digitalWrite(PIN_SINGLE_DIGIT_A, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_B, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_C, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_D, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_E, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_F, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_G, HIGH);
        return 5;
    }

    int fifthHandler(void)
    {
        digitalWrite(PIN_SINGLE_DIGIT_A, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_B, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_C, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_D, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_E, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_F, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_G, HIGH);
        return 6;
    }

    int sixthHandler(void)
    {
        digitalWrite(PIN_SINGLE_DIGIT_A, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_B, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_C, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_D, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_E, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_F, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_G, HIGH);
        return 7;
    }

    int seventhHandler(void)
    {
        digitalWrite(PIN_SINGLE_DIGIT_A, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_B, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_C, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_D, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_E, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_F, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_G, LOW);
        return 8;
    }

    int eighthHandler(void)
    {
        digitalWrite(PIN_SINGLE_DIGIT_A, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_B, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_C, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_D, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_E, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_F, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_G, HIGH);
        return 9;
    }

    int ninethHandler(void)
    {
        digitalWrite(PIN_SINGLE_DIGIT_A, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_B, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_C, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_D, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_E, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_F, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_G, HIGH);
        return 10;
    }

    int zeroHandler(void)
    {
        digitalWrite(PIN_SINGLE_DIGIT_A, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_B, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_C, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_D, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_E, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_F, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_G, LOW);
        return 11;
    }

    void singleDigitOutput(int value)
    {
        switch (value % 10)
        {
        case 0:
        {
            reverseHandler();
            break;
        }
        case 1:
        {
            neutralHandler();
            break;
        }
        case 2:
        {
            firstHandler();
            break;
        }
        case 3:
        {
            secondHandler();
            break;
        }
        case 4:
        {
            thirdHandler();
            break;
        }
        case 5:
        {
            fourthHandler();
            break;
        }
        case 6:
        {
            fifthHandler();
            break;
        }
        case 7:
        {
            sixthHandler();
            break;
        }
        case 8:
        {
            seventhHandler();
            break;
        }
        case 9:
        {
            eighthHandler();
            break;
        }
        case 10:
        {
            ninethHandler();
            break;
        }
        default:
        {
            zeroHandler();
            break;
        }
        }
    }

    void doSingleDigitWork()
    {
        while (!isStopped())
        {
            Data::Tick tick = Data::get();
            singleDigitOutput(tick.outGauge.gear);
            std::this_thread::sleep_for(std::chrono::milliseconds(Data::ACCESS_DELAY_MS));
        }
    }

    std::thread *startThread()
    {
        return new std::thread(doSingleDigitWork);
    }

    void clearAndStop()
    {
        g_isStoppedMutex.lock();
        g_isStopped = true;
        g_isStoppedMutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        digitalWrite(PIN_SINGLE_DIGIT_A, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_B, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_C, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_D, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_E, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_F, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_G, LOW);
    }

}