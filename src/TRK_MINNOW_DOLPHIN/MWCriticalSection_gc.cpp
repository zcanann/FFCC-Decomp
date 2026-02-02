#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/MWCriticalSection_gc.h"

/*
 * --INFO--
 * PAL Address: 0x801af64c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void MWExitCriticalSection(u32* section)
{
    OSRestoreInterrupts(*section);
}

/*
 * --INFO--
 * PAL Address: 0x801af670
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void MWEnterCriticalSection(u32* section)
{
    *section = OSDisableInterrupts();
}

/*
 * --INFO--
 * PAL Address: 0x801af6a0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void MWInitializeCriticalSection(void)
{
}