#include "ffcc/pppSRandDownHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppSRandDownHCVDualSampleScale = 0.5f;
struct PppSRandDownHCVParam2 {
    s32 field0;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s16 fieldC;
    s16 fieldE;
    u8 field10;
};

struct PppSRandDownHCVParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 800639ec
 * PAL Size: 656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandDownHCV(void* param1, void* param2, void* param3)
{
	u8* base = (u8*)param1;
	PppSRandDownHCVParam2* in = (PppSRandDownHCVParam2*)param2;
	PppSRandDownHCVParam3* out = (PppSRandDownHCVParam3*)param3;

	if (gPppCalcDisabled != 0) {
		return;
	}

	float* target;

	if (in->field0 == *(s32*)(base + 0xC)) {
		target = (float*)(base + *out->fieldC + 0x80);

		{
			u8 flag = in->field10;
			float value = -Math.RandF();
			if (flag != 0) {
				float random = Math.RandF();
				float blend = value - random;
				float scale = kPppSRandDownHCVDualSampleScale;
				value = blend * scale;
			}
			target[0] = value;
		}

		{
			u8 flag = in->field10;
			float value = -Math.RandF();
			if (flag != 0) {
				float random = Math.RandF();
				float blend = value - random;
				float scale = kPppSRandDownHCVDualSampleScale;
				value = blend * scale;
			}
			target[1] = value;
		}

		{
			u8 flag = in->field10;
			float value = -Math.RandF();
			if (flag != 0) {
				float random = Math.RandF();
				float blend = value - random;
				float scale = kPppSRandDownHCVDualSampleScale;
				value = blend * scale;
			}
			target[2] = value;
		}

		{
			u8 flag = in->field10;
			float value = -Math.RandF();
			if (flag != 0) {
				float random = Math.RandF();
				float blend = value - random;
				float scale = kPppSRandDownHCVDualSampleScale;
				value = blend * scale;
			}
			target[3] = value;
		}
	} else {
		if (in->field0 != *(s32*)(base + 0xC)) {
			return;
		}
		target = (float*)(base + *out->fieldC + 0x80);
	}

	s32 color_offset = in->field4;
	s16* target_colors = (color_offset == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(base + color_offset + 0x80);

	target_colors[0] += (s8)((f32)in->field8 * target[0]);
	target_colors[1] += (s8)((f32)in->fieldA * target[1]);
	target_colors[2] += (s8)((f32)in->fieldC * target[2]);
	target_colors[3] += (s8)((f32)in->fieldE * target[3]);
}
