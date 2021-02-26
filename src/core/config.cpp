#include "config.h"
#include "utils/files.h"

ConfigSettings Config::s_configSettings;

void Config::loadSettings(const std::string_view filepath)
{
    rapidjson::Document json = loadJSONFile(filepath);
    s_configSettings.fov = json["fov"].GetFloat();
    s_configSettings.mouseSensitivity = json["mouseSensitivity"].GetFloat();
    s_configSettings.renderDistance = json["renderDistance"].GetInt();
}
