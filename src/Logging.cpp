#include "PluginUtils/Logging.h"

#include <fstream>
#include <iostream>

#include "PluginUtils/GameChat.h"

namespace
{
    using namespace PluginUtils;
    using namespace PluginUtils::Logging;
    
    LogLevel g_stdioLevel = LEVEL_INFO;
    LogLevel g_chatLevel = LEVEL_WARNING;
    LogLevel g_fileLevel = LEVEL_NONE;
    
    std::wofstream g_logFile;
    
    GameChat::Color GetColorForLogLevel(LogLevel level)
    {
        switch (level)
        {
        case LEVEL_DEBUG:
            return GameChat::COLOR_DEBUG;
        case LEVEL_WARNING:
            return GameChat::COLOR_WARNING;
        case LEVEL_ERROR:
            return GameChat::COLOR_ERROR;
        case LEVEL_INFO:
        case LEVEL_NONE:
            return GameChat::COLOR_INFO;
        }
        
        return GameChat::COLOR_INFO;
    }   
    
    void Log(LogLevel level, std::wstring_view message)
    {
        if (level >= g_stdioLevel)
        {
            std::wcerr << message.data() << std::endl;
        }
        if (level >= g_chatLevel)
        {
            GameChat::WriteMessage(message, GetColorForLogLevel(level), true);
        }
        if (level >= g_fileLevel && g_logFile.is_open() && g_logFile.good())
        {
            g_logFile << message.data() << std::endl;
        }
    }
}

namespace PluginUtils::Logging
{
    void ConfigureChatLogging(LogLevel minLevel)
    {
        g_chatLevel = minLevel;
    }
    void ConfigureFileLogging(std::filesystem::path filePath, LogLevel minLevel)
    {
        g_logFile.open(filePath, std::ios::app);
        g_fileLevel = minLevel;
    }
    void ConfigureStdioLogging(LogLevel minLevel)
    {
        g_stdioLevel = minLevel;
    }
    
    void Debug(std::wstring_view message)
    {
        Log(LEVEL_DEBUG, message);
    }
    void Info(std::wstring_view message)
    {
        Log(LEVEL_INFO, message);
    }
    void Warning(std::wstring_view message)
    {
        Log(LEVEL_WARNING, message);
    }
    void Error(std::wstring_view message)
    {
        Log(LEVEL_ERROR, message);
    }
}
