#include "ffcc/pppRandChar.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"


struct RandCharParam {
    s32 targetId;
    s32 sourceOffset;
    u8 scale;
    u8 useNormalDistribution;
};

/*
 * --INFO--
 * PAL Address: 0x80060efc
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandChar(_pppPObject* basePtr, RandCharParam* in, _pppCtrlTable* ctrl)
{
    u8* base = (u8*)basePtr;
    u8* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        f32 value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            value += Math.RandF();
        } else {
            value *= 2.0f;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    s32 colorOffset = in->sourceOffset;
    target = (colorOffset == -1) ? gPppDefaultValueBuffer : (u8*)(base + colorOffset + 0x80);

    u8 scale = in->scale;
    s32 delta = (s32)((f32)scale * *valuePtr - (f32)scale);
    *target = (u8)(*target + delta);
}
