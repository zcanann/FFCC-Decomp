#include "ffcc/pppYmMelt.h"
#include "ffcc/pppPart.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "dolphin/mtx.h"

extern int DAT_8032ed70;
extern float lbl_80330AF0;
extern float FLOAT_80330af0;
extern float FLOAT_80330b08;
extern float FLOAT_80330b0c;
extern double DOUBLE_80330af8;
extern double DOUBLE_80330b00;
extern float FLOAT_80330b10;
extern float FLOAT_80330b14;
extern float FLOAT_80330b18;
extern CMapMng MapMng;

extern "C" {
int rand(void);
int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, unsigned int);
void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
void DCFlushRange(void*, unsigned long);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void pppCalcFrameShape__FPlRsRsRss(long*, short&, short&, short&, short);
}

struct YmMeltVertex
{
    Vec m_position;
    u8 m_color[4];
};

struct YmMeltWork {
    YmMeltVertex* m_vertexData;
    s16 m_shapeFrame;
    s16 m_shapeAge;
    s16 m_shapeNext;
    s16 m_phaseOffset;
    f32 m_phase;
    f32 m_phaseVelocity;
    f32 m_phaseAccel;
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void InitPolygonData(PYmMelt*, VERTEX_DATA*, short)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800A5D5C
 * PAL Size: 624b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CalcPolygonHeight(PYmMelt*, VERTEX_DATA* param_2, _GXColor* param_3, float param_4)
{
    s32 i;
    s32 pointCount;
    float savedY;
    Vec worldBase;
    CMapCylinder cylinder;
    Vec hitPosition;
    YmMeltVertex* vertex;

    pointCount = param_2->m_gridSize + 1;
    pointCount *= pointCount;
    savedY = ((Vec*)((u8*)pppMngStPtr + 0x58))->y;

    worldBase.x = pppMngStPtr->m_matrix.value[0][3];
    worldBase.y = pppMngStPtr->m_matrix.value[1][3] + param_2->m_collisionYOffset;
    worldBase.z = pppMngStPtr->m_matrix.value[2][3];

    for (i = 0; i < pointCount; i++) {
        vertex = (YmMeltVertex*)param_3 + i;
        vertex->m_color[0] = param_3->r;
        vertex->m_color[1] = param_3->g;
        vertex->m_color[2] = param_3->b;
        vertex->m_color[3] = param_3->a;

        pppAddVector(vertex->m_position, vertex->m_position, worldBase);

        cylinder.m_bottom = vertex->m_position;
        cylinder.m_direction.x = 0.0f;
        cylinder.m_direction.y = FLOAT_80330b10;
        cylinder.m_direction.z = 0.0f;
        cylinder.m_radius = 0.0f;
        cylinder.m_height = 0.0f;
        cylinder.m_top.x = FLOAT_80330b14;
        cylinder.m_top.y = FLOAT_80330b14;
        cylinder.m_top.z = FLOAT_80330b14;
        cylinder.m_direction2.x = FLOAT_80330b18;
        cylinder.m_direction2.y = FLOAT_80330b18;
        cylinder.m_direction2.z = FLOAT_80330b18;
        cylinder.m_radius2 = FLOAT_80330b18;
        cylinder.m_height2 = FLOAT_80330b18;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &cylinder, &cylinder.m_direction,
                                                                   0xFFFFFFFF) == 0) {
            vertex->m_position.y = savedY;
            if (param_2->m_hideWhenNoGround != 0) {
                vertex->m_color[0] = 0;
                vertex->m_color[1] = 0;
                vertex->m_color[2] = 0;
                vertex->m_color[3] = 0;
            }
        } else {
            CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A88), &vertex->m_position);
            if (vertex->m_position.y < savedY - param_2->m_maxDropDistance) {
                vertex->m_position.y = savedY;
                if (param_2->m_hideWhenNoGround != 0) {
                    vertex->m_color[0] = 0;
                    vertex->m_color[1] = 0;
                    vertex->m_color[2] = 0;
                    vertex->m_color[3] = 0;
                }
            }
        }

        vertex->m_position.y += param_2->m_heightBias;
        vertex->m_position.y -= param_4;
    }

    DCFlushRange(param_3, pointCount * 0x10);
}

/*
 * --INFO--
 * PAL Address: 0x800A5D20
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMelt(PYmMelt* pppYmMelt, PYmMeltDataOffsets* param_2)
{
    f32 value = lbl_80330AF0;
    u8* work = (u8*)pppYmMelt + *param_2->m_serializedDataOffsets + 0x80;

    *(u32*)(work + 0x0) = 0;
    *(u16*)(work + 0x4) = 0;
    *(u16*)(work + 0xA) = 0;
    *(u16*)(work + 0x8) = 0;
    *(u16*)(work + 0x6) = 0;

    *(f32*)(work + 0x14) = value;
    *(f32*)(work + 0x10) = value;
    *(f32*)(work + 0xC) = value;
}

/*
 * --INFO--
 * PAL Address: 0x800A5CE8
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMelt(PYmMelt* pppYmMelt, PYmMeltDataOffsets* param_2)
{
    CMemory::CStage* stage =
        *(CMemory::CStage**)((u8*)pppYmMelt + *param_2->m_serializedDataOffsets + 0x80);
    if (stage != nullptr) {
        pppHeapUseRate(stage);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800A5A40
 * PAL Size: 680b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmMelt(PYmMelt* ymMelt, YmMeltCtrl* ctrl, PYmMeltDataOffsets* offsets)
{
    static char s_pppYmMelt_cpp[] = "pppYmMelt.cpp";

    if (DAT_8032ed70 != 0) {
        return;
    }

    YmMeltWork* work = (YmMeltWork*)((u8*)ymMelt + *offsets->m_serializedDataOffsets + 0x80);
    int grid = (int)((u16)((u8*)&ctrl->m_initWOrk)[2]) + 1;
    float matrixY = pppMngStPtr->m_matrix.value[1][3];

    if (work->m_vertexData == nullptr) {
        int pointCount = grid * grid;
        work->m_vertexData = (YmMeltVertex*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (unsigned long)pointCount * sizeof(YmMeltVertex), pppEnvStPtr->m_stagePtr, s_pppYmMelt_cpp, 0xA9);

        YmMeltVertex* vtx = work->m_vertexData;
        s16 phaseDiv = *(s16*)((u8*)&ctrl->m_arg3 + 2);
        int angleSeed = rand();
        work->m_phaseOffset = (phaseDiv != 0) ? (s16)(angleSeed - (angleSeed / phaseDiv) * phaseDiv) : 0;

        float halfWidth = ctrl->m_stepValue * FLOAT_80330b08;
        float step = ctrl->m_stepValue / ((float)((u16)((u8*)&ctrl->m_initWOrk)[2]) - (float)DOUBLE_80330af8);
        float rot = FLOAT_80330b0c * ((float)(work->m_phaseOffset) - (float)DOUBLE_80330b00);

        for (float z = -halfWidth; z <= halfWidth; z += step) {
            for (float x = -halfWidth; x <= halfWidth; x += step) {
                vtx->m_position.x = x;
                vtx->m_position.y = FLOAT_80330af0;
                vtx->m_position.z = z;

                if (work->m_phaseOffset != 0) {
                    Mtx rotMtx;
                    PSMTXRotRad(rotMtx, 'y', rot);
                    PSMTXMultVec(rotMtx, &vtx->m_position, &vtx->m_position);
                }

                vtx++;
            }
        }

        CalcPolygonHeight(ymMelt, (VERTEX_DATA*)ctrl, (_GXColor*)work->m_vertexData, matrixY);
    }

    work->m_phaseVelocity = work->m_phaseVelocity + work->m_phaseAccel;
    work->m_phase = work->m_phase + work->m_phaseVelocity;

    if (ctrl->m_graphId == *(s32*)ymMelt) {
        work->m_phase += *(float*)&ctrl->m_payload[0];
        work->m_phaseVelocity += *(float*)&ctrl->m_payload[4];
        work->m_phaseAccel += *(float*)&ctrl->m_payload[8];
    }

    if (ctrl->m_dataValIndex != 0xFFFF) {
        long* shape = *(long**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + ctrl->m_dataValIndex * 4);
        pppCalcFrameShape__FPlRsRsRss(shape, work->m_shapeFrame, work->m_shapeAge, work->m_shapeNext,
                                      (s16)ctrl->m_initWOrk);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderYmMelt(void)
{
	// TODO
}
