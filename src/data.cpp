#include "data.hpp"
#include <mutex>

namespace Data
{
    std::mutex g_DataMutex;
    Tick g_CurrentTick;

    void set(const Tick &tick)
    {
        g_DataMutex.lock();
        g_CurrentTick = tick;
        g_DataMutex.unlock();
    }

    Tick get()
    {
        g_DataMutex.lock();
        Tick tick = g_CurrentTick;
        g_DataMutex.unlock();
        return tick;
    }
}