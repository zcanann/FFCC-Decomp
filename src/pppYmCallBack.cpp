#include "ffcc/pppYmCallBack.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"

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
void pppFrameYmCallBack(void)
{
	_pppMngSt* p_Var1;
	int iVar2;
	unsigned int uVar3;
	Vec local_18;
	
	p_Var1 = pppMngStPtr;
	// Complex graph ID comparison and matrix operations
	// TODO: Need to understand the structure better to complete implementation
}