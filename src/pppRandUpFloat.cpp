#include "ffcc/pppRandUpFloat.h"

/*
 * --INFO--
 * PAL Address: 0x800628e0
 * PAL Size: 108b
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
    
    int r6 = p1[3];
    if (r6 != 0) {
        int r0 = p2[0];
        if (r0 != r6) {
            return;
        }
    }
    
    unsigned char* p2_bytes = (unsigned char*)param2;
    static const float kHalf = 0.5f;  // Force to sdata2
    float f2 = kHalf;
    
    if (p2_bytes[0xC] != 0) {
        extern float lbl_8032FFF8;
        f2 = f2 * lbl_8032FFF8;
    }
    
    int r5 = p3[3];
    if (r5 != -1) {
        float* target = (float*)((char*)param1 + r5 + 0x80);
        *target = f2;
        return;
    }
    
    float f1 = *(float*)((char*)param2 + 8);
    extern float lbl_801EADC8;
    lbl_801EADC8 = lbl_801EADC8 + (f1 * f2);
}