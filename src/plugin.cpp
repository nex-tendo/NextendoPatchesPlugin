/* 
    I used the example plugin from 
    https://github.com/wiiu-env/WiiUPluginSystem/blob/main/plugins/example_plugin_cpp/src/main.cpp#L198
*/

#include "plugin.hpp"

bool PluginConfig::connected = true;
bool PluginConfig::restart = false;

WUPSConfigAPICallbackStatus ConfigMenuOpenedCallback(WUPSConfigCategoryHandle rootHandle) {
    WUPSConfigCategory root = WUPSConfigCategory(rootHandle);

    // TODO: Add Menu

    return WUPSCONFIG_API_CALLBACK_RESULT_SUCCESS;
}

static void ConfigMenuClosedCallback()
{
    // Save the storage
    WUPSStorageAPI::SaveStorage();

    if (PluginConfig::restart) {
        SYSLaunchMenu();
        PluginConfig::restart = false;
    }
}

// I used the example config init from Inkay
void PluginConfig::PluginInit() 
{
    WUPSConfigAPIOptionsV1 configOptions = { .name = "Nextendo Patcher Plugin" };
    if (WUPSConfigAPI_Init(configOptions, ConfigMenuOpenedCallback, ConfigMenuClosedCallback) != WUPSCONFIG_API_RESULT_SUCCESS) {
        WHBLogPrintf("Error to initialize the WUPS Config API");
        return;
    }

    WUPSStorageError storageRes;
    if ((storageRes = WUPSStorageAPI::Get<bool>("connected", PluginConfig::connected)) == WUPS_STORAGE_ERROR_NOT_FOUND) {
        WHBLogPrintf("Connect value not found.");

        bool skipPatches = false;
        if (WUPSStorageAPI::Get<bool>("skipPatches", skipPatches) == WUPS_STORAGE_ERROR_SUCCESS) {
            PluginConfig::connected = !skipPatches;
            WUPSStorageAPI::DeleteItem("skipPatches");
        }
    
        if (WUPSStorageAPI::Store<bool>("connected", connected) != WUPS_STORAGE_ERROR_SUCCESS) {
            WHBLogPrintf("Error to store the bool");
        }
    }
    else if (storageRes != WUPS_STORAGE_ERROR_SUCCESS) {
        WHBLogPrintf("Error to get the bool %s (%d)", WUPSStorageAPI_GetStatusStr(storageRes), storageRes);
    }

    // Save the storage
    WUPSStorageAPI::SaveStorage();
}