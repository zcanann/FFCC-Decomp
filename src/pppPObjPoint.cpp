#include "ffcc/pppPObjPoint.h"
#include "dolphin/mtx.h"

// Structure definitions based on assembly analysis
struct PppObjData {
    u32 id;          // 0x0
    u32 field_4;     // 0x4
    void* data;      // 0x8
    u32 objId;       // 0xc
};

struct PppPointData {
    void* field_0;   // 0x0
    void* matrix;    // 0x4 - points to transformation matrix
    u32 field_8;     // 0x8
    u32 id;          // 0xc
    f32 field_10;    // 0x10
    f32 field_14;    // 0x14
    f32 field_18;    // 0x18
    f32 x;           // 0x1c
    f32 field_20;    // 0x20
    f32 field_24;    // 0x24
    f32 field_28;    // 0x28
    f32 y;           // 0x2c
    f32 field_30;    // 0x30
    f32 field_34;    // 0x34
    f32 field_38;    // 0x38
    f32 z;           // 0x3c
};

struct PppContainer {
    u32 field_0[3];  // 0x0-0x8
    void* ptrData;   // 0xc
};

struct PppPointObj {
    f32 x;           // 0x0
    f32 y;           // 0x4
    f32 z;           // 0x8
    u8 padding[4];   // 0xc
    void* vecPtr;    // 0x10
};

extern u32 lbl_8032ED70; // Global enable flag
extern void* lbl_8032ED50; // Global data structure

/*
 * --INFO--
 * Address:	80060A80
 * Size:	108 bytes (0x6C)
 */
static void pppParMatrix(PppPointData* pointData)
{
    Vec tempVec;
    void* matrix;
    
    // Load matrix pointer first (to match target instruction order)
    matrix = pointData->matrix;
    
    // Load vector from pointData
    tempVec.x = pointData->x;
    tempVec.y = pointData->y;
    tempVec.z = pointData->z;
    
    // Multiply with matrix (matrix + 0x10 offset)
    PSMTXMultVec(*((Mtx*)((u8*)matrix + 0x10)), &tempVec, &tempVec);
    
    // Store result back
    pointData->x = tempVec.x;
    pointData->y = tempVec.y;
    pointData->z = tempVec.z;
}

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