#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "session.h"
#include "window.h"
#include "screen.h"

static s8 sGilSynced;
static u32 sGilAmount;
static u8 sGilDigits;
static s16 sGilCursorX;
static s8 sGilQuit;
static s8 sGilWaiting;

void GilScreen_DrawCursor(void);
void GilScreen_HandleInput(void);
s32 GilScreen_OpenConfirm(void);
s32 GilScreen_CloseConfirm(void);

void GilScreen_Setup(void)
{
    s32 i;
    s32 n;

    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    gWindows[0].active = 1;
    gWindows[0].x = 17;
    gWindows[0].y = 3;
    gWindows[0].rows = 4;
    gWindows[0].width = 12;
    gWindows[0].height = gWindows[0].width / 2 + 2;
    gWindows[0].style = 6;
    gWindows[0].variant = 0;
    gWindows[0].bg = 2;
    gWindows[0].slot = 0;
    gWindows[0].textX = 0;
    Window_ResetItems(&gWindows[0], 1);

    gWindows[1].active = 1;
    gWindows[1].width = 9;
    gWindows[1].x = gWindows[0].x - 9;
    gWindows[1].y = 10;
    gWindows[1].rows = 2;
    gWindows[1].height = gWindows[1].rows * 2 + 2;
    gWindows[1].style = 3;
    gWindows[1].variant = 0;
    gWindows[1].bg = 2;
    gWindows[1].slot = 1;
    gWindows[1].textX = 16;
    Window_ResetItems(&gWindows[1], 1);
    for (i = 0; i < gWindows[1].rows; i++) {
        if (i == 0 && (gMask & 0x100))
            gWindows[1].items[i].enabled = 0;
        else
            gWindows[1].items[i].enabled = 1;
        if (i == 0)
            gWindows[1].items[0].text = Msg_GetSystem(34);
        else
            gWindows[1].items[i].text = Msg_GetSystem(4);
    }

    Text_LoadPalette(3, 0, 0);
    Font_LoadPalette(0x050000E0, 0);
    Font_LoadPalette(0x05000100, 2);
    Obj_AllocPalette(9, 0);
    Obj_AllocPalette(6, 0);
    Obj_LoadToBg(9, 0, 2, 0);
    Obj_LoadToBg(6, 1, 2, 0);
    Text_CopyFill(0x06008400);
    sGilAmount = 0;
    for (i = 1, n = 10; i <= 7 && gSession.gil / n != 0; i++, n *= 10)
        ;
    sGilDigits = i;
    n = (gWindows[0].width * 8 - 80) >> 1;
    sGilCursorX = (gWindows[0].x << 3) + n + 56;
    gSubMode = 0;
    gSubState = 0;
    sGilWaiting = 0;
    sGilQuit = 0;
    for (i = 0; i <= 9; i++) {
        n = Link_SendEvent(21, 0, 0);
        if (n == 0)
            break;
    }
    sGilSynced = i <= 9;
    gScreenInitDone = 1;
}

s32 GilScreen_Init(void)
{
    struct Window *win;
    s32 ret = 0;

    if (gScreenInitDone == 0)
        GilScreen_Setup();
    Text_SetFill(1, 0);
    Text_Clear();
    win = gWindows;
    Window_PrintNextItem(win);
    Window_Open(win);
    if ((win->anim >> 3) >= win->height - 2) {
        win->anim = 0;
        ret = 1;
    } else {
        win->anim += 8;
    }
    return ret;
}

s32 GilScreen_Main(void)
{
    struct Window *win;
    s32 x;
    s32 i;
    s32 ret;

    if (sGilSynced == 0) {
        for (i = 0; i <= 9; i++) {
            ret = Link_SendEvent(21, 0, 0);
            if (ret == 0)
                break;
        }
        if (i > 9) {
            if (gKeysNew & A_BUTTON) {
                m4aSongNumStart(0);
            } else if (gKeysNew & B_BUTTON) {
                sGilQuit = 1;
                gOpenMenuReq = 1;
                m4aSongNumStart(3);
                return 1;
            } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
                if (gKeysNew & R_BUTTON)
                    gScreenStep = 1;
                else
                    gScreenStep = -1;
                ret = 1;
                sGilQuit = ret;
                m4aSongNumStart(6);
                return ret;
            }
            return 0;
        }
        sGilSynced = 1;
    }
    if (gSession.gil < sGilAmount)
        sGilAmount = gSession.gil;
    if (gSubMode && gSubState == 0) {
        ret = GilScreen_OpenConfirm();
        if (ret) {
            gSubState++;
            gWindows[1].anim = 0;
        }
    } else if (!gSubMode || (gSubState == 1 && sGilWaiting == 0)) {
        if (gMenuHasInput)
            GilScreen_HandleInput();
    } else if (gSubState == 1) {
        u16 key = gDataFlags & DATA_REPLY;

        if (key) {
            if (gReplyResult)
                sGilWaiting = 0;
            else
                gSubState = 2;
            sGilAmount = 0;
            Reply_Clear();
        } else if (Reply_IsTimedOut()) {
            m4aSongNumStart(0);
            sGilWaiting = key;
            Reply_Clear();
            sGilAmount = key;
        }
    } else {
        ret = GilScreen_CloseConfirm();
        if (ret) {
            gSubState = 0;
            gWindows[1].anim = 0;
            gSubMode = 0;
        }
    }
    if (gMenuHasInput)
        GilScreen_DrawCursor();
    win = gWindows;
    x = win->x * 8;
    ret = (win->y + 1) * 8;
    Obj_DrawGil(x, ret, win->width, win->bg, gSession.gil, -1);
    ret = (win->y + 4) * 8;
    Obj_DrawGil(x, ret, win->width, win->bg, sGilAmount, 4);
    ret = sGilQuit != 0;
    return ret;
}

s32 GilScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 2) {
        ret = 1;
        win->anim = 0;
        Obj_FreePalette(9);
        Obj_FreePalette(6);
    } else {
        win->anim += 8;
    }
    return ret;
}

void GilScreen_DrawCursor(void)
{
    struct Window *win;
    s32 x, y;

    if (gSubMode == 0) {
        win = gWindows;
        x = sGilCursorX - win->cursor * 8;
        y = (win->y + win->height - 2) * 8;
        Obj_Draw(x, y, 2, 5, Obj_GetPalette(2, 5), win->bg, 0);
    } else if (gSubState == 1) {
        win = &gWindows[1];
        x = win->x * 8 - 8;
        y = (win->y + 1) * 8;
        y += win->cursor * 16;
        Obj_Draw(x, y, 0, 45, Obj_GetPalette(0, 45), 1, 0);
    }
}

void GilScreen_HandleInput(void)
{
    if (gKeysRepeat == 0)
        return;
    if (gSubMode == 0) {
        if (gSession.gil != 0) {
            struct Window *win = gWindows;
            u32 step = 1;
            s32 i;

            i = 0;
            while (i < win->cursor) {
                i++;
                step *= 10;
            }
            if (gKeysRepeat & DPAD_UP) {
                if (gSession.gil >= sGilAmount + step)
                    sGilAmount += step;
                else
                    sGilAmount = 0;
                m4aSongNumStart(1);
            } else if (gKeysRepeat & DPAD_DOWN) {
                s32 val = sGilAmount - step;

                if (val < 0)
                    val = gSession.gil;
                sGilAmount = val;
                m4aSongNumStart(1);
            }
            if (gKeysRepeat & DPAD_LEFT) {
                if (win->cursor < sGilDigits - 1) {
                    win->cursor++;
                    m4aSongNumStart(1);
                } else {
                    m4aSongNumStart(0);
                }
            } else if (gKeysRepeat & DPAD_RIGHT) {
                if (win->cursor != 0) {
                    win->cursor--;
                    m4aSongNumStart(1);
                } else {
                    m4aSongNumStart(0);
                }
            }
        }
        if (gKeysRepeat & DPAD_ANY)
            return;
        if (gKeysNew & A_BUTTON) {
            if ((s32)sGilAmount > 0) {
                if (gLetterAttachKind) {
                    Letter_SetGilAttachment(1, sGilAmount);
                    sGilQuit = 1;
                } else {
                    gSubMode = 1;
                    gSubState = 0;
                }
                m4aSongNumStart(2);
            } else {
                m4aSongNumStart(0);
            }
        } else if (gKeysNew & B_BUTTON) {
            if (gLetterAttachKind)
                Letter_SetGilAttachment(0, 0);
            else
                gOpenMenuReq = 1;
            sGilQuit = 1;
            m4aSongNumStart(3);
        } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
            if (gLetterAttachKind) {
                m4aSongNumStart(0);
            } else {
                if (gKeysNew & R_BUTTON)
                    gScreenStep = 1;
                else
                    gScreenStep = -1;
                m4aSongNumStart(6);
                sGilQuit = 1;
            }
        }
    } else {
        struct Window *win = &gWindows[1];

        if (gKeysRepeat & (DPAD_UP | DPAD_DOWN)) {
            win->cursor ^= 1;
            m4aSongNumStart(1);
        }
        if (gKeysRepeat & (DPAD_UP | DPAD_DOWN))
            return;
        if (gKeysNew & A_BUTTON) {
            if (win->cursor < win->rows - 1) {
                Link_SendGil(1, sGilAmount);
                sGilWaiting = 1;
                Reply_Clear();
                gReplyWaiting = 1;
            } else {
                gSubState++;
            }
            m4aSongNumStart(2);
        } else if (gKeysNew & B_BUTTON) {
            gSubState++;
            m4aSongNumStart(3);
        } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
            m4aSongNumStart(0);
        }
    }
}

s32 GilScreen_OpenConfirm(void)
{
    struct Window *win = &gWindows[1];
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
        sGilWaiting = 0;
        ret = 1;
    }
    win->anim += 8;
    return ret;
}

s32 GilScreen_CloseConfirm(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[1];

    Text_SetFill(0, 0);
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 1) {
        sGilWaiting = 0;
        ret = 1;
    }
    win->anim += 8;
    return ret;
}
