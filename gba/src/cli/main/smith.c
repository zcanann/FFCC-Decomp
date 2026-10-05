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

#if !defined(VERSION_GCCP01)
#define SMITH_ACTION_WIDTH 7
#define SMITH_EQUIP_ACTION_X 6
#define SMITH_CURRENCY_MSG 5
#else
#define SMITH_ACTION_WIDTH 9
#define SMITH_EQUIP_ACTION_X 4
#define SMITH_CURRENCY_MSG 13
#endif

static s8 sSmithTop;
static s8 sSmithRow;
static s8 sSmithResult;
static s8 sSmithSel;
static s8 sSmithCanForge;
static s8 sSmithWaiting;
static s8 sSmithResultSlot;
static s8 sSmithCanEquip;
static s8 sSmithSlotsInit;
static s8 sSmithEquipPending;
static s8 sSmithVariant;
static s8 sSmithRowOffset;
static s8 sSmithListValid;
static s8 sSmithKnownLoaded;
static u32 sSmithKnown[4];
#if !defined(VERSION_GCCJGC)
const char sPluralText[] = "s";
#endif

void SmithForge_DrawRow(s32, s32);
s32 SmithForge_OpenConfirm(void);
s32 SmithForge_CloseConfirm(void);
s32 Smith_EquipResult(s32);
void SmithTopScreen_PrintRow(s32, s32);
s32 Smith_IsRecipeKnown(s32);
s32 Smith_GetItem(s32);
s32 SmithTopScreen_HandleInput(void);
void SmithTopScreen_DrawCursor(void);
void SmithTopScreen_DrawIcons(void);
void SmithForge_ClearRows(void);
void SmithForge_DrawCursor(void);
s32 SmithForge_HandleInput(void);
void SmithForgeScreen_PrintNextRow(void);
void SmithEquipScreen_PrintNextRow(void);
s32 SmithEquip_OpenSlots(void);
s32 SmithEquip_CloseSlots(void);
void SmithEquip_DrawSlotIcons(void);

static inline struct Recipe *GetRecipe(void)
{
    u8 *list = LIST_BUF;
    s32 n = (s8)list[0];
    struct Recipe *p;

    n++;
    if (n & 3)
        n = ((n >> 2) + 1) << 2;
    p = (struct Recipe *)(list + n);
    return &p[sSmithSel];
}

void SmithTopScreen_Setup(void)
{
    s32 i;

    Bg_SetScroll(15, 0, 0);
    Link_SendRequest(REQ_SMITH_LIST, 0);
    gSubState = 0;
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    ListWin_Setup(0, 16, 0, 2);
    gSubMode = 0;
    Text_LoadPalette(3, 0, 0);
    Text_LoadPalette(4, 2, 0);
    Font_LoadPalette(0x05000100, 1);
    Obj_AllocPalette(3, 0);
    Obj_LoadToBg(3, 0, 2, 0);
    Text_CopyFill(0x06008000);
    Window_ResetItems(gWindows, 1);
    sSmithResult = 0;
    sSmithRow = 0;
    if (sSmithListValid == 0) {
        sSmithTop = 0;
        sSmithRowOffset = 0;
        sSmithListValid = 1;
    } else {
        gWindows[0].cursor = sSmithSel - sSmithTop;
        sSmithRowOffset = gWindows[0].rows - sSmithTop % gWindows[0].rows;
    }
    sSmithKnownLoaded = 0;
    for (i = 0; i < 4; i++)
        sSmithKnown[i] = 0;
    HelpWin_Clear(1, 1);
    HelpWin_DrawFrame(1, 1, 8);
    sSmithSel = 0;
    gScreenInitDone = 1;
}

s32 SmithTopScreen_Init(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0)
        SmithTopScreen_Setup();
    win = gWindows;
    Text_SetFill(1, 0);
    Text_Clear();
    Window_PrintNextItem(win);
    Window_Open(win);
    if ((win->anim >> 3) >= win->height - 2) {
        ret = 1;
        win->anim = 0;
    } else {
        win->anim += 8;
    }
    return ret;
}

s32 SmithTopScreen_Main(void)
{
    struct Window *win;
    s32 count;
    u8 *p;
    s32 idx;
    s32 ret;

    if (!(gDataFlags & DATA_SMITH_LIST)) {
        if (gKeysNew & B_BUTTON) {
            sSmithResult = -1;
            m4aSongNumStart(3);
            Link_SendEvent(EVT_SMITH_LEAVE, 0, 0);
            return 1;
        }
        return 0;
    }
    win = gWindows;
    count = (s8)LIST_BUF[0];
    if (sSmithKnownLoaded == 0) {
        idx = ((count + 1) >> 2) * 4;
        if ((count + 1) & 3)
            idx += 4;
        p = &LIST_BUF[idx];
        p += count * 56;
        memcpy(sSmithKnown, p, 16);
        sSmithKnownLoaded = 1;
    }
    if (sSmithRow < count && sSmithRow < win->rows) {
        idx = sSmithRow + sSmithTop;
        SmithTopScreen_PrintRow(idx, sSmithRow);
        Window_DrawRow(0, win->bg, sSmithRow, sSmithRow, Smith_IsRecipeKnown(idx) ? 3 : 4);
        sSmithRow++;
        if (sSmithRow < count && sSmithRow < win->rows)
            return 0;
        idx = win->cursor + sSmithTop;
        HelpWin_PrintItemDesc(Smith_GetItem(idx), 1, 1);
    }
    Text_SetFill(1, 0);
    ret = 0;
    if (gMenuHasInput) {
        ret = SmithTopScreen_HandleInput();
        SmithTopScreen_DrawCursor();
    }
    SmithTopScreen_DrawIcons();
    if (ret)
        HelpWin_Clear(1, 1);
    return ret;
}

s32 SmithTopScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    Text_Clear();
    win = gWindows;
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 2) {
        ret = sSmithResult;
        Obj_FreePalette(3);
    }
    win->anim += 8;
    return ret;
}

void SmithTopScreen_DrawCursor(void)
{
    s32 x = (gWindows[0].x - 1) * 8;
    s32 y = (gWindows[0].y + 1) * 8 + gWindows[0].cursor * 16;

    Obj_Draw(x, y, 0, 45, Obj_GetPalette(0, 45), 2, 0);
}

s32 SmithTopScreen_HandleInput(void)
{
    struct Window *win;
    s32 count;
    s32 ret;
    s32 idx;
    s32 row;
    u8 *list = LIST_BUF;

    if (gKeysRepeat == 0)
        return 0;
    count = (s8)list[0];
    ret = 0;
    win = gWindows;
    if (gKeysRepeat & DPAD_UP) {
        if (win->cursor != 0) {
            win->cursor--;
            idx = sSmithTop + win->cursor;
            HelpWin_PrintItemDesc(Smith_GetItem(idx), 1, 1);
            m4aSongNumStart(1);
        } else if (sSmithTop != 0) {
            s32 pal;

            Window_ScrollRows(1, 0, win->bg);
            idx = sSmithTop - 1;
            row = idx + sSmithRowOffset;
            SmithTopScreen_PrintRow(idx, row % win->rows);
            pal = Smith_IsRecipeKnown(idx) ? 3 : 4;
            Window_DrawRow(0, win->bg, row % win->rows, 0, pal);
            sSmithTop--;
            idx = sSmithTop + win->cursor;
            HelpWin_PrintItemDesc(Smith_GetItem(idx), 1, 1);
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    } else if (gKeysRepeat & DPAD_DOWN) {
        if (win->cursor < win->rows - 1) {
            win->cursor++;
            idx = sSmithTop + win->cursor;
            HelpWin_PrintItemDesc(Smith_GetItem(idx), 1, 1);
            m4aSongNumStart(1);
        } else if (sSmithTop + win->rows >= count) {
            m4aSongNumStart(0);
        } else {
            s32 pal;

            Window_ScrollRows(0, 0, win->bg);
            idx = sSmithTop + win->rows;
            row = idx + sSmithRowOffset;
            SmithTopScreen_PrintRow(idx, row % win->rows);
            pal = Smith_IsRecipeKnown(idx) ? 3 : 4;
            Window_DrawRow(0, win->bg, row % win->rows, win->rows - 1, pal);
            sSmithTop++;
            idx = sSmithTop + win->cursor;
            HelpWin_PrintItemDesc(Smith_GetItem(idx), 1, 1);
            m4aSongNumStart(1);
        }
    }
    if (!(gKeysRepeat & (DPAD_UP | DPAD_DOWN))) {
        if (gKeysNew & A_BUTTON) {
            idx = sSmithTop + win->cursor;
            if (idx >= count || (s8)list[idx] < 0 || !Smith_IsRecipeKnown(idx)) {
                m4aSongNumStart(0);
            } else {
                sSmithResult = 1;
                ret = 1;
                sSmithSel = idx;
                m4aSongNumStart(2);
            }
        }
        if (gKeysNew & B_BUTTON) {
            gInputLockFrames = 6;
            sSmithResult = -1;
            ret = 1;
            Link_SendEvent(EVT_SMITH_LEAVE, 0, 0);
            m4aSongNumStart(3);
        }
    }
    return ret;
}

/*
 * --INFO--
 * PAL Address: 0x020184AC
 * PAL Size: 196b
 * EN Address: 0x020182BC
 * EN Size: 196b
 * JP Address: 0x0201782C
 * JP Size: 196b
 */
void SmithTopScreen_DrawIcons(void)
{
    struct Window *win = gWindows;
    s32 x = (win->x + 1) * 8;
    s32 y = (win->y + 1) * 8;
#if defined(VERSION_GCCJGC)
    s32 frame = 50;
#else
    s32 frame = 48;
#endif
    s32 pal = Obj_GetPalette(0, frame);
    s32 count = (s8)LIST_BUF[0];
    s32 i;
    s32 flags;

    for (i = 0; i < win->rows && i + sSmithTop < count; i++, y += 16)
        Obj_Draw(x, y, 0, frame, pal, win->bg, 0);
    flags = sSmithTop != 0;
    if (sSmithTop + win->rows < count)
        flags |= 2;
    Window_DrawScrollArrows(0, win->bg, flags);
}

/*
 * --INFO--
 * PAL Address: 0x02018570
 * PAL Size: 404b
 * EN Address: 0x02018380
 * EN Size: 404b
 * JP Address: 0x020178F0
 * JP Size: 388b
 */
void SmithForgeScreen_Setup(void)
{
    s32 i;

    gSubState = 0;
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    gWindows[0].active = 1;
    gWindows[0].cursor = 0;
    gWindows[0].x = 0;
    gWindows[0].y = 0;
    gWindows[0].rows = 8;
    gWindows[0].width = 30;
    gWindows[0].height = 18;
    gWindows[0].style = 13;
    gWindows[0].variant = 0;
    gWindows[0].bg = 2;
    gWindows[0].slot = 0;
    gWindows[0].textX = 0;
    gWindows[1].active = 1;
    gWindows[1].cursor = 0;
    gWindows[1].x = 2;
    gWindows[1].y = 13;
    gWindows[1].rows = 2;
    gWindows[1].width = SMITH_ACTION_WIDTH;
    gWindows[1].height = 4;
    gWindows[1].style = 3;
    gWindows[1].variant = 0;
    gWindows[1].bg = 1;
    gWindows[1].slot = 1;
    gWindows[1].textX = 0;
    Text_LoadPalette(3, 0, 0);
    Text_LoadPalette(4, 4, 0);
    Text_LoadPalette(5, 3, 0);
    Font_LoadPalette(0x050000E0, 0);
    Font_LoadPalette(0x05000100, 2);
    Obj_AllocPalette(16, 0);
    Obj_AllocPalette(6, 0);
    Obj_LoadToBg(16, 0, 2, 0);
    Obj_LoadToBg(6, 1, 1, 0);
    Text_CopyFill(0x06008000);
    Window_ResetItems(&gWindows[0], 1);
    for (i = 0; i < gWindows[1].rows; i++) {
        gWindows[1].items[i].enabled = 1;
        if (i == 0)
            gWindows[1].items[0].text = Msg_GetSystem(25);
        else
            gWindows[1].items[i].text = Msg_GetSystem(4);
    }
    gSubMode = 0;
    sSmithResult = 0;
    gSubMode = 0;
    sSmithRow = 0;
    sSmithCanForge = 1;
    sSmithWaiting = 0;
    sSmithCanEquip = 0;
    sSmithVariant = 0;
    gScreenInitDone = 1;
}

s32 SmithForgeScreen_Init(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0)
        SmithForgeScreen_Setup();
    win = gWindows;
    Text_SetFill(1, 0);
    Text_Clear();
    Window_PrintNextItem(win);
    Window_Open(win);
    if ((win->anim >> 3) >= win->height - 2) {
        ret = 1;
        SmithForge_ClearRows();
    }
    win->anim += 8;
    return ret;
}

s32 SmithForgeScreen_Main(void)
{
    struct Window *win = gWindows;
    s32 id;
    s32 x, y;
    s32 frame;
    s32 ret;

    SmithForgeScreen_PrintNextRow();
    if (sSmithRow < win->rows)
        return 0;
    Text_SetFill(1, 0);
    id = GetRecipe()->ids[sSmithVariant];
    x = (win->x + 1) * 8;
    y = (win->y + 1) * 8;
    frame = Item_GetIcon(id);
    Obj_Draw(x, y, 0, frame, Obj_GetPalette(0, frame), win->bg, 0);
    ret = 0;
    if (gSubMode == 0 || gSubState == 1) {
        if (sSmithWaiting == 0) {
            if (gMenuHasInput)
                ret = SmithForge_HandleInput();
        } else if (gDataFlags & DATA_REPLY) {
            if (gReplyResult) {
                m4aSongNumStart(0);
            } else {
                gSubState++;
                sSmithResult = 1;
            }
            Reply_Clear();
            sSmithWaiting = 0;
        } else if (Reply_IsTimedOut()) {
            m4aSongNumStart(0);
            sSmithWaiting = 0;
            Reply_Clear();
            gInputLockFrames = 6;
        }
    } else if (gSubState == 0) {
        ret = SmithForge_OpenConfirm();
        if (ret) {
            gSubState++;
            gWindows[1].anim = 0;
        }
        ret = 0;
    } else if (gSubState == 2) {
        ret = SmithForge_CloseConfirm();
        if (ret) {
            gSubState = 0;
            gWindows[1].anim = 0;
            gSubMode = 0;
            if (sSmithResult)
                ret = sSmithResult;
            else
                ret = 0;
        }
    }
    if (gSubMode && gMenuHasInput)
        SmithForge_DrawCursor();
    return ret;
}

s32 SmithForgeScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    Text_Clear();
    win = gWindows;
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 2) {
        gInputLockFrames = 6;
        ret = sSmithResult;
        Obj_FreePalette(16);
        Obj_FreePalette(6);
        if (ret > 0)
            sSmithListValid = 0;
    }
    win->anim += 8;
    return ret;
}

void SmithForge_DrawCursor(void)
{
    struct Window *win;
    s32 x, y;

    if (gSubMode == 1)
        win = &gWindows[1];
    else
        win = &gWindows[3];
    x = (win->x - 1) * 8;
    if (gSubMode == 1)
        y = win->y * 8 + win->cursor * 16;
    else
        y = (win->y + 1) * 8 + win->cursor * 16;
    Obj_Draw(x, y, 0, 45, Obj_GetPalette(0, 45), 1, 0);
}

s32 SmithForge_HandleInput(void)
{
    struct Window *win;
    s32 ret;
    s8 sel;
    u8 *p;

    if (gKeysRepeat == 0)
        return 0;
    ret = 0;
    win = NULL;
    if (gSubMode) {
        if (gSubMode == 1)
            win = &gWindows[1];
        else
            win = &gWindows[3];
        if (gKeysRepeat & (DPAD_UP | DPAD_DOWN)) {
            win->cursor ^= 1;
            m4aSongNumStart(1);
        }
    }
    if (gSubMode == 0 || !(gKeysRepeat & (DPAD_UP | DPAD_DOWN))) {
        if (gKeysNew & A_BUTTON) {
            if (gSubMode == 0) {
                if (gScreen == SCREEN_SMITH_FORGE) {
                    if (sSmithCanForge == 0) {
                        m4aSongNumStart(0);
                        return 0;
                    } else {
                        gSubMode++;
                    }
                } else {
                    if (sSmithCanEquip == 0) {
                        sSmithResult = 1;
                        ret = 1;
                    } else {
                        gSubMode++;
                    }
                }
            } else if (gSubMode == 1) {
                switch (win->cursor) {
                case 0:
                    if (gScreen == SCREEN_SMITH_FORGE) {
                        sel = win->cursor;
                        if (win->items[sel].enabled != 0) {
                            s32 slot = gSession.appearance & 3;
                            p = &LIST_BUF[sSmithSel];
                            Link_SendEvent(EVT_SMITH_FORGE, p[1], slot);
                            sSmithWaiting = 1;
                            Reply_Clear();
                            gReplyWaiting = 1;
                        } else {
                            m4aSongNumStart(0);
                            return 0;
                        }
                    } else {
                        if (Smith_EquipResult(sSmithResultSlot) == 0) {
                            sSmithResult = 1;
                            gInputLockFrames = 6;
                        } else {
                            sSmithSlotsInit = 0;
                            sSmithEquipPending = 1;
                        }
                        gSubState++;
                        ret = 0;
                    }
                    break;
                default:
                    gSubState++;
                    break;
                }
            } else {
                gSession.equipment[win->cursor + 3] = sSmithResultSlot;
                Link_SendEquipSlot(win->cursor + 3, sSmithResultSlot);
                gInputLockFrames = 6;
                m4aSongNumStart(2);
                sSmithResult = 1;
                gSubState++;
            }
            m4aSongNumStart(2);
        }
        if (gKeysNew & B_BUTTON) {
            if (gSubMode == 0) {
                sSmithResult = -1;
                ret = 1;
            } else {
                if (gScreen == SCREEN_SMITH_EQUIP)
                    sSmithResult = -1;
                gSubState++;
            }
            m4aSongNumStart(3);
        }
    }
    return ret;
}

/*
 * --INFO--
 * PAL Address: 0x02018C38
 * PAL Size: 1144b
 * EN Address: 0x02018A48
 * EN Size: 1164b
 * JP Address: 0x02017FAC
 * JP Size: 1140b
 */
void SmithForgeScreen_PrintNextRow(void)
{
    char buf[64];
    struct Window *win = gWindows;
    struct Recipe *recipe;
    u8 *list;
    u32 dst;
    s32 i, j;
    s32 id;
    s32 n;
    s32 cnt;
    s32 w;
    s32 x;

    if (sSmithRow >= win->rows)
        return;
    list = LIST_BUF;
    x = (s8)list[0];
    x++;
    if (x & 3)
        x = ((x >> 2) + 1) << 2;
    recipe = (struct Recipe *)(list + x);
    recipe += sSmithSel;
    n = gSession.appearance & 3;
    Text_SetFill(1, 0);
    Text_Clear();
    dst = win->width * (sSmithRow << 6) + 0x06009000;
    if (sSmithRow == 0) {
        if (recipe->ids[n] > 0) {
            sSmithVariant = n;
        } else {
            for (i = 0; i <= 3; i++) {
                if (i != n && recipe->ids[i] != 0) {
                    sSmithVariant = i;
                    break;
                }
            }
        }
        id = recipe->ids[sSmithVariant];
        Text_SetX(16);
        Text_Print(Msg_GetItemName(id), TEXT_DRAW);
        Text_CopyToVram(dst, win->width);
        x = Item_CanEquip(&recipe->items[sSmithVariant].flags);
        if (x) {
            sSmithCanEquip = 1;
        } else {
            sSmithCanEquip = 0;
            sSmithCanForge = 0;
        }
        if (sSmithCanForge) {
            if (recipe->price > gSession.gil)
                sSmithCanForge = 0;
            if (sSmithCanForge) {
                for (i = 0; i < 3 && (x = recipe->materials[i]) != 0; i++) {
                    cnt = 0;
                    for (j = 0; j < 64; j++) {
                        if (gSession.items[j] == x)
                            cnt++;
                    }
                    if (recipe->counts[i] > cnt)
                        sSmithCanForge = 0;
                }
            }
        }
        n = sSmithCanForge ? 4 : 5;
        SmithForge_DrawRow(sSmithRow, n);
    } else if (sSmithRow == 1) {
        w = Text_Print(Msg_GetSystem(17), TEXT_WIDTH);
#if !defined(VERSION_GCCP01)
        x = 88;
#else
        x = 104;
#endif
        Text_SetX(x - w);
        Text_Print(Msg_GetSystem(17), TEXT_DRAW);
#if !defined(VERSION_GCCP01)
        Text_SetX(96);
        Text_Print(Msg_GetSystem(19), TEXT_DRAW);
#endif
        Text_SetX(108);
        Item_FormatWearer(&recipe->items[sSmithVariant].flags, buf);
        Text_Print(buf, TEXT_DRAW);
        Text_CopyToVram(dst, win->width);
        n = sSmithCanEquip ? 3 : 5;
        SmithForge_DrawRow(sSmithRow, n);
    } else if (sSmithRow == 2) {
        w = Text_Print(Msg_GetSystem(22), TEXT_WIDTH);
        x = 104 - w;
        Text_SetX(x);
        Text_Print(Msg_GetSystem(22), TEXT_DRAW);
        Text_SetX(112);
        Text_Print(Msg_GetSystem(18), TEXT_DRAW);
        Text_SetX(128);
        Text_Print(Msg_GetSystem(21), TEXT_DRAW);
        Text_CopyToVram(dst, win->width);
        SmithForge_DrawRow(sSmithRow, 3);
    } else if (sSmithRow == 3) {
        w = Text_Print(Msg_GetSystem(SMITH_CURRENCY_MSG), TEXT_WIDTH) + 72;
        x = 104 - w;
        Text_PrintNumber(recipe->price, x, 8);
        Text_Print(Msg_GetSystem(SMITH_CURRENCY_MSG), TEXT_DRAW);
        Text_SetX(112);
        Text_Print(Msg_GetSystem(18), TEXT_DRAW);
        x = (win->width - 2) * 8 - w;
        Text_PrintNumber(gSession.gil, x, 8);
        Text_Print(Msg_GetSystem(SMITH_CURRENCY_MSG), TEXT_DRAW);
        Text_CopyToVram(dst, win->width);
        x = recipe->price > gSession.gil ? 5 : 3;
        SmithForge_DrawRow(sSmithRow, x);
    } else if (sSmithRow == 4) {
        w = Text_Print(Msg_GetSystem(23), TEXT_WIDTH);
        x = 104 - w;
        Text_SetX(x);
        Text_Print(Msg_GetSystem(23), TEXT_DRAW);
        Text_SetX(152);
        Text_Print(Msg_GetSystem(24), TEXT_DRAW);
        Text_CopyToVram(dst, win->width);
        SmithForge_DrawRow(sSmithRow, 3);
    } else {
        id = recipe->materials[sSmithRow - 5];
        if (id == 0) {
            sSmithRow = win->rows;
            return;
        }
        cnt = 0;
        for (i = 0; i < 64; i++) {
            if (gSession.items[i] == id)
                cnt++;
        }
        w = Text_Print(Msg_GetItemName(id), TEXT_WIDTH);
        x = 104 - w;
        Text_SetX(x);
        Text_Print(Msg_GetItemName(id), TEXT_DRAW);
        Text_SetX(112);
        Text_Print(Msg_GetSystem(20), TEXT_DRAW);
        Text_PrintNumber(recipe->counts[sSmithRow - 5], 126, 2);
        Text_SetX(152);
        Text_Print(Msg_GetSystem(18), TEXT_DRAW);
        Text_PrintNumber(cnt, 166, 2);
        Text_CopyToVram(dst, win->width);
        x = recipe->counts[sSmithRow - 5] > cnt ? 5 : 3;
        SmithForge_DrawRow(sSmithRow, x);
    }
    sSmithRow++;
}

void SmithForge_ClearRows(void)
{
    u16 buf[2][30];
    struct Window *win = gWindows;
    s32 attr = 3 << 12;
    s32 i;
    s32 size;
    u16 *map;

    for (i = 0; i < win->width; i++) {
        if (!(i & 1)) {
            buf[0][i] = attr;
            buf[1][i] = attr | 1;
        } else {
            buf[0][i] = attr | 2;
            buf[1][i] = attr | 3;
        }
    }
    map = Bg_GetMapPtr(win->bg, win->x + 1, win->y + 1);
    size = (win->width - 2) * 2;
    for (i = 1; i < win->height - 1; i++) {
        if (i & 1) {
            DmaSet(3, buf[0], map, 0x80000000 | (size / 2));
        } else {
            DmaSet(3, buf[1], map, 0x80000000 | (size / 2));
        }
        map += 32;
    }
}

void SmithForge_DrawRow(s32 idx, s32 pal)
{
    u16 buf[30];
    struct Window *win = gWindows;
    s32 attr = pal << 12;
    s32 y = win->y + 1 + idx * 2;
    s32 w;
    s32 t;
    s32 i;
    s32 j;
    s32 bg;
    s32 row;
    u16 *map;

    if (gScreen == SCREEN_SMITH_EQUIP && idx != 0)
        y++;
    w = win->width - 2;
    for (i = 0; i < 2; i++) {
        t = (win->width << 1) * idx + 128;
        t += i;
        j = 0;
        bg = win->bg;
        row = y + i;
        for (; j < w; j++) {
            if (!(j & 1)) {
                buf[j] = attr | t;
            } else {
                buf[j] = (t + 2) | attr;
                t += 4;
            }
        }
        map = Bg_GetMapPtr(bg, win->x + 1, row);
        DmaCopy16(3, buf, map, w << 1);
    }
}

s32 SmithForge_OpenConfirm(void)
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
        sSmithWaiting = ret;
        ret = 1;
    }
    win->anim += 8;
    return ret;
}

s32 SmithForge_CloseConfirm(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[1];

    Text_SetFill(0, 0);
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 1) {
        sSmithWaiting = ret;
        ret = 1;
    }
    win->anim += 8;
    return ret;
}

void Smith_SetResultSlot(s8 val)
{
    sSmithResultSlot = val;
}

/*
 * --INFO--
 * PAL Address: 0x0201931C
 * PAL Size: 476b
 * EN Address: 0x02019140
 * EN Size: 476b
 * JP Address: 0x0201868C
 * JP Size: 496b
 */
void SmithEquipScreen_Setup(void)
{
    s32 i;

    gSubState = 0;
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);

    gWindows[0].active = 1;
    gWindows[0].cursor = 0;
    gWindows[0].x = 13;
    gWindows[0].y = 1;
    gWindows[0].rows = 5;
    gWindows[0].width = 16;
    gWindows[0].height = 11;
    gWindows[0].style = 13;
    gWindows[0].variant = 0;
    gWindows[0].bg = 2;
    gWindows[0].slot = 0;
    gWindows[0].textX = 0;
    gWindows[0].skipRows = 1;

    gWindows[1].active = 1;
    gWindows[1].cursor = 0;
    gWindows[1].x = SMITH_EQUIP_ACTION_X;
    gWindows[1].y = 12;
    gWindows[1].rows = 2;
    gWindows[1].width = SMITH_ACTION_WIDTH;
    gWindows[1].height = 4;
    gWindows[1].style = 3;
    gWindows[1].variant = 0;
    gWindows[1].bg = 1;
    gWindows[1].slot = 1;
    gWindows[1].textX = 0;

    Text_LoadPalette(3, 0, 0);
    Text_LoadPalette(4, 4, 0);
    Text_LoadPalette(5, 3, 0);
    Font_LoadPalette(0x050000E0, 0);
    Font_LoadPalette(0x05000100, 2);
    Obj_AllocPalette(16, 0);
    Obj_AllocPalette(6, 0);
    Obj_AllocPalette(12, 0);
    Obj_LoadToBg(16, 0, 2, 0);
    Obj_LoadToBg(6, 1, 1, 0);
    Obj_LoadToBg(12, 3, 1, 0);
    Text_CopyFill(0x06008000);
    Text_SetFill(1, 1);
    Text_Clear();
    Text_LoadPalette(6, 0, 1);
    Text_CopyFill(0x06000C00);
    Window_ResetItems(gWindows, 1);
    for (i = 0; i < 16; i++)
        ;
    for (i = 0; i < gWindows[1].rows; i++) {
        gWindows[1].items[i].enabled = 1;
        if (i == 0)
            gWindows[1].items[i].text = Msg_GetSystem(26);
        else
            gWindows[1].items[i].text = Msg_GetSystem(4);
    }
    gSubMode = 0;
    sSmithResult = 0;
    gSubMode = 0;
    sSmithRow = 0;
    sSmithCanForge = 1;
    sSmithWaiting = 0;
    sSmithSlotsInit = 0;
    sSmithEquipPending = 0;
    gScreenInitDone = 1;
}

s32 SmithEquipScreen_Init(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0)
        SmithEquipScreen_Setup();
    win = gWindows;
    Text_SetFill(1, 0);
    Text_Clear();
    SmithEquipScreen_PrintNextRow();
    Window_Open(win);
    if ((win->anim >> 3) == 3)
        win->skipRows = 0;
    if ((win->anim >> 3) >= win->height - 2) {
        win->anim = 0;
        ret = 1;
    } else {
        win->anim += 8;
    }
    return ret;
}

s32 SmithEquipScreen_Main(void)
{
    s32 ret;
    s32 x;
    s32 y;
    s32 frame;
    s32 id;

    Text_SetFill(1, 0);
    id = GetRecipe()->ids[sSmithVariant];
    x = (gWindows[0].x + 1) * 8;
    y = (gWindows[0].y + 2) * 8;
    frame = Item_GetIcon(id);
    Obj_Draw(x, y, 0, frame, Obj_GetPalette(0, frame), gWindows[0].bg, 0);
    ret = 0;
    if (gSubMode == 0 || gSubState == 1) {
        if (gMenuHasInput)
            ret = SmithForge_HandleInput();
    } else if (gSubMode == 1 && gSubState == 0) {
        ret = SmithForge_OpenConfirm();
        if (ret) {
            gSubState++;
            gWindows[1].anim = 0;
        }
        ret = 0;
    } else if (gSubMode == 1 && gSubState == 2) {
        ret = SmithForge_CloseConfirm();
        if (ret) {
            gSubState = 0;
            gWindows[1].anim = 0;
            if (sSmithEquipPending) {
                gSubMode++;
                ret = 0;
            } else {
                gSubMode = 0;
                if (sSmithResult)
                    ret = sSmithResult;
                else
                    ret = 0;
            }
        }
    } else if (gSubMode == 2 && gSubState == 0) {
        ret = SmithEquip_OpenSlots();
        if (ret) {
            gSubState++;
            gWindows[1].anim = 0;
        }
        ret = 0;
    } else if (gSubMode == 2 && gSubState == 2) {
        ret = SmithEquip_CloseSlots();
        if (ret) {
            gSubState = 0;
            gWindows[1].anim = 0;
            gSubMode = 0;
            sSmithEquipPending = 0;
            if (sSmithResult)
                ret = sSmithResult;
            else
                ret = 0;
        }
    }
    if (gSubState == 1) {
        if (gSubMode != 0 && gMenuHasInput)
            SmithForge_DrawCursor();
        if (gSubMode == 2)
            SmithEquip_DrawSlotIcons();
    }
    return ret;
}

s32 SmithEquipScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    Text_Clear();
    win = gWindows;
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 2) {
        gInputLockFrames = 6;
        ret = sSmithResult;
        Obj_FreePalette(16);
        Obj_FreePalette(6);
        Obj_FreePalette(12);
    }
    win->anim += 8;
    return ret;
}

/*
 * --INFO--
 * PAL Address: 0x0201978C
 * PAL Size: 492b
 * EN Address: 0x020195B0
 * EN Size: 492b
 * JP Address: 0x02018B14
 * JP Size: 524b
 */
void SmithEquipScreen_PrintNextRow(void)
{
    struct Window *win = gWindows;
    struct Recipe *recipe;
    u32 dst;
    u16 flags;
    u16 count;
    u16 kind;
    s32 id;
    s32 n;
    s32 msg;
    s32 digits;
    s32 x;
    char *str;

    if (sSmithRow >= win->rows)
        return;
    str = (char *)LIST_BUF;
    n = (s8)str[0];
    n++;
    if (n & 3)
        n = ((n >> 2) + 1) << 2;
    recipe = (struct Recipe *)(str + n);
    recipe = &recipe[sSmithSel];
    dst = Window_GetTextVram(win, sSmithRow, 0);
    flags = recipe->items[sSmithVariant].flags;
    count = recipe->items[sSmithVariant].count;
    kind = recipe->items[sSmithVariant].kind;
    Text_SetFill(1, 0);
    Text_Clear();
    if (sSmithRow == 0) {
        id = recipe->ids[sSmithVariant];
        Text_SetX(16);
        Text_Print(Msg_GetItemName(id), TEXT_DRAW);
        Text_CopyToVram(dst, win->width);
    } else if (sSmithRow == 1) {
        Text_CopyToVram(dst, win->width);
    } else if (sSmithRow == 2) {
        Text_SetX(0);
        if (flags & 0x3000) {
            Text_Print(Msg_GetStat(kind - 1), TEXT_DRAW);
            if (count != 0 && kind != 16) {
                n = Item_IsPercentKind(kind);
                msg = 39;
                if (n)
                    msg = 40;
                n = Text_Print(Msg_GetSystem(msg), TEXT_WIDTH);
                if (count <= 9)
                    digits = 1;
                else if (count <= 99)
                    digits = 2;
                else
                    digits = 3;
                x = (win->width - 2) * 8 - digits * 9 - n;
                Text_SetX(x);
                Text_Print(Msg_GetSystem(msg), TEXT_DRAW);
                x = Text_GetX();
                Text_PrintNumber(count, x, digits);
            }
        } else {
            if (flags & 0x100)
                str = Msg_GetSystem(16);
            else
#if defined(VERSION_GCCJGC)
                str = Msg_GetSystem(7);
#else
                str = Msg_GetSystem(63);
#endif
            Text_SetX(0);
            Text_Print(str, TEXT_DRAW);
            n = win->width * 8 - 34;
            Text_PrintNumber(count, n, 2);
        }
        Text_CopyToVram(dst, win->width);
    } else if (sSmithRow == 3 && (flags & 0xE00)) {
        if (kind != 0) {
            Text_SetX(0);
            Text_Print(Msg_GetStat(kind - 1), TEXT_DRAW);
            Text_CopyToVram(dst, win->width);
        } else {
            Text_CopyToVram(dst, win->width);
        }
    } else {
        Text_CopyToVram(dst, win->width);
    }
    sSmithRow++;
}

s32 Smith_EquipResult(s32 val)
{
    struct ItemInfo *item = GetRecipe()->items + sSmithVariant;
    s32 slot;

    if (item->flags & 0x100) {
        gSession.equipment[0] = val;
        slot = 0;
    } else if (item->flags & 0x400) {
        gSession.equipment[1] = val;
        slot = 1;
    } else if (item->flags & 0xA00) {
        gSession.equipment[2] = val;
        slot = 2;
    } else {
        gSession.equipment[3] = val;
        slot = 3;
    }
    Link_SendEquipSlot(slot, val);
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x02019A24
 * PAL Size: 250b
 * EN Address: 0x02019848
 * EN Size: 250b
 * JP Address: 0x02018DCC
 * JP Size: 242b
 */
s32 SmithEquip_OpenSlots(void)
{
    struct Window *win = &gWindows[3];
    s32 ret;
    s32 i;

    Text_SetFill(1, 1);
    Text_Clear();
    if (sSmithSlotsInit == 0) {
        memset(win, 0, sizeof(struct Window));
        Text_SetFill(1, 1);
        Text_Clear();
        win->active = 1;
        win->x = 14;
        win->rows = 2;
        win->width = 15;
        win->height = 6;
        win->y = win[-3].y + win[-3].height - 6;
        win->style = 9;
        win->variant = 0;
        win->bg = 1;
        win->slot = 3;
        win->textX = 16;
        for (i = 0; i < win->rows; i++) {
            s32 id;

            win->items[i].enabled = 1;
            id = ((u8 *)gSession.unkE4)[(s8)gSession.equipment[i + 3]];
            win->items[i].text = Msg_GetItemName(id);
        }
        sSmithSlotsInit = 1;
    }
    Window_PrintNextItem(win);
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) >= win->height) {
        ret = 1;
        win->anim = 0;
    } else {
        win->anim += 8;
    }
    return ret;
}

s32 SmithEquip_CloseSlots(void)
{
    struct Window *win = &gWindows[3];
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

/*
 * --INFO--
 * PAL Address: 0x02019B54
 * PAL Size: 148b
 * EN Address: 0x02019978
 * EN Size: 148b
 * JP Address: 0x02018EF4
 * JP Size: 152b
 */
void SmithEquip_DrawSlotIcons(void)
{
    struct Window *win = &gWindows[3];
    s32 x;
    s32 y;
    s32 frame;
    s32 i;

    SmithEquipScreen_PrintNextRow();
    x = (win->x + 1) * 8;
    y = (win->y + 1) * 8;
    for (i = 0; i < win->rows; i++, y += 16) {
        s32 id = (s8)gSession.equipment[i + 3];

        id = ((u8 *)gSession.unkE4)[id];
        frame = Item_GetIcon(id);
        Obj_Draw(x, y, 0, frame, Obj_GetPalette(0, frame), win->bg, 0);
    }
}

void SmithTopScreen_PrintRow(s32 idx, s32 row)
{
    s32 id;

    Text_SetFill(1, 0);
    Text_Clear();
    Text_SetX(16);
    id = gSession.items[SMITH_ITEM_SLOTS[idx]];
    if (id > 0)
        Text_Print(Msg_GetItemName(id), TEXT_DRAW);
    Text_CopyToVram(gWindows[0].width * 64 * row + 0x06009000, gWindows[0].width);
}

void Smith_ResetList(void)
{
    sSmithListValid = 0;
}

/*
 * --INFO--
 * PAL Address: 0x02019C58
 * PAL Size: 178b
 * EN Address: 0x02019A7C
 * EN Size: 178b
 * JP Address: 0x02019004
 * JP Size: 162b
 */
void Item_FormatWearer(u16 *flags, char *dst)
{
    s32 lo = *flags & 15;
    s32 hi = *flags & 0x30;
    s32 i;

    *dst = 0;
    if (hi) {
        if (lo) {
            for (i = 0; i < 4; i++) {
                if ((lo >> i) & 1) {
                    strcpy(dst, Msg_GetTribe(i));
#if !defined(VERSION_GCCJGC)
                    if ((gLanguage & 15) == 1)
                        strcat(dst, sPluralText);
#endif
                    break;
                }
            }
        }
        if (hi == 16)
            strcat(dst, Msg_GetSystem(27));
        else
            strcat(dst, Msg_GetSystem(28));
    } else if (lo == 15) {
        strcpy(dst, Msg_GetSystem(29));
    } else {
        for (i = 0; i < 4; i++) {
            if ((lo >> i) & 1) {
                strcpy(dst, Msg_GetTribe(i));
                break;
            }
        }
    }
}

s32 Smith_IsRecipeKnown(s32 idx)
{
    s32 id = gSession.items[SMITH_ITEM_SLOTS[idx]];
    s32 q;
    s32 r;

    if (id <= 0)
        return 0;
    id -= 401;
    q = id / 32;
    r = id % 32;
    return (sSmithKnown[q] & (1 << r)) != 0;
}

s32 Smith_GetItem(s32 idx)
{
    s8 *list = (s8 *)LIST_BUF;
    s32 id;

    if (*list++ > idx) {
        id = gSession.items[list[idx]];
        if (id > 0)
            return id;
    }
    return -1;
}
