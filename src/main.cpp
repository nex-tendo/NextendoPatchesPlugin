#include <wups.h>
#include <whb/log.h>
#include <whb/log_udp.h>
#include <whb/log_cafe.h>

#include "utils.hpp"
#include "plugin.hpp"
#include "version.h"
#include "patchs/act.hpp"
#include "patchs/shop.hpp"
#include "patchs/ssl.hpp"

WUPS_PLUGIN_NAME(PATCHER_NAME);
WUPS_PLUGIN_DESCRIPTION(PATCHER_DESCRIPTION);
WUPS_PLUGIN_VERSION(PATCHER_VERSION);
WUPS_PLUGIN_AUTHOR(PATCHER_AUTHOR);
WUPS_PLUGIN_LICENSE(PATCHER_LICENSE);

WUPS_USE_WUT_DEVOPTAB();
WUPS_USE_STORAGE(PATCHER_LICENSE);

INITIALIZE_PLUGIN() {
    WHBLogUdpInit();
    WHBLogCafeInit();
    Mocha_InitLibrary();

    PluginConfig::PluginInit();

    if (PluginConfig::connected) {
        PatchAct();
        PatchShop();
        PatchSSL();
        WHBLogPrintf("Patches applying successfully!");
    } else {
        WHBLogPrintf("Patches unapplying successfully!");
    }
}

DEINITIALIZE_PLUGIN() {
    WHBLogUdpDeinit();
    WHBLogCafeDeinit();
    Mocha_DeInitLibrary();
}

ON_APPLICATION_START() {
    WHBLogUdpInit();
    WHBLogPrintf("Nextendo Patcher starting..");
}

ON_APPLICATION_ENDS() {
    WHBLogPrintf("Nextendo Patcher ending..");
}