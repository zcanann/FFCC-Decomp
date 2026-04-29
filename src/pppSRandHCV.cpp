#include "ffcc/pppSRandHCV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"


struct SRandHCVParams {
    s32 targetId;
    s32 sourceOffset;
    s16 delta[4];
    u8 useNormalDistribution;
};

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

static inline short randshort(short value, float scale)
{
    return (short)((f32)value * scale - (f32)value);
}

/*
 * --INFO--
 * PAL Address: 80063e34
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandHCV(_pppPObject* basePtr, SRandHCVParams* in, _pppCtrlTable* ctrl)
{
	u8* base = (u8*)basePtr;
	if (gPppCalcDisabled != 0) {
		return;
	}

	float* target;

	if (in->targetId == *(s32*)(base + 0xC)) {
		target = (float*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
		target[0] = randf(in->useNormalDistribution);
		target[1] = randf(in->useNormalDistribution);
		target[2] = randf(in->useNormalDistribution);
		target[3] = randf(in->useNormalDistribution);
	} else {
		if (in->targetId != *(s32*)(base + 0xC)) {
			return;
		}
		target = (float*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
	}
	s32 color_offset = in->sourceOffset;
	s16* target_colors = (color_offset == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(base + color_offset + 0x80);

	target_colors[0] = target_colors[0] + (s8)randshort(in->delta[0], target[0]);
	target_colors[1] = target_colors[1] + (s8)randshort(in->delta[1], target[1]);
	target_colors[2] = target_colors[2] + (s8)randshort(in->delta[2], target[2]);
	target_colors[3] = target_colors[3] + (s8)randshort(in->delta[3], target[3]);
}
