#include "ffcc/pppYmTracer2.h"
#include "ffcc/mapmesh.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"
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

extern int DAT_8032ed70;
extern int DAT_801eadc8;
extern float FLOAT_80331840;
extern float FLOAT_80331844;
extern float FLOAT_80331848;
extern float FLOAT_80331860;
extern double DOUBLE_80331850;
extern double DOUBLE_80331858;
extern CUtil DAT_8032ec70;

static char s_pppYmTracer2_cpp_801dc4b8[] = "pppYmTracer2.cpp";

struct YmTracer2Step {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    s32 m_stepValue;
    s32 m_arg3;
    u8* m_payload;
};

struct TraceEntry {
    Vec pos;
    float pad0;
    Vec targetPos;
    float pad1;
    u8 flags[8];
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
void pppConstructYmTracer2(pppYmTracer2* pppYmTracer2, UnkC* param_2)
{
	float fVar1 = FLOAT_80331844;
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
void pppConstruct2YmTracer2(pppYmTracer2* pppYmTracer2, UnkC* param_2)
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
void pppDestructYmTracer2(pppYmTracer2* pppYmTracer2, UnkC* param_2)
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
void pppFrameYmTracer2(pppYmTracer2* pppYmTracer2, UnkB* param_2, UnkC* param_3)
{
    bool useFallback;
    float fVar2;
    s16 alpha;
    s32 iVar4;
    float* pfVar6;
    void* pWorkPtr;
    s32 iVar8;
    s16 visibleCount;
    Vec* dest;
    Vec* pVVar10;
    u32 i;
    Vec* source;
    u8* work;
    Vec local_a8;
    Vec local_9c;
    Vec local_90;
    Vec local_84;
    Mtx MStack_78;
    u32 uStack_44;
    u32 uStack_3c;
    YmTracer2Step* step = (YmTracer2Step*)param_2;

    if (DAT_8032ed70 != 0) {
        return;
    }

    useFallback = false;
    iVar4 = param_3->m_serializedDataOffsets[1];
    work = (u8*)pppYmTracer2 + 0x80 + *param_3->m_serializedDataOffsets;

    if (step->m_initWOrk == -1) {
        pWorkPtr = &DAT_801eadc8;
    } else {
        pWorkPtr = (u8*)&pppMngStPtr->m_kind + step->m_initWOrk * 0x10 + step->m_stepValue;
    }
    *(void**)(work + 0x20) = pWorkPtr;

    if (step->m_arg3 == -1) {
        pWorkPtr = &DAT_801eadc8;
    } else {
        pWorkPtr = (u8*)&pppMngStPtr->m_kind + step->m_arg3 * 0x10 + *(s32*)step->m_payload;
    }
    *(void**)(work + 0x24) = pWorkPtr;

    if (*(u32*)(work + 0x28) == 0) {
        useFallback = true;
        *(u16*)(work + 0x30) = (u16)step->m_payload[8] / *(u16*)(step->m_payload + 6);
        *(void**)(work + 0x28) = pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (u32)*(u16*)(step->m_payload + 4) * 0x28, pppEnvStPtr->m_stagePtr, s_pppYmTracer2_cpp_801dc4b8, 0xAD);

        fVar2 = FLOAT_80331840;
        pfVar6 = *(float**)(work + 0x28);
        for (iVar8 = 0; iVar8 < (s32)(u32)*(u16*)(step->m_payload + 4); iVar8++) {
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

    source = *(Vec**)(work + 0x28);
    *(u8*)&source[2].z = 1;
    pVVar10 = source;

    for (i = 0; (s32)i < (s32)(step->m_payload[9] + 1); i++) {
        iVar8 = *(u16*)(step->m_payload + 4) - 2;
        pfVar6 = (float*)((u8*)source + iVar8 * 0x28);

        for (; (s32)i <= iVar8; iVar8--) {
            *(u8*)(pfVar6 + 0x12) = *(u8*)(pfVar6 + 8);
            local_a8.x = *pfVar6;
            dest = (Vec*)((u8*)source + (iVar8 + 1) * 0x28);
            local_a8.y = pfVar6[1];
            local_a8.z = pfVar6[2];
            pppCopyVector__FR3Vec3Vec(dest, &local_a8);
            local_9c.x = pfVar6[4];
            local_9c.y = pfVar6[5];
            local_9c.z = pfVar6[6];
            pppCopyVector__FR3Vec3Vec((Vec*)&dest[1].y, &local_9c);
            *(u8*)(pfVar6 + 0x11) = *(u8*)(pfVar6 + 7);
            *(u8*)((u8*)pfVar6 + 0x45) = *(u8*)((u8*)pfVar6 + 0x1d);
            *(u8*)((u8*)pfVar6 + 0x46) = *(u8*)((u8*)pfVar6 + 0x1e);
            *(u8*)((u8*)pfVar6 + 0x47) = *(u8*)((u8*)pfVar6 + 0x1f);
            pfVar6 -= 10;
        }

        fVar2 = **(float**)(work + 0x20);
        *(float*)work = fVar2;
        pVVar10->x = fVar2;
        fVar2 = *(float*)(*(s32*)(work + 0x20) + 4);
        *(float*)(work + 4) = fVar2;
        pVVar10->y = fVar2;
        fVar2 = *(float*)(*(s32*)(work + 0x20) + 8);
        *(float*)(work + 8) = fVar2;
        pVVar10->z = fVar2;
        fVar2 = **(float**)(work + 0x24);
        *(float*)(work + 0x10) = fVar2;
        pVVar10[1].y = fVar2;
        fVar2 = *(float*)(*(s32*)(work + 0x24) + 4);
        *(float*)(work + 0x14) = fVar2;
        pVVar10[1].z = fVar2;
        fVar2 = *(float*)(*(s32*)(work + 0x24) + 8);
        *(float*)(work + 0x18) = fVar2;
        pVVar10[2].x = fVar2;
        *(u8*)&pVVar10[2].y = ((u8*)pppYmTracer2)[iVar4 + 0x88];
        *((u8*)&pVVar10[2].y + 1) = ((u8*)pppYmTracer2)[iVar4 + 0x89];
        *((u8*)&pVVar10[2].y + 2) = ((u8*)pppYmTracer2)[iVar4 + 0x8A];

        if (i == 0) {
            PSMTXConcat(pppMngStPtr->m_matrix.value, *(Mtx*)((u8*)pppYmTracer2 + 4), MStack_78);
            PSMTXMultVec(MStack_78, source, source);
            PSMTXMultVec(MStack_78, (Vec*)&source[1].y, (Vec*)&source[1].y);
        } else if (!useFallback) {
            uStack_3c = i ^ 0x80000000;
            uStack_44 = (step->m_payload[9] + 1) ^ 0x80000000;
            if (GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f(
                    (FLOAT_80331860 / (float)((double)((u64)0x43300000 << 32 | uStack_44) - DOUBLE_80331858)) *
                        (float)((double)((u64)0x43300000 << 32 | uStack_3c) - DOUBLE_80331858),
                    pppMngStPtr, MStack_78) == 0) {
                useFallback = true;
            } else {
                PSMTXConcat(MStack_78, *(Mtx*)((u8*)pppYmTracer2 + 4), MStack_78);
                PSMTXMultVec(MStack_78, pVVar10, pVVar10);
                PSMTXMultVec(MStack_78, (Vec*)&pVVar10[1].y, (Vec*)&pVVar10[1].y);
            }
        }

        pVVar10 = (Vec*)&pVVar10[3].y;
    }

    if (useFallback) {
        Vec* pFallback = source;

        for (iVar4 = 0; iVar4 < (s32)(u32)*(u16*)(step->m_payload + 4); iVar4++) {
            local_84.x = source->x;
            local_84.y = source->y;
            local_84.z = source->z;
            pppCopyVector__FR3Vec3Vec(pFallback, &local_84);
            local_90.x = source[1].y;
            local_90.y = source[1].z;
            local_90.z = source[2].x;
            pppCopyVector__FR3Vec3Vec((Vec*)&pFallback[1].y, &local_90);
            pFallback = (Vec*)&pFallback[3].y;
        }
    }

    visibleCount = 0;
    for (iVar4 = 0; iVar4 < (s32)(u32)*(u16*)(step->m_payload + 4); iVar4++) {
        alpha = (u16)step->m_payload[8] - (s16)iVar4 * *(s16*)(work + 0x30);
        if ((alpha < 0) || ((useFallback = *(char*)&source[2].z == '\0'), useFallback)) {
            *(u8*)((u8*)&source[2].y + 3) = 0;
        } else if (!useFallback) {
            *(u8*)((u8*)&source[2].y + 3) = (u8)alpha;
            visibleCount++;
        }
        source = (Vec*)&source[3].y;
    }
    *(s16*)(work + 0x2c) = visibleCount;
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
void pppRenderYmTracer2(pppYmTracer2* pppYmTracer2, UnkB* param_2, UnkC* param_3)
{
    YmTracer2Step* step = (YmTracer2Step*)param_2;
    s32 dataOffset = *param_3->m_serializedDataOffsets;
    s32 colorOffset = param_3->m_serializedDataOffsets[1];
    TraceEntry* entries = *(TraceEntry**)((u8*)pppYmTracer2 + 0x80 + dataOffset + 0x28);
    CMapMesh* mapMesh = ((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[step->m_dataValIndex];
    CTexture* texture;
    int textureIndex;
    u16 visibleCount;
    float uvStep;
    float alphaScale;

    if (step->m_dataValIndex == 0xFFFF) {
        return;
    }

    pppSetBlendMode__FUc(step->m_payload[10]);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (void*)((u8*)pppYmTracer2 + 0x88 + colorOffset), (void*)&ppvCameraMatrix0, FLOAT_80331840, step->m_payload[0xC],
        step->m_payload[0xB], step->m_payload[10], 0, 1, 1, 0);
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

    if (step->m_payload[0xD] == 0) {
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
    } else {
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
    }

    visibleCount = *(u16*)((u8*)pppYmTracer2 + 0x80 + dataOffset + 0x2C);
    uvStep = FLOAT_80331844 / (float)visibleCount;
    GXSetCullMode(GX_CULL_NONE);

    if (visibleCount > 1) {
        alphaScale = ((float)((double)((u64)0x4330000000000000ULL | (u32)((u8*)pppYmTracer2)[colorOffset + 0x8B]) -
                               DOUBLE_80331850)) /
                     FLOAT_80331848;

        GXBegin((GXPrimitive)0x98, GX_VTXFMT7, (u16)(visibleCount - 1) * 4);
        for (u16 i = 0; i < (u16)(visibleCount - 1); i++) {
            if (alphaScale < FLOAT_80331840) {
                alphaScale = FLOAT_80331840;
            }
            if (alphaScale > FLOAT_80331844) {
                alphaScale = FLOAT_80331844;
            }

            float u0 = (float)i * uvStep;
            float u1 = (float)(i + 1) * uvStep;
            TraceEntry* current = &entries[i];
            TraceEntry* next = &entries[i + 1];
            u8 currentAlpha = (u8)(alphaScale * current->flags[7]);
            u8 nextAlpha = (u8)(alphaScale * next->flags[7]);
            u32 currentColor = ((u32)current->flags[1] << 24) | ((u32)current->flags[2] << 16) |
                               ((u32)current->flags[3] << 8) | currentAlpha;
            u32 nextColor =
                ((u32)next->flags[1] << 24) | ((u32)next->flags[2] << 16) | ((u32)next->flags[3] << 8) | nextAlpha;

            GXPosition3f32(current->targetPos.x, current->targetPos.y, current->targetPos.z);
            GXColor1u32(currentColor);
            GXTexCoord2f32(u0, FLOAT_80331844);

            GXPosition3f32(current->pos.x, current->pos.y, current->pos.z);
            GXColor1u32(currentColor);
            GXTexCoord2f32(u0, FLOAT_80331840);

            GXPosition3f32(next->targetPos.x, next->targetPos.y, next->targetPos.z);
            GXColor1u32(nextColor);
            GXTexCoord2f32(u1, FLOAT_80331844);

            GXPosition3f32(next->pos.x, next->pos.y, next->pos.z);
            GXColor1u32(nextColor);
            GXTexCoord2f32(u1, FLOAT_80331840);
        }
    }
}
