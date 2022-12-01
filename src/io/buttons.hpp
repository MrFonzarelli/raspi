#ifndef IO_BUTTONS_HPP
#define IO_BUTTONS_HPP

#include "io.hpp"
#include <mutex>

namespace IO::Buttons
{

    std::thread *startScreenScrollLeftButtonThread();
    std::thread *startScreenScrollRightButtonThread(DisplayState &displayStateRef, std::mutex &displayStateMutex);
    std::thread *startChangeUnitsToGayThread();
    std::thread *startResetStatButtonThread();

}

#endif