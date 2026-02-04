#include "ffcc/pppWDrawMatrixFront.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80090654
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppWDrawMatrixFront(struct _pppPObject* param_1)
{
	Vec local_18;
	
	PSMTXScaleApply(
		param_1->m_localMatrix.value,
		(param_1 + 1)->m_localMatrix.value,
		(pppMngStPtr->m_scale).x,
		(pppMngStPtr->m_scale).y,
		(pppMngStPtr->m_scale).z
	);
	
	local_18.x = param_1->m_localMatrix.value[0][3];
	local_18.y = param_1->m_localMatrix.value[1][3];
	local_18.z = param_1->m_localMatrix.value[2][3];
	
	PSMTXMultVec(ppvCameraMatrix0, &local_18, &local_18);
	
	(param_1 + 1)->m_graphId = (s32)local_18.x;
	(param_1 + 1)->m_localMatrix.value[0][3] = local_18.y;
	(param_1 + 1)->m_localMatrix.value[1][3] = local_18.z;
}