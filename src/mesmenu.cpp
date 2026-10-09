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

enum
{
#ifdef VERSION_GCCJGC
    MesMenuBattleTexture = 0x15,
    MesMenuHeartTexture = 0x16,
    MesMenuFaceTexture = 0x17,
    MesMenuGbaTexture = 0x1D
#else
    MesMenuBattleTexture = 0x16,
    MesMenuHeartTexture = 0x17,
    MesMenuFaceTexture = 0x18,
    MesMenuGbaTexture = 0x1E
#endif
};

extern "C" {
int s_mesMenuShakePattern[4] = {1, 0, -1, 0};
int s_mesMenuIconFrames[4] = {1, 6, 7, 6};
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: UNUSED
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::SetTlut(CMenuPcs::TEX tex, _GXColor* tlut)
{
    m_textures[tex]->SetExternalTlut(tlut, 1);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMesMenu::close(int closeReason)
{
    CFlatRuntime::CStack stack[2];

    m_mes.Set(0, 0);
    stack[0].m_word = m_menuIndex;
    stack[1].m_word = m_closeReason;
    gCFlatRuntime().SystemCall(0, 1, 3, 2, stack, 0);
    m_state = 4;
    m_active = 0;
    if (m_menuIndex < 4) {
        MenuPcs.GetRingMenu(m_menuIndex)->SetFade(1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009e17c
 * PAL Size: 68b
 * EN Address: 0x8009DAA0
 * EN Size: 68b
 * JP Address: 0x8009C264
 * JP Size: 68b
 */
CMesMenu::CMesMenu()
{
}

/*
 * --INFO--
 * PAL Address: 0x8009e0fc
 * PAL Size: 128b
 * EN Address: 0x8009DA20
 * EN Size: 128b
 * JP Address: 0x8009C1E4
 * JP Size: 128b
 */
CMesMenu::~CMesMenu()
{
    Destroy();
}

/*
 * --INFO--
 * PAL Address: 0x8009dfd0
 * PAL Size: 300b
 * EN Address: 0x8009D900
 * EN Size: 288b
 * JP Address: 0x8009C0BC
 * JP Size: 296b
 */
void CMesMenu::Create()
{
    Destroy();
    CMenu::Create();

    float defaultValue = 0.0f;
#ifdef VERSION_GCCP01
    m_offsetY = defaultValue;
    m_offsetX = defaultValue;
#endif
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
        defaultValue = 0.0f;
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
 * PAL Address: 0x8009df90
 * PAL Size: 64b
 * EN Address: 0x8009D8C0
 * EN Size: 64b
 * JP Address: 0x8009C07C
 * JP Size: 64b
 */
void CMesMenu::Destroy()
{
    m_mes.Set(0, 0);
    CMenu::Destroy();
}

/*
 * --INFO--
 * PAL Address: 0x8009d69c
 * PAL Size: 2292b
 * EN Address: 0x8009CFE8
 * EN Size: 2264b
 * JP Address: 0x8009B7A4
 * JP Size: 2264b
 */
void CMesMenu::onCalc()
{
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
    if (m_stageFadeOut != desiredStageFlag) {
#ifdef VERSION_GCCP01
        System.Printf("mesMenu\x95\x8e\xa6on/off\x82\xaa\x95\xcf\x8d\x58\x82\xb3\x82\xea\x82\xdc\x82\xb5\x82\xbd\x81\x42%d-%d\n", m_menuIndex, desiredStageFlag);
#endif
        m_stageFadeOut = !m_stageFadeOut;
        m_stageFadeTimer = 0x10 - m_stageFadeTimer;
    }

    unsigned int timer = m_stageFadeTimer - 1;
    m_stageFadeTimer = timer & ~((int)timer >> 0x1F);

    if ((m_menuIndex >= 4) && (m_active == 0)) {
        return;
    }

    if (m_menuIndex < 4) {
        CCaravanWork* scriptFood = Game.m_scriptFoodBase[m_menuIndex];
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
        (void)sin((-1.5707964f) +
                  (3.1415927f * (float)m_stateTimer) / (float)m_stateTimerMax);
        break;
    case 1: {
            m_windowScale = 1.0f;
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
                int altCursor = m_mes.mRubyOffset;
                int cursorMax = m_mes.mRubyLine;
                int cursor = m_mes.mRubyHeight;
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

                m_mes.SetIdxSelect(cursor);
                if ((altCursor >= 0) && (cursor == altCursor)) {
                    cursor = -1;
                }
                m_mes.SetValue(0, cursor);
            } else {
                int wait1 = m_mes.GetWait();
                if (((wait1 == 1) || (m_mes.GetWait() == 5)) && !m_mes.IsFadeOut()) {
                    m_mes.FadeOut();
                }
            }

            if ((downMask & 0x100) != 0) {
                int wait2 = m_mes.GetWait();
                if (wait2 == 0) {
                    m_mes.Skip();
                } else {
                    int wait3 = m_mes.GetWait();
                    if ((wait3 == 3) && ((m_flags & 0x4000) == 0)) {
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                    }
                    int wait4 = m_mes.GetWait();
                    if ((wait4 != 1) && (m_mes.GetWait() != 5) &&
                        !m_mes.IsEnd() && ((m_flags & 0x4000) == 0)) {
                        Sound.PlaySe(0xC, 0x40, 0x7F, 0);
                    }

                    if (m_mes.IsFadeOut()) {
                        goto close;
                    }
                    m_mes.FadeOut();
                }
            }

            if (m_mes.IsFadeOut()) {
                if (m_mes.IsFadeOutCompleted()) {
                close:
                    if (m_mes.IsEnd()) {
                        int wait5 = m_mes.GetWait();
                        if (wait5 != 4) {
                            CloseRequest(0);
                        }
                    } else {
                        m_mes.Next();
                    }
                }
            }
        }
        break;
    case 3: {
        float step = 1.0f - (float)m_stateTimer / (float)m_stateTimerMax;
        float wave = (float)sin(3.1415927f * step + (-1.5707964f));
        m_windowScale = 0.5f * (1.0f + wave);
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
            close(m_closeReason);
            break;
        }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009bedc
 * PAL Size: 6080b
 * EN Address: 0x8009B848
 * EN Size: 6048b
 * JP Address: 0x8009A018
 * JP Size: 6028b
 */
#ifdef VERSION_GCCJGC
#include "src/mesmenu_jp.inc"
#else
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
            unsigned int buttons = Pad.GetButton(0);

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
            32.0f, 32.0f, 0.0f, (float)(iconFrame << 5), 1.0f, 1.0f,
            0.0f);
    }

    int menuIndex = m_menuIndex;
    if ((menuIndex >= 4) && (m_active == 0)) {
        return;
    }
    if ((Game.m_gameWork.m_menuStageMode != 0) && (menuIndex >= 1) && (menuIndex < 4)) {
        return;
    }

    CFont* font = MenuPcs.m_fonts[0];
    font->SetMargin(0.0f);
    font->SetShadow(1);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    float stageBlend = (float)m_stageFadeTimer / 16.0f;
    if (m_stageFadeOut != 0) {
        stageBlend = 1.0f - stageBlend;
    }
    if (0.0f == stageBlend) {
        return;
    }

    float stateBlend;
    int state = m_state;
    if ((state == 0) || ((unsigned int)(state - 1) <= 1) || (state == 3)) {
        if (state == 0) {
            stateBlend = (float)m_stateTimer / (float)m_stateTimerMax;
        } else if (state == 3) {
            stateBlend = 1.0f - (float)m_stateTimer / (float)m_stateTimerMax;
        } else {
            stateBlend = 1.0f;
        }
    } else {
        stateBlend = 0.0f;
    }

    float width;
    float height;
    float drawX;
    float drawY;

    if (m_menuIndex < 4) {
        CCaravanWork* scriptFood = Game.m_scriptFoodBase[m_menuIndex];
        if (scriptFood == 0) {
            return;
        }

        float pulse = 32.0f * (1.0f - sinf(1.5707964f * stageBlend));
        MenuPcs.GetRingMenu(m_menuIndex)->GetDispCounter();
        int maskX = m_menuIndex & 1;
        float pulseX;
        if (maskX != 0) {
            pulseX = pulse;
        } else {
            pulseX = -pulse;
        }
        int maskY = m_menuIndex & 2;
#ifndef VERSION_GCCP01
        float posX = m_baseX;
#else
        float posX = m_baseX + m_offsetX;
#endif
        float baseX = posX + pulseX;
        float pulseY;
        if (maskY != 0) {
            pulseY = pulse;
        } else {
            pulseY = -pulse;
        }
#ifndef VERSION_GCCP01
        float baseY = (m_baseY) + pulseY;
#else
        float baseY = (m_baseY + m_offsetY) + pulseY;
#endif

        if (0.0f < stateBlend) {
            width = m_windowWidth * stateBlend;
            height = m_windowHeight * stateBlend;
            float edgeX;
            if (maskX != 0) {
                edgeX = -m_windowWidth;
            } else {
                edgeX = m_windowWidth - width;
            }
            drawX = baseX + edgeX;

            float edgeY;
            if (maskY != 0) {
#ifndef VERSION_GCCP01
#ifdef VERSION_GCCJGC
                edgeY = ((-60.0f) - m_windowHeight) + (m_windowHeight - height);
#else
                edgeY = ((-40.0f) - m_windowHeight) + (m_windowHeight - height);
#endif
#else
                edgeY = ((-44.0f) - m_windowHeight) + (m_windowHeight - height);
#endif
            } else {
#ifdef VERSION_GCCJGC
                edgeY = 60.0f;
#else
                edgeY = 40.0f;
#endif
            }
            drawY = baseY + edgeY;

            float stateAlpha = 255.0f * stateBlend;
            float alphaF = stateAlpha * stageBlend;
            MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).Ref());
            MenuPcs.DrawWindow(drawX, drawY, width, height, static_cast<CMenuPcs::TEX>(2), 32.0f);

            if ((m_state == 1) && (1.0f == stageBlend)) {
                m_mes.Draw();
                MenuPcs.DrawInit();
            }

            if ((m_itemIndex >= 0) || (m_nameIndex >= 0)) {
                MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x14));
                MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).Ref());

                float cursorWave = sinf(1.5707964f * (1.0f - stateBlend) + 1.5707964f);
                int iconMenuIndex = m_menuIndex;
                int signX = -32;
                if ((iconMenuIndex & 1) != 0) {
                    signX = 32;
                }
                float wobble = (float)signX * (1.0f - cursorWave);
                float iconX = (drawX + wobble) +
                              (((iconMenuIndex & 1) != 0) ? (-10.0f) : (width - 144.0f) - (-10.0f));
                float iconY = drawY + (((iconMenuIndex & 2) != 0) ? (-8.0f) + height : (-48.0f));
                MenuPcs.DrawRect(
                    ((iconMenuIndex & 1) != 0) ? 8 : 0, iconX, iconY, 144.0f, 56.0f,
                    (float)(((iconMenuIndex & 2) != 0) ? 144 : 0), 0.0f, 1.0f, 1.0f,
                    0.0f);

                if (m_nameIndex >= 0) {
                    font->SetScale(0.775f);
                    font->SetShadow(1);
                    font->SetMargin(0.0f);
                    float textWidth = font->GetWidth(Game.m_cFlatDataArr[1].TableStrings(2)[m_nameIndex]);
                    font->DrawInit();
                    font->SetTlut(0xF);
                    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).color);
                    font->SetPosX(iconX + (((m_menuIndex & 1) != 0) ? 62.0f : 82.0f - textWidth));
                    font->SetPosY(iconY + (float)(((m_menuIndex & 2) != 0) ? 8 : 31));
                    font->Draw(Game.m_cFlatDataArr[1].TableStrings(2)[m_nameIndex]);
                    MenuPcs.DrawInit();
                }

                if (m_itemIndex >= 0) {
                    int itemIndex = m_itemIndex;
                    int itemU = (itemIndex % 8) * 0x30;
                    int itemV = (itemIndex / 8) * 0x30;
                    MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).Ref());
                    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(MesMenuFaceTexture));
                    MenuPcs.SetTlut(static_cast<CMenuPcs::TEX>(MesMenuFaceTexture), 0);
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
                        iconX + (float)itemOffsetX, (-1.0f) + iconY, 48.0f, 49.0f,
                        (float)itemU, (float)itemV, 1.0f, 1.0f, 0.0f);
                }
            }
        }

        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(MesMenuBattleTexture));
        float titleAlpha = 255.0f * stageBlend;
        MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(titleAlpha)).Ref());
        unsigned int frameMask = m_menuIndex;
        float frameX = baseX - (float)((frameMask & 1) ? 0x80 : 0);
        float frameY = baseY - (float)((frameMask & 2) ? 0x38 : 0);
        MenuPcs.DrawRect(
            0, frameX, frameY, 128.0f, 56.0f,
            (float)(((frameMask & 2) != 0) ? 0x80 : 0),
            (float)(((frameMask & 1) != 0) ? 0x38 : 0), 1.0f, 1.0f,
            0.0f);

        font->SetScale(0.775f);
        float titleWidth = font->GetWidth(reinterpret_cast<char*>(scriptFood->m_name));
        font->DrawInit();
        font->SetTlut(0xF);
        font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(titleAlpha)).color);
        font->SetPosX(baseX + (((m_menuIndex & 1) != 0) ? (-62.0f) - titleWidth : 62.0f));
        font->SetPosY(27.0f + frameY);
        font->Draw(reinterpret_cast<char*>(scriptFood->m_name));
        MenuPcs.DrawInit();

        DrawHeart(frameX, frameY, 1.0f, stageBlend);

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
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(MesMenuFaceTexture));
        MenuPcs.SetTlut(static_cast<CMenuPcs::TEX>(MesMenuFaceTexture), (scriptFood->m_hp != 0) ? 0 : MenuPcs.GetFaceTlut());
        int foodMaskX = m_menuIndex & 1;
        int foodOffsetX = 5;
        if (foodMaskX != 0) {
            foodOffsetX = 75;
        }
        MenuPcs.DrawRect(
            (foodMaskX != 0) ? 0 : 8, (frameX + shakeX) + (float)foodOffsetX,
            (-1.0f) + (frameY + shakeY), 48.0f, 49.0f,
            (float)foodU, (float)foodV, 1.0f, 1.0f,
            0.0f);
    } else {
        width = m_windowWidth * stateBlend;
        height = m_windowHeight * stateBlend;
#ifndef VERSION_GCCP01
        drawX = (0.5f * m_windowWidth + (m_baseX)) - 0.5f * width;
#else
        drawX = (0.5f * m_windowWidth + (m_baseX + m_offsetX)) - 0.5f * width;
#endif
#ifndef VERSION_GCCP01
        drawY = (0.5f * m_windowHeight + (m_baseY)) - 0.5f * height;
#else
        drawY = (0.5f * m_windowHeight + (m_baseY + m_offsetY)) - 0.5f * height;
#endif

        if ((m_flags & 1) == 0) {
            float stateAlpha = 255.0f * stateBlend;
            float alphaF = stateAlpha * stageBlend;
            MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).Ref());

            MenuPcs.DrawWindow(drawX, drawY, width, height,
                               static_cast<CMenuPcs::TEX>(((m_flags & 0x200) != 0) ? 2 : 0xB), 32.0f);

            if ((m_itemIndex >= 0) || (m_nameIndex >= 0)) {
                unsigned int iconAnchor = (m_flags >> 10) & 7;
                if (iconAnchor != 0) {
                    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x14));
                    MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).Ref());
                    int anchorY;
                    int anchorX = (iconAnchor - 1) & 1;
                    float iconEdgeX;
                    if (anchorX != 0) {
                        iconEdgeX = (-10.0f);
                    } else {
                        iconEdgeX = (width - 144.0f) - (-10.0f);
                    }
                    anchorY = (iconAnchor - 1) & 2;
                    float iconX = 0.0f;
                    iconX = drawX + iconX;
                    iconX += iconEdgeX;
                    float iconEdgeY;
                    if (anchorY != 0) {
                        iconEdgeY = (-8.0f) + height;
                    } else {
                        iconEdgeY = (-48.0f);
                    }
                    float iconY = drawY + iconEdgeY;
                    MenuPcs.DrawRect(
                        (anchorX != 0) ? 8 : 0, iconX, iconY, 144.0f, 56.0f,
                        (float)((anchorY != 0) ? 144 : 0), 0.0f, 1.0f, 1.0f,
                        0.0f);

                    if (m_nameIndex >= 0) {
                        font->SetScale(0.775f);
                        font->SetShadow(1);
                        font->SetMargin(0.0f);
                        float textWidth = font->GetWidth(Game.m_cFlatDataArr[1].TableStrings(2)[m_nameIndex]);
                        font->DrawInit();
                        font->SetTlut(0xF);
                        font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).color);
                        font->SetPosX(iconX + ((anchorX != 0) ? 62.0f : 82.0f - textWidth));
                        font->SetPosY(iconY + (float)((anchorY != 0) ? 8 : 31));
                        font->Draw(Game.m_cFlatDataArr[1].TableStrings(2)[m_nameIndex]);
                        MenuPcs.DrawInit();
                    }

                    if (m_itemIndex >= 0) {
                        int itemIndex = m_itemIndex;
                        int itemU = (itemIndex % 8) * 0x30;
                        int itemV = (itemIndex / 8) * 0x30;
                        MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).Ref());
                        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(MesMenuFaceTexture));
                        MenuPcs.SetTlut(static_cast<CMenuPcs::TEX>(MesMenuFaceTexture), 0);
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
                            iconX + (float)itemOffsetX, (-1.0f) + iconY, 48.0f, 49.0f,
                            (float)itemU, (float)itemV, 1.0f, 1.0f,
                            0.0f);
                    }
                }
            }
        }

        if ((m_state == 1) && ((m_flags & 0x2000) != 0)) {
            float windowScale = stateBlend * stageBlend;
            float pulseScale = 0.25f * (1.0f - windowScale) + 1.0f;
            float timeRaw = fmod(0.05f * (float)m_stateTimer, 2.0);
            float time = (timeRaw > 1.0f) ? (2.0f - timeRaw) : timeRaw;

            float angle = 3.1415927f * time;
            float sinY = sinf(angle);
            float sinX = sinf((-1.5707964f) + angle);
            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(MesMenuGbaTexture));
            float alpha255 = 255.0f * windowScale;
            MenuPcs.SetColor(CColor(0, 0, 0, static_cast<unsigned char>((0.5f * alpha255) * stageBlend)).Ref());
            float fadeScale = 1.0f - pulseScale;
            float rotation = 0.2f * (2.0f * (time - 0.5f));
            float promptX = (float)(int)(40.0f + drawX);
            float promptY = (float)(int)(32.0f + drawY);
            float driftX = 5.0f * (pulseScale * sinX);
            float driftY = 10.0f * (pulseScale * sinY);
            float waveX = promptX + driftX;
            float waveY = promptY - driftY;
            MenuPcs.DrawRect(
                3, 8.0f + waveX, 8.0f + waveY, 80.0f, 48.0f, 0.0f,
                0.0f, 0.75f * (1.0f + fadeScale), 0.75f * (pulseScale + fadeScale),
                rotation);
            MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha255 * stageBlend)).Ref());
            MenuPcs.DrawRect(
                3, waveX, waveY, 80.0f, 48.0f, 0.0f, 0.0f,
                0.75f * pulseScale, 0.75f * pulseScale, rotation);
        }

        if (m_state == 1) {
            m_mes.Draw();
            MenuPcs.DrawInit();
        }
    }

    switch (m_state) {
    case 1:
        if (m_mes.GetWait() == 3) {
            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0));
            MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * stageBlend)).Ref());

            MenuPcs.DrawRect(
                0, (-12.0f) + m_mes.GetPosX(),
                (float)m_mes.GetIdxSelect() * m_mes.GetHSelect() +
                    (2.0f + m_mes.GetPosY() + m_mes.GetYSelect()),
                32.0f, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        }
        break;
    }
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8009bcec
 * PAL Size: 496b
 * EN Address: 0x8009B658
 * EN Size: 496b
 * JP Address: 0x80099E28
 * JP Size: 496b
 */
void CMesMenu::CalcHeart()
{
    CCaravanWork* scriptFood = Game.m_scriptFoodBase[m_menuIndex];
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
 * PAL Address: 0x8009b958
 * PAL Size: 916b
 * EN Address: 0x8009B2C4
 * EN Size: 916b
 * JP Address: 0x80099AF4
 * JP Size: 820b
 */
void CMesMenu::DrawHeart(float x, float y, float z, float alpha)
{
    CCaravanWork* scriptFood = Game.m_scriptFoodBase[m_menuIndex];
    if ((scriptFood != 0) && (0.0f < alpha)) {
        MenuPcs.SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)).Ref());
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(MesMenuHeartTexture));

        float pulseSinScale = 3.1415927f;
        float heartBaseX = x + (float)(((m_menuIndex & 1) != 0) ? 0x30 : 0x4C);
        float heartBaseY = 12.0f + y;
        float heartZero = 0.0f, pulseBase = 0.8f, pulseAmp = 0.2f, pulseOne = 1.0f, pulseTimerScale = 0.0625f;

        for (int heartIndex = 0; heartIndex < (int)((unsigned int)scriptFood->m_maxHp >> 1); heartIndex++) {
            int heartValue = m_heartValue - heartIndex * 0xC;
            float heartPulse = (float)sin(pulseSinScale * (pulseOne - (float)m_heartGrowTimers[heartIndex] * pulseTimerScale));
            heartPulse = pulseAmp * heartPulse + pulseOne;
            heartPulse *= pulseBase;
            int timer = m_heartDropTimers[heartIndex];
            float shakeX = (float)((timer == 0) ? 0 : (timer >> 2) * s_mesMenuShakePattern[(timer + 1) & 3]);
            float shakeY = (float)((timer == 0) ? 0 : (timer >> 2) * s_mesMenuShakePattern[timer & 3]);

            MenuPcs.DrawRect(3, heartBaseX + shakeX, heartBaseY + shakeY, 24.0f, 24.0f, heartZero, heartZero,
                             heartPulse, heartPulse, heartZero);

            if (heartValue > 0) {
                int fillAmount = (heartValue < 0x0B) ? heartValue : 0x0B;
                MenuPcs.DrawRect(3, heartBaseX + shakeX, heartBaseY + shakeY, 24.0f, 24.0f,
                                 (float)((scriptFood->m_statusTimers[2] != 0) ? 0 : 0x18),
                                 (float)((0x0C - fillAmount) * 0x18), heartPulse, heartPulse, 0.0f);
            }

            heartBaseX += ((m_menuIndex & 1) != 0) ? (-20.400002f) : 20.400002f;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009b8e8
 * PAL Size: 112b
 * EN Address: 0x8009B254
 * EN Size: 112b
 * JP Address: 0x80099A84
 * JP Size: 112b
 */
void CMesMenu::onScriptChanging(char*)
{
    int menuIndex;

    m_mes.Set(0, 0);
    m_state = 4;
    m_active = 0;
    menuIndex = m_menuIndex;
    if (menuIndex < 4) {
        MenuPcs.GetRingMenu(menuIndex)->SetFade(1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009b8e4
 * PAL Size: 4b
 * EN Address: 0x8009B250
 * EN Size: 4b
 * JP Address: 0x80099A80
 * JP Size: 4b
 */
void CMesMenu::onScriptChanged(char*, int)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x8009b5fc
 * PAL Size: 744b
 * EN Address: 0x8009AF9C
 * EN Size: 692b
 * JP Address: 0x800997BC
 * JP Size: 708b
 */
void CMesMenu::Open(char* script, int x, int y, int flags, int buttonMask, int itemIndex, int nameIndex)
{
    float zero;
    unsigned int menuIndex;
    bool alignRight;
    float yPos;

    zero = 0.0f;
#ifdef VERSION_GCCP01
    m_offsetY = 0.0f;
    m_offsetX = zero;
#endif
    m_active = 1;
    m_closeReason = 0;
    m_flags = (unsigned int)flags;

    if (m_menuIndex >= 4) {
        m_baseX = (float)x;
        m_baseY = (float)y;
        m_fromScriptPosition = 1;
        float margin = 24.0f;
        m_marginX = margin;
        m_marginY = margin;
        m_mes.SetTlut(((flags & 2) != 0) ? 0x1C : 0, ((flags & 2) != 0) ? 0 : 1);
    } else {
        MenuPcs.GetRingMenu(m_menuIndex)->SetFade(0);
        float marginX = 16.0f;
#ifdef VERSION_GCCJGC
        float marginY = 16.0f;
#else
        float marginY = 8.0f;
#endif
        m_marginX = marginX;
        m_marginY = marginY;
    }

    m_buttonMask = buttonMask;
    m_itemIndex = itemIndex;
    m_nameIndex = nameIndex;
    m_mes.Set(script, flags & 0x20);

    float two = 2.0f;
    m_windowWidth = 2.0f * m_marginX + m_mes.GetWidth();
    m_windowHeight = two * m_marginY + m_mes.GetHeight();

    if (m_menuIndex >= 4) {
        if ((flags & 8) != 0) {
            float half = 0.5f;
            m_baseX = -(0.5f * m_windowWidth - m_baseX);
            m_baseY = -(half * m_windowHeight - m_baseY);
        } else if ((flags & 0x8000) != 0) {
            m_baseX -= m_windowWidth;
        }
    } else if ((flags & 0x100) == 0) {
        float width = m_windowWidth;
        m_windowWidth = (width < 296.0f) ? 296.0f : width;
    }

    menuIndex = (unsigned int)m_menuIndex;
    if ((int)menuIndex < 4) {
        if ((menuIndex & 2) != 0) {
#ifndef VERSION_GCCP01
#ifdef VERSION_GCCJGC
            yPos = ((m_baseY - 60.0f) + m_marginY) - m_windowHeight;
#else
            yPos = ((m_baseY - 40.0f) + m_marginY) - m_windowHeight;
#endif
#else
            yPos = ((m_baseY - 44.0f) + m_offsetY + m_marginY) - m_windowHeight;
#endif
        } else {
#ifndef VERSION_GCCP01
#ifdef VERSION_GCCJGC
            yPos = (m_baseY + m_marginY) + 60.0f;
#else
            yPos = (m_baseY + m_marginY) + 40.0f;
#endif
#else
            yPos = (m_baseY + m_offsetY + m_marginY) + 40.0f;
#endif
        }
    } else {
#ifndef VERSION_GCCP01
        yPos = (m_baseY) + m_marginY;
#else
        yPos = (m_baseY + m_offsetY) + m_marginY;
#endif
    }

    alignRight = false;
    if (((int)menuIndex < 4) && ((menuIndex & 1) != 0)) {
        alignRight = true;
    }
    float xPos;
    if (alignRight) {
#ifndef VERSION_GCCP01
        xPos = ((m_baseX) + m_marginX) - m_windowWidth;
#else
        xPos = ((m_baseX + m_offsetX) + m_marginX) - m_windowWidth;
#endif
    } else {
#ifndef VERSION_GCCP01
        xPos = (m_baseX) + m_marginX;
#else
        xPos = (m_baseX + m_offsetX) + m_marginX;
#endif
    }
    m_mes.SetPosition(xPos, yPos);

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
 * PAL Address: 0x8009b4f0
 * PAL Size: 268b
 * EN Address: 0x8009AE90
 * EN Size: 268b
 * JP Address: 0x800996B0
 * JP Size: 268b
 */
void CMesMenu::CloseRequest(int closeReason)
{
    m_closeReason = closeReason;
    if (m_state <= 1) {
        if ((m_flags & 0x40) != 0) {
            close(m_closeReason);
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
 * PAL Address: 0x8009b4e4
 * PAL Size: 12b
 * EN Address: 0x8009ADC4
 * EN Size: 204b
 * JP Address: UNUSED
 * JP Size: UNUSED
 */
#ifndef VERSION_GCCJGC
void CMesMenu::SetPos(float x, float y)
{
#ifndef VERSION_GCCP01
    m_baseX = x;
    m_baseY = y;
    unsigned int menuIndex = (unsigned int)m_menuIndex;
    float yPos;
    if ((int)menuIndex < 4) {
        if ((menuIndex & 2) != 0) {
            yPos = ((m_baseY - 40.0f) + m_marginY) - m_windowHeight;
        } else {
            yPos = (m_baseY + m_marginY) + 40.0f;
        }
    } else {
        yPos = m_baseY + m_marginY;
    }
    bool alignRight = false;
    if (((int)menuIndex < 4) && ((menuIndex & 1) != 0)) {
        alignRight = true;
    }
    float xPos;
    if (alignRight) {
        xPos = (m_baseX + m_marginX) - m_windowWidth;
    } else {
        xPos = m_baseX + m_marginX;
    }
    m_mes.SetPosition(xPos, yPos);
#else
    m_offsetX = x;
    m_offsetY = y;
#endif
}
#endif
