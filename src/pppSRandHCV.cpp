#include "ffcc/pppSRandHCV.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

STATIC_ASSERT(sizeof(SRandHCVDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(SRandHCVDataOffsets, m_stateOffset) == 0x0);

static inline SRandHCVDataOffsets* GetSRandHCVDataOffsets(_pppCtrlTable* ctrl)
{
	return reinterpret_cast<SRandHCVDataOffsets*>(ctrl->m_serializedDataOffsets);
}

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
	if (ppvUserStopPartF != 0) {
		return;
	}

	float* target;

	if (in->targetId == basePtr->m_graphId) {
		target = (float*)(basePtr->m_workArea + GetSRandHCVDataOffsets(ctrl)->m_stateOffset);
		target[0] = randf(in->useNormalDistribution);
		target[1] = randf(in->useNormalDistribution);
		target[2] = randf(in->useNormalDistribution);
		target[3] = randf(in->useNormalDistribution);
	} else {
		if (in->targetId != basePtr->m_graphId) {
			return;
		}
		target = (float*)(basePtr->m_workArea + GetSRandHCVDataOffsets(ctrl)->m_stateOffset);
	}
	s32 color_offset = in->sourceOffset;
	s16* target_colors = (color_offset == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(basePtr->m_workArea + color_offset);

	target_colors[0] += (s8)randshort(in->delta[0], target[0]);
	target_colors[1] += (s8)randshort(in->delta[1], target[1]);
	target_colors[2] += (s8)randshort(in->delta[2], target[2]);
	target_colors[3] += (s8)randshort(in->delta[3], target[3]);
}
