#include "ffcc/pppRandUpIV.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppRandUpIVDualSampleScale = 0.5f;
struct PppRandUpIVParam2 {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s32 field10;
    u8 field14[4];
    u8 field18;
};

struct PppRandUpIVParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x80062e0c
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandUpIV(void* param1, void* param2, void* param3)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)param1;
    PppRandUpIVParam2* in = (PppRandUpIVParam2*)param2;
    PppRandUpIVParam3* out = (PppRandUpIVParam3*)param3;
    f32 value;
    f32* valuePtr;

    if (in->field0 == *(s32*)(base + 0xC)) {
        value = Math.RandF();
        if (in->field18 != 0) {
            f32 randValue = value + Math.RandF();
            f32 scale = kPppRandUpIVDualSampleScale;
            value = randValue * scale;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != *(s32*)(base + 0xC)) {
            return;
        }
        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    s32* target = (in->field4 == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(base + in->field4 + 0x80);
    f32 scale = *valuePtr;

    target[0] += (s32)((f32)in->field8 * scale);
    target[1] += (s32)((f32)in->fieldC * scale);
    target[2] += (s32)((f32)in->field10 * scale);
}

#ifndef VERSION_GCCP01
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int randint(int value, float scale)
{
    return (int)((f32)value * scale);
}
#endif
