#include "ffcc/pppMiasma.h"
#include "ffcc/graphic.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"

#include <string.h>

extern int lbl_8032ED70;
extern float FLOAT_80331928;
extern float FLOAT_8033192c;
extern float FLOAT_80331930;
extern float FLOAT_80331934;
extern float FLOAT_80331938;

extern struct {
    float _224_4_, _228_4_, _232_4_;
} CameraPcs;

extern "C" {
void GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh*, CMaterialSet*, int&);
}

struct PppMiasmaRenderStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_payload[0x20];
};

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
void pppRenderMiasma(pppMiasma* pppMiasma, void* param_2, pppMiasmaCtrl* param_3)
{
    PppMiasmaRenderStep* step;
    pppModelSt* model;
    s16* work;
    Vec managerPos;
    Vec cameraPos;
    float radius;
    float maxRadius;
    float radiusScale;
    int colorOffset;
    int textureIndex;
    u16 i;
    bool inFarZone;

    Graphic.SetDrawDoneDebugData(0x31);

    step = (PppMiasmaRenderStep*)param_2;
    work = (s16*)((u8*)pppMiasma + 0x80 + param_3->m_serializedDataOffsets[2]);
    colorOffset = param_3->m_serializedDataOffsets[1];
    radiusScale = *(float*)((u8*)pppMiasma + 0x80 + param_3->m_serializedDataOffsets[3]);

    textureIndex = 0;
    model = (pppModelSt*)(((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[step->m_dataValIndex]);
    GetTexture__8CMapMeshFP12CMaterialSetRi((CMapMesh*)model, pppEnvStPtr->m_materialSetPtr, textureIndex);

    if (step->m_payload[0x1e] == 0xFF) {
        step->m_payload[0x1e] = 0xFE;
    }

    managerPos.x = pppMngStPtr->m_matrix.value[0][3];
    managerPos.y = pppMngStPtr->m_matrix.value[1][3];
    managerPos.z = pppMngStPtr->m_matrix.value[2][3];

    if (Game.game.m_currentSceneId == 7) {
        float* radiusArray;
        u16 meshCount;

        cameraPos.x = ppvCameraMatrix0[0][3];
        cameraPos.y = ppvCameraMatrix0[1][3];
        cameraPos.z = ppvCameraMatrix0[2][3];
        maxRadius = FLOAT_80331930;

        meshCount = *(u16*)((u8*)&model->m_mapMesh + 0x0);
        radiusArray = *(float**)((u8*)&model->m_mapMesh + 0x2c);
        for (i = 0; i < meshCount; i++) {
            radius = radiusArray[i * 3];
            if (maxRadius < radius) {
                maxRadius = radius;
            }
        }
    } else {
        cameraPos.x = CameraPcs._224_4_;
        cameraPos.y = CameraPcs._228_4_;
        cameraPos.z = CameraPcs._232_4_;
        maxRadius = FLOAT_80331934;
    }

    maxRadius = maxRadius * radiusScale;
    inFarZone = (FLOAT_80331938 + maxRadius) <= PSVECDistance(&cameraPos, &managerPos);

    (void)colorOffset;
    (void)work;
    (void)inFarZone;
    (void)step;
    (void)textureIndex;
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

    if (lbl_8032ED70 != 0) {
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
