#include <dolphin.h>
#include <dolphin/os.h>

#include "dolphin/os/__os.h"

// prototypes
void __OSSystemCallVectorStart(void);
void __OSSystemCallVectorEnd(void);

/*
 * --INFO--
 * PAL Address: 0x80180970
 * PAL Size: 32b
 * EN Address: 0x8017F854
 * EN Size: 32b
 * JP Address: 0x8017AF00
 * JP Size: 32b
 */
static asm void SystemCallVector(void) {
entry __OSSystemCallVectorStart
    nofralloc
    mfspr r9, HID0
    ori r10, r9, 0x8
    mtspr HID0, r10
    isync
    sync
    mtspr HID0, r9
    rfi
entry __OSSystemCallVectorEnd
    nop
}

void __OSInitSystemCall(void) {
    void* addr = (void*)OSPhysicalToCached(0xC00);

    memcpy(addr, __OSSystemCallVectorStart, (u32)__OSSystemCallVectorEnd - (u32)__OSSystemCallVectorStart);
    DCFlushRangeNoSync(addr, 0x100);
    __sync();
    ICInvalidateRange(addr, 0x100);
}
