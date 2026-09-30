#include "gba_types.h"

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
    s8 unk5D;
    u8 unk5E[4];
    u8 unk62[2];
    s16 unk64[64];
    s16 unkE4[8];
    s16 unkF4[8];
    u32 unk104;
    u32 unk108[3];
    u8 unk114[12];
    s16 unk120[4];
    u8 unk128;
    s8 unk129;
};

struct ItemInfo {
    u16 flags;
    u16 count;
    u16 kind;
    u16 unk6;
};

extern s16 *lbl_030027B0;
extern s16 lbl_030027B4;
extern s32 lbl_030027B8;
extern s8 lbl_030027BC;
extern s8 lbl_030027BD;
extern s8 lbl_030027BE;
extern s8 lbl_030027BF;
extern s8 lbl_030027C0;
extern s8 lbl_030027C1;
extern u16 lbl_0300299C;
extern u16 lbl_030029AC;
extern u32 lbl_03002AC8;
extern u8 lbl_03002ACC;
extern u16 lbl_03002AEC;
extern u8 lbl_03002C98;
extern struct Work lbl_03002CA0;
extern s8 lbl_03003090;
extern s8 lbl_03003098;
extern s32 lbl_030030A4;
extern s32 lbl_030030AC;
extern struct Window lbl_030030B0[];
extern struct Window lbl_03003120;
extern struct Window lbl_03003190;
extern u8 lbl_030032E0;
extern s32 lbl_030032EC;
extern const u8 lbl_0201CF38[];
extern s16 lbl_0203A800[];
extern struct ItemInfo lbl_0203D804[];

void m4aSongNumStart(u16);
void fn_02000CF0(s32, s32, s32);
void fn_0200194C(s32);
void fn_020025E4(s32);
void fn_0200330C(u8, s32);
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
s32 fn_02004CAC(s32);
s32 fn_02004CC8(s32);
s32 fn_02004D3C(s32);
s32 fn_02004E74(s32);
void fn_02005968(struct Window *);
void fn_020059D4(struct Window *, s32, s32);
void fn_02005A50(struct Window *);
void fn_02008178(struct Window *);
u32 fn_02009340(struct Window *, s32, s32);
s32 fn_02009414(s32);
void fn_020095AC(s32);
void fn_02009764(s32, s32, s32);
void fn_020098B8(s32, s32);
void fn_020098F0(s32, s32, s32, s32, s32);
void fn_0200996C(struct Window *, s32, s32, s32, s32, s32);
void fn_02009A14(s32, s32, s32);
void fn_02009AB8(s32, s32, s32, s32, s32);
void fn_02009BB0(s32, s32, s32);
void fn_02009D68(s32, s32);
void fn_02009DA8(s32, s32);
void fn_02009F68(s32, s32, s32);
void fn_0200E184(void);
char *fn_0201A73C(s32);
char *fn_0201A7D4(s32);
char *fn_0201A83C(s32);
char *fn_0201AAAC(s32);
s32 fn_0201AB14(s32);

void fn_0200E67C(void);
void fn_0200E734(void);
s32 fn_0200EA90(void);
s32 fn_0200EB44(void);
void fn_0200EB80(void);
s32 fn_0200ECA8(s32);
void fn_0200ED08(s32, s32);
s32 fn_0200EDC0(s32);
void fn_0200EE24(s32, s32);
void fn_0200EE88(void);
void fn_0200F010(s32);
s32 fn_0200F07C(s32);
void fn_0200F0CC(void);
void fn_0200F3C8(void);
void fn_0200F580(void);
void fn_0200F600(s32);
void fn_0200F6A8(void);
void fn_0200F734(void);

s32 fn_0200E344(void)
{
    struct Window *win = lbl_030030B0;
    s32 ret;
    s32 row;
    s32 y;
    s32 top;

    fn_02003394(1, 0);
    if (lbl_030030AC == 0)
        fn_0200E184();
    ret = fn_02009414(0);
    if (ret)
        win->unk1 = 0;
    win += 2;
    fn_02003394(0, 0);
    fn_020033F4();
    row = win->unk1 >> 3;
    if (row < lbl_03002CA0.unk5D) {
        fn_02009764(2, fn_0200ECA8(row), row);
        fn_020038F4(8);
        if (row == 0) {
            fn_02003464(fn_0201A73C(9), 0);
            y = 0;
        } else if (row == 1) {
            fn_02003464(fn_0201A73C(36), 0);
            y = 2;
        } else {
            if (row < win->unkE && lbl_03002CA0.unkF4[row] >= 0)
                fn_02003464(fn_0201AAAC(fn_0200F07C(row)), 0);
            y = row * 2;
        }
        win->unk5--;
        fn_020059D4(win, row, 0);
        top = win->unk12 + y;
        fn_0200996C(win, win->unk5, row, win->unk10, top, 7);
        win->unk5++;
    }
    if (row < win->unkE - 1)
        win->unk1 += 8;
    return ret;
}

s32 fn_0200E458(void)
{
    s32 ret;

    fn_020095AC(0);
    if (!(lbl_03002AEC & 0x200)) {
        if (lbl_030029AC & 1) {
            m4aSongNumStart(0);
        } else if (lbl_030029AC & 2) {
            lbl_030027BD = 1;
            lbl_030032E0 = 1;
            m4aSongNumStart(3);
            return 1;
        } else if (lbl_030029AC & 0x300) {
            if (lbl_030029AC & 0x100)
                lbl_03003098 = 1;
            else
                lbl_03003098 = -1;
            lbl_030027BD = 1;
            m4aSongNumStart(6);
            return 1;
        }
        if (++lbl_030027BF >= 60) {
            fn_020025E4(lbl_03003090);
            lbl_030027BF = 0;
        }
        return 0;
    }
    if (lbl_030027BE == 0) {
        fn_0200F0CC();
        lbl_030027BE = 1;
    }
    if (lbl_030032EC && lbl_030030A4 == 0) {
        ret = fn_0200EA90();
        if (ret) {
            fn_0200F0CC();
            lbl_030030A4++;
            lbl_030030B0[1].unk1 = 0;
        }
    } else if (!lbl_030032EC || lbl_030030A4 == 1) {
        if (lbl_03002ACC)
            fn_0200E734();
        else if (lbl_030032EC)
            lbl_030030A4++;
    } else {
        ret = fn_0200EB44();
        if (ret) {
            lbl_030030A4 = 0;
            lbl_030030B0[1].unk1 = 0;
            lbl_030032EC = 0;
            fn_0200F0CC();
        }
    }
    fn_0200EE88();
    fn_0200E67C();
    ret = lbl_030027BD != 0;
    if (ret)
        fn_02009DA8(2, 1);
    return ret;
}

s32 fn_0200E5E0(void)
{
    struct Window *win = lbl_030030B0;
    s32 ret = 0;
    s32 row;
    s32 y;

    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        ret = 1;
        fn_02004320(17);
        fn_0200194C(0);
        win->unk1 = 0;
    } else {
        win->unk1 += 8;
    }
    win = &lbl_03003190;
    row = win->unk1 >> 3;
    y = win->unk12 + (win->unkE - row - 1) * 2;
    fn_020098F0(win->unk5 - 1, win->unk10, y, win->unk14, 2);
    fn_020098B8(2, win->unkE - row - 1);
    if (row < win->unkE - 1)
        win->unk1 += 8;
    return ret;
}

void fn_0200E67C(void)
{
    s32 pal;
    struct Window *win;
    s32 x;
    s32 y;

    if (lbl_03002ACC) {
        pal = fn_02004030(0, 45);
        if (!lbl_030032EC || (lbl_03002AC8 & 2)) {
            win = &lbl_03003190;
            x = (win->unk10 - 1) * 8;
            y = win->unk12 * 8;
            y += win->unk2 * 16;
            fn_02003C3C(x, y, 0, 45, pal, win->unk5, 0);
        }
        if (lbl_030032EC && lbl_030030A4 == 1) {
            win = &lbl_03003120;
            x = (win->unk10 - 1) * 8;
            y = (win->unk12 + 1) * 8;
            y += win->unk2 * 16;
            fn_02003C3C(x, y, 0, 45, pal, win->unk5, 0);
        }
    }
}

void fn_0200E734(void)
{
    struct Window *win;
    s32 min;
    s32 n;
    s32 idx;
    s32 row;

    if (lbl_0300299C == 0)
        return;
    if (lbl_030032EC) {
        min = 0;
        win = &lbl_03003120;
        n = win->unkE;
    } else {
        min = 2;
        n = lbl_03002CA0.unk5D;
        win = &lbl_03003190;
    }
    if (lbl_0300299C & 0x40) {
        if (win->unk2 > min) {
            win->unk2--;
            fn_0200F0CC();
            m4aSongNumStart(1);
        } else if (!lbl_030032EC) {
            win->unk2 = n - 1;
            fn_0200F0CC();
            m4aSongNumStart(1);
        } else if (lbl_030027B4 <= win->unkE) {
            win->unk2 = lbl_030027B4 - 1;
            fn_0200F0CC();
            m4aSongNumStart(1);
        } else {
            fn_02009A14(1, 1, win->unk5);
            idx = (lbl_030027B8 - 1) % lbl_030027B4;
            if (idx < 0)
                idx += lbl_030027B4;
            row = (lbl_030027B8 - 1 + lbl_030027BC) % win->unkE;
            if (row < 0)
                row += win->unkE;
            fn_0200ED08(idx, row % win->unkE);
            fn_02009AB8(1, win->unk5, row, 0, fn_0200EDC0(idx) ? 5 : 6);
            lbl_030027B8--;
            fn_0200F0CC();
            m4aSongNumStart(1);
        }
    } else if (lbl_0300299C & 0x80) {
        if (((!lbl_030032EC || lbl_030027B4 > win->unkE) && win->unk2 < n - 1)
            || (lbl_030032EC && lbl_030027B4 <= win->unkE && win->unk2 < lbl_030027B4 - 1)) {
            win->unk2++;
            fn_0200F0CC();
            m4aSongNumStart(1);
        } else if (!lbl_030032EC) {
            win->unk2 = min;
            fn_0200F0CC();
            m4aSongNumStart(1);
        } else {
            if (lbl_030027B4 <= win->unkE) {
                win->unk2 = min;
                m4aSongNumStart(1);
            } else {
                fn_02009A14(0, 1, win->unk5);
                idx = (lbl_030027B8 + win->unkE) % lbl_030027B4;
                if (idx < 0)
                    idx += lbl_030027B4;
                row = (lbl_030027B8 + win->unkE + lbl_030027BC) % win->unkE;
                if (row < 0)
                    row += win->unkE;
                fn_0200ED08(idx, row);
                fn_02009AB8(1, win->unk5, row, win->unkE - 1, fn_0200EDC0(idx) ? 5 : 6);
                lbl_030027B8++;
            }
            fn_0200F0CC();
            m4aSongNumStart(1);
        }
    }
    if (lbl_0300299C & 0xC0)
        return;
    if (lbl_030029AC & 1) {
        if (!lbl_030032EC) {
            lbl_030032EC = 1;
        } else {
            idx = (lbl_030030B0[1].unk2 + lbl_030027B8) % lbl_030027B4;
            if (idx < 0)
                idx += lbl_030027B4;
            if (!fn_0200EDC0(idx)) {
                m4aSongNumStart(0);
                return;
            }
            lbl_030030A4++;
            fn_0200EE24(lbl_030030B0[2].unk2, idx - 1);
        }
        m4aSongNumStart(2);
    } else if (lbl_030029AC & 2) {
        if (!lbl_030032EC) {
            lbl_030032E0 = 1;
            lbl_030027BD = -1;
        } else {
            lbl_030030A4++;
        }
        m4aSongNumStart(3);
    } else if (lbl_030029AC & 0x300) {
        if (lbl_030032EC) {
            m4aSongNumStart(0);
        } else {
            if (lbl_030029AC & 0x100)
                lbl_03003098 = 1;
            else
                lbl_03003098 = -1;
            m4aSongNumStart(6);
            lbl_030027BD = -1;
        }
    }
}

s32 fn_0200EA90(void)
{
    struct Window *win = &lbl_03003120;
    s32 row;
    s32 idx;
    s32 ret;

    fn_02003394(1, 0);
    fn_020033F4();
    row = win->unk1 >> 3;
    if (row < win->unkE) {
        if (row < lbl_030027B4) {
            idx = (row + lbl_030027B8) % lbl_030027B4;
            if (idx < 0)
                idx += lbl_030027B4;
        } else {
            idx = row;
        }
        fn_0200ED08(idx, row);
        win->items[row].unk0 = fn_0200EDC0(idx);
    }
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        ret = 1;
        win->unk1 = 0;
        lbl_030027BC = (win->unkE - lbl_030027B8) % win->unkE;
        if (lbl_030027BC < 0)
            lbl_030027BC += win->unkE;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

s32 fn_0200EB44(void)
{
    s32 ret = 0;
    struct Window *win = &lbl_03003120;

    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        ret = 1;
        win->unk1 = 0;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

void fn_0200EB80(void)
{
    s32 n;
    s32 i;
    s32 j;
    s32 type;
    s32 count;
    u8 id;

    lbl_030027B0 = lbl_0203A800;
    n = 0;
    for (i = 0; i < 64; i++) {
        type = fn_02004CAC(i);
        if (type == 0 || type == 5 || type == 6 || type == 8 || type == 9)
            continue;
        if (type == 1) {
            s32 w = lbl_03002CA0.unk64[i];
            s32 party = lbl_03002CA0.unk0 & 3;
            if (fn_0201AB14(w) != party)
                continue;
        }
        lbl_030027B0[n++] = (s8)i;
    }
    count = 5;
    for (i = 0; i < count; i++) {
        id = lbl_0201CF38[i];
        if (lbl_03002CA0.unk108[(id - 159) >> 5] & (1 << ((id - 159) & 31)))
            lbl_030027B0[n++] = id - 95;
    }
    for (i = 0; i < 4; i++) {
        if (lbl_03002CA0.unk120[i] != 0) {
            for (j = 0; j < count; j++) {
                if (lbl_03002CA0.unk120[i] == lbl_0201CF38[j])
                    lbl_030027B0[n++] = i + 160;
            }
        }
    }
    lbl_030027B4 = n + 1;
}

s32 fn_0200ECA8(s32 row)
{
    s32 id;

    if (row <= 1)
        return 0;
    if (row >= lbl_03002CA0.unk5D || (id = lbl_03002CA0.unkF4[row]) < 0)
        return -1;
    if (id < 64) {
        id = fn_02004CAC(id);
        if (id == 3)
            return 1;
        if (id == 7)
            return 2;
        if (id == 1)
            return 3;
        if (id == 4)
            goto end;
    }
    id = 5;
end:
    return id;
}

void fn_0200ED08(s32 idx, s32 row)
{
    struct Window *win = &lbl_03003120;
    const char *str;
    s32 id;

    fn_02003394(1, 0);
    fn_020033F4();
    fn_020038F4(8);
    if (idx == 0) {
        str = fn_0201A73C(10);
    } else if (idx >= lbl_030027B4) {
        str = fn_0201A73C(0);
    } else {
        id = lbl_030027B0[idx - 1];
        if (id < 64)
            id = lbl_03002CA0.unk64[id];
        else if (id >= 64 && id < 160)
            id += 95;
        else
            id = lbl_03002CA0.unk120[id - 160];
        if (id > 0)
            str = fn_0201AAAC(id);
        else
            str = fn_0201A73C(0);
    }
    fn_02003464(str, 0);
    fn_020059D4(win, row, 0);
}

s32 fn_0200EDC0(s32 idx)
{
    s32 ret;

    if (idx >= lbl_030027B4)
        ret = 0;
    else if (idx == 0)
        ret = lbl_03002CA0.unkF4[lbl_030030B0[2].unk2] >= 0;
    else
        ret = fn_02004D3C(lbl_030027B0[idx - 1]) == 0;
    return ret;
}

void fn_0200EE24(s32 slot, s32 idx)
{
    if (idx < 0)
        lbl_03002CA0.unkF4[slot] = -1;
    else
        lbl_03002CA0.unkF4[slot] = lbl_030027B0[idx];
    fn_0200330C(slot, lbl_03002CA0.unkF4[slot]);
    fn_0200F010(slot);
}

void fn_0200EE88(void)
{
    struct Window *win = &lbl_03003190;
    s32 x;
    s32 i;
    s32 id;
    s32 pal;
    s32 idx;
    s32 y;

    x = (win->unk10 + win->unk14) * 8 - 18;
    for (i = 2; i < win->unkE; i++) {
        if (lbl_03002CA0.unkF4[i] != -1) {
            id = fn_0201AB14(fn_0200F07C(i));
            pal = fn_02004030(0, id);
            y = win->unk12 * 8 + i * 16;
            fn_02003C3C(x, y, 0, id, pal, win->unk5, 0);
        }
    }
    if (lbl_030032EC && lbl_030030A4 == 1) {
        win = &lbl_03003120;
        id = (lbl_03002C98 & 15) == 1 ? 24 : 4;
        pal = fn_02004030(2, id);
        x = win->unk10 * 8 + 6;
        for (i = 0; i < win->unkE; i++) {
            if (lbl_030027B4 > win->unkE) {
                idx = (i + lbl_030027B8) % lbl_030027B4;
                if (idx < 0)
                    idx += lbl_030027B4;
            } else {
                idx = i;
            }
            if (idx > 0 && idx < lbl_030027B4 && !fn_0200EDC0(idx)) {
                y = (win->unk12 + 1) * 8 + i * 16 + 3;
                fn_02003C3C(x, y, 2, id, pal, win->unk5, 0);
            }
        }
        if (lbl_030027B4 > win->unkE)
            fn_02009BB0(1, win->unk5, 3);
    }
}

void fn_0200F010(s32 row)
{
    struct Window *win = &lbl_03003190;

    fn_02003394(0, 0);
    fn_020033F4();
    fn_02009764(2, fn_0200ECA8(row), row);
    fn_020038F4(8);
    if (lbl_03002CA0.unkF4[row] >= 0)
        fn_02003464(fn_0201AAAC(fn_0200F07C(row)), 0);
    win->unk5--;
    fn_020059D4(win, row, 0);
    win->unk5++;
}

s32 fn_0200F07C(s32 row)
{
    s32 id = lbl_03002CA0.unkF4[row];

    if (id < 0)
        return -1;
    if (id < 64)
        id = lbl_03002CA0.unk64[id];
    else if (id < 160)
        id += 95;
    else
        id = lbl_03002CA0.unk120[id - 160];
    return id;
}

void fn_0200F0CC(void)
{
    struct Window *win;
    struct ItemInfo *item;
    s32 id;
    s32 idx;
    s32 n;
    s32 i;
    s32 v;
    s32 w;
    s32 digits;
    s32 msg;

    win = lbl_030032EC ? &lbl_030030B0[1] : &lbl_030030B0[2];
    if (!lbl_030032EC) {
        id = fn_0200F07C(win->unk2);
    } else {
        idx = (win->unk2 + lbl_030027B8) % lbl_030027B4;
        if (idx < 0)
            idx += lbl_030027B4;
        if (idx == 0) {
            id = 0;
        } else {
            id = lbl_030027B0[idx - 1];
            if (id < 64)
                id = lbl_03002CA0.unk64[id];
            else if (id >= 64 && id < 160)
                id += 95;
            else
                id = lbl_03002CA0.unk120[id - 160];
        }
    }
    if (fn_02004CC8(id) == 1) {
        fn_02003394(0, 0);
        fn_020033F4();
        if (!lbl_030032EC) {
            id = lbl_03002CA0.unkF4[win->unk2];
        } else {
            idx = win->unk2 + lbl_030027B8 - 1;
            idx %= lbl_030027B4;
            if (idx < 0)
                idx += lbl_030027B4;
            id = lbl_030027B0[idx];
        }
        n = 0;
        for (i = 0; i < lbl_030027B4; i++) {
            v = lbl_030027B0[i];
            if (v < 64) {
                w = lbl_03002CA0.unk64[v];
                if (fn_02004CC8(w) == 1 && fn_0201AB14(w) <= 3) {
                    if (v == id)
                        break;
                    n++;
                }
            }
        }
        item = &lbl_0203D804[n];
        if (item->flags & 0x100)
            fn_02003464(fn_0201A73C(16), 0);
        else if (item->flags & 0xE00)
            fn_02003464(fn_0201A73C(63), 0);
        if (!(item->flags & 0x3000)) {
            fn_02003900(8);
            idx = fn_02003910();
            fn_02000CF0(item->count, idx, 2);
        }
        if (!(item->flags & 0x100) && item->kind != 0) {
            if (item->flags & 0xE00)
                fn_02003900(8);
            fn_02003464(fn_0201A83C(item->kind - 1), 0);
            if ((item->flags & 0x3000) && item->count != 0 && item->kind != 16) {
                idx = fn_02004E74(item->kind);
                msg = 39;
                if (idx)
                    msg = 40;
                fn_02003900(8);
                fn_02003464(fn_0201A73C(msg), 0);
                idx = fn_02003910();
                if (item->count <= 9)
                    digits = 1;
                else if (item->count <= 99)
                    digits = 2;
                else
                    digits = 3;
                fn_02000CF0(item->count, idx, digits);
            }
        }
        fn_02009D68(2, 1);
    } else {
        fn_02009F68(id, 2, 1);
    }
}

void fn_0200F348(void)
{
    struct Window *win = &lbl_03003190;
    s32 row;
    s32 y;

    fn_02003394(0, 0);
    fn_020033F4();
    fn_020038F4(8);
    fn_02009764(2, -1, lbl_03002CA0.unk5D - 1);
    win->unkE = lbl_03002CA0.unk5D;
    row = lbl_03002CA0.unk5D - 1;
    win->unk5--;
    fn_020059D4(win, row, 0);
    y = win->unk12 + row * 2;
    fn_0200996C(win, win->unk5, row, win->unk10, y, 7);
    win->unk5++;
}

void fn_0200F3C8(void)
{
    s32 i;

    lbl_030030A4 = 0;
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);

    lbl_030030B0[0].unk0 = 0;
    lbl_030030B0[0].unk2 = 0;
    lbl_030030B0[0].unk10 = 3;
    lbl_030030B0[0].unk12 = 1;
    lbl_030030B0[0].unkE = 5;
    lbl_030030B0[0].unk14 = 24;
    lbl_030030B0[0].unk16 = 17;
    lbl_030030B0[0].unk3 = 0;
    lbl_030030B0[0].unk4 = 0;
    lbl_030030B0[0].unk5 = 2;
    lbl_030030B0[0].unk6 = 0;
    lbl_030030B0[0].unk7 = 0;
    lbl_030030B0[0].unk9[0] = 1;
    for (i = 0; i < lbl_030030B0[0].unkE; i++)
        lbl_030030B0[0].items[i].unk0 = 1;

    fn_02003394(1, 0);
    fn_020037C8(3, 0, 0);
    fn_020038D8(0x06008000);
    fn_020041D4(3, 0);
    fn_02004098(3, 0, 2, 0);
    fn_02003890(0x050000E0, 0);
    lbl_030027C1 = 0;
    lbl_030027C0 = 0;
    lbl_030030AC = 1;
}

s32 fn_0200F494(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    if (lbl_030030AC == 0)
        fn_0200F3C8();
    win = lbl_030030B0;
    fn_02005968(win);
    fn_02005A50(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2)
        ret = 1;
    else
        win->unk1 += 8;
    return ret;
}

s32 fn_0200F4E4(void)
{
    s32 ret;

    if (lbl_030027C1 <= 4) {
        fn_0200F600(lbl_030027C1);
        lbl_030027C1++;
        return 0;
    }
    fn_02003394(1, 0);
    if (lbl_03002ACC)
        fn_0200F580();
    ret = lbl_030027C0 != 0;
    fn_0200F6A8();
    fn_0200F734();
    return ret;
}

s32 fn_0200F540(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    win = lbl_030030B0;
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        ret = 1;
        fn_02004320(3);
    } else {
        win->unk1 += 8;
    }
    return ret;
}

void fn_0200F580(void)
{
    if (lbl_030029AC & 1) {
        m4aSongNumStart(0);
    } else if (lbl_030029AC & 2) {
        lbl_030027C0 = 1;
        lbl_030032E0 = 1;
        m4aSongNumStart(3);
    } else if (lbl_030029AC & 0x300) {
        if (lbl_030029AC & 0x100)
            lbl_03003098 = 1;
        else
            lbl_03003098 = -1;
        m4aSongNumStart(6);
        lbl_030027C0 = 1;
    }
}

void fn_0200F600(s32 idx)
{
    struct Window *win = lbl_030030B0;
    s32 lv;

    fn_02003394(1, 0);
    fn_020033F4();
    if (idx == 0) {
        fn_020038F4(16);
        fn_02003464(fn_0201A7D4(lbl_03002CA0.unk129), 0);
    } else {
        lv = lbl_03002CA0.unk4[idx - 1];
        if (lv <= 0)
            return;
        fn_02003464(fn_0201A73C(lv + 53), 0);
        if ((lbl_03002C98 & 15) == 1)
            fn_020038F4(80);
        else
            fn_020038F4(56);
        fn_02003464(lbl_03002CA0.names[idx - 1], 0);
    }
    fn_020037A8(fn_02009340(win, idx, 0), win->unk14);
}

void fn_0200F6A8(void)
{
    struct Window *win = lbl_030030B0;
    s32 x;
    s32 y;
    s32 i;
    s32 id;
    s32 hp;
    s32 lv;

    x = (win->unk10 + win->unk14 - 3) * 8;
    y = (win->unk12 + 4) * 8;
    for (i = 0; i < 4 && (lv = lbl_03002CA0.unk4[i]) > 0; i++, y += 24) {
        hp = lbl_03002CA0.unk8[i];
        if (hp <= 20)
            id = 33;
        else if (hp <= 40)
            id = 32;
        else if (hp <= 60)
            id = 31;
        else if (hp <= 80)
            id = 30;
        else
            id = 29;
        fn_02003C3C(x, y, 0, id, fn_02004030(0, id), 2, 0);
    }
}

void fn_0200F734(void)
{
    struct Window *win = lbl_030030B0;
    s32 x;
    s32 y;

    x = (win->unk10 + 1) * 8 + 4;
    y = (win->unk12 + 1) * 8 + 4;
    fn_02003C3C(x, y, 2, 6, fn_02004030(2, 6), 2, 0);
}
