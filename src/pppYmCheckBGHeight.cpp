#include "ffcc/pppYmCheckBGHeight.h"
#include "ffcc/map.h"
#include "ffcc/pppPart.h"

#include <dolphin/types.h>

extern int DAT_8032ed70;
extern struct _pppMngSt* pppMngStPtr;
extern struct CMapMng MapMng;

// Float constants (addresses from Ghidra)
extern float FLOAT_80330ed0;
extern float FLOAT_80330ed4; 
extern float FLOAT_80330ed8;
extern float FLOAT_80330edc;

/*
 * --INFO--
 * PAL Address: 800d8c18
 * PAL Size: 4b
 */
void pppConstructYmCheckBGHeight(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 800d8abc  
 * PAL Size: 348b
 */
struct pppYmCheckBGHeight* pppFrameYmCheckBGHeight(struct pppYmCheckBGHeight* pppYmCheckBGHeight, struct UnkC* param_2)
{
	struct _pppMngSt* pppMngSt;
	int iVar1;
	double dVar2;
	unsigned char auStack_78[4];
	float local_74;
	float local_6c;
	float local_68;
	float local_64;
	float local_60;
	float local_5c;
	float local_58;
	float local_48;
	float local_44;
	float local_40;
	float local_3c;
	float local_38;
	float local_34;
	float local_30;
	float local_2c;
	float local_28;
	float local_24;
	
	pppMngSt = pppMngStPtr;
	if (DAT_8032ed70 == 0) {
		local_6c = FLOAT_80330ed0;
		local_68 = FLOAT_80330ed4;
		local_64 = FLOAT_80330ed0;
		dVar2 = (double)(pppMngStPtr->m_matrix).value[1][3];
		local_60 = (pppMngStPtr->m_matrix).value[0][3];
		local_58 = (pppMngStPtr->m_matrix).value[2][3];
		local_5c = (float)(dVar2 + (double)(float)param_2->m_unk0x4);
		local_30 = FLOAT_80330ed8;
		local_34 = FLOAT_80330ed8;
		local_38 = FLOAT_80330ed8;
		local_24 = FLOAT_80330edc;
		local_28 = FLOAT_80330edc;
		local_2c = FLOAT_80330edc;
		local_48 = FLOAT_80330ed0;
		local_44 = FLOAT_80330ed4;
		local_40 = FLOAT_80330ed0;
		local_3c = FLOAT_80330ed0;
		
		iVar1 = MapMng.CheckHitCylinderNear((CMapCylinder*)&local_60, (Vec*)&local_6c, 0xffffffff);
		if (iVar1 != 0) {
			// Simplified version - calculate hit position adjustment
			if ((float)(dVar2 - (double)(float)param_2->m_serializedDataOffsets) <= local_74) {
				dVar2 = (double)(local_74 + (float)param_2->m_unk0x8);
			}
		}
		(pppMngSt->m_position).y = (float)dVar2;
		(pppMngStPtr->m_matrix).value[0][3] = (pppMngSt->m_position).x;
		(pppMngStPtr->m_matrix).value[1][3] = (pppMngSt->m_position).y;
		(pppMngStPtr->m_matrix).value[2][3] = (pppMngSt->m_position).z;
		
		pppSetFpMatrix(pppMngSt);
	}
	return pppYmCheckBGHeight;
}