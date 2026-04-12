#include "ffcc/pppYmTracer2.h"
#include "ffcc/mapmesh.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/textureman.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/symbols_shared.h"
#include "ffcc/util.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" int GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f(float, _pppMngSt*, Mtx);
extern "C" void pppSetBlendMode(unsigned char);
extern "C" void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
    unsigned char);
extern "C" int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh*, CMaterialSet*, int&);
extern "C" void SetVtxFmt_POS_CLR_TEX__5CUtilFv(void*);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);

extern float FLOAT_80331840;
extern float FLOAT_80331844;
extern float FLOAT_80331848;
extern float FLOAT_80331860;
extern double DOUBLE_80331850;
extern double DOUBLE_80331858;

static char s_pppYmTracer2_cpp_801dc4b8[] = "pppYmTracer2.cpp";

struct TRACE_POLYGON {
    Vec pos;
    float pad0;
    Vec targetPos;
    u8 color[4];
    u8 active;
    u8 pad1[7];
};

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
    u16 alphaStep;
    u16 pad32;
};

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

union PackedColor {
    u32 value;
    u8 bytes[4];
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void initTracePolygon(pppYmTracer2*, TRACE_POLYGON& poly)
{
    poly.pos.x = FLOAT_80331840;
    poly.pos.y = FLOAT_80331840;
    poly.pos.z = FLOAT_80331840;
    poly.targetPos.x = FLOAT_80331840;
    poly.targetPos.y = FLOAT_80331840;
    poly.targetPos.z = FLOAT_80331840;
    poly.color[0] = 0;
    poly.color[1] = 0;
    poly.color[2] = 0;
    poly.color[3] = 0;
    poly.active = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void copyPolygonData(TRACE_POLYGON* dst, TRACE_POLYGON* src)
{
    dst->active = src->active;
    pppCopyVector(dst->pos, src->pos);
    pppCopyVector(dst->targetPos, src->targetPos);
    dst->color[0] = src->color[0];
    dst->color[1] = src->color[1];
    dst->color[2] = src->color[2];
    dst->color[3] = src->color[3];
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
	unsigned char* puVar2 = (unsigned char*)pppYmTracer2 + 0x80 + *param_2->m_serializedDataOffsets;
	
	*(u32*)(puVar2 + 0x28) = 0;
	*(u32*)(puVar2 + 0x24) = 0;
	*(u32*)(puVar2 + 0x20) = 0;
	*(u16*)(puVar2 + 0x2c) = 0;
	
	*(float*)(puVar2 + 0xc) = fVar1;
	*(float*)(puVar2 + 8) = fVar1;
	*(float*)(puVar2 + 4) = fVar1;
	*(float*)puVar2 = fVar1;
	*(float*)(puVar2 + 0x1c) = fVar1;
	*(float*)(puVar2 + 0x18) = fVar1;
	*(float*)(puVar2 + 0x14) = fVar1;
	*(float*)(puVar2 + 0x10) = fVar1;
	
	*(u16*)(puVar2 + 0x2e) = 0;
	*(u16*)(puVar2 + 0x30) = 0;
	*(u16*)(puVar2 + 0x32) = 0;
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
	unsigned char* iVar1 = (unsigned char*)pppYmTracer2 + 0x80 + *param_2->m_serializedDataOffsets;
	
	*(short*)(iVar1 + 0x2e) = 0;
	*(short*)(iVar1 + 0x2c) = 0;
	*(short*)(iVar1 + 0x32) = 0;
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
	void** memPtr = (void**)((unsigned char*)pppYmTracer2 + 0x80 + *param_2->m_serializedDataOffsets + 0x28);
	if (*memPtr != 0) {
		pppHeapUseRate((CMemory::CStage*)*memPtr);
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
    bool useFallback;
    float fVar2;
    s16 alpha;
    u8* colorData;
    s32 iVar4;
    float* pfVar6;
    s32 iVar8;
    s16 visibleCount;
    u32 i;
    TRACE_POLYGON* entries;
    TRACE_POLYGON* entry;
    TracerWork* work;
    Vec local_a8;
    Vec local_9c;
    Vec local_90;
    Vec local_84;
    Mtx MStack_78;
    float frameT;

    if (gPppCalcDisabled != 0) {
        return;
    }

    useFallback = false;
    colorData = (u8*)pppYmTracer2 + 0x80 + param_3->m_serializedDataOffsets[1];
    work = (TracerWork*)((u8*)pppYmTracer2 + 0x80 + *param_3->m_serializedDataOffsets);

    if (param_2->m_initWOrk == 0xffffffff) {
        pfVar6 = reinterpret_cast<float*>(gPppDefaultValueBuffer);
    } else {
        pfVar6 = reinterpret_cast<float*>(
            reinterpret_cast<TracerMngRaw*>(pppMngStPtr)->dataValues[param_2->m_initWOrk].workBase + 0x80 +
            param_2->m_stepValue);
    }
    work->initWork = pfVar6;

    if (param_2->m_arg3 == 0xffffffff) {
        pfVar6 = reinterpret_cast<float*>(gPppDefaultValueBuffer);
    } else {
        pfVar6 = reinterpret_cast<float*>(
            reinterpret_cast<TracerMngRaw*>(pppMngStPtr)->dataValues[param_2->m_arg3].workBase + 0x80 +
            *(s32*)param_2->m_payload);
    }
    work->arg3Work = pfVar6;

    if (work->entries == nullptr) {
        useFallback = true;
        work->alphaStep = (u16)param_2->m_payload[8] / *(u16*)(param_2->m_payload + 6);
        work->entries = (TRACE_POLYGON*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (u32)*(u16*)(param_2->m_payload + 4) * 0x28, pppEnvStPtr->m_stagePtr, s_pppYmTracer2_cpp_801dc4b8, 0xAD);

        fVar2 = FLOAT_80331840;
        pfVar6 = (float*)work->entries;
        for (iVar8 = 0; iVar8 < (s32)(u32)*(u16*)(param_2->m_payload + 4); iVar8++) {
            *(u8*)(pfVar6 + 8) = 0;
            *(u8*)((u8*)pfVar6 + 0x1f) = 0;
            pfVar6[2] = fVar2;
            pfVar6[1] = fVar2;
            pfVar6[0] = fVar2;
            pfVar6[6] = fVar2;
            pfVar6[5] = fVar2;
            pfVar6[4] = fVar2;
            pfVar6 += 10;
        }
    }

    entries = work->entries;
    entries[0].active = 1;
    entry = entries;

    for (i = 0; (s32)i < (s32)(param_2->m_payload[9] + 1); i++) {
        iVar8 = *(u16*)(param_2->m_payload + 4) - 2;
        pfVar6 = (float*)(entries + iVar8);

        for (; (s32)i <= iVar8; iVar8--) {
            copyPolygonData(entries + (iVar8 + 1), entries + iVar8);
            pfVar6 -= 10;
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
        entry->color[0] = colorData[8];
        entry->color[1] = colorData[9];
        entry->color[2] = colorData[10];

        if (i == 0) {
            PSMTXConcat(pppMngStPtr->m_matrix.value, ((_pppPObject*)pppYmTracer2)->m_localMatrix.value, MStack_78);
            PSMTXMultVec(MStack_78, &entries[0].pos, &entries[0].pos);
            PSMTXMultVec(MStack_78, &entries[0].targetPos, &entries[0].targetPos);
        } else if (!useFallback) {
            frameT = (FLOAT_80331860 / (f32)((s32)param_2->m_payload[9] + 1)) * (f32)(s32)i;
            if (GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f(frameT, pppMngStPtr, MStack_78) == 0) {
                useFallback = true;
            } else {
                PSMTXConcat(MStack_78, ((_pppPObject*)pppYmTracer2)->m_localMatrix.value, MStack_78);
                PSMTXMultVec(MStack_78, &entry->pos, &entry->pos);
                PSMTXMultVec(MStack_78, &entry->targetPos, &entry->targetPos);
            }
        }

        entry++;
    }

    if (useFallback) {
        TRACE_POLYGON* pFallback = entries;

        for (iVar4 = 0; iVar4 < (s32)(u32)*(u16*)(param_2->m_payload + 4); iVar4++) {
            local_84.x = entries->pos.x;
            local_84.y = entries->pos.y;
            local_84.z = entries->pos.z;
            pppCopyVector(pFallback->pos, local_84);
            local_90.x = entries->targetPos.x;
            local_90.y = entries->targetPos.y;
            local_90.z = entries->targetPos.z;
            pppCopyVector(pFallback->targetPos, local_90);
            pFallback++;
        }
    }

    visibleCount = 0;
    for (iVar4 = 0; iVar4 < (s32)(u32)*(u16*)(param_2->m_payload + 4); iVar4++) {
        alpha = (u16)param_2->m_payload[8] - (s16)iVar4 * work->alphaStep;
        if ((alpha < 0) || (entries->active == 0)) {
            entries->color[3] = 0;
        } else if (entries->active != 0) {
            entries->color[3] = (u8)alpha;
            visibleCount++;
        }
        entries++;
    }
    work->visibleCount = visibleCount;
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
    u8* colorData;
    TracerWork* work;
    TRACE_POLYGON* poly;
    CTexture* texture;
    s32 dataOffset;
    s32 colorOffset;
    s32 dataValIndex;
    CMapMesh* mapMesh;
    PackedColor colorTop;
    PackedColor colorBottom;
    u32 i;
    f32 uTop;
    f32 uBottom;
    f32 uvStep;
    int textureIndex[2];

    dataOffset = *param_3->m_serializedDataOffsets;
    colorOffset = param_3->m_serializedDataOffsets[1];
    work = (TracerWork*)((u8*)pppYmTracer2 + 0x80 + dataOffset);
    colorData = (u8*)pppYmTracer2 + 0x80 + colorOffset;
    poly = work->entries;
    dataValIndex = param_2->m_dataValIndex;
    mapMesh = ((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[dataValIndex];

    if (dataValIndex != 0xFFFF) {
        pppSetBlendMode(param_2->m_payload[10]);
        pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
            (void*)(colorData + 8), (void*)&ppvCameraMatrix02, FLOAT_80331840,
            param_2->m_payload[0xC], param_2->m_payload[0xB], param_2->m_payload[10], 0, 1, 1, 0);
        SetVtxFmt_POS_CLR_TEX__5CUtilFv(&gUtil);

        textureIndex[0] = 0;
        texture = (CTexture*)GetTexture__8CMapMeshFP12CMaterialSetRi(mapMesh, pppEnvStPtr->m_materialSetPtr, textureIndex[0]);
        if (texture != nullptr) {
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

            if (param_2->m_payload[0xD] == 0) {
                _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
            } else {
                _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
            }

            uvStep = FLOAT_80331844 / (f32)((f64)work->visibleCount - DOUBLE_80331850);
            GXSetCullMode(GX_CULL_NONE);

            if (work->visibleCount > 1) {
                f64 alphaScale = (f32)colorData[0x0B] / FLOAT_80331848;

                GXBegin((GXPrimitive)0x98, GX_VTXFMT7, (work->visibleCount - 1) * 4);

                for (i = 0; i < (u32)(work->visibleCount - 1); i++) {
                    TRACE_POLYGON* next = poly + 1;

                    uTop = (f32)((f64)(s32)i * (f64)uvStep);
                    uBottom = (f32)((f64)(s32)(i + 1) * (f64)uvStep);

                    if (alphaScale < (f64)FLOAT_80331840) {
                        alphaScale = (f64)FLOAT_80331840;
                    }
                    if ((f64)FLOAT_80331844 < alphaScale) {
                        alphaScale = (f64)FLOAT_80331844;
                    }

                    colorTop.value = 0;
                    colorBottom.value = 0;
                    colorTop.bytes[0] = poly->color[0];
                    colorTop.bytes[1] = poly->color[1];
                    colorTop.bytes[2] = poly->color[2];
                    colorTop.bytes[3] = (u8)(alphaScale * (f64)poly->color[3]);
                    colorBottom.bytes[0] = next->color[0];
                    colorBottom.bytes[1] = next->color[1];
                    colorBottom.bytes[2] = next->color[2];
                    colorBottom.bytes[3] = (u8)(alphaScale * (f64)next->color[3]);

                    GXPosition3f32(poly->targetPos.x, poly->targetPos.y, poly->targetPos.z);
                    GXColor1u32(colorTop.value);
                    GXTexCoord2f32(uTop, FLOAT_80331844);

                    GXPosition3f32(poly->pos.x, poly->pos.y, poly->pos.z);
                    GXColor1u32(colorTop.value);
                    GXTexCoord2f32(uTop, FLOAT_80331840);

                    GXPosition3f32(next->targetPos.x, next->targetPos.y, next->targetPos.z);
                    GXColor1u32(colorBottom.value);
                    GXTexCoord2f32(uBottom, FLOAT_80331844);

                    poly = next;
                    GXPosition3f32(poly->pos.x, poly->pos.y, poly->pos.z);
                    GXColor1u32(colorBottom.value);
                    GXTexCoord2f32(uBottom, FLOAT_80331840);
                }
            }
        }
    }
}
