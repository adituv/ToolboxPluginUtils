#include "PluginUtils/PluginUtils.h"

#include <Shlobj.h>
#include <Windows.h>

#include <filesystem>

namespace PluginUtils::Environment
{
    std::filesystem::path GetComputerName()
    {
        wchar_t buf[MAX_COMPUTERNAME_LENGTH + 1];
        DWORD written = MAX_COMPUTERNAME_LENGTH + 1;
        if (!GetComputerNameW(buf, &written))
        {
            Logging::Error(std::format(L"GetComputerName: Cannot get computer name. ({})", GetLastError()));
            return L"";
        }
        if (buf[0] == L'\0')
        {
            Logging::Error(L"GetComputerName: No computer name.");
            return L"";
        }
        
        return {buf};
    }

    std::filesystem::path GetDocumentsPath()
    {
        wchar_t buf[MAX_PATH];
        HRESULT result = SHGetFolderPathW(nullptr, CSIDL_MYDOCUMENTS, nullptr, 0, buf);
        if (FAILED(result))
        {
            Logging::Error(std::format(L"GetDocumentsPath: SHGetFolderPathW failed. ({})", GetLastError()));
            return L"";
        }
        if (buf[0] == L'\0')
        {
            Logging::Error(L"GetDocumentsPath: SHGetFolderPathW returned empty path.");
            return L"";
        }
        return {buf};
    }
    
    std::filesystem::path GetToolboxSettingsPath()
    {
        std::filesystem::path computer_name = GetComputerName();
        std::filesystem::path docpath = GetDocumentsPath();
        
        if (computer_name.empty() || docpath.empty())
        {
            Logging::Error(L"GetToolboxSettingsPath: Failed to get Toolbox path.");
            return L"";
        }

        return docpath / L"GWToolboxpp" / computer_name;
    }
}
