#include "ffcc/pppSRandDownHCV.h"
#include "ffcc/math.h"

extern CMath math;

/*
 * --INFO--
 * PAL Address: 800639ec
 * PAL Size: 656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandDownHCV(void* param1, void* param2)
{
    extern int lbl_8032ED70;
    if (lbl_8032ED70 != 0) return;
    
    // Check if indices match
    int currentIndex = *((int*)param2);
    int targetIndex = *((int*)param1 + 3);
    if (currentIndex != targetIndex) {
        // When indices don't match, get data offset from param2
        int dataOffset = *((int*)param2 + 3);
        float* target = (float*)((char*)param1 + dataOffset + 0x80);
        
        unsigned char flag = *((unsigned char*)param2 + 0x10);
        
        // Generate 4 random float values
        for (int i = 0; i < 4; i++) {
            math.RandF(); // bl RandF__5CMathFv
            float randVal = -1.0f; // fneg f31, f1 (placeholder for RandF result)
            if (flag != 0) {
                math.RandF(); // Second RandF call
                float randVal2 = 1.0f; // Placeholder for second RandF
                randVal = (-randVal - randVal2) * 0.5f; // fsubs + fmuls
            }
            target[i] = randVal;
        }
        
        // Get target short array pointer from param2 offset
        int shortOffset = *((int*)param2 + 1);
        short* targetColors;
        if (shortOffset == -1) {
            extern short lbl_801EADC8[];
            targetColors = lbl_801EADC8;
        } else {
            targetColors = (short*)((char*)param1 + shortOffset + 0x80);
        }
        
        // Apply random modifications to short values
        for (int i = 0; i < 4; i++) {
            short baseValue = *((short*)param2 + 4 + i);
            float randomMult = target[i];
            int adjustment = (int)(baseValue * randomMult);
            short currentValue = targetColors[i];
            targetColors[i] = currentValue + adjustment;
        }
        return;
    }
    
    // Main path when indices match
    int dataOffset = *((int*)param2 + 3);
    float* target = (float*)((char*)param1 + dataOffset + 0x80);
    unsigned char flag = *((unsigned char*)param2 + 0x10);
    
    // Generate 4 random float values
    for (int i = 0; i < 4; i++) {
        math.RandF(); // bl RandF__5CMathFv
        float randVal = -1.0f; // fneg f31, f1 (placeholder for RandF result)
        if (flag != 0) {
            math.RandF(); // Second RandF call
            float randVal2 = 1.0f; // Placeholder for second RandF
            randVal = (-randVal - randVal2) * 0.5f; // fsubs + fmuls
        }
        target[i] = randVal;
    }
    
    // Get short array target
    int shortOffset = *((int*)param2 + 1);
    short* targetColors;
    if (shortOffset == -1) {
        extern short lbl_801EADC8[];
        targetColors = lbl_801EADC8;
    } else {
        targetColors = (short*)((char*)param1 + shortOffset + 0x80);
    }
    
    // Apply random modifications to 4 short values
    for (int i = 0; i < 4; i++) {
        short baseValue = *((short*)param2 + 4 + i);
        float randomMult = target[i];
        int adjustment = (int)(baseValue * randomMult);
        short currentValue = targetColors[i];
        targetColors[i] = currentValue + adjustment;
    }
}

/*
 * --INFO--
 * Address: TODO 
 * Size: TODO
 */
void randshort(short val, float mult)
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