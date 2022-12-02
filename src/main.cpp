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

    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(4444);
    addrLen = sizeof(myaddr);
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

    long long tickCounter = 0;
    auto oldTime = std::chrono::high_resolution_clock::now();

    while (true)
    {
        int res = recvfrom(sfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientaddr, (socklen_t *)&addrLen);
        if (res == -1)
        {
            printf("recv err \n");
            return 0;
        }
        else
        {
            auto newTime = std::chrono::high_resolution_clock::now();

            OutGauge *s = (OutGauge *)buffer;
            Data::Tick tickData;
            tickData.outGauge = *s;
            tickData.tickCounter = tickCounter;
            tickData.tickTime = (newTime - oldTime).count();
            Data::set(tickData);

            oldTime = newTime;
        }
        tickCounter++;
    }

    return 0;
}
