#include "ffcc/p_graphic.h"
#include "types.h"

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
extern CGraphicPcs GraphicsPcs;

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
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::calc()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::drawEnd()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::drawCopy()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGraphicPcs::drawSFCircle(int, int, int, int, _GXColor, _GXColor)
{
	// TODO
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
