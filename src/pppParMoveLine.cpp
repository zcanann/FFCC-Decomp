#include "ffcc/pppParMoveLine.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>

extern "C" {
const float FLOAT_80330638 = 0.0f;
}

struct ParMoveLineParams {
    u8 m_pad0[4];
    float m_speed;
};

static inline Vec* MoveLineCurrentPosition(_pppMngSt* mng)
{
    return &mng->UserPosition();
}

static inline Vec* MoveLinePreviousPosition(_pppMngSt* mng)
{
    return &mng->BasePosition();
}

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
    ParMoveLineParams* params;
    Vec local_1c;
    Vec VStack_28;
    float fVar1;
    float x;

    pppMngSt = ppvMng;
    params = reinterpret_cast<ParMoveLineParams*>(param_2);
    PSVECSubtract(&ppvMng->m_paramVec0, MoveLinePreviousPosition(ppvMng), &local_1c);

    x = pppMngSt->m_position.x;
    fVar1 = FLOAT_80330638;
    MoveLineCurrentPosition(pppMngSt)->x = x;
    MoveLineCurrentPosition(pppMngSt)->y = pppMngSt->m_position.y;
    MoveLineCurrentPosition(pppMngSt)->z = pppMngSt->m_position.z;

    if ((fVar1 != local_1c.x) || (fVar1 != local_1c.y) || (fVar1 != local_1c.z)) {
        PSVECNormalize(&local_1c, &VStack_28);
        PSVECScale(&VStack_28, &local_1c, params->m_speed * pppMngSt->m_savedPosition.y);
        PSVECAdd(&local_1c, &pppMngSt->m_position, &pppMngSt->m_position);
    }

    ppvMng->m_matrix.value[0][3] = pppMngSt->m_position.x;
    ppvMng->m_matrix.value[1][3] = pppMngSt->m_position.y;
    ppvMng->m_matrix.value[2][3] = pppMngSt->m_position.z;

    pppSetFpMatrix(pppMngSt);
}
