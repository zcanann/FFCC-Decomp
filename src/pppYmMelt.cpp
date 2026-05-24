#include "ffcc/pppYmMelt.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/textureman.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "dolphin/mtx.h"
#include "dolphin/os/OSCache.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>
extern "C" {
extern const float kPppYmMeltZero;
u32 g_ymMelt;
extern int gPppCalcDisabled;
}
extern const float FLOAT_80330af4;
extern const float FLOAT_80330b08;
extern const float FLOAT_80330b0c;
extern const float FLOAT_80330b10;
extern const float FLOAT_80330b14;
extern const float FLOAT_80330b18;

struct YmMeltVertex
{
    Vec m_position;
    union {
        _GXColor m_gxColor;
        u32 m_rawColor;
        float m_colorValue;
        u8 m_bytes[4];
    } m_color;
};

struct YmMeltWork {
    YmMeltVertex* m_vertexData;
    s16 m_phaseOffset;
    s16 m_shapeCurrentFrame;
    s16 m_shapeDrawFrame;
    s16 m_shapeFrameTime;
    f32 m_phase;
    f32 m_phaseVelocity;
    f32 m_phaseAccel;
};

struct YmMeltColorWork {
    u8 _pad0[8];
    union {
        pppCVECTOR m_color;
        float m_colorValue;
    };
};

struct Vec2d {
    f32 x;
    f32 y;
};

struct CMapCylinderRaw {
    Vec m_bottom;
    u8 m_pad0C[0xC];
    Vec m_rayDirection;
    f32 m_rayPadding;
    Vec m_topBounds;
    Vec m_expandBounds;
};

static inline YmMeltWork* GetYmMeltWork(PYmMelt* ymMelt, PYmMeltDataOffsets* offsets)
{
    return reinterpret_cast<YmMeltWork*>(reinterpret_cast<u8*>(ymMelt) + *offsets->m_serializedDataOffsets + 0x80);
}

static inline YmMeltColorWork* GetYmMeltColorWork(PYmMelt* ymMelt, PYmMeltDataOffsets* offsets)
{
    return reinterpret_cast<YmMeltColorWork*>(
        reinterpret_cast<u8*>(ymMelt) + offsets->m_serializedDataOffsets[1] + 0x80);
}

#define CalcPolygonHeight CalcPolygonHeight__FP7PYmMeltP11VERTEX_DATAP8_GXColorf
extern "C" void CalcPolygonHeight(VERTEX_DATA*, YmMeltVertex*, _GXColor*, float);

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

    shape = *(pppShapeSt**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + ctrl->m_dataValIndex * 4);

    pppSetDrawEnv(&colorWork->m_color, (pppFMATRIX*)&ppvCameraMatrix, kPppYmMeltZero, ctrl->m_payload[0x19],
                  ctrl->m_payload[0x18], ctrl->m_blendMode, 2, 1, 1, 0);
    pppSetBlendMode(ctrl->m_blendMode);

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, (GXAttrType)1);
    GXSetVtxDesc((GXAttr)0xb, (GXAttrType)1);
    GXSetVtxDesc((GXAttr)0xd, (GXAttrType)1);
    GXSetVtxAttrFmt(GX_VTXFMT7, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, (GXAttr)0xb, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, (GXAttr)0xd, (GXCompCnt)1, (GXCompType)4, 0);

    textureIndex = 0;
    texture = (CTexture*)shape->GetTexture((long*)shape->m_animData, pppEnvStPtr->m_materialSetPtr, textureIndex);
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

    phaseLerp = FLOAT_80330af4 - work->m_phase;
    drawColor = g_ymMelt;
    drawColorBytes = reinterpret_cast<u8*>(&drawColor);
    drawColorBytes[0] = colorWork->m_color.rgba[0];
    drawColorBytes[1] = colorWork->m_color.rgba[1];
    drawColorBytes[2] = colorWork->m_color.rgba[2];
    drawColorBytes[3] = colorWork->m_color.rgba[3];
    vertexData = work->m_vertexData;
    worldX = pppMngStPtr->m_matrix.value[0][3];
    worldY = pppMngStPtr->m_matrix.value[1][3];
    worldZ = pppMngStPtr->m_matrix.value[2][3];
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

            if (FLOAT_80330af4 != work->m_phase) {
                vtx0.x = phaseLerp * (worldX - vtx0.x) + vtx0.x;
                vtx0.z = phaseLerp * (worldZ - vtx0.z) + vtx0.z;
                vtx1.x = phaseLerp * (worldX - vtx1.x) + vtx1.x;
                vtx1.z = phaseLerp * (worldZ - vtx1.z) + vtx1.z;
                vtx3.x = phaseLerp * (worldX - vtx3.x) + vtx3.x;
                vtx3.z = phaseLerp * (worldZ - vtx3.z) + vtx3.z;
                vtx2.x = phaseLerp * (worldX - vtx2.x) + vtx2.x;
                vtx2.z = phaseLerp * (worldZ - vtx2.z) + vtx2.z;
            }

            GXPosition3f32(vtx0.x, vtx0.y, vtx0.z);
            if (p0Data->m_color.m_bytes[3] != 0) {
                colorValue = drawColor;
            } else {
                colorValue = p0Data->m_color.m_rawColor;
            }
            GXColor1u32(colorValue);
            GXTexCoord2f32(uvMin.x + (f32)x * uStep, uvMin.y + v1);

            GXPosition3f32(vtx1.x, vtx1.y, vtx1.z);
            if (p1Data->m_color.m_bytes[3] != 0) {
                colorValue = drawColor;
            } else {
                colorValue = p1Data->m_color.m_rawColor;
            }
            GXColor1u32(colorValue);
            GXTexCoord2f32(uvMin.x + (f32)x * uStep, uvMin.y + v0);

            GXPosition3f32(vtx2.x, vtx2.y, vtx2.z);
            if (p2Data->m_color.m_bytes[3] != 0) {
                colorValue = drawColor;
            } else {
                colorValue = p2Data->m_color.m_rawColor;
            }
            GXColor1u32(colorValue);
            GXTexCoord2f32(uvMin.x + (f32)(x + 1) * uStep, uvMin.y + v0);

            GXPosition3f32(vtx3.x, vtx3.y, vtx3.z);
            if (p3Data->m_color.m_bytes[3] != 0) {
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

void pppFrameYmMelt(PYmMelt* ymMelt, YmMeltCtrl* ctrl, PYmMeltDataOffsets* offsets)
{
    s16 phaseWork;
    int gridCount;
    int vertexCount;
    int angleSeed;
    YmMeltWork* work;
    YmMeltColorWork* colorWork;
    YmMeltVertex* rowVertex;
    YmMeltVertex* vertex;
    YmMeltVertex* vertexBase;
    float step;
    float halfWidth;
    float matrixY;
    float x;
    float rot;
    float z;
    Mtx rotMtx;

    if (gPppCalcDisabled != 0) {
        return;
    }

    work = GetYmMeltWork(ymMelt, offsets);
    colorWork = GetYmMeltColorWork(ymMelt, offsets);
    gridCount = ctrl->m_gridSize + 1;
    vertexCount = gridCount * gridCount;
    matrixY = pppMngStPtr->m_matrix.value[1][3];

    if (work->m_vertexData == nullptr) {
        work->m_vertexData = (YmMeltVertex*)pppMemAlloc(
            (unsigned long)vertexCount * sizeof(YmMeltVertex), pppEnvStPtr->m_stagePtr,
            const_cast<char*>(s_pppYmMelt_cpp),
            0xA9);

        vertexBase = work->m_vertexData;
        angleSeed = rand();
        phaseWork = ctrl->m_phasePeriod;
        int phaseQuotient = angleSeed / phaseWork;
        work->m_phaseOffset = angleSeed - phaseQuotient * phaseWork;
        halfWidth = ctrl->m_stepValue * FLOAT_80330b08;
        phaseWork = work->m_phaseOffset;
        step = ctrl->m_stepValue / (f32)ctrl->m_gridSize;
        rot = FLOAT_80330b0c * (f32)phaseWork;
        vertex = vertexBase;

        for (z = -halfWidth; z <= halfWidth; z += step) {
            rowVertex = vertex;
            for (x = -halfWidth; x <= halfWidth; x += step) {
                rowVertex->m_position.x = x;
                rowVertex->m_position.y = kPppYmMeltZero;
                rowVertex->m_position.z = z;

                if (phaseWork != 0) {
                    PSMTXRotRad(rotMtx, 'y', rot);
                    PSMTXMultVec(rotMtx, &rowVertex->m_position, &rowVertex->m_position);
                }

                rowVertex++;
                vertex++;
            }
        }

        CalcPolygonHeight((VERTEX_DATA*)ctrl, vertexBase, (_GXColor*)&colorWork->m_color, matrixY);
    }

    work->m_phaseVelocity = work->m_phaseVelocity + work->m_phaseAccel;
    work->m_phase = work->m_phase + work->m_phaseVelocity;

    if (ctrl->m_graphId == ymMelt->m_graphId) {
        work->m_phase += *(float*)&ctrl->m_payload[0];
        work->m_phaseVelocity += *(float*)&ctrl->m_payload[4];
        work->m_phaseAccel += *(float*)&ctrl->m_payload[8];
    }

    if (ctrl->m_dataValIndex != 0xFFFF) {
        long* animData = **(long***)(*(u32*)&pppEnvStPtr->m_particleColors[0] + ctrl->m_dataValIndex * 4);
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
    float expand;
    float top;
    float rayY;
    float zero;
    float previousY;
    Vec rayDirection;
    Vec worldBase;
    YmMeltVertex* vertex;
    CMapCylinderRaw cylinder;
    u8* colorBytes = (u8*)color;

    pointCount = vertexData->m_gridSize + 1;
    pointCount *= pointCount;
    previousY = pppMngStPtr->m_previousPosition.x;
    zero = kPppYmMeltZero;
    rayY = FLOAT_80330b10;
    top = FLOAT_80330b14;
    expand = FLOAT_80330b18;
    for (i = 0; i < pointCount; i++) {
        vertex = &vertexBuffer[i];

        vertex->m_color.m_bytes[0] = colorBytes[0];
        vertex->m_color.m_bytes[1] = colorBytes[1];
        vertex->m_color.m_bytes[2] = colorBytes[2];
        vertex->m_color.m_bytes[3] = colorBytes[3];

        worldBase.x = pppMngStPtr->m_matrix.value[0][3];
        worldBase.y = pppMngStPtr->m_matrix.value[1][3];
        worldBase.z = pppMngStPtr->m_matrix.value[2][3];
        worldBase.y += vertexData->m_collisionYOffset;
        rayDirection.x = zero;
        rayDirection.y = rayY;
        rayDirection.z = zero;
        pppAddVector(vertex->m_position, vertex->m_position, worldBase);

        cylinder.m_topBounds.z = top;
        cylinder.m_topBounds.y = top;
        cylinder.m_topBounds.x = top;
        cylinder.m_expandBounds.z = expand;
        cylinder.m_expandBounds.y = expand;
        cylinder.m_expandBounds.x = expand;
        cylinder.m_bottom = vertex->m_position;
        cylinder.m_rayDirection.x = rayDirection.x;
        cylinder.m_rayDirection.y = rayDirection.y;
        cylinder.m_rayDirection.z = rayDirection.z;
        cylinder.m_rayPadding = zero;

        if (MapMng.CheckHitCylinderNear((CMapCylinder*)&cylinder, &rayDirection, 0xFFFFFFFF) != 0) {
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
