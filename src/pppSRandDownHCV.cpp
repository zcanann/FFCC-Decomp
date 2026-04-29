#include "ffcc/pppSRandDownHCV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct SRandDownHCVParams {
    s32 targetId;
    s32 sourceOffset;
    s16 delta[4];
    u8 randomTwice;
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

static inline short randshort(short value, float scale)
{
    return (short)((f32)value * scale);
}

/*
 * --INFO--
 * PAL Address: 800639ec
 * PAL Size: 656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandDownHCV(_pppPObject* basePtr, SRandDownHCVParams* in, _pppCtrlTable* ctrl)
{
	u8* base = (u8*)basePtr;
	if (gPppCalcDisabled != 0) {
		return;
	}

	float* target;

	if (in->targetId == *(s32*)(base + 0xC)) {
		target = (float*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);

		{
			u8 flag = in->randomTwice;
			float value = -Math.RandF();
			if (flag != 0) {
				float random = Math.RandF();
				float blend = value - random;
				float scale = 0.5f;
				value = blend * scale;
			}
			target[0] = value;
		}

		{
			u8 flag = in->randomTwice;
			float value = -Math.RandF();
			if (flag != 0) {
				float random = Math.RandF();
				float blend = value - random;
				float scale = 0.5f;
				value = blend * scale;
			}
			target[1] = value;
		}

		{
			u8 flag = in->randomTwice;
			float value = -Math.RandF();
			if (flag != 0) {
				float random = Math.RandF();
				float blend = value - random;
				float scale = 0.5f;
				value = blend * scale;
			}
			target[2] = value;
		}

		{
			u8 flag = in->randomTwice;
			float value = -Math.RandF();
			if (flag != 0) {
				float random = Math.RandF();
				float blend = value - random;
				float scale = 0.5f;
				value = blend * scale;
			}
			target[3] = value;
		}
	} else {
		if (in->targetId != *(s32*)(base + 0xC)) {
			return;
		}
		target = (float*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
	}

	s32 color_offset = in->sourceOffset;
	s16* target_colors = (color_offset == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(base + color_offset + 0x80);

	target_colors[0] += (s8)randshort(in->delta[0], target[0]);
	target_colors[1] += (s8)randshort(in->delta[1], target[1]);
	target_colors[2] += (s8)randshort(in->delta[2], target[2]);
	target_colors[3] += (s8)randshort(in->delta[3], target[3]);
}
