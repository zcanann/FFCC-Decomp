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

#define DmaCopy16(dmaAddr, src, dst, size) \
    DmaSet(dmaAddr, src, dst, 0x80000000 | ((size) >> 1))

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
    u8 unk0[0x5D];
    s8 unk5D;
};

struct Unk03002FB0 {
    char unk0[17];
    s8 unk11;
    u8 unk12[2];
    u8 unk14[4];
    u8 unk18[4];
};

extern s8 lbl_03002780;
extern s8 lbl_03002782[2];
extern s8 lbl_030027A0[8];
extern s8 lbl_030027A8;
extern s8 lbl_030027A9;
extern s8 lbl_030027AA;
extern s8 lbl_030027AB;
extern s8 lbl_030027AC;
extern s32 lbl_030027B8;
extern u8 lbl_030027BC;
extern u8 lbl_030027BD;
extern u8 lbl_030027BE;
extern u8 lbl_030027BF;
extern u16 lbl_0300299C;
extern u16 lbl_030029AC;
extern u32 lbl_03002AC8;
extern u16 lbl_03002AEC;
extern u8 lbl_03002AF4;
extern s8 lbl_03002AFC;
extern struct Work lbl_03002CA0;
extern struct Unk03002FB0 lbl_03002FB0;
extern s32 lbl_030030A4;
extern s32 lbl_030030AC;
extern struct Window lbl_030030B0[];
extern struct Window lbl_03003120;
extern s32 lbl_030032EC;
extern const char lbl_0201D040[];

void *memcpy(void *, const void *, u32);
void *memset(void *, int, u32);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
void m4aSongNumStart(u16);
u16 *fn_02000A40(s32, s32, s32);
void fn_02000A74(void);
void fn_02001578(void);
s32 fn_02001604(void);
void fn_0200321C(u8);
void fn_0200324C(void);
void fn_0200327C(u8 *);
void fn_02003394(s32, s32);
void fn_020033F4(void);
s32 fn_02003464(const char *, s32);
void fn_020037C8(s32, s32, s32);
void fn_02003890(u32, s32);
void fn_020038D8(u32);
void fn_020038F4(s32);
void fn_02003900(s32);
void fn_0200391C(s32, s32, s32);
void fn_02003C3C(s32, s32, s32, s32, s32, s32, s32);
s32 fn_02004030(s32, s32);
void fn_02004098(s32, s32, s32, s32);
void fn_020041D4(s32, s32);
void fn_02005968(struct Window *);
void fn_020059D4(struct Window *, s32, s32);
void fn_02005A50(struct Window *);
void fn_02008178(struct Window *);
void fn_02008E88(s32, s32, s32, s32, s32, s32);
void fn_020091D4(void);
s32 fn_02009280(void);
s32 fn_020092C4(void);
s32 fn_020092E8(void);
void fn_020093B4(s32, s32);
void fn_02009B80(struct Window *, s32);
void fn_02009CBC(s32, s32, s32);
void fn_02009DA8(s32, s32);
void fn_0200B294(char *, s32);
void fn_0200B340(void);
void fn_0200CC5C(s32);
void fn_0200EB80(void);
char *fn_0201A6D4(s32);
char *fn_0201A73C(s32);
char *fn_0201A7D4(s32);
char *fn_0201A8A4(s32);
char *fn_0201A974(s32);
char *fn_0201A9DC(s32);

void fn_0200CF54(void);
void fn_0200D380(void);
void fn_0200D680(void);
void fn_0200D6E4(void);
void fn_0200D7D0(void);
s32 fn_0200D838(void);
void fn_0200D934(void);
void fn_0200DD44(void);
void fn_0200DE80(void);
void fn_0200DF38(void);
s32 fn_0200DFE0(void);

void fn_0200CEC4(s32 up)
{
    struct Window *win = lbl_030030B0;
    s32 step = 64;
    s32 from;
    s32 to;
    u8 *src;
    u8 *dst;
    s32 i;
    s32 j;

    if (up) {
        to = win->unk12 + 1 + win->unkE * 2;
        from = to - 2;
        step = -step;
    } else {
        from = win->unk12 + 4;
        to = win->unk12 + 2;
    }
    src = (u8 *)fn_02000A40(win->unk5 - 1, win->unk10 + 1, from);
    dst = (u8 *)fn_02000A40(win->unk5 - 1, win->unk10 + 1, to);
    for (i = 0; i < win->unkE - 1; i++) {
        for (j = 0; j < 2; j++) {
            DmaSet(DMA0, src, dst, 0x8000000F);
            src += step;
            dst += step;
        }
    }
}

void fn_0200CF54(void)
{
    s32 i;
    s32 tmp;

    tmp = lbl_030027A0[lbl_03002782[0]];
    lbl_030027A0[lbl_03002782[0]] = lbl_030027A0[lbl_03002782[1]];
    lbl_030027A0[lbl_03002782[1]] = tmp;
    for (i = 0; i < 2; i++) {
        if (lbl_03002782[i] >= lbl_030027AB && lbl_03002782[i] < lbl_030027AB + lbl_030030B0[0].unkE)
            fn_0200CC5C(lbl_03002782[i] - lbl_030027AB);
    }
}

void fn_0200CFBC(void)
{
    s32 frame = 45;
    struct Window *win = lbl_030030B0;
    s32 x;
    s32 y;
    s32 blink;

    if (lbl_030032EC) {
        x = win[1].unk10 * 8 - 10;
        y = win[1].unk12 * 8 + 5;
    } else {
        x = win->unk10 * 8;
        y = win->unk12 * 8;
        y += (win->unk2 + 1) * 16;
    }
    fn_02003C3C(x, y, 0, frame, fn_02004030(0, frame), 1, 0);
    if (lbl_030027AA && (lbl_03002AC8 & 2)) {
        if (lbl_03002782[0] >= lbl_030027AB && lbl_03002782[0] < lbl_030027AB + win->unkE) {
            x = win->unk10 * 8;
            y = win->unk12 * 8;
            y += (lbl_03002782[0] - lbl_030027AB + 1) * 16;
            fn_02003C3C(x - 2, y - 2, 0, frame, fn_02004030(0, frame), 1, 0);
        }
    }
    blink = (lbl_03002AC8 & 8) >> 2;
    x = (win->unk10 + 23) * 8;
    if (lbl_030027AB != 0) {
        y = (win->unk12 + 3) * 8;
        y += blink;
        fn_02003C3C(x, y, 0, 46, fn_02004030(0, 46), 1, 0);
    }
    if (lbl_030027AB + win->unkE <= 8) {
        y = (win->unk12 + 11) * 8;
        y -= blink;
        fn_02003C3C(x, y, 0, 46, fn_02004030(0, 46), 1, 0x20000000);
    }
}

s32 fn_0200D138(void)
{
    struct Window *win;
    s32 ret;
    u8 buf[8];
    s32 i;
    s32 v;

    if (lbl_0300299C == 0)
        return 0;
    win = lbl_030030B0;
    ret = 0;
    if (lbl_030032EC == 0) {
        if (lbl_0300299C & 0x40) {
            if (win->unk2 == 0) {
                if (lbl_030027AB == 0) {
                    m4aSongNumStart(0);
                } else {
                    lbl_030027AB--;
                    fn_0200CEC4(1);
                    fn_0200CC5C(0);
                    m4aSongNumStart(1);
                }
            } else {
                win->unk2--;
                m4aSongNumStart(1);
            }
        } else if (lbl_0300299C & 0x80) {
            if (win->unk2 >= win->unkE - 1) {
                if (lbl_030027AB + win->unkE < 8) {
                    lbl_030027AB++;
                    fn_0200CEC4(0);
                    fn_0200CC5C(win->unkE - 1);
                    m4aSongNumStart(1);
                } else {
                    m4aSongNumStart(0);
                }
            } else {
                win->unk2++;
                m4aSongNumStart(1);
            }
        }
    } else if (lbl_030029AC & 0xC0) {
        m4aSongNumStart(0);
    }

    if (lbl_030029AC & 0x20) {
        if (lbl_030032EC) {
            lbl_030032EC = 0;
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    } else if (lbl_030029AC & 0x10) {
        if (lbl_030032EC == 0) {
            if (lbl_030027AA) {
                m4aSongNumStart(0);
            } else {
                lbl_030032EC = 1;
                m4aSongNumStart(1);
            }
        } else {
            m4aSongNumStart(0);
        }
    }

    if (!(lbl_0300299C & 0xF0)) {
        if (lbl_030029AC & 1) {
            if (lbl_030032EC == 0) {
                lbl_03002782[lbl_030027AA] = lbl_030027AB + win->unk2;
                if (lbl_030027AA)
                    fn_0200CF54();
                lbl_030027AA ^= 1;
            } else {
                for (i = 0; i < 4; i++)
                    buf[i] = 0;
                for (i = 0; i < 8; i++) {
                    v = lbl_030027A0[i];
                    if (v & 1)
                        buf[v >> 1] |= (i & 15) << 4;
                    else
                        buf[v >> 1] |= i & 15;
                }
                fn_0200327C(buf);
                lbl_03002780 = 1;
                lbl_030027AC = 1;
                fn_02001578();
                lbl_03002AF4 = 1;
            }
            m4aSongNumStart(2);
        } else if (lbl_030029AC & 2) {
            if (lbl_030027AA) {
                lbl_030027AA = 0;
            } else {
                lbl_03002780 = -1;
                ret = 1;
            }
            m4aSongNumStart(3);
        }
    }
    return ret;
}

void fn_0200D380(void)
{
    s32 i;

    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);

    lbl_030030B0->unk0 = 1;
    lbl_030030B0->unk10 = 5;
    lbl_030030B0->unk12 = 5;
    lbl_030030B0->unkE = 6;
    lbl_030030B0->unk14 = 21;
    lbl_030030B0->unk16 = 12;
    lbl_030030B0->unk3 = 8;
    lbl_030030B0->unk4 = 0;
    lbl_030030B0->unk5 = 2;
    lbl_030030B0->unk6 = 0;
    lbl_030030B0->unk7 = 0;
    for (i = 0; i < lbl_030030B0->unkE; i++) {
        lbl_030030B0->items[i].unk0 = 1;
        lbl_030030B0->items[i].unk4 = fn_0201A73C(0);
    }
    lbl_030030B0[4].items[0].unk0 = 1;
    lbl_030030B0[4].items[0].unk4 = fn_0201A8A4(2);
    fn_020091D4();
    lbl_030030B0->unk2 = lbl_03002FB0.unk18[0];

    lbl_03002780 = 0;
    lbl_030027AB = 0;
    lbl_030027AA = 0;
    lbl_030027A8 = 0;
    lbl_030027A9 = 0;
    lbl_030027AC = 0;
    lbl_03002782[1] = 0;
    lbl_03002782[0] = 0;
    lbl_030030A4 = 0;
    lbl_030032EC = 0;
    lbl_030030AC = 1;
    fn_02000A74();
}

s32 fn_0200D490(void)
{
    s32 ret = 0;
    struct Window *win = lbl_030030B0;
    s32 x;

    if (lbl_030030AC == 0)
        fn_0200D380();
    fn_0200D680();
    fn_02003394(1, 0);
    fn_020033F4();
    fn_02005A50(win);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win->unk1 = ret;
        ret = 1;
    }
    fn_02003394(0, 0);
    fn_020033F4();
    if ((win->unk1 >> 3) == 1) {
        fn_02003394(0, 0);
        fn_020033F4();
        x = (144 - fn_02003464(fn_0201A9DC(6), 2)) >> 1;
        fn_0200B294(fn_0201A9DC(6), x);
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 fn_0200D538(void)
{
    s32 ret;

    fn_0200D680();
    fn_0200D6E4();
    ret = 0;
    if (lbl_030030A4 == 0) {
        if (lbl_030027AC == 0) {
            ret = fn_0200D838();
        } else if (lbl_03002AEC & 0x8000) {
            if (lbl_03002AFC != 0) {
                lbl_030030A4 = 1;
                m4aSongNumStart(0);
            } else {
                ret = 1;
            }
            lbl_030027AC = 0;
            fn_02001578();
        } else if (fn_02001604()) {
            lbl_030027AC = ret;
            fn_02001578();
        }
    } else {
        if (lbl_030030A4 == 1) {
            if (fn_02009280())
                lbl_030030A4++;
        } else if (lbl_030030A4 == 2) {
            if (fn_020092C4())
                lbl_030030A4++;
        } else {
            if (fn_020092E8())
                lbl_030030A4 = ret;
        }
        ret = 0;
    }
    fn_0200D7D0();
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 fn_0200D608(void)
{
    s32 ret = 0;
    struct Window *win = lbl_030030B0;

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
            lbl_03002FB0.unk18[0] = win->unk2;
            ret = 1;
        }
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

void fn_0200D680(void)
{
    struct Window tmp;

    if (lbl_030027A8 <= 7) {
        memcpy(&tmp, lbl_030030B0, sizeof(struct Window));
        tmp.unk5--;
        tmp.unk14 = 8;
        fn_02003394(0, 0);
        fn_020033F4();
        fn_02003464(fn_0201A7D4(lbl_030027A8), 0);
        fn_020059D4(&tmp, lbl_030027A8, 0);
        lbl_030027A8++;
    }
}

void fn_0200D6E4(void)
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

    if (lbl_030027A9 <= 3) {
        win = lbl_030030B0;
        for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
            buf[i] = 0x3FF;
        attr = 0x7000;
        tile = lbl_030027A9 * 16 + 128;
        len = 8;
        for (i = 0; i < len; i++) {
            buf[i] = tile++ | attr;
            buf[i + 30] = tile++ | attr;
        }
        tile = lbl_030027A9 * 16 + 192;
        len += 10;
        for (i = 10; i < len; i++) {
            buf[i] = tile++ | attr;
            buf[i + 30] = tile++ | attr;
        }
        x = win->unk10 + 2;
        y = win->unk12 + 2 + lbl_030027A9 * 2;
        map = fn_02000A40(win->unk5 - 1, x, y);
        DmaCopy16(DMA3, buf, map, len * 2);
        DmaCopy16(DMA3, &buf[30], map + 32, len * 2);
        lbl_030027A9++;
    }
}

void fn_0200D7D0(void)
{
    struct Window *win;
    s32 x;
    s32 y;

    if (lbl_030027A9 > 3) {
        win = lbl_030030B0;
        x = win->unk10 * 8 - 2;
        x += (win->unk2 >> 2) * 80;
        y = win->unk12 * 8;
        y += ((win->unk2 & 3) + 1) * 16;
        fn_02003C3C(x, y, 0, 45, fn_02004030(0, 45), 1, 0);
    }
}

s32 fn_0200D838(void)
{
    struct Window *win;
    s32 ret;

    if (lbl_0300299C == 0)
        return 0;
    win = lbl_030030B0;
    ret = 0;
    if (lbl_0300299C & 0x40) {
        if ((win->unk2 & 3) == 0)
            win->unk2 += 3;
        else
            win->unk2--;
        m4aSongNumStart(1);
    } else if (lbl_0300299C & 0x80) {
        if ((win->unk2 & 3) > 2)
            win->unk2 -= 3;
        else
            win->unk2++;
        m4aSongNumStart(1);
    }
    if (lbl_0300299C & 0x30) {
        if ((u8)win->unk2 >> 2 == 0)
            win->unk2 += 4;
        else
            win->unk2 -= 4;
        m4aSongNumStart(1);
    }
    if (!(lbl_0300299C & 0xF0)) {
        if (lbl_030029AC & 1) {
            lbl_03002780 = 1;
            fn_0200321C(win->unk2);
            lbl_030027AC = 1;
            fn_02001578();
            lbl_03002AF4 = 1;
            m4aSongNumStart(2);
        } else if (lbl_030029AC & 2) {
            lbl_03002780 = -1;
            ret = 1;
            m4aSongNumStart(3);
        }
    }
    return ret;
}

void fn_0200D934(void)
{
    struct Window *win;
    s32 i;
    s32 save;

    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);

    lbl_030030B0->unk0 = 1;
    lbl_030030B0->unk10 = 2;
    lbl_030030B0->unk12 = 4;
    lbl_030030B0->unkE = 4;
    lbl_030030B0->unk14 = 25;
    lbl_030030B0->unk16 = 12;
    lbl_030030B0->unk3 = 8;
    lbl_030030B0->unk4 = 0;
    lbl_030030B0->unk5 = 2;
    lbl_030030B0->unk6 = 0;
    lbl_030030B0->unk7 = 0;

    lbl_030030B0[1].unk0 = 1;
    lbl_030030B0[1].unk10 = 18;
    lbl_030030B0[1].unk12 = 15;
    lbl_030030B0[1].unkE = 3;
    lbl_030030B0[1].unk14 = 11;
    lbl_030030B0[1].unk16 = 4;
    lbl_030030B0[1].unk3 = 3;
    lbl_030030B0[1].unk4 = 0;
    lbl_030030B0[1].unk5 = 1;
    lbl_030030B0[1].unk6 = 2;
    lbl_030030B0[1].unk7 = 0;

    for (i = 0; i < lbl_030030B0->unkE; i++) {
        lbl_030030B0->items[i].unk0 = 1;
        lbl_030030B0->items[i].unk4 = fn_0201A73C(0);
    }
    for (i = 0; i < lbl_030030B0[1].unkE; i++) {
        lbl_030030B0[1].items[i].unk0 = 1;
        lbl_030030B0[1].items[i].unk4 = fn_0201A73C(0);
    }

    fn_02003394(0, 0);
    fn_020033F4();
    fn_02003464(fn_0201A9DC(22), 0);
    fn_0200391C(1, 10, 0);

    lbl_03002780 = 0;
    lbl_030027AB = 0;
    lbl_030027AA = 0;
    lbl_030027A8 = 0;
    lbl_030027A9 = 0;

    fn_02003394(0, 0);
    fn_020033F4();
    win = &lbl_03003120;
    save = win->unk5;
    win->unk5 = 0;
    for (i = 2; i >= 0; i--)
        fn_02005968(win);
    win->unk5 = save;

    lbl_030032EC = 1;
    lbl_030030AC = 1;
    fn_02000A74();
}

s32 fn_0200DABC(void)
{
    s32 ret = 0;
    struct Window *win = lbl_030030B0;
    s32 x;

    if (lbl_030030AC == 0)
        fn_0200D934();
    fn_0200DD44();
    fn_02003394(1, 0);
    fn_020033F4();
    fn_02005A50(win);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        fn_02003394(0, 0);
        fn_020033F4();
        fn_02005A50(win + 1);
        if ((win[1].unk1 >> 3) < win[1].unk16 - 1) {
            win[1].unk1 += 8;
        } else {
            win->unk1 = ret;
            win[1].unk1 = ret;
            ret = 1;
        }
    }
    fn_02003394(0, 0);
    fn_020033F4();
    if ((win->unk1 >> 3) == 1) {
        fn_02003394(0, 0);
        fn_020033F4();
        x = (144 - fn_02003464(fn_0201A9DC(20), 2)) >> 1;
        fn_0200B294(fn_0201A9DC(20), x);
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 fn_0200DB98(void)
{
    struct Window *win = &lbl_03003120;
    s32 ret;
    s32 i;
    s32 x;
    s32 y;

    if (lbl_030032EC == 0) {
        fn_02008178(win);
        if ((win->unk1 >> 3) < win->unk16 - 1)
            win->unk1 += 8;
    }
    fn_0200DE80();
    ret = fn_0200DFE0();
    fn_0200DF38();
    fn_02008E88(2, 8, 7, 20, 0, 1);
    if (lbl_030032EC) {
        x = lbl_030030B0[1].unk10 * 8 + 10;
        y = lbl_030030B0[1].unk12 * 8 + 7;
        for (i = 0; i <= 8; i++, x += 16)
            fn_02003C3C(x, y, 22, i, 0, 1, 0);
    }
    return ret;
}

s32 fn_0200DC4C(void)
{
    s32 ret = 0;
    struct Window *win = lbl_030030B0;

    fn_02003394(1, 0);
    fn_02008178(win);
    if (lbl_030032EC) {
        fn_02008178(win + 1);
        if ((win[1].unk1 >> 3) < win[1].unk16 - 1)
            win[1].unk1 += 8;
    }
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win->unk1 = 0;
        win[1].unk1 = 0;
        fn_0200B340();
        if (lbl_03002780 < 0) {
            ret = -1;
            lbl_030030A4 = win->unk2;
        } else {
            fn_0200324C();
            ret = 1;
            lbl_030030A4 = 0;
        }
        fn_02003394(0, 0);
        fn_020033F4();
        fn_020038F4((40 - fn_02003464(fn_0201A9DC(0), 2)) >> 1);
        fn_02003464(fn_0201A9DC(0), 0);
        fn_0200391C(1, 10, 0);
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

void fn_0200DD44(void)
{
    char buf[64];
    struct Window tmp;
    s32 n;
    s32 idx;

    if (lbl_030027A8 <= 3) {
        memcpy(&tmp, lbl_030030B0, sizeof(struct Window));
        tmp.unk5--;
        tmp.unk14 = 23;
        fn_02003394(0, 0);
        fn_020033F4();
        memset(buf, 0, sizeof(buf));
        idx = lbl_030027A8 + 23;
        strcpy(buf, fn_0201A9DC(idx));
        fn_02003464(buf, 0);
        fn_02003900(8);
        if (lbl_030027A8 == 0) {
            fn_02003464(lbl_03002FB0.unk0, 0);
        } else if (lbl_030027A8 == 1) {
            n = (lbl_03002FB0.unk11 & 0x80) ? 8 : 7;
            fn_02003464(fn_0201A9DC(n), 0);
        } else if (lbl_030027A8 == 2) {
            n = lbl_03002FB0.unk11 & 3;
            strcpy(buf, fn_0201A6D4(n));
            strcat(buf, lbl_0201D040);
            fn_02003464(buf, 0);
            fn_02003900(8);
            idx = n * 8;
            if (lbl_03002FB0.unk11 & 0x80)
                idx += 4;
            fn_02003464(fn_0201A974(idx + ((lbl_03002FB0.unk11 >> 2) & 3)), 0);
        } else if (lbl_030027A8 == 3) {
            n = lbl_03002FB0.unk18[0];
            fn_02003464(fn_0201A9DC(n + 12), 0);
        }
        fn_020059D4(&tmp, lbl_030027A8, 0);
        lbl_030027A8++;
    }
}

void fn_0200DE80(void)
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

    if (lbl_030027A9 <= 3) {
        win = lbl_030030B0;
        for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
            buf[i] = 0x3FF;
        attr = 0x7000;
        len = 23;
        tile = lbl_030027A9 * 46 + 128;
        for (i = 0; i < len; i++) {
            buf[i] = tile++ | attr;
            buf[i + 30] = tile++ | attr;
        }
        x = win->unk10 + 2;
        y = win->unk12 + 2 + lbl_030027A9 * 2;
        map = fn_02000A40(win->unk5 - 1, x, y);
        DmaCopy16(DMA3, buf, map, len * 2);
        DmaCopy16(DMA3, &buf[30], map + 32, len * 2);
        lbl_030027A9++;
    }
}

void fn_0200DF38(void)
{
    struct Window *win;
    s32 sel;
    s32 col;
    s32 x;
    s32 y;

    if (lbl_030027A9 > 3) {
        sel = lbl_030032EC;
        win = &lbl_030030B0[sel];
        if (sel) {
            col = win->unk10 - 1;
            y = win->unk12 * 8 + 7;
            x = (win->unk2 * 5 + col) * 8;
            fn_02003C3C(x, y, 0, 45, fn_02004030(0, 45), 1, 0);
        } else {
            x = win->unk10 * 8 - 2;
            y = (win->unk12 + 2) * 8;
            y += win->unk2 * 16;
            fn_02003C3C(x, y, 0, 45, fn_02004030(0, 45), 1, sel);
        }
    }
}

s32 fn_0200DFE0(void)
{
    struct Window *win;
    s32 ret;
    s32 x;
    s32 w;

    if (lbl_0300299C == 0)
        return 0;
    win = &lbl_030030B0[lbl_030032EC];
    ret = 0;
    if (lbl_030032EC == 0) {
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
    }
    if (lbl_030032EC != 0 && (lbl_0300299C & 0x30)) {
        if (lbl_030032EC != 0) {
            win->unk2 ^= 1;
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    }
    if (!(lbl_0300299C & 0xF0)) {
        if (lbl_030029AC & 1) {
            if (lbl_030032EC != 0) {
                if (win->unk2 != 0) {
                    lbl_030032EC = 0;
                    fn_0200B340();
                    fn_02003394(0, 0);
                    fn_020033F4();
                    w = fn_02003464(fn_0201A9DC(21), 2);
                    x = (144 - w) >> 1;
                    fn_0200B294(fn_0201A9DC(21), x);
                } else {
                    lbl_03002780 = 1;
                    ret = 1;
                }
            } else {
                lbl_03002780 = -1;
                ret = 1;
            }
            m4aSongNumStart(2);
        } else if (lbl_030029AC & 2) {
            if (lbl_030032EC != 0) {
                lbl_030032EC = 0;
                m4aSongNumStart(3);
                fn_0200B340();
                fn_02003394(0, 0);
                fn_020033F4();
                w = fn_02003464(fn_0201A9DC(21), 2);
                x = (144 - w) >> 1;
                fn_0200B294(fn_0201A9DC(21), x);
            } else {
                m4aSongNumStart(0);
            }
        }
    }
    return ret;
}

void fn_0200E184(void)
{
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    fn_020093B4(0, 0);

    lbl_030030B0[1].unk0 = 1;
    lbl_030030B0[1].unk2 = 0;
    lbl_030030B0[1].unk10 = 5;
    lbl_030030B0[1].unk12 = 3;
    lbl_030030B0[1].unkE = 6;
    lbl_030030B0[1].unk14 = 14;
    lbl_030030B0[1].unk16 = 14;
    lbl_030030B0[1].unk3 = 0;
    lbl_030030B0[1].unk4 = 0;
    lbl_030030B0[1].unk5 = 0;
    lbl_030030B0[1].unk6 = 1;
    lbl_030030B0[1].unk7 = 0;
    fn_02009B80(&lbl_030030B0[1], 1);

    lbl_030030B0[2].unk0 = 1;
    lbl_030030B0[2].unk2 = 2;
    lbl_030030B0[2].unk10 = 2;
    lbl_030030B0[2].unk12 = 2;
    lbl_030030B0[2].unkE = lbl_03002CA0.unk5D;
    lbl_030030B0[2].unk14 = 14;
    lbl_030030B0[2].unk16 = lbl_030030B0[2].unkE * 2;
    lbl_030030B0[2].unk3 = 16;
    lbl_030030B0[2].unk4 = 0;
    lbl_030030B0[2].unk5 = 2;
    lbl_030030B0[2].unk6 = 2;
    lbl_030030B0[2].unk7 = 0;

    fn_02003394(1, 0);
    fn_020033F4();
    fn_020037C8(4, 0, 0);
    fn_020037C8(5, 0, 0);
    fn_020037C8(6, 2, 0);
    fn_02003890(0x050000E0, 1);
    fn_020038D8(0x06000000);
    fn_020041D4(17, 0);
    fn_020041D4(3, 0);
    fn_02004098(17, 0, 0, 0);
    fn_02004098(3, 1, 1, 0);
    fn_02004098(19, 2, 2, -1);

    lbl_030027B8 = 0;
    lbl_030027BD = 0;
    lbl_030027BC = 0;
    lbl_030030A4 = 0;
    lbl_030032EC = 0;
    fn_0200EB80();
    fn_02009DA8(2, 1);
    fn_02009CBC(2, 1, 7);
    lbl_03002AEC &= ~0x200;
    lbl_030027BE = 0;
    lbl_030027BF = 0;
    lbl_030030AC = 1;
}
