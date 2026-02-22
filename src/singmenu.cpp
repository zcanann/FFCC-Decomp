#include "ffcc/singmenu.h"
#include "ffcc/p_game.h"
#include "ffcc/util.h"
#include <dolphin/gx.h>

typedef signed short s16;
typedef unsigned char u8;

extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawFilter__8CMenuPcsFUcUcUcUc(CMenuPcs*, u8, u8, u8, u8);
extern "C" void Draw__9CShopMenuFv(void*);
extern "C" void SingleDrawCtrl__8CMenuPcsFv(CMenuPcs*);

extern float FLOAT_8033292c;
extern float FLOAT_80332928;
extern float FLOAT_80332934;
extern float FLOAT_80332940;
extern float FLOAT_80332948;
extern float FLOAT_8033294c;
extern float FLOAT_80332970;
extern float FLOAT_803329a4;
extern float FLOAT_803329a8;
extern float FLOAT_803329ac;
extern float FLOAT_803329b0;
extern float FLOAT_803329b4;
extern float FLOAT_803329bc;
extern CUtil DAT_8032ec70;
extern double DOUBLE_80332938;
extern double DOUBLE_80332968;
extern double DOUBLE_80332978;
extern double DOUBLE_80332980;
extern double DOUBLE_80332988;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::createSingleMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::destroySingleMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingMenuInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingMenuEnd()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::calcSingleMenu()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80149534
 * PAL Size: 2344b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawSingleMenu()
{
    u8* self = reinterpret_cast<u8*>(this);

    if ((Game.game.m_gameWork.m_menuStageMode != 0) &&
        (Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != 0)) {
        DrawInit__8CMenuPcsFv(this);
        DrawFilter__8CMenuPcsFUcUcUcUc(this, 0, 0, 0, 0xFF);
        DAT_8032ec70.ClearZBufferRect(FLOAT_8033294c, FLOAT_8033294c, FLOAT_803329a4, FLOAT_803329a4);
        DrawInit__8CMenuPcsFv(this);

        unsigned int scriptFoodBase = Game.game.m_scriptFoodBase[0];
        if (scriptFoodBase != 0) {
            u8 menuType = *reinterpret_cast<u8*>(scriptFoodBase + 0xBE0);
            void* shopMenu = *reinterpret_cast<void**>(self + 0x868);
            if (((menuType == 1) || (menuType == 2)) && (shopMenu != 0)) {
                Draw__9CShopMenuFv(shopMenu);
            }
        }

        s16 mode = *reinterpret_cast<s16*>(self + 0x866);
        if (mode == 1) {
            SingleDrawCtrl__8CMenuPcsFv(this);
            return;
        }

        if ((mode == 0) || (mode == 2)) {
            s16* menuData = *reinterpret_cast<s16**>(self + 0x850);
            if (menuData == 0) {
                return;
            }

            s16 count = menuData[0];
            s16* entry = menuData + 4;

            for (s16 i = 0; i < count; i++) {
                if ((i == 0) || (*reinterpret_cast<s16*>(self + 0x864) != 8)) {
                    float alpha = *reinterpret_cast<float*>(entry + 8);

                    if (i == 0) {
                        DrawInit__8CMenuPcsFv(this);
                        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
                        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
                        u8 a = static_cast<u8>(FLOAT_80332940 * alpha);
                        _GXColor color = {0xFF, 0xFF, 0xFF, a};
                        GXSetChanMatColor(GX_COLOR0A0, color);

                        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x20);
                        DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033294c, FLOAT_8033294c, FLOAT_803329a4, FLOAT_80332928,
                                                         FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
                        DrawRect__8CMenuPcsFUlfffffffff(this, 4, FLOAT_8033294c, FLOAT_803329a8, FLOAT_803329a4, FLOAT_80332928,
                                                         FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);

                        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x28);
                        unsigned int step = 0x20;
                        for (unsigned int y = 0x40; y < 0x180; y += step) {
                            if ((0x180 - y) < step) {
                                step = 0x180 - y;
                            }
                            DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033294c, static_cast<float>(y), FLOAT_803329a4,
                                                             static_cast<float>(step), FLOAT_8033294c, FLOAT_8033294c,
                                                             FLOAT_80332934, FLOAT_80332934, 0.0f);
                        }
                    } else if (i == 1) {
                        DrawInit__8CMenuPcsFv(this);
                        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
                        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
                        _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
                        GXSetChanMatColor(GX_COLOR0A0, white);
                        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x21);
                        DrawRect__8CMenuPcsFUlfffffffff(this, 0, -(FLOAT_803329ac * alpha - FLOAT_803329bc), FLOAT_80332948,
                                                         FLOAT_803329ac, FLOAT_803329b0, FLOAT_8033294c, FLOAT_8033294c,
                                                         alpha, FLOAT_80332934, 0.0f);
                        DrawRect__8CMenuPcsFUlfffffffff(this, 8, FLOAT_803329b4, FLOAT_80332948, FLOAT_803329ac, FLOAT_803329b0,
                                                         FLOAT_8033294c, FLOAT_8033294c, alpha, FLOAT_80332934, 0.0f);
                    } else if (i == 2) {
                        DrawSingleStat(alpha);
                    } else {
                        DrawSingleHelpWim(alpha);
                    }
                }
                entry += 0x20;
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::loadTextureAsync(char **, int, int, CMenuPcs::CTmp*, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingCalcChara(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleBase(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleStat(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleHelpWim(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleCrescent(float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingleCalcFadeIn()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingleDrawFadeIn()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingleCalcFadeOut()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingleDrawFadeOut()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingleCalcCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingleDrawCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleIcon(int, int, int, float, int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawShadowFont(CFont*, char*, float, float, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawNoShadowFont(CFont*, char*, float, float, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetItemType(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcListPos(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawListPosMark(float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::EquipChk(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawEquipMark(int, int, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80146adc
 * PAL Size: 1500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingWin(short mode)
{
    u8* self = reinterpret_cast<u8*>(this);
    s16* win = *reinterpret_cast<s16**>(self + 0x848);

    if (mode >= 0 && win[5] != mode) {
        win[5] = mode;
    }

    if (win[5] == 3) {
        return;
    }

    float left = static_cast<float>(win[0]) + static_cast<float>(win[2]) * 0.5f;
    float top = static_cast<float>(win[1]) + static_cast<float>(win[3]) * 0.5f;
    float width;
    float height;

    if (win[5] == 1) {
        left = static_cast<float>(win[0]);
        top = static_cast<float>(win[1]);
        width = static_cast<float>(win[2]);
        height = static_cast<float>(win[3]);
    } else {
        float leftScale = (((left - static_cast<float>(win[0])) - FLOAT_8033292c) / FLOAT_80332970) * static_cast<float>(win[4]);
        float topScale = (((top - static_cast<float>(win[1])) - FLOAT_8033292c) / FLOAT_80332970) * static_cast<float>(win[4]);
        left = (left - FLOAT_8033292c) - leftScale;
        width = static_cast<float>(DOUBLE_80332978 * static_cast<double>(FLOAT_8033292c + leftScale));
        height = static_cast<float>(DOUBLE_80332978 * static_cast<double>(FLOAT_8033292c + topScale));
        top = (top - FLOAT_8033292c) - topScale;
    }

    int leftPx = static_cast<int>(static_cast<double>(left) - DOUBLE_80332968);
    int topPx = static_cast<int>(static_cast<double>(top) - DOUBLE_80332968);
    int widthPx = static_cast<int>(static_cast<double>(width) - DOUBLE_80332980);
    int heightPx = static_cast<int>(static_cast<double>(height) - DOUBLE_80332980);

    float x0 = static_cast<float>(leftPx);
    float y0 = static_cast<float>(topPx);
    float w = static_cast<float>(widthPx);
    float h = static_cast<float>(heightPx);
    float x1 = x0 + w - FLOAT_8033292c;
    float y1 = y0 + h - FLOAT_8033292c;

    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, white);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x3F);
    for (unsigned long i = 0; i < 4; i++) {
        unsigned long uvFlag = 0;
        float x = x0;
        float y = y0;
        if ((i & 1) != 0) {
            uvFlag = 8;
            x = x1;
        }
        if ((i & 2) != 0) {
            uvFlag |= 4;
            y = y1;
        }
        DrawRect__8CMenuPcsFUlfffffffff(this, uvFlag, x, y, FLOAT_8033292c, FLOAT_8033292c, FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    }

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x41);
    float innerW = w - static_cast<float>(DOUBLE_80332988);
    float innerX = FLOAT_8033292c + x0;
    for (int i = 0; i < 2; i++) {
        unsigned long uvFlag = 0;
        float y = y0;
        if (i != 0) {
            uvFlag = 4;
            y = y1;
        }
        DrawRect__8CMenuPcsFUlfffffffff(this, uvFlag, innerX, y, innerW, FLOAT_8033292c, FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    }

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x40);
    float innerH = h - static_cast<float>(DOUBLE_80332988);
    float innerY = FLOAT_8033292c + y0;
    for (int i = 0; i < 2; i++) {
        unsigned long uvFlag = 0;
        float x = x0;
        if (i != 0) {
            uvFlag = 8;
            x = x1;
        }
        DrawRect__8CMenuPcsFUlfffffffff(this, uvFlag, x, innerY, FLOAT_8033292c, innerH, FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    }

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x42);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, innerX, innerY, innerW, innerH, FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);

    int winStatePtr = *reinterpret_cast<int*>(self + 0x848);
    s16 state = *reinterpret_cast<s16*>(winStatePtr + 10);
    if (state == 0) {
        *reinterpret_cast<s16*>(winStatePtr + 8) = *reinterpret_cast<s16*>(winStatePtr + 8) + 1;
        if (*reinterpret_cast<s16*>(winStatePtr + 8) > 5) {
            *reinterpret_cast<s16*>(winStatePtr + 8) = 6;
            *reinterpret_cast<s16*>(winStatePtr + 10) = 1;
        }
    } else if (state == 1) {
        if (*reinterpret_cast<s16*>(winStatePtr + 8) != 6) {
            *reinterpret_cast<s16*>(winStatePtr + 8) = 6;
        }
    } else if (state == 2) {
        *reinterpret_cast<s16*>(winStatePtr + 8) = *reinterpret_cast<s16*>(winStatePtr + 8) - 1;
        if (*reinterpret_cast<s16*>(winStatePtr + 8) < 1) {
            *reinterpret_cast<s16*>(winStatePtr + 8) = 0;
            *reinterpret_cast<s16*>(winStatePtr + 10) = 3;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingWinMess(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetSingWinSize(int, short*, short*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetSingWinInfo(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetSingDynamicWinMessInfo(int, char*, char*, char*, char*, char*, char*, char*, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetSingWinScl(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetSingWinScl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingWinMessHeight()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkEquipPossible(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetEquipType(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetSmithItem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetRecipeMaterial(int, CMenuPcs::MaterialInfo*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetRaceStr(int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingBar(int, int, int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingSetLetterAttachflg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingGetLetterAttachflg()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcSingLife()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingLife()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingLifeInit(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingLifeResetWait()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetTribeStr(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetJobStr(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetHairStr(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetMenuStr(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetAttrStr(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetItemIcon(int)
{
	// TODO
}
