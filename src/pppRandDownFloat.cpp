#include "ffcc/pppRandDownFloat.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern s32 lbl_8032ED70;
extern f32 lbl_8032FF38;
extern f32 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath*);

struct RandDownFloatParam {
    s32 targetId;
    s32 sourceOffset;
    f32 blend;
    u8 randomTwice;
};

struct RandDownFloatCtx {
    void* unk0;
    void* unk4;
    void* unk8;
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 0x8006155c
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void pppRandDownFloat(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    u8* base = (u8*)param1;
    RandDownFloatCtx* p3 = (RandDownFloatCtx*)param3;
    RandDownFloatParam* p2 = (RandDownFloatParam*)param2;
    f32* valuePtr;

    s32 id = *(s32*)(base + 0xC);
    if (id == 0) {
        f32 value = -RandF__5CMathFv(math);
        if (p2->randomTwice != 0) {
            value = lbl_8032FF38 * (value - RandF__5CMathFv(math));
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
    f32* source = (sourceOffset == -1) ? lbl_801EADC8 : (f32*)(base + sourceOffset + 0x80);

    f32 delta = p2->blend * *valuePtr;
    *source = *source + delta;
}
