#include "ffcc/pppRandFloat.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppRandFloatSingleSampleScale = 2.0f;
struct RandFloatParam {
    s32 targetId;
    s32 sourceOffset;
    f32 blend;
    u8 randomTwice;
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
void pppRandFloat(void* basePtrIn, RandFloatParam* in, _pppCtrlTable* ctrl)
{
    u8* base;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    base = (u8*)basePtrIn;
    s32 state = *(s32*)(base + 0xC);

    if (state == 0) {
        f32 value = Math.RandF();
        if (in->randomTwice != 0) {
            value += Math.RandF();
        } else {
            value *= kPppRandFloatSingleSampleScale;
        }

        valuePtr = (f32*)(base + *ctrl->m_serializedDataOffsets + 0x80);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        valuePtr = (f32*)(base + *ctrl->m_serializedDataOffsets + 0x80);
    }

    s32 sourceOffset = in->sourceOffset;
    f32* source = (sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(base + sourceOffset + 0x80);

    *source = *source + (in->blend * *valuePtr - in->blend);
}
