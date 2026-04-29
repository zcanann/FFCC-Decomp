#include "ffcc/pppRandDownShort.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandDownShortParam {
    s32 targetId;
    s32 sourceOffset;
    u16 scale;
    u8 useNormalDistribution;
};

/*
 * --INFO--
 * PAL Address: 0x80061c1c
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownShort(_pppPObject* basePtr, RandDownShortParam* in, _pppCtrlTable* ctrl)
{
    u8* base = (u8*)basePtr;
    s16* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        f32 value = -Math.RandF();
        if (in->useNormalDistribution != 0) {
            f32 mixed = value - Math.RandF();
            f32 scale = 0.5f;
            value = mixed * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    target = (in->sourceOffset == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(base + in->sourceOffset + 0x80);
    f32 scale = (f32)in->scale;
    f32 current = *valuePtr;
    f32 scaled = scale * current;
    s32 delta = (s32)scaled;
    *target = (s16)(*target + delta);
}
