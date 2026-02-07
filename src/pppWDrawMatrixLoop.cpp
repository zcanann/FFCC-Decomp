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
    PSMTXConcat(ppvCameraMatrix0, param_1->m_localMatrix.value, (param_1 + 1)->m_localMatrix.value);
    PSVECScale((Vec*)((char*)param_1 + 0x40), (Vec*)((char*)param_1 + 0x40), (pppMngStPtr->m_scale).x);
    PSVECScale((Vec*)((char*)param_1 + 0x50), (Vec*)((char*)param_1 + 0x50), (pppMngStPtr->m_scale).y);
    PSVECScale((Vec*)((char*)param_1 + 0x60), (Vec*)((char*)param_1 + 0x60), (pppMngStPtr->m_scale).z);
}
