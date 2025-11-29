#include "TRK_MINNOW_DOLPHIN/MWCriticalSection_gc.h"

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
    *section = OSDisableInterrupts();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
extern void MWInitializeCriticalSection(u32*)
{
	
}