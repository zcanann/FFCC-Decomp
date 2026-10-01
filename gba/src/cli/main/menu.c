#include "global.h"
#include "link.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "window.h"
#include "screen.h"

static s8 sMenuRow;
static u8 sMenuReturn;

void MenuScreen_DrawCursor(void);
void MenuScreen_DrawIcons(void);
s32 MenuScreen_HandleInput(void);
void MenuScreen_PrintRow(s32 page);

void MenuScreen_Setup(void)
{
    s32 i;

    gSubState = 0;
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    gWindows[0].active = 1;
    gWindows[0].cursor = sMenuReturn;
    gWindows[0].x = 2;
    gWindows[0].y = 2;
    gWindows[0].rows = 5;
    gWindows[0].width = 26;
    gWindows[0].height = 16;
    gWindows[0].style = 1;
    gWindows[0].variant = 0;
    gWindows[0].bg = 2;
    gWindows[0].slot = 0;
    gWindows[0].textX = 0;
    gWindows[0].tallRows = 1;
    for (i = 0; i < gWindows[0].rows; i++) {
        gWindows[0].items[i].enabled = 1;
        gWindows[0].items[i].text = Msg_GetSystem(0);
    }
    Text_LoadPalette(3, 0, 0);
    Text_CopyFill(0x06008000);
    Obj_AllocPalette(4, 0);
    Obj_LoadToBg(4, 0, 2, 0);
    sMenuRow = 0;
    gScreenInitDone = 1;
}

s32 MenuScreen_Init(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0)
        MenuScreen_Setup();
    win = gWindows;
    Window_PrintNextItem(win);
    Window_Open(win);
    if ((win->anim >> 3) >= win->height - 2)
        ret = 1;
    else
        win->anim += 8;
    return ret;
}

s32 MenuScreen_Main(void)
{
    s32 ret;

    if (sMenuRow <= 4) {
        MenuScreen_PrintRow(sMenuRow);
        sMenuRow++;
        return 0;
    }
    ret = 0;
    if (gMenuHasInput) {
        ret = MenuScreen_HandleInput();
        MenuScreen_DrawCursor();
    }
    MenuScreen_DrawIcons();
    return ret;
}

s32 MenuScreen_Exit(void)
{
    struct Window *win = gWindows;
    s32 ret = 0;

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 1) {
        ret = 1;
        Obj_FreePalette(4);
        win->anim = 0;
    } else {
        win->anim += 8;
    }
    return ret;
}

void MenuScreen_DrawCursor(void)
{
    s32 pal = Obj_GetPalette(0, 0x2D);
    struct Window *win = gWindows;
    s32 x = (win->x - 1) * 8;
    s32 y;
    u32 n;

    n = win->cursor / 5;
    if ((s8)n)
        x += 104;
    y = (win->y + 1) * 8;
    n = (s8)(win->cursor % 5);
    y += 24 * n;
    Obj_Draw(x, y, 0, 0x2D, pal, win->bg, 0);
}

void MenuScreen_DrawIcons(void)
{
    s32 id = 6;
    s32 pal = Obj_GetPalette(2, id);
    struct Window *win = gWindows;
    s32 x = (win->x + 1) * 8 + 4;
    s32 y = (win->y + 1) * 8 + 4;
    s32 i;

    for (i = 0; i < 10; i++, y += 24) {
        if (i == 5) {
            x += 104;
            y = (win->y + 1) * 8 + 4;
        }
        Obj_Draw(x, y, 2, id, pal, win->bg, 0);
    }
}

s32 MenuScreen_HandleInput(void)
{
    struct Window *win;
    s32 cur;
    s32 lastCol = 4;
    s32 cols = 5;
    s32 last = 9;

    if (gKeysRepeat) {
        win = gWindows;
        if (gKeysRepeat & DPAD_UP) {
            cur = win->cursor;
            if (cur % 5)
                win->cursor--;
            else
                win->cursor += 4;
            m4aSongNumStart(1);
        } else if (gKeysRepeat & DPAD_DOWN) {
            cur = win->cursor;
            if (cur % 5 < lastCol)
                win->cursor++;
            else
                win->cursor -= 4;
            m4aSongNumStart(1);
        }
        if (gKeysRepeat & (DPAD_LEFT | DPAD_RIGHT)) {
            cur = win->cursor;
            if (cur < cols)
                win->cursor += 5;
            else
                win->cursor -= 5;
            m4aSongNumStart(1);
        }
        if (!(gKeysRepeat & DPAD_ANY)) {
            if (gKeysRepeat & L_BUTTON) {
                if (win->cursor)
                    win->cursor--;
                else
                    win->cursor = 9;
                m4aSongNumStart(1);
            } else if (gKeysRepeat & R_BUTTON) {
                cur = win->cursor;
                if (cur < last)
                    win->cursor++;
                else
                    win->cursor = 0;
                m4aSongNumStart(1);
            } else if (gKeysNew & A_BUTTON) {
                m4aSongNumStart(2);
                return 1;
            } else if (gKeysNew & B_BUTTON) {
                m4aSongNumStart(0);
            }
        }
    }
    return 0;
}

void MenuScreen_PrintRow(s32 page)
{
    Text_SetFill(1, 0);
    Text_Clear();
    Text_SetX(16);
    Text_Print(Msg_GetSystem(page + 44), TEXT_DRAW);
    Text_SetX(120);
    Text_Print(Msg_GetSystem(page + 49), TEXT_DRAW);
    Text_CopyToVram(Window_GetTextVram(gWindows, page, 0), gWindows[0].width);
}

void MenuScreen_SetReturn(s32 idx)
{
    sMenuReturn = idx;
}
