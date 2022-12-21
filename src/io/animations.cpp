#include "animations.hpp"
#include "pins.hpp"
#include <chrono>
#include <thread>
#include <wiringPi.h>

namespace IO::Animations
{

    void welcome()
    {
        digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);

        digitalWrite(PIN_SINGLE_DIGIT_A, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_B, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_C, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_D, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_E, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_F, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_G, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_DP, LOW);

        digitalWrite(PIN_TRIPLE_DIG_A, LOW);
        digitalWrite(PIN_TRIPLE_DIG_B, LOW);
        digitalWrite(PIN_TRIPLE_DIG_C, LOW);
        digitalWrite(PIN_TRIPLE_DIG_D, LOW);
        digitalWrite(PIN_TRIPLE_DIG_E, LOW);
        digitalWrite(PIN_TRIPLE_DIG_F, LOW);
        digitalWrite(PIN_TRIPLE_DIG_G, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DP, LOW);

        digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
        digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);

        digitalWrite(PIN_TRIPLE_DIG_A, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_A, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_B, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_C, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN_TRIPLE_DIG_D, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_D, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN_TRIPLE_DIG_E, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_E, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
        digitalWrite(PIN_SINGLE_DIGIT_F, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        digitalWrite(PIN_TRIPLE_DIG_A, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_A, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN_TRIPLE_DIG_B, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_B, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN_TRIPLE_DIG_C, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_C, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN_TRIPLE_DIG_D, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_D, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN_TRIPLE_DIG_E, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_E, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN_TRIPLE_DIG_F, LOW);
        digitalWrite(PIN_SINGLE_DIGIT_F, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
        digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);

        for (int i = 0; i < 70; i++)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_A, LOW);
            digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_D, LOW);
            digitalWrite(PIN_TRIPLE_DIG_E, LOW);
            digitalWrite(PIN_TRIPLE_DIG_F, LOW);
            digitalWrite(PIN_TRIPLE_DIG_G, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);

            digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_A, LOW);
            digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_D, LOW);
            digitalWrite(PIN_TRIPLE_DIG_E, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_G, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
        }

        for (int i = 0; i < 10; i++)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_A, LOW);
            digitalWrite(PIN_TRIPLE_DIG_B, LOW);
            digitalWrite(PIN_TRIPLE_DIG_C, LOW);
            digitalWrite(PIN_TRIPLE_DIG_D, LOW);
            digitalWrite(PIN_TRIPLE_DIG_E, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_G, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);

            digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_A, LOW);
            digitalWrite(PIN_TRIPLE_DIG_B, LOW);
            digitalWrite(PIN_TRIPLE_DIG_C, LOW);
            digitalWrite(PIN_TRIPLE_DIG_D, LOW);
            digitalWrite(PIN_TRIPLE_DIG_E, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_G, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
            digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);

            digitalWrite(PIN_TRIPLE_DIG_DIG1, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_A, LOW);
            digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_D, LOW);
            digitalWrite(PIN_TRIPLE_DIG_E, LOW);
            digitalWrite(PIN_TRIPLE_DIG_F, LOW);
            digitalWrite(PIN_TRIPLE_DIG_G, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
            digitalWrite(PIN_TRIPLE_DIG_DIG1, LOW);
        }

        for (int i = 0; i < 10; i++)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_A, LOW);
            digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_D, LOW);
            digitalWrite(PIN_TRIPLE_DIG_E, LOW);
            digitalWrite(PIN_TRIPLE_DIG_F, LOW);
            digitalWrite(PIN_TRIPLE_DIG_G, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);

            digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_A, LOW);
            digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_D, LOW);
            digitalWrite(PIN_TRIPLE_DIG_E, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_G, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
        }

        for (int i = 0; i < 10; i++)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_A, LOW);
            digitalWrite(PIN_TRIPLE_DIG_B, LOW);
            digitalWrite(PIN_TRIPLE_DIG_C, LOW);
            digitalWrite(PIN_TRIPLE_DIG_D, LOW);
            digitalWrite(PIN_TRIPLE_DIG_E, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_G, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);

            digitalWrite(PIN_TRIPLE_DIG_DIG2, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_A, LOW);
            digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_D, LOW);
            digitalWrite(PIN_TRIPLE_DIG_E, LOW);
            digitalWrite(PIN_TRIPLE_DIG_F, LOW);
            digitalWrite(PIN_TRIPLE_DIG_G, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            digitalWrite(PIN_TRIPLE_DIG_DIG2, LOW);
        }

        for (int i = 0; i < 10; i++)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_A, LOW);
            digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_D, LOW);
            digitalWrite(PIN_TRIPLE_DIG_E, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_F, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_G, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
        }

        for (int i = 0; i < 10; i++)
        {
            digitalWrite(PIN_TRIPLE_DIG_DIG3, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_A, LOW);
            digitalWrite(PIN_TRIPLE_DIG_B, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_C, HIGH);
            digitalWrite(PIN_TRIPLE_DIG_D, LOW);
            digitalWrite(PIN_TRIPLE_DIG_E, LOW);
            digitalWrite(PIN_TRIPLE_DIG_F, LOW);
            digitalWrite(PIN_TRIPLE_DIG_G, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            digitalWrite(PIN_TRIPLE_DIG_DIG3, LOW);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        digitalWrite(PIN_TRIPLE_DIG_A, LOW);
        digitalWrite(PIN_TRIPLE_DIG_B, LOW);
        digitalWrite(PIN_TRIPLE_DIG_C, LOW);
        digitalWrite(PIN_TRIPLE_DIG_D, LOW);
        digitalWrite(PIN_TRIPLE_DIG_E, LOW);
        digitalWrite(PIN_TRIPLE_DIG_F, LOW);
        digitalWrite(PIN_TRIPLE_DIG_G, LOW);
    }

}