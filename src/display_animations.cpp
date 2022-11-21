#include "display_animations.hpp"
#include "pins.hpp"
#include <chrono>
#include <thread>
#include <wiringPi.h>

namespace Display::Animations
{

    void welcome()
    {
        digitalWrite(PIN_DIG1, HIGH);
        digitalWrite(PIN_DIG2, HIGH);
        digitalWrite(PIN_DIG3, HIGH);

        digitalWrite(PIN1, LOW);
        digitalWrite(PIN2, LOW);
        digitalWrite(PIN3, LOW);
        digitalWrite(PIN4, LOW);
        digitalWrite(PIN5, LOW);
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, LOW);
        digitalWrite(PIN8, LOW);

        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, LOW);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, LOW);
        digitalWrite(PIN16, LOW);

        digitalWrite(PIN_DIG1, LOW);
        digitalWrite(PIN_DIG2, LOW);
        digitalWrite(PIN_DIG3, LOW);

        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN1, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN2, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN3, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN4, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN5, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN6, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        digitalWrite(PIN9, LOW);
        digitalWrite(PIN1, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN2, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN11, LOW);
        digitalWrite(PIN3, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN4, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN5, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN6, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        digitalWrite(PIN_DIG1, HIGH);
        digitalWrite(PIN_DIG2, HIGH);
        digitalWrite(PIN_DIG3, HIGH);

        for (int i = 0; i < 70; i++)
        {
            digitalWrite(PIN_DIG2, LOW);
            digitalWrite(PIN9, LOW);
            digitalWrite(PIN10, HIGH);
            digitalWrite(PIN11, HIGH);
            digitalWrite(PIN12, LOW);
            digitalWrite(PIN13, LOW);
            digitalWrite(PIN14, LOW);
            digitalWrite(PIN15, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            digitalWrite(PIN_DIG2, HIGH);

            digitalWrite(PIN_DIG1, LOW);
            digitalWrite(PIN9, LOW);
            digitalWrite(PIN10, HIGH);
            digitalWrite(PIN11, HIGH);
            digitalWrite(PIN12, LOW);
            digitalWrite(PIN13, HIGH);
            digitalWrite(PIN14, HIGH);
            digitalWrite(PIN15, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            digitalWrite(PIN_DIG1, HIGH);
        }

        for (int i = 0; i < 10; i++)
        {
            digitalWrite(PIN_DIG3, LOW);
            digitalWrite(PIN9, LOW);
            digitalWrite(PIN10, LOW);
            digitalWrite(PIN11, LOW);
            digitalWrite(PIN12, LOW);
            digitalWrite(PIN13, HIGH);
            digitalWrite(PIN14, HIGH);
            digitalWrite(PIN15, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
            digitalWrite(PIN_DIG3, HIGH);

            digitalWrite(PIN_DIG2, LOW);
            digitalWrite(PIN9, LOW);
            digitalWrite(PIN10, LOW);
            digitalWrite(PIN11, LOW);
            digitalWrite(PIN12, LOW);
            digitalWrite(PIN13, HIGH);
            digitalWrite(PIN14, HIGH);
            digitalWrite(PIN15, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
            digitalWrite(PIN_DIG2, HIGH);

            digitalWrite(PIN_DIG1, LOW);
            digitalWrite(PIN9, LOW);
            digitalWrite(PIN10, HIGH);
            digitalWrite(PIN11, HIGH);
            digitalWrite(PIN12, LOW);
            digitalWrite(PIN13, LOW);
            digitalWrite(PIN14, LOW);
            digitalWrite(PIN15, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
            digitalWrite(PIN_DIG1, HIGH);
        }

        for (int i = 0; i < 10; i++)
        {
            digitalWrite(PIN_DIG3, LOW);
            digitalWrite(PIN9, LOW);
            digitalWrite(PIN10, HIGH);
            digitalWrite(PIN11, HIGH);
            digitalWrite(PIN12, LOW);
            digitalWrite(PIN13, LOW);
            digitalWrite(PIN14, LOW);
            digitalWrite(PIN15, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            digitalWrite(PIN_DIG3, HIGH);

            digitalWrite(PIN_DIG2, LOW);
            digitalWrite(PIN9, LOW);
            digitalWrite(PIN10, HIGH);
            digitalWrite(PIN11, HIGH);
            digitalWrite(PIN12, LOW);
            digitalWrite(PIN13, HIGH);
            digitalWrite(PIN14, HIGH);
            digitalWrite(PIN15, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            digitalWrite(PIN_DIG2, HIGH);
        }

        for (int i = 0; i < 10; i++)
        {
            digitalWrite(PIN_DIG3, LOW);
            digitalWrite(PIN9, LOW);
            digitalWrite(PIN10, LOW);
            digitalWrite(PIN11, LOW);
            digitalWrite(PIN12, LOW);
            digitalWrite(PIN13, HIGH);
            digitalWrite(PIN14, HIGH);
            digitalWrite(PIN15, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            digitalWrite(PIN_DIG3, HIGH);

            digitalWrite(PIN_DIG2, LOW);
            digitalWrite(PIN9, LOW);
            digitalWrite(PIN10, HIGH);
            digitalWrite(PIN11, HIGH);
            digitalWrite(PIN12, LOW);
            digitalWrite(PIN13, LOW);
            digitalWrite(PIN14, LOW);
            digitalWrite(PIN15, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            digitalWrite(PIN_DIG2, HIGH);
        }

        for (int i = 0; i < 10; i++)
        {
            digitalWrite(PIN_DIG3, LOW);
            digitalWrite(PIN9, LOW);
            digitalWrite(PIN10, HIGH);
            digitalWrite(PIN11, HIGH);
            digitalWrite(PIN12, LOW);
            digitalWrite(PIN13, HIGH);
            digitalWrite(PIN14, HIGH);
            digitalWrite(PIN15, HIGH);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            digitalWrite(PIN_DIG3, HIGH);
        }

        for (int i = 0; i < 10; i++)
        {
            digitalWrite(PIN_DIG3, LOW);
            digitalWrite(PIN9, LOW);
            digitalWrite(PIN10, HIGH);
            digitalWrite(PIN11, HIGH);
            digitalWrite(PIN12, LOW);
            digitalWrite(PIN13, LOW);
            digitalWrite(PIN14, LOW);
            digitalWrite(PIN15, LOW);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            digitalWrite(PIN_DIG3, HIGH);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, LOW);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, LOW);
    }

}