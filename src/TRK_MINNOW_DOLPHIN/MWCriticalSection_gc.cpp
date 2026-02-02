#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/MWCriticalSection_gc.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
extern void MWExitCriticalSection(u32* section)
{
    OSRestoreInterrupts(*section);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
extern void MWEnterCriticalSection(u32* section)
{
    u32 uVar1;
    
    uVar1 = OSDisableInterrupts();
    *section = uVar1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
extern void MWInitializeCriticalSection(void)
{
    
}