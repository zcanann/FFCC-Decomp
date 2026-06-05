#include "ffcc/pppAccele.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"
extern "C" {
const float kPppAcceleZero = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x80064c58
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppAcceleCon(_pppPObject* obj, _pppCtrlTable* param)
{
	float* puVar2 = (float*)(obj->m_workArea + param->m_serializedDataOffsets[1]);
	float uVar1 = kPppAcceleZero;

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
void pppAccele(_pppPObject* obj, pppAcceleStep* param_2, _pppCtrlTable* param_3)
{
	float* pfVar1 = (float*)(obj->m_workArea + *param_3->m_serializedDataOffsets);
	float* pfVar2 = (float*)(obj->m_workArea + param_3->m_serializedDataOffsets[1]);

	if (ppvUserStopPartF != 0) {
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
