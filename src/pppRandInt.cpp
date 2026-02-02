#include "ffcc/pppRandInt.h"
#include "types.h"

/*
 * --INFO--
 * PAL Address: 0x80062194
 * PAL Size: 320b
 */
void pppRandInt(void* basePtr, void* dataPtr, void* outputPtr)
{
    // Early exit check
    extern u32 lbl_8032ED70;
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Get parameters for random int generation
    u32* paramPtr = (u32*)dataPtr;
    u32 minValue = paramPtr[0];
    u32 maxValue = paramPtr[1];
    
    // Get output offset
    u32* outputOffsetPtr = (u32*)outputPtr;
    u32 offset = *outputOffsetPtr;
    
    // Calculate target address
    s32* targetPtr = (s32*)((u8*)basePtr + offset + 0x80);
    
    // Generate random integer in range [minValue, maxValue)
    extern int rand();
    u32 range = maxValue - minValue;
    if (range > 0) {
        *targetPtr = (s32)(minValue + (rand() % range));
    } else {
        *targetPtr = (s32)minValue;
    }
}