#include "ffcc/pppParMoveLine.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>

extern const float FLOAT_80330638;

/*
 * --INFO--
 * PAL Address: 0x800906dc
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppParMoveLine(_pppPObject* param_1, int param_2)
{
    _pppMngSt* pppMngSt;
    Vec local_1c;
    Vec VStack_28;
    float fVar1;
    float x;

    pppMngSt = ppvMng;
    PSVECSubtract((Vec*)((char*)ppvMng + 0x68), (Vec*)((char*)ppvMng + 0x58), &local_1c);

    x = pppMngSt->m_position.x;
    fVar1 = FLOAT_80330638;
    *(float*)((char*)pppMngSt + 0x48) = x;
    *(float*)((char*)pppMngSt + 0x4C) = pppMngSt->m_position.y;
    *(float*)((char*)pppMngSt + 0x50) = pppMngSt->m_position.z;

    if ((fVar1 != local_1c.x) || (fVar1 != local_1c.y) || (fVar1 != local_1c.z)) {
        PSVECNormalize(&local_1c, &VStack_28);
        PSVECScale(&VStack_28, &local_1c, *(float*)(param_2 + 4) * *(float*)((char*)pppMngSt + 0x54));
        PSVECAdd(&local_1c, &pppMngSt->m_position, &pppMngSt->m_position);
    }

    ppvMng->m_matrix.value[0][3] = pppMngSt->m_position.x;
    ppvMng->m_matrix.value[1][3] = pppMngSt->m_position.y;
    ppvMng->m_matrix.value[2][3] = pppMngSt->m_position.z;

    pppSetFpMatrix(pppMngSt);
}
