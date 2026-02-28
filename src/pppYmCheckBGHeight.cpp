#include "ffcc/pppYmCheckBGHeight.h"
#include "ffcc/maphit.h"
#include "ffcc/pppPart.h"

#include <dolphin/types.h>

extern int lbl_8032ED70;
extern struct _pppMngSt* pppMngStPtr;
extern unsigned char MapMng[];

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
    int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(void*, CMapCylinder*, Vec*, unsigned int);
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
        float* cylF = (float*)&cyl;
        Vec hitPos;
        float currentY;
        float resolvedY;
        float baseX;
        float baseZ;
        float bottomY;

        direction.x = lbl_80330ED0;
        direction.y = lbl_80330ED4;
        direction.z = lbl_80330ED0;

        currentY = ((float*)pppMngSt)[0x94 / sizeof(float)];
        resolvedY = currentY;
        baseX = ((float*)pppMngSt)[0x84 / sizeof(float)];
        baseZ = ((float*)pppMngSt)[0xA4 / sizeof(float)];
        bottomY = currentY + param_2->m_unk0x4;

        cylF[12] = lbl_80330ED8;
        cylF[11] = lbl_80330ED8;
        cylF[10] = lbl_80330ED8;
        cylF[15] = lbl_80330EDC;
        cylF[14] = lbl_80330EDC;
        cylF[13] = lbl_80330EDC;
        cylF[6] = lbl_80330ED0;
        cylF[7] = lbl_80330ED4;
        cylF[8] = lbl_80330ED0;
        cylF[9] = lbl_80330ED0;
        cyl.m_bottom.x = baseX;
        cyl.m_bottom.y = bottomY;
        cyl.m_bottom.z = baseZ;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(MapMng, (CMapCylinder*)&cyl, &direction, 0xffffffff) != 0) {
            CalcHitPosition__7CMapObjFP3Vec(*(void**)(MapMng + 0x22A78), &hitPos);
            if (currentY - ((float*)param_2)[3] > hitPos.y) {
                resolvedY = currentY;
            } else {
                resolvedY = hitPos.y + param_2->m_unk0x8;
            }
        }
        currentY = resolvedY;

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
