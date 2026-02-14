#include "ffcc/pppSRandHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math[];
extern int lbl_8032ED70;
extern float lbl_803300A0;
extern s16 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath* instance);

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
	if (lbl_8032ED70 != 0) {
		return;
	}

	float* target;

	if (*(int*)data2 == *((int*)data1 + 3)) {
		int** base_ptr = (int**)((char*)data3 + 0xc);
		int offset = **base_ptr;
		target = (float*)((char*)data1 + offset + 0x80);

		u8 flag = *((u8*)data2 + 0x10);
		float value;

		value = RandF__5CMathFv(math);
		if (flag != 0) {
			value = value + RandF__5CMathFv(math);
		} else {
			value = value * lbl_803300A0;
		}
		target[0] = value;

		value = RandF__5CMathFv(math);
		if (flag != 0) {
			value = value + RandF__5CMathFv(math);
		} else {
			value = value * lbl_803300A0;
		}
		target[1] = value;

		value = RandF__5CMathFv(math);
		if (flag != 0) {
			value = value + RandF__5CMathFv(math);
		} else {
			value = value * lbl_803300A0;
		}
		target[2] = value;

		value = RandF__5CMathFv(math);
		if (flag != 0) {
			value = value + RandF__5CMathFv(math);
		} else {
			value = value * lbl_803300A0;
		}
		target[3] = value;
	} else if (*(int*)data2 != *((int*)data1 + 3)) {
		int** base_ptr = (int**)((char*)data3 + 0xc);
		int offset = **base_ptr;
		target = (float*)((char*)data1 + offset + 0x80);
	}

	int color_offset = *((int*)data2 + 1);
	s16* target_color;
	if (color_offset == -1) {
		target_color = lbl_801EADC8;
	} else {
		target_color = (s16*)((char*)data1 + color_offset + 0x80);
	}

	{
		s16 current = target_color[0];
		s16 base = *(s16*)((char*)data2 + 8);
		s8 delta = (s8)((float)base * target[0] - (float)current);
		target_color[0] = (s16)(current + delta);
	}

	{
		s16 current = target_color[1];
		s16 base = *(s16*)((char*)data2 + 0xa);
		s8 delta = (s8)((float)base * target[1] - (float)current);
		target_color[1] = (s16)(current + delta);
	}

	{
		s16 current = target_color[2];
		s16 base = *(s16*)((char*)data2 + 0xc);
		s8 delta = (s8)((float)base * target[2] - (float)current);
		target_color[2] = (s16)(current + delta);
	}

	{
		s16 current = target_color[3];
		s16 base = *(s16*)((char*)data2 + 0xe);
		s8 delta = (s8)((float)base * target[3] - (float)current);
		target_color[3] = (s16)(current + delta);
	}
}
