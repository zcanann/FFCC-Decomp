#include "ffcc/pppSRandHCV.h"
#include "ffcc/math.h"

extern CMath math;
extern unsigned int lbl_8032ED70;
extern float lbl_803300A0;  
extern double lbl_803300A8;
extern unsigned char lbl_801EADC8[];

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 */
void randshort(short param_1, float param_2) {
    // TODO - not used in main function
}

/*
 * --INFO--
 * PAL Address: TODO 
 * PAL Size: TODO
 */
void randf(unsigned char param_1) {
    // TODO - not used in main function
}

/*
 * --INFO--
 * Address:	80063E34
 * Size:	736
 */
void pppSRandHCV(void* param_1, void* param_2) {
    unsigned int* param_1_u32 = (unsigned int*)param_1;
    unsigned int* param_2_u32 = (unsigned int*)param_2;
    short* param_2_s16 = (short*)param_2;
    unsigned char* param_2_u8 = (unsigned char*)param_2;
    
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    float* randomVector;
    
    // Compare first field
    if (param_2_u32[0] == param_1_u32[3]) {
        // Get random vector base address  
        unsigned int* vectorPtr = (unsigned int*)(*(unsigned int*)((char*)param_1 + 0xC));
        unsigned int offset = vectorPtr[0] + 0x80;
        randomVector = (float*)((unsigned char*)param_1 + offset);
        
        unsigned char randFlag = param_2_u8[0x10];
        
        // Generate 4 random float components
        for (int i = 0; i < 4; i++) {
            math.RandF();
            float baseRand = 0.5f; // Placeholder - actual value returned from RandF
            float finalValue;
            
            if (randFlag != 0) {
                math.RandF();
                float addRand = 0.3f; // Placeholder for second random
                finalValue = baseRand + addRand;
            } else {
                finalValue = baseRand * lbl_803300A0;
            }
            
            randomVector[i] = finalValue;
        }
    } else if (param_2_u32[0] != param_1_u32[3]) {
        return;
    } else {
        // Alternative path
        unsigned int* vectorPtr = (unsigned int*)(*(unsigned int*)((char*)param_1 + 0xC));
        unsigned int offset = vectorPtr[0] + 0x80;
        randomVector = (float*)((unsigned char*)param_1 + offset);
    }
    
    // Get destination vector
    short* destVector;
    if (param_2_u32[1] == 0xFFFFFFFF) {
        destVector = (short*)lbl_801EADC8;
    } else {
        destVector = (short*)((unsigned char*)param_1 + param_2_u32[1] + 0x80);
    }
    
    // Apply random modifications to 4 components  
    for (int i = 0; i < 4; i++) {
        short paramValue = param_2_s16[4 + i];
        float randomValue = randomVector[i];
        short currentValue = destVector[i];
        
        // Convert to float, apply random offset, convert back
        float floatParam = (float)paramValue;
        float result = floatParam * randomValue - (float)currentValue;
        signed char delta = (signed char)result;
        destVector[i] = currentValue + delta;
    }
}