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
    _pppMngSt* pppMngSt = pppMngStPtr;
    Vec local_1c;
    Vec VStack_28;
    float fVar1 = 0.0f;
    Vec* position = (Vec*)((char*)pppMngSt + 0x8);
    Vec* previousPosition = (Vec*)((char*)pppMngSt + 0x48);

    PSVECSubtract((Vec*)((char*)pppMngSt + 0x68), (Vec*)((char*)pppMngSt + 0x58), &local_1c);

    previousPosition->x = position->x;
    previousPosition->y = position->y;
    previousPosition->z = position->z;

    if ((fVar1 != local_1c.x) || (fVar1 != local_1c.y) || (fVar1 != local_1c.z)) {
        PSVECNormalize(&local_1c, &VStack_28);

        float scaleValue = *(float*)(param_2 + 4) * *(float*)((char*)pppMngSt + 0x54);
        PSVECScale(&VStack_28, &local_1c, scaleValue);
        PSVECAdd(&local_1c, position, position);
    }

    pppMngStPtr->m_matrix.value[0][3] = position->x;
    pppMngStPtr->m_matrix.value[1][3] = position->y;
    pppMngStPtr->m_matrix.value[2][3] = position->z;

    pppSetFpMatrix(pppMngSt);
}
