#include "act.hpp"

void PatchAct() 
{
    write_string(0xe31930d4, NEW_ACT_URL);
    WHBLogPrintf("ACT Patch applied successfully!");
}
