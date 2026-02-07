#include "ffcc/pppRandFloat.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_8032FF88;
extern float lbl_801EADC8;
extern "C" float RandF__5CMathFv(CMath* instance);

struct RandFloatParam {
    int targetId;
    int sourceOffset;
    float blend;
    unsigned char randomTwice;
};

struct RandFloatCtx {
    void* unk0;
    void* unk4;
    void* unk8;
    int* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 0x80061d48
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void pppRandFloat(void* param1, void* param2, void* param3)
{
    int* base = (int*)param1;
    RandFloatParam* data = (RandFloatParam*)param2;
    RandFloatCtx* ctx = (RandFloatCtx*)param3;
    int index = base[3];

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (index == 0) {
        float out = RandF__5CMathFv(&math);

        if (data->randomTwice != 0) {
            out += RandF__5CMathFv(&math);
        } else {
            out *= lbl_8032FF88;
        }

        int outputOffset = *ctx->outputOffset;
        *(float*)((char*)param1 + outputOffset + 0x80) = out;
        return;
    }

    if (data->targetId == index) {
        int outputOffset = *ctx->outputOffset;
        float* outputValue = (float*)((char*)param1 + outputOffset + 0x80);
        float* source;

        if (data->sourceOffset == -1) {
            source = &lbl_801EADC8;
        } else {
            source = (float*)((char*)param1 + data->sourceOffset + 0x80);
        }

        *source = *source + (data->blend * *outputValue - data->blend);
    }
}
