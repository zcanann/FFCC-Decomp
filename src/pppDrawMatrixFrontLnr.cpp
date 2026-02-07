#include "ffcc/pppDrawMatrixFrontLnr.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800d1968
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixFrontLnr(_pppPObject* param_1)
{
    Vec local_18;
    
    PSMTXScaleApply(
        *(Mtx*)((char*)param_1 + 0x10),
        *(Mtx*)((char*)param_1 + 0x40),
        *(float*)((char*)pppMngStPtr + 0x28),
        *(float*)((char*)pppMngStPtr + 0x2c),
        *(float*)((char*)pppMngStPtr + 0x30)
    );
    
    local_18.x = *(float*)((char*)param_1 + 0x1c);
    local_18.y = *(float*)((char*)param_1 + 0x2c);
    local_18.z = *(float*)((char*)param_1 + 0x3c);
    
    PSMTXMultVec(ppvCameraMatrix0, &local_18, &local_18);
    
    *(float*)((char*)param_1 + 0x4c) = local_18.x;
    *(float*)((char*)param_1 + 0x5c) = local_18.y;
    *(float*)((char*)param_1 + 0x6c) = local_18.z;
}
