#include "display_triple_digit.hpp"
#include "pins.hpp"
#include <wiringPi.h>

namespace Display::TripleDigit
{

    int firstHandlerTri(void)
    {
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, LOW);
        return 1;
    }

    int secondHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, LOW);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, HIGH);
        return 2;
    }

    int thirdHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, HIGH);
        return 3;
    }

    int fourthHandlerTri(void)
    {
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        return 4;
    }

    int fifthHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        return 5;
    }

    int sixthHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        return 6;
    }

    int seventhHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, LOW);
        return 7;
    }

    int eighthHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        return 8;
    }

    int ninethHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, HIGH);
        return 9;
    }

    int zeroHandlerTri(void)
    {
        digitalWrite(PIN9, HIGH);
        digitalWrite(PIN10, HIGH);
        digitalWrite(PIN11, HIGH);
        digitalWrite(PIN12, HIGH);
        digitalWrite(PIN13, HIGH);
        digitalWrite(PIN14, HIGH);
        digitalWrite(PIN15, LOW);
        return 0;
    }

    int minusHandlerTri(void)
    {
        digitalWrite(PIN9, LOW);
        digitalWrite(PIN10, LOW);
        digitalWrite(PIN11, LOW);
        digitalWrite(PIN12, LOW);
        digitalWrite(PIN13, LOW);
        digitalWrite(PIN14, LOW);
        digitalWrite(PIN15, HIGH);
        return 0;
    }

}