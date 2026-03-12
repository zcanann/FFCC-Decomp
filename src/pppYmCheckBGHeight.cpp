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
    f32 m_radius;
    f32 m_height;
    Vec m_top;
    Vec m_direction2;
    f32 m_radius2;
    f32 m_height2;
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
    _pppMngSt* pppMngSt;
    Vec direction;
    CMapCylinderRaw cylinder;
    Vec hitPos;
    double y;

    if (gPppCalcDisabled == 0) {
        pppMngSt = pppMngStPtr;
        direction.x = kPppYmCheckBGHeightAxisZero;
        direction.y = kPppYmCheckBGHeightProbeDirY;
        direction.z = kPppYmCheckBGHeightAxisZero;

        y = pppMngStPtr->m_matrix.value[1][3];
        cylinder.m_bottom.x = pppMngStPtr->m_matrix.value[0][3];
        cylinder.m_bottom.z = pppMngStPtr->m_matrix.value[2][3];
        cylinder.m_bottom.y = (float)(y + (double)param_2->m_unk0x4);
        cylinder.m_direction.x = kPppYmCheckBGHeightAxisZero;
        cylinder.m_direction.y = kPppYmCheckBGHeightProbeDirY;
        cylinder.m_direction.z = kPppYmCheckBGHeightAxisZero;
        cylinder.m_radius = kPppYmCheckBGHeightAxisZero;
        cylinder.m_height = kPppYmCheckBGHeightCylinderScale;
        cylinder.m_top.x = kPppYmCheckBGHeightAxisZero;
        cylinder.m_top.y = kPppYmCheckBGHeightAxisZero;
        cylinder.m_top.z = kPppYmCheckBGHeightCylinderScale;
        cylinder.m_direction2.x = kPppYmCheckBGHeightCylinderScale;
        cylinder.m_direction2.y = kPppYmCheckBGHeightCylinderScale;
        cylinder.m_direction2.z = kPppYmCheckBGHeightCylinderOffset;
        cylinder.m_radius2 = kPppYmCheckBGHeightCylinderOffset;
        cylinder.m_height2 = kPppYmCheckBGHeightCylinderOffset;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(
                &MapMng, (CMapCylinder*)&cylinder, &direction, (unsigned long)-1) != 0) {
            CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A78), &hitPos);
            if ((float)(y - (double)param_2->m_unk0xC) <= hitPos.y) {
                y = hitPos.y + param_2->m_unk0x8;
            }
        }

        pppMngSt->m_position.y = (float)y;
        pppMngSt->m_savedPosition.y = (float)y;
        pppMngSt->m_paramVec0.y = (float)y;
        pppMngSt->m_previousPosition.y = (float)y;

        pppMngStPtr->m_matrix.value[0][3] = pppMngSt->m_position.x;
        pppMngStPtr->m_matrix.value[1][3] = pppMngSt->m_position.y;
        pppMngStPtr->m_matrix.value[2][3] = pppMngSt->m_position.z;

        pppYmCheckBGHeight = (struct pppYmCheckBGHeight*)pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }

    return pppYmCheckBGHeight;
}
