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

inline CGraphicPcs::CGraphicPcs()
{
}

CGraphicPcs GraphicPcs;

CProcessCallbackTable CGraphicPcs::m_table = {
    "CGraphicPcs",
    static_cast<CProcessCallback>(&CGraphicPcs::create),
    static_cast<CProcessCallback>(&CGraphicPcs::destroy),
    {
        {static_cast<CProcessCallback>(&CGraphicPcs::calc), 0x22, 0x8},
        {static_cast<CProcessCallback>(&CGraphicPcs::drawWait), 0x26, 0x9},
        {static_cast<CProcessCallback>(&CGraphicPcs::drawFlip), 0x27, 0xC},
        {static_cast<CProcessCallback>(&CGraphicPcs::drawBegin), 0x29, 0x9},
        {static_cast<CProcessCallback>(&CGraphicPcs::drawCopy), 0x48, 1},
        {static_cast<CProcessCallback>(&CGraphicPcs::drawEnd), 0x4B, 0x9},
        {static_cast<CProcessCallback>(&CGraphicPcs::preDrawEnvInit), 0x2B, 0x9},
        {static_cast<CProcessCallback>(&CGraphicPcs::stdDrawEnvInit), 0x34, 0x9},
    },
};

static const float kGraphicZero = 0.0f;
static const float kGraphicScreenHeight = 448.0f;
static const float kGraphicScreenWidth = 640.0f;
static const float kGraphicScreenCenterX = 320.0f;
static const float kGraphicScreenCenterY = 224.0f;
static const float kDebugBarLeft = 16.0f;
static const float kDebugBarTop = 440.0f;
static const float kDebugBarRight = 336.0f;
static const float kDebugBarBottom = 441.0f;
static const float kDebugBarMoveBottom = 436.0f;
static const float kDebugIndicatorTop = 420.0f;
static const float kDebugIndicatorFrameRight = 32.0f;
static const float kDebugIndicatorBottom = 424.0f;
static const float kDebugIndicatorFifoLeft = 40.0f;
static const float kDebugIndicatorFifoRight = 56.0f;
static const int kDebugBarLineStep = 8;


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
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::Init()
{
	// TODO
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
 * PAL Address: 0x800476C0
 * PAL Size: 172b
 * EN Address: 0x800474B4
 * EN Size: 172b
 * JP Address: 0x8004700C
 * JP Size: 172b
 */
void CGraphicPcs::create()
{
    _InitGxFunc();
    m_unkB8 = 0;
    m_copySaveFlag = 0;
    m_dofFlag = 0;
    m_dofFlagB = 1;
    m_dofNearZ = 0.6f;
    m_dofFarZ = 200.0f;
    m_dofFlagA = 0;
    m_dofMode = 0;
    m_dofTarget.x = m_dofTarget.y = m_dofTarget.z = 0.0f;
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
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::destroy()
{
	// TODO
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
 * PAL Address: 0x80047554
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::drawWait()
{
	Graphic._WaitDrawDone("p_graphic.cpp", 0xDA);
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
 * PAL Address: 0x80047248
 * PAL Size: 736b
 * EN Address: 0x80051148
 * EN Size: 916b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::drawEnd()
{
	static const char* pTable[] = {
		"",
		"x8",
		"x0",
		"x1/8",
		"x1/4",
		"x1/2",
	};
	char debugPadString[256];
	char debugInputString[256];

	if ((DbgMenuPcs.GetDbgFlag() & 0x10) != 0) {
		Graphic.DrawDebugString();
	}

	if ((DbgMenuPcs.GetDbgFlag() & 1) != 0) {
		drawBar();
	}

	if ((DbgMenuPcs.GetDbgFlag() & 0x10) != 0) {
		Graphic.InitDebugString();

		if (System.m_scenegraphStepMode != 0) {
			Graphic.DrawDebugStringDirect(0x10, 0x10, const_cast<char*>(pTable[System.m_scenegraphStepMode]), 0xC);
		}

		if (Pad.GetPortEmulation() != -1) {
			sprintf(debugPadString, "%dP", Pad.GetPortEmulation() + 1);
			Graphic.DrawDebugStringDirect(0x10, 0x11, debugPadString, 0xC);
		}

		int x;
		int port = 0;
		x = 0x10;
		for (; port < 4; port++) {
			const u16 buttons = Pad.GetButton(port);

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

			sprintf(debugInputString, "%c%c%c%c%c%c%c%c%c%c", down, left, l, r, b, a, start, s, z, c);
			Graphic.DrawDebugStringDirect(x, 0x1A8, debugInputString, 8);
			x += 0x60;
		}

		sprintf(debugInputString, "%d", System.GetCounter());
		Graphic.DrawDebugStringDirect(port * 0x60 + 0x10, 0x1A8, debugInputString, 8);
	}

	Memory.Draw();
	Graphic.EndFrame();
}

static inline bool isDrawDebugText()
{
    bool drawText = false;
    if (Pad.IsDebug(0) != 0 && Joybus.GetPadType(0) != 0x40000) {
        drawText = true;
    }
    return drawText;
}

static inline void setBarColor(GXColor& dst, const u32& colorWord)
{
    const GXColor* src = (const GXColor*)&colorWord;
    dst.r = src->r;
    dst.g = src->g;
    dst.b = src->b;
    dst.a = src->a;
}

/*
 * --INFO--
 * PAL Address: 0x8004674C
 * PAL Size: 2812b
 * EN Address: 0x80046540
 * EN Size: 2812b
 * JP Address: 0x80046040
 * JP Size: 2900b
 */
void CGraphicPcs::drawBar()
{
    Mtx44 ortho;
    Mtx identity;
    CSystem::COrder* textOrder;
    C_MTXOrtho(ortho, kGraphicZero, kGraphicScreenHeight, kGraphicZero, kGraphicScreenWidth, kGraphicZero, -100.0f);
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

    const int textFlag = isDrawDebugText();

    float x = kDebugBarLeft;
    GXColor barColor = {0x80, 0x80, 0x80, 0xFF};
    drawSFRect(kDebugBarLeft, kDebugBarTop, kDebugBarRight, kDebugBarBottom, barColor, barColor);

    int hue;
    int y;
    CSystem::COrder* order = System.GetFirstOrder();
    const int orderCount = System.GetNumOrder();
    int i = 0;
    hue = 0;
    y = 0x10;
    for (; i < orderCount; i++) {
        const int priority = order->m_priority;
        const float lastTime = order->m_lastTime;
        setBarColor(barColor, Math.Hsb2Rgb(hue / orderCount, 100, 100));
        const float width = (kGraphicScreenCenterX * lastTime) / 100.0f;

        if (priority == 0x26) {
            drawSFRect(x, textFlag ? static_cast<float>(y) : kDebugBarMoveBottom,
                       1.0f + (x + width), kDebugBarTop, barColor, barColor);
            x += width;
        } else if (priority != 0x27) {
            drawSFRect(x, textFlag ? static_cast<float>(y) : 432.0f,
                       1.0f + (x + width), kDebugBarMoveBottom, barColor, barColor);
            x += width;
        }

        if (i == orderCount - 1) {
            setBarColor(barColor, Math.Hsb2Rgb(0, 100, 100));
            const float soundWidth = (kGraphicScreenCenterX * Sound.GetPerformance()) / 100.0f;

            drawSFRect(x, textFlag ? static_cast<float>(y) : kDebugBarMoveBottom,
                       1.0f + (x + soundWidth), kDebugBarTop, barColor, barColor);
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

        textOrder = System.GetFirstOrder();
        x = kDebugBarLeft;
        int i = 0;
        y = 0x10;
        for (; i < orderCount; i++) {
            const int priority = textOrder->m_priority;
            const float width = (kGraphicScreenCenterX * textOrder->m_lastTime) / 100.0f;

            if (priority != 0x27) {
                char debugString[260];
                sprintf(debugString, "%s(%d) %.3f%%", textOrder->m_debugName, textOrder->m_insertIndex, textOrder->m_lastTime);

                if (priority == 0x17) {
                    char extraString[256];
                    sprintf(extraString, " MOVE=%.1f%% BG=%.1f%% OBJ=%.1f%% UP=%.1f%% HIT=%.1f%% SCR=%.1f%%",
                            CFlatMoveTime(), CFlatBgCollisionTime(),
                            CFlatObjectCollisionTime(), CFlatUpdateTime(),
                            CFlatHitTime(), CFlatPerformanceTotalTime());
                    strcat(debugString, extraString);
                }

                Graphic.DrawDebugStringDirect(static_cast<u32>(1.0f + x), y, debugString, kDebugBarLineStep);
                x += width;
            }

            textOrder = System.GetNextOrder(textOrder);
            y += kDebugBarLineStep;
        }
    }

    CameraPcs.GetProjectionMatrix(ortho);
    GXSetProjection(ortho, GX_PERSPECTIVE);
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
 * PAL Address: 0x80046538
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::preDrawEnvInit()
{
    MaterialMan.InitEnv();
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
	MaterialMan.LockEnv();
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
 * PAL Address: 0x800462B8
 * PAL Size: 596b
 * EN Address: 0x800460AC
 * EN Size: 596b
 * JP Address: 0x80045BB4
 * JP Size: 588b
 */
void CGraphicPcs::drawSFCircle(int innerRadius, int outerRadius, int centerX, int centerY, _GXColor innerColor, _GXColor outerColor)
{
    float ringPoints[32][4];
    const float step = 0.19634955f;

    for (int i = 0; i < 32; i++) {
        float s;
        const float angle = step * (float)i;
        s = (float)sin(angle);
        const float c = (float)cos(angle);

        ringPoints[i][0] = s * (float)innerRadius + (float)centerX;
        ringPoints[i][1] = c * (float)innerRadius + (float)centerY;
        ringPoints[i][2] = s * (float)outerRadius + (float)centerX;
        ringPoints[i][3] = c * (float)outerRadius + (float)centerY;
    }

    GXBegin((GXPrimitive)0x80, GX_VTXFMT0, 0x80);
    float z = 0.0f;
    for (int i = 0; i < 32; i++) {
        const float* cur = ringPoints[i];
        const float* nxt = ringPoints[(i + 1) % 32];

        GXPosition3f32(cur[0], cur[1], z);
        GXColor1u32(*(u32*)&innerColor);
        GXTexCoord2u16(0, 0);

        GXPosition3f32(nxt[0], nxt[1], z);
        GXColor1u32(*(u32*)&innerColor);
        GXTexCoord2u16(0, 0);

        GXPosition3f32(nxt[2], nxt[3], z);
        GXColor1u32(*(u32*)&outerColor);
        GXTexCoord2u16(0, 0);

        GXPosition3f32(cur[2], cur[3], z);
        GXColor1u32(*(u32*)&outerColor);
        GXTexCoord2u16(0, 0);
    }
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
 * PAL Address: 0x80045178
 * PAL Size: 4256b
 * EN Address: 0x80044F6C
 * EN Size: 4256b
 * JP Address: 0x80044978
 * JP Size: 4508b
 */
void CGraphicPcs::drawScreenFade()
{
    Mtx44 orthoMtx;
    Mtx cameraMtx;
    Mtx44 screenMtx;
    Mtx44 worldScreenMtx;
    Mtx identityMtx;

    int radius;
    C_MTXOrtho(orthoMtx, kGraphicZero, kGraphicScreenHeight, kGraphicZero, kGraphicScreenWidth, kGraphicZero, -100.0f);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);

    CameraPcs.GetViewMatrix(cameraMtx);
    PSMTXCopy(cameraMtx, screenMtx);
    screenMtx[3][2] = kGraphicZero;
    screenMtx[3][1] = kGraphicZero;
    screenMtx[3][0] = kGraphicZero;
    screenMtx[3][3] = 1.0f;
    CameraPcs.GetProjectionMatrix(worldScreenMtx);
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

        GXSetChanAmbColor(GX_COLOR0A0, CColor(0xFF, 0xFF, 0xFF, 0xFF));
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

        float t = (float)slotData->m_timer / (float)slotData->m_duration;
        if (slotData->m_invert != 0) {
            t = 1.0f - t;
        }
        const float fadeWave = (float)sin((double)(1.5707964f * t));
        const u8 fadeAlpha = (u8)(255.0f * fadeWave);

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
            const int barHeight = (int)(48.0f * fadeWave);
            const int barEdge = (int)(8.0f * fadeWave);

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
                CGObject* obj = slotData->m_targetObj;
                if (obj == NULL) {
                    goto drawSlot2Fullscreen;
                }
                Vec pos = obj->m_worldPosition;
                pos.y += slotData->m_targetYOffs;
                PSMTX44MultVec(worldScreenMtx, &pos, &pos);

                const float sx = pos.x * kGraphicScreenCenterX + kGraphicScreenCenterX;
                pos.x = sx;
                const float sy = kGraphicScreenCenterY - kGraphicScreenCenterY * pos.y;
                pos.y = sy;
                float clampedX = 0.0f;
                clampedX = (sx < clampedX) ? clampedX : ((kGraphicScreenWidth < sx) ? kGraphicScreenWidth : sx);
                pos.x = clampedX;
                {
                    float clampedY = 0.0f;
                    clampedY = (pos.y < clampedY) ? clampedY : ((kGraphicScreenHeight < pos.y) ? kGraphicScreenHeight : pos.y);
                    pos.y = clampedY;
                }

                radius = (int)(1280.0f * (1.0f - fadeWave));
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

                t = slotData->m_amplitude * (1.0f - t);
                float wave = (float)sin((double)slotData->m_phase);
                float extent = kGraphicScreenCenterX * t;
                const float offX = slotData->m_stretch * (extent * wave);
                wave = (float)cos((double)slotData->m_phase);
                extent = kGraphicScreenCenterY * t;
                const float offY = slotData->m_stretch * (extent * wave);
                t += 1.0f;

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

                float z = 0.0f;
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

                    const float t0 = (float)row / 2.0f;
                    const float t1 = (float)(row + 1) / 2.0f;
                    gradColor[0].color.r = (u8)(t0 * ((float)slotData->m_colorB.r - (float)baseColor.r) + (float)baseColor.r);
                    gradColor[0].color.g = (u8)(t0 * ((float)slotData->m_colorB.g - (float)baseColor.g) + (float)baseColor.g);
                    gradColor[0].color.b = (u8)(t0 * ((float)slotData->m_colorB.b - (float)baseColor.b) + (float)baseColor.b);
                    gradColor[0].color.a = 0xFF;

                    gradColor[1].color.r = (u8)(t1 * ((float)slotData->m_colorB.r - (float)baseColor.r) + (float)baseColor.r);
                    gradColor[1].color.g = (u8)(t1 * ((float)slotData->m_colorB.g - (float)baseColor.g) + (float)baseColor.g);
                    gradColor[1].color.b = (u8)(t1 * ((float)slotData->m_colorB.b - (float)baseColor.b) + (float)baseColor.b);
                    gradColor[1].color.a = 0xFF;

                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    GXPosition3f32((float)x, (float)y, z);
                    GXColor1u32(*(u32*)&gradColor[0].color);
                    GXTexCoord2u16(0, 0);
                    GXPosition3f32((float)(x + 0x140), (float)y, z);
                    GXColor1u32(*(u32*)&gradColor[0].color);
                    GXTexCoord2u16(2, 0);
                    GXPosition3f32((float)(x + 0x140), (float)(y + 0xE0), z);
                    GXColor1u32(*(u32*)&gradColor[1].color);
                    GXTexCoord2u16(2, 2);
                    GXPosition3f32((float)x, (float)(y + 0xE0), z);
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

    CameraPcs.GetProjectionMatrix(orthoMtx);
    GXSetProjection(orthoMtx, GX_PERSPECTIVE);
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
 * PAL Address: UNUSED
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGraphicPcs::drawSFRect(float x0, float y0, float x1, float y1, _GXColor topColor, _GXColor bottomColor)
{
    PPCWGPipe* fifo = (PPCWGPipe*)GXFIFO_ADDR;
    float z = 0.0f;

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    fifo->f32 = x0;
    fifo->f32 = y0;
    fifo->f32 = z;
    fifo->u32 = *(u32*)&topColor;
    fifo->u16 = 0;
    fifo->u16 = 0;
    fifo->f32 = x1;
    fifo->f32 = y0;
    fifo->f32 = z;
    fifo->u32 = *(u32*)&topColor;
    fifo->u16 = 2;
    fifo->u16 = 0;
    fifo->f32 = x1;
    fifo->f32 = y1;
    fifo->f32 = z;
    fifo->u32 = *(u32*)&bottomColor;
    fifo->u16 = 2;
    fifo->u16 = 2;
    fifo->f32 = x0;
    fifo->f32 = y1;
    fifo->f32 = z;
    fifo->u32 = *(u32*)&bottomColor;
    fifo->u16 = 0;
    fifo->u16 = 2;
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
inline void CGraphicPcs::drawSFRect(float x0, float y0, float x1, float y1, _GXColor color)
{
    drawSFRect(x0, y0, x1, y1, color, color);
}
