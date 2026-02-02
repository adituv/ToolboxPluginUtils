#include "PluginUtils/Scanning.h"

// Required for GWCA/Utilities/Scanner.h to be imported
// Why, GWCA, why?
#include <Windows.h>

#include <GWCA/Utilities/Scanner.h>

#include <ctre.hpp>
#include <ranges>
#include <string>

void* PluginUtils::SiggaScan(std::string_view sigga_pattern, int offset)
{
    std::string pattern;
    std::string mask;

    static constexpr ctll::fixed_string byte_regex = "[0-9a-fA-F]{2}";
    static constexpr ctll::fixed_string wild_regex = "\\?+";

    for (const auto byte : std::ranges::split_view(sigga_pattern, ' '))
    {
        if (ctre::match<byte_regex>(byte))
        {
            unsigned int byte_value = std::stoi(std::string(byte.begin(), byte.end()), nullptr, 16);
            pattern.push_back(static_cast<char>(byte_value));
            mask.push_back('x');
        }
        else if (ctre::match<wild_regex>(byte))
        {
            pattern.push_back('\0');
            mask.push_back('?');
        }
        else
        {
            // TODO: debug log output
            return 0;
        }
    }

    return reinterpret_cast<void*>(GW::Scanner::Find(pattern.c_str(), mask.c_str(), offset));      // NOLINT(performance-no-int-to-ptr)
}
