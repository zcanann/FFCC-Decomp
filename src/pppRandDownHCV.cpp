#include "ffcc/pppRandDownHCV.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"

const float kPppRandDownHCVDualSampleScale = 0.5f;
extern s16 gPppDefaultValueBuffer[];


struct PppRandDownHCVParam2 {
    s32 field0;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s16 fieldC;
    s16 fieldE;
    u8 field10;
};

struct PppRandDownHCVParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 80061794
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandDownHCV(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    PppRandDownHCVParam2* in = (PppRandDownHCVParam2*)param2;
    PppRandDownHCVParam3* out = (PppRandDownHCVParam3*)param3;
    s16* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (in->field0 == *(s32*)(base + 0xC)) {
        f32 value = -Math.RandF();
        if (in->field10 != 0) {
            f32 random = Math.RandF();
            f32 blend = value - random;
            f32 scale = kPppRandDownHCVDualSampleScale;
            value = blend * scale;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else if (in->field0 != *(s32*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    target = (in->field4 == -1) ? &gPppDefaultValueBuffer[0] : (s16*)(base + in->field4 + 0x80);

    f32 scale = *valuePtr;

    {
        s16 baseValue = in->field8;
        target[0] = (s16)(target[0] + (s32)((f32)baseValue * scale));
    }
    {
        s16 baseValue = in->fieldA;
        target[1] = (s16)(target[1] + (s32)((f32)baseValue * scale));
    }
    {
        s16 baseValue = in->fieldC;
        target[2] = (s16)(target[2] + (s32)((f32)baseValue * scale));
    }
    {
        s16 baseValue = in->fieldE;
        target[3] = (s16)(target[3] + (s32)((f32)baseValue * scale));
    }
}
