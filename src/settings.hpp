#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

namespace Settings
{
    struct GeneralSettings
    {
        bool imperialUnits;
        std::string odometerFileName;
        int networkListenPort;
        // TODO add more
    };

    void loadSettings();

    const GeneralSettings &getGeneralSettings();
}

#endif