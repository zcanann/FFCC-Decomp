#include "ffcc/pppSRandDownCV.h"
#include "ffcc/math.h"

/*
 * --INFO--
 * PAL Address: 800635b0
 * PAL Size: 656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandDownCV(void* param1, void* param2)
{
    extern int lbl_8032ED70;
    if (lbl_8032ED70 != 0) return;
    
    CMath math;
    
    unsigned int* p1 = (unsigned int*)param1;
    unsigned char* p2_bytes = (unsigned char*)param2;
    unsigned char* p2_colors = (unsigned char*)param2;
    
    // Check if indices match
    int currentIndex = *((int*)param2);
    int targetIndex = p1[3];
    if (currentIndex != targetIndex) {
        // Handle different path - still generate random data
        int dataOffset = *((int*)param2 + 3);
        float* target = (float*)((char*)param1 + dataOffset + 0x80);
        
        unsigned char flag = p2_bytes[0x10];
        
        // Generate 4 random float values
        for (int i = 0; i < 4; i++) {
            math.RandF();
            float randVal = -1.0f; // Placeholder - RandF result stored elsewhere
            if (flag != 0) {
                math.RandF();
                float randVal2 = 0.5f; // Placeholder for second random
                randVal = (-randVal - randVal2) * 0.5f;
            }
            target[i] = randVal;
        }
        return;
    }
    
    // Main path when indices match
    int dataOffset = *((int*)param2 + 3);
    float* target = (float*)((char*)param1 + dataOffset + 0x80);
    
    unsigned char flag = p2_bytes[0x10];
    
    // Generate 4 random float values and store them
    for (int i = 0; i < 4; i++) {
        math.RandF();
        float randVal = -1.0f; // Placeholder - RandF result stored elsewhere
        if (flag != 0) {
            math.RandF();
            float randVal2 = 0.5f; // Placeholder for second random
            randVal = (-randVal - randVal2) * 0.5f;
        }
        target[i] = randVal;
    }
    
    // Get target color array pointer (bytes instead of shorts for CV)
    int colorOffset = *((int*)param2 + 1);
    unsigned char* targetColors;
    if (colorOffset == -1) {
        extern unsigned char lbl_801EADC8[];
        targetColors = lbl_801EADC8;
    } else {
        targetColors = (unsigned char*)((char*)param1 + colorOffset + 0x80);
    }
    
    // Apply random modifications to 4 color values (bytes instead of shorts)
    for (int i = 0; i < 4; i++) {
        unsigned char baseValue = p2_colors[4 + i]; // +0x4, +0x5, +0x6, +0x7 offsets
        float randomMult = target[i];
        int adjustment = (int)(baseValue * randomMult);
        unsigned char currentValue = targetColors[i];
        targetColors[i] = currentValue + (unsigned char)adjustment;
    }
}

/*
 * --INFO--
 * Address: TODO 
 * Size: TODO
 */
void randchar(char val, float mult)
{
    // TODO - likely unused based on assembly
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO  
 */
void randf(unsigned char flag)
{
    // TODO - likely unused based on assembly
}