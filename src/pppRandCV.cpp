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
	int* baseIndex = *(int**)((char*)param3 + 0xc);
	float* randValuePtr = (float*)((char*)param1 + *baseIndex + 0x80);

	if (lbl_8032ED70 != 0) {
		return;
	}

	if (params->index == *(int*)((char*)param1 + 0xc)) {
		float randVal = RandF__5CMathFv(&math);
		if (params->flag != 0) {
			float randVal2 = RandF__5CMathFv(&math);
			randVal = randVal + randVal2;
		} else {
			randVal = randVal * lbl_8032FF08;
		}
		*randValuePtr = randVal;
		return;
	}

	unsigned char* colors;
	if (params->colorOffset == -1) {
		colors = lbl_801EADC8;
	} else {
		colors = (unsigned char*)param1 + params->colorOffset + 0x80;
	}

	float scale = *randValuePtr;
	for (int i = 0; i < 4; i++) {
		signed char delta = params->delta[i];
		double value = (double)delta;
		double result = value * (double)scale;
		int add = (int)result;
		colors[i] = (unsigned char)(colors[i] + add);
	}
}
