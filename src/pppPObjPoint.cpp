#include "ffcc/pppPObjPoint.h"
#include "dolphin/mtx.h"

extern s32 lbl_8032ED70;
extern void* lbl_8032ED50;
extern u8 lbl_801EADC8[32];

typedef struct PObjPointEntry {
    u32 unk0;
    u32 vecOffset;
    u32 unk8;
    u32 unkC;
} PObjPointEntry;

/*
 * --INFO--
 * PAL Address: 0x80060AEC
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPObjPoint(PppPointData* pointData, PppObjData* objData, PppContainer* container)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    PppPointObj* objPtr = (PppPointObj*)((u8*)pointData + *(s32*)container->ptrData + 0x80);

    if (objData->id == pointData->id) {
        u8* vecPtr;

        if ((objData->field_4 + 0x10000) == 0xFFFF) {
            vecPtr = (u8*)lbl_801EADC8;
        } else {
            PObjPointEntry* table = *(PObjPointEntry**)((u8*)lbl_8032ED50 + 0xD4);
            vecPtr = (u8*)objData->data + 0x80;
            vecPtr += table[objData->field_4].vecOffset;
        }

        objPtr->vecPtr = vecPtr;
    }

    objPtr->x = ((f32*)objPtr->vecPtr)[0];
    objPtr->y = ((f32*)objPtr->vecPtr)[1];
    objPtr->z = ((f32*)objPtr->vecPtr)[2];
}
