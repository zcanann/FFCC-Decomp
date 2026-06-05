#include "ffcc/pppRandDownFV.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandDownFVDataOffsets {
    s32 m_valueOffset;
};

STATIC_ASSERT(offsetof(RandDownFVDataOffsets, m_valueOffset) == 0x0);

static inline RandDownFVDataOffsets* GetRandDownFVDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandDownFVDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline float randf(float value, float scale)
{
    float result = value * scale;
    return result;
}

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
    if (ppvUserStopPartF != 0) {
        return;
    }

    f32* valuePtr;

    s32 baseState = basePtr->m_graphId;
    if (baseState == 0) {
        f32 value = -Math.RandF();
        if (in->useNormalDistribution != 0) {
            f32 randomValue = value - Math.RandF();
            f32 scale = 0.5f;
            value = randomValue * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandDownFVDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != baseState) {
            return;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandDownFVDataOffsets(ctrl)->m_valueOffset);
    }

    s32 sourceOffset = in->sourceOffset;
    f32* target = (sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(basePtr->m_workArea + sourceOffset);
    f32 delta = randf(in->blend[0], *valuePtr);
    f32 scale = *valuePtr;

    target[0] = delta + target[0];
    target[1] += randf(in->blend[1], scale);
    target[2] += randf(in->blend[2], scale);
}
