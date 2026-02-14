#include "ffcc/pppRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math[];
extern int lbl_8032ED70;
extern float lbl_8032FF08;
extern u8 lbl_801EADC8[32];
extern "C" float RandF__5CMathFv(CMath* instance);

typedef struct RandCVParams {
    int index;
    int colorOffset;
    s8 delta[4];
    u8 flag;
    u8 pad[3];
} RandCVParams;

typedef struct RandCVCtx {
    u8 pad[0xC];
    int* outputOffset;
} RandCVCtx;

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 */
void randchar(char range, float factor)
{
	float value = (float)range;
	float scaled = value * factor;
	(void)scaled;
}

/*
 * --INFO--
 * PAL Address: 0x80066194
 * PAL Size: 540b
 */
void pppRandCV(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    RandCVParams* params = (RandCVParams*)param2;
    RandCVCtx* ctx = (RandCVCtx*)param3;
    float* randomValue;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (params->index == *(int*)(base + 0xC)) {
        float value = RandF__5CMathFv(math);
        if (params->flag != 0) {
            value += RandF__5CMathFv(math);
        } else {
            value *= lbl_8032FF08;
        }

        randomValue = (float*)(base + *ctx->outputOffset + 0x80);
        *randomValue = value;
    }

    if (params->index != *(int*)(base + 0xC)) {
        return;
    }

    randomValue = (float*)(base + *ctx->outputOffset + 0x80);

    u8* target;
    if (params->colorOffset == -1) {
        target = lbl_801EADC8;
    } else {
        target = base + params->colorOffset + 0x80;
    }

    {
        float scale = *randomValue;
        u8 current = target[0];
        s8 delta = params->delta[0];
        target[0] = (u8)(current + (int)((float)delta * scale - (float)current));
    }

    {
        float scale = *randomValue;
        u8 current = target[1];
        s8 delta = params->delta[1];
        target[1] = (u8)(current + (int)((float)delta * scale - (float)current));
    }

    {
        float scale = *randomValue;
        u8 current = target[2];
        s8 delta = params->delta[2];
        target[2] = (u8)(current + (int)((float)delta * scale - (float)current));
    }

    {
        float scale = *randomValue;
        u8 current = target[3];
        s8 delta = params->delta[3];
        target[3] = (u8)(current + (int)((float)delta * scale - (float)current));
    }
}
