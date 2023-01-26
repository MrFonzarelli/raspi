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

    IO::DisplayState stringToDisplayState(const std::string &str)
    {
        if (str == "speed")
            return IO::DisplayState::Speed;
        else if (str == "turbopressure")
            return IO::DisplayState::TurboPressure;
        else if (str == "currentfuel")
            return IO::DisplayState::CurrentFuelConsumption;
        else if (str == "averagefuel")
            return IO::DisplayState::AverageFuelConsumption;
        else if (str == "tripodometer")
            return IO::DisplayState::TripOdometer;
        else if (str == "odometer")
            return IO::DisplayState::Odometer;
        else if (str == "enginetemp")
            return IO::DisplayState::EngineTemp;
        else if (str == "oiltemp")
            return IO::DisplayState::OilTemp;
        else if (str == "0-100")
            return IO::DisplayState::ZeroTo100;
        else if (str == "0-200")
            return IO::DisplayState::ZeroTo200;
        else if (str == "0-300")
            return IO::DisplayState::ZeroTo300;
        else if (str == "100-200")
            return IO::DisplayState::HundredTo200;
        else if (str == "100-300")
            return IO::DisplayState::HundredTo300;
        else if (str == "200-300")
            return IO::DisplayState::TwoHundredTo300;
        else if (str == "quartermile")
            return IO::DisplayState::QuarterMile;
        else if (str == "manualtimer")
            return IO::DisplayState::CustomTimer;
        else if (str == "rpm")
            return IO::DisplayState::RPM;
        else if (str == "rpmandspeed")
            return IO::DisplayState::RPMandSpeed;
        else if (str == "rpmandspeed-sep")
            return IO::DisplayState::RPMandSpeedSep;

        return (IO::DisplayState)-1;
    }

    std::string invalidValueMessage(const std::string &settingName, const std::string &value)
    {
        return std::string("Error: invalid settings value '") + settingName + "' of '" + value + "'\n";
    }

    bool extractOptions(bpt::ptree &options)
    {
        // General
        g_GeneralSettings.printConnectionIP = options.get<bool>("General.PrintConnectionIP", false);
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
        std::string activeDisplayStatesString = options.get<std::string>("IO.ActiveDisplayStates", "speed turbopressure rpm averagefuel rpmandspeed-sep 0-100 quartermile manualtimer");
        std::istringstream split(activeDisplayStatesString);
        std::string word;
        while (split >> word)
        {
            IO::DisplayState state = stringToDisplayState(word);
            if ((int)state >= 0)
            {
                g_IOSettings.activeDisplayStates.push_back(state);
            }
            else
            {
                errors << invalidValueMessage("IO.ActiveDisplayStates", word);
            }
        }

        // SingleDigitDisplay
        g_IOSettings.singleDigitDisplaySettings.enabled = options.get<bool>("SingleDigitDisplay.Enabled", true);

        auto errorMessage = errors.str();
        if (!errorMessage.empty())
        {
            std::cout << errorMessage;
            return false;
        }

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