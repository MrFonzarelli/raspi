#ifndef TIMERS_HPP
#define TIMERS_HPP

#include "io.hpp"
#include <thread>

namespace IO::Timers
{

    std::thread *startThread();

    void reset();

    double getTime(DisplayState displayState);

}

#endif