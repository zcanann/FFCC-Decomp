#include "ffcc/pppYmCheckBGHeight.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/pppPart.h"

#include <dolphin/types.h>

extern int lbl_8032ED70;
extern struct _pppMngSt* pppMngStPtr;

// Float constants (addresses from Ghidra)
extern float lbl_80330ED0;
extern float lbl_80330ED4;
extern float lbl_80330ED8;
extern float lbl_80330EDC;

extern "C" {
    int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, unsigned int);
    void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
    void* pppSetFpMatrix__FP9_pppMngSt(struct _pppMngSt*);
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

    if (lbl_8032ED70 == 0) {
        Vec direction;
        CMapCylinder cyl;
        Vec hitPos;
        double currentY;
        float baseX;
        float baseZ;

        direction.x = lbl_80330ED0;
        direction.y = lbl_80330ED4;
        direction.z = lbl_80330ED0;

        currentY = (double)pppMngSt->m_matrix.value[1][3];
        baseX = pppMngSt->m_matrix.value[0][3];
        baseZ = pppMngSt->m_matrix.value[2][3];

        cyl.m_bottom.x = baseX;
        cyl.m_bottom.y = (float)(currentY + (double)param_2->m_unk0x4);
        cyl.m_bottom.z = baseZ;
        cyl.m_top.x = lbl_80330ED8;
        cyl.m_top.y = lbl_80330ED8;
        cyl.m_top.z = lbl_80330ED8;
        cyl.m_direction2.x = lbl_80330EDC;
        cyl.m_direction2.y = lbl_80330EDC;
        cyl.m_direction2.z = lbl_80330EDC;
        cyl.m_radius = lbl_80330ED0;
        cyl.m_height = lbl_80330ED4;
        cyl.m_direction.x = lbl_80330ED0;
        cyl.m_direction.y = lbl_80330ED4;
        cyl.m_direction.z = lbl_80330ED0;
        cyl.m_radius2 = lbl_80330ED0;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &cyl, &direction, 0xFFFFFFFF) != 0) {
            CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A78), &hitPos);
            if ((float)(currentY - (double)param_2->m_serializedDataOffsets) <= hitPos.y) {
                currentY = (double)(hitPos.y + param_2->m_unk0x8);
            }
        }

        pppMngSt->m_position.y = (float)currentY;
        pppMngSt->m_savedPosition.y = (float)currentY;
        pppMngSt->m_paramVec0.y = (float)currentY;
        pppMngSt->m_previousPosition.y = (float)currentY;

        pppMngStPtr->m_matrix.value[0][3] = pppMngSt->m_position.x;
        pppMngStPtr->m_matrix.value[1][3] = pppMngSt->m_position.y;
        pppMngStPtr->m_matrix.value[2][3] = pppMngSt->m_position.z;

        pppYmCheckBGHeight = (struct pppYmCheckBGHeight*)pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }
    return pppYmCheckBGHeight;
}
