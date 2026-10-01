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

static s8 sLetterState;
static s8 sLetterQuit;
static s8 sLetterStateInit;
static s8 sLetterSubInit;
static u8 sLetterTop;
static u8 sLetterRow;
static s8 sLetterLines;
static s16 sLetterSel;
static s8 sLetterSubState;
static s8 sLetterSubPhase;
static s8 sLetterAnswers;
static s8 sLetterResult;
static s8 sLetterAnswer;
static s8 sLetterFailed;
static s8 sLetterAlign;
static s8 sLetterAttachType;
static u32 sLetterAttachValue;
static s8 sLetterGiftTop;
static s16 sLetterPollTimer;

void LetterList_PrintRow(s32, s32);
void LetterList_DrawRow(s32, s32, s32, s32);
s32 LetterList_GetRowPalette(s32);
void Letter_DrawCursor(s32, s32);
s32 LetterList_HandleInput(void);
void LetterList_DrawIcons(void);
void LetterRead_PrintNextLine(void);
void LetterRead_DrawAttachIcon(void);
void LetterGift_DrawIcons(void);
s32 LetterGift_HandleInput(void);
void Letter_BuildText(char *, s32);
s32 LetterGift_CanGive(s32 idx);
void LetterGift_PrintItem(s32 idx, s32 row);
s32 Str_CountLines(s8 *str);
s32 LetterList_Init(void);
s32 LetterList_Main(void);
s32 LetterList_Exit(void);
s32 LetterRead_Init(void);
s32 LetterRead_Main(void);
s32 LetterRead_Exit(void);
s32 LetterGift_Init(void);
s32 LetterGift_Main(void);
s32 LetterGift_Exit(void);
s32 LetterSend_Init(void);
s32 LetterSend_Main(void);
s32 LetterSend_Exit(void);
s32 LetterError_Init(void);
s32 LetterError_Main(void);
s32 LetterError_Exit(void);
s32 LetterTake_Init(void);
s32 LetterTake_Main(void);
s32 LetterTake_Exit(void);
s32 LetterTaken_Init(void);
s32 LetterTaken_Main(void);
s32 LetterTaken_Exit(void);
s32 LetterAnswer_Init(void);
s32 LetterAnswer_Main(void);
s32 LetterAnswer_Exit(void);
s32 LetterAttach_Init(void);
s32 LetterAttach_Main(void);
s32 LetterAttach_Exit(void);

struct ScreenFuncs gLetterStates[] = {
    { LetterList_Init, LetterList_Main, LetterList_Exit },
    { LetterRead_Init, LetterRead_Main, LetterRead_Exit },
    { LetterGift_Init, LetterGift_Main, LetterGift_Exit },
    { LetterSend_Init, LetterSend_Main, LetterSend_Exit },
    { LetterError_Init, LetterError_Main, LetterError_Exit },
};

struct ScreenFuncs gLetterReadStates[] = {
    { LetterTake_Init, LetterTake_Main, LetterTake_Exit },
    { LetterTaken_Init, LetterTaken_Main, LetterTaken_Exit },
    { LetterAnswer_Init, LetterAnswer_Main, LetterAnswer_Exit },
    { LetterAttach_Init, LetterAttach_Main, LetterAttach_Exit },
};

const char sSpaceText[] = " ";
const char sQuestionText[] = "?";
const char sPeriodText[] = ".";

void LetterScreen_Setup(void)
{
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    Xfer_ClearLetterData();
    Link_SendRequest(3, 0);
    sLetterPollTimer = 0;
    Text_SetFill(1, 0);
    Text_Clear();
    Text_LoadPalette(3, 0, 0);
    Text_CopyFill(0x06008000);
    Font_LoadPalette(0x050000E0, 0);
    Font_LoadPalette(0x05000100, 2);
    Font_LoadPalette(0x05000120, 3);
    if (gLetterAttachKind == 0) {
        sLetterState = 0;
        sLetterQuit = 0;
        sLetterSubInit = 0;
        sLetterTop = 0;
        sLetterRow = 0;
        sLetterSel = -1;
        sLetterLines = 0;
        sLetterAnswers = 0;
        sLetterSubState = 0;
        sLetterSubPhase = -1;
        sLetterResult = 0;
        sLetterAnswer = -1;
        sLetterFailed = 0;
        sLetterAttachType = 0;
        sLetterAttachValue = 0;
    } else {
        gLetterAttachKind = 0;
        if (sLetterResult == 1) {
            sLetterState = 3;
        } else {
            sLetterState = 1;
            sLetterSubState = 2;
            sLetterSubPhase = 0;
        }
    }
    HelpWin_Clear(1, 1);
    gScreenPhase = PHASE_EXIT;
    sLetterStateInit = 0;
    gScreenInitDone = 1;
}

s32 LetterScreen_Update(void)
{
    s32 ret;

    if (gScreenInitDone == 0)
        LetterScreen_Setup();
    if (gSubState == 0)
        ret = gLetterStates[sLetterState].init();
    else if (gSubState == 1)
        ret = gLetterStates[sLetterState].main();
    else
        ret = gLetterStates[sLetterState].exit();
    if (ret) {
        ret = 0;
        if (gSubState <= 1) {
            gSubState++;
        } else {
            sLetterStateInit = 0;
            gSubState = 0;
            if (sLetterState == 0) {
                sLetterState++;
                sLetterSubPhase = -1;
                sLetterSubState = 0;
            } else if (sLetterState == 1 && sLetterResult != -1) {
                sLetterAttachType = 0;
                sLetterAttachValue = 0;
                if (sLetterResult == 2) {
                    sLetterAttachType = 0;
                    sLetterState += 2;
                } else {
                    sLetterState++;
                    if (sLetterResult != 0) {
                        ret = 1;
                        gLetterAttachKind = sLetterResult + 1;
                    }
                }
                sLetterSubState = 0;
                sLetterSubPhase = 0;
            } else if (sLetterState == 2) {
                if (sLetterResult == -1) {
                    sLetterState = 1;
                    sLetterSubState = 2;
                    sLetterSubPhase = 0;
                } else {
                    sLetterState++;
                }
            } else if (sLetterState == 3) {
                if (sLetterResult == -1) {
                    sLetterState = 1;
                    sLetterSubState = 2;
                    sLetterSubPhase = 0;
                } else if (sLetterFailed) {
                    sLetterState++;
                } else {
                    sLetterState = 0;
                }
            } else if (sLetterState == 4) {
                sLetterState--;
                gSubState = 2;
                sLetterFailed = 0;
                sLetterResult = -1;
            } else {
                sLetterState = 0;
            }
            if (sLetterQuit)
                ret = 1;
        }
        if (ret)
            HelpWin_Clear(1, 1);
    }
    return ret;
}

s32 LetterList_Init(void)
{
    struct Window *win = gWindows;
    s32 ret;

    if (sLetterStateInit == 0) {
        memset(win, 0, sizeof(struct Window));
        win->active = 1;
        if (sLetterSel >= 0)
            win->cursor = sLetterSel - sLetterTop;
        win->x = 0;
        win->y = 0;
        win->rows = 8;
        win->width = 30;
        win->height = 18;
        win->style = 0;
        win->variant = 1;
        win->bg = 2;
        win->slot = 0;
        win->textX = 0;
        Window_ResetItems(win, 1);
        Text_SetFill(1, 0);
        Font_LoadPalette(0x050000E0, 0);
        Font_LoadPalette(0x05000100, 2);
        Font_LoadPalette(0x050001C0, 1);
        Obj_AllocPalette(3, 1);
        Obj_LoadToBg(3, 0, 2, 1);
        Text_SetFill(0, 0);
        Text_Clear();
        HelpWin_Clear(1, 2);
        HelpWin_DrawFrame(1, 2, 14);
        sLetterRow = 0;
        sLetterSel = -1;
        sLetterAnswer = -1;
        sLetterStateInit = 1;
    }
    Text_SetFill(1, 0);
    Window_PrintNextItem(win);
    if (win->items[win->rows - 1].drawn == 0)
        return 0;
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 2) < win->width) {
        win->anim += 8;
    } else {
        ret = 1;
        Text_SetFill(0, 0);
        Text_Clear();
        Text_Print(Msg_GetSystem(61), TEXT_DRAW);
        HelpWin_CopyText(1, 2);
        win->anim = 0;
    }
    return ret;
}

s32 LetterList_Main(void)
{
    s32 n;
    s32 idx;
    s32 attr;
    s32 ret;

    if (gNewLetter) {
        Link_SendRequest(3, 0);
        DmaClear16(0, 0x3FF, 0x0600E800, 0x800);
        gNewLetter = 0;
        sLetterRow = 0;
        sLetterPollTimer = 0;
    }
    if (!(gDataFlags & DATA_LETTER_LIST)) {
        if (gKeysNew & A_BUTTON) {
            m4aSongNumStart(0);
        } else if (gKeysNew & B_BUTTON) {
            sLetterQuit = 1;
            gOpenMenuReq = 1;
            m4aSongNumStart(3);
            return 1;
        } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
            if (gKeysNew & R_BUTTON)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            ret = 1;
            sLetterQuit = ret;
            m4aSongNumStart(6);
            return 1;
        }
        if (sLetterRow)
            LetterList_DrawIcons();
        if (++sLetterPollTimer >= 300) {
            Link_SendRequest(3, 0);
            sLetterPollTimer = 0;
        }
        return 0;
    }
    if (((struct LetterListHeader *)LIST_BUF)->count > gWindows[0].rows)
        n = gWindows[0].rows;
    else
        n = ((struct LetterListHeader *)LIST_BUF)->count;
    ret = 0;
    if (sLetterRow < n) {
        idx = sLetterTop + sLetterRow;
        n = idx % gWindows[0].rows;
        LetterList_PrintRow(idx, n);
        attr = LetterList_GetRowPalette(sLetterTop + sLetterRow);
        LetterList_DrawRow(n, sLetterRow, 25, attr);
        sLetterRow++;
    } else if (gMenuHasInput) {
        ret = LetterList_HandleInput();
        Letter_DrawCursor(gWindows[0].x * 8, (gWindows[0].y + 1) * 8 + gWindows[0].cursor * 16);
    }
    LetterList_DrawIcons();
    if (ret)
        HelpWin_Clear(1, 2);
    return ret;
}

s32 LetterList_Exit(void)
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

s32 LetterRead_Init(void)
{
    struct Window *win = gWindows;
    s32 i;
    s32 ret;

    if (sLetterStateInit == 0) {
        memset(win, 0, sizeof(struct Window));
        win->active = 1;
        win->x = 2;
        win->y = 1;
        win->rows = 7;
        win->width = 27;
        win->height = 17;
        win->style = 8;
        win->variant = 0;
        win->bg = 2;
        win->slot = 0;
        win->textX = 0;
        for (i = 0; i < win->rows; i++) {
            win->items[i].enabled = 1;
            win->items[i].text = Msg_GetSystem(0);
        }
        Font_LoadPalette(0x050000E0, 0);
        Obj_AllocPalette(11, 0);
        Obj_LoadToBg(11, 0, 2, 0);
        Text_SetFill(1, 1);
        Text_Clear();
        Text_LoadPalette(5, 0, 1);
        Text_CopyFill(0x06000800);
        Obj_AllocPalette(12, 0);
        Obj_LoadToBg(12, 2, 0, 0);
        sLetterRow = 0;
        sLetterLines = 0;
        sLetterAnswers = 0;
        sLetterSubInit = 0;
        sLetterResult = -1;
        sLetterFailed = 0;
        sLetterPollTimer = 0;
        sLetterAlign = 0;
        sLetterStateInit = 1;
    }
    Text_SetFill(1, 0);
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        win->anim = 0;
    }
    return ret;
}

s32 LetterRead_Main(void)
{
    struct LetterListHeader *list;
    struct LetterEntry *entries;
    s32 ret;

    if (!(gDataFlags & DATA_LETTER)) {
        if (gKeysNew & B_BUTTON) {
            sLetterResult = -1;
            m4aSongNumStart(3);
            return 1;
        }
        if (++sLetterPollTimer >= 60) {
            Link_SendRequest(2, sLetterSel);
            sLetterPollTimer = 0;
        }
        return 0;
    }
    list = (struct LetterListHeader *)LIST_BUF;
    entries = LETTER_ENTRIES;
    if (sLetterRow == 0) {
        entries[sLetterSel].flags |= 1;
        sLetterLines = Str_CountLines(DETAIL_BUF);
    }
    if (sLetterRow < sLetterLines)
        LetterRead_PrintNextLine();
    ret = 0;
    if (sLetterSubPhase < 0) {
        if (gKeysNew & B_BUTTON) {
            sLetterResult = -1;
            ret = 1;
            m4aSongNumStart(3);
        } else if (gKeysNew & A_BUTTON) {
            if ((entries[sLetterSel].flags & 0x18) && !(entries[sLetterSel].flags & 2)) {
                sLetterSubPhase = 0;
                sLetterSubState = 0;
                sLetterResult = 0;
                sLetterFailed = 0;
                sLetterSubInit = 0;
                sLetterAnswer = -1;
            } else if (!(entries[sLetterSel].flags & 4) && list->canReply && (entries[sLetterSel].flags & 0x20)) {
                sLetterSubPhase = 0;
                sLetterSubState = 2;
                sLetterResult = 0;
                sLetterFailed = 0;
                sLetterSubInit = 0;
                sLetterAnswer = -1;
            }
            m4aSongNumStart(2);
        } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
            m4aSongNumStart(0);
        }
    } else {
        if (sLetterSubPhase == 0)
            ret = gLetterReadStates[sLetterSubState].init();
        else if (sLetterSubPhase == 1)
            ret = gLetterReadStates[sLetterSubState].main();
        else
            ret = gLetterReadStates[sLetterSubState].exit();
        if (ret) {
            ret = 0;
            if (sLetterSubPhase <= 1) {
                sLetterSubPhase++;
            } else {
                sLetterSubInit = 0;
                if (sLetterSubState == 0) {
                    if (sLetterFailed) {
                        sLetterSubState++;
                        sLetterFailed = 0;
                        sLetterSubPhase = 0;
                    } else if (!(entries[sLetterSel].flags & 4)) {
                        if (list->canReply && (entries[sLetterSel].flags & 0x20)) {
                            sLetterSubState += 2;
                            sLetterSubPhase = 0;
                        } else {
                            sLetterSubPhase = -1;
                            sLetterResult = -1;
                        }
                    } else {
                        sLetterSubPhase = -1;
                        sLetterResult = -1;
                    }
                } else if (sLetterSubState == 1) {
                    if (!(entries[sLetterSel].flags & 4)) {
                        if (list->canReply && (entries[sLetterSel].flags & 0x20)) {
                            sLetterSubState++;
                            sLetterSubPhase = 0;
                        } else {
                            sLetterSubPhase = -1;
                            sLetterResult = -1;
                        }
                    } else {
                        sLetterSubPhase = -1;
                        sLetterResult = -1;
                    }
                } else if (sLetterSubState == 2) {
                    if (sLetterResult < 0) {
                        sLetterResult = -1;
                        sLetterSubPhase = -1;
                    } else {
                        sLetterSubState++;
                        sLetterSubPhase = 0;
                    }
                } else if (sLetterSubState == 3) {
                    if (sLetterResult < 0) {
                        sLetterSubState--;
                        sLetterSubPhase = 0;
                    } else {
                        ret = 1;
                    }
                } else {
                    sLetterResult = -1;
                    sLetterSubPhase = -1;
                }
            }
        }
    }
    LetterRead_DrawAttachIcon();
    return ret;
}

s32 LetterRead_Exit(void)
{
    struct Window *win = gWindows;
    s32 ret;

    Window_Close(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        Obj_FreePalette(11);
        Obj_FreePalette(12);
        win->anim = 0;
    }
    return ret;
}

s32 LetterGift_Init(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    if (sLetterStateInit == 0) {
        DmaClear32(0, ret, gWindows, sizeof(struct Window) * 5);
        ListWin_Setup(1, 16, 0, 2);
        Text_SetFill(1, 0);
        Text_Clear();
        Text_LoadPalette(5, 0, 0);
        Text_LoadPalette(6, 2, 0);
        Font_LoadPalette(0x050000E0, 0);
        Font_LoadPalette(0x05000100, 1);
        Obj_AllocPalette(3, 0);
        Obj_LoadToBg(3, 1, 2, 0);
        Text_CopyFill(0x06008400);
        sLetterRow = 0;
        gSubState = 0;
        sLetterGiftTop = 0;
        sLetterResult = 0;
        HelpWin_Clear(1, 1);
        HelpWin_DrawFrame(1, 1, 8);
        sLetterStateInit = 1;
    }
    win = &gWindows[1];
    Text_SetFill(1, 0);
    Text_Clear();
    Window_PrintNextItem(win);
    Window_Open(win);
    if ((win->anim >> 3) >= win->height - 2) {
        win->anim = ret;
        HelpWin_PrintItemDesc(gSession.items[0], 1, 1);
        ret = 1;
    } else {
        win->anim += 8;
    }
    return ret;
}

s32 LetterGift_Main(void)
{
    struct Window *win = &gWindows[1];
    s32 id;
    s32 attr;
    s32 ret;

    if (sLetterRow < win->rows) {
        id = gSession.items[sLetterRow];
        Text_SetFill(1, 0);
        Text_Clear();
        if (id > 0) {
            Text_SetX(16);
            Text_Print(Msg_GetItemName(id), TEXT_DRAW);
        }
        Window_PutText(win, sLetterRow, 0);
        attr = Session_IsItemInUse(sLetterRow) ? 6 : 5;
        if (attr == 5 && (Session_GetItemCategory(sLetterRow) == 1 || Session_GetItemCategory(sLetterRow) == 3))
            attr = 6;
        Window_DrawRow(1, win->bg, sLetterRow, sLetterRow, attr);
        sLetterRow++;
        if (sLetterRow < win->rows)
            return 0;
    }
    Text_SetFill(1, 0);
    ret = LetterGift_HandleInput();
    Letter_DrawCursor(win->x * 8 - 10, (win->y + 1) * 8 + win->cursor * 16);
    attr = sLetterGiftTop + win->rows < 64;
    Window_DrawScrollArrows(1, win->bg, (u8)((attr << 8) | 64));
    LetterGift_DrawIcons();
    if (sLetterResult)
        HelpWin_Clear(1, 1);
    return ret;
}

s32 LetterGift_Exit(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    Text_Clear();
    win = &gWindows[1];
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 2) {
        ret = sLetterResult;
        Obj_FreePalette(3);
        win->anim = 0;
    } else {
        win->anim += 8;
    }
    return ret;
}

s32 LetterSend_Init(void)
{
    struct Window *win = gWindows;
    char buf[256];
    s32 w;
    s32 len;
    s32 n;
    s32 i;
    s32 row;
    s32 ret;

    if (sLetterStateInit == 0) {
        memset(win, 0, sizeof(struct Window));
        memset(buf, 0, sizeof(buf));
        Letter_BuildText(buf, 0);
        Text_SetFill(1, 0);
        Text_Clear();
        Text_Print(buf, TEXT_DRAW);
        w = Text_GetX();
        memset(buf, 0, sizeof(buf));
        Letter_BuildText(buf, 1);
        len = Text_Print(buf, TEXT_WIDTH);
        if (len > w)
            w = len;
        len = Text_Print(Msg_GetLetter(7), TEXT_WIDTH);
        if (len > w)
            w = len;
        if (sLetterAttachType & 0x18) {
            memset(buf, 0, sizeof(buf));
            Letter_BuildText(buf, 2);
            len = Text_Print(buf, TEXT_WIDTH);
            if (len > w)
                w = len;
        }
        n = w >> 3;
        if (w & 7)
            n++;
        w = n;
        win->active = 1;
        win->x = (28 - w) >> 1;
        win->y = 2;
        n = sLetterAttachType ? 6 : 5;
        win->rows = n;
        win->cursor = n - 2;
        win->width = w + 2;
        win->height = n * 2 + 2;
        win->style = 0;
        win->variant = 0;
        win->bg = 2;
        win->slot = 0;
        win->textX = 0;
        Obj_AllocPalette(3, 0);
        Obj_LoadToBg(3, 0, win->bg, 0);
        for (i = 0; i < win->rows; i++) {
            win->items[i].enabled = 1;
            win->items[i].text = Msg_GetSystem(0);
        }
        Window_PutText(win, 0, 0);
        sLetterResult = 0;
        sLetterFailed = 0;
        sLetterStateInit = 1;
    }
    Text_SetFill(1, 0);
    Text_Clear();
    row = win->anim >> 3;
    if (row != 0 && row < win->rows) {
        memset(buf, 0, sizeof(buf));
        if (row == 1) {
            Letter_BuildText(buf, 1);
            Text_Print(buf, TEXT_DRAW);
        }
        if (sLetterAttachType && row <= 3) {
            if (row == 2) {
                Letter_BuildText(buf, 2);
                Text_Print(buf, TEXT_DRAW);
            } else if (row == 3) {
                Text_Print(Msg_GetLetter(7), TEXT_DRAW);
            }
        } else if (!sLetterAttachType && row == 2) {
            Text_Print(Msg_GetLetter(7), TEXT_DRAW);
        } else {
            Text_SetX(16);
            if (sLetterAttachType)
                Text_Print(Msg_GetSystem(row - 2), TEXT_DRAW);
            else
                Text_Print(Msg_GetSystem(row - 1), TEXT_DRAW);
        }
        Window_PutText(win, row, 0);
    }
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) < win->height - 2) {
        win->anim += 8;
    } else {
        ret = 1;
        win->anim = 0;
    }
    return ret;
}

s32 LetterSend_Main(void)
{
    struct LetterEntry *entry = &LETTER_ENTRIES[sLetterSel];
    struct Window *win = gWindows;
    s32 ret = 0;

    if (gMenuHasInput) {
        if (sLetterResult == 0) {
            if (gKeysRepeat & (DPAD_UP | DPAD_DOWN)) {
                if (win->cursor == win->rows - 1)
                    win->cursor--;
                else
                    win->cursor++;
                m4aSongNumStart(1);
            }
            if (!(gKeysRepeat & (DPAD_UP | DPAD_DOWN))) {
                if (gKeysNew & A_BUTTON) {
                    if (win->cursor >= win->rows - 1) {
                        sLetterResult = -1;
                        ret = 1;
                    } else if (Link_SendLetterReply(sLetterSel, sLetterAnswer, (sLetterAttachType & 0x10) != 0, sLetterAttachValue) == 0) {
                        sLetterResult = 1;
                        Reply_Clear();
                        gReplyWaiting = 1;
                    }
                    m4aSongNumStart(2);
                } else if (gKeysNew & B_BUTTON) {
                    sLetterResult = -1;
                    ret = 1;
                    m4aSongNumStart(3);
                } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
                    m4aSongNumStart(0);
                }
            }
        } else if (gDataFlags & DATA_REPLY) {
            if (gReplyResult == 0) {
                entry->flags |= 4;
                sLetterFailed = 0;
                ret = 1;
            } else {
                sLetterFailed = 1;
                ret = 1;
            }
        } else if (Reply_IsTimedOut()) {
            sLetterFailed = 1;
            ret = 1;
        }
        Letter_DrawCursor((win->x + 1) * 8 - 2, (win->y + 1) * 8 + win->cursor * 16);
    }
    return ret;
}

s32 LetterSend_Exit(void)
{
    struct Window *win;
    s32 ret;

    if (sLetterFailed)
        return 1;
    win = gWindows;
    Window_Close(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        win->anim = 0;
        Obj_FreePalette(3);
    }
    return ret;
}

s32 LetterError_Init(void)
{
    struct Window *win = &gWindows[1];
    s32 w;
    s32 i;
    s32 ret;

    if (sLetterStateInit == 0) {
        memset(win, 0, sizeof(struct Window));
        Obj_AllocPalette(12, 0);
        Obj_LoadToBg(12, 2, 0, 0);
        Text_CopyFill(0x06000800);
        Text_SetFill(1, 1);
        Text_Clear();
        Text_Print(Msg_GetLetter(10), TEXT_DRAW);
        w = Text_GetX();
        w = (w & 7) ? (w >> 3) + 1 : w >> 3;
        win->active = 1;
        win->x = (28 - w) >> 1;
        win->y = 7;
        win->rows = 1;
        win->width = w + 2;
        win->height = win->rows * 2 + 2;
        win->style = 9;
        win->variant = 0;
        win->bg = 0;
        win->slot = 2;
        win->textX = 0;
        for (i = 0; i < win->rows; i++) {
            win->items[i].enabled = 1;
            win->items[i].text = Msg_GetSystem(0);
        }
        Window_PutText(win, 0, 0);
        sLetterFailed = 0;
        sLetterStateInit = 1;
        m4aSongNumStart(0);
    }
    Text_SetFill(1, 1);
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        win->anim = 0;
    }
    return ret;
}

s32 LetterError_Main(void)
{
    s32 ret = 0;

    if (gMenuHasInput && (gKeysNew & (A_BUTTON | B_BUTTON))) {
        ret = 1;
        m4aSongNumStart(2);
    }
    return ret;
}

s32 LetterError_Exit(void)
{
    struct Window *win = &gWindows[1];
    s32 ret;

    Window_Close(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        Obj_FreePalette(12);
        win->anim = 0;
    }
    return ret;
}

s32 LetterTake_Init(void)
{
    char buf[256];
    s32 mode = gLanguage & 15;
    struct Window *win = &gWindows[1];
    struct LetterEntry *entry;
    s32 w;
    s32 i;
    s32 ret;

    if (sLetterSubInit == 0) {
        memset(win, 0, sizeof(struct Window));
        entry = &LETTER_ENTRIES[sLetterSel];
        memset(buf, 0, sizeof(buf));
        if (mode != 1)
            strcpy(buf, Msg_GetLetter(0));
        if (entry->flags & 8) {
            if (mode == 1)
                strcat(buf, Msg_GetLetter(2));
            strcat(buf, Msg_GetItemName(entry->attachment));
            if (mode == 1)
                strcat(buf, Msg_GetLetter(3));
        } else {
            w = strlen(buf);
            IntToStr(buf + w, entry->attachment);
            strcat(buf, sSpaceText);
            strcat(buf, Msg_GetSystem(5));
        }
        if (mode == 1)
            strcat(buf, Msg_GetLetter(0));
        else
            strcat(buf, sQuestionText);
        Text_SetFill(1, 1);
        Text_Clear();
        Text_Print(buf, TEXT_DRAW);
        w = Text_GetX();
        w = (w & 7) ? (w >> 3) + 1 : w >> 3;
        win->active = 1;
        win->cursor = 1;
        win->x = (28 - w) >> 1;
        win->y = 4;
        win->rows = 3;
        win->width = w + 2;
        win->height = 8;
        win->style = 9;
        win->variant = 0;
        win->bg = 0;
        win->slot = 2;
        win->textX = 0;
        for (i = 0; i < win->rows; i++) {
            win->items[i].enabled = 1;
            win->items[i].text = Msg_GetSystem(0);
        }
        Window_PutText(win, 0, 0);
        sLetterAnswers = 0;
        sLetterFailed = 0;
        sLetterSubInit = 1;
    }
    Text_SetFill(1, 1);
    w = win->anim >> 3;
    if (w == 1 || w == 2) {
        Text_Clear();
        Text_SetX(16);
        Text_Print(Msg_GetSystem(w + 1), TEXT_DRAW);
        Window_PutText(win, w, 0);
    }
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        win->anim = 0;
    }
    return ret;
}

s32 LetterTake_Main(void)
{
    s32 ret = 0;
    struct LetterEntry *entry = &LETTER_ENTRIES[sLetterSel];
    struct Window *win;

    if (gMenuHasInput) {
        win = &gWindows[1];
        if (gKeysRepeat && sLetterResult == 0) {
            if (gKeysRepeat & DPAD_UP) {
                if (win->cursor > 1)
                    win->cursor--;
                else
                    win->cursor = win->rows - 1;
                m4aSongNumStart(1);
            } else if (gKeysRepeat & DPAD_DOWN) {
                if (win->cursor < win->rows - 1)
                    win->cursor++;
                else
                    win->cursor = 1;
                m4aSongNumStart(1);
            }
            if (!(gKeysRepeat & (DPAD_UP | DPAD_DOWN))) {
                if (gKeysNew & A_BUTTON) {
                    if (win->cursor == 1) {
                        if (Link_SendEvent(0, sLetterSel, 0) == 0) {
                            sLetterResult = 1;
                            Reply_Clear();
                            gReplyWaiting = 1;
                        }
                    } else {
                        sLetterResult = -1;
                    }
                    m4aSongNumStart(2);
                } else if (gKeysNew & B_BUTTON) {
                    sLetterResult = -1;
                    m4aSongNumStart(3);
                } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
                    m4aSongNumStart(0);
                }
                if (sLetterResult < 0)
                    ret = 1;
            }
        } else if (sLetterResult) {
            if (gDataFlags & DATA_REPLY) {
                if (gReplyResult) {
                    sLetterResult = -1;
                    sLetterFailed = 1;
                } else {
                    entry->flags |= 2;
                    sLetterFailed = 0;
                }
                ret = 1;
            } else if (Reply_IsTimedOut()) {
                sLetterResult = -1;
                sLetterFailed = 1;
                ret = 1;
            }
        }
        Letter_DrawCursor((win->x + 1) * 8 - 2, (win->y + 1) * 8 + win->cursor * 16);
    }
    if (ret)
        Reply_Clear();
    return ret;
}

s32 LetterTake_Exit(void)
{
    struct Window *win = &gWindows[1];
    s32 ret;

    Window_Close(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        win->anim = 0;
    }
    return ret;
}

s32 LetterTaken_Init(void)
{
    char buf[256];
    struct Window *win = &gWindows[1];
    struct LetterEntry *entry;
    char *str;
    s32 w;
    s32 w2;
    s32 i;
    s32 ret;

    if (sLetterSubInit == 0) {
        memset(win, 0, sizeof(struct Window));
        memset(buf, 0, sizeof(buf));
        entry = &LETTER_ENTRIES[sLetterSel];
        if (!(gLanguage & 15))
            strcat(buf, Msg_GetLetter(8));
        if (entry->flags & 8) {
            strcat(buf, Msg_GetItemName(entry->attachment));
        } else {
            w = strlen(buf);
            IntToStr(buf + w, entry->attachment);
            strcat(buf, sSpaceText);
            strcat(buf, Msg_GetSystem(5));
        }
        if (!(gLanguage & 15))
            strcat(buf, sPeriodText);
        Text_SetFill(1, 1);
        Text_Clear();
        if (gLanguage & 15) {
            w2 = Text_Print(Msg_GetLetter(9), TEXT_WIDTH);
            str = buf;
        } else {
            w2 = Text_Print(buf, TEXT_WIDTH);
            str = Msg_GetLetter(9);
        }
        Text_Print(str, TEXT_DRAW);
        w = Text_GetX();
        if (w < w2)
            w = w2;
        w = (w & 7) ? (w >> 3) + 1 : w >> 3;
        win->active = 1;
        win->cursor = 1;
        win->x = (28 - w) >> 1;
        win->y = 5;
        win->rows = 2;
        win->width = w + 2;
        win->height = 6;
        win->style = 9;
        win->variant = 0;
        win->bg = 0;
        win->slot = 2;
        win->textX = 0;
        for (i = 0; i < win->rows; i++) {
            win->items[i].enabled = 1;
            win->items[i].text = Msg_GetSystem(0);
        }
        Window_PutText(win, 0, 0);
        if (!(gLanguage & 15)) {
            Text_Clear();
            Text_Print(buf, TEXT_DRAW);
            Window_PutText(win, 1, 0);
        }
        sLetterFailed = 0;
        sLetterSubInit = 1;
        m4aSongNumStart(0);
    }
    Text_SetFill(1, 1);
    w = win->anim >> 3;
    if (w == 1 && (gLanguage & 15)) {
        Text_Clear();
        Text_Print(Msg_GetLetter(9), TEXT_DRAW);
        Window_PutText(win, 1, 0);
    }
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        win->anim = 0;
    }
    return ret;
}

s32 LetterTaken_Main(void)
{
    s32 ret = 0;

    if (gMenuHasInput) {
        if (gKeysNew & (A_BUTTON | B_BUTTON)) {
            ret = 1;
            m4aSongNumStart(2);
        } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
            m4aSongNumStart(0);
        }
    }
    return ret;
}

s32 LetterTaken_Exit(void)
{
    struct Window *win = &gWindows[1];
    s32 ret;

    Window_Close(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        win->anim = 0;
    }
    return ret;
}

s32 LetterAnswer_Init(void)
{
    char buf[256];
    struct Window *win = &gWindows[1];
    char *str;
    char *nl;
    s32 w;
    s32 len;
    s32 i;
    s32 ret;
    s32 n;

    if (sLetterSubInit == 0) {
        memset(win, 0, sizeof(struct Window));
        str = (char *)DETAIL_BUF;
        str = strlen(str) + (char *)(DETAIL_BUF + 1);
        sLetterAnswers = Str_CountLines(str);
        Text_SetFill(1, 1);
        Text_Clear();
        w = 0;
        for (i = 0; i < sLetterAnswers; i++) {
            memset(buf, 0, sizeof(buf));
            strcpy(buf, Msg_GetLetter(2));
            nl = strchr(str, '\n');
            if (nl) {
                len = nl - str;
                memcpy(buf + strlen(buf), str, len);
                str = nl + 1;
            } else {
                strcat(buf, str);
            }
            strcat(buf, Msg_GetLetter(3));
            if (i) {
                len = Text_Print(buf, TEXT_WIDTH);
            } else {
                Text_Print(buf, TEXT_DRAW);
                len = Text_GetX();
            }
            if (w < len)
                w = len;
        }
        len = Text_Print(Msg_GetSystem(4), TEXT_WIDTH);
        if (w < len)
            w = len;
        w = (w & 7) ? (w >> 3) + 1 : w >> 3;
        win->active = 1;
        if (sLetterAnswer >= 0) {
            win->cursor = sLetterAnswer;
            sLetterAnswer = -1;
        }
        win->x = (28 - w) >> 1;
        win->y = 7 - sLetterAnswers;
        n = sLetterAnswers + 1;
        win->rows = n;
        win->width = w + 2;
        win->height = n * 2 + 2;
        win->style = 9;
        win->variant = 0;
        win->bg = 0;
        win->slot = 2;
        win->textX = 0;
        for (i = 0; i < win->rows; i++) {
            win->items[i].enabled = 1;
            win->items[i].text = Msg_GetSystem(0);
        }
        Window_PutText(win, 0, 0);
        sLetterFailed = 0;
        sLetterSubInit = 1;
    }
    Text_SetFill(1, 1);
    w = win->anim >> 3;
    if (w != 0 && w < win->rows) {
        Text_Clear();
        if (w >= win->rows - 1) {
            Text_Print(Msg_GetSystem(4), TEXT_DRAW);
        } else {
            memset(buf, 0, sizeof(buf));
            str = (char *)DETAIL_BUF;
            str = strlen(str) + (char *)(DETAIL_BUF + 1);
            for (i = 0; i < w; i++) {
                nl = strchr(str, '\n');
                if (nl != NULL)
                    str = nl + 1;
                else
                    break;
            }
            strcpy(buf, Msg_GetLetter(2));
            nl = strchr(str, '\n');
            if (nl) {
                len = nl - str;
                memcpy(buf + strlen(buf), str, len);
            } else {
                strcat(buf, str);
            }
            strcat(buf, Msg_GetLetter(3));
            Text_Print(buf, TEXT_DRAW);
        }
        Window_PutText(win, w, 0);
    }
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        win->anim = 0;
    }
    return ret;
}

s32 LetterAnswer_Main(void)
{
    struct Window *win = &gWindows[1];
    s32 ret = 0;

    if (gMenuHasInput) {
        if (gKeysRepeat) {
            if (gKeysRepeat & DPAD_UP) {
                if (win->cursor > 0)
                    win->cursor--;
                else
                    win->cursor = win->rows - 1;
                m4aSongNumStart(1);
            } else if (gKeysRepeat & DPAD_DOWN) {
                if (win->cursor < win->rows - 1)
                    win->cursor++;
                else
                    win->cursor = 0;
                m4aSongNumStart(1);
            }
            if (!(gKeysRepeat & (DPAD_UP | DPAD_DOWN))) {
                if (gKeysNew & A_BUTTON) {
                    if (win->cursor >= win->rows - 1) {
                        sLetterResult = -1;
                    } else {
                        sLetterResult = win->cursor;
                        sLetterAnswer = win->cursor;
                    }
                    m4aSongNumStart(2);
                    ret = 1;
                } else if (gKeysNew & B_BUTTON) {
                    sLetterResult = -1;
                    ret = 1;
                    m4aSongNumStart(3);
                } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
                    m4aSongNumStart(0);
                }
            }
        }
        Letter_DrawCursor(win->x * 8 - 10, (win->y + 1) * 8 + win->cursor * 16);
    }
    return ret;
}

s32 LetterAnswer_Exit(void)
{
    struct Window *win = &gWindows[1];
    s32 ret;

    Window_Close(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        win->anim = 0;
    }
    return ret;
}

s32 LetterAttach_Init(void)
{
    struct Window *win = &gWindows[1];
    s32 w;
    s32 w2;
    s32 i;
    s32 ret;

    Text_SetFill(1, 1);
    Text_Clear();
    if (sLetterSubInit == 0) {
        memset(win, 0, sizeof(struct Window));
        w = Text_Print(Msg_GetLetter(1), TEXT_WIDTH);
        w2 = Text_Print(Msg_GetLetter(11), TEXT_WIDTH);
        if (w < w2)
            w = w2;
        w2 = Text_Print(Msg_GetLetter(12), TEXT_WIDTH);
        if (w < w2)
            w = w2;
        w2 = Text_Print(Msg_GetSystem(4), TEXT_WIDTH);
        if (w < w2)
            w = w2;
        w = (w & 7) ? (w >> 3) + 1 : w >> 3;
        win->active = 1;
        win->cursor = 0;
        win->x = (28 - w) >> 1;
        win->y = 4;
        win->rows = 4;
        win->width = w + 2;
        win->height = 10;
        win->style = 9;
        win->variant = 0;
        win->bg = 0;
        win->slot = 2;
        win->textX = 0;
        for (i = 0; i < win->rows; i++)
            win->items[i].enabled = 1;
        win->items[0].text = Msg_GetLetter(1);
        win->items[1].text = Msg_GetLetter(11);
        win->items[2].text = Msg_GetLetter(12);
        win->items[3].text = Msg_GetSystem(4);
        Window_PutText(win, 0, 0);
        sLetterFailed = 0;
        sLetterSubInit = 1;
    }
    Window_PrintNextItem(win);
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        win->anim = 0;
    }
    return ret;
}

s32 LetterAttach_Main(void)
{
    struct Window *win = &gWindows[1];
    s32 ret = 0;

    if (gMenuHasInput) {
        if (gKeysRepeat) {
            if (gKeysRepeat & DPAD_UP) {
                if (win->cursor > 0)
                    win->cursor--;
                else
                    win->cursor = win->rows - 1;
                m4aSongNumStart(1);
            } else if (gKeysRepeat & DPAD_DOWN) {
                if (win->cursor < win->rows - 1)
                    win->cursor++;
                else
                    win->cursor = 0;
                m4aSongNumStart(1);
            }
            if (!(gKeysRepeat & (DPAD_UP | DPAD_DOWN))) {
                if (gKeysNew & A_BUTTON) {
                    if (win->cursor >= win->rows - 1)
                        sLetterResult = -1;
                    else
                        sLetterResult = win->cursor;
                    m4aSongNumStart(2);
                    ret = 1;
                } else if (gKeysNew & B_BUTTON) {
                    sLetterResult = -1;
                    ret = 1;
                    m4aSongNumStart(3);
                } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
                    m4aSongNumStart(0);
                }
            }
        }
        Letter_DrawCursor(win->x * 8 - 10, (win->y + 1) * 8 + win->cursor * 16);
    }
    return ret;
}

s32 LetterAttach_Exit(void)
{
    struct Window *win = &gWindows[1];
    s32 ret;

    Window_Close(win);
    ret = 0;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        ret = 1;
        win->anim = 0;
    }
    return ret;
}

void LetterList_PrintRow(s32 idx, s32 row)
{
    char buf[64];
    struct Window tmp;
    char *src;
    struct LetterEntry *entry;
    s32 no;
    struct LetterListHeader *list = (struct LetterListHeader *)LIST_BUF;
    struct LetterEntry *entries = LETTER_ENTRIES;
    char *names = (char *)(entries + list->count);
    char *descs = names + list->subjectCount * 24;

    Text_SetFill(0, 0);
    Text_Clear();
    memset(buf, 0, sizeof(buf));
    entry = &entries[idx];
    no = entry->subject;
    src = names + no * 24;
    memcpy(buf, src, 24);
    Text_Print(buf, TEXT_DRAW);
    Text_SetX(120);
    memset(buf, 0, sizeof(buf));
    no = entry->sender;
    src = descs + no * 16;
    memcpy(buf, src, 16);
    Text_Print(buf, TEXT_DRAW);
    memcpy(&tmp, gWindows, sizeof(struct Window));
    tmp.width = 25;
    tmp.bg--;
    Window_PutText(&tmp, row, 0);
}

void LetterList_DrawRow(s32 idx, s32 row, s32 n, s32 pal)
{
    u16 buf[60];
    s32 tile = idx * (n * 2) + 128;
    u16 *map;
    s32 i;

    pal <<= 12;
    for (i = 0; i < n; i++) {
        buf[i] = tile++ | pal;
        (buf + 30)[i] = tile++ | pal;
    }
    map = Bg_GetMapPtr(gWindows[0].bg - 1, 2, row * 2 + 1);
    DmaCopy16(3, buf, map, n * 2);
    DmaCopy16(3, &buf[30], map + 32, n * 2);
}

s32 LetterList_GetRowPalette(s32 idx)
{
    struct LetterEntry *entry = &LETTER_ENTRIES[idx];
    s32 pal;

    if (entry->flags & 4)
        pal = 8;
    else if (entry->flags & 1)
        pal = 7;
    else
        pal = 9;
    return pal;
}

void LetterList_ScrollRows(s32 up)
{
    s32 step = 64;
    s32 dstRow;
    s32 srcRow;
    u8 *dst;
    u8 *src;
    s32 i;
    s32 j;

    if (up) {
        srcRow = gWindows[0].rows * 2;
        dstRow = srcRow - 2;
        step = -step;
    } else {
        dstRow = 3;
        srcRow = 1;
    }
    dst = (u8 *)Bg_GetMapPtr(gWindows[0].bg - 1, 2, dstRow);
    src = (u8 *)Bg_GetMapPtr(gWindows[0].bg - 1, 2, srcRow);
    for (i = 0; i < gWindows[0].rows - 1; i++) {
        for (j = 0; j < 2; j++) {
            DmaSet(0, dst, src, 0x80000019);
            dst += step;
            src += step;
        }
    }
}

void Letter_DrawCursor(s32 x, s32 y)
{
    Obj_Draw(x, y, 0, 45, Obj_GetPalette(0, 45), 0, 0);
}

s32 LetterList_HandleInput(void)
{
    struct LetterListHeader *list;
    struct Window *win;
    s32 ret;
    s32 pal;
    s32 row;
    s32 sel;

    if (gKeysRepeat == 0)
        return 0;
    list = (struct LetterListHeader *)LIST_BUF;
    win = gWindows;
    if (gKeysRepeat & DPAD_UP) {
        if (win->cursor) {
            win->cursor--;
            m4aSongNumStart(1);
        } else if (sLetterTop) {
            LetterList_ScrollRows(1);
            row = sLetterTop - 1;
            pal = LetterList_GetRowPalette(row);
            row = (sLetterTop - 1) % win->rows;
            LetterList_PrintRow(sLetterTop - 1, row);
            LetterList_DrawRow(row, 0, 25, pal);
            sLetterTop--;
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    } else if (gKeysRepeat & DPAD_DOWN) {
        if (sLetterTop + win->cursor + 1 < list->count) {
            if (win->cursor + 1 < win->rows) {
                win->cursor++;
            } else {
                LetterList_ScrollRows(0);
                row = win->cursor + sLetterTop + 1;
                pal = LetterList_GetRowPalette(row);
                row = (win->cursor + sLetterTop + 1) % win->rows;
                LetterList_PrintRow(win->cursor + sLetterTop + 1, row);
                LetterList_DrawRow(row, win->rows - 1, 25, pal);
                sLetterTop++;
            }
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    }
    ret = 0;
    if (!(gKeysRepeat & (DPAD_UP | DPAD_DOWN))) {
        if (gKeysNew & B_BUTTON) {
            sLetterQuit = 1;
            gOpenMenuReq = 1;
            m4aSongNumStart(3);
            return 1;
        }
        if (gKeysNew & A_BUTTON) {
            sel = win->cursor + sLetterTop;
            if (sel < list->count) {
                sLetterSel = sel;
                Link_SendRequest(2, sel);
                ret = 1;
                m4aSongNumStart(2);
            } else {
                m4aSongNumStart(0);
            }
        } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
            if (gKeysNew & R_BUTTON)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            ret = 1;
            sLetterQuit = 1;
            m4aSongNumStart(6);
        }
    }
    return ret;
}

void LetterList_DrawIcons(void)
{
    s32 *hdr = (s32 *)LIST_BUF;
    struct LetterEntry *entry = LETTER_ENTRIES;
    s32 n;
    s32 x;
    s32 y;
    s32 i;
    s32 frame;
    s32 pal;
    s32 anim;

    n = (hdr[0] > gWindows[0].rows) ? gWindows[0].rows : hdr[0];
    if (n > sLetterRow)
        n = sLetterRow;
    x = (gWindows[0].x + gWindows[0].width - 3) * 8;
    entry += sLetterTop;
    for (i = 0; i < n; i++, entry++) {
        if (entry->flags & 0x18) {
            y = (i * 2 + 1) * 8;
            frame = (entry->flags & 2) ? 0x35 : 0x34;
            Obj_Draw(x, y - 3, 0, frame, Obj_GetPalette(0, frame), 0, 0);
        }
    }
    pal = Obj_GetPalette(0, 0x2E);
    x -= 16;
    anim = (gFrameCount & 8) >> 2;
    if (sLetterTop) {
        y = anim;
        Obj_Draw(x, y, 0, 0x2E, pal, 0, 0);
    }
    if (gWindows[0].rows + sLetterTop < hdr[0]) {
        y = gWindows[0].height * 8 - 16;
        y -= anim;
        Obj_Draw(x, y, 0, 0x2E, pal, 0, 0x20000000);
    }
}

void LetterRead_PrintNextLine(void)
{
    char buf[256];
    struct Window win;
    u16 tiles[60];
    char *line = (char *)DETAIL_BUF;
    char *nl = line;
    s32 i;
    s32 w;
    s32 n;
    s32 attr;
    s32 size;
    s32 x;
    s32 y;
    u16 *dst;

    memset(buf, 0, sizeof(buf));
    memcpy(&win, gWindows, sizeof(win));
    win.bg--;
    for (i = 0; i <= sLetterRow; i++) {
        nl = strchr(line, '\n');
        if (nl && i < sLetterRow)
            line = nl + 1;
        else
            break;
    }
    if (*line == 0x1D) {
        sLetterAlign = 0;
        line++;
    } else if (*line == 0x1E) {
        sLetterAlign = 1;
        line++;
    } else if (*line == 0x1C) {
        sLetterAlign = 2;
        line++;
    }
    if (nl) {
        i = nl - line;
        memcpy(buf, line, i);
    } else {
        strcpy(buf, line);
    }
    Text_SetFill(0, 0);
    Text_Clear();
    if (sLetterAlign) {
        n = Text_Print(buf, TEXT_WIDTH);
        i = (win.width - 5) * 8;
        if (n >= i) {
            Text_SetX(0);
        } else {
            n = i - n;
            if (sLetterAlign == 1)
                n >>= 1;
            Text_SetX(n);
        }
    }
    Text_Print(buf, TEXT_DRAW);
    w = Text_GetX();
    w = (w & 7) ? (w >> 3) + 1 : w >> 3;
    Window_PutText(&win, sLetterRow, 0);
    if (w) {
        n = (win.width << 1) * sLetterRow + 0x80;
        attr = 0x7000;
        if (w >= win.width - 5)
            w = win.width - 5;
        size = w * 2;
        for (i = 0; i < w; i++) {
            tiles[i] = n++ | attr;
            tiles[i + 30] = n++ | attr;
        }
        x = win.x + 2;
        y = win.y + 1 + sLetterRow * 2;
        dst = Bg_GetMapPtr(win.bg, x, y);
        DmaCopy16(3, tiles, dst, size);
        DmaCopy16(3, tiles + 30, dst + 32, size);
    }
    sLetterRow++;
}

s32 Str_CountLines(s8 *str)
{
    s32 n = 0;
    s8 c;

    for (;;) {
        c = *str;
        if (c == '\n' || c == 0) {
            n++;
            if (c == 0)
                break;
        }
        str++;
    }
    return n;
}

void LetterRead_DrawAttachIcon(void)
{
    struct LetterEntry *entry = &LETTER_ENTRIES[sLetterSel];
    struct Window *win;
    s32 x;
    s32 y;
    s32 frame;

    if (entry->flags & 0x18) {
        win = gWindows;
        x = win->x + win->width - 5;
        y = win->y + win->height - 4;
        x *= 8;
        y *= 8;
        frame = (entry->flags & 2) ? 0x35 : 0x34;
        Obj_Draw(x, y, 0, frame, Obj_GetPalette(0, frame), win->bg - 1, 0);
    }
}

void Letter_SetGilAttachment(s32 ok, u32 value)
{
    if (ok) {
        sLetterResult = 1;
        sLetterAttachType = 16;
        sLetterAttachValue = value;
    } else {
        sLetterResult = -1;
        sLetterAttachType = 0;
        sLetterAttachValue = 0;
    }
}

void Letter_SetItemAttachment(s32 ok, u32 value, s32 idx)
{
    if (ok) {
        sLetterResult = 1;
        sLetterAttachType = 8;
        sLetterAttachValue = (idx << 16) | value;
    } else {
        sLetterResult = -1;
        sLetterAttachType = 0;
        sLetterAttachValue = 0;
    }
}

void LetterGift_DrawIcons(void)
{
    struct Window *win = &gWindows[1];
    s32 x = (win->x + 1) * 8;
    s32 y = (win->y + 1) * 8;
    s32 i;
    s32 id;
    s32 pal;
    s16 v;

    for (i = 0; i < win->rows; i++, y += 16) {
        v = gSession.items[i + sLetterGiftTop];
        if (v > 0) {
            id = Item_GetIcon(v);
            pal = Obj_GetPalette(0, id);
            Obj_Draw(x - 2, y, 0, id, pal, win->bg, 0);
        }
    }
    x = (win->x + 1) * 8;
    y = (win->y + 1) * 8;
    id = ((gLanguage & 15) == 1) ? 24 : 4;
    pal = Obj_GetPalette(2, id);
    for (i = 0; i < win->rows; i++, y += 16) {
        if (Session_IsItemInUse(i + sLetterGiftTop))
            Obj_Draw(x - 4, y, 2, id, pal, win->bg - 1, 0);
    }
}

s32 LetterGift_HandleInput(void)
{
    struct Window *win;
    s32 idx;
    s32 v;
    s32 pal;
    s32 count = 64;

    if (gKeysRepeat) {
        win = &gWindows[1];
        if (gKeysRepeat & DPAD_UP) {
            if (win->cursor) {
                win->cursor--;
                HelpWin_PrintItemDesc(gSession.items[sLetterGiftTop + win->cursor], 1, 1);
                m4aSongNumStart(1);
            } else if (sLetterGiftTop == 0) {
                m4aSongNumStart(0);
            } else {
                Window_ScrollRows(1, 1, win->bg);
                idx = sLetterGiftTop - 1;
                LetterGift_PrintItem(idx, idx % win->rows);
                v = gSession.items[idx];
                if (Session_IsItemInUse(idx) == 0) {
                    if (v <= 0x124)
                        pal = 6;
                    else
                        pal = 5;
                } else {
                    pal = 6;
                }
                Window_DrawRow(1, win->bg, idx % win->rows, 0, pal);
                sLetterGiftTop--;
                HelpWin_PrintItemDesc(gSession.items[sLetterGiftTop + win->cursor], 1, 1);
                m4aSongNumStart(1);
            }
        } else if (gKeysRepeat & DPAD_DOWN) {
            if (win->cursor < win->rows - 1) {
                win->cursor++;
                HelpWin_PrintItemDesc(gSession.items[sLetterGiftTop + win->cursor], 1, 1);
                m4aSongNumStart(1);
            } else if (sLetterGiftTop + win->rows >= count) {
                m4aSongNumStart(0);
            } else {
                Window_ScrollRows(0, 1, win->bg);
                idx = sLetterGiftTop + win->rows;
                LetterGift_PrintItem(idx, idx % win->rows);
                v = gSession.items[idx];
                if (Session_IsItemInUse(idx) == 0) {
                    if (v <= 0x124)
                        pal = 6;
                    else
                        pal = 5;
                } else {
                    pal = 6;
                }
                Window_DrawRow(1, win->bg, idx % win->rows, win->rows - 1, pal);
                sLetterGiftTop++;
                HelpWin_PrintItemDesc(gSession.items[sLetterGiftTop + win->cursor], 1, 1);
                m4aSongNumStart(1);
            }
        }
        if (!(gKeysRepeat & (DPAD_UP | DPAD_DOWN))) {
            if (gKeysNew & A_BUTTON) {
                idx = win->cursor + sLetterGiftTop;
                if (LetterGift_CanGive(idx)) {
                    sLetterResult = 1;
                    sLetterAttachType = 8;
                    sLetterAttachValue = (idx << 16) | gSession.items[idx];
                    gSubState++;
                    m4aSongNumStart(2);
                } else {
                    m4aSongNumStart(0);
                }
            }
            if (gKeysNew & B_BUTTON) {
                sLetterResult = -1;
                sLetterAttachType = 0;
                sLetterAttachValue = 0;
                gSubState++;
                m4aSongNumStart(3);
            } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
                m4aSongNumStart(0);
            }
        }
    }
    return 0;
}

s32 LetterGift_CanGive(s32 idx)
{
    s32 v = gSession.items[idx];
    s32 ret;

    if (v <= 0)
        ret = 0;
    else
        ret = Session_IsItemInUse(idx) == 0;
    if (v <= 0x124)
        ret = 0;
    return ret;
}

void LetterGift_PrintItem(s32 idx, s32 row)
{
    struct Window *win = &gWindows[1];
    s32 v;
    char *str;

    Text_SetFill(1, 0);
    Text_Clear();
    v = gSession.items[idx];
    if (v > 0) {
        Text_SetX(16);
        str = Msg_GetItemName(v);
    } else {
        str = Msg_GetSystem(0);
    }
    Text_Print(str, TEXT_DRAW);
    Window_PutText(win, row, 0);
}

void Letter_BuildText(char *buf, s32 type)
{
    s32 *hdr = (s32 *)LIST_BUF;
    struct LetterEntry *entry = LETTER_ENTRIES;
    s32 n = hdr[1] * 24;
    char *names = (char *)(entry + hdr[0]) + n;
    s32 mode;
    char *p;
    char *nl;
    s32 len;

    entry += sLetterSel;
    mode = gLanguage & 15;
    if (type == 0) {
        p = names + entry->sender * 16;
        if (mode == 1) {
            memcpy(buf, p, 16);
            strcat(buf, Msg_GetLetter(5));
        } else if (mode == 2) {
            strcpy(buf, Msg_GetLetter(5));
            len = strlen(buf);
            memcpy(buf + len, p, 16);
        } else if (mode == 3 || mode == 4) {
            strcpy(buf, Msg_GetLetter(5));
            len = strlen(buf);
            memcpy(buf + len, p, 16);
            strcat(buf, Msg_GetLetter(4));
        } else {
            strcpy(buf, Msg_GetLetter(4));
            strcat(buf, sSpaceText);
            len = strlen(buf);
            memcpy(buf + len, p, 16);
            strcat(buf, Msg_GetLetter(5));
        }
    } else if (type == 1) {
        if (mode == 2)
            strcpy(buf, Msg_GetLetter(6));
        else
            buf[0] = 0;
        p = (char *)DETAIL_BUF;
        p = strlen(p) + (char *)(DETAIL_BUF + 1);
        for (type = 0; type < sLetterAnswer; type++) {
            nl = strchr(p, '\n');
            if (nl)
                p = nl + 1;
            else
                break;
        }
        strcat(buf, Msg_GetLetter(2));
        nl = strchr(p, '\n');
        if (nl) {
            type = nl - p;
            memcpy(buf + strlen(buf), p, type);
        } else {
            strcat(buf, p);
        }
        strcat(buf, Msg_GetLetter(3));
        if (mode == 1)
            strcat(buf, Msg_GetLetter(6));
        else if (mode == 2)
            strcat(buf, sQuestionText);
    } else if (sLetterAttachType & 0x18) {
        if (mode != 1)
            strcpy(buf, Msg_GetLetter(13));
        len = strlen(buf);
        if (sLetterAttachType & 0x10) {
            IntToStr(buf + len, sLetterAttachValue);
            strcat(buf, sSpaceText);
            strcat(buf, Msg_GetSystem(5));
        } else {
            if (mode == 1)
                strcat(buf, Msg_GetLetter(2));
            strcat(buf, Msg_GetItemName((u16)sLetterAttachValue));
            if (mode == 1)
                strcat(buf, Msg_GetLetter(3));
        }
        if (mode == 1)
            strcat(buf, Msg_GetLetter(13));
    }
}
