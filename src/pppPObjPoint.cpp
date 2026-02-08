#include "ffcc/pppPObjPoint.h"
#include "dolphin/mtx.h"

extern s32 lbl_8032ED70;
extern void* lbl_8032ED50;
extern u8 lbl_801EADC8[32];

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
            u32 index = (objData->field_4 << 4) + 4;
            u32 tableAddr = *(u32*)((u8*)lbl_8032ED50 + 0xD4);
            vectorAddr = (u32)objData->data + *(u32*)(tableAddr + index) + 0x80;
        }

        objPtr->vecPtr = (void*)vectorAddr;
    }

    objPtr->x = ((f32*)objPtr->vecPtr)[0];
    objPtr->y = ((f32*)objPtr->vecPtr)[1];
    objPtr->z = ((f32*)objPtr->vecPtr)[2];
}
