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

struct Cmd {
    u8 unk[4];
};

struct Unk03002CA0 {
    u8 unk0[0x128];
    s8 unk128;
};

struct Unk03002FD0 {
    u8 unk0[7];
    u8 unk7;
};

struct WinItem {
    s16 unk0;
    s16 unk2;
    char *unk4;
};

struct Window {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    s8 unk3;
    s8 unk4;
    s8 unk5;
    s8 unk6;
    s8 unk7;
    s8 unk8;
    s8 unk9;
    s8 unkA;
    u8 unkB[3];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    struct WinItem items[1];
};

extern u8 lbl_030029A0;
extern u8 lbl_03002ACC;
extern u8 lbl_03002C98;
extern struct Unk03002CA0 lbl_03002CA0;
extern struct Unk03002FD0 lbl_03002FD0[];
extern u32 lbl_03003090;
extern u32 lbl_03003094;
extern u16 lbl_030032E4;
extern u32 lbl_030032E8;
extern u8 lbl_030032FC[];

void fn_02000990(void);
u16 *fn_02000A40(s32 bg, s32 x, s32 y);
void fn_02000A74(void);
void fn_02001438(s32, s32);
void fn_0200194C(s32);
s32 fn_02002FAC(void);
s32 fn_02004030(s32, s32);
s32 fn_020059EC(s32, s32);
s32 fn_02005A0C(s32);
void fn_02005844(void);
void fn_02009318(void);
void fn_02019C4C(void);
void fn_02003C3C(s32, s32, s32, s32, s32, s32, s32);
void fn_020098F0(s32, s32, s32, s32, s32);

void fn_0200714C(struct Window *win);
void fn_0200823C(struct Window *win);
void fn_02008328(struct Window *win);
void fn_02008478(struct Window *win);
void fn_02008540(struct Window *win);
void fn_020086A8(struct Window *win);
void fn_020087E8(struct Window *win);
void fn_020088E0(struct Window *win);
void fn_02008A48(struct Window *win);
void fn_02008B8C(struct Window *win);
void fn_02008CC0(struct Window *win);
void fn_02008DB8(struct Window *win);

void fn_02006670(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    s32 t;
    s32 k;
    s32 odd;
    s32 attr;
    u16 *map;

    px = win->unk10 * 8;
    py = win->unk12 * 8 + win->unk1 + 8;
    if ((py >> 3) > win->unk12 + win->unk16)
        return;
    if (win->unk1 == 0 && win->unkA == 0) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                t = tile;
            else if (i + 1 >= win->unk14)
                t = tile + 2;
            else
                t = tile + 1;
            buf[i] = t | pal;
        }
        map = fn_02000A40(win->unk5, win->unk10, win->unk12);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
    }
    if (lbl_03003094 || win->unk1) {
        if (win->unk1 && win->unkA == 0) {
            for (i = 0; i < win->unk14; i++) {
                if (i == 0)
                    t = tile + 3;
                else if (i + 1 >= win->unk14)
                    t = tile + 5;
                else
                    t = tile + 4;
                if ((py >> 3) >= win->unk12 + win->unk16)
                    t += 3;
                buf[i] = t | pal;
            }
            map = fn_02000A40(win->unk5, win->unk10, (py - 8) >> 3);
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        }
        k = win->unk1 >> 3;
        k -= win->unk8;
        if ((lbl_03003094 == 0 ? k > 0 : k >= 0) && k <= win->unkE * 2) {
            t = fn_02005A0C(win->unk6);
            if (lbl_03003094) {
                odd = k & 1;
                k >>= 1;
            } else {
                odd = ~k & 1;
                k = (k - 1) >> 1;
            }
            t += win->unk14 * 2 * k + odd;
            attr = win->items[k].unk0 ? 7 : 8;
            attr <<= 12;
            for (i = 1; i < win->unk14 - 1; i++) {
                if (i & 1) {
                    buf[i] = attr | t;
                } else {
                    buf[i] = (t + 2) | attr;
                    t += 4;
                }
            }
            buf[0] = 0x3FF;
            buf[win->unk14 - 1] = 0x3FF;
            map = fn_02000A40(win->unk5 - 1, win->unk10, (py - 8) >> 3);
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        }
    }
    if ((py >> 3) < win->unk12 + win->unk16 && win->unkA == 0) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                t = 6;
            else if (i + 1 >= win->unk14)
                t = 8;
            else
                t = 7;
            fn_02003C3C(px, py, 6, t, win->unk4, win->unk5 - 1, 0);
            px += 8;
        }
    }
}

void fn_02006920(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    s32 t;
    s32 n;
    s32 odd;
    s32 attr;
    s8 hidden;
    u16 *map;

    px = win->unk10 * 8;
    py = win->unk12 * 8 + win->unk1 + 8;
    if ((py >> 3) > win->unk12 + win->unk16)
        return;
    hidden = win->unkA;
    if (win->unk1 == 0 && hidden == 0) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                t = tile;
            else if (i == 1)
                t = tile + 1;
            else if (i >= win->unk14 - 1)
                t = tile + 3;
            else
                t = tile + 2;
            buf[i] = t | pal;
        }
        map = fn_02000A40(win->unk5, win->unk10, win->unk12);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
    } else {
        n = win->unk1 >> 3;
        for (i = 0; i < win->unk14; i++) {
            if (n < win->unk16 - 2) {
                if (i == 0)
                    t = tile + 4;
                else if (i >= win->unk14 - 1)
                    t = tile + 6;
                else
                    t = tile + 5;
            } else if (n >= win->unk16 - 1) {
                if (i == 0)
                    t = tile + 9;
                else if (i == win->unk14 - 2)
                    t = tile + 11;
                else if (i >= win->unk14 - 1)
                    t = tile + 12;
                else
                    t = tile + 10;
            } else {
                if (i == 0)
                    t = tile + 7;
                else if (i >= win->unk14 - 1)
                    t = tile + 8;
                else
                    t = tile + 5;
            }
            buf[i] = t | pal;
        }
        if (hidden == 0) {
            map = fn_02000A40(win->unk5, win->unk10, (py - 8) >> 3);
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        }
        n -= win->unk8;
        if (n > 0 && n <= win->unkE * 2) {
            t = fn_02005A0C(win->unk6);
            odd = ~n & 1;
            t += win->unk14 * 2 * ((n - 1) >> 1) + odd;
            if (n <= 4)
                attr = 7 << 12;
            else
                attr = 8 << 12;
            for (i = 1; i < win->unk14 - 1; i++) {
                if (i & 1) {
                    buf[i] = attr | t;
                } else {
                    buf[i] = (t + 2) | attr;
                    t += 4;
                }
            }
            if (win->unk5 - 1 <= 1) {
                buf[0] = 0x3FF;
                buf[win->unk14 - 1] = 0x3FF;
            } else {
                buf[0] = 0x2FF;
                buf[win->unk14 - 1] = 0x2FF;
            }
            map = fn_02000A40(win->unk5 - 1, win->unk10, (py - 8) >> 3);
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        }
    }
    if ((py >> 3) < win->unk12 + win->unk16 && win->unkA == 0) {
        for (i = 0; i < win->unk14; i++, px += 8) {
            if (i == 0)
                t = 9;
            else if (i == win->unk14 - 2)
                t = 11;
            else if (i >= win->unk14 - 1)
                t = 12;
            else
                t = 10;
            fn_02003C3C(px, py, 7, t, win->unk4, win->unk5 - 1, 0);
        }
    }
}

void fn_02006BD4(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 y;
    s32 py;
    s32 i;
    s32 t;
    s32 k;
    s32 attr;
    u16 *map;

    px = win->unk10 * 8;
    y = win->unk12 * 8 + win->unk1;
    py = y + 16;
    if ((py >> 3) - win->unk12 >= win->unk16)
        return;
    if (win->unk1 == 0) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                buf[i] = tile | pal;
            else if (i != win->unk14 - 1) {
                if (i & 1)
                    buf[i] = (tile + 1) | pal;
                else
                    buf[i] = (tile + 2) | pal;
            } else
                buf[i] = (tile + 3) | pal;
        }
        map = fn_02000A40(win->unk5, win->unk10, win->unk12);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        attr = fn_020059EC(win->items[0].unk0, win->unk6);
        for (i = 0; i < win->unk14; i++) {
            if (i & 1)
                buf[i] = (tile - 4) | attr;
            else
                buf[i] = (tile - 2) | attr;
        }
        buf[0] = pal | (tile + 4);
        buf[win->unk14 - 1] = pal | (tile + 5);
        map = fn_02000A40(win->unk5, win->unk10, win->unk12 + 1);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
    } else {
        k = win->unk1 >> 3;
        if (k != 0) {
            t = fn_02005A0C(win->unk6);
            py = y + 8;
            t += win->unk14 * 2 * ((k - 1) >> 1) + (~k & 1);
            attr = fn_020059EC(win->items[(k - 1) >> 1].unk0, win->unk6);
            for (i = 1; i < win->unk14 - 1; i++) {
                if (i & 1) {
                    buf[i] = attr | t;
                } else {
                    buf[i] = (t + 2) | attr;
                    t += 4;
                }
            }
            if (k & 1) {
                buf[0] = (tile + 4) | pal;
                buf[win->unk14 - 1] = (tile + 5) | pal;
            } else {
                buf[0] = (tile + 6) | pal;
                buf[win->unk14 - 1] = (tile + 7) | pal;
            }
            map = fn_02000A40(win->unk5, win->unk10, py >> 3);
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
            py += 8;
            if (py >= (win->unk12 + win->unk16) * 8 - 8) {
                for (i = 0; i < win->unk14; i++) {
                    if (i == 0)
                        buf[i] = (tile + 8) | pal;
                    else if (i != win->unk14 - 1) {
                        if (i & 1)
                            buf[i] = (tile + 9) | pal;
                        else
                            buf[i] = (tile + 10) | pal;
                    } else
                        buf[i] = (tile + 11) | pal;
                }
                map = fn_02000A40(win->unk5, win->unk10, py >> 3);
                DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
            }
        }
    }
    if ((py >> 3) - win->unk12 - 1 < win->unk16) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                t = 8;
            else if (i != win->unk14 - 1)
                t = 10;
            else
                t = 11;
            fn_02003C3C(px, py, 8, t, win->unk4, win->unk5, 0);
            px += 8;
        }
    }
}

void fn_02006F30(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    s32 t;
    u16 *map;

    px = win->unk10 * 8;
    py = win->unk12 * 8 + win->unk1 + 8;
    if ((py >> 3) > win->unk12 + win->unk16)
        return;
    if (win->unk1 == 0) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                t = tile;
            else if (i + 1 >= win->unk14)
                t = tile + 2;
            else
                t = tile + 1;
            buf[i] = t | pal;
        }
        map = fn_02000A40(win->unk5, win->unk10, win->unk12);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
    }
    if (lbl_03003094 || win->unk1) {
        if (win->unk1) {
            for (i = 0; i < win->unk14; i++) {
                if (i == 0)
                    t = tile + 3;
                else if (i + 1 >= win->unk14)
                    t = tile + 5;
                else
                    t = tile + 4;
                if ((py >> 3) >= win->unk12 + win->unk16)
                    t += 3;
                buf[i] = t | pal;
            }
            map = fn_02000A40(win->unk5, win->unk10, (py - 8) >> 3);
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        }
        if ((py >> 3) - win->unk12 >= win->unk16 - 1) {
            for (i = 0; i < win->unk14; i++) {
                if (i == 0)
                    t = tile + 6;
                else if (i + 1 >= win->unk14)
                    t = tile + 8;
                else
                    t = tile + 7;
                buf[i] = t | pal;
            }
            map = fn_02000A40(win->unk5, win->unk10, (py >> 3));
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        }
    }
    if ((py >> 3) < win->unk12 + win->unk16) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                t = 6;
            else if (i + 1 >= win->unk14)
                t = 8;
            else
                t = 7;
            fn_02003C3C(px, py, 9, t, win->unk4, win->unk5 - 1, 0);
            px += 8;
        }
    }
}

void fn_0200714C(struct Window *win)
{
}

void fn_02007150(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 y;
    s32 py;
    s32 i;
    s32 j;
    s32 t;
    s32 k;
    s32 skip;
    s32 attr;
    u16 *map;

    px = win->unk10 * 8;
    y = win->unk12 * 8 + win->unk1;
    py = y + 16;
    fn_0200714C(win);
    if ((py >> 3) - win->unk12 >= win->unk16)
        return;
    if (win->unk1 == 0) {
        for (j = 0; j < 2; j++) {
            skip = 0;
            for (i = 0; i < win->unk14; i++) {
                if (i <= 4) {
                    t = i;
                } else if (i < win->unk14 - 7) {
                    t = 5;
                    skip++;
                } else {
                    t = i - skip;
                }
                if (j != 0)
                    t += 12;
                buf[i] = (tile + t) | pal;
            }
            map = fn_02000A40(win->unk5, win->unk10, win->unk12 + j);
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        }
    } else {
        k = (win->unk1 >> 3) - 1 - win->unk8;
        attr = 3 << 12;
        if (k < 0) {
            for (i = 1; i < win->unk14 - 1; i++) {
                t = tile - 2;
                if (i & 1)
                    t -= 2;
                if (k & 1)
                    t++;
                buf[i] = t | attr;
            }
        } else {
            t = fn_02005A0C(win->unk6);
            t += win->unk14 * 2 * (k >> 1) + (k & 1);
            for (i = 1; i < win->unk14 - 1; i++) {
                if (i & 1) {
                    buf[i] = attr | t;
                } else {
                    buf[i] = (t + 2) | attr;
                    t += 4;
                }
            }
        }
        if (k == 0) {
            buf[0] = (tile + 24) | pal;
            buf[win->unk14 - 1] = (tile + 25) | pal;
        } else {
            buf[0] = (tile + 26) | pal;
            buf[win->unk14 - 1] = (tile + 27) | pal;
        }
        map = fn_02000A40(win->unk5, win->unk10, (y + 8) >> 3);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        if ((py >> 3) - win->unk12 >= win->unk16 - 1) {
            for (i = 0; i < win->unk14; i++) {
                if (i == 0)
                    t = 28;
                else if (i + 1 >= win->unk14)
                    t = 30;
                else
                    t = 29;
                buf[i] = (tile + t) | pal;
            }
            map = fn_02000A40(win->unk5, win->unk10, (py >> 3));
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        }
    }
    if ((py >> 3) - win->unk12 < win->unk16 - 1) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                t = 28;
            else if (i + 1 >= win->unk14)
                t = 30;
            else
                t = 29;
            fn_02003C3C(px, py, 10, t, win->unk4, win->unk5 - 1, 0);
            px += 8;
        }
    }
}

void fn_0200743C(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 y;
    s32 py;
    s32 n;
    s32 i;
    s32 t;
    s32 a;
    s32 odd;
    s32 attr;
    u16 *map;

    px = win->unk10 * 8;
    y = win->unk12 * 8 + win->unk1;
    py = y + 8;
    n = win->unk1 >> 3;
    if (n >= win->unk16)
        return;
    if (n <= 1) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                t = tile;
            else if (i == 1)
                t = tile + 1;
            else if (i == win->unk14 - 2)
                t = tile + 4;
            else if (i >= win->unk14 - 1)
                t = tile + 5;
            else if (i & 2)
                t = tile + 2;
            else
                t = tile + 3;
            if (n != 0)
                t += 6;
            buf[i] = t | pal;
        }
        map = fn_02000A40(win->unk5, win->unk10, win->unk12 + (win->unk1 >> 3));
    } else if (n < win->unk16 - 3) {
        odd = n & 1;
        attr = fn_020059EC(1, win->unk6);
        for (i = 0; i < win->unk14; i++) {
            if (i <= 1 || i >= win->unk14 - 2) {
                if (i <= 1)
                    t = i + 12;
                else
                    t = i - win->unk14 + 16;
                t += tile;
                if (odd)
                    t += 4;
                a = pal;
            } else {
                if (i & 2)
                    t = tile - 2;
                else
                    t = tile - 4;
                if (odd)
                    t += 1;
                a = attr;
            }
            buf[i] = t | a;
        }
        map = fn_02000A40(win->unk5, win->unk10, y >> 3);
    } else {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                t = tile + 20;
            else if (i == 1)
                t = tile + 21;
            else if (i == win->unk14 - 2)
                t = tile + 24;
            else if (i >= win->unk14 - 1)
                t = tile + 25;
            else if (i & 2)
                t = tile + 22;
            else
                t = tile + 23;
            t += (n + 3 - win->unk16) * 6;
            buf[i] = t | pal;
        }
        map = fn_02000A40(win->unk5, win->unk10, y >> 3);
    }
    DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
    if ((py >> 3) - win->unk12 < win->unk16) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                t = 32;
            else if (i == 1)
                t = 33;
            else if (i > 1 && i <= win->unk14 - 3) {
                if (i & 2)
                    t = 34;
                else
                    t = 35;
            } else if (i == win->unk14 - 2)
                t = 36;
            else
                t = 37;
            fn_02003C3C(px, py, 11, t, win->unk4, win->unk5, 0);
            px += 8;
        }
    }
}

void fn_020076A4(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 y;
    s32 py;
    s32 i;
    s32 t;
    s32 k;
    s32 attr;
    u16 *map;

    px = win->unk10 * 8;
    y = win->unk12 * 8 + win->unk1;
    py = y + 8;
    if ((py >> 3) - win->unk12 >= win->unk16)
        return;
    if (win->unk1 == 0) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                buf[i] = tile | pal;
            else if (i != win->unk14 - 1) {
                if (i & 1)
                    buf[i] = (tile + 1) | pal;
                else
                    buf[i] = (tile + 2) | pal;
            } else
                buf[i] = (tile + 3) | pal;
        }
        map = fn_02000A40(win->unk5, win->unk10, win->unk12);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        attr = (win->unk6 == 2 ? 5 : 6) << 12;
        for (i = 0; i < win->unk14; i++) {
            if (i & 1)
                buf[i] = (tile - 4) | attr;
            else
                buf[i] = (tile - 2) | attr;
        }
        buf[0] = pal | (tile + 4);
        buf[win->unk14 - 1] = pal | (tile + 5);
        map = fn_02000A40(win->unk5, win->unk10, win->unk12 + 1);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
    } else {
        k = win->unk1 >> 3;
        if (k != 0) {
            t = win->unk6 == 2 ? 0x238 : 0x29C;
            py = y;
            t += win->unk14 * 2 * ((k - 1) >> 1) + (~k & 1);
            attr = (win->unk6 == 2 ? 5 : 6) << 12;
            for (i = 1; i < win->unk14 - 1; i++) {
                if (i & 1) {
                    buf[i] = attr | t;
                } else {
                    buf[i] = (t + 2) | attr;
                    t += 4;
                }
            }
            if (k < win->unkE * 2) {
                buf[0] = (tile + 4) | pal;
                buf[win->unk14 - 1] = (tile + 5) | pal;
            } else {
                buf[0] = (tile + 6) | pal;
                buf[win->unk14 - 1] = (tile + 7) | pal;
            }
            map = fn_02000A40(win->unk5, win->unk10, py >> 3);
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
            py += 8;
            if (py >= (win->unk12 + win->unk16) * 8 - 8) {
                for (i = 0; i < win->unk14; i++) {
                    if (i == 0)
                        buf[i] = (tile + 8) | pal;
                    else if (i != win->unk14 - 1) {
                        if (i & 1)
                            buf[i] = (tile + 9) | pal;
                        else
                            buf[i] = (tile + 10) | pal;
                    } else
                        buf[i] = (tile + 11) | pal;
                }
                map = fn_02000A40(win->unk5, win->unk10, py >> 3);
                DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
            }
        }
    }
    if ((py >> 3) - win->unk12 - 1 < win->unk16) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                t = 8;
            else if (i != win->unk14 - 1)
                t = 10;
            else
                t = 11;
            fn_02003C3C(px, py, 12, t, win->unk4, win->unk5, 0);
            px += 8;
        }
    }
}

void fn_020079FC(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 y;
    s32 py;
    s32 i;
    s32 t;
    s32 k;
    s32 attr;
    u32 flags;
    u16 *map;

    px = win->unk10 * 8;
    y = win->unk12 * 8 + win->unk1;
    py = y + 8;
    if ((py >> 3) > win->unk12 + win->unk16)
        return;
    if (win->unk1 == 0) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0 || i == win->unk14 - 1)
                buf[i] = pal | tile;
            else if (i == 1 || i == win->unk14 - 2)
                buf[i] = (tile + 1) | pal;
            else
                buf[i] = (tile + 2) | pal;
            if (i >= win->unk14 - 2)
                buf[i] |= 0x400;
        }
        map = fn_02000A40(win->unk5, win->unk10, win->unk12);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        attr = fn_020059EC(win->items[0].unk0, win->unk6);
        for (i = 0; i < win->unk14; i++) {
            if (i & 1)
                buf[i] = (tile - 4) | attr;
            else
                buf[i] = (tile - 2) | attr;
        }
        buf[0] = pal | (tile + 3);
        buf[win->unk14 - 1] = (pal | (tile + 3)) | 0x400;
        map = fn_02000A40(win->unk5, win->unk10, win->unk12 + 1);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
    } else {
        k = (win->unk1 >> 3) - win->unk8;
        if (k != 0) {
            t = fn_02005A0C(win->unk6);
            py = y;
            t += win->unk14 * 2 * ((k - 1) >> 1) + (~k & 1);
            attr = fn_020059EC(win->items[(k - 1) >> 1].unk0, win->unk6);
            for (i = 1; i < win->unk14 - 1; i++) {
                if (i & 1) {
                    buf[i] = attr | t;
                } else {
                    buf[i] = (t + 2) | attr;
                    t += 4;
                }
            }
            k = win->unk1 >> 3;
            if (k == 1 || k == win->unk16 - 2)
                buf[0] = (tile + 3) | pal;
            else
                buf[0] = (tile + 4) | pal;
            buf[win->unk14 - 1] = buf[0] | 0x400;
            if (k >= win->unk16 - 2) {
                buf[0] |= 0x800;
                buf[win->unk14 - 1] |= 0x800;
            }
            map = fn_02000A40(win->unk5, win->unk10, py >> 3);
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
            py += 8;
            if (py >= (win->unk16 + win->unk12) * 8 - 8) {
                for (i = 0; i < win->unk14; i++) {
                    if (i == 0 || i == win->unk14 - 1)
                        buf[i] = pal | tile;
                    else if (i == 1 || i == win->unk14 - 2)
                        buf[i] = (tile + 1) | pal;
                    else
                        buf[i] = (tile + 2) | pal;
                    if (i >= win->unk14 - 2)
                        buf[i] |= 0x400;
                    buf[i] |= 0x800;
                }
                map = fn_02000A40(win->unk5, win->unk10, py >> 3);
                DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
            }
        }
    }
    if ((py >> 3) - win->unk12 < win->unk16) {
        for (i = 0; i < win->unk14; i++, px += 8) {
            flags = 0x20000000;
            if (i == 0 || i == win->unk14 - 1)
                t = 0;
            else if (i == 1 || i == win->unk14 - 2)
                t = 1;
            else
                t = 2;
            if (i >= win->unk14 - 2)
                flags |= 0x10000000;
            fn_02003C3C(px, py, 17, t, win->unk4, win->unk5, flags);
        }
    }
}

void fn_02007D9C(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 px;
    s32 y;
    s32 py;
    s32 i;
    s32 t;
    s32 n;
    u16 *map;

    px = win->unk10 * 8;
    y = win->unk12 * 8 + win->unk1;
    py = y + 8;
    if ((py >> 3) >= win->unk12 + win->unk16)
        return;
    if (win->unk1 == 0) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                buf[i] = tile | pal;
            else if (i != win->unk14 - 1) {
                if (i & 1)
                    buf[i] = (tile + 1) | pal;
                else
                    buf[i] = (tile + 2) | pal;
            } else
                buf[i] = (tile + 3) | pal;
        }
        map = fn_02000A40(0, win->unk10, win->unk12);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        for (i = 0; i < win->unk14; i++) {
            if (i & 1)
                buf[i] = (tile - 4) | 0xF000;
            else
                buf[i] = (tile - 2) | 0xF000;
        }
        buf[0] = pal | (tile + 4);
        buf[win->unk14 - 1] = pal | (tile + 5);
        map = fn_02000A40(0, win->unk10, win->unk12 + 1);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
    } else {
        n = win->unk1 >> 3;
        if (n == 1 || n == win->unkE * 2) {
            for (i = 0; i < win->unk14; i++) {
                if (i & 1)
                    buf[i] = (tile - 4) | 0xF000;
                else
                    buf[i] = (tile - 2) | 0xF000;
            }
            buf[0] = pal | (tile + 4);
            buf[win->unk14 - 1] = pal | (tile + 5);
            map = fn_02000A40(0, win->unk10, y >> 3);
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        } else {
            n--;
            t = win->unk14 * 2 * ((n - 1) >> 1) + 0x340 + (~n & 1);
            for (i = 1; i < win->unk14 - 1; i++) {
                if (i & 1) {
                    buf[i] = 0xF000 | t;
                } else {
                    buf[i] = (t + 2) | 0xF000;
                    t += 4;
                }
            }
            if (n < win->unkE * 2) {
                buf[0] = (tile + 4) | pal;
                buf[win->unk14 - 1] = (tile + 5) | pal;
            } else {
                buf[0] = (tile + 6) | pal;
                buf[win->unk14 - 1] = (tile + 7) | pal;
            }
            map = fn_02000A40(0, win->unk10, y >> 3);
            DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        }
        if (py >= (win->unk12 + win->unk16) * 8 - 8) {
            for (i = 0; i < win->unk14; i++) {
                if (i == 0)
                    buf[i] = (tile + 8) | pal;
                else if (i != win->unk14 - 1) {
                    if (i & 1)
                        buf[i] = (tile + 9) | pal;
                    else
                        buf[i] = (tile + 10) | pal;
                } else
                    buf[i] = (tile + 11) | pal;
            }
            map = fn_02000A40(0, win->unk10, (py >> 3));
            DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        }
    }
    if ((py >> 3) - win->unk12 < win->unk16 - 1) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                t = 8;
            else if (i != win->unk14 - 1)
                t = 10;
            else
                t = 11;
            fn_02003C3C(px, py, 12, t, win->unk4, 0, 0);
            px += 8;
        }
    }
}

void fn_02008178(struct Window *win)
{
    switch (win->unk3) {
    case -1:
        fn_02008CC0(win);
        break;
    case 0:
        if (win->unk4)
            fn_02008328(win);
        else
            fn_0200823C(win);
        break;
    case 1:
    case 2:
    case 13:
        fn_02008478(win);
        break;
    case 3:
        fn_02008540(win);
        break;
    case 4:
        fn_020086A8(win);
        break;
    case 5:
        fn_020087E8(win);
        break;
    case 6:
        fn_020088E0(win);
        break;
    case 7:
        fn_02008A48(win);
        break;
    case 8:
        fn_02008B8C(win);
        break;
    case 9:
        fn_02008CC0(win);
        break;
    case 10:
        fn_0200823C(win);
        break;
    case 14:
        fn_02008DB8(win);
        break;
    }
}

void fn_0200823C(struct Window *win)
{
    s32 px;
    s32 py;
    s32 i;
    s32 frame;
    u32 flags;

    px = win->unk10 * 8;
    py = (win->unk12 - 1 + win->unk16) * 8 - win->unk1;
    if (py >> 3 > win->unk12) {
        fn_020098F0(win->unk5, win->unk10, py >> 3, win->unk14, 1);
        if ((py >> 3) - 1 <= win->unk12)
            fn_020098F0(win->unk5, win->unk10, (py >> 3) - 1, win->unk14, 1);
        if ((py >> 3) - 1 > win->unk12) {
            py -= 8;
            flags = 0x20000000;
            for (i = 0; i < win->unk14; i++, px += 8) {
                if (i == 0 || i == win->unk14 - 1)
                    frame = 0;
                else if (i == 1 || i == win->unk14 - 2)
                    frame = 1;
                else if (i == 2 || i == win->unk14 - 3)
                    frame = 2;
                else
                    frame = 3;
                if (i >= win->unk14 >> 1)
                    flags |= 0x10000000;
                fn_02003C3C(px, py, 3, frame, win->unk4, win->unk5, flags);
            }
        }
    }
}

void fn_02008328(struct Window *win)
{
    s32 px;
    s32 py;
    s32 cols;
    s32 i;
    s32 frame;
    u32 flags;
    u16 tile;
    u16 *map;

    px = win->unk10 * 8 + win->unk1;
    py = win->unk12 * 8;
    if (win->unk5 <= 1)
        tile = 0x3FF;
    else
        tile = 0x2FF;
    cols = win->unk14 - ((win->unk1 >> 2) + 1);
    map = fn_02000A40(win->unk5, px >> 3, win->unk12);
    if (cols >= 0) {
        for (i = 0; i < win->unk16; i++) {
            map[0] = tile;
            map[cols] = tile;
            if (win->unk5 == 1 || win->unk5 == 2) {
                map[-0x400] = 0x3FF;
                map[cols - 0x400] = 0x3FF;
            }
            map += 32;
        }
        flags = 0;
        for (i = 0; i < win->unk16; i++, py += 8) {
            if (i == 0 || i + 1 >= win->unk16)
                frame = 6;
            else if (i == 1 || i + 2 >= win->unk16)
                frame = 9;
            else if (i == 2 || i + 3 >= win->unk16)
                frame = 10;
            else
                frame = 11;
            if (i >= win->unk16 >> 1)
                flags = 0x20000000;
            fn_02003C3C(px, py, 3, frame, 0, win->unk5, flags);
            fn_02003C3C(px + cols * 8, py, 3, frame, 0, win->unk5, flags | 0x10000000);
        }
    }
}

void fn_02008478(struct Window *win)
{
    s32 px;
    s32 py;
    s32 i;
    s32 id;
    s32 frame;

    px = win->unk10 * 8;
    py = (win->unk12 - 1 + win->unk16) * 8 - win->unk1;
    if (py >> 3 > win->unk12) {
        fn_020098F0(win->unk5, win->unk10, py >> 3, win->unk14, 1);
        if ((py >> 3) - 1 <= win->unk12)
            fn_020098F0(win->unk5, win->unk10, (py >> 3) - 1, win->unk14, 1);
        if ((py >> 3) - 1 > win->unk12) {
            py -= 8;
            for (i = 0; i < win->unk14; i++, px += 8) {
                if (win->unk3 == 1)
                    id = 4;
                else if (win->unk3 == 2)
                    id = 5;
                else
                    id = 16;
                if (i == 0)
                    frame = 8;
                else if (i != win->unk14 - 1)
                    frame = 10;
                else
                    frame = 11;
                fn_02003C3C(px, py, id, frame, win->unk4, win->unk5, 0);
            }
        }
    }
}

void fn_02008540(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    u16 tile;
    u16 *map;
    s32 frame;
    s32 bg;

    px = win->unk10 * 8;
    py = (win->unk12 - 1 + win->unk16) * 8 - win->unk1;
    if (py >> 3 > win->unk12) {
        if (win->unk5 <= 1)
            tile = 0x3FF;
        else
            tile = 0x2FF;
        for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
            buf[i] = tile;
        map = fn_02000A40(win->unk5, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 <= win->unk12)
            DmaSet(DMA3, buf, map - 32, 0x80000000 | win->unk14);
        bg = win->unk5;
        if (bg == 2) {
            for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
                buf[i] = 0x3FF;
        }
        map = fn_02000A40(bg - 1, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 <= win->unk12 && lbl_03003094)
            DmaSet(DMA3, buf, map - 32, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 > win->unk12) {
            py -= 8;
            for (i = 0; i < win->unk14; i++, px += 8) {
                if (i == 0)
                    frame = 6;
                else if (i + 1 >= win->unk14)
                    frame = 8;
                else
                    frame = 7;
                fn_02003C3C(px, py, 6, frame, win->unk4, win->unk5 - 1, 0);
            }
        }
    }
}

void fn_020086A8(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    u16 tile;
    u16 *map;
    s32 frame;
    s32 bg;

    px = win->unk10 * 8;
    py = (win->unk12 - 1 + win->unk16) * 8 - win->unk1;
    if (py >> 3 > win->unk12) {
        if (win->unk5 <= 1)
            tile = 0x3FF;
        else
            tile = 0x2FF;
        for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
            buf[i] = tile;
        map = fn_02000A40(win->unk5, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 <= win->unk12)
            DmaSet(DMA3, buf, map - 32, 0x80000000 | win->unk14);
        bg = win->unk5;
        if (bg == 2) {
            for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
                buf[i] = 0x3FF;
        }
        map = fn_02000A40(bg - 1, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 > win->unk12) {
            py -= 8;
            for (i = 0; i < win->unk14; i++, px += 8) {
                if (i == 0)
                    frame = 9;
                else if (i == win->unk14 - 2)
                    frame = 11;
                else if (i >= win->unk14 - 1)
                    frame = 12;
                else
                    frame = 10;
                fn_02003C3C(px, py, 7, frame, win->unk4, win->unk5 - 1, 0);
            }
        }
    }
}

void fn_020087E8(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    u16 tile;
    u16 *map;
    s32 frame;

    px = win->unk10 * 8;
    py = (win->unk12 - 1 + win->unk16) * 8 - win->unk1;
    if (py >> 3 > win->unk12) {
        if (win->unk5 <= 1)
            tile = 0x3FF;
        else
            tile = 0x2FF;
        for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
            buf[i] = tile;
        map = fn_02000A40(win->unk5, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 <= win->unk12)
            DmaSet(DMA3, buf, map - 32, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 > win->unk12) {
            py -= 8;
            for (i = 0; i < win->unk14; i++, px += 8) {
                if (i == 0)
                    frame = 8;
                else if (i != win->unk14 - 1)
                    frame = 10;
                else
                    frame = 11;
                fn_02003C3C(px, py, 8, frame, win->unk4, win->unk5, 0);
            }
        }
    }
}

void fn_020088E0(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    u16 tile;
    u16 *map;
    s32 frame;
    s32 bg;

    px = win->unk10 * 8;
    py = (win->unk12 - 1 + win->unk16) * 8 - win->unk1;
    if (py >> 3 > win->unk12) {
        if (win->unk5 <= 1)
            tile = 0x3FF;
        else
            tile = 0x2FF;
        for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
            buf[i] = tile;
        map = fn_02000A40(win->unk5, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 <= win->unk12)
            DmaSet(DMA3, buf, map - 32, 0x80000000 | win->unk14);
        bg = win->unk5;
        if (bg == 2) {
            for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
                buf[i] = 0x3FF;
        }
        map = fn_02000A40(bg - 1, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 <= win->unk12 && lbl_03003094)
            DmaSet(DMA3, buf, map - 32, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 > win->unk12) {
            py -= 8;
            for (i = 0; i < win->unk14; i++, px += 8) {
                if (i == 0)
                    frame = 6;
                else if (i + 1 >= win->unk14)
                    frame = 8;
                else
                    frame = 7;
                fn_02003C3C(px, py, 9, frame, win->unk4, win->unk5 - 1, 0);
            }
        }
    }
}

void fn_02008A48(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    u16 tile;
    u16 *map;
    s32 frame;

    px = win->unk10 * 8;
    py = (win->unk12 - 1 + win->unk16) * 8 - win->unk1;
    if (py >> 3 > win->unk12) {
        if (win->unk5 <= 1)
            tile = 0x3FF;
        else
            tile = 0x2FF;
        for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
            buf[i] = tile;
        map = fn_02000A40(win->unk5, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        if (win->unk5 == 2) {
            for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
                buf[i] = 0x3FF;
        }
        map = fn_02000A40(win->unk5 - 1, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        if ((py >> 3) - 2 <= win->unk12) {
            for (i = 0; i < 2; i++) {
                map -= 32;
                DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
            }
        }
        if ((py >> 3) - 2 > win->unk12) {
            py -= 8;
            for (i = 0; i < win->unk14; i++, px += 8) {
                if (i == 0)
                    frame = 28;
                else if (i + 1 >= win->unk14)
                    frame = 30;
                else
                    frame = 29;
                fn_02003C3C(px, py, 10, frame, win->unk4, win->unk5 - 1, 0);
            }
        }
    }
}

void fn_02008B8C(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    u16 tile;
    u16 *map;
    s32 frame;

    px = win->unk10 * 8;
    py = (win->unk12 - 1 + win->unk16) * 8 - win->unk1;
    if (py >> 3 >= win->unk12) {
        tile = win->unk5 <= 1 ? 0x3FF : 0x2FF;
        for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
            buf[i] = tile;
        map = fn_02000A40(win->unk5, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
            buf[i] = 0x3FF;
        map = fn_02000A40(win->unk5 - 1, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 > win->unk12) {
            py -= 8;
            for (i = 0; i < win->unk14; i++, px += 8) {
                if (i == 0)
                    frame = 32;
                else if (i == 1)
                    frame = 33;
                else if (i > 1 && i <= win->unk14 - 3) {
                    if (i & 2)
                        frame = 34;
                    else
                        frame = 35;
                } else if (i == win->unk14 - 2)
                    frame = 36;
                else
                    frame = 37;
                fn_02003C3C(px, py, 11, frame, win->unk4, win->unk5, 0);
            }
        }
    }
}

void fn_02008CC0(struct Window *win)
{
    u16 buf[30];
    s32 px;
    s32 py;
    s32 i;
    u16 tile;
    u16 *map;
    s32 frame;

    px = win->unk10 * 8;
    py = (win->unk12 - 1 + win->unk16) * 8 - win->unk1;
    if (py >> 3 > win->unk12) {
        if (win->unk5 <= 1)
            tile = 0x3FF;
        else
            tile = 0x2FF;
        for (i = 0; i < sizeof(buf) / sizeof(buf[0]); i++)
            buf[i] = tile;
        map = fn_02000A40(win->unk5, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 <= win->unk12)
            DmaSet(DMA3, buf, map - 32, 0x80000000 | win->unk14);
        if ((py >> 3) - 1 > win->unk12) {
            py -= 8;
            for (i = 0; i < win->unk14; i++, px += 8) {
                if (i == 0)
                    frame = 8;
                else if (i != win->unk14 - 1)
                    frame = 10;
                else
                    frame = 11;
                fn_02003C3C(px, py, 12, frame, win->unk4, win->unk5, 0);
            }
        }
    }
}

void fn_02008DB8(struct Window *win)
{
    s32 px;
    s32 py;
    s32 i;
    s32 frame;
    u32 flags;

    px = win->unk10 * 8;
    py = (win->unk12 - 1 + win->unk16) * 8 - win->unk1;
    if (py >> 3 > win->unk12) {
        fn_020098F0(win->unk5, win->unk10, py >> 3, win->unk14, 1);
        if ((py >> 3) - 1 <= win->unk12)
            fn_020098F0(win->unk5, win->unk10, (py >> 3) - 1, win->unk14, 1);
        if ((py >> 3) - 1 > win->unk12) {
            py -= 8;
            for (i = 0; i < win->unk14; i++, px += 8) {
                flags = 0x20000000;
                if (i == 0 || i == win->unk14 - 1)
                    frame = 0;
                else if (i == 1 || i == win->unk14 - 2)
                    frame = 1;
                else
                    frame = 2;
                if (i >= win->unk14 - 2)
                    flags |= 0x10000000;
                fn_02003C3C(px, py, 17, frame, win->unk4, win->unk5, flags);
            }
        }
    }
}

void fn_02008E88(s32 prio, s32 x, s32 y, s32 n, s32 offset, s32 mode)
{
    s32 px;
    s32 i;
    s32 id;
    s32 frame;

    px = x + offset;
    id = y + 10;
    if (mode == 0) {
        for (i = 0; i <= 9; i++, px += 16)
            fn_02003C3C(px, id, 22, i, 0, 0, 0);
    }
    px = x;
    if (mode == 0)
        id = 15;
    else
        id = 18;
    for (i = 0; i < n; i++, px += 8) {
        s32 k = i;

        if (i <= 2)
            frame = i;
        else if (i >= n - 3)
            frame = 7 - (n - i);
        else
            frame = 3;
        fn_02003C3C(px, y, id, frame, 0, prio, k);
        fn_02003C3C(px, y + 16, id, frame + 7, 0, prio, k);
    }
}

void fn_02008F48(struct Cmd cmd)
{
    u16 v;

    v = (cmd.unk[1] << 8) | cmd.unk[2];
    if ((v & 0xFF) != (lbl_030032E4 & 0xFF)) {
        lbl_03003090 = 0;
        lbl_030032FC[0] = 0;
        lbl_030032FC[1] = 0xFF;
    }
    lbl_030032E4 = v;
}

void fn_02008F8C(s32 x, s32 y, s32 len, s32 pal, u32 value, s32 color)
{
    u32 max;
    s32 i;
    s32 div;
    u32 rem;
    s32 digit;
    s32 c;

    div = (len * 8 - 80) >> 1;
    x += div;
    max = 1;
    for (i = 0; i < 8; i++)
        max *= 10;
    div = max / 10;
    rem = value;
    if (color < 0)
        c = fn_02004030(1, 0);
    else
        c = color;
    for (i = 0; i < 8; i++, x += 8, rem %= div, div /= 10) {
        if (value >= max) {
            digit = 9;
        } else {
            digit = rem / div;
            if (digit == 0 && value <= div && i + 1 < 8)
                continue;
        }
        fn_02003C3C(x, y, 1, digit, c, pal, 0);
    }
    if ((lbl_03002C98 & 15) == 1)
        i = 54;
    else
        i = 44;
    c = fn_02004030(0, i);
    fn_02003C3C(x + 1, y, 0, i, c, pal, 0);
}

void fn_0200907C(s32 x, s32 y, s32 n, s32 pal, s32 fill)
{
    s32 i;
    s32 k;
    s32 frame;
    u32 flags;

    k = 0;
    for (i = 0; i < n; i++, x += 8) {
        flags = 0;
        if (i == 0 || i + 1 >= n) {
            frame = 0;
            if (i != 0)
                flags = 0x10000000;
        } else {
            k += 2;
            if (k <= fill) {
                if (fill <= 4)
                    frame = 22;
                else if (fill <= 6)
                    frame = 20;
                else
                    frame = 1;
            } else if (k == fill + 1) {
                if (fill <= 4)
                    frame = 23;
                else if (fill <= 6)
                    frame = 21;
                else
                    frame = 2;
            } else {
                frame = 3;
            }
        }
        fn_02003C3C(x, y, 2, frame, fn_02004030(2, frame), pal, flags);
    }
}

void fn_0200911C(struct Cmd cmd)
{
    lbl_03003094 = cmd.unk[1];
    if (lbl_03003094 != 0) {
        lbl_03002CA0.unk128 = 0;
        if (lbl_03003094 == 4) {
            fn_02001438(33, 0);
            lbl_03002FD0[fn_02002FAC()].unk7 = 0;
        }
    }
    if (lbl_03003094 == 0 || lbl_03003094 == 4)
        lbl_03002ACC = 0;
    else
        lbl_03002ACC = 1;
    if (lbl_03003094 == 1)
        fn_02009318();
    fn_02019C4C();
    if (lbl_030029A0)
        lbl_03003090 = 0;
    else
        lbl_030032E8 = 0;
    lbl_030032FC[0] = 0;
    lbl_030032FC[1] = 0xFF;
    fn_02005844();
    fn_02000990();
    fn_0200194C(0);
    fn_02000A74();
}
