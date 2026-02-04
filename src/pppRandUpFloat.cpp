#include "ffcc/pppRandUpFloat.h"
#include "ffcc/math.h"

extern CMath math;

/*
 * --INFO--
 * PAL Address: 0x800628e0
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpFloat(void* param1, void* param2, void* param3) {
    extern int lbl_8032ED70;
    if (lbl_8032ED70 != 0) {
        return;
    }

    int* p1 = (int*)param1;
    int* p2 = (int*)param2;
    int* p3 = (int*)param3;
    unsigned char* p2_bytes = (unsigned char*)param2;
    
    int r6 = p1[3];
    if (r6 != 0) {
        int r0 = p2[0];
        if (r0 != r6) {
            return;
        }
    }
    
    // Generate random float value
    math.RandF();
    float f31 = 1.0f;  // Placeholder for RandF() result
    
    if (p2_bytes[0xC] != 0) {
        // If flag is set, add another random value
        math.RandF(); 
        float f1 = 0.5f;   // Placeholder for second random value
        f31 = f31 + f1;
        
        extern float lbl_8032FFF8;
        f31 = f31 * lbl_8032FFF8;
    }
    
    int r5 = p3[3];
    if (r5 != -1) {
        // Store result at specific offset
        float* target = (float*)((char*)param1 + r5 + 0x80);
        *target = f31;
        return;
    }
    
    // Add to global float using parameter
    float f1 = *(float*)((char*)param2 + 8);
    extern float lbl_801EADC8;
    float f0 = lbl_801EADC8;
    f0 = f0 + (f1 * f31);
    lbl_801EADC8 = f0;
}