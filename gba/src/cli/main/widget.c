#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "session.h"
#include "window.h"
#include "screen.h"

static inline u32 GetBgVram(s32 bg)
{
    if (bg != 0) {
        if (bg != 1)
            return 0x06008000;
    }
    return 0x06000000;
}

void MsgBox_Layout(void)
{
    struct Window *win = &gWindows[4];
    s32 max;
    s32 n;
    s32 i;
    s32 len;
    s32 w;

    win->active = 1;
    win->style = -1;
    win->variant = 0;
    win->bg = 0;
    win->slot = 4;
    win->textX = 0;
    Text_Clear();
    max = 0;
    len = 0;
    n = 0;
    for (i = 0; i <= 10; i++, n++) {
        if (win->items[i].text == 0)
            break;
        len = strlen(win->items[i].text);
        if (len == 0)
            break;
        len = Text_Print(win->items[i].text, TEXT_WIDTH);
        if (len > max)
            max = len;
    }
    if (max & 7)
        max += 8;
    w = max >> 3;
    win->rows = n + 1;
    win->height = (n + 1) * 2 + 2;
    win->y = (20 - win->height) >> 1;
    max = w << 3;
    win->width = w + 2;
    win->x = (30 - win->width) >> 1;
    win->textX = (max - len) / 2;
}

s32 MsgBox_Open(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[4];

    Text_SetFill(1, 1);
    Text_Clear();
    Window_PrintNextItem(win);
    Window_Open(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = 0;
        ret = 1;
    }
    return ret;
}

s32 MsgBox_WaitKey(void)
{
    s32 ret;

    if (gKeysNew & (A_BUTTON | B_BUTTON)) {
        m4aSongNumStart(2);
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

s32 MsgBox_Close(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[4];

    Window_Close(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = 0;
        ret = 1;
    }
    return ret;
}

void CMake_Reset(void)
{
    memset(&gCMakeData, 0, sizeof(gCMakeData));
    gCMakeData.favorites[0] = 0x10;
    gCMakeData.favorites[1] = 0x32;
    gCMakeData.favorites[2] = 0x54;
    gCMakeData.favorites[3] = 0x76;
}

u32 Window_GetTextVram(struct Window *win, s32 row, s32 half)
{
    u32 addr = GetBgVram(win->bg);
    s32 n;

    if (win->slot == 0)
        addr += 0x1000;
    else if (win->slot == 1)
        addr += 0x2B80;
    else if (win->slot == 2)
        addr += 0x4700;
    else if (win->slot == 3)
        addr += 0x5380;
    else
        addr = 0x06006800;
    n = 1;
    if (half == 0)
        n = 2;
    addr += win->width * 32 * n * row;
    return addr;
}

void StatusWin_Setup(s32 idx, s32 bg)
{
    struct Window *win = &gWindows[idx];

    DmaClear32(0, 0, win, sizeof(struct Window));
    win->active = 1;
    win->x = 20;
    win->y = 1;
    win->rows = 6;
    win->width = 10;
    win->height = 14;
    win->style = win->height;
    win->variant = 0;
    win->bg = bg;
    win->slot = idx;
    win->skipRows = 0;
    Window_ResetItems(win, 0);
}

s32 StatusWin_Open(s32 idx)
{
    struct Window *win = &gWindows[idx];
    s32 row;
    u32 addr;
    s32 n;
    s32 x;

    Text_SetFill(1, 0);
    Text_Clear();
    row = win->anim >> 3;
    if (row == 0) {
        Window_PutText(win, 0, 0);
    } else if (row <= win->rows) {
        row--;
        if (row <= 2) {
            Text_Print(Msg_GetSystem(row + 6), TEXT_DRAW);
            n = gSession.stats[row];
            x = win->width * 8 - 34;
            Text_PrintNumber(n, x, 2);
        } else if (row == 4) {
            addr = Window_GetTextVram(win, 4, 0);
            Text_Print(Msg_GetSystem(1), TEXT_DRAW);
            Text_CopyToVram(addr, win->width);
        } else if (row == 5) {
            n = gSession.memories;
            x = win->width * 8 - 43;
            Text_PrintNumber(n, x, 3);
        }
        Window_PutText(win, row, 0);
        row++;
    }
    Window_Open(win);
    if (row == 0)
        win->skipRows = 1;
    else if (row > 6)
        win->skipRows = 0;
    if (row < win->height - 2) {
        win->anim += 8;
        return 0;
    }
    return 1;
}

void StatusWin_Refresh(s32 idx)
{
    struct Window *win = &gWindows[idx];
    s32 i;
    s32 n;
    s32 x;

    Text_SetFill(1, 0);
    for (i = 0; i <= 2; i++) {
        Text_Clear();
        Text_Print(Msg_GetSystem(i + 6), TEXT_DRAW);
        n = gSession.stats[i];
        x = win->width * 8 - 34;
        Text_PrintNumber(n, x, 2);
        Text_CopyToVram(Window_GetTextVram(win, i, 0), win->width);
    }
    Text_Clear();
    n = gSession.memories;
    x = win->width * 8 - 43;
    Text_PrintNumber(n, x, 3);
    Window_PutText(win, 5, 0);
    Text_CopyToVram(Window_GetTextVram(win, 5, 0), win->width);
}

void StatusWin_DrawIcon(s32 idx)
{
    struct Window *win = &gWindows[idx];
    s32 x = win->x + 3;
    s32 y = win->y + win->height - 3;

    x *= 8;
    y *= 8;
    Obj_Draw(x, y, 0, 47, Obj_GetPalette(0, 47), win->bg, 0);
}

void BonusWin_Setup(s32 idx)
{
    struct Window *win = &gWindows[idx];
    s32 i;

    DmaClear32(0, 0, win, sizeof(struct Window));
    win->active = 1;
    win->x = 0;
    win->y = 0;
    win->rows = 2;
    win->width = 30;
    win->height = 2;
    win->style = 0;
    win->variant = 0;
    win->bg = 0;
    win->slot = idx;
    Text_SetFill(0, 0);
    for (i = 0; i <= 1; i++) {
        Text_Clear();
        Text_SetX(8);
        Text_Print(gBonusStr[i], TEXT_DRAW);
        Window_PutText(win, i, 0);
    }
}

void BonusWin_Show(s32 idx, s32 pal)
{
    struct Window *win = &gWindows[idx];
    u16 buf[30];
    s32 i;
    s32 j;
    s32 tile;
    s32 blank;
    u32 dst;

    pal <<= 12;
    blank = 0x3FF;
    for (i = 0; i <= 3; i++) {
        for (j = 0; j < 30; j++)
            buf[j] = blank;
        tile = Window_GetTextTile(win->slot);
        j = i >> 1;
        tile += win->width * 2 * j;
        tile += i & 1;
        for (j = 0; j < win->width; j++) {
            if (j & 1) {
                buf[j] = (tile + 2) | pal;
                tile += 4;
            } else {
                buf[j] = pal | tile;
            }
        }
        dst = (u32)Bg_GetMapPtr(win->bg, 0, 16 + i);
        DmaCopy16(0, buf, dst, win->width << 1);
    }
}

void BonusWin_Hide(s32 bg)
{
    Bg_FillBlank(bg, 0, 16, 30, 4);
}

void Window_DrawSlotRow(s32 idx, s32 mode, s32 row)
{
    struct Window *win = &gWindows[idx];
    u16 buf[30];
    s32 pal;
    s32 y;
    s32 base;
    s32 i;
    s32 j;
    s32 off;
    s32 w;
    u32 dst;

    if (mode <= 1)
        pal = 1;
    else
        pal = (mode >> 1) + 1;
    pal <<= 12;
    y = win->y + row * 2;
    base = Window_GetFrameTile(win->slot) + 4;
    for (i = 0; i <= 1; i++) {
        if (mode < 0)
            off = 0;
        else if (mode & 1)
            off = 10;
        else
            off = 0;
        off += i + base;
        for (j = 0; j < win->width; j++) {
            if (j == 0) {
                if (mode < 0)
                    buf[j] = off + 16;
                else
                    buf[j] = off;
            } else if (mode <= 0) {
                if (j < win->width - 1) {
                    if (mode != 0)
                        buf[j] = off + 6;
                    else
                        buf[j] = off + 2;
                } else {
                    if (mode != 0)
                        buf[j] = off + 8;
                    else
                        buf[j] = off + 18;
                }
            } else {
                w = win->width - 3;
                if (j < w)
                    buf[j] = off + 2;
                else if (j == w)
                    buf[j] = off + 4;
                else if (j == win->width - 2)
                    buf[j] = i + base + 6;
                else
                    buf[j] = i + base + 8;
            }
            buf[j] |= pal;
        }
        dst = (u32)Bg_GetMapPtr(win->bg, win->x, y + i);
        DmaCopy16(0, buf, dst, win->width << 1);
    }
}

void Window_ClearRow(s32 idx, s32 row)
{
    struct Window *win = &gWindows[idx];
    s32 y = win->y + row * 2;

    Bg_FillBlank(win->bg, win->x, y, win->width, 2);
}

void Bg_FillBlank(s32 bg, s32 x, s32 y, s32 w, s32 h)
{
    u16 buf[30];
    u16 fill;
    u32 dst;
    s32 i;

    fill = 0x2FF;
    if (bg <= 1)
        fill = 0x3FF;
    for (i = 0; i < 30; i++)
        buf[i] = fill;
    dst = (u32)Bg_GetMapPtr(bg, x, y);
    for (i = 0; i < h; i++) {
        DmaCopy16(0, buf, dst, w << 1);
        dst += 64;
    }
}

s32 Window_GetRowTile(struct Window *win, s32 row)
{
    return Window_GetTextTile(win->slot) + (win->width << 1) * row;
}

void Window_PutRowAt(struct Window *win, s32 bg, s32 row, s32 x, s32 y, s32 pal)
{
    u16 buf[30];
    s32 i;
    s32 j;
    s32 tile;
    u32 dst;

    Window_GetTextVram(win, row, 0);
    pal <<= 12;
    for (i = 0; i <= 1; i++) {
        tile = Window_GetRowTile(win, row) + i;
        for (j = 0; j < win->width; j++) {
            if (j & 1) {
                buf[j] = (tile + 2) | pal;
                tile += 4;
            } else {
                buf[j] = pal | tile;
            }
        }
        dst = (u32)Bg_GetMapPtr(bg, x, y + i);
        DmaCopy16(0, buf, dst, win->width << 1);
    }
}

void Window_ScrollRows(s32 dir, s32 idx, s32 bg)
{
    struct Window *win = &gWindows[idx];
    s32 step;
    s32 y0;
    s32 y1;
    u32 src;
    u32 dst;
    s32 i;
    s32 j;

    step = 64;
    if (dir) {
        y1 = win->rows * 2;
        y0 = y1 - 2;
        step = -step;
    } else {
        y0 = 3;
        y1 = 1;
    }
    y0 += win->y;
    y1 += win->y;
    src = (u32)Bg_GetMapPtr(bg, win->x + 1, y0);
    dst = (u32)Bg_GetMapPtr(bg, win->x + 1, y1);
    for (i = 0; i < win->rows - 1; i++) {
        for (j = 0; j < 2; j++) {
            DmaCopy16(0, src, dst, (win->width - 2) << 1);
            src += step;
            dst += step;
        }
    }
}

void Window_DrawRow(s32 idx, s32 bg, s32 row, s32 y, s32 pal)
{
    struct Window *win = &gWindows[idx];
    u16 buf[30];
    s32 w;
    s32 i;
    s32 j;
    s32 tile;
    u32 dst;
    s32 ty;

    pal <<= 12;
    ty = win->y + 1 + y * 2;
    w = win->width - 2;
    for (i = 0; i <= 1; i++) {
        tile = Window_GetTextTile(win->slot);
        tile += (win->width << 1) * row;
        tile += i;
        for (j = 0; j < w; j++) {
            if (!(j & 1)) {
                buf[j] = pal | tile;
            } else {
                buf[j] = (tile + 2) | pal;
                tile += 4;
            }
        }
        dst = (u32)Bg_GetMapPtr(bg, win->x + 1, ty + i);
        DmaCopy16(3, buf, dst, w << 1);
    }
}

void Window_ResetItems(struct Window *win, s32 val)
{
    s32 i;

    for (i = 0; i < win->rows; i++) {
        win->items[i].enabled = val;
        win->items[i].text = Msg_GetSystem(0);
    }
}

void Window_DrawScrollArrows(s32 idx, s32 bg, s32 flags)
{
    struct Window *win = &gWindows[idx];
    s32 x;
    s32 y;
    s32 cell;
    s32 anim;
    s32 i;
    u32 attr;

    x = (win->x + win->width - 2) * 8;
    cell = Obj_GetPalette(0, 46);
    anim = (gFrameCount & 8) >> 2;
    for (i = 0; i <= 1; i++) {
        if ((flags >> i) & 1) {
            if (i == 0) {
                attr = 0;
                y = (win->y + 1) * 8;
                y += anim;
            } else {
                attr = 0x20000000;
                y = (win->y + win->height - 3) * 8;
                y -= anim;
            }
            Obj_Draw(x, y, 0, 46, cell, bg, attr);
        }
    }
}

void ListWin_Setup(s32 idx, s32 x, s32 w, s32 bg)
{
    struct Window *win = &gWindows[idx];

    DmaClear32(0, 0, win, sizeof(struct Window));
    win->active = 1;
    win->x = x;
    win->y = 0;
    win->rows = 8;
    win->width = w ? w : 14;
    win->height = 18;
    win->style = 0;
    win->variant = 0;
    win->bg = bg;
    win->slot = idx;
    win->skipRows = 0;
    Window_ResetItems(win, 1);
}

void HelpWin_DrawFrame(s32 bg, s32 idx, s32 pal)
{
    u16 buf[30];
    u16 fill;
    u32 dst;
    s32 i;
    s32 j;
    s32 tile;

    fill = 0x2FF;
    if (bg <= 1)
        fill = 0x3FF;
    for (i = 0; i < 30; i++)
        buf[i] = fill;
    pal <<= 12;
    dst = (u32)Bg_GetMapPtr(bg, 1, 18);
    for (i = 0; i <= 1; i++) {
        tile = Window_GetTextTile(idx) + i;
        for (j = 0; j <= 24; j++) {
            if (j & 1) {
                buf[j] = (tile + 2) | pal;
                tile += 4;
            } else {
                buf[j] = pal | tile;
            }
        }
        DmaCopy16(3, buf, dst, 50);
        dst += 64;
    }
}

void HelpWin_CopyText(s32 bg, s32 idx)
{
    u32 off;
    u32 base;

    if (idx == 0)
        off = 0x1000;
    else if (idx == 1)
        off = 0x2B80;
    else if (idx == 2)
        off = 0x4700;
    else
        off = 0x5380;
    base = 0x06000000;
    if (bg != 0) {
        if (bg != 1)
            base = 0x06008000;
    }
    Text_CopyToVram(off + base, 25);
}

void HelpWin_Clear(s32 bg, s32 idx)
{
    u16 buf[30];
    struct Window *win;
    s32 val;
    u32 dst;
    s32 i;

    val = 0x2FF;
    if (bg <= 1)
        val = 0x3FF;
    for (i = 0; i < 30; i++)
        buf[i] = val;
    win = &gWindows[idx];
    val = win->bg;
    win->bg = bg;
    dst = (u32)Bg_GetMapPtr(bg, 0, 18);
    win->bg = val;
    for (i = 0; i < 2; i++) {
        DmaCopy16(0, buf, dst, 60);
        dst += 64;
    }
    Text_SetFill(0, 0);
    Text_Clear();
    HelpWin_CopyText(bg, idx);
}

s32 MsgScreen_Init(void)
{
    if (!(gDataFlags & DATA_OBJ))
        return 0;
    if (gScreenInitDone == 0) {
        DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
        Text_SetFill(1, 0);
        Text_LoadPalette(3, 0, 1);
        Obj_LoadToBg(12, 4, 0, 0);
        Text_LoadPalette(15, 0, 1);
        Text_CopyFill(0x06006000);
        gWindows[4].items[0].text = Msg_GetNotice(gMsgScreenId);
        MsgBox_Layout();
        gScreenInitDone = 1;
    }
    return MsgBox_Open();
}

s32 MsgScreen_Main(void)
{
    return 0;
}

void Menu_OnOpen(u32 data)
{
    s32 prev = gScreen;
    struct JoyArgs *cmd = (struct JoyArgs *)&data;

    gScreen = cmd->arg;
    if (gScreen == 11) {
        if (gMode != MODE_FIELD) {
            gSavedScreen = 0;
            gMode = MODE_FIELD;
        } else {
            gSavedScreen = prev;
        }
        gMsgScreenId = 6;
    } else if (gScreen == 12) {
        gScreen = gSavedScreen;
    } else {
        gSavedScreen = gScreen;
    }
    Screen_Reset();
    Bg_ClearMaps();
}

void Header_PrintItemDesc(s32 no)
{
    char buf[68];

    Header_Clear();
    if (no > 0) {
        Msg_GetItemDesc(no, buf);
        Header_Print(buf);
    }
}

void HelpWin_PrintItemDesc(s32 no, s32 bg, s32 idx)
{
    char buf[68];

    Text_SetFill(0, 0);
    Text_Clear();
    if (no > 0) {
        Msg_GetItemDesc(no, buf);
        Text_Print(buf, TEXT_DRAW);
    }
    HelpWin_CopyText(bg, idx);
}
