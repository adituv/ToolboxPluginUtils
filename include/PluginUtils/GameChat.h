#pragma once

#include <cstdint>

namespace PluginUtils::GameChat
{
    enum Color
    {
        COLOR_WHITE = 0xFFFFFF,
        COLOR_DEFAULT = COLOR_WHITE,
        COLOR_INFO = COLOR_WHITE,

        COLOR_RED = 0xFF4444,
        COLOR_ERROR = COLOR_RED,

        COLOR_YELLOW = 0xFFFF44,
        COLOR_WARNING = COLOR_YELLOW,

        COLOR_TEAL = 0x44CCCC,
        COLOR_DEBUG = COLOR_TEAL
    };

    void SetPrefix(const wchar_t* prefix);
    void WriteMessage(const wchar_t* message, uint32_t color = COLOR_DEFAULT, bool transient = false);
}
