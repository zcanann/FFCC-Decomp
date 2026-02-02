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
extern void MWExitCriticalSection(u32* param_1)
{
    OSRestoreInterrupts(*param_1);
    return;
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
extern void MWEnterCriticalSection(u32* param_1)
{
    u32 uVar1;
    
    uVar1 = OSDisableInterrupts();
    *param_1 = uVar1;
    return;
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
extern void MWInitializeCriticalSection(void)
{
    return;
}