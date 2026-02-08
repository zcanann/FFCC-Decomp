#include "ffcc/pppSRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;
extern int lbl_8032ED70;
extern u8 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath* instance);

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SRandCVParams {
    s32 index;
    s32 colorOffset;
    s8 delta[4];
    s32* valueOffset;
    u8 flag;
} SRandCVParams;

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
    SRandCVParams* params = (SRandCVParams*)param2;
    s32** sourceOffsets = (s32**)((u8*)param3 + 0xc);
    float* values;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (params->index == *(s32*)((u8*)param1 + 0xc)) {
        int i;

        values = (float*)((u8*)param1 + **sourceOffsets + 0x80);
        for (i = 0; i < 4; i++) {
            float value = RandF__5CMathFv(&math);
            if (params->flag != 0) {
                value += RandF__5CMathFv(&math);
            } else {
                value *= 2.0f;
            }
            values[i] = value;
        }
        return;
    }

    values = (float*)((u8*)param1 + *params->valueOffset + 0x80);
    {
        u8* colors;
        int i;

        if (params->colorOffset == -1) {
            colors = lbl_801EADC8;
        } else {
            colors = (u8*)param1 + params->colorOffset + 0x80;
        }

        for (i = 0; i < 2; i++) {
            s8 delta0 = params->delta[(i * 2) + 0];
            s8 delta1 = params->delta[(i * 2) + 1];
            u8 color0 = colors[(i * 2) + 0];
            u8 color1 = colors[(i * 2) + 1];
            int add0 = (int)(((double)delta0 * (double)values[(i * 2) + 0]) - (double)color0);
            int add1 = (int)(((double)delta1 * (double)values[(i * 2) + 1]) - (double)color1);

            colors[(i * 2) + 0] = (u8)(color0 + add0);
            colors[(i * 2) + 1] = (u8)(color1 + add1);
        }
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
