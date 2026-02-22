#include "ffcc/p_menu.h"
#include "ffcc/textureman.h"

#include <dolphin/mtx.h>

extern CTextureMan TextureMan;
extern CMenuPcs MenuPcs;
extern "C" void* __register_global_object(void* object, void* destructor, void* regmem);
extern "C" void __dt__8CMenuPcsFv(void* self);
extern void* __vt__8CManager;
extern void* lbl_801E8668;
extern void* lbl_8020F2D0;
extern u32 lbl_8020EDF8[];
extern u32 lbl_8020EE04[];
extern u32 lbl_8020EE10[];
extern u32 lbl_8020EE1C[];
extern u32 lbl_8020EE28[];
extern u32 lbl_8020EE34[];
extern u32 lbl_8020EE40[];
extern u8 lbl_802EA1A0[];

/*
 * --INFO--
 * PAL Address: 0x80097618
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_menu_cpp(void)
{
    volatile void** base = reinterpret_cast<volatile void**>(&MenuPcs);
    *base = &__vt__8CManager;
    *base = &lbl_801E8668;
    *base = &lbl_8020F2D0;

    u32* mcCtrl = reinterpret_cast<u32*>(reinterpret_cast<u8*>(&MenuPcs) + 0x20);
    mcCtrl[0] = 0;
    mcCtrl[1] = 0;
    mcCtrl[2] = 0;
    mcCtrl[3] = 0;
    mcCtrl[4] = 0;
    mcCtrl[5] = 0;
    mcCtrl[6] = 0;
    mcCtrl[7] = 0;

    __register_global_object(&MenuPcs, reinterpret_cast<void*>(__dt__8CMenuPcsFv), lbl_802EA1A0);

    u32* dst = lbl_8020EE40;

    dst[0x004 / 4] = lbl_8020EDF8[0];
    dst[0x008 / 4] = lbl_8020EDF8[1];
    dst[0x00C / 4] = lbl_8020EDF8[2];
    dst[0x010 / 4] = lbl_8020EE04[0];
    dst[0x014 / 4] = lbl_8020EE04[1];
    dst[0x018 / 4] = lbl_8020EE04[2];
    dst[0x01C / 4] = lbl_8020EE10[0];
    dst[0x020 / 4] = lbl_8020EE10[1];
    dst[0x024 / 4] = lbl_8020EE10[2];
    dst[0x030 / 4] = lbl_8020EE1C[0];
    dst[0x034 / 4] = lbl_8020EE1C[1];
    dst[0x038 / 4] = lbl_8020EE1C[2];
    dst[0x044 / 4] = lbl_8020EE28[0];
    dst[0x048 / 4] = lbl_8020EE28[1];
    dst[0x04C / 4] = lbl_8020EE28[2];
    dst[0x058 / 4] = lbl_8020EE34[0];
    dst[0x05C / 4] = lbl_8020EE34[1];
    dst[0x060 / 4] = lbl_8020EE34[2];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMenuPcs::CMenuPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMenuPcs::~CMenuPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetTable(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::loadFont(int, char*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::loadTexture(char **, int, int, CMenuPcs::CTmp*, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::freeTexture(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::changeMode(CMenuPcs::MENUMODE)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetAttrFmt(CMenuPcs::FMT)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawQuit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetButtonDown(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetButtonRepeat(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::onScriptChanging(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::onMapChanging(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::onMapChanged(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80095bd0
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetTexture(CMenuPcs::TEX tex)
{
    CTexture* texture;
    Mtx texMtx;

    if ((int)tex == -1) {
        texture = 0;
    } else {
        CTexture** textures = (CTexture**)((u8*)this + 0x18C);
        u32 width;
        u32 height;

        texture = textures[(int)tex];
        TextureMan.SetTexture(GX_TEXMAP0, texture);

        width = *(u32*)((u8*)texture + 0x64);
        height = *(u32*)((u8*)texture + 0x68);
        PSMTXScale(texMtx, 1.0f / (f32)width, 1.0f / (f32)height, 1.0f);
        GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    }

    TextureMan.SetTextureTev(texture);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawRect(unsigned long, float, float, float, float, float, float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawRect(unsigned long, float, float, float, float, float, float, _GXColor*, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawBar(float, float, float, CMenuPcs::TEX, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawWindow(float x, float y, float width, float height, CMenuPcs::TEX texBase, float corner)
{
	if (width <= 0.0f || height <= 0.0f) {
		return;
	}

	const float twoCorner = corner * 2.0f;
	float midW = width - twoCorner;
	float midH = height - twoCorner;
	float overW = twoCorner - width;
	float overH = twoCorner - height;
	float uOff = 0.0f;
	float vOff = 0.0f;
	const int tex = static_cast<int>(texBase);
	const float xL = x;
	const float yT = y;
	const float xM = x + corner;
	const float yM = y + corner;
	const float xR = (x + width) - corner;
	const float yB = (y + height) - corner;

	if (midW < 0.0f) {
		midW = 0.0f;
	}
	if (midH < 0.0f) {
		midH = 0.0f;
	}
	if (overW < 0.0f) {
		overW = 0.0f;
	}
	if (overH < 0.0f) {
		overH = 0.0f;
	}
	if (corner > 0.0f) {
		uOff = overW / twoCorner;
		vOff = overH / twoCorner;
	}

	SetTexture(static_cast<CMenuPcs::TEX>(tex));
	DrawRect(0, xL, yT, corner, corner, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 1));
	DrawRect(0, xM, yT, midW, corner, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 2));
	DrawRect(0, xR, yT, corner, corner, uOff, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 3));
	DrawRect(0, xL, yM, corner, midH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 4));
	DrawRect(0, xM, yM, midW, midH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 5));
	DrawRect(0, xR, yM, corner, midH, uOff, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 6));
	DrawRect(0, xL, yB, corner, corner, 0.0f, vOff, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 7));
	DrawRect(0, xM, yB, midW, corner, 0.0f, vOff, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 8));
	DrawRect(0, xR, yB, corner, corner, uOff, vOff, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetColor(CColor&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::LoadExtraFont(int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetExtraFontTlut(int, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::drawPause()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::createBattle()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::destroyBattle()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::calcBattle()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::drawBattle()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChgPlayModeFromScript(bool)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetTexture(CMenuPcs::TEX)
{
	// TODO
}
