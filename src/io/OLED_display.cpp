#include "io.hpp"
#include "ssd1306_i2c.h"
#include "OLED_display.hpp"

namespace IO::OLED
{
    void doOLEDWork()
    {
        ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
        ssd1306_clearDisplay();
        int ch = 65;
        unsigned char text = ch;
        ssd1306_drawChar(0, 0, ch, 1, 3);
        ssd1306_display();
        while (true)
        {
            DisplayState displayState = getDisplayState();

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    std::thread *startThread()
    {
        return new std::thread(doOLEDWork);
    }
}