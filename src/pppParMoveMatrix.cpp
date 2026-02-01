#include "ffcc/pppParMoveMatrix.h"
#include "ffcc/pppPart.h"

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
void pppParMoveMatrix(void)
{
	_pppMngSt *pppMngSt;
	Vec local_68;
	Vec local_5c;
	Vec local_50;
	Vec local_44;
	Mtx MStack_38;
	
	pppMngSt = pppMngStPtr;
	
	// Access m_previousPosition and m_position via pointer arithmetic since structure is WIP
	// From objdiff: m_previousPosition appears to be at offset 0x48, m_position at 0x8
	Vec* previousPosition = (Vec*)((char*)pppMngStPtr + 0x48);
	Vec* position = (Vec*)((char*)pppMngStPtr + 0x8);
	PSVECSubtract(previousPosition, position, &local_44);
	
	if (((0.0f != local_44.x) || (0.0f != local_44.y)) || (0.0f != local_44.z)) {
		PSVECNormalize(&local_44, &local_68);
		local_50.z = -local_68.x;
		local_50.x = local_68.z;
		local_50.y = 0.0f;
		if ((0.0f == local_68.z) && (0.0f == local_50.z)) {
			local_50.x = 1.0f;
			local_50.z = 0.0f;
			local_5c.x = 0.0f;
			local_5c.y = 0.0f;
			local_5c.z = 1.0f;
		}
		else {
			PSVECNormalize(&local_50, &local_50);
			PSVECCrossProduct(&local_68, &local_50, &local_5c);
			PSVECNormalize(&local_5c, &local_5c);
		}
		(pppMngStPtr->m_matrix).value[0][0] = local_50.x;
		(pppMngStPtr->m_matrix).value[1][0] = local_50.y;
		(pppMngStPtr->m_matrix).value[2][0] = local_50.z;
		(pppMngStPtr->m_matrix).value[0][1] = local_5c.x;
		(pppMngStPtr->m_matrix).value[1][1] = local_5c.y;
		(pppMngStPtr->m_matrix).value[2][1] = local_5c.z;
		(pppMngStPtr->m_matrix).value[0][2] = local_68.x;
		(pppMngStPtr->m_matrix).value[1][2] = local_68.y;
		(pppMngStPtr->m_matrix).value[2][2] = local_68.z;
		PSMTXScale(MStack_38, (pppMngStPtr->m_scale).x, (pppMngStPtr->m_scale).y, (pppMngStPtr->m_scale).z);
		PSMTXConcat(MStack_38, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
		(pppMngStPtr->m_matrix).value[0][3] = (pppMngSt->m_position).x;
		(pppMngStPtr->m_matrix).value[1][3] = (pppMngSt->m_position).y;
		(pppMngStPtr->m_matrix).value[2][3] = (pppMngSt->m_position).z;
		pppSetFpMatrix(pppMngSt);
	}
}