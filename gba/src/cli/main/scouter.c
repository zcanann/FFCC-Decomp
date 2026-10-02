#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "radar.h"
#include "window.h"
#include "screen.h"

static s8 sScouterRow;
static s8 sScouterActive;
static struct ScouterHit sScouterShown;

void ScouterScreen_PrintNextRow(void);
void ScouterScreen_ClearRows(void);

void ScouterScreen_Setup(void)
{
    gSubState = 0;
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    StatusWin_Setup(0, 0);
    gWindows[1].active = 1;
    gWindows[1].cursor = 0;
    gWindows[1].x = 1;
    gWindows[1].y = 0;
    gWindows[1].rows = 7;
    gWindows[1].width = 18;
    gWindows[1].height = gWindows[1].width - 2;
    gWindows[1].style = 4;
    gWindows[1].variant = 0;
    gWindows[1].bg = 2;
    gWindows[1].slot = 1;
    gWindows[1].textX = 0;
    Window_ResetItems(&gWindows[1], 1);
    Text_SetFill(1, 0);
    Text_LoadPalette(4, 0, 0);
    Font_LoadPalette(0x050000E0, 1);
    Font_LoadPalette(0x05000100, 0);
    Font_LoadPalette(0x05000120, Link_GetPlayerNo() + 5);
    Text_CopyFill(0x06000000);
    Obj_AllocPalette(17, 0);
    Obj_AllocPalette(7, 0);
    Obj_LoadToBg(17, 0, 0, 0);
    Obj_LoadToBg(7, 1, 2, 0);
    BonusWin_Setup(3);
    sScouterRow = 0;
    ScouterScreen_ClearRows();
    memset(&sScouterShown, 0xFF, sizeof(sScouterShown));
    gScreenInitDone = 1;
}

s32 ScouterScreen_Init(void)
{
    struct Window *win;
    s32 ret;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0) {
        ScouterScreen_Setup();
        if (gScreenInitDone == 0)
            return 0;
    }
    StatusWin_Open(0);
    win = &gWindows[1];
    Text_SetFill(0, 0);
    Text_Clear();
    win->bg--;
    Window_PrintNextItem(win);
    win->bg++;
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) >= win->height - 1) {
        ret = 1;
        win->anim = 0;
        BonusWin_Show(3, 9);
    } else {
        win->anim += 8;
    }
    return ret;
}

s32 ScouterScreen_Main(void)
{
    struct Window *win;

    StatusWin_DrawIcon(0);
    win = &gWindows[1];
    if (sScouterActive == 0) {
        if (gKeysNew & (L_BUTTON | R_BUTTON)) {
            if (gKeysNew & R_BUTTON)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            m4aSongNumStart(6);
            BonusWin_Hide(gWindows[3].bg);
            return 1;
        }
        if (gKeysNew & A_BUTTON) {
            m4aSongNumStart(0);
            return 0;
        }
        if (gKeysNew & B_BUTTON) {
            gOpenMenuReq = 1;
            m4aSongNumStart(3);
            return 1;
        }
        return 0;
    }
    if (gScouterDirty) {
        s32 reset;

        if (gScouterHit.enemy < 0 || sScouterShown.enemy != gScouterHit.enemy || sScouterRow < win->rows)
            reset = 1;
        else
            reset = 0;
        sScouterShown = gScouterHit;
        if (reset) {
            ScouterScreen_ClearRows();
            sScouterRow = 0;
        } else {
            sScouterRow = 1;
            ScouterScreen_PrintNextRow();
            sScouterRow = win->rows;
        }
        gScouterDirty = 0;
    }
    ScouterScreen_PrintNextRow();
    Text_SetFill(1, 0);
    if (gMenuHasInput == 0)
        return 0;
    if (gKeysNew & (L_BUTTON | R_BUTTON)) {
        if (gKeysNew & R_BUTTON)
            gScreenStep = 1;
        else
            gScreenStep = -1;
        BonusWin_Hide(gWindows[3].bg);
        return 1;
    }
    if (gKeysNew & A_BUTTON) {
        m4aSongNumStart(0);
    } else if (gKeysNew & B_BUTTON) {
        gOpenMenuReq = 1;
        m4aSongNumStart(3);
        return 1;
    }
    return 0;
}

s32 ScouterScreen_Exit(void)
{
    struct Window *win;
    s32 ret;

    Scouter_SetDirty(0);
    win = gWindows;
    ret = 0;
    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) < win->height - 1)
        win->anim += 8;
    win++;
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 1) {
        ret = 1;
        Obj_FreePalette(17);
        Obj_FreePalette(7);
        win->anim = 0;
    } else {
        win->anim += 8;
    }
    return ret;
}

void ScouterScreen_PrintNextRow(void)
{
    struct Window *win = &gWindows[1];
    struct ScouterInfo *item;
    char buf[68];
    s32 idx;
    s32 row;
    s32 x;

    Text_SetFill(0, 0);
    Text_Clear();
    idx = sScouterShown.enemy;
    if (idx < 0)
        return;
    item = &((struct ScouterInfo *)LIST_BUF)[idx];
    row = sScouterRow;
    if (row >= win->rows)
        return;
    if (sScouterRow == 0) {
        idx = item->monster;
        Text_Print(Msg_GetMonsterName(idx), TEXT_DRAW);
    } else if (sScouterRow == 1) {
        x = win->width * 8;
        x -= 86;
        x -= 8 + Text_Print(Msg_GetSystem(18), TEXT_CHAR);
        x -= Text_Print(Msg_GetSystem(30), TEXT_WIDTH);
        Text_SetX(x);
        Text_Print(Msg_GetSystem(30), TEXT_DRAW);
        x = Text_GetX();
        if (item->monster != 154) {
            Text_PrintNumber(sScouterShown.hp, x + 8, 3);
        } else {
            Text_SetX(x + 8);
            Text_Print(Msg_GetSystem(41), TEXT_DRAW);
        }
        Text_Print(Msg_GetSystem(18), TEXT_DRAW);
        x = Text_GetX();
        if (item->monster != 154) {
            Text_PrintNumber(item->maxHp, x + 8, 3);
        } else {
            Text_SetX(x + 8);
            Text_Print(Msg_GetSystem(41), TEXT_DRAW);
        }
    } else if (sScouterRow <= 4) {
        if (item->traits[0] >= 0 && ((struct ScouterInfo *)LIST_BUF)[idx].traits[row - 2] >= 0) {
            if (item->traits[0] <= 1) {
                idx = item->traits[0] * 2;
                if (sScouterRow == 2) {
                    strcpy(buf, Msg_GetSystem(31));
                    strcat(buf, Msg_GetTrait(idx));
                    Text_Print(buf, TEXT_DRAW);
                } else if (sScouterRow == 3) {
                    strcpy(buf, Msg_GetSystem(31));
                    strcat(buf, Msg_GetTrait(idx + 1));
                    Text_Print(buf, TEXT_DRAW);
                }
            } else {
                idx = ((struct ScouterInfo *)LIST_BUF)[idx].traits[row - 2];
                if (idx >= 0) {
                    strcpy(buf, Msg_GetSystem(31));
                    strcat(buf, Msg_GetTrait(idx + 3));
                    Text_Print(buf, TEXT_DRAW);
                }
            }
        }
    } else if (sScouterRow == 5) {
        strcpy(buf, Msg_GetSystem(31));
        strcat(buf, Msg_GetSystem(32));
        Text_Print(buf, TEXT_DRAW);
    } else {
        Text_SetX(24);
        idx = item->dropItem;
        if (idx < 0)
            Text_Print(Msg_GetSystem(41), TEXT_DRAW);
        else if (idx == 0)
            Text_Print(Msg_GetSystem(62), TEXT_DRAW);
        else
            Text_Print(Msg_GetItemName(idx), TEXT_DRAW);
    }
    idx = win->bg;
    win->bg--;
    Window_PutText(win, sScouterRow, 0);
    win->bg = idx;
    sScouterRow++;
}

void ScouterScreen_ClearRows(void)
{
    struct Window *win = &gWindows[1];
    s32 i;

    Text_SetFill(0, 0);
    Text_Clear();
    win->bg--;
    for (i = 0; i < win->rows; i++)
        Window_PutText(win, i, 0);
    win->bg++;
}

void Scouter_SetDirty(s32 mode)
{
    sScouterActive = mode;
    ScouterScreen_ClearRows();
}
