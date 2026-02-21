#include "ffcc/pppYmMana.h"
#include "ffcc/graphic.h"
#include "ffcc/p_game.h"
#include "ffcc/pppPart.h"

extern Mtx ppvCameraMatrix0;

extern float FLOAT_80330e4c;
extern float FLOAT_80330e58;
extern float FLOAT_80330e5c;
extern float FLOAT_80330e68;

extern struct {
    float _224_4_;
    float _228_4_;
    float _232_4_;
} CameraPcs;

struct Vec2d {
    float x;
    float y;
};

extern "C" {
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(int, int, int,
                                                                                                            int, int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(int, int, int,
                                                                                                            int, int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
}

/*
 * --INFO--
 * PAL Address: 0x800d7ff8
 * PAL Size: 1816b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SetEnvMap(PYmMana*, VYmMana* vYmMana)
{
    unsigned char* vYmManaBytes = (unsigned char*)vYmMana;
    GXTexObj* texObjA = *(GXTexObj**)(vYmManaBytes + 0x2c);
    GXTexObj* texObjB = *(GXTexObj**)(vYmManaBytes + 0x28);
    void* texObjCData = *(void**)(vYmManaBytes + 0x80);
    GXTexObj* texObjC = (GXTexObj*)((unsigned char*)texObjCData + 0x28);
    unsigned char alpha = *(unsigned char*)(vYmManaBytes + 0xe8);

    _GXColor white = {0xff, 0xff, 0xff, 0xff};
    _GXColor whiteAlpha = {0xff, 0xff, 0xff, alpha};
    _GXColor alphaOnly = {0x00, 0x00, 0x00, alpha};

    GXSetNumChans(1);
    GXSetChanCtrl((GXChannelID)4, (GXBool)0, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
    GXSetBlendMode((GXBlendMode)1, (GXBlendFactor)4, (GXBlendFactor)5, (GXLogicOp)0xf);
    GXSetChanAmbColor((GXChannelID)4, white);
    GXSetChanMatColor((GXChannelID)4, white);
    GXSetTevKColor((GXTevKColorID)0, alphaOnly);
    GXSetTevKColor((GXTevKColorID)1, whiteAlpha);
    GXSetTevSwapModeTable((GXTevSwapSel)1, (GXTevColorChan)3, (GXTevColorChan)3, (GXTevColorChan)3, (GXTevColorChan)3);

    GXSetTevDirect((GXTevStageID)0);
    GXLoadTexObj(texObjC, (GXTexMapID)0);
    GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)0, (GXTexCoordID)0, (GXTexMapID)0, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)0, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)0, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xc);
    GXSetTevColorOp((GXTevStageID)0, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)0, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)4);
    GXSetTevAlphaOp((GXTevStageID)0, (GXTevOp)0, (GXTevBias)0, (GXTevScale)2, (GXBool)1, (GXTevRegID)1);

    GXSetTevDirect((GXTevStageID)1);
    GXLoadTexObj(texObjC, (GXTexMapID)0);
    GXSetTexCoordGen2((GXTexCoordID)1, (GXTexGenType)1, (GXTexGenSrc)5, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)1, (GXTexCoordID)1, (GXTexMapID)0, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)1, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)1, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xc);
    GXSetTevColorOp((GXTevStageID)1, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)1, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)4);
    GXSetTevAlphaOp((GXTevStageID)1, (GXTevOp)0, (GXTevBias)0, (GXTevScale)2, (GXBool)1, (GXTevRegID)2);

    GXSetTevDirect((GXTevStageID)2);
    GXLoadTexObj(texObjA, (GXTexMapID)1);
    GXSetTexCoordGen2((GXTexCoordID)2, (GXTexGenType)1, (GXTexGenSrc)4, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)2, (GXTexCoordID)2, (GXTexMapID)1, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)2, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevKColor((GXTevKColorID)0, alphaOnly);
    GXSetTevKColorSel((GXTevStageID)2, (GXTevKColorSel)0xc);
    GXSetTevKAlphaSel((GXTevStageID)2, (GXTevKAlphaSel)0x1c);
    GXSetTevColorIn((GXTevStageID)2, (GXTevColorArg)10, (GXTevColorArg)0xe, (GXTevColorArg)8, (GXTevColorArg)0xf);
    GXSetTevColorOp((GXTevStageID)2, (GXTevOp)8, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)3);
    GXSetTevAlphaIn((GXTevStageID)2, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)1);
    GXSetTevAlphaOp((GXTevStageID)2, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)3);
    GXLoadTexObj(texObjA, (GXTexMapID)1);
    GXSetTexCoordGen2((GXTexCoordID)3, (GXTexGenType)1, (GXTexGenSrc)4, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)3, (GXTexCoordID)3, (GXTexMapID)0, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)3, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)3, (GXTevColorArg)0xf, (GXTevColorArg)6, (GXTevColorArg)9, (GXTevColorArg)0xf);
    GXSetTevColorOp((GXTevStageID)3, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)3);
    GXSetTevAlphaIn((GXTevStageID)3, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)1);
    GXSetTevAlphaOp((GXTevStageID)3, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)4);
    GXLoadTexObj(texObjB, (GXTexMapID)2);
    GXSetTexCoordGen2((GXTexCoordID)4, (GXTexGenType)1, (GXTexGenSrc)5, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)4, (GXTexCoordID)4, (GXTexMapID)2, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)4, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevKColor((GXTevKColorID)1, whiteAlpha);
    GXSetTevKColorSel((GXTevStageID)4, (GXTevKColorSel)0xd);
    GXSetTevKAlphaSel((GXTevStageID)4, (GXTevKAlphaSel)0x1d);
    GXSetTevColorIn((GXTevStageID)4, (GXTevColorArg)0xe, (GXTevColorArg)0xb, (GXTevColorArg)8, (GXTevColorArg)0xf);
    GXSetTevColorOp((GXTevStageID)4, (GXTevOp)8, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)4, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)2);
    GXSetTevAlphaOp((GXTevStageID)4, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)5);
    GXLoadTexObj(texObjB, (GXTexMapID)2);
    GXSetTexCoordGen2((GXTexCoordID)5, (GXTexGenType)1, (GXTexGenSrc)5, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)5, (GXTexCoordID)5, (GXTexMapID)0, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)5, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)5, (GXTevColorArg)0xf, (GXTevColorArg)0, (GXTevColorArg)9, (GXTevColorArg)0xf);
    GXSetTevColorOp((GXTevStageID)5, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)5, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)2);
    GXSetTevAlphaOp((GXTevStageID)5, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)6);
    GXSetTevOrder((GXTevStageID)6, (GXTexCoordID)0xff, (GXTexMapID)0xff, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)6, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)6, (GXTevColorArg)0xf, (GXTevColorArg)6, (GXTevColorArg)0xc, (GXTevColorArg)0);
    GXSetTevColorOp((GXTevStageID)6, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)6, (GXTevAlphaArg)7, (GXTevAlphaArg)1, (GXTevAlphaArg)6, (GXTevAlphaArg)2);
    GXSetTevAlphaOp((GXTevStageID)6, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)7);
    GXSetTevOrder((GXTevStageID)7, (GXTexCoordID)0xff, (GXTexMapID)0xff, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)7, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevKAlphaSel((GXTevStageID)7, (GXTevKAlphaSel)0x1c);
    GXSetTevColorIn((GXTevStageID)7, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0);
    GXSetTevColorOp((GXTevStageID)7, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)7, (GXTevAlphaArg)7, (GXTevAlphaArg)0, (GXTevAlphaArg)6, (GXTevAlphaArg)7);
    GXSetTevAlphaOp((GXTevStageID)7, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetNumTevStages(8);
    GXSetNumTexGens(6);
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
 * PAL Address: 0x800d7fcc
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void Mana_BeforeDrawShadowLockEnvCallback(CChara::CModel*, void*, void*, int)
{
	GXSetZMode((GXBool)0, (GXCompare)3, (GXBool)0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Chara_DrawShadowMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Mana_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructYmMana(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructYmMana(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameYmMana(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800d6908
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmMana(void)
{
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
void Mana_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*) [4], int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetViewportv(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MakeWave(Vec*, unsigned short*, float*, Vec&, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CreateWaterMesh(Vec*, Vec*, Vec2d*, unsigned short*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdateWaterMesh(VYmMana*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800d55f4
 * PAL Size: 1472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void RenderWaterMesh(VYmMana* mana)
{
    u8* work = (u8*)mana;
    u16* indices = *(u16**)(work + 0x50);
    void* texObj0 = *(void**)(work + 0x28);
    void* texObj1 = *(void**)(work + 0x2C);
    void* texObj2 = (u8*)*(void**)(work + 0x80) + 0x28;
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
    modulateColor.r = *(u8*)(work + 0xE8);
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
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0xB, 0xE, 8,
                                                                                                           0xF);
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
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0xE, 0xB, 8,
                                                                                                           0);
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
void CalculateNormal(VYmMana*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800d50dc
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CalcWaterReflectionVector__FP3VecP3VecP3Vecl3VecPA4_fP8_GXColorP5Vec2d(
    Vec* reflectionVec, Vec* positions, Vec* normals, long count, Vec waterOrigin, float (*matrix)[4], _GXColor* color, Vec2d* texCoord)
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

    transformedCameraPos.x = FLOAT_80330e4c;
    transformedCameraPos.y = FLOAT_80330e4c;
    transformedCameraPos.z = FLOAT_80330e4c;

    PSMTXCopy(matrix, matrixNoTranslate);
    objPos.x = matrixNoTranslate[0][3];
    objPos.y = matrixNoTranslate[1][3];
    objPos.z = matrixNoTranslate[2][3];
    matrixNoTranslate[0][3] = transformedCameraPos.x;
    matrixNoTranslate[1][3] = transformedCameraPos.y;
    matrixNoTranslate[2][3] = transformedCameraPos.z;
    PSMTXInverse(matrixNoTranslate, inverseMtx);

    PSVECSubtract(&objPos, &cameraPos, &cameraPos);
    PSVECScale(&cameraPos, &cameraPos, FLOAT_80330e68);
    PSMTXMultVec(inverseMtx, &cameraPos, &transformedCameraPos);

    texCoordFloat = (float*)texCoord;
    colorBytes = (unsigned char*)color;
    zero = (double)FLOAT_80330e4c;
    half = (double)FLOAT_80330e5c;

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
            *texCoordFloat = -reflectionVec->x / (FLOAT_80330e58 - reflectionVec->z);
            texCoordFloat[1] = -reflectionVec->y / (FLOAT_80330e58 - reflectionVec->z);
        } else {
            colorBytes[0] = 0x80;
            colorBytes[1] = 0x80;
            colorBytes[2] = 0xff;
            colorBytes[3] = 0xbc;
            *texCoordFloat = -reflectionVec->x / (FLOAT_80330e58 + reflectionVec->z);
            texCoordFloat[1] = -reflectionVec->y / (FLOAT_80330e58 + reflectionVec->z);
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
    DCFlushRange(texCoord, count * sizeof(Vec2d));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalcReflectionVector2(Vec*, S16Vec*, S16Vec*, long, unsigned long, unsigned long, float (*) [4], void*, unsigned long, _GXColor*, S16Vec2d*, S16Vec2d*, CChara::CNode*, PYmMana*, VYmMana*)
{
	// TODO
}
