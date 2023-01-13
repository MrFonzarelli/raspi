#ifndef TIMERS_HPP
#define TIMERS_HPP

#include "io.hpp"
#include <thread>

namespace IO::Timers
{

    std::thread *startThread();

    void reset();

    void startTimerCustom();
    void stopTimerCustom();
    void resetTimerCustom();
    bool timerCustomIsRunning();

    double getTime(DisplayState displayState);

}

#endif