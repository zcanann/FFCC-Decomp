#include "ffcc/pppMove.h"

extern u32 lbl_8032ED70;   // Global enable flag
extern f32 lbl_8032FED8;   // Zero constant

struct PppMoveObj {
    f32 x;           // 0x0
    f32 y;           // 0x4
    f32 z;           // 0x8
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
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    u32 inputId = *(u32*)input;
    u32 baseId = *((u32*)((u8*)basePtr + 0xc));
    
    u32 data1Offset = *((u32*)data1->ptrData);
    u32 data2Offset = *((u32*)data2->ptrData);
    
    // Match target: add offset directly then add basePtr
    f32* data1Obj = (f32*)((u8*)basePtr + data1Offset + 0x80);
    f32* data2Obj = (f32*)((u8*)basePtr + data2Offset + 0x80);
    
    if (inputId == baseId) {
        data2Obj[0] += input->x;
        data2Obj[1] += input->y;  
        data2Obj[2] += input->z;
    }
    
    data1Obj[0] += data2Obj[0];
    data1Obj[1] += data2Obj[1];
    data1Obj[2] += data2Obj[2];
}