#include "ffcc/pppRandDownIV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_8032FF68;
extern float lbl_801EADC8[32];
extern "C" float RandF__5CMathFv(CMath* instance);

struct RandDownIVParam {
    int targetId;
    int sourceOffset;
    int x;
    int y;
    int z;
    unsigned char randomTwice;
};

struct RandDownIVCtx {
    void* unk0;
    void* unk4;
    void* unk8;
    int* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 0x80061a88
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void randint(int param1, float param2)
{
}

/*
 * --INFO--
 * PAL Address: 0x80061a88
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownIV(void* arg1, void* arg2, void* arg3)
{
    int* objectWords = (int*)arg1;
    RandDownIVParam* data = (RandDownIVParam*)arg2;
    RandDownIVCtx* ctx = (RandDownIVCtx*)arg3;
    float* output;
    int* source;
    float randomValue;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (data->targetId != objectWords[3]) {
        return;
    }

    randomValue = -RandF__5CMathFv(&math);
    if (data->randomTwice != 0) {
        randomValue = (randomValue - RandF__5CMathFv(&math)) * lbl_8032FF68;
    }

    output = (float*)((char*)arg1 + *ctx->outputOffset + 0x80);
    *output = randomValue;

    if (data->sourceOffset == -1) {
        source = (int*)&lbl_801EADC8[0];
    } else {
        source = (int*)((char*)arg1 + data->sourceOffset + 0x80);
    }

    source[0] += (int)((float)data->x * *output);
    source[1] += (int)((float)data->y * *output);
    source[2] += (int)((float)data->z * *output);
}
