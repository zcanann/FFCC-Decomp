#include "ffcc/pppSRandDownHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math[];
extern int gPppCalcDisabled;
extern s16 gPppDefaultValueBuffer[];
extern float lbl_80330088;
extern "C" float RandF__5CMathFv(CMath* instance);

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
	if (gPppCalcDisabled != 0) {
		return;
	}

	float* target;

	if (*(int*)param2 == *((int*)param1 + 3)) {
		int** base_ptr = (int**)((char*)param3 + 0xc);
		int offset = **base_ptr;
		target = (float*)((char*)param1 + offset + 0x80);

		{
			u8 flag = *((u8*)param2 + 0x10);
			float value = -RandF__5CMathFv(math);
			if (flag != 0) {
				float random = RandF__5CMathFv(math);
				float blend = value - random;
				float scale = lbl_80330088;
				value = blend * scale;
			}
			target[0] = value;
		}

		{
			u8 flag = *((u8*)param2 + 0x10);
			float value = -RandF__5CMathFv(math);
			if (flag != 0) {
				float random = RandF__5CMathFv(math);
				float blend = value - random;
				float scale = lbl_80330088;
				value = blend * scale;
			}
			target[1] = value;
		}

		{
			u8 flag = *((u8*)param2 + 0x10);
			float value = -RandF__5CMathFv(math);
			if (flag != 0) {
				float random = RandF__5CMathFv(math);
				float blend = value - random;
				float scale = lbl_80330088;
				value = blend * scale;
			}
			target[2] = value;
		}

		{
			u8 flag = *((u8*)param2 + 0x10);
			float value = -RandF__5CMathFv(math);
			if (flag != 0) {
				float random = RandF__5CMathFv(math);
				float blend = value - random;
				float scale = lbl_80330088;
				value = blend * scale;
			}
			target[3] = value;
		}
	} else {
		int** base_ptr = (int**)((char*)param3 + 0xc);
		int offset = **base_ptr;
		target = (float*)((char*)param1 + offset + 0x80);
	}

	s16* target_colors;
	int color_offset = *((int*)param2 + 1);
	if (color_offset == -1) {
		target_colors = gPppDefaultValueBuffer;
	} else {
		target_colors = (s16*)((char*)param1 + color_offset + 0x80);
	}

	{
		s16 base = *(s16*)((char*)param2 + 0x8);
		s8 delta = (s8)(base * target[0]);
		target_colors[0] = (s16)(target_colors[0] + delta);
	}

	{
		s16 base = *(s16*)((char*)param2 + 0xa);
		s8 delta = (s8)(base * target[1]);
		target_colors[1] = (s16)(target_colors[1] + delta);
	}

	{
		s16 base = *(s16*)((char*)param2 + 0xc);
		s8 delta = (s8)(base * target[2]);
		target_colors[2] = (s16)(target_colors[2] + delta);
	}

	{
		s16 base = *(s16*)((char*)param2 + 0xe);
		s8 delta = (s8)(base * target[3]);
		target_colors[3] = (s16)(target_colors[3] + delta);
	}
}
