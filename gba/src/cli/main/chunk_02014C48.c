#include "gba_types.h"

#define DMA0 0x040000B0

#define ABS(x) ((x) < 0 ? -(x) : (x))

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

struct Work {
    s8 unk0;
    u8 unk1[3];
    u8 unk4[4];
    u8 unk8[4];
    char names[4][18];
    u8 unk54[8];
    u8 unk5C;
    u8 unk5D;
    u8 unk5E[4];
    u8 unk62[2];
    s16 unk64[64];
    s16 unkE4[8];
    u16 unkF4[8];
    union {
        u32 word;
        u8 bytes[4];
    } unk104;
    u8 unk108[12];
    u8 unk114[12];
    s16 unk120[4];
    u8 unk128;
    u8 unk129;
};

struct Command {
    s8 unk0;
    u8 unk1;
    s16 unk2;
};

struct ItemInfo {
    u8 unk0;
    s8 unk1[3];
    s16 unk4;
    s16 unk6;
};

struct MarkerEntry {
    u8 unk0;
    u8 unk1[3];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
};

struct MarkerList {
    u8 count;
    u32 unk4;
    struct MarkerEntry entries[32];
};

struct Flag3 {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
};

extern struct ItemInfo lbl_0203A800[];
extern s8 lbl_030027FC;
extern u32 lbl_03002800;
extern u8 lbl_03002804;
extern s16 lbl_03002806;
extern s8 lbl_03002808;
extern s8 lbl_03002809;
extern s8 lbl_0300280C;
extern s8 lbl_0300280D;
extern struct Command lbl_03002810;
extern s8 lbl_03002814;
extern u8 lbl_03002998;
extern u16 lbl_0300299C;
extern u16 lbl_030029AC;
extern u8 lbl_03002ACC;
extern u16 lbl_03002AEC;
extern u8 lbl_03002AF4;
extern s8 lbl_03002AFC;
extern s8 lbl_03002B00;
extern struct MarkerList lbl_03002B10;
extern struct Work lbl_03002CA0;
extern struct Command lbl_03002DCC;
extern struct Flag3 lbl_03002DD0[64];
extern struct Flag3 lbl_03002EE0[16];
extern s8 lbl_03003098;
extern s8 lbl_0300309C;
extern s32 lbl_030030A4;
extern s32 lbl_030030AC;
extern struct Window lbl_030030B0[];
extern struct Window lbl_03003120;
extern s8 lbl_030032E0;
extern u16 lbl_030032E4;
extern s32 lbl_030032EC;
extern u8 lbl_030032FC[];

void *memset(void *, s32, u32);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
void m4aSongNumStart(u16);
void fn_02000AD4(u8 mask, u16 x, u16 y);
void fn_02000CF0(s32 value, s32 x, s32 digits);
void fn_02001578(void);
s32 fn_02001604(void);
s32 fn_02002FAC(void);
s32 fn_02002FE4(u8, u8, u8);
void fn_0200314C(u8 a, u32 b);
void fn_02003394(s32, s32);
void fn_020033F4(void);
s32 fn_02003464(const char *, s32);
void fn_020037C8(s32, s32, s32);
void fn_02003890(u32, s32);
void fn_020038D8(u32);
void fn_020038F4(s32);
s32 fn_02003910(void);
void fn_02003C3C(s32 x, s32 y, s32 id, s32 frame, s32 pal, s32 prio, u32 flags);
s32 fn_02004030(s32, s32);
void fn_02004098(s32, s32, s32, s32);
void fn_020041D4(s32, s32);
void fn_02004320(s32);
void fn_020045F4(s16 *, s16 *);
struct Flag3 *fn_020046F0(int idx);
void fn_02005968(struct Window *);
void fn_020059D4(struct Window *, s32, s32);
void fn_02005A50(struct Window *);
void fn_02008178(struct Window *);
void fn_02008F8C(s32 x, s32 y, s32 len, s32 pal, u32 value, s32 color);
void fn_020093B4(s32 idx, s32 bg);
s32 fn_02009414(s32 idx);
void fn_020095AC(s32 idx);
void fn_020095FC(s32 idx);
void fn_02009684(s32 idx, s32 pal);
void fn_0200974C(s32 bg);
void fn_02009B80(struct Window *win, s32 val);
void fn_02013BB8(s32, u32);
char *fn_0201A73C(s32);
char *fn_0201A90C(s32);
char *fn_0201AAAC(s32);
char *fn_0201AB20(s32);

void fn_02015438(void);
void fn_020154E0(void);
s32 fn_02015788(void);
s32 fn_020157FC(void);
void fn_0201583C(void);
void fn_02015BE4(void);
void fn_02015DF4(void);
void fn_02015E34(s32);
void fn_02015E48(void);
void fn_02015FF8(void);
s32 fn_02016044(void);

void fn_02014C48(void)
{
    s16 x, y;
    s32 left, top, right, bottom;
    s32 i;

    if (lbl_03002B10.count == 0)
        return;
    fn_020045F4(&x, &y);
    left = x - 80;
    top = y - 64;
    right = x + 80;
    bottom = y + 64;
    for (i = 0; i < lbl_03002B10.count; i++) {
        s32 frame = lbl_03002B10.entries[i].unk0;
        s32 dx, dy, n, stepx, stepy, ox, oy;

        if (!(lbl_03002B10.unk4 & (1 << i)))
            continue;
        dx = lbl_03002B10.entries[i].unk8 - lbl_03002B10.entries[i].unk4;
        dy = lbl_03002B10.entries[i].unkA - lbl_03002B10.entries[i].unk6;
        if (ABS(dx) >= ABS(dy)) {
            n = ABS(dx) >> 3;
            stepx = 8;
            stepy = dy / n;
            if ((ABS(dx) & 7) > 3)
                n++;
        } else {
            n = ABS(dy) >> 3;
            stepx = dx / n;
            stepy = 8;
            if ((ABS(dy) & 7) > 3)
                n++;
        }
        n++;
        if (n <= 0)
            continue;
        oy = 0;
        ox = 0;
        do {
            x = lbl_03002B10.entries[i].unk4 + ox;
            y = lbl_03002B10.entries[i].unk6 + oy;
            if (x >= left && right >= x && y >= top && bottom >= y) {
                x -= left;
                y -= top;
                fn_02003C3C(x - 4, y - 4, 2, frame, fn_02004030(2, frame), 2, 0);
            }
            oy += stepy;
            ox += stepx;
        } while (--n != 0);
    }
}

void fn_02014DE8(void)
{
    s32 i;
    s16 frame = 8;

    for (i = 0; i <= 3; i++, frame++) {
        struct Flag3 *p = fn_020046F0(i);

        if (p->unk0) {
            s16 x = p->unk1 + 76;
            s16 y = p->unk2 + 60;

            fn_02003C3C(x, y, 2, frame, fn_02004030(2, frame), 2, 0);
        }
    }
}

void fn_02014E64(void)
{
    s32 i;

    for (i = 0; i < 64; i++) {
        u8 type = lbl_03002DD0[i].unk3;

        if (lbl_03002DD0[i].unk0 && (u8)(type - 1) < 3) {
            s16 x = lbl_03002DD0[i].unk1 + 76;
            s16 y = lbl_03002DD0[i].unk2 + 60;
            s32 frame = lbl_03002DD0[i].unk3 + 15;

            fn_02003C3C(x, y, 2, frame, fn_02004030(2, frame), 2, 0);
        }
    }
}

void fn_02014ED8(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        if (lbl_03002EE0[i].unk0 && (u8)(lbl_03002EE0[i].unk3 - 4) < 2) {
            s16 x = lbl_03002EE0[i].unk1 + 76;
            s16 y = lbl_03002EE0[i].unk2 + 60;
            s32 frame = lbl_03002EE0[i].unk3 + 2;

            fn_02003C3C(x, y, 2, frame, fn_02004030(2, frame), 2, 0);
        }
    }
}

void fn_02014F4C(void)
{
    s32 i;
    u32 div;
    s32 ret;

    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    lbl_030030B0[0].unk0 = 1;
    lbl_030030B0[0].unk10 = 17;
    lbl_030030B0[0].unk12 = 3;
    lbl_030030B0[0].unkE = 4;
    lbl_030030B0[0].unk14 = 12;
    lbl_030030B0[0].unk16 = 8;
    lbl_030030B0[0].unk3 = 6;
    lbl_030030B0[0].unk4 = 0;
    lbl_030030B0[0].unk5 = 2;
    lbl_030030B0[0].unk6 = 0;
    lbl_030030B0[0].unk7 = 0;
    fn_02009B80(&lbl_030030B0[0], 1);

    lbl_030030B0[1].unk0 = 1;
    lbl_030030B0[1].unk14 = 9;
    lbl_030030B0[1].unk10 = lbl_030030B0[0].unk10 - 9;
    lbl_030030B0[1].unk12 = 10;
    lbl_030030B0[1].unkE = 2;
    lbl_030030B0[1].unk16 = lbl_030030B0[1].unkE * 2 + 2;
    lbl_030030B0[1].unk3 = 3;
    lbl_030030B0[1].unk4 = 0;
    lbl_030030B0[1].unk5 = 2;
    lbl_030030B0[1].unk6 = 1;
    lbl_030030B0[1].unk7 = 16;
    fn_02009B80(&lbl_030030B0[1], 1);
    for (i = 0; i < lbl_030030B0[1].unkE; i++) {
        if (i == 0 && (lbl_030032E4 & 0x100))
            lbl_030030B0[1].items[i].unk0 = 0;
        else
            lbl_030030B0[1].items[i].unk0 = 1;
        if (i == 0)
            lbl_030030B0[1].items[0].unk4 = fn_0201A73C(34);
        else
            lbl_030030B0[1].items[i].unk4 = fn_0201A73C(4);
    }

    fn_020037C8(3, 0, 0);
    fn_02003890(0x050000E0, 0);
    fn_02003890(0x05000100, 2);
    fn_020041D4(9, 0);
    fn_020041D4(6, 0);
    fn_02004098(9, 0, 2, 0);
    fn_02004098(6, 1, 2, 0);
    fn_020038D8(0x06008400);
    lbl_03002800 = 0;
    for (i = 1, div = 10; i <= 7 && lbl_03002CA0.unk104.word / div != 0; i++, div *= 10)
        ;
    lbl_03002804 = i;
    ret = (lbl_030030B0[0].unk14 * 8 - 80) >> 1;
    lbl_03002806 = lbl_030030B0[0].unk10 * 8 + ret + 56;
    lbl_030032EC = 0;
    lbl_030030A4 = 0;
    lbl_03002809 = 0;
    lbl_03002808 = 0;
    for (i = 0; i <= 9; i++) {
        ret = fn_02002FE4(21, 0, 0);
        if (ret == 0)
            break;
    }
    lbl_030027FC = i <= 9;
    lbl_030030AC = 1;
}

s32 fn_02015170(void)
{
    struct Window *win;
    s32 ret = 0;

    if (lbl_030030AC == 0)
        fn_02014F4C();
    fn_02003394(1, 0);
    fn_020033F4();
    win = lbl_030030B0;
    fn_02005968(win);
    fn_02005A50(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        win->unk1 = 0;
        ret = 1;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

s32 fn_020151C8(void)
{
    struct Window *win;
    s32 x;
    s32 i;
    s32 ret;

    if (lbl_030027FC == 0) {
        for (i = 0; i <= 9; i++) {
            ret = fn_02002FE4(21, 0, 0);
            if (ret == 0)
                break;
        }
        if (i > 9) {
            if (lbl_030029AC & 1) {
                m4aSongNumStart(0);
            } else if (lbl_030029AC & 2) {
                lbl_03002808 = 1;
                lbl_030032E0 = 1;
                m4aSongNumStart(3);
                return 1;
            } else if (lbl_030029AC & 0x300) {
                if (lbl_030029AC & 0x100)
                    lbl_03003098 = 1;
                else
                    lbl_03003098 = -1;
                ret = 1;
                lbl_03002808 = ret;
                m4aSongNumStart(6);
                return ret;
            }
            return 0;
        }
        lbl_030027FC = 1;
    }
    if (lbl_03002CA0.unk104.word < lbl_03002800)
        lbl_03002800 = lbl_03002CA0.unk104.word;
    if (lbl_030032EC && lbl_030030A4 == 0) {
        ret = fn_02015788();
        if (ret) {
            lbl_030030A4++;
            lbl_030030B0[1].unk1 = 0;
        }
    } else if (!lbl_030032EC || (lbl_030030A4 == 1 && lbl_03002809 == 0)) {
        if (lbl_03002ACC)
            fn_020154E0();
    } else if (lbl_030030A4 == 1) {
        u16 key = lbl_03002AEC & 0x8000;

        if (key) {
            if (lbl_03002AFC)
                lbl_03002809 = 0;
            else
                lbl_030030A4 = 2;
            lbl_03002800 = 0;
            fn_02001578();
        } else if (fn_02001604()) {
            m4aSongNumStart(0);
            lbl_03002809 = key;
            fn_02001578();
            lbl_03002800 = key;
        }
    } else {
        ret = fn_020157FC();
        if (ret) {
            lbl_030030A4 = 0;
            lbl_030030B0[1].unk1 = 0;
            lbl_030032EC = 0;
        }
    }
    if (lbl_03002ACC)
        fn_02015438();
    win = lbl_030030B0;
    x = win->unk10 * 8;
    ret = (win->unk12 + 1) * 8;
    fn_02008F8C(x, ret, win->unk14, win->unk5, lbl_03002CA0.unk104.word, -1);
    ret = (win->unk12 + 4) * 8;
    fn_02008F8C(x, ret, win->unk14, win->unk5, lbl_03002800, 4);
    ret = lbl_03002808 != 0;
    return ret;
}

s32 fn_020153EC(void)
{
    s32 ret = 0;
    struct Window *win = lbl_030030B0;

    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        ret = 1;
        win->unk1 = 0;
        fn_02004320(9);
        fn_02004320(6);
    } else {
        win->unk1 += 8;
    }
    return ret;
}

void fn_02015438(void)
{
    struct Window *win;
    s32 x, y;

    if (lbl_030032EC == 0) {
        win = lbl_030030B0;
        x = lbl_03002806 - win->unk2 * 8;
        y = (win->unk12 + win->unk16 - 2) * 8;
        fn_02003C3C(x, y, 2, 5, fn_02004030(2, 5), win->unk5, 0);
    } else if (lbl_030030A4 == 1) {
        win = &lbl_03003120;
        x = win->unk10 * 8 - 8;
        y = (win->unk12 + 1) * 8;
        y += win->unk2 * 16;
        fn_02003C3C(x, y, 0, 45, fn_02004030(0, 45), 1, 0);
    }
}

void fn_020154E0(void)
{
    if (lbl_0300299C == 0)
        return;
    if (lbl_030032EC == 0) {
        if (lbl_03002CA0.unk104.word != 0) {
            struct Window *win = lbl_030030B0;
            u32 step = 1;
            s32 i;

            for (i = 0; i < win->unk2; i++)
                step *= 10;
            if (lbl_0300299C & 0x40) {
                if (lbl_03002CA0.unk104.word >= lbl_03002800 + step)
                    lbl_03002800 += step;
                else
                    lbl_03002800 = 0;
                m4aSongNumStart(1);
            } else if (lbl_0300299C & 0x80) {
                s32 val = lbl_03002800 - step;

                if (val < 0)
                    val = lbl_03002CA0.unk104.word;
                lbl_03002800 = val;
                m4aSongNumStart(1);
            }
            if (lbl_0300299C & 0x20) {
                if (win->unk2 < lbl_03002804 - 1) {
                    win->unk2++;
                    m4aSongNumStart(1);
                } else {
                    m4aSongNumStart(0);
                }
            } else if (lbl_0300299C & 0x10) {
                if (win->unk2 != 0) {
                    win->unk2--;
                    m4aSongNumStart(1);
                } else {
                    m4aSongNumStart(0);
                }
            }
        }
        if (lbl_0300299C & 0xF0)
            return;
        if (lbl_030029AC & 1) {
            if ((s32)lbl_03002800 > 0) {
                if (lbl_0300309C) {
                    fn_02013BB8(1, lbl_03002800);
                    lbl_03002808 = 1;
                } else {
                    lbl_030032EC = 1;
                    lbl_030030A4 = 0;
                }
                m4aSongNumStart(2);
            } else {
                m4aSongNumStart(0);
            }
        } else if (lbl_030029AC & 2) {
            if (lbl_0300309C)
                fn_02013BB8(0, 0);
            else
                lbl_030032E0 = 1;
            lbl_03002808 = 1;
            m4aSongNumStart(3);
        } else if (lbl_030029AC & 0x300) {
            if (lbl_0300309C) {
                m4aSongNumStart(0);
            } else {
                if (lbl_030029AC & 0x100)
                    lbl_03003098 = 1;
                else
                    lbl_03003098 = -1;
                m4aSongNumStart(6);
                lbl_03002808 = 1;
            }
        }
    } else {
        struct Window *win = &lbl_03003120;

        if (lbl_0300299C & 0xC0) {
            win->unk2 ^= 1;
            m4aSongNumStart(1);
        }
        if (lbl_0300299C & 0xC0)
            return;
        if (lbl_030029AC & 1) {
            if (win->unk2 < win->unkE - 1) {
                fn_0200314C(1, lbl_03002800);
                lbl_03002809 = 1;
                fn_02001578();
                lbl_03002AF4 = 1;
            } else {
                lbl_030030A4++;
            }
            m4aSongNumStart(2);
        } else if (lbl_030029AC & 2) {
            lbl_030030A4++;
            m4aSongNumStart(3);
        } else if (lbl_030029AC & 0x300) {
            m4aSongNumStart(0);
        }
    }
}

s32 fn_02015788(void)
{
    struct Window *win = &lbl_03003120;
    s32 row;
    s32 ret;

    fn_02003394(0, 0);
    fn_020033F4();
    row = win->unk1 >> 3;
    if (row < win->unkE) {
        win->unk5--;
        fn_02003464(win->items[row].unk4, 0);
        fn_020059D4(win, row, 0);
        win->unk5++;
    }
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        lbl_03002809 = 0;
        ret = 1;
    }
    win->unk1 += 8;
    return ret;
}

s32 fn_020157FC(void)
{
    s32 ret = 0;
    struct Window *win = &lbl_03003120;

    fn_02003394(0, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        lbl_03002809 = 0;
        ret = 1;
    }
    win->unk1 += 8;
    return ret;
}

void fn_0201583C(void)
{
    lbl_030030A4 = 0;
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    fn_020093B4(0, 0);
    lbl_030030B0[1].unk0 = 1;
    lbl_030030B0[1].unk2 = 0;
    lbl_030030B0[1].unk10 = 1;
    lbl_030030B0[1].unk12 = 0;
    lbl_030030B0[1].unkE = 7;
    lbl_030030B0[1].unk14 = 18;
    lbl_030030B0[1].unk16 = lbl_030030B0[1].unk14 - 2;
    lbl_030030B0[1].unk3 = 4;
    lbl_030030B0[1].unk4 = 0;
    lbl_030030B0[1].unk5 = 2;
    lbl_030030B0[1].unk6 = 1;
    lbl_030030B0[1].unk7 = 0;
    fn_02009B80(&lbl_030030B0[1], 1);
    fn_02003394(1, 0);
    fn_020037C8(4, 0, 0);
    fn_02003890(0x050000E0, 1);
    fn_02003890(0x05000100, 0);
    fn_02003890(0x05000120, fn_02002FAC() + 5);
    fn_020038D8(0x06000000);
    fn_020041D4(17, 0);
    fn_020041D4(7, 0);
    fn_02004098(17, 0, 0, 0);
    fn_02004098(7, 1, 2, 0);
    fn_020095FC(3);
    lbl_0300280C = 0;
    fn_02015DF4();
    memset(&lbl_03002810, 0xFF, sizeof(lbl_03002810));
    lbl_030030AC = 1;
}

s32 fn_02015960(void)
{
    struct Window *win;
    s32 ret;

    fn_02003394(1, 0);
    if (lbl_030030AC == 0) {
        fn_0201583C();
        if (lbl_030030AC == 0)
            return 0;
    }
    fn_02009414(0);
    win = &lbl_03003120;
    fn_02003394(0, 0);
    fn_020033F4();
    win->unk5--;
    fn_02005968(win);
    win->unk5++;
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        ret = 1;
        win->unk1 = 0;
        fn_02009684(3, 9);
    } else {
        win->unk1 += 8;
    }
    return ret;
}

s32 fn_020159E4(void)
{
    struct Window *win;

    fn_020095AC(0);
    win = &lbl_03003120;
    if (lbl_0300280D == 0) {
        if (lbl_030029AC & 0x300) {
            if (lbl_030029AC & 0x100)
                lbl_03003098 = 1;
            else
                lbl_03003098 = -1;
            m4aSongNumStart(6);
            fn_0200974C(lbl_030030B0[3].unk5);
            return 1;
        }
        if (lbl_030029AC & 1) {
            m4aSongNumStart(0);
            return 0;
        }
        if (lbl_030029AC & 2) {
            lbl_030032E0 = 1;
            m4aSongNumStart(3);
            return 1;
        }
        return 0;
    }
    if (lbl_03002B00) {
        s32 reset;

        if (lbl_03002DCC.unk0 < 0 || lbl_03002810.unk0 != lbl_03002DCC.unk0 || lbl_0300280C < win->unkE)
            reset = 1;
        else
            reset = 0;
        lbl_03002810 = lbl_03002DCC;
        if (reset) {
            fn_02015DF4();
            lbl_0300280C = 0;
        } else {
            lbl_0300280C = 1;
            fn_02015BE4();
            lbl_0300280C = win->unkE;
        }
        lbl_03002B00 = 0;
    }
    fn_02015BE4();
    fn_02003394(1, 0);
    if (lbl_03002ACC == 0)
        return 0;
    if (lbl_030029AC & 0x300) {
        if (lbl_030029AC & 0x100)
            lbl_03003098 = 1;
        else
            lbl_03003098 = -1;
        fn_0200974C(lbl_030030B0[3].unk5);
        return 1;
    }
    if (lbl_030029AC & 1) {
        m4aSongNumStart(0);
    } else if (lbl_030029AC & 2) {
        lbl_030032E0 = 1;
        m4aSongNumStart(3);
        return 1;
    }
    return 0;
}

s32 fn_02015B78(void)
{
    struct Window *win;
    s32 ret;

    fn_02015E34(0);
    win = lbl_030030B0;
    ret = 0;
    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) < win->unk16 - 1)
        win->unk1 += 8;
    win++;
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        ret = 1;
        fn_02004320(17);
        fn_02004320(7);
        win->unk1 = 0;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

void fn_02015BE4(void)
{
    struct Window *win = &lbl_03003120;
    struct ItemInfo *item;
    char buf[68];
    s32 idx;
    s32 row;
    s32 x;
    s32 n;
    s32 pal;

    fn_02003394(0, 0);
    fn_020033F4();
    idx = lbl_03002810.unk0;
    if (idx < 0)
        return;
    item = &lbl_0203A800[idx];
    row = lbl_0300280C;
    if (row >= win->unkE)
        return;
    if (row == 0) {
        fn_02003464(fn_0201AB20(item->unk0), 0);
    } else if (row == 1) {
        x = win->unk14 * 8 - 86;
        x = x - fn_02003464(fn_0201A73C(18), 3) - 8;
        x -= fn_02003464(fn_0201A73C(30), 2);
        fn_020038F4(x);
        fn_02003464(fn_0201A73C(30), 0);
        x = fn_02003910();
        if (item->unk0 != 154) {
            fn_02000CF0(lbl_03002810.unk2, x + 8, 3);
        } else {
            fn_020038F4(x + 8);
            fn_02003464(fn_0201A73C(41), 0);
        }
        fn_02003464(fn_0201A73C(18), 0);
        x = fn_02003910();
        if (item->unk0 != 154) {
            fn_02000CF0(item->unk4, x + 8, 3);
        } else {
            fn_020038F4(x + 8);
            fn_02003464(fn_0201A73C(41), 0);
        }
    } else if (row <= 4) {
        if (item->unk1[0] >= 0 && lbl_0203A800[idx].unk1[row - 2] >= 0) {
            if (item->unk1[0] <= 1) {
                n = item->unk1[0] * 2;
                if (row == 2) {
                    strcpy(buf, fn_0201A73C(31));
                    strcat(buf, fn_0201A90C(n));
                    fn_02003464(buf, 0);
                } else if (row == 3) {
                    strcpy(buf, fn_0201A73C(31));
                    strcat(buf, fn_0201A90C(n + 1));
                    fn_02003464(buf, 0);
                }
            } else {
                n = lbl_0203A800[idx].unk1[row - 2];
                if (n >= 0) {
                    strcpy(buf, fn_0201A73C(31));
                    strcat(buf, fn_0201A90C(n + 3));
                    fn_02003464(buf, 0);
                }
            }
        }
    } else if (row == 5) {
        strcpy(buf, fn_0201A73C(31));
        strcat(buf, fn_0201A73C(32));
        fn_02003464(buf, 0);
    } else {
        fn_020038F4(24);
        n = item->unk6;
        if (n < 0)
            fn_02003464(fn_0201A73C(41), 0);
        else if (n == 0)
            fn_02003464(fn_0201A73C(62), 0);
        else
            fn_02003464(fn_0201AAAC(n), 0);
    }
    pal = win->unk5;
    win->unk5--;
    fn_020059D4(win, lbl_0300280C, 0);
    win->unk5 = pal;
    lbl_0300280C++;
}

void fn_02015DF4(void)
{
    struct Window *win = &lbl_03003120;
    s32 i;

    fn_02003394(0, 0);
    fn_020033F4();
    win->unk5--;
    for (i = 0; i < win->unkE; i++)
        fn_020059D4(win, i, 0);
    win->unk5++;
}

void fn_02015E34(s32 mode)
{
    lbl_0300280D = mode;
    fn_02015DF4();
}

void fn_02015E48(void)
{
    s32 i;

    fn_02000AD4(15, 0, 0);
    lbl_030030A4 = 0;
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    lbl_030030B0[0].unk0 = 1;
    lbl_030030B0[0].unk2 = lbl_030032FC[0];
    lbl_030030B0[0].unk10 = 20;
    lbl_030030B0[0].unk12 = 1;
    lbl_030030B0[0].unkE = 3;
    lbl_030030B0[0].unk14 = 9;
    lbl_030030B0[0].unk16 = 8;
    lbl_030030B0[0].unk3 = 1;
    lbl_030030B0[0].unk4 = 0;
    lbl_030030B0[0].unk5 = 2;
    lbl_030030B0[0].unk6 = 0;
    lbl_030030B0[0].unk7 = 0;
    lbl_030032EC = 0;
    for (i = 0; i < lbl_030030B0[0].unkE; i++) {
        lbl_030030B0[0].items[i].unk0 = 1;
        if (i <= 1)
            lbl_030030B0[0].items[i].unk4 = fn_0201A73C(i + 11);
        else
            lbl_030030B0[0].items[i].unk4 = fn_0201A73C(4);
    }
    fn_020037C8(3, 0, 0);
    fn_020037C8(4, 2, 0);
    fn_020038D8(0x06008000);
    fn_020041D4(4, 0);
    fn_02004098(4, 0, 2, 0);
    lbl_03002814 = 0;
    lbl_030030AC = 1;
}

s32 fn_02015F2C(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    if (lbl_030030AC == 0)
        fn_02015E48();
    win = lbl_030030B0;
    fn_02003394(1, 0);
    fn_020033F4();
    fn_02005968(win);
    fn_02005A50(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2)
        ret = 1;
    win->unk1 += 8;
    return ret;
}

s32 fn_02015F84(void)
{
    s32 ret;

    fn_02003394(1, 0);
    ret = 0;
    if (lbl_03002ACC) {
        ret = fn_02016044();
        fn_02015FF8();
    }
    return ret;
}

s32 fn_02015FB0(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    fn_020033F4();
    win = lbl_030030B0;
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        ret = lbl_03002814;
        fn_02004320(4);
    }
    win->unk1 += 8;
    return ret;
}

void fn_02015FF8(void)
{
    struct Window *win = lbl_030030B0;
    s32 x = (win->unk10 - 1) * 8;
    s32 y = (win->unk12 + 1) * 8;

    y += win->unk2 * 16;
    fn_02003C3C(x, y, 0, 45, fn_02004030(0, 45), 2, 0);
}

s32 fn_02016044(void)
{
    struct Window *win;
    s32 ret;

    if (lbl_0300299C == 0)
        return 0;
    ret = 0;
    win = lbl_030030B0;
    if (lbl_0300299C & 0x40) {
        if (win->unk2 != 0)
            win->unk2--;
        else
            win->unk2 = win->unkE - 1;
        m4aSongNumStart(1);
    } else if (lbl_0300299C & 0x80) {
        if (win->unk2 < win->unkE - 1)
            win->unk2++;
        else
            win->unk2 = 0;
        m4aSongNumStart(1);
    }
    if (lbl_0300299C & 0xC0)
        return ret;
    if (lbl_030029AC & 1) {
        if (win->unk2 == win->unkE - 1) {
            lbl_03002814 = -1;
            lbl_03002998 = 6;
            fn_02002FE4(7, 0, 0);
        } else if (win->unk2 == 0) {
            lbl_03002814 = 1;
        } else {
            lbl_03002814 = 1;
        }
        ret = 1;
        m4aSongNumStart(2);
    }
    if (lbl_030029AC & 2) {
        lbl_03002998 = 6;
        lbl_03002814 = -1;
        ret = 1;
        fn_02002FE4(7, 0, 0);
        m4aSongNumStart(3);
    }
    return ret;
}
