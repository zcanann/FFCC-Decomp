#include "gba_types.h"

#define REG_DISPCNT (*(vu16 *)0x04000000)

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

struct Entry {
    u32 unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
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

extern u8 lbl_030027DC;
extern u8 lbl_030027DD;
extern s16 lbl_030027E0;
extern s8 lbl_030027E5;
extern s8 lbl_030027E6;
extern s8 lbl_030027E8;
extern u8 lbl_030027E9;
extern u32 lbl_030027EC;
extern s8 lbl_030027F0;
extern s8 lbl_030027F4;
extern u8 lbl_030027F5;
extern s8 lbl_030027F8;
extern u16 lbl_0300299C;
extern u16 lbl_030029AC;
extern u32 lbl_03002AC8;
extern u8 lbl_03002ACC;
extern u16 lbl_03002AEC;
extern u8 lbl_03002AF8;
extern u8 lbl_03002C98;
extern struct Work lbl_03002CA0;
extern u8 lbl_03002ED0;
extern u8 lbl_03002FF0;
extern s8 lbl_03003098;
extern s32 lbl_030030A4;
extern s32 lbl_030030AC;
extern struct Window lbl_030030B0[];
extern s8 lbl_030032E0;
extern s32 lbl_030032F4;
extern s32 lbl_0203A800[];
extern struct Entry lbl_0203A810[];
extern char lbl_0203D800[];
extern char lbl_0203D801[];
extern const char lbl_0201D044[];
extern const char lbl_0201D048[];

void *memset(void *, s32, u32);
void *memcpy(void *, const void *, u32);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
u32 strlen(const char *);
char *strchr(const char *, s32);
void m4aSongNumStart(u16);
void fn_020008D0(void);
u16 *fn_02000A40(s32, s32, s32);
void fn_02000D9C(char *, s32);
void fn_020017DC(void);
void fn_02001828(void);
void fn_020018C8(void);
void fn_0200194C(s32);
void fn_0200197C(void);
void fn_02001C44(s32, s32);
u8 fn_02002594(void);
s32 fn_02002FAC(void);
void fn_02003394(s32, s32);
void fn_020033F4(void);
s32 fn_02003464(const char *, s32);
void fn_020037A8(u32, s32);
void fn_020037C8(s32, s32, s32);
void fn_02003890(u32, s32);
void fn_020038D8(u32);
void fn_020038F4(s32);
s32 fn_02003910(void);
void fn_02003C3C(s32, s32, s32, s32, s32, s32, s32);
s32 fn_02004030(s32, s32);
void fn_02004098(s32, s32, s32, s32);
void fn_020041D4(s32, s32);
void fn_02004320(s32);
void fn_02004604(s16 *, s16 *);
s32 fn_02004D3C(s32);
void fn_02005968(struct Window *);
void fn_020059D4(struct Window *, s32, s32);
void fn_02005A50(struct Window *);
void fn_02008178(struct Window *);
u32 fn_02009340(struct Window *, s32, s32);
void fn_020093B4(s32, s32);
s32 fn_02009414(s32);
void fn_020095AC(s32);
void fn_020095FC(s32);
void fn_02009684(s32, s32);
void fn_0200974C(s32);
void fn_02009A14(s32, s32, s32);
void fn_02009AB8(s32, s32, s32, s32, s32);
void fn_02009F68(s32, s32, s32);
char *fn_0201A73C(s32);
char *fn_0201AA44(s32);
char *fn_0201AAAC(s32);
s32 fn_0201AB14(s32);
void fn_02014C48(void);
void fn_02014DE8(void);
void fn_02014E64(void);
void fn_02014ED8(void);

s32 fn_02014060(s32 idx);
void fn_0201409C(s32 idx, s32 row);
void fn_02014500(void);
void fn_02014578(void);
s32 fn_020145EC(void);
void fn_02014708(s32 page);
void fn_02014B54(void);

void fn_02013844(void)
{
    s32 *hdr = lbl_0203A800;
    struct Entry *entry = lbl_0203A810;
    s32 n;
    s32 x;
    s32 y;
    s32 i;
    s32 frame;
    s32 pal;
    s32 anim;

    n = (hdr[0] > lbl_030030B0[0].unkE) ? lbl_030030B0[0].unkE : hdr[0];
    if (n > lbl_030027DD)
        n = lbl_030027DD;
    x = (lbl_030030B0[0].unk10 + lbl_030030B0[0].unk14 - 3) * 8;
    entry += lbl_030027DC;
    for (i = 0; i < n; i++, entry++) {
        if (entry->unk6 & 0x18) {
            y = (i * 2 + 1) * 8;
            frame = (entry->unk6 & 2) ? 0x35 : 0x34;
            fn_02003C3C(x, y - 3, 0, frame, fn_02004030(0, frame), 0, 0);
        }
    }
    pal = fn_02004030(0, 0x2E);
    x -= 16;
    anim = (lbl_03002AC8 & 8) >> 2;
    if (lbl_030027DC) {
        y = anim;
        fn_02003C3C(x, y, 0, 0x2E, pal, 0, 0);
    }
    if (lbl_030030B0[0].unkE + lbl_030027DC < hdr[0]) {
        y = lbl_030030B0[0].unk16 * 8 - 16;
        y -= anim;
        fn_02003C3C(x, y, 0, 0x2E, pal, 0, 0x20000000);
    }
}

void fn_0201396C(void)
{
    char buf[256];
    struct Window win;
    u16 tiles[60];
    char *line = lbl_0203D800;
    char *nl = line;
    s32 i;
    s32 w;
    s32 width;
    s32 tile;
    s32 attr;
    s32 size;
    s32 x;
    s32 y;
    u16 *dst;

    memset(buf, 0, sizeof(buf));
    memcpy(&win, lbl_030030B0, sizeof(win));
    win.unk5--;
    for (i = 0; i <= lbl_030027DD; i++) {
        nl = strchr(line, '\n');
        if (nl && i < lbl_030027DD)
            line = nl + 1;
        else
            break;
    }
    if (*line == 0x1D) {
        lbl_030027E8 = 0;
        line++;
    } else if (*line == 0x1E) {
        lbl_030027E8 = 1;
        line++;
    } else if (*line == 0x1C) {
        lbl_030027E8 = 2;
        line++;
    }
    if (nl) {
        i = nl - line;
        memcpy(buf, line, i);
    } else {
        strcpy(buf, line);
    }
    fn_02003394(0, 0);
    fn_020033F4();
    if (lbl_030027E8) {
        width = fn_02003464(buf, 2);
        i = (win.unk14 - 5) * 8;
        if (width >= i) {
            fn_020038F4(0);
        } else {
            width = i - width;
            if (lbl_030027E8 == 1)
                width >>= 1;
            fn_020038F4(width);
        }
    }
    fn_02003464(buf, 0);
    w = fn_02003910();
    w = (w & 7) ? (w >> 3) + 1 : w >> 3;
    fn_020059D4(&win, lbl_030027DD, 0);
    if (w) {
        tile = (win.unk14 << 1) * lbl_030027DD + 0x80;
        attr = 0x7000;
        if (w >= win.unk14 - 5)
            w = win.unk14 - 5;
        size = w * 2;
        for (i = 0; i < w; i++) {
            tiles[i] = tile++ | attr;
            tiles[i + 30] = tile++ | attr;
        }
        x = win.unk10 + 2;
        y = win.unk12 + lbl_030027DD * 2 + 1;
        dst = fn_02000A40(win.unk5, x, y);
        DmaCopy16(DMA3, tiles, dst, size);
        DmaCopy16(DMA3, tiles + 30, dst + 32, size);
    }
    lbl_030027DD++;
}

s32 fn_02013B1C(s8 *str)
{
    s32 n = 0;
    s8 c;

    for (;;) {
        c = *str;
        if (c == '\n' || c == 0) {
            n++;
            if (c == 0)
                break;
        }
        str++;
    }
    return n;
}

void fn_02013B3C(void)
{
    struct Entry *entry = &lbl_0203A810[lbl_030027E0];
    struct Window *win;
    s32 x;
    s32 y;
    s32 frame;

    if (entry->unk6 & 0x18) {
        win = lbl_030030B0;
        x = win->unk10 + win->unk14 - 5;
        y = win->unk12 + win->unk16 - 4;
        x *= 8;
        y *= 8;
        frame = (entry->unk6 & 2) ? 0x35 : 0x34;
        fn_02003C3C(x, y, 0, frame, fn_02004030(0, frame), win->unk5 - 1, 0);
    }
}

void fn_02013BB8(s32 ok, u32 value)
{
    if (ok) {
        lbl_030027E5 = 1;
        lbl_030027E9 = 16;
        lbl_030027EC = value;
    } else {
        lbl_030027E5 = -1;
        lbl_030027E9 = 0;
        lbl_030027EC = 0;
    }
}

void fn_02013C04(s32 ok, u32 value, s32 idx)
{
    if (ok) {
        lbl_030027E5 = 1;
        lbl_030027E9 = 8;
        lbl_030027EC = (idx << 16) | value;
    } else {
        lbl_030027E5 = -1;
        lbl_030027E9 = 0;
        lbl_030027EC = 0;
    }
}

void fn_02013C54(void)
{
    struct Window *win = &lbl_030030B0[1];
    s32 x = (win->unk10 + 1) * 8;
    s32 y = (win->unk12 + 1) * 8;
    s32 i;
    s32 id;
    s32 pal;
    s16 v;

    for (i = 0; i < win->unkE; i++, y += 16) {
        v = lbl_03002CA0.unk64[i + lbl_030027F0];
        if (v > 0) {
            id = fn_0201AB14(v);
            pal = fn_02004030(0, id);
            fn_02003C3C(x - 2, y, 0, id, pal, win->unk5, 0);
        }
    }
    x = (win->unk10 + 1) * 8;
    y = (win->unk12 + 1) * 8;
    id = ((lbl_03002C98 & 15) == 1) ? 24 : 4;
    pal = fn_02004030(2, id);
    for (i = 0; i < win->unkE; i++, y += 16) {
        if (fn_02004D3C(i + lbl_030027F0))
            fn_02003C3C(x - 4, y, 2, id, pal, win->unk5 - 1, 0);
    }
}

s32 fn_02013D70(void)
{
    struct Window *win;
    s32 idx;
    s32 v;
    s32 pal;
    s32 count = 64;

    if (lbl_0300299C) {
        win = &lbl_030030B0[1];
        if (lbl_0300299C & 0x40) {
            if (win->unk2) {
                win->unk2--;
                fn_02009F68(lbl_03002CA0.unk64[lbl_030027F0 + win->unk2], 1, 1);
                m4aSongNumStart(1);
            } else if (lbl_030027F0 == 0) {
                m4aSongNumStart(0);
            } else {
                fn_02009A14(1, 1, win->unk5);
                idx = lbl_030027F0 - 1;
                fn_0201409C(idx, idx % win->unkE);
                v = lbl_03002CA0.unk64[idx];
                if (fn_02004D3C(idx) == 0) {
                    if (v <= 0x124)
                        pal = 6;
                    else
                        pal = 5;
                } else {
                    pal = 6;
                }
                fn_02009AB8(1, win->unk5, idx % win->unkE, 0, pal);
                lbl_030027F0--;
                fn_02009F68(lbl_03002CA0.unk64[lbl_030027F0 + win->unk2], 1, 1);
                m4aSongNumStart(1);
            }
        } else if (lbl_0300299C & 0x80) {
            if (win->unk2 < win->unkE - 1) {
                win->unk2++;
                fn_02009F68(lbl_03002CA0.unk64[lbl_030027F0 + win->unk2], 1, 1);
                m4aSongNumStart(1);
            } else if (lbl_030027F0 + win->unkE >= count) {
                m4aSongNumStart(0);
            } else {
                fn_02009A14(0, 1, win->unk5);
                idx = lbl_030027F0 + win->unkE;
                fn_0201409C(idx, idx % win->unkE);
                v = lbl_03002CA0.unk64[idx];
                if (fn_02004D3C(idx) == 0) {
                    if (v <= 0x124)
                        pal = 6;
                    else
                        pal = 5;
                } else {
                    pal = 6;
                }
                fn_02009AB8(1, win->unk5, idx % win->unkE, win->unkE - 1, pal);
                lbl_030027F0++;
                fn_02009F68(lbl_03002CA0.unk64[lbl_030027F0 + win->unk2], 1, 1);
                m4aSongNumStart(1);
            }
        }
        if (!(lbl_0300299C & 0xC0)) {
            if (lbl_030029AC & 1) {
                idx = win->unk2 + lbl_030027F0;
                if (fn_02014060(idx)) {
                    lbl_030027E5 = 1;
                    lbl_030027E9 = 8;
                    lbl_030027EC = (idx << 16) | lbl_03002CA0.unk64[idx];
                    lbl_030030A4++;
                    m4aSongNumStart(2);
                } else {
                    m4aSongNumStart(0);
                }
            }
            if (lbl_030029AC & 2) {
                lbl_030027E5 = -1;
                lbl_030027E9 = 0;
                lbl_030027EC = 0;
                lbl_030030A4++;
                m4aSongNumStart(3);
            } else if (lbl_030029AC & 0x300) {
                m4aSongNumStart(0);
            }
        }
    }
    return 0;
}

s32 fn_02014060(s32 idx)
{
    s32 v = lbl_03002CA0.unk64[idx];
    s32 ret;

    if (v <= 0)
        ret = 0;
    else
        ret = fn_02004D3C(idx) == 0;
    if (v <= 0x124)
        ret = 0;
    return ret;
}

void fn_0201409C(s32 idx, s32 row)
{
    struct Window *win = &lbl_030030B0[1];
    s32 v;
    char *str;

    fn_02003394(1, 0);
    fn_020033F4();
    v = lbl_03002CA0.unk64[idx];
    if (v > 0) {
        fn_020038F4(16);
        str = fn_0201AAAC(v);
    } else {
        str = fn_0201A73C(0);
    }
    fn_02003464(str, 0);
    fn_020059D4(win, row, 0);
}

void fn_020140F4(char *buf, s32 type)
{
    s32 *hdr = lbl_0203A800;
    struct Entry *entry = lbl_0203A810;
    s32 n = hdr[1] * 24;
    char *names = (char *)(entry + hdr[0]) + n;
    s32 mode;
    char *p;
    char *nl;
    s32 len;

    entry += lbl_030027E0;
    mode = lbl_03002C98 & 15;
    if (type == 0) {
        p = names + entry->unk5 * 16;
        if (mode == 1) {
            memcpy(buf, p, 16);
            strcat(buf, fn_0201AA44(5));
        } else if (mode == 2) {
            strcpy(buf, fn_0201AA44(5));
            len = strlen(buf);
            memcpy(buf + len, p, 16);
        } else if (mode == 3 || mode == 4) {
            strcpy(buf, fn_0201AA44(5));
            len = strlen(buf);
            memcpy(buf + len, p, 16);
            strcat(buf, fn_0201AA44(4));
        } else {
            strcpy(buf, fn_0201AA44(4));
            strcat(buf, lbl_0201D044);
            len = strlen(buf);
            memcpy(buf + len, p, 16);
            strcat(buf, fn_0201AA44(5));
        }
    } else if (type == 1) {
        if (mode == 2)
            strcpy(buf, fn_0201AA44(6));
        else
            buf[0] = 0;
        p = lbl_0203D800;
        p = strlen(p) + lbl_0203D801;
        for (type = 0; type < lbl_030027E6; type++) {
            nl = strchr(p, '\n');
            if (nl)
                p = nl + 1;
            else
                break;
        }
        strcat(buf, fn_0201AA44(2));
        nl = strchr(p, '\n');
        if (nl) {
            type = nl - p;
            memcpy(buf + strlen(buf), p, type);
        } else {
            strcat(buf, p);
        }
        strcat(buf, fn_0201AA44(3));
        if (mode == 1)
            strcat(buf, fn_0201AA44(6));
        else if (mode == 2)
            strcat(buf, lbl_0201D048);
    } else if (lbl_030027E9 & 0x18) {
        if (mode != 1)
            strcpy(buf, fn_0201AA44(13));
        len = strlen(buf);
        if (lbl_030027E9 & 0x10) {
            fn_02000D9C(buf + len, lbl_030027EC);
            strcat(buf, lbl_0201D044);
            strcat(buf, fn_0201A73C(5));
        } else {
            if (mode == 1)
                strcat(buf, fn_0201AA44(2));
            strcat(buf, fn_0201AAAC((u16)lbl_030027EC));
            if (mode == 1)
                strcat(buf, fn_0201AA44(3));
        }
        if (mode == 1)
            strcat(buf, fn_0201AA44(13));
    }
}

void fn_02014354(void)
{
    s32 i;

    lbl_030030A4 = 0;
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    lbl_030030B0[0].unk0 = 1;
    lbl_030030B0[0].unk2 = lbl_030027F5;
    lbl_030030B0[0].unk10 = 2;
    lbl_030030B0[0].unk12 = 2;
    lbl_030030B0[0].unkE = 5;
    lbl_030030B0[0].unk14 = 26;
    lbl_030030B0[0].unk16 = 16;
    lbl_030030B0[0].unk3 = 1;
    lbl_030030B0[0].unk4 = 0;
    lbl_030030B0[0].unk5 = 2;
    lbl_030030B0[0].unk6 = 0;
    lbl_030030B0[0].unk7 = 0;
    lbl_030030B0[0].unk9[0] = 1;
    for (i = 0; i < lbl_030030B0[0].unkE; i++) {
        lbl_030030B0[0].items[i].unk0 = 1;
        lbl_030030B0[0].items[i].unk4 = fn_0201A73C(0);
    }
    fn_020037C8(3, 0, 0);
    fn_020038D8(0x06008000);
    fn_020041D4(4, 0);
    fn_02004098(4, 0, 2, 0);
    lbl_030027F4 = 0;
    lbl_030030AC = 1;
}

s32 fn_02014428(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    if (lbl_030030AC == 0)
        fn_02014354();
    win = lbl_030030B0;
    fn_02005968(win);
    fn_02005A50(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2)
        ret = 1;
    else
        win->unk1 += 8;
    return ret;
}

s32 fn_02014478(void)
{
    s32 ret;

    if (lbl_030027F4 <= 4) {
        fn_02014708(lbl_030027F4);
        lbl_030027F4++;
        return 0;
    }
    ret = 0;
    if (lbl_03002ACC) {
        ret = fn_020145EC();
        fn_02014500();
    }
    fn_02014578();
    return ret;
}

s32 fn_020144BC(void)
{
    struct Window *win = lbl_030030B0;
    s32 ret = 0;

    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        ret = 1;
        fn_02004320(4);
        win->unk1 = 0;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

void fn_02014500(void)
{
    s32 pal = fn_02004030(0, 0x2D);
    struct Window *win = lbl_030030B0;
    s32 x = (win->unk10 - 1) * 8;
    s32 y;
    s8 col;
    s8 row;

    col = win->unk2 / 5;
    if (col)
        x += 104;
    y = (win->unk12 + 1) * 8;
    row = win->unk2 % 5;
    y += 24 * row;
    fn_02003C3C(x, y, 0, 0x2D, pal, win->unk5, 0);
}

void fn_02014578(void)
{
    s32 id = 6;
    s32 pal = fn_02004030(2, id);
    struct Window *win = lbl_030030B0;
    s32 x = (win->unk10 + 1) * 8 + 4;
    s32 y = (win->unk12 + 1) * 8 + 4;
    s32 i;

    for (i = 0; i < 10; i++, y += 24) {
        if (i == 5) {
            x += 104;
            y = (win->unk12 + 1) * 8 + 4;
        }
        fn_02003C3C(x, y, 2, id, pal, win->unk5, 0);
    }
}

s32 fn_020145EC(void)
{
    struct Window *win;
    s32 cur;
    s32 lastCol = 4;
    s32 cols = 5;
    s32 last = 9;

    if (lbl_0300299C) {
        win = lbl_030030B0;
        if (lbl_0300299C & 0x40) {
            cur = win->unk2;
            if (cur % 5)
                win->unk2--;
            else
                win->unk2 += 4;
            m4aSongNumStart(1);
        } else if (lbl_0300299C & 0x80) {
            cur = win->unk2;
            if (cur % 5 < lastCol)
                win->unk2++;
            else
                win->unk2 -= 4;
            m4aSongNumStart(1);
        }
        if (lbl_0300299C & 0x30) {
            cur = win->unk2;
            if (cur < cols)
                win->unk2 += 5;
            else
                win->unk2 -= 5;
            m4aSongNumStart(1);
        }
        if (!(lbl_0300299C & 0xF0)) {
            if (lbl_0300299C & 0x200) {
                if (win->unk2)
                    win->unk2--;
                else
                    win->unk2 = 9;
                m4aSongNumStart(1);
            } else if (lbl_0300299C & 0x100) {
                cur = win->unk2;
                if (cur < last)
                    win->unk2++;
                else
                    win->unk2 = 0;
                m4aSongNumStart(1);
            } else if (lbl_030029AC & 1) {
                m4aSongNumStart(2);
                return 1;
            } else if (lbl_030029AC & 2) {
                m4aSongNumStart(0);
            }
        }
    }
    return 0;
}

void fn_02014708(s32 page)
{
    fn_02003394(1, 0);
    fn_020033F4();
    fn_020038F4(16);
    fn_02003464(fn_0201A73C(page + 44), 0);
    fn_020038F4(120);
    fn_02003464(fn_0201A73C(page + 49), 0);
    fn_020037A8(fn_02009340(lbl_030030B0, page, 0), lbl_030030B0[0].unk14);
}

void fn_02014760(u8 idx)
{
    lbl_030027F5 = idx;
}

void fn_0201476C(void)
{
    REG_DISPCNT = 0x9940;
    lbl_030030A4 = 0;
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    fn_020093B4(0, 0);
    fn_02003394(1, 0);
    fn_020037C8(4, 0, 0);
    fn_02003890(0x050000E0, 1);
    fn_02003890(0x05000120, fn_02002FAC() + 5);
    fn_020038D8(0x06000000);
    fn_020041D4(17, 0);
    fn_02004098(17, 0, 0, 0);
    fn_02004098(14, 1, 1, 0);
    lbl_030027F8 = 0;
    fn_020008D0();
    fn_020018C8();
    fn_020017DC();
    if (lbl_03002ED0 == 0)
        fn_02001828();
    fn_0200194C(1);
    fn_02014B54();
    fn_020095FC(3);
    lbl_030030AC = 1;
}

s32 fn_0201484C(void)
{
    struct Window *win = lbl_030030B0;
    s32 ret;

    fn_02003394(1, 0);
    if (lbl_030030AC == 0) {
        fn_0201476C();
        if (lbl_030030AC == 0) {
            if (lbl_03002ACC && (lbl_030029AC & 0x300)) {
                if (lbl_030029AC & 0x100)
                    lbl_03003098 = 1;
                else
                    lbl_03003098 = -1;
                m4aSongNumStart(6);
                lbl_030032F4++;
                REG_DISPCNT = 0x9F40;
                fn_0200194C(0);
                return 1;
            }
            if (lbl_030030AC == 0)
                return 0;
        }
    }
    ret = fn_02009414(0);
    if (ret) {
        win->unk1 = 0;
        REG_DISPCNT = 0x9F40;
        fn_02009684(3, 9);
    }
    return ret;
}

s32 fn_0201491C(void)
{
    s16 dx;
    s16 dy;

    fn_020095AC(0);
    if ((lbl_03002AEC & 0x402) != 0x402 && lbl_030027F8) {
        REG_DISPCNT = 0x9940;
        fn_020017DC();
        lbl_030027F8 = 0;
    }
    fn_02003394(1, 0);
    if (fn_02002594() && lbl_03002FF0) {
        fn_02014DE8();
        if (lbl_03002ED0 == 1 || lbl_03002ED0 == 3) {
            fn_02014E64();
            if (lbl_03002ED0 == 3)
                fn_02014ED8();
        }
        if (lbl_03002ED0 == 0)
            fn_02014C48();
    }
    if ((lbl_03002AEC & 0x402) == 0x402 && lbl_030027F8 == 0 && lbl_03002FF0) {
        REG_DISPCNT = 0x9F40;
        if (lbl_03002ED0 == 0)
            fn_0200197C();
        lbl_030027F8 = 1;
    }
    if (lbl_03002FF0 && lbl_03002ED0 == 0 && !(lbl_03002AF8 & 1) && (lbl_03002AEC & 0x400)) {
        fn_02004604(&dx, &dy);
        if (dx < -6 || dx > 6 || dy > 6 || dy <= -7)
            fn_0200197C();
        else
            fn_02001C44(dx, dy);
    }
    if (lbl_03002ACC) {
        if (lbl_030029AC & 0x300) {
            if (lbl_030029AC & 0x100)
                lbl_03003098 = 1;
            else
                lbl_03003098 = -1;
            REG_DISPCNT = 0x9940;
            m4aSongNumStart(6);
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
    }
    return 0;
}

s32 fn_02014AFC(void)
{
    struct Window *win = lbl_030030B0;
    s32 ret = 0;

    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        ret = 1;
        fn_02004320(17);
        fn_0200194C(0);
        REG_DISPCNT = 0x9F40;
        win->unk1 = 0;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

void fn_02014B54(void)
{
    u16 buf[30];
    s32 row;
    s32 col;
    s32 tile;
    s32 v;
    u16 *dst;
    s32 attr = 0xB000;

    for (row = 0; row < 16; row++) {
        dst = fn_02000A40(1, 0, row);
        if (row == 1 || row + 1 >= 16) {
            for (col = 0; col < sizeof(buf) / sizeof(buf[0]); col++)
                buf[col] = 0x3FF;
        }
        for (col = 0; col < 20; col++) {
            tile = 36;
            if (row == 0 || row + 1 >= 16) {
                if (col == 1 || col == 18)
                    tile = 37;
                else if (col >= 2 && col <= 17)
                    tile = 38;
                v = attr | tile;
                buf[col] = v;
                if (row != 0)
                    buf[col] = v | 0x800;
                if (col > 17)
                    buf[col] |= 0x400;
            } else {
                if (row >= 3 && row <= 13)
                    break;
                tile = (row == 1 || row == 14) ? 39 : 40;
                v = attr | tile;
                buf[0] = v;
                if (row > 13)
                    buf[0] = v | 0x800;
                buf[19] = buf[0] | 0x400;
            }
        }
        DmaCopy16(DMA0, buf, dst, 40);
    }
}
