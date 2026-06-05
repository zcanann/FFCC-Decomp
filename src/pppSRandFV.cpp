#include "ffcc/pppSRandFV.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "dolphin/types.h"
#include "ffcc/ppp_default_buffer.h"

struct SRandFVDataOffsets {
    s32 m_stateOffset;
};

STATIC_ASSERT(offsetof(SRandFVDataOffsets, m_stateOffset) == 0x0);

static inline SRandFVDataOffsets* GetSRandFVDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<SRandFVDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline float randf(unsigned char flag)
{
    float value = Math.RandF();
    if (flag != 0) {
        value = value + Math.RandF();
    } else {
        float scale = 2.0f;
        value = value * scale;
    }
    return value;
}

static inline float randfloat(float value, float scale)
{
    return value * scale - value;
}

/*
 * --INFO--
 * PAL Address: 0x80063c7c
 * PAL Size: 440b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandFV(_pppPObject* basePtr, SRandFVParams* in, _pppCtrlTable* ctrl)
{
    f32* randVec;
    if (ppvUserStopPartF != 0) {
        return;
    }

    s32 currentIndex = basePtr->m_graphId;
    if (currentIndex == 0) {
        randVec = (f32*)(basePtr->m_workArea + GetSRandFVDataOffsets(ctrl)->m_stateOffset);
        randVec[0] = randf(in->useNormalDistribution);
        randVec[1] = randf(in->useNormalDistribution);
        randVec[2] = randf(in->useNormalDistribution);
    } else {
        if (in->targetId != currentIndex) {
            return;
        }
        randVec = (f32*)(basePtr->m_workArea + GetSRandFVDataOffsets(ctrl)->m_stateOffset);
    }

    f32* target = (in->sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(basePtr->m_workArea + in->sourceOffset);

    target[0] += randfloat(in->blend[0], randVec[0]);
    target[1] += randfloat(in->blend[1], randVec[1]);
    target[2] += randfloat(in->blend[2], randVec[2]);
}
