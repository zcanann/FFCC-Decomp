#include "PowerPC_EABI_Support/Runtime/ptmf.h"

const __ptmf __ptmf_null = {0, 0, {0}};

/*
 * --INFO--
 * PAL Address: 0x801AFEEC
 * PAL Size: 48b
 * EN Address: 0x801AEDCC
 * EN Size: 48b
 * JP Address: 0x801AB3F4
 * JP Size: 48b
 */
asm long __ptmf_test(register __ptmf* ptmf) {
    // clang-format off
    nofralloc

    lwz r5, __ptmf.this_delta(r3)
    lwz r6, __ptmf.v_offset(r3)
    lwz r7, __ptmf.f_data(r3)
    li r3, 1
    cmpwi r5, 0
    cmpwi cr6, r6, 0
    cmpwi cr7, r7, 0
    bnelr 
    bnelr cr6
    bnelr cr7
    li r3, 0
    blr
    // clang-format on
}

/*
 * --INFO--
 * PAL Address: 0x801AFF1C
 * PAL Size: 40b
 * EN Address: 0x801AEDFC
 * EN Size: 40b
 * JP Address: 0x801AB424
 * JP Size: 40b
 */
asm void __ptmf_scall(...) {
    // clang-format off
    nofralloc

    lwz r0, 0(r12)
    lwz r11, 4(r12)
    lwz r12, 8(r12)
    add r3, r3, r0
    cmpwi r11, 0
    blt call_member

    lwzx r12, r3, r12
    lwzx r12, r12, r11

call_member:
    mtctr r12
    bctr
    // clang-format on
}
