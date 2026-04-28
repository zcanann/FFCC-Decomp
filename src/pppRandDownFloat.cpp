#include "ffcc/pppRandDownFloat.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppRandDownFloatDualSampleScale = 0.5f;
struct RandDownFloatParam {
    s32 targetId;
    s32 sourceOffset;
    f32 blend;
    u8 randomTwice;
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
void pppRandDownFloat(void* basePtr, RandDownFloatParam* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)basePtr;
    f32* valuePtr;

    s32 id = *(s32*)(base + 0xC);
    if (id == 0) {
        f32 value = -Math.RandF();
        if (in->randomTwice != 0) {
            f32 randomValue = value - Math.RandF();
            f32 scale = kPppRandDownFloatDualSampleScale;
            value = randomValue * scale;
        }

        valuePtr = (f32*)(base + *ctrl->m_serializedDataOffsets + 0x80);
        *valuePtr = value;
    } else {
        if (in->targetId != id) {
            return;
        }
        valuePtr = (f32*)(base + *ctrl->m_serializedDataOffsets + 0x80);
    }

    s32 sourceOffset = in->sourceOffset;
    f32* source = (sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(base + sourceOffset + 0x80);

    f32 delta = in->blend * *valuePtr;
    *source = *source + delta;
}
