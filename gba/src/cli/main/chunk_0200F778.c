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
    s8 unk5E[4];
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

extern s8 lbl_030027C4;
extern s8 lbl_030027C5;
extern s8 lbl_030027C6;
extern s8 lbl_030027C7;
extern s8 lbl_030027C8;
extern s32 lbl_030027CC;
extern s8 lbl_030027D0;
extern s8 lbl_030027D1;
extern s8 lbl_030027D2;
extern s16 lbl_030027D4;
extern u8 gInputLockFrames;
extern u16 lbl_0300299C;
extern u16 lbl_030029AC;
extern u32 lbl_03002AC8;
extern u8 gMenuHasInput;
extern u16 gDataFlags;
extern s8 gItemUseFlags;
extern u8 gLanguage;
extern struct Work gSession;
extern s8 gScreenStep;
extern s32 lbl_030030A4;
extern s32 gScreenInitDone;
extern struct Window gWindows[];
extern u8 gOpenMenuReq;
extern s32 lbl_030032EC;
extern u8 gDetailBuf[];

void m4aSongNumStart(u16);
void fn_02000CF0(s32, s32, s32);
void Link_SendItemOp(u8, u8, u8);
void Link_SendEquipSlot(u8, u8);
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
s32 fn_02004D3C(s32);
s32 Item_CanEquip(u16 *);
s32 fn_02004E74();
void fn_02005968(struct Window *);
void fn_020059D4(struct Window *, s32, s32);
void fn_02005A50(struct Window *);
void fn_0200714C(struct Window *);
void fn_02008178(struct Window *);
u32 fn_02009340(struct Window *, s32, s32);
void fn_020093B4(s32, s32);
s32 fn_02009414(s32);
void fn_020095AC(s32);
void fn_02009A14(s32, s32, s32);
void fn_02009AB8(s32, s32, s32, s32, s32);
void fn_02009B80(struct Window *, s32);
void fn_02009BB0(s32, s32, s32);
void fn_02009C54(s32, s32, s32, s32);
void fn_02009CBC(s32, s32, s32);
void fn_02009D68(s32, s32);
void fn_02009DA8(s32, s32);
void fn_02009F68(s32, s32, s32);
s32 fn_0201106C(void);
s32 fn_020110E0(void);
void fn_0201111C(s32, s32);
void fn_02011170(s32);
void fn_020111A4(void);
s32 fn_02011244(void);
char *fn_0201A73C(s32);
char *fn_0201A83C(s32);
char *fn_0201AAAC(s32);
s32 fn_0201AB14(s32);

void fn_0200FB60(void);
void fn_0200FC10(void);
void fn_0200FF54(s32);
void fn_0200FFB0(void);
s32 fn_020101EC(void);
s32 fn_0201027C(void);
void fn_020102B0(s32, s32);
s32 fn_02010334(s32);
void fn_020103D8(void);
void fn_020103F0(s32);
void fn_02010420(void);
void fn_020109A0(void);
void fn_02010A50(void);
void fn_02010E54(void);

void fn_0200F778(void)
{
    struct Window *win;

    DmaClear32(DMA0, 0, gWindows, sizeof(struct Window) * 5);
    fn_020093B4(0, 2);
    fn_02009C54(1, 5, 15, 1);
    fn_02009B80(&gWindows[1], 1);

    win = &gWindows[2];
    win->unk0 = 1;
    win->unk10 = 1;
    win->unk12 = 2;
    win->unkE = 4;
    win->unk14 = 14;
    win->unk16 = 11;
    win->unk3 = 7;
    win->unk4 = 0;
    win->unk5 = 2;
    win->unk6 = 2;
    win->unk7 = 0;
    fn_02009B80(win, 1);

    fn_02003394(1, 0);
    fn_020033F4();
    fn_020037C8(3, 0, 0);
    fn_020037C8(4, 0, 0);
    fn_020037C8(5, 0, 0);
    fn_020037C8(6, 2, 0);
    fn_02003890(0x050000E0, 1);
    fn_020038D8(0x06008000);
    fn_020038D8(0x06008800);
    fn_020038D8(0x06000400);
    fn_020041D4(17, 0);
    fn_020041D4(3, 0);
    fn_020041D4(10, 0);
    fn_02004098(17, 0, 2, 0);
    fn_02004098(3, 1, 1, 0);
    fn_02004098(10, 2, 2, 0);
    fn_02009DA8(2, 1);
    fn_02009CBC(2, 1, 7);
    lbl_030027C6 = 0;
    lbl_030027C4 = 0;
    lbl_030027C5 = 0;
    lbl_030032EC = 0;
    lbl_030030A4 = 0;
    lbl_030027C7 = 0;
    gScreenInitDone = 1;
}

s32 EquipScreen_Init(void)
{
    s32 ret;
    struct Window *win;

    if (gScreenInitDone == 0)
        fn_0200F778();
    ret = fn_02009414(0);
    win = &gWindows[2];
    fn_02003394(1, 0);
    fn_020033F4();
    fn_02005968(win);
    fn_02005A50(win);
    if ((win->unk1 >> 3) < win->unk16 - 2)
        win->unk1 += 8;
    if (ret) {
        win->unk1 = 0;
        lbl_030027C8 = gItemUseFlags;
    }
    return ret;
}

s32 EquipScreen_Main(void)
{
    struct Window *win;
    s32 ret;

    fn_020095AC(0);
    win = &gWindows[2];
    fn_0200714C(win);
    if (!(gDataFlags & 0x10) && (lbl_030029AC & 2)) {
        lbl_030027C4 = 1;
        gOpenMenuReq = 1;
        m4aSongNumStart(3);
        return 1;
    }
    if (lbl_030027C5 < win->unkE) {
        fn_0200FF54(lbl_030027C5);
        lbl_030027C5++;
        if (lbl_030027C5 < win->unkE)
            return 0;
        fn_02010420();
    }
    if (lbl_030027C8 != gItemUseFlags && lbl_030032EC)
        lbl_030030A4 = 2;
    if (lbl_030032EC == 1 && lbl_030030A4 == 0) {
        ret = fn_020101EC();
        if (ret) {
            lbl_030030A4++;
            gWindows[2].unk1 = 0;
        }
    } else if (!lbl_030032EC || lbl_030030A4 == 1) {
        if (gMenuHasInput)
            fn_0200FC10();
        else if (lbl_030032EC)
            lbl_030030A4++;
    } else if (lbl_030032EC == 1 && lbl_030030A4 == 2) {
        ret = fn_0201027C();
        if (ret) {
            lbl_030030A4 = 0;
            lbl_030032EC--;
            fn_02010420();
        }
    }
    fn_0200FFB0();
    if (gMenuHasInput)
        fn_0200FB60();
    ret = lbl_030027C4 != 0;
    if (!lbl_030032EC || lbl_030030A4 == 1)
        lbl_030027C8 = gItemUseFlags;
    if (ret)
        fn_02009DA8(2, 1);
    return ret;
}

s32 EquipScreen_Exit(void)
{
    struct Window *win = gWindows;
    s32 ret;

    fn_02008178(win);
    fn_02008178(win + 2);
    ret = 0;
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        ret = 1;
        fn_02004320(17);
        fn_02004320(3);
        fn_02004320(10);
        win->unk1 = 0;
        win[2].unk1 = 0;
    } else {
        win->unk1 += 8;
        win[2].unk1 += 8;
    }
    if (!ret && (win[2].unk1 >> 3) < win[2].unk16 - 2)
        fn_0200714C(&win[2]);
    return ret;
}

void fn_0200FB60(void)
{
    struct Window *win;
    s32 x;
    s32 y;
    s32 pal = fn_02004030(0, 45);

    if (!lbl_030032EC || (lbl_03002AC8 & 2)) {
        win = &gWindows[2];
        x = (win->unk10 - 1) * 8;
        y = (win->unk12 + 2) * 8;
        y += win->unk2 * 16;
        fn_02003C3C(x, y, 0, 45, pal, win->unk5, 0);
    }
    if (lbl_030032EC == 1 && lbl_030030A4 == 1) {
        win = &gWindows[1];
        x = (win->unk10 - 1) * 8;
        y = (win->unk12 + 1) * 8;
        y += win->unk2 * 16;
        fn_02003C3C(x, y, 0, 45, pal, win->unk5, 0);
    }
}

void fn_0200FC10(void)
{
    u8 *list;
    struct Window *win;
    s32 n;
    s32 idx;
    s32 row;
    s32 pal;

    if (lbl_0300299C == 0)
        return;
    list = gDetailBuf;
    if (lbl_030032EC == 0) {
        win = &gWindows[2];
        n = win->unkE;
    } else {
        win = &gWindows[1];
        n = list[0];
        n++;
    }
    list++;
    if (lbl_0300299C & 0x40) {
        if (lbl_030032EC == 0) {
            if (win->unk2 != 0) {
                win->unk2--;
                m4aSongNumStart(1);
            } else {
                win->unk2 = n - 1;
            }
            fn_02010420();
            m4aSongNumStart(1);
        } else if (win->unk2 != 0) {
            win->unk2--;
            fn_02010420();
            m4aSongNumStart(1);
        } else if (lbl_030027C6 == 0) {
            m4aSongNumStart(0);
        } else {
            fn_02009A14(1, 1, win->unk5);
            idx = lbl_030027C6 - 1;
            row = idx + lbl_030027C7;
            fn_020102B0(idx, row % win->unkE);
            pal = fn_02010334(idx) ? 5 : 6;
            fn_02009AB8(1, win->unk5, row % win->unkE, 0, pal);
            lbl_030027C6--;
            fn_02010420();
            m4aSongNumStart(1);
        }
    } else if (lbl_0300299C & 0x80) {
        if (lbl_030032EC == 0) {
            if (win->unk2 < win->unkE - 1)
                win->unk2++;
            else
                win->unk2 = 0;
            fn_02010420();
            m4aSongNumStart(1);
        } else if (win->unk2 < win->unkE - 1) {
            win->unk2++;
            fn_02010420();
            m4aSongNumStart(1);
        } else if (lbl_030027C6 + win->unkE >= n) {
            m4aSongNumStart(0);
        } else {
            fn_02009A14(0, 1, win->unk5);
            idx = lbl_030027C6 + win->unkE;
            row = idx + lbl_030027C7;
            fn_020102B0(idx, row % win->unkE);
            pal = fn_02010334(idx) ? 5 : 6;
            fn_02009AB8(1, win->unk5, row % win->unkE, win->unkE - 1, pal);
            lbl_030027C6++;
            fn_02010420();
            m4aSongNumStart(1);
        }
    }
    if (lbl_0300299C & 0xC0)
        return;
    if (lbl_030029AC & 1) {
        if (lbl_030032EC == 0) {
            if (!(gItemUseFlags & 2)) {
                m4aSongNumStart(0);
                return;
            }
            lbl_030032EC = 1;
            lbl_030030A4 = 0;
        } else {
            idx = lbl_030027C6 + win->unk2;
            if (!fn_02010334(idx)) {
                m4aSongNumStart(0);
                return;
            }
            if (idx == 0)
                fn_020103D8();
            else
                fn_020103F0(*(list + idx - 1));
            fn_0200FF54(win[1].unk2);
            lbl_030030A4++;
        }
        m4aSongNumStart(2);
    } else if (lbl_030029AC & 2) {
        if (lbl_030032EC == 0) {
            lbl_030027C4 = 1;
            gOpenMenuReq = 1;
        } else {
            lbl_030030A4++;
        }
        m4aSongNumStart(3);
    } else if (lbl_030029AC & 0x300) {
        if (lbl_030032EC) {
            m4aSongNumStart(0);
        } else {
            if (lbl_030029AC & 0x100)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            m4aSongNumStart(6);
            lbl_030027C4 = 1;
        }
    }
}

void fn_0200FF54(s32 row)
{
    struct Window *win = &gWindows[2];

    fn_02003394(1, 0);
    fn_020033F4();
    fn_020038F4(16);
    if (gSession.unk5E[row] >= 0)
        fn_02003464(fn_0201AAAC(gSession.unk64[gSession.unk5E[row]]), 0);
    fn_020037A8(fn_02009340(win, row, 0), win->unk14);
}

void fn_0200FFB0(void)
{
    struct Window *win = &gWindows[2];
    s32 x;
    s32 y;
    s32 i;
    s32 id;
    s32 icon;
    s32 pal;
    s32 n;
    s8 *list;
    s32 idx;
    s32 flags;

    x = (win->unk10 + 1) * 8;
    y = (win->unk12 + 2) * 8;
    for (i = 0; i < win->unkE; i++, y += 16) {
        id = gSession.unk5E[i];
        if (id >= 0) {
            id = gSession.unk64[id];
            icon = fn_0201AB14(id);
            pal = fn_02004030(0, icon);
            fn_02003C3C(x, y, 0, icon, pal, win->unk5, 0);
        }
    }
    if (lbl_030032EC == 1 && lbl_030030A4 == 1) {
        win = &gWindows[1];
        x = (win->unk10 + 2) * 8;
        y = (win->unk12 + 1) * 8;
        list = (s8 *)gDetailBuf;
        n = *list++;
        n++;
        for (i = 0; i < win->unkE; i++, y += 16) {
            idx = i + lbl_030027C6;
            if (idx == 0)
                continue;
            if (idx >= n)
                break;
            id = *(list + idx - 1);
            id = gSession.unk64[id];
            icon = fn_0201AB14(id);
            pal = fn_02004030(0, icon);
            fn_02003C3C(x, y, 0, icon, pal, win->unk5, 0);
        }
        x = (win->unk10 + 1) * 8;
        y = (win->unk12 + 1) * 8;
        if ((gLanguage & 15) == 1)
            icon = 24;
        else
            icon = 4;
        pal = fn_02004030(2, icon);
        for (i = 0; i < win->unkE; i++, y += 16) {
            idx = i + lbl_030027C6;
            if (idx == 0)
                continue;
            if (idx >= n)
                break;
            id = *(list + idx - 1);
            if (fn_02004D3C(id))
                fn_02003C3C(x, y + 4, 2, icon, pal, win->unk5, 0);
        }
        flags = lbl_030027C6 != 0;
        if (lbl_030027C6 + win->unkE < n)
            flags |= 2;
        fn_02009BB0(1, win->unk5, flags);
    }
}

s32 fn_020101EC(void)
{
    struct Window *win = &gWindows[1];
    s32 row;
    s32 ret;

    fn_02003394(1, 0);
    fn_020033F4();
    row = win->unk1 >> 3;
    if (row < win->unkE) {
        fn_020102B0(row + lbl_030027C6, row);
        win->items[row].unk0 = fn_02010334(row + lbl_030027C6);
    }
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        win->unk1 = ret;
        fn_02010420();
        lbl_030027C7 = win->unkE - lbl_030027C6 % win->unkE;
        ret = 1;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

s32 fn_0201027C(void)
{
    s32 ret = 0;
    struct Window *win = &gWindows[1];

    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        win->unk1 = ret;
        ret = 1;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

void fn_020102B0(s32 idx, s32 row)
{
    struct Window *win;
    u8 *list = gDetailBuf;
    s32 n = *list++ + 1;
    const char *str;
    s32 id;

    win = &gWindows[1];
    fn_02003394(1, 0);
    fn_020033F4();
    fn_020038F4(24);
    if (idx == 0) {
        str = fn_0201A73C(10);
    } else if (idx >= n) {
        str = fn_0201A73C(0);
    } else {
        id = gDetailBuf[idx];
        id = gSession.unk64[id];
        if (id > 0)
            str = fn_0201AAAC(id);
        else
            str = fn_0201A73C(0);
    }
    fn_02003464(str, 0);
    fn_020059D4(win, row, 0);
}

s32 fn_02010334(s32 idx)
{
    s32 slot = gWindows[2].unk2;
    s32 n = gDetailBuf[0];
    s32 size;
    struct ItemInfo *item;
    s32 mask;

    if (idx - 1 >= n)
        return 0;
    if (idx == 0) {
        if (slot <= 2)
            return 0;
        return gSession.unk5E[slot] >= 0;
    }
    if (fn_02004D3C(gDetailBuf[idx]))
        return 0;
    size = n + 1;
    if (size & 3)
        size = ((size >> 2) + 1) << 2;
    item = (struct ItemInfo *)(gDetailBuf + size);
    item += idx - 1;
    if (!Item_CanEquip((u16 *)item))
        return 0;
    mask = 0x100;
    if (slot != 0) {
        mask = 0x400;
        if (slot != 1) {
            mask = 0x3000;
            if (slot == 2)
                mask = 0xA00;
        }
    }
    return (item->flags & mask) != 0;
}

void fn_020103D8(void)
{
    gSession.unk5E[3] = -1;
    Link_SendEquipSlot(3, 0xFF);
}

void fn_020103F0(s32 id)
{
    s32 slot = gWindows[2].unk2;

    gSession.unk5E[slot] = id;
    Link_SendEquipSlot(slot, id);
}

void fn_02010420(void)
{
    struct Window *win;
    s8 *list;
    struct ItemInfo *item;
    s32 n;
    s32 mode;
    s32 idx;
    s32 i;
    s8 id;
    s32 size;
    s32 msg;
    s32 x;
    s32 digits;

    fn_02003394(0, 0);
    fn_020033F4();
    mode = lbl_030032EC;
    i = 1;
    if (mode == 0)
        i = 2;
    win = &gWindows[i];
    list = (s8 *)gDetailBuf;
    n = *list++;
    if (mode == 0) {
        id = gSession.unk5E[win->unk2];
        for (i = 0; i < n; i++) {
            if (id == list[i])
                break;
        }
        idx = -1;
        if (i < n)
            idx = i;
    } else {
        idx = lbl_030027C6 + win->unk2;
        if (idx > 0) {
            idx--;
            if (idx >= n)
                goto end;
        } else {
            idx = -1;
        }
    }
    if (idx < 0)
        goto end;
    size = n + 1;
    if (size & 3)
        size = ((size >> 2) + 1) << 2;
    list += size - 1;
    item = (struct ItemInfo *)list + idx;
    if (item->flags & 0x100)
        fn_02003464(fn_0201A73C(16), 0);
    else if (item->flags & 0xE00)
        fn_02003464(fn_0201A73C(63), 0);
    if (!(item->flags & 0x3000)) {
        fn_02003900(8);
        fn_02000CF0(item->count, fn_02003910(), 2);
    }
    if (!(item->flags & 0x100) && item->kind != 0) {
        if (item->flags & 0xE00)
            fn_02003900(8);
        fn_02003464(fn_0201A83C(item->kind - 1), 0);
        if ((item->flags & 0x3000) && item->count != 0 && item->kind != 16) {
            msg = fn_02004E74() ? 40 : 39;
            fn_02003900(8);
            fn_02003464(fn_0201A73C(msg), 0);
            x = fn_02003910();
            if (item->count <= 9)
                digits = 1;
            else if (item->count <= 99)
                digits = 2;
            else
                digits = 3;
            fn_02000CF0(item->count, x, digits);
        }
    }
end:
    fn_02009D68(2, 1);
}

void fn_020105BC(void)
{
    struct Window *win;
    s32 i;

    lbl_030030A4 = 0;
    DmaClear32(DMA0, 0, gWindows, sizeof(struct Window) * 5);
    fn_020093B4(0, 2);
    fn_02009C54(1, 2, 15, 2);
    fn_02009B80(&gWindows[1], 1);

    gWindows[2].unk0 = 1;
    gWindows[2].unk14 = 9;
    gWindows[2].unk10 = 11;
    gWindows[2].unk12 = 8;
    gWindows[2].unkE = 4;
    gWindows[2].unk16 = gWindows[2].unkE * 2 + 2;
    gWindows[2].unk3 = 3;
    gWindows[2].unk4 = 0;
    gWindows[2].unk5 = 1;
    gWindows[2].unk6 = 2;
    gWindows[2].unk7 = 0;
    fn_02009B80(&gWindows[2], 1);
    win = &gWindows[2];
    for (i = 0; i < win->unkE; i++) {
        if (i < win->unkE - 1)
            win->items[i].unk4 = fn_0201A73C(i + 33);
        else
            win->items[i].unk4 = fn_0201A73C(4);
    }

    fn_02003394(1, 0);
    fn_020037C8(4, 0, 0);
    fn_020037C8(5, 0, 0);
    fn_020037C8(6, 2, 0);
    fn_02003890(0x050000E0, 0);
    fn_02003890(0x05000100, 2);
    fn_02003890(0x05000120, 1);
    fn_020038D8(0x06008000);
    fn_020038D8(0x06008400);
    fn_020041D4(17, 0);
    fn_020041D4(3, 0);
    fn_020041D4(6, 0);
    fn_02004098(17, 0, 2, 0);
    fn_02004098(3, 1, 2, 0);
    fn_02004098(6, 2, 1, 0);
    fn_02009DA8(1, 1);
    fn_02009CBC(1, 1, 9);
    lbl_030027CC = 0;
    lbl_030027D1 = 0;
    lbl_030027D0 = 0;
    lbl_030027D2 = 0;
    lbl_030027D4 = 1;
    gScreenInitDone = 1;
}

s32 ItemScreen_Init(void)
{
    struct Window *win;
    s32 ret;

    fn_02003394(1, 0);
    if (gScreenInitDone == 0) {
        fn_020105BC();
        if (gScreenInitDone == 0)
            return 0;
    }
    fn_02009414(0);
    win = &gWindows[1];
    fn_02005968(win);
    fn_02005A50(win);
    ret = 0;
    if ((win->unk1 >> 3) >= win->unk16 - 2) {
        ret = 1;
        win->unk1 = 0;
        fn_02009F68(gSession.unk64[win->unk2], 1, 1);
    } else {
        win->unk1 += 8;
    }
    return ret;
}

s32 ItemScreen_Main(void)
{
    struct Window *win;
    s32 pal;

    fn_020095AC(0);
    fn_02003394(1, 0);
    fn_020033F4();
    win = &gWindows[1];
    if (lbl_030027D1 < win->unkE) {
        fn_0201111C(lbl_030027D1, lbl_030027D1);
        pal = fn_02004D3C(lbl_030027D1) ? 6 : 5;
        fn_02009AB8(1, win->unk5, lbl_030027D1, lbl_030027D1, pal);
        lbl_030027D1++;
        if (lbl_030027D1 < win->unkE)
            return 0;
    }
    if (lbl_030032EC && lbl_030030A4 == 1 && fn_02011244()) {
        fn_020111A4();
        lbl_030030A4 = 0;
    }
    if (lbl_030032EC && lbl_030030A4 == 0) {
        if (fn_0201106C()) {
            lbl_030030A4++;
            gWindows[2].unk1 = 0;
            gWindows[2].unk9[1] = 0;
        }
    } else if (!lbl_030032EC || lbl_030030A4 == 1) {
        if (gMenuHasInput)
            fn_02010A50();
        else if (lbl_030032EC)
            lbl_030030A4++;
    } else if (fn_020110E0()) {
        lbl_030030A4 = 0;
        gWindows[2].unk1 = 0;
        lbl_030032EC = 0;
    }
    fn_02010E54();
    if (gMenuHasInput)
        fn_020109A0();
    if (lbl_030027D0)
        fn_02009DA8(1, 1);
    return lbl_030027D0;
}

s32 ItemScreen_Exit(void)
{
    struct Window *win = gWindows;
    s32 ret = 0;

    fn_02003394(1, 0);
    fn_02008178(win);
    if ((win->unk1 >> 3) < win->unk16 - 1)
        win->unk1 += 8;
    win++;
    fn_02008178(win);
    if ((win->unk1 >> 3) >= win->unk16 - 1) {
        ret = 1;
        fn_02004320(17);
        fn_02004320(3);
        fn_02004320(6);
        win->unk1 = 0;
    } else {
        win->unk1 += 8;
    }
    return ret;
}

void fn_020109A0(void)
{
    struct Window *win;
    s32 x;
    s32 y;
    s32 pal = fn_02004030(0, 45);

    if (!lbl_030032EC || (lbl_03002AC8 & 2)) {
        win = &gWindows[1];
        x = (win->unk10 - 1) * 8;
        y = (win->unk12 + 1) * 8;
        y += win->unk2 * 16;
        fn_02003C3C(x, y, 0, 45, pal, win->unk5, 0);
    }
    if (lbl_030032EC && lbl_030030A4 == 1) {
        win = &gWindows[2];
        x = (win->unk10 - 1) * 8;
        y = (win->unk12 + 1) * 8;
        y += win->unk2 * 16;
        fn_02003C3C(x, y, 0, 45, pal, win->unk5, 0);
    }
}

void fn_02010A50(void)
{
    struct Window *win;
    s32 n;
    s32 idx;
    s32 pal;
    s32 type;

    if (lbl_0300299C == 0)
        return;
    win = &gWindows[1] + lbl_030032EC;
    n = 64;
    if (lbl_030032EC)
        n = win->unkE;
    if (lbl_0300299C & 0x40) {
        if (lbl_030032EC == 0) {
            if (win->unk2 != 0) {
                win->unk2--;
                fn_02011170(win->unk2 + lbl_030027CC);
                m4aSongNumStart(1);
            } else {
                fn_02009A14(1, 1, win->unk5);
                idx = (lbl_030027CC - 1) % n;
                if (idx < 0)
                    idx += n;
                fn_0201111C(idx, idx % win->unkE);
                pal = fn_02004D3C(idx) ? 6 : 5;
                fn_02009AB8(1, win->unk5, idx % win->unkE, 0, pal);
                lbl_030027CC--;
                fn_02011170(win->unk2 + lbl_030027CC);
                m4aSongNumStart(1);
            }
        } else {
            if (win->unk2 != 0)
                win->unk2--;
            else
                win->unk2 = n - 1;
            m4aSongNumStart(1);
        }
    } else if (lbl_0300299C & 0x80) {
        if (lbl_030032EC == 0) {
            if (win->unk2 < win->unkE - 1) {
                win->unk2++;
                fn_02011170(win->unk2 + lbl_030027CC);
                m4aSongNumStart(1);
            } else {
                fn_02009A14(0, 1, win->unk5);
                idx = (lbl_030027CC + win->unkE) % n;
                if (idx < 0)
                    idx += n;
                fn_0201111C(idx, idx % win->unkE);
                pal = fn_02004D3C(idx) ? 6 : 5;
                fn_02009AB8(1, win->unk5, idx % win->unkE, win->unkE - 1, pal);
                lbl_030027CC++;
                fn_02011170(win->unk2 + lbl_030027CC);
                m4aSongNumStart(1);
            }
        } else {
            if (win->unk2 < n - 1)
                win->unk2++;
            else
                win->unk2 = 0;
            m4aSongNumStart(1);
        }
    }
    if (lbl_0300299C & 0xC0)
        return;
    if (lbl_030029AC & 1) {
        if (lbl_030032EC == 0) {
            idx = (win->unk2 + lbl_030027CC) % 64;
            if (idx < 0)
                idx += 64;
            if (gSession.unk64[idx] == -1 || fn_02004D3C(idx)) {
                m4aSongNumStart(0);
                return;
            }
            lbl_030032EC = 1;
            lbl_030030A4 = 0;
            gWindows[1].unk1 = 0;
            type = fn_02004CAC(idx);
            if (type == 7)
                gWindows[2].items[0].unk0 = 1;
            else
                gWindows[2].items[0].unk0 = 0;
            if (type == 1)
                gWindows[2].items[1].unk0 = 0;
            else
                gWindows[2].items[1].unk0 = 1;
            if (!(gItemUseFlags & 1))
                gWindows[2].items[0].unk0 = 0;
            if (!(gItemUseFlags & 2))
                gWindows[2].items[1].unk0 = 0;
            m4aSongNumStart(2);
        } else {
            if (win->items[win->unk2].unk0 == 0) {
                m4aSongNumStart(0);
                return;
            }
            m4aSongNumStart(2);
            if (win->unk2 < win->unkE - 1) {
                m4aSongNumStart(2);
                idx = (gWindows[1].unk2 + lbl_030027CC) % 64;
                if (idx < 0)
                    idx += 64;
                if (win->unk2 == 0)
                    Link_SendItemOp(1, idx, 0);
                else if (win->unk2 == 1)
                    Link_SendItemOp(2, idx, 0);
                else
                    Link_SendItemOp(3, idx, 0);
                gInputLockFrames = 6;
            }
            lbl_030030A4++;
        }
    } else if (lbl_030029AC & 2) {
        if (lbl_030032EC == 0) {
            gOpenMenuReq = 1;
            lbl_030027D0 = 1;
        } else {
            lbl_030030A4++;
        }
        m4aSongNumStart(3);
    } else if (lbl_030029AC & 0x300) {
        if (lbl_030032EC) {
            m4aSongNumStart(0);
        } else {
            if (lbl_030029AC & 0x100)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            m4aSongNumStart(6);
            lbl_030027D0 = 1;
        }
    }
}
