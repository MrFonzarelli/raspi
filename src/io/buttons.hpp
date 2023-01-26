#ifndef IO_BUTTONS_HPP
#define IO_BUTTONS_HPP

#include <functional>
#include <mutex>
#include <thread>

namespace IO::Buttons
{

    std::thread *startButtonThread(int buttonPin, std::function<void()> callback);

    // Callback actions for buttons
    void buttonResetStatAction();
    void buttonMultiAction();

}

#endif