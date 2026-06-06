#include "ffcc/pppRandFloat.h"
#include "global.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

STATIC_ASSERT(sizeof(RandFloatDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(RandFloatDataOffsets, m_valueOffset) == 0x0);

static inline RandFloatDataOffsets* GetRandFloatDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandFloatDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x80061d48
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandFloat(_pppPObject* basePtrIn, RandFloatParam* in, _pppCtrlTable* ctrl)
{
    f32* valuePtr;

    if (ppvUserStopPartF != 0) {
        return;
    }

    s32 state = basePtrIn->m_graphId;

    if (state == 0) {
        f32 value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            value += Math.RandF();
        } else {
            value *= 2.0f;
        }

        valuePtr = (f32*)(basePtrIn->m_workArea + GetRandFloatDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        valuePtr = (f32*)(basePtrIn->m_workArea + GetRandFloatDataOffsets(ctrl)->m_valueOffset);
    }

    s32 sourceOffset = in->sourceOffset;
    f32* source = (sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(basePtrIn->m_workArea + sourceOffset);

    *source = *source + (in->blend * *valuePtr - in->blend);
}
