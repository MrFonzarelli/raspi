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
            std::get<OutGauge>(tick.vehicleTelemetry).airspeed *= 0.621371;
            std::get<OutGauge>(tick.vehicleTelemetry).turbo *= 14.5038;
            (std::get<OutGauge>(tick.vehicleTelemetry).engTemp *= 1.8) += 32;
            tick.fuelCons = 235.21 / tick.fuelCons;
            tick.fuelConsAvg = 235.21 / tick.fuelConsAvg;
            std::get<OutGauge>(tick.vehicleTelemetry).speed *= 0.621371;
            (std::get<OutGauge>(tick.vehicleTelemetry).oilTemp *= 1.8) += 32;
            tick.odometer.total *= 0.621371;
            tick.odometer.trip *= 0.621371;
        }
    }

    void set(const Tick &tick)
    {
        g_DataMutex.lock();

        Data::Tick prevTick = g_CurrentTick;
        g_CurrentTick = tick;

        double speedToCount = std::get<OutGauge>(g_CurrentTick.vehicleTelemetry).speed > 0.5 ? std::get<OutGauge>(g_CurrentTick.vehicleTelemetry).speed : 0;

        double fuelBurned = std::get<OutGauge>(prevTick.vehicleTelemetry).fuel_remaining < std::get<OutGauge>(g_CurrentTick.vehicleTelemetry).fuel_remaining
                                ? 0
                                : std::get<OutGauge>(prevTick.vehicleTelemetry).fuel_remaining - std::get<OutGauge>(g_CurrentTick.vehicleTelemetry).fuel_remaining;

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

    void setAssetto(const Tick &tick)
    {
        g_DataMutex.lock();

        Data::Tick prevTick = g_CurrentTick;
        g_CurrentTick = tick;

        double speedToCount = std::get<RTCarInfo>(g_CurrentTick.vehicleTelemetry).speed_Ms > 0.5 ? std::get<RTCarInfo>(g_CurrentTick.vehicleTelemetry).speed_Ms : 0;
        double distDelta = g_CurrentTick.tickTime * speedToCount / 1000;
        g_CurrentTick.odometer.trip = prevTick.odometer.trip + distDelta;
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

    void setImperialUnits(bool value)
    {
        g_GayUnitsMutex.lock();
        g_GayUnits = value;
        g_GayUnitsMutex.unlock();
    }
}