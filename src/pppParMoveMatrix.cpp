#include "ffcc/pppParMoveMatrix.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>

extern _pppMngSt* lbl_8032ED50;
extern float lbl_80330E38;
extern float lbl_80330E3C;

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
	
	pppMngSt = lbl_8032ED50;
	Vec* previousPosition = (Vec*)&pppMngSt->m_userFloat0;
	Vec* position = &pppMngSt->m_position;
	PSVECSubtract(previousPosition, position, &local_44);
	
	if (((lbl_80330E38 != local_44.x) || (lbl_80330E38 != local_44.y)) || (lbl_80330E38 != local_44.z)) {
		PSVECNormalize(&local_44, &local_68);
		local_50.x = local_68.z;
		local_50.y = lbl_80330E38;
		local_50.z = -local_68.x;
		if (!((local_68.z != lbl_80330E38) || (lbl_80330E38 != local_50.z))) {
			local_50.y = lbl_80330E38;
			local_50.x = lbl_80330E3C;
			local_50.z = lbl_80330E38;
			local_5c.x = lbl_80330E38;
			local_5c.y = lbl_80330E38;
			local_5c.z = lbl_80330E3C;
		}
		else {
			PSVECNormalize(&local_50, &local_50);
			PSVECCrossProduct(&local_68, &local_50, &local_5c);
			PSVECNormalize(&local_5c, &local_5c);
		}
		lbl_8032ED50->m_matrix.value[0][0] = local_50.x;
		lbl_8032ED50->m_matrix.value[1][0] = local_50.y;
		lbl_8032ED50->m_matrix.value[2][0] = local_50.z;
		lbl_8032ED50->m_matrix.value[0][1] = local_5c.x;
		lbl_8032ED50->m_matrix.value[1][1] = local_5c.y;
		lbl_8032ED50->m_matrix.value[2][1] = local_5c.z;
		lbl_8032ED50->m_matrix.value[0][2] = local_68.x;
		lbl_8032ED50->m_matrix.value[1][2] = local_68.y;
		lbl_8032ED50->m_matrix.value[2][2] = local_68.z;
		PSMTXScale(MStack_38, lbl_8032ED50->m_scale.x, lbl_8032ED50->m_scale.y, lbl_8032ED50->m_scale.z);
		PSMTXConcat(MStack_38, lbl_8032ED50->m_matrix.value, lbl_8032ED50->m_matrix.value);
		lbl_8032ED50->m_matrix.value[0][3] = pppMngSt->m_position.x;
		lbl_8032ED50->m_matrix.value[1][3] = pppMngSt->m_position.y;
		lbl_8032ED50->m_matrix.value[2][3] = pppMngSt->m_position.z;
		pppSetFpMatrix(pppMngSt);
	}
}
