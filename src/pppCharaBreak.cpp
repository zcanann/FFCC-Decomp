#include "ffcc/pppCharaBreak.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"

extern char MaterialMan[];
extern struct {
    float _224_4_, _228_4_, _232_4_, _236_4_, _240_4_, _244_4_, _252_4_;
    Mtx m_cameraMatrix;
} CameraPcs;
extern void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void* materialMan, void* materialSet,
                                                                        unsigned int materialIdx, int, int);

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
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructCharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstruct2CharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructCharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameCharaBreak(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderCharaBreak(void)
{
	// TODO
}
