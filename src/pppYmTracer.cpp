#include "ffcc/pppYmTracer.h"
#include "ffcc/gxfunc.h"
#include "ffcc/mapmesh.h"
#include "ffcc/pppPart.h"
#include "ffcc/textureman.h"
extern "C" {
extern f32 gPppDefaultValueBuffer[];
}
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern const f32 FLOAT_803306e8;
extern const f32 FLOAT_803306ec;
extern u32 kYmTracerTopColorBase;
extern u32 kYmTracerBottomColorBase;

extern "C" const char s_pppYmTracer_cpp[] = "pppYmTracer.cpp";

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
    u32 _pad2;
};

struct TracerWork {
    Vec from;
    float _pad0;
    Vec to;
    float _pad1c;
    float* initWork;
    float* arg3Work;
    TRACE_POLYGON* entries;
    u16 count;
    u16 _pad2e;
};

union PackedColor {
    u32 value;
    u8 bytes[4];
};

static inline void copyPolygonData(TRACE_POLYGON* dst, TRACE_POLYGON* src)
{
    pppCopyVector(dst->from, src->from);
    pppCopyVector(dst->to, src->to);
    dst->life = src->life;
    dst->decay = src->decay;
    dst->colorR = src->colorR;
    dst->colorG = src->colorG;
    dst->colorB = src->colorB;
    dst->alpha = src->alpha;
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
void pppRenderYmTracer(pppYmTracer* pppYmTracer, pppYmTracerUnkB* param_2, pppYmTracerUnkC* param_3)
{
    TracerWork* work;
    CMapMesh* mapMesh;
    u8* colorData;
    TRACE_POLYGON* poly;
    CTexture* texture;
    s32 i;
    s32 dataOffset;
    s32 colorOffset;
    s32 dataValIndex;
    PackedColor colorTop;
    PackedColor colorBottom;
    f32 uTop;
    f32 uBottom;
    f32 uvStep;
    int textureIndex[2];

    dataValIndex = param_2->m_dataValIndex;
    dataOffset = *param_3->m_serializedDataOffsets;
    work = (TracerWork*)(pppYmTracer->m_object.m_workArea + dataOffset);
    colorOffset = param_3->m_serializedDataOffsets[1];
    poly = work->entries;
    mapMesh = pppEnvStPtr->m_mapMeshPtr[dataValIndex];
    colorData = pppYmTracer->m_object.m_workArea + colorOffset;

    if (dataValIndex != 0xFFFF) {
        pppSetBlendMode(param_2->m_tracer.m_blendMode);
        pppSetDrawEnv(
            reinterpret_cast<pppCVECTOR*>(colorData + 8), reinterpret_cast<pppFMATRIX*>(&ppvCameraMatrix),
            FLOAT_803306e8,
            param_2->m_tracer.m_drawEnvColor1, param_2->m_tracer.m_drawEnvColor0,
            param_2->m_tracer.m_blendMode, 0, 1, 1, 0);
        gUtil.SetVtxFmt_POS_CLR_TEX();

        textureIndex[0] = 0;
        texture = (CTexture*)mapMesh->GetTexture(pppEnvStPtr->m_materialSetPtr, textureIndex[0]);
        if (texture != 0) {
            GXLoadTexObj(&texture->m_texObj, GX_TEXMAP0);
            GXSetNumChans(1);
            GXSetNumTexGens(1);
            GXSetNumTevStages(1);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
            _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
            _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);

            u32 format = (u32)texture->m_format;
            if ((format == 8) || (format == 9)) {
                SetUpPaletteEnv(texture);
            }

            uvStep = FLOAT_803306ec / (f32)(u32)work->count;
            GXSetCullMode(GX_CULL_NONE);

            for (i = 0; i < (s32)(work->count - 1); i++) {
                TRACE_POLYGON* next = poly + 1;

                if ((next->life > 0) && (FLOAT_803306e8 != poly->to.x) && (FLOAT_803306e8 != poly->to.y) &&
                    (FLOAT_803306e8 != poly->to.z) && (FLOAT_803306e8 != poly->from.x) &&
                    (FLOAT_803306e8 != poly->from.y) && (FLOAT_803306e8 != poly->from.z) &&
                    (FLOAT_803306e8 != next->to.x) && (FLOAT_803306e8 != next->to.y) &&
                    (FLOAT_803306e8 != next->to.z) && (FLOAT_803306e8 != next->from.x) &&
                    (FLOAT_803306e8 != next->from.y) && (FLOAT_803306e8 != next->from.z)) {
                    uTop = (f32)i * uvStep;
                    uBottom = (f32)(i + 1) * uvStep;
                    colorTop.value = kYmTracerTopColorBase;
                    colorTop.bytes[3] = poly->alpha;
                    colorBottom.value = kYmTracerBottomColorBase;
                    colorBottom.bytes[3] = next->alpha;

                    GXBegin((GXPrimitive)0x98, GX_VTXFMT7, 4);
                    GXPosition3f32(poly->to.x, poly->to.y, poly->to.z);
                    GXColor1u32(*(u32*)&colorTop);
                    GXTexCoord2f32(uTop, FLOAT_803306ec);

                    GXPosition3f32(poly->from.x, poly->from.y, poly->from.z);
                    GXColor1u32(*(u32*)&colorTop);
                    GXTexCoord2f32(uTop, FLOAT_803306e8);

                    GXPosition3f32(next->to.x, next->to.y, next->to.z);
                    GXColor1u32(*(u32*)&colorBottom);
                    GXTexCoord2f32(uBottom, FLOAT_803306ec);

                    GXPosition3f32(next->from.x, next->from.y, next->from.z);
                    GXColor1u32(*(u32*)&colorBottom);
                    GXTexCoord2f32(uBottom, FLOAT_803306e8);
                }
                poly++;
            }
        }
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
void pppFrameYmTracer(pppYmTracer* pppYmTracer, pppYmTracerUnkB* param_2, pppYmTracerUnkC* param_3)
{
    TRACE_POLYGON* entries;
    TRACE_POLYGON* entry;
    TRACE_POLYGON* poly;
    TracerWork* work;
    f32 fVar3;
    u8 alpha;
    u8 decay;
    s32 i;
    TRACE_POLYGON* entriesPtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    work = (TracerWork*)(pppYmTracer->m_object.m_workArea + *param_3->m_serializedDataOffsets);
    entriesPtr = work->entries;
    entries = entriesPtr;
    if (entriesPtr == 0) {
        work->entries = (TRACE_POLYGON*)pppMemAlloc(
            (u32)param_2->m_tracer.m_entryCount * sizeof(TRACE_POLYGON), pppEnvStPtr->m_stagePtr,
            const_cast<char*>(s_pppYmTracer_cpp), 0xEB);
        fVar3 = FLOAT_803306e8;
        entries = work->entries;
        entry = entries;
        for (i = 0; i < (s32)(u32)param_2->m_tracer.m_entryCount; i++) {
            entry->life = -1;
            entry->alpha = param_2->m_tracer.m_entryAlpha;
            entry->decay = (u8)((u16)param_2->m_tracer.m_entryAlpha / param_2->m_tracer.m_entryLife);
            entry->from.z = fVar3;
            entry->from.y = fVar3;
            entry->from.x = fVar3;
            entry->to.z = fVar3;
            entry->to.y = fVar3;
            entry->to.x = fVar3;
            entry++;
        }
    }

    if (param_2->m_graphId == pppYmTracer->m_object.m_graphId) {
        work->initWork =
            (param_2->m_initWOrk == -1)
                ? reinterpret_cast<float*>(gPppDefaultValueBuffer)
                : reinterpret_cast<float*>(
                      reinterpret_cast<_pppPObject*>(
                          pppMngStPtr->m_pppPDataVals[param_2->m_initWOrk].m_pppPObjLink)
                              ->m_workArea +
                      param_2->m_stepValue);

        work->arg3Work =
            (param_2->m_arg3 == -1)
                ? reinterpret_cast<float*>(gPppDefaultValueBuffer)
                : reinterpret_cast<float*>(
                      reinterpret_cast<_pppPObject*>(pppMngStPtr->m_pppPDataVals[param_2->m_arg3].m_pppPObjLink)
                              ->m_workArea +
                      param_2->m_tracer.m_arg3WorkOffset);
    }

    if (work->count + 1 < param_2->m_tracer.m_entryCount) {
        for (i = param_2->m_tracer.m_entryCount - 2; i >= 0; i--) {
            copyPolygonData(&entries[i + 1], &entries[i]);
        }

        entries = work->entries;
        entries[0].life = -1;
        entries[0].alpha = param_2->m_tracer.m_entryAlpha;
        entries[0].decay = (u8)((u16)param_2->m_tracer.m_entryAlpha / param_2->m_tracer.m_entryLife);
        fVar3 = FLOAT_803306e8;
        entries[0].from.z = fVar3;
        entries[0].from.y = fVar3;
        entries[0].from.x = fVar3;
        entries[0].to.z = fVar3;
        entries[0].to.y = fVar3;
        entries[0].to.x = fVar3;

        fVar3 = work->initWork[0];
        work->from.x = fVar3;
        entries[0].from.x = fVar3;
        fVar3 = work->initWork[1];
        work->from.y = fVar3;
        entries[0].from.y = fVar3;
        fVar3 = work->initWork[2];
        work->from.z = fVar3;
        entries[0].from.z = fVar3;
        fVar3 = work->arg3Work[0];
        work->to.x = fVar3;
        entries[0].to.x = fVar3;
        fVar3 = work->arg3Work[1];
        work->to.y = fVar3;
        entries[0].to.y = fVar3;
        fVar3 = work->arg3Work[2];
        work->to.z = fVar3;
        entries[0].to.z = fVar3;

        entries[0].life = param_2->m_tracer.m_entryLife;
        entries[0].alpha = param_2->m_tracer.m_entryAlpha;

        {
            pppFMATRIX result;

            pppMulMatrix(result, pppMngStPtr->m_matrix, pppYmTracer->m_object.m_localMatrix);
            PSMTXMultVec(result.value, &entries[0].from, &entries[0].from);
            PSMTXMultVec(result.value, &entries[0].to, &entries[0].to);
        }

        work->count++;

        if (work->count >= 4) {
            Vec splineFrom[4];
            Vec splineTo[4];
            s16 splineCount = 0;
            f32 t;
            f32 stepScale = FLOAT_803306ec / (f32)(param_2->m_tracer.m_splineCount + 1);

            for (i = 0; i < (s32)(u32)param_2->m_tracer.m_splineCount; i++) {
                t = stepScale * (f32)(i + 1);

                gUtil.GetSplinePos(splineFrom[(param_2->m_tracer.m_splineCount - 1) - i], entries[3].from, entries[2].from,
                                          entries[1].from, entries[0].from, t, FLOAT_803306ec);
                gUtil.GetSplinePos(splineTo[(param_2->m_tracer.m_splineCount - 1) - i], entries[3].to, entries[2].to,
                                          entries[1].to, entries[0].to, t, FLOAT_803306ec);

                splineCount++;
                work->count++;
                if (work->count + 1 >= param_2->m_tracer.m_entryCount) {
                    break;
                }
            }

            for (i = 0; i < splineCount; i++) {
                for (s32 j = param_2->m_tracer.m_entryCount - 2; j >= 2; j--) {
                    copyPolygonData(&entries[j + 1], &entries[j]);
                }
            }

            TRACE_POLYGON* splineEntry = entries;
            for (i = 0; i < splineCount; i++) {
                s32 idx = i + 2;
                splineEntry[2].alpha = param_2->m_tracer.m_entryAlpha - idx * splineEntry[2].decay;
                pppCopyVector(entries[idx].from, splineFrom[i]);
                pppCopyVector(entries[idx].to, splineTo[i]);
                splineEntry++;
            }
        }
    }

    poly = entries;
    for (i = 0; i < (s32)(u32)work->count; i++) {
        if (poly->life > 0) {
            alpha = poly->alpha;
            decay = poly->decay;
            s32 remainingAlpha = (u32)alpha - (u32)decay;
            if (remainingAlpha <= 0) {
                poly->alpha = 0;
            } else {
                poly->alpha = alpha - decay;
            }

            poly->life--;
            if (poly->life <= 0) {
                work->count--;
                poly->life = 0;
            }
        }
        poly++;
    }
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
void pppDestructYmTracer(pppYmTracer* pppYmTracer, pppYmTracerUnkC* param_2)
{
    TracerWork* work = (TracerWork*)(pppYmTracer->m_object.m_workArea + *param_2->m_serializedDataOffsets);
    if (work->entries != 0) {
        pppHeapUseRate((CMemory::CStage*)work->entries);
    }
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
void pppConstruct2YmTracer(pppYmTracer* pppYmTracer, pppYmTracerUnkC* param_2)
{
    TracerWork* work;

    work = (TracerWork*)(pppYmTracer->m_object.m_workArea + *param_2->m_serializedDataOffsets);
    work->_pad2e = 0;
    work->count = 0;
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
void pppConstructYmTracer(pppYmTracer* pppYmTracer, pppYmTracerUnkC* param_2)
{
    f32 fVar1;
    TracerWork* work;

    fVar1 = FLOAT_803306e8;
    work = (TracerWork*)(pppYmTracer->m_object.m_workArea + *param_2->m_serializedDataOffsets);

    work->entries = 0;
    work->arg3Work = 0;
    work->initWork = 0;
    work->count = 0;
    work->_pad0 = fVar1;
    work->from.z = fVar1;
    work->from.y = fVar1;
    work->from.x = fVar1;
    work->_pad1c = fVar1;
    work->to.z = fVar1;
    work->to.y = fVar1;
    work->to.x = fVar1;
    work->_pad2e = 0;
}

extern const f64 kPppParHitSphZero = 0.0;
extern const char s_common_80330708[8] = "common";
