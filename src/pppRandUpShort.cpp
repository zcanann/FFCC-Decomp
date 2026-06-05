#include "ffcc/pppRandUpShort.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandUpShortDataOffsets {
    s32 m_valueOffset;
};

STATIC_ASSERT(offsetof(RandUpShortDataOffsets, m_valueOffset) == 0x0);

static inline RandUpShortDataOffsets* GetRandUpShortDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandUpShortDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x80062fa0
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpShort(_pppPObject* basePtr, RandUpShortParam* in, _pppCtrlTable* ctrl)
{
    s16* target;
    f32* valuePtr;

    if (ppvUserStopPartF != 0) {
        return;
    }

    s32 state = basePtr->m_graphId;
    if (state == 0) {
        f32 value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            f32 mixed = value + Math.RandF();
            f32 scale = 0.5f;
            value = mixed * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandUpShortDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + GetRandUpShortDataOffsets(ctrl)->m_valueOffset);
    }

    target = (in->sourceOffset == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(basePtr->m_workArea + in->sourceOffset);
    u16 scale = in->scale;
    f32 scaled = (f32)scale * *valuePtr;
    s32 delta = (s32)scaled;
    
    *target = (s16)(*target + delta);
}
