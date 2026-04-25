#include "ffcc/pppYmTracer.h"
#include "ffcc/mapmesh.h"
#include "ffcc/pppPart.h"
#include "ffcc/textureman.h"
extern "C" {
extern int gPppCalcDisabled;
extern u8 gPppDefaultValueBuffer[];
}
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern f32 FLOAT_803306e8;
extern f32 FLOAT_803306ec;
extern u32 DAT_803306e0;
extern u32 DAT_803306e4;

extern "C" {
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);

void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
    unsigned char);
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh*, CMaterialSet*, int&);
void SetVtxFmt_POS_CLR_TEX__5CUtilFv(void*);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
}

static const char s_pppYmTracer_cpp_801d9ce0[] = "pppYmTracer.cpp";

struct TracerDataValue {
    u32 unk0;
    u8* workBase;
    u32 unk8;
    u32 unkC;
};

struct TracerMngRaw {
    u8 _pad[0xD4];
    TracerDataValue* dataValues;
};

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

static inline void copyPolygonData(TRACE_POLYGON* dst, const TRACE_POLYGON* src)
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
    colorOffset = param_3->m_serializedDataOffsets[1];
    work = (TracerWork*)(pppYmTracer->m_serializedData + dataOffset);
    colorData = pppYmTracer->m_serializedData + colorOffset;
    poly = work->entries;
    mapMesh = pppEnvStPtr->m_mapMeshPtr[dataValIndex];

    if (dataValIndex != 0xFFFF) {
        pppSetBlendMode(param_2->m_payload[10]);
        pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
            colorData + 8, (void*)&ppvCameraMatrix02, FLOAT_803306e8,
            param_2->m_payload[0xC], param_2->m_payload[0xB], param_2->m_payload[10], 0, 1, 1, 0);
        SetVtxFmt_POS_CLR_TEX__5CUtilFv(&gUtil);

        textureIndex[0] = 0;
        texture = (CTexture*)GetTexture__8CMapMeshFP12CMaterialSetRi(mapMesh, pppEnvStPtr->m_materialSetPtr,
                                                                     textureIndex[0]);
        if (texture != 0) {
            GXLoadTexObj(&texture->m_texObj, GX_TEXMAP0);
            GXSetNumChans(1);
            GXSetNumTexGens(1);
            GXSetNumTevStages(1);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
            _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);

            u32 format = (u32)texture->m_format;
            if ((format == 8) || (format == 9)) {
                SetUpPaletteEnv(texture);
            }

            uvStep = FLOAT_803306ec / (f32)work->count;
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
                    colorTop.value = DAT_803306e0;
                    colorBottom.value = DAT_803306e4;
                    colorTop.bytes[3] = poly->alpha;
                    colorBottom.bytes[3] = next->alpha;

                    GXBegin((GXPrimitive)0x98, GX_VTXFMT7, 4);
                    GXPosition3f32(poly->to.x, poly->to.y, poly->to.z);
                    GXColor1u32(colorTop.value);
                    GXTexCoord2f32(uTop, FLOAT_803306ec);

                    GXPosition3f32(poly->from.x, poly->from.y, poly->from.z);
                    GXColor1u32(colorTop.value);
                    GXTexCoord2f32(uTop, FLOAT_803306e8);

                    GXPosition3f32(next->to.x, next->to.y, next->to.z);
                    GXColor1u32(colorBottom.value);
                    GXTexCoord2f32(uBottom, FLOAT_803306ec);

                    GXPosition3f32(next->from.x, next->from.y, next->from.z);
                    GXColor1u32(colorBottom.value);
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
    TracerMngRaw* mng;
    TracerWork* work;
    TRACE_POLYGON* entries;
    TRACE_POLYGON* entry;
    TRACE_POLYGON* source;
    TRACE_POLYGON* dest;
    TRACE_POLYGON* poly;
    float* valuePtr;
    f32 fVar3;
    u8 alpha;
    u8 decay;
    s32 i;

    if (gPppCalcDisabled != 0) {
        return;
    }

    work = (TracerWork*)(pppYmTracer->m_serializedData + *param_3->m_serializedDataOffsets);
    entries = work->entries;
    if (entries == 0) {
        work->entries = (TRACE_POLYGON*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (u32)*(u16*)(param_2->m_payload + 4) * sizeof(TRACE_POLYGON), pppEnvStPtr->m_stagePtr,
            const_cast<char*>(s_pppYmTracer_cpp_801d9ce0), 0xEB);
        fVar3 = FLOAT_803306e8;
        entry = work->entries;
        for (i = 0; i < (s32)(u32)*(u16*)(param_2->m_payload + 4); i++) {
            entry->life = -1;
            entry->alpha = param_2->m_payload[8];
            entry->decay = (u8)((u16)param_2->m_payload[8] / *(u16*)(param_2->m_payload + 6));
            entry->from.z = fVar3;
            entry->from.y = fVar3;
            entry->from.x = fVar3;
            entry->to.z = fVar3;
            entry->to.y = fVar3;
            entry->to.x = fVar3;
            entry++;
        }
    }

    if (param_2->m_graphId == pppYmTracer->m_graphId) {
        if (param_2->m_initWOrk == -1) {
            valuePtr = reinterpret_cast<float*>(gPppDefaultValueBuffer);
        } else {
            mng = reinterpret_cast<TracerMngRaw*>(pppMngStPtr);
            valuePtr = reinterpret_cast<float*>(mng->dataValues[param_2->m_initWOrk].workBase + 0x80 +
                                                param_2->m_stepValue);
        }
        work->initWork = valuePtr;

        if (param_2->m_arg3 == -1) {
            valuePtr = reinterpret_cast<float*>(gPppDefaultValueBuffer);
        } else {
            mng = reinterpret_cast<TracerMngRaw*>(pppMngStPtr);
            valuePtr = reinterpret_cast<float*>(mng->dataValues[param_2->m_arg3].workBase + 0x80 +
                                                *(s32*)param_2->m_payload);
        }
        work->arg3Work = valuePtr;
    }

    entries = work->entries;
    if (work->count + 1 < *(u16*)(param_2->m_payload + 4)) {
        source = entries + (*(u16*)(param_2->m_payload + 4) - 2);
        for (i = *(u16*)(param_2->m_payload + 4) - 2; i >= 0; i--) {
            dest = source + 1;
            copyPolygonData(dest, source);
            source--;
        }

        entries[0].life = -1;
        entries[0].alpha = param_2->m_payload[8];
        entries[0].decay = (u8)((u16)param_2->m_payload[8] / *(u16*)(param_2->m_payload + 6));
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

        entries[0].life = *(u16*)(param_2->m_payload + 6);
        entries[0].alpha = param_2->m_payload[8];

        {
            pppFMATRIX result;

            pppMulMatrix(result, pppMngStPtr->m_matrix, pppYmTracer->m_localMatrix);
            PSMTXMultVec(result.value, &entries[0].from, &entries[0].from);
            PSMTXMultVec(result.value, &entries[0].to, &entries[0].to);
        }

        work->count++;

        if (work->count > 3) {
            Vec splineFrom[4];
            Vec splineTo[4];
            s16 splineCount = 0;
            f32 stepScale = FLOAT_803306ec / (f32)(param_2->m_payload[9] + 1);

            for (i = 0; i < (s32)(u32)param_2->m_payload[9]; i++) {
                f32 t = stepScale * (f32)(i + 1);

                gUtil.GetSplinePos(splineFrom[(param_2->m_payload[9] - 1) - i], entries[3].to, entries[2].to,
                                          entries[1].to, entries[0].from, t, FLOAT_803306ec);
                gUtil.GetSplinePos(splineTo[(param_2->m_payload[9] - 1) - i], entries[4].from, entries[3].from,
                                          entries[2].from, entries[0].to, t, FLOAT_803306ec);

                splineCount++;
                work->count++;
                if (*(u16*)(param_2->m_payload + 4) <= work->count + 1) {
                    break;
                }
            }

            for (i = 0; i < splineCount; i++) {
                source = entries + (*(u16*)(param_2->m_payload + 4) - 2);
                for (s32 j = *(u16*)(param_2->m_payload + 4) - 2; j > 1; j--) {
                    dest = source + 1;
                    copyPolygonData(dest, source);
                    source--;
                }
            }

            for (i = 0; i < splineCount; i++) {
                s32 idx = i + 2;
                entries[idx].alpha = (u8)(param_2->m_payload[8] - (u8)(idx * entries[0].decay));
                pppCopyVector(entries[idx].from, splineFrom[i]);
                pppCopyVector(entries[idx].to, splineTo[i]);
            }
        }
    }

    poly = work->entries;
    for (i = 0; i < (s32)(u32)work->count; i++) {
        if (poly->life > 0) {
            alpha = poly->alpha;
            decay = poly->decay;
            if ((s32)((u32)alpha - (u32)decay) < 1) {
                poly->alpha = 0;
            } else {
                poly->alpha = alpha - decay;
            }

            poly->life--;
            if (poly->life < 1) {
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
    TracerWork* work = (TracerWork*)(pppYmTracer->m_serializedData + *param_2->m_serializedDataOffsets);
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

    work = (TracerWork*)(pppYmTracer->m_serializedData + *param_2->m_serializedDataOffsets);
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
    work = (TracerWork*)(pppYmTracer->m_serializedData + *param_2->m_serializedDataOffsets);

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
