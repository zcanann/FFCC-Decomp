#include "ffcc/pppYmCheckBGHeight.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/pppPart.h"

#include <dolphin/types.h>

extern int gPppCalcDisabled;
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

    if (gPppCalcDisabled == 0) {
        Vec direction;
        float cyl[16];
        Vec hitPos;
        float currentY = pppMngSt->m_matrix.value[1][3];
        float updatedY = currentY;

        direction.x = lbl_80330ED0;
        direction.y = lbl_80330ED4;
        direction.z = lbl_80330ED0;

        cyl[0] = pppMngSt->m_matrix.value[0][3];
        cyl[1] = currentY + param_2->m_unk0x4;
        cyl[2] = pppMngSt->m_matrix.value[2][3];
        cyl[6] = lbl_80330ED0;
        cyl[7] = lbl_80330ED4;
        cyl[8] = lbl_80330ED8;
        cyl[9] = lbl_80330ED8;
        cyl[10] = lbl_80330ED8;
        cyl[11] = lbl_80330EDC;
        cyl[12] = lbl_80330EDC;
        cyl[13] = lbl_80330EDC;
        cyl[14] = lbl_80330ED0;
        cyl[15] = lbl_80330ED0;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, (CMapCylinder*)cyl, &direction, -1) != 0) {
            CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A78), &hitPos);
            if (currentY - param_2->m_unk0x0 <= hitPos.y) {
                updatedY = hitPos.y + param_2->m_unk0x8;
            }
        }

        pppMngSt->m_position.y = updatedY;
        pppMngSt->m_savedPosition.y = updatedY;
        pppMngSt->m_paramVec0.y = updatedY;
        pppMngSt->m_previousPosition.y = updatedY;

        pppMngStPtr->m_matrix.value[0][3] = pppMngSt->m_position.x;
        pppMngStPtr->m_matrix.value[1][3] = pppMngSt->m_position.y;
        pppMngStPtr->m_matrix.value[2][3] = pppMngSt->m_position.z;

        pppYmCheckBGHeight = (struct pppYmCheckBGHeight*)pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }

    return pppYmCheckBGHeight;
}
