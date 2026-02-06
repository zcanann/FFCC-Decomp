#include "ffcc/pppRandUpFloat.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_8032FFF8;
extern float lbl_801EADC8;

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
    if (lbl_8032ED70 != 0) {
        return;
    }

    int* p1 = (int*)param1;
    int* p2 = (int*)param2;
    int* p3 = (int*)param3;

    int id = p1[3];
    if (id == 0) {
        math.RandF();
        float value = 1.0f;

        if (((unsigned char*)param2)[0xC] != 0) {
            math.RandF();
            value = (value + 0.5f) * lbl_8032FFF8;
        }

        int outIndex = *(int*)p3[3];
        *(float*)((char*)param1 + outIndex + 0x80) = value;
        return;
    }

    if (p2[0] != id) {
        return;
    }

    int outIndex = *(int*)p3[3];
    float* outValue = (float*)((char*)param1 + outIndex + 0x80);

    int sourceIndex = p2[1];
    float* source = &lbl_801EADC8;
    if (sourceIndex != -1) {
        source = (float*)((char*)param1 + sourceIndex + 0x80);
    }

    *source = *source + (*(float*)((char*)param2 + 8) * *outValue);
}
