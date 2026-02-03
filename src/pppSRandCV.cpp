#include "ffcc/pppSRandCV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * --INFO--
 * PAL Address: 800632d0
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandCV(void* param1, void* param2)
{
    // Global state check - assembly shows comparison with lbl_8032ED70
    if (lbl_8032ED70 == 0) {
        // First branch: check if param2[0] == param1[0xc]  
        if (*(int*)param2 == *(int*)((char*)param1 + 0xc)) {
            // Get data pointer from param2[0xc]
            int dataPtr = *(int*)((char*)param2 + 0xc);
            dataPtr = *(int*)dataPtr; // Dereference
            float* targetData = (float*)((char*)param1 + dataPtr + 0x80);
            
            unsigned char flag = *((unsigned char*)param2 + 0xc);
            
            // Generate 4 random values for RGBA channels
            for (int i = 0; i < 4; i++) {
                math.RandF(); // First random call
                float baseRand = 1.0f; // Placeholder for random result
                
                if (flag != 0) {
                    math.RandF(); // Second random call
                    float extraRand = 0.5f; // Placeholder for second random
                    targetData[i] = baseRand + extraRand;
                } else {
                    targetData[i] = baseRand * 2.0f; // Assembly shows lbl_80330060 (2.0f)
                }
            }
        } else {
            // Alternative path when indices don't match
            int altDataPtr = *(int*)((char*)param2 + 0xc);
            altDataPtr = *(int*)altDataPtr + 0x80;
            float* sourceData = (float*)((char*)param1 + altDataPtr);
            
            // Get sprite data pointer
            int spriteIndex = *(int*)((char*)param2 + 0x4);
            unsigned char* spriteData;
            if (spriteIndex == -1) {
                spriteData = (unsigned char*)0x801EADC8; // From assembly
            } else {
                spriteData = (unsigned char*)((char*)param1 + spriteIndex + 0x80);
            }
            
            // Process 4 channels with color interpolation
            for (int channel = 0; channel < 4; channel++) {
                signed char deltaValue = *((signed char*)param2 + 0x8 + channel);
                unsigned char currentValue = spriteData[channel];
                float sourceValue = sourceData[channel];
                
                // Color interpolation: result = delta * source - delta
                float interpolation = (float)deltaValue * sourceValue - (float)deltaValue;
                int modification = (int)interpolation;
                spriteData[channel] = currentValue + modification;
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randchar(char, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randf(unsigned char)
{
	// TODO
}

#ifdef __cplusplus
}
#endif