#include "ffcc/pppRandDownFV.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern "C" f32 RandF__5CMathFv(CMath*);

/*
 * --INFO--
 * PAL Address: 0x80061664
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownFV(void* param1, void* param2, void* param3)
{
    extern int lbl_8032ED70;
    extern f32 lbl_8032FF40;
    extern f32 lbl_801EADC8[];

    struct RandDownFVParam {
        u32 field0;
        s32 field4;
        f32 field8;
        f32 fieldC;
        f32 field10;
        u8 field14[4];
        u8 field18;
    };
    struct RandDownFVCtx {
        u8 field0[0xC];
        s32* fieldC;
    };

    u8* base = (u8*)r3;
    RandDownFVParam* in = (RandDownFVParam*)r4;
    RandDownFVCtx* ctx = (RandDownFVCtx*)r5;
    s32 state;

    if (lbl_8032ED70 == 0) {
        return;
    }

    state = *(u32*)(base + 0xC);
    if (state == 0) {
        f32 value = -RandF__5CMathFv(math);
        if (in->field18 != 0) {
            value = (value - RandF__5CMathFv(math)) * lbl_8032FF40;
        }
        *(f32*)(base + *ctx->fieldC + 0x80) = value;
        return;
    }

    if (in->field0 != state) {
        return;
    }

    f32* target;
    if (in->field4 == -1) {
        target = lbl_801EADC8;
    } else {
        target = (f32*)(base + in->field4 + 0x80);
    }

    f32 value = *(f32*)(base + *ctx->fieldC + 0x80);
    target[0] += in->field8 * value;
    target[1] += in->fieldC * value;
    target[2] += in->field10 * value;
}
