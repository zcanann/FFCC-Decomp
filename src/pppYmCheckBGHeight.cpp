#include "ffcc/pppYmCheckBGHeight.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/pppPart.h"

#include <dolphin/types.h>

/*
 * --INFO--
 * PAL Address: 0x800d8abc
 * PAL Size: 348b
 * EN Address: 0x800D8288
 * EN Size: 348b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmCheckBGHeight(pppYmCheckBGHeight* obj, pppYmCheckBGHeightStep* step)
{
    _pppMngSt* pppMngSt;
    Vec direction;
    Vec hitPos;
    float currentY;
    float zero;
    float probeLength;
    float bottomX;
    float bottomY;
    float bottomZ;

    if (ppvUserStopPartF == 0) {
        pppMngSt = ppvMng;
        zero = 0.0f;
        probeLength = -2000.0f;
        direction.x = zero;
        direction.y = probeLength;
        direction.z = zero;

        bottomY = ppvMng->m_matrix.value[1][3];
        currentY = bottomY;
        float finalY = currentY;
        bottomX = ppvMng->m_matrix.value[0][3];
        bottomZ = ppvMng->m_matrix.value[2][3];
        bottomY += step->m_probeStartOffset;
        CMapCylinder cylinder;
        cylinder.m_bottom.x = bottomX;
        cylinder.m_bottom.y = bottomY;
        cylinder.m_bottom.z = bottomZ;
        cylinder.m_axis.x = zero;
        cylinder.m_axis.y = probeLength;
        cylinder.m_axis.z = zero;
        cylinder.m_radius = zero;

        if (MapMng.CheckHitCylinderNear(&cylinder, &direction, (unsigned long)-1) != 0) {
            MapMng.m_hitMapObj->CalcHitPosition(&hitPos);
            if ((currentY - step->m_fallLimit) > hitPos.y) {
                finalY = currentY;
            } else {
                finalY = hitPos.y + step->m_hitHeightOffset;
            }
        } else {
            finalY = currentY;
        }

        pppMngSt->m_position.y = finalY;
        pppMngSt->BasePosition().y = finalY;
        pppMngSt->m_paramVec0.y = finalY;
        pppMngSt->UserPosition().y = finalY;

        ppvMng->m_matrix.value[0][3] = pppMngSt->m_position.x;
        ppvMng->m_matrix.value[1][3] = pppMngSt->m_position.y;
        ppvMng->m_matrix.value[2][3] = pppMngSt->m_position.z;

        pppSetFpMatrix(pppMngSt);
    }
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
}
