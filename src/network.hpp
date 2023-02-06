#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "data.hpp"
#include "settings.hpp"
#include <arpa/inet.h>
#include <chrono>
#include <string>

class Network
{
    bool m_IsOk;
    int m_SocketFd;
    long long m_TickCounter;
    struct in_addr m_ClientIp;
    std::string m_ClientIpAsString;
    std::chrono::high_resolution_clock::time_point m_PrevTime;
    Settings::AssettoCorsaSettings m_AssettoCorsaSettings;
    Settings::BeamNGSettings m_BeamNGSettings;
    Settings::GeneralSettings m_GeneralSettings;

    void initializeBeamNGConnection();
    void initializeAssettoCorsaConnection();

public:
    Network();
    Data::Tick getTickData();
    bool Ok();
    const std::string &getClientIpAsString();
};

#endif