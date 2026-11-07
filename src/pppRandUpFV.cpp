#include "ffcc/pppRandUpFV.h"
#include "global.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

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
void pppRandUpFV(_pppPObject* basePtr, RandUpFVParams* in, _pppCtrlTable* ctrl)
{
    if (ppvUserStopPartF != 0) {
        return;
    }

    f32* valuePtr;
    s32 currentIndex = basePtr->m_graphId;
    if (currentIndex == 0) {
        f32 value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            f32 randomValue = value + Math.RandF();
            f32 scale = 0.5f;
            value = randomValue * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + ctrl->m_serializedDataOffsets[0]);
        *valuePtr = value;
    } else {
        if (in->targetId != currentIndex) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + ctrl->m_serializedDataOffsets[0]);
    }

    f32* target = (in->sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(basePtr->m_workArea + in->sourceOffset);
    f32 x = in->blend[0];
    f32 scale = *valuePtr;

    target[0] += randf(x, scale);
    x = in->blend[1];
    target[1] += randf(x, scale);
    x = in->blend[2];
    target[2] += randf(x, scale);
}
