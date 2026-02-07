#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/MWCriticalSection_gc.h"

/*
 * --INFO--
 * PAL Address: 0x801C9C6C
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void MWExitCriticalSection(u32* section) {
    OSRestoreInterrupts(*section);
}

/*
 * --INFO--
 * PAL Address: 0x801C9C90
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void MWEnterCriticalSection(u32* section) {
    *section = OSDisableInterrupts();
}

/*
 * --INFO--
 * PAL Address: 0x801C9CC0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void MWInitializeCriticalSection(u32* section) {
    (void)section;
}
