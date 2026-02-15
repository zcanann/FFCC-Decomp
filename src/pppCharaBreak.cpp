#include "ffcc/pppCharaBreak.h"

#include "ffcc/graphic.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"

extern char MaterialMan[];
extern CGraphic Graphic;
extern struct {
    float _224_4_, _228_4_, _232_4_, _236_4_, _240_4_, _244_4_, _252_4_;
    Mtx m_cameraMatrix;
} CameraPcs;
extern char s_pppCharaBreak_cpp_801dd690[];
extern float FLOAT_80332048;
extern void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void* materialMan, void* materialSet,
                                                                        unsigned int materialIdx, int, int);
extern "C" {
void _WaitDrawDone__8CGraphicFPci(CGraphic*, const char*, int);
void pppHeapUseRate__FPQ27CMemory6CStage(void*);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);
void pppInitBlendMode__Fv(void);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
}

/*
 * --INFO--
 * PAL Address: 0x80140F18
 * PAL Size: 708b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CharaBreak_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f(void* model, void* modelData, void*,
                                                                                 s32 meshIndex, Mtx meshMtx)
{
    Mtx cameraMtx;
    Mtx drawMtx;
    s32 meshArrayBase;
    s32 materialData;
    s32 drawListIndex;
    s32 materialIndex;

    if (*(s32*)((u8*)modelData + 0x44) == 0) {
        return;
    }

    meshArrayBase = *(s32*)((u8*)model + 0xAC) + (meshIndex * 0x14);
    drawListIndex = *(s32*)((u8*)meshArrayBase + 8);
    materialData = *(s32*)((u8*)drawListIndex + 0x50);

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

    for (materialIndex = *(s32*)((u8*)drawListIndex + 0x4C) - 1; materialIndex >= 0; materialIndex--) {
        s32 meshTable = *(s32*)((u8*)*(s32*)((u8*)modelData + 0x1C) + (meshIndex * 4));
        s32 displayList = *(s32*)((u8*)meshTable + (materialIndex * 4));
        s32 vertexData = *(s32*)((u8*)displayList + 0xC);
        u16 faceCount = *(u16*)((u8*)displayList + 8);
        u16 i;

        SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(MaterialMan, *(void**)((u8*)*(s32*)((u8*)model + 0xA4) + 0x24),
                                                                    *(u16*)((u8*)materialData + 8), 0, 0);

        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXSetCullMode(GX_CULL_NONE);
        GXClearVtxDesc();
        GXSetVtxDesc((GXAttr)9, GX_DIRECT);
        GXSetVtxDesc((GXAttr)10, GX_INDEX16);
        GXSetVtxDesc((GXAttr)11, GX_INDEX16);
        GXSetVtxDesc((GXAttr)13, GX_INDEX16);
        GXSetVtxDesc((GXAttr)14, GX_INDEX16);
        GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, GX_POS_XYZ, GX_S16, *(u32*)((u8*)*(s32*)((u8*)model + 0xA4) + 0x34) & 0xFF);
        GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)10, GX_CLR_RGB, GX_RGBA8, *(u32*)((u8*)*(s32*)((u8*)model + 0xA4) + 0x38) & 0xFF);
        GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)11, GX_NRM_XYZ, GX_S16, 0);
        GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)13, GX_TEX_ST, GX_S16, 0xC);
        GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)14, GX_TEX_ST, GX_S16, 0xC);

        if (*(s32*)((u8*)*(s32*)((u8*)meshArrayBase + 8) + 0x54) == 0) {
            GXLoadPosMtxImm(cameraMtx, 0);
        } else {
            PSMTXConcat(cameraMtx, meshMtx, drawMtx);
            GXLoadPosMtxImm(drawMtx, 0);
        }

        GXBegin((GXPrimitive)0x90, (GXVtxFmt)7, (u16)(faceCount * 3));
        for (i = 0; i < faceCount; i++) {
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x10);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x12);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x14);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x28);
            GXWGFifo.u16 = 0;
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x2E);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x2E);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x16);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x18);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x1A);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x2A);
            GXWGFifo.u16 = 0;
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x30);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x30);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x1C);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x1E);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x20);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x2C);
            GXWGFifo.u16 = 0;
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x32);
            GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x32);

            vertexData += 0x34;
        }

        materialData += 0xC;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801411DC
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CharaBreak_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f(void)
{
}

/*
 * --INFO--
 * PAL Address: 0x801411E0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CharaBreak_BeforeMeshLockEnvCallback__FPQ26CChara6CModelPvPvi(void)
{
}

/*
 * --INFO--
 * PAL Address: 0x801411E4
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" u32 CharaBreak_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv(u32 value, void* modelData, void* meshData)
{
    if (*(u32*)((u8*)modelData + 0x44) == 0) {
        return value;
    }

    return (u32)__cntlzw(1 - (u32)*((u8*)meshData + 0x42)) >> 5;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CreatePolygon(POLYGON_DATA*, void*, unsigned long, CChara::CModel*, CChara::CMesh*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void InitPolygonParameter(PCharaBreak*, VCharaBreak*, POLYGON_DATA*, unsigned long, CChara::CModel*, CChara::CMesh*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdatePolygonData(PCharaBreak*, VCharaBreak*, CChara::CModel*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801400B0
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructCharaBreak(pppCharaBreak* charaBreak, CharaBreakUnkC* data)
{
    int dataOffset = data->m_serializedDataOffsets[2];

    *(u32*)((u8*)charaBreak + 0x9C + dataOffset) = 0;
    *(float*)((u8*)charaBreak + 0x8C + dataOffset) = FLOAT_80332048;
    *(float*)((u8*)charaBreak + 0x88 + dataOffset) = FLOAT_80332048;
    *(float*)((u8*)charaBreak + 0x84 + dataOffset) = FLOAT_80332048;
    *(float*)((u8*)charaBreak + 0x98 + dataOffset) = FLOAT_80332048;
    *(float*)((u8*)charaBreak + 0x94 + dataOffset) = FLOAT_80332048;
    *(float*)((u8*)charaBreak + 0x90 + dataOffset) = FLOAT_80332048;
    *(u32*)((u8*)charaBreak + 0xC4 + dataOffset) = 1;
}

/*
 * --INFO--
 * PAL Address: 0x80140080
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2CharaBreak(pppCharaBreak* charaBreak, CharaBreakUnkC* data)
{
    int dataOffset = data->m_serializedDataOffsets[2];

    *(float*)((u8*)charaBreak + 0x8C + dataOffset) = FLOAT_80332048;
    *(float*)((u8*)charaBreak + 0x88 + dataOffset) = FLOAT_80332048;
    *(float*)((u8*)charaBreak + 0x84 + dataOffset) = FLOAT_80332048;
    *(float*)((u8*)charaBreak + 0x98 + dataOffset) = FLOAT_80332048;
    *(float*)((u8*)charaBreak + 0x94 + dataOffset) = FLOAT_80332048;
    *(float*)((u8*)charaBreak + 0x90 + dataOffset) = FLOAT_80332048;
}

/*
 * --INFO--
 * PAL Address: 0x8013FF14
 * PAL Size: 364b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructCharaBreak(pppCharaBreak* charaBreak, CharaBreakUnkC* data)
{
    _WaitDrawDone__8CGraphicFPci(&Graphic, s_pppCharaBreak_cpp_801dd690, 0x319);

    int dataOffset = data->m_serializedDataOffsets[2];
    u8* model = *(u8**)((u8*)charaBreak + 0xC0 + dataOffset);
    void** perMeshBuffers = *(void***)((u8*)charaBreak + 0x9C + dataOffset);
    u8* mesh = *(u8**)(model + 0xAC);

    *(u32*)(model + 0xE4) = 0;
    *(u32*)(model + 0xE8) = 0;
    *(u32*)(model + 0xF4) = 0;
    *(u32*)(model + 0xFC) = 0;
    *(u32*)(model + 0x104) = 0;
    *(u32*)(model + 0xEC) = 0;

    if (perMeshBuffers != NULL) {
        u32 meshCount = *(u32*)(*(u8**)(model + 0xA4) + 0xC);
        for (u32 meshIndex = 0; meshIndex < meshCount; meshIndex++) {
            int* dlEntries = (int*)perMeshBuffers[meshIndex];
            u32 dlCount = *(u32*)(*(u8**)(mesh + 8) + 0x4C);

            if (dlEntries != NULL) {
                for (u32 dlIndex = 0; dlIndex < dlCount; dlIndex++) {
                    int dlInfo = dlEntries[dlIndex];
                    if (dlInfo != 0) {
                        if (*(void**)dlInfo != NULL) {
                            pppHeapUseRate__FPQ27CMemory6CStage(*(void**)dlInfo);
                            *(u32*)dlInfo = 0;
                        }
                        if (*(void**)(dlInfo + 0xC) != NULL) {
                            pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(dlInfo + 0xC));
                            *(u32*)(dlInfo + 0xC) = 0;
                        }
                    }
                    if (dlInfo != 0) {
                        pppHeapUseRate__FPQ27CMemory6CStage((void*)dlInfo);
                        dlEntries[dlIndex] = 0;
                    }
                }
            }

            if (perMeshBuffers[meshIndex] != NULL) {
                pppHeapUseRate__FPQ27CMemory6CStage(perMeshBuffers[meshIndex]);
                perMeshBuffers[meshIndex] = NULL;
            }
            mesh += 0x14;
        }
    }

    if (perMeshBuffers != NULL) {
        pppHeapUseRate__FPQ27CMemory6CStage(perMeshBuffers);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8013FAA0
 * PAL Size: 1140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameCharaBreak(pppCharaBreak*, CharaBreakUnkB*, CharaBreakUnkC*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8013F9D0
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderCharaBreak(pppCharaBreak* charaBreak, CharaBreakUnkB*, CharaBreakUnkC* data)
{
    int colorOffset = data->m_serializedDataOffsets[0];
    u8* work = (u8*)charaBreak + 0x80 + data->m_serializedDataOffsets[2];

    if (*(u32*)(work + 0x44) != 0) {
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
        pppInitBlendMode__Fv();
        pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
            (u8*)charaBreak + 0x88 + colorOffset,
            (u8*)charaBreak + 0x40,
            FLOAT_80332048,
            0,
            0,
            0,
            0,
            1,
            1,
            0);
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 2, 2, 3);
        work[0] = 0xFF;
        work[1] = 0xFF;
        work[2] = 0xFF;
        work[3] = *((u8*)charaBreak + 0x8B + colorOffset);
    }
}
