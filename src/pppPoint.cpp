#include "ffcc/pppPoint.h"
#include "ffcc/partMng.h"

extern const float kPppPointZero;

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
	int dataOffset = ctrlTable->m_serializedDef->m_workOffset;
	float* dst = (float*)((char*)pObject + dataOffset + 0x80);
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
	if (gPppCalcDisabled != 0) {
		return;
	}

	if (step->m_graphId != *(int*)((char*)pObject + 0xC)) {
		return;
	}

	int dataOffset = ctrlTable->m_serializedDef->m_workOffset;
	float* dst = (float*)((char*)pObject + dataOffset + 0x80);

	dst[0] += step->m_x;
	dst[1] += step->m_y;
	dst[2] += step->m_z;
}
