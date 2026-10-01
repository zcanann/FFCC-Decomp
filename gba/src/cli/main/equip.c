#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "session.h"
#include "window.h"
#include "screen.h"
#include "lists.h"

static s8 sEquipQuit;
static s8 sEquipRow;
static s8 sEquipTop;
static s8 sEquipRowOffset;
static s8 sEquipUseFlags;

void EquipScreen_DrawCursor(void);
void EquipScreen_HandleInput(void);
void EquipScreen_PrintSlot(s32);
void EquipScreen_DrawIcons(void);
s32 EquipScreen_OpenPicker(void);
s32 EquipScreen_ClosePicker(void);
void EquipScreen_PrintCandidate(s32, s32);
s32 EquipScreen_CanUseCandidate(s32);
void EquipScreen_Unequip(void);
void EquipScreen_SetSlot(s32);
void EquipScreen_PrintDesc(void);

void EquipScreen_Setup(void)
{
    struct Window *win;

    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    StatusWin_Setup(0, 2);
    ListWin_Setup(1, 5, 15, 1);
    Window_ResetItems(&gWindows[1], 1);

    win = &gWindows[2];
    win->active = 1;
    win->x = 1;
    win->y = 2;
    win->rows = 4;
    win->width = 14;
    win->height = 11;
    win->style = 7;
    win->variant = 0;
    win->bg = 2;
    win->slot = 2;
    win->textX = 0;
    Window_ResetItems(win, 1);

    Text_SetFill(1, 0);
    Text_Clear();
    Text_LoadPalette(3, 0, 0);
    Text_LoadPalette(4, 0, 0);
    Text_LoadPalette(5, 0, 0);
    Text_LoadPalette(6, 2, 0);
    Font_LoadPalette(0x050000E0, 1);
    Text_CopyFill(0x06008000);
    Text_CopyFill(0x06008800);
    Text_CopyFill(0x06000400);
    Obj_AllocPalette(17, 0);
    Obj_AllocPalette(3, 0);
    Obj_AllocPalette(10, 0);
    Obj_LoadToBg(17, 0, 2, 0);
    Obj_LoadToBg(3, 1, 1, 0);
    Obj_LoadToBg(10, 2, 2, 0);
    HelpWin_Clear(2, 1);
    HelpWin_DrawFrame(2, 1, 7);
    sEquipTop = 0;
    sEquipQuit = 0;
    sEquipRow = 0;
    gSubMode = 0;
    gSubState = 0;
    sEquipRowOffset = 0;
    gScreenInitDone = 1;
}

s32 EquipScreen_Init(void)
{
    s32 ret;
    struct Window *win;

    if (gScreenInitDone == 0)
        EquipScreen_Setup();
    ret = StatusWin_Open(0);
    win = &gWindows[2];
    Text_SetFill(1, 0);
    Text_Clear();
    Window_PrintNextItem(win);
    Window_Open(win);
    if ((win->anim >> 3) < win->height - 2)
        win->anim += 8;
    if (ret) {
        win->anim = 0;
        sEquipUseFlags = gItemUseFlags;
    }
    return ret;
}

s32 EquipScreen_Main(void)
{
    struct Window *win;
    s32 ret;

    StatusWin_DrawIcon(0);
    win = &gWindows[2];
    Window_Nop(win);
    if (!(gDataFlags & DATA_EQUIP_LIST) && (gKeysNew & B_BUTTON)) {
        sEquipQuit = 1;
        gOpenMenuReq = 1;
        m4aSongNumStart(3);
        return 1;
    }
    if (sEquipRow < win->rows) {
        EquipScreen_PrintSlot(sEquipRow);
        sEquipRow++;
        if (sEquipRow < win->rows)
            return 0;
        EquipScreen_PrintDesc();
    }
    if (sEquipUseFlags != gItemUseFlags && gSubMode)
        gSubState = 2;
    if (gSubMode == 1 && gSubState == 0) {
        ret = EquipScreen_OpenPicker();
        if (ret) {
            gSubState++;
            gWindows[2].anim = 0;
        }
    } else if (!gSubMode || gSubState == 1) {
        if (gMenuHasInput)
            EquipScreen_HandleInput();
        else if (gSubMode)
            gSubState++;
    } else if (gSubMode == 1 && gSubState == 2) {
        ret = EquipScreen_ClosePicker();
        if (ret) {
            gSubState = 0;
            gSubMode--;
            EquipScreen_PrintDesc();
        }
    }
    EquipScreen_DrawIcons();
    if (gMenuHasInput)
        EquipScreen_DrawCursor();
    ret = sEquipQuit != 0;
    if (!gSubMode || gSubState == 1)
        sEquipUseFlags = gItemUseFlags;
    if (ret)
        HelpWin_Clear(2, 1);
    return ret;
}

s32 EquipScreen_Exit(void)
{
    struct Window *win = gWindows;
    s32 ret;

    Window_Close(win);
    Window_Close(win + 2);
    ret = 0;
    if ((win->anim >> 3) >= win->height - 1) {
        ret = 1;
        Obj_FreePalette(17);
        Obj_FreePalette(3);
        Obj_FreePalette(10);
        win->anim = 0;
        win[2].anim = 0;
    } else {
        win->anim += 8;
        win[2].anim += 8;
    }
    if (!ret && (win[2].anim >> 3) < win[2].height - 2)
        Window_Nop(&win[2]);
    return ret;
}

void EquipScreen_DrawCursor(void)
{
    struct Window *win;
    s32 x;
    s32 y;
    s32 pal = Obj_GetPalette(0, 45);

    if (!gSubMode || (gFrameCount & 2)) {
        win = &gWindows[2];
        x = (win->x - 1) * 8;
        y = (win->y + 2) * 8;
        y += win->cursor * 16;
        Obj_Draw(x, y, 0, 45, pal, win->bg, 0);
    }
    if (gSubMode == 1 && gSubState == 1) {
        win = &gWindows[1];
        x = (win->x - 1) * 8;
        y = (win->y + 1) * 8;
        y += win->cursor * 16;
        Obj_Draw(x, y, 0, 45, pal, win->bg, 0);
    }
}

void EquipScreen_HandleInput(void)
{
    u8 *list;
    struct Window *win;
    s32 n;
    s32 idx;
    s32 row;
    s32 pal;

    if (gKeysRepeat == 0)
        return;
    list = DETAIL_BUF;
    if (gSubMode == 0) {
        win = &gWindows[2];
        n = win->rows;
    } else {
        win = &gWindows[1];
        n = list[0];
        n++;
    }
    list++;
    if (gKeysRepeat & DPAD_UP) {
        if (gSubMode == 0) {
            if (win->cursor != 0) {
                win->cursor--;
                m4aSongNumStart(1);
            } else {
                win->cursor = n - 1;
            }
            EquipScreen_PrintDesc();
            m4aSongNumStart(1);
        } else if (win->cursor != 0) {
            win->cursor--;
            EquipScreen_PrintDesc();
            m4aSongNumStart(1);
        } else if (sEquipTop == 0) {
            m4aSongNumStart(0);
        } else {
            Window_ScrollRows(1, 1, win->bg);
            idx = sEquipTop - 1;
            row = idx + sEquipRowOffset;
            EquipScreen_PrintCandidate(idx, row % win->rows);
            pal = EquipScreen_CanUseCandidate(idx) ? 5 : 6;
            Window_DrawRow(1, win->bg, row % win->rows, 0, pal);
            sEquipTop--;
            EquipScreen_PrintDesc();
            m4aSongNumStart(1);
        }
    } else if (gKeysRepeat & DPAD_DOWN) {
        if (gSubMode == 0) {
            if (win->cursor < win->rows - 1)
                win->cursor++;
            else
                win->cursor = 0;
            EquipScreen_PrintDesc();
            m4aSongNumStart(1);
        } else if (win->cursor < win->rows - 1) {
            win->cursor++;
            EquipScreen_PrintDesc();
            m4aSongNumStart(1);
        } else if (sEquipTop + win->rows >= n) {
            m4aSongNumStart(0);
        } else {
            Window_ScrollRows(0, 1, win->bg);
            idx = sEquipTop + win->rows;
            row = idx + sEquipRowOffset;
            EquipScreen_PrintCandidate(idx, row % win->rows);
            pal = EquipScreen_CanUseCandidate(idx) ? 5 : 6;
            Window_DrawRow(1, win->bg, row % win->rows, win->rows - 1, pal);
            sEquipTop++;
            EquipScreen_PrintDesc();
            m4aSongNumStart(1);
        }
    }
    if (gKeysRepeat & (DPAD_UP | DPAD_DOWN))
        return;
    if (gKeysNew & A_BUTTON) {
        if (gSubMode == 0) {
            if (!(gItemUseFlags & 2)) {
                m4aSongNumStart(0);
                return;
            }
            gSubMode = 1;
            gSubState = 0;
        } else {
            idx = sEquipTop + win->cursor;
            if (!EquipScreen_CanUseCandidate(idx)) {
                m4aSongNumStart(0);
                return;
            }
            if (idx == 0)
                EquipScreen_Unequip();
            else
                EquipScreen_SetSlot(*(list + idx - 1));
            EquipScreen_PrintSlot(win[1].cursor);
            gSubState++;
        }
        m4aSongNumStart(2);
    } else if (gKeysNew & B_BUTTON) {
        if (gSubMode == 0) {
            sEquipQuit = 1;
            gOpenMenuReq = 1;
        } else {
            gSubState++;
        }
        m4aSongNumStart(3);
    } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
        if (gSubMode) {
            m4aSongNumStart(0);
        } else {
            if (gKeysNew & R_BUTTON)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            m4aSongNumStart(6);
            sEquipQuit = 1;
        }
    }
}

void EquipScreen_PrintSlot(s32 row)
{
    struct Window *win = &gWindows[2];

    Text_SetFill(1, 0);
    Text_Clear();
    Text_SetX(16);
    if ((s8)gSession.equipment[row] >= 0)
        Text_Print(Msg_GetItemName(gSession.items[(s8)gSession.equipment[row]]), TEXT_DRAW);
    Text_CopyToVram(Window_GetTextVram(win, row, 0), win->width);
}

void EquipScreen_DrawIcons(void)
{
    struct Window *win = &gWindows[2];
    s32 x;
    s32 y;
    s32 i;
    s32 id;
    s32 icon;
    s32 pal;
    s32 n;
    s8 *list;
    s32 idx;
    s32 flags;

    x = (win->x + 1) * 8;
    y = (win->y + 2) * 8;
    for (i = 0; i < win->rows; i++, y += 16) {
        id = (s8)gSession.equipment[i];
        if (id >= 0) {
            id = gSession.items[id];
            icon = Item_GetIcon(id);
            pal = Obj_GetPalette(0, icon);
            Obj_Draw(x, y, 0, icon, pal, win->bg, 0);
        }
    }
    if (gSubMode == 1 && gSubState == 1) {
        win = &gWindows[1];
        x = (win->x + 2) * 8;
        y = (win->y + 1) * 8;
        list = (s8 *)DETAIL_BUF;
        n = *list++;
        n++;
        for (i = 0; i < win->rows; i++, y += 16) {
            idx = i + sEquipTop;
            if (idx == 0)
                continue;
            if (idx >= n)
                break;
            id = *(list + idx - 1);
            id = gSession.items[id];
            icon = Item_GetIcon(id);
            pal = Obj_GetPalette(0, icon);
            Obj_Draw(x, y, 0, icon, pal, win->bg, 0);
        }
        x = (win->x + 1) * 8;
        y = (win->y + 1) * 8;
        if ((gLanguage & 15) == 1)
            icon = 24;
        else
            icon = 4;
        pal = Obj_GetPalette(2, icon);
        for (i = 0; i < win->rows; i++, y += 16) {
            idx = i + sEquipTop;
            if (idx == 0)
                continue;
            if (idx >= n)
                break;
            id = *(list + idx - 1);
            if (Session_IsItemInUse(id))
                Obj_Draw(x, y + 4, 2, icon, pal, win->bg, 0);
        }
        flags = sEquipTop != 0;
        if (sEquipTop + win->rows < n)
            flags |= 2;
        Window_DrawScrollArrows(1, win->bg, flags);
    }
}

s32 EquipScreen_OpenPicker(void)
{
    struct Window *win = &gWindows[1];
    s32 row;
    s32 ret;

    Text_SetFill(1, 0);
    Text_Clear();
    row = win->anim >> 3;
    if (row < win->rows) {
        EquipScreen_PrintCandidate(row + sEquipTop, row);
        win->items[row].enabled = EquipScreen_CanUseCandidate(row + sEquipTop);
    }
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) >= win->height - 2) {
        win->anim = ret;
        EquipScreen_PrintDesc();
        sEquipRowOffset = win->rows - sEquipTop % win->rows;
        ret = 1;
    } else {
        win->anim += 8;
    }
    return ret;
}

s32 EquipScreen_ClosePicker(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[1];

    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 1) {
        win->anim = ret;
        ret = 1;
    } else {
        win->anim += 8;
    }
    return ret;
}

void EquipScreen_PrintCandidate(s32 idx, s32 row)
{
    struct Window *win;
    u8 *list = DETAIL_BUF;
    s32 n = *list++;
    const char *str;
    s32 id;

    n++;
    win = &gWindows[1];
    Text_SetFill(1, 0);
    Text_Clear();
    Text_SetX(24);
    if (idx == 0) {
        str = Msg_GetSystem(10);
    } else if (idx >= n) {
        str = Msg_GetSystem(0);
    } else {
        id = DETAIL_BUF[idx];
        id = gSession.items[id];
        if (id > 0)
            str = Msg_GetItemName(id);
        else
            str = Msg_GetSystem(0);
    }
    Text_Print(str, TEXT_DRAW);
    Window_PutText(win, row, 0);
}

s32 EquipScreen_CanUseCandidate(s32 idx)
{
    s32 slot = gWindows[2].cursor;
    u8 *list = DETAIL_BUF;
    s32 n = *list++;
    s32 size;
    struct ItemInfo *item;
    s32 mask;

    if (idx - 1 >= n)
        return 0;
    if (idx == 0) {
        if (slot <= 2)
            return 0;
        return (s8)gSession.equipment[slot] >= 0;
    }
    if (Session_IsItemInUse(list[idx - 1]))
        return 0;
    size = n + 1;
    if (size & 3)
        size = ((size >> 2) + 1) << 2;
    item = (struct ItemInfo *)(DETAIL_BUF + size);
    item += idx - 1;
    if (!Item_CanEquip((u16 *)item))
        return 0;
    mask = 0x100;
    if (slot != 0) {
        mask = 0x400;
        if (slot != 1) {
            mask = 0x3000;
            if (slot == 2)
                mask = 0xA00;
        }
    }
    return (item->flags & mask) != 0;
}

void EquipScreen_Unequip(void)
{
    gSession.equipment[3] = -1;
    Link_SendEquipSlot(3, 0xFF);
}

void EquipScreen_SetSlot(s32 id)
{
    s32 slot = gWindows[2].cursor;

    gSession.equipment[slot] = id;
    Link_SendEquipSlot(slot, id);
}

void EquipScreen_PrintDesc(void)
{
    struct Window *win;
    s8 *list;
    struct ItemInfo *item;
    s32 n;
    s32 mode;
    s32 idx;
    s32 i;
    s8 id;
    s32 size;
    s32 msg;
    s32 x;
    s32 digits;

    Text_SetFill(0, 0);
    Text_Clear();
    mode = gSubMode;
    i = 1;
    if (mode == 0)
        i = 2;
    win = &gWindows[i];
    list = (s8 *)DETAIL_BUF;
    n = *list++;
    if (mode == 0) {
        id = (s8)gSession.equipment[win->cursor];
        for (i = 0; i < n; i++) {
            if (id == list[i])
                break;
        }
        idx = -1;
        if (i < n)
            idx = i;
    } else {
        i = sEquipTop + win->cursor;
        if (i > 0) {
            idx = i - 1;
            if (idx >= n)
                idx = -1;
        } else {
            idx = -1;
        }
    }
    if (idx < 0)
        goto end;
    size = n + 1;
    if (size & 3)
        size = ((size >> 2) + 1) << 2;
    list += size - 1;
    item = (struct ItemInfo *)list + idx;
    if (item->flags & 0x100)
        Text_Print(Msg_GetSystem(16), TEXT_DRAW);
    else if (item->flags & 0xE00)
        Text_Print(Msg_GetSystem(63), TEXT_DRAW);
    if (!(item->flags & 0x3000)) {
        Text_AddX(8);
        x = Text_GetX();
        Text_PrintNumber(item->count, x, 2);
    }
    if (!(item->flags & 0x100) && item->kind != 0) {
        if (item->flags & 0xE00)
            Text_AddX(8);
        Text_Print(Msg_GetStat(item->kind - 1), TEXT_DRAW);
        if ((item->flags & 0x3000) && item->count != 0 && item->kind != 16) {
            i = Item_IsPercentKind(item->kind);
            msg = 39;
            if (i)
                msg = 40;
            Text_AddX(8);
            Text_Print(Msg_GetSystem(msg), TEXT_DRAW);
            x = Text_GetX();
            if (item->count <= 9)
                digits = 1;
            else if (item->count <= 99)
                digits = 2;
            else
                digits = 3;
            Text_PrintNumber(item->count, x, digits);
        }
    }
end:
    HelpWin_CopyText(2, 1);
}
