#include "ffcc/pppAccele.h"

extern int DAT_8032ed70;
extern float DAT_8032fec8;

/*
 * --INFO--
 * PAL Address: 0x80064c7c
 * PAL Size: 156b
 */
void pppAccele(pppAcceleObj* obj, UnkB* param_2, UnkC* param_3)
{
	float* pfVar1 = (float*)((char*)obj + *param_3->m_serializedDataOffsets + 0x80);
	float* pfVar2 = (float*)((char*)obj + param_3->m_serializedDataOffsets[1] + 0x80);
	
	if (DAT_8032ed70 != 0) {
		return;
	}
	
	if (param_2->m_graphId == obj->m_graphId) {
		*pfVar2 = *pfVar2 + (float)param_2->m_initWOrk;
		pfVar2[1] = pfVar2[1] + param_2->m_stepValue;
		pfVar2[2] = pfVar2[2] + (float)param_2->m_arg3;
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
void pppAcceleCon(pppAcceleObj* obj, UnkC* param)
{
	float* puVar2 = (float*)((char*)obj + param->m_serializedDataOffsets[1] + 0x80);
	float uVar1 = DAT_8032fec8;
	
	puVar2[2] = uVar1;
	puVar2[1] = uVar1;
	*puVar2 = uVar1;
}