#include "timers.hpp"
#include "data.hpp"

#include <chrono>
#include <mutex>
#include <thread>
#include <cstdio>

namespace IO::Timers
{

    std::chrono::steady_clock::time_point g_StartTime;
    bool g_IsRunning = false;
    bool g_IsReset = true;
    double g_Timer0to100 = 0;
    double g_Timer0to200 = 0;
    double g_Timer0to300 = 0;
    double g_Timer100to200 = 0;
    double g_Timer100to300 = 0;
    double g_Timer200to300 = 0;
    double g_TimerQuarterMile = 0;
    double g_Distance = 0;
    bool g_Timer0to100Finished = false;
    bool g_Timer0to200Finished = false;
    bool g_Timer0to300Finished = false;
    bool g_TimerQuarterMileFinished = false;
    std::mutex g_TimerMutex;

    void doTimerWork()
    {
        auto oldTime = std::chrono::steady_clock::now();
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            Data::Tick tick = Data::get();
            auto currentTime = std::chrono::steady_clock::now();
            g_TimerMutex.lock();
            if (g_IsReset && tick.outGauge.airspeed > 0.5)
            {
                if (!g_IsRunning)
                {
                    g_StartTime = std::chrono::steady_clock::now();
                }
                g_IsReset = false;
                g_IsRunning = true;
            }

            if (g_IsRunning)
            {
                std::chrono::duration<double> timeDelta = currentTime - oldTime;
                if (!g_Timer0to100Finished)
                {
                    g_Timer0to100 += timeDelta.count();
                }

                if (!g_Timer0to200Finished)
                {
                    g_Timer0to200 += timeDelta.count();
                    g_Timer100to200 = g_Timer0to200 - g_Timer0to100;
                }

                if (!g_Timer0to300Finished)
                {
                    g_Timer0to300 += timeDelta.count();
                    g_Timer100to300 = g_Timer0to300 - g_Timer0to100;
                    g_Timer200to300 = g_Timer0to300 - g_Timer0to200;
                }

                if (!g_TimerQuarterMileFinished)
                {
                    g_TimerQuarterMile += timeDelta.count();
                }

                if (tick.outGauge.airspeed >= 100)
                {
                    g_Timer0to100Finished = true;
                    printf("0-100: %.3fs\n", g_Timer0to100);
                }

                if (tick.outGauge.airspeed >= 200)
                {
                    g_Timer0to200Finished = true;
                    printf("0-200: %.3fs\n", g_Timer0to200);
                    printf("100-200: %.3fs\n", g_Timer100to200);
                }

                if (tick.outGauge.airspeed >= 300)
                {
                    g_Timer0to100Finished = true;
                    printf("0-300: %.3fs\n", g_Timer0to300);
                    printf("100-300: %.3fs\n", g_Timer100to300);
                    printf("200-300: %.3fs\n", g_Timer200to300);
                }

                g_Distance += timeDelta.count() * (tick.outGauge.airspeed / 3.6);
                if (g_Distance > 402.336)
                {
                    g_TimerQuarterMileFinished = true;
                    printf("1/4 mile: %.3fs\n", g_TimerQuarterMile);
                }
            }
            oldTime = currentTime;
            g_TimerMutex.unlock();
        }
    }

    std::thread *startThread()
    {
        return new std::thread(doTimerWork);
    }

    void reset()
    {
        g_IsReset = true;
        g_Timer0to100 = 0;
        g_Timer0to200 = 0;
        g_Timer0to300 = 0;
        g_TimerQuarterMile = 0;
        g_Timer0to100Finished = false;
        g_Timer0to200Finished = false;
        g_Timer0to300Finished = false;
        g_TimerQuarterMileFinished = false;
        g_Distance = 0;
    }

    double getTime(DisplayState displayState)
    {
        g_TimerMutex.lock();
        double result;
        switch (displayState)
        {
        case DisplayState::ZeroTo100:
            result = g_Timer0to100;
            break;
        case DisplayState::ZeroTo200:
            result = g_Timer0to200;
            break;
        case DisplayState::ZeroTo300:
            result = g_Timer0to300;
            break;
        case DisplayState::QuarterMile:
            result = g_TimerQuarterMile;
            break;
        case DisplayState::HundredTo200:
            result = g_Timer100to200;
            break;
        case DisplayState::HundredTo300:
            result = g_Timer100to300;
            break;
        case DisplayState::TwoHundredTo300:
            result = g_Timer200to300;
            break;
        default:
            result = 420.69;
        }
        g_TimerMutex.unlock();
        return result;
    }

}