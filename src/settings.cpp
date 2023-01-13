#include "settings.hpp"
#include "data.hpp"
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>

#define SETTINGS_FILENAME "settings.ini"

namespace bpt = boost::property_tree;

namespace Settings
{
    GeneralSettings g_GeneralSettings;

    void extractOptions(bpt::ptree &options)
    {
        // General
        g_GeneralSettings.imperialUnits = options.get<bool>("General.UseImperialUnits", false);
        g_GeneralSettings.odometerFileName = options.get<std::string>("General.OdometerFileName", "delete-to-reset-odometer");
        g_GeneralSettings.networkListenPort = options.get<int>("General.NetworkListenPort", 4444);

        auto gameTypeString = options.get<std::string>("General.GameType", "beamng");
        if (gameTypeString == "beamng")
        {
            g_GeneralSettings.gameType = Settings::GameType::BEAMNG;
        }
        else if (gameTypeString == "assetto")
        {
            g_GeneralSettings.gameType = Settings::GameType::ASSETTO;
        }
    }

    void doPostInitializations()
    {
        Data::setImperialUnits(g_GeneralSettings.imperialUnits);
    }

    // PUBLIC ------------------------------------------

    void loadSettings()
    {
        std::ifstream ifs(SETTINGS_FILENAME);
        bpt::ptree options;
        if (ifs.good())
        {
            bpt::read_ini(ifs, options);
        }
        ifs.close();
        extractOptions(options);
        doPostInitializations();
    }

    const GeneralSettings &getGeneralSettings()
    {
        return g_GeneralSettings;
    }
}