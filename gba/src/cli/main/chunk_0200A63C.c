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
    s8 unk0;
    u8 unk1[0x107];
    s32 unk108[3];
    s32 unk114[3];
};

struct Unk03002FB0 {
    char unk0[17];
    s8 unk11;
    u8 unk12[2];
    u8 unk14[4];
    u8 unk18[4];
};

extern s8 lbl_03002774;
extern s8 lbl_03002780;
extern s8 lbl_03002782[2];
extern char lbl_03002788[17];
extern s8 lbl_03002799;
extern s8 lbl_0300279A;
extern s8 lbl_0300279B;
extern char *lbl_0202FB94[];
extern s8 lbl_030027AC;
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
extern s32 lbl_030032F4;

void *memset(void *, int, u32);
u32 strlen(const char *);
void *memcpy(void *, const void *, u32);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
void m4aSongNumStart(u16);
u16 *fn_02000A40(s32, s32, s32);
void fn_02000F00(const char *, s32, char *);
s32 fn_02000F48(const char *, s32);
s32 fn_02000F60(const char *);
void fn_02000A74(void);
void fn_02001578(void);
s32 fn_02001604(void);
void fn_02003190(u8 *);
void fn_02003200(s32);
void fn_02003238(void);
void fn_02003394(s32, s32);
void fn_020033F4(void);
s32 fn_02003464(const char *, s32);
void fn_020037A8(u32, s32);
void fn_020037C8(s32, s32, s32);
void fn_02003890(u32, s32);
void fn_020038D8(u32);
void fn_020038F4(s32);
void fn_0200391C(s32, s32, s32);
void fn_02003C3C(s32, s32, s32, s32, s32, s32, s32);
s32 fn_02004030(s32, s32);
void fn_02004098(s32, s32, s32, s32);
void fn_020041D4(s32, s32);
void fn_02004320(s32);
void fn_02005968(struct Window *);
void fn_020059D4(struct Window *, s32, s32);
void fn_02005A50(struct Window *);
void fn_02008178(struct Window *);
void fn_02008E88(s32, s32, s32, s32, s32, s32);
void fn_020091D4(void);
s32 fn_02009280(void);
s32 fn_020092C4(void);
s32 fn_020092E8(void);
u32 fn_02009340(struct Window *, s32, s32);
void fn_02009AB8(s32, s32, s32, s32, s32);
void fn_02009CBC(s32, s32, s32);
void fn_02009D68(s32, s32);
void fn_02009DA8(s32, s32);
char *fn_0201A73C(s32);
char *fn_0201A8A4(s32);
char *fn_0201A9DC(s32);
char *fn_0201AAAC(s32);
void fn_0201AB88(s32, char *);

void fn_0200A700(s32 idx, s32 row);
s32 fn_0200A758(s32 idx);
void fn_0200A7EC(void);
void fn_0200AD90(void);
s32 fn_0200AECC(void);
void fn_0200B164(void);
void fn_0200B294(char *str, s32 x);
void fn_0200B340(void);
void fn_0200B390(s32 mode);
void fn_0200B444(void);
s32 fn_0200B4B0(void);
void fn_0200B4B4(char *str);
void fn_0200B518(void);
void fn_0200B560(void);
void fn_0200B874(void);
s32 fn_0200B8C8(void);

void fn_0200A63C(void)
{
    struct Window *win = &lbl_03003120;
    s32 i;
    s32 n;
    s32 word;
    s32 bit;
    s32 pal;

    for (i = 0; i < win->unkE; i++) {
        n = lbl_03002774 + i;
        word = n >> 5;
        bit = n % 32;
        if (((lbl_03002CA0.unk108[word] ^ lbl_03002CA0.unk114[word]) >> bit) & 1) {
            fn_0200A700(n, n % win->unkE);
            pal = fn_0200A758(n) ? 5 : 6;
            fn_02009AB8(1, win->unk5, n % win->unkE, i, pal);
        }
    }
}

void fn_0200A700(s32 idx, s32 row)
{
    char *str;

    fn_02003394(1, 0);
    fn_020033F4();
    fn_020038F4(24);
    if (fn_0200A758(idx))
        str = fn_0201AAAC(idx + 159);
    else
        str = fn_0201A73C(41);
    fn_02003464(str, 0);
    fn_020037A8(fn_02009340(&lbl_03003120, row, 0), lbl_03003120.unk14);
}

s32 fn_0200A758(s32 idx)
{
    s32 word = idx >> 5;
    s32 bit = idx % 32;
    s32 flag = lbl_03002CA0.unk108[word] & (1 << bit);

    if (flag)
        flag = 1;
    return flag;
}

void fn_0200A790(void)
{
    struct Window *win;
    char buf[68];
    s32 n;
    char *str;

    fn_02003394(0, 0);
    fn_020033F4();
    win = &lbl_03003120;
    n = lbl_03002774 + win->unk2;
    if (fn_0200A758(n)) {
        fn_0201AB88(n + 159, buf);
        str = buf;
    } else {
        str = fn_0201A73C(0);
    }
    fn_02003464(str, 0);
    fn_02009D68(1, 1);
}

void fn_0200A7EC(void)
{
    struct Window *win;
    s32 x;
    s32 i;
    u8 buf[20];

    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);

    lbl_030030B0[0].unk0 = 1;
    lbl_030030B0[0].unk10 = 1;
    lbl_030030B0[0].unk12 = 3;
    lbl_030030B0[0].unkE = 6;
    lbl_030030B0[0].unk14 = 28;
    lbl_030030B0[0].unk16 = 15;
    lbl_030030B0[0].unk3 = 8;
    lbl_030030B0[0].unk4 = 0;
    lbl_030030B0[0].unk5 = 2;
    lbl_030030B0[0].unk6 = 0;
    lbl_030030B0[0].unk7 = 0;

    lbl_030030B0[1].unk0 = 1;
    lbl_030030B0[1].unk10 = 20;
    lbl_030030B0[1].unk12 = 15;
    lbl_030030B0[1].unkE = 3;
    lbl_030030B0[1].unk14 = 9;
    lbl_030030B0[1].unk16 = 3;
    lbl_030030B0[1].unk3 = 3;
    lbl_030030B0[1].unk4 = 0;
    lbl_030030B0[1].unk5 = 1;
    lbl_030030B0[1].unk6 = 2;
    lbl_030030B0[1].unk7 = 0;

    for (i = 0; i < lbl_030030B0[0].unkE; i++) {
        lbl_030030B0[0].items[i].unk0 = 1;
        lbl_030030B0[0].items[i].unk4 = fn_0201A73C(0);
    }
    for (i = 0; i < lbl_030030B0[1].unkE; i++) {
        lbl_030030B0[1].items[i].unk0 = 1;
        lbl_030030B0[1].items[i].unk4 = fn_0201A73C(0);
    }
    lbl_030030B0[4].items[0].unk0 = 1;
    lbl_030030B0[4].items[0].unk4 = fn_0201A8A4(0);

    fn_020091D4();
    fn_02003394(1, 0);
    fn_020037C8(3, 0, 0);
    fn_02003890(0x050000E0, 0);
    fn_02003890(0x05000100, 2);
    fn_02003890(0x05000120, 1);
    fn_020041D4(11, 0);
    fn_020041D4(12, 0);
    fn_020041D4(6, 0);
    fn_020041D4(18, 0);
    fn_020041D4(20, 0);
    fn_02004098(11, 0, 2, 0);
    fn_02004098(6, 2, 1, 0);
    fn_02004098(12, 4, 0, 0);
    fn_020038D8(0x06008000);
    fn_02003394(1, 1);
    fn_020037C8(15, 0, 1);
    fn_020038D8(0x06006000);
    fn_02003394(0, 0);
    fn_020033F4();
    x = (lbl_030030B0[1].unk14 * 8 - fn_02003464(fn_0201A9DC(0), 2)) >> 1;
    fn_020038F4(x);
    fn_02003464(fn_0201A9DC(0), 0);
    fn_0200391C(1, 14, 0);
    fn_02009DA8(2, 1);
    fn_02009CBC(2, 1, 9);

    lbl_03002780 = 0;
    lbl_03002799 = 0;
    lbl_0300279B = 0;
    lbl_030027AC = 0;
    memset(lbl_03002788, 0, 17);
    strcpy(lbl_03002788, lbl_03002FB0.unk0);
    lbl_0300279A = fn_02000F60(lbl_03002788);
    if (lbl_0300279A == 0) {
        lbl_03002782[1] = 0;
        lbl_03002782[0] = 0;
    } else {
        lbl_03002782[0] = 11;
        lbl_03002782[1] = 5;
    }
    memset(buf, 0, 17);
    fn_02003190(buf);
    fn_02003394(0, 0);
    fn_020033F4();

    win = &lbl_03003120;
    x = win->unk5;
    win->unk5 = 0;
    for (i = 2; i >= 0; i--)
        fn_02005968(win);
    win->unk5 = x;

    lbl_030030A4 = 0;
    lbl_030032EC = 0;
    lbl_030030AC = 1;
}

s32 fn_0200AAC8(void)
{
    s32 ret = 0;
    struct Window *win = lbl_030030B0;

    if (lbl_030030AC == 0)
        fn_0200A7EC();
    fn_02003394(0, 0);
    fn_020033F4();
    fn_02005968(win);
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
            fn_0200B4B4(lbl_03002788);
            ret = 1;
        }
    }
    if ((win->unk1 >> 3) == 1) {
        s32 x;

        fn_02003394(0, 0);
        fn_020033F4();
        x = (144 - fn_02003464(fn_0201A9DC(1), 2)) >> 1;
        fn_0200B294(fn_0201A9DC(1), x);
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 fn_0200AB8C(void)
{
    s32 ret = 0;
    s32 i;
    s32 x;
    s32 y;

    if (lbl_030030A4 == 0) {
        if (lbl_030027AC == 0) {
            ret = fn_0200AECC();
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
            lbl_030027AC = 0;
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
                lbl_030030A4 = 0;
        }
        ret = 0;
    }
    fn_0200B518();
    fn_0200B164();
    fn_0200AD90();
    fn_02008E88(2, 8, 7, 20, 0, 1);
    x = lbl_030030B0[1].unk10 * 8;
    y = lbl_030030B0[1].unk12 * 8 + 5;
    for (i = 0; i <= 4; i++, x += 16)
        fn_02003C3C(x, y, 22, i, 0, 1, 0);
    if (ret)
        fn_02009DA8(2, 1);
    return ret;
}

s32 fn_0200ACC4(void)
{
    s32 ret = 0;
    struct Window *win = lbl_030030B0;

    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win->unk1 = 0;
        fn_0200B340();
        fn_02009DA8(2, 1);
        strcpy(lbl_03002FB0.unk0, lbl_03002788);
        if (lbl_03002780 < 0) {
            fn_02004320(11);
            fn_02004320(6);
            fn_02004320(12);
            fn_02004320(18);
            fn_02004320(20);
            fn_02003238();
            ret = -1;
        } else {
            ret = 1;
        }
    }
    if (ret == 0) {
        win = &lbl_03003120;
        fn_02008178(win);
        if ((win->unk1 >> 3) < win->unk16 - 1)
            win->unk1 += 8;
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

void fn_0200AD90(void)
{
    s32 x;
    s32 y;
    s32 id;

    if (lbl_030032F4 != 1)
        return;
    if (lbl_03002AC8 & 0x20) {
        fn_02003C3C(8, 112, 0, 40, fn_02004030(0, 40), 1, 0);
        fn_02003C3C(216, 112, 0, 41, fn_02004030(0, 41), 1, 0);
    }
    if (lbl_0300279B > 4 && lbl_030030A4 == 0) {
        struct Window *win;

        id = 45;
        win = lbl_030030B0;
        if (lbl_03002782[1] == 5 && lbl_03002782[0] > 9) {
            x = win[1].unk10 * 8 - 18;
            y = win[1].unk12 * 8 + 5;
        } else {
            x = (win->unk10 + lbl_03002782[0] * 2) * 8;
            x -= 2;
            y = (win->unk12 + 2 + lbl_03002782[1] * 2) * 8;
        }
        fn_02003C3C(x, y, 0, id, fn_02004030(0, id), 0, 0);
        if (lbl_0300279A != 7 && (lbl_03002AC8 & 4)) {
            x = lbl_0300279A * 16 + 68;
            fn_02003C3C(x, 136, 2, 5, fn_02004030(2, 5), 1, 0x20000000);
        }
    }
}

s32 fn_0200AECC(void)
{
    s32 ret;
    s32 i;
    s32 len;

    if (lbl_0300299C == 0 || lbl_0300279B <= 4)
        return 0;
    ret = 0;
    if (lbl_0300299C & 0x20) {
        if (lbl_03002782[1] <= 4) {
            if (lbl_03002782[0] <= 0)
                lbl_03002782[0] = 11;
            else
                lbl_03002782[0]--;
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    } else if (lbl_0300299C & 0x10) {
        if (lbl_03002782[1] <= 4) {
            if (lbl_03002782[0] > 10)
                lbl_03002782[0] = 0;
            else
                lbl_03002782[0]++;
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    }
    if (lbl_0300299C & 0x40) {
        if (lbl_03002782[1] <= 0) {
            if (lbl_03002782[0] > 9)
                lbl_03002782[1] = 5;
            else
                lbl_03002782[1] = 4;
        } else {
            lbl_03002782[1]--;
        }
        m4aSongNumStart(1);
    } else if (lbl_0300299C & 0x80) {
        if (lbl_03002782[1] >= 4) {
            if (lbl_03002782[1] == 4 && lbl_03002782[0] > 9)
                lbl_03002782[1]++;
            else
                lbl_03002782[1] = 0;
        } else {
            lbl_03002782[1]++;
        }
        m4aSongNumStart(1);
    }
    if (lbl_0300299C & 0xF0)
        return ret;
    if (lbl_030029AC & 8) {
        lbl_03002782[0] = 11;
        lbl_03002782[1] = 5;
        m4aSongNumStart(2);
    } else if (lbl_030029AC & 0x200) {
        if (lbl_03002799 <= 0)
            lbl_03002799 = 2;
        else
            lbl_03002799--;
        lbl_0300279B = 0;
        m4aSongNumStart(6);
    } else if (lbl_030029AC & 0x100) {
        if (lbl_03002799 > 1)
            lbl_03002799 = 0;
        else
            lbl_03002799++;
        lbl_0300279B = 0;
        m4aSongNumStart(6);
    } else if (lbl_030029AC & 1) {
        if (lbl_03002782[1] > 4) {
            if (lbl_0300279A == 0) {
                m4aSongNumStart(0);
            } else {
                len = strlen(lbl_03002788);
                for (i = 0; i < len && lbl_03002788[i] == ' '; i++)
                    ;
                if (i >= len) {
                    lbl_030030A4 = 1;
                    m4aSongNumStart(0);
                } else {
                    lbl_03002780 = 0;
                    fn_02003190((u8 *)lbl_03002788);
                    lbl_030027AC = 1;
                    fn_02001578();
                    lbl_03002AF4 = 1;
                    m4aSongNumStart(2);
                }
            }
        } else if (lbl_0300279A > 6 && fn_0200B4B0() == 0) {
            m4aSongNumStart(0);
        } else {
            m4aSongNumStart(2);
            fn_0200B390(0);
        }
    } else if (lbl_030029AC & 2) {
        if (lbl_0300279A != 0) {
            fn_0200B444();
        } else {
            lbl_03002780 = -1;
            ret = 1;
        }
        m4aSongNumStart(3);
    }
    return ret;
}

void fn_0200B164(void)
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

    if (lbl_0300279B <= 4) {
        fn_02003394(0, 0);
        fn_020033F4();
        str = lbl_0202FB94[lbl_03002799 * 5 + lbl_0300279B];
        for (i = 0; i < 12; i++) {
            fn_02000F00(str, i, ch);
            fn_020038F4(i * 16);
            fn_02003464(ch, 0);
        }
        memcpy(&win, lbl_030030B0, sizeof(struct Window));
        win.unk5--;
        fn_020059D4(&win, lbl_0300279B, 0);
        for (i = 0; i < sizeof(buf) / sizeof(u16); i++)
            buf[i] = 0x3FF;
        n = 24;
        tile = win.unk14 * (lbl_0300279B * 2) + 128;
        pal = 0x7000;
        for (i = 0; i < n; i++) {
            buf[i] = tile++ | pal;
            buf[i + 30] = tile++ | pal;
        }
        x = win.unk10 + 2;
        y = win.unk12 + 2 + lbl_0300279B * 2;
        dst = fn_02000A40(win.unk5, x, y);
        DmaSet(DMA3, buf, dst, 0x80000000 | n);
        DmaSet(DMA3, buf + 30, dst + 32, 0x80000000 | n);
        lbl_0300279B++;
    }
}

void fn_0200B294(char *str, s32 x)
{
    u16 buf[60];
    s32 n;
    s32 i;
    u32 size;
    s32 tile;
    s32 pal;
    u16 *dst;

    fn_02003394(0, 0);
    fn_020033F4();
    fn_020038F4(x);
    fn_02003464(str, 0);
    n = 20;
    dst = (u16 *)0x06005380;
    fn_020037A8((u32)dst, n);
    for (i = 0; i < sizeof(buf) / sizeof(u16); i++)
        buf[i] = 0x3FF;
    tile = 0x29C;
    pal = 0x9000;
    size = n * sizeof(u16);
    for (i = 0; i < n; i++) {
        buf[i] = tile++ | pal;
        buf[i + 30] = tile++ | pal;
    }
    dst = fn_02000A40(1, 2, 2);
    DmaCopy16(DMA3, buf, dst, size);
    DmaCopy16(DMA3, buf + 30, dst + 32, size);
}

void fn_0200B340(void)
{
    u16 buf[60];
    s32 i;
    s32 n;
    u16 *dst;

    n = 20;
    for (i = 0; i < sizeof(buf) / sizeof(u16); i++)
        buf[i] = 0x3FF;
    dst = fn_02000A40(1, 2, 2);
    DmaCopy16(DMA3, buf, dst, n * sizeof(u16));
    DmaCopy16(DMA3, buf + 30, dst + 32, n * sizeof(u16));
}

void fn_0200B390(s32 mode)
{
    char ch[4];
    char prev[4];

    memset(ch, 0, 3);
    memset(prev, 0, 3);
    if (mode == 0) {
        char *str = lbl_0202FB94[lbl_03002799 * 5 + lbl_03002782[1]];

        fn_02000F00(str, lbl_03002782[0], ch);
        fn_02000F48(lbl_03002788, lbl_0300279A - 1);
        fn_02000F00(lbl_03002788, lbl_0300279A - 1, prev);
        strcat(lbl_03002788, ch);
        lbl_0300279A++;
    }
    fn_02003394(0, 0);
    fn_020033F4();
    fn_0200B4B4(lbl_03002788);
    if (lbl_0300279A > 6) {
        lbl_03002782[0] = 11;
        lbl_03002782[1] = 5;
    }
}

void fn_0200B444(void)
{
    char ch[4];
    s32 wide;
    s32 len;

    memset(ch, 0, 3);
    wide = fn_02000F48(lbl_03002788, lbl_0300279A - 1);
    len = strlen(lbl_03002788);
    if (wide)
        lbl_03002788[len - 2] = 0;
    else
        lbl_03002788[len - 1] = 0;
    lbl_0300279A--;
    fn_02003394(0, 0);
    fn_020033F4();
    fn_0200B4B4(lbl_03002788);
}

s32 fn_0200B4B0(void)
{
    return 0;
}

void fn_0200B4B4(char *str)
{
    char ch[4];
    s32 i;

    fn_02003394(0, 0);
    fn_020033F4();
    fn_020038F4(56);
    for (i = 0; i < lbl_0300279A; i++) {
        fn_02000F00(str, i, ch);
        fn_020038F4(56 + i * 16);
        fn_02003464(ch, 0);
    }
    fn_02009D68(2, 1);
}

void fn_0200B518(void)
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
        fn_02003C3C(x, y, 20, id, 0, 3, 0);
    }
}

void fn_0200B560(void)
{
    s32 i;

    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    lbl_030030B0[0].unk0 = 1;
    lbl_030030B0[0].unk10 = 9;
    lbl_030030B0[0].unk12 = 7;
    lbl_030030B0[0].unkE = 2;
    lbl_030030B0[0].unk14 = 14;
    lbl_030030B0[0].unk16 = 7;
    lbl_030030B0[0].unk3 = 8;
    lbl_030030B0[0].unk4 = 0;
    lbl_030030B0[0].unk5 = 2;
    lbl_030030B0[0].unk6 = 0;
    lbl_030030B0[0].unk7 = 0;
    for (i = 0; i < lbl_030030B0[0].unkE; i++) {
        lbl_030030B0[0].items[i].unk0 = 1;
        lbl_030030B0[0].items[i].unk4 = fn_0201A73C(0);
    }
    if (lbl_03002FB0.unk11 & 0x80)
        lbl_030030B0[0].unk2 = 1;
    lbl_03002780 = 0;
    lbl_030030AC = 1;
    fn_02000A74();
}

s32 fn_0200B614(void)
{
    struct Window tmp;
    u16 buf[60];
    s32 ret = 0;
    struct Window *win = lbl_030030B0;
    s32 row;
    s32 n;
    s32 i;
    s32 tile;
    s32 pal;
    u16 *p;
    u16 *map;

    if (lbl_030030AC == 0)
        fn_0200B560();
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
    if (ret == 0 && !(row & 1) && (n = row >> 1) <= 2) {
        fn_020033F4();
        row = n - 1;
        memcpy(&tmp, win, sizeof(struct Window));
        tmp.unk5--;
        fn_020038F4(36);
        fn_02003464(fn_0201A9DC(n + 6), 0);
        fn_020059D4(&tmp, row, 0);
        p = buf;
        for (i = 0; i < sizeof(buf) / sizeof(u16); i++)
            buf[i] = 0x3FF;
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
        row = (144 - fn_02003464(fn_0201A9DC(2), 2)) >> 1;
        fn_0200B294(fn_0201A9DC(2), row);
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 fn_0200B7BC(void)
{
    s32 ret = fn_0200B8C8();

    fn_0200B874();
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

s32 fn_0200B7E8(void)
{
    s32 ret = 0;
    struct Window *win = lbl_030030B0;

    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        win->unk1 = 0;
        fn_0200B340();
        if (lbl_03002780 < 0) {
            ret = -1;
        } else {
            ret = 1;
            lbl_03002FB0.unk11 &= 0x7F;
            if (win->unk2)
                lbl_03002FB0.unk11 |= 0x80;
        }
    }
    fn_02008E88(2, 8, 7, 20, 0, 1);
    return ret;
}

void fn_0200B874(void)
{
    s32 x;
    s32 y;

    if (lbl_030032F4 == 1) {
        x = (lbl_030030B0[0].unk10 + 2) * 8;
        y = (lbl_030030B0[0].unk12 + 1) * 8 + lbl_030030B0[0].unk2 * 16;
        fn_02003C3C(x, y, 0, 45, fn_02004030(0, 45), 1, 0);
    }
}

s32 fn_0200B8C8(void)
{
    struct Window *win;
    s32 ret;

    if (lbl_0300299C == 0)
        return 0;
    win = lbl_030030B0;
    ret = 0;
    if (lbl_0300299C & 0xC0) {
        win->unk2 ^= 1;
        m4aSongNumStart(1);
    } else if (lbl_030029AC & 1) {
        m4aSongNumStart(2);
        lbl_03002780 = 1;
        ret = 1;
    } else if (lbl_030029AC & 2) {
        m4aSongNumStart(3);
        lbl_03002780 = -1;
        ret = 1;
    }
    return ret;
}

void fn_0200B944(void)
{
    s32 i;

    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    lbl_030030B0[0].unk0 = 1;
    lbl_030030B0[0].unk10 = 2;
    lbl_030030B0[0].unk12 = 6;
    lbl_030030B0[0].unkE = 4;
    lbl_030030B0[0].unk14 = 12;
    lbl_030030B0[0].unk16 = 11;
    lbl_030030B0[0].unk3 = 8;
    lbl_030030B0[0].unk4 = 0;
    lbl_030030B0[0].unk5 = 2;
    lbl_030030B0[0].unk6 = 0;
    lbl_030030B0[0].unk7 = 0;
    memcpy(&lbl_030030B0[1], &lbl_030030B0[0], sizeof(struct Window));
    lbl_030030B0[1].unk10 += lbl_030030B0[0].unk14 + 1;
    lbl_030030B0[1].unk12 = 6;
    lbl_030030B0[1].unkE = 4;
    lbl_030030B0[1].unk14 = 13;
    for (i = 0; i < lbl_030030B0[0].unkE; i++) {
        lbl_030030B0[0].items[i].unk0 = 1;
        lbl_030030B0[0].items[i].unk4 = fn_0201A73C(0);
    }
    for (i = 0; i < lbl_030030B0[1].unkE; i++) {
        lbl_030030B0[1].items[i].unk0 = 1;
        lbl_030030B0[1].items[i].unk4 = fn_0201A73C(0);
    }
    lbl_030030B0[0].unk2 = lbl_03002FB0.unk11 & 3;
    lbl_030030B0[1].unk2 = (lbl_03002FB0.unk11 >> 2) & 3;
    lbl_030030B0[4].items[0].unk0 = 1;
    lbl_030030B0[4].items[0].unk4 = fn_0201A8A4(1);
    fn_020091D4();
    lbl_03002780 = 0;
    lbl_030027AC = 0;
    fn_02003200(0xFF);
    lbl_030030AC = 1;
    fn_02000A74();
}
