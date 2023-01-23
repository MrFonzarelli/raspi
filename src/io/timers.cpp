#include "timers.hpp"
#include "data.hpp"

#include <chrono>
#include <mutex>
#include <thread>
#include <cstdio>

namespace IO::Timers
{

    std::chrono::steady_clock::time_point g_Tmr1StartTime;
    std::chrono::steady_clock::time_point g_Tmr2StartTime;
    bool g_Tmr1IsRunning = false;
    bool g_Tmr1IsReset = true;
    bool g_Tmr2IsRunning = false;
    bool g_Tmr2IsReset = true;
    bool g_Tmr2Split = false;
    double g_TimerCustom = 0;
    double g_TimerCustomSplitOffset = 0;
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
    std::mutex g_Timer1Mutex;
    std::mutex g_Timer2Mutex;

    void doTimerWork()
    {
        auto oldTime = std::chrono::steady_clock::now();
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            Data::Tick tick = Data::get();
            auto currentTime = std::chrono::steady_clock::now();
            g_Timer1Mutex.lock();
            if (g_Tmr1IsReset && tick.outGauge.airspeed > 0.5)
            {
                if (!g_Tmr1IsRunning)
                {
                    g_Tmr1StartTime = std::chrono::steady_clock::now();
                }
                g_Tmr1IsReset = false;
                g_Tmr1IsRunning = true;
            }

            g_Timer2Mutex.lock();
            if (g_Tmr2IsRunning)
            {
                if (!g_Tmr2Split)
                {
                    g_TimerCustom += g_TimerCustomSplitOffset;
                    g_TimerCustomSplitOffset = 0;
                    std::chrono::duration<double> timeDelta = currentTime - oldTime;
                    g_TimerCustom += timeDelta.count();
                }
                else
                {
                    std::chrono::duration<double> timeDelta = currentTime - oldTime;
                    g_TimerCustomSplitOffset += timeDelta.count();
                }
            }
            g_Timer2Mutex.unlock();

            if (g_Tmr1IsRunning)
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

                if (tick.outGauge.airspeed * 3.6 > 100 && !g_Timer0to100Finished)
                {
                    g_Timer0to100Finished = true;
                }

                if (tick.outGauge.airspeed * 3.6 > 200 && !g_Timer0to200Finished)
                {
                    g_Timer0to200Finished = true;
                }

                if (tick.outGauge.airspeed * 3.6 > 300 && !g_Timer0to300Finished)
                {
                    g_Timer0to300Finished = true;
                }

                g_Distance += timeDelta.count() * tick.outGauge.airspeed;
                if (g_Distance > 402.336 && !g_TimerQuarterMileFinished)
                {
                    g_TimerQuarterMileFinished = true;
                }
            }
            oldTime = currentTime;
            g_Timer1Mutex.unlock();
        }
    }

    std::thread *startThread()
    {
        return new std::thread(doTimerWork);
    }

    void reset()
    {
        g_Tmr1IsReset = true;
        g_Tmr1IsRunning = false;
        g_Timer0to100 = 0;
        g_Timer0to200 = 0;
        g_Timer0to300 = 0;
        g_Timer100to200 = 0;
        g_Timer100to300 = 0;
        g_Timer200to300 = 0;
        g_TimerQuarterMile = 0;
        g_Timer0to100Finished = false;
        g_Timer0to200Finished = false;
        g_Timer0to300Finished = false;
        g_TimerQuarterMileFinished = false;
        g_Distance = 0;
    }

    void startTimerCustom()
    {
        g_Timer2Mutex.lock();
        g_Tmr2IsRunning = true;
        if (g_Tmr2IsReset)
        {
            g_Tmr2StartTime = std::chrono::steady_clock::now();
            g_Tmr2IsReset = false;
        }
        g_Timer2Mutex.unlock();
    }

    void stopTimerCustom()
    {
        g_Timer2Mutex.lock();
        g_Tmr2IsRunning = false;
        g_Timer2Mutex.unlock();
    }

    void resetTimerCustom()
    {
        g_Timer2Mutex.lock();
        g_Tmr2IsRunning = false;
        g_TimerCustom = 0;
        g_Tmr2IsReset = true;
        g_Timer2Mutex.unlock();
    }

    void splitTimerCustom()
    {
        g_Timer2Mutex.lock();
        g_Tmr2Split = true;
        g_Timer2Mutex.unlock();
    }

    void unsplitTimerCustom()
    {
        g_Timer2Mutex.lock();
        g_Tmr2Split = false;
        g_Timer2Mutex.unlock();
    }

    bool timerCustomIsRunning()
    {
        g_Timer2Mutex.lock();
        bool isRunning = g_Tmr2IsRunning;
        g_Timer2Mutex.unlock();
        return isRunning;
    }

    double getTime(DisplayState displayState)
    {

        double result;
        switch (displayState)
        {
        case DisplayState::ZeroTo100:
            g_Timer1Mutex.lock();
            result = g_Timer0to100 * 1000;
            g_Timer1Mutex.unlock();
            break;
        case DisplayState::ZeroTo200:
            g_Timer1Mutex.lock();
            result = g_Timer0to200 * 1000;
            g_Timer1Mutex.unlock();
            break;
        case DisplayState::ZeroTo300:
            g_Timer1Mutex.lock();
            result = g_Timer0to300 * 1000;
            g_Timer1Mutex.unlock();
            break;
        case DisplayState::QuarterMile:
            g_Timer1Mutex.lock();
            result = g_TimerQuarterMile * 1000;
            g_Timer1Mutex.unlock();
            break;
        case DisplayState::HundredTo200:
            g_Timer1Mutex.lock();
            result = g_Timer100to200 * 1000;
            g_Timer1Mutex.unlock();
            break;
        case DisplayState::HundredTo300:
            g_Timer1Mutex.lock();
            result = g_Timer100to300 * 1000;
            g_Timer1Mutex.unlock();
            break;
        case DisplayState::TwoHundredTo300:
            g_Timer1Mutex.lock();
            result = g_Timer200to300 * 1000;
            g_Timer1Mutex.unlock();
            break;
        case DisplayState::CustomTimer:
            g_Timer2Mutex.lock();
            result = g_TimerCustom * 1000;
            g_Timer2Mutex.unlock();
            break;
        default:
            result = 420.69;
        }

        return result;
    }

}