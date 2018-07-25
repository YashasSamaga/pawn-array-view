#include "main.h"

#include <sdk/amx/amx.h>
#include <sdk/plugincommon.h>
#include <pawn/array_view.hpp>

#include "natives/tests.hpp"

extern void *pAMXFunctions;
logprintf_t logprintf;

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
    logprintf("*** PAWN Library Extension v%d.%d.%d unloaded ***", PLUGIN_MAJOR_VERSION, PLUGIN_MINOR_VERSION, PLUGIN_PATCH_VERSION);
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
    static const AMX_NATIVE_INFO natives[] =
    {
        {"test_cell_0", sample::natives::test_cell_0 },
        {"test_cell_256", sample::natives::test_cell_256 },
        {"test_cell_0_0", sample::natives::test_cell_0_0 },
        {"test_cell_0_128", sample::natives::test_cell_0_128 },
        {"test_cell_256_128", sample::natives::test_cell_256_128 },
        {"test_cell_64_0", sample::natives::test_cell_64_0 },
        {"test_cell_0_0_0", sample::natives::test_cell_0_0_0 },
        {"test_cell_0_0_128", sample::natives::test_cell_0_0_128 },
        {"test_cell_0_128_0", sample::natives::test_cell_0_128_0 },
        {"test_cell_0_64_96", sample::natives::test_cell_0_64_96 },
        {"test_cell_16_0_0", sample::natives::test_cell_16_0_0 },
        {"test_cell_16_0_48", sample::natives::test_cell_16_0_48 },
        {"test_cell_20_30_50", sample::natives::test_cell_20_30_50 },
        {0, 0}
    };
    return amx_Register(amx, natives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
    return AMX_ERR_NONE;
}

