#include "display.hpp"
#include "pins.hpp"
#include <chrono>
#include <thread>
#include <wiringPi.h>

namespace Display
{

    void initialize()
    {
        wiringPiSetup();
        pinMode(PIN1, OUTPUT);
        pinMode(PIN2, OUTPUT);
        pinMode(PIN3, OUTPUT);
        pinMode(PIN4, OUTPUT);
        pinMode(PIN5, OUTPUT);
        pinMode(PIN6, OUTPUT);
        pinMode(PIN7, OUTPUT);
        pinMode(PIN8, OUTPUT);
        pinMode(PIN9, OUTPUT);
        pinMode(PIN10, OUTPUT);
        pinMode(PIN11, OUTPUT);
        pinMode(PIN12, OUTPUT);
        pinMode(PIN13, OUTPUT);
        pinMode(PIN14, OUTPUT);
        pinMode(PIN15, OUTPUT);
        pinMode(PIN16, OUTPUT);
        pinMode(PIN_DIG1, OUTPUT);
        pinMode(PIN_DIG2, OUTPUT);
        pinMode(PIN_DIG3, OUTPUT);
        pinMode(PIN_SCROLL_RIGHT_BUTTON, INPUT);
        pinMode(PIN_SCROLL_LEFT_BUTTON, INPUT);
        pinMode(PIN_CHANGE_UNITS_BUTTON, INPUT);
        pinMode(PIN_RESET_STAT, INPUT);

        // digitalWrite(PIN_DIG1, HIGH);
        // digitalWrite(PIN_DIG2, HIGH);
        // digitalWrite(PIN_DIG3, HIGH);

        // digitalWrite(PIN1, LOW);
        // digitalWrite(PIN2, LOW);
        // digitalWrite(PIN3, LOW);
        // digitalWrite(PIN4, LOW);
        // digitalWrite(PIN5, LOW);
        // digitalWrite(PIN6, LOW);
        // digitalWrite(PIN7, LOW);
        // digitalWrite(PIN8, LOW);

        // digitalWrite(PIN9, LOW);
        // digitalWrite(PIN10, LOW);
        // digitalWrite(PIN11, LOW);
        // digitalWrite(PIN12, LOW);
        // digitalWrite(PIN13, LOW);
        // digitalWrite(PIN14, LOW);
        // digitalWrite(PIN15, LOW);
        // digitalWrite(PIN16, LOW);

        // digitalWrite(PIN_DIG1, LOW);
        // digitalWrite(PIN_DIG2, LOW);
        // digitalWrite(PIN_DIG3, LOW);

        // digitalWrite(PIN9, HIGH);
        // digitalWrite(PIN1, HIGH);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // digitalWrite(PIN10, HIGH);
        // digitalWrite(PIN2, HIGH);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // digitalWrite(PIN11, HIGH);
        // digitalWrite(PIN3, HIGH);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // digitalWrite(PIN12, HIGH);
        // digitalWrite(PIN4, HIGH);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // digitalWrite(PIN13, HIGH);
        // digitalWrite(PIN5, HIGH);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // digitalWrite(PIN14, HIGH);
        // digitalWrite(PIN6, HIGH);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // digitalWrite(PIN9, LOW);
        // digitalWrite(PIN1, LOW);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // digitalWrite(PIN10, LOW);
        // digitalWrite(PIN2, LOW);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // digitalWrite(PIN11, LOW);
        // digitalWrite(PIN3, LOW);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // digitalWrite(PIN12, LOW);
        // digitalWrite(PIN4, LOW);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // digitalWrite(PIN13, LOW);
        // digitalWrite(PIN5, LOW);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // digitalWrite(PIN14, LOW);
        // digitalWrite(PIN6, LOW);
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // digitalWrite(PIN_DIG1, HIGH);
        // digitalWrite(PIN_DIG2, HIGH);
        // digitalWrite(PIN_DIG3, HIGH);

        // for (int i = 0; i < 70; i++)
        // {
        //     digitalWrite(PIN_DIG2, LOW);
        //     digitalWrite(PIN9, LOW);
        //     digitalWrite(PIN10, HIGH);
        //     digitalWrite(PIN11, HIGH);
        //     digitalWrite(PIN12, LOW);
        //     digitalWrite(PIN13, LOW);
        //     digitalWrite(PIN14, LOW);
        //     digitalWrite(PIN15, LOW);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(5));
        //     digitalWrite(PIN_DIG2, HIGH);

        //     digitalWrite(PIN_DIG1, LOW);
        //     digitalWrite(PIN9, LOW);
        //     digitalWrite(PIN10, HIGH);
        //     digitalWrite(PIN11, HIGH);
        //     digitalWrite(PIN12, LOW);
        //     digitalWrite(PIN13, HIGH);
        //     digitalWrite(PIN14, HIGH);
        //     digitalWrite(PIN15, HIGH);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(5));
        //     digitalWrite(PIN_DIG1, HIGH);
        // }

        // for (int i = 0; i < 10; i++)
        // {
        //     digitalWrite(PIN_DIG3, LOW);
        //     digitalWrite(PIN9, LOW);
        //     digitalWrite(PIN10, LOW);
        //     digitalWrite(PIN11, LOW);
        //     digitalWrite(PIN12, LOW);
        //     digitalWrite(PIN13, HIGH);
        //     digitalWrite(PIN14, HIGH);
        //     digitalWrite(PIN15, LOW);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(3));
        //     digitalWrite(PIN_DIG3, HIGH);

        //     digitalWrite(PIN_DIG2, LOW);
        //     digitalWrite(PIN9, LOW);
        //     digitalWrite(PIN10, LOW);
        //     digitalWrite(PIN11, LOW);
        //     digitalWrite(PIN12, LOW);
        //     digitalWrite(PIN13, HIGH);
        //     digitalWrite(PIN14, HIGH);
        //     digitalWrite(PIN15, LOW);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(3));
        //     digitalWrite(PIN_DIG2, HIGH);

        //     digitalWrite(PIN_DIG1, LOW);
        //     digitalWrite(PIN9, LOW);
        //     digitalWrite(PIN10, HIGH);
        //     digitalWrite(PIN11, HIGH);
        //     digitalWrite(PIN12, LOW);
        //     digitalWrite(PIN13, LOW);
        //     digitalWrite(PIN14, LOW);
        //     digitalWrite(PIN15, LOW);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(3));
        //     digitalWrite(PIN_DIG1, HIGH);
        // }

        // for (int i = 0; i < 10; i++)
        // {
        //     digitalWrite(PIN_DIG3, LOW);
        //     digitalWrite(PIN9, LOW);
        //     digitalWrite(PIN10, HIGH);
        //     digitalWrite(PIN11, HIGH);
        //     digitalWrite(PIN12, LOW);
        //     digitalWrite(PIN13, LOW);
        //     digitalWrite(PIN14, LOW);
        //     digitalWrite(PIN15, LOW);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(5));
        //     digitalWrite(PIN_DIG3, HIGH);

        //     digitalWrite(PIN_DIG2, LOW);
        //     digitalWrite(PIN9, LOW);
        //     digitalWrite(PIN10, HIGH);
        //     digitalWrite(PIN11, HIGH);
        //     digitalWrite(PIN12, LOW);
        //     digitalWrite(PIN13, HIGH);
        //     digitalWrite(PIN14, HIGH);
        //     digitalWrite(PIN15, HIGH);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(5));
        //     digitalWrite(PIN_DIG2, HIGH);
        // }

        // for (int i = 0; i < 10; i++)
        // {
        //     digitalWrite(PIN_DIG3, LOW);
        //     digitalWrite(PIN9, LOW);
        //     digitalWrite(PIN10, LOW);
        //     digitalWrite(PIN11, LOW);
        //     digitalWrite(PIN12, LOW);
        //     digitalWrite(PIN13, HIGH);
        //     digitalWrite(PIN14, HIGH);
        //     digitalWrite(PIN15, LOW);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(5));
        //     digitalWrite(PIN_DIG3, HIGH);

        //     digitalWrite(PIN_DIG2, LOW);
        //     digitalWrite(PIN9, LOW);
        //     digitalWrite(PIN10, HIGH);
        //     digitalWrite(PIN11, HIGH);
        //     digitalWrite(PIN12, LOW);
        //     digitalWrite(PIN13, LOW);
        //     digitalWrite(PIN14, LOW);
        //     digitalWrite(PIN15, LOW);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(5));
        //     digitalWrite(PIN_DIG2, HIGH);
        // }

        // for (int i = 0; i < 10; i++)
        // {
        //     digitalWrite(PIN_DIG3, LOW);
        //     digitalWrite(PIN9, LOW);
        //     digitalWrite(PIN10, HIGH);
        //     digitalWrite(PIN11, HIGH);
        //     digitalWrite(PIN12, LOW);
        //     digitalWrite(PIN13, HIGH);
        //     digitalWrite(PIN14, HIGH);
        //     digitalWrite(PIN15, HIGH);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //     digitalWrite(PIN_DIG3, HIGH);
        // }

        // for (int i = 0; i < 10; i++)
        // {
        //     digitalWrite(PIN_DIG3, LOW);
        //     digitalWrite(PIN9, LOW);
        //     digitalWrite(PIN10, HIGH);
        //     digitalWrite(PIN11, HIGH);
        //     digitalWrite(PIN12, LOW);
        //     digitalWrite(PIN13, LOW);
        //     digitalWrite(PIN14, LOW);
        //     digitalWrite(PIN15, LOW);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //     digitalWrite(PIN_DIG3, HIGH);
        // }
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // digitalWrite(PIN9, LOW);
        // digitalWrite(PIN10, LOW);
        // digitalWrite(PIN11, LOW);
        // digitalWrite(PIN12, LOW);
        // digitalWrite(PIN13, LOW);
        // digitalWrite(PIN14, LOW);
        // digitalWrite(PIN15, LOW);
    }

}