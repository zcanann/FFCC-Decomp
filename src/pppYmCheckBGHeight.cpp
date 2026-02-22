#include "ffcc/pppYmCheckBGHeight.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/pppPart.h"

#include <dolphin/types.h>

extern int lbl_8032ED70;
extern struct _pppMngSt* pppMngStPtr;
extern struct CMapMng MapMng;

// Float constants (addresses from Ghidra)
extern float lbl_80330ED0;
extern float lbl_80330ED4;
extern float lbl_80330ED8;
extern float lbl_80330EDC;

struct CMapCylinderRaw
{
    Vec m_bottom;
    Vec m_direction;
    float m_radius;
    float m_height;
    Vec m_top;
    Vec m_direction2;
    float m_radius2;
    float m_height2;
};

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
    if (lbl_8032ED70 == 0) {
        _pppMngSt* pppMngSt = pppMngStPtr;
        Vec direction;
        CMapCylinderRaw cyl;
        Vec hitPos;
        float currentY;

        direction.x = lbl_80330ED0;
        direction.y = lbl_80330ED4;
        direction.z = lbl_80330ED0;

        currentY = ((float*)pppMngSt)[0x94 / sizeof(float)];
        cyl.m_bottom.x = ((float*)pppMngSt)[0x84 / sizeof(float)];
        cyl.m_bottom.z = ((float*)pppMngSt)[0xA4 / sizeof(float)];
        cyl.m_bottom.y = currentY + param_2->m_unk0x4;

        cyl.m_direction2.x = lbl_80330ED8;
        cyl.m_direction2.y = lbl_80330ED8;
        cyl.m_direction2.z = lbl_80330ED8;
        cyl.m_radius2 = lbl_80330EDC;
        cyl.m_height2 = lbl_80330EDC;
        cyl.m_radius = lbl_80330EDC;

        cyl.m_top.x = lbl_80330ED0;
        cyl.m_top.y = lbl_80330ED4;
        cyl.m_top.z = lbl_80330ED0;
        cyl.m_height = lbl_80330ED0;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, (CMapCylinder*)&cyl, &direction, 0xffffffff) != 0) {
            CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A78), &hitPos);
            if (!(currentY - ((float*)param_2)[3] > hitPos.y)) {
                currentY = hitPos.y + param_2->m_unk0x8;
            }
        }

        ((float*)pppMngSt)[0x0C / sizeof(float)] = currentY;
        ((float*)pppMngSt)[0x5C / sizeof(float)] = currentY;
        ((float*)pppMngSt)[0x6C / sizeof(float)] = currentY;
        ((float*)pppMngSt)[0x4C / sizeof(float)] = currentY;

        ((float*)pppMngStPtr)[0x84 / sizeof(float)] = ((float*)pppMngSt)[0x08 / sizeof(float)];
        ((float*)pppMngStPtr)[0x94 / sizeof(float)] = ((float*)pppMngSt)[0x0C / sizeof(float)];
        ((float*)pppMngStPtr)[0xA4 / sizeof(float)] = ((float*)pppMngSt)[0x10 / sizeof(float)];

        pppYmCheckBGHeight = (struct pppYmCheckBGHeight*)pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }
    return pppYmCheckBGHeight;
}
