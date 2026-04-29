#include "ffcc/pppRandDownHCV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandDownHCVParams {
    s32 targetId;
    s32 sourceOffset;
    s16 delta[4];
    u8 randomTwice;
};

static inline short randshort(short value, float scale)
{
    return (short)((f32)value * scale);
}

/*
 * --INFO--
 * PAL Address: 80061794
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandDownHCV(_pppPObject* basePtr, RandDownHCVParams* in, _pppCtrlTable* ctrl)
{
    u8* base = (u8*)basePtr;
    s16* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (in->targetId == *(s32*)(base + 0xC)) {
        f32 value = -Math.RandF();
        if (in->randomTwice != 0) {
            f32 random = Math.RandF();
            f32 blend = value - random;
            f32 scale = 0.5f;
            value = blend * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else if (in->targetId != *(s32*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    target = (in->sourceOffset == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(base + in->sourceOffset + 0x80);

    f32 scale = *valuePtr;

    target[0] = target[0] + randshort(in->delta[0], scale);
    target[1] = target[1] + randshort(in->delta[1], scale);
    target[2] = target[2] + randshort(in->delta[2], scale);
    target[3] = target[3] + randshort(in->delta[3], scale);
}
