#include "ffcc/pppRandInt.h"
#include "ffcc/math.h"

/*
 * --INFO--
 * PAL Address: 0x80062194
 * PAL Size: 320b
 */
void pppRandInt(void* particleSystem, void* particleData, void* outputData)
{
    extern int lbl_8032ED70;
    extern CMath math;
    
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Get system data pointers  
    void** systemDataPtr = (void**)((void**)particleSystem)[3];
    
    if (systemDataPtr == 0) {
        // Generate random value
        math.RandF();
        
        // Check particle flags
        unsigned char* particleFlags = (unsigned char*)((char*)particleData + 12);
        if (*particleFlags != 0) {
            math.RandF();
        }
        
        // Calculate output offset and store result
        int* outputArrayPtr = (int*)((void**)outputData)[3];
        int* outputPtr = (int*)outputArrayPtr;
        int offset = outputPtr[0] + 128;
        float* targetPtr = (float*)((char*)particleSystem + offset);
        // Store some calculated value (placeholder for now)
        *targetPtr = 1.0f;
        return;
    }
    
    // Check if particle ID matches
    int particleId = *(int*)particleData;
    int expectedId = *(int*)systemDataPtr;
    if (particleId != expectedId) {
        return;
    }
    
    // Get values for calculation
    int* outputArrayPtr = (int*)((void**)outputData)[3];
    int* outputPtr = (int*)outputArrayPtr;
    int offset = outputPtr[0] + 128;
    
    int rangeValue = *((int*)particleData + 1);
    int* targetPtr;
    
    if (rangeValue == -1) {
        extern int* lbl_801EADC8;
        targetPtr = lbl_801EADC8;
    } else {
        targetPtr = (int*)((char*)particleSystem + rangeValue + 128);
    }
    
    int baseValue = *((int*)particleData + 2);
    float floatValue = *(float*)((char*)particleSystem + offset);
    
    // Perform integer calculation
    int result = (int)(baseValue * floatValue) - *targetPtr;
    *targetPtr = *targetPtr + result;
}