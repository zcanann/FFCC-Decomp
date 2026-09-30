#include "gba_types.h"

#define NULL ((void *)0)

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

#define DmaCopy16(dmaAddr, src, dst, size) DmaSet(dmaAddr, src, dst, 0x80000000 | ((size) >> 1))

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

struct Entry {
    u32 unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
};

struct EntryList {
    s32 count;
    s32 unk4;
};

extern s8 lbl_030027D9;
extern s8 lbl_030027DA;
extern s8 lbl_030027DB;
extern u8 lbl_030027DC;
extern s16 lbl_030027E0;
extern s8 lbl_030027E4;
extern s8 lbl_030027E5;
extern s8 lbl_030027E6;
extern s8 lbl_030027E7;
extern u8 lbl_030027E9;
extern u32 lbl_030027EC;
extern u16 lbl_0300299C;
extern u16 lbl_030029AC;
extern u8 lbl_03002ACC;
extern u16 lbl_03002AEC;
extern u8 lbl_03002AF4;
extern s8 lbl_03002AFC;
extern u8 lbl_03002C98;
extern s8 lbl_03003098;
extern u8 lbl_030032E0;
extern struct Window lbl_030030B0[];
extern struct EntryList lbl_0203A800;
extern struct Entry lbl_0203A810[];
extern char lbl_0203D800[];
extern const char lbl_0201D044[];
extern const char lbl_0201D048[];
extern const char lbl_0201D04C[];

void *memset(void *, s32, u32);
void *memcpy(void *, const void *, u32);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
u32 strlen(const char *);
char *strchr(const char *, s32);
void m4aSongNumStart(u16);
u16 *fn_02000A40(s32, s32, s32);
void fn_02000D9C(char *, s32);
void fn_02001578(void);
s32 fn_02001604(void);
s32 fn_02002FB8(u8, u8);
s32 fn_02002FE4(u8, u8, u8);
s32 fn_02003014(u8, s8, u8, u32);
void fn_02003394(s32, s32);
void fn_020033F4(void);
s32 fn_02003464(const char *, s32);
void fn_020038D8(u32);
void fn_020038F4(s32);
s32 fn_02003910(void);
void fn_02003C3C(s32, s32, s32, s32, s32, s32, s32);
s32 fn_02004030(s32, s32);
void fn_02004098(s32, s32, s32, s32);
void fn_020041D4(s32, s32);
void fn_02004320(s32);
void fn_02005968(struct Window *);
void fn_020059D4(struct Window *, s32, s32);
void fn_02005A50(struct Window *);
void fn_02008178(struct Window *);
s32 fn_02013B1C(const char *);
char *fn_0201A73C(s32);
char *fn_0201AA44(s32);
char *fn_0201AAAC(s32);

void fn_02013410(s32, s32);
void fn_020134C8(s32, s32, s32, s32);
s32 fn_0201354C(s32);
void fn_0201357C(s32);
void fn_0201361C(s32, s32);

s32 fn_02012364(void)
{
    struct Entry *entry = &lbl_0203A810[lbl_030027E0];
    struct Window *win = lbl_030030B0;
    s32 ret = 0;

    if (lbl_03002ACC) {
        if (lbl_030027E5 == 0) {
            if (lbl_0300299C & 0xC0) {
                if (win->unk2 == win->unkE - 1)
                    win->unk2--;
                else
                    win->unk2++;
                m4aSongNumStart(1);
            }
            if (!(lbl_0300299C & 0xC0)) {
                if (lbl_030029AC & 1) {
                    if (win->unk2 >= win->unkE - 1) {
                        lbl_030027E5 = -1;
                        ret = 1;
                    } else if (fn_02003014(lbl_030027E0, lbl_030027E6, (lbl_030027E9 & 0x10) != 0, lbl_030027EC) == 0) {
                        lbl_030027E5 = 1;
                        fn_02001578();
                        lbl_03002AF4 = 1;
                    }
                    m4aSongNumStart(2);
                } else if (lbl_030029AC & 2) {
                    lbl_030027E5 = -1;
                    ret = 1;
                    m4aSongNumStart(3);
                } else if (lbl_030029AC & 0x300) {
                    m4aSongNumStart(0);
                }
            }
        } else if (lbl_03002AEC & 0x8000) {
            if (lbl_03002AFC == 0) {
                entry->unk6 |= 4;
                lbl_030027E7 = 0;
                ret = 1;
            } else {
                lbl_030027E7 = 1;
                ret = 1;
            }
        } else if (fn_02001604()) {
            lbl_030027E7 = 1;
            ret = 1;
        }
        fn_0201361C((win->unk10 + 1) * 8 - 2, (win->unk12 + 1) * 8 + win->unk2 * 16);
    }
    return ret;
}

s32 fn_0201250C(void)
{
    struct Window *win;
    s32 ret;

    if (lbl_030027E7)
        return 1;
    win = lbl_030030B0;
    fn_02008178(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        ret = 1;
        win->unk1 = 0;
        fn_02004320(3);
    }
    return ret;
}

s32 fn_02012558(void)
{
    struct Window *win = &lbl_030030B0[1];
    s32 w;
    s32 i;
    s32 ret;

    if (lbl_030027DA == 0) {
        memset(win, 0, sizeof(struct Window));
        fn_020041D4(12, 0);
        fn_02004098(12, 2, 0, 0);
        fn_020038D8(0x06000800);
        fn_02003394(1, 1);
        fn_020033F4();
        fn_02003464(fn_0201AA44(10), 0);
        w = fn_02003910();
        w = (w & 7) ? (w >> 3) + 1 : w >> 3;
        win->unk0 = 1;
        win->unk10 = (28 - w) >> 1;
        win->unk12 = 7;
        win->unkE = 1;
        win->unk14 = w + 2;
        win->unk16 = 4;
        win->unk3 = 9;
        win->unk4 = 0;
        win->unk5 = 0;
        win->unk6 = 2;
        win->unk7 = 0;
        for (i = 0; i < win->unkE; i++) {
            win->items[i].unk0 = 1;
            win->items[i].unk4 = fn_0201A73C(0);
        }
        fn_020059D4(win, 0, 0);
        lbl_030027E7 = 0;
        lbl_030027DA = 1;
        m4aSongNumStart(0);
    }
    fn_02003394(1, 1);
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        ret = 1;
        win->unk1 = 0;
    }
    return ret;
}

s32 fn_02012670(void)
{
    s32 ret = 0;

    if (lbl_03002ACC && (lbl_030029AC & 3)) {
        ret = 1;
        m4aSongNumStart(2);
    }
    return ret;
}

s32 fn_020126A0(void)
{
    struct Window *win = &lbl_030030B0[1];
    s32 ret;

    fn_02008178(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        ret = 1;
        fn_02004320(12);
        win->unk1 = 0;
    }
    return ret;
}

s32 fn_020126D8(void)
{
    char buf[256];
    s32 mode = lbl_03002C98 & 15;
    struct Window *win = &lbl_030030B0[1];
    struct Entry *entry;
    s32 w;
    s32 i;
    s32 ret;

    if (lbl_030027DB == 0) {
        memset(win, 0, sizeof(struct Window));
        entry = &lbl_0203A810[lbl_030027E0];
        memset(buf, 0, sizeof(buf));
        if (mode != 1)
            strcpy(buf, fn_0201AA44(0));
        if (entry->unk6 & 8) {
            if (mode == 1)
                strcat(buf, fn_0201AA44(2));
            strcat(buf, fn_0201AAAC(entry->unk0));
            if (mode == 1)
                strcat(buf, fn_0201AA44(3));
        } else {
            w = strlen(buf);
            fn_02000D9C(buf + w, entry->unk0);
            strcat(buf, lbl_0201D044);
            strcat(buf, fn_0201A73C(5));
        }
        if (mode == 1)
            strcat(buf, fn_0201AA44(0));
        else
            strcat(buf, lbl_0201D048);
        fn_02003394(1, 1);
        fn_020033F4();
        fn_02003464(buf, 0);
        w = fn_02003910();
        w = (w & 7) ? (w >> 3) + 1 : w >> 3;
        win->unk0 = 1;
        win->unk2 = 1;
        win->unk10 = (28 - w) >> 1;
        win->unk12 = 4;
        win->unkE = 3;
        win->unk14 = w + 2;
        win->unk16 = 8;
        win->unk3 = 9;
        win->unk4 = 0;
        win->unk5 = 0;
        win->unk6 = 2;
        win->unk7 = 0;
        for (i = 0; i < win->unkE; i++) {
            win->items[i].unk0 = 1;
            win->items[i].unk4 = fn_0201A73C(0);
        }
        fn_020059D4(win, 0, 0);
        lbl_030027E4 = 0;
        lbl_030027E7 = 0;
        lbl_030027DB = 1;
    }
    fn_02003394(1, 1);
    w = win->unk1 >> 3;
    if (w == 1 || w == 2) {
        fn_020033F4();
        fn_020038F4(16);
        fn_02003464(fn_0201A73C(w + 1), 0);
        fn_020059D4(win, w, 0);
    }
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        ret = 1;
        win->unk1 = 0;
    }
    return ret;
}

s32 fn_020128D0(void)
{
    s32 ret = 0;
    struct Entry *entry = &lbl_0203A810[lbl_030027E0];
    struct Window *win;

    if (lbl_03002ACC) {
        win = &lbl_030030B0[1];
        if (lbl_0300299C && lbl_030027E5 == 0) {
            if (lbl_0300299C & 0x40) {
                if (win->unk2 > 1)
                    win->unk2--;
                else
                    win->unk2 = win->unkE - 1;
                m4aSongNumStart(1);
            } else if (lbl_0300299C & 0x80) {
                if (win->unk2 < win->unkE - 1)
                    win->unk2++;
                else
                    win->unk2 = 1;
                m4aSongNumStart(1);
            }
            if (!(lbl_0300299C & 0xC0)) {
                if (lbl_030029AC & 1) {
                    if (win->unk2 == 1) {
                        if (fn_02002FE4(0, lbl_030027E0, 0) == 0) {
                            lbl_030027E5 = 1;
                            fn_02001578();
                            lbl_03002AF4 = 1;
                        }
                    } else {
                        lbl_030027E5 = -1;
                    }
                    m4aSongNumStart(2);
                } else if (lbl_030029AC & 2) {
                    lbl_030027E5 = -1;
                    m4aSongNumStart(3);
                } else if (lbl_030029AC & 0x300) {
                    m4aSongNumStart(0);
                }
                if (lbl_030027E5 < 0)
                    ret = 1;
            }
        } else if (lbl_030027E5) {
            if (lbl_03002AEC & 0x8000) {
                if (lbl_03002AFC) {
                    lbl_030027E5 = -1;
                    lbl_030027E7 = 1;
                } else {
                    entry->unk6 |= 2;
                    lbl_030027E7 = 0;
                }
                ret = 1;
            } else if (fn_02001604()) {
                lbl_030027E5 = -1;
                lbl_030027E7 = 1;
                ret = 1;
            }
        }
        fn_0201361C((win->unk10 + 1) * 8 - 2, (win->unk12 + 1) * 8 + win->unk2 * 16);
    }
    if (ret)
        fn_02001578();
    return ret;
}

s32 fn_02012ABC(void)
{
    struct Window *win = &lbl_030030B0[1];
    s32 ret;

    fn_02008178(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        ret = 1;
        win->unk1 = 0;
    }
    return ret;
}

s32 fn_02012AF0(void)
{
    char buf[256];
    struct Window *win = &lbl_030030B0[1];
    struct Entry *entry;
    char *str;
    s32 w;
    s32 w2;
    s32 i;
    s32 ret;

    if (lbl_030027DB == 0) {
        memset(win, 0, sizeof(struct Window));
        memset(buf, 0, sizeof(buf));
        entry = &lbl_0203A810[lbl_030027E0];
        if (!(lbl_03002C98 & 15))
            strcat(buf, fn_0201AA44(8));
        if (entry->unk6 & 8) {
            strcat(buf, fn_0201AAAC(entry->unk0));
        } else {
            w = strlen(buf);
            fn_02000D9C(buf + w, entry->unk0);
            strcat(buf, lbl_0201D044);
            strcat(buf, fn_0201A73C(5));
        }
        if (!(lbl_03002C98 & 15))
            strcat(buf, lbl_0201D04C);
        fn_02003394(1, 1);
        fn_020033F4();
        if (lbl_03002C98 & 15) {
            w2 = fn_02003464(fn_0201AA44(9), 2);
            str = buf;
        } else {
            w2 = fn_02003464(buf, 2);
            str = fn_0201AA44(9);
        }
        fn_02003464(str, 0);
        w = fn_02003910();
        if (w < w2)
            w = w2;
        w = (w & 7) ? (w >> 3) + 1 : w >> 3;
        win->unk0 = 1;
        win->unk2 = 1;
        win->unk10 = (28 - w) >> 1;
        win->unk12 = 5;
        win->unkE = 2;
        win->unk14 = w + 2;
        win->unk16 = 6;
        win->unk3 = 9;
        win->unk4 = 0;
        win->unk5 = 0;
        win->unk6 = 2;
        win->unk7 = 0;
        for (i = 0; i < win->unkE; i++) {
            win->items[i].unk0 = 1;
            win->items[i].unk4 = fn_0201A73C(0);
        }
        fn_020059D4(win, 0, 0);
        if (!(lbl_03002C98 & 15)) {
            fn_020033F4();
            fn_02003464(buf, 0);
            fn_020059D4(win, 1, 0);
        }
        lbl_030027E7 = 0;
        lbl_030027DB = 1;
        m4aSongNumStart(0);
    }
    fn_02003394(1, 1);
    w = win->unk1 >> 3;
    if (w == 1 && (lbl_03002C98 & 15)) {
        fn_020033F4();
        fn_02003464(fn_0201AA44(9), 0);
        fn_020059D4(win, 1, 0);
    }
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        ret = 1;
        win->unk1 = 0;
    }
    return ret;
}

s32 fn_02012D18(void)
{
    s32 ret = 0;

    if (lbl_03002ACC) {
        if (lbl_030029AC & 3) {
            ret = 1;
            m4aSongNumStart(2);
        } else if (lbl_030029AC & 0x300) {
            m4aSongNumStart(0);
        }
    }
    return ret;
}

s32 fn_02012D5C(void)
{
    struct Window *win = &lbl_030030B0[1];
    s32 ret;

    fn_02008178(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        ret = 1;
        win->unk1 = 0;
    }
    return ret;
}

s32 fn_02012D90(void)
{
    char buf[256];
    struct Window *win = &lbl_030030B0[1];
    char *str;
    char *nl;
    s32 w;
    s32 len;
    s32 i;
    s32 ret;
    s32 n;

    if (lbl_030027DB == 0) {
        memset(win, 0, sizeof(struct Window));
        str = lbl_0203D800;
        str += strlen(str);
        str++;
        lbl_030027E4 = fn_02013B1C(str);
        fn_02003394(1, 1);
        fn_020033F4();
        w = 0;
        for (i = 0; i < lbl_030027E4; i++) {
            memset(buf, 0, sizeof(buf));
            strcpy(buf, fn_0201AA44(2));
            nl = strchr(str, '\n');
            if (nl) {
                len = nl - str;
                memcpy(buf + strlen(buf), str, len);
                str = nl + 1;
            } else {
                strcat(buf, str);
            }
            strcat(buf, fn_0201AA44(3));
            if (i) {
                len = fn_02003464(buf, 2);
            } else {
                fn_02003464(buf, 0);
                len = fn_02003910();
            }
            if (w < len)
                w = len;
        }
        len = fn_02003464(fn_0201A73C(4), 2);
        if (w < len)
            w = len;
        w = (w & 7) ? (w >> 3) + 1 : w >> 3;
        win->unk0 = 1;
        if (lbl_030027E6 >= 0) {
            win->unk2 = lbl_030027E6;
            lbl_030027E6 = -1;
        }
        win->unk10 = (28 - w) >> 1;
        win->unk12 = 7 - lbl_030027E4;
        n = lbl_030027E4 + 1;
        win->unkE = n;
        win->unk14 = w + 2;
        win->unk16 = n * 2 + 2;
        win->unk3 = 9;
        win->unk4 = 0;
        win->unk5 = 0;
        win->unk6 = 2;
        win->unk7 = 0;
        for (i = 0; i < win->unkE; i++) {
            win->items[i].unk0 = 1;
            win->items[i].unk4 = fn_0201A73C(0);
        }
        fn_020059D4(win, 0, 0);
        lbl_030027E7 = 0;
        lbl_030027DB = 1;
    }
    fn_02003394(1, 1);
    w = win->unk1 >> 3;
    if (w != 0 && w < win->unkE) {
        fn_020033F4();
        if (w >= win->unkE - 1) {
            fn_02003464(fn_0201A73C(4), 0);
        } else {
            memset(buf, 0, sizeof(buf));
            str = &lbl_0203D800[strlen(lbl_0203D800) + 1];
            for (i = 0; i < w; i++) {
                nl = strchr(str, '\n');
                if (nl != NULL)
                    str = nl + 1;
                else
                    break;
            }
            strcpy(buf, fn_0201AA44(2));
            nl = strchr(str, '\n');
            if (nl) {
                len = nl - str;
                memcpy(buf + strlen(buf), str, len);
            } else {
                strcat(buf, str);
            }
            strcat(buf, fn_0201AA44(3));
            fn_02003464(buf, 0);
        }
        fn_020059D4(win, w, 0);
    }
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        ret = 1;
        win->unk1 = 0;
    }
    return ret;
}

s32 fn_0201304C(void)
{
    struct Window *win = &lbl_030030B0[1];
    s32 ret = 0;

    if (lbl_03002ACC) {
        if (lbl_0300299C) {
            if (lbl_0300299C & 0x40) {
                if (win->unk2 > 0)
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
            if (!(lbl_0300299C & 0xC0)) {
                if (lbl_030029AC & 1) {
                    if (win->unk2 >= win->unkE - 1) {
                        lbl_030027E5 = -1;
                    } else {
                        lbl_030027E5 = win->unk2;
                        lbl_030027E6 = win->unk2;
                    }
                    m4aSongNumStart(2);
                    ret = 1;
                } else if (lbl_030029AC & 2) {
                    lbl_030027E5 = -1;
                    ret = 1;
                    m4aSongNumStart(3);
                } else if (lbl_030029AC & 0x300) {
                    m4aSongNumStart(0);
                }
            }
        }
        fn_0201361C(win->unk10 * 8 - 10, (win->unk12 + 1) * 8 + win->unk2 * 16);
    }
    return ret;
}

s32 fn_0201316C(void)
{
    struct Window *win = &lbl_030030B0[1];
    s32 ret;

    fn_02008178(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        ret = 1;
        win->unk1 = 0;
    }
    return ret;
}

s32 fn_020131A0(void)
{
    struct Window *win = &lbl_030030B0[1];
    s32 w;
    s32 w2;
    s32 i;
    s32 ret;

    fn_02003394(1, 1);
    fn_020033F4();
    if (lbl_030027DB == 0) {
        memset(win, 0, sizeof(struct Window));
        w = fn_02003464(fn_0201AA44(1), 2);
        w2 = fn_02003464(fn_0201AA44(11), 2);
        if (w < w2)
            w = w2;
        w2 = fn_02003464(fn_0201AA44(12), 2);
        if (w < w2)
            w = w2;
        w2 = fn_02003464(fn_0201A73C(4), 2);
        if (w < w2)
            w = w2;
        w = (w & 7) ? (w >> 3) + 1 : w >> 3;
        win->unk0 = 1;
        win->unk2 = 0;
        win->unk10 = (28 - w) >> 1;
        win->unk12 = 4;
        win->unkE = 4;
        win->unk14 = w + 2;
        win->unk16 = 10;
        win->unk3 = 9;
        win->unk4 = 0;
        win->unk5 = 0;
        win->unk6 = 2;
        win->unk7 = 0;
        for (i = 0; i < win->unkE; i++)
            win->items[i].unk0 = 1;
        win->items[0].unk4 = fn_0201AA44(1);
        win->items[1].unk4 = fn_0201AA44(11);
        win->items[2].unk4 = fn_0201AA44(12);
        win->items[3].unk4 = fn_0201A73C(4);
        fn_020059D4(win, 0, 0);
        lbl_030027E7 = 0;
        lbl_030027DB = 1;
    }
    fn_02005968(win);
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        ret = 1;
        win->unk1 = 0;
    }
    return ret;
}

s32 fn_020132C8(void)
{
    struct Window *win = &lbl_030030B0[1];
    s32 ret = 0;

    if (lbl_03002ACC) {
        if (lbl_0300299C) {
            if (lbl_0300299C & 0x40) {
                if (win->unk2 > 0)
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
            if (!(lbl_0300299C & 0xC0)) {
                if (lbl_030029AC & 1) {
                    if (win->unk2 >= win->unkE - 1)
                        lbl_030027E5 = -1;
                    else
                        lbl_030027E5 = win->unk2;
                    m4aSongNumStart(2);
                    ret = 1;
                } else if (lbl_030029AC & 2) {
                    lbl_030027E5 = -1;
                    ret = 1;
                    m4aSongNumStart(3);
                } else if (lbl_030029AC & 0x300) {
                    m4aSongNumStart(0);
                }
            }
        }
        fn_0201361C(win->unk10 * 8 - 10, (win->unk12 + 1) * 8 + win->unk2 * 16);
    }
    return ret;
}

s32 fn_020133DC(void)
{
    struct Window *win = &lbl_030030B0[1];
    s32 ret;

    fn_02008178(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        ret = 1;
        win->unk1 = 0;
    }
    return ret;
}

void fn_02013410(s32 idx, s32 row)
{
    char buf[64];
    struct Window tmp;
    char *src;
    struct EntryList *list = &lbl_0203A800;
    struct Entry *entries = lbl_0203A810;
    char *names = (char *)(entries + list->count);
    char *descs = names + list->unk4 * 24;

    fn_02003394(0, 0);
    fn_020033F4();
    memset(buf, 0, sizeof(buf));
    src = names + entries[idx].unk4 * 24;
    memcpy(buf, src, 24);
    fn_02003464(buf, 0);
    fn_020038F4(120);
    memset(buf, 0, sizeof(buf));
    src = descs + entries[idx].unk5 * 16;
    memcpy(buf, src, 16);
    fn_02003464(buf, 0);
    memcpy(&tmp, lbl_030030B0, sizeof(struct Window));
    tmp.unk14 = 25;
    tmp.unk5--;
    fn_020059D4(&tmp, row, 0);
}

void fn_020134C8(s32 idx, s32 row, s32 n, s32 pal)
{
    u16 buf[60];
    s32 tile = idx * (n * 2) + 128;
    u16 *map;
    s32 i;
    u16 *bot;

    pal <<= 12;
    for (i = 0; i < n; i++) {
        buf[i] = tile++ | pal;
        buf[i + 30] = tile++ | pal;
    }
    bot = &buf[30];
    map = fn_02000A40(lbl_030030B0[0].unk5 - 1, 2, row * 2 + 1);
    DmaCopy16(DMA3, buf, map, n * 2);
    DmaCopy16(DMA3, bot, map + 32, n * 2);
}

s32 fn_0201354C(s32 idx)
{
    struct Entry *entry = &lbl_0203A810[idx];
    s32 pal;

    if (entry->unk6 & 4)
        pal = 8;
    else if (entry->unk6 & 1)
        pal = 7;
    else
        pal = 9;
    return pal;
}

void fn_0201357C(s32 up)
{
    s32 step = 64;
    s32 dstRow;
    s32 srcRow;
    u8 *dst;
    u8 *src;
    s32 i;
    s32 j;

    if (up) {
        srcRow = lbl_030030B0[0].unkE * 2;
        dstRow = srcRow - 2;
        step = -step;
    } else {
        dstRow = 3;
        srcRow = 1;
    }
    dst = (u8 *)fn_02000A40(lbl_030030B0[0].unk5 - 1, 2, dstRow);
    src = (u8 *)fn_02000A40(lbl_030030B0[0].unk5 - 1, 2, srcRow);
    for (i = 0; i < lbl_030030B0[0].unkE - 1; i++) {
        for (j = 0; j < 2; j++) {
            DmaSet(DMA0, dst, src, 0x80000019);
            dst += step;
            src += step;
        }
    }
}

void fn_0201361C(s32 x, s32 y)
{
    fn_02003C3C(x, y, 0, 45, fn_02004030(0, 45), 0, 0);
}

s32 fn_02013648(void)
{
    struct EntryList *list;
    struct Window *win;
    s32 ret;
    s32 pal;
    s32 row;
    s32 sel;

    if (lbl_0300299C == 0)
        return 0;
    list = &lbl_0203A800;
    win = lbl_030030B0;
    if (lbl_0300299C & 0x40) {
        if (win->unk2) {
            win->unk2--;
            m4aSongNumStart(1);
        } else if (lbl_030027DC) {
            fn_0201357C(1);
            row = lbl_030027DC - 1;
            pal = fn_0201354C(row);
            row = (lbl_030027DC - 1) % win->unkE;
            fn_02013410(lbl_030027DC - 1, row);
            fn_020134C8(row, 0, 25, pal);
            lbl_030027DC--;
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    } else if (lbl_0300299C & 0x80) {
        if (lbl_030027DC + win->unk2 + 1 < list->count) {
            if (win->unk2 + 1 < win->unkE) {
                win->unk2++;
            } else {
                fn_0201357C(0);
                row = win->unk2 + lbl_030027DC + 1;
                pal = fn_0201354C(row);
                row = (win->unk2 + lbl_030027DC + 1) % win->unkE;
                fn_02013410(win->unk2 + lbl_030027DC + 1, row);
                fn_020134C8(row, win->unkE - 1, 25, pal);
                lbl_030027DC++;
            }
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    }
    ret = 0;
    if (!(lbl_0300299C & 0xC0)) {
        if (lbl_030029AC & 2) {
            lbl_030027D9 = 1;
            lbl_030032E0 = 1;
            m4aSongNumStart(3);
            return 1;
        }
        if (lbl_030029AC & 1) {
            sel = win->unk2 + lbl_030027DC;
            if (sel < list->count) {
                lbl_030027E0 = sel;
                fn_02002FB8(2, sel);
                ret = 1;
                m4aSongNumStart(2);
            } else {
                m4aSongNumStart(0);
            }
        } else if (lbl_030029AC & 0x300) {
            if (lbl_030029AC & 0x100)
                lbl_03003098 = 1;
            else
                lbl_03003098 = -1;
            ret = 1;
            lbl_030027D9 = 1;
            m4aSongNumStart(6);
        }
    }
    return ret;
}
