#include "ffcc/pppYmTracer.h"
#include "ffcc/mapmesh.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern f32 FLOAT_803306e8;
extern f32 FLOAT_803306ec;
extern u32 DAT_803306e0;
extern u32 DAT_803306e4;
extern f64 DOUBLE_803306f8;
extern s32 DAT_8032ed70;
extern s32 DAT_801eadc8;
extern CUtil DAT_8032ec70;

extern "C" {
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void pppSetBlendMode__FUc(unsigned char);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
    unsigned char);
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh*, CMaterialSet*, int&);
void SetVtxFmt_POS_CLR_TEX__5CUtilFv(void*);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
}

static char s_pppYmTracer_cpp_801d9ce0[] = "pppYmTracer.cpp";

struct TRACE_POLYGON {
    Vec from;
    float _pad0;
    Vec to;
    u8 colorR;
    u8 colorG;
    u8 colorB;
    u8 alpha;
    s16 life;
    u8 decay;
    u8 _pad1;
};

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void initTracePolygon(pppYmTracer*, TRACE_POLYGON*)
{
    // TODO
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void copyPolygonData(TRACE_POLYGON*, TRACE_POLYGON*)
{
    // TODO
}

/*
 * --INFO--
 * PAL Address: 80093cb4
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmTracer(pppYmTracer* pppYmTracer, UnkC* param_2)
{
    f32 fVar1;
    u8* work;

    fVar1 = FLOAT_803306e8;
    work = (u8*)pppYmTracer + 0x80 + *param_2->m_serializedDataOffsets;

    *(u32*)(work + 0x28) = 0;
    *(u32*)(work + 0x24) = 0;
    *(u32*)(work + 0x20) = 0;
    *(u16*)(work + 0x2C) = 0;

    *(f32*)(work + 0xC) = fVar1;
    *(f32*)(work + 0x8) = fVar1;
    *(f32*)(work + 0x4) = fVar1;
    *(f32*)(work + 0x0) = fVar1;
    *(f32*)(work + 0x1C) = fVar1;
    *(f32*)(work + 0x18) = fVar1;
    *(f32*)(work + 0x14) = fVar1;
    *(f32*)(work + 0x10) = fVar1;

    *(u16*)(work + 0x2E) = 0;
}

/*
 * --INFO--
 * PAL Address: 80093c94
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmTracer(pppYmTracer* pppYmTracer, UnkC* param_2)
{
    u8* work;

    work = (u8*)pppYmTracer + 0x80 + *param_2->m_serializedDataOffsets;
    *(u16*)(work + 0x2E) = 0;
    *(u16*)(work + 0x2C) = 0;
}

/*
 * --INFO--
 * PAL Address: 80093c5c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmTracer(pppYmTracer* pppYmTracer, UnkC* param_2)
{
    CMemory::CStage** stagePtr = (CMemory::CStage**)((char*)pppYmTracer + 0xa8 + *param_2->m_serializedDataOffsets);
    if (*stagePtr != nullptr) {
        pppHeapUseRate(*stagePtr);
    }
}

static void shiftTraceEntries(TRACE_POLYGON* entries, s32 count)
{
    for (s32 i = count - 2; i >= 0; i--) {
        entries[i + 1].life = entries[i].life;
        entries[i + 1].decay = entries[i].decay;
        pppCopyVector(entries[i + 1].from, entries[i].from);
        pppCopyVector(entries[i + 1].to, entries[i].to);
        entries[i + 1].colorR = entries[i].colorR;
        entries[i + 1].colorG = entries[i].colorG;
        entries[i + 1].colorB = entries[i].colorB;
        entries[i + 1].alpha = entries[i].alpha;
    }
}

/*
 * --INFO--
 * PAL Address: 800934c4
 * PAL Size: 1944b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmTracer(pppYmTracer* pppYmTracer, UnkB* param_2, UnkC* param_3)
{
    f32* work;
    TRACE_POLYGON* entries;
    u16 maxCount;

    if (DAT_8032ed70 != 0) {
        return;
    }

    work = (f32*)((u8*)pppYmTracer + 0x10 + *param_3->m_serializedDataOffsets);
    entries = (TRACE_POLYGON*)(u32)work[10];
    maxCount = *(u16*)(param_2->m_payload + 4);

    if (entries == nullptr) {
        entries = (TRACE_POLYGON*)pppMemAlloc__FUlPQ27CMemory6CStagePci((u32)maxCount * sizeof(TRACE_POLYGON),
                                                                         pppEnvStPtr->m_stagePtr,
                                                                         s_pppYmTracer_cpp_801d9ce0, 0xEB);
        work[10] = (f32)(u32)entries;

        for (s32 i = 0; i < (s32)maxCount; i++) {
            entries[i].from.x = FLOAT_803306e8;
            entries[i].from.y = FLOAT_803306e8;
            entries[i].from.z = FLOAT_803306e8;
            entries[i].to.x = FLOAT_803306e8;
            entries[i].to.y = FLOAT_803306e8;
            entries[i].to.z = FLOAT_803306e8;
            entries[i].life = -1;
            entries[i].alpha = param_2->m_payload[8];
            entries[i].decay = (u8)((u16)param_2->m_payload[8] / *(u16*)(param_2->m_payload + 6));
        }
    }

    if (param_2->m_graphId == ((s32*)pppYmTracer)[0]) {
        if (param_2->m_initWOrk == -1) {
            work[8] = (f32)(u32)&DAT_801eadc8;
        } else {
            work[8] = (f32)(u32)((u8*)&pppMngStPtr->m_kind + (s32)param_2->m_stepValue);
        }

        if (param_2->m_arg3 == -1) {
            work[9] = (f32)(u32)&DAT_801eadc8;
        } else {
            work[9] = (f32)(u32)((u8*)&pppMngStPtr->m_kind + *(s32*)param_2->m_payload);
        }
    }

    if (*(u16*)(work + 0xB) + 1 < maxCount) {
        shiftTraceEntries(entries, maxCount);

        entries[0].life = *(s16*)(param_2->m_payload + 6);
        entries[0].alpha = param_2->m_payload[8];
        entries[0].decay = (u8)((u16)param_2->m_payload[8] / *(u16*)(param_2->m_payload + 6));

        {
            f32* from = (f32*)(u32)work[8];
            f32* to = (f32*)(u32)work[9];

            work[0] = from[0];
            work[1] = from[1];
            work[2] = from[2];
            entries[0].from.x = from[0];
            entries[0].from.y = from[1];
            entries[0].from.z = from[2];

            work[4] = to[0];
            work[5] = to[1];
            work[6] = to[2];
            entries[0].to.x = to[0];
            entries[0].to.y = to[1];
            entries[0].to.z = to[2];
        }

        {
            pppFMATRIX local;
            pppFMATRIX world;
            pppFMATRIX result;

            pppCopyMatrix(local, *(pppFMATRIX*)((u8*)pppYmTracer + 4));
            pppCopyMatrix(world, pppMngStPtr->m_matrix);
            pppMulMatrix(result, world, local);
            PSMTXMultVec(result.value, &entries[0].from, &entries[0].from);
            PSMTXMultVec(result.value, &entries[0].to, &entries[0].to);
        }

        *(u16*)(work + 0xB) = *(u16*)(work + 0xB) + 1;

        if (*(u16*)(work + 0xB) > 3) {
            Vec splineFrom[0xC];
            Vec splineTo[0xC];
            s16 splineCount;
            f64 stepScale;

            splineCount = 0;
            stepScale = FLOAT_803306ec /
                        (f32)((f64)(param_2->m_payload[9] + 1) - DOUBLE_803306f8);

            for (s32 i = 0; i < (s32)(u32)param_2->m_payload[9]; i++) {
                f32 t;
                Vec p0;
                Vec p1;
                Vec p2;
                Vec p3;
                Vec q0;
                Vec q1;
                Vec q2;
                Vec q3;

                t = (f32)(stepScale * (f64)(i + 1));

                p0 = entries[0].from;
                p1 = entries[1].to;
                p2 = entries[2].to;
                p3 = entries[3].to;
                DAT_8032ec70.GetSplinePos(splineFrom[param_2->m_payload[9] - 1 - i], p3, p2, p1, p0, t,
                                          FLOAT_803306ec);

                q0 = entries[0].to;
                q1 = entries[2].from;
                q2 = entries[3].from;
                q3 = entries[4].from;
                DAT_8032ec70.GetSplinePos(splineTo[param_2->m_payload[9] - 1 - i], q3, q2, q1, q0, t, FLOAT_803306ec);

                splineCount++;
                *(u16*)(work + 0xB) = *(u16*)(work + 0xB) + 1;
                if (maxCount <= *(u16*)(work + 0xB) + 1) {
                    break;
                }
            }

            for (s32 i = 0; i < splineCount; i++) {
                shiftTraceEntries(entries, maxCount);
            }

            for (s32 i = 0; i < splineCount; i++) {
                s32 idx = i + 2;
                entries[idx].alpha = (u8)(param_2->m_payload[8] - idx * entries[0].decay);
                pppCopyVector(entries[idx].from, splineFrom[i]);
                pppCopyVector(entries[idx].to, splineTo[i]);
            }
        }
    }

    entries = (TRACE_POLYGON*)(u32)work[10];
    for (s32 i = 0; i < (s32)(u32)*(u16*)(work + 0xB); i++) {
        if (entries[i].life > 0) {
            if ((s32)((u32)entries[i].alpha - (u32)entries[i].decay) < 1) {
                entries[i].alpha = 0;
            } else {
                entries[i].alpha = entries[i].alpha - entries[i].decay;
            }

            entries[i].life--;
            if (entries[i].life < 1) {
                *(u16*)(work + 0xB) = *(u16*)(work + 0xB) - 1;
                entries[i].life = 0;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 8009312c
 * PAL Size: 920b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmTracer(pppYmTracer* pppYmTracer, UnkB* param_2, UnkC* param_3)
{
    f32* work;
    TRACE_POLYGON* polygons;
    CMapMesh* mapMesh;
    CTexture* texture;
    u16 count;
    f32 uvStep;
    int textureIndex;

    if (param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    work = (f32*)((u8*)pppYmTracer + 0x10 + *param_3->m_serializedDataOffsets);
    polygons = (TRACE_POLYGON*)(u32)work[10];
    count = *(u16*)(work + 0xB);
    if (polygons == nullptr || count < 2) {
        return;
    }

    mapMesh = ((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[param_2->m_dataValIndex];
    pppSetBlendMode__FUc(param_2->m_payload[10]);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (void*)((char*)pppYmTracer + 0x88 + param_3->m_serializedDataOffsets[1]), (void*)&ppvCameraMatrix0,
        FLOAT_803306e8, param_2->m_payload[0xC], param_2->m_payload[0xB], param_2->m_payload[10], 0, 1, 1, 0);
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);

    textureIndex = 0;
    texture = (CTexture*)GetTexture__8CMapMeshFP12CMaterialSetRi(mapMesh, pppEnvStPtr->m_materialSetPtr, textureIndex);
    if (texture == nullptr) {
        return;
    }

    GXLoadTexObj((GXTexObj*)((u8*)texture + 0x28), GX_TEXMAP0);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);

    if ((*(u8*)((u8*)texture + 0x60) == 8) || (*(u8*)((u8*)texture + 0x60) == 9)) {
        SetUpPaletteEnv(texture);
    }

    uvStep = FLOAT_803306ec / (f32)(count - 1);
    GXSetCullMode(GX_CULL_NONE);

    for (u16 i = 0; i < (u16)(count - 1); i++) {
        TRACE_POLYGON* current = &polygons[i];
        TRACE_POLYGON* next = &polygons[i + 1];
        f32 u0;
        f32 u1;
        u32 color0;
        u32 color1;

        if (current->life <= 0) {
            continue;
        }
        if (current->to.x == FLOAT_803306e8 || current->to.y == FLOAT_803306e8 || current->to.z == FLOAT_803306e8) {
            continue;
        }
        if (current->from.x == FLOAT_803306e8 || current->from.y == FLOAT_803306e8 || current->from.z == FLOAT_803306e8) {
            continue;
        }
        if (next->to.x == FLOAT_803306e8 || next->to.y == FLOAT_803306e8 || next->to.z == FLOAT_803306e8) {
            continue;
        }
        if (next->from.x == FLOAT_803306e8 || next->from.y == FLOAT_803306e8 || next->from.z == FLOAT_803306e8) {
            continue;
        }

        u0 = (f32)i * uvStep;
        u1 = (f32)(i + 1) * uvStep;
        color0 = (DAT_803306e0 & 0xFFFFFF00) | current->alpha;
        color1 = (DAT_803306e4 & 0xFFFFFF00) | next->alpha;

        GXBegin((GXPrimitive)0x98, GX_VTXFMT7, 4);
        GXPosition3f32(current->to.x, current->to.y, current->to.z);
        GXColor1u32(color0);
        GXTexCoord2f32(u0, FLOAT_803306ec);

        GXPosition3f32(current->from.x, current->from.y, current->from.z);
        GXColor1u32(color0);
        GXTexCoord2f32(u0, FLOAT_803306e8);

        GXPosition3f32(next->to.x, next->to.y, next->to.z);
        GXColor1u32(color1);
        GXTexCoord2f32(u1, FLOAT_803306ec);

        GXPosition3f32(next->from.x, next->from.y, next->from.z);
        GXColor1u32(color1);
        GXTexCoord2f32(u1, FLOAT_803306e8);
    }
}
