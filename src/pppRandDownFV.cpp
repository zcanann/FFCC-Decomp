#include "ffcc/pppRandDownFV.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

extern "C" {
f32 RandF__5CMathFv(CMath*);
}

struct RandDownFVParams {
    s32 targetId;
    s32 sourceOffset;
    f32 blend[3];
    u8 _pad[0x18 - 0x14];
    u8 useNormalDistribution;
};

struct RandDownFVControl {
    u8 _pad0[0xC];
    s32* serializedDataOffsets;
};

/*
 * --INFO--
 * PAL Address: 0x80061664
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownFV(_pppPObject* basePtr, RandDownFVParams* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)basePtr;
    RandDownFVControl* out = (RandDownFVControl*)ctrl;
    f32* valuePtr;

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = -RandF__5CMathFv(&Math);
        if (in->useNormalDistribution != 0) {
            f32 randomValue = value - RandF__5CMathFv(&Math);
            value = randomValue * 0.5f;
        }

        valuePtr = (f32*)(base + *out->serializedDataOffsets + 0x80);
        *valuePtr = value;
    } else {
        if (in->targetId != baseState) {
            return;
        }

        valuePtr = (f32*)(base + *out->serializedDataOffsets + 0x80);
    }

    s32 sourceOffset = in->sourceOffset;
    f32* target = (sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(base + sourceOffset + 0x80);

    f32 base0 = target[0];
    f32 value = in->blend[0];
    f32 scale = *valuePtr;
    f32 delta0 = value * scale;
    target[0] = base0 + delta0;

    value = in->blend[1] * scale;
    target[1] = target[1] + value;
    value = in->blend[2] * scale;
    target[2] = target[2] + value;
}
