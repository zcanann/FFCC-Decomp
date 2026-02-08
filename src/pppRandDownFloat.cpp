#include "ffcc/pppRandDownFloat.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern s32 lbl_8032ED70;
extern f32 lbl_8032FF38;
extern f32 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath*);

struct RandDownFloatParam {
    s32 targetId;
    s32 sourceOffset;
    f32 blend;
    u8 randomTwice;
};

struct RandDownFloatCtx {
    void* unk0;
    void* unk4;
    void* unk8;
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 0x8006155c
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void pppRandDownFloat(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    RandDownFloatCtx* ctx = (RandDownFloatCtx*)param3;
    RandDownFloatParam* in = (RandDownFloatParam*)param2;
    f32* out;

    if (lbl_8032ED70 != 0) {
        return;
    }

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        f32 value = -RandF__5CMathFv(math);
        if (in->randomTwice != 0) {
            value = (value - RandF__5CMathFv(math)) * lbl_8032FF38;
        }

        out = (f32*)(base + *ctx->outputOffset + 0x80);
        *out = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        out = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    f32* source;
    if (in->sourceOffset == -1) {
        source = &lbl_801EADC8[0];
    } else {
        source = (f32*)(base + in->sourceOffset + 0x80);
    }

    *source = *source + (in->blend * *out);
}
