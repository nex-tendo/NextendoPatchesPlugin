#include <wups.h>
#include <whb/log.h>
#include <whb/log_udp.h>
#include <whb/log_cafe.h>

#include "utils.hpp"
#include "patchs/act.hpp"
#include "patchs/shop.hpp"

WUPS_PLUGIN_NAME("Nextendo Network Patcher");
WUPS_PLUGIN_DESCRIPTION("Nextendo Network Patcher");
WUPS_PLUGIN_VERSION("v1.0");
WUPS_PLUGIN_AUTHOR("cedkeChat01");
WUPS_PLUGIN_LICENSE("MIT");

INITIALIZE_PLUGIN() {
    WHBLogUdpInit();
    WHBLogCafeInit();

    PatchAct();
    PatchShop();
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