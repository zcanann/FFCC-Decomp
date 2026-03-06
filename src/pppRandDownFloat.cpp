#include "ffcc/pppRandDownFloat.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath Math;
extern int gPppCalcDisabled;
extern f32 lbl_8032FF38;
extern f32 gPppDefaultValueBuffer[];
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
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)param1;
    RandDownFloatCtx* p3 = (RandDownFloatCtx*)param3;
    RandDownFloatParam* p2 = (RandDownFloatParam*)param2;
    f32* valuePtr;

    s32 id = *(s32*)(base + 0xC);
    if (id == 0) {
        f32 value = -RandF__5CMathFv(&Math);
        if (p2->randomTwice != 0) {
            f32 randomValue = value - RandF__5CMathFv(&Math);
            value = randomValue * lbl_8032FF38;
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
    f32* source = (sourceOffset == -1) ? gPppDefaultValueBuffer : (f32*)(base + sourceOffset + 0x80);

    f32 delta = p2->blend * *valuePtr;
    *source = *source + delta;
}
