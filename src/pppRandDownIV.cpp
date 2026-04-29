#include "ffcc/pppRandDownIV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct PppRandDownIVParam2 {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s32 field10;
    u8 field14[4];
    u8 field18;
};

static inline int randint(int value, float scale)
{
    return (int)((float)value * scale);
}

/*
 * --INFO--
 * PAL Address: 0x80061a88
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandDownIV(_pppPObject* basePtr, PppRandDownIVParam2* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)basePtr;
    f32 value;
    f32* valuePtr;

    if (in->field0 == *(s32*)(base + 0xC)) {
        value = -Math.RandF();
        if (in->field18 != 0) {
            f32 randValue = value - Math.RandF();
            f32 scale = 0.5f;
            value = randValue * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else {
        if (in->field0 != *(s32*)(base + 0xC)) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    s32* target = (in->field4 == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(base + in->field4 + 0x80);
    f32 scale = *valuePtr;

    target[0] += randint(in->field8, scale);
    target[1] += randint(in->fieldC, scale);
    target[2] += randint(in->field10, scale);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
