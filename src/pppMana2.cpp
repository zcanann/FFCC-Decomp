#include "ffcc/pppMana2.h"
#include "ffcc/graphic.h"
#include "ffcc/gobject.h"
#include "ffcc/p_game.h"
#include "ffcc/pppPart.h"

#include <string.h>
#include <dolphin/os/OSCache.h>

extern char lbl_801DC4D0[];
extern float FLOAT_803318fc;
extern float FLOAT_80331898;
extern float FLOAT_8033189c;
extern float FLOAT_803318a0;
extern float FLOAT_803318a4;
extern float FLOAT_80331904;
extern Mtx ppvCameraMatrix0;
extern struct {
    float _224_4_;
    float _228_4_;
    float _232_4_;
} CameraPcs;
extern char MaterialMan[];
extern char DAT_80331900[];
extern char DAT_803318d4[];
extern char DAT_803318dc[];
extern char DAT_803318e4[];
extern char DAT_803318ec[];
extern char DAT_803318f4[];

extern "C" {
void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned int, int, int);
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(int, int,
                                                                                                            int, int,
                                                                                                            int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int,
                                                                                            int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(int, int,
                                                                                                            int, int,
                                                                                                            int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int,
                                                                                            int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
}

/*
 * --INFO--
 * PAL Address: 0x80108db0
 * PAL Size: 1060b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void Mana2_DrawMeshDLCallback(CChara::CModel* model, void* work, void* step, int partIndex, int dlIndex, float (*mtx)[4])
{
    u8 type = *(u8*)((char*)step + 0x1C);
    int shape = *(int*)(*(int*)((char*)model + 0xAC) + partIndex * 0x14 + 8);
    u32* dlEntry = (u32*)(*(int*)(shape + 0x50) + dlIndex * 0xC);
    bool draw = false;

    if (type == 2) {
        if (strcmp((char*)shape, DAT_80331900) == 0 || strcmp((char*)shape, DAT_803318dc) == 0) {
            draw = true;
        }
    } else if (type < 2) {
        if (type == 0) {
            if (strcmp((char*)shape, DAT_80331900) == 0) {
                draw = true;
            }
        } else if (strcmp((char*)shape, DAT_80331900) == 0 || strcmp((char*)shape, DAT_803318d4) == 0) {
            draw = true;
        }
    } else if (type < 4 && (strcmp((char*)shape, DAT_80331900) == 0 || strcmp((char*)shape, DAT_803318e4) == 0)) {
        draw = true;
    }

    int waterCmp = strcmp((char*)shape, DAT_803318ec);
    if ((waterCmp == 0 && *(char*)((char*)step + 0x1C) == 1) ||
        (strcmp((char*)shape, DAT_803318f4) == 0 && *(char*)((char*)step + 0x1C) == 2)) {
        Mtx cameraMtx;
        Mtx rotMtx;
        Mtx posMtx;
        Vec offset;
        double x = (double)mtx[0][3];
        double y = (double)mtx[1][3];
        double z = (double)mtx[2][3];

        PSMTXCopy(ppvCameraMatrix0, cameraMtx);
        PSMTXRotRad(rotMtx, 'z', FLOAT_80331904);
        mtx[0][3] = FLOAT_80331898;
        mtx[1][3] = FLOAT_80331898;
        mtx[2][3] = FLOAT_80331898;
        PSMTXConcat(mtx, rotMtx, mtx);

        offset.x = FLOAT_80331898;
        offset.y = *(float*)((char*)step + 0x30);
        offset.z = FLOAT_80331898;
        PSMTXMultVec(mtx, &offset, &offset);

        mtx[0][3] = (float)x;
        mtx[1][3] = (float)(y - (double)offset.y);
        mtx[2][3] = (float)z;

        PSMTXConcat(cameraMtx, mtx, posMtx);
        GXLoadPosMtxImm(posMtx, 0);
        PSMTXCopy(mtx, (float(*)[4])((char*)work + 0x80));
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
        RenderWaterMesh((VMana2*)work);
        GXSetCullMode((GXCullMode)1);
    }

    if (draw) {
        if (strcmp((char*)shape, DAT_80331900) != 0) {
            PSMTXCopy(mtx, (float(*)[4])((char*)work + 0xB0));
            if (*(char*)((char*)work + 0xEC) != 0) {
                *(u8*)((char*)work + 0x38) = **(u8**)(shape + 0x28);
                *(u8*)((char*)work + 0x39) = *((u8*)(*(int*)(shape + 0x28)) + 1);
                *(u8*)((char*)work + 0x3A) = *((u8*)(*(int*)(shape + 0x28)) + 2);
                *(u8*)((char*)work + 0x3B) = 0x80;
                DCFlushRange((u8*)work + 0x38, 4);
                GXSetArray((GXAttr)0xB, *(void**)((char*)work + 0x68), 4);
                GXSetArray((GXAttr)0xD, *(void**)((char*)work + 0x6C), 4);
                *(u32*)(MaterialMan + 0x08) = *(u32*)((char*)work + 0x64);
                *(u32*)(MaterialMan + 0x44) = 0xFFFFFFFF;
                *(u8*)(MaterialMan + 0x4C) = 0xFF;
                *(u32*)(MaterialMan + 0x11C) = 0;
                *(u32*)(MaterialMan + 0x120) = 0x1E;
                *(u32*)(MaterialMan + 0x124) = 0;
                *(u8*)(MaterialMan + 0x205) = 0xFF;
                *(u8*)(MaterialMan + 0x206) = 0xFF;
                *(u32*)(MaterialMan + 0x58) = 0;
                *(u32*)(MaterialMan + 0x5C) = 0;
                *(u8*)(MaterialMan + 0x208) = 0;
                *(u32*)(MaterialMan + 0x48) = 0x2ACE0F;
                *(u32*)(MaterialMan + 0x128) = 0;
                *(u32*)(MaterialMan + 0x12C) = 0x1E;
                *(u32*)(MaterialMan + 0x130) = 0;
                *(u32*)(MaterialMan + 0x40) = 0x2ACE0F;
                *(u32*)(MaterialMan + 0xD0) = *(u32*)((char*)work + 0x20);
                GXSetCullMode((GXCullMode)1);
                GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
                SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
                    MaterialMan, *(void**)(*(int*)((char*)model + 0xA4) + 0x24), *(u16*)((char*)dlEntry + 8), 0, 0);
                GXCallDisplayList(*(void**)(*(int*)((char*)work + 0x60) + dlIndex * 4), *dlEntry);
            }
        } else {
            GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
            SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
                MaterialMan, *(void**)(*(int*)((char*)model + 0xA4) + 0x24), *(u16*)((char*)dlEntry + 8), 0, 0);
            GXCallDisplayList((void*)dlEntry[1], dlEntry[0]);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructMana2(pppMana2* pppMana2, UnkC* param_2)
{
    CGObject* gObject;
    void* handle;
    u32 model;
    u32* work;
    s32 workOffset;

    gObject = *(CGObject**)((char*)pppMngStPtr + 0xDC);
    workOffset = *(s32*)((char*)param_2 + 0xC);
    work = (u32*)((char*)pppMana2 + 0x80 + workOffset);
    gObject->m_stepSlopeLimit = FLOAT_803318fc;

    handle = GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    model = *(u32*)((char*)handle + 0x168);
    *(u32*)(model + 0x98) = 0x3F;
    work[1] = (u32)pppMngStPtr;

    work[0] = 0;
    work[1] = 0;
    work[8] = 0;
    work[9] = 0;
    work[15] = 0;
    work[16] = 0;
    work[18] = 0;
    work[19] = 0;
    work[20] = 0;
    work[21] = 0;
    work[22] = 0;
    work[24] = 0;
    work[17] = 0;
    work[23] = 0;
    work[29] = 0;
    work[28] = 0;
    work[30] = 0;
    work[31] = 0;
    work[25] = 0;
    work[26] = 0;
    work[27] = 0;
    work[10] = 0;
    work[11] = 0;
    work[12] = 0;
    work[13] = 0;
    *(u8*)(work + 0x38) = 0xFF;
    PSMTXIdentity((float (*)[4])(work + 0x20));
    PSMTXIdentity((float (*)[4])(work + 0x2C));
    *(u8*)(work + 0xE) = 0xFF;
    *((u8*)work + 0x39) = 0xFF;
    *((u8*)work + 0x3A) = 0xFF;
    *((u8*)work + 0x3B) = 0xFF;
    work[2] = 0;
    work[3] = 0;
    work[4] = 0;
    work[5] = 0;
    work[6] = 0;
    work[7] = 0;
    work[0x39] = 0;
    work[0x3A] = 0;
    *(u8*)(work + 0x3B) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructMana2(pppMana2*, UnkC*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameMana2(pppMana2*, UnkB*, UnkC*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80107e48
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderMana2(pppMana2*, UnkB*, UnkC*)
{
    Graphic.Printf(lbl_801DC4D0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    Graphic.SetViewport();
    pppInitBlendMode();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Mana2_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*) [4], int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalcReflectionVector2(Vec*, S16Vec*, S16Vec*, long, unsigned long, unsigned long, float (*) [4], void*, unsigned long, _GXColor*, S16Vec2d*, CChara::CNode*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MakeWave(Vec*, unsigned short*, float*, Vec*, float, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010701c
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" int CreateWaterMesh__FP3VecP3VecP5Vec2dPUsf2(
    Vec* param_1, Vec* param_2, Vec2d* param_3, unsigned short* param_4, float param_5, float)
{
    float* pPos;
    float* pNormal;
    float* pUv;
    unsigned short* pIdx;
    float xPos;
    float zPos;
    int idxOffset;
    int row;
    int pair;
    int rowCounter;
    int colCounter;
    const float fZero = 0.0f;
    const float fOne = 1.0f;
    const float fStepScale = 0.125f;
    float radius = 0.0f;
    float step = 0.0f;

    pPos = (float*)param_1;
    pNormal = (float*)param_2;
    pUv = (float*)param_3;
    pIdx = param_4;

    radius = param_5 * fOne;
    rowCounter = 0;
    step = param_5 * fStepScale;
    for (zPos = radius; -radius <= zPos; zPos -= step) {
        colCounter = 0;
        for (xPos = -radius; xPos <= radius; xPos += step) {
            pPos[0] = xPos;
            pPos[1] = fZero;
            pPos[2] = zPos;
            pPos += 3;

            pNormal[0] = fZero;
            pNormal[1] = fOne;
            pNormal[2] = fZero;
            pNormal += 3;

            pUv[0] = (float)((double)colCounter * (double)fStepScale);
            pUv[1] = (float)((double)rowCounter * (double)fStepScale);
            pUv += 2;
            colCounter++;
        }
        rowCounter++;
    }

    idxOffset = 0;
    row = 0;
    colCounter = 0;
    do {
        pair = 8;
        rowCounter = colCounter;
        do {
            *(short*)((char*)pIdx + idxOffset) = rowCounter;
            *(short*)((char*)pIdx + idxOffset + 2) = rowCounter + 1;
            *(short*)((char*)pIdx + idxOffset + 4) = rowCounter + 0x12;
            *(short*)((char*)pIdx + idxOffset + 6) = rowCounter + 0x12;
            *(short*)((char*)pIdx + idxOffset + 8) = rowCounter + 0x11;
            *(short*)((char*)pIdx + idxOffset + 10) = rowCounter;
            *(short*)((char*)pIdx + idxOffset + 12) = rowCounter + 1;
            *(short*)((char*)pIdx + idxOffset + 14) = rowCounter + 2;
            *(short*)((char*)pIdx + idxOffset + 16) = rowCounter + 0x13;
            *(short*)((char*)pIdx + idxOffset + 18) = rowCounter + 0x13;
            *(short*)((char*)pIdx + idxOffset + 20) = rowCounter + 0x12;
            *(short*)((char*)pIdx + idxOffset + 22) = rowCounter + 1;
            idxOffset += 0x18;
            pair--;
            rowCounter += 2;
        } while (pair != 0);
        row++;
        colCounter += 0x11;
    } while (row < 0x10);

    return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdateWaterMesh(VMana2*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80106694
 * PAL Size: 1472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void RenderWaterMesh(VMana2* mana2)
{
    u8* work = (u8*)mana2;
    u16* indices = *(u16**)(work + 0x50);
    void* texObj0 = *(void**)(work + 0x28);
    void* texObj1 = *(void**)(work + 0x2C);
    void* texObj2 = (u8*)*(void**)(work + 0x7C) + 0x28;
    _GXColor modulateColor;
    _GXColor blendColor = {0x80, 0x80, 0x80, 0x80};

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, GX_INDEX16);
    GXSetVtxDesc((GXAttr)10, GX_INDEX16);
    GXSetVtxDesc((GXAttr)0xB, GX_INDEX16);
    GXSetVtxDesc((GXAttr)0xD, GX_INDEX16);
    GXSetVtxDesc((GXAttr)0xE, GX_INDEX16);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)10, (GXCompCnt)0, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)0xB, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)0xD, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)0xE, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetNumTexGens(2);
    GXSetCullMode((GXCullMode)0);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 0xF);
    GXSetChanCtrl((GXChannelID)4, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPOT);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
    GXSetNumChans(1);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
    GXSetArray((GXAttr)9, *(void**)(work + 0x3C), 0xC);
    GXSetArray((GXAttr)10, *(void**)(work + 0x40), 0xC);
    GXSetArray((GXAttr)0xB, *(void**)(work + 0x5C), 4);
    GXSetArray((GXAttr)0xD, *(void**)(work + 0x54), 8);
    GXSetArray((GXAttr)0xE, *(void**)(work + 0x58), 8);
    GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2((GXTexCoordID)1, (GXTexGenType)1, (GXTexGenSrc)5, 0x3C, GX_FALSE, 0x7D);
    modulateColor.r = *(u8*)(work + 0xE0);
    modulateColor.g = modulateColor.r;
    modulateColor.b = modulateColor.r;
    modulateColor.a = modulateColor.r;

    GXSetTevDirect((GXTevStageID)0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
    GXLoadTexObj((GXTexObj*)texObj2, GX_TEXMAP0);
    GXSetTevKColor((GXTevKColorID)1, modulateColor);
    GXSetTevKColorSel((GXTevStageID)0, (GXTevKColorSel)0xD);
    GXSetTevKAlphaSel((GXTevStageID)0, (GXTevKAlphaSel)0x1D);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 0xF,
                                                                                                           0xF, 8);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 6, 4, 7);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);

    GXSetTevDirect((GXTevStageID)1);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 1, 1, 4);
    GXLoadTexObj((GXTexObj*)texObj0, GX_TEXMAP1);
    GXSetTevKColor((GXTevKColorID)0, blendColor);
    GXSetTevKColorSel((GXTevStageID)1, (GXTevKColorSel)0xC);
    GXSetTevKAlphaSel((GXTevStageID)1, (GXTevKAlphaSel)0x1C);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0xB, 0xE,
                                                                                                           8, 0xF);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 8, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 7, 7, 0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 1, 1, 0);

    GXSetTevDirect((GXTevStageID)2);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2, 0, 0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 1, 2, 4);
    GXLoadTexObj((GXTexObj*)texObj1, GX_TEXMAP2);
    GXSetTevKColor((GXTevKColorID)0, blendColor);
    GXSetTevKColorSel((GXTevStageID)2, (GXTevKColorSel)0xC);
    GXSetTevKAlphaSel((GXTevStageID)2, (GXTevKAlphaSel)0x1C);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0xE, 0xB,
                                                                                                           8, 0);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 8, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(2, 7, 7, 7, 0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 0, 1, 0);

    GXSetNumTevStages(3);
    GXBegin((GXPrimitive)0x90, GX_VTXFMT7, 0x600);
    for (int i = 0; i < 0x180; i++) {
        GXPosition1x16(indices[0]);
        GXNormal1x16(indices[0]);
        GXColor1x16(indices[0]);
        GXTexCoord1x16(indices[0]);
        GXTexCoord1x16(indices[0]);
        GXPosition1x16(indices[1]);
        GXNormal1x16(indices[1]);
        GXColor1x16(indices[1]);
        GXTexCoord1x16(indices[1]);
        GXTexCoord1x16(indices[1]);
        GXPosition1x16(indices[2]);
        GXNormal1x16(indices[2]);
        GXColor1x16(indices[2]);
        GXTexCoord1x16(indices[2]);
        GXTexCoord1x16(indices[2]);
        GXPosition1x16(indices[3]);
        GXNormal1x16(indices[3]);
        GXColor1x16(indices[3]);
        GXTexCoord1x16(indices[3]);
        GXTexCoord1x16(indices[3]);
        indices += 4;
    }

    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0xFF, 4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 4, 5, 0xF);
    GXSetNumTevStages(1);
    GXLoadTexObj((GXTexObj*)texObj0, GX_TEXMAP0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalculateNormal(VMana2*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010617c
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CalcWaterReflectionVector__FP3VecP3VecP3Vecl3VecPA4_fP8_GXColorP5Vec2d2(
    Vec* reflectionVec,
    Vec* positions,
    Vec* normals,
    long count,
    Vec waterOrigin,
    float (*matrix)[4],
    _GXColor* color,
    Vec2d* texCoord,
    Vec2d*)
{
    Vec cameraPos;
    Vec objPos;
    Vec transformedCameraPos;
    Vec reflected;
    Mtx inverseMtx;
    Mtx matrixNoTranslate;
    float* texCoordFloat;
    unsigned char* colorBytes;
    double zero;
    double half;
    long i;

    (void)waterOrigin;

    if (Game.game.m_currentSceneId == 7) {
        cameraPos.x = ppvCameraMatrix0[0][3];
        cameraPos.y = ppvCameraMatrix0[1][3];
        cameraPos.z = ppvCameraMatrix0[2][3];
    } else {
        cameraPos.x = CameraPcs._224_4_;
        cameraPos.y = CameraPcs._228_4_;
        cameraPos.z = CameraPcs._232_4_;
    }

    transformedCameraPos.x = FLOAT_80331898;
    transformedCameraPos.y = FLOAT_80331898;
    transformedCameraPos.z = FLOAT_80331898;

    PSMTXCopy(matrix, matrixNoTranslate);
    objPos.x = matrixNoTranslate[0][3];
    objPos.y = matrixNoTranslate[1][3];
    objPos.z = matrixNoTranslate[2][3];
    matrixNoTranslate[0][3] = transformedCameraPos.x;
    matrixNoTranslate[1][3] = transformedCameraPos.y;
    matrixNoTranslate[2][3] = transformedCameraPos.z;
    PSMTXInverse(matrixNoTranslate, inverseMtx);

    PSVECSubtract(&objPos, &cameraPos, &cameraPos);
    PSVECScale(&cameraPos, &cameraPos, FLOAT_8033189c);
    PSMTXMultVec(inverseMtx, &cameraPos, &transformedCameraPos);

    texCoordFloat = (float*)texCoord;
    colorBytes = (unsigned char*)color;
    zero = (double)FLOAT_80331898;
    half = (double)FLOAT_803318a4;

    for (i = 0; i < count; i++) {
        PSVECSubtract(positions, &transformedCameraPos, &reflected);
        C_VECReflect(&reflected, normals, reflectionVec);
        PSMTXMultVec(matrixNoTranslate, reflectionVec, reflectionVec);
        PSVECNormalize(reflectionVec, reflectionVec);

        if ((double)reflectionVec->z < zero) {
            colorBytes[0] = 0x80;
            colorBytes[1] = 0xff;
            colorBytes[2] = 0x80;
            colorBytes[3] = 0x7f;
            *texCoordFloat = -reflectionVec->x / (FLOAT_803318a0 - reflectionVec->z);
            texCoordFloat[1] = -reflectionVec->y / (FLOAT_803318a0 - reflectionVec->z);
        } else {
            colorBytes[0] = 0x80;
            colorBytes[1] = 0x80;
            colorBytes[2] = 0xff;
            colorBytes[3] = 0xbc;
            *texCoordFloat = -reflectionVec->x / (FLOAT_803318a0 + reflectionVec->z);
            texCoordFloat[1] = -reflectionVec->y / (FLOAT_803318a0 + reflectionVec->z);
        }

        positions++;
        reflectionVec++;
        normals++;
        colorBytes += 4;
        *texCoordFloat = (float)((double)*texCoordFloat * half);
        *texCoordFloat = (float)((double)*texCoordFloat + half);
        texCoordFloat[1] = (float)((double)texCoordFloat[1] * half);
        texCoordFloat[1] = (float)((double)texCoordFloat[1] + half);
        texCoordFloat += 2;
    }

    DCFlushRange(reflectionVec - count, count * sizeof(Vec));
    DCFlushRange(texCoord, count << 3);
}
