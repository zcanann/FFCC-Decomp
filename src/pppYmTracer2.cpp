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
extern "C" void pppSetBlendMode__FUc(unsigned char);
extern "C" void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
    unsigned char);
extern "C" int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh*, CMaterialSet*, int&);
extern "C" void SetVtxFmt_POS_CLR_TEX__5CUtilFv(void*);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
extern "C" void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);

extern float FLOAT_80331840;
extern float FLOAT_80331844;
extern float FLOAT_80331848;
extern float FLOAT_80331860;
extern double DOUBLE_80331850;
extern double DOUBLE_80331858;

static char s_pppYmTracer2_cpp_801dc4b8[] = "pppYmTracer2.cpp";

struct TraceEntry {
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
    float* initWork;
    float* arg3Work;
    TraceEntry* entries;
    u16 visibleCount;
    u16 pad2e;
    u16 alphaStep;
    u16 pad32;
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void initTracePolygon(PYmTracer2*, TRACE_POLYGON&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void copyPolygonData(TRACE_POLYGON*, TRACE_POLYGON*)
{
	// TODO
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
    _pppPObject* baseObj;
    bool useFallback;
    float fVar2;
    s16 alpha;
    s32 iVar4;
    float* pfVar6;
    void* pWorkPtr;
    s32 iVar8;
    s16 visibleCount;
    u32 i;
    TraceEntry* entries;
    TraceEntry* entry;
    TraceEntry* dest;
    TracerWork* work;
    Vec local_a8;
    Vec local_9c;
    Vec local_90;
    Vec local_84;
    Mtx MStack_78;
    u32 uStack_44;
    u32 uStack_3c;

    if (gPppCalcDisabled != 0) {
        return;
    }

    baseObj = (_pppPObject*)pppYmTracer2;
    useFallback = false;
    iVar4 = param_3->m_serializedDataOffsets[1];
    work = (TracerWork*)((u8*)pppYmTracer2 + 0x80 + *param_3->m_serializedDataOffsets);

    if (param_2->m_initWOrk == -1) {
        pWorkPtr = gPppDefaultValueBuffer;
    } else {
        pWorkPtr = (u8*)&pppMngStPtr->m_kind + param_2->m_initWOrk * 0x10 + param_2->m_stepValue;
    }
    work->initWork = (float*)pWorkPtr;

    if (param_2->m_arg3 == -1) {
        pWorkPtr = gPppDefaultValueBuffer;
    } else {
        pWorkPtr = (u8*)&pppMngStPtr->m_kind + param_2->m_arg3 * 0x10 + *(s32*)param_2->m_payload;
    }
    work->arg3Work = (float*)pWorkPtr;

    if (work->entries == nullptr) {
        useFallback = true;
        work->alphaStep = (u16)param_2->m_payload[8] / *(u16*)(param_2->m_payload + 6);
        work->entries = (TraceEntry*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (u32)*(u16*)(param_2->m_payload + 4) * 0x28, pppEnvStPtr->m_stagePtr, s_pppYmTracer2_cpp_801dc4b8, 0xAD);

        fVar2 = FLOAT_80331840;
        pfVar6 = (float*)work->entries;
        for (iVar8 = 0; iVar8 < (s32)(u32)*(u16*)(param_2->m_payload + 4); iVar8++) {
            *(u8*)(pfVar6 + 8) = 0;
            *(u8*)((u8*)pfVar6 + 0x1f) = 0;
            pfVar6[2] = fVar2;
            pfVar6[1] = fVar2;
            *pfVar6 = fVar2;
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
            *(u8*)(pfVar6 + 0x12) = *(u8*)(pfVar6 + 8);
            local_a8.x = *pfVar6;
            dest = entries + (iVar8 + 1);
            local_a8.y = pfVar6[1];
            local_a8.z = pfVar6[2];
            pppCopyVector__FR3Vec3Vec(&dest->pos, &local_a8);
            local_9c.x = pfVar6[4];
            local_9c.y = pfVar6[5];
            local_9c.z = pfVar6[6];
            pppCopyVector__FR3Vec3Vec(&dest->targetPos, &local_9c);
            *(u8*)(pfVar6 + 0x11) = *(u8*)(pfVar6 + 7);
            *(u8*)((u8*)pfVar6 + 0x45) = *(u8*)((u8*)pfVar6 + 0x1d);
            *(u8*)((u8*)pfVar6 + 0x46) = *(u8*)((u8*)pfVar6 + 0x1e);
            *(u8*)((u8*)pfVar6 + 0x47) = *(u8*)((u8*)pfVar6 + 0x1f);
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
        entry->color[0] = ((u8*)pppYmTracer2)[iVar4 + 0x88];
        entry->color[1] = ((u8*)pppYmTracer2)[iVar4 + 0x89];
        entry->color[2] = ((u8*)pppYmTracer2)[iVar4 + 0x8A];

        if (i == 0) {
            PSMTXConcat(pppMngStPtr->m_matrix.value, baseObj->m_localMatrix.value, MStack_78);
            PSMTXMultVec(MStack_78, &entries[0].pos, &entries[0].pos);
            PSMTXMultVec(MStack_78, &entries[0].targetPos, &entries[0].targetPos);
        } else if (!useFallback) {
            uStack_3c = i ^ 0x80000000;
            uStack_44 = (param_2->m_payload[9] + 1) ^ 0x80000000;
            if (GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f(
                    (FLOAT_80331860 / (float)((double)((u64)0x43300000 << 32 | uStack_44) - DOUBLE_80331858)) *
                        (float)((double)((u64)0x43300000 << 32 | uStack_3c) - DOUBLE_80331858),
                    pppMngStPtr, MStack_78) == 0) {
                useFallback = true;
            } else {
                PSMTXConcat(MStack_78, baseObj->m_localMatrix.value, MStack_78);
                PSMTXMultVec(MStack_78, &entry->pos, &entry->pos);
                PSMTXMultVec(MStack_78, &entry->targetPos, &entry->targetPos);
            }
        }

        entry++;
    }

    if (useFallback) {
        TraceEntry* pFallback = entries;

        for (iVar4 = 0; iVar4 < (s32)(u32)*(u16*)(param_2->m_payload + 4); iVar4++) {
            local_84.x = entries->pos.x;
            local_84.y = entries->pos.y;
            local_84.z = entries->pos.z;
            pppCopyVector__FR3Vec3Vec(&pFallback->pos, &local_84);
            local_90.x = entries->targetPos.x;
            local_90.y = entries->targetPos.y;
            local_90.z = entries->targetPos.z;
            pppCopyVector__FR3Vec3Vec(&pFallback->targetPos, &local_90);
            pFallback++;
        }
    }

    visibleCount = 0;
    for (iVar4 = 0; iVar4 < (s32)(u32)*(u16*)(param_2->m_payload + 4); iVar4++) {
        alpha = (u16)param_2->m_payload[8] - (s16)iVar4 * work->alphaStep;
        if ((alpha < 0) || ((useFallback = entries->active == 0), useFallback)) {
            entries->color[3] = 0;
        } else if (!useFallback) {
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
    TraceEntry* entry;
    TraceEntry* next;
    CMapMesh* mapMesh;
    CTexture* texture;
    u8* work;
    s32 dataOffset;
    s32 colorOffset;
    int textureIndex;
    u32 visibleCount;
    s32 i;
    u32 colorTop;
    u32 colorBottom;
    float uTop;
    float uBottom;
    float uvStep;
    double alphaScale;

    dataOffset = *param_3->m_serializedDataOffsets;
    colorOffset = param_3->m_serializedDataOffsets[1];
    work = (u8*)pppYmTracer2 + 0x80 + dataOffset;
    mapMesh = ((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[param_2->m_dataValIndex];

    if (param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    pppSetBlendMode__FUc(param_2->m_payload[10]);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (void*)((u8*)pppYmTracer2 + 0x88 + colorOffset), (void*)&ppvCameraMatrix0, FLOAT_80331840,
        param_2->m_payload[0xC], param_2->m_payload[0xB], param_2->m_payload[10], 0, 1, 1, 0);
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&gUtil);

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

    if (param_2->m_payload[0xD] == 0) {
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
    } else {
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
    }

    visibleCount = *(u16*)(work + 0x2C);
    uvStep = FLOAT_80331844 / (float)((double)visibleCount - DOUBLE_80331850);
    GXSetCullMode(GX_CULL_NONE);

    if (visibleCount > 1) {
        entry = *(TraceEntry**)(work + 0x28);
        alphaScale =
            (double)((float)((double)(u32)((u8*)pppYmTracer2)[colorOffset + 0x8B] - DOUBLE_80331850) / FLOAT_80331848);

        GXBegin((GXPrimitive)0x98, GX_VTXFMT7, (u16)(visibleCount - 1) * 4);
        for (i = 0; i < (s32)(visibleCount - 1); i++) {
            uTop = (float)i * uvStep;
            uBottom = (float)(i + 1) * uvStep;
            if (alphaScale < FLOAT_80331840) {
                alphaScale = FLOAT_80331840;
            }
            if (alphaScale > FLOAT_80331844) {
                alphaScale = FLOAT_80331844;
            }

            next = entry + 1;
            colorTop = ((u32)entry->color[0] << 0x18) | ((u32)entry->color[1] << 0x10) | ((u32)entry->color[2] << 8) |
                       (u8)(alphaScale * (double)((float)((double)entry->color[3] - DOUBLE_80331850)));
            colorBottom = ((u32)next->color[0] << 0x18) | ((u32)next->color[1] << 0x10) | ((u32)next->color[2] << 8) |
                          (u8)(alphaScale * (double)((float)((double)next->color[3] - DOUBLE_80331850)));

            GXPosition3f32(entry->targetPos.x, entry->targetPos.y, entry->targetPos.z);
            GXColor1u32(colorTop);
            GXTexCoord2f32(uTop, FLOAT_80331844);

            GXPosition3f32(entry->pos.x, entry->pos.y, entry->pos.z);
            GXColor1u32(colorTop);
            GXTexCoord2f32(uTop, FLOAT_80331840);

            GXPosition3f32(next->targetPos.x, next->targetPos.y, next->targetPos.z);
            GXColor1u32(colorBottom);
            GXTexCoord2f32(uBottom, FLOAT_80331844);

            GXPosition3f32(next->pos.x, next->pos.y, next->pos.z);
            GXColor1u32(colorBottom);
            GXTexCoord2f32(uBottom, FLOAT_80331840);
            entry++;
        }
    }
}
