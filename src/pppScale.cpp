#include "ffcc/pppScale.h"
#include "ffcc/ppp_linkage.h"

extern const float FLOAT_80330048;

/*
 * --INFO--
 * PAL Address: 0x800630f0
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppScale(void* obj, void* param2, void* param3)
{
	if (gPppCalcDisabled != 0) {
		return;
	}

	if (*((int*)((char*)param2 + 0x00)) != *((int*)((char*)obj + 0x0c))) {
		return;
	}

	int* data = *((int**)((char*)param3 + 0x0c));
	float* scale = (float*)((char*)obj + data[0] + 0x80);
	scale[0] += *((float*)((char*)param2 + 0x08));
	scale[1] += *((float*)((char*)param2 + 0x0c));
	scale[2] += *((float*)((char*)param2 + 0x10));
}

/*
 * --INFO--
 * PAL Address: 0x800630cc
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppScaleCon(void* obj, void* param)
{
	int* data = *((int**)((char*)param + 0x0c));
	float* value = (float*)((char*)obj + data[0] + 0x80);
	float one = FLOAT_80330048;
	
	value[2] = one;
	value[1] = one;
	value[0] = one;
}
