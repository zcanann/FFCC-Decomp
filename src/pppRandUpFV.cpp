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
    u8 useNormalDistribution;
};

float randf(float value, float scale)
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
void pppRandUpFV(_pppPObject* basePtr, RandUpFVParams* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    f32* valuePtr;
    s32 currentIndex = *(s32*)((u8*)basePtr + 0xC);
    if (currentIndex == 0) {
        f32 value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            f32 randomValue = value + Math.RandF();
            f32 scale = 0.5f;
            value = randomValue * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else {
        if (in->targetId != currentIndex) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    f32* target = (in->sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)((u8*)basePtr + in->sourceOffset + 0x80);

    target[0] += randf(in->blend[0], *valuePtr);
    target[1] += randf(in->blend[1], *valuePtr);
    target[2] += randf(in->blend[2], *valuePtr);
}
