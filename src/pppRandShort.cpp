#include "ffcc/pppRandShort.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

STATIC_ASSERT(sizeof(RandShortDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(RandShortDataOffsets, m_valueOffset) == 0x0);

static inline RandShortDataOffsets* GetRandShortDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandShortDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x8006249c
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandShort(_pppPObject* basePtr, RandShortParams* in, _pppCtrlTable* ctrl)
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

        valuePtr = (f32*)(basePtr->m_workArea + GetRandShortDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != baseState) {
            return;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandShortDataOffsets(ctrl)->m_valueOffset);
    }

    s16* target = (in->sourceOffset == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(basePtr->m_workArea + in->sourceOffset);
    f32 delta = ((f32)in->blend * *valuePtr) - (f32)in->blend;
    
    *target = (s16)(*target + (s16)delta);
}
