// includes
#include "data.hpp"
#include "io/io.hpp"
#include "io/oled_display.hpp"
#include "network.hpp"
#include "outgauge.hpp"
#include "settings.hpp"
#include "ssd1306_i2c.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include <signal.h>

#define ODOMETER_FILENAME "delete-to-reset-odometer"

void readOdometer()
{
    auto filename = Settings::getGeneralSettings().odometerFileName;
    std::ifstream odoFile(filename);
    if (odoFile.good())
    {
        double odoValue;
        odoFile >> odoValue;
        Data::setTotalOdometer(odoValue);
    }
    else
    {
        Data::setTotalOdometer(0);
    }
    odoFile.close();
}

void writeOdometer()
{
    auto filename = Settings::getGeneralSettings().odometerFileName;
    std::ofstream odoFile(filename);
    Data::Odometer odometer = Data::getOdometer();
    odoFile << odometer.trip + odometer.total;
    odoFile.close();
}

void odoSignalHandler(int)
{
    IO::terminate();
    writeOdometer();
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    signal(SIGINT, odoSignalHandler);
    signal(SIGTERM, odoSignalHandler);
    signal(SIGHUP, odoSignalHandler);

    bool loadSettingsSuccess = Settings::loadSettings();
    if (!loadSettingsSuccess)
    {
        std::cout << "Error reading settings, terminating." << std::endl;
        return EXIT_FAILURE;
    }

    readOdometer();

    IO::initialize();

    auto settings = Settings::getGeneralSettings();
    std::cout << "Listening on port " << settings.networkListenPort << "..." << std::endl;
    Network connection(settings.networkListenPort);

    bool connIPPrinted = false;

    while (true)
    {
        Data::Tick tick = connection.getTickData();
        if (connection.Ok())
        {
            if (!connIPPrinted)
            {
                connIPPrinted = true;
                std::cout << "Received connection from " << connection.getClientIpAsString() << "." << std::endl;
                if (settings.printConnectionIP)
                {
                    IO::OLED::staticMessageOLED("Received conn from : " + connection.getClientIpAsString(), 1, 2500);
                }
            }
            // printf("Tick time: %f\n", tick.tickTime);
            Data::set(tick);
        }
        else
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
