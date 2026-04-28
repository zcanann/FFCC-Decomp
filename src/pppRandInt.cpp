#include "ffcc/pppRandInt.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppRandIntSingleSampleScale = 2.0f;
/*
 * --INFO--
 * PAL Address: 0x80062194
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */



struct PppRandIntParam2 {
    s32 field0;
    s32 field4;
    u32 field8;
    u8 fieldC;
};

void pppRandInt(void* basePtr, PppRandIntParam2* in, _pppCtrlTable* ctrl)
{
    u8* base = (u8*)basePtr;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = Math.RandF();
        if (in->fieldC != 0) {
            value += Math.RandF();
        } else {
            value *= kPppRandIntSingleSampleScale;
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
    *target += (s32)((f32)in->field8 * *valuePtr - (f32)in->field8);
}
