#pragma once

#include <cstdint>
#include <string_view>

namespace PluginUtils
{
    uintptr_t SiggaScan(std::string_view sigga_pattern, int offset = 0);
}
