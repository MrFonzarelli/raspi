#ifndef DISPLAY_TRIPLE_DIGIT_HPP
#define DISPLAY_TRIPLE_DIGIT_HPP

#include <thread>

#define WAIT 3

namespace Display::TripleDigit
{
    const int DISPLAY_RENDER_WAIT = 3;

    int firstHandlerTri(void);
    int secondHandlerTri(void);
    int thirdHandlerTri(void);
    int fourthHandlerTri(void);
    int fifthHandlerTri(void);
    int sixthHandlerTri(void);
    int seventhHandlerTri(void);
    int eighthHandlerTri(void);
    int ninethHandlerTri(void);
    int zeroHandlerTri(void);
    int minusHandlerTri(void);
    std::thread *startThread();
}

#endif