#include "ffcc/menu_item.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

enum {
#ifdef VERSION_GCCJGC
    ITEM_TEX_FRAME = 0x2D,
    ITEM_TEX_TAB = 0x46,
    ITEM_TEX_LIST = 0x36,
#else
    ITEM_TEX_FRAME = 0x2E,
    ITEM_TEX_TAB = 0x47,
    ITEM_TEX_LIST = 0x37,
#endif
};

typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

struct MenuItemOpenAnim {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    float u;
    float v;
    float alpha;
    float uvScale;
    int unk18;
    int tex;
    int frame;
    int startFrame;
    int duration;
    unsigned int flags;
    float dx;
    float dy;
    float targetX;
    float targetY;
};

struct ItemMenuAnimList {
    s16 count;
    char pad_02[6];
    MenuItemOpenAnim anims[64];
};

STATIC_ASSERT(offsetof(CMenuPcs, m_fonts) == 0xF8);
STATIC_ASSERT(offsetof(CMenuPcs, m_itemMenuState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_menuWindowInfo) == 0x848);
STATIC_ASSERT(offsetof(CMenuPcs, m_itemList) == 0x850);
STATIC_ASSERT(offsetof(ItemMenuState, optionFlags) == 0x9);
STATIC_ASSERT(offsetof(ItemMenuState, initialized) == 0xB);
STATIC_ASSERT(offsetof(ItemMenuState, closeRequested) == 0xD);
STATIC_ASSERT(offsetof(ItemMenuState, listState) == 0x10);
STATIC_ASSERT(offsetof(ItemMenuState, optionFrame) == 0x12);
STATIC_ASSERT(offsetof(ItemMenuState, optionIndex) == 0x14);
STATIC_ASSERT(offsetof(ItemMenuState, cursorMove) == 0x1E);
STATIC_ASSERT(offsetof(ItemMenuState, frame) == 0x22);
STATIC_ASSERT(offsetof(ItemMenuState, cursorIndex) == 0x26);
STATIC_ASSERT(offsetof(ItemMenuState, mode) == 0x30);
STATIC_ASSERT(offsetof(ItemMenuState, prevMode) == 0x32);
STATIC_ASSERT(offsetof(ItemMenuState, scroll) == 0x34);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, u) == 0x8);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, v) == 0xC);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, alpha) == 0x10);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, uvScale) == 0x14);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, unk18) == 0x18);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, tex) == 0x1C);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, frame) == 0x20);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, startFrame) == 0x24);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, duration) == 0x28);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, flags) == 0x2C);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, dx) == 0x30);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, dy) == 0x34);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, targetX) == 0x38);
STATIC_ASSERT(offsetof(MenuItemOpenAnim, targetY) == 0x3C);
STATIC_ASSERT(sizeof(MenuItemOpenAnim) == 0x40);
STATIC_ASSERT(sizeof(ItemMenuAnimList) == 0x1008);

/*
 * --INFO--
 * PAL Address: 0x80159654
 * PAL Size: 1952b
 * EN Address: 0x801586D0
 * EN Size: 1952b
 * JP Address: 0x80153EA0
 * JP Size: 1952b
 */
int CMenuPcs::ItemCtrlCur()
{
    CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
    s16 hold;
    s16 press;

    press = Pad.GetButtonDown(0);
    hold = Pad.GetButtonRepeat(0);

    if (hold == 0) {
        return 0;
    }

    s16 letterAttachFlg;
    int mode = this->m_itemMenuState->mode;
    letterAttachFlg = SingGetLetterAttachflg();

    if (mode == 0) {
        if ((hold & 8) != 0) {
            int cursor = this->m_itemMenuState->cursorIndex[mode];
            if (cursor != 0) {
                this->m_itemMenuState->cursorIndex[mode] = cursor - 1;
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            } else {
                s16 scroll = this->m_itemMenuState->scroll;
                // The retail binary contains this redundant duplicate branch.
                if (scroll != 0) {
                    this->m_itemMenuState->scroll = scroll - 1;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                } else if (scroll != 0) {
                    this->m_itemMenuState->scroll = scroll - 1;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                } else {
                    this->m_itemMenuState->scroll = 0x3F;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }
            }
        } else if ((hold & 4) != 0) {
            int cursor = this->m_itemMenuState->cursorIndex[mode];
            if (cursor < 7) {
                this->m_itemMenuState->cursorIndex[mode] = cursor + 1;
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            } else {
                s16 scroll = this->m_itemMenuState->scroll;
                // The retail binary contains this redundant duplicate branch.
                if (scroll < 0x3F) {
                    this->m_itemMenuState->scroll = scroll + 1;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                } else if (scroll < 0x3F) {
                    this->m_itemMenuState->scroll = scroll + 1;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                } else {
                    this->m_itemMenuState->scroll = 0;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }
            }
        }

        if ((hold & 0xC) == 0) {
            if ((press & 0x20) != 0) {
                if (letterAttachFlg < 0) {
                    this->m_itemMenuState->cursorMove = 1;
                    Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
                    return 1;
                }
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else if ((press & 0x40) != 0) {
                if (letterAttachFlg < 0) {
                    this->m_itemMenuState->cursorMove = -1;
                    Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
                    return 1;
                }
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else if ((press & 0x100) != 0) {
                int idx = this->m_itemMenuState->scroll + this->m_itemMenuState->cursorIndex[mode];
                if (idx >= 0x40) {
                    idx -= 0x40;
                }

                if ((caravanWork->m_inventoryItems[idx] <= 0) || EquipChk(idx) ||
                    ((letterAttachFlg >= 0) && (caravanWork->m_inventoryItems[idx] < 0x125))) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                } else if (letterAttachFlg >= 0) {
                    LetterSetAttachItem((unsigned int)idx, 1);
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                    return 1;
                } else {
                    this->m_itemMenuState->optionFlags = 0xC;
                    int itemType = GetItemType(idx, 0);

                    if ((itemType == 7) && (caravanWork->CanPlayerUseItem() != 0)) {
                        this->m_itemMenuState->optionFlags = this->m_itemMenuState->optionFlags | 1;
                    }
                    if ((itemType != 1) && (caravanWork->CanPlayerPutItem() != 0)) {
                        this->m_itemMenuState->optionFlags = this->m_itemMenuState->optionFlags | 2;
                    }

                    s16 winW;
                    s16 winH;
                    GetSingWinSize(0, &winW, &winH, 0);
                    SetSingWinInfo(0xF0, 0xA0, winW, winH);

                    this->m_menuWindowInfo->state = 0;
                    this->m_itemMenuState->optionFrame = 0;
                    this->m_itemMenuState->mode = 1;
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                }
            } else if ((press & 0x200) != 0) {
                if (letterAttachFlg >= 0) {
                    LetterSetAttachItem(0, 0xFFFFFFFF);
                    Sound.PlaySe(3, 0x40, 0x7F, 0);
                    return 1;
                }
                this->m_itemMenuState->closeRequested = 1;
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                return 1;
            }
        }
    } else {
        if ((hold & 8) != 0) {
            if (this->m_itemMenuState->cursorIndex[mode] != 0) {
                this->m_itemMenuState->cursorIndex[mode]--;
            } else {
                this->m_itemMenuState->cursorIndex[mode] = 3;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((hold & 4) != 0) {
            if (this->m_itemMenuState->cursorIndex[mode] < 3) {
                this->m_itemMenuState->cursorIndex[mode]++;
            } else {
                this->m_itemMenuState->cursorIndex[mode] = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((hold & 0xC) == 0) {
            if ((press & 0x100) != 0) {
                int option = (int)this->m_itemMenuState->cursorIndex[mode];
                if (((int)this->m_itemMenuState->optionFlags & (1 << option)) == 0) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                } else {
                    int idx = this->m_itemMenuState->scroll + this->m_itemMenuState->cursorIndex[0];
                    if (idx >= 0x40) {
                        idx -= 0x40;
                    }

                    if (option == 0) {
                        caravanWork->FGUseItem(idx, 0);
                        SingLifeInit(0);
                        caravanWork->CalcStatus();
                    } else if (option == 1) {
                        caravanWork->FGPutItem(idx, 0);
                    } else if (option == 2) {
                        caravanWork->DeleteItemIdx(idx, 0);
                    }

                    this->m_menuWindowInfo->state = 2;
                    this->m_itemMenuState->optionFrame = this->m_itemMenuState->optionFrame + 1;
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                }
            } else if ((press & 0x200) != 0) {
                this->m_menuWindowInfo->state = 2;
                this->m_itemMenuState->optionFrame = this->m_itemMenuState->optionFrame + 1;
                Sound.PlaySe(3, 0x40, 0x7F, 0);
            }
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80159df4
 * PAL Size: 2596b
 * EN Address: 0x80158E70
 * EN Size: 2596b
 * JP Address: 0x80154640
 * JP Size: 2588b
 */
void CMenuPcs::ItemDraw()
{
    s16 listState;
    int selectedItemId;
    float x;
    int mode;
    MenuItemOpenAnim* entry;
    CCaravanWork* caravanWork;
    float itemAlpha;
    s16 itemId;
    CFont* helpFont;
    int drawIndex;
    int tex;
    CFont* listFont;
    float y;
    int menuIndex;
    float w;
    float h;
    int hasLetterAttach;
    int texId;
    int i;
    int foundSelected;
    GXColor colors[4];
    float u;
    float v;

    foundSelected = 0;
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    caravanWork = Game.m_scriptFoodBase[0];
    listState = m_itemMenuState->listState;
    mode = m_itemMenuState->mode;
    entry = m_itemList->anims;
    drawIndex = 0;
    hasLetterAttach = (SingGetLetterAttachflg() >= 0) ? 1 : 0;

    for (i = 0; i < m_itemList->count; i++, entry++) {
        tex = entry->tex;
        if (tex < 0) {
            continue;
        }

        x = (float)entry->x;
        y = (float)entry->y;
        w = (float)entry->w;
        h = (float)entry->h;
        u = entry->u;
        v = entry->v;

        if (i == 0) {
            MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(entry->tex));

            colors[0].r = 0xFF;
            colors[0].g = 0xFF;
            colors[0].b = 0xFF;
            colors[0].a = 0xFF;
            colors[1].r = 0xFF;
            colors[1].g = 0xFF;
            colors[1].b = 0xFF;
            colors[1].a = 0xFF;
            colors[2].r = 0xFF;
            colors[2].g = 0xFF;
            colors[2].b = 0xFF;
            colors[2].a = 0xFF;
            colors[3].r = 0xFF;
            colors[3].g = 0xFF;
            colors[3].b = 0xFF;
            colors[3].a = 0xFF;
            GXSetChanMatColor(GX_COLOR0A0, colors[0]);

            w = entry->alpha * w;
            if (w > 0.0f) {
                MenuPcs.DrawRect(0, x, y, w, h, u, v, colors, 1.0f, 1.0f, 0.0f);
                x += w;
                u += w;
            }

            if (w > 0.0f && w < entry->w) {
                colors[1].r = 0xFF;
                colors[1].g = 0xFF;
                colors[1].b = 0xFF;
                colors[1].a = 0;
                colors[3].r = 0xFF;
                colors[3].g = 0xFF;
                colors[3].b = 0xFF;
                colors[3].a = 0;
                w = (float)(1.0 / (double)entry->duration);
                w = w * entry->w;
                MenuPcs.DrawRect(0, x, y, w, h, u, v, colors, 1.0f, 1.0f, 0.0f);
            }

            MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
        } else {
            texId = tex;
            itemAlpha = entry->alpha;
            if (tex == ITEM_TEX_LIST) {
                menuIndex = drawIndex + m_itemMenuState->scroll;
                if (menuIndex >= 0x40) {
                    menuIndex -= 0x40;
                }

                if ((caravanWork->m_inventoryItems[menuIndex] <= 0) || EquipChk(menuIndex) ||
                    (hasLetterAttach && (caravanWork->m_inventoryItems[menuIndex] < 0x125))) {
                    if (EquipChk(menuIndex)) {
                        DrawEquipMark((int)(x - 12.0f), (int)((h - 24.0f) / 2.0 + y),
                                      entry->alpha);
                    }
                    texId = 0x34;
                    itemAlpha = (float)((double)entry->alpha * 0.5);
                }

                if (texId == ITEM_TEX_LIST && drawIndex == m_itemMenuState->cursorIndex[0]) {
                    v += h;
                }
                drawIndex++;
            }

            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(texId));
            colors[0].r = 0xFF;
            colors[0].g = 0xFF;
            colors[0].b = 0xFF;
            colors[0].a = (u8)(255.0f * itemAlpha);
            GXSetChanMatColor(GX_COLOR0A0, colors[0]);
            MenuPcs.DrawRect(0, x, y, w, h, u, v, entry->uvScale, entry->uvScale, 0.0f);
        }
    }

    listFont = GetFontItem();
    listFont->SetMargin(1.0f);
    listFont->SetShadow(0);
    listFont->SetScale(0.9f);
    listFont->DrawInit();

    for (i = 0; i < m_itemList->count; i++) {
        entry = &m_itemList->anims[i];
        if (entry->tex == ITEM_TEX_LIST) {
            break;
        }
    }

    for (i = 0; i < 8; i++) {
        menuIndex = i + m_itemMenuState->scroll;
        if (menuIndex >= 0x40) {
            menuIndex -= 0x40;
        }

        listFont->SetColor(CColor(0xFF, 0xFF, 0xFF, (u8)(255.0f * entry->alpha)).color);

        itemId = caravanWork->m_inventoryItems[menuIndex];
        if (itemId > 0) {
            char* text = Game.GetShortItemName(itemId);
            int selectedIndex = m_itemMenuState->cursorIndex[0] + m_itemMenuState->scroll;
            if (selectedIndex >= 0x40) {
                selectedIndex -= 0x40;
            }
            if (menuIndex == selectedIndex) {
                selectedItemId = itemId;
                foundSelected = 1;
            }

            listFont->GetWidth(text);
            x = (float)(entry[i].x + 0x1C);
            y = (float)(entry[i].y + 0xB);
            listFont->SetPosX(x);
            listFont->SetPosY(y - 4.0f);
            listFont->Draw(text);
        }
    }

    DrawInit();

    for (i = 0; i < 8; i++) {
        menuIndex = i + m_itemMenuState->scroll;
        if (menuIndex >= 0x40) {
            menuIndex -= 0x40;
        }

        itemId = caravanWork->m_inventoryItems[menuIndex];
        if (itemId > 0) {
            int iconY = (int)((float)(entry[i].y + 6) - 1.0f);
            int iconX = (int)((float)(entry[i].x + entry[i].w - 0x10));
            DrawSingleIcon(itemId, iconX, iconY, entry->alpha, 0, 1.0f);
        }
    }

    if (listState == 1) {
        entry = m_itemList->anims;
        float mark = CalcListPos(m_itemMenuState->scroll, 0x40, 1);
        if (mark > 0.0f) {
            DrawListPosMark((float)entry->x, (float)entry->y, mark);
        }
    }

    if (mode == 1) {
        DrawSingWin(-1);
        if (m_itemMenuState->optionFrame == 1) {
            DrawSingWinMess(0, m_itemMenuState->optionFlags, 0);
        }
    }

    if ((mode == 0 && listState == 1) || (mode != 0 && m_itemMenuState->optionFrame == 1)) {
        if (mode == 0) {
            for (i = 0; i < m_itemList->count; i++) {
                entry = &m_itemList->anims[i];
                if (m_itemList->anims[i].tex == ITEM_TEX_LIST) {
                    break;
                }
            }

            entry += m_itemMenuState->cursorIndex[0];
            x = (float)(entry->x - 0x14);
            y = (float)((entry->h - 0x20) / 2.0 + entry->y);
        } else {
            x = (float)m_menuWindowInfo->x;
            y = (float)(m_menuWindowInfo->y + 0x20);
            y += (float)(m_itemMenuState->cursorIndex[1] * SingWinMessHeight());
        }

        x += (float)((int)System.m_frameCounter % 8);
        DrawCursor((int)x, (int)y, 1.0f);
    }

    DrawInit();
    DrawSingLife();

    helpFont = GetFont22();
    s8 helpAlpha = (s8)(255.0f * entry->alpha);
    if (!foundSelected) {
        selectedItemId = -1;
    }
    float helpY = 352.0f;
    DrawHelpMessage(selectedItemId, helpFont, (int)(320.0f - w / 2), (int)helpY,
                    CColor(0xFF, 0xFF, 0xFF, helpAlpha).color, 10, 1.0f, 3.0f);
}

/*
 * --INFO--
 * PAL Address: 0x8015a818
 * PAL Size: 380b
 * EN Address: 0x80159894
 * EN Size: 380b
 * JP Address: 0x8015505C
 * JP Size: 396b
 */
int CMenuPcs::ItemClose()
{
    this->m_itemMenuState->frame++;

    ItemMenuAnimList* itemList = this->m_itemList;
    MenuItemOpenAnim* anim = itemList->anims;
    int finished = 0;
    int count = itemList->count;
    int frame = this->m_itemMenuState->frame;

    for (int i = 0; i < count; i++, anim++) {
        if (frame < anim->startFrame) {
            continue;
        }

        if (anim->startFrame + anim->duration <= frame) {
            finished++;
            anim->alpha = 0.0f;
            anim->dx = 0.0f;
            anim->dy = 0.0f;
        } else {
            anim->frame++;
            anim->alpha = 1.0 - (1.0 / anim->duration) * anim->frame;
            if ((anim->flags & 2) == 0) {
                float ratio = 1.0 - (1.0 / anim->duration) * anim->frame;
                float dx = anim->targetX - (float)anim->x;
                float dy = anim->targetY - (float)anim->y;
                anim->dx = dx * ratio;
                anim->dy = dy * ratio;
            }
        }
    }

    int closed = 0;
    if (count == finished) {
        closed = 1;
    }
    return closed;
}

/*
 * --INFO--
 * PAL Address: 0x8015a994
 * PAL Size: 260b
 * EN Address: 0x80159A10
 * EN Size: 260b
 * JP Address: 0x801551E8
 * JP Size: 260b
 */
int CMenuPcs::ItemCtrl()
{
    int changed = 0;

    this->m_itemMenuState->prevMode = this->m_itemMenuState->mode;

    int mode = this->m_itemMenuState->mode;
    if ((mode == 0) ||
        ((mode != 0) && (this->m_itemMenuState->optionFrame == 1))) {
        changed = ItemCtrlCur();
    } else if ((mode == 1) && (this->m_itemMenuState->optionFrame == 0)) {
        if (this->m_menuWindowInfo->state == 1) {
            changed = 0;
            this->m_itemMenuState->optionFrame++;
        }
    } else if (((mode == 1) && (this->m_itemMenuState->optionFrame == 2)) &&
               (this->m_menuWindowInfo->state == 3)) {
        changed = 0;
        this->m_itemMenuState->optionFrame = 0;
        this->m_itemMenuState->mode = 0;
        this->m_itemMenuState->frame = 0;
    }

    if (changed != 0) {
        SingLifeInit(-1);
        ItemInit1();
    }

    return changed;
}

/*
 * --INFO--
 * PAL Address: 0x8015aa98
 * PAL Size: 444b
 * EN Address: 0x80159B14
 * EN Size: 444b
 * JP Address: 0x801552EC
 * JP Size: 456b
 */
int CMenuPcs::ItemOpen()
{
    if (this->m_itemMenuState->initialized == '\0') {
        SingLifeInit(-1);
        ItemInit();
    }

    this->m_itemMenuState->frame++;
    ItemMenuAnimList* itemList = this->m_itemList;
    MenuItemOpenAnim* anim = itemList->anims;
    int finished = 0;
    int count = itemList->count;
    int frame = this->m_itemMenuState->frame;

    for (int i = 0; i < count; i++, anim++) {
        if (frame >= anim->startFrame) {
            if (anim->startFrame + anim->duration <= frame) {
                finished++;
                anim->alpha = 1.0f;
                anim->dx = 0.0f;
                anim->dy = 0.0f;
            } else {
                anim->frame++;
                anim->alpha = (1.0 / anim->duration) * anim->frame;
                if ((anim->flags & 2) == 0) {
                    float ratio = (1.0 / anim->duration) * anim->frame;
                    float dx = anim->targetX - (float)anim->x;
                    float dy = anim->targetY - (float)anim->y;
                    anim->dx = dx * ratio;
                    anim->dy = dy * ratio;
                }
            }
        }
    }

    int opened = 0;
    if (count == finished) {
        opened = 1;
    }
    return opened;
}

/*
 * --INFO--
 * PAL Address: 0x8015ac54
 * PAL Size: 604b
 * EN Address: 0x80159CD0
 * EN Size: 604b
 * JP Address: 0x801554B4
 * JP Size: 636b
 */
void CMenuPcs::ItemInit1()
{
    float progress;
    int index;
    MenuItemOpenAnim* entry;

    index = 0;
    entry = &this->m_itemList->anims[index++];
    entry->tex = ITEM_TEX_FRAME;
    entry->startFrame = 2;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->tex = ITEM_TEX_TAB;
    entry->startFrame = 7;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->tex = ITEM_TEX_TAB;
    entry->startFrame = 7;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = ITEM_TEX_FRAME;
    entry->startFrame = 7;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = ITEM_TEX_LIST;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = ITEM_TEX_LIST;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = ITEM_TEX_LIST;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = ITEM_TEX_LIST;
    progress = 1.0f;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = ITEM_TEX_LIST;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = ITEM_TEX_LIST;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = ITEM_TEX_LIST;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index];
    entry->flags = 2;
    entry->tex = ITEM_TEX_LIST;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = this->m_itemList->anims;
    for (index = this->m_itemList->count; index > 0; index--) {
        entry->frame = 0;
        entry->alpha = progress;
        entry++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8015aeb0
 * PAL Size: 680b
 * EN Address: 0x80159F2C
 * EN Size: 680b
 * JP Address: 0x80155730
 * JP Size: 748b
 */
void CMenuPcs::ItemInit()
{
    MenuItemOpenAnim* entry;

    memset(m_itemList, 0, sizeof(*m_itemList));
    {
        entry = m_itemList->anims;
        for (int initCount = 0; initCount < 64; initCount++, entry++) {
            entry->uvScale = 1.0f;
        }
    }

    int index = 0;
    entry = &m_itemList->anims[index++];
    entry->tex = ITEM_TEX_FRAME;
    entry->x = 0x68;
    entry->y = 0x28;
    entry->w = 0x78;
    entry->h = 0x108;
    entry->u = 128.0f;
    entry->v = 8.0f;
    entry->uvScale = 1.0f;
    entry->startFrame = 5;
    entry->duration = 5;

    entry = &m_itemList->anims[index++];
    entry->tex = ITEM_TEX_TAB;
    entry->x = 0x50;
    entry->y = 0xE;
    entry->w = 0x30;
    entry->h = 0x30;
    entry->u = 0.0f;
    entry->v = 0.0f;
    entry->uvScale = 1.0f;
    entry->startFrame = 0;
    entry->duration = 5;

    entry = &m_itemList->anims[index++];
    entry->tex = ITEM_TEX_TAB;
    entry->x = 0x55;
    entry->w = 0x30;
    entry->h = 0x30;
    entry->y = 0x150 - entry->h;
    entry->u = 0.0f;
    entry->v = 0.0f;
    entry->uvScale = 0.75f;
    entry->startFrame = 0;
    entry->duration = 5;

    entry = &m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = ITEM_TEX_FRAME;
    entry->x = 0x50;
    entry->y = 8;
    entry->w = 0x48;
    entry->h = 0x140;
    entry->u = 0.0f;
    entry->v = 0.0f;
    entry->startFrame = 0;
    entry->duration = 5;

    MenuItemOpenAnim* firstEntry = m_itemList->anims;
    for (int loopCount = 0; loopCount < 8; loopCount++) {
        entry = &m_itemList->anims[index++];
        entry->flags = 2;
        entry->tex = ITEM_TEX_LIST;
        entry->x = firstEntry->x + 0x24;
        entry->y = firstEntry->y + loopCount * 0x20;
        entry->w = 200;
        entry->h = 0x28;
        entry->u = 0.0f;
        entry->v = 0.0f;
        entry->startFrame = 7;
        entry->duration = 5;
    }

    m_itemList->count = index;
    m_itemMenuState->cursorIndex[0] = 0;
    m_itemMenuState->initialized = 1;
}
