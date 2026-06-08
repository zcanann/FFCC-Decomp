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
static const double kItemIntToDoubleBias = 4503601774854144.0;
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
STATIC_ASSERT(offsetof(ItemMenuState, selectedIndex) == 0x26);
STATIC_ASSERT(offsetof(ItemMenuState, subMenuIndex) == 0x28);
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

static inline float LoadFloat(const float& value)
{
    return value;
}

static inline double LoadDouble(const double& value)
{
    return value;
}

/*
 * --INFO--
 * PAL Address: 0x80159654
 * PAL Size: 1952b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ItemCtrlCur()
{
    bool blocked = false;
    unsigned int press;
    int hold;
    CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

    if ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) {
        blocked = true;
    }
    if (blocked) {
        press = 0;
    } else {
        int padIndex = 0;
        padIndex &= ~-((__cntlzw((unsigned int)Pad.m_debugPadPort) & 0x20) >> 5);
        press = Pad.GetPadInputs()[padIndex].buttonDown[0];
    }

    blocked = false;
    if ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) {
        blocked = true;
    }
    if (blocked) {
        hold = 0;
    } else {
        int padIndex = 0;
        padIndex &= ~-((__cntlzw((unsigned int)Pad.m_debugPadPort) & 0x20) >> 5);
        hold = Pad.GetPadInputs()[padIndex].repeatButton;
    }

    if (hold == 0) {
        return 0;
    }

    int mode = this->m_itemMenuState->mode;
    s16 letterAttachFlg = SingGetLetterAttachflg();

    if (mode == 0) {
        if ((hold & 8) != 0) {
            if (this->m_itemMenuState->selectedIndex != 0) {
                this->m_itemMenuState->selectedIndex = this->m_itemMenuState->selectedIndex - 1;
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            } else {
                if (this->m_itemMenuState->scroll != 0) {
                    this->m_itemMenuState->scroll = this->m_itemMenuState->scroll - 1;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                } else {
                    this->m_itemMenuState->scroll = 0x3F;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }
            }
        } else if ((hold & 4) != 0) {
            if (this->m_itemMenuState->selectedIndex < 7) {
                this->m_itemMenuState->selectedIndex = this->m_itemMenuState->selectedIndex + 1;
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            } else {
                s16 scroll = this->m_itemMenuState->scroll;
                if (scroll < 0x3F) {
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
                int idx = this->m_itemMenuState->scroll + this->m_itemMenuState->selectedIndex;
                if (idx >= 0x40) {
                    idx -= 0x40;
                }

                s16 itemId = caravanWork->m_inventoryItems[idx];

                if ((itemId < 1) || (EquipChk(idx) != 0) ||
                    ((letterAttachFlg >= 0) && (itemId < 0x125))) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                } else if (letterAttachFlg >= 0) {
                    LetterSetAttachItem((unsigned int)idx, 1);
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                    return 1;
                } else {
                    this->m_itemMenuState->optionFlags = 0xC;
                    unsigned int itemType = GetItemType(idx, 0);

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
            if (this->m_itemMenuState->subMenuIndex != 0) {
                this->m_itemMenuState->subMenuIndex = this->m_itemMenuState->subMenuIndex - 1;
            } else {
                this->m_itemMenuState->subMenuIndex = 3;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((hold & 4) != 0) {
            if (this->m_itemMenuState->subMenuIndex < 3) {
                this->m_itemMenuState->subMenuIndex = this->m_itemMenuState->subMenuIndex + 1;
            } else {
                this->m_itemMenuState->subMenuIndex = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((hold & 0xC) == 0) {
            if ((press & 0x100) != 0) {
                int option = (int)this->m_itemMenuState->subMenuIndex;
                if (((int)this->m_itemMenuState->optionFlags & (1 << option)) == 0) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                } else {
                    int idx = this->m_itemMenuState->scroll + this->m_itemMenuState->selectedIndex;
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ItemDraw()
{
    bool foundSelected = false;
    int selectedItemId;

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
    s16 listState = this->m_itemMenuState->listState;
    s16 mode = this->m_itemMenuState->mode;
    ItemMenuAnimList* itemList = this->m_itemList;
    bool hasLetterAttach = SingGetLetterAttachflg() >= 0;
    int drawIndex = 0;
    MenuItemOpenAnim* entry = itemList->anims;

    for (int i = 0; i < this->m_itemList->count; i++, entry++) {
        int tex = entry->tex;
        if (tex < 0) {
            continue;
        }

        float x = (float)entry->x;
        float y = (float)entry->y;
        float w = (float)entry->w;
        float h = (float)entry->h;
        float u = entry->u;
        float v = entry->v;
        float alpha = entry->alpha;

        if (i == 0) {
            MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));

            GXColor colors[4];
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
            w = alpha * w;
            if (w > LoadFloat(kItemZero)) {
                MenuPcs.DrawRect(
                    0, x, y, w, h, u, v, colors, LoadFloat(kItemOne), LoadFloat(kItemOne), LoadFloat(kItemZero));
                x += w;
                u += w;
            }

            if (w > LoadFloat(kItemZero) && w < entry->w) {
                colors[0].r = 0xFF;
                colors[0].g = 0xFF;
                colors[0].b = 0xFF;
                colors[0].a = 0;
                colors[1].r = 0xFF;
                colors[1].g = 0xFF;
                colors[1].b = 0xFF;
                colors[1].a = 0;
                colors[2].r = 0xFF;
                colors[2].g = 0xFF;
                colors[2].b = 0xFF;
                colors[2].a = 0;
                colors[3].r = 0xFF;
                colors[3].g = 0xFF;
                colors[3].b = 0xFF;
                colors[3].a = 0;

                float remainW = (float)((double)(LoadDouble(kItemOneDouble) / (double)entry->duration) * (double)entry->w);
                MenuPcs.DrawRect(
                    0, x, y, remainW, h, u, v, colors, LoadFloat(kItemOne), LoadFloat(kItemOne), LoadFloat(kItemZero));
            }

            MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
        } else {
            float itemAlpha = alpha;
            if (tex == 0x37) {
                unsigned int menuIndex = drawIndex + this->m_itemMenuState->scroll;
                if (menuIndex > 0x3F) {
                    menuIndex -= 0x40;
                }

                s16 itemId = caravanWork->m_inventoryItems[menuIndex];
                if ((itemId < 1) || (EquipChk(menuIndex) != 0) ||
                    (hasLetterAttach && (itemId < 0x125))) {
                    if (EquipChk(menuIndex) != 0) {
                        int markX = (unsigned int)(x - LoadFloat(kItemMarkXOffset));
                        int markY = (unsigned int)((float)((h - LoadFloat(kItemMarkHeight)) * (float)LoadDouble(kItemHalfDouble)) + y);
                        DrawEquipMark(markX, markY, alpha);
                    }
                    tex = 0x34;
                    itemAlpha = (float)((double)LoadDouble(kItemHalfDouble) * (double)alpha);
                }

                if (tex == 0x37 && drawIndex == this->m_itemMenuState->selectedIndex) {
                    v += h;
                }
                drawIndex++;
            }

            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
            GXColor color;
            color.r = 0xFF;
            color.g = 0xFF;
            color.b = 0xFF;
            color.a = (u8)(LoadFloat(kItemColorMax) * itemAlpha);
            GXSetChanMatColor(GX_COLOR0A0, color);
            MenuPcs.DrawRect(0, x, y, w, h, u, v, entry->uvScale, entry->uvScale, LoadFloat(kItemZero));
        }
    }

    CFont* listFont = this->m_fonts[4];
    listFont->SetMargin(LoadFloat(kItemOne));
    listFont->SetShadow(0);
    listFont->SetScale(LoadFloat(kItemListFontScale));
    listFont->DrawInit();

    MenuItemOpenAnim* listStart = itemList->anims;
    int listCount = itemList->count;
    for (int i = 0; i < listCount; i++, listStart++) {
        if (listStart->tex == 0x37) {
            break;
        }
    }

    MenuItemOpenAnim* textEntry = listStart;
    for (int i = 0; i < 8; i++, textEntry++) {
        int menuIndex = i + this->m_itemMenuState->scroll;
        if (menuIndex > 0x3F) {
            menuIndex -= 0x40;
        }

        CColor textColor(0xFF, 0xFF, 0xFF, (u8)(LoadFloat(kItemColorMax) * listStart->alpha));
        listFont->SetColor(textColor.color);

        s16 itemId = caravanWork->m_inventoryItems[menuIndex];
        if (itemId > 0) {
            const char* text = Game.m_cFlatDataArr[1].TableStrings(0)[itemId * 5 + 4];
            unsigned int selectedIndex = this->m_itemMenuState->selectedIndex + this->m_itemMenuState->scroll;
            if (selectedIndex > 0x3F) {
                selectedIndex -= 0x40;
            }
            if (menuIndex == selectedIndex) {
                foundSelected = true;
                selectedItemId = itemId;
            }

            listFont->GetWidth(text);
            listFont->SetPosX((float)(textEntry->x + 0x1C));
            listFont->SetPosY((float)(textEntry->y + 0xB) - LoadFloat(kItemTextYOffset));
            listFont->Draw(text);
        }
    }

    DrawInit();

    MenuItemOpenAnim* iconEntry = listStart;
    for (int i = 0; i < 8; i++, iconEntry++) {
        int menuIndex = i + this->m_itemMenuState->scroll;
        if (menuIndex > 0x3F) {
            menuIndex -= 0x40;
        }

        s16 itemId = caravanWork->m_inventoryItems[menuIndex];
        if (itemId > 0) {
            int iconY = (int)((float)(iconEntry->y + 6) - LoadFloat(kItemOne));
            int iconX = (int)(float)(iconEntry->x + iconEntry->w - 0x10);
            DrawSingleIcon(itemId, iconX, iconY, listStart->alpha, 0, LoadFloat(kItemZero));
        }
    }

    if (listState == 1) {
        float mark = CalcListPos(this->m_itemMenuState->scroll, 0x40, 1);
        if (mark > LoadFloat(kItemZero)) {
            DrawListPosMark((float)itemList->anims[0].x, (float)itemList->anims[0].y, mark);
        }
    }

    if (mode == 1) {
        DrawSingWin(-1);
        if (this->m_itemMenuState->optionFrame == 1) {
            DrawSingWinMess(0, this->m_itemMenuState->optionFlags, 0);
        }
    }

    MenuItemOpenAnim* cursorEntry = listStart;
    if ((mode == 0 && listState == 1) || (mode != 0 && this->m_itemMenuState->optionFrame == 1)) {
        float cursorX;
        float cursorY;

        if (mode == 0) {
            cursorEntry = itemList->anims;
            int cursorCount = itemList->count;
            for (int i = 0; i < cursorCount; i++, cursorEntry++) {
                if (cursorEntry->tex == 0x37) {
                    break;
                }
            }

            cursorEntry += this->m_itemMenuState->selectedIndex;
            cursorX = (float)(cursorEntry->x - 0x14);
            cursorY = (float)((float)(cursorEntry->h - 0x20) * (float)LoadDouble(kItemHalfDouble) + (float)cursorEntry->y);
        } else {
            MenuWindowInfo* window = this->m_menuWindowInfo;
            cursorX = (float)window->x;
            cursorY = (float)(window->y + 0x20);
            int messageHeight = SingWinMessHeight();
            cursorY += (float)(this->m_itemMenuState->subMenuIndex * messageHeight);
        }

        int cursorAnim = (int)System.m_frameCounter % 8;
        DrawCursor((int)(cursorX + (float)cursorAnim), (int)cursorY, LoadFloat(kItemOne));
    }

    DrawInit();
    DrawSingLife();

    CFont* helpFont = this->m_fonts[0];
    CColor helpColor(0xFF, 0xFF, 0xFF, (u8)(LoadFloat(kItemColorMax) * cursorEntry->alpha));
    if (!foundSelected) {
        selectedItemId = -1;
    }
    float helpBaseX = LoadFloat(kItemHelpCenterX);
    float helpOffsetX = LoadFloat(kItemHalf);
    int helpX = (unsigned int)(helpBaseX - (float)(LoadDouble(kItemHalfDouble) * (double)helpOffsetX));
    int helpY = (int)LoadFloat(kItemHelpY);
    DrawHelpMessage(
        selectedItemId,
        helpFont,
        helpX,
        helpY,
        helpColor.color,
        10,
        LoadFloat(kItemOne),
        LoadFloat(kItemHelpScale));
}

/*
 * --INFO--
 * PAL Address: 0x8015a818
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::ItemClose()
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
            float zero = LoadFloat(kItemZero);
            finished++;
            anim->alpha = zero;
            anim->dx = zero;
            anim->dy = zero;
        } else {
            anim->frame++;
            double one = LoadDouble(kItemOneDouble);
            anim->alpha =
                (float)-((LoadDouble(kItemOneDouble) / (double)anim->duration) * (double)anim->frame - LoadDouble(kItemOneDouble));
            if ((anim->flags & 2) == 0) {
                float ratio = (float)-((one / (double)anim->duration) * (double)anim->frame - one);
                float dx = anim->targetX - (float)anim->x;
                float dy = anim->targetY - (float)anim->y;
                anim->dx = dx * ratio;
                anim->dy = dy * ratio;
            }
        }
    }

    bool closed = false;
    if (count == finished) {
        closed = true;
    }
    return closed;
}

/*
 * --INFO--
 * PAL Address: 0x8015a994
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ItemCtrl()
{
    int changed = 0;

    this->m_itemMenuState->prevMode = this->m_itemMenuState->mode;

    if ((this->m_itemMenuState->mode == 0) ||
        ((this->m_itemMenuState->mode != 0) && (this->m_itemMenuState->optionFrame == 1))) {
        changed = ItemCtrlCur();
    } else if ((this->m_itemMenuState->mode == 1) && (this->m_itemMenuState->optionFrame == 0)) {
        if (this->m_menuWindowInfo->state == 1) {
            changed = 0;
            this->m_itemMenuState->optionFrame++;
        }
    } else if (((this->m_itemMenuState->mode == 1) && (this->m_itemMenuState->optionFrame == 2)) &&
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::ItemOpen()
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
                anim->alpha = LoadFloat(kItemOne);
                anim->dx = LoadFloat(kItemZero);
                anim->dy = LoadFloat(kItemZero);
            } else {
                anim->frame++;
                double one = LoadDouble(kItemOneDouble);
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

    bool opened = false;
    if (count == finished) {
        opened = true;
    }
    return opened;
}

/*
 * --INFO--
 * PAL Address: 0x8015ac54
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ItemInit1()
{
    float progress;
    int count;
    unsigned int blocks;
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
    progress = LoadFloat(kItemOne);
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
    count = (unsigned int)itemList->count;
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ItemInit()
{
    int index;
    int yOffset;
    int count;
    MenuItemOpenAnim* entry;
    ItemMenuAnimList* itemList;

    memset(this->m_itemList, 0, sizeof(*this->m_itemList));
    float one = LoadFloat(kItemOne);
    entry = this->m_itemList->anims;
    for (int initCount = 0; initCount < 64; initCount++, entry++) {
        entry->uvScale = one;
    }

    index = 0;
    entry = &this->m_itemList->anims[index++];
    entry->tex = 0x2E;
    entry->x = 0x68;
    entry->y = 0x28;
    entry->w = 0x78;
    entry->h = 0x108;
    float titleAlpha = LoadFloat(kItemInitU);
    float titleScale = kItemInitV;
    float zero = LoadFloat(kItemZero);
    entry->u = titleAlpha;
    entry->v = titleScale;
    entry->uvScale = one;
    count = 4;
    entry->startFrame = 5;
    entry->duration = 5;

    entry = &this->m_itemList->anims[index++];
    entry->tex = 0x47;
    entry->x = 0x50;
    entry->y = 0xE;
    entry->w = 0x30;
    entry->h = 0x30;
    entry->u = zero;
    entry->v = zero;
    entry->uvScale = one;
    entry->startFrame = 0;
    entry->duration = 5;

    entry = &this->m_itemList->anims[index++];
    entry->tex = 0x47;
    entry->x = 0x55;
    entry->w = 0x30;
    entry->h = 0x30;
    entry->y = 0x150 - entry->h;
    float rightUvScale = kItemSmallScale;
    entry->u = zero;
    entry->v = zero;
    entry->uvScale = rightUvScale;
    entry->startFrame = 0;
    entry->duration = 5;

    entry = &this->m_itemList->anims[index++];
    entry->flags = 2;
    entry->tex = 0x2E;
    entry->x = 0x50;
    entry->y = 8;
    entry->w = 0x48;
    entry->h = 0x140;
    entry->u = zero;
    entry->v = zero;
    entry->startFrame = 0;
    entry->duration = 5;

    itemList = this->m_itemList;
    yOffset = 0;
    for (int loopCount = 0; loopCount < 4; loopCount++) {
        entry = &this->m_itemList->anims[index++];
        entry->flags = 2;
        entry->tex = 0x37;
        count = count + 2;
        entry->x = itemList->anims[0].x + 0x24;
        entry->y = itemList->anims[0].y + yOffset;
        yOffset = yOffset + 0x20;
        entry->w = 200;
        entry->h = 0x28;
        entry->u = zero;
        entry->v = zero;
        entry->startFrame = 7;
        entry->duration = 5;

        entry = &this->m_itemList->anims[index++];
        entry->flags = 2;
        entry->tex = 0x37;
        entry->x = itemList->anims[0].x + 0x24;
        entry->y = itemList->anims[0].y + yOffset;
        yOffset = yOffset + 0x20;
        entry->w = 200;
        entry->h = 0x28;
        entry->u = zero;
        entry->v = zero;
        entry->startFrame = 7;
        entry->duration = 5;
    }

    this->m_itemList->count = count;
    this->m_itemMenuState->selectedIndex = 0;
    this->m_itemMenuState->initialized = 1;
}
