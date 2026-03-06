#include "ffcc/pppAccele.h"

extern int gPppCalcDisabled;
extern float lbl_8032FEC8;

/*
 * --INFO--
 * PAL Address: 0x80064c58
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppAcceleCon(pppAcceleObj* obj, pppAcceleUnkC* param)
{
	float* puVar2 = (float*)((char*)obj + param->m_serializedDataOffsets[1] + 0x80);
	float uVar1 = lbl_8032FEC8;

	puVar2[2] = uVar1;
	puVar2[1] = uVar1;
	*puVar2 = uVar1;
}

/*
 * --INFO--
 * PAL Address: 0x80064c7c
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppAccele(pppAcceleObj* obj, pppAcceleUnkB* param_2, pppAcceleUnkC* param_3)
{
	float* pfVar1 = (float*)((char*)obj + *param_3->m_serializedDataOffsets + 0x80);
	float* pfVar2 = (float*)((char*)obj + param_3->m_serializedDataOffsets[1] + 0x80);

	if (gPppCalcDisabled != 0) {
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

