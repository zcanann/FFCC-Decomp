#include "ffcc/pppSRandHCV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppSRandHCVSingleSampleScale = 2.0f;

struct PppSRandHCVParam2 {
    s32 field0;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s16 fieldC;
    s16 fieldE;
    u8 field10;
};

/*
 * --INFO--
 * PAL Address: 80063e34
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandHCV(_pppPObject* basePtr, PppSRandHCVParam2* in, _pppCtrlTable* ctrl)
{
	u8* base = (u8*)basePtr;
	if (gPppCalcDisabled != 0) {
		return;
	}

	float* target;

	if (in->field0 == *(s32*)(base + 0xC)) {
		target = (float*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);

		{
			u8 flag = in->field10;
			float value = Math.RandF();
			if (flag != 0) {
				value = value + Math.RandF();
			} else {
				float scale = kPppSRandHCVSingleSampleScale;
				value = value * scale;
			}
			target[0] = value;
		}

		{
			u8 flag = in->field10;
			float value = Math.RandF();
			if (flag != 0) {
				value = value + Math.RandF();
			} else {
				float scale = kPppSRandHCVSingleSampleScale;
				value = value * scale;
			}
			target[1] = value;
		}

		{
			u8 flag = in->field10;
			float value = Math.RandF();
			if (flag != 0) {
				value = value + Math.RandF();
			} else {
				float scale = kPppSRandHCVSingleSampleScale;
				value = value * scale;
			}
			target[2] = value;
		}

		{
			u8 flag = in->field10;
			float value = Math.RandF();
			if (flag != 0) {
				value = value + Math.RandF();
			} else {
				float scale = kPppSRandHCVSingleSampleScale;
				value = value * scale;
			}
			target[3] = value;
		}
	} else {
		if (in->field0 != *(s32*)(base + 0xC)) {
			return;
		}
		target = (float*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
	}
	s32 color_offset = in->field4;
	s16* target_colors = (color_offset == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(base + color_offset + 0x80);

	{
		s16 color = target_colors[0];
		target_colors[0] = color + (s8)((f32)in->field8 * target[0] - (f32)in->field8);
	}
	{
		s16 color = target_colors[1];
		target_colors[1] = color + (s8)((f32)in->fieldA * target[1] - (f32)in->fieldA);
	}
	{
		s16 color = target_colors[2];
		target_colors[2] = color + (s8)((f32)in->fieldC * target[2] - (f32)in->fieldC);
	}
	{
		s16 color = target_colors[3];
		target_colors[3] = color + (s8)((f32)in->fieldE * target[3] - (f32)in->fieldE);
	}
}
