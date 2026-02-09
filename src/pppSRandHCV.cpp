#include "ffcc/pppSRandHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_803300A0;
extern s16 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath* instance);

typedef struct SRandHCVParams {
	int index;
	int colorOffset;
	s16 base[4];
	u8 flag;
	u8 pad[3];
} SRandHCVParams;

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void randshort(short value, float range)
{
	(void)value;
	(void)range;
}

/*
 * --INFO--
 * PAL Address: TODO 
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void randf(unsigned char flag)
{
	(void)flag;
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
void pppSRandHCV(void* data1, void* data2, void* data3)
{
	SRandHCVParams* params = (SRandHCVParams*)data2;
	float* rand_values;

	if (lbl_8032ED70 != 0) {
		return;
	}

	if (params->index == *(int*)((char*)data1 + 0xc)) {
		int** base_ptr = (int**)((char*)data3 + 0xc);
		int offset = **base_ptr;
		u8 flag = params->flag;
		float value;
		rand_values = (float*)((char*)data1 + offset + 0x80);

		value = RandF__5CMathFv(&math);
		if (flag != 0) {
			value = value + RandF__5CMathFv(&math);
		} else {
			value = value * lbl_803300A0;
		}
		rand_values[0] = value;

		value = RandF__5CMathFv(&math);
		if (flag != 0) {
			value = value + RandF__5CMathFv(&math);
		} else {
			value = value * lbl_803300A0;
		}
		rand_values[1] = value;

		value = RandF__5CMathFv(&math);
		if (flag != 0) {
			value = value + RandF__5CMathFv(&math);
		} else {
			value = value * lbl_803300A0;
		}
		rand_values[2] = value;

		value = RandF__5CMathFv(&math);
		if (flag != 0) {
			value = value + RandF__5CMathFv(&math);
		} else {
			value = value * lbl_803300A0;
		}
		rand_values[3] = value;
	} else if (params->index != *(int*)((char*)data1 + 0xc)) {
		int** base_ptr = (int**)((char*)data3 + 0xc);
		int offset = **base_ptr;
		rand_values = (float*)((char*)data1 + offset + 0x80);
	}

	s16* target_color;
	int color_offset = params->colorOffset;
	if (color_offset == -1) {
		target_color = lbl_801EADC8;
	} else {
		target_color = (s16*)((char*)data1 + color_offset + 0x80);
	}

	{
		s16 current = target_color[0];
		s16 base = params->base[0];
		s8 delta = (s8)((float)base * rand_values[0] - (float)current);
		target_color[0] = (s16)(current + delta);
	}

	{
		s16 current = target_color[1];
		s16 base = params->base[1];
		s8 delta = (s8)((float)base * rand_values[1] - (float)current);
		target_color[1] = (s16)(current + delta);
	}

	{
		s16 current = target_color[2];
		s16 base = params->base[2];
		s8 delta = (s8)((float)base * rand_values[2] - (float)current);
		target_color[2] = (s16)(current + delta);
	}

	{
		s16 current = target_color[3];
		s16 base = params->base[3];
		s8 delta = (s8)((float)base * rand_values[3] - (float)current);
		target_color[3] = (s16)(current + delta);
	}
}
