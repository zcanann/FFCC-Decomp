#include "ffcc/pppYmCallBack.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/p_game.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800a6090
 * PAL Size: 4b
 */
void pppConstructYmCallBack(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 4b
 */
void pppDestructYmCallBack(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800a5fcc
 * PAL Size: 192b
 */
void pppFrameYmCallBack(void* pppYmCallBack, void* param_2)
{
	_pppMngSt* p_Var1;
	int iVar2;
	unsigned int uVar3;
	Vec local_18;
	
	p_Var1 = pppMngStPtr;
	
	// Get graph ID from pppYmCallBack object (assumed structure)
	uVar3 = *(unsigned int*)((char*)pppYmCallBack + 0xc); // m_graphId access
	
	// Graph ID comparison with bit shifting
	if (((int)uVar3 >> 0xc) + (unsigned int)((int)uVar3 < 0 && (uVar3 & 0xfff) != 0) == 
		*(short*)((char*)param_2 + 4)) {
		
		// Extract position from pppMngStPtr matrix
		local_18.x = p_Var1->m_matrix.value[0][3];
		local_18.y = p_Var1->m_matrix.value[1][3]; 
		local_18.z = p_Var1->m_matrix.value[2][3];
		
		// Transform position using world matrix
		PSMTXMultVec(ppvWorldMatrix, &local_18, &local_18);
		
		// Complex calculation for first parameter
		iVar2 = (int)&p_Var1[0x5f2411].m_scale / 0x158 + ((int)&p_Var1[0x5f2411].m_scale >> 0x1f);
		
		// Call particle frame callback
		Game.game.ParticleFrameCallback(
			iVar2 - (iVar2 >> 0x1f),
			(int)p_Var1->m_kind,
			(int)p_Var1->m_nodeIndex, 
			*(short*)((char*)param_2 + 6),
			*(short*)((char*)param_2 + 4),
			&local_18
		);
	}
}