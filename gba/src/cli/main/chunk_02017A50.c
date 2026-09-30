#include "gba_types.h"

#define NULL ((void *)0)

#define DMA0 0x040000B0

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

struct ItemInfo {
    u16 flags;
    u16 count;
    u16 kind;
    u16 unk6;
};

struct Recipe {
    u32 price;
    s16 materials[3];
    s16 counts[3];
    s16 ids[4];
    struct ItemInfo items[4];
};

extern const char lbl_0201D050[];
extern u8 lbl_0203A800[];
extern s16 lbl_0203A804[];
extern char lbl_0203AB00[];
extern s8 lbl_03002815;
extern s8 lbl_03002819;
extern s8 lbl_0300281B;
extern s8 lbl_0300281D;
extern s8 lbl_03002820;
extern s8 lbl_03002821;
extern s8 lbl_03002822;
extern s8 lbl_03002823;
extern s8 lbl_03002824;
extern s8 lbl_03002825;
extern s8 lbl_03002826;
extern s8 lbl_03002827;
extern s8 lbl_03002828;
extern s8 lbl_03002829;
extern s8 lbl_0300282A;
extern s8 lbl_0300282B;
extern s8 lbl_0300282C;
extern s8 lbl_0300282D;
extern u32 lbl_03002830[4];
extern u8 lbl_03002998;
extern u16 lbl_0300299C;
extern u16 lbl_030029AC;
extern u8 lbl_03002ACC;
extern u16 lbl_03002AEC;
extern u8 lbl_03002AF4;
extern s8 lbl_03002AFC;
extern struct Work lbl_03002CA0;
extern s32 lbl_03003090;
extern s32 lbl_030030A4;
extern s32 lbl_030030AC;
extern struct Window lbl_030030B0[];
extern struct Window lbl_03003120;
extern s32 lbl_030032EC;

void *memcpy(void *, const void *, u32);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
u32 strlen(const char *);
char *strchr(const char *, s32);
void m4aSongNumStart(u16);
void fn_02000AD4(s32, s32, s32);
void fn_02000CF0(s32, s32, s32);
void fn_02001578(void);
s32 fn_02001604(void);
void fn_02002FB8(s32, s32);
s32 fn_02002FE4(u8, u8, u8);
void fn_020032DC(u8, u8);
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
s32 fn_02004CAC(s32);
s32 fn_02004DA0(u16 *);
void fn_02005968(struct Window *);
void fn_020059D4(struct Window *, s32, s32);
void fn_02005A50(struct Window *);
void fn_02008178(struct Window *);
void fn_02009A14(s32, s32, s32);
void fn_02009AB8(s32, s32, s32, s32, s32);
void fn_02009B80(struct Window *, s32);
void fn_02009BB0(s32, s32, s32);
void fn_02009C54(s32, s32, s32, s32);
void fn_02009CBC(s32, s32, s32);
void fn_02009DA8(s32, s32);
void fn_02009F68(s32, s32, s32);
void fn_020173A4(s32);
void fn_02019180(s32, s32);
s32 fn_0201925C(void);
s32 fn_020192D0(void);
s32 fn_02019978(s32);
void fn_02019BE8(s32, s32);
void fn_02019C58(u16 *, char *);
s32 fn_02019D0C(s32);
s32 fn_02019D68(s32);
char *fn_0201A73C(s32);
char *fn_0201AAAC(s32);
s32 fn_0201AB14(s32);

s32 fn_02017CB8(void);
void fn_02017DF0(s32 idx, s32 row);
void fn_02017EAC(void);
s32 fn_02018230(void);
void fn_020181E4(void);
void fn_020184AC(void);
void fn_02018570(void);
void fn_020190B0(void);
void fn_020189A8(void);
s32 fn_02018A0C(void);
void fn_02018C38(void);

static inline struct Recipe *GetRecipe(void)
{
    s32 n = (s8)lbl_0203A800[0];
    struct Recipe *p;

    n++;
    if (n & 3)
        n = ((n >> 2) + 1) << 2;
    p = (struct Recipe *)(lbl_0203A800 + n);
    return &p[lbl_03002823];
}

void fn_02017A50(s32 line, char *dst)
{
    char *p = (char *)lbl_0203A800;
    char *s;
    s32 len;
    s32 idx;
    s32 i;

    if (lbl_03003090 == 1) {
        u32 n = *(u8 *)p;

        p = (char *)&lbl_0203A804[n];
        if (n & 1)
            p += 2;
        s = p + n * 4;
        idx = lbl_03002815;
    } else {
        s = lbl_0203AB00;
        if ((u32)fn_02004CAC(lbl_03002815) <= 1)
            return;
        idx = lbl_03002815;
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

s32 fn_02017B1C(s32 delta)
{
    s32 count;
    s32 i;
    s32 old;

    count = 0;
    for (i = 0; i < 64; i++) {
        if (lbl_03002CA0.unk64[i] == -1)
            count++;
    }
    old = lbl_0300281B;
    lbl_0300281B += delta;
    if (lbl_0300281B <= 0 || lbl_0300281B > count)
        lbl_0300281B = old;
    if (lbl_0300281B != old) {
        u8 *buf = lbl_0203A800;
        s32 n = buf[0];
        s16 *items = (s16 *)(buf + 4);
        u32 *prices;

        if (n & 1)
            n++;
        prices = (u32 *)&items[n];
        if (prices[lbl_03002815] * lbl_0300281B > lbl_03002CA0.unk104.word)
            lbl_0300281B = old;
    }
    return lbl_0300281B != old;
}

void fn_02017BBC(s8 val)
{
    lbl_0300281D = val;
}

void fn_02017BC8(void)
{
    s32 id;
    s32 x, y;
    s32 frame;

    if (lbl_03003090 == 1) {
        u8 *buf = lbl_0203A800;
        s16 *items = (s16 *)(buf + 4);

        if (lbl_03002815 >= buf[0])
            return;
        id = items[lbl_03002815];
    } else {
        id = lbl_03002CA0.unk64[lbl_03002815];
    }
    if (id <= 0)
        return;
    x = (lbl_030030B0[0].unk10 + 1) * 8;
    y = (lbl_030030B0[0].unk12 + 1) * 8;
    frame = fn_0201AB14(id);
    fn_02003C3C(x, y, 0, frame, fn_02004030(0, frame), lbl_030030B0[0].unk5, 0);
    if (fn_02017CB8() && lbl_0300281D) {
        x = (lbl_030030B0[0].unk10 + 12) * 8;
        y = (lbl_030030B0[0].unk12 + lbl_030030B0[0].unk16 - 1) * 8;
        fn_02003C3C(x, y, 2, 5, fn_02004030(2, 5), lbl_030030B0[0].unk5, 0);
    }
}

s32 fn_02017CB8(void)
{
    s32 ret = 0;

    if (lbl_03002819 > lbl_030030B0[0].unkE)
        ret = 1;
    return ret;
}

void fn_02017CE0(void)
{
    char buf[32];
    struct Window *win = lbl_030030B0;
    s32 ofs = win->unk14 * 64;
    u32 dst = win->unk14 * 256 + 0x06009000;
    u8 *p = lbl_0203A800;
    u8 n;
    s32 x;
    s32 w;
    s32 y;

    n = *p;
    p += 4;
    p += n * 2;
    if (n & 1)
        p += 2;
    fn_02003394(1, 2);
    fn_020033F4();
    strcpy(buf, fn_0201A73C(13));
    strcat(buf, lbl_0201D050);
    w = fn_02003464(buf, 2) + 72;
    x = (win->unk14 - 2) * 8 - w;
    fn_020038F4(x);
    fn_02000CF0(((u32 *)p)[lbl_03002815] * lbl_0300281B, x, 8);
    fn_02003464(fn_0201A73C(13), 0);
    fn_020037A8(dst, win->unk14);
    fn_020033F4();
    dst += ofs;
    w = fn_02003464(fn_0201A73C(15), 2) + 18;
    x = (win->unk14 - 3) * 8 - w;
    fn_020038F4(x);
    fn_02003464(fn_0201A73C(15), 0);
    y = fn_02003910();
    fn_02000CF0(lbl_0300281B, y, 2);
    fn_020037A8(dst, win->unk14);
}

void fn_02017DF0(s32 idx, s32 row)
{
    struct Window *win = &lbl_03003120;
    s32 id;
    char *str;

    fn_02003394(1, 0);
    fn_020033F4();
    id = lbl_03002CA0.unk64[idx];
    if (id > 0) {
        fn_020038F4(16);
        str = fn_0201AAAC(id);
    } else {
        str = fn_0201A73C(0);
    }
    fn_02003464(str, 0);
    fn_020059D4(win, row, 0);
}

void fn_02017E48(s32 idx)
{
    struct Window *win = &lbl_03003120;
    s32 id;
    char *str;

    fn_02003394(1, 0);
    fn_020033F4();
    id = lbl_03002CA0.unk64[idx];
    if (id > 0) {
        fn_020038F4(16);
        str = fn_0201AAAC(id);
    } else {
        str = fn_0201A73C(0);
    }
    fn_02003464(str, 0);
    fn_02017DF0(idx, idx % win->unkE);
    fn_020173A4(idx);
}

void fn_02017EAC(void)
{
    s32 i;

    fn_02000AD4(15, 0, 0);
    fn_02002FB8(8, 0);
    lbl_030030A4 = 0;
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    fn_02009C54(0, 16, 0, 2);
    lbl_030032EC = 0;
    fn_020037C8(3, 0, 0);
    fn_020037C8(4, 2, 0);
    fn_02003890(0x05000100, 1);
    fn_020041D4(3, 0);
    fn_02004098(3, 0, 2, 0);
    fn_020038D8(0x06008000);
    fn_02009B80(lbl_030030B0, 1);
    lbl_03002822 = 0;
    lbl_03002821 = 0;
    if (lbl_0300282C == 0) {
        lbl_03002820 = 0;
        lbl_0300282B = 0;
        lbl_0300282C = 1;
    } else {
        lbl_030030B0[0].unk2 = lbl_03002823 - lbl_03002820;
        lbl_0300282B = lbl_030030B0[0].unkE - lbl_03002820 % lbl_030030B0[0].unkE;
    }
    lbl_0300282D = 0;
    for (i = 0; i < 4; i++)
        lbl_03002830[i] = 0;
    fn_02009DA8(1, 1);
    fn_02009CBC(1, 1, 8);
    lbl_03002823 = 0;
    lbl_030030AC = 1;
}

s32 fn_02017FEC(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    if (lbl_030030AC == 0)
        fn_02017EAC();
    win = lbl_030030B0;
    fn_02003394(1, 0);
    fn_020033F4();
    fn_02005968(win);
    fn_02005A50(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        ret = 1;
        win->unk1 = 0;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

s32 fn_0201804C(void)
{
    struct Window *win;
    s32 count;
    s32 ofs;
    u8 *p;
    s32 idx;
    s32 ret;

    if (!(lbl_03002AEC & 0x80)) {
        if (lbl_030029AC & 2) {
            lbl_03002822 = -1;
            m4aSongNumStart(3);
            fn_02002FE4(11, 0, 0);
            return 1;
        }
        return 0;
    }
    win = lbl_030030B0;
    count = (s8)lbl_0203A800[0];
    if (lbl_0300282D == 0) {
        ofs = ((count + 1) >> 2) * 4;
        if ((count + 1) & 3)
            ofs += 4;
        p = &lbl_0203A800[ofs];
        p += count * 56;
        memcpy(lbl_03002830, p, 16);
        lbl_0300282D = 1;
    }
    if (lbl_03002821 < count && lbl_03002821 < win->unkE) {
        idx = lbl_03002821 + lbl_03002820;
        fn_02019BE8(idx, lbl_03002821);
        fn_02009AB8(0, win->unk5, lbl_03002821, lbl_03002821, fn_02019D0C(idx) ? 3 : 4);
        lbl_03002821++;
        if (lbl_03002821 < count && lbl_03002821 < win->unkE)
            return 0;
        idx = win->unk2 + lbl_03002820;
        fn_02009F68(fn_02019D68(idx), 1, 1);
    }
    fn_02003394(1, 0);
    ret = 0;
    if (lbl_03002ACC) {
        ret = fn_02018230();
        fn_020181E4();
    }
    fn_020184AC();
    if (ret)
        fn_02009DA8(1, 1);
    return ret;
}

s32 fn_0201819C(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    fn_020033F4();
    win = lbl_030030B0;
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        ret = lbl_03002822;
        fn_02004320(3);
    }
    win->unk1 += 8;
    return ret;
}

void fn_020181E4(void)
{
    s32 x = (lbl_030030B0[0].unk10 - 1) * 8;
    s32 y = (lbl_030030B0[0].unk12 + 1) * 8 + lbl_030030B0[0].unk2 * 16;

    fn_02003C3C(x, y, 0, 45, fn_02004030(0, 45), 2, 0);
}

s32 fn_02018230(void)
{
    struct Window *win;
    s32 count;
    s32 ret;
    s32 idx;
    s32 row;

    if (lbl_0300299C == 0)
        return 0;
    count = (s8)lbl_0203A800[0];
    ret = 0;
    win = lbl_030030B0;
    if (lbl_0300299C & 0x40) {
        if (win->unk2 != 0) {
            win->unk2--;
            idx = lbl_03002820 + win->unk2;
            fn_02009F68(fn_02019D68(idx), 1, 1);
            m4aSongNumStart(1);
        } else if (lbl_03002820 != 0) {
            s32 pal;

            fn_02009A14(1, 0, win->unk5);
            idx = lbl_03002820 - 1;
            row = idx + lbl_0300282B;
            fn_02019BE8(idx, row % win->unkE);
            pal = fn_02019D0C(idx) ? 3 : 4;
            fn_02009AB8(0, win->unk5, row % win->unkE, 0, pal);
            lbl_03002820--;
            idx = lbl_03002820 + win->unk2;
            fn_02009F68(fn_02019D68(idx), 1, 1);
            m4aSongNumStart(1);
        } else {
            m4aSongNumStart(0);
        }
    } else if (lbl_0300299C & 0x80) {
        if (win->unk2 < win->unkE - 1) {
            win->unk2++;
            idx = lbl_03002820 + win->unk2;
            fn_02009F68(fn_02019D68(idx), 1, 1);
            m4aSongNumStart(1);
        } else if (lbl_03002820 + win->unkE >= count) {
            m4aSongNumStart(0);
        } else {
            s32 pal;

            fn_02009A14(0, 0, win->unk5);
            idx = lbl_03002820 + win->unkE;
            row = idx + lbl_0300282B;
            fn_02019BE8(idx, row % win->unkE);
            pal = fn_02019D0C(idx) ? 3 : 4;
            fn_02009AB8(0, win->unk5, row % win->unkE, win->unkE - 1, pal);
            lbl_03002820++;
            idx = lbl_03002820 + win->unk2;
            fn_02009F68(fn_02019D68(idx), 1, 1);
            m4aSongNumStart(1);
        }
    }
    if (!(lbl_0300299C & 0xC0)) {
        if (lbl_030029AC & 1) {
            idx = lbl_03002820 + win->unk2;
            if (idx >= count || (s8)lbl_0203A800[idx] < 0 || !fn_02019D0C(idx)) {
                m4aSongNumStart(0);
            } else {
                lbl_03002822 = 1;
                ret = 1;
                lbl_03002823 = idx;
                m4aSongNumStart(2);
            }
        }
        if (lbl_030029AC & 2) {
            lbl_03002998 = 6;
            lbl_03002822 = -1;
            ret = 1;
            fn_02002FE4(11, 0, 0);
            m4aSongNumStart(3);
        }
    }
    return ret;
}

void fn_020184AC(void)
{
    struct Window *win = lbl_030030B0;
    s32 x = (win->unk10 + 1) * 8;
    s32 y = (win->unk12 + 1) * 8;
    s32 frame = 48;
    s32 pal = fn_02004030(0, frame);
    s32 count = (s8)lbl_0203A800[0];
    s32 i;
    s32 flags;

    for (i = 0; i < win->unkE && i + lbl_03002820 < count; i++, y += 16)
        fn_02003C3C(x, y, 0, frame, pal, win->unk5, 0);
    flags = lbl_03002820 != 0;
    if (lbl_03002820 + win->unkE < count)
        flags |= 2;
    fn_02009BB0(0, win->unk5, flags);
}

void fn_02018570(void)
{
    s32 i;

    lbl_030030A4 = 0;
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    lbl_030030B0[0].unk0 = 1;
    lbl_030030B0[0].unk2 = 0;
    lbl_030030B0[0].unk10 = 0;
    lbl_030030B0[0].unk12 = 0;
    lbl_030030B0[0].unkE = 8;
    lbl_030030B0[0].unk14 = 30;
    lbl_030030B0[0].unk16 = 18;
    lbl_030030B0[0].unk3 = 13;
    lbl_030030B0[0].unk4 = 0;
    lbl_030030B0[0].unk5 = 2;
    lbl_030030B0[0].unk6 = 0;
    lbl_030030B0[0].unk7 = 0;
    lbl_030030B0[1].unk0 = 1;
    lbl_030030B0[1].unk2 = 0;
    lbl_030030B0[1].unk10 = 2;
    lbl_030030B0[1].unk12 = 13;
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
    fn_02004098(16, 0, 2, 0);
    fn_02004098(6, 1, 1, 0);
    fn_020038D8(0x06008000);
    fn_02009B80(&lbl_030030B0[0], 1);
    for (i = 0; i < lbl_030030B0[1].unkE; i++) {
        lbl_030030B0[1].items[i].unk0 = 1;
        if (i == 0)
            lbl_030030B0[1].items[0].unk4 = fn_0201A73C(25);
        else
            lbl_030030B0[1].items[i].unk4 = fn_0201A73C(4);
    }
    lbl_030032EC = 0;
    lbl_03002822 = 0;
    lbl_03002821 = 0;
    lbl_03002824 = 1;
    lbl_03002825 = 0;
    lbl_03002827 = 0;
    lbl_0300282A = 0;
    lbl_030030AC = 1;
}

s32 fn_02018704(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    if (lbl_030030AC == 0)
        fn_02018570();
    win = lbl_030030B0;
    fn_02003394(1, 0);
    fn_020033F4();
    fn_02005968(win);
    fn_02005A50(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        ret = 1;
        fn_020190B0();
    }
    win->unk1 += 8;
    return ret;
}

s32 fn_02018760(void)
{
    struct Window *win = lbl_030030B0;
    s32 id;
    s32 x, y;
    s32 frame;
    s32 ret;

    fn_02018C38();
    if (lbl_03002821 < win->unkE)
        return 0;
    fn_02003394(1, 0);
    id = GetRecipe()->ids[lbl_0300282A];
    x = (win->unk10 + 1) * 8;
    y = (win->unk12 + 1) * 8;
    frame = fn_0201AB14(id);
    fn_02003C3C(x, y, 0, frame, fn_02004030(0, frame), win->unk5, 0);
    ret = 0;
    if (lbl_030032EC == 0 || lbl_030030A4 == 1) {
        if (lbl_03002825 == 0) {
            if (lbl_03002ACC)
                ret = fn_02018A0C();
        } else if (lbl_03002AEC & 0x8000) {
            if (lbl_03002AFC) {
                m4aSongNumStart(0);
            } else {
                lbl_030030A4++;
                lbl_03002822 = 1;
            }
            fn_02001578();
            lbl_03002825 = 0;
        } else if (fn_02001604()) {
            m4aSongNumStart(0);
            lbl_03002825 = 0;
            fn_02001578();
            lbl_03002998 = 6;
        }
    } else if (lbl_030030A4 == 0) {
        ret = fn_0201925C();
        if (ret) {
            lbl_030030A4++;
            lbl_030030B0[1].unk1 = 0;
        }
        ret = 0;
    } else if (lbl_030030A4 == 2) {
        ret = fn_020192D0();
        if (ret) {
            lbl_030030A4 = 0;
            lbl_030030B0[1].unk1 = 0;
            lbl_030032EC = 0;
            if (lbl_03002822)
                ret = lbl_03002822;
            else
                ret = 0;
        }
    }
    if (lbl_030032EC && lbl_03002ACC)
        fn_020189A8();
    return ret;
}

s32 fn_02018940(void)
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
        if (ret > 0)
            lbl_0300282C = 0;
    }
    win->unk1 += 8;
    return ret;
}

void fn_020189A8(void)
{
    struct Window *win;
    s32 x, y;

    if (lbl_030032EC == 1)
        win = &lbl_030030B0[1];
    else
        win = &lbl_030030B0[3];
    x = (win->unk10 - 1) * 8;
    if (lbl_030032EC == 1)
        y = win->unk12;
    else
        y = win->unk12 + 1;
    y = y * 8 + win->unk2 * 16;
    fn_02003C3C(x, y, 0, 45, fn_02004030(0, 45), 1, 0);
}

s32 fn_02018A0C(void)
{
    struct Window *win;
    s32 ret;
    s32 sel;
    u8 *p;

    if (lbl_0300299C == 0)
        return 0;
    ret = 0;
    win = NULL;
    if (lbl_030032EC) {
        if (lbl_030032EC == 1)
            win = &lbl_030030B0[1];
        else
            win = &lbl_030030B0[3];
        if (lbl_0300299C & 0xC0) {
            win->unk2 ^= 1;
            m4aSongNumStart(1);
        }
    }
    if (lbl_030032EC == 0 || !(lbl_0300299C & 0xC0)) {
        if (lbl_030029AC & 1) {
            if (lbl_030032EC == 0) {
                if (lbl_03003090 != 1 && lbl_03002827 == 0) {
                    lbl_03002822 = 1;
                    ret = 1;
                } else if (lbl_03003090 == 1 && lbl_03002824 == 0) {
                    m4aSongNumStart(0);
                    return 0;
                } else {
                    lbl_030032EC = 1;
                }
            } else if (lbl_030032EC == 1) {
                sel = win->unk2;
                switch (sel) {
                case 0:
                    if (lbl_03003090 == 1) {
                        if (win->items[sel].unk0 != 0) {
                            p = &lbl_0203A800[lbl_03002823];
                            fn_02002FE4(10, p[1], lbl_03002CA0.unk0 & 3);
                            lbl_03002825 = 1;
                            fn_02001578();
                            lbl_03002AF4 = 1;
                        } else {
                            m4aSongNumStart(0);
                            return 0;
                        }
                    } else {
                        if (fn_02019978(lbl_03002826) == 0) {
                            lbl_03002822 = 1;
                            lbl_03002998 = 6;
                        } else {
                            lbl_03002828 = sel;
                            lbl_03002829 = 1;
                        }
                        lbl_030030A4++;
                        ret = 0;
                    }
                    break;
                default:
                    lbl_030030A4++;
                    break;
                }
            } else {
                lbl_03002CA0.unk5E[win->unk2 + 3] = lbl_03002826;
                fn_020032DC(win->unk2 + 3, lbl_03002826);
                lbl_03002998 = 6;
                m4aSongNumStart(2);
                lbl_03002822 = 1;
                lbl_030030A4++;
            }
            m4aSongNumStart(2);
        }
        if (lbl_030029AC & 2) {
            if (lbl_030032EC == 0) {
                lbl_03002822 = -1;
                ret = 1;
            } else {
                if (lbl_03003090 == 2)
                    lbl_03002822 = -1;
                lbl_030030A4++;
            }
            m4aSongNumStart(3);
        }
    }
    return ret;
}

void fn_02018C38(void)
{
    char buf[64];
    struct Window *win = lbl_030030B0;
    struct Recipe *recipe;
    s32 sel;
    u32 dst;
    s32 i, j;
    s32 id;
    s32 count;
    s32 w;
    s32 pal;

    if (lbl_03002821 >= win->unkE)
        return;
    recipe = GetRecipe();
    sel = lbl_03002CA0.unk0 & 3;
    fn_02003394(1, 0);
    fn_020033F4();
    dst = win->unk14 * (lbl_03002821 * 64) + 0x06009000;
    if (lbl_03002821 == 0) {
        if (recipe->ids[sel] > 0) {
            lbl_0300282A = sel;
        } else {
            for (i = 0; i <= 3; i++) {
                if (i != sel && recipe->ids[i] != 0) {
                    lbl_0300282A = i;
                    break;
                }
            }
        }
        id = recipe->ids[lbl_0300282A];
        fn_020038F4(16);
        fn_02003464(fn_0201AAAC(id), 0);
        fn_020037A8(dst, win->unk14);
        if (fn_02004DA0(&recipe->items[lbl_0300282A].flags)) {
            lbl_03002827 = 1;
        } else {
            lbl_03002827 = 0;
            lbl_03002824 = 0;
        }
        if (lbl_03002824) {
            if (recipe->price > lbl_03002CA0.unk104.word)
                lbl_03002824 = 0;
            if (lbl_03002824) {
                for (i = 0; i < 3 && recipe->materials[i] != 0; i++) {
                    count = 0;
                    for (j = 0; j < 64; j++) {
                        if (lbl_03002CA0.unk64[j] == recipe->materials[i])
                            count++;
                    }
                    if (recipe->counts[i] > count)
                        lbl_03002824 = 0;
                }
            }
        }
        pal = lbl_03002824 ? 4 : 5;
        fn_02019180(lbl_03002821, pal);
    } else if (lbl_03002821 == 1) {
        w = fn_02003464(fn_0201A73C(17), 2);
        fn_020038F4(104 - w);
        fn_02003464(fn_0201A73C(17), 0);
        fn_020038F4(108);
        fn_02019C58(&recipe->items[lbl_0300282A].flags, buf);
        fn_02003464(buf, 0);
        fn_020037A8(dst, win->unk14);
        pal = lbl_03002827 ? 3 : 5;
        fn_02019180(lbl_03002821, pal);
    } else if (lbl_03002821 == 2) {
        w = fn_02003464(fn_0201A73C(22), 2);
        fn_020038F4(104 - w);
        fn_02003464(fn_0201A73C(22), 0);
        fn_020038F4(112);
        fn_02003464(fn_0201A73C(18), 0);
        fn_020038F4(128);
        fn_02003464(fn_0201A73C(21), 0);
        fn_020037A8(dst, win->unk14);
        fn_02019180(lbl_03002821, 3);
    } else if (lbl_03002821 == 3) {
        w = fn_02003464(fn_0201A73C(13), 2) + 72;
        fn_02000CF0(recipe->price, 104 - w, 8);
        fn_02003464(fn_0201A73C(13), 0);
        fn_020038F4(112);
        fn_02003464(fn_0201A73C(18), 0);
        fn_02000CF0(lbl_03002CA0.unk104.word, (win->unk14 - 2) * 8 - w, 8);
        fn_02003464(fn_0201A73C(13), 0);
        fn_020037A8(dst, win->unk14);
        pal = recipe->price > lbl_03002CA0.unk104.word ? 5 : 3;
        fn_02019180(lbl_03002821, pal);
    } else if (lbl_03002821 == 4) {
        w = fn_02003464(fn_0201A73C(23), 2);
        fn_020038F4(104 - w);
        fn_02003464(fn_0201A73C(23), 0);
        fn_020038F4(152);
        fn_02003464(fn_0201A73C(24), 0);
        fn_020037A8(dst, win->unk14);
        fn_02019180(lbl_03002821, 3);
    } else {
        id = recipe->materials[lbl_03002821 - 5];
        if (id == 0) {
            lbl_03002821 = win->unkE;
            return;
        }
        count = 0;
        for (j = 0; j < 64; j++) {
            if (lbl_03002CA0.unk64[j] == id)
                count++;
        }
        w = fn_02003464(fn_0201AAAC(id), 2);
        fn_020038F4(104 - w);
        fn_02003464(fn_0201AAAC(id), 0);
        fn_020038F4(112);
        fn_02003464(fn_0201A73C(20), 0);
        fn_02000CF0(recipe->counts[lbl_03002821 - 5], 126, 2);
        fn_020038F4(152);
        fn_02003464(fn_0201A73C(18), 0);
        fn_02000CF0(count, 166, 2);
        fn_020037A8(dst, win->unk14);
        pal = recipe->counts[lbl_03002821 - 5] > count ? 5 : 3;
        fn_02019180(lbl_03002821, pal);
    }
    lbl_03002821++;
}
