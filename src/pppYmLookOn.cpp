#include "ffcc/pppYmLookOn.h"
#include "global.h"
#include "ffcc/gobject.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/ppp_constants.h"
#include <dolphin/mtx.h>

STATIC_ASSERT(sizeof(YmLookOnDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(YmLookOnDataOffsets, m_workOffset) == 0x0);

static inline YmLookOnDataOffsets* GetYmLookOnDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<YmLookOnDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline CGObject** GetYmLookOnWork(pppYmLookOn* lookOn, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<CGObject**>(lookOn->m_workArea + GetYmLookOnDataOffsets(ctrl)->m_workOffset);
}

/*
 * --INFO--
 * PAL Address: 0x800d88c8
 * PAL Size: 476b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmLookOn(pppYmLookOn* lookOn, struct pppYmLookOnStep* step, struct _pppCtrlTable* ctrl)
{
    struct _pppMngSt* pppMngSt;
    CGObject* owner;
    CGObject** work;
    Vec toEffect;
    Vec axisX;
    Vec axisY;
    Vec axisZ;
    Vec targetPos;
    Vec effectPos;

    if (ppvUserStopPartF != 0) {
        return;
    }

    pppMngSt = ppvMng;
    owner = pppMngSt->m_lookTarget;
    work = GetYmLookOnWork(lookOn, ctrl);
    if (owner == nullptr) {
        if (*work == nullptr) {
            return;
        }
    }
    *work = owner;
    if (owner == nullptr) {
        owner = *work;
    }

    targetPos = owner->m_worldPosition;
    targetPos.y += step->m_dataValIndex;
    effectPos.x = ppvMng->m_matrix.value[0][3];
    effectPos.y = ppvMng->m_matrix.value[1][3];
    effectPos.z = ppvMng->m_matrix.value[2][3];
    PSVECSubtract(&effectPos, &targetPos, &toEffect);

    if (((gPppYmLookOnZero != toEffect.x) || (gPppYmLookOnZero != toEffect.y)) || (gPppYmLookOnZero != toEffect.z)) {
        PSVECNormalize(&toEffect, &axisZ);
        axisX.x = axisZ.z;
        axisX.y = gPppYmLookOnZero;
        axisX.z = -axisZ.x;
        f32 zero = gPppYmLookOnZero;
        if ((zero == axisZ.z) && (zero == axisX.z)) {
            axisX.x = gPppYmLookOnOne;
            axisX.y = gPppYmLookOnZero;
            axisX.z = gPppYmLookOnZero;
            axisY.x = gPppYmLookOnZero;
            axisY.y = gPppYmLookOnZero;
            axisY.z = gPppYmLookOnOne;
        } else {
            PSVECNormalize(&axisX, &axisX);
            PSVECCrossProduct(&axisZ, &axisX, &axisY);
            PSVECNormalize(&axisY, &axisY);
        }
        ppvMng->m_matrix.value[0][0] = axisX.x;
        ppvMng->m_matrix.value[1][0] = axisX.y;
        ppvMng->m_matrix.value[2][0] = axisX.z;
        ppvMng->m_matrix.value[0][1] = axisY.x;
        ppvMng->m_matrix.value[1][1] = axisY.y;
        ppvMng->m_matrix.value[2][1] = axisY.z;
        ppvMng->m_matrix.value[0][2] = axisZ.x;
        ppvMng->m_matrix.value[1][2] = axisZ.y;
        ppvMng->m_matrix.value[2][2] = axisZ.z;
        pppSetFpMatrix(pppMngSt);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d8aa4
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmLookOn(pppYmLookOn* lookOn, struct _pppCtrlTable* ctrl)
{
    *GetYmLookOnWork(lookOn, ctrl) = 0;
}
