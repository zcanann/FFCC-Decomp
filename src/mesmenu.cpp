#include "ffcc/mesmenu.h"
#include "ffcc/chara.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/linkage.h"
#include "ffcc/menu.h"
#include "ffcc/p_menu.h"
#include "ffcc/pad.h"
#include "ffcc/ringmenu.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/textureman.h"

#include <math.h>
#include <string.h>

static const char sMesMenuClassName[] = "CMesMenu";
extern "C" {
const char s_mesMenuOnOffChangedFmt[] =
    "mesMenu\x95\x8e\xa6on/off\x82\xaa\x95\xcf\x8d\x58\x82\xb3\x82\xea\x82\xdc\x82\xb5\x82\xbd\x81\x42%d-%d\n\0\0\0";
int s_mesMenuShakePattern[4] = {1, 0, -1, 0};
int s_mesMenuIconFrames[4] = {1, 6, 7, 6};
extern float FLOAT_803308d8;
extern float FLOAT_803308dc;
extern float FLOAT_803308e0;
extern float FLOAT_803308e4;
extern float FLOAT_803308e8;
extern float FLOAT_803308ec;
extern float FLOAT_803308f0;
extern float FLOAT_803308f4;
extern float FLOAT_803308f8;
extern double DOUBLE_80330900;
extern float FLOAT_80330908;
extern float FLOAT_8033090c;
extern float FLOAT_80330910;
extern float FLOAT_80330914;
extern float FLOAT_80330918;
extern float FLOAT_8033091c;
extern float FLOAT_80330920;
extern float FLOAT_80330924;
extern float FLOAT_80330928;
extern float FLOAT_8033092c;
extern float FLOAT_80330930;
extern float FLOAT_80330934;
extern float FLOAT_80330938;
extern float FLOAT_8033093C;
extern float FLOAT_80330940;
extern float FLOAT_80330944;
extern float FLOAT_80330948;
extern float FLOAT_8033094C;
extern float FLOAT_80330950;
extern float FLOAT_80330954;
extern float FLOAT_80330958;
extern float FLOAT_8033095C;
extern float FLOAT_80330960;
extern float FLOAT_80330964;
extern float FLOAT_80330968;
extern float FLOAT_8033096C;
extern float FLOAT_80330970;
extern float FLOAT_80330974;
extern double DOUBLE_80330978;
extern float FLOAT_80330984;
extern float FLOAT_80330988;
extern float FLOAT_8033098C;
extern float FLOAT_80330990;
extern float FLOAT_80330980;
extern float FLOAT_80330994;
}

/*
 * --INFO--
 * PAL Address: 0x8009b4e4
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::SetPos(float x, float y)
{
	m_offsetX = x;
	m_offsetY = y;
}

/*
 * --INFO--
 * PAL Address: 0x8009b4f0
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::CloseRequest(int closeReason)
{
    CFlatRuntime::CStack stack[2];

    m_closeReason = closeReason;
    if (m_state <= 1) {
        if ((m_flags & 0x40) != 0) {
            m_mes.Set(0, 0);
            stack[0].m_word = m_menuIndex;
            stack[1].m_word = m_closeReason;
            gCFlatRuntime().SystemCall(0, 1, 3, 2, stack, 0);
            m_state = 4;
            m_active = 0;
            if (m_menuIndex < 4) {
                int menuIndex = m_menuIndex;
                MenuPcs.m_battleRingMenus[menuIndex]->SetFade(1);
            }
        } else {
            m_state = 2;
            m_stateTimer = 0;
            m_stateTimerMax = 4;
            if (((m_flags & 1) == 0) &&
                ((m_flags & 0x4000) == 0)) {
                Sound.PlaySe(6, 0x40, 0x7F, 0);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009b5fc
 * PAL Size: 744b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::Open(char* script, int x, int y, int flags, int unk1, int unk2, int unk3)
{
    float fVar1;
    unsigned int uVar2;
    bool bVar3;
    double dVar4;

    fVar1 = FLOAT_803308d8;
    m_offsetY = FLOAT_803308d8;
    m_offsetX = fVar1;
    m_active = 1;
    m_closeReason = 0;
    m_flags = (unsigned int)flags;

    if (m_menuIndex >= 4) {
        m_baseX = (float)x;
        m_baseY = (float)y;
        m_fromScriptPosition = 1;
        uVar2 = ((unsigned int)__cntlzw((unsigned int)(flags & 2))) >> 5;
        fVar1 = FLOAT_803308dc;
        m_marginX = fVar1;
        m_marginY = fVar1;
        int flagMask = -(flags >> 1 & 1);
        int displayOffset = 0x1C;
        displayOffset &= flagMask;
        m_mes.SetTlutBase(displayOffset);
        m_mes.SetShadow(uVar2);
    } else {
        MenuPcs.m_battleRingMenus[m_menuIndex]->SetFade(0);
        fVar1 = FLOAT_803308e0;
        float scaleY = FLOAT_803308e4;
        m_marginX = fVar1;
        m_marginY = scaleY;
    }

    m_buttonMask = unk1;
    m_itemIndex = unk2;
    m_nameIndex = unk3;
    m_mes.Set(script, flags & 0x20);

    fVar1 = FLOAT_803308e8;
    m_windowWidth = FLOAT_803308e8 * m_marginX + m_mes.GetMaxWidth();
    m_windowHeight = fVar1 * m_marginY + m_mes.GetMaxHeight();

    if (m_menuIndex >= 4) {
        if ((flags & 8) != 0) {
            fVar1 = FLOAT_803308ec;
            m_baseX = -(FLOAT_803308ec * m_windowWidth - m_baseX);
            m_baseY = -(fVar1 * m_windowHeight - m_baseY);
        } else if ((flags & 0x8000) != 0) {
            m_baseX -= m_windowWidth;
        }
    } else if ((flags & 0x100) == 0) {
        fVar1 = m_windowWidth;
        m_windowWidth = (fVar1 < FLOAT_803308f0) ? FLOAT_803308f0 : fVar1;
    }

    uVar2 = (unsigned int)m_menuIndex;
    if ((int)uVar2 < 4) {
        if ((uVar2 & 2) != 0) {
            dVar4 = (double)(((m_baseY - FLOAT_803308f4) +
                              m_offsetY + m_marginY) -
                             m_windowHeight);
        } else {
            dVar4 = (double)((m_baseY + m_offsetY +
                              m_marginY) +
                             FLOAT_803308f8);
        }
    } else {
        dVar4 = (double)((m_baseY + m_offsetY) +
                         m_marginY);
    }

    bVar3 = false;
    if (((int)uVar2 < 4) && ((uVar2 & 1) != 0)) {
        bVar3 = true;
    }
    if (bVar3) {
        fVar1 = ((m_baseX + m_offsetX) +
                 m_marginX) -
                m_windowWidth;
    } else {
        fVar1 = (m_baseX + m_offsetX) +
                m_marginX;
    }
    m_mes.SetPosition(fVar1, (float)dVar4);

    unsigned int state;
    if (m_menuIndex < 4) {
        state = ((unsigned int)flags >> 4) & 1;
    } else {
        state = (flags & 0x10) != 0;
    }
    m_state = state;
    m_stateTimer = 0;
    m_stateTimerMax = 8;
    if ((flags & 0x11) == 0 && ((m_flags & 0x4000) == 0)) {
        Sound.PlaySe(5, 0x40, 0x7F, 0);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009b8e4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::onScriptChanged(char*, int)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x8009b8e8
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::onScriptChanging(char*)
{
    int menuIndex;

    m_mes.Set(0, 0);
    m_state = 4;
    m_active = 0;
    menuIndex = m_menuIndex;
    if (menuIndex < 4) {
        MenuPcs.m_battleRingMenus[menuIndex]->SetFade(1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009b958
 * PAL Size: 916b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::DrawHeart(float x, float y, float z, float alpha)
{
    (void)z;

    CCaravanWork* scriptFood = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[m_menuIndex]);
    if (scriptFood == 0) {
        return;
    }

    if (FLOAT_803308d8 < alpha) {
        MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(FLOAT_80330908 * alpha)).Ref());
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x17));

        int heartOffset = 0x4C;
        if ((m_menuIndex & 1) != 0) {
            heartOffset = 0x30;
        }

        float pulseSinScale = FLOAT_80330910;
        float heartBaseX = x + (float)heartOffset;
        float heartBaseY = FLOAT_8033090c + y;
        float heartZero = FLOAT_803308d8;
        float pulseBase = FLOAT_80330920;
        float pulseAmp = FLOAT_8033091c;
        float pulseOne = FLOAT_80330914;
        float pulseTimerScale = FLOAT_80330918;

        for (int heartIndex = 0; heartIndex < (int)((unsigned int)scriptFood->m_maxHp >> 1); heartIndex++) {
            int heartValue = m_heartValue - heartIndex * 0xC;
            float heartTimer = (float)m_heartGrowTimers[heartIndex];
            float heartPulse =
                pulseAmp * (float)sin(pulseSinScale * -(heartTimer * pulseTimerScale - pulseOne)) + pulseOne;
            heartPulse *= pulseBase;

            int heartSubTimer = m_heartDropTimers[heartIndex];
            int heartShakeX;
            if (heartSubTimer == 0) {
                heartShakeX = 0;
            } else {
                heartShakeX = (heartSubTimer >> 2) * s_mesMenuShakePattern[(heartSubTimer + 1) & 3];
            }

            float heartX = heartBaseX + (float)heartShakeX;
            int heartShakeY;
            if (heartSubTimer == 0) {
                heartShakeY = 0;
            } else {
                heartShakeY = (heartSubTimer >> 2) * s_mesMenuShakePattern[heartSubTimer & 3];
            }

            float heartY = heartBaseY + (float)heartShakeY;

            MenuPcs.DrawRect(
                3, heartX, heartY, FLOAT_803308dc, FLOAT_803308dc, heartZero, heartZero,
                heartPulse, heartPulse, heartZero);

            if (heartValue > 0) {
                int fillAmount = 0x0B;
                if (heartValue < 0x0B) {
                    fillAmount = heartValue;
                }

                float u = (float)((scriptFood->m_statusTimers[5] != 0) ? 0 : 0x18);
                float v = (float)((0x0C - fillAmount) * 0x18);
                MenuPcs.DrawRect(
                    3, heartX, heartY, FLOAT_803308dc, FLOAT_803308dc, u, v, heartPulse, heartPulse,
                    FLOAT_803308d8);
            }

            heartBaseX += ((m_menuIndex & 1) != 0) ? FLOAT_80330924 : FLOAT_80330928;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009bcec
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::CalcHeart()
{
    CCaravanWork* scriptFood = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[m_menuIndex]);
    if (scriptFood == 0) {
        return;
    }

    unsigned int foodCount = static_cast<unsigned int>(scriptFood->m_hp);
    int targetValue = (int)(foodCount * 6);
    if (m_heartTarget < targetValue) {
        m_heartTarget += targetValue - m_heartTarget;
    } else if (targetValue < m_heartTarget) {
        m_heartTarget -= m_heartTarget - targetValue;
    }

    int currentValue = m_heartValue;
    if (currentValue < m_heartTarget) {
        int index = currentValue / 0xC;
        if (m_heartGrowTimers[index] == 0) {
            m_heartGrowTimers[index] = 0x10;
        }

        int nextValue = m_heartValue + 2;
        int maxValue = m_heartTarget;
        if (nextValue < maxValue) {
            maxValue = nextValue;
        }
        m_heartValue = maxValue;
    } else if (m_heartTarget < currentValue) {
        m_heartValue = (currentValue - 2U) & ~((int)(currentValue - 2U) >> 0x1F);

        int decValue = m_heartValue;
        int index = decValue / 0xC;
        if (m_heartDropTimers[index] == 0) {
            m_heartDropTimers[index] = 0x10;
        }
        if (m_foodShakeTimer == 0) {
            m_foodShakeTimer = 0x10;
        }
    }

    for (int i = 0; i < 8; i += 4) {
        int value = m_heartGrowTimers[i] - 1;
        m_heartGrowTimers[i] = value & ~((int)value >> 0x1F);

        value = m_heartDropTimers[i] - 1;
        m_heartDropTimers[i] = value & ~((int)value >> 0x1F);

        value = m_heartGrowTimers[i + 1] - 1;
        m_heartGrowTimers[i + 1] = value & ~((int)value >> 0x1F);

        value = m_heartDropTimers[i + 1] - 1;
        m_heartDropTimers[i + 1] = value & ~((int)value >> 0x1F);

        value = m_heartGrowTimers[i + 2] - 1;
        m_heartGrowTimers[i + 2] = value & ~((int)value >> 0x1F);

        value = m_heartDropTimers[i + 2] - 1;
        m_heartDropTimers[i + 2] = value & ~((int)value >> 0x1F);

        value = m_heartGrowTimers[i + 3] - 1;
        m_heartGrowTimers[i + 3] = value & ~((int)value >> 0x1F);

        value = m_heartDropTimers[i + 3] - 1;
        m_heartDropTimers[i + 3] = value & ~((int)value >> 0x1F);
    }

    unsigned int value = m_foodShakeTimer - 1;
    m_foodShakeTimer = value & ~((int)value >> 0x1F);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::onDraw()
{
    if ((m_menuIndex == 0) &&
        (static_cast<signed char>(static_cast<int>(static_cast<unsigned int>(CFlatGameFlags()) << 30) >> 31) != 0)) {
        int iconFrame = 0;
        int charaMode = Chara.MogFur().m_commandIndex;
        switch (charaMode) {
        case 0:
            iconFrame = 3;
            break;
        case 1:
            iconFrame = 4;
            break;
        case 2:
            iconFrame = 5;
            break;
        case 3:
            iconFrame = 2;
            break;
        case 4: {
            bool activeInput = false;
            unsigned short buttons;

            if ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) {
                activeInput = true;
            }

            if (activeInput) {
                buttons = 0;
            } else {
                int padIndex = 0;
                padIndex &= ~-((__cntlzw(static_cast<unsigned int>(Pad.m_debugPadPort)) & 0x20) >> 5);
                buttons = Pad.GetPadInputs()[padIndex].button[0];
            }

            if ((buttons & 0x100) != 0) {
                iconFrame = s_mesMenuIconFrames[(System.m_frameCounter & 6) >> 1];
            } else {
                iconFrame = s_mesMenuIconFrames[0];
            }
            break;
        }
        }

        MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).Ref());
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0));
        MenuPcs.DrawRect(
            0, (float)(int)(Chara.MogFur().m_cursorX - 0x20), (float)(int)Chara.MogFur().m_cursorY,
            FLOAT_8033092c, FLOAT_8033092c, FLOAT_803308d8, (float)(iconFrame << 5), FLOAT_80330914, FLOAT_80330914,
            FLOAT_803308d8);
    }

    int menuIndex = m_menuIndex;
    if ((menuIndex >= 4) && (m_active == 0)) {
        return;
    }
    if ((Game.m_gameWork.m_menuStageMode != 0) && (menuIndex >= 1) && (menuIndex < 4)) {
        return;
    }

    CFont* font = MenuPcs.m_fonts[0];
    font->SetMargin(FLOAT_803308d8);
    font->SetShadow(1);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    float stageBlend = (float)m_stageFadeTimer * FLOAT_80330918;
    if (m_stageFadeOut != 0) {
        stageBlend = FLOAT_80330914 - stageBlend;
    }
    if (FLOAT_803308d8 == stageBlend) {
        return;
    }

    float stateBlend;
    int state = m_state;
    if ((state == 0) || ((unsigned int)(state - 1) <= 1) || (state == 3)) {
        if (state == 0) {
            stateBlend = (float)m_stateTimer / (float)m_stateTimerMax;
        } else if (state == 3) {
            stateBlend = FLOAT_80330914 - (float)m_stateTimer / (float)m_stateTimerMax;
        } else {
            stateBlend = FLOAT_80330914;
        }
    } else {
        stateBlend = FLOAT_803308d8;
    }

    if (m_menuIndex < 4) {
        CCaravanWork* scriptFood = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[m_menuIndex]);
        if (scriptFood == 0) {
            return;
        }

        float pulse = FLOAT_8033092c * (FLOAT_80330914 - sinf(FLOAT_80330930 * stageBlend));
        MenuPcs.m_battleRingMenus[m_menuIndex]->GetDispCounter();
        int maskX = m_menuIndex & 1;
        float pulseX;
        if (maskX != 0) {
            pulseX = pulse;
        } else {
            pulseX = -pulse;
        }
        int maskY = m_menuIndex & 2;
        float baseX = (m_baseX + m_offsetX) + pulseX;
        float pulseY;
        if (maskY != 0) {
            pulseY = pulse;
        } else {
            pulseY = -pulse;
        }
        float baseY = (m_baseY + m_offsetY) + pulseY;

        if (FLOAT_803308d8 < stateBlend) {
            float width = m_windowWidth * stateBlend;
            float height = m_windowHeight * stateBlend;
            float edgeX;
            if (maskX != 0) {
                edgeX = -m_windowWidth;
            } else {
                edgeX = m_windowWidth - width;
            }
            float drawX = baseX + edgeX;

            float edgeY;
            if (maskY != 0) {
                edgeY = (FLOAT_80330934 - m_windowHeight) + (m_windowHeight - height);
            } else {
                edgeY = FLOAT_803308f8;
            }
            float drawY = baseY + edgeY;

            float stateAlpha = FLOAT_80330908 * stateBlend;
            float alphaF = stateAlpha * stageBlend;
            MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).Ref());
            MenuPcs.DrawWindow(drawX, drawY, width, height, static_cast<CMenuPcs::TEX>(2), FLOAT_8033092c);

            if ((m_state == 1) && (FLOAT_80330914 == stageBlend)) {
                m_mes.Draw();
                MenuPcs.DrawInit();
            }

            if ((m_itemIndex >= 0) || (m_nameIndex >= 0)) {
                MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x14));
                MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).Ref());

                float cursorWave = sinf(FLOAT_80330930 * (FLOAT_80330914 - stateBlend) + FLOAT_80330930);
                int iconMenuIndex = m_menuIndex;
                int signX = -32;
                if ((iconMenuIndex & 1) != 0) {
                    signX = 32;
                }
                float wobble = (float)signX * (FLOAT_80330914 - cursorWave);
                float iconX = (drawX + wobble) +
                              (((iconMenuIndex & 1) != 0) ? FLOAT_80330938 : (width - FLOAT_8033093C) - FLOAT_80330938);
                float iconY = drawY + (((iconMenuIndex & 2) != 0) ? FLOAT_80330940 + height : FLOAT_80330944);
                MenuPcs.DrawRect(
                    ((iconMenuIndex & 1) != 0) ? 8 : 0, iconX, iconY, FLOAT_8033093C, FLOAT_80330948,
                    (float)(((iconMenuIndex & 2) != 0) ? 144 : 0), FLOAT_803308d8, FLOAT_80330914, FLOAT_80330914,
                    FLOAT_803308d8);

                if (m_nameIndex >= 0) {
                    font->SetScale(FLOAT_8033094C);
                    font->SetShadow(1);
                    font->SetMargin(FLOAT_803308d8);
                    float textWidth = font->GetWidth(Game.m_cFlatDataArr[1].TableStrings(2)[m_nameIndex]);
                    font->DrawInit();
                    font->SetTlut(0xF);
                    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).color);
                    font->SetPosX(iconX + (((m_menuIndex & 1) != 0) ? FLOAT_80330950 : FLOAT_80330954 - textWidth));
                    font->SetPosY(iconY + (float)(((m_menuIndex & 2) != 0) ? 8 : 31));
                    font->Draw(Game.m_cFlatDataArr[1].TableStrings(2)[m_nameIndex]);
                    MenuPcs.DrawInit();
                }

                if (m_itemIndex >= 0) {
                    int itemIndex = m_itemIndex;
                    int itemU = (itemIndex % 8) * 0x30;
                    int itemV = (itemIndex / 8) * 0x30;
                    MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).Ref());
                    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x18));
                    MenuPcs.m_textures[0x18]->SetExternalTlut(0, 1);
                    int itemMaskX = m_menuIndex & 1;
                    int itemOffsetX = 83;
                    if (itemMaskX != 0) {
                        itemOffsetX = 13;
                    }
                    bool itemFlip = false;
                    if ((itemMaskX != 0) && ((m_flags & 4) == 0)) {
                        itemFlip = true;
                    }
                    MenuPcs.DrawRect(
                        itemFlip ? 8 : 0,
                        iconX + (float)itemOffsetX, FLOAT_80330958 + iconY, FLOAT_8033095C, FLOAT_80330960,
                        (float)itemU, (float)itemV, FLOAT_80330914, FLOAT_80330914, FLOAT_803308d8);
                }
            }
        }

        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x16));
        float titleAlpha = FLOAT_80330908 * stageBlend;
        MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(titleAlpha)).Ref());
        unsigned int frameMask = m_menuIndex;
        int frameNegX = -(int)(frameMask & 1);
        float frameX = baseX - (float)(frameNegX & 0x80);
        float frameY = baseY - (float)(-(int)(frameMask >> 1 & 1) & 0x38);
        MenuPcs.DrawRect(
            0, frameX, frameY, FLOAT_80330964, FLOAT_80330948,
            (float)(((int)(-(int)(frameMask & 2) | (int)(frameMask & 2)) >> 31) & 0x80),
            (float)(((int)(frameNegX | (int)(frameMask & 1)) >> 31) & 0x38), FLOAT_80330914, FLOAT_80330914,
            FLOAT_803308d8);

        font->SetScale(FLOAT_8033094C);
        float titleWidth = font->GetWidth(reinterpret_cast<char*>(scriptFood->m_name));
        font->DrawInit();
        font->SetTlut(0xF);
        font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(titleAlpha)).color);
        font->SetPosX(baseX + (((m_menuIndex & 1) != 0) ? FLOAT_80330968 - titleWidth : FLOAT_80330950));
        font->SetPosY(FLOAT_8033096C + frameY);
        font->Draw(reinterpret_cast<char*>(scriptFood->m_name));
        MenuPcs.DrawInit();

        {
            CCaravanWork* heartFood =
                reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[m_menuIndex]);
            if ((heartFood != 0) && (FLOAT_803308d8 < stageBlend)) {
                MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(titleAlpha)).Ref());
                MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x17));

                int heartOffset = 0x4C;
                if ((m_menuIndex & 1) != 0) {
                    heartOffset = 0x30;
                }

                float heartBaseX = frameX + (float)heartOffset;
                float heartBaseY = FLOAT_8033090c + frameY;
                float pulseSinScale = FLOAT_80330910;
                float pulseTimerScale = FLOAT_80330918;
                float pulseOne = FLOAT_80330914;
                float pulseAmp = FLOAT_8033091c;
                float pulseBase = FLOAT_80330920;
                float heartZero = FLOAT_803308d8;

                for (int heartIndex = 0; heartIndex < (int)((unsigned int)heartFood->m_maxHp >> 1);
                     heartIndex++) {
                    int heartValue = m_heartValue - heartIndex * 0xC;
                    float heartTimer = (float)m_heartGrowTimers[heartIndex];
                    float heartPulse =
                        pulseAmp * (float)sin(pulseSinScale * -(heartTimer * pulseTimerScale - pulseOne)) + pulseOne;
                    heartPulse *= pulseBase;

                    int heartSubTimer = m_heartDropTimers[heartIndex];
                    int heartShakeX;
                    if (heartSubTimer == 0) {
                        heartShakeX = 0;
                    } else {
                        heartShakeX = (heartSubTimer >> 2) * s_mesMenuShakePattern[(heartSubTimer + 1) & 3];
                    }

                    float heartX = heartBaseX + (float)heartShakeX;
                    int heartShakeY;
                    if (heartSubTimer == 0) {
                        heartShakeY = 0;
                    } else {
                        heartShakeY = (heartSubTimer >> 2) * s_mesMenuShakePattern[heartSubTimer & 3];
                    }

                    float heartY = heartBaseY + (float)heartShakeY;

                    MenuPcs.DrawRect(
                        3, heartX, heartY, FLOAT_803308dc, FLOAT_803308dc, heartZero, heartZero,
                        heartPulse, heartPulse, heartZero);

                    if (heartValue > 0) {
                        int fillAmount = 0x0B;
                        if (heartValue < 0x0B) {
                            fillAmount = heartValue;
                        }

                        float u = (float)((heartFood->m_statusTimers[5] != 0) ? 0 : 0x18);
                        float v = (float)((0x0C - fillAmount) * 0x18);
                        MenuPcs.DrawRect(
                            3, heartX, heartY, FLOAT_803308dc, FLOAT_803308dc, u, v, heartPulse, heartPulse,
                            FLOAT_803308d8);
                    }

                    heartBaseX += ((m_menuIndex & 1) != 0) ? FLOAT_80330924 : FLOAT_80330928;
                }
            }
        }

        int foodTimer = m_foodShakeTimer;
        int foodId = scriptFood->m_id;
        int foodIcon = foodId % 100 + ((foodId - 100) / 100) * 4;
        int foodU = (foodIcon % 8) * 0x30;
        int foodV = (foodIcon / 8) * 0x30;
        int foodShakeX;
        if (foodTimer == 0) {
            foodShakeX = 0;
        } else {
            foodShakeX = (foodTimer >> 2) * s_mesMenuShakePattern[3 - ((foodTimer + 1) & 3)];
        }
        float shakeX = (float)foodShakeX;
        int foodShakeY;
        if (foodTimer == 0) {
            foodShakeY = 0;
        } else {
            foodShakeY = (foodTimer >> 2) * s_mesMenuShakePattern[3 - (foodTimer & 3)];
        }
        float shakeY = (float)foodShakeY;
        MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(titleAlpha)).Ref());
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x18));
        MenuPcs.m_textures[0x18]->SetExternalTlut(
            (scriptFood->m_hp != 0) ? 0 : (void*)MenuPcs.m_externalFontTlut, 1);
        int foodMaskX = m_menuIndex & 1;
        int foodOffsetX = 5;
        if (foodMaskX != 0) {
            foodOffsetX = 75;
        }
        MenuPcs.DrawRect(
            (foodMaskX != 0) ? 0 : 8, (frameX + shakeX) + (float)foodOffsetX,
            FLOAT_80330958 + (frameY + shakeY), FLOAT_8033095C, FLOAT_80330960,
            (float)foodU, (float)foodV, FLOAT_80330914, FLOAT_80330914,
            FLOAT_803308d8);
    } else {
        float sizeX = m_windowWidth * stateBlend;
        float sizeY = m_windowHeight * stateBlend;
        float drawX = (FLOAT_803308ec * m_windowWidth + (m_baseX + m_offsetX)) - FLOAT_803308ec * sizeX;
        float drawY = (FLOAT_803308ec * m_windowHeight + (m_baseY + m_offsetY)) - FLOAT_803308ec * sizeY;

        if ((m_flags & 1) == 0) {
            float stateAlpha = FLOAT_80330908 * stateBlend;
            float alphaF = stateAlpha * stageBlend;
            MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).Ref());

            int tex = 0xB;
            if ((m_flags & 0x200) != 0) {
                tex = 2;
            }
            MenuPcs.DrawWindow(drawX, drawY, sizeX, sizeY, static_cast<CMenuPcs::TEX>(tex), FLOAT_8033092c);

            if ((m_itemIndex >= 0) || (m_nameIndex >= 0)) {
                unsigned int iconAnchor = (m_flags >> 10) & 7;
                if (iconAnchor != 0) {
                    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x14));
                    MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).Ref());
                    int anchorX = (iconAnchor - 1) & 1;
                    float iconEdgeX;
                    if (anchorX != 0) {
                        iconEdgeX = FLOAT_80330938;
                    } else {
                        iconEdgeX = (sizeX - FLOAT_8033093C) - FLOAT_80330938;
                    }
                    unsigned int anchorY = (iconAnchor - 1) & 2;
                    float iconX = (drawX + FLOAT_803308d8) + iconEdgeX;
                    float iconEdgeY;
                    if (anchorY != 0) {
                        iconEdgeY = FLOAT_80330940 + sizeY;
                    } else {
                        iconEdgeY = FLOAT_80330944;
                    }
                    float iconY = drawY + iconEdgeY;
                    MenuPcs.DrawRect(
                        (anchorX != 0) ? 8 : 0, iconX, iconY, FLOAT_8033093C, FLOAT_80330948,
                        (float)((anchorY != 0) ? 144 : 0), FLOAT_803308d8, FLOAT_80330914, FLOAT_80330914,
                        FLOAT_803308d8);

                    if (m_nameIndex >= 0) {
                        font->SetScale(FLOAT_8033094C);
                        font->SetShadow(1);
                        font->SetMargin(FLOAT_803308d8);
                        float textWidth = font->GetWidth(Game.m_cFlatDataArr[1].TableStrings(2)[m_nameIndex]);
                        font->DrawInit();
                        font->SetTlut(0xF);
                        font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).color);
                        font->SetPosX(iconX + ((anchorX != 0) ? FLOAT_80330950 : FLOAT_80330954 - textWidth));
                        font->SetPosY(iconY + (float)((anchorY != 0) ? 8 : 31));
                        font->Draw(Game.m_cFlatDataArr[1].TableStrings(2)[m_nameIndex]);
                        MenuPcs.DrawInit();
                    }

                    if (m_itemIndex >= 0) {
                        int itemIndex = m_itemIndex;
                        int itemU = (itemIndex % 8) * 0x30;
                        int itemV = (itemIndex / 8) * 0x30;
                        MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).Ref());
                        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x18));
                        MenuPcs.m_textures[0x18]->SetExternalTlut(0, 1);
                        int itemOffsetX = 83;
                        if (anchorX != 0) {
                            itemOffsetX = 13;
                        }
                        bool itemFlip = false;
                        if ((anchorX != 0) && ((m_flags & 4) == 0)) {
                            itemFlip = true;
                        }
                        MenuPcs.DrawRect(
                            itemFlip ? 8 : 0,
                            iconX + (float)itemOffsetX, FLOAT_80330958 + iconY, FLOAT_8033095C, FLOAT_80330960,
                            (float)itemU, (float)itemV, FLOAT_80330914, FLOAT_80330914,
                            FLOAT_803308d8);
                    }
                }
            }
        }

        if ((m_state == 1) && ((m_flags & 0x2000) != 0)) {
            float windowScale = stateBlend * stageBlend;
            float pulseScale = FLOAT_80330970 * (FLOAT_80330914 - windowScale) + FLOAT_80330914;
            float time = fmod(FLOAT_80330974 * (float)m_stateTimer, DOUBLE_80330978);
            if (time > FLOAT_80330914) {
                time = FLOAT_803308e8 - time;
            }

            float angle = FLOAT_80330910 * time;
            float sinY = sinf(angle);
            float sinX = sinf(FLOAT_80330980 + angle);
            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));
            float alpha255 = FLOAT_80330908 * windowScale;
            MenuPcs.SetColor(CColor(0, 0, 0, static_cast<unsigned char>((FLOAT_803308ec * alpha255) * stageBlend)).Ref());
            float promptX = (float)(int)(FLOAT_803308f8 + drawX);
            float promptY = (float)(int)(FLOAT_8033092c + drawY);
            float waveX = promptX + FLOAT_80330984 * (pulseScale * sinX);
            float waveY = promptY - FLOAT_80330988 * (pulseScale * sinY);
            float fadeScale = FLOAT_80330914 - pulseScale;
            float rotation = FLOAT_8033091c * (FLOAT_803308e8 * (time - FLOAT_803308ec));
            MenuPcs.DrawRect(
                3, FLOAT_803308e4 + waveX, FLOAT_803308e4 + waveY, FLOAT_8033098C, FLOAT_8033095C, FLOAT_803308d8,
                FLOAT_803308d8, FLOAT_80330990 * (FLOAT_80330914 + fadeScale), FLOAT_80330990 * (pulseScale + fadeScale),
                rotation);
            MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha255 * stageBlend)).Ref());
            MenuPcs.DrawRect(
                3, waveX, waveY, FLOAT_8033098C, FLOAT_8033095C, FLOAT_803308d8, FLOAT_803308d8,
                FLOAT_80330990 * pulseScale, FLOAT_80330990 * pulseScale, rotation);
        }

        if (m_state == 1) {
            m_mes.Draw();
            MenuPcs.DrawInit();
        }
    }

    if ((m_state == 1) && (m_mes.GetWait() == 3)) {
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0));
        MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(FLOAT_80330908 * stageBlend)).Ref());

        MenuPcs.DrawRect(
            0, FLOAT_80330994 + *(float*)((char*)this + 0x3CB8),
            (float)*(int*)((char*)this + 0x3D34) * *(float*)((char*)this + 0x3D40) +
                (FLOAT_803308e8 + *(float*)((char*)this + 0x3CBC) + *(float*)((char*)this + 0x3D3C)),
            FLOAT_8033092c, FLOAT_8033092c, FLOAT_803308d8, FLOAT_803308d8, FLOAT_80330914, FLOAT_80330914, FLOAT_803308d8);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009d69c
 * PAL Size: 2292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::onCalc()
{
    CFlatRuntime::CStack stack2[2];
    if (Game.m_gameWork.m_menuStageMode != 0) {
        if ((m_menuIndex >= 1) && (m_menuIndex < 4)) {
            return;
        }
    }

    unsigned int stageBit = 0;
    if (m_menuIndex < 4) {
        stageBit = CFlatEnabledEventFlags() & 1;
    } else {
        stageBit = CFlatEnabledEventFlags() & 2;
    }

    int desiredStageFlag = stageBit != 0;
    if (desiredStageFlag != m_stageFadeOut) {
        System.Printf(const_cast<char*>(s_mesMenuOnOffChangedFmt));
        m_stageFadeOut =
            ((unsigned int)__cntlzw(m_stageFadeOut) >> 5) & 0xFF;
        m_stageFadeTimer = 0x10 - m_stageFadeTimer;
    }

    unsigned int timer = m_stageFadeTimer - 1;
    m_stageFadeTimer = timer & ~((int)timer >> 0x1F);

    if ((m_menuIndex >= 4) && (m_active == 0)) {
        return;
    }

    if (m_menuIndex < 4) {
        CCaravanWork* scriptFood = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[m_menuIndex]);
        if (scriptFood != 0) {
            unsigned int foodCount = (unsigned int)scriptFood->m_hp;
            int targetValue = (int)(foodCount * 6);
            if (m_heartTarget < targetValue) {
                m_heartTarget += targetValue - m_heartTarget;
            } else if (targetValue < m_heartTarget) {
                m_heartTarget -= m_heartTarget - targetValue;
            }

            int currentValue = m_heartValue;
            if (currentValue < m_heartTarget) {
                int idx = currentValue / 0xC;
                if (m_heartGrowTimers[idx] == 0) {
                    m_heartGrowTimers[idx] = 0x10;
                }

                int nextValue = m_heartValue + 2;
                int maxValue = m_heartTarget;
                if (nextValue < maxValue) {
                    maxValue = nextValue;
                }
                m_heartValue = maxValue;
            } else if (m_heartTarget < currentValue) {
                m_heartValue = (currentValue - 2U) & ~((int)(currentValue - 2U) >> 0x1F);

                int decValue = m_heartValue;
                int idx = decValue / 0xC;
                if (m_heartDropTimers[idx] == 0) {
                    m_heartDropTimers[idx] = 0x10;
                }
                if (m_foodShakeTimer == 0) {
                    m_foodShakeTimer = 0x10;
                }
            }

            int value;
            for (int heartIndex = 0; heartIndex < 8; heartIndex += 4) {
                value = m_heartGrowTimers[heartIndex] - 1;
                m_heartGrowTimers[heartIndex] = value & ~((int)value >> 0x1F);

                value = m_heartDropTimers[heartIndex] - 1;
                m_heartDropTimers[heartIndex] = value & ~((int)value >> 0x1F);

                value = m_heartGrowTimers[heartIndex + 1] - 1;
                m_heartGrowTimers[heartIndex + 1] = value & ~((int)value >> 0x1F);

                value = m_heartDropTimers[heartIndex + 1] - 1;
                m_heartDropTimers[heartIndex + 1] = value & ~((int)value >> 0x1F);

                value = m_heartGrowTimers[heartIndex + 2] - 1;
                m_heartGrowTimers[heartIndex + 2] = value & ~((int)value >> 0x1F);

                value = m_heartDropTimers[heartIndex + 2] - 1;
                m_heartDropTimers[heartIndex + 2] = value & ~((int)value >> 0x1F);

                value = m_heartGrowTimers[heartIndex + 3] - 1;
                m_heartGrowTimers[heartIndex + 3] = value & ~((int)value >> 0x1F);

                value = m_heartDropTimers[heartIndex + 3] - 1;
                m_heartDropTimers[heartIndex + 3] = value & ~((int)value >> 0x1F);
            }

            value = m_foodShakeTimer - 1;
            m_foodShakeTimer = value & ~((int)value >> 0x1F);
        }
    }

    if (m_active == 0) {
        return;
    }

    int state = m_state;
    switch (state) {
    case 0:
        (void)sin(FLOAT_80330980 +
                  (FLOAT_80330910 * (float)m_stateTimer) / (float)m_stateTimerMax);
        break;
    case 1: {
            m_windowScale = FLOAT_80330914;
            m_mes.Calc();

            unsigned int downMask = 0;
            unsigned int repeatMask = 0;
            if (m_stateTimer > 0) {
                for (int button = 0; button < 4; button++) {
                    if ((m_buttonMask & (1 << button)) != 0) {
                        downMask |= MenuPcs.GetButtonDown(button) & 0xFFFF;
                        repeatMask |= MenuPcs.GetButtonRepeat(button) & 0xFFFF;
                    }
                }
            }

            int wait = m_mes.GetWait();
            if (wait == 3) {
                int cursor = *(int*)((char*)this + 0x3D34);
                int cursorMax = *(int*)((char*)this + 0x3D30);
                int altCursor = *(int*)((char*)this + 0x3D38);
                if ((repeatMask & 8) != 0) {
                    cursor--;
                    if (cursor < 0) {
                        cursor = cursorMax - 1;
                    }
                    if ((m_flags & 0x4000) == 0) {
                        Sound.PlaySe(1, 0x40, 0x7F, 0);
                    }
                } else if ((repeatMask & 4) != 0) {
                    cursor++;
                    if (cursorMax <= cursor) {
                        cursor = 0;
                    }
                    if ((m_flags & 0x4000) == 0) {
                        Sound.PlaySe(1, 0x40, 0x7F, 0);
                    }
                } else if ((downMask & 0x200) != 0) {
                    if (altCursor >= 0) {
                        cursor = altCursor;
                        if ((m_flags & 0x4000) == 0) {
                            Sound.PlaySe(3, 0x40, 0x7F, 0);
                        }
                    } else {
                        if ((m_flags & 0x4000) == 0) {
                            Sound.PlaySe(1, 0x40, 0x7F, 0);
                        }
                    }
                }

                *(int*)((char*)this + 0x3D34) = cursor;
                if ((altCursor >= 0) && (cursor == altCursor)) {
                    cursor = -1;
                }
                *(int*)((char*)this + 0x3CDC) = cursor;
            } else {
                int wait1 = m_mes.GetWait();
                if (((wait1 == 1) || (m_mes.GetWait() == 5)) &&
                    (*(int*)((char*)this + 0x3CC8) == 0)) {
                    *(int*)((char*)this + 0x3CC8) = 1;
                    *(int*)((char*)this + 0x3CD8) = 0;
                }
            }

            if ((downMask & 0x100) != 0) {
                int wait2 = m_mes.GetWait();
                if (wait2 == 0) {
                    *(int*)((char*)this + 0x3C9C) = *(int*)((char*)this + 0x3C98) + 1000;
                    m_mes.useFlag(*(int*)((char*)this + 0x3C28), 1);
                } else {
                    int wait3 = m_mes.GetWait();
                    if ((wait3 == 3) && ((m_flags & 0x4000) == 0)) {
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                    }
                    int wait4 = m_mes.GetWait();
                    if ((wait4 != 1) && (m_mes.GetWait() != 5) &&
                        (*(int*)((char*)this + 0x3C90) == 0) && ((m_flags & 0x4000) == 0)) {
                        Sound.PlaySe(0xC, 0x40, 0x7F, 0);
                    }
                }

                if (*(int*)((char*)this + 0x3CC8) == 0) {
                    *(int*)((char*)this + 0x3CC8) = 1;
                    *(int*)((char*)this + 0x3CD8) = 0;
                }
            }

            int msgState = *(int*)((char*)this + 0x3CC8);
            if (msgState != 0) {
                bool closeReady = false;
                if ((msgState != 0) && (*(int*)((char*)this + 0x3CD8) == *(int*)((char*)this + 0x3CD4))) {
                    closeReady = true;
                }
                if (closeReady) {
                if (*(int*)((char*)this + 0x3C90) != 0) {
                    int wait5 = m_mes.GetWait();
                    if (wait5 != 4) {
                        m_closeReason = 0;
                        if (m_state <= 1) {
                            if ((m_flags & 0x40) != 0) {
                                CFlatRuntime::CStack stack[2];
                                m_mes.Set(0, 0);
                                stack[0].m_word = m_menuIndex;
                                stack[1].m_word = m_closeReason;
                                gCFlatRuntime().SystemCall(0, 1, 3, 2, stack, 0);
                                m_state = 4;
                                m_active = 0;
                                if (m_menuIndex < 4) {
                                    MenuPcs.m_battleRingMenus[m_menuIndex]->SetFade(1);
                                }
                            } else {
                                m_state = 2;
                                m_stateTimer = 0;
                                m_stateTimerMax = 4;
                                if (((m_flags & 1) == 0) &&
                                    ((m_flags & 0x4000) == 0)) {
                                    Sound.PlaySe(6, 0x40, 0x7F, 0);
                                }
                            }
                        }
                    }
                } else {
                    m_mes.Next();
                }
                }
            }
        }
        break;
    case 3: {
        float step = FLOAT_80330914 - (float)m_stateTimer / (float)m_stateTimerMax;
        m_windowScale = FLOAT_803308ec * (FLOAT_80330914 + (float)sin(FLOAT_80330910 * step + FLOAT_80330980));
        break;
    }
    }

    m_stateTimer = m_stateTimer + 1;
    if (m_stateTimerMax < m_stateTimer) {
        int nextState = m_state;
        switch (nextState) {
        case 0:
            m_state = 1;
            m_stateTimer = 0;
            m_stateTimerMax = 0;
            break;
        case 2:
            m_state = 3;
            m_stateTimer = 0;
            m_stateTimerMax = 8;
            break;
        case 3: {
            m_state = 4;
            m_stateTimer = 0;
            m_stateTimerMax = 0;
            m_mes.Set(0, 0);
            stack2[0].m_word = m_menuIndex;
            stack2[1].m_word = m_closeReason;
            gCFlatRuntime().SystemCall(0, 1, 3, 2, stack2, 0);
            m_state = 4;
            m_active = 0;
            if (m_menuIndex < 4) {
                MenuPcs.m_battleRingMenus[m_menuIndex]->SetFade(1);
            }
            break;
        }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009df90
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::Destroy()
{
    m_mes.Set(0, 0);
    CMenu::Destroy();
}

/*
 * --INFO--
 * PAL Address: 0x8009dfd0
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::Create()
{
    Destroy();
    CMenu::Create();

    float defaultValue = FLOAT_803308d8;
    m_offsetY = defaultValue;
    m_offsetX = defaultValue;
    m_active = 0;
    m_state = 4;
    m_stageFadeTimer = 0;
    m_stageFadeOut = 0;

    if (m_menuIndex < 4) {
        int x = 0x10;
        if ((m_menuIndex & 1) != 0) {
            x = 0x270;
        }
        m_baseX = (float)x;

        int y = 0x18;
        if ((m_menuIndex & 2) != 0) {
            y = 0x1B0;
        }
        defaultValue = FLOAT_803308d8;
        m_baseY = (float)y;
        m_windowWidth = defaultValue;
        m_windowHeight = defaultValue;
        m_windowScale = defaultValue;
        m_fromScriptPosition = 0;
        m_flags = 0;
        m_heartValue = 0;
        m_heartTarget = 0;
        memset(m_heartGrowTimers, 0, sizeof(m_heartGrowTimers));
        memset(m_heartDropTimers, 0, sizeof(m_heartDropTimers));
        m_foodShakeTimer = 0;
    }

    m_nameIndex = 0;
    m_itemIndex = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8009e0fc
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMesMenu::~CMesMenu()
{
    Destroy();
}

/*
 * --INFO--
 * PAL Address: 0x8009e17c
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMesMenu::CMesMenu()
{
}
