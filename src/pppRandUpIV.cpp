#include "ffcc/pppRandUpIV.h"
#include "ffcc/math.h"
#include "types.h"

extern s32 DAT_8032ed70;
extern f32 DAT_80330028;
extern f64 DAT_80330030;
extern CMath math;
extern s32 DAT_801EADC8;

extern "C" {
float RandF__5CMathFv(CMath*);
}

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
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void randint(int param1, float param2)
{
    float temp = (float)param1 * param2;
    (void)temp;
}

/*
 * --INFO--
 * PAL Address: 0x80062e0c
 * PAL Size: 404b
 */
extern "C" void pppRandUpIV(void* param1, void* param2, void* param3)
{
    PppRandUpIVParam2* in = (PppRandUpIVParam2*)param2;
    u8* base = (u8*)param1;
    PppRandUpIVParam3* out = (PppRandUpIVParam3*)param3;
    f32* valuePtr;
    s32* target;
    f32 scale;

    if (DAT_8032ed70 == 0) {
        if (in->field0 == *(s32*)(base + 0xC)) {
            f32 value = RandF__5CMathFv(&math);

            if (in->field18 != 0) {
                value = (value + RandF__5CMathFv(&math)) * DAT_80330028;
            }

            valuePtr = (f32*)(base + *out->fieldC + 0x80);
            *valuePtr = value;
        } else if (in->field0 != *(s32*)(base + 0xC)) {
            return;
        } else {
            valuePtr = (f32*)(base + *out->fieldC + 0x80);
        }

        if (in->field4 == -1) {
            target = &DAT_801EADC8;
        } else {
            target = (s32*)(base + in->field4 + 0x80);
        }

        scale = *valuePtr;

        target[0] += (s32)((f32)in->field8 * scale);
        target[1] += (s32)((f32)in->fieldC * scale);
        target[2] += (s32)((f32)in->field10 * scale);
    }
}
