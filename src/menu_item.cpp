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

typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

static const float kItemZero = 0.0f;
static const float kItemOne = 1.0f;
static const double kItemOneDouble = 1.0;
static const float kItemMarkXOffset = 12.0f;
static const float kItemMarkHeight = 24.0f;
static const double kItemHalfDouble = 0.5;
static const float kItemColorMax = 255.0f;
static const float kItemListFontScale = 0.9f;
static const float kItemTextYOffset = 4.0f;
static const float kItemHelpCenterX = 320.0f;
static const float kItemHelpY = 352.0f;
static const float kItemHelpScale = 3.0f;
static const float kItemHalf = 0.5f;
static const float kItemInitU = 128.0f;
static const float kItemInitV = 8.0f;
static const float kItemSmallScale = 0.75f;

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
 * EN Address: 0x8017C77C
 * EN Size: 2144b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ItemCtrlCur()
{
    CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
    s16 press = Pad.GetButtonDown(0);
    s16 hold = Pad.GetButtonRepeat(0);

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
            int cursor = this->m_itemMenuState->cursorIndex[mode];
            if (cursor != 0) {
                this->m_itemMenuState->cursorIndex[mode] = cursor - 1;
            } else {
                this->m_itemMenuState->cursorIndex[mode] = 3;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((hold & 4) != 0) {
            int cursor = this->m_itemMenuState->cursorIndex[mode];
            if (cursor < 3) {
                this->m_itemMenuState->cursorIndex[mode] = cursor + 1;
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
 * EN Address: 0x8017BB1C
 * EN Size: 3168b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ItemDraw()
{
    int foundSelected = 0;
    int selectedItemId;
    float x;
    float y;
    float w;
    float h;
    float u;
    float v;
    GXColor colors[4];

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
    s16 listState = this->m_itemMenuState->listState;
    int mode = this->m_itemMenuState->mode;
    MenuItemOpenAnim* entry = this->m_itemList->anims;
    int drawIndex = 0;
    int hasLetterAttach = (SingGetLetterAttachflg() >= 0) ? 1 : 0;

    for (int i = 0; i < this->m_itemList->count; i++, entry++) {
        int texCheck = entry->tex;
        if (texCheck < 0) {
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
            if (w > kItemZero) {
                MenuPcs.DrawRect(
                    0, x, y, w, h, u, v, colors, kItemOne, kItemOne, kItemZero);
                x += w;
                u += w;
            }

            if (w > kItemZero && w < entry->w) {
                colors[1].r = 0xFF;
                colors[1].g = 0xFF;
                colors[1].b = 0xFF;
                colors[1].a = 0;
                colors[3].r = 0xFF;
                colors[3].g = 0xFF;
                colors[3].b = 0xFF;
                colors[3].a = 0;

                float widthFrac = (float)(kItemOneDouble / (double)entry->duration);
                w = widthFrac * (float)entry->w;
                MenuPcs.DrawRect(
                    0, x, y, w, h, u, v, colors, kItemOne, kItemOne, kItemZero);
            }

            MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
        } else {
            int tex = texCheck;
            float itemAlpha = entry->alpha;
            if (tex == 0x37) {
                int menuIndex = drawIndex + this->m_itemMenuState->scroll;
                if (menuIndex >= 0x40) {
                    menuIndex -= 0x40;
                }

                if ((caravanWork->m_inventoryItems[menuIndex] <= 0) || EquipChk(menuIndex) ||
                    (hasLetterAttach && (caravanWork->m_inventoryItems[menuIndex] < 0x125))) {
                    if (EquipChk(menuIndex)) {
                        int markX = (int)(x - kItemMarkXOffset);
                        int markY = (int)((h - kItemMarkHeight) * kItemHalfDouble + y);
                        DrawEquipMark(markX, markY, entry->alpha);
                    }
                    tex = 0x34;
                    itemAlpha = (float)((double)entry->alpha * kItemHalfDouble);
                }

                if (tex == 0x37 && drawIndex == this->m_itemMenuState->cursorIndex[0]) {
                    v += h;
                }
                drawIndex++;
            }

            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
            colors[0].r = 0xFF;
            colors[0].g = 0xFF;
            colors[0].b = 0xFF;
            colors[0].a = (u8)(itemAlpha * kItemColorMax);
            GXSetChanMatColor(GX_COLOR0A0, colors[0]);
            MenuPcs.DrawRect(0, x, y, w, h, u, v, entry->uvScale, entry->uvScale, kItemZero);
        }
    }

    CFont* listFont = this->m_fonts[4];
    listFont->SetMargin(kItemOne);
    listFont->SetShadow(0);
    listFont->SetScale(kItemListFontScale);
    listFont->DrawInit();

    {
        ItemMenuAnimList* list = this->m_itemList;
        int listCount = list->count;
        for (int i = 0; i < listCount; i++) {
            entry = &list->anims[i];
            if (entry->tex == 0x37) {
                break;
            }
        }
    }

    float colorMax = kItemColorMax;
    MenuItemOpenAnim* textEntry = entry;
    for (int i = 0; i < 8; i++, textEntry++) {
        int menuIndex = i + this->m_itemMenuState->scroll;
        if (menuIndex >= 0x40) {
            menuIndex -= 0x40;
        }

        listFont->SetColor(CColor(0xFF, 0xFF, 0xFF, (u8)(colorMax * entry->alpha)).color);

        s16 itemId = caravanWork->m_inventoryItems[menuIndex];
        if (itemId > 0) {
            const char* text = Game.m_cFlatDataArr[1].TableStrings(0)[itemId * 5 + 4];
            int selectedIndex = this->m_itemMenuState->cursorIndex[0] + this->m_itemMenuState->scroll;
            if (selectedIndex >= 0x40) {
                selectedIndex -= 0x40;
            }
            if (menuIndex == selectedIndex) {
                selectedItemId = itemId;
                foundSelected = 1;
            }

            listFont->GetWidth(text);
            float textX = (float)(textEntry->x + 0x1C);
            float textY = (float)(textEntry->y + 0xB);
            listFont->SetPosX(textX);
            listFont->SetPosY(textY - kItemTextYOffset);
            listFont->Draw(text);
        }
    }

    DrawInit();

    MenuItemOpenAnim* iconEntry = entry;
    for (int i = 0; i < 8; i++, iconEntry++) {
        int menuIndex = i + this->m_itemMenuState->scroll;
        if (menuIndex >= 0x40) {
            menuIndex -= 0x40;
        }

        s16 itemId = caravanWork->m_inventoryItems[menuIndex];
        if (itemId > 0) {
            int iconY = (int)((float)(iconEntry->y + 6) - kItemOne);
            int iconX = (int)(float)(iconEntry->x + iconEntry->w - 0x10);
            DrawSingleIcon(itemId, iconX, iconY, entry->alpha, 0, kItemZero);
        }
    }

    if (listState == 1) {
        entry = this->m_itemList->anims;
        float mark = CalcListPos(this->m_itemMenuState->scroll, 0x40, 1);
        if (mark > kItemZero) {
            DrawListPosMark((float)entry->x, (float)entry->y, mark);
        }
    }

    if (mode == 1) {
        DrawSingWin(-1);
        if (this->m_itemMenuState->optionFrame == 1) {
            DrawSingWinMess(0, this->m_itemMenuState->optionFlags, 0);
        }
    }

    if ((mode == 0 && listState == 1) || (mode != 0 && this->m_itemMenuState->optionFrame == 1)) {
        float cursorX;
        float cursorY;

        if (mode == 0) {
            ItemMenuAnimList* list = this->m_itemList;
            int cursorCount = list->count;
            for (int i = 0; i < cursorCount; i++) {
                entry = &list->anims[i];
                if (list->anims[i].tex == 0x37) {
                    break;
                }
            }

            entry += this->m_itemMenuState->cursorIndex[0];
            cursorX = (float)(entry->x - 0x14);
            cursorY = (float)((double)(entry->h - 0x20) * kItemHalfDouble + (double)entry->y);
        } else {
            MenuWindowInfo* window = this->m_menuWindowInfo;
            cursorX = (float)window->x;
            cursorY = (float)(window->y + 0x20);
            int messageHeight = SingWinMessHeight();
            cursorY += (float)(this->m_itemMenuState->cursorIndex[1] * messageHeight);
        }

        int cursorAnim = (int)System.m_frameCounter % 8;
        cursorX += (float)cursorAnim;
        DrawCursor((int)cursorX, (int)cursorY, kItemOne);
    }

    DrawInit();
    DrawSingLife();

    CFont* helpFont = this->m_fonts[0];
    s8 helpAlpha = (s8)(entry->alpha * kItemColorMax);
    if (!foundSelected) {
        selectedItemId = -1;
    }
    GXColor helpColor = CColor(0xFF, 0xFF, 0xFF, helpAlpha).color;
    int helpX = (int)(kItemHelpCenterX - kItemHalf * w);
    int helpY = (int)kItemHelpY;
    DrawHelpMessage(
        selectedItemId,
        helpFont,
        helpX,
        helpY,
        helpColor,
        10,
        kItemOne,
        kItemHelpScale);
}

/*
 * --INFO--
 * PAL Address: 0x8015a818
 * PAL Size: 380b
 * EN Address: 0x8017B8F4
 * EN Size: 552b
 * JP Address: TODO
 * JP Size: TODO
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
            float zero = kItemZero;
            finished++;
            anim->alpha = zero;
            anim->dx = zero;
            anim->dy = zero;
        } else {
            anim->frame++;
            double one = kItemOneDouble;
            anim->alpha =
                (float)-((kItemOneDouble / (double)anim->duration) * (double)anim->frame - kItemOneDouble);
            if ((anim->flags & 2) == 0) {
                float ratio = (float)-((one / (double)anim->duration) * (double)anim->frame - one);
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
 * EN Address: 0x8017B7C0
 * EN Size: 308b
 * JP Address: TODO
 * JP Size: TODO
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
 * EN Address: 0x8017B57C
 * EN Size: 580b
 * JP Address: TODO
 * JP Size: TODO
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
                anim->alpha = kItemOne;
                anim->dx = kItemZero;
                anim->dy = kItemZero;
            } else {
                anim->frame++;
                double one = kItemOneDouble;
                anim->alpha = (float)((one / (double)anim->duration) * (double)anim->frame);
                if ((anim->flags & 2) == 0) {
                    float ratio = (float)((one / (double)anim->duration) * (double)anim->frame);
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
 * EN Address: 0x8017B3E0
 * EN Size: 412b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ItemInit1()
{
    float progress;
    int count;
    int index;
    MenuItemOpenAnim* entry;
    ItemMenuAnimList* itemList;

    index = 0;
    entry = &this->m_itemList->anims[index++];
    entry->tex = 0x2E;
    entry->startFrame = 2;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->tex = 0x47;
    entry->startFrame = 7;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->tex = 0x47;
    entry->startFrame = 7;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = 0x2E;
    entry->startFrame = 7;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = 0x37;
    progress = kItemOne;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = &this->m_itemList->anims[index];
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    itemList = this->m_itemList;
    count = itemList->count;
    entry = itemList->anims;
    for (unsigned int i = 0; i < count; i++, entry++) {
        entry->frame = 0;
        entry->alpha = progress;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8015aeb0
 * PAL Size: 680b
 * EN Address: 0x8017B0F8
 * EN Size: 744b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ItemInit()
{
    int index;
    MenuItemOpenAnim* entry;

    memset(m_itemList, 0, sizeof(*m_itemList));
    {
        entry = m_itemList->anims;
        for (int initCount = 0; initCount < 64; initCount++, entry++) {
            entry->uvScale = kItemOne;
        }
    }

    index = 0;
    entry = &m_itemList->anims[index++];
    entry->tex = 0x2E;
    entry->x = 0x68;
    entry->y = 0x28;
    entry->w = 0x78;
    entry->h = 0x108;
    entry->u = kItemInitU;
    entry->v = kItemInitV;
    entry->uvScale = kItemOne;
    entry->startFrame = 5;
    entry->duration = 5;

    entry = &m_itemList->anims[index++];
    entry->tex = 0x47;
    entry->x = 0x50;
    entry->y = 0xE;
    entry->w = 0x30;
    entry->h = 0x30;
    entry->u = kItemZero;
    entry->v = kItemZero;
    entry->uvScale = kItemOne;
    entry->startFrame = 0;
    entry->duration = 5;

    entry = &m_itemList->anims[index++];
    entry->tex = 0x47;
    entry->x = 0x55;
    entry->w = 0x30;
    entry->h = 0x30;
    entry->y = 0x150 - entry->h;
    entry->u = kItemZero;
    entry->v = kItemZero;
    entry->uvScale = kItemSmallScale;
    entry->startFrame = 0;
    entry->duration = 5;

    entry = &m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = 0x2E;
    entry->x = 0x50;
    entry->y = 8;
    entry->w = 0x48;
    entry->h = 0x140;
    entry->u = kItemZero;
    entry->v = kItemZero;
    entry->startFrame = 0;
    entry->duration = 5;

    MenuItemOpenAnim* firstEntry = m_itemList->anims;
    for (int loopCount = 0; loopCount < 8; loopCount++) {
        entry = &m_itemList->anims[index++];
        entry->flags = 2;
        entry->tex = 0x37;
        entry->x = firstEntry->x + 0x24;
        entry->y = firstEntry->y + loopCount * 0x20;
        entry->w = 200;
        entry->h = 0x28;
        entry->u = kItemZero;
        entry->v = kItemZero;
        entry->startFrame = 7;
        entry->duration = 5;
    }

    m_itemList->count = index;
    m_itemMenuState->cursorIndex[0] = 0;
    m_itemMenuState->initialized = 1;
}
