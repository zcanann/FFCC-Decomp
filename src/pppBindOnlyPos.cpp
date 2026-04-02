#include "ffcc/pppBindOnlyPos.h"
#include "ffcc/ppp_linkage.h"


/*
 * --INFO--
 * PAL Address: 0x80127b54
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameBindOnlyPos(_pppPObject*, void*, _pppCtrlTable*)
{
	if (gPppCalcDisabled != 0) {
		return;
	}

	if (*(volatile unsigned int*)((char*)pppMngStPtr + 0xd8) != 0) {
		return;
	}
}



/*
 * --INFO--
 * PAL Address: 0x80127b70
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructBindOnlyPos(_pppPObjLink*, _pppCtrlTable*)
{
	return;
}
