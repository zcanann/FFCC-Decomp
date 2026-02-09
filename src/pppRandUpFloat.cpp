#include "ffcc/pppRandUpFloat.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math;
extern s32 lbl_8032ED70;
extern f32 lbl_8032FFF8;
extern f32 lbl_801EADC8;
extern "C" {
f32 RandF__5CMathFv(CMath*);
}

struct RandUpFloatParam {
    s32 targetId;
    s32 sourceOffset;
    f32 blend;
    u8 randomTwice;
};

struct RandUpFloatCtx {
    u8 unk0[0xC];
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 0x800628e0
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpFloat(void* param1, void* param2, void* param3) {
    if (lbl_8032ED70 != 0) {
        return;
    }

    u8* base = (u8*)param1;
    RandUpFloatCtx* p3 = (RandUpFloatCtx*)param3;
    RandUpFloatParam* p2 = (RandUpFloatParam*)param2;
    f32* valuePtr;

    s32 id = *(s32*)(base + 0xC);
    if (id == 0) {
        f32 value = RandF__5CMathFv(&math);

        if (p2->randomTwice != 0) {
            value = (value + RandF__5CMathFv(&math)) * lbl_8032FFF8;
        }

        valuePtr = (f32*)(base + *p3->outputOffset + 0x80);
        *valuePtr = value;
    } else {
        if (p2->targetId != id) {
            return;
        }
        valuePtr = (f32*)(base + *p3->outputOffset + 0x80);
    }

    s32 sourceOffset = p2->sourceOffset;
    f32* source;
    if (sourceOffset == -1) {
        source = &lbl_801EADC8;
    } else {
        source = (f32*)(base + sourceOffset + 0x80);
    }

    f32 delta = p2->blend * *valuePtr;
    *source = *source + delta;
}
