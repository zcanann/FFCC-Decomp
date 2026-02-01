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
    // Match target assembly order: load data2 pointer, then global flag
    void* data2ObjPtr = data2->ptrData;
    
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Load data pointers following target pattern
    void* data1ObjPtr = data1->ptrData;
    u32 inputId = *(u32*)input;
    u32 baseId = *((u32*)((u8*)basePtr + 0xc));
    u32 data1Offset = *((u32*)data1ObjPtr);
    u32 data2Offset = *((u32*)data2ObjPtr);
    
    // Calculate object pointers with +0x80
    data1Offset += 0x80;
    data2Offset += 0x80;
    PppMoveObj* obj1 = (PppMoveObj*)((u8*)basePtr + data1Offset);
    PppMoveObj* obj2 = (PppMoveObj*)((u8*)basePtr + data2Offset);
    
    // Conditional input addition to obj2
    if (inputId == baseId) {
        obj2->x += input->x;
        obj2->y += input->y;
        obj2->z += input->z;
    }
    
    // Always add obj2 to obj1
    obj1->x += obj2->x;
    obj1->y += obj2->y;
    obj1->z += obj2->z;
}