#include "ffcc/pppDrawMatrixWood.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"

extern unsigned char* lbl_8032ED50;

/*
 * --INFO--
 * PAL Address: 0x8008abc0
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixWood(_pppPObject* param_1) {
    char* p = (char*)param_1;

    PSMTXScaleApply(
        *(Mtx*)(p + 0x10),
        *(Mtx*)(p + 0x40),
        *(float*)((char*)lbl_8032ED50 + 0x28),
        *(float*)((char*)lbl_8032ED50 + 0x2C),
        *(float*)((char*)lbl_8032ED50 + 0x30)
    );

    *(float*)(p + 0x4C) = *(float*)(p + 0x1C);
    *(float*)(p + 0x5C) = *(float*)(p + 0x2C);
    *(float*)(p + 0x6C) = *(float*)(p + 0x3C);

    PSMTXConcat(ppvWorldMatrixWood, *(Mtx*)(p + 0x40), *(Mtx*)(p + 0x40));
}
