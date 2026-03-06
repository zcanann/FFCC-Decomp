#include "ffcc/pppDrawMatrix.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80065350
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrix(struct _pppPObject* object, void*, struct _pppCtrlTable*)
{
	PSMTXConcat(ppvWorldMatrix, *(Mtx*)((char*)object + 0x10), *(Mtx*)((char*)object + 0x40));
}
