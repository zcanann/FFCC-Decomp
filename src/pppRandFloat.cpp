#include "ffcc/pppRandFloat.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern s32 lbl_8032ED70;
extern f32 lbl_8032FF88;
extern f32 lbl_801EADC8;
extern "C" float RandF__5CMathFv(CMath* instance);

struct RandFloatParam {
    s32 targetId;
    s32 sourceOffset;
    f32 blend;
    u8 randomTwice;
};

struct RandFloatCtx {
    void* unk0;
    void* unk4;
    void* unk8;
    s32* outputOffset;
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
    RandFloatParam* in = (RandFloatParam*)param2;
    RandFloatCtx* ctx = (RandFloatCtx*)param3;
    u8* base;
    f32* valuePtr;

    if (lbl_8032ED70 != 0) {
        return;
    }

    base = (u8*)param1;
    s32 state = *(s32*)(base + 0xC);

    if (state == 0) {
        f32 value = RandF__5CMathFv(math);
        if (in->randomTwice != 0) {
            value += RandF__5CMathFv(math);
        } else {
            value *= lbl_8032FF88;
        }

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    f32* source;
    if (in->sourceOffset == -1) {
        source = &lbl_801EADC8;
    } else {
        source = (f32*)(base + in->sourceOffset + 0x80);
    }

    *source = *source + (in->blend * *valuePtr - in->blend);
}
