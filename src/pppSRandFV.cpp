#include "ffcc/pppSRandFV.h"
#include "ffcc/math.h"

extern CMath math[];
extern int lbl_8032ED70;
extern float lbl_80330098;
extern float lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath*);

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
 * PAL Address: 0x80063c7c
 * PAL Size: 440b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
struct PppSRandFVParam2 {
    int field0;
    int field4;
    float field8;
    float fieldC;
    float field10;
    unsigned char _pad14[0x18 - 0x14];
    unsigned char field18;
};

struct PppSRandFVParam3 {
    unsigned char _pad0[0xC];
    int* fieldC;
};

void pppSRandFV(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    unsigned char* base = (unsigned char*)param1;
    PppSRandFVParam2* in = (PppSRandFVParam2*)param2;
    PppSRandFVParam3* out = (PppSRandFVParam3*)param3;
    float* valuePtr;

    int state = *(int*)(base + 0xC);
    if (state == 0) {
        unsigned char blendTwice = in->field18;
        valuePtr = (float*)(base + *out->fieldC + 0x80);

        float value = RandF__5CMathFv(math);
        if (blendTwice != 0) {
            value = value + RandF__5CMathFv(math);
        } else {
            value = value * lbl_80330098;
        }
        valuePtr[0] = value;

        value = RandF__5CMathFv(math);
        if (blendTwice != 0) {
            value = value + RandF__5CMathFv(math);
        } else {
            value = value * lbl_80330098;
        }
        valuePtr[1] = value;

        value = RandF__5CMathFv(math);
        if (blendTwice != 0) {
            value = value + RandF__5CMathFv(math);
        } else {
            value = value * lbl_80330098;
        }
        valuePtr[2] = value;
    } else {
        if (in->field0 != state) {
            return;
        }
        valuePtr = (float*)(base + *out->fieldC + 0x80);
    }

    float* target;
    if (in->field4 == -1) {
        target = lbl_801EADC8;
    } else {
        target = (float*)(base + in->field4 + 0x80);
    }

    float value = in->field8 * valuePtr[0] - in->field8;
    target[0] = target[0] + value;
    value = in->fieldC * valuePtr[1] - in->fieldC;
    target[1] = target[1] + value;
    value = in->field10 * valuePtr[2] - in->field10;
    target[2] = target[2] + value;
}
