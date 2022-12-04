#ifndef IO_BUTTONS_HPP
#define IO_BUTTONS_HPP

#include <mutex>
#include <thread>

namespace IO::Buttons
{

    std::thread *startScreenScrollLeftButtonThread();
    std::thread *startScreenScrollRightButtonThread();
    std::thread *startChangeUnitsToGayThread();
    std::thread *startResetStatButtonThread();

}

#endif