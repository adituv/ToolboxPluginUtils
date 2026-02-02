#pragma once

#include <string_view>

namespace PluginUtils
{
    void* SiggaScan(std::string_view sigga_pattern, int offset = 0);
}
