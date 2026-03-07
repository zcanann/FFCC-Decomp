#include "ffcc/pppYmMelt.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/symbols_shared.h"
#include "dolphin/mtx.h"

extern int gPppCalcDisabled;
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
void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
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
    zero = kPppYmMeltZero;
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

        vertex->m_position.y = vertex->m_position.y + param_2->m_heightBias;
        vertex->m_position.y = (float)((double)vertex->m_position.y - param_4);
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
    f32 value = kPppYmMeltZero;
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

    if (gPppCalcDisabled != 0) {
        return;
    }

    YmMeltWork* work = (YmMeltWork*)((u8*)ymMelt + *offsets->m_serializedDataOffsets + 0x80);
    u16 gridSize = *(u16*)((u8*)&ctrl->m_initWOrk + 2);
    int grid = (int)gridSize + 1;
    float matrixY = pppMngStPtr->m_matrix.value[1][3];

    if (work->m_vertexData == nullptr) {
        work->m_vertexData = (YmMeltVertex*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (unsigned long)(grid * grid) * sizeof(YmMeltVertex), pppEnvStPtr->m_stagePtr, s_pppYmMelt_cpp, 0xA9);

        YmMeltVertex* vtx = work->m_vertexData;
        int angleSeed = rand();
        s16 phaseDiv = *(s16*)((u8*)&ctrl->m_arg3 + 2);
        work->m_phaseOffset = (s16)angleSeed - (s16)(angleSeed / (int)phaseDiv) * phaseDiv;

        double halfWidth = (double)(ctrl->m_stepValue * FLOAT_80330b08);
        double step = (double)(ctrl->m_stepValue / (float)((double)gridSize - DOUBLE_80330af8));
        double rot = (double)(FLOAT_80330b0c * (float)((double)work->m_phaseOffset - DOUBLE_80330b00));
        for (double z = -halfWidth; z <= halfWidth; z = (double)(float)(z + step)) {
            for (double x = -halfWidth; x <= halfWidth; x = (double)(float)(x + step)) {
                vtx->m_position.x = (float)x;
                vtx->m_position.y = kPppYmMeltZero;
                vtx->m_position.z = (float)z;

                if (phaseDiv != 0) {
                    Mtx rotMtx;
                    PSMTXRotRad(rotMtx, 'y', (float)rot);
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
        long** shapeTable = (long**)*(u32*)&pppEnvStPtr->m_particleColors[0];
        pppCalcFrameShape__FPlRsRsRss(shapeTable[ctrl->m_dataValIndex], work->m_shapeFrame, work->m_shapeAge,
                                      work->m_shapeNext, *(s16*)&ctrl->m_initWOrk);
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
    if (ctrl->m_dataValIndex == 0xFFFF) {
        return;
    }

    shape = *(pppShapeSt**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + ctrl->m_dataValIndex * 4);

    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (u8*)ymMelt + 0x88 + colorOffset, &ppvCameraMatrix0, kPppYmMeltZero, ctrl->m_payload[0x19],
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
        u32 x = 0;

        while (x < grid) {
            u32 idx0 = x + z * stride;
            u32 idx1 = x + (z + 1) * stride;
            float* p0Data = (float*)&work->m_vertexData[idx1];
            float* p1Data = (float*)&work->m_vertexData[idx0];
            float* p2Data = (float*)&work->m_vertexData[idx0 + 1];
            float* p3Data = (float*)&work->m_vertexData[idx1 + 1];
            Vec p0;
            Vec p1;
            Vec p2;
            Vec p3;
            Vec vtx0;
            Vec vtx1;
            Vec vtx2;
            Vec vtx3;
            float u0 = uvMin.x + (f32)x * uStep;
            float u1 = uvMin.x + (f32)(x + 1) * uStep;
            float c0 = drawColor;
            float c1 = drawColor;
            float c2 = drawColor;
            float c3 = drawColor;

            p0.x = p0Data[0];
            p0.y = p0Data[1];
            p0.z = p0Data[2];
            pppCopyVector__FR3Vec3Vec(&vtx0, &p0);
            p1.x = p1Data[0];
            p1.y = p1Data[1];
            p1.z = p1Data[2];
            pppCopyVector__FR3Vec3Vec(&vtx1, &p1);
            p2.x = p2Data[0];
            p2.y = p2Data[1];
            p2.z = p2Data[2];
            pppCopyVector__FR3Vec3Vec(&vtx2, &p2);
            p3.x = p3Data[0];
            p3.y = p3Data[1];
            p3.z = p3Data[2];
            pppCopyVector__FR3Vec3Vec(&vtx3, &p3);

            vtx0.y += worldY;
            vtx1.y += worldY;
            vtx2.y += worldY;
            vtx3.y += worldY;

            if (FLOAT_80330af4 != work->m_phase) {
                vtx0.x = phaseLerp * (worldX - vtx0.x) + vtx0.x;
                vtx0.z = phaseLerp * (worldZ - vtx0.z) + vtx0.z;
                vtx1.x = phaseLerp * (worldX - vtx1.x) + vtx1.x;
                vtx1.z = phaseLerp * (worldZ - vtx1.z) + vtx1.z;
                vtx2.x = phaseLerp * (worldX - vtx2.x) + vtx2.x;
                vtx2.z = phaseLerp * (worldZ - vtx2.z) + vtx2.z;
                vtx3.x = phaseLerp * (worldX - vtx3.x) + vtx3.x;
                vtx3.z = phaseLerp * (worldZ - vtx3.z) + vtx3.z;
            }

            if (*(u8*)((u8*)p0Data + 0xF) == 0) {
                c0 = p0Data[3];
            }
            if (*(u8*)((u8*)p1Data + 0xF) == 0) {
                c1 = p1Data[3];
            }
            if (*(u8*)((u8*)p2Data + 0xF) == 0) {
                c2 = p2Data[3];
            }
            if (*(u8*)((u8*)p3Data + 0xF) == 0) {
                c3 = p3Data[3];
            }

            GXPosition3f32(vtx0.x, vtx0.y, vtx0.z);
            GXColor1u32(floatBits(c0));
            GXTexCoord2f32(u0, v1);
            GXPosition3f32(vtx1.x, vtx1.y, vtx1.z);
            GXColor1u32(floatBits(c1));
            GXTexCoord2f32(u0, v0);
            GXPosition3f32(vtx2.x, vtx2.y, vtx2.z);
            GXColor1u32(floatBits(c2));
            GXTexCoord2f32(u1, v0);
            GXPosition3f32(vtx3.x, vtx3.y, vtx3.z);
            GXColor1u32(floatBits(c3));
            GXTexCoord2f32(u1, v1);
            x++;
        }
    }

    if ((*(u8*)((u8*)texture + 0x60) == 8) || (*(u8*)((u8*)texture + 0x60) == 9)) {
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    }
}
