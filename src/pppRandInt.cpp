#include "ffcc/pppRandInt.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandIntDataOffsets {
    s32 m_valueOffset;
};

STATIC_ASSERT(offsetof(RandIntDataOffsets, m_valueOffset) == 0x0);

static inline RandIntDataOffsets* GetRandIntDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandIntDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x80062194
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandInt(_pppPObject* basePtr, RandIntParams* in, _pppCtrlTable* ctrl)
{
    f32* valuePtr;

    if (ppvUserStopPartF != 0) {
        return;
    }

    s32 baseState = basePtr->m_graphId;
    if (baseState == 0) {
        f32 value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            value += Math.RandF();
        } else {
            value *= 2.0f;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandIntDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != baseState) {
            return;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandIntDataOffsets(ctrl)->m_valueOffset);
    }

    s32* target = (in->sourceOffset == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(basePtr->m_workArea + in->sourceOffset);
    
    *target += (s32)((f32)in->blend * *valuePtr - (f32)in->blend);
}
