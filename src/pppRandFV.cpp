#include "ffcc/pppRandFV.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandFVDataOffsets {
    s32 m_valueOffset;
};

STATIC_ASSERT(offsetof(RandFVDataOffsets, m_valueOffset) == 0x0);

static inline RandFVDataOffsets* GetRandFVDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandFVDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline float randf(float value, float scale)
{
    return value * scale - value;
}

/*
 * --INFO--
 * PAL Address: 0x80061e54
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandFV(_pppPObject* basePtr, RandFVParams* in, _pppCtrlTable* ctrl)
{
    if (ppvUserStopPartF != 0) {
        return;
    }

    f32* valuePtr;

    s32 state = basePtr->m_graphId;
    if (state == 0) {
        f32 value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            value += Math.RandF();
        } else {
            value *= 2.0f;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandFVDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + GetRandFVDataOffsets(ctrl)->m_valueOffset);
    }

    f32* target = (in->sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(basePtr->m_workArea + in->sourceOffset);
    f32 x = in->blend[0];
    f32 scale = *valuePtr;

    target[0] += randf(x, scale);
    target[1] += randf(in->blend[1], scale);
    target[2] += randf(in->blend[2], scale);
}
