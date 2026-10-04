#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "session.h"
#include "window.h"
#include "screen.h"

struct CMakeData gCMakeData;

static s8 sCMakeResult;
static s8 sCMakeCursor[2];
static s8 sCMakeBirthday[2];
static char sCMakeName[17];
static s8 sCMakeCharPage;
static s8 sCMakeNameLen;
static s8 sCMakeCharRow;
static s8 sCMakeFoodOrder[8];
static s8 sCMakeTextRow;
static s8 sCMakeTileRow;
static s8 sCMakeSwapping;
static s8 sCMakeTop;
static s8 sCMakeWaiting;
char *gNameCharTables[] = {
    "ABCDEFGHIJKL",
    "MNOPQRSTUVWX",
    "YZ \xC0\xC1\xC2\xC4\x8C\xC7\xC8\xC9\xCA",
    "\xCB\xCC\xCD\xCE\xCF\xD1\xD2\xD3\xD4\xD6\xD9\xDA",
    "\xDB\xDC\xDF         ",
    "abcdefghijkl",
    "mnopqrstuvwx",
    "yz \xE0\xE1\xE2\xE4\x9C\xE7\xE8\xE9\xEA",
    "\xEB\xEC\xED\xEE\xEF\xF1\xF2\xF3\xF4\xF6\xF9\xFA",
    "\xFB\xFC\xDF         ",
    "0123456789-#",
    "!\xA1?\xBF%&\xB0\"'()@",
    "*,./:;<=>[]_",
    "|\xAB\xBB\x82\x84       ",
    "            ",
};

const s8 sDaysInMonth[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void CMakeNameScreen_DrawCursor(void);
s32 CMakeNameScreen_HandleInput(void);
void CMakeNameScreen_PrintNextRow(void);
void CMake_PrintTitle(char *str, s32 x);
void CMake_ClearTitle(void);
void CMakeName_AddChar(s32 mode);
void CMakeName_DeleteChar(void);
s32 CMakeName_IsFull(void);
void CMakeName_PrintName(char *str);
void CMake_DrawFooter(void);
void CMakeGenderScreen_DrawCursor(void);
s32 CMakeGenderScreen_HandleInput(void);
void CMakeLookScreen_DrawCursor(void);
s32 CMakeLookScreen_HandleInput(void);
s32 CMakeLookScreen_OpenLooks(void);
s32 CMakeLookScreen_CloseLooks(void);
void CMakeBirthdayScreen_PrintDate(void);
void CMakeBirthdayScreen_DrawCursor(void);
s32 CMakeBirthdayScreen_HandleInput(void);
void CMakeFavoriteScreen_PrintNextRow(void);
void CMakeFavoriteScreen_DrawNextRow(void);
void CMakeFavoriteScreen_DrawRow(s32);
void CMakeFavoriteScreen_DrawIcons(void);
void CMakeFavoriteScreen_DrawCursor(void);
s32 CMakeFavoriteScreen_HandleInput(void);
void CMakeJobScreen_PrintNextRow(void);
void CMakeJobScreen_DrawNextRow(void);
void CMakeJobScreen_DrawCursor(void);
s32 CMakeJobScreen_HandleInput(void);
void CMakeConfirmScreen_PrintNextRow(void);
void CMakeConfirmScreen_DrawNextRow(void);
void CMakeConfirmScreen_DrawCursor(void);
s32 CMakeConfirmScreen_HandleInput(void);

void CMakeNameScreen_Setup(void)
{
    struct Window *win;
    s32 x;
    s32 i;
    u8 buf[20];

    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);

    gWindows[0].active = 1;
    gWindows[0].x = 1;
    gWindows[0].y = 3;
    gWindows[0].rows = 6;
    gWindows[0].width = 28;
    gWindows[0].height = 15;
    gWindows[0].style = 8;
    gWindows[0].variant = 0;
    gWindows[0].bg = 2;
    gWindows[0].slot = 0;
    gWindows[0].textX = 0;

    gWindows[1].active = 1;
    gWindows[1].x = 20;
    gWindows[1].y = 15;
    gWindows[1].rows = 3;
    gWindows[1].width = 9;
    gWindows[1].height = 3;
    gWindows[1].style = 3;
    gWindows[1].variant = 0;
    gWindows[1].bg = 1;
    gWindows[1].slot = 2;
    gWindows[1].textX = 0;

    for (i = 0; i < gWindows[0].rows; i++) {
        gWindows[0].items[i].enabled = 1;
        gWindows[0].items[i].text = Msg_GetSystem(0);
    }
    for (i = 0; i < gWindows[1].rows; i++) {
        gWindows[1].items[i].enabled = 1;
        gWindows[1].items[i].text = Msg_GetSystem(0);
    }
    gWindows[4].items[0].enabled = 1;
    gWindows[4].items[0].text = Msg_GetNotice(NOTICE_NAME_TAKEN);

    MsgBox_Layout();
    Text_SetFill(1, 0);
    Text_LoadPalette(3, 0, 0);
    Font_LoadPalette(0x050000E0, 0);
    Font_LoadPalette(0x05000100, 2);
    Font_LoadPalette(0x05000120, 1);
    Obj_AllocPalette(11, 0);
    Obj_AllocPalette(12, 0);
    Obj_AllocPalette(6, 0);
    Obj_AllocPalette(18, 0);
    Obj_AllocPalette(20, 0);
    Obj_LoadToBg(11, 0, 2, 0);
    Obj_LoadToBg(6, 2, 1, 0);
    Obj_LoadToBg(12, 4, 0, 0);
    Text_CopyFill(0x06008000);
    Text_SetFill(1, 1);
    Text_LoadPalette(15, 0, 1);
    Text_CopyFill(0x06006000);
    Text_SetFill(0, 0);
    Text_Clear();
    x = (gWindows[1].width * 8 - Text_Print(Msg_GetCMake(0), TEXT_WIDTH)) >> 1;
    Text_SetX(x);
    Text_Print(Msg_GetCMake(0), TEXT_DRAW);
    Text_CopyToObj(1, 14, 0);
    HelpWin_Clear(2, 1);
    HelpWin_DrawFrame(2, 1, 9);

    sCMakeResult = 0;
    sCMakeCharPage = 0;
    sCMakeCharRow = 0;
    sCMakeWaiting = 0;
    memset(sCMakeName, 0, 17);
    strcpy(sCMakeName, gCMakeData.name);
    sCMakeNameLen = Str_Length(sCMakeName);
    if (sCMakeNameLen == 0) {
        sCMakeCursor[1] = 0;
        sCMakeCursor[0] = 0;
    } else {
        sCMakeCursor[0] = 11;
        sCMakeCursor[1] = 5;
    }
    memset(buf, 0, 17);
    Link_SendCMakeName(buf);
    Text_SetFill(0, 0);
    Text_Clear();

    win = &gWindows[1];
    x = win->bg;
    win->bg = 0;
    for (i = 2; i >= 0; i--)
        Window_PrintNextItem(win);
    win->bg = x;

    gSubState = 0;
    gSubMode = 0;
    gScreenInitDone = 1;
}

s32 CMakeNameScreen_Init(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;

    if (gScreenInitDone == 0)
        CMakeNameScreen_Setup();
    Text_SetFill(0, 0);
    Text_Clear();
    Window_PrintNextItem(win);
    Window_Open(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win++;
        Window_Open(win);
        if ((win->anim >> 3) < win->height - 1) {
            win->anim += 8;
        } else {
            win[-1].anim = 0;
            win->anim = 0;
            CMakeName_PrintName(sCMakeName);
            ret = 1;
        }
    }
    if ((win->anim >> 3) == 1) {
        s32 x;

        Text_SetFill(0, 0);
        Text_Clear();
        x = (144 - Text_Print(Msg_GetCMake(1), TEXT_WIDTH)) >> 1;
        CMake_PrintTitle(Msg_GetCMake(1), x);
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 CMakeNameScreen_Main(void)
{
    s32 ret = 0;
    s32 i;
    s32 x;
    s32 y;

    if (gSubState == 0) {
        if (sCMakeWaiting == 0) {
            ret = CMakeNameScreen_HandleInput();
        } else if (gDataFlags & DATA_REPLY) {
            if (gReplyResult != 0) {
                gSubState = 1;
                m4aSongNumStart(0);
            } else {
                ret = 1;
            }
            sCMakeWaiting = 0;
            Reply_Clear();
        } else if (Reply_IsTimedOut()) {
            sCMakeWaiting = 0;
            Reply_Clear();
        }
    } else {
        if (gSubState == 1) {
            if (MsgBox_Open())
                gSubState++;
        } else if (gSubState == 2) {
            if (MsgBox_WaitKey())
                gSubState++;
        } else {
            if (MsgBox_Close())
                gSubState = 0;
        }
        ret = 0;
    }
    CMake_DrawFooter();
    CMakeNameScreen_PrintNextRow();
    CMakeNameScreen_DrawCursor();
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    x = gWindows[1].x * 8;
    y = gWindows[1].y * 8 + 5;
    for (i = 0; i <= 4; i++, x += 16)
        Obj_Draw(x, y, 22, i, 0, 1, 0);
    if (ret)
        HelpWin_Clear(2, 1);
    return ret;
}

s32 CMakeNameScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = 0;
        CMake_ClearTitle();
        HelpWin_Clear(2, 1);
        strcpy(gCMakeData.name, sCMakeName);
        if (sCMakeResult < 0) {
            Obj_FreePalette(11);
            Obj_FreePalette(6);
            Obj_FreePalette(12);
            Obj_FreePalette(18);
            Obj_FreePalette(20);
            Link_SendCMakeCancel();
            ret = -1;
        } else {
            ret = 1;
        }
    }
    if (ret == 0) {
        win = &gWindows[1];
        Window_Close(win);
        if ((win->anim >> 3) < win->height - 1)
            win->anim += 8;
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

void CMakeNameScreen_DrawCursor(void)
{
    s32 x;
    s32 y;
    s32 id;

    if (gScreenPhase != PHASE_MAIN)
        return;
    if (gFrameCount & 0x20) {
        Obj_Draw(8, 112, 0, 40, Obj_GetPalette(0, 40), 1, 0);
        Obj_Draw(216, 112, 0, 41, Obj_GetPalette(0, 41), 1, 0);
    }
    if (sCMakeCharRow > 4 && gSubState == 0) {
        struct Window *win;

        id = 45;
        win = gWindows;
        if (sCMakeCursor[1] == 5 && sCMakeCursor[0] > 9) {
            x = win[1].x * 8 - 18;
            y = win[1].y * 8 + 5;
        } else {
            x = (win->x + sCMakeCursor[0] * 2) * 8;
            x -= 2;
            y = (win->y + 2 + sCMakeCursor[1] * 2) * 8;
        }
        Obj_Draw(x, y, 0, id, Obj_GetPalette(0, id), 0, 0);
        if (sCMakeNameLen != 7 && (gFrameCount & 4)) {
            x = sCMakeNameLen * 16 + 68;
            Obj_Draw(x, 136, 2, 5, Obj_GetPalette(2, 5), 1, 0x20000000);
        }
    }
}

s32 CMakeNameScreen_HandleInput(void)
{
    s32 ret;
    s32 i;
    s32 len;

    if (gKeysRepeat == 0 || sCMakeCharRow <= 4)
        return 0;
    ret = 0;
    if (gKeysRepeat & DPAD_LEFT) {
        if (sCMakeCursor[1] <= 4) {
            if (sCMakeCursor[0] <= 0)
                sCMakeCursor[0] = 11;
            else
                sCMakeCursor[0]--;
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    } else if (gKeysRepeat & DPAD_RIGHT) {
        if (sCMakeCursor[1] <= 4) {
            if (sCMakeCursor[0] > 10)
                sCMakeCursor[0] = 0;
            else
                sCMakeCursor[0]++;
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    }
    if (gKeysRepeat & DPAD_UP) {
        if (sCMakeCursor[1] <= 0) {
            if (sCMakeCursor[0] > 9)
                sCMakeCursor[1] = 5;
            else
                sCMakeCursor[1] = 4;
        } else {
            sCMakeCursor[1]--;
        }
        m4aSongNumStart(1);
    } else if (gKeysRepeat & DPAD_DOWN) {
        if (sCMakeCursor[1] >= 4) {
            if (sCMakeCursor[1] == 4 && sCMakeCursor[0] > 9)
                sCMakeCursor[1]++;
            else
                sCMakeCursor[1] = 0;
        } else {
            sCMakeCursor[1]++;
        }
        m4aSongNumStart(1);
    }
    if (gKeysRepeat & DPAD_ANY)
        return ret;
    if (gKeysNew & START_BUTTON) {
        sCMakeCursor[0] = 11;
        sCMakeCursor[1] = 5;
        m4aSongNumStart(2);
    } else if (gKeysNew & L_BUTTON) {
        if (sCMakeCharPage <= 0)
            sCMakeCharPage = 2;
        else
            sCMakeCharPage--;
        sCMakeCharRow = 0;
        m4aSongNumStart(6);
    } else if (gKeysNew & R_BUTTON) {
        if (sCMakeCharPage > 1)
            sCMakeCharPage = 0;
        else
            sCMakeCharPage++;
        sCMakeCharRow = 0;
        m4aSongNumStart(6);
    } else if (gKeysNew & A_BUTTON) {
        if (sCMakeCursor[1] > 4) {
            if (sCMakeNameLen == 0) {
                m4aSongNumStart(0);
            } else {
                len = strlen(sCMakeName);
                for (i = 0; i < len && sCMakeName[i] == ' '; i++)
                    ;
                if (i >= len) {
                    gSubState = 1;
                    m4aSongNumStart(0);
                } else {
                    sCMakeResult = 0;
                    Link_SendCMakeName((u8 *)sCMakeName);
                    sCMakeWaiting = 1;
                    Reply_Clear();
                    gReplyWaiting = 1;
                    m4aSongNumStart(2);
                }
            }
        } else if (sCMakeNameLen > 6 && CMakeName_IsFull() == 0) {
            m4aSongNumStart(0);
        } else {
            m4aSongNumStart(2);
            CMakeName_AddChar(0);
        }
    } else if (gKeysNew & B_BUTTON) {
        if (sCMakeNameLen != 0) {
            CMakeName_DeleteChar();
        } else {
            sCMakeResult = -1;
            ret = 1;
        }
        m4aSongNumStart(3);
    }
    return ret;
}

void CMakeNameScreen_PrintNextRow(void)
{
    char ch[4];
    u16 buf[60];
    struct Window win;
    char *str;
    s32 i;
    s32 n;
    s32 tile;
    s32 pal;
    u16 *dst;
    s32 x;
    s32 y;

    if (sCMakeCharRow <= 4) {
        Text_SetFill(0, 0);
        Text_Clear();
        str = gNameCharTables[sCMakeCharPage * 5 + sCMakeCharRow];
        for (i = 0; i < 12; i++) {
            Str_GetChar(str, i, ch);
            Text_SetX(i * 16);
            Text_Print(ch, TEXT_DRAW);
        }
        memcpy(&win, gWindows, sizeof(struct Window));
        win.bg--;
        Window_PutText(&win, sCMakeCharRow, 0);
        for (i = 0; i < ARRAY_COUNT(buf); i++)
            buf[i] = 0x3FF;
        n = 24;
        tile = win.width * (sCMakeCharRow * 2) + 128;
        pal = 0x7000;
        for (i = 0; i < n; i++) {
            buf[i] = tile++ | pal;
            buf[i + 30] = tile++ | pal;
        }
        x = win.x + 2;
        y = win.y + 2 + sCMakeCharRow * 2;
        dst = Bg_GetMapPtr(win.bg, x, y);
        DmaSet(3, buf, dst, 0x80000000 | n);
        DmaSet(3, buf + 30, dst + 32, 0x80000000 | n);
        sCMakeCharRow++;
    }
}

void CMake_PrintTitle(char *str, s32 x)
{
    u16 buf[60];
    s32 n;
    s32 i;
    u32 size;
    s32 tile;
    s32 pal;
    u16 *dst;

    Text_SetFill(0, 0);
    Text_Clear();
    Text_SetX(x);
    Text_Print(str, TEXT_DRAW);
    n = 20;
    dst = (u16 *)0x06005380;
    Text_CopyToVram((u32)dst, n);
    for (i = 0; i < ARRAY_COUNT(buf); i++)
        buf[i] = 0x3FF;
    tile = 0x29C;
    pal = 0x9000;
    size = n * sizeof(u16);
    for (i = 0; i < n; i++) {
        buf[i] = tile++ | pal;
        buf[i + 30] = tile++ | pal;
    }
    dst = Bg_GetMapPtr(1, 2, 2);
    DmaCopy16(3, buf, dst, size);
    DmaCopy16(3, buf + 30, dst + 32, size);
}

void CMake_ClearTitle(void)
{
    u16 buf[60];
    s32 i;
    s32 n;
    u16 *dst;

    n = 20;
    for (i = 0; i < ARRAY_COUNT(buf); i++)
        buf[i] = 0x3FF;
    dst = Bg_GetMapPtr(1, 2, 2);
    DmaCopy16(3, buf, dst, n * sizeof(u16));
    DmaCopy16(3, buf + 30, dst + 32, n * sizeof(u16));
}

void CMakeName_AddChar(s32 mode)
{
    char ch[4];
    char prev[4];

    memset(ch, 0, 3);
    memset(prev, 0, 3);
    if (mode == 0) {
        char *str = gNameCharTables[sCMakeCharPage * 5 + sCMakeCursor[1]];

        Str_GetChar(str, sCMakeCursor[0], ch);
        Str_IsWideChar(sCMakeName, sCMakeNameLen - 1);
        Str_GetChar(sCMakeName, sCMakeNameLen - 1, prev);
        strcat(sCMakeName, ch);
        sCMakeNameLen++;
    }
    Text_SetFill(0, 0);
    Text_Clear();
    CMakeName_PrintName(sCMakeName);
    if (sCMakeNameLen > 6) {
        sCMakeCursor[0] = 11;
        sCMakeCursor[1] = 5;
    }
}

void CMakeName_DeleteChar(void)
{
    char ch[4];
    s32 wide;
    s32 len;

    memset(ch, 0, 3);
    wide = Str_IsWideChar(sCMakeName, sCMakeNameLen - 1);
    len = strlen(sCMakeName);
    if (wide)
        sCMakeName[len - 2] = 0;
    else
        sCMakeName[len - 1] = 0;
    sCMakeNameLen--;
    Text_SetFill(0, 0);
    Text_Clear();
    CMakeName_PrintName(sCMakeName);
}

s32 CMakeName_IsFull(void)
{
    return 0;
}

void CMakeName_PrintName(char *str)
{
    char ch[4];
    s32 i;

    Text_SetFill(0, 0);
    Text_Clear();
    Text_SetX(56);
    for (i = 0; i < sCMakeNameLen; i++) {
        Str_GetChar(str, i, ch);
        Text_SetX(56 + i * 16);
        Text_Print(ch, TEXT_DRAW);
    }
    HelpWin_CopyText(2, 1);
}

void CMake_DrawFooter(void)
{
    s32 x = 0;
    s32 y = 144;
    s32 i;
    s32 id;

    for (i = 0; i < 30; i++, x += 8) {
        if (i == 7 || i == 22)
            id = 1;
        else if (i >= 8 && i <= 21)
            id = 2;
        else
            id = 0;
        Obj_Draw(x, y, 20, id, 0, 3, 0);
    }
}

void CMakeGenderScreen_Setup(void)
{
    s32 i;

    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    gWindows[0].active = 1;
    gWindows[0].x = 9;
    gWindows[0].y = 7;
    gWindows[0].rows = 2;
    gWindows[0].width = 14;
    gWindows[0].height = 7;
    gWindows[0].style = 8;
    gWindows[0].variant = 0;
    gWindows[0].bg = 2;
    gWindows[0].slot = 0;
    gWindows[0].textX = 0;
    for (i = 0; i < gWindows[0].rows; i++) {
        gWindows[0].items[i].enabled = 1;
        gWindows[0].items[i].text = Msg_GetSystem(0);
    }
    if (gCMakeData.look & 0x80)
        gWindows[0].cursor = 1;
    sCMakeResult = 0;
    gScreenInitDone = 1;
    Header_Clear();
}

s32 CMakeGenderScreen_Init(void)
{
    struct Window tmp;
    u16 buf[60];
    s32 ret = 0;
    struct Window *win = gWindows;
    s32 row;
    s32 n;
    s32 i;
    s32 tile;
    s32 pal;
    u16 *p;
    u16 *map;

    if (gScreenInitDone == 0)
        CMakeGenderScreen_Setup();
    Text_SetFill(0, 0);
    Text_Clear();
    Window_Open(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = 0;
        ret = 1;
    }
    row = win->anim >> 3;
    if (ret == 0 && !(row & 1) && (n = row >> 1) <= 2) {
        Text_Clear();
        row = n - 1;
        memcpy(&tmp, win, sizeof(struct Window));
        tmp.bg--;
        Text_SetX(36);
        Text_Print(Msg_GetCMake(n + 6), TEXT_DRAW);
        Window_PutText(&tmp, row, 0);
        for (i = 0, p = buf; i < ARRAY_COUNT(buf); i++)
            buf[i] = 0x3FF;
        tile = tmp.width * (row * 2) + 128;
        pal = 0x7000;
        for (i = 0; i < tmp.width; i++) {
            p[i] = tile++ | pal;
            p[i + 30] = tile++ | pal;
        }
        map = Bg_GetMapPtr(tmp.bg, tmp.x, tmp.y + 1 + row * 2);
        DmaSet(3, p, map, 0x80000000 | tmp.width);
        DmaSet(3, &buf[30], map + 32, 0x80000000 | tmp.width);
    }
    if ((win->anim >> 3) == 1) {
        Text_SetFill(0, 0);
        Text_Clear();
        row = (144 - Text_Print(Msg_GetCMake(2), TEXT_WIDTH)) >> 1;
        CMake_PrintTitle(Msg_GetCMake(2), row);
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 CMakeGenderScreen_Main(void)
{
    s32 ret = CMakeGenderScreen_HandleInput();

    CMakeGenderScreen_DrawCursor();
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 CMakeGenderScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = 0;
        CMake_ClearTitle();
        if (sCMakeResult < 0) {
            ret = -1;
        } else {
            ret = 1;
            gCMakeData.look &= 0x7F;
            if (win->cursor)
                gCMakeData.look |= 0x80;
        }
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

void CMakeGenderScreen_DrawCursor(void)
{
    s32 x;
    s32 y;

    if (gScreenPhase == PHASE_MAIN) {
        x = (gWindows[0].x + 2) * 8;
        y = (gWindows[0].y + 1) * 8 + gWindows[0].cursor * 16;
        Obj_Draw(x, y, 0, 45, Obj_GetPalette(0, 45), 1, 0);
    }
}

s32 CMakeGenderScreen_HandleInput(void)
{
    struct Window *win;
    s32 ret;

    if (gKeysRepeat == 0)
        return 0;
    win = gWindows;
    ret = 0;
    if (gKeysRepeat & (DPAD_UP | DPAD_DOWN)) {
        win->cursor ^= 1;
        m4aSongNumStart(1);
    } else if (gKeysNew & A_BUTTON) {
        m4aSongNumStart(2);
        sCMakeResult = 1;
        ret = 1;
    } else if (gKeysNew & B_BUTTON) {
        m4aSongNumStart(3);
        sCMakeResult = -1;
        ret = 1;
    }
    return ret;
}

void CMakeLookScreen_Setup(void)
{
    s32 i;

    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    gWindows[0].active = 1;
    gWindows[0].x = 2;
    gWindows[0].y = 6;
    gWindows[0].rows = 4;
    gWindows[0].width = 12;
    gWindows[0].height = gWindows[0].rows * 2 + 3;
    gWindows[0].style = 8;
    gWindows[0].variant = 0;
    gWindows[0].bg = 2;
    gWindows[0].slot = 0;
    gWindows[0].textX = 0;
    memcpy(&gWindows[1], &gWindows[0], sizeof(struct Window));
    gWindows[1].x += gWindows[0].width + 1;
    gWindows[1].y = 6;
    gWindows[1].rows = 4;
    gWindows[1].width = 13;
    for (i = 0; i < gWindows[0].rows; i++) {
        gWindows[0].items[i].enabled = 1;
        gWindows[0].items[i].text = Msg_GetSystem(0);
    }
    for (i = 0; i < gWindows[1].rows; i++) {
        gWindows[1].items[i].enabled = 1;
        gWindows[1].items[i].text = Msg_GetSystem(0);
    }
    gWindows[0].cursor = gCMakeData.look & 3;
    gWindows[1].cursor = (gCMakeData.look >> 2) & 3;
    gWindows[4].items[0].enabled = 1;
    gWindows[4].items[0].text = Msg_GetNotice(NOTICE_LOOK_TAKEN);
    MsgBox_Layout();
    sCMakeResult = 0;
    sCMakeWaiting = 0;
    Link_SendCMakeLook(0xFF);
    gScreenInitDone = 1;
    Header_Clear();
}

s32 CMakeLookScreen_Init(void)
{
    struct Window tmp;
    u16 buf[60];
    s32 ret = 0;
    struct Window *win = gWindows;
    s32 row;
    s32 i;
    s32 tile;
    s32 pal;
    u16 *p;
    u16 *map;

    if (gScreenInitDone == 0)
        CMakeLookScreen_Setup();
    Text_SetFill(0, 0);
    Text_Clear();
    Window_Open(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = 0;
        ret = 1;
    }
    row = win->anim >> 3;
    if (ret == 0 && !(row & 1) && (row >>= 1) <= 4) {
        Text_Clear();
        row--;
        memcpy(&tmp, win, sizeof(struct Window));
        tmp.bg--;
        Text_SetX(20);
        Text_Print(Msg_GetTribe(row), TEXT_DRAW);
        Window_PutText(&tmp, row, 0);
        for (i = 0, p = buf; i < ARRAY_COUNT(buf); i++)
            buf[i] = 0x3FF;
        tile = tmp.width * (row * 2) + 128;
        pal = 0x7000;
        for (i = 0; i < tmp.width; i++) {
            p[i] = tile++ | pal;
            p[i + 30] = tile++ | pal;
        }
        map = Bg_GetMapPtr(tmp.bg, tmp.x, tmp.y + 1 + row * 2);
        DmaSet(3, p, map, 0x80000000 | tmp.width);
        DmaSet(3, &buf[30], map + 32, 0x80000000 | tmp.width);
    }
    if ((win->anim >> 3) == 1) {
        Text_SetFill(0, 0);
        Text_Clear();
        row = (144 - Text_Print(Msg_GetCMake(3), TEXT_WIDTH)) >> 1;
        CMake_PrintTitle(Msg_GetCMake(3), row);
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 CMakeLookScreen_Main(void)
{
    s32 ret = 0;
    s32 state = gSubState;

    if (state == 0) {
        ret = CMakeLookScreen_HandleInput();
    } else if (state >= 1 && state <= 3) {
        if (state == 1) {
            if (CMakeLookScreen_OpenLooks())
                gSubState++;
        } else if (state == 2) {
            if (sCMakeWaiting == 0) {
                CMakeLookScreen_HandleInput();
                if (gSubMode == 0)
                    gSubState++;
                else if (sCMakeResult < 0)
                    ret = 1;
            } else if (gDataFlags & DATA_REPLY) {
                if (gReplyResult != 0) {
                    gSubState = 4;
                    m4aSongNumStart(0);
                } else {
                    ret = 1;
                }
                sCMakeWaiting = 0;
                Reply_Clear();
            } else if (Reply_IsTimedOut()) {
                sCMakeWaiting = ret;
                Reply_Clear();
            }
        } else {
            if (CMakeLookScreen_CloseLooks())
                gSubState = ret;
        }
    } else if (state == 4) {
        if (MsgBox_Open())
            gSubState++;
    } else if (state == 5) {
        if (MsgBox_WaitKey())
            gSubState++;
    } else {
        if (MsgBox_Close())
            gSubState = 2;
    }
    CMakeLookScreen_DrawCursor();
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 CMakeLookScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;

    Text_SetFill(1, 0);
    Window_Close(win);
    if (sCMakeResult > 0)
        Window_Close(win + 1);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
        if (sCMakeResult > 0)
            win[1].anim += 8;
    } else {
        win->anim = ret;
        win[1].anim += 8;
        CMake_ClearTitle();
        if (sCMakeResult < 0) {
            ret = -1;
        } else {
            ret = 1;
            gCMakeData.look = (gCMakeData.look & ~0xF) | ((win->cursor & 3) | ((win[1].cursor & 3) << 2));
            Bg_LoadBackdrop(win->cursor & 3);
        }
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

void CMakeLookScreen_DrawCursor(void)
{
    struct Window *win;
    s32 frame;
    s32 i;
    s32 x;
    s32 y;

    if (gScreenPhase == PHASE_MAIN && (gSubState == 0 || gSubState == 2)) {
        frame = 45;
        for (i = 0; i <= gSubMode; i++) {
            if (gSubMode != 0 && i == 0 && (gFrameCount & 2))
                continue;
            win = &gWindows[i];
            x = win->x * 8;
            y = (win->y + 1) * 8 + win->cursor * 16;
            Obj_Draw(x, y, 0, frame, Obj_GetPalette(0, frame), 1, 0);
        }
    }
}

s32 CMakeLookScreen_HandleInput(void)
{
    struct Window *win;
    s32 ret;

    if (gKeysRepeat == 0)
        return 0;
    win = &gWindows[gSubMode];
    ret = 0;
    if (gKeysRepeat & DPAD_UP) {
        if (win->cursor == 0)
            win->cursor = win->rows - 1;
        else
            win->cursor--;
        m4aSongNumStart(1);
    } else if (gKeysRepeat & DPAD_DOWN) {
        if (win->cursor >= win->rows - 1)
            win->cursor = 0;
        else
            win->cursor++;
        m4aSongNumStart(1);
    }
    if (!(gKeysRepeat & (DPAD_UP | DPAD_DOWN))) {
        if (gKeysNew & A_BUTTON) {
            m4aSongNumStart(2);
            if (gSubMode == 0) {
                gSubMode = 1;
                gSubState = 1;
            } else {
                sCMakeResult = 1;
                Link_SendCMakeLook((u8)(gCMakeData.look & ~0x7F) | (gWindows[0].cursor & 3) | ((gWindows[1].cursor & 3) << 2));
                sCMakeWaiting = 1;
                Reply_Clear();
                gReplyWaiting = 1;
            }
        } else if (gKeysNew & B_BUTTON) {
            if (gSubMode != 0) {
                gSubMode = 0;
            } else {
                sCMakeResult = -1;
                ret = 1;
            }
            m4aSongNumStart(3);
        }
    }
    return ret;
}

s32 CMakeLookScreen_OpenLooks(void)
{
    struct Window tmp;
    u16 buf[60];
    s32 ret = 0;
    struct Window *win = &gWindows[1];
    struct Window *prev;
    s32 row;
    s32 half;
    s32 line;
    s32 i;
    s32 tile;
    s32 pal;
    u16 *map;

    Text_SetFill(0, 0);
    Text_Clear();
    Window_Open(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = 0;
        ret = 1;
    }
    row = win->anim >> 3;
    if (ret == 0 && !(row & 1) && (half = row >> 1) <= 4) {
        Text_Clear();
        row = half - 1;
        prev = win - 1;
        memcpy(&tmp, prev, sizeof(struct Window));
        tmp.bg--;
        Text_SetX(20);
        i = prev->cursor * 8;
        if (gCMakeData.look & 0x80)
            i += 4;
        Text_Print(Msg_GetLook(i + row), TEXT_DRAW);
        line = half + 3;
        Window_PutText(&tmp, line, 0);
        for (i = 0; i < ARRAY_COUNT(buf); i++)
            buf[i] = 0x3FF;
        tile = tmp.width * (line * 2) + 128;
        pal = 0x7000;
        for (i = 0; i < tmp.width; i++) {
            buf[i] = tile++ | pal;
            buf[i + 30] = tile++ | pal;
        }
        map = Bg_GetMapPtr(tmp.bg, win->x, win->y + 1 + row * 2);
        DmaSet(3, buf, map, 0x80000000 | win->width);
        DmaSet(3, &buf[30], map + 32, 0x80000000 | win->width);
    }
    if ((win->anim >> 3) == 1) {
        Text_SetFill(0, 0);
        Text_Clear();
        row = (144 - Text_Print(Msg_GetCMake(3), TEXT_WIDTH)) >> 1;
        CMake_PrintTitle(Msg_GetCMake(3), row);
    }
    return ret;
}

s32 CMakeLookScreen_CloseLooks(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[1];

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = 0;
        ret = 1;
    }
    return ret;
}

void CMakeBirthdayScreen_Setup(void)
{
    struct Window *win;
    s32 i;

    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    win = gWindows;
    win->active = 1;
    win->x = 9;
    win->y = 7;
    win->rows = 2;
    win->width = 14;
    win->height = 7;
    win->style = 8;
    win->variant = 0;
    win->bg = 2;
    win->slot = 0;
    win->textX = 0;
    for (i = 0; i < gWindows[0].rows; i++) {
        gWindows[0].items[i].enabled = 1;
        gWindows[0].items[i].text = Msg_GetSystem(0);
    }
    for (i = 0; i <= 1; i++) {
        sCMakeBirthday[i] = gCMakeData.birthday[i];
        if (sCMakeBirthday[i] == 0)
            sCMakeBirthday[i] = 1;
    }
    if (sCMakeBirthday[0] > 12)
        sCMakeBirthday[0] = 1;
    if (sCMakeBirthday[1] > sDaysInMonth[sCMakeBirthday[0] - 1])
        sCMakeBirthday[1] = 1;
    sCMakeResult = 0;
    sCMakeWaiting = 0;
    gScreenInitDone = 1;
    Header_Clear();
}

s32 CMakeBirthdayScreen_Init(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;
    s32 row;

    if (gScreenInitDone == 0)
        CMakeBirthdayScreen_Setup();
    Text_SetFill(0, 0);
    Text_Clear();
    Window_Open(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = 0;
        ret = 1;
    }
    row = win->anim >> 3;
    if (ret == 0 && row == 3)
        CMakeBirthdayScreen_PrintDate();
    if ((win->anim >> 3) == 1) {
        Text_SetFill(0, 0);
        Text_Clear();
        row = (144 - Text_Print(Msg_GetCMake(4), TEXT_WIDTH)) >> 1;
        CMake_PrintTitle(Msg_GetCMake(4), row);
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 CMakeBirthdayScreen_Main(void)
{
    s32 ret = 0;

    if (sCMakeWaiting == 0) {
        ret = CMakeBirthdayScreen_HandleInput();
    } else if (gDataFlags & DATA_REPLY) {
        if (gReplyResult == 0)
            ret = 1;
        sCMakeWaiting = 0;
        Reply_Clear();
    } else if (Reply_IsTimedOut()) {
        sCMakeWaiting = ret;
        Reply_Clear();
    }
    CMakeBirthdayScreen_DrawCursor();
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 CMakeBirthdayScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = ret;
        CMake_ClearTitle();
        if (sCMakeResult < 0) {
            ret = -1;
        } else {
            ret = 1;
            gCMakeData.birthday[0] = sCMakeBirthday[0];
            gCMakeData.birthday[1] = sCMakeBirthday[1];
        }
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

void CMakeBirthdayScreen_PrintDate(void)
{
    char str[2];
    struct Window tmp;
    u16 buf[60];
    s32 i;
    s32 tile;
    s32 pal;
    s32 digit;
    u16 *map;

    Text_SetFill(0, 0);
    Text_Clear();
    for (i = 0; i <= 2; i++) {
        strcpy(str, "0");
        if (i <= 1) {
            digit = (s8)(sCMakeBirthday[i] / 10);
            if (digit != 0) {
                str[0] += digit;
                Text_Print(str, TEXT_DRAW_FIX);
            } else {
                Text_AddX(9);
            }
            digit = (s8)(sCMakeBirthday[i] % 10);
            str[0] = digit + '0';
            Text_Print(str, TEXT_DRAW_FIX);
        }
        Text_Print(Msg_GetCMake(i + 9), TEXT_DRAW);
    }
    memcpy(&tmp, gWindows, sizeof(struct Window));
    tmp.bg--;
    Window_PutText(&tmp, 0, 0);
    for (i = 0; i < ARRAY_COUNT(buf); i++)
        buf[i] = 0x3FF;
    tile = 128;
    pal = 0x7000;
    for (i = 0; i < tmp.width; i++) {
        buf[i] = tile++ | pal;
        buf[i + 30] = tile++ | pal;
    }
    map = Bg_GetMapPtr(tmp.bg, tmp.x + 1, tmp.y + 2);
    DmaSet(3, buf, map, 0x80000000 | tmp.width);
    DmaSet(3, &buf[30], map + 32, 0x80000000 | tmp.width);
}

void CMakeBirthdayScreen_DrawCursor(void)
{
    s32 x;
    s32 y;

    if (gScreenPhase == PHASE_MAIN) {
        x = (gWindows[0].x + 1) * 8 + 10;
        if (gWindows[0].cursor != 0)
            x += 29;
        y = (gWindows[0].y + 4) * 8;
        Obj_Draw(x, y, 2, 5, Obj_GetPalette(2, 5), 1, 0);
    }
}

s32 CMakeBirthdayScreen_HandleInput(void)
{
    struct Window *win;
    s32 ret;
    s32 sel;

    if (gKeysRepeat == 0)
        return 0;
    win = gWindows;
    ret = 0;
    if (gKeysRepeat & DPAD_UP) {
        sel = win->cursor;
        if (sel == 0) {
            if (sCMakeBirthday[0] >= 12)
                sCMakeBirthday[0] = 1;
            else
                sCMakeBirthday[0]++;
            if (sCMakeBirthday[1] > sDaysInMonth[sCMakeBirthday[0] - 1])
                sCMakeBirthday[1] = sDaysInMonth[sCMakeBirthday[0] - 1];
        } else {
            if (sCMakeBirthday[sel] >= sDaysInMonth[sCMakeBirthday[0] - 1])
                sCMakeBirthday[sel] = 1;
            else
                sCMakeBirthday[sel]++;
        }
        CMakeBirthdayScreen_PrintDate();
        m4aSongNumStart(1);
    } else if (gKeysRepeat & DPAD_DOWN) {
        sel = win->cursor;
        if (sel == 0) {
            if (sCMakeBirthday[0] <= 1)
                sCMakeBirthday[0] = 12;
            else
                sCMakeBirthday[0]--;
            if (sCMakeBirthday[1] > sDaysInMonth[sCMakeBirthday[0] - 1])
                sCMakeBirthday[1] = sDaysInMonth[sCMakeBirthday[0] - 1];
        } else {
            if (sCMakeBirthday[sel] <= 1)
                sCMakeBirthday[sel] = sDaysInMonth[sCMakeBirthday[0] - 1];
            else
                sCMakeBirthday[sel]--;
        }
        CMakeBirthdayScreen_PrintDate();
        m4aSongNumStart(1);
    }
    if (gKeysRepeat & (DPAD_LEFT | DPAD_RIGHT)) {
        win->cursor ^= 1;
        m4aSongNumStart(1);
    }
    if (!(gKeysRepeat & DPAD_ANY)) {
        if (gKeysNew & A_BUTTON) {
            Link_SendCMakeBirthday(sCMakeBirthday[0], sCMakeBirthday[1]);
            sCMakeWaiting = 1;
            Reply_Clear();
            gReplyWaiting = 1;
            sCMakeResult = 1;
            m4aSongNumStart(2);
        } else if (gKeysNew & B_BUTTON) {
            sCMakeResult = -1;
            ret = 1;
            m4aSongNumStart(3);
        }
    }
    return ret;
}

void CMakeFavoriteScreen_Setup(void)
{
    struct Window *win;
    s32 i;
    s32 idx;
    char *str;
    char **dst;

    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    win = gWindows;
    win->active = 1;
    win->x = 1;
    win->y = 3;
    win->rows = 6;
    win->width = 26;
    win->height = 15;
    win->style = 8;
    win->variant = 0;
    win->bg = 2;
    win->slot = 0;
    win->textX = 0;
    win[1].active = 1;
    win[1].x = 24;
    win[1].y = 16;
    win[1].rows = 1;
    win[1].width = 5;
    win[1].height = 3;
    win[1].style = 3;
    win[1].variant = 0;
    win[1].bg = 1;
    win[1].slot = 2;
    win[1].textX = 0;
    for (i = 0; i < gWindows[0].rows; i++) {
        gWindows[0].items[i].enabled = 1;
        str = Msg_GetSystem(0);
        dst = &gWindows[0].items[i].text;
        *dst = str;
    }
    for (i = 0; i <= 7; i++) {
        if (i & 1)
            idx = (gCMakeData.favorites[i >> 1] >> 4) & 15;
        else
            idx = gCMakeData.favorites[i >> 1] & 15;
        sCMakeFoodOrder[idx] = i;
    }
    sCMakeResult = 0;
    sCMakeTextRow = 0;
    sCMakeTileRow = 0;
    sCMakeTop = 0;
    sCMakeSwapping = 0;
    sCMakeWaiting = 0;
    sCMakeCursor[1] = 0;
    sCMakeCursor[0] = 0;
    gSubMode = 0;
    gScreenInitDone = 1;
    Header_Clear();
}

s32 CMakeFavoriteScreen_Init(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;
    s32 x;

    if (gScreenInitDone == 0)
        CMakeFavoriteScreen_Setup();
    Text_SetFill(1, 0);
    Text_Clear();
    CMakeFavoriteScreen_PrintNextRow();
    Window_Open(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win++;
        Window_Open(win);
        if ((win->anim >> 3) < win->height - 1) {
            win->anim += 8;
        } else {
            win[-1].anim = 0;
            win->anim = 0;
            ret = 1;
        }
    }
    Text_SetFill(0, 0);
    Text_Clear();
    if ((win->anim >> 3) == 1) {
        Text_SetFill(0, 0);
        Text_Clear();
        x = (144 - Text_Print(Msg_GetCMake(5), TEXT_WIDTH)) >> 1;
        CMake_PrintTitle(Msg_GetCMake(5), x);
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 CMakeFavoriteScreen_Main(void)
{
    s32 ret;

    CMakeFavoriteScreen_PrintNextRow();
    CMakeFavoriteScreen_DrawNextRow();
    ret = 0;
    if (sCMakeWaiting == 0) {
        ret = CMakeFavoriteScreen_HandleInput();
    } else if (gDataFlags & DATA_REPLY) {
        if (gReplyResult == 0)
            ret = 1;
        sCMakeWaiting = 0;
        Reply_Clear();
    } else if (Reply_IsTimedOut()) {
        sCMakeWaiting = ret;
        Reply_Clear();
    }
    CMakeFavoriteScreen_DrawCursor();
    CMakeFavoriteScreen_DrawIcons();
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 CMakeFavoriteScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;
    s32 i;
    s32 v;

    Text_SetFill(1, 0);
    Window_Close(win);
    Window_Close(win + 1);
    if ((win[1].anim >> 3) < win[1].height - 1)
        win[1].anim += 8;
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = 0;
        win[1].anim = 0;
        CMake_ClearTitle();
        if (sCMakeResult < 0) {
            ret = -1;
        } else {
            for (i = 0; i < 4; i++)
                gCMakeData.favorites[i] = 0;
            for (i = 0; i <= 7; i++) {
                v = sCMakeFoodOrder[i];
                if (v & 1)
                    gCMakeData.favorites[v >> 1] |= (i & 15) << 4;
                else
                    gCMakeData.favorites[v >> 1] |= i & 15;
            }
            ret = 1;
        }
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

void CMakeFavoriteScreen_PrintNextRow(void)
{
    char str[2];
    struct Window tmp;
    s32 i;

    if (sCMakeTextRow > 9)
        return;
    memcpy(&tmp, gWindows, sizeof(struct Window));
    tmp.bg--;
    tmp.width = 18;
    Text_SetFill(0, 0);
    Text_Clear();
    if (sCMakeTextRow == 0) {
        str[0] = str[1] = 0;
        for (i = 1; i <= 9; i++) {
            str[0] = i + '0';
            Text_Print(str, TEXT_DRAW_FIX);
            Text_SetX(i << 4);
        }
    } else {
        Text_Print(Msg_GetItemName(sCMakeTextRow + 380), TEXT_DRAW);
    }
    Window_PutText(&tmp, sCMakeTextRow, 0);
    sCMakeTextRow++;
}

void CMakeFavoriteScreen_DrawNextRow(void)
{
    if (sCMakeTileRow < gWindows[0].rows)
        CMakeFavoriteScreen_DrawRow(sCMakeTileRow++);
}

void CMakeFavoriteScreen_DrawRow(s32 idx)
{
    u16 buf[60];
    struct Window *win = gWindows;
    s32 i;
    s32 n;
    s32 tile;
    s32 pal;
    s32 x;
    s32 y;
    u16 *map;

    if (idx >= win->rows)
        return;
    for (i = 0; i < ARRAY_COUNT(buf); i++)
        buf[i] = 0x3FF;
    n = 2;
    tile = (idx + sCMakeTop) * 4 + 128;
    pal = 0x7000;
    for (i = 0; i < n; i++) {
        buf[i] = tile++ | pal;
        buf[i + 30] = tile++ | pal;
    }
    x = win->x + 2;
    y = win->y + 2 + idx * 2;
    map = Bg_GetMapPtr(win->bg - 1, x, y);
    DmaSet(3, buf, map, 0x80000000 | n);
    DmaSet(3, &buf[30], map + 32, 0x80000000 | n);
    tile = (sCMakeFoodOrder[idx + sCMakeTop] + 1) * 36 + 128;
    n = 10;
    for (i = 0; i < n; i++) {
        buf[i] = tile++ | pal;
        buf[i + 30] = tile++ | pal;
    }
    x += 4;
    map = Bg_GetMapPtr(win->bg - 1, x, y);
    DmaSet(3, buf, map, 0x80000000 | n);
    DmaSet(3, &buf[30], map + 32, 0x80000000 | n);
}

void CMakeFavoriteScreen_DrawIcons(void)
{
    s32 i;
    s32 x;
    s32 y;
    s32 n;
    s32 frame;
    struct Window *win;

    x = gWindows[1].x * 8;
    y = gWindows[1].y * 8 + 5;
    for (i = 0; i <= 2; i++, x += 16)
        Obj_Draw(x, y, 22, i, 0, 1, 0);
    win = gWindows;
    if (gScreenPhase == PHASE_MAIN && sCMakeTileRow >= win->rows)
        n = win->rows;
    else
        n = sCMakeTileRow;
    x = win->x * 8 + 29;
    y = win->y * 8 + 14;
    for (i = 0; i < n; i++, y += 16) {
        frame = sCMakeFoodOrder[i + sCMakeTop] + 20;
        Obj_Draw(x, y, 0, frame, Obj_GetPalette(0, frame), 1, 0);
    }
    x = (win->x + 16) * 8;
    y = (win->y + 2) * 8 + 4;
    for (i = 0; i < n; i++, y += 16)
        Obj_DrawGauge(x, y, 7, 1, 9 - (i + sCMakeTop));
}

void CMakeFavoriteScreen_ScrollRows(s32 up)
{
    struct Window *win = gWindows;
    s32 step = 64;
    s32 from;
    s32 to;
    u8 *src;
    u8 *dst;
    s32 i;
    s32 j;

    if (up) {
        to = win->y + 1 + win->rows * 2;
        from = to - 2;
        step = -step;
    } else {
        from = win->y + 4;
        to = win->y + 2;
    }
    src = (u8 *)Bg_GetMapPtr(win->bg - 1, win->x + 1, from);
    dst = (u8 *)Bg_GetMapPtr(win->bg - 1, win->x + 1, to);
    for (i = 0; i < win->rows - 1; i++) {
        for (j = 0; j < 2; j++) {
            DmaSet(0, src, dst, 0x8000000F);
            src += step;
            dst += step;
        }
    }
}

void CMakeFavoriteScreen_SwapFoods(void)
{
    s32 i;
    s32 tmp;

    tmp = sCMakeFoodOrder[sCMakeCursor[0]];
    sCMakeFoodOrder[sCMakeCursor[0]] = sCMakeFoodOrder[sCMakeCursor[1]];
    sCMakeFoodOrder[sCMakeCursor[1]] = tmp;
    for (i = 0; i < 2; i++) {
        if (sCMakeCursor[i] >= sCMakeTop && sCMakeCursor[i] < sCMakeTop + gWindows[0].rows)
            CMakeFavoriteScreen_DrawRow(sCMakeCursor[i] - sCMakeTop);
    }
}

void CMakeFavoriteScreen_DrawCursor(void)
{
    s32 frame = 45;
    struct Window *win = gWindows;
    s32 x;
    s32 y;
    s32 blink;

    if (gSubMode) {
        x = win[1].x * 8 - 10;
        y = win[1].y * 8 + 5;
    } else {
        x = win->x * 8;
        y = win->y * 8;
        y += (win->cursor + 1) * 16;
    }
    Obj_Draw(x, y, 0, frame, Obj_GetPalette(0, frame), 1, 0);
    if (sCMakeSwapping && (gFrameCount & 2)) {
        if (sCMakeCursor[0] >= sCMakeTop && sCMakeCursor[0] < sCMakeTop + win->rows) {
            x = win->x * 8;
            y = win->y * 8;
            y += (sCMakeCursor[0] - sCMakeTop + 1) * 16;
            Obj_Draw(x - 2, y - 2, 0, frame, Obj_GetPalette(0, frame), 1, 0);
        }
    }
    blink = (gFrameCount & 8) >> 2;
    x = (win->x + 23) * 8;
    if (sCMakeTop != 0) {
        y = (win->y + 3) * 8;
        y += blink;
        Obj_Draw(x, y, 0, 46, Obj_GetPalette(0, 46), 1, 0);
    }
    if (sCMakeTop + win->rows <= 8) {
        y = (win->y + 11) * 8;
        y -= blink;
        Obj_Draw(x, y, 0, 46, Obj_GetPalette(0, 46), 1, 0x20000000);
    }
}

s32 CMakeFavoriteScreen_HandleInput(void)
{
    struct Window *win;
    s32 ret;
    u8 buf[8];
    s32 i;
    s32 v;

    if (gKeysRepeat == 0)
        return 0;
    win = gWindows;
    ret = 0;
    if (gSubMode == 0) {
        if (gKeysRepeat & DPAD_UP) {
            if (win->cursor == 0) {
                if (sCMakeTop == 0) {
                    m4aSongNumStart(0);
                } else {
                    sCMakeTop--;
                    CMakeFavoriteScreen_ScrollRows(1);
                    CMakeFavoriteScreen_DrawRow(0);
                    m4aSongNumStart(1);
                }
            } else {
                win->cursor--;
                m4aSongNumStart(1);
            }
        } else if (gKeysRepeat & DPAD_DOWN) {
            if (win->cursor >= win->rows - 1) {
                if (sCMakeTop + win->rows < 8) {
                    sCMakeTop++;
                    CMakeFavoriteScreen_ScrollRows(0);
                    CMakeFavoriteScreen_DrawRow(win->rows - 1);
                    m4aSongNumStart(1);
                } else {
                    m4aSongNumStart(0);
                }
            } else {
                win->cursor++;
                m4aSongNumStart(1);
            }
        }
    } else if (gKeysNew & (DPAD_UP | DPAD_DOWN)) {
        m4aSongNumStart(0);
    }

    if (gKeysNew & DPAD_LEFT) {
        if (gSubMode) {
            gSubMode = 0;
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    } else if (gKeysNew & DPAD_RIGHT) {
        if (gSubMode == 0) {
            if (sCMakeSwapping) {
                m4aSongNumStart(0);
            } else {
                gSubMode = 1;
                m4aSongNumStart(1);
            }
        } else {
            m4aSongNumStart(0);
        }
    }

    if (!(gKeysRepeat & DPAD_ANY)) {
        if (gKeysNew & A_BUTTON) {
            if (gSubMode == 0) {
                sCMakeCursor[sCMakeSwapping] = sCMakeTop + win->cursor;
                if (sCMakeSwapping)
                    CMakeFavoriteScreen_SwapFoods();
                sCMakeSwapping ^= 1;
            } else {
                for (i = 0; i < 4; i++)
                    buf[i] = 0;
                for (i = 0; i < 8; i++) {
                    v = sCMakeFoodOrder[i];
                    if (v & 1)
                        buf[v >> 1] |= (i & 15) << 4;
                    else
                        buf[v >> 1] |= i & 15;
                }
                Link_SendCMakeFavorite(buf);
                sCMakeResult = 1;
                sCMakeWaiting = 1;
                Reply_Clear();
                gReplyWaiting = 1;
            }
            m4aSongNumStart(2);
        } else if (gKeysNew & B_BUTTON) {
            if (sCMakeSwapping) {
                sCMakeSwapping = 0;
            } else {
                sCMakeResult = -1;
                ret = 1;
            }
            m4aSongNumStart(3);
        }
    }
    return ret;
}

void CMakeJobScreen_Setup(void)
{
    s32 i;

    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);

    gWindows->active = 1;
    gWindows->x = 5;
    gWindows->y = 5;
    gWindows->rows = 6;
    gWindows->width = 21;
    gWindows->height = 12;
    gWindows->style = 8;
    gWindows->variant = 0;
    gWindows->bg = 2;
    gWindows->slot = 0;
    gWindows->textX = 0;
    for (i = 0; i < gWindows->rows; i++) {
        gWindows->items[i].enabled = 1;
        gWindows->items[i].text = Msg_GetSystem(0);
    }
    gWindows[4].items[0].enabled = 1;
    gWindows[4].items[0].text = Msg_GetNotice(NOTICE_JOB_TAKEN);
    MsgBox_Layout();
    gWindows->cursor = gCMakeData.job[0];

    sCMakeResult = 0;
    sCMakeTop = 0;
    sCMakeSwapping = 0;
    sCMakeTextRow = 0;
    sCMakeTileRow = 0;
    sCMakeWaiting = 0;
    sCMakeCursor[1] = 0;
    sCMakeCursor[0] = 0;
    gSubState = 0;
    gSubMode = 0;
    gScreenInitDone = 1;
    Header_Clear();
}

s32 CMakeJobScreen_Init(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;
    s32 x;

    if (gScreenInitDone == 0)
        CMakeJobScreen_Setup();
    CMakeJobScreen_PrintNextRow();
    Text_SetFill(1, 0);
    Text_Clear();
    Window_Open(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = ret;
        ret = 1;
    }
    Text_SetFill(0, 0);
    Text_Clear();
    if ((win->anim >> 3) == 1) {
        Text_SetFill(0, 0);
        Text_Clear();
        x = (144 - Text_Print(Msg_GetCMake(6), TEXT_WIDTH)) >> 1;
        CMake_PrintTitle(Msg_GetCMake(6), x);
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 CMakeJobScreen_Main(void)
{
    s32 ret;

    CMakeJobScreen_PrintNextRow();
    CMakeJobScreen_DrawNextRow();
    ret = 0;
    if (gSubState == 0) {
        if (sCMakeWaiting == 0) {
            ret = CMakeJobScreen_HandleInput();
        } else if (gDataFlags & DATA_REPLY) {
            if (gReplyResult != 0) {
                gSubState = 1;
                m4aSongNumStart(0);
            } else {
                ret = 1;
            }
            sCMakeWaiting = 0;
            Reply_Clear();
        } else if (Reply_IsTimedOut()) {
            sCMakeWaiting = ret;
            Reply_Clear();
        }
    } else {
        if (gSubState == 1) {
            if (MsgBox_Open())
                gSubState++;
        } else if (gSubState == 2) {
            if (MsgBox_WaitKey())
                gSubState++;
        } else {
            if (MsgBox_Close())
                gSubState = ret;
        }
        ret = 0;
    }
    CMakeJobScreen_DrawCursor();
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 CMakeJobScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = ret;
        CMake_ClearTitle();
        if (sCMakeResult < 0) {
            ret = -1;
        } else {
            gCMakeData.job[0] = win->cursor;
            ret = 1;
        }
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

void CMakeJobScreen_PrintNextRow(void)
{
    struct Window tmp;

    if (sCMakeTextRow <= 7) {
        memcpy(&tmp, gWindows, sizeof(struct Window));
        tmp.bg--;
        tmp.width = 8;
        Text_SetFill(0, 0);
        Text_Clear();
        Text_Print(Msg_GetJob(sCMakeTextRow), TEXT_DRAW);
        Window_PutText(&tmp, sCMakeTextRow, 0);
        sCMakeTextRow++;
    }
}

void CMakeJobScreen_DrawNextRow(void)
{
    u16 buf[60];
    struct Window *win;
    s32 i;
    s32 len;
    s32 attr;
    s32 tile;
    u16 *map;
    s32 x;
    s32 y;

    if (sCMakeTileRow <= 3) {
        win = gWindows;
        for (i = 0; i < ARRAY_COUNT(buf); i++)
            buf[i] = 0x3FF;
        attr = 0x7000;
        tile = sCMakeTileRow * 16 + 128;
        len = 8;
        for (i = 0; i < len; i++) {
            buf[i] = tile++ | attr;
            buf[i + 30] = tile++ | attr;
        }
        tile = sCMakeTileRow * 16 + 192;
        len += 10;
        for (i = 10; i < len; i++) {
            buf[i] = tile++ | attr;
            buf[i + 30] = tile++ | attr;
        }
        x = win->x + 2;
        y = win->y + 2 + sCMakeTileRow * 2;
        map = Bg_GetMapPtr(win->bg - 1, x, y);
        DmaCopy16(3, buf, map, len << 1);
        DmaCopy16(3, &buf[30], map + 32, len << 1);
        sCMakeTileRow++;
    }
}

void CMakeJobScreen_DrawCursor(void)
{
    struct Window *win;
    s32 x;
    s32 y;

    if (sCMakeTileRow > 3) {
        win = gWindows;
        x = win->x * 8 - 2;
        x += (win->cursor >> 2) * 80;
        y = win->y * 8;
        y += ((win->cursor & 3) + 1) * 16;
        Obj_Draw(x, y, 0, 45, Obj_GetPalette(0, 45), 1, 0);
    }
}

s32 CMakeJobScreen_HandleInput(void)
{
    struct Window *win;
    s32 ret;
    u8 key;

    if (gKeysRepeat == 0)
        return 0;
    win = gWindows;
    ret = 0;
    if (gKeysRepeat & DPAD_UP) {
        if ((win->cursor & 3) == 0)
            win->cursor += 3;
        else
            win->cursor--;
        m4aSongNumStart(1);
    } else {
        key = gKeysRepeat & DPAD_DOWN;
        if (key) {
            if ((win->cursor & 3) > 2)
                win->cursor -= 3;
            else
                win->cursor++;
            m4aSongNumStart(1);
        }
    }
    if (gKeysRepeat & (DPAD_LEFT | DPAD_RIGHT)) {
        key = (u8)win->cursor >> 2;
        if (key == 0)
            win->cursor += 4;
        else
            win->cursor -= 4;
        m4aSongNumStart(1);
    }
    if (!(gKeysRepeat & DPAD_ANY)) {
        if (gKeysNew & A_BUTTON) {
            sCMakeResult = 1;
            Link_SendCMakeJob(win->cursor);
            sCMakeWaiting = 1;
            Reply_Clear();
            gReplyWaiting = 1;
            m4aSongNumStart(2);
        } else if (gKeysNew & B_BUTTON) {
            sCMakeResult = -1;
            ret = 1;
            m4aSongNumStart(3);
        }
    }
    return ret;
}

void CMakeConfirmScreen_Setup(void)
{
    struct Window *win;
    s32 i;
    s32 save;

    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);

    gWindows->active = 1;
    gWindows->x = 2;
    gWindows->y = 4;
    gWindows->rows = 4;
    gWindows->width = 25;
    gWindows->height = 12;
    gWindows->style = 8;
    gWindows->variant = 0;
    gWindows->bg = 2;
    gWindows->slot = 0;
    gWindows->textX = 0;

    gWindows[1].active = 1;
    gWindows[1].x = 18;
    gWindows[1].y = 15;
    gWindows[1].rows = 3;
    gWindows[1].width = 11;
    gWindows[1].height = 4;
    gWindows[1].style = 3;
    gWindows[1].variant = 0;
    gWindows[1].bg = 1;
    gWindows[1].slot = 2;
    gWindows[1].textX = 0;

    for (i = 0; i < gWindows->rows; i++) {
        gWindows->items[i].enabled = 1;
        gWindows->items[i].text = Msg_GetSystem(0);
    }
    for (i = 0; i < gWindows[1].rows; i++) {
        gWindows[1].items[i].enabled = 1;
        gWindows[1].items[i].text = Msg_GetSystem(0);
    }

    Text_SetFill(0, 0);
    Text_Clear();
    Text_Print(Msg_GetCMake(22), TEXT_DRAW);
    Text_CopyToObj(1, 10, 0);

    sCMakeResult = 0;
    sCMakeTop = 0;
    sCMakeSwapping = 0;
    sCMakeTextRow = 0;
    sCMakeTileRow = 0;

    Text_SetFill(0, 0);
    Text_Clear();
    win = &gWindows[1];
    save = win->bg;
    win->bg = 0;
    for (i = 2; i >= 0; i--)
        Window_PrintNextItem(win);
    win->bg = save;

    gSubMode = 1;
    gScreenInitDone = 1;
    Header_Clear();
}

s32 CMakeConfirmScreen_Init(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;
    s32 x;

    if (gScreenInitDone == 0)
        CMakeConfirmScreen_Setup();
    CMakeConfirmScreen_PrintNextRow();
    Text_SetFill(1, 0);
    Text_Clear();
    Window_Open(win);
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        Text_SetFill(0, 0);
        Text_Clear();
        Window_Open(win + 1);
        if ((win[1].anim >> 3) < win[1].height - 1) {
            win[1].anim += 8;
        } else {
            win->anim = ret;
            win[1].anim = ret;
            ret = 1;
        }
    }
    Text_SetFill(0, 0);
    Text_Clear();
    if ((win->anim >> 3) == 1) {
        Text_SetFill(0, 0);
        Text_Clear();
        x = (144 - Text_Print(Msg_GetCMake(20), TEXT_WIDTH)) >> 1;
        CMake_PrintTitle(Msg_GetCMake(20), x);
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 CMakeConfirmScreen_Main(void)
{
    struct Window *win = &gWindows[1];
    s32 ret;
    s32 i;
    s32 x;
    s32 y;

    if (gSubMode == 0) {
        Window_Close(win);
        if ((win->anim >> 3) < win->height - 1)
            win->anim += 8;
    }
    CMakeConfirmScreen_DrawNextRow();
    ret = CMakeConfirmScreen_HandleInput();
    CMakeConfirmScreen_DrawCursor();
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    if (gSubMode) {
        x = gWindows[1].x * 8 + 10;
        y = gWindows[1].y * 8 + 7;
        for (i = 0; i <= 8; i++, x += 16)
            Obj_Draw(x, y, 22, i, 0, 1, 0);
    }
    return ret;
}

s32 CMakeConfirmScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;

    Text_SetFill(1, 0);
    Window_Close(win);
    if (gSubMode) {
        Window_Close(win + 1);
        if ((win[1].anim >> 3) < win[1].height - 1)
            win[1].anim += 8;
    }
    if ((win->anim >> 3) < win->height) {
        win->anim += 8;
    } else {
        win->anim = 0;
        win[1].anim = 0;
        CMake_ClearTitle();
        if (sCMakeResult < 0) {
            ret = -1;
            gSubState = win->cursor;
        } else {
            Link_SendCMakeEnd();
            ret = 1;
            gSubState = 0;
        }
        Text_SetFill(0, 0);
        Text_Clear();
        Text_SetX((40 - Text_Print(Msg_GetCMake(0), TEXT_WIDTH)) >> 1);
        Text_Print(Msg_GetCMake(0), TEXT_DRAW);
        Text_CopyToObj(1, 10, 0);
    }
    Obj_DrawBanner(2, 8, 7, 20, 0, 1);
    return ret;
}

void CMakeConfirmScreen_PrintNextRow(void)
{
    char buf[64];
    struct Window tmp;
    s32 n;
    s32 idx;

    if (sCMakeTextRow <= 3) {
        memcpy(&tmp, gWindows, sizeof(struct Window));
        tmp.bg--;
        tmp.width = 23;
        Text_SetFill(0, 0);
        Text_Clear();
        memset(buf, 0, sizeof(buf));
        idx = sCMakeTextRow + 23;
        strcpy(buf, Msg_GetCMake(idx));
        Text_Print(buf, TEXT_DRAW);
        Text_AddX(8);
        if (sCMakeTextRow == 0) {
            Text_Print(gCMakeData.name, TEXT_DRAW);
        } else if (sCMakeTextRow == 1) {
            n = (gCMakeData.look & 0x80) ? 8 : 7;
            Text_Print(Msg_GetCMake(n), TEXT_DRAW);
        } else if (sCMakeTextRow == 2) {
            n = gCMakeData.look & 3;
            strcpy(buf, Msg_GetTribe(n));
            strcat(buf, ",");
            Text_Print(buf, TEXT_DRAW);
            Text_AddX(8);
            idx = n * 8;
            if (gCMakeData.look & 0x80)
                idx += 4;
            Text_Print(Msg_GetLook(idx + ((gCMakeData.look >> 2) & 3)), TEXT_DRAW);
        } else if (sCMakeTextRow == 3) {
            n = gCMakeData.job[0];
            Text_Print(Msg_GetCMake(n + 12), TEXT_DRAW);
        }
        Window_PutText(&tmp, sCMakeTextRow, 0);
        sCMakeTextRow++;
    }
}

void CMakeConfirmScreen_DrawNextRow(void)
{
    u16 buf[60];
    struct Window *win;
    s32 i;
    s32 len;
    s32 attr;
    s32 tile;
    u16 *map;
    s32 x;
    s32 y;

    if (sCMakeTileRow <= 3) {
        win = gWindows;
        for (i = 0; i < ARRAY_COUNT(buf); i++)
            buf[i] = 0x3FF;
        attr = 0x7000;
        len = 23;
        tile = sCMakeTileRow * 46 + 128;
        for (i = 0; i < len; i++) {
            buf[i] = tile++ | attr;
            buf[i + 30] = tile++ | attr;
        }
        x = win->x + 2;
        y = win->y + 2 + sCMakeTileRow * 2;
        map = Bg_GetMapPtr(win->bg - 1, x, y);
        DmaCopy16(3, buf, map, len << 1);
        DmaCopy16(3, &buf[30], map + 32, len << 1);
        sCMakeTileRow++;
    }
}

void CMakeConfirmScreen_DrawCursor(void)
{
    struct Window *win;
    s32 sel;
    s32 col;
    s32 x;
    s32 y;

    if (sCMakeTileRow > 3) {
        sel = gSubMode;
        win = &gWindows[sel];
        if (sel) {
            col = win->x - 1;
            y = win->y * 8 + 7;
            x = (win->cursor * 5 + col) * 8;
            Obj_Draw(x, y, 0, 45, Obj_GetPalette(0, 45), 1, 0);
        } else {
            x = win->x * 8 - 2;
            y = (win->y + 2) * 8;
            y += win->cursor * 16;
            Obj_Draw(x, y, 0, 45, Obj_GetPalette(0, 45), 1, sel);
        }
    }
}

s32 CMakeConfirmScreen_HandleInput(void)
{
    struct Window *win;
    s32 ret;
    s32 x;
    s32 w;

    if (gKeysRepeat == 0)
        return 0;
    win = &gWindows[gSubMode];
    ret = 0;
    if (gSubMode == 0) {
        if (gKeysRepeat & DPAD_UP) {
            if (win->cursor == 0)
                win->cursor = win->rows - 1;
            else
                win->cursor--;
            m4aSongNumStart(1);
        } else if (gKeysRepeat & DPAD_DOWN) {
            if (win->cursor >= win->rows - 1)
                win->cursor = 0;
            else
                win->cursor++;
            m4aSongNumStart(1);
        }
    }
    if (gSubMode != 0 && (gKeysRepeat & (DPAD_LEFT | DPAD_RIGHT))) {
        if (gSubMode != 0) {
            win->cursor ^= 1;
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    }
    if (!(gKeysRepeat & DPAD_ANY)) {
        if (gKeysNew & A_BUTTON) {
            if (gSubMode != 0) {
                if (win->cursor != 0) {
                    gSubMode = 0;
                    CMake_ClearTitle();
                    Text_SetFill(0, 0);
                    Text_Clear();
                    w = Text_Print(Msg_GetCMake(21), TEXT_WIDTH);
                    x = (144 - w) >> 1;
                    CMake_PrintTitle(Msg_GetCMake(21), x);
                } else {
                    sCMakeResult = 1;
                    ret = 1;
                }
            } else {
                sCMakeResult = -1;
                ret = 1;
            }
            m4aSongNumStart(2);
        } else if (gKeysNew & B_BUTTON) {
            if (gSubMode != 0) {
                gSubMode = 0;
                m4aSongNumStart(3);
                CMake_ClearTitle();
                Text_SetFill(0, 0);
                Text_Clear();
                w = Text_Print(Msg_GetCMake(21), TEXT_WIDTH);
                x = (144 - w) >> 1;
                CMake_PrintTitle(Msg_GetCMake(21), x);
            } else {
                m4aSongNumStart(0);
            }
        }
    }
    return ret;
}
