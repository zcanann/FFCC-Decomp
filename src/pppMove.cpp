#include "ffcc/pppMove.h"
#include "ffcc/partMng.h"
#include "ffcc/symbols_shared.h"

extern int gPppCalcDisabled;   // Global enable flag

struct PppMoveObj {
    f32 x;           // 0x0
    f32 y;           // 0x4
    f32 z;           // 0x8
};

struct PppMoveOffsets {
    u32 a;           // 0x0
    u32 b;           // 0x4
};

/*
 * --INFO--
 * PAL Address: 0x80065b18
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void pppMoveCon(void* basePtr, _pppCtrlTable* ctrlTable)
{
    u32 offset = static_cast<u32>(ctrlTable->m_serializedDef->m_workOffsetAlt);
    PppMoveObj* moveObj = (PppMoveObj*)((u8*)basePtr + offset + 0x80);
    
    // Initialize to zero (store order: z, y, x to match assembly)
    f32 zero = kPppMoveZero;
    moveObj->z = zero;
    moveObj->y = zero;
    moveObj->x = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80065b3c
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO  
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMove(void* basePtr, PppMoveInput* input, _pppCtrlTable* ctrlTable)
{
    PppMoveOffsets* offsets = (PppMoveOffsets*)ctrlTable->m_serializedDef;
    PppMoveObj* a = (PppMoveObj*)((u8*)basePtr + offsets->a + 0x80);
    PppMoveObj* b = (PppMoveObj*)((u8*)basePtr + offsets->b + 0x80);

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 inputId = *(s32*)input;
    s32 baseId = *(s32*)((u8*)basePtr + 0xc);

    if (inputId == baseId) {
        b->x += input->x;
        b->y += input->y;
        b->z += input->z;
    }

    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
}
