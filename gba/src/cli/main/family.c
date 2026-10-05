#include "global.h"
#include "link.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "session.h"
#include "window.h"
#include "screen.h"

static s8 sFamilyQuit;
static s8 sFamilyRow;

void FamilyScreen_HandleInput(void);
void FamilyScreen_PrintRow(s32);
void FamilyScreen_DrawHearts(void);
void FamilyScreen_DrawIcon(void);

void FamilyScreen_Setup(void)
{
    s32 i;

    gSubState = 0;
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);

    gWindows[0].active = 0;
    gWindows[0].cursor = 0;
    gWindows[0].x = 3;
    gWindows[0].y = 1;
    gWindows[0].rows = 5;
    gWindows[0].width = 24;
    gWindows[0].height = 17;
    gWindows[0].style = 0;
    gWindows[0].variant = 0;
    gWindows[0].bg = 2;
    gWindows[0].slot = 0;
    gWindows[0].textX = 0;
    gWindows[0].tallRows = 1;
    for (i = 0; i < gWindows[0].rows; i++)
        gWindows[0].items[i].enabled = 1;

    Text_SetFill(1, 0);
    Text_LoadPalette(3, 0, 0);
    Text_CopyFill(0x06008000);
    Obj_AllocPalette(3, 0);
    Obj_LoadToBg(3, 0, 2, 0);
    Font_LoadPalette(0x050000E0, 0);
    sFamilyRow = 0;
    sFamilyQuit = 0;
    gScreenInitDone = 1;
}

s32 FamilyScreen_Init(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0)
        FamilyScreen_Setup();
    win = gWindows;
    Window_PrintNextItem(win);
    Window_Open(win);
    if ((win->anim >> 3) >= win->height - 2)
        ret = 1;
    else
        win->anim += 8;
    return ret;
}

s32 FamilyScreen_Main(void)
{
    s32 ret;

    if (sFamilyRow <= 4) {
        FamilyScreen_PrintRow(sFamilyRow);
        sFamilyRow++;
        return 0;
    }
    Text_SetFill(1, 0);
    if (gMenuHasInput)
        FamilyScreen_HandleInput();
    ret = sFamilyQuit != 0;
    FamilyScreen_DrawHearts();
    FamilyScreen_DrawIcon();
    return ret;
}

s32 FamilyScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    win = gWindows;
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 2) {
        ret = 1;
        Obj_FreePalette(3);
    } else {
        win->anim += 8;
    }
    return ret;
}

void FamilyScreen_HandleInput(void)
{
    if (gKeysNew & A_BUTTON) {
        m4aSongNumStart(0);
    } else if (gKeysNew & B_BUTTON) {
        sFamilyQuit = 1;
        gOpenMenuReq = 1;
        m4aSongNumStart(3);
    } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
        if (gKeysNew & R_BUTTON)
            gScreenStep = 1;
        else
            gScreenStep = -1;
        m4aSongNumStart(6);
        sFamilyQuit = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x0200F600
 * PAL Size: 168b
 * EN Address: 0x0200F524
 * EN Size: 136b
 * JP Address: 0x0200C1EC
 * JP Size: 152b
 */
void FamilyScreen_PrintRow(s32 idx)
{
    struct Window *win = gWindows;
    s32 lv;

    Text_SetFill(1, 0);
    Text_Clear();
    if (idx == 0) {
        Text_SetX(16);
        lv = gSession.job;
        Text_Print(Msg_GetJob(lv), TEXT_DRAW);
    } else {
        lv = gSession.relationType[idx - 1];
        if (lv <= 0)
            return;
        Text_Print(Msg_GetSystem(lv + 53), TEXT_DRAW);
#if defined(VERSION_GCCE01) || defined(VERSION_GCCJGC)
        Text_SetX(56);
#else
        if ((gLanguage & 15) == 1)
            Text_SetX(80);
        else
            Text_SetX(56);
#endif
        Text_Print(gSession.relationNames[idx - 1], TEXT_DRAW);
    }
    Text_CopyToVram(Window_GetTextVram(win, idx, 0), win->width);
}

void FamilyScreen_DrawHearts(void)
{
    struct Window *win = gWindows;
    s32 x;
    s32 y;
    s32 i;
    s32 id;
    s32 hp;
    s32 lv;

    x = (win->x + win->width - 3) * 8;
    y = (win->y + 4) * 8;
    for (i = 0; i < 4 && (lv = gSession.relationType[i]) > 0; i++, y += 24) {
        hp = gSession.relationValue[i];
        if (hp <= 20)
            id = 33;
        else if (hp <= 40)
            id = 32;
        else if (hp <= 60)
            id = 31;
        else if (hp <= 80)
            id = 30;
        else
            id = 29;
        Obj_Draw(x, y, 0, id, Obj_GetPalette(0, id), 2, 0);
    }
}

void FamilyScreen_DrawIcon(void)
{
    struct Window *win = gWindows;
    s32 x;
    s32 y;

    x = (win->x + 1) * 8 + 4;
    y = (win->y + 1) * 8 + 4;
    Obj_Draw(x, y, 2, 6, Obj_GetPalette(2, 6), 2, 0);
}
