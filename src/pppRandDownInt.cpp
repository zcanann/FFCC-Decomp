#include "ffcc/pppRandDownInt.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppRandDownIntDualSampleScale = 0.5f;
struct PppRandDownIntParam2 {
    s32 field0;
    s32 field4;
    u32 field8;
    u8 fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x80066ab4
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownInt(_pppPObject* basePtr, PppRandDownIntParam2* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)basePtr;
    f32* valuePtr;

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = -Math.RandF();
        if (in->fieldC != 0) {
            f32 mixed = value - Math.RandF();
            f32 scale = kPppRandDownIntDualSampleScale;
            value = mixed * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else {
        if (in->field0 != baseState) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    s32* target = (in->field4 == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(base + in->field4 + 0x80);

    f32 factor = (f32)in->field8;
    f32 scaled = factor * *valuePtr;
    s32 delta = (s32)scaled;
    *target += delta;
}
