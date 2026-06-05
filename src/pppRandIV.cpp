#include "ffcc/pppRandIV.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandIVDataOffsets {
    s32 m_valueOffset;
};

STATIC_ASSERT(offsetof(RandIVDataOffsets, m_valueOffset) == 0x0);

static inline RandIVDataOffsets* GetRandIVDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandIVDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline int randint(int value, float scale)
{
    return (int)((float)value * scale - (float)value);
}

/*
 * --INFO--
 * PAL Address: 0x800622d4
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandIV(_pppPObject* basePtr, RandIVParams* in, _pppCtrlTable* ctrl)
{
    f32 value;
    f32* valuePtr;

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (in->targetId == basePtr->m_graphId) {
        value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            value += Math.RandF();
        } else {
            value *= 2.0f;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandIVDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != basePtr->m_graphId) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + GetRandIVDataOffsets(ctrl)->m_valueOffset);
    }

    s32* target = (in->sourceOffset == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(basePtr->m_workArea + in->sourceOffset);
    f32 scale = *valuePtr;

    target[0] += randint(in->blend[0], scale);
    target[1] += randint(in->blend[1], scale);
    target[2] += randint(in->blend[2], scale);
}
