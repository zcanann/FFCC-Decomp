#include "ffcc/pppRandDownFloat.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70; // Global state flag
extern float lbl_8032FF38; // Float constant  
extern float lbl_801EADC8; // Another float constant
extern "C" float RandF__5CMathFv(CMath*);

typedef struct {
    int field0;
    int field4;
    float field8;
    unsigned char fieldC;
} PppRandDownFloatParam;

typedef struct {
    void* field0;
    void* field4;
    void* field8;
    int* fieldC;
} PppRandDownFloatState;

/*
 * --INFO--
 * PAL Address: 0x8006155c
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void pppRandDownFloat(void* r3, void* r4, void* r5) {
    int* obj = (int*)r3;
    PppRandDownFloatState* state = (PppRandDownFloatState*)r5;
    PppRandDownFloatParam* param = (PppRandDownFloatParam*)r4;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (obj[3] == 0) {
        float value = RandF__5CMathFv(&math);
        value = -value;

        if (param->fieldC != 0) {
            value = (value - RandF__5CMathFv(&math)) * lbl_8032FF38;
        }

        *(float*)((char*)obj + *state->fieldC + 0x80) = value;
        return;
    }

    if (param->field0 == obj[3]) {
        float* dst = (float*)((char*)obj + *state->fieldC + 0x80);
        float* src;

        if (param->field4 == -1) {
            src = &lbl_801EADC8;
        } else {
            src = (float*)((char*)obj + param->field4 + 0x80);
        }

        *src += param->field8 * *dst;
    }
}
