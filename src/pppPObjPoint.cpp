#include "ffcc/pppPObjPoint.h"
#include "dolphin/mtx.h"

extern s32 lbl_8032ED70;
extern void* lbl_8032ED50;

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

    u8* pointBase = (u8*)pointData;
    s32 pointOffset = *(s32*)container->ptrData;
    PppPointObj* objPtr = (PppPointObj*)(pointBase + pointOffset + 0x80);

    if (objData->id == pointData->id) {
        void* vectorPtr;

        if ((objData->field_4 + 0x10000) == 0xFFFF) {
            extern u32 lbl_801EADC8;
            vectorPtr = (void*)&lbl_801EADC8;
        } else {
            void* arrayPtr = *(void**)((u8*)lbl_8032ED50 + 0xD4);
            u32 index = objData->field_4 << 4;
            u32 baseOffset = *(u32*)((u8*)arrayPtr + index + 4);
            vectorPtr = (u8*)objData->data + baseOffset + 0x80;
        }

        objPtr->vecPtr = vectorPtr;
    }

    f32* src = (f32*)objPtr->vecPtr;
    objPtr->x = src[0];
    objPtr->y = src[1];
    objPtr->z = src[2];
}
