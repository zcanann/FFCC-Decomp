#include "ffcc/pppRandInt.h"
#include "types.h"

/*
 * --INFO--
 * PAL Address: 0x80062194
 * PAL Size: 320b
 */

// Forward declarations from CMath
extern "C" {
    float RandF__5CMathFv();
}

void pppRandInt(void* basePtr, void* dataPtr, void* outputPtr)
{
    extern u32 lbl_8032ED70;
    
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Check if dataPtr has valid data
    if (((u8*)dataPtr)[0xC] == 0) {
        // Generate random float
        float randomFloat = RandF__5CMathFv();
        
        // Check some condition in dataPtr
        if (((u8*)dataPtr)[0xC] != 0) {
            randomFloat += RandF__5CMathFv();
        } else {
            randomFloat *= 2.0f;
        }
        
        // Get output offset and calculate target address
        u32 offset = *(u32*)outputPtr;
        float* targetPtr = (float*)((u8*)basePtr + offset + 0x80);
        *targetPtr = randomFloat;
        
    } else {
        // Handle integer case with parameters
        u32* paramPtr = (u32*)dataPtr;
        u32 param1 = paramPtr[0];
        u32 param2 = paramPtr[1];
        
        if (param1 != param2) {
            u32 offset = *(u32*)outputPtr;
            
            // Check for special value case
            if (paramPtr[2] == 0xFFFFFFFF) {
                // Use some special data
                extern float lbl_801EADC8[];
                float* specialPtr = lbl_801EADC8;
                float specialValue = *specialPtr;
            } else {
                u32* targetPtr = (u32*)((u8*)basePtr + offset + 0x80);
                
                // Complex floating point calculation
                float floatParam2 = (float)paramPtr[2];
                float existingValue = *(float*)targetPtr;
                float floatParam1 = (float)param1;
                
                float result = floatParam1 + existingValue * floatParam2 - floatParam1;
                s32 intResult = (s32)result + param1;
                *targetPtr = intResult;
            }
        }
    }
}