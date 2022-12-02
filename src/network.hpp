#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "data.hpp"
#include <chrono>

class Network
{
    bool isOk;
    int socketFd;
    long long tickCounter;
    std::chrono::time_point<std::chrono::steady_clock> prevTime;

public:
    Network(int port);
    OutGauge getOutGaugeData();
    bool Ok();
};

#endif