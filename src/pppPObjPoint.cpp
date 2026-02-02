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
    
    void* containerData = container->ptrData;
    s32 objId = objData->id;
    s32 pointId = pointData->id;  
    void* dataPtr = *(void**)containerData;
    
    if (objId == pointId) {
        void* vectorPtr;
        
        if ((objData->field_4 + 0x10000) == 0xFFFF) {
            extern u32 lbl_801EADC8;
            vectorPtr = (void*)&lbl_801EADC8;
        } else {
            void* globalData = lbl_8032ED50;
            void* arrayPtr = *((void**)((u8*)globalData + 0xD4));
            u32 index = objData->field_4 << 4;
            void* entry = (u8*)arrayPtr + index;
            void* basePtr = *((void**)((u8*)entry + 0x4));
            vectorPtr = (u8*)objData->data + (u32)basePtr + 0x80;
        }
        
        PppPointObj* objPtr = (PppPointObj*)((u8*)pointData + (u32)dataPtr + 0x80);
        objPtr->vecPtr = vectorPtr;
    }
    
    PppPointObj* objPtr = (PppPointObj*)((u8*)pointData + (u32)dataPtr + 0x80);
    f32* src = (f32*)objPtr->vecPtr;
    objPtr->x = src[0];
    objPtr->y = src[1]; 
    objPtr->z = src[2];
}
