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

extern const float FLOAT_80332e60;
extern const float FLOAT_80332e64;
extern const double DOUBLE_80332e68;
extern const float FLOAT_80332e70;
extern const float FLOAT_80332e74;
extern const double DOUBLE_80332e78;
extern const float FLOAT_80332e80;
extern const float FLOAT_80332e84;
extern const float FLOAT_80332e88;
extern const float FLOAT_80332e8c;
extern const float FLOAT_80332e90;
extern const float FLOAT_80332e94;
extern const float FLOAT_80332E98;
extern const double DOUBLE_80332ea0;
extern const float FLOAT_80332EA8;
extern const float FLOAT_80332EAC;
extern const float FLOAT_80332EB0;
extern const double DOUBLE_80333388 = 373.0;
extern const float FLOAT_80333390 = 214.0f;
extern const float FLOAT_80333394 = 112.0f;
extern const float FLOAT_80333398 = 474.0f;
extern const double DOUBLE_803333a0 = 32.0;

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

struct ItemFlatTableEntry {
    int count;
    const char** index;
    char* buffer;
};

struct ItemFlatData {
    char pad[0x6C];
    ItemFlatTableEntry table[8];
};

STATIC_ASSERT(offsetof(CMenuPcs, helpFont) == 0xF8);
STATIC_ASSERT(offsetof(CMenuPcs, listFont) == 0x108);
STATIC_ASSERT(offsetof(CMenuPcs, itemMenuState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, singWindowInfo) == 0x848);
STATIC_ASSERT(offsetof(CMenuPcs, itemList) == 0x850);
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

static inline ItemMenuAnimList* GetItemOpenAnimList(CMenuPcs* menu)
{
    return reinterpret_cast<ItemMenuAnimList*>(menu->itemList);
}

static inline MenuItemOpenAnim* GetItemOpenAnim(CMenuPcs* menu, int index)
{
    return reinterpret_cast<MenuItemOpenAnim*>(
        reinterpret_cast<unsigned char*>(GetItemOpenAnimList(menu)) + 8 + index * sizeof(MenuItemOpenAnim));
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
    unsigned int hold;
    CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        blocked = true;
    }
    if (blocked) {
        press = 0;
    } else {
        int padIndex = blocked;
        padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
        press = *(u16*)((u8*)&Pad + padIndex * 0x54 + 8);
    }

    blocked = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        blocked = true;
    }
    if (blocked) {
        hold = 0;
    } else {
        int padIndex = blocked;
        padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
        hold = *(u16*)((u8*)&Pad + padIndex * 0x54 + 0x14);
    }

    if (hold == 0) {
        return 0;
    }

    int mode = this->itemMenuState->mode;
    s16 letterAttachFlg = SingGetLetterAttachflg();

    if (mode == 0) {
        if ((hold & 8) != 0) {
            if (this->itemMenuState->selectedIndex == 0) {
                if (this->itemMenuState->scroll == 0) {
                    this->itemMenuState->scroll = 0x3F;
                } else {
                    this->itemMenuState->scroll = this->itemMenuState->scroll - 1;
                }
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            } else {
                this->itemMenuState->selectedIndex = this->itemMenuState->selectedIndex - 1;
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            }
        } else if ((hold & 4) != 0) {
            if (this->itemMenuState->selectedIndex < 7) {
                this->itemMenuState->selectedIndex = this->itemMenuState->selectedIndex + 1;
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            } else {
                s16 scroll = this->itemMenuState->scroll;
                if (scroll > 0x3E) {
                    this->itemMenuState->scroll = 0;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                } else {
                    this->itemMenuState->scroll = scroll + 1;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }
            }
        }

        if ((hold & 0xC) == 0) {
            if ((press & 0x20) != 0) {
                if (letterAttachFlg < 0) {
                    this->itemMenuState->cursorMove = 1;
                    Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
                    return 1;
                }
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else if ((press & 0x40) != 0) {
                if (letterAttachFlg < 0) {
                    this->itemMenuState->cursorMove = -1;
                    Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
                    return 1;
                }
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else if ((press & 0x100) != 0) {
                int idx = this->itemMenuState->scroll + this->itemMenuState->selectedIndex;
                if (idx > 0x3F) {
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
                    this->itemMenuState->optionFlags = 0xC;
                    int itemType = GetItemType(idx, 0);

                    if ((itemType == 7) && (caravanWork->CanPlayerUseItem() != 0)) {
                        this->itemMenuState->optionFlags = this->itemMenuState->optionFlags | 1;
                    }
                    if ((itemType != 1) && (caravanWork->CanPlayerPutItem() != 0)) {
                        this->itemMenuState->optionFlags = this->itemMenuState->optionFlags | 2;
                    }

                    s16 winW;
                    s16 winH;
                    GetSingWinSize(0, &winW, &winH, 0);
                    SetSingWinInfo(0xF0, 0xA0, winW, winH);

                    this->singWindowInfo[5] = 0;
                    this->itemMenuState->optionFrame = 0;
                    this->itemMenuState->mode = 1;
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                }
            } else if ((press & 0x200) != 0) {
                if (letterAttachFlg >= 0) {
                    LetterSetAttachItem(0, 0xFFFFFFFF);
                    Sound.PlaySe(3, 0x40, 0x7F, 0);
                    return 1;
                }
                this->itemMenuState->closeRequested = 1;
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                return 1;
            }
        }
    } else {
        int optBase = (int)this->itemMenuState + mode * 2;

        if ((hold & 8) != 0) {
            if (*(s16*)(optBase + 0x26) == 0) {
                *(s16*)(optBase + 0x26) = 3;
            } else {
                *(s16*)(optBase + 0x26) = *(s16*)(optBase + 0x26) - 1;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((hold & 4) != 0) {
            if (*(s16*)(optBase + 0x26) < 3) {
                *(s16*)(optBase + 0x26) = *(s16*)(optBase + 0x26) + 1;
            } else {
                *(s16*)(optBase + 0x26) = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((hold & 0xC) == 0) {
            if ((press & 0x100) != 0) {
                int option = (int)*(s16*)(optBase + 0x26);
                if (((int)this->itemMenuState->optionFlags & (1 << option)) == 0) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                } else {
                    int idx = this->itemMenuState->scroll + this->itemMenuState->selectedIndex;
                    if (idx > 0x3F) {
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

                    this->singWindowInfo[5] = 2;
                    this->itemMenuState->optionFrame = this->itemMenuState->optionFrame + 1;
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                }
            } else if ((press & 0x200) != 0) {
                this->singWindowInfo[5] = 2;
                this->itemMenuState->optionFrame = this->itemMenuState->optionFrame + 1;
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
    int selectedItemId = -1;

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
    ItemMenuState* itemState = this->itemMenuState;
    ItemMenuAnimList* itemList = this->itemList;
    s16 listState = itemState->listState;
    s16 mode = itemState->mode;
    bool hasLetterAttach = SingGetLetterAttachflg() >= 0;
    int drawIndex = 0;
    int count = itemList->count;
    MenuItemOpenAnim* entry = itemList->anims;

    for (int i = 0; i < count; i++, entry++) {
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
        float uvScale = entry->uvScale;

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
            float fillW = alpha * w;
            if (fillW > FLOAT_80332e60) {
                MenuPcs.DrawRect(
                    0, x, y, fillW, h, u, v, colors, FLOAT_80332e64, FLOAT_80332e64, FLOAT_80332e60);
                x += fillW;
                u += fillW;
            }

            if (fillW > FLOAT_80332e60 && fillW < w) {
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

                float remainW = (float)((double)(DOUBLE_80332e68 / (double)entry->duration) * (double)w);
                MenuPcs.DrawRect(
                    0, x, y, remainW, h, u, v, colors, FLOAT_80332e64, FLOAT_80332e64, FLOAT_80332e60);
            }

            MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
        } else {
            float itemAlpha = alpha;
            if (tex == 0x37) {
                int menuIndex = drawIndex + itemState->scroll;
                if (menuIndex > 0x3F) {
                    menuIndex -= 0x40;
                }

                s16 itemId = caravanWork->m_inventoryItems[menuIndex];
                if ((itemId < 1) || (EquipChk(menuIndex) != 0) ||
                    (hasLetterAttach && (itemId < 0x125))) {
                    if (EquipChk(menuIndex) != 0) {
                        int markX = (int)(x - FLOAT_80332e70);
                        int markY = (int)((float)((h - FLOAT_80332e74) * (float)DOUBLE_80332e78) + y);
                        DrawEquipMark(markX, markY, alpha);
                    }
                    tex = 0x34;
                    itemAlpha = (float)((double)DOUBLE_80332e78 * (double)alpha);
                }

                if (tex == 0x37 && drawIndex == itemState->selectedIndex) {
                    v += h;
                }
                drawIndex++;
            }

            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
            GXColor color;
            color.r = 0xFF;
            color.g = 0xFF;
            color.b = 0xFF;
            color.a = (u8)(FLOAT_80332e80 * itemAlpha);
            GXSetChanMatColor(GX_COLOR0A0, color);
            MenuPcs.DrawRect(0, x, y, w, h, u, v, uvScale, uvScale, FLOAT_80332e60);
        }
    }

    CFont* listFont = this->listFont;
    listFont->SetMargin(FLOAT_80332e64);
    listFont->SetShadow(0);
    listFont->SetScale(FLOAT_80332e84);
    listFont->DrawInit();

    s16* listStart = reinterpret_cast<s16*>(itemList->anims);
    int listCount = itemList->count;
    for (int i = 0; i < listCount; i++, listStart += 0x20) {
        if (*(int*)(listStart + 0xE) == 0x37) {
            break;
        }
    }

    const ItemFlatData* flatData = reinterpret_cast<const ItemFlatData*>(&Game.m_cFlatDataArr[1]);
    s16* textEntry = listStart;
    for (int i = 0; i < 8; i++, textEntry += 0x20) {
        int menuIndex = i + itemState->scroll;
        if (menuIndex > 0x3F) {
            menuIndex -= 0x40;
        }

        CColor textColor(0xFF, 0xFF, 0xFF, (u8)(FLOAT_80332e80 * *(float*)(listStart + 8)));
        listFont->SetColor(textColor.color);

        s16 itemId = caravanWork->m_inventoryItems[menuIndex];
        if (itemId > 0) {
            const char* text = flatData->table[0].index[itemId * 5 + 4];
            int selectedIndex = itemState->selectedIndex + itemState->scroll;
            if (selectedIndex > 0x3F) {
                selectedIndex -= 0x40;
            }
            if (menuIndex == selectedIndex) {
                selectedItemId = itemId;
            }

            listFont->GetWidth(text);
            listFont->SetPosX((float)(textEntry[0] + 0x1C));
            listFont->SetPosY((float)(textEntry[1] + 0xB) - FLOAT_80332e88);
            listFont->Draw(text);
        }
    }

    DrawInit();

    s16* iconEntry = listStart;
    for (int i = 0; i < 8; i++, iconEntry += 0x20) {
        int menuIndex = i + itemState->scroll;
        if (menuIndex > 0x3F) {
            menuIndex -= 0x40;
        }

        s16 itemId = caravanWork->m_inventoryItems[menuIndex];
        if (itemId > 0) {
            int iconY = (int)((float)(iconEntry[1] + 6) - FLOAT_80332e64);
            int iconX = (int)(float)(iconEntry[0] + iconEntry[2] - 0x10);
            DrawSingleIcon(itemId, iconX, iconY, *(float*)(listStart + 8), 0, FLOAT_80332e60);
        }
    }

    if (listState == 1) {
        float mark = CalcListPos(itemState->scroll, 0x40, 1);
        if (mark > FLOAT_80332e60) {
            DrawListPosMark((float)itemList->anims[0].x, (float)itemList->anims[0].y, mark);
        }
    }

    if (mode == 1) {
        DrawSingWin(-1);
        if (this->itemMenuState->optionFrame == 1) {
            DrawSingWinMess(0, this->itemMenuState->optionFlags, 0);
        }
    }

    s16* cursorEntry = listStart;
    if ((mode == 0 && listState == 1) || (mode != 0 && itemState->optionFrame == 1)) {
        float cursorX;
        float cursorY;

        if (mode == 0) {
            cursorEntry += itemState->selectedIndex * 0x20;
            cursorX = (float)(cursorEntry[0] - 0x14);
            cursorY = (float)((float)(cursorEntry[3] - 0x20) * (float)DOUBLE_80332e78 + (float)cursorEntry[1]);
        } else {
            s16* singWindow = this->singWindowInfo;
            cursorX = (float)singWindow[0];
            cursorY = (float)(singWindow[1] + 0x20);
            int messageHeight = SingWinMessHeight();
            cursorY += (float)(this->itemMenuState->subMenuIndex * messageHeight);
        }

        int cursorAnim = (int)System.m_frameCounter % 8;
        DrawCursor((int)(cursorX + (float)cursorAnim), (int)cursorY, FLOAT_80332e64);
    }

    DrawInit();
    DrawSingLife();

    CFont* helpFont = this->helpFont;
    CColor helpColor(0xFF, 0xFF, 0xFF, (u8)(FLOAT_80332e80 * *(float*)(cursorEntry + 8)));
    DrawHelpMessage(
        selectedItemId,
        helpFont,
        (int)-((double)(DOUBLE_80332e78 * (double)FLOAT_80332e90) - (double)FLOAT_80332e8c),
        (int)FLOAT_80332e94,
        helpColor.color,
        10,
        FLOAT_80332e64,
        FLOAT_80332E98);
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
    this->itemMenuState->frame++;

    ItemMenuAnimList* itemList = this->itemList;
    MenuItemOpenAnim* anim = itemList->anims;
    int finished = 0;
    int count = itemList->count;
    int frame = this->itemMenuState->frame;

    for (int i = 0; i < count; i++, anim++) {
        if (frame < anim->startFrame) {
            continue;
        }

        if (anim->startFrame + anim->duration <= frame) {
            float zero = FLOAT_80332e60;
            finished++;
            anim->alpha = zero;
            anim->dx = zero;
            anim->dy = zero;
        } else {
            anim->frame++;
            double one = DOUBLE_80332e68;
            anim->alpha =
                (float)-((DOUBLE_80332e68 / (double)anim->duration) * (double)anim->frame - DOUBLE_80332e68);
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
    int sVar1;
    int iVar2;
    int iVar3;

    iVar3 = 0;
    *(s16*)((int)itemMenuState + 0x32) = *(s16*)((int)itemMenuState + 0x30);
    iVar2 = (int)itemMenuState;
    sVar1 = *(s16*)(iVar2 + 0x30);

    if ((sVar1 == 0) || ((sVar1 != 0) && (*(s16*)(iVar2 + 0x12) == 1))) {
        iVar3 = ItemCtrlCur();
    } else if ((sVar1 == 1) && ((int)*(s16*)(iVar2 + 0x12) == 0)) {
        if (*(s16*)((int)singWindowInfo + 10) == 1) {
            iVar3 = 0;
            *(s16*)(iVar2 + 0x12) = *(s16*)(iVar2 + 0x12) + 1;
        }
    } else if (((sVar1 == 1) && (*(s16*)(iVar2 + 0x12) == 2)) &&
               (*(s16*)((int)singWindowInfo + 10) == 3)) {
        iVar3 = 0;
        *(s16*)(iVar2 + 0x12) = 0;
        *(s16*)((int)itemMenuState + 0x30) = 0;
        *(s16*)((int)itemMenuState + 0x22) = 0;
    }

    if (iVar3 != 0) {
        SingLifeInit(-1);
        ItemInit1();
    }

    return iVar3;
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
    if (this->itemMenuState->initialized == '\0') {
        SingLifeInit(-1);
        ItemInit();
    }

    this->itemMenuState->frame++;
    ItemMenuAnimList* itemList = this->itemList;
    MenuItemOpenAnim* anim = itemList->anims;
    int finished = 0;
    int count = itemList->count;
    int frame = this->itemMenuState->frame;

    for (int i = 0; i < count; i++, anim++) {
        if (frame >= anim->startFrame) {
            if (anim->startFrame + anim->duration <= frame) {
                finished++;
                anim->alpha = FLOAT_80332e64;
                anim->dx = FLOAT_80332e60;
                anim->dy = FLOAT_80332e60;
            } else {
                anim->frame++;
                double one = DOUBLE_80332e68;
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
    unsigned int count;
    unsigned int blocks;
    int index;
    MenuItemOpenAnim* entry;
    ItemMenuAnimList* itemList;

    index = 0;
    entry = GetItemOpenAnim(this, index++);
    entry->tex = 0x2E;
    entry->startFrame = 2;
    entry->duration = 5;
    entry = GetItemOpenAnim(this, index++);
    entry->tex = 0x47;
    entry->startFrame = 7;
    entry->duration = 5;
    entry = GetItemOpenAnim(this, index++);
    entry->tex = 0x47;
    entry->startFrame = 7;
    entry->duration = 5;
    entry = GetItemOpenAnim(this, index++);
    entry->flags = 2;
    entry->tex = 0x2E;
    entry->startFrame = 7;
    entry->duration = 5;
    entry = GetItemOpenAnim(this, index++);
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = GetItemOpenAnim(this, index++);
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = GetItemOpenAnim(this, index++);
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = GetItemOpenAnim(this, index++);
    entry->flags = 2;
    entry->tex = 0x37;
    progress = FLOAT_80332e64;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = GetItemOpenAnim(this, index++);
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = GetItemOpenAnim(this, index++);
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = GetItemOpenAnim(this, index++);
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    entry = GetItemOpenAnim(this, index);
    entry->flags = 2;
    entry->tex = 0x37;
    entry->startFrame = 0;
    entry->duration = 5;
    itemList = GetItemOpenAnimList(this);
    count = (unsigned int)itemList->count;
    entry = itemList->anims;
    if (0 < (int)count) {
        blocks = count >> 3;
        if (blocks != 0) {
            do {
                entry[0].frame = 0;
                entry[0].alpha = progress;
                entry[1].frame = 0;
                entry[1].alpha = progress;
                entry[2].frame = 0;
                entry[2].alpha = progress;
                entry[3].frame = 0;
                entry[3].alpha = progress;
                entry[4].frame = 0;
                entry[4].alpha = progress;
                entry[5].frame = 0;
                entry[5].alpha = progress;
                entry[6].frame = 0;
                entry[6].alpha = progress;
                entry[7].frame = 0;
                entry[7].alpha = progress;
                entry += 8;
                blocks--;
            } while (blocks != 0);
            count &= 7;
        }
        if (count != 0) {
            do {
                entry->frame = 0;
                entry->alpha = progress;
                entry++;
                count--;
            } while (count != 0);
        }
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
    short yOffset;
    short count;
    MenuItemOpenAnim* entry;
    ItemMenuAnimList* itemList;

    memset(this->itemList, 0, sizeof(*this->itemList));
    float one = FLOAT_80332e64;
    entry = this->itemList->anims;
    int initCount = 8;
    do {
        entry[0].uvScale = one;
        entry[1].uvScale = one;
        entry[2].uvScale = one;
        entry[3].uvScale = one;
        entry[4].uvScale = one;
        entry[5].uvScale = one;
        entry[6].uvScale = one;
        entry[7].uvScale = one;
        entry += 8;
        initCount--;
    } while (initCount != 0);

    index = 0;
    entry = GetItemOpenAnim(this, index++);
    entry->tex = 0x2E;
    entry->x = 0x68;
    entry->y = 0x28;
    entry->w = 0x78;
    entry->h = 0x108;
    float titleAlpha = FLOAT_80332EA8;
    float titleScale = FLOAT_80332EAC;
    float zero = FLOAT_80332e60;
    entry->u = titleAlpha;
    entry->v = titleScale;
    entry->uvScale = one;
    count = 4;
    entry->startFrame = 5;
    entry->duration = 5;

    entry = GetItemOpenAnim(this, index++);
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

    entry = GetItemOpenAnim(this, index++);
    entry->tex = 0x47;
    entry->x = 0x55;
    entry->w = 0x30;
    entry->h = 0x30;
    entry->y = 0x150 - entry->h;
    float rightUvScale = FLOAT_80332EB0;
    entry->u = zero;
    entry->v = zero;
    entry->uvScale = rightUvScale;
    entry->startFrame = 0;
    entry->duration = 5;

    entry = GetItemOpenAnim(this, index++);
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

    itemList = this->itemList;
    yOffset = 0;
    int listOffset = 0x100;
    int loopCount = 4;
    do {
        entry = reinterpret_cast<MenuItemOpenAnim*>(reinterpret_cast<unsigned char*>(this->itemList) + listOffset + 8);
        entry->flags = 2;
        entry->tex = 0x37;
        count = count + 2;
        entry->x = itemList->anims[0].x + 0x24;
        short nextY = yOffset + 0x20;
        entry->y = itemList->anims[0].y + yOffset;
        entry->w = 200;
        entry->h = 0x28;
        entry->u = zero;
        entry->v = zero;
        entry->startFrame = 7;
        entry->duration = 5;

        int secondOffset = listOffset + 0x48;
        listOffset = listOffset + 0x80;
        entry = reinterpret_cast<MenuItemOpenAnim*>(reinterpret_cast<unsigned char*>(this->itemList) + secondOffset);
        entry->flags = 2;
        entry->tex = 0x37;
        entry->x = itemList->anims[0].x + 0x24;
        yOffset = yOffset + 0x40;
        entry->y = itemList->anims[0].y + nextY;
        entry->w = 200;
        entry->h = 0x28;
        entry->u = zero;
        entry->v = zero;
        entry->startFrame = 7;
        entry->duration = 5;
        loopCount--;
    } while (loopCount != 0);

    this->itemList->count = count;
    this->itemMenuState->selectedIndex = 0;
    this->itemMenuState->initialized = 1;
}
