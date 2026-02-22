#include "ffcc/p_menu.h"
#include "ffcc/color.h"
#include "ffcc/math.h"
#include "ffcc/menu.h"
#include "ffcc/p_camera.h"
#include "ffcc/ringmenu.h"
#include "ffcc/textureman.h"

#include <dolphin/mtx.h>

extern CTextureMan TextureMan;
extern CMath Math;

struct Vec4d
{
    float x;
    float y;
    float z;
    float w;
};

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
 * PAL Address: 0x80093ec4
 * PAL Size: 1864b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawBattle()
{
    u8* self = reinterpret_cast<u8*>(this);

    if (*reinterpret_cast<s32*>(self + 0x48) != 0) {
        const float frame = static_cast<float>(*reinterpret_cast<s32*>(self + 0x58));
        float fade = 1.0f - (frame * 0.05f);
        if (fade < 0.0f) {
            fade = 0.0f;
        }

        Mtx44 screenMtx;
        Vec4d projected;
        PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<u8*>(&CameraPcs) + 0x48), screenMtx);
        Math.MTX44MultVec4(screenMtx, reinterpret_cast<Vec*>(self + 0x4C), &projected);

        if (projected.w > 0.0f) {
            const int totalWidth = static_cast<int>(static_cast<float>(*reinterpret_cast<s32*>(self + 0x60)) * fade);
            const int halfWidth = totalWidth / 2;
            float screenX = 320.0f + (320.0f * projected.x) / projected.w;
            float screenY = 240.0f - (240.0f * projected.y) / projected.w;

            if (screenX < static_cast<float>(halfWidth)) {
                screenX = static_cast<float>(halfWidth);
            } else {
                const float right = 640.0f - static_cast<float>(halfWidth);
                if (screenX > right) {
                    screenX = right;
                }
            }

            if (screenY < 32.0f) {
                screenY = 32.0f;
            } else if (screenY > 448.0f) {
                screenY = 448.0f;
            }

            int fillWidth = 0;
            if (*reinterpret_cast<s32*>(self + 0x64) != 0) {
                fillWidth = ((totalWidth - 16) * *reinterpret_cast<s32*>(self + 0x6C)) /
                            *reinterpret_cast<s32*>(self + 0x64);
            }

            const float left = screenX - static_cast<float>(halfWidth);
            const float bodyLeft = left + 8.0f;
            const float alphaF = 80.0f * fade;
            const u8 alpha = static_cast<u8>(alphaF < 0.0f ? 0.0f : (alphaF > 255.0f ? 255.0f : alphaF));
            const CColor frameColor(0xFF, 0xFF, 0xFF, alpha);
            GXSetChanMatColor(GX_COLOR0A0, frameColor.color);

            if (totalWidth > 0) {
                CTexture* tex = *reinterpret_cast<CTexture**>(self + 0x500);
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                if (tex != 0) {
                    Mtx texMtx;
                    const u32 width = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x64);
                    const u32 height = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x68);
                    PSMTXScale(texMtx, 1.0f / static_cast<float>(width), 1.0f / static_cast<float>(height), 1.0f);
                    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetNumTexGens(1);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                }
                TextureMan.SetTextureTev(tex);
                DrawRect(0, left, screenY, 8.0f, 8.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

                tex = *reinterpret_cast<CTexture**>(self + 0x504);
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                if (tex != 0) {
                    Mtx texMtx;
                    const u32 width = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x64);
                    const u32 height = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x68);
                    PSMTXScale(texMtx, 1.0f / static_cast<float>(width), 1.0f / static_cast<float>(height), 1.0f);
                    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetNumTexGens(1);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                }
                TextureMan.SetTextureTev(tex);
                DrawRect(0, bodyLeft, screenY, static_cast<float>(totalWidth - 16), 8.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

                tex = *reinterpret_cast<CTexture**>(self + 0x508);
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                if (tex != 0) {
                    Mtx texMtx;
                    const u32 width = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x64);
                    const u32 height = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x68);
                    PSMTXScale(texMtx, 1.0f / static_cast<float>(width), 1.0f / static_cast<float>(height), 1.0f);
                    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetNumTexGens(1);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                }
                TextureMan.SetTextureTev(tex);
                DrawRect(0, (left + static_cast<float>(totalWidth)) - 8.0f, screenY, 8.0f, 8.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
            }

            const u8 gauge = static_cast<u8>((*reinterpret_cast<s32*>(self + 0x5C) * 0xFF) >> 4);
            const CColor fillTop(0xFF, gauge, gauge, alpha);
            GXSetChanMatColor(GX_COLOR0A0, fillTop.color);
            TextureMan.SetTextureTev(0);
            DrawRect(0, bodyLeft, screenY + 1.0f, static_cast<float>(fillWidth), 3.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

            const u8 gaugeTop = static_cast<u8>(((*reinterpret_cast<s32*>(self + 0x5C) * 0x7F) >> 4) + 0x80);
            const CColor fillBottom(0xFF, gaugeTop, gauge, alpha);
            GXSetChanMatColor(GX_COLOR0A0, fillBottom.color);
            DrawRect(0, bodyLeft, screenY + 4.0f, static_cast<float>(fillWidth), 3.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        }
    }

    for (int i = 0; i < 4; i++) {
        CMenu* menu = *reinterpret_cast<CMenu**>(self + 0x13C + i * 4);
        if (menu != 0) {
            menu->Draw();
        }
    }
    for (int i = 0; i < 12; i++) {
        CMenu* menu = *reinterpret_cast<CMenu**>(self + 0x10C + i * 4);
        if (menu != 0) {
            menu->Draw();
        }
    }
    for (int i = 0; i < 4; i++) {
        CRingMenu* menu = *reinterpret_cast<CRingMenu**>(self + 0x13C + i * 4);
        if (menu != 0) {
            menu->DrawIcon();
        }
    }
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
