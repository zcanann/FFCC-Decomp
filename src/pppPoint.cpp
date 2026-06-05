#include "global.h"
#include "ffcc/pppPoint.h"
#include "ffcc/partMng.h"

extern "C" const float kPppPointZero = 0.0f;

struct PppPointDataOffsets {
	s32 m_pointOffset;
};

STATIC_ASSERT(offsetof(PppPointDataOffsets, m_pointOffset) == 0x0);

static inline PppPointDataOffsets* GetPppPointDataOffsets(_pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<PppPointDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

static inline float* GetPppPointWork(_pppPObject* pObject, _pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<float*>(pObject->m_workArea + GetPppPointDataOffsets(ctrlTable)->m_pointOffset);
}

/*
 * --INFO--
 * PAL Address: 0x80065cd8
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointCon(_pppPObject* pObject, _pppCtrlTable* ctrlTable)
{
	float* dst = GetPppPointWork(pObject, ctrlTable);
	float value = kPppPointZero;

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
void pppPoint(_pppPObject* pObject, pppPointStep* step, _pppCtrlTable* ctrlTable)
{
	if (ppvUserStopPartF != 0) {
		return;
	}

	if (step->m_graphId != pObject->m_graphId) {
		return;
	}

	float* dst = GetPppPointWork(pObject, ctrlTable);

	dst[0] += step->m_x;
	dst[1] += step->m_y;
	dst[2] += step->m_z;
}
