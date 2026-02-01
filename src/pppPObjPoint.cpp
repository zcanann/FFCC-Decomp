#include "ffcc/pppPObjPoint.h"
#include "dolphin/mtx.h"

extern u32 lbl_8032ED70; // Global enable flag
extern void* lbl_8032ED50; // Global data structure

/*
 * --INFO--
 * Address:	80060AEC
 * Size:	148 bytes (0x94)
 */
void pppPObjPoint(PppPointData* pointData, PppObjData* objData, PppContainer* container)
{
    // Check global enable flag - return early if disabled
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Load container data and dereference
    void* containerData = container->ptrData;
    u32 objId = objData->id;
    u32 pointId = pointData->id;
    void* dataPtr = *(void**)containerData;
    
    // Compare IDs
    if (objId == pointId) {
        // IDs match - set up vector pointer
        void* vectorPtr;
        
        // Calculate base object pointer with 0x80 offset
        PppPointObj* objPtr = (PppPointObj*)((u8*)pointData + (u32)dataPtr + 0x80);
        
        // Check for special case (field_4 == 0xFFFF)  
        if ((objData->field_4 + 0x10000) == 0xFFFF) {
            // Use static/default vector pointer
            extern u32 lbl_801EADC8;
            vectorPtr = (void*)&lbl_801EADC8;
        } else {
            // Calculate dynamic vector pointer
            void* globalData = lbl_8032ED50;
            void* arrayPtr = *((void**)((u8*)globalData + 0xD4));
            u32 index = objData->field_4 << 4; // multiply by 16
            void* entry = (u8*)arrayPtr + index;
            void* basePtr = *((void**)((u8*)entry + 0x4));
            vectorPtr = (u8*)objData->data + (u32)basePtr + 0x80;
        }
        
        // Store vector pointer
        objPtr->vecPtr = vectorPtr;
    }
    
    // Always copy vector data (happens regardless of ID match)
    PppPointObj* objPtr = (PppPointObj*)((u8*)pointData + (u32)dataPtr + 0x80);
    f32* src = (f32*)objPtr->vecPtr;
    objPtr->x = src[0];
    objPtr->y = src[1]; 
    objPtr->z = src[2];
}
