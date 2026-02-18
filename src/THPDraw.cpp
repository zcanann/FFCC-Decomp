#include "dolphin/thp/THPDraw.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "ffcc/gxfunc.h"

void THPGXYuv2RgbDraw(u32* yImage, u32* uImage, u32* vImage, s16 x, s16 y, s16 texWidth, s16 texHeight, s16 polyWidth, s16 polyHeight) {
    GXTexObj yTexObj;
    GXTexObj uTexObj;
    GXTexObj vTexObj;
    
    GXInitTexObj(&yTexObj, yImage, texWidth, texHeight, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&yTexObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&yTexObj, GX_TEXMAP0);
    
    GXInitTexObj(&uTexObj, uImage, texWidth >> 1, texHeight >> 1, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&uTexObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&uTexObj, GX_TEXMAP1);
    
    GXInitTexObj(&vTexObj, vImage, texWidth >> 1, texHeight >> 1, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&vTexObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&vTexObj, GX_TEXMAP2);
    
    GXBegin(GX_QUADS, GX_VTXFMT7, 4);
    
    GXPosition3s16(x, y, 0);
    GXTexCoord2s16(0, 0);
    
    GXPosition3s16(x + polyWidth, y, 0);
    GXTexCoord2s16(1, 0);
    
    GXPosition3s16(x + polyWidth, y + polyHeight, 0);
    GXTexCoord2s16(1, 1);
    
    GXPosition3s16(x, y + polyHeight, 0);
    GXTexCoord2s16(0, 1);
}

/*
 * --INFO--
 * PAL Address: 0x80105b58
 * PAL Size: 1268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void THPGXYuv2RgbSetup(GXRenderModeObj* rmode) {
    Mtx modelMtx;
    Mtx44 projMtx;
    GXColorS10 tevColor;
    GXColor kColor0;
    GXColor kColor1;
    GXColor kColor2;
    u16 fbWidth;
    u16 efbHeight;

    fbWidth = rmode->fbWidth;
    efbHeight = rmode->efbHeight;

    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    C_MTXOrtho(projMtx, 0.0f, (f32)efbHeight, 0.0f, (f32)fbWidth, 0.0f, 1.0f);
    GXSetProjection(projMtx, GX_ORTHOGRAPHIC);
    GXSetViewport(0.0f, 0.0f, (f32)fbWidth, (f32)efbHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, fbWidth, efbHeight);

    PSMTXIdentity(modelMtx);
    GXLoadPosMtxImm(modelMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    _GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetDispCopyGamma(GX_GM_1_0);
    GXSetNumChans(0);

    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXInvalidateTexAll();

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);

    GXSetNumTevStages(4);

    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_C0);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_A0);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
    GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

    _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP2, GX_COLOR_NULL);
    _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, GX_CC_CPREV);
    _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_FALSE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_APREV);
    _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K1);
    GXSetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_K1_A);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);

    _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_CPREV);
    _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);

    _GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    _GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_APREV, GX_CC_CPREV, GX_CC_KONST, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    _GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    _GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevKColorSel(GX_TEVSTAGE3, GX_TEV_KCSEL_K2);

    tevColor.r = -90;
    tevColor.g = 0;
    tevColor.b = -114;
    tevColor.a = 135;
    GXSetTevColorS10(GX_TEVREG0, tevColor);

    kColor0.r = 0;
    kColor0.g = 0;
    kColor0.b = 226;
    kColor0.a = 88;
    GXSetTevKColor(GX_KCOLOR0, kColor0);

    kColor1.r = 179;
    kColor1.g = 0;
    kColor1.b = 0;
    kColor1.a = 182;
    GXSetTevKColor(GX_KCOLOR1, kColor1);

    kColor2.r = 0;
    kColor2.g = 135;
    kColor2.b = 0;
    kColor2.a = 0;
    GXSetTevKColor(GX_KCOLOR2, kColor2);

    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);

    GXSetCullMode(GX_CULL_NONE);
    _GXSetAlphaCompare(GX_GEQUAL, 0, GX_AOP_AND, GX_ALWAYS, 0);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
}

/*
 * --INFO--
 * PAL Address: 0x8010604c
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void THPGXRestore(void) {
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    _GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_SET);
    GXSetNumTexGens(1);
    GXSetNumChans(0);
    GXSetNumTevStages(1);

    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    _GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);

    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetAlphaCompare(GX_GEQUAL, 0, GX_AOP_AND, GX_ALWAYS, 0);
}
