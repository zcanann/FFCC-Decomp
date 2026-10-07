#include "global.h"

#include <dolphin/os.h>
#include "dolphin/base/PPCArch.h"
#include "PowerPC_EABI_Support/Runtime/runtime.h"

extern "C" {
/*
 * --INFO--
 * PAL Address: 0x80003400
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
SECTION_INIT asm void __init_hardware(void)
{
    // clang-format off
    nofralloc

    mfmsr r0
    ori r0, r0, 0x2000
    mtmsr r0
    mflr r31
    bl __OSPSInit
    bl __OSFPRInit
    bl __OSCacheInit
    mtlr r31
    blr
    // clang-format on
}

/*
 * --INFO--
 * PAL Address: 0x80003424
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
SECTION_INIT asm void __flush_cache(void* addr, unsigned int size)
{
    // clang-format off
    nofralloc

    lis r5, 0xFFFF
    ori r5, r5, 0xFFF1
    and r5, r5, r3
    subf r3, r5, r3
    add r4, r4, r3

lbl_80003438:
    dcbst 0, r5
    sync
    icbi 0, r5
    addic r5, r5, 8
    addic. r4, r4, -8
    bge lbl_80003438

    isync
    blr
    // clang-format on
}

static void __init_cpp(void);

/*
 * --INFO--
 * PAL Address: 0x8018201C
 * PAL Size: 32b
 * EN Address: 0x80180F00
 * EN Size: 32b
 * JP Address: 0x8017C5B0
 * JP Size: 32b
 */
void __init_user(void) {
    __init_cpp();
}

/*
 * --INFO--
 * PAL Address: 0x8018203C
 * PAL Size: 84b
 * EN Address: 0x80180F20
 * EN Size: 84b
 * JP Address: 0x8017C5D0
 * JP Size: 84b
 */
static void __init_cpp(void) {
    voidfunctionptr* constructor;

    for (constructor = _ctors; *constructor != 0; constructor++) {
        (*constructor)();
    }
}

/*
 * --INFO--
 * PAL Address: 0x80182090
 * PAL Size: 32b
 * EN Address: 0x80180F74
 * EN Size: 32b
 * JP Address: 0x8017C624
 * JP Size: 32b
 */
void _ExitProcess(void) {
    PPCHalt();
}

}
