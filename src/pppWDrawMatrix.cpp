#include "ffcc/pppWDrawMatrix.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800905dc
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppWDrawMatrix(_pppPObject* pppPObject)
{
    Vec* inVec;
    
    PSMTXConcat(ppvCameraMatrix0, pppPObject->m_localMatrix.value, *(Mtx*)((char*)pppPObject + 0x34));
    PSVECScale((Vec*)((char*)pppPObject + 0x34), (Vec*)((char*)pppPObject + 0x34), (pppMngStPtr->m_scale).x);
    PSVECScale((Vec*)((char*)pppPObject + 0x38), (Vec*)((char*)pppPObject + 0x38), (pppMngStPtr->m_scale).y);
    inVec = (Vec*)((char*)pppPObject + 0x3c);
    PSVECScale(inVec, inVec, (pppMngStPtr->m_scale).z);
}