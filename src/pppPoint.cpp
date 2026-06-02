#include "ffcc/pppPoint.h"
#include "ffcc/partMng.h"

extern const float kPppPointZero[2];

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
	int dataOffset = ctrlTable->m_serializedDataOffsets[0];
	float* dst = (float*)(pObject->m_workArea + dataOffset);
	float value = kPppPointZero[0];

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

	int dataOffset = ctrlTable->m_serializedDataOffsets[0];
	float* dst = (float*)(pObject->m_workArea + dataOffset);

	dst[0] += step->m_x;
	dst[1] += step->m_y;
	dst[2] += step->m_z;
}
