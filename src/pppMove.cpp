#include "ffcc/pppMove.h"

extern s32 lbl_8032ED70;   // Global enable flag
extern f32 lbl_8032FED8;   // Zero constant

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
void pppMoveCon(void* basePtr, PppMoveData* data)
{
    // Get object pointer from data structure
    void* objPtr = data->ptrData;
    u32 offset = *((u32*)((u8*)objPtr + 0x4));
    PppMoveObj* moveObj = (PppMoveObj*)((u8*)basePtr + offset + 0x80);
    
    // Initialize to zero (store order: z, y, x to match assembly)
    f32 zero = lbl_8032FED8;
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
void pppMove(void* basePtr, PppMoveInput* input, PppMoveData* data1, PppMoveData* data2)
{
    PppMoveOffsets* offsets = (PppMoveOffsets*)data1->ptrData;
    PppMoveObj* a = (PppMoveObj*)((u8*)basePtr + offsets->a + 0x80);
    PppMoveObj* b = (PppMoveObj*)((u8*)basePtr + offsets->b + 0x80);

    (void)data2;

    if (lbl_8032ED70 != 0) {
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
