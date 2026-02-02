#include "ffcc/pppYmMoveParabola.h"
#include "types.h"
#include "dolphin/mtx.h"

/*
 * --INFO--
 * Address:	800d4558
 * Size:	292b
 */
void pppConstructYmMoveParabola(struct pppYmMoveParabola* basePtr, struct UnkC* dataPtr)
{
    // Get offset from data pointer 
    u32 offset = *dataPtr->m_serializedDataOffsets;
    f32* targetPtr = (f32*)((u8*)basePtr + offset + 8);
    
    // Initialize velocity components to 0.0f
    f32 zero = 0.0f;
    targetPtr[0] = zero;  // x velocity
    targetPtr[1] = zero;  // y velocity  
    targetPtr[2] = zero;  // z velocity
    
    // Initialize counter to 1
    *(u16*)(targetPtr + 3) = 1;
}

/*
 * --INFO--
 * Address:	800d4278
 * Size:	736b
 */
void pppFrameYmMoveParabola(struct pppYmMoveParabola* basePtr, struct UnkB* stepData, struct UnkC* offsetData)
{
    // Get offset from data pointer
    u32 offset = *offsetData->m_serializedDataOffsets;
    f32* targetPtr = (f32*)((u8*)basePtr + offset + 8);
    
    // Basic velocity update - simplified implementation
    targetPtr[1] += targetPtr[2];  // vy += vz  
    targetPtr[0] += targetPtr[1];  // vx += vy
    
    // Increment counter
    *(u16*)(targetPtr + 3) += 1;
}