#include <wups.h>
#include <whb/log.h>
#include <whb/log_udp.h>
#include <whb/log_cafe.h>

#include "utils.hpp"
#include "patchs/act.hpp"
#include "patchs/shop.hpp"
#include "patchs/ssl.hpp"

WUPS_PLUGIN_NAME("Nextendo Network Patcher");
WUPS_PLUGIN_DESCRIPTION("Nextendo Network Patcher");
WUPS_PLUGIN_VERSION("v1.0");
WUPS_PLUGIN_AUTHOR("cedkeChat01");
WUPS_PLUGIN_LICENSE("MIT");

WUPS_USE_STORAGE("Nextendo Patcher");

static bool patches = false;
static bool prevValue = false;

INITIALIZE_PLUGIN() {
    WHBLogUdpInit();
    WHBLogCafeInit();

    WUPSStorageError storageRes = WUPS_OpenStorage();
    if (storageRes != WUPS_STORAGE_ERROR_SUCCESS) {
        WHBLogPrintf("Failed to open storage %s (%d)", WUPS_GetStorageStatusStr(storageRes), storageRes);
    }
    else {
        if ((storageRes = WUPS_StoreBool(nullptr, "patches", &patches)) == WUPS_STORAGE_ERROR_NOT_FOUND) {
            if (WUPS_StoreBool(nullptr, "patches", patches) != WUPS_STORAGE_ERROR_SUCCESS) {
                WHBLogPrintf("Failed to store bool");
            }
        }
        else if (storageRes != WUPS_STORAGE_ERROR_SUCCESS) {
            WHBLogPrintf("Failed to get bool %s (%d)", WUPS_GetStorageStatusStr(storageRes), storageRes);
        }

        prevValue = patches;

        if (WUPS_CloseStorage() != WUPS_STORAGE_ERROR_SUCCESS) {
            WHBLogPrintf("Failed to close storage");
        }
    }

    if (patches) {
        PatchAct();
        PatchShop();
        PatchSSL();
        WHBLogPrintf("Patches applying successfully!");
    } else {
        WHBLogPrintf("Patches removing successfully!");
    }
}

DEINITIALIZE_PLUGIN() {
    WHBLogUdpDeinit();
    WHBLogCafeDeinit();
}

ON_APPLICATION_START() {
    WHBLogUdpInit();
    WHBLogPrintf("Patcher starting..");
}

ON_APPLICATION_ENDS() {
    WHBLogPrintf("Patcher ending..");
}