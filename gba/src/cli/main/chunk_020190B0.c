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

struct Work {
    u8 unk0[0x54];
    u8 unk54[8];
    u8 unk5C;
    u8 unk5D;
    s8 unk5E[6];
    s16 unk64[64];
    u8 unkE4[0x48];
};

struct ItemInfo {
    u16 flags;
    u16 count;
    u16 kind;
    u16 unk6;
};

struct Recipe {
    u8 unk0[16];
    s16 ids[4];
    struct ItemInfo items[4];
};

extern s8 lbl_03002821;
extern s8 lbl_03002822;
extern s8 lbl_03002823;
extern s8 lbl_03002824;
extern s8 lbl_03002825;
extern s8 lbl_03002826;
extern s8 lbl_03002828;
extern s8 lbl_03002829;
extern s8 lbl_0300282A;
extern s8 lbl_0300282C;
extern u32 lbl_03002830[];
extern s8 lbl_03002840[8];
extern s8 lbl_03002848;
extern s8 lbl_03002849;
extern s8 lbl_0300284C;
extern s8 lbl_0300284D;
extern s8 lbl_0300284E;
extern s8 lbl_0300284F;
extern u8 lbl_03002998;
extern u16 lbl_030029AC;
extern u8 lbl_03002ACC;
extern u8 lbl_03002C98;
extern struct Work lbl_03002CA0;
extern s32 lbl_03003090;
extern s8 lbl_03003098;
extern s32 lbl_030030A4;
extern s32 lbl_030030AC;
extern struct Window lbl_030030B0[];
extern s8 lbl_030032E0;
extern s32 lbl_030032EC;
extern s8 lbl_0203A800;
extern s8 lbl_0203A801[];
extern const char lbl_0201D054[];

void *memset(void *, int, u32);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
void m4aSongNumStart(u16);
u16 *fn_02000A40(s32, s32, s32);
void fn_02000CF0(s32, s32, s32);
void fn_020032DC(u8, u8);
void fn_02003394(s32, s32);
void fn_020033F4(void);
s32 fn_02003464(const char *, s32);
void fn_020037A8(u32, s32);
void fn_020037C8(s32, s32, s32);
void fn_02003890(u32, s32);
void fn_020038D8(u32);
void fn_020038F4(s32);
void fn_02003900(s32);
s32 fn_02003910(void);
void fn_02003C3C(s32, s32, s32, s32, s32, s32, s32);
s32 fn_02004030(s32, s32);
void fn_02004098(s32, s32, s32, s32);
void fn_020041D4(s32, s32);
void fn_02004320(s32);
s32 fn_02004E74(s32);
void fn_02005968(struct Window *);
void fn_020059D4(struct Window *, s32, s32);
s32 fn_02005A0C(s32);
void fn_02005A50(struct Window *);
void fn_02008178(struct Window *);
void fn_0200907C(s32, s32, s32, s32, s32);
u32 fn_02009340(struct Window *, s32, s32);
void fn_020093B4(s32, s32);
s32 fn_02009414(s32);
void fn_020095AC(s32);
void fn_02009AB8(s32, s32, s32, s32, s32);
void fn_02009B80(struct Window *, s32);
void fn_02009C54(s32, s32, s32, s32);
void fn_02009CBC(s32, s32, s32);
void fn_02009D68(s32, s32);
void fn_02009DA8(s32, s32);
void fn_020189A8(void);
s32 fn_02018A0C(void);
void fn_0201A568(void);
void fn_0201A5EC(void);
void fn_0201A664(s32);
char *fn_0201A6D4(s32);
char *fn_0201A73C(s32);
char *fn_0201A83C(s32);
char *fn_0201AAAC(s32);
s32 fn_0201AB14(s32);

void fn_0201978C(void);
s32 fn_02019A24(void);
s32 fn_02019B20(void);
void fn_02019B54(void);
void fn_0201A038(void);
void fn_0201A100(s32 idx);
void fn_0201A1C8(void);
void fn_0201A248(void);

static inline struct Recipe *GetRecipe(void)
{
    s32 n = lbl_0203A800;
    struct Recipe *p;

    n++;
    if (n & 3)
        n = ((n >> 2) + 1) << 2;
    p = (struct Recipe *)((u8 *)&lbl_0203A800 + n);
    return &p[lbl_03002823];
}

void fn_020190B0(void)
{
    u16 buf[2][30];
    struct Window *win = lbl_030030B0;
    s32 attr = 3 << 12;
    s32 t = 0;
    s32 i;
    s32 size;
    u16 *map;

    for (i = 0; i < win->unk14; i++) {
        if (!(i & 1)) {
            buf[0][i] = attr | t;
            buf[1][i] = attr | (t + 1);
        } else {
            buf[0][i] = attr | 2 | t;
            buf[1][i] = attr | 3 | t;
        }
    }
    map = fn_02000A40(win->unk5, win->unk10 + 1, win->unk12 + 1);
    size = (win->unk14 - 2) * 2;
    for (i = 1; i < win->unk16 - 1; i++) {
        if (i & 1) {
            DmaSet(DMA3, buf[0], map, 0x80000000 | (size / 2));
        } else {
            DmaSet(DMA3, buf[1], map, 0x80000000 | (size / 2));
        }
        map += 32;
    }
}

void fn_02019180(s32 idx, s32 pal)
{
    u16 buf[30];
    s32 attr = pal << 12;
    s32 y = lbl_030030B0[0].unk12 + 1 + idx * 2;
    s32 w;
    s32 t;
    s32 i;
    s32 j;
    s32 bg;
    s32 row;
    u16 *map;

    if (lbl_03003090 == 2 && idx != 0)
        y++;
    w = lbl_030030B0[0].unk14 - 2;
    for (i = 0; i < 2; i++) {
        t = (lbl_030030B0[0].unk14 << 1) * idx + 128;
        t += i;
        j = 0;
        bg = lbl_030030B0[0].unk5;
        row = y + i;
        for (; j < w; j++) {
            if (!(j & 1)) {
                buf[j] = attr | t;
            } else {
                buf[j] = (t + 2) | attr;
                t += 4;
            }
        }
        map = fn_02000A40(bg, lbl_030030B0[0].unk10 + 1, row);
        DmaCopy16(DMA3, buf, map, w * 2);
    }
}

s32 fn_0201925C(void)
{
    struct Window *win = &lbl_030030B0[1];
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
        lbl_03002825 = ret;
        ret = 1;
    }
    win->unk1 += 8;
    return ret;
}

s32 fn_020192D0(void)
{
    s32 ret = 0;
    struct Window *win = &lbl_030030B0[1];

    fn_02003394(0, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        lbl_03002825 = ret;
        ret = 1;
    }
    win->unk1 += 8;
    return ret;
}

void fn_02019310(s8 val)
{
    lbl_03002826 = val;
}

void fn_0201931C(void)
{
    s32 i;

    lbl_030030A4 = 0;
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);

    lbl_030030B0[0].unk0 = 1;
    lbl_030030B0[0].unk2 = 0;
    lbl_030030B0[0].unk10 = 13;
    lbl_030030B0[0].unk12 = 1;
    lbl_030030B0[0].unkE = 5;
    lbl_030030B0[0].unk14 = 16;
    lbl_030030B0[0].unk16 = 11;
    lbl_030030B0[0].unk3 = 13;
    lbl_030030B0[0].unk4 = 0;
    lbl_030030B0[0].unk5 = 2;
    lbl_030030B0[0].unk6 = 0;
    lbl_030030B0[0].unk7 = 0;
    lbl_030030B0[0].unk8 = 1;

    lbl_030030B0[1].unk0 = 1;
    lbl_030030B0[1].unk2 = 0;
    lbl_030030B0[1].unk10 = 4;
    lbl_030030B0[1].unk12 = 12;
    lbl_030030B0[1].unkE = 2;
    lbl_030030B0[1].unk14 = 9;
    lbl_030030B0[1].unk16 = 4;
    lbl_030030B0[1].unk3 = 3;
    lbl_030030B0[1].unk4 = 0;
    lbl_030030B0[1].unk5 = 1;
    lbl_030030B0[1].unk6 = 1;
    lbl_030030B0[1].unk7 = 0;

    fn_020037C8(3, 0, 0);
    fn_020037C8(4, 4, 0);
    fn_020037C8(5, 3, 0);
    fn_02003890(0x050000E0, 0);
    fn_02003890(0x05000100, 2);
    fn_020041D4(16, 0);
    fn_020041D4(6, 0);
    fn_020041D4(12, 0);
    fn_02004098(16, 0, 2, 0);
    fn_02004098(6, 1, 1, 0);
    fn_02004098(12, 3, 1, 0);
    fn_020038D8(0x06008000);
    fn_02003394(1, 1);
    fn_020033F4();
    fn_020037C8(6, 0, 1);
    fn_020038D8(0x06000C00);
    fn_02009B80(lbl_030030B0, 1);
    for (i = 0; i < 16; i++)
        ;
    for (i = 0; i < lbl_030030B0[1].unkE; i++) {
        lbl_030030B0[1].items[i].unk0 = 1;
        if (i == 0)
            lbl_030030B0[1].items[i].unk4 = fn_0201A73C(26);
        else
            lbl_030030B0[1].items[i].unk4 = fn_0201A73C(4);
    }
    lbl_030032EC = 0;
    lbl_03002822 = 0;
    lbl_03002821 = 0;
    lbl_03002824 = 1;
    lbl_03002825 = 0;
    lbl_03002828 = 0;
    lbl_03002829 = 0;
    lbl_030030AC = 1;
}

s32 fn_020194F8(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    if (lbl_030030AC == 0)
        fn_0201931C();
    win = lbl_030030B0;
    fn_02003394(1, 0);
    fn_020033F4();
    fn_0201978C();
    fn_02005A50(win);
    if ((win->unk1 >> 3) == 3)
        win->unk8 = 0;
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        win->unk1 = 0;
        ret = 1;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

s32 fn_02019560(void)
{
    s32 ret;
    s32 x;
    s32 y;
    s32 frame;
    s32 id;

    fn_02003394(1, 0);
    id = GetRecipe()->ids[lbl_0300282A];
    x = (lbl_030030B0[0].unk10 + 1) * 8;
    y = (lbl_030030B0[0].unk12 + 2) * 8;
    frame = fn_0201AB14(id);
    fn_02003C3C(x, y, 0, frame, fn_02004030(0, frame), lbl_030030B0[0].unk5, 0);
    ret = 0;
    if (lbl_030032EC == 0 || lbl_030030A4 == 1) {
        if (lbl_03002ACC)
            ret = fn_02018A0C();
    } else if (lbl_030032EC == 1 && lbl_030030A4 == 0) {
        ret = fn_0201925C();
        if (ret) {
            lbl_030030A4++;
            lbl_030030B0[1].unk1 = 0;
        }
        ret = 0;
    } else if (lbl_030032EC == 1 && lbl_030030A4 == 2) {
        ret = fn_020192D0();
        if (ret) {
            lbl_030030A4 = 0;
            lbl_030030B0[1].unk1 = 0;
            if (lbl_03002829) {
                lbl_030032EC++;
                ret = 0;
            } else {
                lbl_030032EC = 0;
                if (lbl_03002822)
                    ret = lbl_03002822;
                else
                    ret = 0;
            }
        }
    } else if (lbl_030032EC == 2 && lbl_030030A4 == 0) {
        ret = fn_02019A24();
        if (ret) {
            lbl_030030A4++;
            lbl_030030B0[1].unk1 = 0;
        }
        ret = 0;
    } else if (lbl_030032EC == 2 && lbl_030030A4 == 2) {
        ret = fn_02019B20();
        if (ret) {
            lbl_030030A4 = 0;
            lbl_030030B0[1].unk1 = 0;
            lbl_030032EC = 0;
            lbl_03002829 = 0;
            if (lbl_03002822)
                ret = lbl_03002822;
            else
                ret = 0;
        }
    }
    if (lbl_030030A4 == 1) {
        if (lbl_030032EC != 0 && lbl_03002ACC)
            fn_020189A8();
        if (lbl_030032EC == 2)
            fn_02019B54();
    }
    return ret;
}

s32 fn_0201972C(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    fn_020033F4();
    win = lbl_030030B0;
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        lbl_03002998 = 6;
        ret = lbl_03002822;
        fn_02004320(16);
        fn_02004320(6);
        fn_02004320(12);
    }
    win->unk1 += 8;
    return ret;
}

void fn_0201978C(void)
{
    struct Window *win = lbl_030030B0;
    struct Recipe *recipe;
    u32 dst;
    u16 flags;
    u16 count;
    u16 kind;
    s32 id;
    s32 n;
    s32 msg;
    s32 x;
    s32 digits;
    char *str;

    if (lbl_03002821 >= win->unkE)
        return;
    n = lbl_0203A800;
    n++;
    if (n & 3)
        n = ((n >> 2) + 1) << 2;
    recipe = (struct Recipe *)((u8 *)&lbl_0203A800 + n);
    recipe = &recipe[lbl_03002823];
    dst = fn_02009340(win, lbl_03002821, 0);
    flags = recipe->items[lbl_0300282A].flags;
    count = recipe->items[lbl_0300282A].count;
    kind = recipe->items[lbl_0300282A].kind;
    fn_02003394(1, 0);
    fn_020033F4();
    if (lbl_03002821 == 0) {
        id = recipe->ids[lbl_0300282A];
        fn_020038F4(16);
        fn_02003464(fn_0201AAAC(id), 0);
        fn_020037A8(dst, win->unk14);
    } else if (lbl_03002821 == 1) {
        fn_020037A8(dst, win->unk14);
    } else if (lbl_03002821 == 2) {
        fn_020038F4(0);
        if (flags & 0x3000) {
            fn_02003464(fn_0201A83C(kind - 1), 0);
            if (count != 0 && kind != 16) {
                x = fn_02004E74(kind);
                msg = 39;
                if (x)
                    msg = 40;
                x = fn_02003464(fn_0201A73C(msg), 2);
                if (count <= 9)
                    digits = 1;
                else if (count <= 99)
                    digits = 2;
                else
                    digits = 3;
                x = (win->unk14 - 2) * 8 - digits * 9 - x;
                fn_020038F4(x);
                fn_02003464(fn_0201A73C(msg), 0);
                fn_02000CF0(count, fn_02003910(), digits);
            }
        } else {
            if (flags & 0x100)
                str = fn_0201A73C(16);
            else
                str = fn_0201A73C(63);
            fn_020038F4(0);
            fn_02003464(str, 0);
            x = win->unk14 * 8 - 34;
            fn_02000CF0(count, x, 2);
        }
        fn_020037A8(dst, win->unk14);
    } else if (lbl_03002821 == 3 && (flags & 0xE00)) {
        if (kind != 0) {
            fn_020038F4(0);
            fn_02003464(fn_0201A83C(kind - 1), 0);
        }
        fn_020037A8(dst, win->unk14);
    } else {
        fn_020037A8(dst, win->unk14);
    }
    lbl_03002821++;
}

s32 fn_02019978(s32 val)
{
    struct ItemInfo *item = GetRecipe()->items + lbl_0300282A;
    s32 slot;

    if (item->flags & 0x100) {
        lbl_03002CA0.unk5E[0] = val;
        slot = 0;
    } else if (item->flags & 0x400) {
        lbl_03002CA0.unk5E[1] = val;
        slot = 1;
    } else if (item->flags & 0xA00) {
        lbl_03002CA0.unk5E[2] = val;
        slot = 2;
    } else {
        lbl_03002CA0.unk5E[3] = val;
        slot = 3;
    }
    fn_020032DC(slot, val);
    return 0;
}

s32 fn_02019A24(void)
{
    struct Window *win = &lbl_030030B0[3];
    s32 ret;
    s32 i;

    fn_02003394(1, 1);
    fn_020033F4();
    if (lbl_03002828 == 0) {
        memset(win, 0, sizeof(struct Window));
        fn_02003394(1, 1);
        fn_020033F4();
        win->unk0 = 1;
        win->unk10 = 14;
        win->unkE = 2;
        win->unk14 = 15;
        win->unk16 = 6;
        win->unk12 = win[-3].unk12 + win[-3].unk16 - 6;
        win->unk3 = 9;
        win->unk4 = 0;
        win->unk5 = 1;
        win->unk6 = 3;
        win->unk7 = 16;
        for (i = 0; i < win->unkE; i++) {
            win->items[i].unk0 = 1;
            win->items[i].unk4 = fn_0201AAAC(lbl_03002CA0.unkE4[lbl_03002CA0.unk5E[i + 3]]);
        }
        lbl_03002828 = 1;
    }
    fn_02005968(win);
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) >= win->unk16) {
        ret = 1;
        win->unk1 = 0;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

s32 fn_02019B20(void)
{
    struct Window *win = &lbl_030030B0[3];
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

void fn_02019B54(void)
{
    struct Window *win = &lbl_030030B0[3];
    s32 x;
    s32 y;
    s32 frame;
    s32 i;

    fn_0201978C();
    x = (win->unk10 + 1) * 8;
    y = (win->unk12 + 1) * 8;
    for (i = 0; i < win->unkE; i++, y += 16) {
        frame = fn_0201AB14(lbl_03002CA0.unkE4[lbl_03002CA0.unk5E[i + 3]]);
        fn_02003C3C(x, y, 0, frame, fn_02004030(0, frame), win->unk5, 0);
    }
}

void fn_02019BE8(s32 idx, s32 row)
{
    s32 id;

    fn_02003394(1, 0);
    fn_020033F4();
    fn_020038F4(16);
    id = lbl_03002CA0.unk64[lbl_0203A801[idx]];
    if (id > 0)
        fn_02003464(fn_0201AAAC(id), 0);
    fn_020037A8(lbl_030030B0[0].unk14 * 64 * row + 0x06009000, lbl_030030B0[0].unk14);
}

void fn_02019C4C(void)
{
    lbl_0300282C = 0;
}

void fn_02019C58(u16 *flags, char *dst)
{
    s32 lo = *flags & 15;
    s32 hi = *flags & 0x30;
    s32 i;

    *dst = 0;
    if (hi) {
        if (lo) {
            for (i = 0; i < 4; i++) {
                if ((lo >> i) & 1) {
                    strcpy(dst, fn_0201A6D4(i));
                    if ((lbl_03002C98 & 15) == 1)
                        strcat(dst, lbl_0201D054);
                    break;
                }
            }
        }
        if (hi == 16)
            strcat(dst, fn_0201A73C(27));
        else
            strcat(dst, fn_0201A73C(28));
    } else if (lo == 15) {
        strcpy(dst, fn_0201A73C(29));
    } else {
        for (i = 0; i < 4; i++) {
            if ((lo >> i) & 1) {
                strcpy(dst, fn_0201A6D4(i));
                break;
            }
        }
    }
}

s32 fn_02019D0C(s32 idx)
{
    s32 id = lbl_03002CA0.unk64[lbl_0203A801[idx]];
    s32 q;
    s32 r;

    if (id <= 0)
        return 0;
    id -= 401;
    q = id / 32;
    r = id % 32;
    return (lbl_03002830[q] & (1 << r)) != 0;
}

s32 fn_02019D68(s32 idx)
{
    s8 *list = &lbl_0203A800;
    s32 id;

    if (*list++ > idx) {
        id = lbl_03002CA0.unk64[list[idx]];
        if (id > 0)
            return id;
    }
    return -1;
}

void fn_02019DA0(void)
{
    s32 i;
    s32 j;
    s32 max;
    s32 tmp;

    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    lbl_030030B0[0].unk0 = 1;
    lbl_030030B0[0].unk2 = 0;
    lbl_030030B0[0].unk10 = 1;
    lbl_030030B0[0].unk12 = 0;
    lbl_030030B0[0].unkE = 8;
    lbl_030030B0[0].unk14 = 28;
    lbl_030030B0[0].unk16 = 18;
    lbl_030030B0[0].unk3 = 0;
    lbl_030030B0[0].unk4 = 1;
    lbl_030030B0[0].unk5 = 2;
    lbl_030030B0[0].unk6 = 0;
    lbl_030030B0[0].unk7 = 0;
    fn_02009B80(lbl_030030B0, 1);
    fn_02003394(1, 0);
    fn_020038D8(0x06008000);
    fn_020037C8(3, 0, 0);
    fn_020041D4(3, 1);
    fn_02004098(3, 0, 2, 1);
    for (i = 0; i < 8; i++)
        lbl_03002840[i] = i;
    for (i = 0; i < 8; i++) {
        max = lbl_03002CA0.unk54[lbl_03002840[i]];
        for (j = i + 1; j < 8; j++) {
            if (max < lbl_03002CA0.unk54[lbl_03002840[j]]) {
                tmp = lbl_03002840[i];
                lbl_03002840[i] = lbl_03002840[j];
                lbl_03002840[j] = tmp;
                max = lbl_03002CA0.unk54[lbl_03002840[i]];
            }
        }
    }
    lbl_03002848 = 0;
    lbl_03002849 = 1;
    lbl_030030AC = 1;
}

s32 fn_02019ECC(void)
{
    struct Window *win;
    s32 ret;
    s32 i;

    if (lbl_030030AC == 0)
        fn_02019DA0();
    win = lbl_030030B0;
    fn_02003394(1, 0);
    fn_020033F4();
    fn_02005968(win);
    if (win->items[win->unkE - 1].unk2 == 0)
        return 0;
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 2) < win->unk14) {
        win->unk1 += 8;
    } else {
        for (i = 0; i < win->unkE; i++)
            fn_0201A100(i);
        ret = 1;
        win->unk1 = 0;
    }
    return ret;
}

s32 fn_02019F50(void)
{
    struct Window *win = lbl_030030B0;
    s32 ret = 0;

    if (lbl_03002848 < win->unkE) {
        fn_0201A038();
        return 0;
    }
    if (lbl_03002ACC) {
        if (lbl_030029AC & 1) {
            m4aSongNumStart(0);
        } else if (lbl_030029AC & 2) {
            lbl_030032E0 = 1;
            m4aSongNumStart(3);
            ret = 1;
        } else if (lbl_030029AC & 0x300) {
            if (lbl_030029AC & 0x100)
                lbl_03003098 = 1;
            else
                lbl_03003098 = -1;
            ret = 1;
            m4aSongNumStart(6);
        }
    }
    fn_0201A248();
    fn_0201A1C8();
    return ret;
}

s32 fn_0201A000(void)
{
    struct Window *win = lbl_030030B0;
    s32 ret;

    fn_02008178(win);
    ret = 0;
    if ((win->unk1 >> 2) < win->unk14) {
        win->unk1 += 8;
    } else {
        ret = 1;
        fn_02004320(3);
        win->unk1 = 0;
    }
    return ret;
}

void fn_0201A038(void)
{
    char buf[2];
    struct Window *win = lbl_030030B0;
    s32 i;
    s32 score;

    if (lbl_03002848 >= win->unkE)
        return;
    fn_02003394(1, 0);
    fn_020033F4();
    buf[0] = lbl_03002849 + '0';
    buf[1] = 0;
    fn_020038F4(8);
    fn_02003464(buf, 1);
    fn_02003900(24);
    score = lbl_03002840[lbl_03002848];
    fn_02003464(fn_0201AAAC(score + 381), 0);
    fn_020059D4(win, lbl_03002848, 0);
    i = lbl_03002848;
    if (i < win->unkE - 1) {
        score = lbl_03002CA0.unk54[lbl_03002840[i]];
        if (score != lbl_03002CA0.unk54[lbl_03002840[i + 1]])
            lbl_03002849 = lbl_03002848 + 2;
    }
    lbl_03002848++;
}

void fn_0201A100(s32 idx)
{
    u16 buf[30];
    struct Window *win = lbl_030030B0;
    u16 *map;
    s32 attr;
    s32 y;
    s32 w;
    s32 t;
    s32 i;
    s32 j;

    y = win->unk12 + 1 + idx * 2;
    w = win->unk14 - 2;
    map = fn_02000A40(win->unk5, win->unk10 + 1, y);
    attr = 3 << 12;
    for (i = 0; i < 2; i++, map += 32) {
        t = fn_02005A0C(0);
        t += (win->unk14 << 1) * idx;
        t += i;
        for (j = 0; j < w; j++) {
            if (j & 1) {
                buf[j] = (t + 2) | attr;
                t += 4;
            } else {
                buf[j] = attr | t;
            }
        }
        DmaCopy16(DMA3, buf, map, w * 2);
    }
}

void fn_0201A1C8(void)
{
    struct Window *win = lbl_030030B0;
    s32 x;
    s32 y;
    s32 frame;
    s32 i;

    x = (win->unk10 + 3) * 8;
    y = (win->unk12 + 1) * 8;
    x += 5;
    y -= 2;
    for (i = 0; i < win->unkE; i++, y += 16) {
        frame = fn_0201AB14(lbl_03002840[i] + 381);
        fn_02003C3C(x, y, 0, frame, fn_02004030(0, frame), win->unk5, 0);
    }
}

void fn_0201A248(void)
{
    struct Window *win = lbl_030030B0;
    s32 x;
    s32 y;
    s32 i;

    x = (win->unk10 + 16) * 8;
    y = (win->unk12 + 1) * 8 + 4;
    for (i = 0; i < win->unkE; i++, y += 16) {
        fn_0200907C(x, y, 7, 2, (lbl_03002CA0.unk54[lbl_03002840[i]] + 9) / 10);
    }
}

void fn_0201A2BC(void)
{
    struct Window *win;

    lbl_030030A4 = 0;
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    fn_020093B4(0, 2);
    fn_02009C54(1, 2, 15, 2);
    win = &lbl_030030B0[1];
    win->unk12 = 2;
    win->unkE = 4;
    win->unk16 = 10;
    fn_02009B80(win, 1);
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
    lbl_0300284C = 0;
    lbl_0300284E = 0;
    lbl_0300284D = 0;
    fn_02009DA8(1, 1);
    fn_02009CBC(1, 1, 8);
    lbl_0300284F = 0;
    lbl_030030AC = 1;
}

s32 fn_0201A3D4(void)
{
    struct Window *win;
    s32 ret;

    fn_02003394(1, 0);
    if (lbl_030030AC == 0) {
        fn_0201A2BC();
        if (lbl_030030AC == 0)
            return 0;
    }
    ret = fn_02009414(0);
    win = &lbl_030030B0[1];
    fn_02005968(win);
    fn_02005A50(win);
    if ((win->unk1 >> 3) < win->unk16 - 2)
        win->unk1 += 8;
    if (ret) {
        win[-1].unk1 = 0;
        win->unk1 = 0;
        fn_02003394(0, 0);
        fn_020033F4();
        fn_02003464(fn_0201A73C(43), 0);
        fn_02009D68(1, 1);
    }
    return ret;
}

s32 fn_0201A45C(void)
{
    struct Window *win;
    s32 ret;
    s32 pal;

    fn_020095AC(0);
    fn_02003394(1, 0);
    fn_020033F4();
    win = &lbl_030030B0[1];
    if (lbl_0300284E < win->unkE) {
        fn_0201A664(lbl_0300284E);
        pal = 5;
        fn_02009AB8(1, win->unk5, lbl_0300284E, lbl_0300284E, pal);
        lbl_0300284E++;
        if (lbl_0300284E < win->unkE)
            return 0;
    }
    if (lbl_03002ACC)
        fn_0201A568();
    fn_0201A5EC();
    ret = lbl_0300284D != 0;
    if (ret)
        fn_02009DA8(1, 1);
    return ret;
}
