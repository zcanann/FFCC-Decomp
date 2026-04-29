#include "ffcc/pppRandUpInt.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandUpIntParams {
    s32 targetId;
    s32 sourceOffset;
    u32 blend;
    u8 useNormalDistribution;
};

/*
 * --INFO--
 * PAL Address: 0x80062ce0
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpInt(_pppPObject* basePtr, RandUpIntParams* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)basePtr;
    f32* valuePtr;

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            f32 mixed = value + Math.RandF();
            f32 scale = 0.5f;
            value = mixed * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else {
        if (in->targetId != baseState) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    s32* target = (in->sourceOffset == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(base + in->sourceOffset + 0x80);
    f32 scaled = (f32)in->blend * *valuePtr;
    s32 delta = (s32)scaled;
    
    *target += delta;
}
