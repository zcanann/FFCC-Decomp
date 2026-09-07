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

static const float kYmTracer2UvMin = 0.0f;
static const float kYmTracer2UvMax = 1.0f;

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
STATIC_ASSERT(offsetof(YmTracer2ColorBlock, color) == 0x8);

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
#pragma opt_common_subs off
void pppRenderYmTracer2(pppYmTracer2* pppYmTracer2, pppYmTracer2Step* param_2, _pppCtrlTable* param_3)
{
    YmTracer2Work* work;
    CMapMesh* mapMesh;
    YmTracer2Polygon* poly;
    YmTracer2ColorBlock* colorData;
    CTexture* texture;
    s32 i;
    s32 dataOffset;
    s32 colorOffset;
    s32 dataValIndex;
    f32 uTop;
    f32 uBottom;
    f32 uvStep;
    int textureIndex[2];

    dataValIndex = param_2->m_dataValIndex;
    dataOffset = GetYmTracer2DataOffsets(param_3)->m_workOffset;
    work = (YmTracer2Work*)(pppYmTracer2->m_workArea + dataOffset);
    colorOffset = GetYmTracer2DataOffsets(param_3)->m_colorOffset;
    poly = work->entries;
    mapMesh = ppvEnv->m_mapMeshPtr[dataValIndex];
    colorData = reinterpret_cast<YmTracer2ColorBlock*>(pppYmTracer2->m_workArea + colorOffset);

    if (dataValIndex != 0xFFFF) {
        pppSetBlendMode(param_2->m_tracer.m_blendMode);
        pppSetDrawEnv(
            &colorData->color, reinterpret_cast<pppFMATRIX*>(&ppvCameraMatrix),
            kYmTracer2UvMin,
            param_2->m_tracer.m_drawEnvColor1, param_2->m_tracer.m_drawEnvColor0,
            param_2->m_tracer.m_blendMode, 0, 1, 1, 0);
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
            if ((format == 8) || (format == 9)) {
                SetUpPaletteEnv(texture);
            }

            if (param_2->m_tracer.m_useTextureTev == 0) {
                _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
            } else {
                _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
            }

            uvStep = kYmTracer2UvMax / (f32)work->visibleCount;
            GXSetCullMode(GX_CULL_NONE);

            if (work->visibleCount > 1) {
                f32 alphaScale = (f32)colorData->color.rgba[3] / 255.0f;

                GXBegin((GXPrimitive)0x98, GX_VTXFMT7, (work->visibleCount - 1) * 4);

                YmTracer2Polygon* current = poly;
                f32 uvMin = kYmTracer2UvMin;
                f32 uvMax = kYmTracer2UvMax;

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
#pragma opt_common_subs on
void pppFrameYmTracer2(pppYmTracer2* pppYmTracer2, pppYmTracer2Step* param_2, _pppCtrlTable* param_3)
{
    YmTracer2Work* work;
    YmTracer2ColorBlock* colorData;
    YmTracer2Polygon* entries;
    YmTracer2Polygon* entry;
    s32 useFallback;
    float fVar2;
    s16 alpha;
    s32 iVar4;
    float* pfVar6;
    s32 iVar8;
    s32 visibleCount;
    s32 i;
    Mtx MStack_78;
    float frameT;

    if (ppvUserStopPartF != 0) {
        return;
    }

    useFallback = 0;
    work = (YmTracer2Work*)(pppYmTracer2->m_workArea + GetYmTracer2DataOffsets(param_3)->m_workOffset);
    colorData = reinterpret_cast<YmTracer2ColorBlock*>(
        pppYmTracer2->m_workArea + GetYmTracer2DataOffsets(param_3)->m_colorOffset);

    work->initWork = (param_2->m_initWork == 0xffffffff)
                         ? gPppDefaultValueBuffer
                         : GetTracerWorkValue(param_2->m_initWork, param_2->m_stepValue);

    work->arg3Work = (param_2->m_arg3 == 0xffffffff)
                         ? gPppDefaultValueBuffer
                         : GetTracerWorkValue(param_2->m_arg3, param_2->m_tracer.m_arg3WorkOffset);

    if (work->entries == nullptr) {
        useFallback = 1;
        work->alphaStep = (u16)param_2->m_tracer.m_entryAlpha / param_2->m_tracer.m_entryLife;
        work->entries = (YmTracer2Polygon*)pppMemAlloc(
            (u32)param_2->m_tracer.m_entryCount * sizeof(YmTracer2Polygon), ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppYmTracer2_cpp), 0xAD);

        fVar2 = kYmTracer2UvMin;
        entry = work->entries;
        for (iVar8 = 0; iVar8 < (s32)(u32)param_2->m_tracer.m_entryCount; iVar8++) {
            entry->active = 0;
            entry->alpha = 0;
            entry->pos.z = fVar2;
            entry->pos.y = fVar2;
            entry->pos.x = fVar2;
            entry->targetPos.z = fVar2;
            entry->targetPos.y = fVar2;
            entry->targetPos.x = fVar2;
            entry++;
        }
    }

    entries = work->entries;
    entries[0].active = 1;
    entry = entries;

    for (i = 0; i < (s32)(param_2->m_tracer.m_historyFrameCount + 1); i++) {
        iVar8 = param_2->m_tracer.m_entryCount - 2;
        for (; (s32)i <= iVar8; iVar8--) {
            copyPolygonData(entries + (iVar8 + 1), entries + iVar8);
        }

        fVar2 = work->initWork[0];
        work->pos.x = fVar2;
        entry->pos.x = fVar2;
        fVar2 = work->initWork[1];
        work->pos.y = fVar2;
        entry->pos.y = fVar2;
        fVar2 = work->initWork[2];
        work->pos.z = fVar2;
        entry->pos.z = fVar2;
        fVar2 = work->arg3Work[0];
        work->targetPos.x = fVar2;
        entry->targetPos.x = fVar2;
        fVar2 = work->arg3Work[1];
        work->targetPos.y = fVar2;
        entry->targetPos.y = fVar2;
        fVar2 = work->arg3Work[2];
        work->targetPos.z = fVar2;
        entry->targetPos.z = fVar2;
        entry->colorR = colorData->color.rgba[0];
        entry->colorG = colorData->color.rgba[1];
        entry->colorB = colorData->color.rgba[2];

        if (i == 0) {
            PSMTXConcat(ppvMng->m_matrix.value, pppYmTracer2->m_localMatrix.value, MStack_78);
            PSMTXMultVec(MStack_78, &entries[0].pos, &entries[0].pos);
            PSMTXMultVec(MStack_78, &entries[0].targetPos, &entries[0].targetPos);
        } else if (!useFallback) {
            frameT = (-1.0f / (f32)((s32)param_2->m_tracer.m_historyFrameCount + 1)) * (f32)(s32)i;
            if (GetCharaNodeFrameMatrix(ppvMng, frameT, MStack_78) == 0) {
                useFallback = 1;
            } else {
                PSMTXConcat(MStack_78, pppYmTracer2->m_localMatrix.value, MStack_78);
                PSMTXMultVec(MStack_78, &entry->pos, &entry->pos);
                PSMTXMultVec(MStack_78, &entry->targetPos, &entry->targetPos);
            }
        }

        entry++;
    }

    if (useFallback) {
        YmTracer2Polygon* pFallback = entries;

        for (iVar4 = 0; iVar4 < (s32)(u32)param_2->m_tracer.m_entryCount; iVar4++) {
            pppCopyVector(pFallback->pos, entries->pos);
            pppCopyVector(pFallback->targetPos, entries->targetPos);
            pFallback++;
        }
    }

    entry = entries;
    visibleCount = 0;
    for (iVar4 = 0; iVar4 < (s32)(u32)param_2->m_tracer.m_entryCount; iVar4++) {
        alpha = (u16)param_2->m_tracer.m_entryAlpha - iVar4 * work->alphaStep;
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
void pppDestructYmTracer2(pppYmTracer2* pppYmTracer2, _pppCtrlTable* param_2)
{
    YmTracer2Work* work = (YmTracer2Work*)(pppYmTracer2->m_workArea + GetYmTracer2DataOffsets(param_2)->m_workOffset);
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
void pppConstruct2YmTracer2(pppYmTracer2* pppYmTracer2, _pppCtrlTable* param_2)
{
    YmTracer2Work* work = (YmTracer2Work*)(pppYmTracer2->m_workArea + GetYmTracer2DataOffsets(param_2)->m_workOffset);

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
void pppConstructYmTracer2(pppYmTracer2* pppYmTracer2, _pppCtrlTable* param_2)
{
    float fVar1 = kYmTracer2UvMin;
    YmTracer2Work* work = (YmTracer2Work*)(pppYmTracer2->m_workArea + GetYmTracer2DataOffsets(param_2)->m_workOffset);

    work->entries = 0;
    work->arg3Work = 0;
    work->initWork = 0;
    work->visibleCount = 0;

    work->pad0 = fVar1;
    work->pos.z = fVar1;
    work->pos.y = fVar1;
    work->pos.x = fVar1;
    work->pad1c = fVar1;
    work->targetPos.z = fVar1;
    work->targetPos.y = fVar1;
    work->targetPos.x = fVar1;

    work->pad2e = 0;
    work->alphaStep = 0;
    work->pad32 = 0;
}
