#ifndef SETTINGS_HPP
#define SETTINGS_HPP

namespace Settings
{
    struct GeneralSettings
    {
        bool imperialUnits;
        std::string odometerFileName;
        // TODO add more
    };

    void loadSettings();

    const GeneralSettings &getGeneralSettings();
}

#endif