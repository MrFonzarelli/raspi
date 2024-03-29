#ifndef DISPLAY_TRIPLE_DIGIT_HPP
#define DISPLAY_TRIPLE_DIGIT_HPP

#include "io.hpp"
#include <thread>

namespace IO::TripleDigit
{

    const int DISPLAY_RENDER_WAIT = 1;

    std::thread *startThread();

    void clearAndStop();

}

#endif