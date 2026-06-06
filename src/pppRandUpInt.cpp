#include "ffcc/pppRandUpInt.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

STATIC_ASSERT(sizeof(RandUpIntDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(RandUpIntDataOffsets, m_valueOffset) == 0x0);

static inline RandUpIntDataOffsets* GetRandUpIntDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandUpIntDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x80062ce0
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpInt(_pppPObject* basePtr, RandUpIntParams* in, _pppCtrlTable* ctrl)
{
    if (ppvUserStopPartF != 0) {
        return;
    }

    f32* valuePtr;

    s32 baseState = basePtr->m_graphId;
    if (baseState == 0) {
        f32 value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            f32 mixed = value + Math.RandF();
            f32 scale = 0.5f;
            value = mixed * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandUpIntDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != baseState) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + GetRandUpIntDataOffsets(ctrl)->m_valueOffset);
    }

    s32* target = (in->sourceOffset == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(basePtr->m_workArea + in->sourceOffset);
    f32 scaled = (f32)in->blend * *valuePtr;
    s32 delta = (s32)scaled;
    
    *target += delta;
}
