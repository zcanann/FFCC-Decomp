#include "ffcc/pppMiasma.h"

#include <string.h>

extern int DAT_8032ed70;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalcSphereRadius(Vec*, unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CreateScaleMatrix(_pppPObject*, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80109b6c
 * PAL Size: 5604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderMiasma(pppMiasma*, void*, pppMiasmaCtrl*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80109b08
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructMiasma(pppMiasma* pppMiasma, pppMiasmaCtrl* param_2)
{
    u8* work;

    work = (u8*)pppMiasma + 0x80 + param_2->m_serializedDataOffsets[2];
    memset(work, 0, 8);
    memset(work + 8, 0, 8);
    memset(work + 0x10, 0, 8);
}

/*
 * --INFO--
 * PAL Address: 0x80109aa4
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2Miasma(pppMiasma* pppMiasma, pppMiasmaCtrl* param_2)
{
    u8* work;

    work = (u8*)pppMiasma + 0x80 + param_2->m_serializedDataOffsets[2];
    memset(work, 0, 8);
    memset(work + 8, 0, 8);
    memset(work + 0x10, 0, 8);
}

/*
 * --INFO--
 * PAL Address: 0x80109aa0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructMiasma(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x80109930
 * PAL Size: 368b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameMiasma(pppMiasma* pppMiasma, pppMiasmaFrameStep* param_2, pppMiasmaCtrl* param_3)
{
    s16* work;

    if (DAT_8032ed70 != 0) {
        return;
    }

    work = (s16*)((u8*)pppMiasma + 0x80 + param_3->m_serializedDataOffsets[2]);
    work[4] = work[4] + work[8];
    work[0] = work[0] + work[4];
    work[5] = work[5] + work[9];
    work[1] = work[1] + work[5];
    work[6] = work[6] + work[10];
    work[2] = work[2] + work[6];
    work[7] = work[7] + work[11];
    work[3] = work[3] + work[7];

    if (pppMiasma->m_graphId != param_2->m_graphId) {
        return;
    }

    work[0] = work[0] + param_2->m_addPosX;
    work[1] = work[1] + param_2->m_addPosY;
    work[2] = work[2] + param_2->m_addPosZ;
    work[3] = work[3] + param_2->m_addPosW;
    work[4] = work[4] + param_2->m_addVelX;
    work[5] = work[5] + param_2->m_addVelY;
    work[6] = work[6] + param_2->m_addVelZ;
    work[7] = work[7] + param_2->m_addVelW;
    work[8] = work[8] + param_2->m_addAccX;
    work[9] = work[9] + param_2->m_addAccY;
    work[10] = work[10] + param_2->m_addAccZ;
    work[11] = work[11] + param_2->m_addAccW;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}
