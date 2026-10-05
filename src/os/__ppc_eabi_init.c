#include "dolphin/base/PPCArch.h"
#include "PowerPC_EABI_Support/Runtime/runtime.h"

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
