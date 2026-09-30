#include "gba_types.h"

#define DMA0 0x040000B0
#define DMA3 0x040000D4

#define DmaSet(dmaAddr, src, dst, cnt) \
    { \
        vu32 *dmaRegs = (vu32 *)(dmaAddr); \
        dmaRegs[0] = (u32)(src); \
        dmaRegs[1] = (u32)(dst); \
        dmaRegs[2] = (u32)(cnt); \
        dmaRegs[2]; \
    }

#define DmaCopy16(dmaAddr, src, dst, size) DmaSet(dmaAddr, src, dst, 0x80000000 | ((size) / 2))

#define DmaClear32(dmaAddr, value, dst, size) \
    { \
        vu32 tmp = (vu32)(value); \
        DmaSet(dmaAddr, &tmp, dst, 0x85000000 | ((size) / 4)); \
    }

struct Cmd {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 unk3;
};

struct WinItem {
    s16 unk0;
    s16 unk2;
    char *unk4;
};

struct Window {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    s8 unk3;
    s8 unk4;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    u8 unk8;
    u8 unk9[5];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    struct WinItem items[11];
};

struct Work {
    u8 unk0;
    s8 unk1[0x61];
    u16 unk62;
};

struct Unk03002FB0 {
    u8 unk0[20];
    u8 unk14[4];
    u8 unk18[4];
};

extern s8 lbl_03002774;
extern s8 lbl_03002775;
extern s8 lbl_03002776;
extern s8 lbl_03002777;
extern s8 lbl_03002778;
extern s8 lbl_03002779;
extern u16 lbl_0300277A;
extern u16 lbl_0300299C;
extern u16 lbl_030029AC;
extern u32 lbl_03002AC8;
extern u8 gMenuHasInput;
extern u16 gDataFlags;
extern struct Work gSession;
extern char gBonusStr[2][65];
extern struct Unk03002FB0 lbl_03002FB0;
extern s32 gScreen;
extern s32 gMode;
extern s8 gScreenStep;
extern s32 lbl_030030A4;
extern s32 gScreenInitDone;
extern struct Window gWindows[];
extern s8 gOpenMenuReq;
extern s32 gSavedScreen;
extern s8 gMsgScreenId;
extern u8 gListBuf[];

void *memset(void *, int, unsigned long);
s32 strlen(const char *);
void m4aSongNumStart(u16);
void fn_02000990(void);
u32 fn_02000A40(s32, s32, s32);
void fn_02000A74(void);
void fn_02000A80(const char *);
void fn_02000CF0(s32, s32, s32);
s32 Link_SendRequest(u8, u8);
void fn_02003394(s32, s32);
void fn_020033F4(void);
s32 fn_02003464(const char *, s32);
void fn_020037A8(u32, s32);
void fn_020037C8(s32, s32, s32);
void fn_02003890(u32, s32);
void fn_020038D8(u32);
void fn_020038F4(s32);
void fn_02003C3C(s32, s32, s32, s32, s32, s32, s32);
s32 fn_02004030(s32, s32);
void fn_02004098(s32, s32, s32, s32);
void fn_020041D4(s32, s32);
void fn_02004320(s32);
void Session_OnArtifacts(u8 *);
void Screen_Reset(void);
void fn_02005968(struct Window *);
void fn_020059D4(struct Window *, s32, s32);
s32 fn_02005A0C(s32);
s32 fn_02005A2C(s32);
void fn_02005A50(struct Window *);
void fn_02008178(struct Window *);
void fn_0200A700(s32, s32);
s32 fn_0200A758(s32);
void fn_0200A790(void);
char *fn_0201A73C(s32);
char *fn_0201A8A4(s32);
s32 fn_0201AB14(s32);
void fn_0201AB88(s32, char *);

void fn_02009B80(struct Window *win, s32 val);
void fn_020098F0(s32 bg, s32 x, s32 y, s32 w, s32 h);
void fn_0200A328(void);
void fn_0200A370(void);
void fn_0200A57C(void);

void fn_020091D4(void)
{
    struct Window *win = &gWindows[4];
    s32 max;
    s32 n;
    s32 i;
    s32 len;
    s32 w;

    win->unk0 = 1;
    win->unk3 = -1;
    win->unk4 = 0;
    win->unk5 = 0;
    win->unk6 = 4;
    win->unk7 = 0;
    fn_020033F4();
    max = 0;
    len = 0;
    n = 0;
    for (i = 0; i <= 10; i++, n++) {
        if (win->items[i].unk4 == 0)
            break;
        len = strlen(win->items[i].unk4);
        if (len == 0)
            break;
        len = fn_02003464(win->items[i].unk4, 2);
        if (len > max)
            max = len;
    }
    if (max & 7)
        max += 8;
    w = max >> 3;
    win->unkE = n + 1;
    win->unk16 = (n + 1) * 2 + 2;
    win->unk12 = (20 - win->unk16) >> 1;
    max = w << 3;
    win->unk14 = w + 2;
    win->unk10 = (30 - win->unk14) >> 1;
    win->unk7 = (max - len) / 2;
}

s32 fn_02009280(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[4];

    fn_02003394(1, 1);
    fn_020033F4();
    fn_02005968(win);
    fn_02005A50(win);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win->unk1 = 0;
        ret = 1;
    }
    return ret;
}

s32 fn_020092C4(void)
{
    s32 ret;

    if (lbl_030029AC & 3) {
        m4aSongNumStart(2);
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

s32 fn_020092E8(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[4];

    fn_02008178(win);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win->unk1 = 0;
        ret = 1;
    }
    return ret;
}

void fn_02009318(void)
{
    memset(&lbl_03002FB0, 0, 28);
    lbl_03002FB0.unk14[0] = 0x10;
    lbl_03002FB0.unk14[1] = 0x32;
    lbl_03002FB0.unk14[2] = 0x54;
    lbl_03002FB0.unk14[3] = 0x76;
}

static inline u32 GetBgVram(s32 bg)
{
    u32 addr = 0x06000000;

    if (bg != 0) {
        if (bg != 1)
            addr = 0x06008000;
    }
    return addr;
}

u32 fn_02009340(struct Window *win, s32 row, s32 half)
{
    u32 addr = GetBgVram(win->unk5);
    s32 n;

    if (win->unk6 == 0)
        addr += 0x1000;
    else if (win->unk6 == 1)
        addr += 0x2B80;
    else if (win->unk6 == 2)
        addr += 0x4700;
    else if (win->unk6 == 3)
        addr += 0x5380;
    else
        addr = 0x06006800;
    n = 1;
    if (half == 0)
        n = 2;
    addr += n * 32 * win->unk14 * row;
    return addr;
}

void fn_020093B4(s32 idx, s32 bg)
{
    struct Window *win = &gWindows[idx];

    DmaClear32(DMA0, 0, win, sizeof(struct Window));
    win->unk0 = 1;
    win->unk10 = 20;
    win->unk12 = 1;
    win->unkE = 6;
    win->unk14 = 10;
    win->unk16 = 14;
    win->unk3 = win->unk16;
    win->unk4 = 0;
    win->unk5 = bg;
    win->unk6 = idx;
    win->unk8 = 0;
    fn_02009B80(win, 0);
}

s32 fn_02009414(s32 idx)
{
    struct Window *win = &gWindows[idx];
    s32 row;
    u32 addr;

    fn_02003394(1, 0);
    fn_020033F4();
    row = win->unk1 >> 3;
    if (row == 0) {
        fn_020059D4(win, 0, 0);
    } else if (row <= win->unkE) {
        row--;
        if (row <= 2) {
            fn_02003464(fn_0201A73C(row + 6), 0);
            fn_02000CF0(gSession.unk1[row], win->unk14 * 8 - 34, 2);
        } else if (row == 4) {
            addr = fn_02009340(win, 4, 0);
            fn_02003464(fn_0201A73C(1), 0);
            fn_020037A8(addr, win->unk14);
        } else if (row == 5) {
            fn_02000CF0(gSession.unk62, win->unk14 * 8 - 43, 3);
        }
        fn_020059D4(win, row, 0);
        row++;
    }
    fn_02005A50(win);
    if (row == 0)
        win->unk8 = 1;
    else if (row > 6)
        win->unk8 = 0;
    if (row < win->unk16 - 2) {
        win->unk1 += 8;
        return 0;
    }
    return 1;
}

void fn_02009508(s32 idx)
{
    struct Window *win = &gWindows[idx];
    s32 i;

    fn_02003394(1, 0);
    for (i = 0; i <= 2; i++) {
        fn_020033F4();
        fn_02003464(fn_0201A73C(i + 6), 0);
        fn_02000CF0(gSession.unk1[i], win->unk14 * 8 - 34, 2);
        fn_020037A8(fn_02009340(win, i, 0), win->unk14);
    }
    fn_020033F4();
    fn_02000CF0(gSession.unk62, win->unk14 * 8 - 43, 3);
    fn_020059D4(win, 5, 0);
    fn_020037A8(fn_02009340(win, 5, 0), win->unk14);
}

void fn_020095AC(s32 idx)
{
    struct Window *win = &gWindows[idx];
    s32 x = win->unk10 + 3;
    s32 y = win->unk12 + win->unk16 - 3;

    x *= 8;
    y *= 8;
    fn_02003C3C(x, y, 0, 47, fn_02004030(0, 47), win->unk5, 0);
}

void fn_020095FC(s32 idx)
{
    struct Window *win = &gWindows[idx];
    s32 i;

    DmaClear32(DMA0, 0, win, sizeof(struct Window));
    win->unk0 = 1;
    win->unk10 = 0;
    win->unk12 = 0;
    win->unkE = 2;
    win->unk14 = 30;
    win->unk16 = 2;
    win->unk3 = 0;
    win->unk4 = 0;
    win->unk5 = 0;
    win->unk6 = idx;
    fn_02003394(0, 0);
    for (i = 0; i <= 1; i++) {
        fn_020033F4();
        fn_020038F4(8);
        fn_02003464(gBonusStr[i], 0);
        fn_020059D4(win, i, 0);
    }
}

void fn_02009684(s32 idx, s32 pal)
{
    struct Window *win = &gWindows[idx];
    u16 buf[30];
    s32 i;
    s32 j;
    s32 tile;
    u32 dst;

    pal <<= 12;
    for (i = 0; i <= 3; i++) {
        for (j = 0; j < 30; j++)
            buf[j] = 0x3FF;
        tile = fn_02005A0C(win->unk6);
        tile += win->unk14 * 2 * (i >> 1);
        tile += i & 1;
        for (j = 0; j < win->unk14; j++) {
            if (j & 1) {
                buf[j] = (tile + 2) | pal;
                tile += 4;
            } else {
                buf[j] = pal | tile;
            }
        }
        dst = fn_02000A40(win->unk5, 0, 16 + i);
        DmaCopy16(DMA0, buf, dst, win->unk14 << 1);
    }
}

void fn_0200974C(s32 bg)
{
    fn_020098F0(bg, 0, 16, 30, 4);
}

void fn_02009764(s32 idx, s32 mode, s32 row)
{
    struct Window *win = &gWindows[idx];
    u16 buf[30];
    s32 pal;
    s32 y;
    s32 base;
    s32 i;
    s32 j;
    s32 off;
    s32 w;
    u32 dst;

    if (mode <= 1)
        pal = 1;
    else
        pal = (mode >> 1) + 1;
    pal <<= 12;
    y = win->unk12 + row * 2;
    base = fn_02005A2C(win->unk6) + 4;
    for (i = 0; i <= 1; i++) {
        if (mode < 0)
            off = 0;
        else if (mode & 1)
            off = 10;
        else
            off = 0;
        off += i + base;
        for (j = 0; j < win->unk14; j++) {
            if (j == 0) {
                if (mode < 0)
                    buf[j] = off + 16;
                else
                    buf[j] = off;
            } else if (mode <= 0) {
                if (j < win->unk14 - 1) {
                    if (mode != 0)
                        buf[j] = off + 6;
                    else
                        buf[j] = off + 2;
                } else {
                    if (mode != 0)
                        buf[j] = off + 8;
                    else
                        buf[j] = off + 18;
                }
            } else {
                w = win->unk14 - 3;
                if (j < w)
                    buf[j] = off + 2;
                else if (j == w)
                    buf[j] = off + 4;
                else if (j == win->unk14 - 2)
                    buf[j] = i + base + 6;
                else
                    buf[j] = i + base + 8;
            }
            buf[j] |= pal;
        }
        dst = fn_02000A40(win->unk5, win->unk10, y + i);
        DmaCopy16(DMA0, buf, dst, win->unk14 << 1);
    }
}

void fn_020098B8(s32 idx, s32 row)
{
    struct Window *win = &gWindows[idx];
    s32 y = win->unk12 + row * 2;

    fn_020098F0(win->unk5, win->unk10, y, win->unk14, 2);
}

void fn_020098F0(s32 bg, s32 x, s32 y, s32 w, s32 h)
{
    u16 buf[30];
    u16 fill;
    u32 dst;
    s32 i;

    fill = 0x2FF;
    if (bg <= 1)
        fill = 0x3FF;
    for (i = 0; i < 30; i++)
        buf[i] = fill;
    dst = fn_02000A40(bg, x, y);
    for (i = 0; i < h; i++) {
        DmaCopy16(DMA0, buf, dst, w << 1);
        dst += 64;
    }
}

s32 fn_0200994C(struct Window *win, s32 row)
{
    return fn_02005A0C(win->unk6) + (win->unk14 << 1) * row;
}

void fn_0200996C(struct Window *win, s32 bg, s32 row, s32 x, s32 y, s32 pal)
{
    u16 buf[30];
    s32 i;
    s32 j;
    s32 tile;
    u32 dst;

    fn_02009340(win, row, 0);
    pal <<= 12;
    for (i = 0; i <= 1; i++) {
        tile = fn_0200994C(win, row) + i;
        for (j = 0; j < win->unk14; j++) {
            if (j & 1) {
                buf[j] = (tile + 2) | pal;
                tile += 4;
            } else {
                buf[j] = pal | tile;
            }
        }
        dst = fn_02000A40(bg, x, y + i);
        DmaCopy16(DMA0, buf, dst, win->unk14 << 1);
    }
}

void fn_02009A14(s32 dir, s32 idx, s32 bg)
{
    struct Window *win = &gWindows[idx];
    s32 step;
    s32 y0;
    s32 y1;
    u32 src;
    u32 dst;
    s32 i;
    s32 j;

    step = 64;
    if (dir) {
        y1 = win->unkE * 2;
        y0 = y1 - 2;
        step = -step;
    } else {
        y0 = 3;
        y1 = 1;
    }
    y0 += win->unk12;
    y1 += win->unk12;
    src = fn_02000A40(bg, win->unk10 + 1, y0);
    dst = fn_02000A40(bg, win->unk10 + 1, y1);
    for (i = 0; i < win->unkE - 1; i++) {
        for (j = 0; j < 2; j++) {
            DmaCopy16(DMA0, src, dst, (win->unk14 - 2) * 2);
            src += step;
            dst += step;
        }
    }
}

void fn_02009AB8(s32 idx, s32 bg, s32 row, s32 y, s32 pal)
{
    struct Window *win = &gWindows[idx];
    u16 buf[30];
    s32 w;
    s32 i;
    s32 j;
    s32 tile;
    u32 dst;

    pal <<= 12;
    y = win->unk12 + y * 2 + 1;
    w = win->unk14 - 2;
    for (i = 0; i <= 1; i++) {
        tile = fn_02005A0C(win->unk6);
        tile += (win->unk14 << 1) * row;
        tile += i;
        for (j = 0; j < w; j++) {
            if (!(j & 1)) {
                buf[j] = pal | tile;
            } else {
                buf[j] = (tile + 2) | pal;
                tile += 4;
            }
        }
        dst = fn_02000A40(bg, win->unk10 + 1, y + i);
        DmaCopy16(DMA3, buf, dst, w << 1);
    }
}

void fn_02009B80(struct Window *win, s32 val)
{
    s32 i;

    for (i = 0; i < win->unkE; i++) {
        win->items[i].unk0 = val;
        win->items[i].unk4 = fn_0201A73C(0);
    }
}

void fn_02009BB0(s32 idx, s32 bg, s32 flags)
{
    struct Window *win = &gWindows[idx];
    s32 x;
    s32 y;
    s32 cell;
    s32 anim;
    s32 i;
    u32 attr;

    x = (win->unk10 + win->unk14 - 2) * 8;
    cell = fn_02004030(0, 46);
    anim = (lbl_03002AC8 & 8) >> 2;
    for (i = 0; i <= 1; i++) {
        if ((flags >> i) & 1) {
            if (i == 0) {
                attr = 0;
                y = (win->unk12 + 1) * 8;
                y += anim;
            } else {
                attr = 0x20000000;
                y = (win->unk12 + win->unk16 - 3) * 8;
                y -= anim;
            }
            fn_02003C3C(x, y, 0, 46, cell, bg, attr);
        }
    }
}

void fn_02009C54(s32 idx, s32 x, s32 w, s32 bg)
{
    struct Window *win = &gWindows[idx];

    DmaClear32(DMA0, 0, win, sizeof(struct Window));
    win->unk0 = 1;
    win->unk10 = x;
    win->unk12 = 0;
    win->unkE = 8;
    win->unk14 = w ? w : 14;
    win->unk16 = 18;
    win->unk3 = 0;
    win->unk4 = 0;
    win->unk5 = bg;
    win->unk6 = idx;
    win->unk8 = 0;
    fn_02009B80(win, 1);
}

void fn_02009CBC(s32 bg, s32 idx, s32 pal)
{
    u16 buf[30];
    u16 fill;
    u32 dst;
    s32 i;
    s32 j;
    s32 tile;

    fill = 0x2FF;
    if (bg <= 1)
        fill = 0x3FF;
    for (i = 0; i < 30; i++)
        buf[i] = fill;
    pal <<= 12;
    dst = fn_02000A40(bg, 1, 18);
    for (i = 0; i <= 1; i++) {
        tile = fn_02005A0C(idx) + i;
        for (j = 0; j <= 24; j++) {
            if (j & 1) {
                buf[j] = (tile + 2) | pal;
                tile += 4;
            } else {
                buf[j] = pal | tile;
            }
        }
        DmaCopy16(DMA3, buf, dst, 50);
        dst += 64;
    }
}

void fn_02009D68(s32 bg, s32 idx)
{
    u32 off;
    u32 base;

    if (idx == 0)
        off = 0x1000;
    else if (idx == 1)
        off = 0x2B80;
    else if (idx == 2)
        off = 0x4700;
    else
        off = 0x5380;
    base = 0x06000000;
    if (bg != 0) {
        if (bg != 1)
            base = 0x06008000;
    }
    fn_020037A8(off + base, 25);
}

void fn_02009DA8(s32 bg, s32 idx)
{
    u16 buf[30];
    struct Window *win;
    s32 val;
    u32 dst;
    s32 i;

    val = 0x2FF;
    if (bg <= 1)
        val = 0x3FF;
    for (i = 0; i < 30; i++)
        buf[i] = val;
    win = &gWindows[idx];
    val = win->unk5;
    win->unk5 = bg;
    dst = fn_02000A40(bg, 0, 18);
    win->unk5 = val;
    for (i = 0; i < 2; i++) {
        DmaCopy16(DMA0, buf, dst, 60);
        dst += 64;
    }
    fn_02003394(0, 0);
    fn_020033F4();
    fn_02009D68(bg, idx);
}

s32 MsgScreen_Init(void)
{
    if (!(gDataFlags & 1))
        return 0;
    if (gScreenInitDone == 0) {
        DmaClear32(DMA0, 0, gWindows, sizeof(struct Window) * 5);
        fn_02003394(1, 0);
        fn_020037C8(3, 0, 1);
        fn_02004098(12, 4, 0, 0);
        fn_020037C8(15, 0, 1);
        fn_020038D8(0x06006000);
        gWindows[4].items[0].unk4 = fn_0201A8A4(gMsgScreenId);
        fn_020091D4();
        gScreenInitDone = 1;
    }
    return fn_02009280();
}

s32 MsgScreen_Main(void)
{
    return 0;
}

void Menu_OnOpen(u32 data)
{
    s32 prev = gScreen;
    struct Cmd *cmd = (struct Cmd *)&data;

    gScreen = cmd->unk2;
    if (gScreen == 11) {
        if (gMode != 0) {
            gSavedScreen = 0;
            gMode = 0;
        } else {
            gSavedScreen = prev;
        }
        gMsgScreenId = 6;
    } else if (gScreen == 12) {
        gScreen = gSavedScreen;
    } else {
        gSavedScreen = gScreen;
    }
    Screen_Reset();
    fn_02000990();
}

void fn_02009F44(s32 no)
{
    char buf[68];

    fn_02000A74();
    if (no > 0) {
        fn_0201AB88(no, buf);
        fn_02000A80(buf);
    }
}

void fn_02009F68(s32 no, s32 bg, s32 idx)
{
    char buf[68];

    fn_02003394(0, 0);
    fn_020033F4();
    if (no > 0) {
        fn_0201AB88(no, buf);
        fn_02003464(buf, 0);
    }
    fn_02009D68(bg, idx);
}

void fn_02009FA4(void)
{
    lbl_030030A4 = 0;
    DmaClear32(DMA0, 0, gWindows, sizeof(struct Window) * 5);
    fn_020093B4(0, 2);
    fn_02009C54(1, 2, 15, 2);
    fn_02009B80(&gWindows[1], 1);
    fn_02003394(1, 0);
    fn_020037C8(4, 0, 0);
    fn_020037C8(5, 0, 0);
    fn_020037C8(6, 2, 0);
    fn_02003890(0x050000E0, 0);
    fn_02003890(0x05000100, 1);
    fn_020038D8(0x06008000);
    fn_020038D8(0x06008400);
    fn_020041D4(17, 0);
    fn_020041D4(3, 0);
    fn_02004098(17, 0, 2, 0);
    fn_02004098(3, 1, 2, 0);
    lbl_03002774 = 0;
    lbl_03002776 = 0;
    lbl_03002775 = 0;
    lbl_03002777 = 0;
    lbl_0300277A = 1;
    fn_02009DA8(1, 1);
    fn_02009CBC(1, 1, 8);
    gDataFlags &= ~0x100;
    Link_SendRequest(9, 0);
    lbl_03002779 = 0;
    lbl_03002778 = 0;
    gScreenInitDone = 1;
}

s32 ArtifactScreen_Init(void)
{
    struct Window *win;
    s32 ret;

    fn_02003394(1, 0);
    if (gScreenInitDone == 0) {
        fn_02009FA4();
        if (gScreenInitDone == 0)
            return 0;
    }
    fn_02009414(0);
    win = &gWindows[1];
    fn_02005968(win);
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        ret = 1;
        win->unk1 = 0;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

s32 ArtifactScreen_Main(void)
{
    s32 ret;
    struct Window *win;

    fn_020095AC(0);
    if (!(gDataFlags & 0x100)) {
        if (lbl_030029AC & 1) {
            m4aSongNumStart(0);
        } else if (lbl_030029AC & 2) {
            lbl_03002775 = 1;
            gOpenMenuReq = 1;
            m4aSongNumStart(3);
            return 1;
        } else if (lbl_030029AC & 0x300) {
            if (lbl_030029AC & 0x100)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            ret = 1;
            lbl_03002775 = ret;
            m4aSongNumStart(6);
            return ret;
        }
        if (++lbl_03002778 >= 60) {
            Link_SendRequest(9, 0);
            lbl_03002778 = 0;
        }
        return 0;
    }
    if (lbl_03002779 == 0) {
        Session_OnArtifacts(gListBuf);
        lbl_03002779 = 1;
    }
    fn_02003394(1, 0);
    fn_020033F4();
    win = &gWindows[1];
    if (lbl_03002776 < win->unkE) {
        fn_0200A700(lbl_03002776, lbl_03002776);
        fn_02009AB8(1, win->unk5, lbl_03002776, lbl_03002776, fn_0200A758(lbl_03002776) ? 5 : 6);
        lbl_03002776++;
        if (lbl_03002776 < win->unkE)
            return 0;
        fn_0200A790();
    }
    if (gMenuHasInput)
        fn_0200A370();
    fn_0200A57C();
    if (gMenuHasInput)
        fn_0200A328();
    ret = lbl_03002775 != 0;
    if (ret)
        fn_02009DA8(1, 1);
    return ret;
}

s32 ArtifactScreen_Exit(void)
{
    struct Window *win = gWindows;
    s32 ret = 0;

    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) < win->unk16 - 1)
        win->unk1 += 8;
    win++;
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        ret = 1;
        fn_02004320(17);
        fn_02004320(3);
        win->unk1 = 0;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

void fn_0200A328(void)
{
    s32 cell = fn_02004030(0, 45);
    struct Window *win = &gWindows[1];

    fn_02003C3C((win->unk10 - 1) * 8, (win->unk12 + 1) * 8 + win->unk2 * 16, 0, 45, cell, win->unk5, 0);
}

void fn_0200A370(void)
{
    struct Window *win;
    s32 prev;
    s32 n;
    s32 pal;
    s32 max = 73;

    if (lbl_0300299C == 0)
        return;
    win = &gWindows[1];
    prev = lbl_03002774 + win->unk2;
    if (lbl_0300299C & 0x40) {
        if (win->unk2 != 0) {
            win->unk2--;
            m4aSongNumStart(1);
        } else if (lbl_03002774 != 0) {
            fn_02009A14(1, 1, win->unk5);
            n = lbl_03002774 - 1;
            fn_0200A700(n, n % win->unkE);
            pal = fn_0200A758(n) ? 5 : 6;
            fn_02009AB8(1, win->unk5, n % win->unkE, 0, pal);
            lbl_03002774--;
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    } else if (lbl_0300299C & 0x80) {
        if (win->unk2 < win->unkE - 1) {
            win->unk2++;
            m4aSongNumStart(1);
        } else if (lbl_03002774 + win->unkE >= max) {
            m4aSongNumStart(0);
        } else {
            fn_02009A14(0, 1, win->unk5);
            n = lbl_03002774 + win->unkE;
            fn_0200A700(n, n % win->unkE);
            pal = fn_0200A758(n) ? 5 : 6;
            fn_02009AB8(1, win->unk5, n % win->unkE, win->unkE - 1, pal);
            lbl_03002774++;
            m4aSongNumStart(1);
        }
    }
    if (!(lbl_0300299C & 0xC0)) {
        if (lbl_030029AC & 1) {
            m4aSongNumStart(0);
        } else if (lbl_030029AC & 2) {
            lbl_03002775 = 1;
            gOpenMenuReq = 1;
            m4aSongNumStart(3);
        } else if (lbl_030029AC & 0x300) {
            if (lbl_030029AC & 0x100)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            m4aSongNumStart(6);
            lbl_03002775 = 1;
        }
    } else if (prev != lbl_03002774 + win->unk2) {
        fn_0200A790();
    }
}

void fn_0200A57C(void)
{
    struct Window *win = &gWindows[1];
    s32 x = (win->unk10 + 2) * 8;
    s32 y = (win->unk12 + 1) * 8;
    s32 n = win->unkE;
    s32 base = lbl_03002774 + 159;
    s32 i;
    s32 id;
    s32 flags;

    for (i = 0; i < n; i++, y += 16) {
        if (fn_0200A758(lbl_03002774 + i)) {
            id = fn_0201AB14(base + i);
            fn_02003C3C(x, y, 0, id, fn_02004030(0, id), 2, 0);
        }
    }
    flags = lbl_03002774 != 0;
    if (lbl_03002774 + win->unkE <= 72)
        flags |= 2;
    fn_02009BB0(1, win->unk5, flags);
}
