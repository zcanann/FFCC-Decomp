#include "ffcc/pppDrawMatrixNoRot.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

struct pppDrawMatrixNoRotMngLayout
{
    unsigned char m_pad00[0x64];
    Vec m_scale;
};

/*
 * --INFO--
 * PAL Address: 0x8008ac30
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixNoRot(struct _pppPObject* param_1)
{
    PSMTXScaleApply(
        *(Mtx*)((char*)param_1 + 0x10),
        *(Mtx*)((char*)param_1 + 0x40),
        ((volatile pppDrawMatrixNoRotMngLayout*)lbl_8032ED50)->m_scale.x,
        ((volatile pppDrawMatrixNoRotMngLayout*)lbl_8032ED50)->m_scale.y,
        ((volatile pppDrawMatrixNoRotMngLayout*)lbl_8032ED50)->m_scale.z
    );
    *(float*)((char*)param_1 + 0x4c) =
        (*(float*)((char*)param_1 + 0x1c)) *
            ((volatile pppDrawMatrixNoRotMngLayout*)lbl_8032ED50)->m_scale.x +
        ppvWorldMatrix[0][3];
    *(float*)((char*)param_1 + 0x5c) =
        (*(float*)((char*)param_1 + 0x2c)) *
            ((volatile pppDrawMatrixNoRotMngLayout*)lbl_8032ED50)->m_scale.y +
        ppvWorldMatrix[1][3];
    *(float*)((char*)param_1 + 0x6c) =
        (*(float*)((char*)param_1 + 0x3c)) *
            ((volatile pppDrawMatrixNoRotMngLayout*)lbl_8032ED50)->m_scale.z +
        ppvWorldMatrix[2][3];
}
