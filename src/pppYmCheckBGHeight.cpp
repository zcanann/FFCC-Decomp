#include "ffcc/pppYmCheckBGHeight.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/pppPart.h"

#include <dolphin/types.h>

extern int DAT_8032ed70;
extern struct _pppMngSt* pppMngStPtr;
extern struct CMapMng MapMng;

// Float constants (addresses from Ghidra)
extern float FLOAT_80330ed0;
extern float FLOAT_80330ed4; 
extern float FLOAT_80330ed8;
extern float FLOAT_80330edc;

extern "C" {
    int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(struct CMapMng*, CMapCylinder*, Vec*, unsigned int);
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
void pppConstructYmCheckBGHeight(void)
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
struct pppYmCheckBGHeight* pppFrameYmCheckBGHeight(struct pppYmCheckBGHeight* pppYmCheckBGHeight, struct UnkC* param_2)
{
    struct _pppMngSt* pppMngSt;
    CMapCylinder cyl;
    Vec hitPos;
    double posY;

    pppMngSt = pppMngStPtr;
    if (DAT_8032ed70 == 0) {
        cyl.m_direction.x = FLOAT_80330ed0;
        cyl.m_direction.y = FLOAT_80330ed4;
        cyl.m_direction.z = FLOAT_80330ed0;

        posY = (double)pppMngStPtr->m_matrix.value[1][3];
        cyl.m_bottom.x = pppMngStPtr->m_matrix.value[0][3];
        cyl.m_bottom.z = pppMngStPtr->m_matrix.value[2][3];
        cyl.m_bottom.y = (float)(posY + (double)(float)param_2->m_unk0x4);

        cyl.m_direction2.x = FLOAT_80330ed8;
        cyl.m_direction2.y = FLOAT_80330ed8;
        cyl.m_direction2.z = FLOAT_80330ed8;

        cyl.m_radius2 = FLOAT_80330edc;
        cyl.m_height2 = FLOAT_80330edc;
        cyl.m_radius = FLOAT_80330edc;

        cyl.m_top.x = FLOAT_80330ed0;
        cyl.m_top.y = FLOAT_80330ed4;
        cyl.m_top.z = FLOAT_80330ed0;
        cyl.m_height = FLOAT_80330ed0;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &cyl, &cyl.m_direction, 0xffffffff) != 0) {
            CalcHitPosition__7CMapObjFP3Vec(*(void**)((char*)&MapMng + 0x22A88), &hitPos);
            if ((float)(posY - (double)(float)param_2->m_serializedDataOffsets) <= hitPos.y) {
                posY = (double)(hitPos.y + (float)param_2->m_unk0x8);
            }
        }

        pppMngSt->m_position.y = (float)posY;
        *((float*)pppMngSt + 0x17) = (float)posY; // m_savedPosition.y
        *((float*)pppMngSt + 0x1B) = (float)posY; // m_paramVec0.y
        *((float*)pppMngSt + 0x13) = (float)posY; // m_previousPosition.y

        pppMngStPtr->m_matrix.value[0][3] = pppMngSt->m_position.x;
        pppMngStPtr->m_matrix.value[1][3] = pppMngSt->m_position.y;
        pppMngStPtr->m_matrix.value[2][3] = pppMngSt->m_position.z;

        pppYmCheckBGHeight = (struct pppYmCheckBGHeight*)pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }

    return pppYmCheckBGHeight;
}
