#include "ffcc/pppRandDownCV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

const float kPppRandDownCVDualSampleScale = 0.5f;

struct PppRandDownCVParam2 {
    s32 field0;
    s32 field4;
    s8 field8;
    s8 field9;
    s8 fieldA;
    s8 fieldB;
    u8 fieldC;
};

inline char randchar(char value, float scale)
{
    return (char)((f32)value * scale);
}

/*
 * --INFO--
 * PAL Address: 80061384
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandDownCV(void* basePtr, PppRandDownCVParam2* in, _pppCtrlTable* ctrl)
{
    u8* base = (u8*)basePtr;
    u8* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (in->field0 == *(s32*)(base + 0xC)) {
        f32 value = -Math.RandF();
        if (in->fieldC != 0) {
            f32 random = Math.RandF();
            f32 blend = value - random;
            f32 scale = kPppRandDownCVDualSampleScale;
            value = blend * scale;
        }

        valuePtr = (f32*)(base + *ctrl->m_serializedDataOffsets + 0x80);
        *valuePtr = value;
    } else if (in->field0 != *(s32*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(base + *ctrl->m_serializedDataOffsets + 0x80);
    }

    target = (in->field4 == -1) ? &gPppDefaultValueBuffer[0] : (u8*)(base + in->field4 + 0x80);

    f32 scale = *valuePtr;
    {
        s8 baseValue = in->field8;
        target[0] = (u8)(target[0] + randchar(baseValue, scale));
    }
    {
        s8 baseValue = in->field9;
        target[1] = (u8)(target[1] + randchar(baseValue, scale));
    }
    {
        s8 baseValue = in->fieldA;
        target[2] = (u8)(target[2] + randchar(baseValue, scale));
    }
    {
        s8 baseValue = in->fieldB;
        target[3] = (u8)(target[3] + randchar(baseValue, scale));
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
