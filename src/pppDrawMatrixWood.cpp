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
void pppDrawMatrixWood(_pppPObject* param_1)
{
    PSMTXScaleApply(
        (MtxPtr)((char*)param_1 + 0x10),
        (MtxPtr)((char*)param_1 + 0x40),
        *(float*)((char*)pppMngStPtr + 0x28),
        *(float*)((char*)pppMngStPtr + 0x2C),
        *(float*)((char*)pppMngStPtr + 0x30)
    );

    *(float*)((char*)param_1 + 0x4C) = *(float*)((char*)param_1 + 0x1C);
    *(float*)((char*)param_1 + 0x5C) = *(float*)((char*)param_1 + 0x2C);
    *(float*)((char*)param_1 + 0x6C) = *(float*)((char*)param_1 + 0x3C);

    PSMTXConcat(
        ppvWorldMatrixWood,
        (MtxPtr)((char*)param_1 + 0x40),
        (MtxPtr)((char*)param_1 + 0x40)
    );
}
