#include "ffcc/pppSRandUpHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppColor.h"
extern s16 gPppDefaultValueBuffer[];
extern "C" float RandF__5CMathFv(CMath* instance);

struct PppSRandUpHCVParam2 {
    s32 field0;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s16 fieldC;
    s16 fieldE;
    u8 field10;
};

struct PppSRandUpHCVParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x80064550
 * PAL Size: 656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandUpHCV(void* param1, void* param2, void* param3)
{
	u8* base = (u8*)param1;
	PppSRandUpHCVParam2* in = (PppSRandUpHCVParam2*)param2;
	PppSRandUpHCVParam3* out = (PppSRandUpHCVParam3*)param3;

	if (gPppCalcDisabled != 0) {
		return;
	}

	float* target;

	if (in->field0 == *(s32*)(base + 0xC)) {
		target = (float*)(base + *out->fieldC + 0x80);

		{
			u8 flag = in->field10;
			float value = RandF__5CMathFv(&Math);
			if (flag != 0) {
				float random = RandF__5CMathFv(&Math);
				float blend = value + random;
				float scale = kPppSRandUpHCVDualSampleScale;
				value = blend * scale;
			}
			target[0] = value;
		}

		{
			u8 flag = in->field10;
			float value = RandF__5CMathFv(&Math);
			if (flag != 0) {
				float random = RandF__5CMathFv(&Math);
				float blend = value + random;
				float scale = kPppSRandUpHCVDualSampleScale;
				value = blend * scale;
			}
			target[1] = value;
		}

		{
			u8 flag = in->field10;
			float value = RandF__5CMathFv(&Math);
			if (flag != 0) {
				float random = RandF__5CMathFv(&Math);
				float blend = value + random;
				float scale = kPppSRandUpHCVDualSampleScale;
				value = blend * scale;
			}
			target[2] = value;
		}

		{
			u8 flag = in->field10;
			float value = RandF__5CMathFv(&Math);
			if (flag != 0) {
				float random = RandF__5CMathFv(&Math);
				float blend = value + random;
				float scale = kPppSRandUpHCVDualSampleScale;
				value = blend * scale;
			}
			target[3] = value;
		}
	} else {
		target = (float*)(base + *out->fieldC + 0x80);
	}

	s16* target_colors;
	s32 color_offset = in->field4;
	if (color_offset == -1) {
		target_colors = gPppDefaultValueBuffer;
	} else {
		target_colors = (s16*)(base + color_offset + 0x80);
	}

	{
		s16 base = in->field8;
		s8 delta = (s8)((f32)base * target[0]);
		target_colors[0] = (s16)(target_colors[0] + delta);
	}

	{
		s16 base = in->fieldA;
		s8 delta = (s8)((f32)base * target[1]);
		target_colors[1] = (s16)(target_colors[1] + delta);
	}

	{
		s16 base = in->fieldC;
		s8 delta = (s8)((f32)base * target[2]);
		target_colors[2] = (s16)(target_colors[2] + delta);
	}

	{
		s16 base = in->fieldE;
		s8 delta = (s8)((f32)base * target[3]);
		target_colors[3] = (s16)(target_colors[3] + delta);
	}
}
