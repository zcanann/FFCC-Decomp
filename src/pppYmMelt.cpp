#include "ffcc/pppYmMelt.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "dolphin/mtx.h"

extern int DAT_8032ed70;
extern float lbl_80330AF0;
extern float FLOAT_80330af0;
extern float FLOAT_80330af4;
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
void pppSetBlendMode__FUc(unsigned char);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
    unsigned char);
void* GetTexture__10pppShapeStFPlP12CMaterialSetRi(pppShapeSt*, long*, CMaterialSet*, int&);
void pppGetShapeUV__FPlsR5Vec2dR5Vec2di(long*, short, Vec2d&, Vec2d&, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
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

struct Vec2d {
    f32 x;
    f32 y;
};

static u32 floatBits(f32 value)
{
    union {
        f32 f;
        u32 u;
    } cast;

    cast.f = value;
    return cast.u;
}

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
    int i;
    int pointCount;
    double savedY;
    double zero;
    double rayY;
    double top;
    double expand;
    Vec worldBase;
    CMapCylinderRaw cylinder;
    YmMeltVertex* vertex;

    pointCount = param_2->m_gridSize + 1;
    pointCount *= pointCount;
    savedY = ((Vec*)((u8*)pppMngStPtr + 0x58))->y;
    zero = FLOAT_80330af0;
    rayY = FLOAT_80330b10;
    top = FLOAT_80330b14;
    expand = FLOAT_80330b18;
    vertex = (YmMeltVertex*)param_3;

    for (i = 0; i < pointCount; i++, vertex++) {
        vertex->m_color[0] = param_3->r;
        vertex->m_color[1] = param_3->g;
        vertex->m_color[2] = param_3->b;
        vertex->m_color[3] = param_3->a;

        worldBase.x = pppMngStPtr->m_matrix.value[0][3];
        worldBase.y = pppMngStPtr->m_matrix.value[1][3] + param_2->m_collisionYOffset;
        worldBase.z = pppMngStPtr->m_matrix.value[2][3];
        pppAddVector(vertex->m_position, vertex->m_position, worldBase);

        cylinder.m_bottom = vertex->m_position;
        cylinder.m_direction.x = (float)zero;
        cylinder.m_direction.y = (float)rayY;
        cylinder.m_direction.z = (float)zero;
        cylinder.m_radius = (float)zero;
        cylinder.m_height = (float)zero;
        cylinder.m_top.x = (float)top;
        cylinder.m_top.y = (float)top;
        cylinder.m_top.z = (float)top;
        cylinder.m_direction2.x = (float)expand;
        cylinder.m_direction2.y = (float)expand;
        cylinder.m_direction2.z = (float)expand;
        cylinder.m_radius2 = (float)expand;
        cylinder.m_height2 = (float)expand;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, (CMapCylinder*)&cylinder,
                                                                   &cylinder.m_direction, 0xFFFFFFFF) == 0) {
            vertex->m_position.y = (float)savedY;
            if (param_2->m_hideWhenNoGround != 0) {
                vertex->m_color[0] = 0;
                vertex->m_color[1] = 0;
                vertex->m_color[2] = 0;
                vertex->m_color[3] = 0;
            }
        } else {
            CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A88), &vertex->m_position);
            if (((float)vertex->m_position.y < (float)(savedY - (double)param_2->m_maxDropDistance)) &&
                ((vertex->m_position.y = (float)savedY), param_2->m_hideWhenNoGround != 0)) {
                vertex->m_color[0] = 0;
                vertex->m_color[1] = 0;
                vertex->m_color[2] = 0;
                vertex->m_color[3] = 0;
            }
        }

        vertex->m_position.y = (float)((double)(vertex->m_position.y + param_2->m_heightBias) - param_4);
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
        work->m_phaseOffset = (s16)angleSeed - (s16)(angleSeed / (int)phaseDiv) * phaseDiv;

        double halfWidth = (double)(ctrl->m_stepValue * FLOAT_80330b08);
        double step =
            (double)(ctrl->m_stepValue / (float)((double)((u16)((u8*)&ctrl->m_initWOrk)[2]) - DOUBLE_80330af8));
        double rot = (double)(FLOAT_80330b0c * (float)((double)work->m_phaseOffset - DOUBLE_80330b00));
        double z = -halfWidth;
        double x;

        while (z <= halfWidth) {
            x = -halfWidth;
            while (x <= halfWidth) {
                vtx->m_position.x = (float)x;
                vtx->m_position.y = FLOAT_80330af0;
                vtx->m_position.z = (float)z;

                if (phaseDiv != 0) {
                    Mtx rotMtx;
                    PSMTXRotRad(rotMtx, 'y', (float)rot);
                    PSMTXMultVec(rotMtx, &vtx->m_position, &vtx->m_position);
                }

                vtx++;
                x = (double)(float)(x + step);
            }
            z = (double)(float)(z + step);
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
 * PAL Address: 0x800A538C
 * PAL Size: 1716b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmMelt(PYmMelt* ymMelt, YmMeltCtrl* ctrl, PYmMeltDataOffsets* offsets)
{
    s32 colorOffset;
    YmMeltWork* work;
    pppShapeSt* shape;
    CTexture* texture;
    int textureIndex;
    Vec2d uvMin;
    Vec2d uvMax;
    u16 grid;
    float uStep;
    float vStep;
    float phaseLerp;
    float drawColor;
    float worldX;
    float worldY;
    float worldZ;

    colorOffset = offsets->m_serializedDataOffsets[1];
    work = (YmMeltWork*)((u8*)ymMelt + *offsets->m_serializedDataOffsets + 0x80);
    if (ctrl->m_dataValIndex == 0xFFFF || work->m_vertexData == nullptr) {
        return;
    }

    shape = *(pppShapeSt**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + ctrl->m_dataValIndex * 4);
    if (shape == nullptr) {
        return;
    }

    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (u8*)ymMelt + 0x88 + colorOffset, &ppvCameraMatrix0, FLOAT_80330af0, ctrl->m_payload[0x19],
        ctrl->m_payload[0x18], *(u8*)&ctrl->m_arg3, 2, 1, 1, 0);
    pppSetBlendMode__FUc(*(u8*)&ctrl->m_arg3);

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, (GXAttrType)1);
    GXSetVtxDesc((GXAttr)0xb, (GXAttrType)1);
    GXSetVtxDesc((GXAttr)0xd, (GXAttrType)1);
    GXSetVtxAttrFmt(GX_VTXFMT7, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, (GXAttr)0xb, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, (GXAttr)0xd, (GXCompCnt)1, (GXCompType)4, 0);

    textureIndex = 0;
    texture =
        (CTexture*)GetTexture__10pppShapeStFPlP12CMaterialSetRi(shape, (long*)shape->m_animData,
                                                                 pppEnvStPtr->m_materialSetPtr, textureIndex);
    if (texture == nullptr) {
        return;
    }

    GXLoadTexObj((GXTexObj*)((u8*)texture + 0x28), GX_TEXMAP0);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    if ((*(u8*)((u8*)texture + 0x60) == 8) || (*(u8*)((u8*)texture + 0x60) == 9)) {
        SetUpPaletteEnv(texture);
    }

    phaseLerp = FLOAT_80330af4 - work->m_phase;
    drawColor = *(float*)((u8*)ymMelt + 0x88 + colorOffset);
    worldX = pppMngStPtr->m_matrix.value[0][3];
    worldY = pppMngStPtr->m_matrix.value[1][3];
    worldZ = pppMngStPtr->m_matrix.value[2][3];
    pppGetShapeUV__FPlsR5Vec2dR5Vec2di((long*)shape->m_animData, work->m_shapeNext, uvMin, uvMax, 0);

    grid = *(u16*)((u8*)&ctrl->m_initWOrk + 2);
    uStep = (uvMax.x - uvMin.x) / (f32)((double)grid - DOUBLE_80330af8);
    vStep = (uvMax.y - uvMin.y) / (f32)((double)grid - DOUBLE_80330af8);
    GXBegin((GXPrimitive)0x80, GX_VTXFMT7, (u16)((grid * grid * 4) & 0xFFFC));

    for (u32 z = 0; z < grid; z++) {
        float v0 = uvMin.y + (f32)z * vStep;
        float v1 = uvMin.y + (f32)(z + 1) * vStep;
        u32 stride = grid + 1;

        for (u32 x = 0; x < grid; x++) {
            u32 idx0 = x + z * stride;
            u32 idx1 = x + (z + 1) * stride;
            YmMeltVertex* vtx0 = &work->m_vertexData[idx1];
            YmMeltVertex* vtx1 = &work->m_vertexData[idx0];
            YmMeltVertex* vtx2 = &work->m_vertexData[idx0 + 1];
            YmMeltVertex* vtx3 = &work->m_vertexData[idx1 + 1];
            Vec p0 = vtx0->m_position;
            Vec p1 = vtx1->m_position;
            Vec p2 = vtx2->m_position;
            Vec p3 = vtx3->m_position;
            float u0 = uvMin.x + (f32)x * uStep;
            float u1 = uvMin.x + (f32)(x + 1) * uStep;
            float c0 = drawColor;
            float c1 = drawColor;
            float c2 = drawColor;
            float c3 = drawColor;

            p0.y += worldY;
            p1.y += worldY;
            p2.y += worldY;
            p3.y += worldY;

            if (FLOAT_80330af4 != work->m_phase) {
                p0.x = phaseLerp * (worldX - p0.x) + p0.x;
                p0.z = phaseLerp * (worldZ - p0.z) + p0.z;
                p1.x = phaseLerp * (worldX - p1.x) + p1.x;
                p1.z = phaseLerp * (worldZ - p1.z) + p1.z;
                p2.x = phaseLerp * (worldX - p2.x) + p2.x;
                p2.z = phaseLerp * (worldZ - p2.z) + p2.z;
                p3.x = phaseLerp * (worldX - p3.x) + p3.x;
                p3.z = phaseLerp * (worldZ - p3.z) + p3.z;
            }

            if (vtx0->m_color[3] == 0) {
                c0 = *(float*)&vtx0->m_color[0];
            }
            if (vtx1->m_color[3] == 0) {
                c1 = *(float*)&vtx1->m_color[0];
            }
            if (vtx2->m_color[3] == 0) {
                c2 = *(float*)&vtx2->m_color[0];
            }
            if (vtx3->m_color[3] == 0) {
                c3 = *(float*)&vtx3->m_color[0];
            }

            GXPosition3f32(p0.x, p0.y, p0.z);
            GXColor1u32(floatBits(c0));
            GXTexCoord2f32(u0, v1);

            GXPosition3f32(p1.x, p1.y, p1.z);
            GXColor1u32(floatBits(c1));
            GXTexCoord2f32(u0, v0);

            GXPosition3f32(p2.x, p2.y, p2.z);
            GXColor1u32(floatBits(c2));
            GXTexCoord2f32(u1, v0);

            GXPosition3f32(p3.x, p3.y, p3.z);
            GXColor1u32(floatBits(c3));
            GXTexCoord2f32(u1, v1);
        }
    }

    if ((*(u8*)((u8*)texture + 0x60) == 8) || (*(u8*)((u8*)texture + 0x60) == 9)) {
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    }
}
