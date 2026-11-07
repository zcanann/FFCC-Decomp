#include "global.h"
#include "ffcc/pppPoint.h"
#include "ffcc/partMng.h"

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
	float* dst = (float*)(pObject->m_workArea + ctrlTable->m_serializedDataOffsets[0]);

	dst[0] = dst[1] = dst[2] = 0.0f;
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

	float* dst = (float*)(pObject->m_workArea + ctrlTable->m_serializedDataOffsets[0]);

	dst[0] += step->m_x;
	dst[1] += step->m_y;
	dst[2] += step->m_z;
}
