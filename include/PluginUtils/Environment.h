#pragma once

#include <filesystem>
#include <string>

namespace PluginUtils::Environment
{
    std::filesystem::path GetComputerName();
    std::filesystem::path GetDocumentsPath();
    std::filesystem::path GetToolboxSettingsPath();
}
