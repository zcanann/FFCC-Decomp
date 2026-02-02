#include "ffcc/pppConformBGNormal.h"
#include "types.h"
#include "dolphin/mtx.h"

/*
 * --INFO--
 * PAL Address: 0x801097e4
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructConformBGNormal(void* basePtr, void* dataPtr)
{
    // Get offset from data pointer (at offset 0xc from dataPtr base)
    u32 offset = *(u32*)((u8*)dataPtr + 0xc);
    u32 actualOffset = *(u32*)offset; // Dereference to get actual offset
    
    // Calculate target pointer with base offset
    f32* targetPtr = (f32*)((u8*)basePtr + actualOffset + 0x80);
    
    // Initialize three floats to 0.0f (order: z, y, x to match assembly)
    f32 zero = 0.0f;
    targetPtr[2] = zero;  // z at offset 0x8
    targetPtr[1] = zero;  // y at offset 0x4  
    targetPtr[0] = zero;  // x at offset 0x0
    
    // Initialize byte flag to 0
    *(u8*)(targetPtr + 3) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801091d4
 * PAL Size: 1552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameConformBGNormal(void* basePtr, void* stepData, void* offsetData)
{
    // Early exit if global disable flag is set
    extern u32 lbl_8032ED70;
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Get step value from input data
    u8 stepValue = *(u8*)stepData;
    
    // Get offset and calculate data pointer
    u32 offset = *(u32*)offsetData;
    void* dataPtr = (u8*)basePtr + offset + 0x80;
    
    // Initialize normal vector from stored data or defaults
    Vec normal;
    
    // Check if this is the first frame (initialization flag)
    u8* initFlag = (u8*)dataPtr + 0xc;
    if (*initFlag == 0) {
        *initFlag = 1;
        
        // Set default normal vector
        normal.x = 0.0f;
        normal.y = 1.0f;
        normal.z = 0.0f;
        
        // Store initial normal
        Vec* storedNormal = (Vec*)dataPtr;
        storedNormal->x = normal.x;
        storedNormal->y = normal.y;
        storedNormal->z = normal.z;
    } else {
        // Load stored normal
        Vec* storedNormal = (Vec*)dataPtr;
        normal.x = storedNormal->x;
        normal.y = storedNormal->y;
        normal.z = storedNormal->z;
    }
    
    // Process step-specific logic would go here
    // This is a complex function that handles matrix transformations
    // and collision detection - simplified for initial implementation
}