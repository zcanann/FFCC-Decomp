#include "dolphin/base/PPCArch.h"

typedef void (*voidfunctionptr)(void);

extern voidfunctionptr _ctors[];

void __init_cpp(void);

/*
 * --INFO--
 * PAL Address: 0x8018201C
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __init_user(void) {
    __init_cpp();
}

/*
 * --INFO--
 * PAL Address: 0x8018203C
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma peephole off
void __init_cpp(void) {
    voidfunctionptr* constructor;

    for (constructor = _ctors; *constructor != 0; constructor++) {
        (*constructor)();
    }
}
#pragma peephole reset

/*
 * --INFO--
 * PAL Address: 0x80182090
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void _ExitProcess(void) {
    PPCHalt();
}
