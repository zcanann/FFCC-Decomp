#include "ffcc/pppRandUpFV.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandUpFVParams {
    s32 targetId;
    s32 sourceOffset;
    f32 blend[3];
    u8 _pad[4];
    u8 randomTwice;
};

static inline float randf(float value, float scale)
{
    return value * scale;
}

/*
 * --INFO--
 * PAL Address: 0x800629e8
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpFV(_pppPObject* basePtrIn, RandUpFVParams* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)basePtrIn;
    f32* valuePtr;

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        f32 value = Math.RandF();
        if (in->randomTwice != 0) {
            f32 randomValue = value + Math.RandF();
            f32 scale = 0.5f;
            value = randomValue * scale;
        }

        valuePtr = (f32*)(basePtrIn->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        valuePtr = (f32*)(basePtrIn->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    s32 sourceOffset = in->sourceOffset;
    f32* target = (sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(base + sourceOffset + 0x80);

    f32 scale = *valuePtr;
    target[0] = target[0] + randf(in->blend[0], scale);
    target[1] = target[1] + randf(in->blend[1], scale);
    target[2] = target[2] + randf(in->blend[2], scale);
}
