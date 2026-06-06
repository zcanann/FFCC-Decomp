#include "ffcc/pppRandDownIV.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

STATIC_ASSERT(sizeof(RandDownIVDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(RandDownIVDataOffsets, m_valueOffset) == 0x0);

static inline RandDownIVDataOffsets* GetRandDownIVDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandDownIVDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static inline int randint(int value, float scale)
{
    return (int)((float)value * scale);
}

/*
 * --INFO--
 * PAL Address: 0x80061a88
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownIV(_pppPObject* basePtr, RandDownIVParams* in, _pppCtrlTable* ctrl)
{
    if (ppvUserStopPartF != 0) {
        return;
    }

    f32 value;
    f32* valuePtr;

    if (in->targetId == basePtr->m_graphId) {
        value = -Math.RandF();
        if (in->useNormalDistribution != 0) {
            f32 randValue = value - Math.RandF();
            f32 scale = 0.5f;
            value = randValue * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandDownIVDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != basePtr->m_graphId) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + GetRandDownIVDataOffsets(ctrl)->m_valueOffset);
    }

    s32* target = (in->sourceOffset == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(basePtr->m_workArea + in->sourceOffset);
    f32 scale = *valuePtr;

    target[0] += randint(in->blend[0], scale);
    target[1] += randint(in->blend[1], scale);
    target[2] += randint(in->blend[2], scale);
}
