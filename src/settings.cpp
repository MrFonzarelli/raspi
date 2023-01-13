#include "settings.hpp"
#include "data.hpp"
#include "io/io.hpp"
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

#define SETTINGS_FILENAME "settings.ini"

namespace bpt = boost::property_tree;

namespace Settings
{
    GeneralSettings g_GeneralSettings;
    IOSettings g_IOSettings;

    std::string invalidValueMessage(const std::string &settingName, const std::string &value)
    {
        return std::string("Error: invalid settings value '") + settingName + "' of '" + value + "'\n";
    }

    bool extractOptions(bpt::ptree &options)
    {
        // General
        g_GeneralSettings.imperialUnits = options.get<bool>("General.UseImperialUnits", false);
        g_GeneralSettings.odometerFileName = options.get<std::string>("General.OdometerFileName", "delete-to-reset-odometer");
        g_GeneralSettings.networkListenPort = options.get<int>("General.NetworkListenPort", 4444);

        std::ostringstream errors;

        auto gameTypeString = options.get<std::string>("General.GameType", "beamng");
        if (gameTypeString == "beamng")
        {
            g_GeneralSettings.gameType = Settings::GameType::BEAMNG;
        }
        else if (gameTypeString == "assetto")
        {
            g_GeneralSettings.gameType = Settings::GameType::ASSETTO;
        }
        else
        {
            errors << invalidValueMessage("General.GameType", gameTypeString);
        }

        // IO
        g_IOSettings.doWelcomeAnimation = options.get<bool>("IO.DoWelcomeAnimation", true);
        auto defaultDisplayStateString = options.get<std::string>("IO.DefaultDisplayState", "speed");
        if (defaultDisplayStateString == "speed")
            g_IOSettings.defaultDisplayState = IO::DisplayState::Speed;
        else if (defaultDisplayStateString == "turbopressure")
            g_IOSettings.defaultDisplayState = IO::DisplayState::TurboPressure;
        else if (defaultDisplayStateString == "currentfuel")
            g_IOSettings.defaultDisplayState = IO::DisplayState::CurrentFuelConsumption;
        else if (defaultDisplayStateString == "averagefuel")
            g_IOSettings.defaultDisplayState = IO::DisplayState::AverageFuelConsumption;
        else if (defaultDisplayStateString == "tripodometer")
            g_IOSettings.defaultDisplayState = IO::DisplayState::TripOdometer;
        else if (defaultDisplayStateString == "odometer")
            g_IOSettings.defaultDisplayState = IO::DisplayState::Odometer;
        else if (defaultDisplayStateString == "enginetemp")
            g_IOSettings.defaultDisplayState = IO::DisplayState::EngineTemp;
        else if (defaultDisplayStateString == "oiltemp")
            g_IOSettings.defaultDisplayState = IO::DisplayState::OilTemp;
        else if (defaultDisplayStateString == "0-100")
            g_IOSettings.defaultDisplayState = IO::DisplayState::ZeroTo100;
        else if (defaultDisplayStateString == "0-200")
            g_IOSettings.defaultDisplayState = IO::DisplayState::ZeroTo200;
        else if (defaultDisplayStateString == "0-300")
            g_IOSettings.defaultDisplayState = IO::DisplayState::ZeroTo300;
        else if (defaultDisplayStateString == "100-200")
            g_IOSettings.defaultDisplayState = IO::DisplayState::HundredTo200;
        else if (defaultDisplayStateString == "100-300")
            g_IOSettings.defaultDisplayState = IO::DisplayState::HundredTo300;
        else if (defaultDisplayStateString == "200-300")
            g_IOSettings.defaultDisplayState = IO::DisplayState::TwoHundredTo300;
        else if (defaultDisplayStateString == "quartermile")
            g_IOSettings.defaultDisplayState = IO::DisplayState::QuarterMile;
        else if (defaultDisplayStateString == "manualtimer")
            g_IOSettings.defaultDisplayState = IO::DisplayState::CustomTimer;
        else if (defaultDisplayStateString == "rpm")
            g_IOSettings.defaultDisplayState = IO::DisplayState::RPM;
        else
        {
            errors << invalidValueMessage("IO.DefaultDisplayState", defaultDisplayStateString);
        }

        // SingleDigitDisplay
        g_IOSettings.singleDigitDisplaySettings.enabled = options.get<bool>("SingleDigitDisplay.Enabled", true);

        auto errorMessage = errors.str();
        if (!errorMessage.empty())
        {
            std::cout << errorMessage;
            return false;
        }

        // Sijngle

        return true;
    }

    void doPostInitializations()
    {
        Data::setImperialUnits(g_GeneralSettings.imperialUnits);
    }

    // PUBLIC ------------------------------------------

    bool loadSettings()
    {
        std::ifstream ifs(SETTINGS_FILENAME);
        bpt::ptree options;
        if (ifs.good())
        {
            bpt::read_ini(ifs, options);
        }
        ifs.close();

        if (!extractOptions(options))
        {
            return false;
        }
        doPostInitializations();

        return true;
    }

    const GeneralSettings &getGeneralSettings()
    {
        return g_GeneralSettings;
    }

    const IOSettings &getIOSettings()
    {
        return g_IOSettings;
    }

    const LightsSettings &getLightsSettings()
    {
        return g_IOSettings.lightsSettings;
    }

    const OLEDSettings &getOLEDSettings()
    {
        return g_IOSettings.oledSettings;
    }

    const SingleDigitDisplaySettings &getSingleDigitDisplaySettings()
    {
        return g_IOSettings.singleDigitDisplaySettings;
    }

    const TripleDigitDisplaySettings &getTripleDigitDisplaySettings()
    {
        return g_IOSettings.tripleDigitDisplaySettings;
    }

    const ButtonSettings &getButtonSettings()
    {
        return g_IOSettings.buttonSettings;
    }
}