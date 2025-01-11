#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <wups.h>
#include <whb/log.h>
#include <coreinit/launch.h>
#include <sysapp/launch.h>

class PluginConfig {
public:
    static void PluginInit(void);
    static bool connected;
    static bool restart;
};

#endif // PLUGIN_HPP