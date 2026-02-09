#include "ffcc/pppKeDMat.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80095854
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeDMatDraw(_pppPObject* pObject)
{
    PSMTXConcat(ppvWorldMatrix, pObject->m_localMatrix.value, *(Mtx*)((char*)pObject + 0x80));
}
