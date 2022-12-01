// includes
#include "data.hpp"
#include "io/io.hpp"
#include "io/display_single_digit.hpp"
#include "io/display_triple_digit.hpp"
#include "outgauge.hpp"
#include "pins.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <chrono>
#include <wiringPi.h>
#include <fstream>
#include <thread>
#include <mutex>
#include <cmath>
#include <signal.h>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/rolling_sum.hpp>
#include <boost/accumulators/statistics/rolling_count.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>
#include <boost/accumulators/statistics/rolling_window.hpp>

using namespace boost::accumulators;

#define ODOMETER_FILENAME "delete-to-reset-odometer"

std::mutex tripleDigitMutex;

float odometer;
float dist;
double trip_odometer;
double fuelDistance;
double fuelBurnedTotal;
double fuelConsumption;
double fuelConsumption_avg;
double fuelBurned;
double displayFuelCons;
double displayFuelConsAvg;
double fuel_old;
long long tick_counter = 0;

IO::DisplayState displayState = IO::DisplayState::Speed;

void read_odometer()
{
    std::ifstream odo_file(ODOMETER_FILENAME);
    if (odo_file.good())
    {
        odo_file >> odometer;
    }
    else
    {
        odometer = 0;
    }
    odo_file.close();
}

void write_odometer()
{
    std::ofstream odo_file(ODOMETER_FILENAME);
    odo_file << trip_odometer + odometer;
    odo_file.close();
}

double calcFuelConsumption(double fuelBurnedCalc, double distance)
{
    if (fuelBurnedCalc < 1e-4 || distance < 1e-4)
    {
        return 0;
    }
    else
    {
        return ((100 / distance) * fuelBurnedCalc);
    }
}

void odo_signal_handler(int)
{
    write_odometer();
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    signal(SIGINT, odo_signal_handler);
    signal(SIGTERM, odo_signal_handler);
    signal(SIGHUP, odo_signal_handler);
    read_odometer();

    struct sockaddr_in myaddr, clientaddr;
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    memset(&clientaddr, 0, sizeof(struct sockaddr_in));
    socklen_t addr_len = sizeof(struct sockaddr_in);
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));

    IO::initialize();

    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(4444);
    addr_len = sizeof(myaddr);
    int sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sfd == -1)
    {
        printf("socket err \n");
        return 0;
    }
    int resu = bind(sfd, (struct sockaddr *)&myaddr, sizeof(struct sockaddr));
    if (resu == -1)
    {
        printf("bind err \n");
        return 0;
    }

    accumulator_set<double, stats<tag::rolling_mean>> accumulatorFuelConsumption(tag::rolling_window::window_size = 20);
    accumulator_set<double, stats<tag::rolling_sum>> accumulatorDistDelta(tag::rolling_window::window_size = 25);
    accumulator_set<double, stats<tag::rolling_sum>> accumulatorFuelAmount(tag::rolling_window::window_size = 25);

    auto old_time = std::chrono::high_resolution_clock::now();

    while (true)
    {
        int res = recvfrom(sfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientaddr, (socklen_t *)&addr_len);
        if (res == -1)
        {
            printf("recv err \n");
            return 0;
        }
        else
        {
            auto new_time = std::chrono::high_resolution_clock::now();

            Data::Tick tick = Data::get();

            tripleDigitMutex.lock(); // Mutex start
            double speed_to_count = tick.outGauge.speed;

            if (speed_to_count < 0.5)
            {
                speed_to_count = 0;
            }
            if (fuel_old < 1e-6)
            {
                fuelBurned = 0;
                fuel_old = tick.outGauge.fuel_remaining;
            }
            else
            {
                fuelBurned = fuel_old - tick.outGauge.fuel_remaining;
                fuel_old = tick.outGauge.fuel_remaining;
            }
            if (fuelBurned > 1e-6)
            {
                fuelBurnedTotal += fuelBurned;
            }

            double distDelta = tick.tickTime * speed_to_count / 1000;
            trip_odometer += distDelta;
            fuelDistance += distDelta;
            accumulatorFuelAmount(fuelBurned);
            accumulatorDistDelta(distDelta);
            fuelConsumption = calcFuelConsumption(rolling_sum(accumulatorFuelAmount), rolling_sum(accumulatorDistDelta));
            accumulatorFuelConsumption(fuelConsumption);

            if (tick_counter % 5 == 0)
            {
                fuelConsumption_avg = calcFuelConsumption(fuelBurnedTotal, fuelDistance);
                if (tick_counter % 20 == 0)
                {
                    displayFuelCons = rolling_mean(accumulatorFuelConsumption);
                }
            }

            dist = trip_odometer;
            tripleDigitMutex.unlock(); // Mutex end

            {
                OutGauge *s = (OutGauge *)buffer;
                Data::Tick tickData;
                tickData.outGauge = *s;
                tickData.tickCounter = tick_counter;
                tickData.tickTime = (new_time - old_time).count();
                tickData.displayState = displayState;
                tickData.fuelCons = fuelConsumption;
                tickData.fuelConsAvg = displayFuelCons;
                tickData.odometer = odometer;
                tickData.tripOdometer = trip_odometer;
                Data::set(tickData);
            }

            old_time = new_time;
        }
        tick_counter++;
    }

    return 0;
}
