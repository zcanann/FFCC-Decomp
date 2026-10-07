/*
 * --INFO--
 * PAL Address: 0x80179F90
 * PAL Size: 52b
 * EN Address: 0x80178E30
 * EN Size: 52b
 * JP Address: 0x80174F08
 * JP Size: 2552b
 */
void CMenuPcs::DrawHelpMessage(int msgNo, CFont* font, int posX, int posY, _GXColor color, int tlut, float scale, float margin)
{
    if (msgNo < 0) {
        return;
    }
    int lineBaseY[3] = {352, 340, 326};
    const CCaravanWork* const caravanWork = Game.m_scriptFoodBase[0];
    char scratch[0x100];
    font->SetMargin(margin);
    font->SetShadow(1);
    font->SetScale(scale);
    font->DrawInit();
    font->SetTlut(tlut);
    font->SetColor(color);

    int rangeKind;
    if (1 <= msgNo && msgNo < 0x45) {
        rangeKind = 1;
    } else if (0x45 <= msgNo && msgNo < 0x7F) {
        rangeKind = 0x45;
    } else if (0x7F <= msgNo && msgNo < 0x9F) {
        rangeKind = 0x7F;
    } else {
        rangeKind = 0;
    }
    int firstLine = 500;
    int lineMax;
    if (0 <= msgNo && msgNo <= 0x9E) {
        firstLine = msgNo * 3 + 0x1F5;
        lineMax = 3;
    } else if (0x9F <= msgNo && msgNo <= 0xFF) {
        firstLine = msgNo + 0x333;
        lineMax = 1;
    } else if (0x100 <= msgNo && msgNo <= 0x206) {
        firstLine = (msgNo - 0x100) * 2 + 0x433;
        lineMax = 2;
    } else if (0x207 <= msgNo && msgNo <= 0x258) {
        firstLine = (msgNo - 0x207) * 3 + 0x641;
        lineMax = 3;
    } else if (0x259 <= msgNo && msgNo <= 0x268) {
        firstLine = (msgNo - 0x259) * 3 + 0x737;
        lineMax = 3;
    }
    int maxWidth = -1;
    for (int line = firstLine; line < firstLine + lineMax; line++) {
        int width = CMes::drawTagString(font, Game.GetHelpName(line), 0, 0, 0);
        if (width < maxWidth) {
            width = maxWidth;
        }
        maxWidth = width;
    }
    if (rangeKind != 0) {
        int y = lineBaseY[0];
        for (int i = 1; i <= 2; i++) {
            char* msg = Game.GetHelpName(firstLine + i);
            font->SetPosX(static_cast<float>(320 - maxWidth / 2));
            font->SetPosY(static_cast<float>(y));
            CMes::drawTagString(font, msg, 1, 0, 0);
            y = static_cast<int>(static_cast<float>(y) + 25.0f);
        }
        const SItemFlatRow* item = reinterpret_cast<const SItemFlatRow*>(Game.unkCFlatData0[2]) + msgNo;
        u16 flags = item->m_equipFlags;
        if (flags & 0x100) {
            strcpy(scratch, "\x8D\x55\x8C\x82\x97\xCD");
        } else if (flags & 0x200) {
            strcpy(scratch, "\x96\x68\x8C\xE4\x97\xCD");
        } else if (flags & 0x400) {
            strcpy(scratch, "\x96\x68\x8C\xE4\x97\xCD");
        } else if (flags & 0x800) {
            strcpy(scratch, "\x96\x68\x8C\xE4\x97\xCD");
        } else if (flags & 0x1000) {
            strcpy(scratch, "");
        } else if (flags & 0x2000) {
            strcpy(scratch, "");
        }
        int x = 56;
        font->SetPosX(56.0f);
        font->SetPosY(326.0f);
        if (item->m_equipFlags & 0x1000) {
            if (item->m_attribute < 1 || item->m_attribute > 0x13) {
                return;
            }

            strcpy(scratch, GetAttrStr(item->m_attribute));
            font->SetTlut(4);
            font->Draw(scratch);
            x += 10.0f + font->GetWidth(scratch);
            font->SetPosX(static_cast<float>(x));
            font->SetTlut(9);
            unsigned int attr = item->m_attribute;
            if (attr >= 1 && attr <= 8) {
                sprintf(scratch, "%s", "+1");
            } else if (attr == 0xB || attr == 0x11 || attr == 0x12) {
                sprintf(scratch, "%c%d", '+', item->m_value);
            } else if (static_cast<unsigned short>(attr - 9) <= 1 || attr == 0xC) {
                sprintf(scratch, "%c%d", '-', item->m_value);
                font->SetTlut(3);
            } else {
                return;
            }
            font->Draw(scratch);
        } else {
            font->Draw(scratch);
            x += 10.0f + font->GetWidth(scratch);
            font->SetTlut(1);
            font->SetPosX(static_cast<float>(x));
            sprintf(scratch, "%d", item->m_value);
            font->Draw(scratch);
            if (m_battleStateFlag == 2) {
                int sel = m_artiState->currentSelection;
                if (sel == 1) {
                    u16 effectFlags = item->m_equipFlags;
                    if ((effectFlags & 0x1000) == 0) {
                        int currentItem = -1;
                        if (effectFlags & 0x100) {
                            currentItem = 0;
                        } else if (effectFlags & 0x400) {
                            currentItem = 1;
                        } else if (effectFlags & 0x800) {
                            currentItem = 2;
                        } else if (effectFlags & 0x200) {
                            currentItem = 2;
                        } else if (effectFlags & 0x1000) {
                            currentItem = 3;
                        } else if (effectFlags & 0x2000) {
                            currentItem = 3;
                        }
                        int equipmentSlot = caravanWork->m_equipment[currentItem];
                        currentItem = caravanWork->m_inventoryItems[equipmentSlot];
                        if (ChkEquipActive(static_cast<int>(m_artiState->selections[sel]) +
                                           static_cast<int>(m_artiState->scrollOffset))) {
                            const SItemFlatRow* current = reinterpret_cast<const SItemFlatRow*>(Game.unkCFlatData0[2]) + currentItem;
                            unsigned int currentValue;
                            if (currentItem == -1) {
                                currentValue = 0;
                            } else {
                                currentValue = current->m_value;
                            }
                            int delta = static_cast<int>(item->m_value) - static_cast<int>(currentValue);
                            x += 10.0f + font->GetWidth(scratch);
                            font->SetPosX(static_cast<float>(x));
                            if (delta >= 0) {
                                font->SetTlut(9);
                                sprintf(scratch, "%c%d", '+', delta);
                            } else {
                                font->SetTlut(3);
                                sprintf(scratch, "%d", delta);
                            }
                            font->Draw(scratch);
                        }
                    }
                }
            }
            if ((item->m_equipFlags & 0x1000) == 0) {
                if (item->m_attribute >= 1 && item->m_attribute <= 0x13) {
                    x += 10.0f + font->GetWidth(scratch);
                    font->SetPosX(static_cast<float>(x));
                    font->SetTlut(4);
                    strcpy(scratch, GetAttrStr(item->m_attribute));
                    font->Draw(scratch);
                    x += 10.0f + font->GetWidth(scratch);
                    font->SetPosX(static_cast<float>(x));
                    font->SetTlut(9);
                    unsigned int attr = item->m_attribute;
                    if (attr >= 1 && attr <= 8) {
                        sprintf(scratch, "%s", "+1");
                    } else {
                        return;
                    }
                    font->Draw(scratch);
                }
            }
        }
    } else {
        int lineCount = lineMax;
        int widthMax = -1;
        for (int line = firstLine; line < firstLine + lineMax; line++) {
            int width = CMes::drawTagString(font, Game.GetHelpName(line), 0, 0, 0);
            if (width < widthMax) {
                width = widthMax;
            }
            widthMax = width;
        }
        int x = 320 - widthMax / 2;
        for (int i = 0; i < lineMax; i++) {
            if (strlen(Game.GetHelpName(firstLine + i)) <= 2) {
                lineCount--;
            }
        }
        int y = lineBaseY[lineCount - 1];
        for (int i = 0; i < lineCount; i++) {
            char* msg = Game.GetHelpName(firstLine + i);
            font->SetPosX(static_cast<float>(x));
            font->SetPosY(static_cast<float>(y));
            CMes::drawTagString(font, msg, 1, 0, 0);
            y = static_cast<int>(static_cast<float>(y) + 25.0f);
        }
    }
}
