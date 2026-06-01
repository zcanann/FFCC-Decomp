#include "ffcc/pppMove.h"
#include "ffcc/partMng.h"
extern "C" {
extern const float kPppMoveZero;
}


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
void pppMoveCon(_pppPObject* basePtr, _pppCtrlTable* ctrlTable)
{
    u32 offset = static_cast<u32>(ctrlTable->m_serializedDataOffsets[1]);
    PppMoveObj* moveObj = (PppMoveObj*)(basePtr->m_workArea + offset);
    
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
void pppMove(_pppPObject* basePtr, PppMoveInput* input, _pppCtrlTable* ctrlTable)
{
    PppMoveOffsets* offsets = (PppMoveOffsets*)ctrlTable->m_serializedDataOffsets;
    PppMoveObj* a = (PppMoveObj*)(basePtr->m_workArea + offsets->a);
    PppMoveObj* b = (PppMoveObj*)(basePtr->m_workArea + offsets->b);

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 inputId = *(s32*)input;
    s32 baseId = basePtr->m_graphId;

    if (inputId == baseId) {
        b->x += input->x;
        b->y += input->y;
        b->z += input->z;
    }

    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
}
