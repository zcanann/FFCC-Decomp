#ifndef GUARD_WINDOW_H
#define GUARD_WINDOW_H

#include "global.h"

struct WinItem {
    s16 enabled;
    s16 drawn;
    char *text;
};

/* A menu window. Positions and sizes are in 8-pixel tiles. */
struct Window {
    u8 active;
    u8 anim;
    s8 cursor;
    s8 style;
    s8 variant;
    s8 bg;
    s8 slot;
    s8 textX;
    s8 skipRows;
    s8 tallRows;
    s8 keepFrame;
    u8 pad[3];
    s16 rows;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    struct WinItem items[11];
};

extern struct Window gWindows[5];

void Window_PrintNextItem(struct Window *win);
void Window_PutText(struct Window *win, s32 row, s32 unused);
s32 Window_GetItemPalette(s32 enabled, s32 slot);
s32 Window_GetTextTile(s32 slot);
s32 Window_GetFrameTile(s32 slot);
void Window_Open(struct Window *win);
void Window_OpenStyle0(struct Window *win, s32 tile, s32 pal, s32 type);
void Window_OpenStyle0Horz(struct Window *win, s32 tile, s32 pal);
void Window_OpenStyle1(struct Window *win, s32 tile, s32 pal);
void Window_OpenStyle3(struct Window *win, s32 tile, s32 pal);
void Window_OpenStyle4(struct Window *win, s32 tile, s32 pal);
void Window_OpenStyle5(struct Window *win, s32 tile, s32 pal);
void Window_OpenStyle6(struct Window *win, s32 tile, s32 pal);
void Window_Nop(struct Window *win);
void Window_OpenStyle7(struct Window *win, s32 tile, s32 pal);
void Window_OpenStyle8(struct Window *win, s32 tile, s32 pal);
void Window_OpenStyle9(struct Window *win, s32 tile, s32 pal);
void Window_OpenStyle14(struct Window *win, s32 tile, s32 pal);
void Window_OpenStyleNone(struct Window *win, s32 tile, s32 pal);
void Window_Close(struct Window *win);
void Window_CloseStyle0(struct Window *win);
void Window_CloseStyle0Horz(struct Window *win);
void Window_CloseStyle1(struct Window *win);
void Window_CloseStyle3(struct Window *win);
void Window_CloseStyle4(struct Window *win);
void Window_CloseStyle5(struct Window *win);
void Window_CloseStyle6(struct Window *win);
void Window_CloseStyle7(struct Window *win);
void Window_CloseStyle8(struct Window *win);
void Window_CloseStyle9(struct Window *win);
void Window_CloseStyle14(struct Window *win);

void Obj_DrawBanner(s32 prio, s32 x, s32 y, s32 n, s32 offset, s32 mode);
void Obj_DrawGil(s32 x, s32 y, s32 len, s32 pal, u32 value, s32 color);
void Obj_DrawGauge(s32 x, s32 y, s32 n, s32 pal, s32 fill);

void MsgBox_Layout(void);
s32 MsgBox_Open(void);
s32 MsgBox_WaitKey(void);
s32 MsgBox_Close(void);
u32 Window_GetTextVram(struct Window *win, s32 row, s32 half);
void StatusWin_Setup(s32 idx, s32 bg);
s32 StatusWin_Open(s32 idx);
void StatusWin_Refresh(s32 idx);
void StatusWin_DrawIcon(s32 idx);
void BonusWin_Setup(s32 idx);
void BonusWin_Show(s32 idx, s32 pal);
void BonusWin_Hide(s32 bg);
void Window_DrawSlotRow(s32 idx, s32 mode, s32 row);
void Window_ClearRow(s32 idx, s32 row);
void Bg_FillBlank(s32 bg, s32 x, s32 y, s32 w, s32 h);
s32 Window_GetRowTile(struct Window *win, s32 row);
void Window_PutRowAt(struct Window *win, s32 bg, s32 row, s32 x, s32 y, s32 pal);
void Window_ScrollRows(s32 dir, s32 idx, s32 bg);
void Window_DrawRow(s32 idx, s32 bg, s32 row, s32 y, s32 pal);
void Window_ResetItems(struct Window *win, s32 enabled);
void Window_DrawScrollArrows(s32 idx, s32 bg, s32 flags);
void ListWin_Setup(s32 idx, s32 x, s32 w, s32 bg);
void HelpWin_DrawFrame(s32 bg, s32 slot, s32 pal);
void HelpWin_CopyText(s32 bg, s32 slot);
void HelpWin_Clear(s32 bg, s32 slot);
void Header_PrintItemDesc(s32 no);
void HelpWin_PrintItemDesc(s32 no, s32 bg, s32 slot);

#endif
