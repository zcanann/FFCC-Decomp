#include "ffcc/pppRandChar.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

STATIC_ASSERT(sizeof(RandCharDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(RandCharDataOffsets, m_valueOffset) == 0x0);

static inline RandCharDataOffsets* GetRandCharDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandCharDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x80060efc
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandChar(_pppPObject* basePtr, RandCharParam* in, _pppCtrlTable* ctrl)
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
            value += Math.RandF();
        } else {
            value *= 2.0f;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandCharDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + GetRandCharDataOffsets(ctrl)->m_valueOffset);
    }

    s32 colorOffset = in->sourceOffset;
    target = (colorOffset == -1) ? gPppDefaultValueBuffer : (u8*)(basePtr->m_workArea + colorOffset);

    u8 scale = in->scale;
    s32 delta = (s32)((f32)scale * *valuePtr - (f32)scale);
    *target = (u8)(*target + delta);
}
