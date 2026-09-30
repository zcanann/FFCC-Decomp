#include "gba_types.h"

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

extern u8 lbl_02026E35[];
extern s8 lbl_02029DC9[][2];
extern const char lbl_0202A1B4[];
extern const char lbl_0202A1B8[];
extern char *lbl_0202FC3C[];
extern char *lbl_0202FC4C[];
extern char *lbl_0202FC5C[];
extern char *lbl_0202FC6C[];
extern char *lbl_0202FC7C[];
extern char *lbl_0202FC8C[];
extern char *lbl_0202FD94[];
extern char *lbl_0202FE94[];
extern char *lbl_0202FF94[];
extern char *lbl_02030094[];
extern char *lbl_02030194[];
extern char *lbl_020301B4[];
extern char *lbl_020301D4[];
extern char *lbl_020301F4[];
extern char *lbl_02030214[];
extern char *lbl_02030234[];
extern char *lbl_02030280[];
extern char *lbl_020302CC[];
extern char *lbl_02030318[];
extern char *lbl_02030364[];
extern char *lbl_020303B0[];
extern char *lbl_020303CC[];
extern char *lbl_020303E8[];
extern char *lbl_02030404[];
extern char *lbl_02030420[];
extern char *lbl_0203043C[];
extern char *lbl_02030484[];
extern char *lbl_020304CC[];
extern char *lbl_02030514[];
extern char *lbl_0203055C[];
extern char *lbl_020305A4[];
extern char *lbl_02030624[];
extern char *lbl_020306A4[];
extern char *lbl_02030724[];
extern char *lbl_020307A4[];
extern char *lbl_02030824[];
extern char *lbl_02030890[];
extern char *lbl_020308FC[];
extern char *lbl_02030968[];
extern char *lbl_020309D4[];
extern char *lbl_02030A40[];
extern char *lbl_02030A78[];
extern char *lbl_02030AB0[];
extern char *lbl_02030AE8[];
extern char *lbl_02030B20[];
extern char *lbl_02030B58[];
extern char *lbl_0203132C[];
extern char *lbl_02031B00[];
extern char *lbl_020322D4[];
extern char *lbl_02032AA8[];
extern char *lbl_0203327C[];
extern char *lbl_02033594[];
extern char *lbl_020338AC[];
extern char *lbl_02033BC4[];
extern char *lbl_02033EDC[];
extern char *lbl_020341F4[];
extern char *lbl_020342E8[];
extern char *lbl_020343CC[];
extern char *lbl_020344B0[];
extern char *lbl_02034594[];
extern u8 lbl_0300284D;
extern u16 lbl_030029AC;
extern u8 lbl_03002C98;
extern struct Work lbl_03002CA0;
extern s8 lbl_03003098;
extern struct Window lbl_030030B0[];
extern struct Window lbl_03003120;
extern s8 lbl_030032E0;

char *strcpy(char *, const char *);
char *strcat(char *, const char *);
void m4aSongNumStart(u16);
void fn_02003394(s32, s32);
void fn_020033F4(void);
s32 fn_02003464(const char *, s32);
void fn_020037A8(u32, s32);
void fn_020038F4(s32);
void fn_02003C3C(s32, s32, s32, s32, s32, s32, s32);
s32 fn_02004030(s32, s32);
void fn_02004320(s32);
void fn_02008178(struct Window *);
u32 fn_02009340(struct Window *, s32, s32);
char *fn_0201A73C(s32);
char *fn_0201AAAC(s32);
s32 fn_0201AB14(s32);

s32 fn_0201A4F8(void)
{
    struct Window *win = lbl_030030B0;
    s32 done = 0;

    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) < win->unk16 - 1)
        win->unk1 += 8;
    else
        done = 1;
    win++;
    fn_02008178(win);
    if ((win->unk1 >> 3) < win->unk16 - 1)
        win->unk1 += 8;
    if (done) {
        win[-1].unk1 = 0;
        win->unk1 = 0;
        fn_02004320(17);
        fn_02004320(3);
    }
    return done;
}

void fn_0201A568(void)
{
    if (lbl_030029AC == 0)
        return;
    if (lbl_030029AC & 1) {
        m4aSongNumStart(0);
    } else if (lbl_030029AC & 2) {
        lbl_0300284D = 1;
        lbl_030032E0 = 1;
        m4aSongNumStart(3);
    } else if (lbl_030029AC & 0x300) {
        if (lbl_030029AC & 0x100)
            lbl_03003098 = 1;
        else
            lbl_03003098 = -1;
        m4aSongNumStart(6);
        lbl_0300284D = 1;
    }
}

void fn_0201A5EC(void)
{
    s32 i;
    s32 x = (lbl_03003120.unk10 + 1) * 8;
    s32 y = (lbl_03003120.unk12 + 1) * 8;
    s32 n = lbl_03003120.unkE;

    for (i = 0; i < n; i++, y += 16) {
        s16 v = lbl_03002CA0.unk120[i];
        if (v > 0) {
            s32 id = fn_0201AB14(v);
            fn_02003C3C(x, y, 0, id, fn_02004030(0, id), 2, 0);
        }
    }
}

void fn_0201A664(s32 idx, s32 row)
{
    char *str;

    fn_02003394(1, 0);
    fn_020033F4();
    fn_020038F4(16);
    if (lbl_03002CA0.unk120[idx] > 0)
        str = fn_0201AAAC(lbl_03002CA0.unk120[idx]);
    else
        str = fn_0201A73C(0);
    fn_02003464(str, 0);
    fn_020037A8(fn_02009340(&lbl_03003120, row, 0), lbl_03003120.unk14);
}

void fn_0201A6C8(s32 row)
{
    fn_0201A664(row, row);
}

char *fn_0201A6D4(s32 idx)
{
    char **tbl;

    switch (lbl_03002C98 & 0xF) {
    case 1:
        tbl = lbl_0202FC4C;
        break;
    case 2:
        tbl = lbl_0202FC5C;
        break;
    case 3:
        tbl = lbl_0202FC6C;
        break;
    case 4:
        tbl = lbl_0202FC7C;
        break;
    case 0:
    default:
        tbl = lbl_0202FC3C;
        break;
    }
    return tbl[idx];
}

char *fn_0201A73C(s32 idx)
{
    char **tbl;

    switch (lbl_03002C98 & 0xF) {
    case 1:
        tbl = lbl_0202FD94;
        break;
    case 2:
        tbl = lbl_0202FE94;
        break;
    case 3:
        tbl = lbl_0202FF94;
        break;
    case 4:
        tbl = lbl_02030094;
        break;
    case 0:
    default:
        if (lbl_03002C98 & 0x10) {
            if (idx == 51)
                return lbl_0202FC8C[64];
            if (idx == 63)
                return lbl_0202FC8C[65];
        }
        tbl = lbl_0202FC8C;
        break;
    }
    return tbl[idx];
}

char *fn_0201A7D4(s32 idx)
{
    char **tbl;

    switch (lbl_03002C98 & 0xF) {
    case 1:
        tbl = lbl_020301B4;
        break;
    case 2:
        tbl = lbl_020301D4;
        break;
    case 3:
        tbl = lbl_020301F4;
        break;
    case 4:
        tbl = lbl_02030214;
        break;
    case 0:
    default:
        tbl = lbl_02030194;
        break;
    }
    return tbl[idx];
}

char *fn_0201A83C(s32 idx)
{
    char **tbl;

    switch (lbl_03002C98 & 0xF) {
    case 1:
        tbl = lbl_02030280;
        break;
    case 2:
        tbl = lbl_020302CC;
        break;
    case 3:
        tbl = lbl_02030318;
        break;
    case 4:
        tbl = lbl_02030364;
        break;
    case 0:
    default:
        tbl = lbl_02030234;
        break;
    }
    return tbl[idx];
}

char *fn_0201A8A4(s32 idx)
{
    char **tbl;

    switch (lbl_03002C98 & 0xF) {
    case 1:
        tbl = lbl_020303CC;
        break;
    case 2:
        tbl = lbl_020303E8;
        break;
    case 3:
        tbl = lbl_02030404;
        break;
    case 4:
        tbl = lbl_02030420;
        break;
    case 0:
    default:
        tbl = lbl_020303B0;
        break;
    }
    return tbl[idx];
}

char *fn_0201A90C(s32 idx)
{
    char **tbl;

    switch (lbl_03002C98 & 0xF) {
    case 1:
        tbl = lbl_02030484;
        break;
    case 2:
        tbl = lbl_020304CC;
        break;
    case 3:
        tbl = lbl_02030514;
        break;
    case 4:
        tbl = lbl_0203055C;
        break;
    case 0:
    default:
        tbl = lbl_0203043C;
        break;
    }
    return tbl[idx];
}

char *fn_0201A974(s32 idx)
{
    char **tbl;

    switch (lbl_03002C98 & 0xF) {
    case 1:
        tbl = lbl_02030624;
        break;
    case 2:
        tbl = lbl_020306A4;
        break;
    case 3:
        tbl = lbl_02030724;
        break;
    case 4:
        tbl = lbl_020307A4;
        break;
    case 0:
    default:
        tbl = lbl_020305A4;
        break;
    }
    return tbl[idx];
}

char *fn_0201A9DC(s32 idx)
{
    char **tbl;

    switch (lbl_03002C98 & 0xF) {
    case 1:
        tbl = lbl_02030890;
        break;
    case 2:
        tbl = lbl_020308FC;
        break;
    case 3:
        tbl = lbl_02030968;
        break;
    case 4:
        tbl = lbl_020309D4;
        break;
    case 0:
    default:
        tbl = lbl_02030824;
        break;
    }
    return tbl[idx];
}

char *fn_0201AA44(s32 idx)
{
    char **tbl;

    switch (lbl_03002C98 & 0xF) {
    case 1:
        tbl = lbl_02030A78;
        break;
    case 2:
        tbl = lbl_02030AB0;
        break;
    case 3:
        tbl = lbl_02030AE8;
        break;
    case 4:
        tbl = lbl_02030B20;
        break;
    case 0:
    default:
        tbl = lbl_02030A40;
        break;
    }
    return tbl[idx];
}

char *fn_0201AAAC(s32 idx)
{
    char **tbl;

    switch (lbl_03002C98 & 0xF) {
    case 1:
        tbl = lbl_0203132C;
        break;
    case 2:
        tbl = lbl_02031B00;
        break;
    case 3:
        tbl = lbl_020322D4;
        break;
    case 4:
        tbl = lbl_02032AA8;
        break;
    case 0:
    default:
        tbl = lbl_02030B58;
        break;
    }
    return tbl[idx];
}

s32 fn_0201AB14(s32 idx)
{
    return lbl_02026E35[idx];
}

char *fn_0201AB20(s32 idx)
{
    char **tbl;

    switch (lbl_03002C98 & 0xF) {
    case 1:
        tbl = lbl_02033594;
        break;
    case 2:
        tbl = lbl_020338AC;
        break;
    case 3:
        tbl = lbl_02033BC4;
        break;
    case 4:
        tbl = lbl_02033EDC;
        break;
    case 0:
    default:
        tbl = lbl_0203327C;
        break;
    }
    return tbl[idx];
}

void fn_0201AB88(s32 idx, char *buf)
{
    char **tbl;
    char *str;
    s32 id = lbl_02029DC9[idx][0];
    s32 num;
    char digit[2];

    switch (lbl_03002C98 & 0xF) {
    case 1:
        tbl = lbl_020342E8;
        break;
    case 2:
        tbl = lbl_020343CC;
        break;
    case 3:
        tbl = lbl_020344B0;
        break;
    case 4:
        tbl = lbl_02034594;
        break;
    case 0:
    default:
        if (lbl_03002C98 & 0x10) {
            if (id == 5 || id == 6) {
                str = lbl_020341F4[id + 52];
                goto copy;
            }
            if (id == 43) {
                str = lbl_020341F4[59];
                goto copy;
            }
            if (id == 45) {
                str = lbl_020341F4[60];
                goto copy;
            }
        }
        tbl = lbl_020341F4;
        break;
    }
    str = tbl[id];
copy:
    strcpy(buf, str);
    num = lbl_02029DC9[idx][1];
    if (num > 0) {
        strcat(buf, lbl_0202A1B4);
        if (num > 9) {
            strcat(buf, lbl_0202A1B8);
        } else {
            digit[0] = num + '0';
            digit[1] = 0;
            strcat(buf, digit);
        }
    }
}
