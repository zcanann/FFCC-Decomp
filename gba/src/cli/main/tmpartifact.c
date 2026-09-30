#include "global.h"
#include "link.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "session.h"
#include "window.h"
#include "screen.h"

extern s8 sTmpArtifactUnused;
extern s8 sTmpArtifactQuit;
extern s8 sTmpArtifactRow;
extern s8 sTmpArtifactUnused2;

void TmpArtifactScreen_HandleInput(void);
void TmpArtifactScreen_DrawIcons(void);

void TmpArtifactScreen_Setup(void)
{
    struct Window *win;

    gSubState = 0;
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    StatusWin_Setup(0, 2);
    ListWin_Setup(1, 2, 15, 2);
    win = &gWindows[1];
    win->y = 2;
    win->rows = 4;
    win->height = 10;
    Window_ResetItems(win, 1);
    Text_SetFill(1, 0);
    Text_LoadPalette(4, 0, 0);
    Text_LoadPalette(5, 0, 0);
    Text_LoadPalette(6, 2, 0);
    Font_LoadPalette(0x050000E0, 0);
    Font_LoadPalette(0x05000100, 1);
    Text_CopyFill(0x06008000);
    Text_CopyFill(0x06008400);
    Obj_AllocPalette(17, 0);
    Obj_AllocPalette(3, 0);
    Obj_LoadToBg(17, 0, 2, 0);
    Obj_LoadToBg(3, 1, 2, 0);
    sTmpArtifactUnused = 0;
    sTmpArtifactRow = 0;
    sTmpArtifactQuit = 0;
    HelpWin_Clear(1, 1);
    HelpWin_DrawFrame(1, 1, 8);
    sTmpArtifactUnused2 = 0;
    gScreenInitDone = 1;
}

s32 TmpArtifactScreen_Init(void)
{
    struct Window *win;
    s32 ret;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0) {
        TmpArtifactScreen_Setup();
        if (gScreenInitDone == 0)
            return 0;
    }
    ret = StatusWin_Open(0);
    win = &gWindows[1];
    Window_PrintNextItem(win);
    Window_Open(win);
    if ((win->anim >> 3) < win->height - 2)
        win->anim += 8;
    if (ret) {
        win[-1].anim = 0;
        win->anim = 0;
        Text_SetFill(0, 0);
        Text_Clear();
        Text_Print(Msg_GetSystem(43), TEXT_DRAW);
        HelpWin_CopyText(1, 1);
    }
    return ret;
}

s32 TmpArtifactScreen_Main(void)
{
    struct Window *win;
    s32 ret;
    s32 pal;

    StatusWin_DrawIcon(0);
    Text_SetFill(1, 0);
    Text_Clear();
    win = &gWindows[1];
    if (sTmpArtifactRow < win->rows) {
        TmpArtifactScreen_PrintRow(sTmpArtifactRow);
        pal = 5;
        Window_DrawRow(1, win->bg, sTmpArtifactRow, sTmpArtifactRow, pal);
        sTmpArtifactRow++;
        if (sTmpArtifactRow < win->rows)
            return 0;
    }
    if (gMenuHasInput)
        TmpArtifactScreen_HandleInput();
    TmpArtifactScreen_DrawIcons();
    ret = sTmpArtifactQuit != 0;
    if (ret)
        HelpWin_Clear(1, 1);
    return ret;
}

s32 TmpArtifactScreen_Exit(void)
{
    struct Window *win = gWindows;
    s32 done = 0;

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) < win->height - 1)
        win->anim += 8;
    else
        done = 1;
    win++;
    Window_Close(win);
    if ((win->anim >> 3) < win->height - 1)
        win->anim += 8;
    if (done) {
        win[-1].anim = 0;
        win->anim = 0;
        Obj_FreePalette(17);
        Obj_FreePalette(3);
    }
    return done;
}

void TmpArtifactScreen_HandleInput(void)
{
    if (gKeysNew == 0)
        return;
    if (gKeysNew & A_BUTTON) {
        m4aSongNumStart(0);
    } else if (gKeysNew & B_BUTTON) {
        sTmpArtifactQuit = 1;
        gOpenMenuReq = 1;
        m4aSongNumStart(3);
    } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
        if (gKeysNew & R_BUTTON)
            gScreenStep = 1;
        else
            gScreenStep = -1;
        m4aSongNumStart(6);
        sTmpArtifactQuit = 1;
    }
}

void TmpArtifactScreen_DrawIcons(void)
{
    s32 i;
    struct Window *win = &gWindows[1];
    s32 x = (win->x + 1) * 8;
    s32 y = (win->y + 1) * 8;
    s32 n = win->rows;

    for (i = 0; i < n; i++, y += 16) {
        s16 v = gSession.stageArtifacts[i];
        if (v > 0) {
            s32 id = Item_GetIcon(v);
            Obj_Draw(x, y, 0, id, Obj_GetPalette(0, id), 2, 0);
        }
    }
}

void TmpArtifactScreen_PrintRow(s32 idx, s32 row)
{
    char *str;

    Text_SetFill(1, 0);
    Text_Clear();
    Text_SetX(16);
    if (gSession.stageArtifacts[idx] > 0)
        str = Msg_GetItemName(gSession.stageArtifacts[idx]);
    else
        str = Msg_GetSystem(0);
    Text_Print(str, TEXT_DRAW);
    Text_CopyToVram(Window_GetTextVram(&gWindows[1], row, 0), gWindows[1].width);
}

void TmpArtifactScreen_RefreshRow(s32 row)
{
    TmpArtifactScreen_PrintRow(row, row);
}
