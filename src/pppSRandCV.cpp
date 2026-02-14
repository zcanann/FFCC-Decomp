#include "ffcc/pppSRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math[];
extern int lbl_8032ED70;
extern float lbl_80330060;
extern u8 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath* instance);

typedef struct SRandCVParams {
    int index;
    int colorOffset;
    s8 delta[4];
    u8 flag;
    u8 pad[3];
} SRandCVParams;

typedef struct SRandCVCtx {
    u8 pad[0xC];
    int* outputOffset;
} SRandCVCtx;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * --INFO--
 * PAL Address: 800632d0
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandCV(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    u8* base = (u8*)param1;
    SRandCVParams* params = (SRandCVParams*)param2;
    SRandCVCtx* ctx = (SRandCVCtx*)param3;
    float* target;

    if (params->index == *(int*)(base + 0xC)) {
        target = (float*)(base + *ctx->outputOffset + 0x80);

        u8 flag = params->flag;
        float value;

        value = RandF__5CMathFv(math);
        if (flag != 0) {
            value = value + RandF__5CMathFv(math);
        } else {
            value = value * lbl_80330060;
        }
        target[0] = value;

        value = RandF__5CMathFv(math);
        if (flag != 0) {
            value = value + RandF__5CMathFv(math);
        } else {
            value = value * lbl_80330060;
        }
        target[1] = value;

        value = RandF__5CMathFv(math);
        if (flag != 0) {
            value = value + RandF__5CMathFv(math);
        } else {
            value = value * lbl_80330060;
        }
        target[2] = value;

        value = RandF__5CMathFv(math);
        if (flag != 0) {
            value = value + RandF__5CMathFv(math);
        } else {
            value = value * lbl_80330060;
        }
        target[3] = value;
    } else if (params->index != *(int*)(base + 0xC)) {
        target = (float*)(base + *ctx->outputOffset + 0x80);
    }

    int color_offset = params->colorOffset;
    u8* target_color;
    if (color_offset == -1) {
        target_color = lbl_801EADC8;
    } else {
        target_color = base + color_offset + 0x80;
    }

    {
        u8 current = target_color[0];
        s8 baseValue = params->delta[0];
        int delta = (int)((float)baseValue * target[0] - (float)current);
        target_color[0] = (u8)(current + delta);
    }

    {
        u8 current = target_color[1];
        s8 baseValue = params->delta[1];
        int delta = (int)((float)baseValue * target[1] - (float)current);
        target_color[1] = (u8)(current + delta);
    }

    {
        u8 current = target_color[2];
        s8 baseValue = params->delta[2];
        int delta = (int)((float)baseValue * target[2] - (float)current);
        target_color[2] = (u8)(current + delta);
    }

    {
        u8 current = target_color[3];
        s8 baseValue = params->delta[3];
        int delta = (int)((float)baseValue * target[3] - (float)current);
        target_color[3] = (u8)(current + delta);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randchar(char, float)
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

#ifdef __cplusplus
}
#endif
