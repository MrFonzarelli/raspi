#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

namespace Settings
{
    enum class GameType
    {
        BEAMNG,
        ASSETTO
    };

    struct GeneralSettings
    {
        bool imperialUnits;
        std::string odometerFileName;
        int networkListenPort;
        GameType gameType;
        // TODO add more
    };

    void loadSettings();

    const GeneralSettings &getGeneralSettings();
}

#endif