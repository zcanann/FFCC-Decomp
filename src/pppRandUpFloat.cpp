#include "ffcc/pppRandUpFloat.h"

extern class CMath {
public:
    float RandF(void);
} math;
extern int lbl_8032ED70;
extern float lbl_8032FFF8;
extern float lbl_801EADC8;

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

    char* base = (char*)param1;
    RandUpFloatCtx* p3 = (RandUpFloatCtx*)param3;
    RandUpFloatParam* p2 = (RandUpFloatParam*)param2;
    float* valuePtr;

    int id = *(int*)(base + 0xC);
    if (id == 0) {
        float value = math.RandF();

        if (p2->randomTwice != 0) {
            value = (value + math.RandF()) * lbl_8032FFF8;
        }

        valuePtr = (float*)(base + *p3->outputOffset + 0x80);
        *valuePtr = value;
    } else {
        if (p2->targetId != id) {
            return;
        }
        valuePtr = (float*)(base + *p3->outputOffset + 0x80);
    }

    int sourceOffset = p2->sourceOffset;
    float* source;
    if (sourceOffset == -1) {
        source = &lbl_801EADC8;
    } else {
        source = (float*)(base + sourceOffset + 0x80);
    }

    *source = *source + (p2->blend * *valuePtr);
}
