#include "ffcc/pppRandUpChar.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

const float kPppRandUpCharDualSampleScale = 0.5f;

struct RandUpCharParam {
    s32 targetId;
    s32 sourceOffset;
    u8 scale;
    u8 randomTwice;
};

struct RandUpCharCtx {
    u8 _pad[0xC];
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 800625dc
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandUpChar(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    RandUpCharParam* in = (RandUpCharParam*)param2;
    RandUpCharCtx* ctx = (RandUpCharCtx*)param3;
    u8* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        f32 value = Math.RandF();
        if (in->randomTwice != 0) {
            f32 mixed = value + Math.RandF();
            f32 scale = kPppRandUpCharDualSampleScale;
            value = mixed * scale;
        }

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    target = (in->sourceOffset == -1) ? gPppDefaultValueBuffer : (u8*)(base + in->sourceOffset + 0x80);

    f32 current = *valuePtr;
    f32 scaled = (f32)in->scale * current;
    s32 delta = (s32)scaled;
    *target = (u8)(*target + delta);
}
