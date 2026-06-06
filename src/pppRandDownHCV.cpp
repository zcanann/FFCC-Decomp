#include "ffcc/pppRandDownHCV.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

STATIC_ASSERT(sizeof(RandDownHCVDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(RandDownHCVDataOffsets, m_valueOffset) == 0x0);

static inline RandDownHCVDataOffsets* GetRandDownHCVDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandDownHCVDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline short randshort(short value, float scale)
{
    return (short)((f32)value * scale);
}

/*
 * --INFO--
 * PAL Address: 80061794
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownHCV(_pppPObject* basePtr, RandDownHCVParams* in, _pppCtrlTable* ctrl)
{
    s16* target;
    f32* valuePtr;

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (in->targetId == basePtr->m_graphId) {
        f32 value = -Math.RandF();
        if (in->useNormalDistribution != 0) {
            f32 random = Math.RandF();
            f32 blend = value - random;
            f32 scale = 0.5f;
            value = blend * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandDownHCVDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else if (in->targetId != basePtr->m_graphId) {
        return;
    } else {
        valuePtr = (f32*)(basePtr->m_workArea + GetRandDownHCVDataOffsets(ctrl)->m_valueOffset);
    }

    target = (in->sourceOffset == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(basePtr->m_workArea + in->sourceOffset);
    f32 scale = *valuePtr;

    target[0] += randshort(in->delta[0], scale);
    target[1] += randshort(in->delta[1], scale);
    target[2] += randshort(in->delta[2], scale);
    target[3] += randshort(in->delta[3], scale);
}
