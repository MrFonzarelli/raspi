// includes
#include "data.hpp"
#include "io/io.hpp"
#include "network.hpp"
#include "outgauge.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <chrono>
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
    writeOdometer();
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    signal(SIGINT, odoSignalHandler);
    signal(SIGTERM, odoSignalHandler);
    signal(SIGHUP, odoSignalHandler);
    readOdometer();

    struct sockaddr_in myaddr, clientaddr;
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    memset(&clientaddr, 0, sizeof(struct sockaddr_in));
    socklen_t addrLen = sizeof(struct sockaddr_in);
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));

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
            printf("Speed: %d", tick.outGauge.airspeed);
            Data::set(tick);
        }
        else
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
