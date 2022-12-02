#include "network.hpp"
#include "data.hpp"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <chrono>

Network::Network(int port)
    : isOk(false), socketFd(0), tickCounter(0)
{
    struct sockaddr_in myaddr, clientaddr;
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    memset(&clientaddr, 0, sizeof(struct sockaddr_in));
    socklen_t addrLen = sizeof(struct sockaddr_in);
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(4444);
    addrLen = sizeof(myaddr);
    socketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketFd == -1)
    {
        printf("socket err \n");
        return;
    }
    int resu = bind(socketFd, (struct sockaddr *)&myaddr, sizeof(struct sockaddr));
    if (resu == -1)
    {
        printf("bind err \n");
        return;
    }

    isOk = true;
}

OutGauge Network::getOutGaugeData()
{
    struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(struct sockaddr_in));

    char buffer[128];
    memset(buffer, 0, sizeof(buffer));

    long long tickCounter = 0;

    int res = recvfrom(socketFd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientaddr, (socklen_t *)&addrLen);
    if (res == -1)
    {
        printf("recv err \n");
        return OutGauge();
    }
    else
    {
        auto newTime = std::chrono::high_resolution_clock::now();

        OutGauge *s = (OutGauge *)buffer;
        Data::Tick tickData;
        tickData.outGauge = *s;
        tickData.tickCounter = tickCounter;
        tickData.tickTime = (newTime - prevTime).count();
        Data::set(tickData);

        prevTime = newTime;
    }

    tickCounter++;
}