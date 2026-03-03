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
 * Address:	80060AEC
 * Size:	148 bytes (0x94)
 */
void pppPObjPoint(PppPointData* pointData, PppObjData* objData, PppContainer* container)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    PppPointObj* objPtr = (PppPointObj*)((u8*)pointData + *(s32*)container->ptrData + 0x80);

    if (objData->id == pointData->id) {
        u32 vectorAddr;

        if ((objData->field_4 + 0x10000) == 0xFFFF) {
            vectorAddr = (u32)&lbl_801EADC8;
        } else {
            PObjPointEntry* table = *(PObjPointEntry**)((u8*)lbl_8032ED50 + 0xD4);
            vectorAddr = (u32)((u8*)objData->data + table[objData->field_4].vecOffset + 0x80);
        }

        objPtr->vecPtr = (void*)vectorAddr;
    }

    objPtr->x = ((f32*)objPtr->vecPtr)[0];
    objPtr->y = ((f32*)objPtr->vecPtr)[1];
    objPtr->z = ((f32*)objPtr->vecPtr)[2];
}
