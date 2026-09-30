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

#define DmaClear32(dmaAddr, value, dst, size) \
    { \
        vu32 tmp = (vu32)(value); \
        DmaSet(dmaAddr, &tmp, dst, 0x85000000 | ((size) / 4)); \
    }

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

struct Unk03002FB0 {
    u8 unk0[17];
    s8 unk11;
    u8 unk12[2];
    u8 unk14[4];
    u8 unk18[4];
};

extern s8 lbl_03002780;
extern s8 lbl_03002782[2];
extern s8 lbl_03002784[2];
extern s8 lbl_030027A0[8];
extern s8 lbl_030027A8;
extern s8 lbl_030027A9;
extern s8 lbl_030027AA;
extern s8 lbl_030027AB;
extern s8 lbl_030027AC;
extern u16 lbl_0300299C;
extern u16 lbl_030029AC;
extern u32 lbl_03002AC8;
extern u16 gDataFlags;
extern u8 gReplyWaiting;
extern s8 gReplyResult;
extern struct Unk03002FB0 lbl_03002FB0;
extern u8 lbl_03002FC2[2];
extern u8 lbl_03002FC4[12];
extern s32 lbl_030030A4;
extern s32 gScreenInitDone;
extern struct Window gWindows[];
extern s32 lbl_030032EC;
extern s32 gScreenPhase;
extern const s8 lbl_0201D02D[];
extern u16 lbl_0201D03C;

void *memcpy(void *, const void *, u32);
void m4aSongNumStart(u16);
void fn_020007D8(void);
u16 *fn_02000A40(s32, s32, s32);
void fn_02000A74(void);
void Reply_Clear(void);
s32 Reply_IsTimedOut(void);
void Link_SendCMakeLook(s32);
void Link_SendCMakeBirthday(s32, s32);
void fn_02003394(s32, s32);
void fn_020033F4(void);
s32 fn_02003464(const char *, s32);
void fn_020038F4(s32);
void fn_02003900(s32);
void fn_02003C3C(s32, s32, s32, s32, s32, s32, s32);
s32 fn_02004030(s32, s32);
void fn_020059D4(struct Window *, s32, s32);
void fn_02005A50(struct Window *);
void fn_02008178(struct Window *);
void fn_02008E88(s32, s32, s32, s32, s32, s32);
void fn_0200907C(s32, s32, s32, s32, s32);
s32 fn_02009280(void);
s32 fn_020092C4(void);
s32 fn_020092E8(void);
void fn_0200B294(char *, s32);
void fn_0200B340(void);
void fn_0200B944(void);
char *fn_0201A6D4(s32);
char *fn_0201A73C(s32);
char *fn_0201A974(s32);
char *fn_0201A9DC(s32);
char *fn_0201AAAC(s32);

void fn_0200BE1C(void);
s32 fn_0200BEC4(void);
s32 fn_0200C004(void);
s32 fn_0200C1A4(void);
void fn_0200C490(void);
void fn_0200C5D4(void);
s32 fn_0200C62C(void);
void fn_0200CB90(void);
void fn_0200CC30(void);
void fn_0200CC5C(s32);
void fn_0200CD9C(void);
void fn_0200CFBC(void);
s32 fn_0200D138(void);

s32 fn_0200BA90(void)
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
        fn_0200B944();
    fn_02003394(0, 0);
    fn_020033F4();
    fn_02005A50(win);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win->unk1 = 0;
        ret = 1;
    }
    row = win->unk1 >> 3;
    if (ret == 0 && !(row & 1) && (row >>= 1) <= 4) {
        fn_020033F4();
        row--;
        memcpy(&tmp, win, sizeof(struct Window));
        tmp.unk5--;
        fn_020038F4(20);
        fn_02003464(fn_0201A6D4(row), 0);
        fn_020059D4(&tmp, row, 0);
        for (i = 0, p = buf; i < sizeof(buf) / sizeof(buf[0]); i++)
            p[i] = 0x3FF;
        tile = tmp.unk14 * (row * 2) + 128;
        pal = 0x7000;
        for (i = 0; i < tmp.unk14; i++) {
            p[i] = tile++ | pal;
            p[i + 30] = tile++ | pal;
        }
        map = fn_02000A40(tmp.unk5, tmp.unk10, tmp.unk12 + (row * 2 + 1));
        DmaSet(DMA3, p, map, 0x80000000 | tmp.unk14);
        DmaSet(DMA3, &buf[30], map + 32, 0x80000000 | tmp.unk14);
    }
    if ((win->unk1 >> 3) == 1) {
        fn_02003394(0, 0);
        fn_020033F4();
        row = (144 - fn_02003464(fn_0201A9DC(3), 2)) >> 1;
        fn_0200B294(fn_0201A9DC(3), row);
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 fn_0200BC38(void)
{
    s32 ret = 0;
    s32 state = lbl_030030A4;

    if (state == 0) {
        ret = fn_0200BEC4();
    } else if (state >= 1 && state <= 3) {
        if (state == 1) {
            if (fn_0200C004())
                lbl_030030A4++;
        } else if (state == 2) {
            if (lbl_030027AC == 0) {
                fn_0200BEC4();
                if (lbl_030032EC == 0)
                    lbl_030030A4++;
                else if (lbl_03002780 < 0)
                    ret = 1;
            } else if (gDataFlags & 0x8000) {
                if (gReplyResult != 0) {
                    lbl_030030A4 = 4;
                    m4aSongNumStart(0);
                } else {
                    ret = 1;
                }
                lbl_030027AC = 0;
                Reply_Clear();
            } else if (Reply_IsTimedOut()) {
                lbl_030027AC = ret;
                Reply_Clear();
            }
        } else {
            if (fn_0200C1A4())
                lbl_030030A4 = ret;
        }
    } else if (state == 4) {
        if (fn_02009280())
            lbl_030030A4++;
    } else if (state == 5) {
        if (fn_020092C4())
            lbl_030030A4++;
    } else {
        if (fn_020092E8())
            lbl_030030A4 = 2;
    }
    fn_0200BE1C();
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 fn_0200BD5C(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;

    fn_02003394(1, 0);
    fn_02008178(win);
    if (lbl_03002780 > 0)
        fn_02008178(win + 1);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
        if (lbl_03002780 > 0)
            win[1].unk1 += 8;
    } else {
        win->unk1 = ret;
        win[1].unk1 += 8;
        fn_0200B340();
        if (lbl_03002780 < 0) {
            ret = -1;
        } else {
            ret = 1;
            lbl_03002FB0.unk11 = (lbl_03002FB0.unk11 & ~0xF) | ((win->unk2 & 3) | ((win[1].unk2 & 3) << 2));
            fn_020007D8();
        }
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

void fn_0200BE1C(void)
{
    struct Window *win;
    s32 frame;
    s32 i;
    s32 x;
    s32 y;

    if (gScreenPhase == 1 && (lbl_030030A4 == 0 || lbl_030030A4 == 2)) {
        frame = 45;
        for (i = 0; i <= lbl_030032EC; i++) {
            if (lbl_030032EC != 0 && i == 0 && (lbl_03002AC8 & 2))
                continue;
            win = &gWindows[i];
            x = win->unk10 * 8;
            y = (win->unk12 + 1) * 8 + win->unk2 * 16;
            fn_02003C3C(x, y, 0, frame, fn_02004030(0, frame), 1, 0);
        }
    }
}

s32 fn_0200BEC4(void)
{
    struct Window *win;
    s32 ret;

    if (lbl_0300299C == 0)
        return 0;
    win = &gWindows[lbl_030032EC];
    ret = 0;
    if (lbl_0300299C & 0x40) {
        if (win->unk2 == 0)
            win->unk2 = win->unkE - 1;
        else
            win->unk2--;
        m4aSongNumStart(1);
    } else if (lbl_0300299C & 0x80) {
        if (win->unk2 >= win->unkE - 1)
            win->unk2 = 0;
        else
            win->unk2++;
        m4aSongNumStart(1);
    }
    if (!(lbl_0300299C & 0xC0)) {
        if (lbl_030029AC & 1) {
            m4aSongNumStart(2);
            if (lbl_030032EC == 0) {
                lbl_030032EC = 1;
                lbl_030030A4 = 1;
            } else {
                lbl_03002780 = 1;
                Link_SendCMakeLook((u8)(lbl_03002FB0.unk11 & ~0x7F) | (gWindows[0].unk2 & 3) | ((gWindows[1].unk2 & 3) << 2));
                lbl_030027AC = 1;
                Reply_Clear();
                gReplyWaiting = 1;
            }
        } else if (lbl_030029AC & 2) {
            if (lbl_030032EC != 0) {
                lbl_030032EC = 0;
            } else {
                lbl_03002780 = -1;
                ret = 1;
            }
            m4aSongNumStart(3);
        }
    }
    return ret;
}

s32 fn_0200C004(void)
{
    struct Window tmp;
    u16 buf[60];
    s32 ret = 0;
    struct Window *win = &gWindows[1];
    struct Window *prev;
    s32 row;
    s32 half;
    s32 line;
    s32 n;
    s32 i;
    s32 tile;
    s32 pal;
    u16 *map;

    fn_02003394(0, 0);
    fn_020033F4();
    fn_02005A50(win);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win->unk1 = 0;
        ret = 1;
    }
    row = win->unk1 >> 3;
    if (ret == 0 && !(row & 1) && (half = row >> 1) <= 4) {
        fn_020033F4();
        row = half - 1;
        prev = win - 1;
        memcpy(&tmp, prev, sizeof(struct Window));
        tmp.unk5--;
        fn_020038F4(20);
        n = prev->unk2 * 8;
        if (lbl_03002FB0.unk11 & 0x80)
            n += 4;
        fn_02003464(fn_0201A974(n + row), 0);
        line = half + 3;
        fn_020059D4(&tmp, line, 0);
        for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
            buf[i] = 0x3FF;
        tile = tmp.unk14 * (line * 2) + 128;
        pal = 0x7000;
        for (i = 0; i < tmp.unk14; i++) {
            buf[i] = tile++ | pal;
            buf[i + 30] = tile++ | pal;
        }
        half = row * 2 + 1;
        map = fn_02000A40(tmp.unk5, win->unk10, win->unk12 + half);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        DmaSet(DMA3, &buf[30], map + 32, 0x80000000 | win->unk14);
    }
    if ((win->unk1 >> 3) == 1) {
        fn_02003394(0, 0);
        fn_020033F4();
        row = (144 - fn_02003464(fn_0201A9DC(3), 2)) >> 1;
        fn_0200B294(fn_0201A9DC(3), row);
    }
    return ret;
}

s32 fn_0200C1A4(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[1];

    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win->unk1 = 0;
        ret = 1;
    }
    return ret;
}

void fn_0200C1DC(void)
{
    struct Window *win;
    s32 i;

    DmaClear32(DMA0, 0, gWindows, sizeof(struct Window) * 5);
    win = gWindows;
    win->unk0 = 1;
    win->unk10 = 9;
    win->unk12 = 7;
    win->unkE = 2;
    win->unk14 = 14;
    win->unk16 = 7;
    win->unk3 = 8;
    win->unk4 = 0;
    win->unk5 = 2;
    win->unk6 = 0;
    win->unk7 = 0;
    for (i = 0; i < gWindows[0].unkE; i++) {
        gWindows[0].items[i].unk0 = 1;
        gWindows[0].items[i].unk4 = fn_0201A73C(0);
    }
    for (i = 0; i <= 1; i++) {
        lbl_03002784[i] = lbl_03002FC2[i];
        if (lbl_03002784[i] == 0)
            lbl_03002784[i] = 1;
    }
    if (lbl_03002784[0] > 12)
        lbl_03002784[0] = 1;
    if (lbl_03002784[1] > lbl_0201D02D[lbl_03002784[0] - 1])
        lbl_03002784[1] = 1;
    lbl_03002780 = 0;
    lbl_030027AC = 0;
    gScreenInitDone = 1;
    fn_02000A74();
}

s32 fn_0200C2EC(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;
    s32 row;

    if (gScreenInitDone == 0)
        fn_0200C1DC();
    fn_02003394(0, 0);
    fn_020033F4();
    fn_02005A50(win);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win->unk1 = 0;
        ret = 1;
    }
    row = win->unk1 >> 3;
    if (ret == 0 && row == 3)
        fn_0200C490();
    if ((win->unk1 >> 3) == 1) {
        fn_02003394(0, 0);
        fn_020033F4();
        row = (144 - fn_02003464(fn_0201A9DC(4), 2)) >> 1;
        fn_0200B294(fn_0201A9DC(4), row);
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 fn_0200C394(void)
{
    s32 ret = 0;

    if (lbl_030027AC == 0) {
        ret = fn_0200C62C();
    } else if (gDataFlags & 0x8000) {
        if (gReplyResult == 0)
            ret = 1;
        lbl_030027AC = 0;
        Reply_Clear();
    } else if (Reply_IsTimedOut()) {
        lbl_030027AC = ret;
        Reply_Clear();
    }
    fn_0200C5D4();
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 fn_0200C410(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;

    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win->unk1 = ret;
        fn_0200B340();
        if (lbl_03002780 < 0) {
            ret = -1;
        } else {
            ret = 1;
            lbl_03002FB0.unk12[0] = lbl_03002784[0];
            lbl_03002FB0.unk12[1] = lbl_03002784[1];
        }
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

void fn_0200C490(void)
{
    char str[2];
    struct Window tmp;
    u16 buf[60];
    s32 i;
    s32 tile;
    s32 pal;
    s32 digit;
    u16 *map;

    fn_02003394(0, 0);
    fn_020033F4();
    for (i = 0; i <= 2; i++) {
        *(u16 *)str = lbl_0201D03C;
        if (i <= 1) {
            digit = (s8)(lbl_03002784[i] / 10);
            if (digit != 0) {
                str[0] += digit;
                fn_02003464(str, 1);
            } else {
                fn_02003900(9);
            }
            digit = (s8)(lbl_03002784[i] % 10);
            str[0] = digit + '0';
            fn_02003464(str, 1);
        }
        fn_02003464(fn_0201A9DC(i + 9), 0);
    }
    memcpy(&tmp, gWindows, sizeof(struct Window));
    tmp.unk5--;
    fn_020059D4(&tmp, 0, 0);
    for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
        buf[i] = 0x3FF;
    tile = 128;
    pal = 0x7000;
    for (i = 0; i < tmp.unk14; i++) {
        buf[i] = tile++ | pal;
        buf[i + 30] = tile++ | pal;
    }
    map = fn_02000A40(tmp.unk5, tmp.unk10 + 1, tmp.unk12 + 2);
    DmaSet(DMA3, buf, map, 0x80000000 | tmp.unk14);
    DmaSet(DMA3, &buf[30], map + 32, 0x80000000 | tmp.unk14);
}

void fn_0200C5D4(void)
{
    s32 x;
    s32 y;

    if (gScreenPhase == 1) {
        x = (gWindows[0].unk10 + 1) * 8 + 10;
        if (gWindows[0].unk2 != 0)
            x += 29;
        y = (gWindows[0].unk12 + 4) * 8;
        fn_02003C3C(x, y, 2, 5, fn_02004030(2, 5), 1, 0);
    }
}

s32 fn_0200C62C(void)
{
    struct Window *win;
    s32 ret;
    s32 sel;

    if (lbl_0300299C == 0)
        return 0;
    win = gWindows;
    ret = 0;
    if (lbl_0300299C & 0x40) {
        sel = win->unk2;
        if (sel == 0) {
            if (lbl_03002784[0] >= 12)
                lbl_03002784[0] = 1;
            else
                lbl_03002784[0]++;
            if (lbl_03002784[1] > lbl_0201D02D[lbl_03002784[0] - 1])
                lbl_03002784[1] = lbl_0201D02D[lbl_03002784[0] - 1];
        } else {
            if (lbl_03002784[sel] >= lbl_0201D02D[lbl_03002784[0] - 1])
                lbl_03002784[sel] = 1;
            else
                lbl_03002784[sel]++;
        }
        fn_0200C490();
        m4aSongNumStart(1);
    } else if (lbl_0300299C & 0x80) {
        sel = win->unk2;
        if (sel == 0) {
            if (lbl_03002784[0] <= 1)
                lbl_03002784[0] = 12;
            else
                lbl_03002784[0]--;
            if (lbl_03002784[1] > lbl_0201D02D[lbl_03002784[0] - 1])
                lbl_03002784[1] = lbl_0201D02D[lbl_03002784[0] - 1];
        } else {
            if (lbl_03002784[sel] <= 1)
                lbl_03002784[sel] = lbl_0201D02D[lbl_03002784[0] - 1];
            else
                lbl_03002784[sel]--;
        }
        fn_0200C490();
        m4aSongNumStart(1);
    }
    if (lbl_0300299C & 0x30) {
        win->unk2 ^= 1;
        m4aSongNumStart(1);
    }
    if (!(lbl_0300299C & 0xF0)) {
        if (lbl_030029AC & 1) {
            Link_SendCMakeBirthday(lbl_03002784[0], lbl_03002784[1]);
            lbl_030027AC = 1;
            Reply_Clear();
            gReplyWaiting = 1;
            lbl_03002780 = 1;
            m4aSongNumStart(2);
        } else if (lbl_030029AC & 2) {
            lbl_03002780 = -1;
            ret = 1;
            m4aSongNumStart(3);
        }
    }
    return ret;
}

void fn_0200C7F0(void)
{
    struct Window *win;
    s32 i;
    s32 idx;

    DmaClear32(DMA0, 0, gWindows, sizeof(struct Window) * 5);
    win = gWindows;
    win->unk0 = 1;
    win->unk10 = 1;
    win->unk12 = 3;
    win->unkE = 6;
    win->unk14 = 26;
    win->unk16 = 15;
    win->unk3 = 8;
    win->unk4 = 0;
    win->unk5 = 2;
    win->unk6 = 0;
    win->unk7 = 0;
    win[1].unk0 = 1;
    win[1].unk10 = 24;
    win[1].unk12 = 16;
    win[1].unkE = 1;
    win[1].unk14 = 5;
    win[1].unk16 = 3;
    win[1].unk3 = 3;
    win[1].unk4 = 0;
    win[1].unk5 = 1;
    win[1].unk6 = 2;
    win[1].unk7 = 0;
    for (i = 0; i < gWindows[0].unkE; i++) {
        gWindows[0].items[i].unk0 = 1;
        gWindows[0].items[i].unk4 = fn_0201A73C(0);
    }
    for (i = 0; i <= 7; i++) {
        if (i & 1)
            idx = lbl_03002FC4[i >> 1] >> 4;
        else
            idx = lbl_03002FC4[i >> 1] & 15;
        lbl_030027A0[idx] = i;
    }
    lbl_03002780 = 0;
    lbl_030027A8 = 0;
    lbl_030027A9 = 0;
    lbl_030027AB = 0;
    lbl_030027AA = 0;
    lbl_030027AC = 0;
    lbl_03002782[1] = 0;
    lbl_03002782[0] = 0;
    lbl_030032EC = 0;
    gScreenInitDone = 1;
    fn_02000A74();
}

s32 fn_0200C95C(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;
    s32 x;

    if (gScreenInitDone == 0)
        fn_0200C7F0();
    fn_02003394(1, 0);
    fn_020033F4();
    fn_0200CB90();
    fn_02005A50(win);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win++;
        fn_02005A50(win);
        if ((win->unk1 >> 3) < win->unk16 - 1) {
            win->unk1 += 8;
        } else {
            win[-1].unk1 = 0;
            win->unk1 = 0;
            ret = 1;
        }
    }
    fn_02003394(0, 0);
    fn_020033F4();
    if ((win->unk1 >> 3) == 1) {
        fn_02003394(0, 0);
        fn_020033F4();
        x = (144 - fn_02003464(fn_0201A9DC(5), 2)) >> 1;
        fn_0200B294(fn_0201A9DC(5), x);
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 fn_0200CA20(void)
{
    s32 ret;

    fn_0200CB90();
    fn_0200CC30();
    ret = 0;
    if (lbl_030027AC == 0) {
        ret = fn_0200D138();
    } else if (gDataFlags & 0x8000) {
        if (gReplyResult == 0)
            ret = 1;
        lbl_030027AC = 0;
        Reply_Clear();
    } else if (Reply_IsTimedOut()) {
        lbl_030027AC = ret;
        Reply_Clear();
    }
    fn_0200CFBC();
    fn_0200CD9C();
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 fn_0200CAA8(void)
{
    s32 ret = 0;
    struct Window *win = gWindows;
    s32 i;
    s32 v;

    fn_02003394(1, 0);
    fn_02008178(win);
    fn_02008178(win + 1);
    if ((win[1].unk1 >> 3) < win[1].unk16 - 1)
        win[1].unk1 += 8;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win->unk1 = 0;
        win[1].unk1 = 0;
        fn_0200B340();
        if (lbl_03002780 < 0) {
            ret = -1;
        } else {
            for (i = 0; i < 4; i++)
                lbl_03002FB0.unk14[i] = 0;
            for (i = 0; i <= 7; i++) {
                v = lbl_030027A0[i];
                if (v & 1)
                    lbl_03002FC4[v >> 1] |= (i & 15) << 4;
                else
                    lbl_03002FC4[v >> 1] |= i & 15;
            }
            ret = 1;
        }
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

void fn_0200CB90(void)
{
    char str[2];
    struct Window tmp;
    s32 i;

    if (lbl_030027A8 > 9)
        return;
    memcpy(&tmp, gWindows, sizeof(struct Window));
    tmp.unk5--;
    tmp.unk14 = 18;
    fn_02003394(0, 0);
    fn_020033F4();
    if (lbl_030027A8 == 0) {
        str[0] = str[1] = 0;
        for (i = 1; i <= 9; i++) {
            str[0] = i + '0';
            fn_02003464(str, 1);
            fn_020038F4(i << 4);
        }
    } else {
        fn_02003464(fn_0201AAAC(lbl_030027A8 + 380), 0);
    }
    fn_020059D4(&tmp, lbl_030027A8, 0);
    lbl_030027A8++;
}

void fn_0200CC30(void)
{
    if (lbl_030027A9 < gWindows[0].unkE)
        fn_0200CC5C(lbl_030027A9++);
}

void fn_0200CC5C(s32 idx)
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

    if (idx >= win->unkE)
        return;
    for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
        buf[i] = 0x3FF;
    n = 2;
    tile = (idx + lbl_030027AB) * 4 + 128;
    pal = 0x7000;
    for (i = 0; i < n; i++) {
        buf[i] = tile++ | pal;
        buf[i + 30] = tile++ | pal;
    }
    x = win->unk10 + 2;
    y = win->unk12 + 2 + idx * 2;
    map = fn_02000A40(win->unk5 - 1, x, y);
    DmaSet(DMA3, buf, map, 0x80000000 | n);
    DmaSet(DMA3, &buf[30], map + 32, 0x80000000 | n);
    tile = (lbl_030027A0[idx + lbl_030027AB] + 1) * 36 + 128;
    n = 10;
    for (i = 0; i < n; i++) {
        buf[i] = tile++ | pal;
        buf[i + 30] = tile++ | pal;
    }
    x += 4;
    map = fn_02000A40(win->unk5 - 1, x, y);
    DmaSet(DMA3, buf, map, 0x80000000 | n);
    DmaSet(DMA3, &buf[30], map + 32, 0x80000000 | n);
}

void fn_0200CD9C(void)
{
    s32 i;
    s32 x;
    s32 y;
    s32 n;
    s32 frame;
    struct Window *win;

    x = gWindows[1].unk10 * 8;
    y = gWindows[1].unk12 * 8 + 5;
    for (i = 0; i <= 2; i++, x += 16)
        fn_02003C3C(x, y, 22, i, 0, 1, 0);
    win = gWindows;
    if (gScreenPhase == 1 && lbl_030027A9 >= win->unkE)
        n = win->unkE;
    else
        n = lbl_030027A9;
    x = win->unk10 * 8 + 29;
    y = win->unk12 * 8 + 14;
    for (i = 0; i < n; i++, y += 16) {
        frame = lbl_030027A0[i + lbl_030027AB] + 20;
        fn_02003C3C(x, y, 0, frame, fn_02004030(0, frame), 1, 0);
    }
    x = (win->unk10 + 16) * 8;
    y = (win->unk12 + 2) * 8 + 4;
    for (i = 0; i < n; i++, y += 16)
        fn_0200907C(x, y, 7, 1, 9 - (i + lbl_030027AB));
}
