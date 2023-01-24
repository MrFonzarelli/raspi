#ifndef TIMERS_HPP
#define TIMERS_HPP

#include "io.hpp"
#include <thread>
#include <mutex>

namespace IO::Timers
{

    std::thread *startThread();

    void reset();

    void startTimerCustom();
    void stopTimerCustom();
    void resetTimerCustom();
    void splitTimerCustom();
    void unsplitTimerCustom();
    bool timerCustomIsRunning();

    double getTime(DisplayState displayState);

}

#endif