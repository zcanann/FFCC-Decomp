#include "ffcc/pppSRandUpCV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;

// Forward declaration to handle RandF return value
extern "C" float RandF__5CMathFv();

/*
 * --INFO--
 * PAL Address: 80064114
 * PAL Size: 656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void pppSRandUpCV(void* param1, void* param2)
{
    if (lbl_8032ED70 != 0) return;
    
    // Check if indices match
    int currentIndex = *((int*)param2);
    int targetIndex = *((int*)param1 + 3);
    if (currentIndex != targetIndex) return;
    
    // Get data offset and calculate target array
    int dataOffset = *((int*)param2 + 3);
    float* target = (float*)((char*)param1 + dataOffset + 0x80);
    
    unsigned char flag = *((unsigned char*)param2 + 12);
    
    // Generate first random float value
    float randVal1 = RandF__5CMathFv();
    if (flag != 0) {
        float randVal2 = RandF__5CMathFv();
        randVal1 = (randVal1 + randVal2) * 0.5f;
    }
    target[0] = randVal1;
    
    // Generate second random float value  
    randVal1 = RandF__5CMathFv();
    if (flag != 0) {
        float randVal2 = RandF__5CMathFv();
        randVal1 = (randVal1 + randVal2) * 0.5f;
    }
    target[1] = randVal1;
    
    // Generate third random float value
    randVal1 = RandF__5CMathFv();
    if (flag != 0) {
        float randVal2 = RandF__5CMathFv();
        randVal1 = (randVal1 + randVal2) * 0.5f;
    }
    target[2] = randVal1;
    
    // Generate fourth random float value
    randVal1 = RandF__5CMathFv();
    if (flag != 0) {
        float randVal2 = RandF__5CMathFv();
        randVal1 = (randVal1 + randVal2) * 0.5f;
    }
    target[3] = randVal1;
    
    // Get target color array pointer
    int colorOffset = *((int*)param2 + 1);
    unsigned char* targetColors;
    if (colorOffset == -1) {
        extern unsigned char lbl_801EADC8[];
        targetColors = lbl_801EADC8;
    } else {
        targetColors = (unsigned char*)((char*)param1 + colorOffset + 0x80);
    }
    
    // Apply random modifications to first byte value
    signed char baseValue1 = *((signed char*)param2 + 8);
    int adjustment1 = (int)(baseValue1 * target[0]);
    targetColors[0] += (unsigned char)adjustment1;
    
    // Apply random modifications to second byte value
    signed char baseValue2 = *((signed char*)param2 + 9);
    int adjustment2 = (int)(baseValue2 * target[1]);
    targetColors[1] += (unsigned char)adjustment2;
    
    // Apply random modifications to third byte value
    signed char baseValue3 = *((signed char*)param2 + 10);
    int adjustment3 = (int)(baseValue3 * target[2]);
    targetColors[2] += (unsigned char)adjustment3;
    
    // Apply random modifications to fourth byte value
    signed char baseValue4 = *((signed char*)param2 + 11);
    int adjustment4 = (int)(baseValue4 * target[3]);
    targetColors[3] += (unsigned char)adjustment4;
}
