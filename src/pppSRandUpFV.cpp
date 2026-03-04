#include "ffcc/pppSRandUpFV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math[];
extern s32 lbl_8032ED70;
extern f32 lbl_803300C0;
extern f32 lbl_801EADC8[];
extern "C" f32 RandF__5CMathFv(CMath*);

/*
 * --INFO--
 * PAL Address: 0x800643a4
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppSRandUpFV(void* param1, void* param2, void* param3)
{
    struct SRandUpFVParam {
        s32 index;
        s32 targetOffset;
        f32 x;
        f32 y;
        f32 z;
        u8 _pad14[0x18 - 0x14];
        u8 blendTwice;
    };
    struct SRandUpFVCtx {
        u8 _pad0[0xC];
        s32* outputOffset;
    };

    u8* self = (u8*)param1;
    SRandUpFVParam* cfg = (SRandUpFVParam*)param2;
    SRandUpFVCtx* info = (SRandUpFVCtx*)param3;
    f32* randVec;

    if (lbl_8032ED70 != 0) {
        return;
    }

    s32 currentIndex = *(s32*)(self + 0xC);
    if (currentIndex == 0) {
        randVec = (f32*)(self + *info->outputOffset + 0x80);

        {
            u8 flag = cfg->blendTwice;
            f32 value = RandF__5CMathFv(math);
            if (flag != 0) {
                value = lbl_803300C0 * (value + RandF__5CMathFv(math));
            }
            randVec[0] = value;
        }

        {
            u8 flag = cfg->blendTwice;
            f32 value = RandF__5CMathFv(math);
            if (flag != 0) {
                value = lbl_803300C0 * (value + RandF__5CMathFv(math));
            }
            randVec[1] = value;
        }

        {
            u8 flag = cfg->blendTwice;
            f32 value = RandF__5CMathFv(math);
            if (flag != 0) {
                value = lbl_803300C0 * (value + RandF__5CMathFv(math));
            }
            randVec[2] = value;
        }
    } else {
        if (cfg->index != currentIndex) {
            return;
        }
        randVec = (f32*)(self + *info->outputOffset + 0x80);
    }

    f32* target = (cfg->targetOffset == -1) ? lbl_801EADC8 : (f32*)(self + cfg->targetOffset + 0x80);

    {
        f32 value = randVec[0] * cfg->x;
        target[0] = target[0] + value;
    }
    {
        f32 value = randVec[1] * cfg->y;
        target[1] = target[1] + value;
    }
    {
        f32 value = randVec[2] * cfg->z;
        target[2] = target[2] + value;
    }
}
