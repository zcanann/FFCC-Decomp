#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "session.h"
#include "window.h"
#include "screen.h"

static s8 sArtifactTop;
static s8 sArtifactQuit;
static s8 sArtifactRow;
static s8 sArtifactUnused;
static s8 sArtifactPollTimer;
static s8 sArtifactLoaded;
static u16 sArtifactUnused2;

const u8 gCmdArtifactIds[] = { 223, 224, 225, 226, 227 };

void ArtifactScreen_PrintRow(s32, s32);
s32 Artifact_IsOwned(s32);
void ArtifactScreen_PrintDesc(void);
void ArtifactScreen_DrawCursor(void);
void ArtifactScreen_HandleInput(void);
void ArtifactScreen_DrawIcons(void);

void ArtifactScreen_Setup(void)
{
    gSubState = 0;
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    StatusWin_Setup(0, 2);
    ListWin_Setup(1, 2, 15, 2);
    Window_ResetItems(&gWindows[1], 1);
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
    sArtifactTop = 0;
    sArtifactRow = 0;
    sArtifactQuit = 0;
    sArtifactUnused = 0;
    sArtifactUnused2 = 1;
    HelpWin_Clear(1, 1);
    HelpWin_DrawFrame(1, 1, 8);
    gDataFlags &= ~DATA_ARTIFACTS;
    Link_SendRequest(9, 0);
    sArtifactLoaded = 0;
    sArtifactPollTimer = 0;
    gScreenInitDone = 1;
}

s32 ArtifactScreen_Init(void)
{
    struct Window *win;
    s32 ret;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0) {
        ArtifactScreen_Setup();
        if (gScreenInitDone == 0)
            return 0;
    }
    StatusWin_Open(0);
    win = &gWindows[1];
    Window_PrintNextItem(win);
    Window_Open(win);
    ret = 0;
    if ((win->anim >> 3) >= win->height - 2) {
        ret = 1;
        win->anim = 0;
    } else {
        win->anim += 8;
    }
    return ret;
}

s32 ArtifactScreen_Main(void)
{
    s32 ret;
    struct Window *win;

    StatusWin_DrawIcon(0);
    if (!(gDataFlags & DATA_ARTIFACTS)) {
        if (gKeysNew & A_BUTTON) {
            m4aSongNumStart(0);
        } else if (gKeysNew & B_BUTTON) {
            sArtifactQuit = 1;
            gOpenMenuReq = 1;
            m4aSongNumStart(3);
            return 1;
        } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
            if (gKeysNew & R_BUTTON)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            ret = 1;
            sArtifactQuit = ret;
            m4aSongNumStart(6);
            return ret;
        }
        if (++sArtifactPollTimer >= 60) {
            Link_SendRequest(9, 0);
            sArtifactPollTimer = 0;
        }
        return 0;
    }
    if (sArtifactLoaded == 0) {
        Session_OnArtifacts(gListBuf);
        sArtifactLoaded = 1;
    }
    Text_SetFill(1, 0);
    Text_Clear();
    win = &gWindows[1];
    if (sArtifactRow < win->rows) {
        ArtifactScreen_PrintRow(sArtifactRow, sArtifactRow);
        Window_DrawRow(1, win->bg, sArtifactRow, sArtifactRow, Artifact_IsOwned(sArtifactRow) ? 5 : 6);
        sArtifactRow++;
        if (sArtifactRow < win->rows)
            return 0;
        ArtifactScreen_PrintDesc();
    }
    if (gMenuHasInput)
        ArtifactScreen_HandleInput();
    ArtifactScreen_DrawIcons();
    if (gMenuHasInput)
        ArtifactScreen_DrawCursor();
    ret = sArtifactQuit != 0;
    if (ret)
        HelpWin_Clear(1, 1);
    return ret;
}

s32 ArtifactScreen_Exit(void)
{
    struct Window *win = gWindows;
    s32 ret = 0;

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) < win->height - 1)
        win->anim += 8;
    win++;
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 1) {
        ret = 1;
        Obj_FreePalette(17);
        Obj_FreePalette(3);
        win->anim = 0;
    } else {
        win->anim += 8;
    }
    return ret;
}

void ArtifactScreen_DrawCursor(void)
{
    s32 cell = Obj_GetPalette(0, 45);
    struct Window *win = &gWindows[1];

    Obj_Draw((win->x - 1) * 8, (win->y + 1) * 8 + win->cursor * 16, 0, 45, cell, win->bg, 0);
}

void ArtifactScreen_HandleInput(void)
{
    struct Window *win;
    s32 prev;
    s32 n;
    s32 pal;
    s32 max = 73;

    if (gKeysRepeat == 0)
        return;
    win = &gWindows[1];
    prev = sArtifactTop + win->cursor;
    if (gKeysRepeat & DPAD_UP) {
        if (win->cursor != 0) {
            win->cursor--;
            m4aSongNumStart(1);
        } else if (sArtifactTop != 0) {
            Window_ScrollRows(1, 1, win->bg);
            n = sArtifactTop - 1;
            ArtifactScreen_PrintRow(n, n % win->rows);
            pal = Artifact_IsOwned(n) ? 5 : 6;
            Window_DrawRow(1, win->bg, n % win->rows, 0, pal);
            sArtifactTop--;
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    } else if (gKeysRepeat & DPAD_DOWN) {
        if (win->cursor < win->rows - 1) {
            win->cursor++;
            m4aSongNumStart(1);
        } else if (sArtifactTop + win->rows >= max) {
            m4aSongNumStart(0);
        } else {
            Window_ScrollRows(0, 1, win->bg);
            n = sArtifactTop + win->rows;
            ArtifactScreen_PrintRow(n, n % win->rows);
            pal = Artifact_IsOwned(n) ? 5 : 6;
            Window_DrawRow(1, win->bg, n % win->rows, win->rows - 1, pal);
            sArtifactTop++;
            m4aSongNumStart(1);
        }
    }
    if (!(gKeysRepeat & (DPAD_UP | DPAD_DOWN))) {
        if (gKeysNew & A_BUTTON) {
            m4aSongNumStart(0);
        } else if (gKeysNew & B_BUTTON) {
            sArtifactQuit = 1;
            gOpenMenuReq = 1;
            m4aSongNumStart(3);
        } else if (gKeysNew & (L_BUTTON | R_BUTTON)) {
            if (gKeysNew & R_BUTTON)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            m4aSongNumStart(6);
            sArtifactQuit = 1;
        }
    } else if (prev != sArtifactTop + win->cursor) {
        ArtifactScreen_PrintDesc();
    }
}

void ArtifactScreen_DrawIcons(void)
{
    struct Window *win = &gWindows[1];
    s32 x = (win->x + 2) * 8;
    s32 y = (win->y + 1) * 8;
    s32 n = win->rows;
    s32 base = sArtifactTop + 159;
    s32 i;
    s32 id;
    s32 flags;

    for (i = 0; i < n; i++, y += 16) {
        if (Artifact_IsOwned(sArtifactTop + i)) {
            id = Item_GetIcon(base + i);
            Obj_Draw(x, y, 0, id, Obj_GetPalette(0, id), 2, 0);
        }
    }
    flags = sArtifactTop != 0;
    if (sArtifactTop + win->rows <= 72)
        flags |= 2;
    Window_DrawScrollArrows(1, win->bg, flags);
}

void ArtifactScreen_Refresh(void)
{
    struct Window *win = &gWindows[1];
    s32 i;
    s32 n;
    s32 word;
    s32 bit;
    s32 pal;

    for (i = 0; i < win->rows; i++) {
        n = sArtifactTop + i;
        word = n >> 5;
        bit = n % 32;
        if (((s32)(gSession.artifacts[word] ^ gSession.prevArtifacts[word]) >> bit) & 1) {
            ArtifactScreen_PrintRow(n, n % win->rows);
            pal = Artifact_IsOwned(n) ? 5 : 6;
            Window_DrawRow(1, win->bg, n % win->rows, i, pal);
        }
    }
}

void ArtifactScreen_PrintRow(s32 idx, s32 row)
{
    char *str;

    Text_SetFill(1, 0);
    Text_Clear();
    Text_SetX(24);
    if (Artifact_IsOwned(idx))
        str = Msg_GetItemName(idx + 159);
    else
        str = Msg_GetSystem(41);
    Text_Print(str, TEXT_DRAW);
    Text_CopyToVram(Window_GetTextVram(&gWindows[1], row, 0), gWindows[1].width);
}

s32 Artifact_IsOwned(s32 idx)
{
    s32 word = idx >> 5;
    s32 bit = idx % 32;
    s32 flag = gSession.artifacts[word] & (1 << bit);

    if (flag)
        flag = 1;
    return flag;
}

void ArtifactScreen_PrintDesc(void)
{
    struct Window *win;
    char buf[68];
    s32 n;
    char *str;

    Text_SetFill(0, 0);
    Text_Clear();
    win = &gWindows[1];
    n = sArtifactTop + win->cursor;
    if (Artifact_IsOwned(n)) {
        Msg_GetItemDesc(n + 159, buf);
        str = buf;
    } else {
        str = Msg_GetSystem(0);
    }
    Text_Print(str, TEXT_DRAW);
    HelpWin_CopyText(1, 1);
}
