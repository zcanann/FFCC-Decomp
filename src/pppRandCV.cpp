#include "ffcc/pppRandCV.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

struct RandCVDataOffsets {
    s32 m_valueOffset;
};

STATIC_ASSERT(offsetof(RandCVDataOffsets, m_valueOffset) == 0x0);

static inline RandCVDataOffsets* GetRandCVDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<RandCVDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline char randchar(char value, float scale)
{
    return (char)((f32)value * scale - (f32)value);
}

/*
 * --INFO--
 * PAL Address: 0x8006103C
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandCV(_pppPObject* basePtr, RandCVParams* in, _pppCtrlTable* ctrl)
{
    f32* valuePtr;

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (in->index == basePtr->m_graphId) {
        f32 value = Math.RandF();
        if (in->flag != 0) {
            value += Math.RandF();
        } else {
            value *= 2.0f;
        }

        valuePtr = (f32*)(basePtr->m_workArea + GetRandCVDataOffsets(ctrl)->m_valueOffset);
        *valuePtr = value;
    } else if (in->index != basePtr->m_graphId) {
        return;
    } else {
        valuePtr = (f32*)(basePtr->m_workArea + GetRandCVDataOffsets(ctrl)->m_valueOffset);
    }

    u8* targetColor = (in->colorOffset == -1) ? gPppDefaultValueBuffer : (basePtr->m_workArea + in->colorOffset);
    f32 scale = *valuePtr;
    
    targetColor[0] += randchar(in->delta[0], scale);
    targetColor[1] += randchar(in->delta[1], scale);
    targetColor[2] += randchar(in->delta[2], scale);
    targetColor[3] += randchar(in->delta[3], scale);
}
