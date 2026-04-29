#include "ffcc/pppRandHCV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

typedef struct RandHCVParams {
    s32 targetId;
    s32 sourceOffset;
    s16 delta[4];
    u8 useNormalDistribution;
} RandHCVParams;

short randshort(short value, float scale)
{
    return (short)((f32)value * scale - (f32)value);
}

/*
 * --INFO--
 * PAL Address: 80061f88
 * PAL Size: 524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandHCV(_pppPObject* basePtr, RandHCVParams* in, _pppCtrlTable* ctrl)
{
    u8* base = (u8*)basePtr;
    s16* target;
    f32* randomValue;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (in->targetId == *(s32*)(base + 0xC)) {
        f32 value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            value += Math.RandF();
        } else {
            value *= 2.0f;
        }

        randomValue = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *randomValue = value;
    } else if (in->targetId != *(s32*)(base + 0xC)) {
        return;
    } else {
        randomValue = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    target = (in->sourceOffset == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(base + in->sourceOffset + 0x80);
    f32 scale = *randomValue;
    
    target[0] += randshort(in->delta[0], scale);
    target[1] += randshort(in->delta[1], scale);
    target[2] += randshort(in->delta[2], scale);
    target[3] += randshort(in->delta[3], scale);
}
