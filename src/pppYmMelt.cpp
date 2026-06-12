#include "ffcc/ptrarray.h"
#include "ffcc/pppYmMelt.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppVec.h"
#include "ffcc/pppShape.h"
#include "ffcc/textureman.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "dolphin/mtx.h"
#include "dolphin/os/OSCache.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>
#pragma exceptions on
extern "C" {
extern const float kPppYmMeltZero = 0.0f;
extern const float kPppYmMeltPhaseOne = 1.0f;
extern const double kPppYmMeltUnsignedToDoubleBias = 4503599627370496.0;
extern const double kPppYmMeltUnsignedToDoubleAdjust = 4503601774854144.0;
extern const float kPppYmMeltHalf = 0.5f;
extern const float kPppYmMeltDegToRad = 0.017453292f;
extern const float kPppYmMeltRayLength = -2000.0f;
extern const float kPppYmMeltCylinderRadius = 10000000000.0f;
extern const float kPppYmMeltCylinderBound = -10000000000.0f;
extern const u32 kPppYmMeltMaskBit0 = 0x00000001;
extern const u32 kPppYmMeltMaskBit4 = 0x00000010;
extern const float kCFlatPadStickZero = 0.0f;
u32 g_ymMelt;
}

STATIC_ASSERT(sizeof(YmMeltVertex) == 0x10);
STATIC_ASSERT(offsetof(YmMeltVertex, m_position) == 0x00);
STATIC_ASSERT(offsetof(YmMeltVertex, m_color) == 0x0C);
STATIC_ASSERT(offsetof(YmMeltWork, m_vertexData) == 0x00);
STATIC_ASSERT(offsetof(YmMeltWork, m_phaseOffset) == 0x04);
STATIC_ASSERT(offsetof(YmMeltWork, m_shapeCurrentFrame) == 0x06);
STATIC_ASSERT(offsetof(YmMeltWork, m_shapeDrawFrame) == 0x08);
STATIC_ASSERT(offsetof(YmMeltWork, m_shapeFrameTime) == 0x0A);
STATIC_ASSERT(offsetof(YmMeltWork, m_phase) == 0x0C);
STATIC_ASSERT(offsetof(YmMeltWork, m_phaseVelocity) == 0x10);
STATIC_ASSERT(offsetof(YmMeltWork, m_phaseAccel) == 0x14);
STATIC_ASSERT(sizeof(YmMeltWork) == 0x18);
STATIC_ASSERT(offsetof(YmMeltColorWork, m_color) == 0x08);
STATIC_ASSERT(sizeof(YmMeltColorWork) == 0x0C);
STATIC_ASSERT(sizeof(Vec2d) == 0x08);
STATIC_ASSERT(offsetof(YmMeltVertexSetup, m_gridSize) == 0x0A);
STATIC_ASSERT(offsetof(YmMeltVertexSetup, m_stepValue) == 0x0C);
STATIC_ASSERT(offsetof(YmMeltVertexSetup, m_heightBias) == 0x20);
STATIC_ASSERT(offsetof(YmMeltVertexSetup, m_collisionYOffset) == 0x24);
STATIC_ASSERT(offsetof(YmMeltVertexSetup, m_maxDropDistance) == 0x28);
STATIC_ASSERT(offsetof(YmMeltVertexSetup, m_hideWhenNoGround) == 0x2E);
STATIC_ASSERT(offsetof(CMapCylinder, m_bottom) == 0x00);
STATIC_ASSERT(offsetof(CMapCylinder, m_axis) == 0x18);
STATIC_ASSERT(offsetof(CMapCylinder, m_radius) == 0x24);
STATIC_ASSERT(offsetof(CMapCylinder, m_bound) == 0x28);
STATIC_ASSERT(sizeof(YmMeltDataOffsets) == 0x8);
STATIC_ASSERT(offsetof(YmMeltDataOffsets, m_workOffset) == 0x0);
STATIC_ASSERT(offsetof(YmMeltDataOffsets, m_colorWorkOffset) == 0x4);

static inline YmMeltDataOffsets* GetYmMeltDataOffsets(PYmMeltDataOffsets* offsets)
{
    return reinterpret_cast<YmMeltDataOffsets*>(offsets->m_serializedDataOffsets);
}

static inline YmMeltWork* GetYmMeltWork(PYmMelt* ymMelt, PYmMeltDataOffsets* offsets)
{
    return reinterpret_cast<YmMeltWork*>(ymMelt->m_workArea + GetYmMeltDataOffsets(offsets)->m_workOffset);
}

static inline YmMeltColorWork* GetYmMeltColorWork(PYmMelt* ymMelt, PYmMeltDataOffsets* offsets)
{
    return reinterpret_cast<YmMeltColorWork*>(ymMelt->m_workArea + GetYmMeltDataOffsets(offsets)->m_colorWorkOffset);
}

static inline float LoadFloat(const float& value)
{
    return value;
}

#define CalcPolygonHeight CalcPolygonHeight__FP7PYmMeltP11VERTEX_DATAP8_GXColorf
extern "C" void CalcPolygonHeight(VERTEX_DATA*, YmMeltVertex*, _GXColor*, float);

#define InitPolygonData InitPolygonData__FP7PYmMeltP11VERTEX_DATAs

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
    YmMeltWork* work;
    YmMeltVertex* vertexData;
    YmMeltColorWork* colorWork;
    pppShapeSt* shape;
    CTexture* texture;
    int textureIndex;
    Vec2d uvMin;
    Vec2d uvMax;
    u16 grid;
    float worldX;
    float worldY;
    float worldZ;
    float uStep;
    float vStep;
    float phaseLerp;
    u32 drawColor;
    u8* drawColorBytes;

    work = GetYmMeltWork(ymMelt, offsets);
    colorWork = GetYmMeltColorWork(ymMelt, offsets);
    if (ctrl->m_dataValIndex == 0xFFFF) {
        return;
    }

    shape = ppvEnv->m_resourceTables.m_shapeTablePtr[ctrl->m_dataValIndex];

    pppSetDrawEnv(&colorWork->m_color, (pppFMATRIX*)&ppvCameraMatrix, LoadFloat(kPppYmMeltZero),
                  ctrl->m_melt.m_drawEnvColor1, ctrl->m_melt.m_drawEnvColor0, ctrl->m_blendMode, 2, 1, 1, 0);
    pppSetBlendMode(ctrl->m_blendMode);

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, (GXAttrType)1);
    GXSetVtxDesc((GXAttr)0xb, (GXAttrType)1);
    GXSetVtxDesc((GXAttr)0xd, (GXAttrType)1);
    GXSetVtxAttrFmt(GX_VTXFMT7, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, (GXAttr)0xb, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, (GXAttr)0xd, (GXCompCnt)1, (GXCompType)4, 0);

    textureIndex = 0;
    texture = (CTexture*)shape->GetTexture((long*)shape->m_animData, ppvEnv->m_materialSetPtr, textureIndex);
    if (texture == nullptr) {
        return;
    }

    GXLoadTexObj(&texture->m_texObj, GX_TEXMAP0);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    if (((u32)texture->m_format == 8) || ((u32)texture->m_format == 9)) {
        SetUpPaletteEnv(texture);
    }

    phaseLerp = LoadFloat(kPppYmMeltPhaseOne) - work->m_phase;
    drawColor = g_ymMelt;
    drawColorBytes = reinterpret_cast<u8*>(&drawColor);
    drawColorBytes[0] = colorWork->m_color.rgba[0];
    drawColorBytes[1] = colorWork->m_color.rgba[1];
    drawColorBytes[2] = colorWork->m_color.rgba[2];
    drawColorBytes[3] = colorWork->m_color.rgba[3];
    vertexData = work->m_vertexData;
    worldX = ppvMng->m_matrix.value[0][3];
    worldY = ppvMng->m_matrix.value[1][3];
    worldZ = ppvMng->m_matrix.value[2][3];
    pppGetShapeUV((long*)shape->m_animData, work->m_shapeDrawFrame, uvMin, uvMax, 0);

    uStep = uvMax.x - uvMin.x;
    vStep = uvMax.y - uvMin.y;
    grid = ctrl->m_gridSize;
    uStep = uStep / (f32)grid;
    vStep = vStep / (f32)grid;
    GXBegin((GXPrimitive)0x80, GX_VTXFMT7, (u16)((grid * grid * 4) & 0xFFFC));

    for (int z = 0; z < ctrl->m_gridSize; z++) {
        float v1 = (f32)(z + 1) * vStep;
        float v0 = (f32)z * vStep;
        for (int x = 0; x < ctrl->m_gridSize; x++) {
            int gridWork = ctrl->m_gridSize;
            int idx0 = x + z * (gridWork + 1);
            int idx1 = x + (z + 1) * (gridWork + 1);
            YmMeltVertex* p0Data = &vertexData[idx1];
            Vec vtx0;
            u32 colorValue;

            pppCopyVector(vtx0, p0Data->m_position);
            YmMeltVertex* p1Data = &vertexData[idx0];
            Vec vtx1;
            pppCopyVector(vtx1, p1Data->m_position);
            YmMeltVertex* p3Data = &vertexData[idx1 + 1];
            Vec vtx3;
            pppCopyVector(vtx3, p3Data->m_position);
            YmMeltVertex* p2Data = &vertexData[idx0 + 1];
            Vec vtx2;
            pppCopyVector(vtx2, p2Data->m_position);

            vtx0.y += worldY;
            vtx1.y += worldY;
            vtx3.y += worldY;
            vtx2.y += worldY;

            if (kPppYmMeltPhaseOne != work->m_phase) {
                vtx0.x += (worldX - vtx0.x) * phaseLerp;
                vtx0.z += (worldZ - vtx0.z) * phaseLerp;
                vtx1.x += (worldX - vtx1.x) * phaseLerp;
                vtx1.z += (worldZ - vtx1.z) * phaseLerp;
                vtx3.x += (worldX - vtx3.x) * phaseLerp;
                vtx3.z += (worldZ - vtx3.z) * phaseLerp;
                vtx2.x += (worldX - vtx2.x) * phaseLerp;
                vtx2.z += (worldZ - vtx2.z) * phaseLerp;
            }

            GXPosition3f32(vtx0.x, vtx0.y, vtx0.z);
            if (p0Data->m_color.m_gxColor.a != 0) {
                colorValue = drawColor;
            } else {
                colorValue = p0Data->m_color.m_rawColor;
            }
            GXColor1u32(colorValue);
            GXTexCoord2f32(uvMin.x + (f32)x * uStep, uvMin.y + v1);

            GXPosition3f32(vtx1.x, vtx1.y, vtx1.z);
            if (p1Data->m_color.m_gxColor.a != 0) {
                colorValue = drawColor;
            } else {
                colorValue = p1Data->m_color.m_rawColor;
            }
            GXColor1u32(colorValue);
            GXTexCoord2f32(uvMin.x + (f32)x * uStep, uvMin.y + v0);

            GXPosition3f32(vtx2.x, vtx2.y, vtx2.z);
            if (p2Data->m_color.m_gxColor.a != 0) {
                colorValue = drawColor;
            } else {
                colorValue = p2Data->m_color.m_rawColor;
            }
            GXColor1u32(colorValue);
            GXTexCoord2f32(uvMin.x + (f32)(x + 1) * uStep, uvMin.y + v0);

            GXPosition3f32(vtx3.x, vtx3.y, vtx3.z);
            if (p3Data->m_color.m_gxColor.a != 0) {
                colorValue = drawColor;
            } else {
                colorValue = p3Data->m_color.m_rawColor;
            }
            GXColor1u32(colorValue);
            GXTexCoord2f32(uvMin.x + (f32)(x + 1) * uStep, uvMin.y + v1);
        }
    }

    if (((u32)texture->m_format == 8) || ((u32)texture->m_format == 9)) {
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
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
static const char s_pppYmMelt_cpp[] = "pppYmMelt.cpp";

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 372b
 * EN Address: 0x800BA0FC
 * EN Size: 364b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void InitPolygonData(VERTEX_DATA* ctrl, YmMeltVertex* vertexData, s16 phaseOffset)
{
    YmMeltVertex* rowVertex;
    YmMeltVertex* vertex;
    float step;
    float halfWidth;
    float x;
    float rot;
    float z;
    Mtx rotMtx;

    halfWidth = ctrl->m_stepValue * LoadFloat(kPppYmMeltHalf);
    step = ctrl->m_stepValue / (f32)ctrl->m_gridSize;
    rot = kPppYmMeltDegToRad * (f32)phaseOffset;
    vertex = vertexData;

    for (z = -halfWidth; z <= halfWidth; z += step) {
        rowVertex = vertex;
        for (x = -halfWidth; x <= halfWidth; x += step) {
            rowVertex->m_position.x = x;
            rowVertex->m_position.y = kPppYmMeltZero;
            rowVertex->m_position.z = z;

            if (phaseOffset != 0) {
                PSMTXRotRad(rotMtx, 'y', rot);
                PSMTXMultVec(rotMtx, &rowVertex->m_position, &rowVertex->m_position);
            }

            rowVertex++;
            vertex++;
        }
    }
}

void pppFrameYmMelt(PYmMelt* ymMelt, YmMeltCtrl* ctrl, PYmMeltDataOffsets* offsets)
{
    s16 phaseWork;
    int gridCount;
    int vertexCount;
    int angleSeed;
    YmMeltWork* work;
    YmMeltColorWork* colorWork;
    YmMeltVertex* vertexBase;
    float matrixY;

    if (ppvUserStopPartF != 0) {
        return;
    }

    work = GetYmMeltWork(ymMelt, offsets);
    colorWork = GetYmMeltColorWork(ymMelt, offsets);
    gridCount = ctrl->m_gridSize + 1;
    vertexCount = gridCount * gridCount;
    matrixY = ppvMng->m_matrix.value[1][3];

    if (work->m_vertexData == nullptr) {
        work->m_vertexData = (YmMeltVertex*)pppMemAlloc(
            (unsigned long)vertexCount * sizeof(YmMeltVertex), ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppYmMelt_cpp),
            0xA9);

        vertexBase = work->m_vertexData;
        angleSeed = rand();
        phaseWork = ctrl->m_phasePeriod;
        int phaseQuotient = angleSeed / phaseWork;
        work->m_phaseOffset = angleSeed - phaseQuotient * phaseWork;
        phaseWork = work->m_phaseOffset;
        InitPolygonData((VERTEX_DATA*)ctrl, vertexBase, phaseWork);

        CalcPolygonHeight((VERTEX_DATA*)ctrl, vertexBase, (_GXColor*)&colorWork->m_color, matrixY);
    }

    work->m_phaseVelocity = work->m_phaseVelocity + work->m_phaseAccel;
    work->m_phase = work->m_phase + work->m_phaseVelocity;

    if (ctrl->m_graphId == ymMelt->m_graphId) {
        work->m_phase += ctrl->m_melt.m_phaseDelta;
        work->m_phaseVelocity += ctrl->m_melt.m_phaseVelocityDelta;
        work->m_phaseAccel += ctrl->m_melt.m_phaseAccelDelta;
    }

    if (ctrl->m_dataValIndex != 0xFFFF) {
        long* animData = static_cast<long*>(ppvEnv->m_resourceTables.m_shapeTablePtr[ctrl->m_dataValIndex]->m_animData);
        pppCalcFrameShape(animData, work->m_shapeCurrentFrame, work->m_shapeDrawFrame,
                                      work->m_shapeFrameTime, ctrl->m_shapeFrameStep);
    }
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
void pppDestructYmMelt(PYmMelt* ymMelt, PYmMeltDataOffsets* offsets)
{
    YmMeltWork* work = GetYmMeltWork(ymMelt, offsets);

    if (work->m_vertexData != nullptr) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(work->m_vertexData));
    }
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
void pppConstructYmMelt(PYmMelt* ymMelt, PYmMeltDataOffsets* offsets)
{
    f32 value = kPppYmMeltZero;
    YmMeltWork* work = GetYmMeltWork(ymMelt, offsets);

    work->m_vertexData = 0;
    work->m_phaseOffset = 0;
    work->m_shapeFrameTime = 0;
    work->m_shapeDrawFrame = 0;
    work->m_shapeCurrentFrame = 0;

    work->m_phaseAccel = value;
    work->m_phaseVelocity = value;
    work->m_phase = value;
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
extern "C" void CalcPolygonHeight(
    VERTEX_DATA* vertexData, YmMeltVertex* vertexBuffer, _GXColor* color, float yOffset)
{
    int i;
    int pointCount;
    float zero;
    float previousY;
    Vec rayDirection;
    Vec worldBase;
    YmMeltVertex* vertex;
    u8* colorBytes = (u8*)color;

    pointCount = vertexData->m_gridSize + 1;
    pointCount *= pointCount;
    previousY = ppvMng->m_previousPosition.x;
    zero = LoadFloat(kPppYmMeltZero);
    for (i = 0; i < pointCount; i++) {
        vertex = &vertexBuffer[i];

        vertex->m_color.m_bytes[0] = colorBytes[0];
        vertex->m_color.m_bytes[1] = colorBytes[1];
        vertex->m_color.m_bytes[2] = colorBytes[2];
        vertex->m_color.m_bytes[3] = colorBytes[3];

        worldBase.x = ppvMng->m_matrix.value[0][3];
        worldBase.y = ppvMng->m_matrix.value[1][3];
        worldBase.z = ppvMng->m_matrix.value[2][3];
        worldBase.y += vertexData->m_collisionYOffset;
        rayDirection.x = zero;
        rayDirection.y = LoadFloat(kPppYmMeltRayLength);
        rayDirection.z = zero;
        pppAddVector(vertex->m_position, vertex->m_position, worldBase);

        CMapCylinder cylinder(LoadFloat(kPppYmMeltCylinderRadius), kPppYmMeltCylinderBound);
        cylinder.m_bottom = vertex->m_position;
        cylinder.m_axis.x = rayDirection.x;
        cylinder.m_axis.y = rayDirection.y;
        cylinder.m_axis.z = rayDirection.z;
        cylinder.m_radius = zero;

        if (MapMng.CheckHitCylinderNear(&cylinder, &rayDirection, 0xFFFFFFFF) != 0) {
            MapMng.m_hitMapObj->CalcHitPosition(&vertex->m_position);
            if ((previousY - vertexData->m_maxDropDistance) > vertex->m_position.y) {
                vertex->m_position.y = previousY;
                if (vertexData->m_hideWhenNoGround != 0) {
                    vertex->m_color.m_bytes[0] = 0;
                    vertex->m_color.m_bytes[1] = 0;
                    vertex->m_color.m_bytes[2] = 0;
                    vertex->m_color.m_bytes[3] = 0;
                }
            }
        } else {
            vertex->m_position.y = previousY;
            if (vertexData->m_hideWhenNoGround != 0) {
                vertex->m_color.m_bytes[0] = 0;
                vertex->m_color.m_bytes[1] = 0;
                vertex->m_color.m_bytes[2] = 0;
                vertex->m_color.m_bytes[3] = 0;
            }
        }

        vertex->m_position.y = vertex->m_position.y + vertexData->m_heightBias;
        vertex->m_position.y = vertex->m_position.y - yOffset;
    }

    DCFlushRange(vertexBuffer, pointCount * 0x10);
}
