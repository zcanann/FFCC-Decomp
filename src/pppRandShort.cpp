#include "ffcc/pppRandShort.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppRandShortSingleSampleScale = 2.0f;
struct PppRandShortParam2 {
    s32 field0;
    s32 field4;
    u16 field8;
    u8 fieldA;
};

struct PppRandShortParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x8006249c
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandShort(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    PppRandShortParam2* in = (PppRandShortParam2*)param2;
    PppRandShortParam3* out = (PppRandShortParam3*)param3;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = Math.RandF();
        if (in->fieldA != 0) {
            value += Math.RandF();
        } else {
            value *= kPppRandShortSingleSampleScale;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != baseState) {
            return;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    s16* target = (in->field4 == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(base + in->field4 + 0x80);
    f32 delta = ((f32)in->field8 * *valuePtr) - (f32)in->field8;
    *target = (s16)(*target + (s16)delta);
}
