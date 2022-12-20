#include "io.hpp"
#include "ssd1306_i2c.h"
#include "oled_display.hpp"

namespace IO::OLED
{
    void doOLEDWork()
    {
        DisplayState displayState_old;
        ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
        ssd1306_clearDisplay();
        ssd1306_display();
        while (true)
        {
            DisplayState displayState = getDisplayState();
            // if (displayState != displayState_old)
            //{
            switch (displayState)
            {
            case DisplayState::Speed:
            {
                text = "Speed";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(4);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::TurboPressure:
            {
                text = "Turbo";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(4);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::TripOdometer:
            {
                text = "TripOdo";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::Odometer:
            {
                text = "Odomtr";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::EngineTemp:
            {
                text = "EngTmp";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::OilTemp:
            {
                text = "OilTmp";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::CurrentFuelConsumption:
            {
                text = "IstFuel";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::AverageFuelConsumption:
            {
                text = "AvgFuel";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::ZeroTo100:
            {
                text = "0-100";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::ZeroTo200:
            {
                text = "0-200";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::ZeroTo300:
            {
                text = "0-300";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::QuarterMile:
            {
                text = "1/4mi";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(4);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::HundredTo200:
            {
                text = "100-200";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::HundredTo300:
            {
                text = "100-300";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString(text);
                ssd1306_display();
                break;
            }
            case DisplayState::TwoHundredTo300:
            {
                text = "200-300";
                ssd1306_clearDisplay();
                ssd1306_setTextSize(3);
                ssd1306_drawString(text);
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
}
