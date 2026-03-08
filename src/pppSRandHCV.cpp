#include "ffcc/pppSRandHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
extern s16 gPppDefaultValueBuffer[];
extern "C" float RandF__5CMathFv(CMath* instance);

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
	s16* targetColor;
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
				value = value + RandF__5CMathFv(&Math);
			} else {
				value = value * kPppSRandHCVSingleSampleScale;
			}
			target[0] = value;
		}

		{
			u8 flag = in->field10;
			float value = RandF__5CMathFv(&Math);
			if (flag != 0) {
				value = value + RandF__5CMathFv(&Math);
			} else {
				value = value * kPppSRandHCVSingleSampleScale;
			}
			target[1] = value;
		}

		{
			u8 flag = in->field10;
			float value = RandF__5CMathFv(&Math);
			if (flag != 0) {
				value = value + RandF__5CMathFv(&Math);
			} else {
				value = value * kPppSRandHCVSingleSampleScale;
			}
			target[2] = value;
		}

		{
			u8 flag = in->field10;
			float value = RandF__5CMathFv(&Math);
			if (flag != 0) {
				value = value + RandF__5CMathFv(&Math);
			} else {
				value = value * kPppSRandHCVSingleSampleScale;
			}
			target[3] = value;
		}
	} else if (in->field0 != *(s32*)(base + 0xC)) {
		return;
	} else {
		target = (float*)(base + *out->fieldC + 0x80);
	}

	s32 colorOffset = in->field4;
	if (colorOffset == -1) {
		targetColor = gPppDefaultValueBuffer;
	} else {
		targetColor = (s16*)(base + colorOffset + 0x80);
	}

	targetColor[0] = (s16)(targetColor[0] + (s8)((float)in->field8 * target[0] - (float)in->field8));
	targetColor[1] = (s16)(targetColor[1] + (s8)((float)in->fieldA * target[1] - (float)in->fieldA));
	targetColor[2] = (s16)(targetColor[2] + (s8)((float)in->fieldC * target[2] - (float)in->fieldC));
	targetColor[3] = (s16)(targetColor[3] + (s8)((float)in->fieldE * target[3] - (float)in->fieldE));
}
