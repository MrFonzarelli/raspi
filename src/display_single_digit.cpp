#include "display_single_digit.hpp"
#include "pins.hpp"
#include <wiringPi.h>

namespace Display::SingleDigit
{

    int reverseHandler(void)
    {
        digitalWrite(PIN1, LOW);
        digitalWrite(PIN2, LOW);
        digitalWrite(PIN3, LOW);
        digitalWrite(PIN4, LOW);
        digitalWrite(PIN5, HIGH);
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, HIGH);
        return 0;
    }

    int neutralHandler(void)
    {
        digitalWrite(PIN1, LOW);
        digitalWrite(PIN2, LOW);
        digitalWrite(PIN3, HIGH);
        digitalWrite(PIN4, LOW);
        digitalWrite(PIN5, HIGH);
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, HIGH);
        return 1;
    }

    int firstHandler(void)
    {
        digitalWrite(PIN1, LOW);
        digitalWrite(PIN2, HIGH);
        digitalWrite(PIN3, HIGH);
        digitalWrite(PIN4, LOW);
        digitalWrite(PIN5, LOW);
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, LOW);
        return 2;
    }

    int secondHandler(void)
    {
        digitalWrite(PIN1, HIGH);
        digitalWrite(PIN2, HIGH);
        digitalWrite(PIN3, LOW);
        digitalWrite(PIN4, HIGH);
        digitalWrite(PIN5, HIGH);
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, HIGH);
        return 3;
    }

    int thirdHandler(void)
    {
        digitalWrite(PIN1, HIGH);
        digitalWrite(PIN2, HIGH);
        digitalWrite(PIN3, HIGH);
        digitalWrite(PIN4, HIGH);
        digitalWrite(PIN5, LOW);
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, HIGH);
        return 4;
    }

    int fourthHandler(void)
    {
        digitalWrite(PIN1, LOW);
        digitalWrite(PIN2, HIGH);
        digitalWrite(PIN3, HIGH);
        digitalWrite(PIN4, LOW);
        digitalWrite(PIN5, LOW);
        digitalWrite(PIN6, HIGH);
        digitalWrite(PIN7, HIGH);
        return 5;
    }

    int fifthHandler(void)
    {
        digitalWrite(PIN1, HIGH);
        digitalWrite(PIN2, LOW);
        digitalWrite(PIN3, HIGH);
        digitalWrite(PIN4, HIGH);
        digitalWrite(PIN5, LOW);
        digitalWrite(PIN6, HIGH);
        digitalWrite(PIN7, HIGH);
        return 6;
    }

    int sixthHandler(void)
    {
        digitalWrite(PIN1, HIGH);
        digitalWrite(PIN2, LOW);
        digitalWrite(PIN3, HIGH);
        digitalWrite(PIN4, HIGH);
        digitalWrite(PIN5, HIGH);
        digitalWrite(PIN6, HIGH);
        digitalWrite(PIN7, HIGH);
        return 7;
    }

    int seventhHandler(void)
    {
        digitalWrite(PIN1, HIGH);
        digitalWrite(PIN2, HIGH);
        digitalWrite(PIN3, HIGH);
        digitalWrite(PIN4, LOW);
        digitalWrite(PIN5, LOW);
        digitalWrite(PIN6, LOW);
        digitalWrite(PIN7, LOW);
        return 8;
    }

    int eighthHandler(void)
    {
        digitalWrite(PIN1, HIGH);
        digitalWrite(PIN2, HIGH);
        digitalWrite(PIN3, HIGH);
        digitalWrite(PIN4, HIGH);
        digitalWrite(PIN5, HIGH);
        digitalWrite(PIN6, HIGH);
        digitalWrite(PIN7, HIGH);
        return 9;
    }

    int ninethHandler(void)
    {
        digitalWrite(PIN1, HIGH);
        digitalWrite(PIN2, HIGH);
        digitalWrite(PIN3, HIGH);
        digitalWrite(PIN4, HIGH);
        digitalWrite(PIN5, LOW);
        digitalWrite(PIN6, HIGH);
        digitalWrite(PIN7, HIGH);
        return 10;
    }

    int zeroHandler(void)
    {
        digitalWrite(PIN1, HIGH);
        digitalWrite(PIN2, HIGH);
        digitalWrite(PIN3, HIGH);
        digitalWrite(PIN4, HIGH);
        digitalWrite(PIN5, HIGH);
        digitalWrite(PIN6, HIGH);
        digitalWrite(PIN7, LOW);
        return 11;
    }

}