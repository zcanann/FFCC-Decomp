#include "ffcc/pppDrawMatrixWood.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"


/*
 * --INFO--
 * PAL Address: 0x8008abc0
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixWood(_pppPObject* object, void*, _pppCtrlTable*) {
    char* p = (char*)object;

    PSMTXScaleApply(
        *(Mtx*)(p + 0x10),
        *(Mtx*)(p + 0x40),
        *(float*)((char*)pppMngStPtr + 0x28),
        *(float*)((char*)pppMngStPtr + 0x2C),
        *(float*)((char*)pppMngStPtr + 0x30)
    );

    *(float*)(p + 0x4C) = *(float*)(p + 0x1C);
    *(float*)(p + 0x5C) = *(float*)(p + 0x2C);
    *(float*)(p + 0x6C) = *(float*)(p + 0x3C);

    PSMTXConcat(ppvWorldMatrixWood, *(Mtx*)(p + 0x40), *(Mtx*)(p + 0x40));
}


