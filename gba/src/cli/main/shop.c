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

static s8 sShopResult;
static s8 sInfoItem;
static s8 sShopRow;
static s8 sShopTop;
static s8 sShopWaiting;
static s8 sInfoRow;
static s8 sInfoMode;
static s8 sShopQuantity;
static s8 sShopPrevQuantity;
static s8 sInfoArrow;
static s8 sInfoShowIcon;
const char sSlashText[] = "/";

void ShopTopScreen_DrawCursor(void);
s32 ShopTopScreen_HandleInput(void);
void InfoWin_GetDescLine(s32, char *);
s32 Shop_ChangeQuantity(s32);
void InfoWin_ShowQuantityArrow(s32);
void InfoWin_DrawIcons(void);
void InfoWin_PrintTotal(void);
void ShopList_PrintSellItem(s32, s32);
void ShopList_DrawCursor(void);
s32 ShopList_HandleInput(void);
void ShopList_DrawIcons(void);
void ShopList_PrintBuyItem(s32, s32);
void ShopList_DrawRow(s32, s32, s32);
void ShopList_RedrawRows(void);
s32 Shop_CanBuy(s32);
s32 Shop_CanSell(s32);
void ShopList_ScrollRows(s32);
s32 ShopList_OpenConfirm(void);
s32 ShopList_CloseConfirm(void);
s32 InfoWin_Open(void);
s32 InfoWin_Update(void);
s32 InfoWin_Close(void);
void InfoWin_SetItem(s32);
void InfoWin_SetMode(s32);
void InfoWin_ClearRows(s32);
void InfoWin_PrintNextRow(void);
s32 InfoWin_IsDrawn(void);

void ShopTopScreen_Setup(void)
{
    s32 i;

    Bg_SetScroll(15, 0, 0);
    gSubState = 0;
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    gWindows[0].active = 1;
    gWindows[0].cursor = gShopMenuPos[0];
    gWindows[0].x = 20;
    gWindows[0].y = 1;
    gWindows[0].rows = 3;
    gWindows[0].width = 9;
    gWindows[0].height = 8;
    gWindows[0].style = 1;
    gWindows[0].variant = 0;
    gWindows[0].bg = 2;
    gWindows[0].slot = 0;
    gWindows[0].textX = 0;
    gSubMode = 0;
    for (i = 0; i < gWindows[0].rows; i++) {
        gWindows[0].items[i].enabled = 1;
        if (i <= 1)
            gWindows[0].items[i].text = Msg_GetSystem(i + 11);
        else
            gWindows[0].items[i].text = Msg_GetSystem(4);
    }
    Text_LoadPalette(3, 0, 0);
    Text_LoadPalette(4, 2, 0);
    Text_CopyFill(0x06008000);
    Obj_AllocPalette(4, 0);
    Obj_LoadToBg(4, 0, 2, 0);
    sShopResult = 0;
    gScreenInitDone = 1;
}

s32 ShopTopScreen_Init(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0)
        ShopTopScreen_Setup();
    win = gWindows;
    Text_SetFill(1, 0);
    Text_Clear();
    Window_PrintNextItem(win);
    Window_Open(win);
    if ((win->anim >> 3) >= win->height - 2)
        ret = 1;
    win->anim += 8;
    return ret;
}

s32 ShopTopScreen_Main(void)
{
    s32 ret;

    Text_SetFill(1, 0);
    ret = 0;
    if (gMenuHasInput) {
        ret = ShopTopScreen_HandleInput();
        ShopTopScreen_DrawCursor();
    }
    return ret;
}

s32 ShopTopScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    Text_Clear();
    win = gWindows;
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 2) {
        ret = sShopResult;
        Obj_FreePalette(4);
    }
    win->anim += 8;
    return ret;
}

void ShopTopScreen_DrawCursor(void)
{
    struct Window *win = gWindows;
    s32 x = (win->x - 1) * 8;
    s32 y = (win->y + 1) * 8;

    y += win->cursor * 16;
    Obj_Draw(x, y, 0, 45, Obj_GetPalette(0, 45), 2, 0);
}

s32 ShopTopScreen_HandleInput(void)
{
    struct Window *win;
    s32 ret;

    if (gKeysRepeat == 0)
        return 0;
    ret = 0;
    win = gWindows;
    if (gKeysRepeat & DPAD_UP) {
        if (win->cursor != 0)
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
    if (gKeysRepeat & (DPAD_UP | DPAD_DOWN))
        return ret;
    if (gKeysNew & A_BUTTON) {
        if (win->cursor == win->rows - 1) {
            sShopResult = -1;
            gInputLockFrames = 6;
            Link_SendEvent(7, 0, 0);
        } else if (win->cursor == 0) {
            sShopResult = 1;
        } else {
            sShopResult = 1;
        }
        ret = 1;
        m4aSongNumStart(2);
    }
    if (gKeysNew & B_BUTTON) {
        gInputLockFrames = 6;
        sShopResult = -1;
        ret = 1;
        Link_SendEvent(7, 0, 0);
        m4aSongNumStart(3);
    }
    return ret;
}

void ShopList_Setup(void)
{
    s32 i;

    gSubState = 0;
    if (gScreen == 1)
        Link_SendRequest(7, 0);
    else
        Link_SendRequest(6, 0);
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    ListWin_Setup(1, 16, 0, 2);
    gWindows[2].active = 1;
    gWindows[2].cursor = 0;
    gWindows[2].x = 6;
    gWindows[2].y = 14;
    gWindows[2].rows = 2;
    gWindows[2].width = 9;
    gWindows[2].height = 4;
    gWindows[2].style = 3;
    gWindows[2].variant = 0;
    gWindows[2].bg = 2;
    gWindows[2].slot = 2;
    gWindows[2].textX = 0;
    gSubMode = 0;
    for (i = 0; i < gWindows[2].rows; i++) {
        gWindows[2].items[i].enabled = 1;
        if (i == 0)
            gWindows[2].items[i].text = Msg_GetSystem(gScreen == 1 ? 11 : 12);
        else
            gWindows[2].items[i].text = Msg_GetSystem(4);
    }
    Text_SetFill(1, 0);
    Text_Clear();
    Text_LoadPalette(5, 0, 0);
    Text_LoadPalette(6, 2, 0);
    Font_LoadPalette(0x050000E0, 0);
    Obj_AllocPalette(3, 0);
    Obj_AllocPalette(6, 0);
    Obj_LoadToBg(3, 1, 2, 0);
    Obj_LoadToBg(6, 2, 2, 0);
    Text_CopyFill(0x06008400);
    sShopResult = 0;
    sShopRow = 0;
    gSubState = 0;
    sShopTop = 0;
    sShopWaiting = 0;
    gScreenInitDone = 1;
}

s32 ShopBuyScreen_Init(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0)
        ShopList_Setup();
    win = &gWindows[1];
    Text_SetFill(1, 0);
    Text_Clear();
    Window_PrintNextItem(win);
    Window_Open(win);
    InfoWin_Open();
    if ((win->anim >> 3) >= win->height - 2)
        ret = 1;
    win->anim += 8;
    return ret;
}

s32 ShopBuyScreen_Main(void)
{
    struct Window *win;
    struct BuyList *list;
    s32 ret;

    if (!(gDataFlags & DATA_BUY_LIST)) {
        if (gKeysNew & B_BUTTON) {
            sShopResult = -1;
            m4aSongNumStart(3);
            return 1;
        }
        return 0;
    }
    win = &gWindows[1];
    list = (struct BuyList *)LIST_BUF;
    if (sShopRow < list->count && sShopRow < win->rows) {
        ShopList_PrintBuyItem(sShopRow, sShopRow);
        ShopList_DrawRow(sShopRow, sShopRow, Shop_CanBuy(sShopRow));
        sShopRow++;
        if (sShopRow < list->count && sShopRow < win->rows)
            return 0;
    }
    Text_SetFill(1, 0);
    ret = 0;
    if (gSubMode <= 1 || (gSubMode == 2 && gSubState == 1)) {
        if (sShopWaiting == 0) {
            if (gMenuHasInput)
                ret = ShopList_HandleInput();
        } else if (gDataFlags & DATA_REPLY) {
            if (gReplyResult) {
                m4aSongNumStart(0);
                sShopWaiting = 0;
            } else {
                gSubState++;
                ShopList_RedrawRows();
            }
            Reply_Clear();
        } else if (Reply_IsTimedOut()) {
            m4aSongNumStart(0);
            sShopWaiting = 0;
            Reply_Clear();
            gInputLockFrames = 6;
        }
    } else if (gSubMode == 2 && gSubState == 0) {
        ret = ShopList_OpenConfirm();
        if (ret) {
            gSubState++;
            gWindows[2].anim = 0;
        }
        ret = 0;
    } else if (gSubMode == 2 && gSubState == 2) {
        ret = ShopList_CloseConfirm();
        if (ret) {
            gSubState = 0;
            gWindows[2].anim = 0;
            gSubMode = 0;
            InfoWin_SetMode(0);
        }
        ret = 0;
    }
    InfoWin_Update();
    if (gMenuHasInput)
        ShopList_DrawCursor();
    ShopList_DrawIcons();
    return ret;
}

s32 ShopBuyScreen_Exit(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 0);
    Text_Clear();
    win = &gWindows[1];
    Window_Close(win);
    InfoWin_Close();
    if ((win->anim >> 3) >= win->height - 2) {
        ret = sShopResult;
        Obj_FreePalette(3);
        Obj_FreePalette(6);
    }
    win->anim += 8;
    return ret;
}

void ShopList_DrawCursor(void)
{
    struct Window *win = &gWindows[1];
    s32 x;
    s32 y;
    s32 n;
    s32 flags;

    if (!gSubMode || (gFrameCount & 2)) {
        x = (win->x - 1) * 8;
        y = (win->y + 1) * 8 + win->cursor * 16;
        Obj_Draw(x, y, 0, 45, Obj_GetPalette(0, 45), 2, 0);
    }
    n = gScreen == 1 ? 2 : 1;
    if (gSubMode == n && gSubState == 1) {
        win = &gWindows[2];
        x = (win->x - 1) * 8;
        y = win->y * 8 + win->cursor * 16;
        Obj_Draw(x, y, 0, 45, Obj_GetPalette(0, 45), 2, 0);
        win = &gWindows[1];
    }
    if (gScreen == 1)
        n = ((struct BuyList *)LIST_BUF)->count;
    else
        n = 64;
    flags = sShopTop != 0;
    if (sShopTop + win->rows < n)
        flags |= 2;
    Window_DrawScrollArrows(1, 2, flags);
}

s32 ShopList_HandleInput(void)
{
    struct Window *win;
    s32 ret;
    s32 max;
    s32 idx;
    s32 pal;

    if (gKeysRepeat == 0)
        return 0;
    ret = 0;
    idx = gScreen == 1 ? 2 : 1;
    win = gSubMode != idx ? &gWindows[1] : &gWindows[2];
    if (gSubMode == 0) {
        max = 64;
        if (gScreen == 1)
            max = ((struct BuyList *)LIST_BUF)->count;
    } else {
        max = win->rows;
    }

    if (gKeysRepeat & DPAD_UP) {
        if (gSubMode == 0) {
            if (win->cursor != 0) {
                win->cursor--;
                InfoWin_SetItem(sShopTop + win->cursor);
                m4aSongNumStart(1);
            } else if (sShopTop != 0) {
                ShopList_ScrollRows(1);
                idx = sShopTop - 1;
                if (gScreen == 1) {
                    ShopList_PrintBuyItem(idx, idx % win->rows);
                    ShopList_DrawRow(idx % win->rows, 0, Shop_CanBuy(idx));
                } else {
                    ShopList_PrintSellItem(idx, idx % win->rows);
                    pal = Shop_CanSell(idx) == 0 ? 6 : 5;
                    Window_DrawRow(1, win->bg, idx % win->rows, 0, pal);
                }
                sShopTop--;
                InfoWin_SetItem(sShopTop + win->cursor);
                m4aSongNumStart(1);
            } else {
                m4aSongNumStart(0);
            }
        } else if (gScreen == 1 && gSubMode == 1) {
            if (Shop_ChangeQuantity(1))
                m4aSongNumStart(1);
            else
                m4aSongNumStart(0);
        } else {
            win->cursor ^= 1;
            m4aSongNumStart(1);
        }
    } else if (gKeysRepeat & DPAD_DOWN) {
        if (gSubMode == 0) {
            if (win->cursor < win->rows - 1 && win->cursor < max - 1) {
                win->cursor++;
                InfoWin_SetItem(sShopTop + win->cursor);
                m4aSongNumStart(1);
            } else if (sShopTop + win->rows < max) {
                ShopList_ScrollRows(0);
                idx = sShopTop + win->rows;
                if (gScreen == 1) {
                    ShopList_PrintBuyItem(idx, idx % win->rows);
                    ShopList_DrawRow(idx % win->rows, win->rows - 1, Shop_CanBuy(idx));
                } else {
                    ShopList_PrintSellItem(idx, idx % win->rows);
                    pal = Shop_CanSell(idx) == 0 ? 6 : 5;
                    Window_DrawRow(1, win->bg, idx % win->rows, win->rows - 1, pal);
                }
                sShopTop++;
                InfoWin_SetItem(sShopTop + win->cursor);
                m4aSongNumStart(1);
            } else {
                m4aSongNumStart(0);
            }
        } else if (gScreen == 1 && gSubMode == 1) {
            if (Shop_ChangeQuantity(-1))
                m4aSongNumStart(1);
            else
                m4aSongNumStart(0);
        } else {
            win->cursor ^= 1;
            m4aSongNumStart(1);
        }
    }

    if (!(gKeysRepeat & (DPAD_UP | DPAD_DOWN))) {
        if (gKeysNew & A_BUTTON) {
            if (gSubMode == 0) {
                if (gScreen == 1)
                    idx = Shop_CanBuy(win->cursor + sShopTop);
                else
                    idx = Shop_CanSell(win->cursor + sShopTop);
                if (idx) {
                    gSubMode++;
                    if (gScreen == 1) {
                        InfoWin_SetMode(1);
                        InfoWin_ShowQuantityArrow(1);
                    }
                    m4aSongNumStart(2);
                } else {
                    m4aSongNumStart(0);
                }
            } else if (gSubMode == 1) {
                if (gScreen == 1) {
                    gSubMode = 2;
                    gSubState = 0;
                    InfoWin_ShowQuantityArrow(0);
                    gWindows[2].cursor = 0;
                } else if (win->cursor < win->rows - 1) {
                    idx = gWindows[1].cursor + sShopTop;
                    Link_SendEvent(8, idx, 0);
                    sShopWaiting = 1;
                    Reply_Clear();
                    gReplyWaiting = 1;
                    m4aSongNumStart(2);
                } else {
                    gSubState++;
                }
                m4aSongNumStart(2);
            } else {
                if (win->cursor < win->rows - 1) {
                    idx = gWindows[1].cursor + sShopTop;
                    Link_SendEvent(9, idx, sShopQuantity);
                    sShopWaiting = 1;
                    Reply_Clear();
                    gReplyWaiting = 1;
                    m4aSongNumStart(2);
                } else {
                    gSubState++;
                }
                m4aSongNumStart(2);
            }
        }
        if (gKeysNew & B_BUTTON) {
            if (gSubMode == 0) {
                sShopResult = -1;
                ret = 1;
            } else if (gScreen == 1 && gSubMode == 1) {
                gSubMode = 0;
                InfoWin_SetMode(0);
                InfoWin_ShowQuantityArrow(0);
            } else {
                gSubState++;
            }
            m4aSongNumStart(3);
        }
    }
    return ret;
}

s32 ShopSellScreen_Init(void)
{
    return ShopBuyScreen_Init();
}

s32 ShopSellScreen_Main(void)
{
    struct Window *win;
    s32 id;
    s32 ret;

    if (!(gDataFlags & DATA_SELL_LIST)) {
        if (gKeysNew & B_BUTTON) {
            sShopResult = -1;
            m4aSongNumStart(3);
            return 1;
        }
        return 0;
    }
    win = &gWindows[1];
    if (sShopRow < win->rows) {
        id = gSession.items[sShopRow];
        Text_SetFill(1, 0);
        Text_Clear();
        if (id > 0) {
            Text_SetX(16);
            Text_Print(Msg_GetItemName(id), TEXT_DRAW);
        }
        Window_PutText(win, sShopRow, 0);
        Window_DrawRow(1, win->bg, sShopRow, sShopRow, Shop_CanSell(sShopRow) == 0 ? 6 : 5);
        sShopRow++;
        if (sShopRow < win->rows)
            return 0;
    }
    Text_SetFill(1, 0);
    ret = 0;
    if (gSubMode == 0 || (gSubMode == 1 && gSubState == 1)) {
        if (sShopWaiting == 0) {
            if (gMenuHasInput)
                ret = ShopList_HandleInput();
        } else if (gDataFlags & DATA_REPLY) {
            if (gReplyResult) {
                m4aSongNumStart(0);
                sShopWaiting = 0;
            } else {
                gSubState++;
            }
            Reply_Clear();
        } else if (Reply_IsTimedOut()) {
            m4aSongNumStart(0);
            sShopWaiting = 0;
            Reply_Clear();
            gInputLockFrames = 6;
        }
    } else if (gSubMode == 1 && gSubState == 0) {
        ret = ShopList_OpenConfirm();
        if (ret) {
            gSubState++;
            gWindows[2].anim = 0;
        }
        ret = 0;
    } else if (gSubMode == 1 && gSubState == 2) {
        ret = ShopList_CloseConfirm();
        if (ret) {
            gSubState = 0;
            gWindows[2].anim = 0;
            gSubMode = 0;
        }
        ret = 0;
    }
    InfoWin_Update();
    if (gMenuHasInput)
        ShopList_DrawCursor();
    ShopList_DrawIcons();
    return ret;
}

s32 ShopSellScreen_Exit(void)
{
    return ShopBuyScreen_Exit();
}

void ShopList_DrawIcons(void)
{
    struct BuyList *list;
    s16 *ids;
    struct Window *win;
    s32 x;
    s32 y;
    s32 i;
    s32 idx;
    s32 id;
    s32 t;
    s32 pal;

    if (gScreen == 1) {
        list = (struct BuyList *)LIST_BUF;
        ids = list->ids;
    } else {
        list = 0;
        ids = 0;
    }
    win = &gWindows[1];
    x = (win->x + 1) * 8;
    y = (win->y + 1) * 8;
    for (i = 0; i < win->rows; i++, y += 16) {
        idx = i + sShopTop;
        if (gScreen == 1) {
            if (idx >= list->count)
                break;
            id = ids[idx];
            if (id == 0)
                continue;
        } else {
            id = gSession.items[idx];
            if (id <= 0)
                continue;
        }
        t = Item_GetIcon(id);
        pal = Obj_GetPalette(0, t);
        Obj_Draw(x - 1, y, 0, t, pal, win->bg, 0);
    }
    if (gScreen != 1) {
        x = (win->x + 1) * 8;
        y = (win->y + 1) * 8;
        t = (gLanguage & 15) == 1 ? 24 : 4;
        pal = Obj_GetPalette(2, t);
        for (i = 0; i < win->rows; i++, y += 16) {
            if (Session_IsItemInUse(i + sShopTop))
                Obj_Draw(x - 5, y + 4, 2, t, pal, win->bg, 0);
        }
    }
}

void ShopList_PrintBuyItem(s32 idx, s32 slot)
{
    s16 *id;
    struct Window *win;

    Text_SetFill(1, 0);
    Text_Clear();
    Text_SetX(16);
    id = &BUY_ITEM_IDS[idx];
    if (*id > 0)
        Text_Print(Msg_GetItemName(*id), TEXT_DRAW);
    win = &gWindows[1];
    Text_CopyToVram(0x0600AB80 + 2 * 32 * win->width * slot, win->width);
}

void ShopList_DrawRow(s32 idx, s32 row, s32 flag)
{
    u16 buf[30];
    s32 attr;
    s32 y;
    s32 w;
    s32 i;
    s32 j;
    s32 t;
    u16 *map;
    struct Window *win = &gWindows[1];

    attr = 6;
    if (flag)
        attr = 5;
    attr <<= 12;
    y = win->y + 1 + row * 2;
    w = win->width - 2;
    for (j = 0; j < 2; j++) {
        t = 0x15C;
        t += (win->width << 1) * idx;
        t += j;
        for (i = 0; i < w; i++) {
            if (!(i & 1)) {
                buf[i] = attr | t;
            } else {
                buf[i] = (t + 2) | attr;
                t += 4;
            }
        }
        map = Bg_GetMapPtr(win->bg, win->x + 1, y + j);
        DmaCopy16(3, buf, map, w << 1);
    }
}

void ShopList_RedrawRows(void)
{
    struct Window *win = &gWindows[1];
    s32 i;
    s32 idx;

    for (i = 0; i < win->rows; i++) {
        idx = sShopTop + i;
        ShopList_DrawRow(idx % win->rows, i, Shop_CanBuy(idx));
    }
}

s32 Shop_CanBuy(s32 idx)
{
    u8 *p = LIST_BUF;
    u8 count;
    u32 *vals;
    s32 n;
    s32 i;

    count = *p;
    p += 4;
    p += count * 2;
    if (count & 1)
        p += 2;
    vals = (u32 *)p;
    n = 0;
    for (i = 0; i < 64; i++) {
        if (gSession.items[i] == -1)
            n++;
    }
    return gSession.gil >= vals[idx] && n != 0;
}

s32 Shop_CanSell(s32 idx)
{
    s32 ret;

    if (gSession.items[idx] <= 158)
        ret = 0;
    else
        ret = Session_IsItemInUse(idx) == 0;
    return ret;
}

void ShopList_ScrollRows(s32 dir)
{
    struct Window *win = &gWindows[1];
    s32 from;
    s32 to;
    s32 step;
    s32 i;
    s32 j;
    u32 src;
    u32 dst;

    step = 64;
    if (dir) {
        to = win->rows * 2;
        from = to - 2;
        step = -step;
    } else {
        from = 3;
        to = 1;
    }
    src = (u32)Bg_GetMapPtr(win->bg, win->x + 1, from);
    dst = (u32)Bg_GetMapPtr(win->bg, win->x + 1, to);
    for (i = 0; i < win->rows - 1; i++) {
        for (j = 0; j < 2; j++) {
            DmaCopy16(0, src, dst, (win->width - 2) << 1);
            src += step;
            dst += step;
        }
    }
}

s32 ShopList_OpenConfirm(void)
{
    struct Window *win = &gWindows[2];
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
        sShopWaiting = 0;
        ret = 1;
    }
    win->anim += 8;
    return ret;
}

s32 ShopList_CloseConfirm(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[2];

    Text_SetFill(0, 0);
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 1) {
        sShopWaiting = 0;
        ret = 1;
    }
    win->anim += 8;
    return ret;
}

void InfoWin_Setup(void)
{
    s32 i;

    gSubState = 0;
    DmaClear32(0, 0, gWindows, sizeof(struct Window));
    gWindows->active = 1;
    gWindows->cursor = 0;
    gWindows->x = 0;
    gWindows->y = 0;
    gWindows->rows = 6;
    gWindows->width = 15;
    gWindows->height = 14;
    gWindows->style = 2;
    gWindows->variant = 0;
    gWindows->bg = 2;
    gWindows->slot = 0;
    gWindows->textX = 0;
    gSubMode = 0;
    for (i = 0; i < gWindows->rows; i++) {
        gWindows->items[i].enabled = 1;
        gWindows->items[i].text = Msg_GetSystem(0);
    }
    Text_LoadPalette(3, 1, 2);
    Text_CopyFill(0x06008000);
    Obj_AllocPalette(5, 0);
    Obj_LoadToBg(5, 0, 2, 0);
    sInfoItem = 0;
    sInfoRow = 0;
    sInfoMode = 0;
    sShopPrevQuantity = sShopQuantity = 1;
    sInfoArrow = 0;
    sInfoShowIcon = 0;
    gInfoWinReady = 1;
}

s32 InfoWin_Open(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 2);
    Text_Clear();
    if (gInfoWinReady == 0)
        InfoWin_Setup();
    win = gWindows;
    Text_Clear();
    Window_PrintNextItem(win);
    Window_Open(win);
    if ((win->anim >> 3) >= win->height - 2)
        ret = 1;
    else
        win->anim += 8;
    return ret;
}

s32 InfoWin_Update(void)
{
    InfoWin_PrintNextRow();
    if (sInfoShowIcon)
        InfoWin_DrawIcons();
    if (sShopPrevQuantity != sShopQuantity)
        InfoWin_PrintTotal();
    sShopPrevQuantity = sShopQuantity;
    return 0;
}

s32 InfoWin_Close(void)
{
    s32 ret = 0;
    struct Window *win;

    Text_SetFill(1, 2);
    Text_Clear();
    win = gWindows;
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 2) {
        ret = 1;
        Obj_FreePalette(5);
    } else {
        win->anim += 8;
    }
    return ret;
}

void InfoWin_SetItem(s32 idx)
{
    sInfoItem = idx;
    InfoWin_ClearRows(0);
}

void InfoWin_SetMode(s32 mode)
{
    s32 old = sInfoMode;

    sInfoMode = mode;
    if (old != mode)
        InfoWin_ClearRows(1);
    sShopQuantity = 1;
}

void InfoWin_ClearRows(s32 mode)
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
    if (mode) {
        map += 128;
        i = 5;
        sInfoRow = 2;
    } else {
        i = 1;
        sInfoRow = mode;
        sInfoShowIcon = mode;
    }
    for (; i < win->height - 1; i++) {
        if (i & 1) {
            DmaSet(3, buf[0], map, 0x80000000 | (size / 2));
        } else {
            DmaSet(3, buf[1], map, 0x80000000 | (size / 2));
        }
        map += 32;
    }
    sInfoArrow = 0;
}

void InfoWin_PrintNextRow(void)
{
    char str[32];
    struct Window *win = gWindows;
    u16 buf[30];
    struct BuyList *list;
    struct ItemInfo *items;
    u32 *vals;
    u32 dst;
    s32 n;
    s32 w;
    s32 x;
    s32 kind;
    s32 digits;
    s32 attr;
    s32 i;
    s32 k;

    if (sInfoRow > win->rows)
        return;
    items = 0;
    list = (struct BuyList *)LIST_BUF;
    if (gScreen == 1) {
        i = list->count;
        if (i & 1)
            i++;
        vals = (u32 *)&BUY_ITEM_IDS[i];
        n = BUY_ITEM_IDS[sInfoItem];
    } else {
        items = (struct ItemInfo *)list;
        vals = (u32 *)(items + 64);
        n = gSession.items[sInfoItem];
    }
    Text_SetFill(1, 2);
    Text_Clear();
    dst = 0x06009000;
    if (sInfoRow < win->rows)
        dst = sInfoRow * 64 * win->width + 0x06009000;
    if (sInfoRow == 0) {
        if (n > 0) {
            Text_SetX(16);
            Text_Print(Msg_GetItemName(n), TEXT_DRAW);
        }
        Text_CopyToVram(dst, win->width);
    } else if (sInfoRow == 1) {
        if ((gScreen == 1 && n > 0) || (gScreen == 2 && n > 158)) {
            n = Text_Print(Msg_GetSystem(13), TEXT_WIDTH) + 72;
            i = (win->width - 2) * 8 - n;
            Text_SetX(i);
            n = sInfoItem;
            Text_PrintNumber(vals[n], i, 8);
            Text_Print(Msg_GetSystem(13), TEXT_DRAW);
        } else if (n > 0 && gScreen == 2 && n <= 158) {
            n = Text_Print(Msg_GetSystem(38), TEXT_WIDTH);
            i = (win->width - 2) * 8 - n;
            Text_SetX(i);
            Text_Print(Msg_GetSystem(38), TEXT_DRAW);
        }
        Text_CopyToVram(dst, win->width);
    } else if (sInfoRow <= 5) {
        if (sInfoMode == 0) {
            if (n > 0) {
                kind = 0;
                if (gScreen != 1)
                    kind = Session_GetItemCategory(sInfoItem);
                if (gScreen == 1 || kind != 1) {
                    InfoWin_GetDescLine(sInfoRow - 2, str);
                    Text_SetX(0);
                    Text_Print(str, TEXT_DRAW);
                } else {
                    items += sInfoItem;
                    if (sInfoRow == 2) {
                        if (items->flags & 0x3000) {
                            Text_SetX(0);
                            Text_Print(Msg_GetStat(items->kind - 1), TEXT_DRAW);
                            if (items->count != 0 && items->kind != 16) {
                                n = Item_IsPercentKind(items->kind);
                                x = n ? 40 : 39;
                                w = Text_Print(Msg_GetSystem(x), TEXT_WIDTH);
                                i = (win->width - 2) * 8 - w;
                                digits = 1;
                                if (items->count > 9) {
                                    digits = 3;
                                    if (items->count <= 99)
                                        digits = 2;
                                }
                                i -= digits * 9;
                                Text_SetX(i);
                                Text_Print(Msg_GetSystem(x), TEXT_DRAW);
                                i = Text_GetX();
                                Text_PrintNumber(items->count, i, digits);
                            }
                        } else {
                            char *s;

                            if (items->flags & 0x100)
                                s = Msg_GetSystem(16);
                            else
                                s = Msg_GetSystem(63);
                            Text_SetX(0);
                            Text_Print(s, TEXT_DRAW);
                            i = win->width * 8 - 34;
                            Text_PrintNumber(items->count, i, 2);
                        }
                    } else if (sInfoRow == 3) {
                        if ((items->flags & 0xE00) && items->kind != 0) {
                            Text_SetX(0);
                            Text_Print(Msg_GetStat(items->kind - 1), TEXT_DRAW);
                        }
                    }
                }
            }
        } else if (n > 0) {
            if (sInfoRow == 2) {
                w = Text_Print(Msg_GetSystem(14), TEXT_WIDTH);
                i = (win->width - 2) * 8 - w;
                Text_SetX(i >> 1);
                Text_Print(Msg_GetSystem(14), TEXT_DRAW);
            } else if (sInfoRow == 3) {
                strcpy(str, Msg_GetSystem(13));
                strcat(str, sSlashText);
                i = Text_Print(str, TEXT_WIDTH) + 72;
                i = (win->width - 2) * 8 - i;
                Text_SetX(i);
                Text_PrintNumber(gSession.gil, i, 8);
                Text_Print(str, TEXT_DRAW);
            } else if (sInfoRow == 4) {
                strcpy(str, Msg_GetSystem(13));
                strcat(str, sSlashText);
                w = Text_Print(str, TEXT_WIDTH) + 72;
                i = (win->width - 2) * 8 - w;
                Text_SetX(i);
                n = sInfoItem;
                Text_PrintNumber(vals[n], i, 8);
                Text_Print(Msg_GetSystem(13), TEXT_DRAW);
            } else if (sInfoRow == 5) {
                w = Text_Print(Msg_GetSystem(15), TEXT_WIDTH) + 18;
                i = (win->width - 3) * 8 - w;
                Text_SetX(i);
                Text_Print(Msg_GetSystem(15), TEXT_DRAW);
                i = Text_GetX();
                Text_PrintNumber(sShopQuantity, i, 2);
            }
        }
        Text_CopyToVram(dst, win->width);
    } else {
        dst = (u32)Bg_GetMapPtr(gWindows[0].bg, gWindows[0].x + 1, gWindows[0].y + 1);
        attr = 3 << 12;
        w = gWindows[0].width - 2;
        for (i = 0; i < sInfoRow; i++) {
            for (x = 0; x < 2; x++) {
                n = (gWindows[0].width << 1) * i + 0x80;
                n += x;
                for (k = 0; k < w; k++) {
                    if (!(k & 1)) {
                        buf[k] = attr | n;
                    } else {
                        buf[k] = (n + 2) | attr;
                        n += 4;
                    }
                }
                DmaCopy16(3, buf, dst, w << 1);
                dst += 64;
            }
        }
        sInfoShowIcon = 1;
    }
    if (sInfoRow <= win->rows)
        sInfoRow++;
}

void InfoWin_GetDescLine(s32 line, char *dst)
{
    char *p = (char *)LIST_BUF;
    char *s;
    s32 len;
    s32 idx;
    s32 i;

    if (gScreen == 1) {
        u32 n = *(u8 *)p;

        p += 4;
        p += n * 2;
        if (n & 1)
            p += 2;
        s = p + n * 4;
        idx = sInfoItem;
    } else {
        s = SELL_ITEM_DESCS;
        if ((u32)Session_GetItemCategory(sInfoItem) <= 1)
            return;
        idx = sInfoItem;
    }
    for (i = 0; i < idx; i++) {
        len = strlen(s);
        s += len + 1;
    }
    p = s;
    for (i = 0; i <= line; i++) {
        s = strchr(p, '\n');
        if (i == line) {
            if (s == NULL) {
                strcpy(dst, p);
            } else {
                len = s - p;
                memcpy(dst, p, len);
                dst[len] = 0;
            }
            break;
        }
        if (s == NULL) {
            *dst = 0;
            break;
        }
        p = s + 1;
    }
}

s32 Shop_ChangeQuantity(s32 delta)
{
    s32 count;
    s32 i;
    s32 old;

    count = 0;
    for (i = 0; i < 64; i++) {
        if (gSession.items[i] == -1)
            count++;
    }
    old = sShopQuantity;
    sShopQuantity += delta;
    if (sShopQuantity <= 0 || sShopQuantity > count)
        sShopQuantity = old;
    if (sShopQuantity != old) {
        u8 *buf = LIST_BUF;
        s32 n = buf[0];
        s16 *items = (s16 *)(buf + 4);
        u32 *prices;

        if (n & 1)
            n++;
        prices = (u32 *)&items[n];
        n = prices[sInfoItem];
        if (n * sShopQuantity > gSession.gil)
            sShopQuantity = old;
    }
    return sShopQuantity != old;
}

void InfoWin_ShowQuantityArrow(val)
s8 val;
{
    sInfoArrow = val;
}

void InfoWin_DrawIcons(void)
{
    s32 id;
    s32 x, y;
    s32 frame;

    if (gScreen == 1) {
        u8 *buf = LIST_BUF;
        s16 *items = (s16 *)(buf + 4);

        if (sInfoItem >= buf[0])
            return;
        id = items[sInfoItem];
    } else {
        id = gSession.items[sInfoItem];
    }
    if (id <= 0)
        return;
    x = (gWindows[0].x + 1) << 3;
    y = (gWindows[0].y + 1) << 3;
    frame = Item_GetIcon(id);
    Obj_Draw(x, y, 0, frame, Obj_GetPalette(0, frame), gWindows[0].bg, 0);
    if (InfoWin_IsDrawn() && sInfoArrow) {
        x = (gWindows[0].x + 12) << 3;
        y = (gWindows[0].y + gWindows[0].height - 1) << 3;
        Obj_Draw(x, y, 2, 5, Obj_GetPalette(2, 5), gWindows[0].bg, 0);
    }
}

s32 InfoWin_IsDrawn(void)
{
    s32 ret = 0;

    if (sInfoRow > gWindows[0].rows)
        ret = 1;
    return ret;
}

void InfoWin_PrintTotal(void)
{
    char buf[32];
    struct Window *win = gWindows;
    s32 ofs = win->width * 64;
    u32 dst = win->width * 256 + 0x06009000;
    u8 *p = LIST_BUF;
    s32 x;
    s32 w;
    s32 n;

    n = *p;
    p += 4;
    p += n * 2;
    if (n & 1)
        p += 2;
    Text_SetFill(1, 2);
    Text_Clear();
    strcpy(buf, Msg_GetSystem(13));
    strcat(buf, sSlashText);
    w = Text_Print(buf, TEXT_WIDTH) + 72;
    x = (win->width - 2) * 8 - w;
    Text_SetX(x);
    Text_PrintNumber(((u32 *)p)[sInfoItem] * sShopQuantity, x, 8);
    Text_Print(Msg_GetSystem(13), TEXT_DRAW);
    Text_CopyToVram(dst, win->width);
    Text_Clear();
    dst += ofs;
    w = Text_Print(Msg_GetSystem(15), TEXT_WIDTH) + 18;
    x = (win->width - 3) * 8 - w;
    Text_SetX(x);
    Text_Print(Msg_GetSystem(15), TEXT_DRAW);
    n = Text_GetX();
    Text_PrintNumber(sShopQuantity, n, 2);
    Text_CopyToVram(dst, win->width);
}

void ShopList_PrintSellItem(s32 idx, s32 row)
{
    struct Window *win = &gWindows[1];
    s32 id;
    char *str;

    Text_SetFill(1, 0);
    Text_Clear();
    id = gSession.items[idx];
    if (id > 0) {
        Text_SetX(16);
        str = Msg_GetItemName(id);
    } else {
        str = Msg_GetSystem(0);
    }
    Text_Print(str, TEXT_DRAW);
    Window_PutText(win, row, 0);
}

void ShopList_RefreshSellItem(s32 idx)
{
    struct Window *win = &gWindows[1];
    s32 id;
    char *str;

    Text_SetFill(1, 0);
    Text_Clear();
    id = gSession.items[idx];
    if (id > 0) {
        Text_SetX(16);
        str = Msg_GetItemName(id);
    } else {
        str = Msg_GetSystem(0);
    }
    Text_Print(str, TEXT_DRAW);
    ShopList_PrintSellItem(idx, idx % win->rows);
    InfoWin_SetItem(idx);
}
