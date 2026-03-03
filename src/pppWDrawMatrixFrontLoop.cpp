#include "ffcc/pppWDrawMatrixFrontLoop.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

extern "C" {
extern unsigned char* lbl_8032ED50;
extern Mtx ppvCameraMatrix02;
}

/*
 * --INFO--
 * PAL Address: 0x800c4f50
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppWDrawMatrixFrontLoop(struct _pppPObject* param_1)
{
    Vec localPos;

    PSMTXScaleApply(
        *(Mtx*)((char*)param_1 + 0x10),
        *(Mtx*)((char*)param_1 + 0x40),
        *(f32*)(lbl_8032ED50 + 0x28),
        *(f32*)(lbl_8032ED50 + 0x2C),
        *(f32*)(lbl_8032ED50 + 0x30)
    );

    localPos.x = *(float*)((char*)param_1 + 0x1C);
    localPos.y = *(float*)((char*)param_1 + 0x2C);
    localPos.z = *(float*)((char*)param_1 + 0x3C);

    PSMTXMultVec(ppvCameraMatrix02, &localPos, &localPos);

    *(float*)((char*)param_1 + 0x4C) = localPos.x;
    *(float*)((char*)param_1 + 0x5C) = localPos.y;
    *(float*)((char*)param_1 + 0x6C) = localPos.z;
}
