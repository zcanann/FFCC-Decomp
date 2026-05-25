#include "ffcc/pppParMoveMatrix.h"
#include "ffcc/pppPart.h"
#include "ffcc/ppp_constants.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800e092c
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppParMoveMatrix(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable)
{
	(void)obj;
	(void)stepData;
	(void)ctrlTable;
	_pppMngSt *pppMngSt;
	Vec local_44;
	Vec local_50;
	Vec local_5c;
	Vec local_68;
	Mtx MStack_38;
	
	pppMngSt = ppvMng;
	Vec* previousPosition = (Vec*)&pppMngSt->m_userFloat0;
	Vec* position = &pppMngSt->m_position;
	PSVECSubtract(previousPosition, position, &local_44);
	
	if (((gPppParMoveMatrixZero != local_44.x) || (gPppParMoveMatrixZero != local_44.y)) || (gPppParMoveMatrixZero != local_44.z)) {
		PSVECNormalize(&local_44, &local_68);
		local_50.x = local_68.z;
		local_50.y = gPppParMoveMatrixZero;
		local_50.z = -local_68.x;
		f32 zero = gPppParMoveMatrixZero;
		f32 axisZ = local_68.z;
		if ((zero == axisZ) && (zero == local_50.z)) {
			local_50.y = gPppParMoveMatrixZero;
			local_50.x = gPppParMoveMatrixOne;
			local_50.z = gPppParMoveMatrixZero;
			local_5c.x = gPppParMoveMatrixZero;
			local_5c.y = gPppParMoveMatrixZero;
			local_5c.z = gPppParMoveMatrixOne;
		}
		else {
			PSVECNormalize(&local_50, &local_50);
			PSVECCrossProduct(&local_68, &local_50, &local_5c);
			PSVECNormalize(&local_5c, &local_5c);
		}
		ppvMng->m_matrix.value[0][0] = local_50.x;
		ppvMng->m_matrix.value[1][0] = local_50.y;
		ppvMng->m_matrix.value[2][0] = local_50.z;
		ppvMng->m_matrix.value[0][1] = local_5c.x;
		ppvMng->m_matrix.value[1][1] = local_5c.y;
		ppvMng->m_matrix.value[2][1] = local_5c.z;
		ppvMng->m_matrix.value[0][2] = local_68.x;
		ppvMng->m_matrix.value[1][2] = local_68.y;
		ppvMng->m_matrix.value[2][2] = local_68.z;
		PSMTXScale(MStack_38, ppvMng->m_scale.x, ppvMng->m_scale.y, ppvMng->m_scale.z);
		PSMTXConcat(MStack_38, ppvMng->m_matrix.value, ppvMng->m_matrix.value);
		ppvMng->m_matrix.value[0][3] = pppMngSt->m_position.x;
		ppvMng->m_matrix.value[1][3] = pppMngSt->m_position.y;
		ppvMng->m_matrix.value[2][3] = pppMngSt->m_position.z;
		pppSetFpMatrix(pppMngSt);
	}
}


