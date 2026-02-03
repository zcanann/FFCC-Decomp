#include "ffcc/pppSRandDownFV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;

// Forward declaration to handle RandF return value
extern "C" float RandF__5CMathFv();

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randfloat(float, float)
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

/*
 * --INFO--
 * PAL Address: 0x80063840
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandDownFV(void* param1, void* param2)
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
    
    // Generate 3 random float values (FV = Float Vector, 3D)
    for (int i = 0; i < 3; i++) {
        float randVal = -RandF__5CMathFv();  // Negative for "Down"
        if (flag != 0) {
            float randVal2 = -RandF__5CMathFv();  
            randVal = (randVal + randVal2) * 0.5f;
        }
        target[i] = randVal;
    }
    
    // Get target color array pointer  
    int colorOffset = *((int*)param2 + 1);
    unsigned char* targetColors;
    if (colorOffset == -1) {
        extern unsigned char lbl_801EADC8[];
        targetColors = lbl_801EADC8;
    } else {
        targetColors = (unsigned char*)((char*)param1 + colorOffset + 0x80);
    }
    
    // Apply random modifications to 3 float values
    for (int i = 0; i < 3; i++) {
        float baseValue = *((float*)param2 + 2 + i);  // Different offset for FV
        float randomMult = target[i];
        float adjustment = baseValue * randomMult;
        targetColors[i] += (unsigned char)adjustment;  // Addition to target
    }
}