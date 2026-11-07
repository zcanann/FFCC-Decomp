#include "global.h"
#include "ffcc/pppAccele.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_linkage.h"

static inline float* GetPppAcceleValue(_pppPObject* obj, _pppCtrlTable* ctrl)
{
	return reinterpret_cast<float*>(obj->m_workArea + ctrl->m_serializedDataOffsets[0]);
}

static inline float* GetPppAcceleAccel(_pppPObject* obj, _pppCtrlTable* ctrl)
{
	return reinterpret_cast<float*>(obj->m_workArea + ctrl->m_serializedDataOffsets[1]);
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
