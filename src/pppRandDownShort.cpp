#include "ffcc/pppRandDownShort.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern "C" f32 RandF__5CMathFv(CMath*);

extern s32 lbl_8032ED70;
extern f32 lbl_8032FF78;
extern f64 lbl_8032FF80;
extern s16 lbl_801EADC8[];

struct RandDownShortParam {
    s32 targetId;
    s32 sourceOffset;
    u16 scale;
    u8 randomTwice;
};

struct RandDownShortCtx {
    u8 _pad[0xC];
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 0x80061c1c
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandDownShort(void* r3, void* r4, void* r5)
{
    u8* base = (u8*)r3;
    RandDownShortParam* in = (RandDownShortParam*)r4;
    RandDownShortCtx* ctx = (RandDownShortCtx*)r5;
    s16* target;
    f32* valuePtr;

    if (lbl_8032ED70 != 0) {
        return;
    }

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        f32 value = -RandF__5CMathFv(&math[0]);
        if (in->randomTwice != 0) {
            f32 mixed = value - RandF__5CMathFv(&math[0]);
            value = mixed * lbl_8032FF78;
        }

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    target = (in->sourceOffset == -1) ? &lbl_801EADC8[0] : (s16*)(base + in->sourceOffset + 0x80);
    f32 scale = (f32)in->scale;
    f32 current = *valuePtr;
    f32 scaled = scale * current;
    s32 delta = (s32)scaled;
    *target = (s16)(*target + delta);
}
