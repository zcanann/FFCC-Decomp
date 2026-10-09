/*
 * --INFO--
 * PAL Address: 0x8009BEDC
 * PAL Size: 6080b
 * EN Address: 0x8009B848
 * EN Size: 6048b
 * JP Address: 0x8009A018
 * JP Size: 6028b
 */
void CMesMenu::onDraw()
{
    static int tCut[4] = {1, 6, 7, 6};

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
                iconFrame = tCut[(System.m_frameCounter & 6) >> 1];
            } else {
                iconFrame = tCut[0];
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
    font->SetMargin(1.0f);
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
        float posX = m_baseX;
        float baseX = posX + pulseX;
        float pulseY;
        if (maskY != 0) {
            pulseY = pulse;
        } else {
            pulseY = -pulse;
        }
        float baseY = (m_baseY) + pulseY;

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
        font->SetPosX(baseX + (((m_menuIndex & 1) != 0) ? (-70.0f) - titleWidth : 70.0f));
        font->SetPosY(27.0f + frameY);
        font->Draw(reinterpret_cast<char*>(scriptFood->m_name));
        MenuPcs.DrawInit();

        DrawHeart(frameX, frameY, 1.0f, stageBlend);

        if (0.0f < stateBlend) {
            width = m_windowWidth * stateBlend;
            height = m_windowHeight * stateBlend;
            float edgeX;
            if ((m_menuIndex & 1) != 0) {
                edgeX = -m_windowWidth;
            } else {
                edgeX = m_windowWidth - width;
            }
            drawX = baseX + edgeX;

            float edgeY;
            if ((m_menuIndex & 2) != 0) {
                edgeY = ((-60.0f) - m_windowHeight) + (m_windowHeight - height);
            } else {
                edgeY = 60.0f;
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
                    font->SetMargin(1.0f);
                    float textWidth = font->GetWidth(Game.m_cFlatDataArr[1].TableStrings(2)[m_nameIndex]);
                    font->DrawInit();
                    font->SetTlut(0xF);
                    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).color);
                    font->SetPosX(iconX + (((m_menuIndex & 1) != 0) ? 70.0f : 74.0f - textWidth));
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

        int foodTimer = m_foodShakeTimer;
        int foodId = scriptFood->m_id;
        int foodIcon = foodId % 100 + ((foodId - 100) / 100) * 4;
        int foodU = (foodIcon % 8) * 0x30;
        int foodV = (foodIcon / 8) * 0x30;
        int foodShakeX;
        if (foodTimer == 0) {
            foodShakeX = 0;
        } else {
            foodShakeX = (foodTimer >> 2) * tXY[3 - ((foodTimer + 1) & 3)];
        }
        float shakeX = (float)foodShakeX;
        int foodShakeY;
        if (foodTimer == 0) {
            foodShakeY = 0;
        } else {
            foodShakeY = (foodTimer >> 2) * tXY[3 - (foodTimer & 3)];
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
        drawX = (0.5f * m_windowWidth + (m_baseX)) - 0.5f * width;
        drawY = (0.5f * m_windowHeight + (m_baseY)) - 0.5f * height;

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
                    int anchorX = (iconAnchor - 1) & 1;
                    float iconEdgeX;
                    if (anchorX != 0) {
                        iconEdgeX = (-10.0f);
                    } else {
                        iconEdgeX = (width - 144.0f) - (-10.0f);
                    }
                    unsigned int anchorY = (iconAnchor - 1) & 2;
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
                        font->SetMargin(1.0f);
                        float textWidth = font->GetWidth(Game.m_cFlatDataArr[1].TableStrings(2)[m_nameIndex]);
                        font->DrawInit();
                        font->SetTlut(0xF);
                        font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alphaF)).color);
                        font->SetPosX(iconX + ((anchorX != 0) ? 70.0f : 74.0f - textWidth));
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
                    (-2.0f + m_mes.GetPosY() + m_mes.GetYSelect()),
                32.0f, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        }
        break;
    }
}
