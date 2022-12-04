#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "data.hpp"
#include <chrono>

class Network
{
    bool m_IsOk;
    int m_SocketFd;
    long long m_TickCounter;
    std::chrono::high_resolution_clock::time_point m_PrevTime;

public:
    Network(int port);
    Data::Tick getTickData();
    bool Ok();
};

#endif