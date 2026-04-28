#include "ffcc/pppRandDownChar.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

const float kPppRandDownCharDualSampleScale = 0.5f;


struct PppRandDownCharParam2 {
    s32 field0;
    s32 field4;
    u8 field8;
    u8 field9;
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
void pppRandDownChar(void* basePtr, PppRandDownCharParam2* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)basePtr;
    f32* valuePtr;

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = -Math.RandF();
        if (in->field9 != 0) {
            f32 mixed = value - Math.RandF();
            f32 scale = kPppRandDownCharDualSampleScale;
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

    u8* target = (in->field4 == -1) ? gPppDefaultValueBuffer : (u8*)(base + in->field4 + 0x80);

    f32 factor = (f32)in->field8;
    f32 scaled = factor * *valuePtr;
    s32 delta = (s32)scaled;
    *target = (u8)(*target + delta);
}
