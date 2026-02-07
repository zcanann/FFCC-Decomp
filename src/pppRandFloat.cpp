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
    int index = base[3];

    if (lbl_8032ED70 == 0) {
        RandFloatParam* data = (RandFloatParam*)param2;
        RandFloatCtx* ctx = (RandFloatCtx*)param3;

        if (index == 0) {
            float out = RandF__5CMathFv(&math);

            if (data->randomTwice != 0) {
                out = out + RandF__5CMathFv(&math);
            } else {
                out = out * lbl_8032FF88;
            }

            *(float*)((char*)base + (*ctx->outputOffset + 0x80)) = out;
        } else if (data->targetId == index) {
            int outputOffset = *ctx->outputOffset;
            int sourceOffset = data->sourceOffset;
            float* source;

            if (sourceOffset == -1) {
                source = &lbl_801EADC8;
            } else {
                source = (float*)((char*)base + (sourceOffset + 0x80));
            }

            *source = *source + (data->blend * *(float*)((char*)base + (outputOffset + 0x80)) - data->blend);
        }
    }
}
