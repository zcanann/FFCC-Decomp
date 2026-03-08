#include "ffcc/pppYmCheckBGHeight.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/pppPart.h"
#include "ffcc/symbols_shared.h"

#include <dolphin/types.h>


extern "C" {
    int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, unsigned int);
    void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
    void* pppSetFpMatrix__FP9_pppMngSt(struct _pppMngSt*);
}

struct CMapCylinderRaw {
    Vec m_bottom;
    Vec m_direction;
    f32 m_field_18;
    f32 m_field_1C;
    f32 m_field_20;
    f32 m_field_24;
    f32 m_field_28;
    f32 m_field_2C;
    f32 m_field_30;
    f32 m_field_34;
    f32 m_field_38;
    f32 m_field_3C;
};

/*
 * --INFO--
 * PAL Address: 0x800d8c18
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmCheckBGHeight(struct pppYmCheckBGHeight*, struct pppYmCheckBGHeightUnkC*)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800d8abc
 * PAL Size: 348b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
struct pppYmCheckBGHeight* pppFrameYmCheckBGHeight(
    struct pppYmCheckBGHeight* pppYmCheckBGHeight, struct pppYmCheckBGHeightUnkC* param_2)
{
    _pppMngSt* pppMngSt = pppMngStPtr;

    if (gPppCalcDisabled == 0) {
        Vec direction;
        CMapCylinderRaw cyl;
        Vec hitPos;
        float currentY = pppMngStPtr->m_matrix.value[1][3];

        direction.x = kPppYmCheckBGHeightAxisZero;
        direction.y = kPppYmCheckBGHeightProbeDirY;
        direction.z = kPppYmCheckBGHeightAxisZero;

        cyl.m_bottom.x = pppMngStPtr->m_matrix.value[0][3];
        cyl.m_bottom.y = currentY + param_2->m_unk0x4;
        cyl.m_bottom.z = pppMngStPtr->m_matrix.value[2][3];
        cyl.m_direction.x = kPppYmCheckBGHeightAxisZero;
        cyl.m_direction.y = kPppYmCheckBGHeightProbeDirY;
        cyl.m_direction.z = kPppYmCheckBGHeightAxisZero;
        cyl.m_field_18 = kPppYmCheckBGHeightAxisZero;
        cyl.m_field_1C = kPppYmCheckBGHeightCylinderScale;
        cyl.m_field_20 = kPppYmCheckBGHeightAxisZero;
        cyl.m_field_24 = kPppYmCheckBGHeightAxisZero;
        cyl.m_field_28 = kPppYmCheckBGHeightCylinderScale;
        cyl.m_field_2C = kPppYmCheckBGHeightCylinderScale;
        cyl.m_field_30 = kPppYmCheckBGHeightCylinderScale;
        cyl.m_field_34 = kPppYmCheckBGHeightCylinderOffset;
        cyl.m_field_38 = kPppYmCheckBGHeightCylinderOffset;
        cyl.m_field_3C = kPppYmCheckBGHeightCylinderOffset;

        if ((CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, (CMapCylinder*)&cyl, &direction, 0xFFFFFFFF) != 0) &&
            (CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A78), &hitPos),
             (currentY - param_2->m_unk0xC) <= hitPos.y)) {
            currentY = hitPos.y + param_2->m_unk0x8;
        }

        pppMngSt->m_position.y = currentY;
        pppMngSt->m_savedPosition.y = currentY;
        pppMngSt->m_paramVec0.y = currentY;
        pppMngSt->m_previousPosition.y = currentY;

        pppMngStPtr->m_matrix.value[0][3] = pppMngSt->m_position.x;
        pppMngStPtr->m_matrix.value[1][3] = pppMngSt->m_position.y;
        pppMngStPtr->m_matrix.value[2][3] = pppMngSt->m_position.z;

        pppYmCheckBGHeight = (struct pppYmCheckBGHeight*)pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }

    return pppYmCheckBGHeight;
}
