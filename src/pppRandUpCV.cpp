#include "ffcc/pppRandUpCV.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern s32 lbl_8032ED70;
extern f32 lbl_8032FF08;
extern u8 lbl_801EADC8[32];
extern "C" f32 RandF__5CMathFv(CMath* instance);

struct RandUpCVParam {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 randomTwice;
};

struct RandUpCVCtx {
    u8 _pad[0xC];
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 0x80062708
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpCV(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    RandUpCVParam* in = (RandUpCVParam*)param2;
    RandUpCVCtx* ctx = (RandUpCVCtx*)param3;
    f32* valuePtr;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (in->targetId == *(s32*)(base + 0xC)) {
        f32 value = RandF__5CMathFv(math);
        if (in->randomTwice != 0) {
            value = (value + RandF__5CMathFv(math)) * lbl_8032FF08;
        }

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
        *valuePtr = value;
    } else {
        return;
    }

    valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
    f32 scale = *valuePtr;

    s32 colorOffset = in->sourceOffset;
    u8* target;
    if (colorOffset == -1) {
        target = lbl_801EADC8;
    } else {
        target = base + colorOffset + 0x80;
    }

    {
        target[0] = (u8)(target[0] + (s32)((f32)in->delta[0] * scale));
    }

    {
        target[1] = (u8)(target[1] + (s32)((f32)in->delta[1] * scale));
    }

    {
        target[2] = (u8)(target[2] + (s32)((f32)in->delta[2] * scale));
    }

    {
        target[3] = (u8)(target[3] + (s32)((f32)in->delta[3] * scale));
    }
}

/*
 * --INFO--
 * Address: TODO  
 * Size: TODO
 */
void randchar(char, float)
{
    // TODO - appears to be unused based on objdiff
}
