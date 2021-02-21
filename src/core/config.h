#pragma once

struct ConfigSettings
{
    float fov;
    float mouseSensitivity;
};

class Config
{
public:
    static void loadSettings(const std::string_view filepath);

    static const ConfigSettings& getSettings() { return s_configSettings; }

private:
    static ConfigSettings s_configSettings;
};
