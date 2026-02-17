#include "ffcc/p_graphic.h"
#include "ffcc/graphic.h"
#include "ffcc/memory.h"
#include "ffcc/p_minigame.h"
#include "ffcc/pad.h"
#include "types.h"
#include <dolphin/mtx.h>

extern "C" int sprintf(char*, const char*, ...);
extern "C" double sin(double);
extern "C" double cos(double);

extern void* __vt__8CManager;
extern void* lbl_801E8668;
extern void* lbl_801E9E9C;

extern u32 lbl_801E9C90[];
extern u32 lbl_801E9C9C[];
extern u32 lbl_801E9CA8[];
extern u32 lbl_801E9CB4[];
extern u32 lbl_801E9CC0[];
extern u32 lbl_801E9CCC[];
extern u32 lbl_801E9CD8[];
extern u32 lbl_801E9CE4[];
extern u32 lbl_801E9CF0[];
extern u32 lbl_801E9CFC[];
extern u32 lbl_801E9D08[];
extern int DAT_802381a0;
extern CGraphicPcs GraphicsPcs;
extern CMiniGamePcs MiniGamePcs;
extern char* PTR_DAT_801e9e64[];
extern char DAT_8032fbf4[];
extern char DAT_8032fbf8[];
extern char s__c_c_c_c_c_c_c_c_c_c_801d7bf8[];
extern int DAT_802381a0;

/*
 * --INFO--
 * PAL Address: 0x80047788
 * PAL Size: 424b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_graphic_cpp(void)
{
    volatile void** base = (volatile void**)&GraphicsPcs;
    *base = &__vt__8CManager;
    *base = &lbl_801E8668;
    *base = &lbl_801E9E9C;

    u32* dst = lbl_801E9D08;
    dst[1] = lbl_801E9C90[0];
    dst[2] = lbl_801E9C90[1];
    dst[3] = lbl_801E9C90[2];
    dst[4] = lbl_801E9C9C[0];
    dst[5] = lbl_801E9C9C[1];
    dst[6] = lbl_801E9C9C[2];
    dst[7] = lbl_801E9CA8[0];
    dst[8] = lbl_801E9CA8[1];
    dst[9] = lbl_801E9CA8[2];
    dst[12] = lbl_801E9CB4[0];
    dst[13] = lbl_801E9CB4[1];
    dst[14] = lbl_801E9CB4[2];
    dst[17] = lbl_801E9CC0[0];
    dst[18] = lbl_801E9CC0[1];
    dst[19] = lbl_801E9CC0[2];
    dst[22] = lbl_801E9CCC[0];
    dst[23] = lbl_801E9CCC[1];
    dst[24] = lbl_801E9CCC[2];
    dst[27] = lbl_801E9CD8[0];
    dst[28] = lbl_801E9CD8[1];
    dst[29] = lbl_801E9CD8[2];
    dst[32] = lbl_801E9CE4[0];
    dst[33] = lbl_801E9CE4[1];
    dst[34] = lbl_801E9CE4[2];
    dst[37] = lbl_801E9CF0[0];
    dst[38] = lbl_801E9CF0[1];
    dst[39] = lbl_801E9CF0[2];
    dst[42] = lbl_801E9CFC[0];
    dst[43] = lbl_801E9CFC[1];
    dst[44] = lbl_801E9CFC[2];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CGraphicPcs::CGraphicPcs()
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
void CGraphicPcs::GetTable(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::create()
{
	// TODO
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
	*(char*)((char*)this + 0xc4) = flagB;
	*(float*)((char*)this + 0xc8) = nearZ;
	*(float*)((char*)this + 0xcc) = farZ;
	*(char*)((char*)this + 0xe0) = flagA;
	*(int*)((char*)this + 0xd0) = mode;
	*(float*)((char*)this + 0xd4) = focus;
	*(float*)((char*)this + 0xd8) = blurNear;
	*(float*)((char*)this + 0xdc) = blurFar;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::SetBlurParameter(int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, short)
{
	// TODO
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
    int* timerA = (int*)((char*)this + 0x4);
    if (*timerA > 0) {
        *timerA = *timerA - 1;
        if (*timerA == 0) {
            *(int*)((char*)this + 0x1c) = 0;
        }
    }

    int* timerB = (int*)((char*)this + 0x5c);
    if (*timerB > 0) {
        *timerB = *timerB - 1;
        if (*timerB == 0) {
            *(int*)((char*)this + 0x74) = 0;
        }
    }

    int* timerC = (int*)((char*)this + 0x88);
    if (*timerC > 0) {
        *timerC = *timerC - 1;
        if (*timerC == 0) {
            *(int*)((char*)this + 0xa0) = 0;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::drawBegin()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::drawWait()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::drawFlip()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::drawBar()
{
	// TODO
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
	if (*(int*)((u8*)this + 0xBC) != 0) {
		Graphic.CopySaveFrameBuffer();
		*(int*)((u8*)this + 0xBC) = 0;
	}

	if (*(int*)((u8*)this + 0xC0) != 0) {
		Vec target;
		target.x = *(float*)((u8*)this + 0xD4);
		target.y = *(float*)((u8*)this + 0xD8);
		target.z = *(float*)((u8*)this + 0xDC);
		Graphic.RenderDOF(*(signed char*)((u8*)this + 0xE0), *(signed char*)((u8*)this + 0xC4), *(float*)((u8*)this + 0xC8),
		                  *(float*)((u8*)this + 0xCC), target, *(int*)((u8*)this + 0xD0));
	}

	int initBlur = 0;
	if ((*(int*)((u8*)this + 0xE4) == 1) && (DAT_802381a0 == 0)) {
		DAT_802381a0 = 1;
		Graphic.InitBlurParameter();
		initBlur = 1;
		*(u8*)((u8*)this + 0xEF) = *(u8*)((u8*)this + 0xEE) / *(u8*)((u8*)this + 0xEC);
		*(int*)((u8*)this + 0xE8) = 0;
	}

	if ((*(int*)((u8*)this + 0xE4) != 0) || (DAT_802381a0 != 0) || (*(int*)((u8*)this + 0xE8) != 0)) {
		if (*(int*)((u8*)this + 0xE4) != DAT_802381a0) {
			*(int*)((u8*)this + 0xE8) = 1;
		}

		Graphic.RenderBlur(initBlur, *(u8*)((u8*)this + 0xF1), *(u8*)((u8*)this + 0xF0), *(u8*)((u8*)this + 0xED),
		                   *(u8*)((u8*)this + 0xEE), *(s16*)((u8*)this + 0xF2));

		if (*(int*)((u8*)this + 0xE8) != 0) {
			if ((int)((u32)*(u8*)((u8*)this + 0xEE) - (u32)*(u8*)((u8*)this + 0xEF)) < 1) {
				*(u8*)((u8*)this + 0xEE) = 0;
				*(int*)((u8*)this + 0xE8) = 0;
				*(int*)((u8*)this + 0xE4) = 0;
				DAT_802381a0 = 0;
			} else {
				*(u8*)((u8*)this + 0xEE) = *(u8*)((u8*)this + 0xEE) - *(u8*)((u8*)this + 0xEF);
			}
		}
	}

	drawScreenFade();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::setViewport()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::preDrawEnvInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::stdDrawEnvInit()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::GetScreenFadeExecutingBit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::drawScreenFade()
{
	// TODO
}
