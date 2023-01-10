#include "data.hpp"
#include <mutex>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/rolling_sum.hpp>
#include <boost/accumulators/statistics/rolling_count.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>

using namespace boost::accumulators;

namespace Data
{
    bool g_GayUnits = false;
    std::mutex g_GayUnitsMutex;
    std::mutex g_DataMutex;
    Tick g_CurrentTick;

    accumulator_set<double, stats<tag::rolling_mean>> g_AccumulatorFuelConsumption(tag::rolling_window::window_size = 20);
    accumulator_set<double, stats<tag::rolling_sum>> g_AccumulatorDistDelta(tag::rolling_window::window_size = 25);
    accumulator_set<double, stats<tag::rolling_sum>> g_AccumulatorFuelAmount(tag::rolling_window::window_size = 25);

    double g_Odometer = 0;
    double g_FuelBurnedSinceFuelReset = 0;
    double g_DistanceSinceFuelReset = 0;

    double calcFuelConsumption(double fuelBurnedCalc, double distance)
    {
        if (fuelBurnedCalc < 1e-4 || distance < 1e-4)
        {
            return 0;
        }

        return ((100 / distance) * fuelBurnedCalc);
    }

    void adjustForUnits(Tick &tick)
    {
        if (g_GayUnits)
        {
            tick.outGauge.airspeed *= 0.621371;
            tick.outGauge.turbo *= 14.5038;
            tick.outGauge.engTemp = tick.outGauge.engTemp * 1.8 + 32;
            tick.fuelCons = 235.21 / tick.fuelCons;
            tick.fuelConsAvg = 235.21 / tick.fuelConsAvg;
            tick.outGauge.speed *= 0.621371;
            tick.outGauge.oilTemp *= tick.outGauge.oilTemp * 1.8 + 32;
            tick.odometer.total *= 0.621371;
            tick.odometer.trip *= 0.621371;
        }
    }

    void set(const Tick &tick)
    {
        g_DataMutex.lock();

        Data::Tick prevTick = g_CurrentTick;
        g_CurrentTick = tick;

        // Additional calculations and statistics
        // g_CurrentTick.outGauge.speed *= 1.609344;
        // g_CurrentTick.outGauge.airspeed *= 1.609344;
        // g_CurrentTick.outGauge.turbo *= 0.069;
        // g_CurrentTick.outGauge.engTemp = (g_CurrentTick.outGauge.engTemp - 32) * (5 / 9);
        // g_CurrentTick.outGauge.oilTemp = (g_CurrentTick.outGauge.oilTemp - 32) * (5 / 9);

        double speedToCount = g_CurrentTick.outGauge.speed > 0.5 ? g_CurrentTick.outGauge.speed : 0;

        double fuelBurned = prevTick.outGauge.fuel_remaining < 1e-6
                                ? 0
                                : prevTick.outGauge.fuel_remaining - g_CurrentTick.outGauge.fuel_remaining;

        if (fuelBurned > 1e-6)
        {
            g_FuelBurnedSinceFuelReset += fuelBurned;
        }

        double distDelta = g_CurrentTick.tickTime * speedToCount / 1000;
        g_CurrentTick.odometer.trip = prevTick.odometer.trip + distDelta;
        g_DistanceSinceFuelReset += distDelta;
        g_AccumulatorFuelAmount(fuelBurned);
        g_AccumulatorDistDelta(distDelta);
        double fuelConsumption = calcFuelConsumption(rolling_sum(g_AccumulatorFuelAmount), rolling_sum(g_AccumulatorDistDelta));
        g_AccumulatorFuelConsumption(fuelConsumption);

        if (g_CurrentTick.tickCounter % 5 == 0)
        {
            g_CurrentTick.fuelConsAvg = g_CurrentTick.tickCounter % 20 == 0
                                            ? rolling_mean(g_AccumulatorFuelConsumption)
                                            : prevTick.fuelConsAvg;
        }
        g_CurrentTick.fuelCons = fuelConsumption;
        g_CurrentTick.odometer.total = g_Odometer;

        g_DataMutex.unlock();
    }

    Tick get()
    {
        g_DataMutex.lock();
        Tick tick = g_CurrentTick;
        g_DataMutex.unlock();
        adjustForUnits(tick);
        return tick;
    }

    Odometer getOdometer()
    {
        g_DataMutex.lock();
        Odometer result = g_CurrentTick.odometer;
        g_DataMutex.unlock();
        return result;
    }

    void setTotalOdometer(double value)
    {
        g_DataMutex.lock();
        g_Odometer = value;
        g_DataMutex.unlock();
    }

    void resetTripOdometer()
    {
        g_DataMutex.lock();
        g_CurrentTick.odometer.total += g_CurrentTick.odometer.trip;
        g_CurrentTick.odometer.trip = 0;
        g_DataMutex.unlock();
    }

    void resetAvgFuelConsumption()
    {
        g_DataMutex.lock();
        g_FuelBurnedSinceFuelReset = 0;
        g_DistanceSinceFuelReset = 0;
        g_DataMutex.unlock();
    }

    void toggleUnits()
    {
        g_GayUnitsMutex.lock();
        g_GayUnits = !g_GayUnits;
        g_GayUnitsMutex.unlock();
    }
}