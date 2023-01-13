#ifndef DISPLAY_SINGLE_DIGIT_HPP
#define DISPLAY_SINGLE_DIGIT_HPP

#include <thread>

namespace IO::SingleDigit
{

    std::thread *startThread();

    void clearAndStop();

}

#endif