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
void pppDrawMatrix(struct _pppPObject* param_1)
{
	PSMTXConcat(ppvWorldMatrix, *(Mtx*)((char*)param_1 + 0x10), *(Mtx*)((char*)param_1 + 0x40));
}