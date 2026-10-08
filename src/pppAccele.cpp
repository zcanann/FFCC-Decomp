#include "global.h"
#include "ffcc/pppAccele.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"

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
void pppAcceleCon(_pppPObject* obj, _pppCtrlTable* ctrl)
{
	float* accel = GetPppAcceleAccel(obj, ctrl);

	accel[0] = accel[1] = accel[2] = 0.0f;
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
void pppAccele(_pppPObject* obj, pppAcceleStep* step, _pppCtrlTable* ctrl)
{
	float* value = GetPppAcceleValue(obj, ctrl);
	float* accel = GetPppAcceleAccel(obj, ctrl);

	if (ppvUserStopPartF != 0) {
		return;
	}

	if (step->m_graphId == obj->m_graphId) {
		accel[0] += step->m_x;
		accel[1] += step->m_y;
		accel[2] += step->m_z;
	}

	value[0] += accel[0];
	value[1] += accel[1];
	value[2] += accel[2];
}
