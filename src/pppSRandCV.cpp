#include "ffcc/pppSRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;
extern int lbl_8032ED70;
extern u8 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath* instance);

struct SRandCVParams
{
	int index;
	int colorOffset;
	s8 base[4];
	u8 flag;
	u8 pad[3];
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * --INFO--
 * PAL Address: 800632d0
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandCV(void* param1, void* param2, void* param3)
{
	SRandCVParams* params = (SRandCVParams*)param2;
	float* rand_values;

	if (lbl_8032ED70 != 0) {
		return;
	}

	if (params->index == *(int*)((char*)param1 + 0xc)) {
		int** base_ptr = (int**)((char*)param3 + 0xc);
		int offset = **base_ptr;
		u8 flag = params->flag;
		float value;
		rand_values = (float*)((char*)param1 + offset + 0x80);

		value = RandF__5CMathFv(&math);
		if (flag != 0) {
			value = value + RandF__5CMathFv(&math);
		} else {
			value = value * 2.0f;
		}
		rand_values[0] = value;

		value = RandF__5CMathFv(&math);
		if (flag != 0) {
			value = value + RandF__5CMathFv(&math);
		} else {
			value = value * 2.0f;
		}
		rand_values[1] = value;

		value = RandF__5CMathFv(&math);
		if (flag != 0) {
			value = value + RandF__5CMathFv(&math);
		} else {
			value = value * 2.0f;
		}
		rand_values[2] = value;

		value = RandF__5CMathFv(&math);
		if (flag != 0) {
			value = value + RandF__5CMathFv(&math);
		} else {
			value = value * 2.0f;
		}
		rand_values[3] = value;
	} else if (params->index != *(int*)((char*)param1 + 0xc)) {
		int** base_ptr = (int**)((char*)param3 + 0xc);
		int offset = **base_ptr;
		rand_values = (float*)((char*)param1 + offset + 0x80);
	}

	u8* target_color;
	int color_offset = params->colorOffset;
	if (color_offset == -1) {
		target_color = lbl_801EADC8;
	} else {
		target_color = (u8*)((char*)param1 + color_offset + 0x80);
	}

	{
		u8 current = target_color[0];
		s8 base = params->base[0];
		s8 delta = (s8)((float)base * rand_values[0] - (float)current);
		target_color[0] = (u8)(current + delta);
	}

	{
		u8 current = target_color[1];
		s8 base = params->base[1];
		s8 delta = (s8)((float)base * rand_values[1] - (float)current);
		target_color[1] = (u8)(current + delta);
	}

	{
		u8 current = target_color[2];
		s8 base = params->base[2];
		s8 delta = (s8)((float)base * rand_values[2] - (float)current);
		target_color[2] = (u8)(current + delta);
	}

	{
		u8 current = target_color[3];
		s8 base = params->base[3];
		s8 delta = (s8)((float)base * rand_values[3] - (float)current);
		target_color[3] = (u8)(current + delta);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randchar(char, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randf(unsigned char)
{
	// TODO
}

#ifdef __cplusplus
}
#endif
