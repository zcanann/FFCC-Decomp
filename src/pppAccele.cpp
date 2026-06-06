#include "global.h"
#include "ffcc/pppAccele.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"
extern "C" {
const float kPppAcceleZero = 0.0f;
}

STATIC_ASSERT(sizeof(PppAcceleDataOffsets) == 0x8);
STATIC_ASSERT(offsetof(PppAcceleDataOffsets, m_valueOffset) == 0x0);
STATIC_ASSERT(offsetof(PppAcceleDataOffsets, m_accelOffset) == 0x4);

static inline PppAcceleDataOffsets* GetPppAcceleDataOffsets(_pppCtrlTable* ctrl)
{
	return reinterpret_cast<PppAcceleDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline float* GetPppAcceleValue(_pppPObject* obj, _pppCtrlTable* ctrl)
{
	return reinterpret_cast<float*>(obj->m_workArea + GetPppAcceleDataOffsets(ctrl)->m_valueOffset);
}

static inline float* GetPppAcceleAccel(_pppPObject* obj, _pppCtrlTable* ctrl)
{
	return reinterpret_cast<float*>(obj->m_workArea + GetPppAcceleDataOffsets(ctrl)->m_accelOffset);
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
	float* puVar2 = GetPppAcceleAccel(obj, param);
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
	float* pfVar1 = GetPppAcceleValue(obj, param_3);
	float* pfVar2 = GetPppAcceleAccel(obj, param_3);

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
