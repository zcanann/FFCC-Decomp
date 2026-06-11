#include "ffcc/p_graphic.h"
#include "ffcc/color.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/gxfunc.h"
#include "ffcc/gobject.h"
#include "ffcc/joybus.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/p_camera.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <math.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" {
void create__11CGraphicPcsFv(CGraphicPcs*);
void destroy__11CGraphicPcsFv(CGraphicPcs*);
void calc__11CGraphicPcsFv(CGraphicPcs*);
void drawBegin__11CGraphicPcsFv(CGraphicPcs*);
void drawWait__11CGraphicPcsFv(CGraphicPcs*);
void drawFlip__11CGraphicPcsFv(CGraphicPcs*);
void drawEnd__11CGraphicPcsFv(CGraphicPcs*);
void drawCopy__11CGraphicPcsFv(CGraphicPcs*);
void preDrawEnvInit__11CGraphicPcsFv(CGraphicPcs*);
void stdDrawEnvInit__11CGraphicPcsFv(CGraphicPcs*);
}

static CProcessTableCallback s_graphicTableDescCreate = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__11CGraphicPcsFv)};
static CProcessTableCallback s_graphicTableDescDestroy = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__11CGraphicPcsFv)};
static CProcessTableCallback s_graphicTableDescCalc = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__11CGraphicPcsFv)};
static CProcessTableCallback s_graphicTableDescDrawWait = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawWait__11CGraphicPcsFv)};
static CProcessTableCallback s_graphicTableDescDrawFlip = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawFlip__11CGraphicPcsFv)};
static CProcessTableCallback s_graphicTableDescDrawBegin = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBegin__11CGraphicPcsFv)};
static CProcessTableCallback s_graphicTableDescDrawCopy = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawCopy__11CGraphicPcsFv)};
static CProcessTableCallback s_graphicTableDescDrawEnd = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawEnd__11CGraphicPcsFv)};
static CProcessTableCallback s_graphicTableDescPreDrawEnvInit = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(preDrawEnvInit__11CGraphicPcsFv)};
static CProcessTableCallback s_graphicTableDescStdDrawEnvInit = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(stdDrawEnvInit__11CGraphicPcsFv)};

inline CGraphicPcs::CGraphicPcs()
{
    CProcessTable* table = &m_table;

    table->m_fields.m_create = s_graphicTableDescCreate;
    table->m_fields.m_destroy = s_graphicTableDescDestroy;
    table->m_fields.m_entries[0].m_callback = s_graphicTableDescCalc;
    table->m_fields.m_entries[1].m_callback = s_graphicTableDescDrawWait;
    table->m_fields.m_entries[2].m_callback = s_graphicTableDescDrawFlip;
    table->m_fields.m_entries[3].m_callback = s_graphicTableDescDrawBegin;
    table->m_fields.m_entries[4].m_callback = s_graphicTableDescDrawCopy;
    table->m_fields.m_entries[5].m_callback = s_graphicTableDescDrawEnd;
    table->m_fields.m_entries[6].m_callback = s_graphicTableDescPreDrawEnvInit;
    table->m_fields.m_entries[7].m_callback = s_graphicTableDescStdDrawEnvInit;
}

CGraphicPcs GraphicPcs;
static const char s_CGraphicPcs[] = "CGraphicPcs";
static const char sGraphicPcsManagerClassName[] = "CManager";
static const char sGraphicPcsProcessClassName[] = "CProcess";

CProcessTable CGraphicPcs::m_table = {
    const_cast<char*>(s_CGraphicPcs),
    {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0x22, 0x8,
        0, 0, 0,
        0x26, 0x9,
        0, 0, 0,
        0x27, 0xC,
        0, 0, 0,
        0x29, 0x9,
        0, 0, 0,
        0x48, 1,
        0, 0, 0,
        0x4B, 0x9,
        0, 0, 0,
        0x2B, 0x9,
        0, 0, 0,
        0x34, 0x9,
    },
};

static const char s_scenegraph_step_none[] = "";
static const char s_scenegraph_step_x8[] = "x8";
static const char s_scenegraph_step_x0[] = "x0";
static const char s_scenegraph_step_x1_8[] = "x1/8";
static const char s_scenegraph_step_x1_4[] = "x1/4";
static const char s_scenegraph_step_x1_2[] = "x1/2";
extern const float kGraphicZero;
extern const float kGraphicScreenHeight;
extern const float kGraphicScreenWidth;
extern const float kGraphicOrthoFarZ;
extern const float kGraphicOne;
extern const float kScreenFadeHalfPi;
extern const float kGraphicColorMax;
extern const float kScreenFadeBarEdge;
extern const float kScreenFadeRingWidth;
extern const float kGraphicScreenCenterX;
extern const float kGraphicScreenCenterY;
extern const float kScreenFadeCircleRadius;
extern const float kGraphicHalf;
extern const float kSFCircleAngleStep;
extern const float kDebugBarLeft;
extern const float kDebugBarTop;
extern const float kDebugBarRight;
extern const float kDebugBarBottom;
extern const float kDebugBarFrameBudget;
extern const float kDebugBarMoveBottom;
extern const float kDebugBarObjectTop;
extern const float kDebugIndicatorTop;
extern const float kDebugIndicatorFrameRight;
extern const float kDebugIndicatorBottom;
extern const float kDebugIndicatorFifoLeft;
extern const float kDebugIndicatorFifoRight;
static const int kDebugBarLineStep = 8;
static const char s_debug_pad_port_fmt[] = "%dP";
static const char s_debug_frame_fmt[] = "%d";
extern const float kDofDefaultNearZ;
extern const float kDofDefaultFarZ;

static const char s_graphic_order_debug_fmt[] = "%s(%d) %.3f%%";
static const char s_graphic_move_debug_fmt[] = " MOVE=%.1f%% BG=%.1f%% OBJ=%.1f%% UP=%.1f%% HIT=%.1f%% SCR=%.1f%%";
static const char s_graphic_pad_input_fmt[] = "%c%c%c%c%c%c%c%c%c%c";
static const char s_p_graphic_cpp[] = "p_graphic.cpp";
static const char* s_scenegraph_step_labels[] = {
    s_scenegraph_step_none,
    s_scenegraph_step_x8,
    s_scenegraph_step_x0,
    s_scenegraph_step_x1_8,
    s_scenegraph_step_x1_4,
    s_scenegraph_step_x1_2,
};

STATIC_ASSERT(offsetof(CGraphicPcs, m_screenFade) == 0x04);
STATIC_ASSERT(sizeof(CGraphicPcs::ScreenFadeSlot) == 0x2C);
STATIC_ASSERT(offsetof(CGraphicPcs::ScreenFadeSlot, m_timer) == 0x00);
STATIC_ASSERT(offsetof(CGraphicPcs::ScreenFadeSlot, m_duration) == 0x04);
STATIC_ASSERT(offsetof(CGraphicPcs::ScreenFadeSlot, m_colorA) == 0x08);
STATIC_ASSERT(offsetof(CGraphicPcs::ScreenFadeSlot, m_colorB) == 0x0C);
STATIC_ASSERT(offsetof(CGraphicPcs::ScreenFadeSlot, m_invert) == 0x10);
STATIC_ASSERT(offsetof(CGraphicPcs::ScreenFadeSlot, m_mode) == 0x14);
STATIC_ASSERT(offsetof(CGraphicPcs::ScreenFadeSlot, m_targetYOffs) == 0x1C);
STATIC_ASSERT(offsetof(CGraphicPcs::ScreenFadeSlot, m_phase) == 0x20);
STATIC_ASSERT(offsetof(CGraphicPcs::ScreenFadeSlot, m_stretch) == 0x24);

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGraphicPcs::drawSFRect(float x0, float y0, float x1, float y1, _GXColor color)
{
    drawSFRect(x0, y0, x1, y1, color, color);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGraphicPcs::drawSFRect(float x0, float y0, float x1, float y1, _GXColor topColor, _GXColor bottomColor)
{
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x0, y0, kGraphicZero);
    GXColor1u32(*(u32*)&topColor);
    GXTexCoord2u16(0, 0);
    GXPosition3f32(x1, y0, kGraphicZero);
    GXColor1u32(*(u32*)&topColor);
    GXTexCoord2u16(2, 0);
    GXPosition3f32(x1, y1, kGraphicZero);
    GXColor1u32(*(u32*)&bottomColor);
    GXTexCoord2u16(2, 2);
    GXPosition3f32(x0, y1, kGraphicZero);
    GXColor1u32(*(u32*)&bottomColor);
    GXTexCoord2u16(0, 2);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGraphicPcs::drawSFCircle(int innerRadius, int outerRadius, int centerX, int centerY, _GXColor color)
{
    drawSFCircle(innerRadius, outerRadius, centerX, centerY, color, color);
}

/*
 * --INFO--
 * PAL Address: 0x80045178
 * PAL Size: 4256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::drawScreenFade()
{
    Mtx44 orthoMtx;
    Mtx cameraMtx;
    Mtx44 screenMtx;
    Mtx44 worldScreenMtx;
    Mtx identityMtx;

    C_MTXOrtho(orthoMtx, kGraphicZero, kGraphicScreenHeight, kGraphicZero, kGraphicScreenWidth, kGraphicZero, kGraphicOrthoFarZ);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTXCopy(cameraMtx, screenMtx);
    screenMtx[3][2] = kGraphicZero;
    screenMtx[3][1] = kGraphicZero;
    screenMtx[3][0] = kGraphicZero;
    screenMtx[3][3] = kGraphicOne;
    PSMTX44Copy(CameraPcs.m_screenMatrix, worldScreenMtx);
    PSMTX44Concat(worldScreenMtx, screenMtx, worldScreenMtx);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 1);

    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, 0);
    GXLoadTexMtxImm(identityMtx, GX_TEXMTX0, GX_MTX2x4);

    for (int slot = 0; slot < 4; slot++) {
        ScreenFadeSlot* slotData = &m_screenFade[slot];

        if ((slotData->m_invert == 0) && (slotData->m_timer == 0)) {
            continue;
        }
        _GXSetBlendMode((GXBlendMode)1, (GXBlendFactor)4, (GXBlendFactor)5, (GXLogicOp)1);
        GXSetZCompLoc(0);
        _GXSetAlphaCompare((GXCompare)6, 1, (GXAlphaOp)0, (GXCompare)7, 0);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        GXSetCullMode(GX_CULL_NONE);
        GXSetNumTevStages(1);
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

        GXSetChanAmbColor(GX_COLOR0A0, CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

        float t = (float)slotData->m_timer / (float)slotData->m_duration;
        if (slotData->m_invert != 0) {
            t = kGraphicOne - t;
        }
        const float fadeWave = (float)sin((double)(kScreenFadeHalfPi * t));
        const u8 fadeAlpha = (u8)(kGraphicColorMax * fadeWave);

        _GXColor baseColor;
        _GXColor baseColor2;
        baseColor2.r = slotData->m_colorA.r;
        baseColor2.g = slotData->m_colorA.g;
        baseColor2.b = slotData->m_colorA.b;
        baseColor2.a = slotData->m_colorA.a;
        baseColor.r = slotData->m_colorA.r;
        baseColor.g = slotData->m_colorA.g;
        baseColor.b = slotData->m_colorA.b;
        baseColor.a = slotData->m_colorA.a;
        baseColor.a = fadeAlpha;
        baseColor2.a = 0;

        if (slot == 3) {
            const int barHeight = (int)(kScreenFadeBarEdge * fadeWave);
            const int barEdge = (int)(kScreenFadeRingWidth * fadeWave);

            drawSFRect(kGraphicZero, kGraphicZero, kGraphicScreenWidth, (float)barHeight, baseColor, baseColor);
            drawSFRect(kGraphicZero, (float)barHeight, kGraphicScreenWidth, (float)(barHeight + barEdge), baseColor, baseColor2);
            drawSFRect(kGraphicZero, kGraphicScreenHeight, kGraphicScreenWidth, (float)(448 - barHeight), baseColor, baseColor);
            drawSFRect(kGraphicZero, (float)(448 - barHeight), kGraphicScreenWidth, (float)((448 - barHeight) - barEdge), baseColor, baseColor2);
            continue;
        }

        if (slot == 2) {
            const int mode = slotData->m_mode;
            if (mode == 0) {
            drawSlot2Fullscreen:
                drawSFRect(kGraphicZero, kGraphicZero, kGraphicScreenWidth, kGraphicScreenHeight, baseColor, baseColor);
            } else if (mode == 1) {
                CGObject* obj = static_cast<CGObject*>(slotData->m_targetObj);
                if (obj == NULL) {
                    goto drawSlot2Fullscreen;
                }
                Vec pos = obj->m_worldPosition;
                pos.y += slotData->m_targetYOffs;
                PSMTX44MultVec(worldScreenMtx, &pos, &pos);

                const float sx = kGraphicScreenCenterX * pos.x + kGraphicScreenCenterX;
                const float sy = kGraphicScreenCenterY - kGraphicScreenCenterY * pos.y;
                pos.x = sx;
                pos.y = sy;
                float clampedX = 0.0f;
                clampedX = (sx < clampedX) ? clampedX : ((kGraphicScreenWidth < sx) ? kGraphicScreenWidth : sx);
                pos.x = clampedX;
                {
                    float clampedY = 0.0f;
                    clampedY = (pos.y < clampedY) ? clampedY : ((kGraphicScreenHeight < pos.y) ? kGraphicScreenHeight : pos.y);
                    pos.y = clampedY;
                }

                const int radius = (int)(kScreenFadeCircleRadius * (kGraphicOne - fadeWave));
                drawSFCircle(0x500, radius, (int)pos.x, (int)pos.y, baseColor, baseColor);
                drawSFCircle(radius, radius - 8, (int)pos.x, (int)pos.y, baseColor, baseColor2);
            }
            continue;
        }

        if (slot == 0) {
            if (slotData->m_timer < (slotData->m_duration - 1)) {
                GXSetNumTexGens(1);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
                GXLoadTexObj(&Graphic.m_smallBackTexObj, GX_TEXMAP0);

                t = slotData->m_amplitude * (kGraphicOne - t);
                const float offX = slotData->m_stretch * ((kGraphicScreenCenterX * t) * (float)sin((double)slotData->m_phase));
                const float offY = slotData->m_stretch * ((kGraphicScreenCenterY * t) * (float)cos((double)slotData->m_phase));
                t += kGraphicOne;

                drawSFRect((kGraphicScreenCenterX + offX) - kGraphicScreenCenterX * t,
                           (kGraphicScreenCenterY + offY) - kGraphicScreenCenterY * t,
                           (kGraphicScreenCenterX + offX) + kGraphicScreenCenterX * t,
                           (kGraphicScreenCenterY + offY) + kGraphicScreenCenterY * t,
                           baseColor, baseColor);
            }
            continue;
        }

        if (slot == 1) {
            const int mode = slotData->m_mode;
            if (mode == 0) {
                continue;
            }
            if (mode == 4) {
                GXSetNumTexGens(1);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                _GXSetTevColorIn(GX_TEVSTAGE0, (_GXTevColorArg)0xF, (_GXTevColorArg)8, (_GXTevColorArg)10, (_GXTevColorArg)0xF);
                _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, GX_TRUE, GX_TEVPREV);
                _GXSetTevAlphaIn(GX_TEVSTAGE0, (_GXTevAlphaArg)7, (_GXTevAlphaArg)4, (_GXTevAlphaArg)5, (_GXTevAlphaArg)7);
                _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

                int tile = 0;
                do {
                    CColor gradColor[2];
                    _GXTexObj backTexObj;
                    const int x = (tile & 1) ? 0x140 : 0;
                    const int y = (tile & 2) ? 0xE0 : 0;
                    const int row = (tile & 2) ? 1 : 0;

                    Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backTexObj, x, y, 0x140, 0xE0, 0,
                                               GX_NEAR, GX_TF_RGBA8, 0);
                    GXLoadTexObj(&backTexObj, GX_TEXMAP0);

                    baseColor.r = slotData->m_colorA.r;
                    baseColor.g = slotData->m_colorA.g;
                    baseColor.b = slotData->m_colorA.b;
                    baseColor.a = slotData->m_colorA.a;
                    baseColor2.r = slotData->m_colorB.r;
                    baseColor2.g = slotData->m_colorB.g;
                    baseColor2.b = slotData->m_colorB.b;
                    baseColor2.a = slotData->m_colorB.a;

                    const float t0 = (float)row * kGraphicHalf;
                    const float t1 = (float)(row + 1) * kGraphicHalf;
                    gradColor[0].color.r = (u8)(t0 * ((float)slotData->m_colorB.r - (float)baseColor.r) + (float)baseColor.r);
                    gradColor[0].color.g = (u8)(t0 * ((float)slotData->m_colorB.g - (float)baseColor.g) + (float)baseColor.g);
                    gradColor[0].color.b = (u8)(t0 * ((float)slotData->m_colorB.b - (float)baseColor.b) + (float)baseColor.b);
                    gradColor[0].color.a = 0xFF;

                    gradColor[1].color.r = (u8)(t1 * ((float)slotData->m_colorB.r - (float)baseColor.r) + (float)baseColor.r);
                    gradColor[1].color.g = (u8)(t1 * ((float)slotData->m_colorB.g - (float)baseColor.g) + (float)baseColor.g);
                    gradColor[1].color.b = (u8)(t1 * ((float)slotData->m_colorB.b - (float)baseColor.b) + (float)baseColor.b);
                    gradColor[1].color.a = 0xFF;

                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    GXPosition3f32((float)x, (float)y, kGraphicZero);
                    GXColor1u32(*(u32*)&gradColor[0].color);
                    GXTexCoord2u16(0, 0);
                    GXPosition3f32((float)(x + 0x140), (float)y, kGraphicZero);
                    GXColor1u32(*(u32*)&gradColor[0].color);
                    GXTexCoord2u16(2, 0);
                    GXPosition3f32((float)(x + 0x140), (float)(y + 0xE0), kGraphicZero);
                    GXColor1u32(*(u32*)&gradColor[1].color);
                    GXTexCoord2u16(2, 2);
                    GXPosition3f32((float)x, (float)(y + 0xE0), kGraphicZero);
                    GXColor1u32(*(u32*)&gradColor[1].color);
                    GXTexCoord2u16(0, 2);
                    tile++;
                } while (tile < 4);
                continue;
            } else {
                if (mode == 2) {
                    _GXSetBlendMode((GXBlendMode)1, (GXBlendFactor)4, (GXBlendFactor)1, (GXLogicOp)5);
                } else if (mode == 3) {
                    _GXSetBlendMode((GXBlendMode)3, (GXBlendFactor)4, (GXBlendFactor)1, (GXLogicOp)5);
                }

                drawSFRect(kGraphicZero, kGraphicZero, kGraphicScreenWidth, kGraphicScreenHeight,
                           slotData->m_colorA, slotData->m_colorB);
            }
        }
    }

    PSMTX44Copy(CameraPcs.m_screenMatrix, orthoMtx);
    GXSetProjection(orthoMtx, GX_PERSPECTIVE);
}
/*
 * --INFO--
 * PAL Address: 0x80046218
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CGraphicPcs::GetScreenFadeExecutingBit()
{
    unsigned int result = 0;

    for (int i = 0; i < 4; i++) {
        if ((m_screenFade[i].m_invert != 0) || (m_screenFade[i].m_timer != 0)) {
            result |= 1U << i;
        }
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x800462b8
 * PAL Size: 596b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::drawSFCircle(int innerRadius, int outerRadius, int centerX, int centerY, _GXColor innerColor, _GXColor outerColor)
{
    float ringPoints[32][4];
    const float step = kSFCircleAngleStep;

    for (int i = 0; i < 32; i++) {
        const float angle = step * (float)i;
        const float s = (float)sin(angle);
        const float c = (float)cos(angle);

        ringPoints[i][0] = s * (float)innerRadius + (float)centerX;
        ringPoints[i][1] = c * (float)innerRadius + (float)centerY;
        ringPoints[i][2] = s * (float)outerRadius + (float)centerX;
        ringPoints[i][3] = c * (float)outerRadius + (float)centerY;
    }

    GXBegin((GXPrimitive)0x80, GX_VTXFMT0, 0x80);
    const float z = kGraphicZero;
    const u32 innerColorWord = *(u32*)&innerColor;
    const u32 outerColorWord = *(u32*)&outerColor;
    for (int i = 0; i < 32; i++) {
        const float* cur = ringPoints[i];
        const float* nxt = ringPoints[(i + 1) % 32];

        GXPosition3f32(cur[0], cur[1], z);
        GXColor1u32(innerColorWord);
        GXTexCoord2u16(0, 0);

        GXPosition3f32(nxt[0], nxt[1], z);
        GXColor1u32(innerColorWord);
        GXTexCoord2u16(0, 0);

        GXPosition3f32(nxt[2], nxt[3], z);
        GXColor1u32(outerColorWord);
        GXTexCoord2u16(0, 0);

        GXPosition3f32(cur[2], cur[3], z);
        GXColor1u32(outerColorWord);
        GXTexCoord2u16(0, 0);
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGraphicPcs::calcScreenFade()
{
    for (int i = 0; i < 4; i++) {
        if (m_screenFade[i].m_timer > 0 && i != 1) {
            m_screenFade[i].m_timer--;
            if (m_screenFade[i].m_timer == 0) {
                m_screenFade[i].m_targetObj = 0;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004650c
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::stdDrawEnvInit()
{
	MaterialMan.SaveCurrentEnvAsStd();
}

/*
 * --INFO--
 * PAL Address: 0x80046538
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::preDrawEnvInit()
{
    MaterialMan.SetDefaultDrawEnv(0x000ACE0F);
}

/*
 * --INFO--
 * PAL Address: 0x80046594
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::setViewport()
{
	Graphic.SetViewport();
}

/*
 * --INFO--
 * PAL Address: 0x800465bc
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::drawCopy()
{
	if (m_copySaveFlag != 0) {
		Graphic.CopySaveFrameBuffer();
		m_copySaveFlag = 0;
	}

	if (m_dofFlag != 0) {
		Graphic.RenderDOF(m_dofFlagA, m_dofFlagB, m_dofNearZ, m_dofFarZ, m_dofTarget, m_dofMode);
	}

	int initBlur = 0;
	if ((m_blurMode == 1) && (Graphic.m_blurActive == 0)) {
		Graphic.m_blurActive = 1;
		Graphic.InitBlurParameter();
		initBlur = 1;
		m_blurStep = m_blurB / m_blurR;
		m_blurFadeOutFlag = 0;
	}

	if ((m_blurMode != 0) || (Graphic.m_blurActive != 0) || (m_blurFadeOutFlag != 0)) {
		if (m_blurMode != Graphic.m_blurActive) {
			m_blurFadeOutFlag = 1;
		}

		Graphic.RenderBlur(initBlur, m_blurMode2, m_blurA, m_blurG, m_blurB, m_blurScale);

		if (m_blurFadeOutFlag != 0) {
			if (m_blurB - m_blurStep <= 0) {
				m_blurB = 0;
				m_blurFadeOutFlag = 0;
				m_blurMode = 0;
				Graphic.m_blurActive = 0;
			} else {
				m_blurB -= m_blurStep;
			}
		}
	}

	drawScreenFade();
}

/*
 * --INFO--
 * PAL Address: 0x8004674c
 * PAL Size: 2812b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void setBarColor(GXColor& dst, const u32& colorWord)
{
    const GXColor* src = (const GXColor*)&colorWord;
    dst.r = src->r;
    dst.g = src->g;
    dst.b = src->b;
    dst.a = src->a;
}

void CGraphicPcs::drawBar()
{
    Mtx44 ortho;
    Mtx identity;
    C_MTXOrtho(ortho, kGraphicZero, kGraphicScreenHeight, kGraphicZero, kGraphicScreenWidth, kGraphicZero, kGraphicOrthoFarZ);
    GXSetProjection(ortho, GX_ORTHOGRAPHIC);

    _GXSetBlendMode((GXBlendMode)1, (GXBlendFactor)4, (GXBlendFactor)5, (GXLogicOp)1);
    GXSetZCompLoc((GXBool)0);
    _GXSetAlphaCompare((GXCompare)6, 1, (GXAlphaOp)0, (GXCompare)7, 0);
    GXSetZMode((GXBool)0, GX_LEQUAL, (GXBool)0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, (GXBool)0, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetChanCtrl(GX_ALPHA0, (GXBool)0, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 1);
    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, GX_PNMTX0);
    GXLoadTexMtxImm(identity, GX_TEXMTX0, GX_MTX2x4);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

    int drawText;
    bool useDebugPad;
    useDebugPad = drawText = 0;
    if ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) {
        useDebugPad = true;
    }
    int padState;
    if (useDebugPad) {
        padState = 0;
    } else {
        int padIndex = 0;
        padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
        padState = Pad.GetPadInputs()[padIndex].holdOverride;
    }
    if ((padState != 0) && (Joybus.GetPadType(0) != 0x40000)) {
        drawText = 1;
    }
    const int textFlag = (u8)drawText;

    float x = kDebugBarLeft;
    GXColor barColor = {0x80, 0x80, 0x80, 0xFF};
    drawSFRect(kDebugBarLeft, kDebugBarTop, kDebugBarRight, kDebugBarBottom, barColor, barColor);

    int hue;
    u32 y;
    CSystem::COrder* order = System.GetFirstOrder();
    const int orderCount = System.m_orderCount;
    int i = 0;
    hue = 0;
    y = 0x10;
    for (; i < orderCount; i++) {
        const int priority = order->m_priority;
        const float lastTime = order->m_lastTime;
        setBarColor(barColor, Math.Hsb2Rgb(hue / orderCount, 100, 100));
        const float width = (kGraphicScreenCenterX * lastTime) / kDebugBarFrameBudget;

        if (priority == 0x26) {
            drawSFRect(x, textFlag ? static_cast<float>(static_cast<int>(y)) : kDebugBarMoveBottom,
                       kGraphicOne + (x + width), kDebugBarTop, barColor, barColor);
            x += width;
        } else if (priority != 0x27) {
            drawSFRect(x, textFlag ? static_cast<float>(static_cast<int>(y)) : kDebugBarObjectTop,
                       kGraphicOne + (x + width), kDebugBarMoveBottom, barColor, barColor);
            x += width;
        }

        if (i == orderCount - 1) {
            setBarColor(barColor, Math.Hsb2Rgb(0, 100, 100));
            const float soundWidth = (kGraphicScreenCenterX * Sound.GetPerformance()) / kDebugBarFrameBudget;

            drawSFRect(x, textFlag ? static_cast<float>(static_cast<int>(y)) : kDebugBarMoveBottom,
                       kGraphicOne + (x + soundWidth), kDebugBarTop, barColor, barColor);
        }

        order = System.GetNextOrder(order);
        hue += 0x168;
        y += kDebugBarLineStep;
    }

    setBarColor(barColor, (u32)*reinterpret_cast<u32*>(&((Graphic.IsFrameRateOver() != 0) ? CColor(0xFF, 0, 0, 0xFF) : CColor(0, 0xFF, 0, 0xFF)).color));
    drawSFRect(kDebugBarLeft, kDebugIndicatorTop, kDebugIndicatorFrameRight, kDebugIndicatorBottom, barColor, barColor);

    setBarColor(barColor, (u32)*reinterpret_cast<u32*>(&((Graphic.IsFifoOver() != 0) ? CColor(0xFF, 0, 0, 0xFF) : CColor(0, 0xFF, 0, 0xFF)).color));
    drawSFRect(kDebugIndicatorFifoLeft, kDebugIndicatorTop, kDebugIndicatorFifoRight, kDebugIndicatorBottom, barColor, barColor);

    if (textFlag) {
        Graphic.InitDebugString();

        order = System.GetFirstOrder();
        x = kDebugBarLeft;
        int i = 0;
        y = 0x10;
        for (; i < orderCount; i++) {
            const int priority = order->m_priority;
            const float width = (kGraphicScreenCenterX * order->m_lastTime) / kDebugBarFrameBudget;

            if (priority != 0x27) {
                char debugString[260];
                sprintf(debugString, const_cast<char*>(s_graphic_order_debug_fmt), order->m_debugName, order->m_insertIndex, order->m_lastTime);

                if (priority == 0x17) {
                    char extraString[256];
                    sprintf(extraString, const_cast<char*>(s_graphic_move_debug_fmt),
                            CFlatMoveTime(), CFlatBgCollisionTime(),
                            CFlatObjectCollisionTime(), CFlatUpdateTime(),
                            CFlatHitTime(), CFlatPerformanceTotalTime());
                    strcat(debugString, extraString);
                }

                Graphic.DrawDebugStringDirect(static_cast<u32>(kGraphicOne + x), y, debugString, kDebugBarLineStep);
                x += width;
            }

            order = System.GetNextOrder(order);
            y += kDebugBarLineStep;
        }
    }

    PSMTX44Copy(CameraPcs.m_screenMatrix, ortho);
    GXSetProjection(ortho, GX_PERSPECTIVE);
}

/*
 * --INFO--
 * PAL Address: 0x80047248
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::drawEnd()
{
	char debugPadString[256];
	char debugInputString[256];

	if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x10) != 0) {
		Graphic.DrawDebugString();
	}

	if ((DbgMenuPcs.GetDbgFlagsRaw() & 1) != 0) {
		drawBar();
	}

	if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x10) != 0) {
		Graphic.InitDebugString();

		if (System.m_scenegraphStepMode != 0) {
			Graphic.DrawDebugStringDirect(0x10, 0x10, const_cast<char*>(s_scenegraph_step_labels[System.m_scenegraphStepMode]), 0xC);
		}

		if (Pad.m_debugPadPort != -1) {
			sprintf(debugPadString, s_debug_pad_port_fmt, Pad.m_debugPadPort + 1);
			Graphic.DrawDebugStringDirect(0x10, 0x11, debugPadString, 0xC);
		}

		int x;
		int port = 0;
		x = 0x10;
		for (; port < 4; port++) {
			bool suppress = (Pad.m_debugPadLock != 0) || ((port == 0) && (Pad.m_debugPadPort != -1));

			u16 held;
			if (suppress) {
				held = 0;
			} else {
				int selectedPort = Pad.m_debugPadPort;
				u32 portIndex = port & ~((int)~((selectedPort - port) | (port - selectedPort)) >> 31);
				held = Pad.GetPadInputs()[portIndex].button[0];
			}
			const u16 buttons = held;

			const char c = ((buttons & 0x20) != 0) ? 'r' : ' ';
			const char z = ((buttons & 0x40) != 0) ? 'l' : ' ';
			const char s = ((buttons & 0x10) != 0) ? 's' : ' ';
			const char start = ((buttons & 0x1000) != 0) ? 'S' : ' ';
			const char a = ((buttons & 0x100) != 0) ? 'A' : ' ';
			const char b = ((buttons & 0x200) != 0) ? 'B' : ' ';
			const char r = ((buttons & 2) != 0) ? 'R' : ' ';
			const char l = ((buttons & 1) != 0) ? 'L' : ' ';
			const char left = ((buttons & 4) != 0) ? 'D' : ' ';
			const char down = ((buttons & 8) != 0) ? 'U' : ' ';

			sprintf(debugInputString, s_graphic_pad_input_fmt, down, left, l, r, b, a, start, s, z, c);
			Graphic.DrawDebugStringDirect(x, 0x1A8, debugInputString, 8);
			x += 0x60;
		}

		sprintf(debugInputString, s_debug_frame_fmt, System.m_frameCounter);
		Graphic.DrawDebugStringDirect(port * 0x60 + 0x10, 0x1A8, debugInputString, 8);
	}

	Memory.Draw();
	Graphic.EndFrame();
}

/*
 * --INFO--
 * PAL Address: 0x80047528
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::drawFlip()
{
	Graphic.Flip();
	_InitGxFunc();
}

/*
 * --INFO--
 * PAL Address: 0x80047554
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::drawWait()
{
	Graphic._WaitDrawDone(const_cast<char*>(s_p_graphic_cpp), 0xDA);
}

/*
 * --INFO--
 * PAL Address: 0x80047588
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::drawBegin()
{
	Graphic.BeginFrame();
}

/*
 * --INFO--
 * PAL Address: 0x800475b0
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::calc()
{
    calcScreenFade();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::destroy()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8004767c
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::SetBlurParameter(int mode, unsigned char r, unsigned char g, unsigned char b, unsigned char a, unsigned char mode2, short scale)
{
    m_blurMode = mode;
    m_blurR = r;
    m_blurG = g;
    m_blurB = b;
    m_blurA = a;
    m_blurMode2 = mode2;
    m_blurScale = scale;
}

/*
 * --INFO--
 * PAL Address: 0x8004769c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::SetDOFParameter(signed char flagA, signed char flagB, float nearZ, float farZ, float focus, float blurNear, float blurFar, int mode)
{
	m_dofFlagB = flagB;
	m_dofNearZ = nearZ;
	m_dofFarZ = farZ;
	m_dofFlagA = flagA;
	m_dofMode = mode;
	m_dofTarget.x = focus;
	m_dofTarget.y = blurNear;
	m_dofTarget.z = blurFar;
}

/*
 * --INFO--
 * PAL Address: 0x800476c0
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::create()
{
    float dofDefault;
    float farZ;
    float nearZ;

    _InitGxFunc();
    m_unkB8 = 0;
    nearZ = kDofDefaultNearZ;
    m_copySaveFlag = 0;
    farZ = kDofDefaultFarZ;
    m_dofFlag = 0;
    dofDefault = kGraphicZero;
    m_dofFlagB = 1;
    m_dofNearZ = nearZ;
    m_dofFarZ = farZ;
    m_dofFlagA = 0;
    m_dofMode = 0;
    m_dofTarget.z = dofDefault;
    m_dofTarget.y = dofDefault;
    m_dofTarget.x = dofDefault;
    memset(m_screenFade, 0, sizeof(m_screenFade));
    m_blurMode = 0;
    m_blurFadeOutFlag = 0;
    m_blurR = 0;
    m_blurG = 0;
    m_blurB = 0;
    m_blurStep = 0;
    m_blurA = 1;
    m_blurMode2 = 0;
    m_blurScale = 4;
}

/*
 * --INFO--
 * PAL Address: 0x8004776c
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGraphicPcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(&m_table + index);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::Init()
{
	// TODO
}
