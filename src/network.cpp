#include "network.hpp"
#include "data.hpp"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <chrono>
#include <cstdio>
#include <cstring>

Network::Network(int port)
    : m_IsOk(false), m_SocketFd(0), m_TickCounter(0)
{
    struct sockaddr_in myaddr, clientaddr;
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    memset(&clientaddr, 0, sizeof(struct sockaddr_in));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(port);
    m_SocketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_SocketFd == -1)
    {
        printf("socket err \n");
        return;
    }
    int resu = bind(m_SocketFd, (struct sockaddr *)&myaddr, sizeof(struct sockaddr));
    if (resu == -1)
    {
        printf("bind err \n");
        return;
    }

    m_IsOk = true;
    m_PrevTime = std::chrono::high_resolution_clock::now();
}

Data::Tick Network::getTickData()
{
    Data::Tick tickData;
    struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(struct sockaddr_in));

    static char buffer[128];
    socklen_t addrLen = sizeof(clientaddr);
    int res = recvfrom(m_SocketFd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientaddr, (socklen_t *)&addrLen);
    if (res == -1)
    {
        printf("recv err \n");
        m_IsOk = false;
        return Data::Tick();
    }
    else
    {
        auto newTime = std::chrono::high_resolution_clock::now();

        OutGauge *s = (OutGauge *)buffer;
        tickData.outGauge = *s;
        tickData.tickCounter = m_TickCounter;
        tickData.tickTime = (newTime - m_PrevTime).count() / 1e6;
        Data::set(tickData);

        m_PrevTime = newTime;
    }

    m_TickCounter++;
    return tickData;
}

bool Network::Ok()
{
    return m_IsOk;
}