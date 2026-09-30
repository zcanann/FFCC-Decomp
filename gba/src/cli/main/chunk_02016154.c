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

struct IdList {
    u8 count;
    u8 pad[3];
    s16 ids[64];
};

extern s8 lbl_03002814;
extern s8 lbl_03002815;
extern s8 lbl_03002816;
extern s8 lbl_03002817;
extern s8 lbl_03002818;
extern s8 lbl_03002819;
extern s8 lbl_0300281A;
extern s8 lbl_0300281B;
extern s8 lbl_0300281C;
extern s8 lbl_0300281D;
extern s8 lbl_0300281E;
extern u8 lbl_03002998;
extern u16 lbl_0300299C;
extern u16 lbl_030029AC;
extern u32 lbl_03002AC8;
extern u8 lbl_03002ACC;
extern u16 lbl_03002AEC;
extern u8 lbl_03002AF4;
extern s8 lbl_03002AFC;
extern u8 lbl_03002C98;
extern struct Work lbl_03002CA0;
extern s32 lbl_03003090;
extern s8 lbl_030030A0;
extern s32 lbl_030030A4;
extern s32 lbl_030030AC;
extern struct Window lbl_030030B0[];
extern s32 lbl_030032EC;
extern struct IdList lbl_0203A800;
extern s16 lbl_0203A804[];
extern const char lbl_0201D050[];

char *strcat(char *, const char *);
char *strcpy(char *, const char *);
void m4aSongNumStart(u16);
u16 *fn_02000A40(s32, s32, s32);
void fn_02000CF0(s32, s32, s32);
void fn_02001578(void);
s32 fn_02001604(void);
s32 fn_02002FB8(u8, u8);
s32 fn_02002FE4(u8, u8, u8);
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
s32 fn_02004D3C(s32);
s32 fn_02004E74();
void fn_02005968(struct Window *);
void fn_020059D4(struct Window *, s32, s32);
void fn_02005A50(struct Window *);
void fn_02008178(struct Window *);
void fn_02009AB8(s32, s32, s32, s32, s32);
void fn_02009BB0(s32, s32, s32);
void fn_02009C54(s32, s32, s32, s32);
char *fn_0201A73C(s32);
char *fn_0201A83C(s32);
char *fn_0201AAAC(s32);
s32 fn_0201AB14(s32);
void fn_02017A50(s32, char *);
s32 fn_02017B1C(s32);
void fn_02017BBC(s32);
void fn_02017BC8(void);
void fn_02017CE0(void);
void fn_02017DF0(s32, s32);

void fn_02016154(void);
s32 fn_020162F0(void);
s32 fn_0201634C(void);
s32 fn_020164F8(void);
void fn_0201654C(void);
s32 fn_02016650(void);
s32 fn_02016B1C(void);
s32 fn_02016B28(void);
s32 fn_02016D00(void);
void fn_02016D0C(void);
void fn_02016E88(s32, s32);
void fn_02016EDC(s32, s32, s32);
void fn_02016FB0(void);
s32 fn_02016FF0(s32);
s32 fn_02017058(s32);
void fn_02017088(s32);
s32 fn_0201710C(void);
s32 fn_02017180(void);
void fn_020171C0(void);
s32 fn_020172C0(void);
s32 fn_0201731C(void);
s32 fn_02017360(void);
void fn_020173A4(s32);
void fn_020173B8(s32);
void fn_020173E0(s32);
void fn_020174F4(void);

void fn_02016154(void)
{
    s32 i;

    lbl_030030A4 = 0;
    if (lbl_03003090 == 1)
        fn_02002FB8(7, 0);
    else
        fn_02002FB8(6, 0);
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window) * 5);
    fn_02009C54(1, 16, 0, 2);
    lbl_030030B0[2].unk0 = 1;
    lbl_030030B0[2].unk2 = 0;
    lbl_030030B0[2].unk10 = 6;
    lbl_030030B0[2].unk12 = 14;
    lbl_030030B0[2].unkE = 2;
    lbl_030030B0[2].unk14 = 9;
    lbl_030030B0[2].unk16 = 4;
    lbl_030030B0[2].unk3 = 3;
    lbl_030030B0[2].unk4 = 0;
    lbl_030030B0[2].unk5 = 2;
    lbl_030030B0[2].unk6 = 2;
    lbl_030030B0[2].unk7 = 0;
    lbl_030032EC = 0;
    for (i = 0; i < lbl_030030B0[2].unkE; i++) {
        lbl_030030B0[2].items[i].unk0 = 1;
        if (i == 0)
            lbl_030030B0[2].items[i].unk4 = fn_0201A73C(lbl_03003090 == 1 ? 11 : 12);
        else
            lbl_030030B0[2].items[i].unk4 = fn_0201A73C(4);
    }
    fn_02003394(1, 0);
    fn_020033F4();
    fn_020037C8(5, 0, 0);
    fn_020037C8(6, 2, 0);
    fn_02003890(0x050000E0, 0);
    fn_020041D4(3, 0);
    fn_020041D4(6, 0);
    fn_02004098(3, 1, 2, 0);
    fn_02004098(6, 2, 2, 0);
    fn_020038D8(0x06008400);
    lbl_03002814 = 0;
    lbl_03002816 = 0;
    lbl_030030A4 = 0;
    lbl_03002817 = 0;
    lbl_03002818 = 0;
    lbl_030030AC = 1;
}

s32 fn_020162F0(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    if (lbl_030030AC == 0)
        fn_02016154();
    win = &lbl_030030B0[1];
    fn_02003394(1, 0);
    fn_020033F4();
    fn_02005968(win);
    fn_02005A50(win);
    fn_020172C0();
    if ((win->unk1 >> 3) >= win->unk16 - 2)
        ret = 1;
    win->unk1 += 8;
    return ret;
}

s32 fn_0201634C(void)
{
    struct Window *win;
    struct IdList *list;
    s32 ret;

    if (!(lbl_03002AEC & 0x40)) {
        if (lbl_030029AC & 2) {
            lbl_03002814 = -1;
            m4aSongNumStart(3);
            return 1;
        }
        return 0;
    }
    win = &lbl_030030B0[1];
    list = &lbl_0203A800;
    if (lbl_03002816 < list->count && lbl_03002816 < win->unkE) {
        fn_02016E88(lbl_03002816, lbl_03002816);
        fn_02016EDC(lbl_03002816, lbl_03002816, fn_02016FF0(lbl_03002816));
        lbl_03002816++;
        if (lbl_03002816 < list->count && lbl_03002816 < win->unkE)
            return 0;
    }
    fn_02003394(1, 0);
    ret = 0;
    if (lbl_030032EC <= 1 || (lbl_030032EC == 2 && lbl_030030A4 == 1)) {
        if (lbl_03002818 == 0) {
            if (lbl_03002ACC)
                ret = fn_02016650();
        } else if (lbl_03002AEC & 0x8000) {
            if (lbl_03002AFC) {
                m4aSongNumStart(0);
                lbl_03002818 = 0;
            } else {
                lbl_030030A4++;
                fn_02016FB0();
            }
            fn_02001578();
        } else if (fn_02001604()) {
            m4aSongNumStart(0);
            lbl_03002818 = 0;
            fn_02001578();
            lbl_03002998 = 6;
        }
    } else if (lbl_030032EC == 2 && lbl_030030A4 == 0) {
        ret = fn_0201710C();
        if (ret) {
            lbl_030030A4++;
            lbl_030030B0[2].unk1 = 0;
        }
        ret = 0;
    } else if (lbl_030032EC == 2 && lbl_030030A4 == 2) {
        ret = fn_02017180();
        if (ret) {
            lbl_030030A4 = 0;
            lbl_030030B0[2].unk1 = 0;
            lbl_030032EC = 0;
            fn_020173B8(0);
        }
        ret = 0;
    }
    fn_0201731C();
    if (lbl_03002ACC)
        fn_0201654C();
    fn_02016D0C();
    return ret;
}

s32 fn_020164F8(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    fn_020033F4();
    win = &lbl_030030B0[1];
    fn_02008178(win);
    fn_02017360();
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        ret = lbl_03002814;
        fn_02004320(3);
        fn_02004320(6);
    }
    win->unk1 += 8;
    return ret;
}

void fn_0201654C(void)
{
    struct Window *win = &lbl_030030B0[1];
    s32 x;
    s32 y;
    s32 n;
    s32 flags;

    if (!lbl_030032EC || (lbl_03002AC8 & 2)) {
        x = (win->unk10 - 1) * 8;
        y = (win->unk12 + 1) * 8 + win->unk2 * 16;
        fn_02003C3C(x, y, 0, 45, fn_02004030(0, 45), 2, 0);
    }
    n = lbl_03003090 == 1 ? 2 : 1;
    if (lbl_030032EC == n && lbl_030030A4 == 1) {
        win = &lbl_030030B0[2];
        x = (win->unk10 - 1) * 8;
        y = win->unk12 * 8 + win->unk2 * 16;
        fn_02003C3C(x, y, 0, 45, fn_02004030(0, 45), 2, 0);
        win = &lbl_030030B0[1];
    }
    if (lbl_03003090 == 1)
        n = lbl_0203A800.count;
    else
        n = 64;
    flags = lbl_03002817 != 0;
    if (lbl_03002817 + win->unkE < n)
        flags |= 2;
    fn_02009BB0(1, 2, flags);
}

s32 fn_02016650(void)
{
    struct Window *win;
    s32 ret;
    s32 max;
    s32 idx;
    s32 pal;

    if (lbl_0300299C == 0)
        return 0;
    ret = 0;
    idx = lbl_03003090 == 1 ? 2 : 1;
    win = lbl_030032EC != idx ? &lbl_030030B0[1] : &lbl_030030B0[2];
    if (lbl_030032EC == 0) {
        max = 64;
        if (lbl_03003090 == 1)
            max = lbl_0203A800.count;
    } else {
        max = win->unkE;
    }

    if (lbl_0300299C & 0x40) {
        if (lbl_030032EC == 0) {
            if (win->unk2 != 0) {
                win->unk2--;
                fn_020173A4(lbl_03002817 + win->unk2);
                m4aSongNumStart(1);
            } else if (lbl_03002817 != 0) {
                fn_02017088(1);
                idx = lbl_03002817 - 1;
                if (lbl_03003090 == 1) {
                    fn_02016E88(idx, idx % win->unkE);
                    fn_02016EDC(idx % win->unkE, 0, fn_02016FF0(idx));
                } else {
                    fn_02017DF0(idx, idx % win->unkE);
                    pal = fn_02017058(idx) == 0 ? 6 : 5;
                    fn_02009AB8(1, win->unk5, idx % win->unkE, 0, pal);
                }
                lbl_03002817--;
                fn_020173A4(lbl_03002817 + win->unk2);
                m4aSongNumStart(1);
            } else {
                m4aSongNumStart(0);
            }
        } else if (lbl_03003090 == 1 && lbl_030032EC == 1) {
            if (fn_02017B1C(1))
                m4aSongNumStart(1);
            else
                m4aSongNumStart(0);
        } else {
            win->unk2 ^= 1;
            m4aSongNumStart(1);
        }
    } else if (lbl_0300299C & 0x80) {
        if (lbl_030032EC == 0) {
            if (win->unk2 < win->unkE - 1 && win->unk2 < max - 1) {
                win->unk2++;
                fn_020173A4(lbl_03002817 + win->unk2);
                m4aSongNumStart(1);
            } else if (lbl_03002817 + win->unkE < max) {
                fn_02017088(0);
                idx = lbl_03002817 + win->unkE;
                if (lbl_03003090 == 1) {
                    fn_02016E88(idx, idx % win->unkE);
                    fn_02016EDC(idx % win->unkE, win->unkE - 1, fn_02016FF0(idx));
                } else {
                    fn_02017DF0(idx, idx % win->unkE);
                    pal = fn_02017058(idx) == 0 ? 6 : 5;
                    fn_02009AB8(1, win->unk5, idx % win->unkE, win->unkE - 1, pal);
                }
                lbl_03002817++;
                fn_020173A4(lbl_03002817 + win->unk2);
                m4aSongNumStart(1);
            } else {
                m4aSongNumStart(0);
            }
        } else if (lbl_03003090 == 1 && lbl_030032EC == 1) {
            if (fn_02017B1C(-1))
                m4aSongNumStart(1);
            else
                m4aSongNumStart(0);
        } else {
            win->unk2 ^= 1;
            m4aSongNumStart(1);
        }
    }

    if (!(lbl_0300299C & 0xC0)) {
        if (lbl_030029AC & 1) {
            if (lbl_030032EC == 0) {
                if (lbl_03003090 == 1)
                    idx = fn_02016FF0(win->unk2 + lbl_03002817);
                else
                    idx = fn_02017058(win->unk2 + lbl_03002817);
                if (idx) {
                    lbl_030032EC++;
                    if (lbl_03003090 == 1) {
                        fn_020173B8(1);
                        fn_02017BBC(1);
                    }
                    m4aSongNumStart(2);
                } else {
                    m4aSongNumStart(0);
                }
            } else if (lbl_030032EC == 1) {
                if (lbl_03003090 == 1) {
                    lbl_030032EC = 2;
                    lbl_030030A4 = 0;
                    fn_02017BBC(0);
                    lbl_030030B0[2].unk2 = 0;
                } else if (win->unk2 < win->unkE - 1) {
                    idx = lbl_030030B0[1].unk2 + lbl_03002817;
                    fn_02002FE4(8, idx, 0);
                    lbl_03002818 = 1;
                    fn_02001578();
                    lbl_03002AF4 = 1;
                    m4aSongNumStart(2);
                } else {
                    lbl_030030A4++;
                }
                m4aSongNumStart(2);
            } else {
                if (win->unk2 < win->unkE - 1) {
                    idx = lbl_030030B0[1].unk2 + lbl_03002817;
                    fn_02002FE4(9, idx, lbl_0300281B);
                    lbl_03002818 = 1;
                    fn_02001578();
                    lbl_03002AF4 = 1;
                    m4aSongNumStart(2);
                } else {
                    lbl_030030A4++;
                }
                m4aSongNumStart(2);
            }
        }
        if (lbl_030029AC & 2) {
            if (lbl_030032EC == 0) {
                lbl_03002814 = -1;
                ret = 1;
            } else if (lbl_03003090 == 1 && lbl_030032EC == 1) {
                lbl_030032EC = 0;
                fn_020173B8(0);
                fn_02017BBC(0);
            } else {
                lbl_030030A4++;
            }
            m4aSongNumStart(3);
        }
    }
    return ret;
}

s32 fn_02016B1C(void)
{
    return fn_020162F0();
}

s32 fn_02016B28(void)
{
    struct Window *win;
    s32 id;
    s32 ret;

    if (!(lbl_03002AEC & 0x20)) {
        if (lbl_030029AC & 2) {
            lbl_03002814 = -1;
            m4aSongNumStart(3);
            return 1;
        }
        return 0;
    }
    win = &lbl_030030B0[1];
    if (lbl_03002816 < win->unkE) {
        id = lbl_03002CA0.unk64[lbl_03002816];
        fn_02003394(1, 0);
        fn_020033F4();
        if (id > 0) {
            fn_020038F4(16);
            fn_02003464(fn_0201AAAC(id), 0);
        }
        fn_020059D4(win, lbl_03002816, 0);
        fn_02009AB8(1, win->unk5, lbl_03002816, lbl_03002816, fn_02017058(lbl_03002816) == 0 ? 6 : 5);
        lbl_03002816++;
        if (lbl_03002816 < win->unkE)
            return 0;
    }
    fn_02003394(1, 0);
    ret = 0;
    if (lbl_030032EC == 0 || (lbl_030032EC == 1 && lbl_030030A4 == 1)) {
        if (lbl_03002818 == 0) {
            if (lbl_03002ACC)
                ret = fn_02016650();
        } else if (lbl_03002AEC & 0x8000) {
            if (lbl_03002AFC) {
                m4aSongNumStart(0);
                lbl_03002818 = 0;
            } else {
                lbl_030030A4++;
            }
            fn_02001578();
        } else if (fn_02001604()) {
            m4aSongNumStart(0);
            lbl_03002818 = 0;
            fn_02001578();
            lbl_03002998 = 6;
        }
    } else if (lbl_030032EC == 1 && lbl_030030A4 == 0) {
        ret = fn_0201710C();
        if (ret) {
            lbl_030030A4++;
            lbl_030030B0[2].unk1 = 0;
        }
        ret = 0;
    } else if (lbl_030032EC == 1 && lbl_030030A4 == 2) {
        ret = fn_02017180();
        if (ret) {
            lbl_030030A4 = 0;
            lbl_030030B0[2].unk1 = 0;
            lbl_030032EC = 0;
        }
        ret = 0;
    }
    fn_0201731C();
    if (lbl_03002ACC)
        fn_0201654C();
    fn_02016D0C();
    return ret;
}

s32 fn_02016D00(void)
{
    return fn_020164F8();
}

void fn_02016D0C(void)
{
    struct IdList *list;
    s16 *ids;
    struct Window *win;
    s32 x;
    s32 y;
    s32 i;
    s32 idx;
    s32 id;
    s32 t;
    s32 pal;

    if (lbl_03003090 == 1) {
        list = &lbl_0203A800;
        ids = list->ids;
    } else {
        list = 0;
        ids = 0;
    }
    win = &lbl_030030B0[1];
    x = (win->unk10 + 1) * 8;
    y = (win->unk12 + 1) * 8;
    for (i = 0; i < win->unkE; i++, y += 16) {
        idx = i + lbl_03002817;
        if (lbl_03003090 == 1) {
            if (idx >= list->count)
                break;
            id = ids[idx];
            if (id == 0)
                continue;
        } else {
            id = lbl_03002CA0.unk64[idx];
            if (id <= 0)
                continue;
        }
        t = fn_0201AB14(id);
        pal = fn_02004030(0, t);
        fn_02003C3C(x - 1, y, 0, t, pal, win->unk5, 0);
    }
    if (lbl_03003090 != 1) {
        x = (win->unk10 + 1) * 8;
        y = (win->unk12 + 1) * 8;
        t = (lbl_03002C98 & 15) == 1 ? 24 : 4;
        pal = fn_02004030(2, t);
        for (i = 0; i < win->unkE; i++, y += 16) {
            if (fn_02004D3C(i + lbl_03002817))
                fn_02003C3C(x - 5, y + 4, 2, t, pal, win->unk5, 0);
        }
    }
}

void fn_02016E88(s32 idx, s32 slot)
{
    s16 *id;
    struct Window *win;

    fn_02003394(1, 0);
    fn_020033F4();
    fn_020038F4(16);
    id = &lbl_0203A804[idx];
    if (*id > 0)
        fn_02003464(fn_0201AAAC(*id), 0);
    win = &lbl_030030B0[1];
    fn_020037A8(0x0600AB80 + 2 * 32 * win->unk14 * slot, win->unk14);
}

void fn_02016EDC(s32 idx, s32 row, s32 flag)
{
    u16 buf[30];
    s32 attr;
    s32 y;
    s32 w;
    s32 i;
    s32 j;
    s32 t;
    u16 *map;
    struct Window *win = &lbl_030030B0[1];

    attr = 6;
    if (flag)
        attr = 5;
    attr <<= 12;
    y = win->unk12 + 1 + row * 2;
    w = win->unk14 - 2;
    for (j = 0; j < 2; j++) {
        t = (win->unk14 << 1) * idx + 0x15C;
        t += j;
        for (i = 0; i < w; i++) {
            if (!(i & 1)) {
                buf[i] = attr | t;
            } else {
                buf[i] = (t + 2) | attr;
                t += 4;
            }
        }
        map = fn_02000A40(win->unk5, win->unk10 + 1, y + j);
        DmaCopy16(DMA3, buf, map, w * 2);
    }
}

void fn_02016FB0(void)
{
    struct Window *win = &lbl_030030B0[1];
    s32 i;
    s32 idx;

    for (i = 0; i < win->unkE; i++) {
        idx = lbl_03002817 + i;
        fn_02016EDC(idx % win->unkE, i, fn_02016FF0(idx));
    }
}

s32 fn_02016FF0(s32 idx)
{
    u8 *p = (u8 *)&lbl_0203A800;
    u8 count;
    u32 *vals;
    s32 n;
    s32 i;

    count = *p;
    p += 4;
    p += count * 2;
    if (count & 1)
        p += 2;
    vals = (u32 *)p;
    n = 0;
    for (i = 0; i < 64; i++) {
        if (lbl_03002CA0.unk64[i] == -1)
            n++;
    }
    return lbl_03002CA0.unk104 >= vals[idx] && n != 0;
}

s32 fn_02017058(s32 idx)
{
    s32 ret;

    if (lbl_03002CA0.unk64[idx] <= 158)
        ret = 0;
    else
        ret = fn_02004D3C(idx) == 0;
    return ret;
}

void fn_02017088(s32 dir)
{
    struct Window *win = &lbl_030030B0[1];
    s32 from;
    s32 to;
    s32 step;
    s32 i;
    s32 j;
    u16 *src;
    u16 *dst;

    step = 32;
    if (dir) {
        to = win->unkE * 2;
        from = to - 2;
        step = -step;
    } else {
        from = 3;
        to = 1;
    }
    src = fn_02000A40(win->unk5, win->unk10 + 1, from);
    dst = fn_02000A40(win->unk5, win->unk10 + 1, to);
    for (i = 0; i < win->unkE - 1; i++) {
        for (j = 0; j < 2; j++) {
            DmaSet(DMA0, src, dst, 0x80000000 | (win->unk14 - 2));
            src += step;
            dst += step;
        }
    }
}

s32 fn_0201710C(void)
{
    struct Window *win = &lbl_030030B0[2];
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
        lbl_03002818 = 0;
        ret = 1;
    }
    win->unk1 += 8;
    return ret;
}

s32 fn_02017180(void)
{
    s32 ret = 0;
    struct Window *win = &lbl_030030B0[2];

    fn_02003394(0, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        lbl_03002818 = 0;
        ret = 1;
    }
    win->unk1 += 8;
    return ret;
}

void fn_020171C0(void)
{
    s32 i;

    lbl_030030A4 = 0;
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(struct Window));
    lbl_030030B0->unk0 = 1;
    lbl_030030B0->unk2 = 0;
    lbl_030030B0->unk10 = 0;
    lbl_030030B0->unk12 = 0;
    lbl_030030B0->unkE = 6;
    lbl_030030B0->unk14 = 15;
    lbl_030030B0->unk16 = 14;
    lbl_030030B0->unk3 = 2;
    lbl_030030B0->unk4 = 0;
    lbl_030030B0->unk5 = 2;
    lbl_030030B0->unk6 = 0;
    lbl_030030B0->unk7 = 0;
    lbl_030032EC = 0;
    for (i = 0; i < lbl_030030B0->unkE; i++) {
        lbl_030030B0->items[i].unk0 = 1;
        lbl_030030B0->items[i].unk4 = fn_0201A73C(0);
    }
    fn_020037C8(3, 1, 2);
    fn_020038D8(0x06008000);
    fn_020041D4(5, 0);
    fn_02004098(5, 0, 2, 0);
    lbl_03002815 = 0;
    lbl_03002819 = 0;
    lbl_0300281A = 0;
    lbl_0300281C = lbl_0300281B = 1;
    lbl_0300281D = 0;
    lbl_0300281E = 0;
    lbl_030030A0 = 1;
}

s32 fn_020172C0(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 2);
    fn_020033F4();
    if (lbl_030030A0 == 0)
        fn_020171C0();
    win = lbl_030030B0;
    fn_020033F4();
    fn_02005968(win);
    fn_02005A50(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2)
        ret = 1;
    else
        win->unk1 += 8;
    return ret;
}

s32 fn_0201731C(void)
{
    fn_020174F4();
    if (lbl_0300281E)
        fn_02017BC8();
    if (lbl_0300281C != lbl_0300281B)
        fn_02017CE0();
    lbl_0300281C = lbl_0300281B;
    return 0;
}

s32 fn_02017360(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 2);
    fn_020033F4();
    win = lbl_030030B0;
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        ret = 1;
        fn_02004320(5);
    } else {
        win->unk1 += 8;
    }
    return ret;
}

void fn_020173A4(s32 idx)
{
    lbl_03002815 = idx;
    fn_020173E0(0);
}

void fn_020173B8(s32 mode)
{
    s32 old = lbl_0300281A;

    lbl_0300281A = mode;
    if (old != mode)
        fn_020173E0(1);
    lbl_0300281B = 1;
}

void fn_020173E0(s32 mode)
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
            buf[0][i] = attr | (t + 2);
            buf[1][i] = attr | (t + 3);
        }
    }
    map = fn_02000A40(win->unk5, win->unk10 + 1, win->unk12 + 1);
    size = (win->unk14 - 2) * 2;
    if (mode) {
        map += 128;
        i = 5;
        lbl_03002819 = 2;
    } else {
        i = 1;
        lbl_03002819 = mode;
        lbl_0300281E = mode;
    }
    for (; i < win->unk16 - 1; i++) {
        if (i & 1) {
            DmaSet(DMA3, buf[0], map, 0x80000000 | (size / 2));
        } else {
            DmaSet(DMA3, buf[1], map, 0x80000000 | (size / 2));
        }
        map += 32;
    }
    lbl_0300281D = 0;
}

void fn_020174F4(void)
{
    char str[32];
    u16 buf[30];
    struct IdList *list;
    struct ItemInfo *items;
    u32 *vals;
    u32 dst;
    s32 id;
    s32 n;
    s32 w;
    s32 x;
    s32 t;
    s32 kind;
    s32 digits;
    s32 attr;
    s32 i;
    s32 j;
    s32 k;

    if (lbl_03002819 > lbl_030030B0->unkE)
        return;
    items = 0;
    list = &lbl_0203A800;
    if (lbl_03003090 == 1) {
        n = list->count;
        if (n & 1)
            n++;
        vals = (u32 *)&lbl_0203A804[n];
        id = lbl_0203A804[lbl_03002815];
    } else {
        items = (struct ItemInfo *)list;
        vals = (u32 *)(items + 64);
        id = lbl_03002CA0.unk64[lbl_03002815];
    }
    fn_02003394(1, 2);
    fn_020033F4();
    dst = 0x06009000;
    if (lbl_03002819 < lbl_030030B0->unkE)
        dst = lbl_03002819 * 64 * lbl_030030B0->unk14 + 0x06009000;
    if (lbl_03002819 == 0) {
        if (id > 0) {
            fn_020038F4(16);
            fn_02003464(fn_0201AAAC(id), 0);
        }
        fn_020037A8(dst, lbl_030030B0->unk14);
    } else if (lbl_03002819 == 1) {
        if ((lbl_03003090 == 1 && id > 0) || (lbl_03003090 == 2 && id > 158)) {
            w = fn_02003464(fn_0201A73C(13), 2) + 72;
            x = (lbl_030030B0->unk14 - 2) * 8 - w;
            fn_020038F4(x);
            fn_02000CF0(vals[lbl_03002815], x, 8);
            fn_02003464(fn_0201A73C(13), 0);
        } else if (id > 0 && lbl_03003090 == 2 && id <= 158) {
            w = fn_02003464(fn_0201A73C(38), 2);
            x = (lbl_030030B0->unk14 - 2) * 8 - w;
            fn_020038F4(x);
            fn_02003464(fn_0201A73C(38), 0);
        }
        fn_020037A8(dst, lbl_030030B0->unk14);
    } else if (lbl_03002819 <= 5) {
        if (lbl_0300281A == 0) {
            if (id > 0) {
                kind = 0;
                if (lbl_03003090 != 1)
                    kind = fn_02004CAC(lbl_03002815);
                if (lbl_03003090 == 1 || kind != 1) {
                    fn_02017A50(lbl_03002819 - 2, str);
                    fn_020038F4(0);
                    fn_02003464(str, 0);
                } else {
                    items += lbl_03002815;
                    if (lbl_03002819 == 2) {
                        if (items->flags & 0x3000) {
                            fn_020038F4(0);
                            fn_02003464(fn_0201A83C(items->kind - 1), 0);
                            if (items->count != 0 && items->kind != 16) {
                                t = fn_02004E74() ? 40 : 39;
                                w = fn_02003464(fn_0201A73C(t), 2);
                                x = (lbl_030030B0->unk14 - 2) * 8 - w;
                                digits = 1;
                                if (items->count > 9) {
                                    digits = 3;
                                    if (items->count <= 99)
                                        digits = 2;
                                }
                                x -= digits * 9;
                                fn_020038F4(x);
                                fn_02003464(fn_0201A73C(t), 0);
                                x = fn_02003910();
                                fn_02000CF0(items->count, x, digits);
                            }
                        } else {
                            char *s;

                            if (items->flags & 0x100)
                                s = fn_0201A73C(16);
                            else
                                s = fn_0201A73C(63);
                            fn_020038F4(0);
                            fn_02003464(s, 0);
                            x = lbl_030030B0->unk14 * 8 - 34;
                            fn_02000CF0(items->count, x, 2);
                        }
                    } else if (lbl_03002819 == 3) {
                        if ((items->flags & 0xE00) && items->kind != 0) {
                            fn_020038F4(0);
                            fn_02003464(fn_0201A83C(items->kind - 1), 0);
                        }
                    }
                }
            }
        } else if (id > 0) {
            if (lbl_03002819 == 2) {
                w = fn_02003464(fn_0201A73C(14), 2);
                x = (lbl_030030B0->unk14 - 2) * 8 - w;
                fn_020038F4(x >> 1);
                fn_02003464(fn_0201A73C(14), 0);
            } else if (lbl_03002819 == 3) {
                strcpy(str, fn_0201A73C(13));
                strcat(str, lbl_0201D050);
                w = fn_02003464(str, 2) + 72;
                x = (lbl_030030B0->unk14 - 2) * 8 - w;
                fn_020038F4(x);
                fn_02000CF0(lbl_03002CA0.unk104, x, 8);
                fn_02003464(str, 0);
            } else if (lbl_03002819 == 4) {
                strcpy(str, fn_0201A73C(13));
                strcat(str, lbl_0201D050);
                w = fn_02003464(str, 2) + 72;
                x = (lbl_030030B0->unk14 - 2) * 8 - w;
                fn_020038F4(x);
                fn_02000CF0(vals[lbl_03002815], x, 8);
                fn_02003464(fn_0201A73C(13), 0);
            } else if (lbl_03002819 == 5) {
                w = fn_02003464(fn_0201A73C(15), 2) + 18;
                x = (lbl_030030B0->unk14 - 3) * 8 - w;
                fn_020038F4(x);
                fn_02003464(fn_0201A73C(15), 0);
                x = fn_02003910();
                fn_02000CF0(lbl_0300281B, x, 2);
            }
        }
        fn_020037A8(dst, lbl_030030B0->unk14);
    } else {
        dst = (u8 *)fn_02000A40(lbl_030030B0->unk5, lbl_030030B0->unk10 + 1, lbl_030030B0->unk12 + 1);
        attr = 3 << 12;
        w = lbl_030030B0->unk14 - 2;
        for (i = 0; i < lbl_03002819; i++) {
            for (j = 0; j < 2; j++) {
                t = lbl_030030B0->unk14 * 2 * i + 0x80 + j;
                for (k = 0; k < w; k++) {
                    if (!(k & 1)) {
                        buf[k] = attr | t;
                    } else {
                        buf[k] = (t + 2) | attr;
                        t += 4;
                    }
                }
                DmaCopy16(DMA3, buf, dst, w * 2);
                dst += 64;
            }
        }
        lbl_0300281E = 1;
    }
    if (lbl_03002819 <= lbl_030030B0->unkE)
        lbl_03002819++;
}
