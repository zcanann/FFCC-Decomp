#include "ffcc/pppSRandUpCV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"


struct SRandUpCVParam {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 useNormalDistribution;
};

static inline float randf(unsigned char flag)
{
    float value = Math.RandF();
    if (flag != 0) {
        float random = Math.RandF();
        float blend = value + random;
        float scale = 0.5f;
        value = blend * scale;
    }
    return value;
}

static inline char randchar(char value, float scale)
{
    return (char)((f32)value * scale);
}

/*
 * --INFO--
 * PAL Address: 0x80064114
 * PAL Size: 656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandUpCV(_pppPObject* basePtr, SRandUpCVParam* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)basePtr;
    f32* target;

    if (in->targetId == *(s32*)(base + 0xC)) {
        target = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        target[0] = randf(in->useNormalDistribution);
        target[1] = randf(in->useNormalDistribution);
        target[2] = randf(in->useNormalDistribution);
        target[3] = randf(in->useNormalDistribution);
    } else {
        if (in->targetId != *(s32*)(base + 0xC)) {
            return;
        }
        target = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    s32 color_offset = in->sourceOffset;
    u8* target_colors = (color_offset == -1) ? gPppDefaultValueBuffer : (base + color_offset + 0x80);

    target_colors[0] = target_colors[0] + randchar(in->delta[0], target[0]);
    target_colors[1] = target_colors[1] + randchar(in->delta[1], target[1]);
    target_colors[2] = target_colors[2] + randchar(in->delta[2], target[2]);
    target_colors[3] = target_colors[3] + randchar(in->delta[3], target[3]);
}
