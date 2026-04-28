#include "ffcc/pppSRandHCV.h"
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

struct PppSRandHCVParam3 {
    u8 field0[0xC];
    s32* fieldC;
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
void pppSRandHCV(void* data1, void* data2, void* data3)
{
	u8* base = (u8*)data1;
	PppSRandHCVParam2* in = (PppSRandHCVParam2*)data2;
	PppSRandHCVParam3* out = (PppSRandHCVParam3*)data3;
	if (gPppCalcDisabled != 0) {
		return;
	}

	float* target;

	if (in->field0 == *(s32*)(base + 0xC)) {
		target = (float*)(base + *out->fieldC + 0x80);

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
		target = (float*)(base + *out->fieldC + 0x80);
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
