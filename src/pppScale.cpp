#include "ffcc/pppScale.h"

extern int DAT_8032ed70;

/*
 * --INFO--
 * PAL Address: 0x800630f0
 * PAL Size: 96b
 */
void pppScale(void* obj, void* param2, void* param3)
{
	void* dataPtr = *((void**)((char*)param3 + 0x0c));
	
	float* pfVar1 = (float*)((char*)obj + *((int*)((char*)dataPtr + 0x00)) + 0x80);
	float* pfVar2 = (float*)((char*)obj + *((int*)((char*)dataPtr + 0x04)) + 0x80);
	
	if (DAT_8032ed70 != 0) {
		return;
	}
	
	if (*((int*)((char*)param2 + 0x08)) == *((int*)((char*)obj + 0x08))) {
		float scale = *((float*)((char*)param2 + 0x0c));
		*pfVar2 = *pfVar2 * scale;
		pfVar2[1] = pfVar2[1] * scale;
		pfVar2[2] = pfVar2[2] * scale;
	}
	
	*pfVar1 = *pfVar2;
	pfVar1[1] = pfVar2[1];
	pfVar1[2] = pfVar2[2];
}

/*
 * --INFO--
 * PAL Address: 0x800630cc
 * PAL Size: 36b
 */
void pppScaleCon(void* obj, void* param)
{
	void* dataPtr = *((void**)((char*)param + 0x0c));
	float* puVar2 = (float*)((char*)obj + *((int*)((char*)dataPtr + 0x04)) + 0x80);
	
	puVar2[2] = 1.0f;
	puVar2[1] = 1.0f;
	*puVar2 = 1.0f;
}