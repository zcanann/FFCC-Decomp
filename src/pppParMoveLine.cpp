#include "ffcc/pppParMoveLine.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>

extern "C" {
const float kPppParMoveLineZero = 0.0f;
}

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
void pppParMoveLine(_pppPObject* obj, ParMoveLineParams* params)
{
    (void)obj;
    _pppMngSt* pppMngSt;
    Vec moveDelta;
    Vec direction;
    float zero;
    float positionX;

    pppMngSt = ppvMng;
    // Line direction: from the base position toward m_paramVec0.
    PSVECSubtract(&ppvMng->m_paramVec0, MoveLinePreviousPosition(ppvMng), &moveDelta);

    positionX = pppMngSt->m_position.x;
    zero = kPppParMoveLineZero;
    MoveLineCurrentPosition(pppMngSt)->x = positionX;
    MoveLineCurrentPosition(pppMngSt)->y = pppMngSt->m_position.y;
    MoveLineCurrentPosition(pppMngSt)->z = pppMngSt->m_position.z;

    if ((zero != moveDelta.x) || (zero != moveDelta.y) || (zero != moveDelta.z)) {
        // Step along the line by speed * movement scale.
        PSVECNormalize(&moveDelta, &direction);
        PSVECScale(&direction, &moveDelta, params->m_speed * pppMngSt->m_movementScale);
        PSVECAdd(&moveDelta, &pppMngSt->m_position, &pppMngSt->m_position);
    }

    ppvMng->m_matrix.value[0][3] = pppMngSt->m_position.x;
    ppvMng->m_matrix.value[1][3] = pppMngSt->m_position.y;
    ppvMng->m_matrix.value[2][3] = pppMngSt->m_position.z;

    pppSetFpMatrix(pppMngSt);
}
