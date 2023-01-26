#include "io.hpp"
#include "ssd1306_i2c.h"
#include "oled_display.hpp"
#include <mutex>
#include <cmath>
#include <chrono>

namespace IO::OLED
{

    std::mutex g_IsStoppedMutex;
    std::mutex g_OLEDAccessMutex;
    std::string g_Message;
    int g_TextSize;
    int g_GenericInterruptValue;
    int g_InterruptType;
    bool g_InterruptDone = true;
    bool g_IsStopped = false;
    bool g_IsInterrupted = false;

    bool isStopped()
    {
        std::lock_guard<std::mutex> lock(g_IsStoppedMutex);
        return g_IsStopped;
    }

    bool isInterrupted()
    {
        std::lock_guard<std::mutex> lock(g_OLEDAccessMutex);
        return g_IsInterrupted;
    }

    void interrupt()
    {
        g_OLEDAccessMutex.lock();
        g_IsInterrupted = true;
        g_OLEDAccessMutex.unlock();
    }

    void resume()
    {
        g_OLEDAccessMutex.lock();
        g_IsInterrupted = false;
        g_OLEDAccessMutex.unlock();
    }

    void drawProgressBar(DisplayState displayState)
    {
        int displayStateCount = IO::getDisplayStateCount();
        int currentDisplayState = IO::getCurrentDisplayStateIndex();
        double offset_x = WIDTH / displayStateCount;
        int offset_middle = round((WIDTH - round(offset_x * displayStateCount)) / 2);
        ssd1306_drawFastVLine(offset_middle, 28, 4, WHITE);
        ssd1306_drawFastVLine(round(offset_x * displayStateCount) + offset_middle - 1, 28, 4, WHITE);
        ssd1306_drawFastHLine(offset_middle, 28, round(offset_x * displayStateCount), WHITE);
        ssd1306_drawFastHLine(round(offset_x * currentDisplayState) + offset_middle, 29, round(offset_x), WHITE);
        ssd1306_drawFastHLine(round(offset_x * currentDisplayState) + offset_middle, 30, round(offset_x), WHITE);
        ssd1306_drawFastHLine(offset_middle, 31, round(offset_x * displayStateCount), WHITE);
    }

    void staticMessageOLED(const std::string &message, int textSize, int displayTimeMs)
    {
        if (!isStopped())
        {
            if (g_InterruptDone)
            {
                interrupt();
                g_Message = message;
                g_TextSize = textSize;
                g_GenericInterruptValue = displayTimeMs;
                g_InterruptType = 0;
                g_InterruptDone = false;
                resume();
            }
        }
    }

    void writeDisplayState(DisplayState displayState)
    {
        switch (displayState)
        {
        case DisplayState::Speed:
        {
            ssd1306_setTextSize(3);
            ssd1306_drawString("Speed");
            break;
        }
        case DisplayState::TurboPressure:
        {
            ssd1306_setTextSize(3);
            ssd1306_drawString("Boost");
            break;
        }
        case DisplayState::TripOdometer:
        {
            ssd1306_setTextSize(3);
            ssd1306_drawString("TripOdo");
            break;
        }
        case DisplayState::Odometer:
        {
            ssd1306_setTextSize(3);
            ssd1306_drawString("Odomtr");
            break;
        }
        case DisplayState::EngineTemp:
        {
            ssd1306_setTextSize(3);
            ssd1306_drawString("EngTmp");
            break;
        }
        case DisplayState::OilTemp:
        {
            ssd1306_setTextSize(3);
            ssd1306_drawString("OilTmp");
            break;
        }
        case DisplayState::CurrentFuelConsumption:
        {
            ssd1306_setTextSize(3);
            ssd1306_drawString("InsFuel");
            break;
        }
        case DisplayState::AverageFuelConsumption:
        {
            ssd1306_setTextSize(3);
            ssd1306_drawString("AvgFuel");
            break;
        }
        case DisplayState::ZeroTo100:
        {
            ssd1306_setTextSize(2);
            ssd1306_drawString("0-100kmh");
            break;
        }
        case DisplayState::ZeroTo200:
        {
            ssd1306_setTextSize(2);
            ssd1306_drawString("0-200kmh");
            break;
        }
        case DisplayState::ZeroTo300:
        {
            ssd1306_setTextSize(2);
            ssd1306_drawString("0-300kmh");
            break;
        }
        case DisplayState::QuarterMile:
        {
            ssd1306_setTextSize(3);
            ssd1306_drawString("1/4mi");
            break;
        }
        case DisplayState::HundredTo200:
        {
            ssd1306_setTextSize(2);
            ssd1306_drawString("100-200km");
            break;
        }
        case DisplayState::HundredTo300:
        {
            ssd1306_setTextSize(2);
            ssd1306_drawString("100-300km");
            break;
        }
        case DisplayState::TwoHundredTo300:
        {
            ssd1306_setTextSize(2);
            ssd1306_drawString("200-300kmh");
            break;
        }
        case DisplayState::CustomTimer:
        {
            ssd1306_setTextSize(3);
            ssd1306_drawString("ManTmr");
            break;
        }
        case DisplayState::RPM:
        {
            ssd1306_setTextSize(3);
            ssd1306_drawString("RPM");
            break;
        }
        case DisplayState::RPMandSpeed:
        {
            ssd1306_setTextSize(2);
            ssd1306_drawString("RPMx10 Spd");
            break;
        }
        case DisplayState::RPMandSpeedSep:
        {
            ssd1306_setTextSize(2);
            ssd1306_drawString("RPMx1k Spd");
            break;
        }
        default:
        {
            ssd1306_clearDisplay();
            ssd1306_setTextSize(3);
            ssd1306_drawString("Error");
            ssd1306_drawFastHLine(0, 28, WIDTH, WHITE);
            ssd1306_drawFastHLine(0, 29, WIDTH, WHITE);
            ssd1306_drawFastHLine(0, 30, WIDTH, WHITE);
            ssd1306_drawFastHLine(0, 31, WIDTH, WHITE);
            break;
        }
        }
    }

    void doDisplayOLEDWork()
    {
        DisplayState displayState = getDisplayState();
        ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
        ssd1306_clearDisplay();
        ssd1306_display();
        while (!isStopped())
        {
            displayState = getDisplayState();
            if (!isInterrupted())
            {
                if (g_InterruptDone)
                {
                    ssd1306_clearDisplay();
                    drawProgressBar(displayState);
                    writeDisplayState(displayState);
                    ssd1306_display();
                }
                else
                {
                    switch (g_InterruptType)
                    {
                    case 0:
                    {
                        ssd1306_clearDisplay();
                        ssd1306_setTextSize(g_TextSize);
                        ssd1306_drawString(g_Message.c_str());
                        ssd1306_display();
                        std::this_thread::sleep_for(std::chrono::milliseconds(g_GenericInterruptValue));
                        break;
                    }
                    }
                    g_InterruptDone = true;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    std::thread *startThread()
    {
        return new std::thread(doDisplayOLEDWork);
    }

    void clearAndStop()
    {
        g_IsStoppedMutex.lock();
        g_IsStopped = true;
        g_IsStoppedMutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        ssd1306_clearDisplay();
        ssd1306_display();
    }

    void scrollOLEDLeft()
    {
        interrupt();
        ssd1306_clearDisplay();
        ssd1306_display();
        resume();
    }

    void scrollOLEDRight()
    {
        interrupt();
        ssd1306_clearDisplay();
        ssd1306_display();
        resume();
    }

}
