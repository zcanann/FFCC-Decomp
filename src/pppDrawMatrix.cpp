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
void pppDrawMatrix(struct _pppPObject* object, pppNoStep*, struct _pppCtrlTable*)
{
	PSMTXConcat(ppvWorldMatrix, object->m_localMatrix.value, object->m_drawMatrix.value);
}
