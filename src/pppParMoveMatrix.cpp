#include "ffcc/pppParMoveMatrix.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800D467C
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppParMoveMatrix(_pppPObject* obj, pppNoStep* stepData, _pppCtrlTable* ctrlTable)
{
	(void)obj;
	(void)stepData;
	(void)ctrlTable;
	_pppMngSt *pppMngSt;
	Vec moveDelta;
	Vec right;
	Vec up;
	Vec forward;
	Mtx scaleMtx;

	pppMngSt = ppvMng;
	Vec* previousPosition = &pppMngSt->UserPosition();
	Vec* position = &pppMngSt->m_position;
	PSVECSubtract(previousPosition, position, &moveDelta);

	f32 initialZero = 0.0f;
	if (((initialZero != moveDelta.x) || (initialZero != moveDelta.y)) || (initialZero != moveDelta.z)) {
		// Build an orthonormal basis whose Z axis follows the movement direction.
		PSVECNormalize(&moveDelta, &forward);
		right.x = forward.z;
		right.y = 0.0f;
		right.z = -forward.x;
		f32 zero = 0.0f;
		f32 forwardZ = forward.z;
		if ((zero == forwardZ) && (zero == right.z)) {
			// Movement is vertical; fall back to a fixed basis.
			right.y = 0.0f;
			right.x = 1.0f;
			right.z = 0.0f;
			up.x = 0.0f;
			up.y = 0.0f;
			up.z = 1.0f;
		}
		else {
			PSVECNormalize(&right, &right);
			PSVECCrossProduct(&forward, &right, &up);
			PSVECNormalize(&up, &up);
		}
		ppvMng->m_matrix.value[0][0] = right.x;
		ppvMng->m_matrix.value[1][0] = right.y;
		ppvMng->m_matrix.value[2][0] = right.z;
		ppvMng->m_matrix.value[0][1] = up.x;
		ppvMng->m_matrix.value[1][1] = up.y;
		ppvMng->m_matrix.value[2][1] = up.z;
		ppvMng->m_matrix.value[0][2] = forward.x;
		ppvMng->m_matrix.value[1][2] = forward.y;
		ppvMng->m_matrix.value[2][2] = forward.z;
		PSMTXScale(scaleMtx, ppvMng->m_scale.x, ppvMng->m_scale.y, ppvMng->m_scale.z);
		PSMTXConcat(scaleMtx, ppvMng->m_matrix.value, ppvMng->m_matrix.value);
		ppvMng->m_matrix.value[0][3] = pppMngSt->m_position.x;
		ppvMng->m_matrix.value[1][3] = pppMngSt->m_position.y;
		ppvMng->m_matrix.value[2][3] = pppMngSt->m_position.z;
		pppSetFpMatrix(pppMngSt);
	}
}
