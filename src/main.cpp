// includes
#include "data.hpp"
#include "io/io.hpp"
#include "network.hpp"
#include "outgauge.hpp"
#include "ssd1306_i2c.h"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <signal.h>

#define ODOMETER_FILENAME "delete-to-reset-odometer"

void readOdometer()
{
    std::ifstream odoFile(ODOMETER_FILENAME);
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
    std::ofstream odoFile(ODOMETER_FILENAME);
    Data::Odometer odometer = Data::getOdometer();
    odoFile << odometer.trip + odometer.total;
    odoFile.close();
}

void odoSignalHandler(int)
{
    ssd1306_clearDisplay();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    ssd1306_display();
    writeOdometer();
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    signal(SIGINT, odoSignalHandler);
    signal(SIGTERM, odoSignalHandler);
    signal(SIGHUP, odoSignalHandler);
    readOdometer();

    IO::initialize();

    Network connection(4444);
    if (!connection.Ok())
    {
        return EXIT_FAILURE;
    }

    while (true)
    {
        Data::Tick tick = connection.getTickData();
        if (connection.Ok())
        {
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
