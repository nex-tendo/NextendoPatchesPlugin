#include "ssl.hpp"

static bool is555Ver(const MCPSystemVersion& version) {
    return (version.major == 5) && (version.minor == 5) && (version.patch >= 5);
}

void PatchSSL() {
    MCPSystemVersion os_version;

    int mcp_handle = MCP_Open();
    if (mcp_handle < 0) {
        return;
    }

    int ret = MCP_GetSystemVersion(mcp_handle, &os_version);
    if (ret < 0) {
        os_version.major = 5;
        os_version.minor = 5;
        os_version.patch = 5;
        os_version.region = 'E';
    }

    if (is555Ver(os_version)) {
        Mocha_IOSUKernelWrite32(0xE1019F78, 0xE3A00001);
    } else {
        Mocha_IOSUKernelWrite32(0xE1019E84, 0xE3A00001);
    }

    WHBLogPrintf("NoSSL Patch applied successfully!");

    MCP_Close(mcp_handle);
}