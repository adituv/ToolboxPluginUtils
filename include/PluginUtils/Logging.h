#pragma once

#include <filesystem>
#include <string_view>

namespace PluginUtils::Logging
{
    enum LogLevel
    {
        LEVEL_DEBUG,
        LEVEL_INFO,
        LEVEL_WARNING,
        LEVEL_ERROR,
        LEVEL_NONE
    };

    void ConfigureChatLogging(LogLevel minLevel);
    void ConfigureFileLogging(std::filesystem::path filePath, LogLevel minLevel);
    void ConfigureStdioLogging(LogLevel minLevel);

    void Debug(std::wstring_view message);
    void Info(std::wstring_view message);
    void Warning(std::wstring_view message);
    void Error(std::wstring_view message);
}
