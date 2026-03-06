#include "ffcc/pppDrawMatrixNoRot.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x8008ac30
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixNoRot(struct _pppPObject* object, void*, struct _pppCtrlTable*)
{
    PSMTXScaleApply(
        *(Mtx*)((char*)object + 0x10),
        *(Mtx*)((char*)object + 0x40),
        (((_pppMngSt*)pppMngStPtr)->m_scale).x,
        (((_pppMngSt*)pppMngStPtr)->m_scale).y, 
        (((_pppMngSt*)pppMngStPtr)->m_scale).z
    );
    *(float*)((char*)object + 0x4c) =
        (*(float*)((char*)object + 0x1c)) * (((_pppMngSt*)pppMngStPtr)->m_scale).x +
        ppvWorldMatrix[0][3];
    *(float*)((char*)object + 0x5c) =
        (*(float*)((char*)object + 0x2c)) * (((_pppMngSt*)pppMngStPtr)->m_scale).y + ppvWorldMatrix[1][3];
    *(float*)((char*)object + 0x6c) =
        (*(float*)((char*)object + 0x3c)) * (((_pppMngSt*)pppMngStPtr)->m_scale).z + ppvWorldMatrix[2][3];
}
