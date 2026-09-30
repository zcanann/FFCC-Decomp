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

#define DmaFill16(dmaAddr, value, dst, size) \
    { \
        vu16 tmp = (vu16)(value); \
        DmaSet(dmaAddr, &tmp, dst, 0x81000000 | ((size) / 2)); \
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
    u8 unk1[0x63];
    s16 unk64[64];
};

struct State {
    s32 (*init)(void);
    s32 (*main)(void);
    s32 (*exit)(void);
};

struct List {
    s32 count;
    u32 unk4;
    u32 unk8;
    u32 unkC;
};

struct Entry {
    u32 unk0;
    u16 unk4;
    u8 unk6;
    u8 unk7;
};

extern s32 lbl_030027CC;
extern s8 lbl_030027D8;
extern s8 lbl_030027D9;
extern s8 lbl_030027DA;
extern s8 lbl_030027DB;
extern u8 lbl_030027DC;
extern u8 lbl_030027DD;
extern s8 lbl_030027DE;
extern s16 lbl_030027E0;
extern s8 lbl_030027E2;
extern s8 lbl_030027E3;
extern s8 lbl_030027E4;
extern s8 lbl_030027E5;
extern s8 lbl_030027E6;
extern s8 lbl_030027E7;
extern s8 lbl_030027E8;
extern s8 lbl_030027E9;
extern u32 lbl_030027EC;
extern s8 lbl_030027F0;
extern s16 lbl_030027F2;
extern u16 lbl_030029AC;
extern u8 gMenuHasInput;
extern s8 gNewLetter;
extern u16 gDataFlags;
extern s8 gItemUseFlags;
extern u8 gLanguage;
extern struct Work gSession;
extern s8 gScreenStep;
extern s8 gLetterAttachKind;
extern s32 lbl_030030A4;
extern s32 gScreenInitDone;
extern struct Window gWindows[];
extern u8 gOpenMenuReq;
extern s32 gScreenPhase;
extern const struct State lbl_0202FBD0[];
extern const struct State lbl_0202FC0C[];
extern struct List gListBuf;
extern struct Entry lbl_0203A810[];
extern u8 gDetailBuf[];

void *memset(void *, s32, u32);
void m4aSongNumStart(u16);
void Xfer_ClearLetterData(void);
s32 Link_SendRequest(u8, u8);
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
void fn_02005968(struct Window *);
void fn_020059D4(struct Window *, s32, s32);
void fn_02005A50(struct Window *);
void fn_02008178(struct Window *);
u32 fn_02009340(struct Window *, s32, s32);
void fn_02009AB8(s32, s32, s32, s32, s32);
void fn_02009B80(struct Window *, s32);
void fn_02009BB0(s32, s32, s32);
void fn_02009C54(s32, s32, s32, s32);
void fn_02009CBC(s32, s32, s32);
void fn_02009D68(s32, s32);
void fn_02009DA8(s32, s32);
void fn_02009F68(s32, s32, s32);
void fn_02013410(s32, s32);
void fn_020134C8(s32, s32, s32, s32);
s32 fn_0201354C(s32);
void fn_0201361C(s32, s32);
s32 fn_02013648(void);
void fn_02013844(void);
void fn_0201396C(void);
s32 fn_02013B1C(u8 *);
void fn_02013B3C(void);
void fn_02013C54(void);
s32 fn_02013D70(void);
void fn_020140F4(char *, s32);
char *fn_0201A73C(s32);
char *fn_0201AA44(s32);
char *fn_0201AAAC(s32);
s32 fn_0201AB14(s32);

void fn_0201111C(s32 idx, s32 row);
void fn_02011170(s32 idx);
void fn_020112CC(void);

#define WRAP64(dst, n) \
    { \
        dst = (n) % 64; \
        if (dst < 0) \
            dst += 64; \
    }

void fn_02010E54(void)
{
    struct Window *win = &gWindows[1];
    s32 x;
    s32 y;
    s32 n;
    s32 i;
    s32 idx;
    s32 id;
    s32 icon;
    s32 pal;

    x = win->unk10 * 8 + 14;
    y = (win->unk12 + 1) * 8;
    n = win->unkE;
    for (i = 0; i < n; i++, y += 16) {
        WRAP64(idx, lbl_030027CC + i);
        id = gSession.unk64[idx];
        if (id > 0) {
            icon = fn_0201AB14(id);
            pal = fn_02004030(0, icon);
            fn_02003C3C(x, y, 0, icon, pal, 2, 0);
        }
    }
    x = (win->unk10 + 1) * 8;
    y = (win->unk12 + 1) * 8;
    if ((gLanguage & 15) == 1)
        icon = 24;
    else
        icon = 4;
    pal = fn_02004030(2, icon);
    for (i = 0; i < win->unkE; i++, y += 16) {
        WRAP64(idx, lbl_030027CC + i);
        if (fn_02004D3C(idx))
            fn_02003C3C(x, y + 4, 2, icon, pal, win->unk5, 0);
    }
    fn_02009BB0(1, win->unk5, 3);
}

void fn_02010F88(s32 idx)
{
    struct Window *win = &gWindows[1];
    s32 top;
    s32 bottom;
    s32 row;
    s32 pal;

    WRAP64(top, lbl_030027CC);
    WRAP64(bottom, lbl_030027CC + win->unkE);
    if (top < bottom) {
        if (idx < top || idx >= bottom)
            return;
    } else {
        if (idx < 0 || idx >= 64)
            return;
        if (idx >= bottom && idx < top)
            return;
    }
    fn_0201111C(idx, idx % win->unkE);
    pal = fn_02004D3C(idx) ? 6 : 5;
    WRAP64(row, idx - lbl_030027CC);
    fn_02009AB8(1, win->unk5, idx % win->unkE, row, pal);
    fn_02011170(win->unk2 + lbl_030027CC);
}

s32 fn_0201106C(void)
{
    struct Window *win = &gWindows[2];
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
        win->unk1 = ret;
        ret = 1;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

s32 fn_020110E0(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[2];

    fn_02003394(0, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        win->unk1 = ret;
        ret = 1;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

void fn_0201111C(s32 idx, s32 row)
{
    fn_02003394(1, 0);
    fn_020033F4();
    fn_020038F4(24);
    if (gSession.unk64[idx] > 0)
        fn_02003464(fn_0201AAAC(gSession.unk64[idx]), 0);
    fn_020037A8(fn_02009340(&gWindows[1], row, 0), gWindows[1].unk14);
}

void fn_02011170(s32 idx)
{
    s32 i;

    WRAP64(i, idx);
    fn_02009F68(gSession.unk64[i], 1, 1);
}

void fn_020111A4(void)
{
    struct Window *win = &gWindows[2];
    s32 idx;
    s32 type;

    WRAP64(idx, gWindows[1].unk2 + lbl_030027CC);
    type = fn_02004CAC(idx);
    if (type == 7)
        win->items[0].unk0 = 1;
    else
        win->items[0].unk0 = 0;
    if (type == 1)
        gWindows[2].items[1].unk0 = 0;
    else
        gWindows[2].items[1].unk0 = 1;
    if (!(gItemUseFlags & 1))
        gWindows[2].items[0].unk0 = 0;
    if (!(gItemUseFlags & 2))
        gWindows[2].items[1].unk0 = 0;
    win->unk9[1] = 1;
}

s32 fn_02011244(void)
{
    s32 n;
    s32 type;
    s32 mask;
    s32 cur;

    n = gWindows[1].unk2 + lbl_030027CC;
    WRAP64(type, n);
    type = fn_02004CAC(type);
    mask = gItemUseFlags;
    if (type != 7)
        mask &= ~1;
    if (type == 1)
        mask &= ~2;
    cur = gWindows[2].items[0].unk0 != 0;
    if (gWindows[2].items[1].unk0 != 0)
        cur |= 2;
    if (cur != mask)
        return 1;
    return 0;
}

void fn_020112CC(void)
{
    DmaClear32(DMA0, 0, gWindows, sizeof(struct Window) * 5);
    Xfer_ClearLetterData();
    Link_SendRequest(3, 0);
    lbl_030027F2 = 0;
    fn_02003394(1, 0);
    fn_020033F4();
    fn_020037C8(3, 0, 0);
    fn_020038D8(0x06008000);
    fn_02003890(0x050000E0, 0);
    fn_02003890(0x05000100, 2);
    fn_02003890(0x05000120, 3);
    if (gLetterAttachKind == 0) {
        lbl_030027D8 = 0;
        lbl_030027D9 = 0;
        lbl_030027DB = 0;
        lbl_030027DC = 0;
        lbl_030027DD = 0;
        lbl_030027E0 = -1;
        lbl_030027DE = 0;
        lbl_030027E4 = 0;
        lbl_030027E2 = 0;
        lbl_030027E3 = -1;
        lbl_030027E5 = 0;
        lbl_030027E6 = -1;
        lbl_030027E7 = 0;
        lbl_030027E9 = 0;
        lbl_030027EC = 0;
    } else {
        gLetterAttachKind = 0;
        if (lbl_030027E5 == 1) {
            lbl_030027D8 = 3;
        } else {
            lbl_030027D8 = 1;
            lbl_030027E2 = 2;
            lbl_030027E3 = 0;
        }
    }
    fn_02009DA8(1, 1);
    gScreenPhase = 2;
    lbl_030027DA = 0;
    gScreenInitDone = 1;
}

s32 LetterScreen_Update(void)
{
    s32 ret;

    if (gScreenInitDone == 0)
        fn_020112CC();
    if (lbl_030030A4 == 0)
        ret = lbl_0202FBD0[lbl_030027D8].init();
    else if (lbl_030030A4 == 1)
        ret = lbl_0202FBD0[lbl_030027D8].main();
    else
        ret = lbl_0202FBD0[lbl_030027D8].exit();
    if (ret) {
        ret = 0;
        if (lbl_030030A4 <= 1) {
            lbl_030030A4++;
        } else {
            lbl_030027DA = 0;
            lbl_030030A4 = 0;
            if (lbl_030027D8 == 0) {
                lbl_030027D8++;
                lbl_030027E3 = -1;
                lbl_030027E2 = 0;
            } else if (lbl_030027D8 == 1 && lbl_030027E5 != -1) {
                lbl_030027E9 = 0;
                lbl_030027EC = 0;
                if (lbl_030027E5 == 2) {
                    lbl_030027E9 = 0;
                    lbl_030027D8 += 2;
                } else {
                    lbl_030027D8++;
                    if (lbl_030027E5 != 0) {
                        ret = 1;
                        gLetterAttachKind = lbl_030027E5 + 1;
                    }
                }
                lbl_030027E2 = 0;
                lbl_030027E3 = 0;
            } else if (lbl_030027D8 == 2) {
                if (lbl_030027E5 == -1) {
                    lbl_030027D8 = 1;
                    lbl_030027E2 = 2;
                    lbl_030027E3 = 0;
                } else {
                    lbl_030027D8++;
                }
            } else if (lbl_030027D8 == 3) {
                if (lbl_030027E5 == -1) {
                    lbl_030027D8 = 1;
                    lbl_030027E2 = 2;
                    lbl_030027E3 = 0;
                } else if (lbl_030027E7) {
                    lbl_030027D8++;
                } else {
                    lbl_030027D8 = 0;
                }
            } else if (lbl_030027D8 == 4) {
                lbl_030027D8--;
                lbl_030030A4 = 2;
                lbl_030027E7 = 0;
                lbl_030027E5 = -1;
            } else {
                lbl_030027D8 = 0;
            }
            if (lbl_030027D9)
                ret = 1;
        }
        if (ret)
            fn_02009DA8(1, 1);
    }
    return ret;
}

s32 fn_02011638(void)
{
    struct Window *win = gWindows;
    s32 ret;

    if (lbl_030027DA == 0) {
        memset(win, 0, sizeof(struct Window));
        win->unk0 = 1;
        if (lbl_030027E0 >= 0)
            win->unk2 = lbl_030027E0 - lbl_030027DC;
        win->unk10 = 0;
        win->unk12 = 0;
        win->unkE = 8;
        win->unk14 = 30;
        win->unk16 = 18;
        win->unk3 = 0;
        win->unk4 = 1;
        win->unk5 = 2;
        win->unk6 = 0;
        win->unk7 = 0;
        fn_02009B80(win, 1);
        fn_02003394(1, 0);
        fn_02003890(0x050000E0, 0);
        fn_02003890(0x05000100, 2);
        fn_02003890(0x050001C0, 1);
        fn_020041D4(3, 1);
        fn_02004098(3, 0, 2, 1);
        fn_02003394(0, 0);
        fn_020033F4();
        fn_02009DA8(1, 2);
        fn_02009CBC(1, 2, 14);
        lbl_030027DD = 0;
        lbl_030027E0 = -1;
        lbl_030027E6 = -1;
        lbl_030027DA = 1;
    }
    fn_02003394(1, 0);
    fn_02005968(win);
    if (win->items[win->unkE - 1].unk2 == 0)
        return 0;
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 2) < win->unk14) {
        win->unk1 += 8;
    } else {
        ret = 1;
        fn_02003394(0, 0);
        fn_020033F4();
        fn_02003464(fn_0201A73C(61), 0);
        fn_02009D68(1, 2);
        win->unk1 = 0;
    }
    return ret;
}

s32 fn_0201179C(void)
{
    s32 n;
    s32 idx;
    s32 attr;
    s32 ret;

    if (gNewLetter) {
        Link_SendRequest(3, 0);
        DmaFill16(DMA0, 0x3FF, 0x0600E800, 0x800);
        gNewLetter = 0;
        lbl_030027DD = 0;
        lbl_030027F2 = 0;
    }
    if (!(gDataFlags & 8)) {
        if (lbl_030029AC & 1) {
            m4aSongNumStart(0);
        } else if (lbl_030029AC & 2) {
            lbl_030027D9 = 1;
            gOpenMenuReq = 1;
            m4aSongNumStart(3);
            return 1;
        } else if (lbl_030029AC & 0x300) {
            if (lbl_030029AC & 0x100)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            ret = 1;
            lbl_030027D9 = ret;
            m4aSongNumStart(6);
            return 1;
        }
        if (lbl_030027DD)
            fn_02013844();
        if (++lbl_030027F2 >= 300) {
            Link_SendRequest(3, 0);
            lbl_030027F2 = 0;
        }
        return 0;
    }
    if (gListBuf.count > gWindows[0].unkE)
        n = gWindows[0].unkE;
    else
        n = gListBuf.count;
    ret = 0;
    if (lbl_030027DD < n) {
        idx = lbl_030027DC + lbl_030027DD;
        n = idx % gWindows[0].unkE;
        fn_02013410(idx, n);
        attr = fn_0201354C(lbl_030027DC + lbl_030027DD);
        fn_020134C8(n, lbl_030027DD, 25, attr);
        lbl_030027DD++;
    } else if (gMenuHasInput) {
        ret = fn_02013648();
        fn_0201361C(gWindows[0].unk10 * 8, (gWindows[0].unk12 + 1) * 8 + gWindows[0].unk2 * 16);
    }
    fn_02013844();
    if (ret)
        fn_02009DA8(1, 2);
    return ret;
}

s32 fn_0201196C(void)
{
    struct Window *win = gWindows;
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

s32 fn_020119A4(void)
{
    struct Window *win = gWindows;
    s32 i;
    s32 ret;

    if (lbl_030027DA == 0) {
        memset(win, 0, sizeof(struct Window));
        win->unk0 = 1;
        win->unk10 = 2;
        win->unk12 = 1;
        win->unkE = 7;
        win->unk14 = 27;
        win->unk16 = 17;
        win->unk3 = 8;
        win->unk4 = 0;
        win->unk5 = 2;
        win->unk6 = 0;
        win->unk7 = 0;
        for (i = 0; i < win->unkE; i++) {
            win->items[i].unk0 = 1;
            win->items[i].unk4 = fn_0201A73C(0);
        }
        fn_02003890(0x050000E0, 0);
        fn_020041D4(11, 0);
        fn_02004098(11, 0, 2, 0);
        fn_02003394(1, 1);
        fn_020033F4();
        fn_020037C8(5, 0, 1);
        fn_020038D8(0x06000800);
        fn_020041D4(12, 0);
        fn_02004098(12, 2, 0, 0);
        lbl_030027DD = 0;
        lbl_030027DE = 0;
        lbl_030027E4 = 0;
        lbl_030027DB = 0;
        lbl_030027E5 = -1;
        lbl_030027E7 = 0;
        lbl_030027F2 = 0;
        lbl_030027E8 = 0;
        lbl_030027DA = 1;
    }
    fn_02003394(1, 0);
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

s32 fn_02011AF4(void)
{
    struct List *list;
    struct Entry *entries;
    s32 ret;

    if (!(gDataFlags & 4)) {
        if (lbl_030029AC & 2) {
            lbl_030027E5 = -1;
            m4aSongNumStart(3);
            return 1;
        }
        if (++lbl_030027F2 >= 60) {
            Link_SendRequest(2, lbl_030027E0);
            lbl_030027F2 = 0;
        }
        return 0;
    }
    list = &gListBuf;
    entries = lbl_0203A810;
    if (lbl_030027DD == 0) {
        entries[lbl_030027E0].unk6 |= 1;
        lbl_030027DE = fn_02013B1C(gDetailBuf);
    }
    if (lbl_030027DD < lbl_030027DE)
        fn_0201396C();
    ret = 0;
    if (lbl_030027E3 < 0) {
        if (lbl_030029AC & 2) {
            lbl_030027E5 = -1;
            ret = 1;
            m4aSongNumStart(3);
        } else if (lbl_030029AC & 1) {
            if ((entries[lbl_030027E0].unk6 & 0x18) && !(entries[lbl_030027E0].unk6 & 2)) {
                lbl_030027E3 = 0;
                lbl_030027E2 = 0;
                lbl_030027E5 = 0;
                lbl_030027E7 = 0;
                lbl_030027DB = 0;
                lbl_030027E6 = -1;
            } else if (!(entries[lbl_030027E0].unk6 & 4) && list->unkC && (entries[lbl_030027E0].unk6 & 0x20)) {
                lbl_030027E3 = 0;
                lbl_030027E2 = 2;
                lbl_030027E5 = 0;
                lbl_030027E7 = 0;
                lbl_030027DB = 0;
                lbl_030027E6 = -1;
            }
            m4aSongNumStart(2);
        } else if (lbl_030029AC & 0x300) {
            m4aSongNumStart(0);
        }
    } else {
        if (lbl_030027E3 == 0)
            ret = lbl_0202FC0C[lbl_030027E2].init();
        else if (lbl_030027E3 == 1)
            ret = lbl_0202FC0C[lbl_030027E2].main();
        else
            ret = lbl_0202FC0C[lbl_030027E2].exit();
        if (ret) {
            ret = 0;
            if (lbl_030027E3 <= 1) {
                lbl_030027E3++;
            } else {
                lbl_030027DB = 0;
                if (lbl_030027E2 == 0) {
                    if (lbl_030027E7) {
                        lbl_030027E2++;
                        lbl_030027E7 = 0;
                        lbl_030027E3 = 0;
                    } else if (!(entries[lbl_030027E0].unk6 & 4)) {
                        if (list->unkC && (entries[lbl_030027E0].unk6 & 0x20)) {
                            lbl_030027E2 += 2;
                            lbl_030027E3 = 0;
                        } else {
                            lbl_030027E3 = -1;
                            lbl_030027E5 = -1;
                        }
                    } else {
                        lbl_030027E3 = -1;
                        lbl_030027E5 = -1;
                    }
                } else if (lbl_030027E2 == 1) {
                    if (!(entries[lbl_030027E0].unk6 & 4)) {
                        if (list->unkC && (entries[lbl_030027E0].unk6 & 0x20)) {
                            lbl_030027E2++;
                            lbl_030027E3 = 0;
                        } else {
                            lbl_030027E3 = -1;
                            lbl_030027E5 = -1;
                        }
                    } else {
                        lbl_030027E3 = -1;
                        lbl_030027E5 = -1;
                    }
                } else if (lbl_030027E2 == 2) {
                    if (lbl_030027E5 < 0) {
                        lbl_030027E5 = -1;
                        lbl_030027E3 = -1;
                    } else {
                        lbl_030027E2++;
                        lbl_030027E3 = 0;
                    }
                } else if (lbl_030027E2 == 3) {
                    if (lbl_030027E5 < 0) {
                        lbl_030027E2--;
                        lbl_030027E3 = 0;
                    } else {
                        ret = 1;
                    }
                } else {
                    lbl_030027E5 = -1;
                    lbl_030027E3 = -1;
                }
            }
        }
    }
    fn_02013B3C();
    return ret;
}

s32 fn_02011E54(void)
{
    struct Window *win = gWindows;
    s32 ret;

    fn_02008178(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16) {
        win->unk1 += 8;
    } else {
        ret = 1;
        fn_02004320(11);
        fn_02004320(12);
        win->unk1 = 0;
    }
    return ret;
}

s32 fn_02011E94(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    if (lbl_030027DA == 0) {
        DmaClear32(DMA0, ret, gWindows, sizeof(struct Window) * 5);
        fn_02009C54(1, 16, 0, 2);
        fn_02003394(1, 0);
        fn_020033F4();
        fn_020037C8(5, 0, 0);
        fn_020037C8(6, 2, 0);
        fn_02003890(0x050000E0, 0);
        fn_02003890(0x05000100, 1);
        fn_020041D4(3, 0);
        fn_02004098(3, 1, 2, 0);
        fn_020038D8(0x06008400);
        lbl_030027DD = 0;
        lbl_030030A4 = 0;
        lbl_030027F0 = 0;
        lbl_030027E5 = 0;
        fn_02009DA8(1, 1);
        fn_02009CBC(1, 1, 8);
        lbl_030027DA = 1;
    }
    win = &gWindows[1];
    fn_02003394(1, 0);
    fn_020033F4();
    fn_02005968(win);
    fn_02005A50(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        win->unk1 = ret;
        fn_02009F68(gSession.unk64[0], 1, 1);
        ret = 1;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

s32 fn_02011FBC(void)
{
    struct Window *win = &gWindows[1];
    s32 id;
    s32 attr;
    s32 ret;

    if (lbl_030027DD < win->unkE) {
        id = gSession.unk64[lbl_030027DD];
        fn_02003394(1, 0);
        fn_020033F4();
        if (id > 0) {
            fn_020038F4(16);
            fn_02003464(fn_0201AAAC(id), 0);
        }
        fn_020059D4(win, lbl_030027DD, 0);
        attr = fn_02004D3C(lbl_030027DD) ? 6 : 5;
        if (attr == 5 && (fn_02004CAC(lbl_030027DD) == 1 || fn_02004CAC(lbl_030027DD) == 3))
            attr = 6;
        fn_02009AB8(1, win->unk5, lbl_030027DD, lbl_030027DD, attr);
        lbl_030027DD++;
        if (lbl_030027DD < win->unkE)
            return 0;
    }
    fn_02003394(1, 0);
    ret = fn_02013D70();
    fn_0201361C(win->unk10 * 8 - 10, (win->unk12 + 1) * 8 + win->unk2 * 16);
    attr = lbl_030027F0 + win->unkE < 64;
    fn_02009BB0(1, win->unk5, (u8)((attr << 8) | 64));
    fn_02013C54();
    if (lbl_030027E5)
        fn_02009DA8(1, 1);
    return ret;
}

s32 fn_020120D0(void)
{
    s32 ret = 0;
    struct Window *win;

    fn_02003394(1, 0);
    fn_020033F4();
    win = &gWindows[1];
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        ret = lbl_030027E5;
        fn_02004320(3);
        win->unk1 = 0;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

s32 fn_02012120(void)
{
    struct Window *win = gWindows;
    char buf[256];
    s32 w;
    s32 len;
    s32 n;
    s32 i;
    s32 row;
    s32 ret;

    if (lbl_030027DA == 0) {
        memset(win, 0, sizeof(struct Window));
        memset(buf, 0, sizeof(buf));
        fn_020140F4(buf, 0);
        fn_02003394(1, 0);
        fn_020033F4();
        fn_02003464(buf, 0);
        w = fn_02003910();
        memset(buf, 0, sizeof(buf));
        fn_020140F4(buf, 1);
        len = fn_02003464(buf, 2);
        if (len > w)
            w = len;
        len = fn_02003464(fn_0201AA44(7), 2);
        if (len > w)
            w = len;
        if (lbl_030027E9 & 0x18) {
            memset(buf, 0, sizeof(buf));
            fn_020140F4(buf, 2);
            len = fn_02003464(buf, 2);
            if (len > w)
                w = len;
        }
        n = w >> 3;
        if (w & 7)
            n++;
        w = n;
        win->unk0 = 1;
        win->unk10 = (28 - w) >> 1;
        win->unk12 = 2;
        n = lbl_030027E9 ? 6 : 5;
        win->unkE = n;
        win->unk2 = n - 2;
        win->unk14 = w + 2;
        win->unk16 = n * 2 + 2;
        win->unk3 = 0;
        win->unk4 = 0;
        win->unk5 = 2;
        win->unk6 = 0;
        win->unk7 = 0;
        fn_020041D4(3, 0);
        fn_02004098(3, 0, win->unk5, 0);
        for (i = 0; i < win->unkE; i++) {
            win->items[i].unk0 = 1;
            win->items[i].unk4 = fn_0201A73C(0);
        }
        fn_020059D4(win, 0, 0);
        lbl_030027E5 = 0;
        lbl_030027E7 = 0;
        lbl_030027DA = 1;
    }
    fn_02003394(1, 0);
    fn_020033F4();
    row = win->unk1 >> 3;
    if (row != 0 && row < win->unkE) {
        memset(buf, 0, sizeof(buf));
        if (row == 1) {
            fn_020140F4(buf, 1);
            fn_02003464(buf, 0);
        }
        if (lbl_030027E9 && row <= 3) {
            if (row == 2) {
                fn_020140F4(buf, 2);
                fn_02003464(buf, 0);
            } else if (row == 3) {
                fn_02003464(fn_0201AA44(7), 0);
            }
        } else if (!lbl_030027E9 && row == 2) {
            fn_02003464(fn_0201AA44(7), 0);
        } else {
            fn_020038F4(16);
            if (lbl_030027E9)
                fn_02003464(fn_0201A73C(row - 2), 0);
            else
                fn_02003464(fn_0201A73C(row - 1), 0);
        }
        fn_020059D4(win, row, 0);
    }
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) < win->unk16 - 2) {
        win->unk1 += 8;
    } else {
        ret = 1;
        win->unk1 = 0;
    }
    return ret;
}
