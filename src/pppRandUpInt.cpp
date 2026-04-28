#include "ffcc/pppRandUpInt.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppRandUpIntDualSampleScale = 0.5f;
struct PppRandUpIntParam2 {
    s32 field0;
    s32 field4;
    u32 field8;
    u8 fieldC;
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
void pppRandUpInt(void* basePtr, PppRandUpIntParam2* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)basePtr;
    f32* valuePtr;

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = Math.RandF();
        if (in->fieldC != 0) {
            f32 mixed = value + Math.RandF();
            f32 scale = kPppRandUpIntDualSampleScale;
            value = mixed * scale;
        }

        valuePtr = (f32*)(base + *ctrl->m_serializedDataOffsets + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != baseState) {
            return;
        }
        valuePtr = (f32*)(base + *ctrl->m_serializedDataOffsets + 0x80);
    }

    s32* target = (in->field4 == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(base + in->field4 + 0x80);

    f32 scaled = (f32)in->field8 * *valuePtr;
    s32 delta = (s32)scaled;
    *target += delta;
}
