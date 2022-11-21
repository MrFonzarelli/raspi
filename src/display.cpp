#include "display.hpp"
#include "display_animations.hpp"
#include "display_single_digit.hpp"
#include "pins.hpp"
#include <chrono>
#include <memory>
#include <thread>
#include <wiringPi.h>

namespace Display
{
    std::unique_ptr<std::thread> g_SingleDigitThread;

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

        Animations::welcome();

        g_SingleDigitThread = SingleDigit::startThread();
    }

}