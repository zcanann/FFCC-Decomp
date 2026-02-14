#include "ffcc/pppRandCV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_8032FF08;
extern unsigned char lbl_801EADC8[32];
extern "C" float RandF__5CMathFv(CMath* instance);

typedef struct RandCVParams {
	int index;
	int colorOffset;
	signed char delta[4];
	unsigned char flag;
	unsigned char pad[3];
} RandCVParams;

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 */
void randchar(char range, float factor)
{
	float value = (float)range;
	float scaled = value * factor;
	(void)scaled;
}

/*
 * --INFO--
 * PAL Address: 0x80066194
 * PAL Size: 540b
 */
void pppRandCV(void* param1, void* param2, void* param3)
{
	RandCVParams* params = (RandCVParams*)param2;
	float* randValuePtr;

	if (lbl_8032ED70 != 0) {
		return;
	}

	if (params->index == *(int*)((char*)param1 + 0xc)) {
		int** baseIndex = *(int***)((char*)param3 + 0xc);
		int baseOffset = **baseIndex;
		randValuePtr = (float*)((char*)param1 + baseOffset + 0x80);

		float randVal = RandF__5CMathFv(&math);
		if (params->flag != 0) {
			randVal = randVal + RandF__5CMathFv(&math);
		} else {
			randVal = randVal * lbl_8032FF08;
		}
		*randValuePtr = randVal;
		return;
	}

	{
		int** baseIndex = *(int***)((char*)param3 + 0xc);
		int baseOffset = **baseIndex;
		randValuePtr = (float*)((char*)param1 + baseOffset + 0x80);
	}

	unsigned char* colors;
	if (params->colorOffset == -1) {
		colors = lbl_801EADC8;
	} else {
		colors = (unsigned char*)param1 + params->colorOffset + 0x80;
	}

	float scale = *randValuePtr;

	{
		unsigned char current = colors[0];
		signed char delta = (signed char)((float)params->delta[0] * scale - (float)current);
		colors[0] = (unsigned char)(current + delta);
	}
	{
		unsigned char current = colors[1];
		signed char delta = (signed char)((float)params->delta[1] * scale - (float)current);
		colors[1] = (unsigned char)(current + delta);
	}
	{
		unsigned char current = colors[2];
		signed char delta = (signed char)((float)params->delta[2] * scale - (float)current);
		colors[2] = (unsigned char)(current + delta);
	}
	{
		unsigned char current = colors[3];
		signed char delta = (signed char)((float)params->delta[3] * scale - (float)current);
		colors[3] = (unsigned char)(current + delta);
	}
}
