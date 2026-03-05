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
        u32 tableIndex = objData->field_4;
        u8* vecPtr;

        if ((tableIndex + 0x10000) == 0xFFFF) {
            vecPtr = lbl_801EADC8;
        } else {
            PObjPointEntry* table = *(PObjPointEntry**)((u8*)lbl_8032ED50 + 0xD4);
            u8* baseVecPtr = (u8*)objData->data + 0x80;
            vecPtr = baseVecPtr + table[tableIndex].vecOffset;
        }

        objPtr->vecPtr = vecPtr;
    }

    Vec* vec = (Vec*)objPtr->vecPtr;
    objPtr->x = vec->x;
    vec = (Vec*)objPtr->vecPtr;
    objPtr->y = vec->y;
    vec = (Vec*)objPtr->vecPtr;
    objPtr->z = vec->z;
}
