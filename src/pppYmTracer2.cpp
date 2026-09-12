#include "ffcc/pppYmTracer2.h"
#include "global.h"
#include "ffcc/gxfunc.h"
#include "ffcc/mapmesh.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/textureman.h"
#include "ffcc/pppYmEnv.h"
extern "C" {
extern f32 gPppDefaultValueBuffer[];
}
#include "ffcc/util.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#pragma exceptions on

static const char s_pppYmTracer2_cpp[] = "pppYmTracer2.cpp";

STATIC_ASSERT(sizeof(YmTracer2DataOffsets) == 0x8);
STATIC_ASSERT(offsetof(YmTracer2DataOffsets, m_workOffset) == 0x0);
STATIC_ASSERT(offsetof(YmTracer2DataOffsets, m_colorOffset) == 0x4);
STATIC_ASSERT(sizeof(YmTracer2Polygon) == 0x28);
STATIC_ASSERT(offsetof(YmTracer2Polygon, pos) == 0x0);
STATIC_ASSERT(offsetof(YmTracer2Polygon, targetPos) == 0x10);
STATIC_ASSERT(offsetof(YmTracer2Polygon, colorR) == 0x1c);
STATIC_ASSERT(offsetof(YmTracer2Polygon, active) == 0x20);
STATIC_ASSERT(sizeof(YmTracer2Work) == 0x34);
STATIC_ASSERT(offsetof(YmTracer2Work, initWork) == 0x20);
STATIC_ASSERT(offsetof(YmTracer2Work, entries) == 0x28);
STATIC_ASSERT(offsetof(YmTracer2Work, visibleCount) == 0x2c);
STATIC_ASSERT(offsetof(YmTracer2Work, alphaStep) == 0x30);
STATIC_ASSERT(offsetof(VColor, m_color) == 0x8);

static inline void copyPolygonData(YmTracer2Polygon* dst, YmTracer2Polygon* src)
{
    dst->active = src->active;
    pppCopyVector(dst->pos, src->pos);
    pppCopyVector(dst->targetPos, src->targetPos);
    dst->colorR = src->colorR;
    dst->colorG = src->colorG;
    dst->colorB = src->colorB;
    dst->alpha = src->alpha;
}

static inline float* GetTracerWorkValue(int dataValueIndex, int offset)
{
    _pppPObject* object = reinterpret_cast<_pppPObject*>(ppvMng->m_pppPDataVals[dataValueIndex].m_pppPObjLink);
    return reinterpret_cast<float*>(object->m_workArea + offset);
}

static inline YmTracer2DataOffsets* GetYmTracer2DataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<YmTracer2DataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x801035dc
 * PAL Size: 984b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmTracer2(pppYmTracer2* tracer, pppYmTracer2Step* step, _pppCtrlTable* ctrl)
{
    YmTracer2Work* work;
    CMapMesh* mapMesh;
    YmTracer2Polygon* poly;
    VColor* colorData;
    CTexture* texture;
    s32 i;
    s32 dataOffset;
    s32 colorOffset;
    s32 dataValIndex;
    f32 uTop;
    f32 uBottom;
    f32 uvStep;
    int textureIndex[2];

    dataValIndex = step->m_dataValIndex;
    dataOffset = GetYmTracer2DataOffsets(ctrl)->m_workOffset;
    work = (YmTracer2Work*)(tracer->m_workArea + dataOffset);
    colorOffset = GetYmTracer2DataOffsets(ctrl)->m_colorOffset;
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

            if (step->m_tracer.m_useTextureTev == 0) {
                _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
            } else {
                _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
            }

            uvStep = 1.0f / (f32)work->visibleCount;
            GXSetCullMode(GX_CULL_NONE);

            if (work->visibleCount > 1) {
                f32 alphaScale = (f32)colorData->m_color.rgba[3] / 255.0f;

                GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, (work->visibleCount - 1) * 4);

                YmTracer2Polygon* current = poly;
                f32 uvMin = 0.0f;
                f32 uvMax = 1.0f;

                i = 0;
                while (i < (s32)(work->visibleCount - 1)) {
                    YmTracer2Polygon* next = current + 1;

                    uTop = (f32)i * uvStep;
                    uBottom = (f32)(i + 1) * uvStep;

                    if (alphaScale < uvMin) {
                        alphaScale = uvMin;
                    }
                    if (alphaScale > uvMax) {
                        alphaScale = uvMax;
                    }

                    pppPackedColor colorTop = {0};
                    pppPackedColor colorBottom = {0};
                    colorTop.bytes[0] = current->colorR;
                    colorTop.bytes[1] = current->colorG;
                    colorTop.bytes[2] = current->colorB;
                    colorTop.bytes[3] = (u8)(alphaScale * (f32)current->alpha);
                    colorBottom.bytes[0] = next->colorR;
                    colorBottom.bytes[1] = next->colorG;
                    colorBottom.bytes[2] = next->colorB;
                    colorBottom.bytes[3] = (u8)(alphaScale * (f32)next->alpha);

                    GXPosition3f32(current->targetPos.x, current->targetPos.y, current->targetPos.z);
                    GXColor1u32(*(u32*)&colorTop);
                    GXTexCoord2f32(uTop, uvMax);

                    GXPosition3f32(current->pos.x, current->pos.y, current->pos.z);
                    GXColor1u32(*(u32*)&colorTop);
                    GXTexCoord2f32(uTop, uvMin);

                    GXPosition3f32(next->targetPos.x, next->targetPos.y, next->targetPos.z);
                    GXColor1u32(*(u32*)&colorBottom);
                    GXTexCoord2f32(uBottom, uvMax);

                    GXPosition3f32(next->pos.x, next->pos.y, next->pos.z);
                    GXColor1u32(*(u32*)&colorBottom);
                    GXTexCoord2f32(uBottom, uvMin);
                    i++;
                    current++;
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x801039b4
 * PAL Size: 1112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmTracer2(pppYmTracer2* tracer, pppYmTracer2Step* step, _pppCtrlTable* ctrl)
{
    YmTracer2Work* work;
    VColor* colorData;
    YmTracer2Polygon* entries;
    YmTracer2Polygon* entry;
    s32 useFallback;
    float val;
    s16 alpha;
    s32 entryIdx;
    s32 j;
    s32 visibleCount;
    s32 i;
    Mtx frameMtx;
    float frameT;

    if (ppvUserStopPartF != 0) {
        return;
    }

    useFallback = 0;
    work = (YmTracer2Work*)(tracer->m_workArea + GetYmTracer2DataOffsets(ctrl)->m_workOffset);
    colorData = reinterpret_cast<VColor*>(
        tracer->m_workArea + GetYmTracer2DataOffsets(ctrl)->m_colorOffset);

    work->initWork = (step->m_initWork == 0xffffffff)
                         ? gPppDefaultValueBuffer
                         : GetTracerWorkValue(step->m_initWork, step->m_stepValue);

    work->arg3Work = (step->m_arg3 == 0xffffffff)
                         ? gPppDefaultValueBuffer
                         : GetTracerWorkValue(step->m_arg3, step->m_tracer.m_arg3WorkOffset);

    if (work->entries == nullptr) {
        useFallback = 1;
        work->alphaStep = (u16)step->m_tracer.m_entryAlpha / step->m_tracer.m_entryLife;
        work->entries = (YmTracer2Polygon*)pppMemAlloc(
            (u32)step->m_tracer.m_entryCount * sizeof(YmTracer2Polygon), ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppYmTracer2_cpp), 0xAD);

        val = 0.0f;
        entry = work->entries;
        for (j = 0; j < (s32)(u32)step->m_tracer.m_entryCount; j++) {
            entry->active = 0;
            entry->alpha = 0;
            entry->pos.z = val;
            entry->pos.y = val;
            entry->pos.x = val;
            entry->targetPos.z = val;
            entry->targetPos.y = val;
            entry->targetPos.x = val;
            entry++;
        }
    }

    entries = work->entries;
    entries[0].active = 1;
    entry = entries;

    for (i = 0; i < (s32)(step->m_tracer.m_historyFrameCount + 1); i++) {
        j = step->m_tracer.m_entryCount - 2;
        for (; (s32)i <= j; j--) {
            copyPolygonData(entries + (j + 1), entries + j);
        }

        val = work->initWork[0];
        work->pos.x = val;
        entry->pos.x = val;
        val = work->initWork[1];
        work->pos.y = val;
        entry->pos.y = val;
        val = work->initWork[2];
        work->pos.z = val;
        entry->pos.z = val;
        val = work->arg3Work[0];
        work->targetPos.x = val;
        entry->targetPos.x = val;
        val = work->arg3Work[1];
        work->targetPos.y = val;
        entry->targetPos.y = val;
        val = work->arg3Work[2];
        work->targetPos.z = val;
        entry->targetPos.z = val;
        entry->colorR = colorData->m_color.rgba[0];
        entry->colorG = colorData->m_color.rgba[1];
        entry->colorB = colorData->m_color.rgba[2];

        if (i == 0) {
            PSMTXConcat(ppvMng->m_matrix.value, tracer->m_localMatrix.value, frameMtx);
            PSMTXMultVec(frameMtx, &entries[0].pos, &entries[0].pos);
            PSMTXMultVec(frameMtx, &entries[0].targetPos, &entries[0].targetPos);
        } else if (!useFallback) {
            frameT = (-1.0f / (f32)((s32)step->m_tracer.m_historyFrameCount + 1)) * (f32)(s32)i;
            if (GetCharaNodeFrameMatrix(ppvMng, frameT, frameMtx) == 0) {
                useFallback = 1;
            } else {
                PSMTXConcat(frameMtx, tracer->m_localMatrix.value, frameMtx);
                PSMTXMultVec(frameMtx, &entry->pos, &entry->pos);
                PSMTXMultVec(frameMtx, &entry->targetPos, &entry->targetPos);
            }
        }

        entry++;
    }

    if (useFallback) {
        YmTracer2Polygon* pFallback = entries;

        for (entryIdx = 0; entryIdx < (s32)(u32)step->m_tracer.m_entryCount; entryIdx++) {
            pppCopyVector(pFallback->pos, entries->pos);
            pppCopyVector(pFallback->targetPos, entries->targetPos);
            pFallback++;
        }
    }

    entry = entries;
    visibleCount = 0;
    for (entryIdx = 0; entryIdx < (s32)(u32)step->m_tracer.m_entryCount; entryIdx++) {
        alpha = (u16)step->m_tracer.m_entryAlpha - entryIdx * work->alphaStep;
        if ((alpha < 0) || (entry->active == 0)) {
            entry->alpha = 0;
        } else if (entry->active != 0) {
            entry->alpha = (u8)alpha;
            visibleCount++;
        }
        entry++;
    }
    work->visibleCount = (s16)visibleCount;
}


/*
 * --INFO--
 * PAL Address: 0x80103e0c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmTracer2(pppYmTracer2* tracer, _pppCtrlTable* ctrl)
{
    YmTracer2Work* work = (YmTracer2Work*)(tracer->m_workArea + GetYmTracer2DataOffsets(ctrl)->m_workOffset);
    if (work->entries != 0) {
        pppMemFree(work->entries);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80103e44
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmTracer2(pppYmTracer2* tracer, _pppCtrlTable* ctrl)
{
    YmTracer2Work* work = (YmTracer2Work*)(tracer->m_workArea + GetYmTracer2DataOffsets(ctrl)->m_workOffset);

    work->pad2e = 0;
    work->visibleCount = 0;
    work->pad32 = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80103e68
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmTracer2(pppYmTracer2* tracer, _pppCtrlTable* ctrl)
{
    float zero = 0.0f;
    YmTracer2Work* work = (YmTracer2Work*)(tracer->m_workArea + GetYmTracer2DataOffsets(ctrl)->m_workOffset);

    work->entries = 0;
    work->arg3Work = 0;
    work->initWork = 0;
    work->visibleCount = 0;

    work->pad0 = zero;
    work->pos.z = zero;
    work->pos.y = zero;
    work->pos.x = zero;
    work->pad1c = zero;
    work->targetPos.z = zero;
    work->targetPos.y = zero;
    work->targetPos.x = zero;

    work->pad2e = 0;
    work->alphaStep = 0;
    work->pad32 = 0;
}
