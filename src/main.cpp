#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <wups.h>
#include <optional>
#include <nsysnet/nssl.h>
#include <sysapp/title.h>
#include <coreinit/cache.h>
#include <coreinit/dynload.h>
#include <coreinit/mcp.h>
#include <coreinit/memory.h>
#include <coreinit/memorymap.h>
#include <coreinit/memexpheap.h>
#include <coreinit/title.h>
#include <coreinit/filesystem.h>
#include <whb/log.h>
#include <whb/log_udp.h>
#include <whb/log_cafe.h>
#include <nn/erreula/erreula_cpp.h>
#include <nn/act/client_cpp.h>
#include <gx2/surface.h>
#include <kernel/kernel.h>
#include <function_patcher/function_patching.h>
#include "utils.hpp"
#include "plugin.hpp"
#include "patchs/act.hpp"
#include "ca_pem.h"

WUPS_PLUGIN_NAME(PATCHER_NAME);
WUPS_PLUGIN_DESCRIPTION(PATCHER_DESCRIPTION);
WUPS_PLUGIN_VERSION(PATCHER_VERSION);
WUPS_PLUGIN_AUTHOR(PATCHER_AUTHOR);
WUPS_PLUGIN_LICENSE(PATCHER_LICENSE);
WUPS_USE_STORAGE(PATCHER_LICENSE);
WUPS_USE_WUT_DEVOPTAB();

static bool is555(MCPSystemVersion version) {
    return (version.major == 5) && (version.minor == 5) && (version.patch >= 5);
}

INITIALIZE_PLUGIN() {
    WHBLogCafeInit();
    WHBLogUdpInit();

    auto res = Mocha_InitLibrary();
    if (res != MOCHA_RESULT_SUCCESS) {
        return;
    }

    MCPSystemVersion os_version;
    int mcp = MCP_Open();
    int ret = MCP_GetSystemVersion(mcp, &os_version);
    if (ret < 0) {
        os_version = (MCPSystemVersion) {
                .major = 5, .minor = 5, .patch = 5, .region = 'E'
        };
    }

    if (is555(os_version)) {
        Mocha_IOSUKernelWrite32(0xE1019F78, 0xE3A00001);
    } else {
        Mocha_IOSUKernelWrite32(0xE1019E84, 0xE3A00001);
    }

    PatchAct(); // Nextendo Account Patchs

    MCP_Close(mcp);
}

DEINITIALIZE_PLUGIN() {
    Mocha_DeInitLibrary();
    FunctionPatcher_DeInitLibrary();
    WHBLogCafeDeinit();
    WHBLogUdpDeinit();
}

ON_APPLICATION_START() {
    
}

ON_APPLICATION_ENDS() {

}
