#include "ffcc/pppRandDownInt.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandDownIntDataOffsets {
    s32 m_valueOffset;
};

STATIC_ASSERT(offsetof(RandDownIntDataOffsets, m_valueOffset) == 0x0);

static inline RandDownIntDataOffsets* GetRandDownIntDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandDownIntDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x80066ab4
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownInt(_pppPObject* basePtr, RandDownIntParams* in, _pppCtrlTable* ctrl)
{
    if (ppvUserStopPartF != 0) {
        return;
    }

    f32* valuePtr;

    s32 baseState = basePtr->m_graphId;
    if (baseState == 0) {
        f32 value = -Math.RandF();
        if (in->useNormalDistribution != 0) {
            f32 mixed = value - Math.RandF();
            f32 scale = 0.5f;
            value = mixed * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandDownIntDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != baseState) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + GetRandDownIntDataOffsets(ctrl)->m_valueOffset);
    }

    s32* target = (in->sourceOffset == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(basePtr->m_workArea + in->sourceOffset);
    f32 factor = (f32)in->blend;
    f32 scaled = factor * *valuePtr;
    s32 delta = (s32)scaled;
    
    *target += delta;
}
