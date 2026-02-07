#include "ffcc/pppPoint.h"

extern int lbl_8032ED70;

/*
 * --INFO--
 * PAL Address: 0x80065cd8
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointCon(PppData* a, PppData* b)
{
	int* dataOffset = *(int**)&b->values[2];
	float* dst = (float*)((char*)a + *dataOffset + 0x80);
	float value = 0.0f;

	dst[2] = value;
	dst[1] = value;
	dst[0] = value;
}

/*
 * --INFO--
 * PAL Address: 0x80065cfc
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPoint(PppData* a, PppData* b, PppData* c)
{
	if (lbl_8032ED70 != 0) {
		return;
	}

	if (b->id != *(int*)&a->values[2]) {
		return;
	}

	int* dataOffset = *(int**)&c->values[2];
	float* dst = (float*)((char*)a + *dataOffset + 0x80);

	dst[0] += b->values[1];
	dst[1] += b->values[2];
	dst[2] += b->values[3];
}
