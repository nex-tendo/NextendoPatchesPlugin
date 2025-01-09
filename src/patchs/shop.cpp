#include "shop.hpp"

void PatchShop()
{
    write_string(0xe22830a0, NEW_ECS_SHOP_URL);
    write_string(0xe22B3ef8, NEW_ECS_C_SHOP_URL);
    WHBLogPrintf("SHOP Patch applied successfully!");
}