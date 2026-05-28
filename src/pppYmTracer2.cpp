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

extern const float FLOAT_80331840;
extern const float FLOAT_80331844;

extern "C" const char s_pppYmTracer2_cpp[] = "pppYmTracer2.cpp";

struct TRACE_POLYGON {
    Vec pos;
    float pad0;
    Vec targetPos;
    u8 colorR;
    u8 colorG;
    u8 colorB;
    u8 alpha;
    u8 active;
    u8 pad1[7];
};
STATIC_ASSERT(sizeof(TRACE_POLYGON) == 0x28);

struct TracerWork {
    Vec pos;
    float pad0;
    Vec targetPos;
    float pad1c;
    float* initWork;
    float* arg3Work;
    TRACE_POLYGON* entries;
    u16 visibleCount;
    u16 pad2e;
    s16 alphaStep;
    u16 pad32;
};

union PackedColor {
    u32 value;
    u8 bytes[4];
};

extern "C" PackedColor g_pppYmTracer2_1;
extern "C" PackedColor g_pppYmTracer2_2;

static inline void copyPolygonData(TRACE_POLYGON* dst, TRACE_POLYGON* src)
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

/*
 * --INFO--
 * PAL Address: 0x801035dc
 * PAL Size: 984b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmTracer2(pppYmTracer2* pppYmTracer2, pppYmTracer2UnkB* param_2, pppYmTracer2UnkC* param_3)
{
    TracerWork* work;
    CMapMesh* mapMesh;
    TRACE_POLYGON* poly;
    u8* colorData;
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
    work = (TracerWork*)(pppYmTracer2->m_object.m_workArea + dataOffset);
    colorOffset = param_3->m_serializedDataOffsets[1];
    poly = work->entries;
    mapMesh = ppvEnv->m_mapMeshPtr[dataValIndex];
    colorData = pppYmTracer2->m_object.m_workArea + colorOffset;

    if (dataValIndex != 0xFFFF) {
        pppSetBlendMode(param_2->m_tracer.m_blendMode);
        pppSetDrawEnv(
            reinterpret_cast<pppCVECTOR*>(colorData + 8), reinterpret_cast<pppFMATRIX*>(&ppvCameraMatrix),
            FLOAT_80331840,
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

            uvStep = FLOAT_80331844 / (f32)work->visibleCount;
            GXSetCullMode(GX_CULL_NONE);

            if (work->visibleCount > 1) {
                f32 alphaScale = (f32)colorData[0x0B] / 255.0f;

                GXBegin((GXPrimitive)0x98, GX_VTXFMT7, (work->visibleCount - 1) * 4);

                TRACE_POLYGON* current = poly;

                i = 0;
                while (i < (s32)(work->visibleCount - 1)) {
                    TRACE_POLYGON* next = current + 1;

                    uTop = (f32)i * uvStep;
                    uBottom = (f32)(i + 1) * uvStep;

                    if (alphaScale < 0.0f) {
                        alphaScale = 0.0f;
                    }
                    if (alphaScale > 1.0f) {
                        alphaScale = 1.0f;
                    }

                    colorTop = g_pppYmTracer2_1;
                    colorBottom = g_pppYmTracer2_2;
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
                    GXTexCoord2f32(uTop, FLOAT_80331844);

                    GXPosition3f32(current->pos.x, current->pos.y, current->pos.z);
                    GXColor1u32(*(u32*)&colorTop);
                    GXTexCoord2f32(uTop, FLOAT_80331840);

                    GXPosition3f32(next->targetPos.x, next->targetPos.y, next->targetPos.z);
                    GXColor1u32(*(u32*)&colorBottom);
                    GXTexCoord2f32(uBottom, FLOAT_80331844);

                    GXPosition3f32(next->pos.x, next->pos.y, next->pos.z);
                    GXColor1u32(*(u32*)&colorBottom);
                    GXTexCoord2f32(uBottom, FLOAT_80331840);
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
void pppFrameYmTracer2(pppYmTracer2* pppYmTracer2, pppYmTracer2UnkB* param_2, pppYmTracer2UnkC* param_3)
{
    TracerWork* work;
    u8* colorData;
    TRACE_POLYGON* entries;
    TRACE_POLYGON* entry;
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

    if (gPppCalcDisabled != 0) {
        return;
    }

    useFallback = 0;
    work = (TracerWork*)(pppYmTracer2->m_object.m_workArea + *param_3->m_serializedDataOffsets);
    colorData = pppYmTracer2->m_object.m_workArea + param_3->m_serializedDataOffsets[1];

    work->initWork = (param_2->m_initWork == 0xffffffff)
                         ? gPppDefaultValueBuffer
                         : GetTracerWorkValue(param_2->m_initWork, param_2->m_stepValue);

    work->arg3Work = (param_2->m_arg3 == 0xffffffff)
                         ? gPppDefaultValueBuffer
                         : GetTracerWorkValue(param_2->m_arg3, param_2->m_tracer.m_arg3WorkOffset);

    if (work->entries == nullptr) {
        useFallback = 1;
        work->alphaStep = (u16)param_2->m_tracer.m_entryAlpha / param_2->m_tracer.m_entryLife;
        work->entries = (TRACE_POLYGON*)pppMemAlloc(
            (u32)param_2->m_tracer.m_entryCount * sizeof(TRACE_POLYGON), ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppYmTracer2_cpp), 0xAD);

        fVar2 = FLOAT_80331840;
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
        entry->colorR = colorData[8];
        entry->colorG = colorData[9];
        entry->colorB = colorData[10];

        if (i == 0) {
            PSMTXConcat(ppvMng->m_matrix.value, pppYmTracer2->m_object.m_localMatrix.value, MStack_78);
            PSMTXMultVec(MStack_78, &entries[0].pos, &entries[0].pos);
            PSMTXMultVec(MStack_78, &entries[0].targetPos, &entries[0].targetPos);
        } else if (!useFallback) {
            frameT = (-1.0f / (f32)((s32)param_2->m_tracer.m_historyFrameCount + 1)) * (f32)(s32)i;
            if (GetCharaNodeFrameMatrix(ppvMng, frameT, MStack_78) == 0) {
                useFallback = 1;
            } else {
                PSMTXConcat(MStack_78, pppYmTracer2->m_object.m_localMatrix.value, MStack_78);
                PSMTXMultVec(MStack_78, &entry->pos, &entry->pos);
                PSMTXMultVec(MStack_78, &entry->targetPos, &entry->targetPos);
            }
        }

        entry++;
    }

    if (useFallback) {
        TRACE_POLYGON* pFallback = entries;

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
void pppDestructYmTracer2(pppYmTracer2* pppYmTracer2, pppYmTracer2UnkC* param_2)
{
    TracerWork* work = (TracerWork*)(pppYmTracer2->m_object.m_workArea + *param_2->m_serializedDataOffsets);
    if (work->entries != 0) {
        pppHeapUseRate((CMemory::CStage*)work->entries);
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
void pppConstruct2YmTracer2(pppYmTracer2* pppYmTracer2, pppYmTracer2UnkC* param_2)
{
    TracerWork* work = (TracerWork*)(pppYmTracer2->m_object.m_workArea + *param_2->m_serializedDataOffsets);

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
void pppConstructYmTracer2(pppYmTracer2* pppYmTracer2, pppYmTracer2UnkC* param_2)
{
    float fVar1 = FLOAT_80331840;
    TracerWork* work = (TracerWork*)(pppYmTracer2->m_object.m_workArea + *param_2->m_serializedDataOffsets);

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

extern const float FLOAT_80331864 = 0.0f;
extern const char sTHPMagic[4] = "THP";
extern const float kTHPSimpleDefaultVolume = 127.0f;
