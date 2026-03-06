#include "ffcc/pppYmMana.h"
#include "ffcc/graphic.h"
#include "ffcc/gobject.h"
#include "ffcc/p_game.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"

#include <string.h>
#include <dolphin/os/OSCache.h>

extern Mtx ppvCameraMatrix0;

extern float FLOAT_80330e48;
extern float FLOAT_80330e4c;
extern float FLOAT_80330e58;
extern float FLOAT_80330e5c;
extern float FLOAT_80330e60;
extern float FLOAT_80330e64;
extern float FLOAT_80330e6c;
extern float FLOAT_80330e68;
extern float FLOAT_80330eb8;
extern float FLOAT_80330ec0;
extern double DOUBLE_80330e70;
extern void* DAT_80238030;
extern char DAT_80330e50[];
extern char DAT_80330e88[];
extern char DAT_80330e90[];
extern char DAT_80330e98[];
extern char DAT_80330ea0[];
extern char DAT_80330ea8[];
extern char DAT_80330ebc[];
extern char MaterialMan[];
extern char DAT_8032ec70[];
extern int DAT_8032ed70;

extern struct {
    float _224_4_;
    float _228_4_;
    float _232_4_;
    Mtx m_cameraMatrix;
    Mtx44 m_screenMatrix;
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
void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned int, int, int);
void* GetCharaHandlePtr__FP8CGObjectl(void*, long);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void*);
int GetTextureFromRSD__FiP9_pppEnvSt(int, _pppEnvSt*);
void InitTexObj__8CTextureFv(void*);
void genParaboloidMap__FPvPUlUs9_GXVtxFmt(void*, unsigned long*, unsigned short, GXVtxFmt);
void DispCharaParts__8CGObjectFi(CGObject*, int);
void _WaitDrawDone__8CGraphicFPci(CGraphic*, char*, int);
int IsHasDrawFmtDL__5CUtilFUc(void*, unsigned char);
void ConvI2FVector__5CUtilFR3Vec6S16Vecl(void*, Vec*, S16Vec*, unsigned long);
void ConvF2IVector2d__5CUtilFR8S16Vec2d5Vec2dl(void*, S16Vec2d*, Vec2d*, long);
void RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor(
    void* util, float x0, float y0, float x1, float y1, _GXTexObj* texObj, Vec2d* uv0, Vec2d* uv1, _GXColor* color,
    _GXBlendFactor srcFactor, _GXBlendFactor dstFactor);
void Draw__Q29CCharaPcs7CHandleFi(CCharaPcs::CHandle* handle, int drawType);
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
 * PAL Address: 0x800d7ef4
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void Chara_DrawShadowMeshDLCallback(CChara::CModel* model, void* work, void* vYmMana, int meshIndex, int dlIndex, float (*) [4])
{
    s32 meshData = *(s32*)((u8*)model + 0xAC);
    u8 alpha = *(u8*)((u8*)vYmMana + 0x3B);

    *(u8*)((u8*)work + 0xFC) = 0xFF;
    *(u8*)((u8*)work + 0xFD) = 0xFF;
    *(u8*)((u8*)work + 0xFE) = 0xFF;
    *(u8*)((u8*)work + 0xFF) = alpha == 0 ? 0xFF : alpha;

    DCFlushRange((u8*)work + 0xFC, 4);
    GXSetArray((GXAttr)0xB, (u8*)work + 0xFC, 4);

    u32* dl = (u32*)(*(s32*)(*(s32*)(meshData + meshIndex * 0x14 + 8) + 0x50) + dlIndex * 0xC);
    SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
        MaterialMan, *(void**)(*(s32*)((u8*)model + 0xA4) + 0x24), *(u16*)((u8*)dl + 8), 0, 0);
    GXCallDisplayList((void*)dl[1], dl[0]);
}

/*
 * --INFO--
 * PAL Address: 0x800d79f4
 * PAL Size: 1280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void Mana_DrawMeshDLCallback(CChara::CModel* model, void* work, void* step, int partIndex, int dlIndex, float (*mtx)[4])
{
    u8 type = *(u8*)((u8*)step + 0x1C);
    int mesh = *(int*)(*(int*)((u8*)model + 0xAC) + partIndex * 0x14 + 8);
    u32* dl = (u32*)(*(int*)(mesh + 0x50) + dlIndex * 0xC);
    bool draw = false;

    if (type == 2) {
        if (strcmp((char*)mesh, DAT_80330ebc) == 0 || strcmp((char*)mesh, DAT_80330e90) == 0) {
            draw = true;
        }
    } else if (type < 2) {
        if (type == 0) {
            if (strcmp((char*)mesh, DAT_80330ebc) == 0) {
                draw = true;
            }
        } else if (strcmp((char*)mesh, DAT_80330ebc) == 0 || strcmp((char*)mesh, DAT_80330e88) == 0) {
            draw = true;
        }
    } else if (type < 4 && (strcmp((char*)mesh, DAT_80330ebc) == 0 || strcmp((char*)mesh, DAT_80330e98) == 0)) {
        draw = true;
    }

    int waterCmp = strcmp((char*)mesh, DAT_80330ea0);
    if ((waterCmp == 0 && type == 1) || (strcmp((char*)mesh, DAT_80330ea8) == 0 && type == 2)) {
        Mtx cameraMtx;
        Mtx rotXMtx;
        Mtx rotZMtx;
        Mtx offsetMtx;
        Mtx worldMtx;

        PSMTXCopy(ppvCameraMatrix0, cameraMtx);
        PSMTXCopy(mtx, (float (*)[4])((u8*)work + 0x88));
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
        GXSetCullMode(GX_CULL_NONE);
        PSMTXRotRad(rotXMtx, 'x', FLOAT_80330e48);
        PSMTXRotRad(rotZMtx, 'z', FLOAT_80330e48);
        PSMTXIdentity(offsetMtx);
        offsetMtx[1][3] = -*(float*)((u8*)step + 0x30);
        PSMTXConcat(rotZMtx, offsetMtx, offsetMtx);
        PSMTXConcat(rotXMtx, offsetMtx, offsetMtx);
        PSMTXConcat(mtx, offsetMtx, offsetMtx);
        PSMTXConcat(cameraMtx, offsetMtx, worldMtx);
        GXLoadPosMtxImm(worldMtx, 0);
        RenderWaterMesh((VYmMana*)work);
    }

    if (!draw) {
        return;
    }

    if (strcmp((char*)mesh, DAT_80330ebc) != 0) {
        PSMTXCopy(mtx, (float (*)[4])((u8*)work + 0xB8));
        if (*(u8*)((u8*)work + 0xF4) != 0) {
            *(u8*)((u8*)work + 0x38) = **(u8**)(mesh + 0x28);
            *(u8*)((u8*)work + 0x39) = *((u8*)(*(int*)(mesh + 0x28)) + 1);
            *(u8*)((u8*)work + 0x3A) = *((u8*)(*(int*)(mesh + 0x28)) + 2);
            *(u8*)((u8*)work + 0x3B) = 0x80;
            DCFlushRange((u8*)work + 0x38, 4);
            GXSetArray((GXAttr)0xB, *(void**)((u8*)work + 0x68), 4);
            GXSetArray((GXAttr)0xD, *(void**)((u8*)work + 0x6C), 4);
            GXSetArray((GXAttr)0xE, *(void**)((u8*)work + 0x70), 4);
            *(u32*)(MaterialMan + 0x08) = *(u32*)((u8*)work + 0x64);
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
            *(u32*)(MaterialMan + 0x48) = 0xAEE0F;
            *(u32*)(MaterialMan + 0x128) = 0;
            *(u32*)(MaterialMan + 0x12C) = 0x1E;
            *(u32*)(MaterialMan + 0x130) = 0;
            *(u32*)(MaterialMan + 0x40) = 0xAEE0F;
            *(u32*)(MaterialMan + 0xD0) = *(u32*)((u8*)work + 0x28);
            *(u32*)(MaterialMan + 0xDC) = *(u32*)((u8*)work + 0x2C);
            GXSetCullMode((GXCullMode)1);
            GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
            SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
                MaterialMan, *(void**)(*(int*)((u8*)model + 0xA4) + 0x24), *(u16*)((u8*)dl + 8), 0, 0);
            SetEnvMap((PYmMana*)step, (VYmMana*)work);
            GXCallDisplayList(*(void**)(*(int*)((u8*)work + 0x60) + dlIndex * 4), dl[0]);
            for (int i = 0; i < 16; i++) {
                GXSetTevKColorSel((GXTevStageID)i, (GXTevKColorSel)6);
                GXSetTevKAlphaSel((GXTevStageID)i, (GXTevKAlphaSel)0);
            }
        }
        return;
    }

    if (Game.game.m_currentMapId == 0x21) {
        float alphaScale = FLOAT_80330ec0 * *(float*)(*(int*)work + 0x4B0);
        int alpha = (int)alphaScale;
        *(u8*)((u8*)work + 0x100) = 0xFF;
        *(u8*)((u8*)work + 0x101) = 0xFF;
        *(u8*)((u8*)work + 0x102) = 0xFF;
        *(u8*)((u8*)work + 0x103) = (u8)alpha;
    } else {
        *(u8*)((u8*)work + 0x100) = *(u8*)((u8*)step + 0x3C);
        *(u8*)((u8*)work + 0x101) = *(u8*)((u8*)step + 0x3D);
        *(u8*)((u8*)work + 0x102) = *(u8*)((u8*)step + 0x3E);
        *(u8*)((u8*)work + 0x103) = 0xFF;
        if (*(u8*)((u8*)step + 0x3C) == 0) {
            *(u8*)((u8*)work + 0x100) = 0xFF;
        }
        if (*(u8*)((u8*)step + 0x3D) == 0) {
            *(u8*)((u8*)work + 0x101) = 0xFF;
        }
        if (*(u8*)((u8*)step + 0x3E) == 0) {
            *(u8*)((u8*)work + 0x102) = 0xFF;
        }
    }

    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    DCFlushRange((u8*)work + 0x100, 4);
    GXSetArray((GXAttr)0xB, (u8*)work + 0x100, 4);
    SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
        MaterialMan, *(void**)(*(int*)((u8*)model + 0xA4) + 0x24), *(u16*)((u8*)dl + 8), 0, 0);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 4, 1, 0xF);
    GXCallDisplayList((void*)dl[1], dl[0]);
}

/*
 * --INFO--
 * PAL Address: 0x800d7864
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMana(PYmMana* ymMana, pppYmManaUnkC* param_2)
{
    CGObject* gObject = *(CGObject**)((u8*)pppMngStPtr + 0xDC);
    u32* work = (u32*)((u8*)ymMana + 8 + param_2->m_serializedDataOffsets[2]);
    void* handle;
    u32 model;

    if (Game.game.m_currentSceneId == 7) {
        gObject->m_lookAtTimer = FLOAT_80330e58;
    }

    if (Game.game.m_currentMapId != 0x21) {
        gObject->m_stepSlopeLimit = FLOAT_80330eb8;
    }

    handle = GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    model = *(u32*)((u8*)handle + 0x168);
    *(u32*)(model + 0x98) = 0x3F;
    work[1] = (u32)pppMngStPtr;

    work[0] = 0;
    work[1] = 0;
    work[9] = 0;
    work[8] = 0;
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
    work[30] = 0;
    work[29] = 0;
    work[31] = 0;
    work[32] = 0;
    work[25] = 0;
    work[26] = 0;
    work[27] = 0;
    work[28] = 0;
    work[10] = 0;
    work[11] = 0;
    work[12] = 0;
    work[13] = 0;
    *(u8*)(work + 0x3A) = 0xFF;
    PSMTXIdentity((float (*)[4])(work + 0x22));
    PSMTXIdentity((float (*)[4])(work + 0x2E));
    *(u8*)(work + 0xE) = 0xFF;
    *((u8*)work + 0x39) = 0xFF;
    *((u8*)work + 0x3A) = 0xFF;
    *((u8*)work + 0x3B) = 0xFF;
    *(u8*)(work + 0x3F) = 0xFF;
    *((u8*)work + 0xFD) = 0xFF;
    *((u8*)work + 0xFE) = 0xFF;
    *((u8*)work + 0xFF) = 0xFF;
    *(u8*)(work + 0x40) = 0xFF;
    *((u8*)work + 0x101) = 0xFF;
    *((u8*)work + 0x102) = 0xFF;
    *((u8*)work + 0x103) = 0xFF;
    work[2] = 0;
    work[3] = 0;
    work[4] = 0;
    work[5] = 0;
    work[6] = 0;
    work[7] = 0;
    work[0x3B] = 0;
    work[0x3C] = 0;
    *(u8*)(work + 0x3D) = 0;
    work[0x3E] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800d7440
 * PAL Size: 1060b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMana(PYmMana* ymMana, pppYmManaUnkC* param_2)
{
    u32* work = (u32*)((u8*)ymMana + 8 + param_2->m_serializedDataOffsets[2]);
    CGObject* gObject = (CGObject*)work[0];
    void* handle;
    s32 model;
    s32 meshEntry;
    s32 step;
    u32 i;
    u32 j;

    DispCharaParts__8CGObjectFi(gObject, 1);
    handle = GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(u32*)(model + 0xE4) = 0;
    *(u32*)(model + 0xE8) = 0;
    *(u32*)(model + 0xF0) = 0;
    *(u32*)(model + 0xFC) = 0;
    _WaitDrawDone__8CGraphicFPci(&Graphic, (char*)"pppYmMana.cpp", 0x2CE);
    *(u32*)(MaterialMan + 0x208) = 0;
    *(u32*)(MaterialMan + 0x220) = 0;

    if (work[10] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[10]);
        work[10] = 0;
    }
    if (work[11] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[11]);
        work[11] = 0;
    }
    if (work[12] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[12]);
        work[12] = 0;
    }
    if (work[13] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[13]);
        work[13] = 0;
    }
    if (work[8] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[8]);
        work[8] = 0;
    }
    if (work[15] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[15]);
        work[15] = 0;
    }
    if (work[16] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[16]);
        work[16] = 0;
    }
    if (work[18] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[18]);
        work[18] = 0;
    }
    if (work[19] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[19]);
        work[19] = 0;
    }
    if (work[20] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[20]);
        work[20] = 0;
    }
    if (work[21] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[21]);
        work[21] = 0;
    }
    if (work[22] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[22]);
        work[22] = 0;
    }
    if (work[30] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[30]);
        work[30] = 0;
    }
    if (work[9] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[9]);
        work[9] = 0;
    }
    if (work[23] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[23]);
        work[23] = 0;
    }
    if (work[17] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[17]);
        work[17] = 0;
    }
    if (work[25] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[25]);
        work[25] = 0;
    }
    if (work[26] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[26]);
        work[26] = 0;
    }
    if (work[27] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[27]);
        work[27] = 0;
    }
    if (work[28] != 0) {
        pppHeapUseRate((CMemory::CStage*)work[28]);
        work[28] = 0;
    }

    meshEntry = *(s32*)(model + 0xAC);
    step = work[0x1D];
    for (i = 0; i < *(u32*)(*(s32*)(model + 0xA4) + 0xC); i++) {
        char stepType = *(char*)(step + 0x1C);
        s32 shape = *(s32*)(meshEntry + 8);

        if (stepType == 1) {
            if (strcmp((char*)shape, DAT_80330e88) == 0) {
                for (j = 0; j < *(u32*)(shape + 0x4C); j++) {
                    if (work[0x18] != 0 && *(CMemory::CStage**)(work[0x18] + j * 4) != NULL) {
                        pppHeapUseRate(*(CMemory::CStage**)(work[0x18] + j * 4));
                        *(u32*)(work[0x18] + j * 4) = 0;
                    }
                }
                if (work[0x18] != 0) {
                    pppHeapUseRate((CMemory::CStage*)work[0x18]);
                    work[0x18] = 0;
                }
            }
        } else if (stepType == 2) {
            if (strcmp((char*)shape, DAT_80330e90) == 0) {
                for (j = 0; j < *(u32*)(shape + 0x4C); j++) {
                    if (work[0x18] != 0 && *(CMemory::CStage**)(work[0x18] + j * 4) != NULL) {
                        pppHeapUseRate(*(CMemory::CStage**)(work[0x18] + j * 4));
                        *(u32*)(work[0x18] + j * 4) = 0;
                    }
                }
                if (work[0x18] != 0) {
                    pppHeapUseRate((CMemory::CStage*)work[0x18]);
                    work[0x18] = 0;
                }
            }
        } else if (stepType == 3 && strcmp((char*)shape, DAT_80330e98) == 0) {
            for (j = 0; j < *(u32*)(shape + 0x4C); j++) {
                if (work[0x18] != 0 && *(CMemory::CStage**)(work[0x18] + j * 4) != NULL) {
                    pppHeapUseRate(*(CMemory::CStage**)(work[0x18] + j * 4));
                    *(u32*)(work[0x18] + j * 4) = 0;
                }
            }
            if (work[0x18] != 0) {
                pppHeapUseRate((CMemory::CStage*)work[0x18]);
                work[0x18] = 0;
            }
        }

        meshEntry += 0x14;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d694c
 * PAL Size: 2804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmMana(PYmMana* pppYmMana, pppYmManaUnkB* param_2, pppYmManaUnkC* param_3)
{
    u32 texBufferSize;
    u32* work;
    void* dstBuffer;
    u32* texList;
    void* handle;
    s32 model;
    CGObject* gObject;
    s32 i;
    s32 setupOffset;

    if (DAT_8032ed70 != 0) {
        return;
    }

    gObject = *(CGObject**)((u8*)pppMngStPtr + 0xDC);
    setupOffset = param_3->m_serializedDataOffsets[1];
    work = (u32*)((u8*)pppYmMana + 8 + param_3->m_serializedDataOffsets[2]);
    if (gObject == NULL) {
        return;
    }

    handle = GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    work[0x1D] = (u32)param_2;
    if (Game.game.m_currentMapId == 0x21) {
        *((u8*)param_2 + 0x24) = 0;
    }

    if ((*(u8*)&gObject->m_weaponNodeFlags & 1) != 0) {
        work[0x3E] = (u32)gObject->m_attachOwner;
    }

    *(u32*)(model + 0xE4) = (u32)work;
    *(u32*)(model + 0xE8) = (u32)param_2;
    *(u32*)(model + 0xF0) = (u32)Mana_BeforeDrawCallback;
    *(u32*)(model + 0xFC) = (u32)Mana_DrawMeshDLCallback;

    MaterialMan[0x228] = (u8)((float)*((u8*)pppYmMana + 0x8B + setupOffset) * gObject->m_lookAtTimer);
    *((u8*)work + 0xE8) = MaterialMan[0x228];

    if (*(s32*)pppYmMana != 0) {
        return;
    }

    work[0] = (u32)gObject;
    *(u32*)(model + 0xE4) = (u32)work;
    *(u32*)(model + 0xE8) = (u32)param_2;
    *(u32*)(model + 0xF0) = (u32)Mana_BeforeDrawCallback;
    *(u32*)(model + 0xFC) = (u32)Mana_DrawMeshDLCallback;
    work[2] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((u8*)param_2 + 0x08), pppEnvStPtr);
    work[3] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((u8*)param_2 + 0x0C), pppEnvStPtr);
    work[4] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((u8*)param_2 + 0x10), pppEnvStPtr);
    work[5] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((u8*)param_2 + 0x14), pppEnvStPtr);
    work[6] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((u8*)param_2 + 0x20), pppEnvStPtr);
    work[7] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((u8*)param_2 + 0x24), pppEnvStPtr);
    work[0x1F] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((u8*)param_2 + 0x30), pppEnvStPtr);
    work[0x20] = (u32)GetTextureFromRSD__FiP9_pppEnvSt(*(s32*)((u8*)param_2 + 0x34), pppEnvStPtr);

    *(u32*)(work[0x1F] + 0x6C) = 0;
    InitTexObj__8CTextureFv((void*)work[0x1F]);
    *(u32*)(work[0x20] + 0x6C) = 0;
    InitTexObj__8CTextureFv((void*)work[0x20]);

    if (work[0x1E] == 0) {
        work[0x1E] = (u32)pppMemAlloc(0xC0, pppEnvStPtr->m_stagePtr, (char*)"pppYmMana.cpp", 0x38F);
    }
    if (work[10] == 0) {
        work[10] = (u32)pppMemAlloc(0x20, pppEnvStPtr->m_stagePtr, (char*)"pppYmMana.cpp", 0x395);
    }
    if (work[11] == 0) {
        work[11] = (u32)pppMemAlloc(0x20, pppEnvStPtr->m_stagePtr, (char*)"pppYmMana.cpp", 0x399);
    }

    texBufferSize = GXGetTexBufferSize(0x80, 0x80, GX_TF_RGBA8, GX_FALSE, 0);
    if (work[12] == 0) {
        work[12] = (u32)pppMemAlloc(texBufferSize, pppEnvStPtr->m_stagePtr, (char*)"pppYmMana.cpp", 0x3A1);
    }
    if (work[13] == 0) {
        work[13] = (u32)pppMemAlloc(texBufferSize, pppEnvStPtr->m_stagePtr, (char*)"pppYmMana.cpp", 0x3A3);
    }

    GXInitTexObj((GXTexObj*)work[10], (void*)work[12], 0x80, 0x80, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObj((GXTexObj*)work[11], (void*)work[13], 0x80, 0x80, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);

    if (work[8] == 0) {
        work[8] = (u32)pppMemAlloc(0xC0, pppEnvStPtr->m_stagePtr, (char*)"pppYmMana.cpp", 0x3B0);
    }
    dstBuffer = (void*)work[8];
    texList = &work[2];
    for (i = 0; i < 6; i++) {
        *(u32*)(texList[0] + 0x6C) = 0;
        InitTexObj__8CTextureFv((void*)texList[0]);
        memcpy(dstBuffer, (void*)(texList[0] + 0x28), 0x20);
        dstBuffer = (void*)((u8*)dstBuffer + 0x20);
        texList++;
    }

    if (work[9] == 0) {
        work[9] = (u32)pppMemAlloc(0xA5E8, pppEnvStPtr->m_stagePtr, (char*)"pppYmMana.cpp", 0x3CB);
        genParaboloidMap__FPvPUlUs9_GXVtxFmt((void*)work[9], &work[0x3B], 0x1E, GX_VTXFMT7);
    }
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
void pppRenderYmMana(PYmMana*, pppYmManaUnkB*, pppYmManaUnkC*)
{
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    Graphic.SetViewport();
    pppInitBlendMode();
}

/*
 * --INFO--
 * PAL Address: 0x800d6110
 * PAL Size: 2040b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void Mana_BeforeDrawCallback(CChara::CModel*, void* workPtr, void* step, float (*)[4], int pass)
{
    u32* work = (u32*)workPtr;
    Mtx savedCameraMtx;
    Mtx lookAtMtx;
    Mtx44 savedScreenMtx;
    Mtx44 projectionMtx;
    _GXTexObj sceneTexObj;
    _GXTexObj depthTexObj;
    Vec centerPos;
    Vec cameraPos;
    Vec cameraUp;
    CCharaPcs::CHandle* handle;
    CGObject* gObject;
    s32 model;
    u32 depthTexSize;
    u32 sourceTexObjs;
    u32 targetTexObjs;
    s32 i;
    f32 savedViewport[6];

    if (pass != 0 || *(u8*)((u8*)step + 0x1C) == 0) {
        return;
    }

    if (Game.game.m_currentMapId == 0x21) {
        GXGetViewportv(savedViewport);
    }

    Graphic.SetViewport();
    PSMTXCopy(CameraPcs.m_cameraMatrix, savedCameraMtx);
    PSMTX44Copy(CameraPcs.m_screenMatrix, savedScreenMtx);
    Graphic.GetBackBufferRect2(DAT_80238030, &sceneTexObj, 0, 0, 0x80, 0x80, 0, GX_NEAR, GX_TF_RGBA8, 0);

    gObject = (CGObject*)work[0];
    if (gObject == NULL) {
        return;
    }

    handle = (CCharaPcs::CHandle*)GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(u32*)(model + 0xF0) = 0;
    *(u32*)(model + 0xFC) = 0;

    if (Game.game.m_currentSceneId == 7) {
        centerPos.x = FLOAT_80330e4c;
        centerPos.y = FLOAT_80330e4c;
        centerPos.z = FLOAT_80330e4c;
    } else {
        centerPos = gObject->m_worldPosition;
    }
    centerPos.y += FLOAT_80330e60;

    depthTexSize = GXGetTexBufferSize(0x80, 0x80, GX_TF_Z24X8, GX_FALSE, 0);
    GXGetTexBufferSize(0x80, 0x80, GX_TF_RGBA8, GX_FALSE, 0);
    sourceTexObjs = work[8];

    if (*(u8*)((u8*)step + 0x38) != 0) {
        Graphic.GetBackBufferRect2(DAT_80238030, &depthTexObj, 0, 0, 0x80, 0x80, depthTexSize, GX_LINEAR,
                                   (_GXTexFmt)0x16, 1);
        GXSetViewport(FLOAT_80330e4c, FLOAT_80330e4c, FLOAT_80330e48, FLOAT_80330e48, FLOAT_80330e4c, FLOAT_80330e58);
        C_MTXPerspective(projectionMtx, FLOAT_80330eb8, FLOAT_80330e58, FLOAT_80330e58, FLOAT_80330ec0);
        GXSetProjection(projectionMtx, (_GXProjectionType)0);

        for (i = 0; i < 6; i++) {
            cameraPos = centerPos;
            cameraUp.x = FLOAT_80330e4c;
            cameraUp.y = FLOAT_80330e58;
            cameraUp.z = FLOAT_80330e4c;

            if (i == 3) {
                cameraPos.z -= FLOAT_80330e58;
            } else if (i < 3) {
                if (i == 1) {
                    cameraPos.z += FLOAT_80330e58;
                } else if (i < 1) {
                    cameraPos.x += FLOAT_80330e58;
                } else {
                    cameraPos.x -= FLOAT_80330e58;
                }
            } else if (i == 5) {
                cameraPos.y -= FLOAT_80330e58;
                cameraUp.y = FLOAT_80330e4c;
                cameraUp.z = FLOAT_80330e4c;
            } else {
                cameraPos.y += FLOAT_80330e58;
                cameraUp.y = FLOAT_80330e4c;
                cameraUp.z = FLOAT_80330e68;
            }

            C_MTXLookAt(lookAtMtx, (Point3d*)&centerPos, &cameraUp, (Point3d*)&cameraPos);
            Graphic.SetViewport();
            GXSetScissor(0, 0, 0x80, 0x80);
            RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor(
                DAT_8032ec70, FLOAT_80330e4c, FLOAT_80330e4c, FLOAT_80330e48, FLOAT_80330e48, (GXTexObj*)sourceTexObjs,
                0, 0, 0, (_GXBlendFactor)4, (_GXBlendFactor)5);

            GXSetViewport(FLOAT_80330e4c, FLOAT_80330e4c, FLOAT_80330e48, FLOAT_80330e48, FLOAT_80330e4c, FLOAT_80330e58);
            GXSetScissor(0, 0, 0x80, 0x80);
            PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);
            GXSetProjection(projectionMtx, (_GXProjectionType)0);

            if (((gObject->m_weaponNodeFlags & 1) != 0 || gObject->m_attachOwner != NULL) &&
                gObject->m_attachOwner != NULL && gObject->m_attachOwner->m_charaModelHandle != NULL) {
                CCharaPcs::CHandle* owner = gObject->m_attachOwner->m_charaModelHandle;
                s32 ownerModel = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(owner);

                *(u32*)(ownerModel + 0xE4) = (u32)work;
                *(u32*)(ownerModel + 0xE8) = (u32)step;
                *(u32*)(ownerModel + 0xF0) = (u32)Mana_BeforeDrawShadowLockEnvCallback;
                *(u32*)(ownerModel + 0x100) = (u32)Chara_DrawShadowMeshDLCallback;
                Draw__Q29CCharaPcs7CHandleFi(owner, 1);
                *(u32*)(ownerModel + 0xE4) = 0;
                *(u32*)(ownerModel + 0xE8) = 0;
                *(u32*)(ownerModel + 0xF0) = 0;
                *(u32*)(ownerModel + 0x100) = 0;
            }

            Graphic.GetBackBufferRect2(DAT_80238030, (_GXTexObj*)sourceTexObjs, 0, 0, 0x80, 0x80, depthTexSize,
                                       GX_NEAR, GX_TF_RGBA8, 0);
            depthTexSize += GXGetTexBufferSize(0x80, 0x80, GX_TF_RGBA8, GX_FALSE, 0);
            sourceTexObjs += 0x20;
        }

        PSMTXCopy(savedCameraMtx, CameraPcs.m_cameraMatrix);
        Graphic.SetViewport();
        GXSetScissor(0, 0, 0x280, 0x1C0);
        for (i = 0; i < 0x10; i++) {
            GXSetTevKColorSel((GXTevStageID)i, (GXTevKColorSel)6);
            GXSetTevKAlphaSel((GXTevStageID)i, (GXTevKAlphaSel)0);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(i, 0, 0);
        }
        *((u8*)work + 0xF4) = 1;
    }

    targetTexObjs = work[0x1F];
    if (*(u8*)((u8*)step + 0x38) == 0) {
        if (*((u8*)work + 0xF4) == 0) {
            GXInitTexObj((GXTexObj*)work[10], (void*)work[12], 0x80, 0x80, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObj((GXTexObj*)work[11], (void*)work[13], 0x80, 0x80, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
            drawParaboloidMap((GXTexObj*)work[8], (GXTexObj*)work[11], (void*)work[9], work[0x3B],
                              (GXTexObj*)(targetTexObjs + 0x28), 1);
            drawParaboloidMap((GXTexObj*)work[8], (GXTexObj*)work[10], (void*)work[9], work[0x3B],
                              (GXTexObj*)(targetTexObjs + 0x28), 0);
            RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor(
                DAT_8032ec70, FLOAT_80330e4c, FLOAT_80330e4c, FLOAT_80330e48, FLOAT_80330e48, &sceneTexObj, 0, 0, 0,
                (_GXBlendFactor)4, (_GXBlendFactor)5);
            *((u8*)work + 0xF4) = 1;
        }
    } else {
        GXInitTexObj((GXTexObj*)work[10], (void*)work[12], 0x80, 0x80, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD((GXTexObj*)work[10], GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXInitTexObj((GXTexObj*)work[11], (void*)work[13], 0x80, 0x80, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD((GXTexObj*)work[11], GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        drawParaboloidMap((GXTexObj*)work[0x1E], (GXTexObj*)work[11], (void*)work[9], work[0x3B],
                          (GXTexObj*)(targetTexObjs + 0x28), 1);
        drawParaboloidMap((GXTexObj*)work[0x1E], (GXTexObj*)work[10], (void*)work[9], work[0x3B],
                          (GXTexObj*)(targetTexObjs + 0x28), 0);
        Graphic.SetViewport();
        GXSetProjection(savedScreenMtx, (_GXProjectionType)0);
        PSMTXCopy(savedCameraMtx, CameraPcs.m_cameraMatrix);
        RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor(
            DAT_8032ec70, FLOAT_80330e4c, FLOAT_80330e4c, FLOAT_80330e48, FLOAT_80330e48, &sceneTexObj, 0, 0, 0,
            (_GXBlendFactor)4, (_GXBlendFactor)5);
    }

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    handle = (CCharaPcs::CHandle*)GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(u32*)(model + 0xF0) = (u32)Mana_BeforeDrawCallback;
    *(u32*)(model + 0xFC) = (u32)Mana_DrawMeshDLCallback;

    if (Game.game.m_currentMapId == 0x21) {
        GXSetViewport(savedViewport[0], savedViewport[1], savedViewport[2], savedViewport[3], savedViewport[4],
                      savedViewport[5]);
    }
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
 * PAL Address: 0x800d5f7c
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CreateWaterMesh(Vec* positionsInOut, Vec* normalsOut, Vec2d* uvOut, unsigned short* indicesOut, float size)
{
    float* pPos = (float*)positionsInOut;
    float* pNormal = (float*)normalsOut;
    float* pUv = (float*)uvOut;
    float radius = size * FLOAT_80330e5c;
    float step = size * FLOAT_80330e6c;
    u32 rowCounter = 0;
    double stepScale = (double)FLOAT_80330e6c;

    for (float zPos = radius; -radius <= zPos; zPos -= step) {
        u32 colCounter = 0;
        float* pos = pPos;
        float* normal = pNormal;
        float* uv = pUv;

        for (float xPos = -radius; xPos <= radius; xPos += step) {
            *pos = xPos;
            pos[1] = FLOAT_80330e4c;
            pos[2] = zPos;
            pPos += 3;
            pos += 3;

            *normal = FLOAT_80330e4c;
            normal[1] = FLOAT_80330e58;
            normal[2] = FLOAT_80330e4c;
            pNormal += 3;
            normal += 3;

            *uv = (float)((double)colCounter * stepScale);
            uv[1] = (float)((double)rowCounter * stepScale);
            pUv += 2;
            uv += 2;

            colCounter++;
        }
        rowCounter++;
    }

    int idxOffset = 0;
    int row = 0;
    short rowBase = 0;
    do {
        int pair = 8;
        short rowCounter2 = rowBase;
        do {
            *(short*)((char*)indicesOut + idxOffset) = rowCounter2;
            *(short*)((char*)indicesOut + idxOffset + 2) = rowCounter2 + 1;
            *(short*)((char*)indicesOut + idxOffset + 4) = rowCounter2 + 0x12;
            *(short*)((char*)indicesOut + idxOffset + 6) = rowCounter2 + 0x12;
            *(short*)((char*)indicesOut + idxOffset + 8) = rowCounter2 + 0x11;
            *(short*)((char*)indicesOut + idxOffset + 10) = rowCounter2;
            *(short*)((char*)indicesOut + idxOffset + 12) = rowCounter2 + 1;
            *(short*)((char*)indicesOut + idxOffset + 14) = rowCounter2 + 2;
            *(short*)((char*)indicesOut + idxOffset + 16) = rowCounter2 + 0x13;
            *(short*)((char*)indicesOut + idxOffset + 18) = rowCounter2 + 0x13;
            *(short*)((char*)indicesOut + idxOffset + 20) = rowCounter2 + 0x12;
            *(short*)((char*)indicesOut + idxOffset + 22) = rowCounter2 + 1;
            idxOffset += 0x18;
            pair--;
            rowCounter2 += 2;
        } while (pair != 0);
        row++;
        rowBase += 0x11;
    } while (row < 0x10);

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800d5bb4
 * PAL Size: 968b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void UpdateWaterMesh(VYmMana* mana)
{
    u8* work;
    float* waterHeightA;
    float* waterHeightB;
    Vec* positions;
    Vec origin;

    work = (u8*)mana;
    waterHeightA = *(float**)(work + 0x48);
    positions = *(Vec**)(work + 0x3C);
    waterHeightB = *(float**)(work + 0x4C);
    if (waterHeightA == NULL) {
        return;
    }

    for (int row = 1; row < 0x10; row++) {
        int rowBase = row * 0x11;
        for (int colBlock = 0; colBlock < 3; colBlock++) {
            int col = colBlock * 5 + 1;
            int idx = rowBase + col;

            waterHeightB[idx + 0] = FLOAT_80330e5c * waterHeightA[idx + 0] +
                                    FLOAT_80330e4c * (waterHeightA[idx + 1] + waterHeightA[idx - 1] +
                                                      waterHeightA[idx - 0x11] + waterHeightA[idx + 0x11]) -
                                    waterHeightB[idx + 0];

            waterHeightB[idx + 1] = FLOAT_80330e5c * waterHeightA[idx + 1] +
                                    FLOAT_80330e4c * (waterHeightA[idx + 2] + waterHeightA[idx + 0] +
                                                      waterHeightA[idx - 0x10] + waterHeightA[idx + 0x12]) -
                                    waterHeightB[idx + 1];

            waterHeightB[idx + 2] = FLOAT_80330e5c * waterHeightA[idx + 2] +
                                    FLOAT_80330e4c * (waterHeightA[idx + 3] + waterHeightA[idx + 1] +
                                                      waterHeightA[idx - 0x0F] + waterHeightA[idx + 0x13]) -
                                    waterHeightB[idx + 2];

            waterHeightB[idx + 3] = FLOAT_80330e5c * waterHeightA[idx + 3] +
                                    FLOAT_80330e4c * (waterHeightA[idx + 4] + waterHeightA[idx + 2] +
                                                      waterHeightA[idx - 0x0E] + waterHeightA[idx + 0x14]) -
                                    waterHeightB[idx + 3];

            waterHeightB[idx + 4] = FLOAT_80330e5c * waterHeightA[idx + 4] +
                                    FLOAT_80330e4c * (waterHeightA[idx + 5] + waterHeightA[idx + 3] +
                                                      waterHeightA[idx - 0x0D] + waterHeightA[idx + 0x15]) -
                                    waterHeightB[idx + 4];
        }
    }

    for (int i = 0; i < 0x121; i++) {
        float tmp = waterHeightA[i];
        waterHeightA[i] = waterHeightB[i];
        waterHeightB[i] = tmp;
        positions[i].y = waterHeightA[i];
    }

    DCFlushRange(positions, 0xD8C);
    CalculateNormal(mana);

    origin.x = *(float*)(work + 0x94);
    origin.y = *(float*)(work + 0xA4);
    origin.z = *(float*)(work + 0xB4);
    CalcWaterReflectionVector(*(Vec**)(work + 0x44), *(Vec**)(work + 0x3C), *(Vec**)(work + 0x40), 0x121, origin,
                              (float(*)[4])(work + 0x88), *(_GXColor**)(work + 0x5C), *(Vec2d**)(work + 0x58));
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
void CalculateNormal(VYmMana* mana)
{
    Vec* positions = *(Vec**)((u8*)mana + 0x3C);
    Vec* normals = *(Vec**)((u8*)mana + 0x40);
    u16* indices = *(u16**)((u8*)mana + 0x50);
    Vec edgeA;
    Vec edgeB;
    Vec faceNormal;

    for (int i = 0; i < 0x121; i++) {
        normals[i].x = FLOAT_80330e4c;
        normals[i].y = FLOAT_80330e4c;
        normals[i].z = FLOAT_80330e4c;
    }

    for (int tri = 0; tri < 0x200; tri++) {
        u16 idx0 = indices[0];
        u16 idx1 = indices[1];
        u16 idx2 = indices[2];

        edgeA.x = positions[idx1].x - positions[idx0].x;
        edgeA.y = positions[idx1].y - positions[idx0].y;
        edgeA.z = positions[idx1].z - positions[idx0].z;

        edgeB.x = positions[idx2].x - positions[idx0].x;
        edgeB.y = positions[idx2].y - positions[idx0].y;
        edgeB.z = positions[idx2].z - positions[idx0].z;

        PSVECCrossProduct(&edgeA, &edgeB, &faceNormal);
        PSVECNormalize(&faceNormal, &faceNormal);
        PSVECAdd(&normals[idx0], &faceNormal, &normals[idx0]);
        PSVECAdd(&normals[idx1], &faceNormal, &normals[idx1]);
        PSVECAdd(&normals[idx2], &faceNormal, &normals[idx2]);

        indices += 3;
    }

    for (int i = 0; i < 0x121; i++) {
        PSVECNormalize(&normals[i], &normals[i]);
    }

    DCFlushRange(normals, 0xD8C);
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
 * PAL Address: 0x800d4c7c
 * PAL Size: 1120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CalcReflectionVector2(
    Vec* reflectionVec,
    S16Vec* positions,
    S16Vec* normals,
    long count,
    unsigned long posScale,
    unsigned long normalScale,
    float (*matrix)[4],
    void* displayList,
    unsigned long displayListSize,
    _GXColor* color,
    S16Vec2d* texCoordA,
    S16Vec2d* texCoordB,
    CChara::CNode* node,
    PYmMana*,
    VYmMana*)
{
    Vec cameraPos;
    Vec nodePos;
    Vec matrixPos;
    Vec worldPos;
    Vec position;
    Vec normal;
    Vec eyeToPos;
    Vec2d uv;
    Mtx matrixCopy;
    Mtx nodeOffsetMtx;
    Mtx nodeRotMtx;
    Mtx workMtx;
    Mtx rotateMtx;
    u16* dl = (u16*)displayList;
    u16* dlEnd = (u16*)((u8*)displayList + displayListSize);
    const double zero = (double)FLOAT_80330e4c;
    const double denomBias = (double)FLOAT_80330e58;
    const double half = (double)FLOAT_80330e5c;
    const double warp = (double)FLOAT_80330e60;
    const double scale = (double)FLOAT_80330e64;
    char* compareName = (char*)&Game + 0xC7F4;

    cameraPos.x = CameraPcs._224_4_;
    cameraPos.y = CameraPcs._228_4_;
    cameraPos.z = CameraPcs._232_4_;

    PSMTXCopy(matrix, matrixCopy);
    PSMTXCopy((float (*)[4])((u8*)node + 0x14), nodeOffsetMtx);
    PSMTXCopy((float (*)[4])((u8*)node + 0x6C), workMtx);

    nodePos.x = workMtx[0][3];
    nodePos.y = workMtx[1][3];
    nodePos.z = workMtx[2][3];

    matrixPos.x = matrixCopy[0][3];
    matrixPos.y = matrixCopy[1][3];
    matrixPos.z = matrixCopy[2][3];
    PSVECAdd(&nodePos, &matrixPos, &worldPos);

    PSMTXCopy(workMtx, nodeRotMtx);
    PSMTXRotRad(rotateMtx, 'y', FLOAT_80330e48);
    nodeRotMtx[0][3] = worldPos.x;
    nodeRotMtx[1][3] = worldPos.y;
    nodeRotMtx[2][3] = worldPos.z;

    PSMTXCopy(nodeRotMtx, workMtx);
    workMtx[0][3] = FLOAT_80330e4c;
    workMtx[1][3] = FLOAT_80330e4c;
    workMtx[2][3] = FLOAT_80330e4c;

    while (dl < dlEnd) {
        u8 drawFmt = *(u8*)dl;
        u16 itemCount = *(u16*)((u8*)dl + 1);
        int i;

        if (IsHasDrawFmtDL__5CUtilFUc((void*)DAT_8032ec70, drawFmt) == 0) {
            break;
        }

        dl = (u16*)((u8*)dl + 3);
        for (i = 0; i < itemCount; i++) {
            u16 posIndex = dl[0];
            u16 normalIndex = dl[1];
            u16* next = dl + 4;
            float denom;
            double uVal;
            double vVal;
            u8* colorBytes = (u8*)&color[posIndex];

            if ((drawFmt & 7) == 2) {
                next = dl + 5;
            }

            ConvI2FVector__5CUtilFR3Vec6S16Vecl((void*)DAT_8032ec70, &position, &positions[posIndex], posScale);
            ConvI2FVector__5CUtilFR3Vec6S16Vecl((void*)DAT_8032ec70, &normal, &normals[normalIndex], normalScale);
            PSMTXMultVec(nodeRotMtx, &position, &position);
            PSMTXMultVec(workMtx, &normal, &normal);

            PSVECSubtract(&position, &cameraPos, &eyeToPos);
            C_VECReflect(&eyeToPos, &normal, &reflectionVec[posIndex]);

            if (strcmp(DAT_80330e50, compareName) == 0) {
                PSMTXMultVec(rotateMtx, &reflectionVec[posIndex], &reflectionVec[posIndex]);
            }

            if ((double)reflectionVec[posIndex].z < zero) {
                colorBytes[0] = 0;
                colorBytes[1] = 0;
                colorBytes[2] = 0;
                colorBytes[3] = 0;
            } else {
                colorBytes[0] = 0xFF;
                colorBytes[1] = 0xFF;
                colorBytes[2] = 0xFF;
                colorBytes[3] = 0xFF;
            }

            denom = (float)(denomBias + (double)reflectionVec[posIndex].z);
            uVal = (double)(float)((double)(-reflectionVec[posIndex].x / denom) * half + half);
            vVal = (double)(float)((double)(-reflectionVec[posIndex].y / denom) * half + half);
            uv.x = -(float)(scale * (double)(float)(warp * (double)(float)(uVal - half) - uVal) - uVal);
            uv.y = -(float)(scale * (double)(float)(warp * (double)(float)(vVal - half) - vVal) - vVal);
            ConvF2IVector2d__5CUtilFR8S16Vec2d5Vec2dl((void*)DAT_8032ec70, &texCoordA[posIndex], &uv, 12);

            denom = (float)(denomBias - (double)reflectionVec[posIndex].z);
            uVal = (double)(float)((double)(-reflectionVec[posIndex].x / denom) * half + half);
            vVal = (double)(float)((double)(-reflectionVec[posIndex].y / denom) * half + half);
            uv.x = -(float)(scale * (double)(float)(warp * (double)(float)(uVal - half) - uVal) - uVal);
            uv.y = -(float)(scale * (double)(float)(warp * (double)(float)(vVal - half) - vVal) - vVal);
            ConvF2IVector2d__5CUtilFR8S16Vec2d5Vec2dl((void*)DAT_8032ec70, &texCoordB[posIndex], &uv, 12);

            dl = next;
        }
    }

    DCFlushRange(texCoordA, count << 2);
    DCFlushRange(texCoordB, count << 2);
    DCFlushRange(color, count << 2);
    DCFlushRange(reflectionVec, count * 0xC);
}

