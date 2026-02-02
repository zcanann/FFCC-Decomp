#include "ffcc/pppWDrawMatrixLoop.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800c4dd8
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppWDrawMatrixLoop(_pppPObject* param_1)
{
    Vec* inVec;
    
    PSMTXConcat(ppvCameraMatrix0, param_1->m_localMatrix.value, *(Mtx*)((char*)param_1 + 0x34));
    PSVECScale((Vec*)((char*)param_1 + 0x34), (Vec*)((char*)param_1 + 0x34), pppMngStPtr->m_scale.x);
    PSVECScale((Vec*)((char*)param_1 + 0x38), (Vec*)((char*)param_1 + 0x38), pppMngStPtr->m_scale.y);
    inVec = (Vec*)((char*)param_1 + 0x3c);
    PSVECScale(inVec, inVec, pppMngStPtr->m_scale.z);
}