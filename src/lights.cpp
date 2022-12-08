#include "lights.hpp"
#include "data.hpp"

#include <chrono>
#include <iostream>

namespace IO::Lights
{

    void displayLights(const OutGauge::DashLights &dashLights)
    {
        // Example
        // if (dashLights.shiftLight)
        // {
        //     // turn on shiftLight
        // }
    }

    void doLightsWork()
    {
        long long tickCounter = 0;
        OutGauge::DashLights oldDashLights; // test
        while (true)
        {
            Data::Tick tick;
            if (tickCounter % 1000 == 0)
            {
                tick = Data::get();
            }

            auto currentDashLights = tick.outGauge.getDashLights(); // test

            displayLights(currentDashLights);

            // test, if you couldn't tell lmao xd
            if (currentDashLights.shiftLight != oldDashLights.shiftLight)
            {
                std::cout << "shiftLight: " << currentDashLights.shiftLight << std::endl;
            }
            if (currentDashLights.lowBeam != oldDashLights.lowBeam)
            {
                std::cout << "lowBeam: " << currentDashLights.lowBeam << std::endl;
            }
            if (currentDashLights.highBeam != oldDashLights.highBeam)
            {
                std::cout << "highBeam: " << currentDashLights.highBeam << std::endl;
            }
            if (currentDashLights.abs != oldDashLights.abs)
            {
                std::cout << "abs: " << currentDashLights.abs << std::endl;
            }
            if (currentDashLights.engineRunning != oldDashLights.engineRunning)
            {
                std::cout << "engineRunning: " << currentDashLights.engineRunning << std::endl;
            }
            if (currentDashLights.fogLight != oldDashLights.fogLight)
            {
                std::cout << "fogLight: " << currentDashLights.fogLight << std::endl;
            }
            if (currentDashLights.hazardLight != oldDashLights.hazardLight)
            {
                std::cout << "hazardLight: " << currentDashLights.hazardLight << std::endl;
            }
            if (currentDashLights.oilWarning != oldDashLights.oilWarning)
            {
                std::cout << "oilWarning: " << currentDashLights.oilWarning << std::endl;
            }
            if (currentDashLights.parkBrake != oldDashLights.parkBrake)
            {
                std::cout << "parkBrake: " << currentDashLights.parkBrake << std::endl;
            }
            if (currentDashLights.signalLeft != oldDashLights.signalLeft)
            {
                std::cout << "signalLeft: " << currentDashLights.signalLeft << std::endl;
            }
            if (currentDashLights.signalRight != oldDashLights.signalRight)
            {
                std::cout << "signalRight: " << currentDashLights.signalRight << std::endl;
            }
            if (currentDashLights.tractionControl != oldDashLights.tractionControl)
            {
                std::cout << "tractionControl: " << currentDashLights.tractionControl << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::microseconds(10));
            tickCounter++;
            oldDashLights = currentDashLights;
        }
    }

    std::thread *startThread()
    {
        return new std::thread(doLightsWork);
    }

}