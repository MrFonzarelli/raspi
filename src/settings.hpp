#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "io/io.hpp"
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

    struct LightsSettings
    {
        bool enabled;
        // TODO
    };

    struct OLEDSettings
    {
        bool enabled;
        // TODO
    };

    struct SingleDigitDisplaySettings
    {
        bool enabled;
        // TODO
    };

    struct TripleDigitDisplaySettings
    {
        bool enabled;
        // TODO
    };

    struct ButtonSettings
    {
        bool enabled;
        // TODO
    };

    struct IOSettings
    {
        LightsSettings lightsSettings;
        OLEDSettings oledSettings;
        SingleDigitDisplaySettings singleDigitDisplaySettings;
        TripleDigitDisplaySettings tripleDigitDisplaySettings;
        ButtonSettings buttonSettings;

        IO::DisplayState defaultDisplayState;
        bool doWelcomeAnimation;
    };

    bool loadSettings();

    const GeneralSettings &getGeneralSettings();

    const IOSettings &getIOSettings();

    const LightsSettings &getLightsSettings();

    const OLEDSettings &getOLEDSettings();

    const SingleDigitDisplaySettings &getSingleDigitDisplaySettings();

    const TripleDigitDisplaySettings &getTripleDigitDisplaySettings();

    const ButtonSettings &getButtonSettings();
}

#endif