#include "ffcc/pppSRandFV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "dolphin/types.h"
#include "ffcc/ppp_default_buffer.h"

static inline float randf(unsigned char flag)
{
    float value = Math.RandF();
    if (flag != 0) {
        value = value + Math.RandF();
    } else {
        float scale = 2.0f;
        value = value * scale;
    }
    return value;
}

/*
 * --INFO--
 * PAL Address: 0x80063c7c
 * PAL Size: 440b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
struct SRandFVParams {
    s32 targetId;
    s32 sourceOffset;
    f32 blend[3];
    u8 _pad[4];
    u8 useNormalDistribution;
};

void pppSRandFV(_pppPObject* basePtr, SRandFVParams* in, _pppCtrlTable* ctrl)
{
    f32* randVec;
    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 currentIndex = *(s32*)((u8*)basePtr + 0xC);
    if (currentIndex == 0) {
        randVec = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        randVec[0] = randf(in->useNormalDistribution);
        randVec[1] = randf(in->useNormalDistribution);
        randVec[2] = randf(in->useNormalDistribution);
    } else {
        if (in->targetId != currentIndex) {
            return;
        }
        randVec = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    f32* target = (in->sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)((u8*)basePtr + in->sourceOffset + 0x80);

    target[0] +=(in->blend[0] * randVec[0] - in->blend[0]);
    target[1] +=(in->blend[1] * randVec[1] - in->blend[1]);
    target[2] +=(in->blend[2] * randVec[2] - in->blend[2]);
}
