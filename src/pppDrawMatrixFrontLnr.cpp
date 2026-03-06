#include "ffcc/pppDrawMatrixFrontLnr.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

extern "C" {
extern Mtx ppvCameraMatrix02;
}

/*
 * --INFO--
 * PAL Address: 0x800d1968
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixFrontLnr(_pppPObject* object, void*, _pppCtrlTable*)
{
    Vec local_18;
    _pppMngSt* mng = (_pppMngSt*)pppMngStPtr;
    
    PSMTXScaleApply(
        *(Mtx*)((char*)object + 0x10),
        *(Mtx*)((char*)object + 0x40),
        mng->m_scale.x,
        mng->m_scale.y,
        mng->m_scale.z
    );
    
    local_18.x = *(float*)((char*)object + 0x1c);
    local_18.y = *(float*)((char*)object + 0x2c);
    local_18.z = *(float*)((char*)object + 0x3c);
    
    PSMTXMultVec(ppvCameraMatrix02, &local_18, &local_18);
    
    *(float*)((char*)object + 0x4c) = local_18.x;
    *(float*)((char*)object + 0x5c) = local_18.y;
    *(float*)((char*)object + 0x6c) = local_18.z;
}


