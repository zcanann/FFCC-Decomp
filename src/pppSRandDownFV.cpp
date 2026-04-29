#include "ffcc/pppSRandDownFV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct SRandDownFVParams {
    s32 targetId;
    s32 sourceOffset;
    f32 blend[3];
    u8 _pad[4];
    u8 useNormalDistribution;
};

static inline float randf(unsigned char flag)
{
    float value = -Math.RandF();
    if (flag != 0) {
        float random = Math.RandF();
        float blend = value - random;
        float scale = 0.5f;
        value = blend * scale;
    }
    return value;
}

/*
 * --INFO--
 * PAL Address: 0x80063840
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandDownFV(_pppPObject* basePtr, SRandDownFVParams* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    f32* randVec;
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

    target[0] += in->blend[0] * randVec[0];
    target[1] += in->blend[1] * randVec[1];
    target[2] += in->blend[2] * randVec[2];
}
