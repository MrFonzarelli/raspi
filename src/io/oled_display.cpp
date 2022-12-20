#include "io.hpp"
#include "ssd1306_i2c.h"
#include "oled_display.hpp"
#include <mutex>

namespace IO::OLED
{
    std::mutex g_isStoppedMutex;
    bool g_isStopped = false;

    bool isStopped()
    {
        std::lock_guard<std::mutex> lock(g_isStoppedMutex);
        return g_isStopped;
    }

    void doOLEDWork()
    {
        DisplayState displayState_old;
        ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
        ssd1306_clearDisplay();
        ssd1306_display();
        while (!isStopped())
        {
            DisplayState displayState = getDisplayState();
            // if (displayState != displayState_old)
            //{
            switch (displayState)
            {
            case DisplayState::Speed:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(4);
                ssd1306_drawString("Speed");
                ssd1306_display();
                break;
            }
            case DisplayState::TurboPressure:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(4);
                ssd1306_drawString("Turbo");
                ssd1306_display();
                break;
            }
            case DisplayState::TripOdometer:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString("TripOdo");
                ssd1306_display();
                break;
            }
            case DisplayState::Odometer:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString("Odomtr");
                ssd1306_display();
                break;
            }
            case DisplayState::EngineTemp:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString("EngTmp");
                ssd1306_display();
                break;
            }
            case DisplayState::OilTemp:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString("OilTmp");
                ssd1306_display();
                break;
            }
            case DisplayState::CurrentFuelConsumption:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString("IstFuel");
                ssd1306_display();
                break;
            }
            case DisplayState::AverageFuelConsumption:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString("AvgFuel");
                ssd1306_display();
                break;
            }
            case DisplayState::ZeroTo100:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString("0-100");
                ssd1306_display();
                break;
            }
            case DisplayState::ZeroTo200:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString("0-200");
                ssd1306_display();
                break;
            }
            case DisplayState::ZeroTo300:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString("0-300");
                ssd1306_display();
                break;
            }
            case DisplayState::QuarterMile:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(4);
                ssd1306_drawString("1/4mi");
                ssd1306_display();
                break;
            }
            case DisplayState::HundredTo200:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString("100-200");
                ssd1306_display();
                break;
            }
            case DisplayState::HundredTo300:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString("100-300");
                ssd1306_display();
                break;
            }
            case DisplayState::TwoHundredTo300:
            {
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString("200-300");
                ssd1306_display();
                break;
            }
            }
            // displayState_old = displayState;
            //}
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    std::thread *startThread()
    {
        return new std::thread(doOLEDWork);
    }

    void clearAndStop()
    {
        g_isStoppedMutex.lock();
        g_isStopped = true;
        g_isStoppedMutex.unlock();
        ssd1306_clearDisplay();
        ssd1306_display();
    }
}
