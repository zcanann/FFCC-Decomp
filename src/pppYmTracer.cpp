#include "global.h"
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

static const char s_pppYmTracer_cpp[] = "pppYmTracer.cpp";

STATIC_ASSERT(sizeof(YmTracerDataOffsets) == 0x8);
STATIC_ASSERT(offsetof(YmTracerDataOffsets, m_workOffset) == 0x0);
STATIC_ASSERT(offsetof(YmTracerDataOffsets, m_colorOffset) == 0x4);
STATIC_ASSERT(sizeof(TRACE_POLYGON) == 0x28);
STATIC_ASSERT(offsetof(TRACE_POLYGON, from) == 0x0);
STATIC_ASSERT(offsetof(TRACE_POLYGON, to) == 0x10);
STATIC_ASSERT(offsetof(TRACE_POLYGON, colorR) == 0x1c);
STATIC_ASSERT(offsetof(TRACE_POLYGON, life) == 0x20);
STATIC_ASSERT(offsetof(TRACE_POLYGON, decay) == 0x22);
STATIC_ASSERT(sizeof(YmTracerWork) == 0x30);
STATIC_ASSERT(offsetof(YmTracerWork, initWork) == 0x20);
STATIC_ASSERT(offsetof(YmTracerWork, entries) == 0x28);
STATIC_ASSERT(offsetof(YmTracerWork, count) == 0x2c);
STATIC_ASSERT(offsetof(VColor, m_color) == 0x8);

static inline YmTracerDataOffsets* GetYmTracerDataOffsets(pppYmTracerCtrl* ctrl)
{
    return reinterpret_cast<YmTracerDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void initTracePolygon(PYmTracer* params, TRACE_POLYGON& polygon)
{
    polygon.life = -1;
    polygon.alpha = params->m_tracer.m_entryAlpha;
    polygon.decay = params->m_tracer.m_entryAlpha / params->m_tracer.m_entryLife;
    polygon.from.z = 0.0f;
    polygon.from.y = 0.0f;
    polygon.from.x = 0.0f;
    polygon.to.z = 0.0f;
    polygon.to.y = 0.0f;
    polygon.to.x = 0.0f;
}

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

static inline YmTracerWork* GetYmTracerWork(pppYmTracer* tracer, pppYmTracerCtrl* ctrl)
{
    return reinterpret_cast<YmTracerWork*>(tracer->m_workArea + GetYmTracerDataOffsets(ctrl)->m_workOffset);
}

static inline float* GetYmTracerDataValueWork(int dataValueIndex, int offset)
{
    return reinterpret_cast<float*>(
        reinterpret_cast<_pppPObject*>(ppvMng->m_pppPDataVals[dataValueIndex].m_pppPObjLink)->m_workArea +
        offset);
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
void pppRenderYmTracer(pppYmTracer* tracer, pppYmTracerStep* step, pppYmTracerCtrl* ctrl)
{
    YmTracerWork* work;
    CMapMesh* mapMesh;
    VColor* colorData;
    TRACE_POLYGON* poly;
    CTexture* texture;
    s32 i;
    s32 colorOffset;
    s32 dataValIndex;
    f32 uTop;
    f32 uBottom;
    f32 uvStep;
    int textureIndex[2];

    dataValIndex = step->m_dataValIndex;
    work = GetYmTracerWork(tracer, ctrl);
    colorOffset = GetYmTracerDataOffsets(ctrl)->m_colorOffset;
    poly = work->entries;
    mapMesh = ppvEnv->m_mapMeshPtr[dataValIndex];
    colorData = reinterpret_cast<VColor*>(tracer->m_workArea + colorOffset);

    if (dataValIndex != 0xFFFF) {
        pppSetBlendMode(step->m_tracer.m_blendMode);
        pppSetDrawEnv(
            &colorData->m_color, reinterpret_cast<pppFMATRIX*>(&ppvCameraMatrix),
            0.0f,
            step->m_tracer.m_drawEnvColor1, step->m_tracer.m_drawEnvColor0,
            step->m_tracer.m_blendMode, 0, 1, 1, 0);
        gUtil.SetVtxFmt_POS_CLR_TEX();

        textureIndex[0] = 0;
        texture = (CTexture*)mapMesh->GetTexture(ppvEnv->m_materialSetPtr, textureIndex[0]);
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
            if ((format == GX_TF_C4) || (format == GX_TF_C8)) {
                SetUpPaletteEnv(texture);
            }

            uvStep = 1.0f / (f32)(u32)work->count;
            GXSetCullMode(GX_CULL_NONE);

            for (i = 0; i < (s32)(work->count - 1); i++) {
                TRACE_POLYGON* next = poly + 1;

                if ((next->life > 0) && (0.0f != poly->to.x) && (0.0f != poly->to.y) &&
                    (0.0f != poly->to.z) && (0.0f != poly->from.x) &&
                    (0.0f != poly->from.y) && (0.0f != poly->from.z) &&
                    (0.0f != next->to.x) && (0.0f != next->to.y) &&
                    (0.0f != next->to.z) && (0.0f != next->from.x) &&
                    (0.0f != next->from.y) && (0.0f != next->from.z)) {
                    uTop = (f32)i * uvStep;
                    uBottom = (f32)(i + 1) * uvStep;
                    pppPackedColor colorTop = {0xFFFFFF00};
                    colorTop.bytes[3] = poly->alpha;
                    pppPackedColor colorBottom = {0xFFFFFF00};
                    colorBottom.bytes[3] = next->alpha;

                    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
                    GXPosition3f32(poly->to.x, poly->to.y, poly->to.z);
                    GXColor1u32(*(u32*)&colorTop);
                    GXTexCoord2f32(uTop, 1.0f);

                    GXPosition3f32(poly->from.x, poly->from.y, poly->from.z);
                    GXColor1u32(*(u32*)&colorTop);
                    GXTexCoord2f32(uTop, 0.0f);

                    GXPosition3f32(next->to.x, next->to.y, next->to.z);
                    GXColor1u32(*(u32*)&colorBottom);
                    GXTexCoord2f32(uBottom, 1.0f);

                    GXPosition3f32(next->from.x, next->from.y, next->from.z);
                    GXColor1u32(*(u32*)&colorBottom);
                    GXTexCoord2f32(uBottom, 0.0f);
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
void pppFrameYmTracer(pppYmTracer* tracer, pppYmTracerStep* step, pppYmTracerCtrl* ctrl)
{
    TRACE_POLYGON* entries;
    TRACE_POLYGON* entry;
    TRACE_POLYGON* poly;
    YmTracerWork* work;
    f32 val;
    s32 i;
    TRACE_POLYGON* entriesPtr;

    if (ppvUserStopPartF != 0) {
        return;
    }

    work = GetYmTracerWork(tracer, ctrl);
    entriesPtr = work->entries;
    entries = entriesPtr;
    if (entriesPtr == 0) {
        work->entries = (TRACE_POLYGON*)pppMemAlloc(
            (u32)step->m_tracer.m_entryCount * sizeof(TRACE_POLYGON), ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppYmTracer_cpp), 0xEB);
        entries = work->entries;
        entry = entries;
        for (i = 0; i < (s32)(u32)step->m_tracer.m_entryCount; i++) {
            initTracePolygon(step, *entry);
            entry++;
        }
    }

    if (step->m_graphId == tracer->m_graphId) {
        work->initWork =
            (step->m_initWOrk == -1)
                ? reinterpret_cast<float*>(gPppDefaultValueBuffer)
                : GetYmTracerDataValueWork(step->m_initWOrk, step->m_stepValue);

        work->arg3Work =
            (step->m_arg3 == -1)
                ? reinterpret_cast<float*>(gPppDefaultValueBuffer)
                : GetYmTracerDataValueWork(step->m_arg3, step->m_tracer.m_arg3WorkOffset);
    }

    if (work->count + 1 < step->m_tracer.m_entryCount) {
        for (i = step->m_tracer.m_entryCount - 2; i >= 0; i--) {
            copyPolygonData(&entries[i + 1], &entries[i]);
        }

        entries = work->entries;
        initTracePolygon(step, entries[0]);

        val = work->initWork[0];
        work->from.x = val;
        entries[0].from.x = val;
        val = work->initWork[1];
        work->from.y = val;
        entries[0].from.y = val;
        val = work->initWork[2];
        work->from.z = val;
        entries[0].from.z = val;
        val = work->arg3Work[0];
        work->to.x = val;
        entries[0].to.x = val;
        val = work->arg3Work[1];
        work->to.y = val;
        entries[0].to.y = val;
        val = work->arg3Work[2];
        work->to.z = val;
        entries[0].to.z = val;

        entries[0].life = step->m_tracer.m_entryLife;
        entries[0].alpha = step->m_tracer.m_entryAlpha;

        {
            pppFMATRIX result;

            pppMulMatrix(result, ppvMng->m_matrix, tracer->m_localMatrix);
            PSMTXMultVec(result.value, &entries[0].from, &entries[0].from);
            PSMTXMultVec(result.value, &entries[0].to, &entries[0].to);
        }

        work->count++;

        if (work->count >= 4) {
            Vec splineFrom[4];
            Vec splineTo[4];
            s16 splineCount = 0;
            f32 t;
            f32 stepScale = 1.0f / (f32)(step->m_tracer.m_splineCount + 1);

            for (i = 0; i < (s32)(u32)step->m_tracer.m_splineCount; i++) {
                t = stepScale * (f32)(i + 1);

                gUtil.GetSplinePos(splineFrom[(step->m_tracer.m_splineCount - 1) - i], entries[3].from, entries[2].from,
                                          entries[1].from, entries[0].from, t, 1.0f);
                gUtil.GetSplinePos(splineTo[(step->m_tracer.m_splineCount - 1) - i], entries[3].to, entries[2].to,
                                          entries[1].to, entries[0].to, t, 1.0f);

                splineCount++;
                work->count++;
                if (work->count + 1 >= step->m_tracer.m_entryCount) {
                    break;
                }
            }

            for (i = 0; i < splineCount; i++) {
                for (s32 j = step->m_tracer.m_entryCount - 2; j >= 2; j--) {
                    copyPolygonData(&entries[j + 1], &entries[j]);
                }
            }

            TRACE_POLYGON* splineEntry = entries;
            for (i = 0; i < splineCount; i++) {
                s32 idx = i + 2;
                splineEntry[2].alpha = step->m_tracer.m_entryAlpha - idx * splineEntry[2].decay;
                pppCopyVector(entries[idx].from, splineFrom[i]);
                pppCopyVector(entries[idx].to, splineTo[i]);
                splineEntry++;
            }
        }
    }

    poly = entries;
    for (i = 0; i < (s32)(u32)work->count; i++) {
        if (poly->life > 0) {
            if ((s32)((u32)poly->alpha - (u32)poly->decay) <= 0) {
                poly->alpha = 0;
            } else {
                poly->alpha -= poly->decay;
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
void pppDestructYmTracer(pppYmTracer* tracer, pppYmTracerCtrl* ctrl)
{
    YmTracerWork* work = GetYmTracerWork(tracer, ctrl);
    if (work->entries != 0) {
        pppMemFree(work->entries);
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
void pppConstruct2YmTracer(pppYmTracer* tracer, pppYmTracerCtrl* ctrl)
{
    YmTracerWork* work;

    work = GetYmTracerWork(tracer, ctrl);
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
void pppConstructYmTracer(pppYmTracer* tracer, pppYmTracerCtrl* ctrl)
{
    f32 zero;
    YmTracerWork* work;

    zero = 0.0f;
    work = GetYmTracerWork(tracer, ctrl);

    work->entries = 0;
    work->arg3Work = 0;
    work->initWork = 0;
    work->count = 0;
    work->_pad0 = zero;
    work->from.z = zero;
    work->from.y = zero;
    work->from.x = zero;
    work->_pad1c = zero;
    work->to.z = zero;
    work->to.y = zero;
    work->to.x = zero;
    work->_pad2e = 0;
}
