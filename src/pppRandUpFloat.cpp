#include "ffcc/pppRandUpFloat.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandUpFloatDataOffsets {
    s32 m_valueOffset;
};

STATIC_ASSERT(offsetof(RandUpFloatDataOffsets, m_valueOffset) == 0x0);

static inline RandUpFloatDataOffsets* GetRandUpFloatDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandUpFloatDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x800628e0
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpFloat(_pppPObject* basePtr, RandUpFloatParam* in, _pppCtrlTable* ctrl) {
    if (ppvUserStopPartF != 0) {
        return;
    }

    f32* valuePtr;

    s32 id = basePtr->m_graphId;
    if (id == 0) {
        f32 value = Math.RandF();

        if (in->useNormalDistribution != 0) {
            f32 randomValue = value + Math.RandF();
            f32 scale = 0.5f;
            value = randomValue * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandUpFloatDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else {
        if (in->targetId != id) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + GetRandUpFloatDataOffsets(ctrl)->m_valueOffset);
    }

    s32 sourceOffset = in->sourceOffset;
    f32* source = (sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(basePtr->m_workArea + sourceOffset);
    f32 delta = in->blend * *valuePtr;
    
    *source = *source + delta;
}
