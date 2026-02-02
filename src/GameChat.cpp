#include "PluginUtils/GameChat.h"

// GWCA whyyy
#include <Windows.h>

#include <GWCA/Managers/ChatMgr.h>
#include <GWCA/Managers/GameThreadMgr.h>

#include <format>
#include <string>

namespace
{
    const wchar_t* g_chatPrefix = L"PLUGIN";
}

namespace PluginUtils::GameChat
{    
    void SetPrefix(const wchar_t* prefix)
    {
        g_chatPrefix = prefix;
    }
    
    void WriteMessage(const wchar_t* message, uint32_t color, bool transient)
    {
        std::wstring formatted_message = std::format(L"<a=1>{}</a><c=#{:06x}>: {}</c>", g_chatPrefix, color, message);
        GW::GameThread::Enqueue([formatted_message, transient]()
        {
            GW::Chat::WriteChat(GW::Chat::Channel::CHANNEL_GWCA2, formatted_message.c_str(), nullptr, transient);
        });
    }

    void WriteMessage(const std::wstring& message, uint32_t color, bool transient)
    {
        WriteMessage(message.c_str(), color, transient);
    }
}
