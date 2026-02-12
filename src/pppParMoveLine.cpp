#include "ffcc/pppParMoveLine.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>

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
    Vec VStack_28;
    Vec local_1c;
    float fVar1;

    pppMngSt = pppMngStPtr;
    PSVECSubtract((Vec*)((char*)pppMngStPtr + 0x68), (Vec*)((char*)pppMngStPtr + 0x58), &local_1c);

    fVar1 = 0.0f;
    *(float*)((char*)pppMngSt + 0x48) = pppMngSt->m_position.x;
    *(float*)((char*)pppMngSt + 0x4C) = pppMngSt->m_position.y;
    *(float*)((char*)pppMngSt + 0x50) = pppMngSt->m_position.z;

    if ((fVar1 != local_1c.x) || (fVar1 != local_1c.y) || (fVar1 != local_1c.z)) {
        PSVECNormalize(&local_1c, &VStack_28);
        PSVECScale(&VStack_28, &local_1c, *(float*)(param_2 + 4) * *(float*)((char*)pppMngSt + 0x54));
        PSVECAdd(&local_1c, &pppMngSt->m_position, &pppMngSt->m_position);
    }

    pppMngStPtr->m_matrix.value[0][3] = pppMngSt->m_position.x;
    pppMngStPtr->m_matrix.value[1][3] = pppMngSt->m_position.y;
    pppMngStPtr->m_matrix.value[2][3] = pppMngSt->m_position.z;

    pppSetFpMatrix(pppMngSt);
}
