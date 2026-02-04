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
    Vec *inVec;
    
    PSMTXConcat(ppvCameraMatrix0, pppPObject->m_localMatrix.value, *(Mtx*)((char*)pppPObject + 0x40));
    PSVECScale((Vec*)((char*)pppPObject + 0x40), (Vec*)((char*)pppPObject + 0x40), (pppMngStPtr->m_scale).x);
    PSVECScale((Vec*)((char*)pppPObject + 0x50), (Vec*)((char*)pppPObject + 0x50), (pppMngStPtr->m_scale).y);
    inVec = (Vec*)((char*)pppPObject + 0x60);
    PSVECScale(inVec, inVec, (pppMngStPtr->m_scale).z);
    return;
}