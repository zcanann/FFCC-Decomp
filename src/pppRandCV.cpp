#include "ffcc/pppRandCV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_8032FF08;
extern double lbl_8032FF10;
extern unsigned char lbl_801EADC8[32];
extern "C" float RandF__5CMathFv(CMath* instance);

typedef struct RandCVParams {
	int index;
	int colorOffset;
	signed char delta[4];
	unsigned char flag;
	unsigned char pad[3];
} RandCVParams;

typedef union DoubleConv {
	struct {
		unsigned int hi;
		unsigned int lo;
	} parts;
	double d;
} DoubleConv;

typedef struct RandCVConv {
	DoubleConv d0;
	DoubleConv c0;
	DoubleConv d1;
	DoubleConv c1;
	DoubleConv d2;
	DoubleConv c2;
	DoubleConv d3;
	DoubleConv c3;
} RandCVConv;

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
	void* p1 = param1;
	void* p2 = param2;
	void* p3 = param3;
	RandCVParams* params = (RandCVParams*)p2;
	int* baseIndex;
	int baseOffset;
	float* randValuePtr;

	if (lbl_8032ED70 != 0) {
		return;
	}

	if (params->index == *(int*)((char*)p1 + 0xc)) {
		baseIndex = *(int**)((char*)p3 + 0xc);
		baseOffset = *baseIndex;
		randValuePtr = (float*)((char*)p1 + baseOffset + 0x80);

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

	baseIndex = *(int**)((char*)p3 + 0xc);
	baseOffset = *baseIndex;
	randValuePtr = (float*)((char*)p1 + baseOffset + 0x80);

	unsigned char* colors;
	if (params->colorOffset == -1) {
		colors = lbl_801EADC8;
	} else {
		colors = (unsigned char*)p1 + params->colorOffset + 0x80;
	}

	float scale = *randValuePtr;
	const double bias = lbl_8032FF10;
	RandCVConv conv;

	{
		signed char delta = params->delta[0];
		unsigned char current = colors[0];
		conv.d0.parts.hi = 0x43300000;
		conv.d0.parts.lo = (unsigned int)((int)delta ^ 0x8000);
		conv.c0.parts.hi = 0x43300000;
		conv.c0.parts.lo = (unsigned int)(current ^ 0x8000);
		double value = conv.d0.d - bias;
		double baseValue = conv.c0.d - bias;
		double result = value * (double)scale - baseValue;
		int add = (int)result;
		colors[0] = (unsigned char)(current + add);
	}

	{
		signed char delta = params->delta[1];
		unsigned char current = colors[1];
		conv.d1.parts.hi = 0x43300000;
		conv.d1.parts.lo = (unsigned int)((int)delta ^ 0x8000);
		conv.c1.parts.hi = 0x43300000;
		conv.c1.parts.lo = (unsigned int)(current ^ 0x8000);
		double value = conv.d1.d - bias;
		double baseValue = conv.c1.d - bias;
		double result = value * (double)scale - baseValue;
		int add = (int)result;
		colors[1] = (unsigned char)(current + add);
	}

	{
		signed char delta = params->delta[2];
		unsigned char current = colors[2];
		conv.d2.parts.hi = 0x43300000;
		conv.d2.parts.lo = (unsigned int)((int)delta ^ 0x8000);
		conv.c2.parts.hi = 0x43300000;
		conv.c2.parts.lo = (unsigned int)(current ^ 0x8000);
		double value = conv.d2.d - bias;
		double baseValue = conv.c2.d - bias;
		double result = value * (double)scale - baseValue;
		int add = (int)result;
		colors[2] = (unsigned char)(current + add);
	}

	{
		signed char delta = params->delta[3];
		unsigned char current = colors[3];
		conv.d3.parts.hi = 0x43300000;
		conv.d3.parts.lo = (unsigned int)((int)delta ^ 0x8000);
		conv.c3.parts.hi = 0x43300000;
		conv.c3.parts.lo = (unsigned int)(current ^ 0x8000);
		double value = conv.d3.d - bias;
		double baseValue = conv.c3.d - bias;
		double result = value * (double)scale - baseValue;
		int add = (int)result;
		colors[3] = (unsigned char)(current + add);
	}
}
