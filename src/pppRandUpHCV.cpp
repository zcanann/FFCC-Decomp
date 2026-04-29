#include "ffcc/pppRandUpHCV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppRandUpHCVDualSampleScale = 0.5f;
struct PppRandUpHCVParam2 {
    s32 field0;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s16 fieldC;
    s16 fieldE;
    u8 field10;
};

inline short randshort(short value, float scale)
{
    return (short)((f32)value * scale);
}

/*
 * --INFO--
 * PAL Address: 80062B18
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandUpHCV(_pppPObject* basePtr, PppRandUpHCVParam2* in, _pppCtrlTable* ctrl)
{
    u8* base = (u8*)basePtr;
    s16* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (in->field0 == *(s32*)(base + 0xC)) {
        f32 value = Math.RandF();
        if (in->field10 != 0) {
            f32 random = Math.RandF();
            f32 blend = value + random;
            f32 scale = kPppRandUpHCVDualSampleScale;
            value = blend * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else if (in->field0 != *(s32*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    target = (in->field4 == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(base + in->field4 + 0x80);

    f32 scale = *valuePtr;

    target[0] = target[0] + randshort(in->field8, scale);
    target[1] = target[1] + randshort(in->fieldA, scale);
    target[2] = target[2] + randshort(in->fieldC, scale);
    target[3] = target[3] + randshort(in->fieldE, scale);
}
