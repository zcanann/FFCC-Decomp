#include "ffcc/pppDrawMatrixFront.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x8006a584
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixFront(_pppPObject* param_1)
{
    Vec localPos;

    PSMTXScaleApply(
        *(Mtx*)((char*)param_1 + 0x10),
        *(Mtx*)((char*)param_1 + 0x40),
        *(f32*)((char*)pppMngStPtr + 0x28),
        *(f32*)((char*)pppMngStPtr + 0x2C),
        *(f32*)((char*)pppMngStPtr + 0x30)
    );

    localPos.x = *(float*)((char*)param_1 + 0x1c);
    localPos.y = *(float*)((char*)param_1 + 0x2c);
    localPos.z = *(float*)((char*)param_1 + 0x3c);

    PSMTXMultVec(ppvWorldMatrix, &localPos, &localPos);

    *(float*)((char*)param_1 + 0x4c) = localPos.x;
    *(float*)((char*)param_1 + 0x5c) = localPos.y;
    *(float*)((char*)param_1 + 0x6c) = localPos.z;
}
