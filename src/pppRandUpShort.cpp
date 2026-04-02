#include "ffcc/pppRandUpShort.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppRandUpShortDualSampleScale = 0.5f;
struct RandUpShortParam {
    s32 targetId;
    s32 sourceOffset;
    u16 scale;
    u8 randomTwice;
};

struct RandUpShortCtx {
    u8 _pad[0xC];
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 0x80062fa0
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandUpShort(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    RandUpShortParam* in = (RandUpShortParam*)param2;
    RandUpShortCtx* ctx = (RandUpShortCtx*)param3;
    s16* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        f32 value = Math.RandF();
        if (in->randomTwice != 0) {
            f32 mixed = value + Math.RandF();
            f32 scale = kPppRandUpShortDualSampleScale;
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

    target = (in->sourceOffset == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(base + in->sourceOffset + 0x80);

    u16 scale = in->scale;
    f32 scaled = (f32)scale * *valuePtr;
    s32 delta = (s32)scaled;
    *target = (s16)(*target + delta);
}
