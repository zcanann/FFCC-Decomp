#include "ffcc/pppYmMelt.h"
#include "ffcc/linkage.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/symbols_shared.h"
#include "dolphin/mtx.h"

const float FLOAT_80330af4 = 1.0f;
const float FLOAT_80330b08 = 0.5f;
const float FLOAT_80330b0c = 0.017453292f;
const float FLOAT_80330b10 = -2000.0f;
const float FLOAT_80330b14 = 10000000000.0f;
const float FLOAT_80330b18 = -10000000000.0f;

extern "C" {
int rand(void);
int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, unsigned int);
void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
void DCFlushRange(void*, unsigned long);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);

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

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void InitPolygonData(PYmMelt*, VERTEX_DATA*, short)
{
	// TODO
}

#define CalcPolygonHeight CalcPolygonHeight__FP7PYmMeltP11VERTEX_DATAP8_GXColorf
extern "C" void CalcPolygonHeight(VERTEX_DATA*, YmMeltVertex*, _GXColor*, float);

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
    float savedY;
    float zero;
    float rayY;
    float top;
    float expand;
    Vec worldBase;
    Vec rayDirection;
    CMapCylinder cylinder;
    YmMeltVertex* vertex;
    u8* colorBytes = (u8*)color;

    pointCount = vertexData->m_gridSize + 1;
    pointCount *= pointCount;
    savedY = pppMngStPtr->m_savedPosition.y;
    zero = kPppYmMeltZero;
    rayY = FLOAT_80330b10;
    top = FLOAT_80330b14;
    expand = FLOAT_80330b18;
    vertex = vertexBuffer;

    for (i = 0; i < pointCount; i++, vertex++) {
        vertex->m_color.m_bytes[0] = colorBytes[0];
        vertex->m_color.m_bytes[1] = colorBytes[1];
        vertex->m_color.m_bytes[2] = colorBytes[2];
        vertex->m_color.m_bytes[3] = colorBytes[3];

        worldBase.x = pppMngStPtr->m_matrix.value[0][3];
        worldBase.y = pppMngStPtr->m_matrix.value[1][3] + vertexData->m_collisionYOffset;
        worldBase.z = pppMngStPtr->m_matrix.value[2][3];
        pppAddVector(vertex->m_position, vertex->m_position, worldBase);

        rayDirection.x = zero;
        rayDirection.y = rayY;
        rayDirection.z = zero;
        cylinder.m_bottom = vertex->m_position;
        cylinder.m_direction = rayDirection;
        cylinder.m_radius = zero;
        cylinder.m_height = zero;
        cylinder.m_top.x = top;
        cylinder.m_top.y = top;
        cylinder.m_top.z = top;
        cylinder.m_direction2.x = expand;
        cylinder.m_direction2.y = expand;
        cylinder.m_direction2.z = expand;
        cylinder.m_radius2 = expand;
        cylinder.m_height2 = expand;

        if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(
                &MapMng, (CMapCylinder*)&cylinder, &rayDirection, 0xFFFFFFFF) == 0) {
            vertex->m_position.y = savedY;
            if (vertexData->m_hideWhenNoGround != 0) {
                vertex->m_color.m_bytes[0] = 0;
                vertex->m_color.m_bytes[1] = 0;
                vertex->m_color.m_bytes[2] = 0;
                vertex->m_color.m_bytes[3] = 0;
            }
        } else {
            CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A78), &vertex->m_position);
            if ((savedY - vertexData->m_maxDropDistance) > vertex->m_position.y) {
                vertex->m_position.y = savedY;
                if (vertexData->m_hideWhenNoGround != 0) {
                    vertex->m_color.m_bytes[0] = 0;
                    vertex->m_color.m_bytes[1] = 0;
                    vertex->m_color.m_bytes[2] = 0;
                    vertex->m_color.m_bytes[3] = 0;
                }
            }
        }

        vertex->m_position.y = vertex->m_position.y + vertexData->m_heightBias;
        vertex->m_position.y = vertex->m_position.y - yOffset;
    }

    DCFlushRange(vertexBuffer, pointCount * 0x10);
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
char s_pppYmMelt_cpp_801DA048[] = "pppYmMelt.cpp";

void pppFrameYmMelt(PYmMelt* ymMelt, YmMeltCtrl* ctrl, PYmMeltDataOffsets* offsets)
{
    int colorOffset;
    int gridCount;

    if (gPppCalcDisabled != 0) {
        return;
    }

    YmMeltWork* work = (YmMeltWork*)((u8*)ymMelt + *offsets->m_serializedDataOffsets + 0x80);
    colorOffset = offsets->m_serializedDataOffsets[1];
    gridCount = *(u16*)((u8*)&ctrl->m_initWOrk + 2) + 1;
    int vertexCount = gridCount * gridCount;
    float matrixY = pppMngStPtr->m_matrix.value[1][3];

    if (work->m_vertexData == nullptr) {
        work->m_vertexData = (YmMeltVertex*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (unsigned long)vertexCount * sizeof(YmMeltVertex), pppEnvStPtr->m_stagePtr, s_pppYmMelt_cpp_801DA048,
            0xA9);

        YmMeltVertex* vertexBase = work->m_vertexData;
        int angleSeed = rand();
        s16 phaseDiv = *(s16*)((u8*)&ctrl->m_arg3 + 2);
        work->m_phaseOffset = angleSeed - angleSeed / phaseDiv * phaseDiv;
        float halfWidth = ctrl->m_stepValue * FLOAT_80330b08;
        s16 phaseOffset = work->m_phaseOffset;
        float step = ctrl->m_stepValue / (f32)*(u16*)((u8*)&ctrl->m_initWOrk + 2);
        float rot = FLOAT_80330b0c * (f32)phaseOffset;
        Vec* vertex = &vertexBase->m_position;
        Mtx rotMtx;

        for (float z = -halfWidth; z <= halfWidth; z += step) {
            Vec* rowVertex = vertex;
            for (float x = -halfWidth; x <= halfWidth; x += step) {
                rowVertex->x = x;
                rowVertex->y = kPppYmMeltZero;
                rowVertex->z = z;

                if (phaseOffset != 0) {
                    PSMTXRotRad(rotMtx, 'y', rot);
                    PSMTXMultVec(rotMtx, rowVertex, rowVertex);
                }

                rowVertex = (Vec*)((u8*)rowVertex + sizeof(YmMeltVertex));
                vertex = (Vec*)((u8*)vertex + sizeof(YmMeltVertex));
            }
        }

        CalcPolygonHeight((VERTEX_DATA*)ctrl, vertexBase, (_GXColor*)((u8*)ymMelt + colorOffset + 0x88), matrixY);
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
                                      work->m_shapeFrameTime, *(s16*)&ctrl->m_initWOrk);
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
    YmMeltColorWork* colorWork;
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
    colorWork = (YmMeltColorWork*)((u8*)ymMelt + colorOffset + 0x80);
    if (ctrl->m_dataValIndex == 0xFFFF) {
        return;
    }

    shape = *(pppShapeSt**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + ctrl->m_dataValIndex * 4);

    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        &colorWork->m_color, &ppvCameraMatrix0, kPppYmMeltZero, ctrl->m_payload[0x19],
        ctrl->m_payload[0x18], *(u8*)&ctrl->m_arg3, 2, 1, 1, 0);
    pppSetBlendMode(*(u8*)&ctrl->m_arg3);

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
    drawColor = colorWork->m_colorValue;
    worldX = pppMngStPtr->m_matrix.value[0][3];
    worldY = pppMngStPtr->m_matrix.value[1][3];
    worldZ = pppMngStPtr->m_matrix.value[2][3];
    pppGetShapeUV__FPlsR5Vec2dR5Vec2di((long*)shape->m_animData, work->m_shapeDrawFrame, uvMin, uvMax, 0);

    grid = *(u16*)((u8*)&ctrl->m_initWOrk + 2);
    uStep = (uvMax.x - uvMin.x) / (f32)grid;
    vStep = (uvMax.y - uvMin.y) / (f32)grid;
    GXBegin((GXPrimitive)0x80, GX_VTXFMT7, (u16)((grid * grid * 4) & 0xFFFC));

    for (u32 z = 0; z < grid; z++) {
        float v0 = uvMin.y + (f32)z * vStep;
        float v1 = uvMin.y + (f32)(z + 1) * vStep;
        u32 stride = grid + 1;
        u32 x = 0;

        while (x < grid) {
            u32 idx0 = x + z * stride;
            u32 idx1 = x + (z + 1) * stride;
            YmMeltVertex* p0Data = &work->m_vertexData[idx1];
            YmMeltVertex* p1Data = &work->m_vertexData[idx0];
            YmMeltVertex* p2Data = &work->m_vertexData[idx0 + 1];
            YmMeltVertex* p3Data = &work->m_vertexData[idx1 + 1];
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

            pppCopyVector(vtx0, p0Data->m_position);
            pppCopyVector(vtx1, p1Data->m_position);
            pppCopyVector(vtx2, p2Data->m_position);
            pppCopyVector(vtx3, p3Data->m_position);

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

            if (p0Data->m_color.m_bytes[3] == 0) {
                c0 = p0Data->m_color.m_colorValue;
            }
            if (p1Data->m_color.m_bytes[3] == 0) {
                c1 = p1Data->m_color.m_colorValue;
            }
            if (p2Data->m_color.m_bytes[3] == 0) {
                c2 = p2Data->m_color.m_colorValue;
            }
            if (p3Data->m_color.m_bytes[3] == 0) {
                c3 = p3Data->m_color.m_colorValue;
            }

            GXPosition3f32(vtx0.x, vtx0.y, vtx0.z);
            GXColor1u32(*(u32*)&c0);
            GXTexCoord2f32(u0, v1);
            GXPosition3f32(vtx1.x, vtx1.y, vtx1.z);
            GXColor1u32(*(u32*)&c1);
            GXTexCoord2f32(u0, v0);
            GXPosition3f32(vtx2.x, vtx2.y, vtx2.z);
            GXColor1u32(*(u32*)&c2);
            GXTexCoord2f32(u1, v0);
            GXPosition3f32(vtx3.x, vtx3.y, vtx3.z);
            GXColor1u32(*(u32*)&c3);
            GXTexCoord2f32(u1, v1);
            x++;
        }
    }

    if ((*(u8*)((u8*)texture + 0x60) == 8) || (*(u8*)((u8*)texture + 0x60) == 9)) {
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    }
}
