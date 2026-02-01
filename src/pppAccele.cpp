#include "ffcc/pppAccele.h"

extern int DAT_8032ed70;
extern float DAT_8032fec8;

/*
 * --INFO--
 * PAL Address: 0x80064c7c
 * PAL Size: 156b
 */
void pppAccele(void* obj, void* param2, void* param3)
{
	void* dataPtr = *((void**)((char*)param3 + 0x0c));
	
	float* pfVar1 = (float*)((char*)obj + *((int*)((char*)dataPtr + 0x00)) + 0x80);
	float* pfVar2 = (float*)((char*)obj + *((int*)((char*)dataPtr + 0x04)) + 0x80);
	
	if (DAT_8032ed70 != 0) {
		return;
	}
	
	if (*((int*)((char*)param2 + 0x00)) == *((int*)((char*)obj + 0x0c))) {
		*pfVar2 = *pfVar2 + *((float*)((char*)param2 + 0x0c));
		pfVar2[1] = pfVar2[1] + *((float*)((char*)param2 + 0x10));
		pfVar2[2] = pfVar2[2] + *((float*)((char*)param2 + 0x14));
	}
	
	*pfVar1 = *pfVar1 + *pfVar2;
	pfVar1[1] = pfVar1[1] + pfVar2[1];
	pfVar1[2] = pfVar1[2] + pfVar2[2];
}

/*
 * --INFO--
 * PAL Address: 0x80064c58 
 * PAL Size: 36b
 */
void pppAcceleCon(void* obj, void* param)
{
	void* dataPtr = *((void**)((char*)param + 0x0c));
	float* puVar2 = (float*)((char*)obj + *((int*)((char*)dataPtr + 0x04)) + 0x80);
	float uVar1 = DAT_8032fec8;
	
	puVar2[2] = uVar1;
	puVar2[1] = uVar1;
	*puVar2 = uVar1;
}