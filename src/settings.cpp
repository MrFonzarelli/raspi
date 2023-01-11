#include "settings.hpp"
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
        // TODO
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
    }

    const GeneralSettings &getGeneralSettings()
    {
        return g_GeneralSettings;
    }
}