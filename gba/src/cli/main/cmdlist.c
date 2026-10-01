#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "session.h"
#include "radar.h"
#include "window.h"
#include "screen.h"
#include "lists.h"

static s16 *sCmdCandidates;
static s16 sCmdCandidateCount;
static s32 sCmdTop;
static s8 sCmdRowOffset;
static s8 sCmdQuit;
static s8 sCmdLoaded;
static s8 sCmdPollTimer;
extern const u8 gCmdArtifactIds[];

void CmdListScreen_DrawCursor(void);
void CmdListScreen_HandleInput(void);
s32 CmdListScreen_OpenPicker(void);
s32 CmdListScreen_ClosePicker(void);
s32 CmdList_GetSlotType(s32);
void CmdListScreen_PrintCandidate(s32, s32);
s32 CmdListScreen_CanUseCandidate(s32);
void CmdList_SetSlot(s32, s32);
void CmdListScreen_DrawIcons(void);
s32 CmdList_GetSlotItem(s32);
void CmdListScreen_PrintDesc(void);

void CmdListScreen_Setup(void)
{
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    StatusWin_Setup(0, 0);

    gWindows[1].active = 1;
    gWindows[1].cursor = 0;
    gWindows[1].x = 5;
    gWindows[1].y = 3;
    gWindows[1].rows = 6;
    gWindows[1].width = 14;
    gWindows[1].height = 14;
    gWindows[1].style = 0;
    gWindows[1].variant = 0;
    gWindows[1].bg = 0;
    gWindows[1].slot = 1;
    gWindows[1].textX = 0;
    Window_ResetItems(&gWindows[1], 1);

    gWindows[2].active = 1;
    gWindows[2].cursor = 2;
    gWindows[2].x = 2;
    gWindows[2].y = 2;
    gWindows[2].rows = gSession.cmdSlotCount;
    gWindows[2].width = 14;
    gWindows[2].height = gWindows[2].rows * 2;
    gWindows[2].style = 16;
    gWindows[2].variant = 0;
    gWindows[2].bg = 2;
    gWindows[2].slot = 2;
    gWindows[2].textX = 0;

    Text_SetFill(1, 0);
    Text_Clear();
    Text_LoadPalette(4, 0, 0);
    Text_LoadPalette(5, 0, 0);
    Text_LoadPalette(6, 2, 0);
    Font_LoadPalette(0x050000E0, 1);
    Text_CopyFill(0x06000000);
    Obj_AllocPalette(17, 0);
    Obj_AllocPalette(3, 0);
    Obj_LoadToBg(17, 0, 0, 0);
    Obj_LoadToBg(3, 1, 1, 0);
    Obj_LoadToBg(19, 2, 2, -1);

    sCmdTop = 0;
    sCmdQuit = 0;
    sCmdRowOffset = 0;
    gSubState = 0;
    gSubMode = 0;
    CmdListScreen_BuildCandidates();
    HelpWin_Clear(2, 1);
    HelpWin_DrawFrame(2, 1, 7);
    gDataFlags &= ~DATA_CMD_LIST;
    sCmdLoaded = 0;
    sCmdPollTimer = 0;
    gScreenInitDone = 1;
}

s32 CmdListScreen_Init(void)
{
    struct Window *win = gWindows;
    s32 ret;
    s32 row;
    s32 y;
    s32 top;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0)
        CmdListScreen_Setup();
    ret = StatusWin_Open(0);
    if (ret)
        win->anim = 0;
    win += 2;
    Text_SetFill(0, 0);
    Text_Clear();
    row = win->anim >> 3;
    if (row < gSession.cmdSlotCount) {
        Window_DrawSlotRow(2, CmdList_GetSlotType(row), row);
        Text_SetX(8);
        if (row == 0) {
            Text_Print(Msg_GetSystem(9), TEXT_DRAW);
            y = 0;
        } else if (row == 1) {
            Text_Print(Msg_GetSystem(36), TEXT_DRAW);
            y = 2;
        } else {
            if (row < win->rows && (s16)gSession.cmdSlots[row] >= 0)
                Text_Print(Msg_GetItemName(CmdList_GetSlotItem(row)), TEXT_DRAW);
            y = row * 2;
        }
        win->bg--;
        Window_PutText(win, row, 0);
        top = win->y + y;
        Window_PutRowAt(win, win->bg, row, win->x, top, 7);
        win->bg++;
    }
    if (row < win->rows - 1)
        win->anim += 8;
    return ret;
}

s32 CmdListScreen_Main(void)
{
    s32 ret;

    StatusWin_DrawIcon(0);
    if (!(gDataFlags & DATA_CMD_LIST)) {
        if (gKeysNew & A_BUTTON) {
            m4aSongNumStart(0);
        } else if (gKeysNew & B_BUTTON) {
            sCmdQuit = 1;
            gOpenMenuReq = 1;
            m4aSongNumStart(3);
            return 1;
        } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
            if (gKeysNew & R_BUTTON)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            sCmdQuit = 1;
            m4aSongNumStart(6);
            return 1;
        }
        if (++sCmdPollTimer >= 60) {
            /* only the low byte of gScreen is read here */
            Link_SendScreenId(*(s8 *)&gScreen);
            sCmdPollTimer = 0;
        }
        return 0;
    }
    if (sCmdLoaded == 0) {
        CmdListScreen_PrintDesc();
        sCmdLoaded = 1;
    }
    if (gSubMode && gSubState == 0) {
        ret = CmdListScreen_OpenPicker();
        if (ret) {
            CmdListScreen_PrintDesc();
            gSubState++;
            gWindows[1].anim = 0;
        }
    } else if (!gSubMode || gSubState == 1) {
        if (gMenuHasInput)
            CmdListScreen_HandleInput();
        else if (gSubMode)
            gSubState++;
    } else {
        ret = CmdListScreen_ClosePicker();
        if (ret) {
            gSubState = 0;
            gWindows[1].anim = 0;
            gSubMode = 0;
            CmdListScreen_PrintDesc();
        }
    }
    CmdListScreen_DrawIcons();
    CmdListScreen_DrawCursor();
    ret = sCmdQuit != 0;
    if (ret)
        HelpWin_Clear(2, 1);
    return ret;
}

s32 CmdListScreen_Exit(void)
{
    struct Window *win = gWindows;
    s32 ret = 0;
    s32 row;
    s32 y;

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 1) {
        ret = 1;
        Obj_FreePalette(17);
        Bg_SetBlend(0);
        win->anim = 0;
    } else {
        win->anim += 8;
    }
    win = &gWindows[2];
    row = win->anim >> 3;
    y = win->y + (win->rows - row - 1) * 2;
    Bg_FillBlank(win->bg - 1, win->x, y, win->width, 2);
    Window_ClearRow(2, win->rows - row - 1);
    if (row < win->rows - 1)
        win->anim += 8;
    return ret;
}

void CmdListScreen_DrawCursor(void)
{
    s32 pal;
    struct Window *win;
    s32 x;
    s32 y;

    if (gMenuHasInput) {
        pal = Obj_GetPalette(0, 45);
        if (!gSubMode || (gFrameCount & 2)) {
            win = &gWindows[2];
            x = (win->x - 1) * 8;
            y = win->y * 8;
            y += win->cursor * 16;
            Obj_Draw(x, y, 0, 45, pal, win->bg, 0);
        }
        if (gSubMode && gSubState == 1) {
            win = &gWindows[1];
            x = (win->x - 1) * 8;
            y = (win->y + 1) * 8;
            y += win->cursor * 16;
            Obj_Draw(x, y, 0, 45, pal, win->bg, 0);
        }
    }
}

void CmdListScreen_HandleInput(void)
{
    struct Window *win;
    s32 min;
    s32 n;
    s32 idx;
    s32 row;

    if (gKeysRepeat == 0)
        return;
    if (gSubMode) {
        min = 0;
        win = &gWindows[1];
        n = win->rows;
    } else {
        min = 2;
        n = gSession.cmdSlotCount;
        win = &gWindows[2];
    }
    if (gKeysRepeat & DPAD_UP) {
        if (win->cursor > min) {
            win->cursor--;
            CmdListScreen_PrintDesc();
            m4aSongNumStart(1);
        } else if (!gSubMode) {
            win->cursor = n - 1;
            CmdListScreen_PrintDesc();
            m4aSongNumStart(1);
        } else if (sCmdCandidateCount <= win->rows) {
            win->cursor = sCmdCandidateCount - 1;
            CmdListScreen_PrintDesc();
            m4aSongNumStart(1);
        } else {
            Window_ScrollRows(1, 1, win->bg);
            idx = (sCmdTop - 1) % sCmdCandidateCount;
            if (idx < 0)
                idx += sCmdCandidateCount;
            row = (sCmdTop - 1 + sCmdRowOffset) % win->rows;
            if (row < 0)
                row += win->rows;
            CmdListScreen_PrintCandidate(idx, row % win->rows);
            Window_DrawRow(1, win->bg, row, 0, CmdListScreen_CanUseCandidate(idx) ? 5 : 6);
            sCmdTop--;
            CmdListScreen_PrintDesc();
            m4aSongNumStart(1);
        }
    } else if (gKeysRepeat & DPAD_DOWN) {
        if (((!gSubMode || sCmdCandidateCount > win->rows) && win->cursor < n - 1)
            || (gSubMode && sCmdCandidateCount <= win->rows && win->cursor < sCmdCandidateCount - 1)) {
            win->cursor++;
            CmdListScreen_PrintDesc();
            m4aSongNumStart(1);
        } else if (!gSubMode) {
            win->cursor = min;
            CmdListScreen_PrintDesc();
            m4aSongNumStart(1);
        } else {
            if (sCmdCandidateCount <= win->rows) {
                win->cursor = min;
                m4aSongNumStart(1);
            } else {
                Window_ScrollRows(0, 1, win->bg);
                idx = (sCmdTop + win->rows) % sCmdCandidateCount;
                if (idx < 0)
                    idx += sCmdCandidateCount;
                row = (sCmdTop + win->rows + sCmdRowOffset) % win->rows;
                if (row < 0)
                    row += win->rows;
                CmdListScreen_PrintCandidate(idx, row);
                Window_DrawRow(1, win->bg, row, win->rows - 1, CmdListScreen_CanUseCandidate(idx) ? 5 : 6);
                sCmdTop++;
            }
            CmdListScreen_PrintDesc();
            m4aSongNumStart(1);
        }
    }
    if (gKeysRepeat & (DPAD_UP | DPAD_DOWN))
        return;
    if (gKeysNew & A_BUTTON) {
        if (!gSubMode) {
            gSubMode = 1;
        } else {
            idx = (gWindows[1].cursor + sCmdTop) % sCmdCandidateCount;
            if (idx < 0)
                idx += sCmdCandidateCount;
            if (!CmdListScreen_CanUseCandidate(idx)) {
                m4aSongNumStart(0);
                return;
            }
            gSubState++;
            CmdList_SetSlot(gWindows[2].cursor, idx - 1);
        }
        m4aSongNumStart(2);
    } else if (gKeysNew & B_BUTTON) {
        if (!gSubMode) {
            gOpenMenuReq = 1;
            sCmdQuit = -1;
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
            sCmdQuit = -1;
        }
    }
}

s32 CmdListScreen_OpenPicker(void)
{
    struct Window *win = &gWindows[1];
    s32 row;
    s32 idx;
    s32 ret;

    Text_SetFill(1, 0);
    Text_Clear();
    row = win->anim >> 3;
    if (row < win->rows) {
        if (row < sCmdCandidateCount) {
            idx = (row + sCmdTop) % sCmdCandidateCount;
            if (idx < 0)
                idx += sCmdCandidateCount;
        } else {
            idx = row;
        }
        CmdListScreen_PrintCandidate(idx, row);
        win->items[row].enabled = CmdListScreen_CanUseCandidate(idx);
    }
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) >= win->height - 2) {
        ret = 1;
        win->anim = 0;
        sCmdRowOffset = (win->rows - sCmdTop) % win->rows;
        if (sCmdRowOffset < 0)
            sCmdRowOffset += win->rows;
    } else {
        win->anim += 8;
    }
    return ret;
}

s32 CmdListScreen_ClosePicker(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[1];

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 1) {
        ret = 1;
        win->anim = 0;
    } else {
        win->anim += 8;
    }
    return ret;
}

void CmdListScreen_BuildCandidates(void)
{
    s32 n;
    s32 i;
    s32 j;
    s32 type;
    s32 k;
    s32 count;
    u8 id;

    sCmdCandidates = (s16 *)LIST_BUF;
    n = 0;
    for (i = 0; i < 64; i++) {
        type = Session_GetItemCategory(i);
        if (type == 0 || type == 5 || type == 6 || type == 8 || type == 9)
            continue;
        if (type == 1) {
            s32 w = gSession.items[i];
            s32 party = gSession.appearance & 3;
            k = Item_GetIcon(w);
            if (k != party)
                continue;
        }
        sCmdCandidates[n++] = (s8)i;
    }
    count = 5;
    for (i = 0; i < count; i++) {
        id = gCmdArtifactIds[i];
        k = id - 159;
        if (gSession.artifacts[k >> 5] & (1 << (k & 31)))
            sCmdCandidates[n++] = id - 95;
    }
    for (i = 0; i < 4; i++) {
        if (gSession.stageArtifacts[i] != 0) {
            for (j = 0; j < count; j++) {
                if (gSession.stageArtifacts[i] == gCmdArtifactIds[j])
                    sCmdCandidates[n++] = i + 160;
            }
        }
    }
    sCmdCandidateCount = n + 1;
}

s32 CmdList_GetSlotType(s32 row)
{
    s32 id;

    if (row <= 1)
        return 0;
    if (row >= gSession.cmdSlotCount || (id = (s16)gSession.cmdSlots[row]) < 0)
        return -1;
    if (id < 64) {
        id = Session_GetItemCategory(id);
        if (id == 3)
            return 1;
        if (id == 7)
            return 2;
        if (id == 1)
            return 3;
        if (id == 4)
            goto end;
    }
    id = 5;
end:
    return id;
}

void CmdListScreen_PrintCandidate(s32 idx, s32 row)
{
    struct Window *win = &gWindows[1];
    const char *str;
    s32 id;

    Text_SetFill(1, 0);
    Text_Clear();
    Text_SetX(8);
    if (idx == 0) {
        str = Msg_GetSystem(10);
    } else if (idx >= sCmdCandidateCount) {
        str = Msg_GetSystem(0);
    } else {
        id = sCmdCandidates[idx - 1];
        if (id < 64)
            id = gSession.items[id];
        else if (id >= 64 && id < 160)
            id += 95;
        else
            id = gSession.stageArtifacts[id - 160];
        if (id > 0)
            str = Msg_GetItemName(id);
        else
            str = Msg_GetSystem(0);
    }
    Text_Print(str, TEXT_DRAW);
    Window_PutText(win, row, 0);
}

s32 CmdListScreen_CanUseCandidate(s32 idx)
{
    s32 ret;

    if (idx >= sCmdCandidateCount)
        ret = 0;
    else if (idx == 0)
        ret = (s16)gSession.cmdSlots[gWindows[2].cursor] >= 0;
    else
        ret = Session_IsItemInUse(sCmdCandidates[idx - 1]) == 0;
    return ret;
}

void CmdList_SetSlot(s32 slot, s32 idx)
{
    if (idx < 0)
        gSession.cmdSlots[slot] = -1;
    else
        gSession.cmdSlots[slot] = sCmdCandidates[idx];
    Link_SendCmdSlot(slot, (s16)gSession.cmdSlots[slot]);
    CmdListScreen_PrintSlot(slot);
}

void CmdListScreen_DrawIcons(void)
{
    struct Window *win = &gWindows[2];
    s32 x;
    s32 i;
    s32 id;
    s32 pal;
    s32 idx;
    s32 y;

    x = (win->x + win->width) * 8 - 18;
    for (i = 2; i < win->rows; i++) {
        if ((s16)gSession.cmdSlots[i] != -1) {
            id = Item_GetIcon(CmdList_GetSlotItem(i));
            pal = Obj_GetPalette(0, id);
            y = win->y * 8 + i * 16;
            Obj_Draw(x, y, 0, id, pal, win->bg, 0);
        }
    }
    if (gSubMode && gSubState == 1) {
        win = &gWindows[1];
        id = (gLanguage & 15) == 1 ? 24 : 4;
        pal = Obj_GetPalette(2, id);
        x = win->x * 8 + 6;
        for (i = 0; i < win->rows; i++) {
            if (sCmdCandidateCount > win->rows) {
                idx = (i + sCmdTop) % sCmdCandidateCount;
                if (idx < 0)
                    idx += sCmdCandidateCount;
            } else {
                idx = i;
            }
            if (idx > 0 && idx < sCmdCandidateCount && !CmdListScreen_CanUseCandidate(idx)) {
                y = (win->y + 1) * 8 + i * 16 + 3;
                Obj_Draw(x, y, 2, id, pal, win->bg, 0);
            }
        }
        if (sCmdCandidateCount > win->rows)
            Window_DrawScrollArrows(1, win->bg, 3);
    }
}

void CmdListScreen_PrintSlot(s32 row)
{
    struct Window *win = &gWindows[2];

    Text_SetFill(0, 0);
    Text_Clear();
    Window_DrawSlotRow(2, CmdList_GetSlotType(row), row);
    Text_SetX(8);
    if ((s16)gSession.cmdSlots[row] >= 0)
        Text_Print(Msg_GetItemName(CmdList_GetSlotItem(row)), TEXT_DRAW);
    win->bg--;
    Window_PutText(win, row, 0);
    win->bg++;
}

s32 CmdList_GetSlotItem(s32 row)
{
    s32 id = (s16)gSession.cmdSlots[row];

    if (id < 0)
        return -1;
    if (id < 64)
        id = gSession.items[id];
    else if (id < 160)
        id += 95;
    else
        id = gSession.stageArtifacts[id - 160];
    return id;
}

void CmdListScreen_PrintDesc(void)
{
    struct Window *win;
    struct ItemInfo *item;
    s32 id;
    s32 idx;
    s32 n;
    s32 i;
    s32 v;
    s32 w;
    s32 digits;
    s32 msg;

    win = gSubMode ? &gWindows[1] : &gWindows[2];
    if (!gSubMode) {
        id = CmdList_GetSlotItem(win->cursor);
    } else {
        idx = (win->cursor + sCmdTop) % sCmdCandidateCount;
        if (idx < 0)
            idx += sCmdCandidateCount;
        if (idx == 0) {
            id = 0;
        } else {
            id = sCmdCandidates[idx - 1];
            if (id < 64)
                id = gSession.items[id];
            else if (id >= 64 && id < 160)
                id += 95;
            else
                id = gSession.stageArtifacts[id - 160];
        }
    }
    if (Item_GetCategory(id) == 1) {
        Text_SetFill(0, 0);
        Text_Clear();
        if (!gSubMode) {
            id = (s16)gSession.cmdSlots[win->cursor];
        } else {
            idx = win->cursor + sCmdTop - 1;
            idx %= sCmdCandidateCount;
            if (idx < 0)
                idx += sCmdCandidateCount;
            id = sCmdCandidates[idx];
        }
        n = 0;
        for (i = 0; i < sCmdCandidateCount; i++) {
            v = sCmdCandidates[i];
            if (v < 64) {
                w = gSession.items[v];
                if (Item_GetCategory(w) == 1 && Item_GetIcon(w) <= 3) {
                    if (v == id)
                        break;
                    n++;
                }
            }
        }
        item = CMD_ITEM_INFO + n;
        if (item->flags & 0x100)
            Text_Print(Msg_GetSystem(16), TEXT_DRAW);
        else if (item->flags & 0xE00)
            Text_Print(Msg_GetSystem(63), TEXT_DRAW);
        if (!(item->flags & 0x3000)) {
            Text_AddX(8);
            idx = Text_GetX();
            Text_PrintNumber(item->count, idx, 2);
        }
        if (!(item->flags & 0x100) && item->kind != 0) {
            if (item->flags & 0xE00)
                Text_AddX(8);
            Text_Print(Msg_GetStat(item->kind - 1), TEXT_DRAW);
            if ((item->flags & 0x3000) && item->count != 0 && item->kind != 16) {
                idx = Item_IsPercentKind(item->kind);
                msg = 39;
                if (idx)
                    msg = 40;
                Text_AddX(8);
                Text_Print(Msg_GetSystem(msg), TEXT_DRAW);
                idx = Text_GetX();
                if (item->count <= 9)
                    digits = 1;
                else if (item->count <= 99)
                    digits = 2;
                else
                    digits = 3;
                Text_PrintNumber(item->count, idx, digits);
            }
        }
        HelpWin_CopyText(2, 1);
    } else {
        HelpWin_PrintItemDesc(id, 2, 1);
    }
}

void CmdListScreen_AddSlot(void)
{
    struct Window *win = &gWindows[2];
    s32 row;
    s32 y;

    Text_SetFill(0, 0);
    Text_Clear();
    Text_SetX(8);
    Window_DrawSlotRow(2, -1, gSession.cmdSlotCount - 1);
    win->rows = gSession.cmdSlotCount;
    row = gSession.cmdSlotCount - 1;
    win->bg--;
    Window_PutText(win, row, 0);
    y = win->y + row * 2;
    Window_PutRowAt(win, win->bg, row, win->x, y, 7);
    win->bg++;
}
