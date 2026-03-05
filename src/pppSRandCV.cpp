#include "ffcc/pppSRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math[];
extern int lbl_8032ED70;
extern float lbl_80330060;
extern u8 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath* instance);

struct PppSRandCVParam2 {
    s32 field0;
    s32 field4;
    s8 field8;
    s8 field9;
    s8 fieldA;
    s8 fieldB;
    u8 fieldC;
};

struct PppSRandCVParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * --INFO--
 * PAL Address: 800632d0
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandCV(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    PppSRandCVParam2* in = (PppSRandCVParam2*)param2;
    PppSRandCVParam3* out = (PppSRandCVParam3*)param3;

    if (lbl_8032ED70 != 0) {
        return;
    }

    float* target;

    if (in->field0 == *(s32*)(base + 0xC)) {
        target = (float*)(base + *out->fieldC + 0x80);

        {
            u8 flag = in->fieldC;
            float value = RandF__5CMathFv(&math[0]);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&math[0]);
            } else {
                value = value * lbl_80330060;
            }
            target[0] = value;
        }

        {
            u8 flag = in->fieldC;
            float value = RandF__5CMathFv(&math[0]);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&math[0]);
            } else {
                value = value * lbl_80330060;
            }
            target[1] = value;
        }

        {
            u8 flag = in->fieldC;
            float value = RandF__5CMathFv(&math[0]);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&math[0]);
            } else {
                value = value * lbl_80330060;
            }
            target[2] = value;
        }

        {
            u8 flag = in->fieldC;
            float value = RandF__5CMathFv(&math[0]);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&math[0]);
            } else {
                value = value * lbl_80330060;
            }
            target[3] = value;
        }
    } else {
        if (in->field0 != *(s32*)(base + 0xC)) {
            return;
        }
        target = (float*)(base + *out->fieldC + 0x80);
    }

    u8* color = (in->field4 == -1) ? lbl_801EADC8 : (u8*)(base + in->field4 + 0x80);

    s8 baseValue = in->field8;
    color[0] = (u8)(color[0] + (s32)((f32)baseValue * target[0] - (f32)baseValue));

    baseValue = in->field9;
    color[1] = (u8)(color[1] + (s32)((f32)baseValue * target[1] - (f32)baseValue));

    baseValue = in->fieldA;
    color[2] = (u8)(color[2] + (s32)((f32)baseValue * target[2] - (f32)baseValue));

    baseValue = in->fieldB;
    color[3] = (u8)(color[3] + (s32)((f32)baseValue * target[3] - (f32)baseValue));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randchar(char, float)
{
    // TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randf(unsigned char)
{
    // TODO
}

#ifdef __cplusplus
}
#endif
