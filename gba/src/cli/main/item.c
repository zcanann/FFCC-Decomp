#include "global.h"
#include "link.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "session.h"
#include "window.h"
#include "screen.h"

#define WRAP64(dst, n) \
    { \
        dst = (n) % 64; \
        if (dst < 0) \
            dst += 64; \
    }

static s32 sItemTop;
static s8 sItemQuit;
static s8 sItemRow;
static s8 sItemUnused;
static s16 sItemUnused2;

s32 ItemScreen_OpenActions(void);
s32 ItemScreen_CloseActions(void);
void ItemScreen_PrintItem(s32, s32);
void ItemScreen_PrintDesc(s32);
void ItemScreen_UpdateActions(void);
s32 ItemScreen_ActionsChanged(void);
void ItemScreen_DrawCursor(void);
void ItemScreen_HandleInput(void);
void ItemScreen_DrawIcons(void);

/*
 * --INFO--
 * PAL Address: 0x020105BC
 * PAL Size: 436b
 * EN Address: 0x020104B8
 * EN Size: 436b
 * JP Address: 0x0200F204
 * JP Size: 440b
 */
void ItemScreen_Setup(void)
{
    struct Window *win;
    s32 i;

    gSubState = 0;
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    StatusWin_Setup(0, 2);
    ListWin_Setup(1, 2, 15, 2);
    Window_ResetItems(&gWindows[1], 1);

    gWindows[2].active = 1;
#if defined(VERSION_GCCE01)
    gWindows[2].width = 7;
    gWindows[2].x = 12;
#else
    gWindows[2].width = 9;
    gWindows[2].x = 11;
#endif
    gWindows[2].y = 8;
    gWindows[2].rows = 4;
    gWindows[2].height = gWindows[2].rows * 2 + 2;
    gWindows[2].style = 3;
    gWindows[2].variant = 0;
    gWindows[2].bg = 1;
    gWindows[2].slot = 2;
    gWindows[2].textX = 0;
    Window_ResetItems(&gWindows[2], 1);
    win = &gWindows[2];
    for (i = 0; i < win->rows; i++) {
        if (i < win->rows - 1)
            win->items[i].text = Msg_GetSystem(i + 33);
        else
            win->items[i].text = Msg_GetSystem(4);
    }

    Text_SetFill(1, 0);
    Text_LoadPalette(4, 0, 0);
    Text_LoadPalette(5, 0, 0);
    Text_LoadPalette(6, 2, 0);
    Font_LoadPalette(0x050000E0, 0);
    Font_LoadPalette(0x05000100, 2);
    Font_LoadPalette(0x05000120, 1);
    Text_CopyFill(0x06008000);
    Text_CopyFill(0x06008400);
    Obj_AllocPalette(17, 0);
    Obj_AllocPalette(3, 0);
    Obj_AllocPalette(6, 0);
    Obj_LoadToBg(17, 0, 2, 0);
    Obj_LoadToBg(3, 1, 2, 0);
    Obj_LoadToBg(6, 2, 1, 0);
    HelpWin_Clear(1, 1);
    HelpWin_DrawFrame(1, 1, 9);
    sItemTop = 0;
    sItemRow = 0;
    sItemQuit = 0;
    sItemUnused = 0;
    sItemUnused2 = 1;
    gScreenInitDone = 1;
}

s32 ItemScreen_Init(void)
{
    struct Window *win;
    s32 ret;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0) {
        ItemScreen_Setup();
        if (gScreenInitDone == 0)
            return 0;
    }
    StatusWin_Open(0);
    win = &gWindows[1];
    Window_PrintNextItem(win);
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) >= win->height - 2) {
        ret = 1;
        win->anim = 0;
        HelpWin_PrintItemDesc(gSession.items[win->cursor], 1, 1);
    } else {
        win->anim += 8;
    }
    return ret;
}

s32 ItemScreen_Main(void)
{
    struct Window *win;
    s32 pal;
    s32 mode;

    StatusWin_DrawIcon(0);
    Text_SetFill(1, 0);
    Text_Clear();
    win = &gWindows[1];
    if (sItemRow < win->rows) {
        ItemScreen_PrintItem(sItemRow, sItemRow);
        pal = Session_IsItemInUse(sItemRow) ? 6 : 5;
        Window_DrawRow(1, win->bg, sItemRow, sItemRow, pal);
        sItemRow++;
        if (sItemRow < win->rows)
            return 0;
    }
    if (gSubMode && gSubState == 1 && ItemScreen_ActionsChanged()) {
        ItemScreen_UpdateActions();
        gSubState = 0;
    }
    mode = gSubMode;
    if (mode && gSubState == 0) {
        if (ItemScreen_OpenActions()) {
            gSubState++;
            gWindows[2].anim = 0;
            gWindows[2].keepFrame = 0;
        }
    } else if (!mode || gSubState == 1) {
        if (gMenuHasInput)
            ItemScreen_HandleInput();
        else if (gSubMode)
            gSubState++;
    } else if (ItemScreen_CloseActions()) {
        gSubState = 0;
        gWindows[2].anim = 0;
        gSubMode = 0;
    }
    ItemScreen_DrawIcons();
    if (gMenuHasInput)
        ItemScreen_DrawCursor();
    if (sItemQuit)
        HelpWin_Clear(1, 1);
    return sItemQuit;
}

s32 ItemScreen_Exit(void)
{
    struct Window *win = gWindows;
    s32 ret = 0;

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) < win->height - 1)
        win->anim += 8;
    win++;
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 1) {
        ret = 1;
        Obj_FreePalette(17);
        Obj_FreePalette(3);
        Obj_FreePalette(6);
        win->anim = 0;
    } else {
        win->anim += 8;
    }
    return ret;
}

void ItemScreen_DrawCursor(void)
{
    struct Window *win;
    s32 x;
    s32 y;
    s32 pal = Obj_GetPalette(0, 45);

    if (!gSubMode || (gFrameCount & 2)) {
        win = &gWindows[1];
        x = (win->x - 1) * 8;
        y = (win->y + 1) * 8;
        y += win->cursor * 16;
        Obj_Draw(x, y, 0, 45, pal, win->bg, 0);
    }
    if (gSubMode && gSubState == 1) {
        win = &gWindows[2];
        x = (win->x - 1) * 8;
        y = (win->y + 1) * 8;
        y += win->cursor * 16;
        Obj_Draw(x, y, 0, 45, pal, win->bg, 0);
    }
}

void ItemScreen_HandleInput(void)
{
    struct Window *win;
    s32 n;
    s32 idx;
    s32 pal;
    s32 type;

    if (gKeysRepeat == 0)
        return;
    win = &gWindows[1] + gSubMode;
    n = 64;
    if (gSubMode)
        n = win->rows;
    if (gKeysRepeat & DPAD_UP) {
        if (gSubMode == 0) {
            if (win->cursor != 0) {
                win->cursor--;
                ItemScreen_PrintDesc(win->cursor + sItemTop);
                m4aSongNumStart(1);
            } else {
                Window_ScrollRows(1, 1, win->bg);
                idx = (sItemTop - 1) % n;
                if (idx < 0)
                    idx += n;
                ItemScreen_PrintItem(idx, idx % win->rows);
                pal = Session_IsItemInUse(idx) ? 6 : 5;
                Window_DrawRow(1, win->bg, idx % win->rows, 0, pal);
                sItemTop--;
                ItemScreen_PrintDesc(win->cursor + sItemTop);
                m4aSongNumStart(1);
            }
        } else {
            if (win->cursor != 0)
                win->cursor--;
            else
                win->cursor = n - 1;
            m4aSongNumStart(1);
        }
    } else if (gKeysRepeat & DPAD_DOWN) {
        if (gSubMode == 0) {
            if (win->cursor < win->rows - 1) {
                win->cursor++;
                ItemScreen_PrintDesc(win->cursor + sItemTop);
                m4aSongNumStart(1);
            } else {
                Window_ScrollRows(0, 1, win->bg);
                idx = (sItemTop + win->rows) % n;
                if (idx < 0)
                    idx += n;
                ItemScreen_PrintItem(idx, idx % win->rows);
                pal = Session_IsItemInUse(idx) ? 6 : 5;
                Window_DrawRow(1, win->bg, idx % win->rows, win->rows - 1, pal);
                sItemTop++;
                ItemScreen_PrintDesc(win->cursor + sItemTop);
                m4aSongNumStart(1);
            }
        } else {
            if (win->cursor < n - 1)
                win->cursor++;
            else
                win->cursor = 0;
            m4aSongNumStart(1);
        }
    }
    if (gKeysRepeat & (DPAD_UP | DPAD_DOWN))
        return;
    if (gKeysNew & A_BUTTON) {
        if (gSubMode == 0) {
            idx = (win->cursor + sItemTop) % 64;
            if (idx < 0)
                idx += 64;
            if (gSession.items[idx] == -1 || Session_IsItemInUse(idx)) {
                m4aSongNumStart(0);
                return;
            }
            gSubMode = 1;
            gSubState = 0;
            gWindows[1].anim = 0;
            type = Session_GetItemCategory(idx);
            if (type == 7)
                gWindows[2].items[0].enabled = 1;
            else
                gWindows[2].items[0].enabled = 0;
            if (type == 1)
                gWindows[2].items[1].enabled = 0;
            else
                gWindows[2].items[1].enabled = 1;
            if (!(gItemUseFlags & 1))
                gWindows[2].items[0].enabled = 0;
            if (!(gItemUseFlags & 2))
                gWindows[2].items[1].enabled = 0;
            m4aSongNumStart(2);
        } else {
            if (win->items[win->cursor].enabled == 0) {
                m4aSongNumStart(0);
                return;
            }
            m4aSongNumStart(2);
            if (win->cursor < win->rows - 1) {
                m4aSongNumStart(2);
                idx = (gWindows[1].cursor + sItemTop) % 64;
                if (idx < 0)
                    idx += 64;
                if (win->cursor == 0)
                    Link_SendItemOp(ITEM_OP_USE, idx, 0);
                else if (win->cursor == 1)
                    Link_SendItemOp(ITEM_OP_PUT, idx, 0);
                else
                    Link_SendItemOp(ITEM_OP_DISCARD, idx, 0);
                gInputLockFrames = 6;
            }
            gSubState++;
        }
    } else if (gKeysNew & B_BUTTON) {
        if (gSubMode == 0) {
            gOpenMenuReq = 1;
            sItemQuit = 1;
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
            sItemQuit = 1;
        }
    }
}

void ItemScreen_DrawIcons(void)
{
    struct Window *win = &gWindows[1];
    s32 x;
    s32 y;
    s32 n;
    s32 i;
    s32 idx;
    s32 id;
    s32 icon;
    s32 pal;

    x = win->x * 8 + 14;
    y = (win->y + 1) * 8;
    n = win->rows;
    for (i = 0; i < n; i++, y += 16) {
        WRAP64(idx, sItemTop + i);
        id = gSession.items[idx];
        if (id > 0) {
            icon = Item_GetIcon(id);
            pal = Obj_GetPalette(0, icon);
            Obj_Draw(x, y, 0, icon, pal, 2, 0);
        }
    }
    x = (win->x + 1) * 8;
    y = (win->y + 1) * 8;
    if ((gLanguage & 15) == 1)
        icon = 24;
    else
        icon = 4;
    pal = Obj_GetPalette(2, icon);
    for (i = 0; i < win->rows; i++, y += 16) {
        WRAP64(idx, sItemTop + i);
        if (Session_IsItemInUse(idx))
            Obj_Draw(x, y + 4, 2, icon, pal, win->bg, 0);
    }
    Window_DrawScrollArrows(1, win->bg, 3);
}

void ItemScreen_RefreshItem(s32 idx)
{
    struct Window *win = &gWindows[1];
    s32 top;
    s32 bottom;
    s32 row;
    s32 pal;

    WRAP64(top, sItemTop);
    WRAP64(bottom, sItemTop + win->rows);
    if (top < bottom) {
        if (idx < top || idx >= bottom)
            return;
    } else {
        if (idx < 0 || idx >= 64)
            return;
        if (idx >= bottom && idx < top)
            return;
    }
    ItemScreen_PrintItem(idx, idx % win->rows);
    pal = Session_IsItemInUse(idx) ? 6 : 5;
    WRAP64(row, idx - sItemTop);
    Window_DrawRow(1, win->bg, idx % win->rows, row, pal);
    ItemScreen_PrintDesc(win->cursor + sItemTop);
}

s32 ItemScreen_OpenActions(void)
{
    struct Window *win = &gWindows[2];
    s32 row;
    s32 ret;

    Text_SetFill(0, 0);
    Text_Clear();
    row = win->anim >> 3;
    if (row < win->rows) {
        win->bg--;
        Text_Print(win->items[row].text, TEXT_DRAW);
        Window_PutText(win, row, 0);
        win->bg++;
    }
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) >= win->height - 1) {
        win->anim = ret;
        ret = 1;
    } else {
        win->anim += 8;
    }
    return ret;
}

s32 ItemScreen_CloseActions(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[2];

    Text_SetFill(0, 0);
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 1) {
        win->anim = ret;
        ret = 1;
    } else {
        win->anim += 8;
    }
    return ret;
}

void ItemScreen_PrintItem(s32 idx, s32 row)
{
    Text_SetFill(1, 0);
    Text_Clear();
    Text_SetX(24);
    if (gSession.items[idx] > 0)
        Text_Print(Msg_GetItemName(gSession.items[idx]), TEXT_DRAW);
    Text_CopyToVram(Window_GetTextVram(&gWindows[1], row, 0), gWindows[1].width);
}

void ItemScreen_PrintDesc(s32 idx)
{
    s32 i;

    WRAP64(i, idx);
    HelpWin_PrintItemDesc(gSession.items[i], 1, 1);
}

void ItemScreen_UpdateActions(void)
{
    struct Window *win = &gWindows[2];
    s32 idx;
    s32 type;

    WRAP64(idx, gWindows[1].cursor + sItemTop);
    type = Session_GetItemCategory(idx);
    if (type == 7)
        win->items[0].enabled = 1;
    else
        win->items[0].enabled = 0;
    if (type == 1)
        gWindows[2].items[1].enabled = 0;
    else
        gWindows[2].items[1].enabled = 1;
    if (!(gItemUseFlags & 1))
        gWindows[2].items[0].enabled = 0;
    if (!(gItemUseFlags & 2))
        gWindows[2].items[1].enabled = 0;
    win->keepFrame = 1;
}

s32 ItemScreen_ActionsChanged(void)
{
    s32 n;
    s32 type;
    s32 mask;
    s32 cur;

    n = gWindows[1].cursor + sItemTop;
    WRAP64(type, n);
    type = Session_GetItemCategory(type);
    mask = gItemUseFlags;
    if (type != 7)
        mask &= ~1;
    if (type == 1)
        mask &= ~2;
    cur = gWindows[2].items[0].enabled != 0;
    if (gWindows[2].items[1].enabled != 0)
        cur |= 2;
    if (cur != mask)
        return 1;
    return 0;
}
