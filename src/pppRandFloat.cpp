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
    int index;
    int outputOffset;
    RandFloatCtx* ctx;
    RandFloatParam* data;
    float* source;
    float* output;
    char* base;
    float value;

    if (lbl_8032ED70 != 0) {
        return;
    }

    base = (char*)param1;
    index = ((int*)base)[3];
    ctx = (RandFloatCtx*)param3;
    data = (RandFloatParam*)param2;

    if (index == 0) {
        value = RandF__5CMathFv(&math);
        if (data->randomTwice != 0) {
            value += RandF__5CMathFv(&math);
        } else {
            value *= lbl_8032FF88;
        }

        outputOffset = *ctx->outputOffset;
        output = (float*)(base + outputOffset + 0x80);
        *output = value;
        return;
    }

    if (data->targetId == index) {
        outputOffset = *ctx->outputOffset;
        output = (float*)(base + outputOffset + 0x80);
        if (data->sourceOffset == -1) {
            source = &lbl_801EADC8;
        } else {
            source = (float*)(base + data->sourceOffset + 0x80);
        }
        *source = *source + (data->blend * *output - data->blend);
    }
}
