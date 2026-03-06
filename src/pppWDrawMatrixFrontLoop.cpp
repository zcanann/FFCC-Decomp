#include "ffcc/pppWDrawMatrixFrontLoop.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

extern "C" {
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
void pppWDrawMatrixFrontLoop(struct _pppPObject* object, void*, struct _pppCtrlTable*)
{
    Vec localPos;

    PSMTXScaleApply(
        *(Mtx*)((char*)object + 0x10),
        *(Mtx*)((char*)object + 0x40),
        *(f32*)(pppMngStPtr + 0x28),
        *(f32*)(pppMngStPtr + 0x2C),
        *(f32*)(pppMngStPtr + 0x30)
    );

    localPos.x = *(float*)((char*)object + 0x1C);
    localPos.y = *(float*)((char*)object + 0x2C);
    localPos.z = *(float*)((char*)object + 0x3C);

    PSMTXMultVec(ppvCameraMatrix02, &localPos, &localPos);

    *(float*)((char*)object + 0x4C) = localPos.x;
    *(float*)((char*)object + 0x5C) = localPos.y;
    *(float*)((char*)object + 0x6C) = localPos.z;
}


