#include "global.h"
#include "link.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "session.h"
#include "window.h"
#include "screen.h"

static s8 sFavoriteOrder[8];
static s8 sFavoriteRow;
static s8 sFavoriteRank;

void FavoriteScreen_PrintNextRow(void);
void FavoriteScreen_DrawRow(s32 idx);
void FavoriteScreen_DrawIcons(void);
void FavoriteScreen_DrawGauges(void);

void FavoriteScreen_Setup(void)
{
    s32 i;
    s32 j;
    s32 max;
    s32 tmp;

    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    gWindows[0].active = 1;
    gWindows[0].cursor = 0;
    gWindows[0].x = 1;
    gWindows[0].y = 0;
    gWindows[0].rows = 8;
    gWindows[0].width = 28;
    gWindows[0].height = 18;
    gWindows[0].style = 0;
    gWindows[0].variant = 1;
    gWindows[0].bg = 2;
    gWindows[0].slot = 0;
    gWindows[0].textX = 0;
    Window_ResetItems(gWindows, 1);
    Text_SetFill(1, 0);
    Text_CopyFill(0x06008000);
    Text_LoadPalette(3, 0, 0);
    Obj_AllocPalette(3, 1);
    Obj_LoadToBg(3, 0, 2, 1);
    for (i = 0; i < 8; i++)
        sFavoriteOrder[i] = i;
    for (i = 0; i < 8; i++) {
        max = gSession.favorites[sFavoriteOrder[i]];
        for (j = i + 1; j < 8; j++) {
            if (max < gSession.favorites[sFavoriteOrder[j]]) {
                tmp = sFavoriteOrder[i];
                sFavoriteOrder[i] = sFavoriteOrder[j];
                sFavoriteOrder[j] = tmp;
                max = gSession.favorites[sFavoriteOrder[i]];
            }
        }
    }
    sFavoriteRow = 0;
    sFavoriteRank = 1;
    gScreenInitDone = 1;
}

s32 FavoriteScreen_Init(void)
{
    struct Window *win;
    s32 ret;
    s32 i;

    if (gScreenInitDone == 0)
        FavoriteScreen_Setup();
    win = gWindows;
    Text_SetFill(1, 0);
    Text_Clear();
    Window_PrintNextItem(win);
    if (win->items[win->rows - 1].drawn == 0)
        return 0;
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 2) < win->width) {
        win->anim += 8;
    } else {
        for (i = 0; i < win->rows; i++)
            FavoriteScreen_DrawRow(i);
        ret = 1;
        win->anim = 0;
    }
    return ret;
}

s32 FavoriteScreen_Main(void)
{
    struct Window *win = gWindows;
    s32 ret = 0;

    if (sFavoriteRow < win->rows) {
        FavoriteScreen_PrintNextRow();
        return 0;
    }
    if (gMenuHasInput) {
        if (gKeysNew & A_BUTTON) {
            m4aSongNumStart(0);
        } else if (gKeysNew & B_BUTTON) {
            gOpenMenuReq = 1;
            m4aSongNumStart(3);
            ret = 1;
        } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
            if (gKeysNew & R_BUTTON)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            ret = 1;
            m4aSongNumStart(6);
        }
    }
    FavoriteScreen_DrawGauges();
    FavoriteScreen_DrawIcons();
    return ret;
}

s32 FavoriteScreen_Exit(void)
{
    struct Window *win = gWindows;
    s32 ret;

    Window_Close(win);
    ret = 0;
    if ((win->anim >> 2) < win->width) {
        win->anim += 8;
    } else {
        ret = 1;
        Obj_FreePalette(3);
        win->anim = 0;
    }
    return ret;
}

void FavoriteScreen_PrintNextRow(void)
{
    char buf[2];
    struct Window *win = gWindows;
    s32 i;
    s32 score;

    if (sFavoriteRow >= win->rows)
        return;
    Text_SetFill(1, 0);
    Text_Clear();
    buf[0] = sFavoriteRank + '0';
    buf[1] = 0;
    Text_SetX(8);
    Text_Print(buf, TEXT_DRAW_FIX);
    Text_AddX(24);
    score = sFavoriteOrder[sFavoriteRow];
    Text_Print(Msg_GetItemName(score + 381), TEXT_DRAW);
    Window_PutText(win, sFavoriteRow, 0);
    i = sFavoriteRow;
    if (i < win->rows - 1) {
        score = gSession.favorites[sFavoriteOrder[i]];
        if (score != gSession.favorites[sFavoriteOrder[i + 1]])
            sFavoriteRank = sFavoriteRow + 2;
    }
    sFavoriteRow++;
}

void FavoriteScreen_DrawRow(s32 idx)
{
    u16 buf[30];
    struct Window *win = gWindows;
    u32 map;
    s32 attr;
    s32 y;
    s32 w;
    s32 step;
    s32 t;
    s32 i;
    s32 j;

    y = win->y + 1 + idx * 2;
    w = win->width - 2;
    map = (u32)Bg_GetMapPtr(win->bg, win->x + 1, y);
    attr = 3 << 12;
    step = 64;
    for (i = 0; i < 2; map += step, i++) {
        t = Window_GetTextTile(0);
        t += (win->width << 1) * idx;
        t += i;
        for (j = 0; j < w; j++) {
            if (j & 1) {
                buf[j] = (t + 2) | attr;
                t += 4;
            } else {
                buf[j] = attr | t;
            }
        }
        DmaCopy16(3, buf, map, w << 1);
    }
}

void FavoriteScreen_DrawIcons(void)
{
    struct Window *win = gWindows;
    s32 x;
    s32 y;
    s32 frame;
    s32 i;

    x = (win->x + 3) * 8;
    y = (win->y + 1) * 8;
    x += 5;
    y -= 2;
    for (i = 0; i < win->rows; i++, y += 16) {
        frame = Item_GetIcon(sFavoriteOrder[i] + 381);
        Obj_Draw(x, y, 0, frame, Obj_GetPalette(0, frame), win->bg, 0);
    }
}

void FavoriteScreen_DrawGauges(void)
{
    struct Window *win = gWindows;
    s32 x;
    s32 y;
    s32 i;

    x = (win->x + 16) * 8;
    y = (win->y + 1) * 8 + 4;
    for (i = 0; i < win->rows; i++, y += 16) {
        Obj_DrawGauge(x, y, 7, 2, (gSession.favorites[sFavoriteOrder[i]] + 9) / 10);
    }
}
