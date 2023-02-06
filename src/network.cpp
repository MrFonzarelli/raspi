#include "network.hpp"
#include "data.hpp"
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <locale>
#include <cstdio>
#include <cstdint>
#include <cstring>

#define ASSETTO_STRING_SIZE 100

struct AssettoRequest
{
    enum class OperationType
    {
        HANDSHAKE = 0,
        SUBSCRIBE_UPDATE = 1, // Player vehicle-specific information, such as speed
        SUBSCRIBE_SPOT = 2,   // Race information - lap times for all drivers
        DISMISS = 3
    };

    int32_t identifier = 1;
    int32_t version = 1;
    int32_t operation;
};

struct AssettoHandshakeResponse
{
    char carName[ASSETTO_STRING_SIZE];
    char driverName[ASSETTO_STRING_SIZE];
    int32_t identifier;
    int32_t version;
    char trackName[ASSETTO_STRING_SIZE];
    char trackConfig[ASSETTO_STRING_SIZE];
};

void convertAssettoWideString(char *str)
{
    int i = 0;
    while (str[i * 2] != '%' && i < ASSETTO_STRING_SIZE / 2)
    {
        str[i] = str[i * 2];
        i++;
    }
    str[i] = 0;
}

void Network::initializeBeamNGConnection()
{
    struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(struct sockaddr_in));
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(m_BeamNGSettings.listenPort);
    m_SocketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_SocketFd == -1)
    {
        printf("socket err \n");
        return;
    }
    int resu = bind(m_SocketFd, (struct sockaddr *)&clientaddr, sizeof(struct sockaddr));
    if (resu == -1)
    {
        printf("bind err \n");
        return;
    }
    printf("Listening on port %d...\n", m_BeamNGSettings.listenPort);
}

void Network::initializeAssettoCorsaConnection()
{
    struct sockaddr_in hostaddr;
    memset(&hostaddr, 0, sizeof(struct sockaddr_in));
    hostaddr.sin_family = AF_INET;
    hostaddr.sin_port = htons(m_AssettoCorsaSettings.hostPort);
    inet_aton(m_AssettoCorsaSettings.hostIpString.c_str(), &hostaddr.sin_addr);
    m_SocketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_SocketFd == -1)
    {
        printf("socket err \n");
        return;
    }
    printf("Trying to connect to host at %s:%d\n", inet_ntoa(hostaddr.sin_addr), m_AssettoCorsaSettings.hostPort);
    int res = connect(m_SocketFd, (struct sockaddr *)&hostaddr, sizeof(struct sockaddr));
    if (res == -1)
    {
        printf("connect err\n");
        return;
    }

    // Do handshake
    AssettoRequest request;
    request.operation = (int)AssettoRequest::OperationType::HANDSHAKE;
    res = send(m_SocketFd, &request, sizeof(request), 0);
    if (res < 0)
    {
        printf("Failed to send handshake request\n");
        return;
    }
    AssettoHandshakeResponse response;
    res = recv(m_SocketFd, &response, sizeof(response), 0);
    if (res < 0)
    {
        printf("Failed to receive handshake response\n");
        return;
    }
    printf("Successfully received Assetto handshake.\nPayload size in bytes: %d\nIdentifier and version: %d, %d\n", res, response.identifier, response.version);
    convertAssettoWideString(response.carName);
    convertAssettoWideString(response.driverName);
    convertAssettoWideString(response.trackName);
    std::cout << "CarName: " << response.carName << std::endl
              << "DriverName: " << response.driverName << std::endl
              << "TrackName: " << response.trackName << std::endl;

    request.operation = (int)AssettoRequest::OperationType::SUBSCRIBE_UPDATE;
    res = send(m_SocketFd, &request, sizeof(request), 0);
    if (res < 0)
    {
        printf("Failed to send subscribe request\n");
        return;
    }
}

Network::Network()
    : m_IsOk(false), m_SocketFd(0), m_TickCounter(0), m_AssettoCorsaSettings(Settings::getAssettoCorsaSettings()),
      m_BeamNGSettings(Settings::getBeamNGSettings()), m_GeneralSettings(Settings::getGeneralSettings())
{
    switch (m_GeneralSettings.gameType)
    {
    case Settings::GameType::BeamNG:
        initializeBeamNGConnection();
        break;
    case Settings::GameType::AssettoCorsa:
        initializeAssettoCorsaConnection();
        break;
    }

    m_PrevTime = std::chrono::high_resolution_clock::now();
}

Data::Tick Network::getTickData()
{
    Data::Tick tickData;
    struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(struct sockaddr_in));

    static char buffer[sizeof(RTCarInfo)];
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
        m_IsOk = true;
        if (m_ClientIpAsString.empty())
        {
            m_ClientIp = clientaddr.sin_addr;
            m_ClientIpAsString = std::string(inet_ntoa(m_ClientIp));
        }
        auto newTime = std::chrono::high_resolution_clock::now();

        switch (m_GeneralSettings.gameType)
        {
        case Settings::GameType::BeamNG:
            tickData.vehicleTelemetry = *(OutGauge *)buffer;
            break;
        case Settings::GameType::AssettoCorsa:
            tickData.vehicleTelemetry = *(RTCarInfo *)buffer;
            break;
        }
        tickData.tickCounter = m_TickCounter;
        tickData.tickTime = (newTime - m_PrevTime).count() * 1e-9;
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

const std::string &Network::getClientIpAsString()
{
    return m_ClientIpAsString;
}