#include "ffcc/p_graphic.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/render_buffers.h"
#include "ffcc/gxfunc.h"
#include "ffcc/joybus.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_minigame.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

CGraphicPcs GraphicsPcs;
extern "C" double sin(double);
extern "C" double cos(double);
extern "C" int GetPadType__6JoyBusFi(void*, int);
extern "C" void create__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void destroy__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void calc__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void drawBegin__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void drawWait__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void drawFlip__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void drawEnd__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void drawBar__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void drawCopy__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void setViewport__11CGraphicPcsFv(CGraphicPcs*);
char s_CGraphicPcs_801D7B80[] = "CGraphicPcs";

u32 m_table_desc0__11CGraphicPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(create__11CGraphicPcsFv)};
u32 m_table_desc1__11CGraphicPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(destroy__11CGraphicPcsFv)};
u32 m_table_desc2__11CGraphicPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(calc__11CGraphicPcsFv)};
u32 m_table_desc3__11CGraphicPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(drawBegin__11CGraphicPcsFv)};
u32 m_table_desc4__11CGraphicPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(drawWait__11CGraphicPcsFv)};
u32 m_table_desc5__11CGraphicPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(drawFlip__11CGraphicPcsFv)};
u32 m_table_desc6__11CGraphicPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(drawEnd__11CGraphicPcsFv)};
u32 m_table_desc7__11CGraphicPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(drawBar__11CGraphicPcsFv)};
u32 m_table_desc8__11CGraphicPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(drawCopy__11CGraphicPcsFv)};
u32 m_table_desc9__11CGraphicPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(setViewport__11CGraphicPcsFv)};
u32 m_table__11CGraphicPcs[0x15C / sizeof(u32)] = {
    reinterpret_cast<u32>(s_CGraphicPcs_801D7B80), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x22, 0x8, 0, 0, 0, 0x26, 0x9, 0, 0, 0, 0x27, 0xC, 0, 0, 0, 0x29,
    0x9, 0, 0, 0, 0x48, 1, 0, 0, 0, 0x4B, 0x9, 0, 0, 0, 0x2B, 0x9, 0, 0, 0, 0x34, 0x9
};

extern char* PTR_DAT_801e9e64[];
extern char DAT_8032fbf4[];
extern char DAT_8032fbf8[];
extern u32 DAT_8032fb74;
extern char s__c_c_c_c_c_c_c_c_c_c_801d7bf8[];
extern int DAT_802381a0;
extern "C" float FLOAT_8032fb78;
extern "C" float FLOAT_8032fbfc;
extern "C" float FLOAT_8032fc00;

static char s_p_graphic_cpp_801d7c10[] = "p_graphic.cpp";
static char s__s__d____3f___801d7ba4[] = "%s(%d) %.3f%%";
static char s_MOVE___1f___BG___1f___OBJ___1f___801d7bb4[] = " MOVE=%.1f%% BG=%.1f%% OBJ=%.1f%% UP=%.1f%% HIT=%.1f%% SCR=%.1f%%";

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
    return reinterpret_cast<int>(reinterpret_cast<unsigned char*>(m_table__11CGraphicPcs) + index * 0x15C);
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
    _InitGxFunc();
    m_unkB8 = 0;
    m_copySaveFlag = 0;
    m_dofFlag = 0;
    m_dofFlagB = 1;
    m_dofNearZ = FLOAT_8032fbfc;
    m_dofFarZ = FLOAT_8032fc00;
    m_dofFlagA = 0;
    m_dofMode = 0;
    m_dofFocus = FLOAT_8032fb78;
    m_dofBlurNear = FLOAT_8032fb78;
    m_dofBlurFar = FLOAT_8032fb78;
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
	m_dofFocus = focus;
	m_dofBlurNear = blurNear;
	m_dofBlurFar = blurFar;
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
    for (int i = 0; i < 4; i++) {
        if (m_screenFade[i].m_timer > 0) {
            m_screenFade[i].m_timer--;
            if (m_screenFade[i].m_timer == 0) {
                m_screenFade[i].m_targetObj = 0;
            }
        }
    }
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
	Graphic._WaitDrawDone(s_p_graphic_cpp_801d7c10, 0xDA);
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGraphicPcs::drawEnd()
{
	const u32 miniGameFlags = *(u32*)((u8*)&MiniGamePcs + 0x6484);
	char debugInputString[256];
	char debugPadString[256];

	if ((miniGameFlags & 0x10) != 0) {
		Graphic.DrawDebugString();
	}

	if ((miniGameFlags & 1) != 0) {
		drawBar();
	}

	if ((miniGameFlags & 0x10) != 0) {
		Graphic.InitDebugString();

		if (System.m_scenegraphStepMode != 0) {
			Graphic.DrawDebugStringDirect(0x10, 0x10, PTR_DAT_801e9e64[System.m_scenegraphStepMode], 0xC);
		}

		if (Pad._448_4_ != -1) {
			sprintf(debugPadString, DAT_8032fbf4, Pad._448_4_ + 1);
			Graphic.DrawDebugStringDirect(0x10, 0x11, debugPadString, 0xC);
		}

		short x = 0x10;
		for (u32 port = 0; port < 4; port++) {
			bool suppress = false;
			if (Pad._452_4_ == 0) {
				if ((port == 0) && (Pad._448_4_ != -1)) {
					suppress = true;
				}
			} else {
				suppress = true;
			}

			u16 buttons = 0;
			if (!suppress) {
				u32 portIndex = port;
				if ((int)port == Pad._448_4_) {
					portIndex = 0;
				}
				buttons = *(u16*)((u8*)&Pad + 4 + portIndex * 0x54);
			}

			const char down = ((buttons & 8) != 0) ? 'U' : ' ';
			const char left = ((buttons & 4) != 0) ? 'D' : ' ';
			const char l = ((buttons & 1) != 0) ? 'L' : ' ';
			const char r = ((buttons & 2) != 0) ? 'R' : ' ';
			const char b = ((buttons & 0x200) != 0) ? 'B' : ' ';
			const char a = ((buttons & 0x100) != 0) ? 'A' : ' ';
			const char start = ((buttons & 0x1000) != 0) ? 'S' : ' ';
			const char s = ((buttons & 0x10) != 0) ? 's' : ' ';
			const char z = ((buttons & 0x40) != 0) ? 'l' : ' ';
			const char c = ((buttons & 0x20) != 0) ? 'r' : ' ';

			sprintf(debugInputString, s__c_c_c_c_c_c_c_c_c_c_801d7bf8, down, left, l, r, b, a, start, s, z, c);
			Graphic.DrawDebugStringDirect(x, 0x1A8, debugInputString, 8);
			x += 0x60;
		}

		sprintf(debugInputString, DAT_8032fbf8, System.m_frameCounter);
		Graphic.DrawDebugStringDirect(x, 0x1A8, debugInputString, 8);
	}

	Memory.Draw();
	Graphic.EndFrame();
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
void CGraphicPcs::drawBar()
{
    Mtx44 ortho;
    Mtx identity;
    C_MTXOrtho(ortho, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 1.0f);
    GXSetProjection(ortho, GX_ORTHOGRAPHIC);

    _GXSetBlendMode((GXBlendMode)1, (GXBlendFactor)4, (GXBlendFactor)5, (GXLogicOp)1);
    GXSetZCompLoc((GXBool)0);
    _GXSetAlphaCompare((GXCompare)6, 1, (GXAlphaOp)0, (GXCompare)7, 0);
    GXSetZMode((GXBool)0, GX_ALWAYS, (GXBool)0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, (GXBool)0, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, (GXBool)0, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPEC);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 1);
    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, GX_PNMTX0);
    GXLoadTexMtxImm(identity, GX_TEXMTX0, GX_MTX2x4);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

    const bool useDebugPad = (Pad._452_4_ != 0) || (Pad._448_4_ != -1);
    int padState = 0;
    if (!useDebugPad) {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        padState = *reinterpret_cast<int*>(reinterpret_cast<u8*>(&Pad) + 0x60);
    }
    const bool drawText = (padState != 0) && (GetPadType__6JoyBusFi(&Joybus, 0) != 0x40000);

    const u32 backColor = DAT_8032fb74;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 448.0f, 0.0f);
    GXColor1u32(backColor);
    GXTexCoord2u16(0, 0);
    GXPosition3f32(640.0f, 448.0f, 0.0f);
    GXColor1u32(backColor);
    GXTexCoord2u16(2, 0);
    GXPosition3f32(640.0f, 480.0f, 0.0f);
    GXColor1u32(backColor);
    GXTexCoord2u16(2, 2);
    GXPosition3f32(0.0f, 480.0f, 0.0f);
    GXColor1u32(backColor);
    GXTexCoord2u16(0, 2);

    const int orderCount = System.m_orderCount;
    CSystem::COrder* order = System.GetFirstOrder();
    float x = 0.0f;
    int hue = 0;
    u32 y = 0x10;
    for (int i = 0; i < orderCount && order != NULL; i++) {
        const float width = (100.0f * order->m_lastTime) / 16.666666f;
        const u32 rgb = Math.Hsb2Rgb(orderCount > 0 ? (hue / orderCount) : 0, 100, 100);
        const float y0 = drawText ? static_cast<float>(y) : ((order->m_priority == 0x26) ? 456.0f : 464.0f);
        const float y1 = drawText ? static_cast<float>(y + 8) : ((order->m_priority == 0x26) ? 464.0f : 456.0f);

        if (order->m_priority == 0x26) {
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(x, y0, 0.0f);
            GXColor1u32(rgb);
            GXTexCoord2u16(0, 0);
            GXPosition3f32(x + width, y0, 0.0f);
            GXColor1u32(rgb);
            GXTexCoord2u16(2, 0);
            GXPosition3f32(x + width, y1, 0.0f);
            GXColor1u32(rgb);
            GXTexCoord2u16(2, 2);
            GXPosition3f32(x, y1, 0.0f);
            GXColor1u32(rgb);
            GXTexCoord2u16(0, 2);
            x += width;
        } else if (order->m_priority != 0x27) {
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(x, y0, 0.0f);
            GXColor1u32(rgb);
            GXTexCoord2u16(0, 0);
            GXPosition3f32(x + width, y0, 0.0f);
            GXColor1u32(rgb);
            GXTexCoord2u16(2, 0);
            GXPosition3f32(x + width, y1, 0.0f);
            GXColor1u32(rgb);
            GXTexCoord2u16(2, 2);
            GXPosition3f32(x, y1, 0.0f);
            GXColor1u32(rgb);
            GXTexCoord2u16(0, 2);
            x += width;
        }

        if (i == orderCount - 1) {
            const float soundWidth = (100.0f * Sound.GetPerformance()) / 16.666666f;
            const u32 soundColor = Math.Hsb2Rgb(0, 100, 100);

            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(x, drawText ? static_cast<float>(y) : 456.0f, 0.0f);
            GXColor1u32(soundColor);
            GXTexCoord2u16(0, 0);
            GXPosition3f32(x + soundWidth, drawText ? static_cast<float>(y) : 456.0f, 0.0f);
            GXColor1u32(soundColor);
            GXTexCoord2u16(2, 0);
            GXPosition3f32(x + soundWidth, drawText ? static_cast<float>(y + 8) : 464.0f, 0.0f);
            GXColor1u32(soundColor);
            GXTexCoord2u16(2, 2);
            GXPosition3f32(x, drawText ? static_cast<float>(y + 8) : 464.0f, 0.0f);
            GXColor1u32(soundColor);
            GXTexCoord2u16(0, 2);
        }

        order = System.GetNextOrder(order);
        y += 8;
        hue += 0x168;
    }

    const u32 frameColor = (Graphic.IsFrameRateOver() == 0) ? 0x00FF00FF : 0xFF0000FF;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 468.0f, 0.0f);
    GXColor1u32(frameColor);
    GXTexCoord2u16(0, 0);
    GXPosition3f32(32.0f, 468.0f, 0.0f);
    GXColor1u32(frameColor);
    GXTexCoord2u16(2, 0);
    GXPosition3f32(32.0f, 472.0f, 0.0f);
    GXColor1u32(frameColor);
    GXTexCoord2u16(2, 2);
    GXPosition3f32(0.0f, 472.0f, 0.0f);
    GXColor1u32(frameColor);
    GXTexCoord2u16(0, 2);

    const u32 fifoColor = (Graphic.IsFifoOver() == 0) ? 0x00FF00FF : 0xFF0000FF;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(40.0f, 468.0f, 0.0f);
    GXColor1u32(fifoColor);
    GXTexCoord2u16(0, 0);
    GXPosition3f32(48.0f, 468.0f, 0.0f);
    GXColor1u32(fifoColor);
    GXTexCoord2u16(2, 0);
    GXPosition3f32(48.0f, 472.0f, 0.0f);
    GXColor1u32(fifoColor);
    GXTexCoord2u16(2, 2);
    GXPosition3f32(40.0f, 472.0f, 0.0f);
    GXColor1u32(fifoColor);
    GXTexCoord2u16(0, 2);

    if (drawText) {
        Graphic.InitDebugString();

        order = System.GetFirstOrder();
        x = 0.0f;
        y = 0x10;
        for (int i = 0; i < orderCount && order != NULL; i++) {
            const float width = (100.0f * order->m_lastTime) / 16.666666f;

            if (order->m_priority != 0x27) {
                char debugString[260];
                sprintf(debugString, s__s__d____3f___801d7ba4, order->m_debugName, order->m_insertIndex, order->m_lastTime);

                if (order->m_priority == 0x17) {
                    char extraString[256];
                    sprintf(extraString, s_MOVE___1f___BG___1f___OBJ___1f___801d7bb4,
                            *reinterpret_cast<float*>(&CFlat[4920]), *reinterpret_cast<float*>(&CFlat[4924]),
                            *reinterpret_cast<float*>(&CFlat[4928]), *reinterpret_cast<float*>(&CFlat[4932]),
                            *reinterpret_cast<float*>(&CFlat[4936]), *reinterpret_cast<float*>(&CFlat[72]));
                    strcat(debugString, extraString, sizeof(debugString));
                }

                Graphic.DrawDebugStringDirect(static_cast<u32>(x + 1.0f), y, debugString, 8);
                x += width;
            }

            order = System.GetNextOrder(order);
            y += 8;
        }
    }
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
		Vec target;
		target.x = m_dofFocus;
		target.y = m_dofBlurNear;
		target.z = m_dofBlurFar;
		Graphic.RenderDOF(m_dofFlagA, m_dofFlagB, m_dofNearZ, m_dofFarZ, target, m_dofMode);
	}

	int initBlur = 0;
	if ((m_blurMode == 1) && (DAT_802381a0 == 0)) {
		DAT_802381a0 = 1;
		Graphic.InitBlurParameter();
		initBlur = 1;
		m_blurStep = m_blurB / m_blurR;
		m_blurFadeOutFlag = 0;
	}

	if ((m_blurMode != 0) || (DAT_802381a0 != 0) || (m_blurFadeOutFlag != 0)) {
		if (m_blurMode != DAT_802381a0) {
			m_blurFadeOutFlag = 1;
		}

		Graphic.RenderBlur(initBlur, m_blurMode2, m_blurA, m_blurG, m_blurB, m_blurScale);

		if (m_blurFadeOutFlag != 0) {
			if ((int)((u32)m_blurB - (u32)m_blurStep) < 1) {
				m_blurB = 0;
				m_blurFadeOutFlag = 0;
				m_blurMode = 0;
				DAT_802381a0 = 0;
			} else {
				m_blurB = m_blurB - m_blurStep;
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
    unsigned char* materialMan = reinterpret_cast<unsigned char*>(&MaterialMan);
    *(u32*)(materialMan + 0x48) = 0x000ACE0F;
    *(u32*)(materialMan + 0x44) = 0xFFFFFFFF;
    *(u8*)(materialMan + 0x4C) = 0xFF;
    *(u32*)(materialMan + 0x128) = 0;
    *(u32*)(materialMan + 0x11C) = 0;
    *(u32*)(materialMan + 0x12C) = 0x1E;
    *(u32*)(materialMan + 0x120) = 0x1E;
    *(u32*)(materialMan + 0x130) = 0;
    *(u32*)(materialMan + 0x124) = 0;
    *(u8*)(materialMan + 0x205) = 0xFF;
    *(u8*)(materialMan + 0x206) = 0xFF;
    *(u32*)(materialMan + 0x58) = 0;
    *(u32*)(materialMan + 0x5C) = 0;
    *(u8*)(materialMan + 0x208) = 0;
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
	unsigned char* materialMan = reinterpret_cast<unsigned char*>(&MaterialMan);
	*(u32*)(materialMan + 0x128) = *(u32*)(materialMan + 0x11C);
	*(u32*)(materialMan + 0x12C) = *(u32*)(materialMan + 0x120);
	*(u32*)(materialMan + 0x130) = *(u32*)(materialMan + 0x124);
	*(u32*)(materialMan + 0x40) = *(u32*)(materialMan + 0x48);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::calcScreenFade()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::drawSFRect(float, float, float, float, _GXColor, _GXColor)
{
	// TODO
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
void CGraphicPcs::drawSFCircle(int innerRadius, int centerX, int outerRadius, int centerY, _GXColor innerColor, _GXColor outerColor)
{
    float ringPoints[32][4];
    const float step = 0.19634955f;

    for (int i = 0; i < 32; i++) {
        const double angle = (double)step * (double)i;
        const float s = (float)sin(angle);
        const float c = (float)cos(angle);

        ringPoints[i][0] = s * (float)innerRadius + (float)centerX;
        ringPoints[i][1] = c * (float)innerRadius + (float)centerY;
        ringPoints[i][2] = s * (float)outerRadius + (float)centerX;
        ringPoints[i][3] = c * (float)outerRadius + (float)centerY;
    }

    GXBegin((GXPrimitive)0x80, GX_VTXFMT0, 0x80);
    for (int i = 0; i < 32; i++) {
        const int next = (i + 1) & 0x1F;

        GXPosition3f32(ringPoints[i][0], ringPoints[i][1], 0.0f);
        GXColor1u32(*(u32*)&innerColor);
        GXTexCoord2u16(0, 0);

        GXPosition3f32(ringPoints[next][0], ringPoints[next][1], 0.0f);
        GXColor1u32(*(u32*)&innerColor);
        GXTexCoord2u16(0, 0);

        GXPosition3f32(ringPoints[next][2], ringPoints[next][3], 0.0f);
        GXColor1u32(*(u32*)&outerColor);
        GXTexCoord2u16(0, 0);

        GXPosition3f32(ringPoints[i][2], ringPoints[i][3], 0.0f);
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

    if ((m_screenFade[0].m_invert != 0) || (m_screenFade[0].m_timer != 0)) {
        result = 1;
    }
    if ((m_screenFade[1].m_invert != 0) || (m_screenFade[1].m_timer != 0)) {
        result |= 2;
    }
    if ((m_screenFade[2].m_invert != 0) || (m_screenFade[2].m_timer != 0)) {
        result |= 4;
    }
    if ((m_screenFade[3].m_invert != 0) || (m_screenFade[3].m_timer != 0)) {
        result |= 8;
    }

    return result;
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
    struct ScreenFadeObjPos {
        char _padding0[0x15C];
        float x;
        float y;
        float z;
    };

    Mtx44 orthoMtx;
    Mtx cameraMtx;
    Mtx screenMtx;
    Mtx44 worldScreenMtx;
    Mtx identityMtx;

    C_MTXOrtho(orthoMtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 1.0f);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTXCopy(cameraMtx, screenMtx);
    screenMtx[3][0] = 0.0f;
    screenMtx[3][1] = 0.0f;
    screenMtx[3][2] = 0.0f;
    screenMtx[3][3] = 1.0f;
    PSMTX44Copy(CameraPcs.m_screenMatrix, worldScreenMtx);
    PSMTX44Concat(worldScreenMtx, screenMtx, worldScreenMtx);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 1);

    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, 0);
    GXLoadTexMtxImm(identityMtx, GX_TEXMTX0, GX_MTX3x4);

    for (int slot = 0; slot < 4; slot++) {
        ScreenFadeSlot* slotData = &m_screenFade[slot];
        const int timer = slotData->m_timer;
        const int duration = slotData->m_duration;
        const int invert = slotData->m_invert;

        if ((invert == 0) && (timer == 0)) {
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
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

        _GXColor baseColor = slotData->m_colorA;
        _GXColor baseColor2 = slotData->m_colorB;

        float t = (float)timer / (float)duration;
        if (invert != 0) {
            t = 1.0f - t;
        }
        const float fadeWave = (float)sin((double)(3.1415927f * t));
        const u8 fadeAlpha = (u8)(255.0f * fadeWave);
        baseColor.a = fadeAlpha;
        baseColor2.a = fadeAlpha;

        const _GXColor whiteColor = {0xFF, 0xFF, 0xFF, 0xFF};
        GXSetChanAmbColor(GX_COLOR0A0, *(GXColor*)&whiteColor);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

        if (slot == 3) {
            const int barHeight = (int)(448.0f * fadeWave);
            const int barEdge = (int)(32.0f * fadeWave);

            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(0, 0);
            GXPosition3f32(640.0f, 0.0f, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(2, 0);
            GXPosition3f32(640.0f, 480.0f, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(2, 2);
            GXPosition3f32(0.0f, 480.0f, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(0, 2);

            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(0, 0);
            GXPosition3f32(640.0f, 0.0f, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(2, 0);
            GXPosition3f32(640.0f, (float)barHeight, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(2, 2);
            GXPosition3f32(0.0f, (float)barHeight, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(0, 2);

            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(0.0f, 480.0f - (float)barHeight, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(0, 0);
            GXPosition3f32(640.0f, 480.0f - (float)barHeight, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(2, 0);
            GXPosition3f32(640.0f, 480.0f, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(2, 2);
            GXPosition3f32(0.0f, 480.0f, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(0, 2);

            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(0.0f, (float)barHeight, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(0, 0);
            GXPosition3f32(640.0f, (float)barHeight, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(2, 0);
            GXPosition3f32(640.0f, (float)(barHeight + barEdge), 0.0f);
            GXColor1u32(*(u32*)&baseColor2);
            GXTexCoord2u16(2, 2);
            GXPosition3f32(0.0f, (float)(barHeight + barEdge), 0.0f);
            GXColor1u32(*(u32*)&baseColor2);
            GXTexCoord2u16(0, 2);

            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(0.0f, 480.0f - (float)barHeight, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(0, 0);
            GXPosition3f32(640.0f, 480.0f - (float)barHeight, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(2, 0);
            GXPosition3f32(640.0f, 480.0f - (float)(barHeight + barEdge), 0.0f);
            GXColor1u32(*(u32*)&baseColor2);
            GXTexCoord2u16(2, 2);
            GXPosition3f32(0.0f, 480.0f - (float)(barHeight + barEdge), 0.0f);
            GXColor1u32(*(u32*)&baseColor2);
            GXTexCoord2u16(0, 2);
            continue;
        }

        if (slot == 2) {
            const int mode = slotData->m_mode;
            if (mode == 1) {
                ScreenFadeObjPos* obj = (ScreenFadeObjPos*)slotData->m_targetObj;
                if (obj != NULL) {
                    Vec pos;
                    pos.x = obj->x;
                    pos.y = obj->y + slotData->m_targetYOffs;
                    pos.z = obj->z;
                    PSMTX44MultVec(worldScreenMtx, &pos, &pos);

                    float sx = pos.x * 320.0f + 320.0f;
                    float sy = -(pos.y * 240.0f - 240.0f);
                    if (sx < 0.0f) {
                        sx = 0.0f;
                    } else if (sx > 640.0f) {
                        sx = 640.0f;
                    }
                    if (sy < 0.0f) {
                        sy = 0.0f;
                    } else if (sy > 480.0f) {
                        sy = 480.0f;
                    }

                    const int radius = (int)(640.0f * (1.0f - t));
                    drawSFCircle(0x500, (int)sx, radius, (int)sy, baseColor, baseColor);
                    drawSFCircle(radius, (int)sx, radius - 8, (int)sy, baseColor, baseColor2);
                    continue;
                }
            }

            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(0, 0);
            GXPosition3f32(640.0f, 0.0f, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(2, 0);
            GXPosition3f32(640.0f, 480.0f, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(2, 2);
            GXPosition3f32(0.0f, 480.0f, 0.0f);
            GXColor1u32(*(u32*)&baseColor);
            GXTexCoord2u16(0, 2);
            continue;
        }

        if (slot == 0) {
            if (timer < (duration - 1)) {
                GXSetNumTexGens(1);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);

                const float phase = m_screenFade[0].m_phase;
                const float stretch = m_screenFade[0].m_stretch;
                const float amp = m_screenFade[0].m_amplitude * (1.0f - t);
                const float size = amp + 1.0f;
                const float offX = stretch * (320.0f * amp) * (float)sin((double)phase);
                const float offY = stretch * (240.0f * amp) * (float)cos((double)phase);
                const float cx = 320.0f + offX;
                const float cy = 240.0f + offY;
                const float w = 320.0f * size;
                const float h = 240.0f * size;

                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(cx - w, cy - h, 0.0f);
                GXColor1u32(*(u32*)&baseColor);
                GXTexCoord2u16(0, 0);
                GXPosition3f32(cx + w, cy - h, 0.0f);
                GXColor1u32(*(u32*)&baseColor);
                GXTexCoord2u16(2, 0);
                GXPosition3f32(cx + w, cy + h, 0.0f);
                GXColor1u32(*(u32*)&baseColor);
                GXTexCoord2u16(2, 2);
                GXPosition3f32(cx - w, cy + h, 0.0f);
                GXColor1u32(*(u32*)&baseColor);
                GXTexCoord2u16(0, 2);
                continue;
            }
        }

        if (slot == 1) {
            const int mode = slotData->m_mode;
            if (mode == 4) {
                GXSetNumTexGens(1);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                _GXSetTevColorIn(GX_TEVSTAGE0, (_GXTevColorArg)0xF, (_GXTevColorArg)8, (_GXTevColorArg)10, (_GXTevColorArg)0xF);
                _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_DIVIDE_2, GX_TRUE, GX_TEVPREV);
                _GXSetTevAlphaIn(GX_TEVSTAGE0, (_GXTevAlphaArg)7, (_GXTevAlphaArg)4, (_GXTevAlphaArg)5, (_GXTevAlphaArg)7);
                _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

                for (u32 tile = 0; tile < 4; tile++) {
                    _GXTexObj backTexObj;
                    const int x = (tile & 1) ? 0x140 : 0;
                    const int y = (tile & 2) ? 0xE0 : 0;
                    const float t0 = ((tile & 2) ? 1.0f : 0.0f) * 0.5f;
                    const float t1 = t0 + 0.5f;

                    Graphic.GetBackBufferRect2(gRenderScratchTextureBuffer, &backTexObj, x, y, 0x140, 0xE0, 0, GX_LINEAR, GX_TF_RGBA8, 0);
                    GXLoadTexObj(&backTexObj, GX_TEXMAP0);

                    _GXColor topColor;
                    topColor.r = (u8)(t0 * ((float)baseColor2.r - (float)baseColor.r) + (float)baseColor.r);
                    topColor.g = (u8)(t0 * ((float)baseColor2.g - (float)baseColor.g) + (float)baseColor.g);
                    topColor.b = (u8)(t0 * ((float)baseColor2.b - (float)baseColor.b) + (float)baseColor.b);
                    topColor.a = 0xFF;

                    _GXColor bottomColor;
                    bottomColor.r = (u8)(t1 * ((float)baseColor2.r - (float)baseColor.r) + (float)baseColor.r);
                    bottomColor.g = (u8)(t1 * ((float)baseColor2.g - (float)baseColor.g) + (float)baseColor.g);
                    bottomColor.b = (u8)(t1 * ((float)baseColor2.b - (float)baseColor.b) + (float)baseColor.b);
                    bottomColor.a = 0xFF;

                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    GXPosition3f32((float)x, (float)y, 0.0f);
                    GXColor1u32(*(u32*)&topColor);
                    GXTexCoord2u16(0, 0);
                    GXPosition3f32((float)(x + 0x140), (float)y, 0.0f);
                    GXColor1u32(*(u32*)&topColor);
                    GXTexCoord2u16(2, 0);
                    GXPosition3f32((float)(x + 0x140), (float)(y + 0xE0), 0.0f);
                    GXColor1u32(*(u32*)&bottomColor);
                    GXTexCoord2u16(2, 2);
                    GXPosition3f32((float)x, (float)(y + 0xE0), 0.0f);
                    GXColor1u32(*(u32*)&bottomColor);
                    GXTexCoord2u16(0, 2);
                }
                continue;
            } else if (mode == 2) {
                _GXSetBlendMode((GXBlendMode)1, (GXBlendFactor)4, (GXBlendFactor)1, (GXLogicOp)5);
            } else if (mode == 3) {
                _GXSetBlendMode((GXBlendMode)3, (GXBlendFactor)4, (GXBlendFactor)1, (GXLogicOp)5);
            }
        }

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(0.0f, 0.0f, 0.0f);
        GXColor1u32(*(u32*)&baseColor);
        GXTexCoord2u16(0, 0);
        GXPosition3f32(640.0f, 0.0f, 0.0f);
        GXColor1u32(*(u32*)&baseColor);
        GXTexCoord2u16(2, 0);
        GXPosition3f32(640.0f, 480.0f, 0.0f);
        GXColor1u32(*(u32*)&baseColor2);
        GXTexCoord2u16(2, 2);
        GXPosition3f32(0.0f, 480.0f, 0.0f);
        GXColor1u32(*(u32*)&baseColor2);
        GXTexCoord2u16(0, 2);
    }

    PSMTX44Copy(CameraPcs.m_screenMatrix, orthoMtx);
    GXSetProjection(orthoMtx, GX_PERSPECTIVE);
}
