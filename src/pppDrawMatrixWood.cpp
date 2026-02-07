#include "ffcc/pppDrawMatrixWood.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"

/*
 * --INFO--
 * PAL Address: 0x8008abc0
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixWood(_pppPObject* param_1)
{
	PSMTXScaleApply(
		param_1->m_localMatrix.value,
		param_1[1].m_localMatrix.value,
		(pppMngStPtr->m_scale).x,
		(pppMngStPtr->m_scale).y,
		(pppMngStPtr->m_scale).z
	);

	param_1[1].m_localMatrix.value[0][3] = (param_1->m_localMatrix).value[0][3];
	param_1[1].m_localMatrix.value[1][3] = (param_1->m_localMatrix).value[1][3];
	param_1[1].m_localMatrix.value[2][3] = (param_1->m_localMatrix).value[2][3];

	PSMTXConcat(ppvWorldMatrixWood, param_1[1].m_localMatrix.value, param_1[1].m_localMatrix.value);
}
