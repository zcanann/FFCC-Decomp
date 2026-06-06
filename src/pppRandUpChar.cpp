#include "ffcc/pppRandUpChar.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

STATIC_ASSERT(sizeof(RandUpCharDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(RandUpCharDataOffsets, m_valueOffset) == 0x0);

static inline RandUpCharDataOffsets* GetRandUpCharDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandUpCharDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 800625dc
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpChar(_pppPObject* basePtr, RandUpCharParam* in, _pppCtrlTable* ctrl)
{
    u8* target;
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

        valuePtr = (f32*)(basePtr->m_workArea + GetRandUpCharDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + GetRandUpCharDataOffsets(ctrl)->m_valueOffset);
    }

    target = (in->sourceOffset == -1) ? gPppDefaultValueBuffer : (u8*)(basePtr->m_workArea + in->sourceOffset);
    f32 current = *valuePtr;
    f32 scaled = (f32)in->scale * current;
    s32 delta = (s32)scaled;
    
    *target = (u8)(*target + delta);
}
