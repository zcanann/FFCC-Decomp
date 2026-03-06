#include "ffcc/pppDrawMatrixFront.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

extern "C" {
extern unsigned char* lbl_8032ED50;
}

/*
 * --INFO--
 * PAL Address: 0x8006a584
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixFront(_pppPObject* object, void*, _pppCtrlTable*)
{
    Vec localPos;

    PSMTXScaleApply(
        *(Mtx*)((char*)object + 0x10),
        *(Mtx*)((char*)object + 0x40),
        *(f32*)(lbl_8032ED50 + 0x28),
        *(f32*)(lbl_8032ED50 + 0x2C),
        *(f32*)(lbl_8032ED50 + 0x30)
    );

    localPos.x = *(float*)((char*)object + 0x1c);
    localPos.y = *(float*)((char*)object + 0x2c);
    localPos.z = *(float*)((char*)object + 0x3c);

    PSMTXMultVec(ppvWorldMatrix, &localPos, &localPos);

    *(float*)((char*)object + 0x4c) = localPos.x;
    *(float*)((char*)object + 0x5c) = localPos.y;
    *(float*)((char*)object + 0x6c) = localPos.z;
}
