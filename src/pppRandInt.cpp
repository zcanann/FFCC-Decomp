#include "ffcc/pppRandInt.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

/*
 * --INFO--
 * PAL Address: 0x80062194
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */



struct RandIntParams {
    s32 targetId;
    s32 sourceOffset;
    u32 blend;
    u8 useNormalDistribution;
};

void pppRandInt(_pppPObject* basePtr, RandIntParams* in, _pppCtrlTable* ctrl)
{
    u8* base = (u8*)basePtr;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            value += Math.RandF();
        } else {
            value *= 2.0f;
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
    *target += (s32)((f32)in->blend * *valuePtr - (f32)in->blend);
}
