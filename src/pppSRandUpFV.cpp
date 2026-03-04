#include "ffcc/pppSRandUpFV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math[];
extern s32 lbl_8032ED70;
extern f32 lbl_803300C0;
extern f32 lbl_801EADC8[];
extern "C" f32 RandF__5CMathFv(CMath*);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randfloat(float f1, float f2)
{
    // Basic random float implementation
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randf(unsigned char param)
{
    // Basic random function with byte parameter
}

/*
 * --INFO--
 * PAL Address: 0x800643a4
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppSRandUpFV(void* param1, void* param2, void* param3)
{
    struct SRandUpFVParam {
        s32 index;
        s32 targetOffset;
        f32 x;
        f32 y;
        f32 z;
        u8 _pad14[0x18 - 0x14];
        u8 blendTwice;
    };
    struct SRandUpFVCtx {
        u8 _pad0[0xC];
        s32* outputOffset;
    };

    u8* base = (u8*)param1;
    SRandUpFVParam* in = (SRandUpFVParam*)param2;
    SRandUpFVCtx* ctx = (SRandUpFVCtx*)param3;
    f32* randVec;

    if (lbl_8032ED70 != 0) {
        return;
    }

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        randVec = (f32*)(base + *ctx->outputOffset + 0x80);

        {
            u8 flag = in->blendTwice;
            f32 value = RandF__5CMathFv(math);
            if (flag != 0) {
                value = (value + RandF__5CMathFv(math)) * lbl_803300C0;
            }
            randVec[0] = value;
        }

        {
            u8 flag = in->blendTwice;
            f32 value = RandF__5CMathFv(math);
            if (flag != 0) {
                value = (value + RandF__5CMathFv(math)) * lbl_803300C0;
            }
            randVec[1] = value;
        }

        {
            u8 flag = in->blendTwice;
            f32 value = RandF__5CMathFv(math);
            if (flag != 0) {
                value = (value + RandF__5CMathFv(math)) * lbl_803300C0;
            }
            randVec[2] = value;
        }
    } else {
        if (in->index != state) {
            return;
        }
        randVec = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    s32 targetOffset = in->targetOffset;
    f32* target = (targetOffset == -1) ? lbl_801EADC8 : (f32*)(base + targetOffset + 0x80);

    {
        f32 value = in->x * randVec[0];
        target[0] = target[0] + value;
    }
    {
        f32 value = in->y * randVec[1];
        target[1] = target[1] + value;
    }
    {
        f32 value = in->z * randVec[2];
        target[2] = target[2] + value;
    }
}
