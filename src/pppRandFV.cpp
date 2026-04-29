#include "ffcc/pppRandFV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct PppRandFVParam2 {
    s32 field0;
    s32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    u8 unk14[0x18 - 0x14];
    u8 field18;
};

static float randf(float value, float scale)
{
    return value * scale - value;
}

/*
 * --INFO--
 * PAL Address: 0x80061e54
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandFV(_pppPObject* basePtr, PppRandFVParam2* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)basePtr;
    f32* valuePtr;

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        f32 value = Math.RandF();
        if (in->field18 != 0) {
            value += Math.RandF();
        } else {
            value *= 2.0f;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else {
        if (in->field0 != state) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    f32* target = (in->field4 == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(base + in->field4 + 0x80);

    f32 x = in->field8;
    f32 scale = *valuePtr;
    target[0] = target[0] + randf(x, scale);
    target[1] = target[1] + randf(in->fieldC, scale);
    target[2] = target[2] + randf(in->field10, scale);
}
