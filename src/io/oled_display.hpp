#ifndef OLED_DISPLAY_HPP
#define OLED_DISPLAY_HPP

#include <thread>
#include <string>

namespace IO::OLED
{

    std::thread *startThread();

    void clearAndStop();

    void scrollOLEDRight();

    void scrollOLEDLeft();

    void staticMessageOLED(const std::string &message, int textSize, int displayTimeMs);

}

#endif
