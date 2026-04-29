#include "ffcc/pppRandDownChar.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"



struct RandDownCharParams {
    s32 targetId;
    s32 sourceOffset;
    u8 blend;
    u8 randomTwice;
};

/*
 * --INFO--
 * PAL Address: 80061258
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownChar(_pppPObject* basePtr, RandDownCharParams* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)basePtr;
    f32* valuePtr;

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = -Math.RandF();
        if (in->randomTwice != 0) {
            f32 mixed = value - Math.RandF();
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

    u8* target = (in->sourceOffset == -1) ? gPppDefaultValueBuffer : (u8*)(base + in->sourceOffset + 0x80);

    f32 factor = (f32)in->blend;
    f32 scaled = factor * *valuePtr;
    s32 delta = (s32)scaled;
    *target = (u8)(*target + delta);
}
