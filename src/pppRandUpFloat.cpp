#include "ffcc/pppRandUpFloat.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_8032FFF8;
extern float lbl_801EADC8;
extern "C" float RandF__5CMathFv(CMath* instance);

struct RandUpFloatParam {
    int targetId;
    int sourceOffset;
    float blend;
    unsigned char randomTwice;
};

struct RandUpFloatCtx {
    void* unk0;
    void* unk4;
    void* unk8;
    int* outputOffset;
};

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
    RandUpFloatParam* p2 = (RandUpFloatParam*)param2;
    RandUpFloatCtx* p3 = (RandUpFloatCtx*)param3;

    int id = p1[3];
    if (id == 0) {
        float value = RandF__5CMathFv(&math);

        if (p2->randomTwice != 0) {
            value = (value + RandF__5CMathFv(&math)) * lbl_8032FFF8;
        }

        int outIndex = *p3->outputOffset;
        float* outValue = (float*)((char*)param1 + outIndex + 0x80);
        *outValue = value;
        return;
    }

    if (p2->targetId != id) {
        return;
    }

    int outIndex = *p3->outputOffset;
    float* outValue = (float*)((char*)param1 + outIndex + 0x80);

    int sourceIndex = p2->sourceOffset;
    float* source = &lbl_801EADC8;
    if (sourceIndex != -1) {
        source = (float*)((char*)param1 + sourceIndex + 0x80);
    }

    float blend = p2->blend;
    float current = *source;
    float output = *outValue;
    *source = current + (blend * output);
}
