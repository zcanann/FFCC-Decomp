#include "ffcc/pppYmCheckBGHeight.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/pppPart.h"

#include <dolphin/types.h>

extern "C" {
    void* pppSetFpMatrix__FP9_pppMngSt(struct _pppMngSt*);
}

static inline Vec* CheckBGHeightPreviousPosition(_pppMngSt* mng)
{
    return &mng->UserPosition();
}

static inline Vec* CheckBGHeightBasePosition(_pppMngSt* mng)
{
    return &mng->BasePosition();
}

static inline Vec* CheckBGHeightTargetPosition(_pppMngSt* mng)
{
    return &mng->m_paramVec0;
}

struct CheckBGHeightCylinder {
    Vec m_bottom;
    Vec m_top;
    Vec m_axis;
    float m_radius;
    Vec m_boundsMin;
    Vec m_boundsMax;
};
typedef char CheckBGHeightCylinder_size_check[(sizeof(CheckBGHeightCylinder) == sizeof(CMapCylinder)) ? 1 : -1];

/*
 * --INFO--
 * PAL Address: 0x800d8abc
 * PAL Size: 348b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
pppYmCheckBGHeight* pppFrameYmCheckBGHeight(
    pppYmCheckBGHeight* object, pppYmCheckBGHeightStep* param_2)
{
    _pppMngSt* pppMngSt;
    Vec direction;
    CheckBGHeightCylinder cylinder;
    Vec hitPos;
    float nextY;
    float zero;
    float probeY;
    float scale;
    float offset;
    float bottomX;
    float bottomY;
    float bottomZ;

    if (ppvUserStopPartF == 0) {
        pppMngSt = ppvMng;
        zero = 0.0f;
        probeY = -2000.0f;
        scale = 10000000000.0f;
        offset = -10000000000.0f;
        direction.x = zero;
        direction.y = probeY;
        direction.z = zero;

        bottomY = ppvMng->m_matrix.value[1][3];
        nextY = bottomY;
        float finalY = nextY;
        bottomX = ppvMng->m_matrix.value[0][3];
        bottomZ = ppvMng->m_matrix.value[2][3];
        bottomY += param_2->m_probeStartOffset;
        cylinder.m_boundsMin.z = scale;
        cylinder.m_boundsMin.y = scale;
        cylinder.m_boundsMin.x = scale;
        cylinder.m_boundsMax.z = offset;
        cylinder.m_boundsMax.y = offset;
        cylinder.m_boundsMax.x = offset;
        cylinder.m_bottom.x = bottomX;
        cylinder.m_bottom.y = bottomY;
        cylinder.m_bottom.z = bottomZ;
        cylinder.m_axis.x = zero;
        cylinder.m_axis.y = probeY;
        cylinder.m_axis.z = zero;
        cylinder.m_radius = zero;

        if (MapMng.CheckHitCylinderNear(reinterpret_cast<CMapCylinder*>(&cylinder), &direction, (unsigned long)-1) != 0) {
            MapMng.m_hitMapObj->CalcHitPosition(&hitPos);
            if ((nextY - param_2->m_fallLimit) > hitPos.y) {
                finalY = nextY;
            } else {
                finalY = hitPos.y + param_2->m_hitHeightOffset;
            }
        } else {
            finalY = nextY;
        }

        pppMngSt->m_position.y = finalY;
        CheckBGHeightBasePosition(pppMngSt)->y = finalY;
        CheckBGHeightTargetPosition(pppMngSt)->y = finalY;
        CheckBGHeightPreviousPosition(pppMngSt)->y = finalY;

        ppvMng->m_matrix.value[0][3] = pppMngSt->m_position.x;
        ppvMng->m_matrix.value[1][3] = pppMngSt->m_position.y;
        ppvMng->m_matrix.value[2][3] = pppMngSt->m_position.z;

        object = (pppYmCheckBGHeight*)pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }

    return object;
}

/*
 * --INFO--
 * PAL Address: 0x800d8c18
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmCheckBGHeight(pppYmCheckBGHeight*, _pppCtrlTable*)
{
	return;
}
