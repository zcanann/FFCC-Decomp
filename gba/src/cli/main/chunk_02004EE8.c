#include "gba_types.h"

#define REG_DISPCNT (*(vu16 *)0x04000000)
#define REG_IE (*(vu16 *)0x04000200)

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

#define DmaClear16(dmaAddr, value, dst, size) \
    { \
        vu16 tmp = (vu16)(value); \
        DmaSet(dmaAddr, &tmp, dst, 0x81000000 | ((size) / 2)); \
    }

#define DmaClear32(dmaAddr, value, dst, size) \
    { \
        vu32 tmp = (vu32)(value); \
        DmaSet(dmaAddr, &tmp, dst, 0x85000000 | ((size) / 4)); \
    }

typedef unsigned long size_t;

void *memset(void *, int, size_t);
void *memcpy(void *, const void *, size_t);

struct Cmd {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 unk3;
};

struct Cmd16 {
    u8 unk0;
    u8 unk1;
    u16 unk2;
};

struct Flag3 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
};

struct Work {
    u8 unk0[0x5D];
    s8 unk5D;
    u8 unk5E[4];
    u16 unk62;
    u8 unk64[0xF4 - 0x64];
    s16 unkF4[8];
};

struct Member {
    void *unk0;
    s16 unk4;
    s8 unk6;
    s8 unk7;
};

struct Command {
    u8 unk0;
    u8 unk1;
    u16 unk2;
};

struct Task {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 unk3[0x70 - 3];
};

struct State {
    int (*init)(void);
    int (*main)(void);
    int (*exit)(void);
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
    u8 unkA[4];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    struct WinItem items[1];
};

extern u8 lbl_03002994;
extern u8 lbl_030029A0;
extern u8 lbl_030029A4;
extern u8 lbl_03002AC4;
extern u8 lbl_03002ACC;
extern u16 lbl_03002AEC;
extern u8 lbl_03002B00;
extern u8 lbl_03002B04;
extern u8 lbl_03002C98;
extern struct Work lbl_03002CA0;
extern struct Command lbl_03002DCC;
extern struct Flag3 lbl_03002DD0[64];
extern u8 lbl_03002ED0;
extern struct Flag3 lbl_03002EE0[16];
extern struct Member lbl_03002FD0[4];
extern u8 lbl_03002FF0;
extern s32 lbl_03003090;
extern u32 lbl_03003094;
extern s8 lbl_03003098;
extern s8 lbl_0300309C;
extern u8 lbl_030030A0;
extern s32 lbl_030030A4;
extern u32 lbl_030030A8;
extern u32 lbl_030030AC;
extern struct Task lbl_030030B0[5];
extern s8 lbl_030032E0;
extern u16 lbl_030032E4;
extern s32 lbl_030032E8;
extern u32 lbl_030032EC;
extern s8 lbl_030032F0;
extern s32 lbl_030032F4;
extern u8 lbl_030032F8;
extern s8 lbl_030032FC[2];
extern const struct State lbl_0202FA38[];
extern const struct State lbl_0202FAEC[];
extern const struct State lbl_0202FB34[];
extern const struct State lbl_0202FB64[];
extern u8 lbl_0203A800[];
extern u8 lbl_0203D800[];

void fn_02000990(void);
void fn_02000AD4(s32, s32, s32);
u32 fn_02000A40(s32, s32, s32);
void fn_0200163C(void);
void fn_0200194C(s32);
void fn_020025E4(s32);
void fn_020033F4(void);
void fn_02003464(const char *, s32);
void fn_020037A8(s32, s32);
void fn_020038F4(s32);
void fn_02003C3C(s32, s32, s32, s32, s32, s32, s32);
void fn_02003F74(s32, s32, s32, s32);
void fn_02004360(void);
void fn_02005844(void);
void fn_0200586C(void);
int fn_020051E4(void);
int fn_0200543C(void);
int fn_02005568(void);
int fn_020056A4(void);
int fn_020057B8(void);
void fn_02005B84(struct Window *, s32, s32, s32);
void fn_02006044(struct Window *, s32, s32);
void fn_020062A8(struct Window *, s32, s32);
void fn_02006670(struct Window *, s32, s32);
void fn_02006920(struct Window *, s32, s32);
void fn_02006BD4(struct Window *, s32, s32);
void fn_02006F30(struct Window *, s32, s32);
void fn_02007150(struct Window *, s32, s32);
void fn_0200743C(struct Window *, s32, s32);
void fn_020076A4(struct Window *, s32, s32);
void fn_020079FC(struct Window *, s32, s32);
void fn_02007D9C(struct Window *, s32, s32);
s32 fn_02009340(struct Window *, s32, s32);
void fn_02009318(void);
void fn_02009508(s32);
int fn_02009E2C(void);
int fn_02009ED0(void);
void fn_0200F348(void);
void fn_02014760(s32);
int fn_02015960(void);
int fn_020159E4(void);
int fn_02015B78(void);
void fn_02015E34(s32);
void fn_02019C4C(void);

void fn_02004EE8(u8 *p)
{
    int i;

    for (i = 0; i < 64; i++)
        lbl_03002DD0[i].unk3 = *p++;
    for (i = 0; i < 16; i++)
        lbl_03002EE0[i].unk3 = *p++;
}

void fn_02004F1C(u32 data)
{
    struct Cmd *cmd = (struct Cmd *)&data;
    s8 old = lbl_03002ED0;

    lbl_03002ED0 = cmd->unk2;
    if (lbl_03003090 == 0 && lbl_03002ED0 != old) {
        fn_02005844();
        fn_02000990();
    }
}

void fn_02004F54(u32 data)
{
    struct Cmd *cmd = (struct Cmd *)&data;
    s8 old = lbl_03002FF0;

    lbl_03002FF0 = cmd->unk2;
    if (lbl_03003090 == 0 && lbl_03002FF0 != old) {
        fn_02005844();
        fn_02000990();
    }
}

void fn_02004F8C(u8 *p)
{
    int size = 0x200;

    memcpy(lbl_0203A800, p, size);
    memset(&lbl_03002DCC, 0xFF, sizeof(lbl_03002DCC));
    lbl_03002B00 = 1;
    fn_02015E34(1);
}

void fn_02004FC0(u32 data)
{
    struct Cmd16 *cmd = (struct Cmd16 *)&data;

    lbl_03002DCC.unk0 = cmd->unk1;
    lbl_03002DCC.unk2 = cmd->unk2;
    lbl_03002B00 = 1;
}

void fn_02004FE4(u8 *p)
{
    int size = p[0] * 8 + 1;

    memcpy(lbl_0203D800, p, size);
    lbl_03002AEC |= 0x200;
}

void fn_02005010(u32 data)
{
    struct Cmd *cmd = (struct Cmd *)&data;

    lbl_03002B04 = cmd->unk2;
}

void fn_02005024(u32 data)
{
    struct Cmd *cmd = (struct Cmd *)&data;

    lbl_03002AC4 = cmd->unk2;
}

void fn_02005038(u32 data)
{
    struct Cmd *cmd = (struct Cmd *)&data;
    int old = lbl_03002CA0.unk5D;

    if (old == cmd->unk2)
        return;
    lbl_03002CA0.unk5D = cmd->unk2;
    lbl_03002CA0.unkF4[lbl_03002CA0.unk5D] = 0xFFFF;
    if (old < cmd->unk2 && lbl_03003090 == 1)
        fn_0200F348();
}

void fn_0200508C(u32 data)
{
    struct Cmd *cmd = (struct Cmd *)&data;

    lbl_03002CA0.unk62 = (u8)cmd->unk2;
    if ((u32)lbl_03003090 <= 3)
        fn_02009508(0);
}

void fn_020050B8(void)
{
    int i;

    for (i = 0; i < 4; i++)
        lbl_03002FD0[i].unk7 = 1;
}

void fn_020050D4(u32 data)
{
    struct Cmd *cmd = (struct Cmd *)&data;

    lbl_03002C98 = cmd->unk2;
}

void fn_020050E8(void)
{
    vu16 ie;

    lbl_03003094 = 0;
    fn_02009318();
    fn_02019C4C();
    lbl_03003090 = 0;
    fn_02005844();
    lbl_030032FC[0] = 0;
    lbl_030032FC[1] = -1;
    lbl_0300309C = 0;
    lbl_030030A0 = 0;
    fn_02015E34(0);
    ie = REG_IE;
    REG_IE = 0;
    lbl_030032F0 = 0;
    REG_IE = ie;
    lbl_030032E4 = 0;
    DmaClear32(DMA0, 0, lbl_030030B0, sizeof(lbl_030030B0));
    fn_02000990();
    lbl_030032E8 = lbl_03003090;
    lbl_030032E0 = 0;
    fn_02014760(0);
}

int fn_02005194(void)
{
    int ret;

    switch (lbl_03003094) {
    case 0:
        ret = fn_020051E4();
        break;
    case 1:
        ret = fn_0200543C();
        break;
    case 2:
        ret = fn_02005568();
        break;
    case 3:
        ret = fn_020056A4();
        break;
    case 4:
    default:
        ret = fn_020057B8();
        break;
    }
    return ret;
}

int fn_020051E4(void)
{
    int ret;
    int i;

    if (lbl_030032F0) {
        fn_02005844();
        fn_02000990();
    }
    if (lbl_03002994 && lbl_030029A0 && lbl_030029A4) {
        lbl_03003090 = lbl_030032E8;
        fn_0200194C(0);
        REG_DISPCNT = 0x9F40;
        fn_02000990();
        fn_02005844();
        lbl_03002994 = 0;
    }

    ret = 0;
    if (lbl_030032F4 == 0) {
        if (lbl_030029A4 || lbl_03003090 == 13) {
            if (lbl_03003090 == 0 && lbl_03002ED0 == 2)
                ret = fn_02015960();
            else
                ret = lbl_0202FA38[lbl_03003090].init();
        }
    } else if (lbl_030032F4 == 1) {
        if (lbl_03003090 == 0 && lbl_03002ED0 == 2)
            ret = fn_020159E4();
        else
            ret = lbl_0202FA38[lbl_03003090].main();
    } else {
        if (lbl_03003090 == 0 && lbl_03002ED0 == 2)
            ret = fn_02015B78();
        else
            ret = lbl_0202FA38[lbl_03003090].exit();
    }

    if (ret) {
        if (lbl_030032F4 <= 1) {
            lbl_030032F4++;
        } else {
            if (lbl_030032E0) {
                fn_02014760(lbl_03003090);
                lbl_03003090 = 10;
            } else if (lbl_03003090 == 10) {
                lbl_03003090 = lbl_030030B0[0].unk2;
            } else if (lbl_03003090 == 9 && lbl_0300309C == 2) {
                lbl_03003090 = 6;
            } else if (lbl_03003090 != 9 && lbl_0300309C) {
                lbl_03003090 = 9;
            } else {
                fn_0200163C();
                if (lbl_03003098 > 0) {
                    lbl_03003090++;
                    if (lbl_0202FA38[lbl_03003090].init == 0)
                        lbl_03003090++;
                    if (lbl_03003090 > 9)
                        lbl_03003090 = 0;
                } else {
                    lbl_03003090--;
                    if (lbl_0202FA38[lbl_03003090].init == 0)
                        lbl_03003090--;
                    if (lbl_03003090 < 0)
                        lbl_03003090 = 9;
                }
            }
            lbl_03003098 = 0;
            fn_02000990();
            fn_02005844();
        }
        for (i = 0; i < 5; i++)
            lbl_030030B0[i].unk1 = 0;
    }
    return ret;
}

int fn_0200543C(void)
{
    int ret;
    int i;

    if (lbl_030032F0) {
        fn_02005844();
        fn_02000990();
    }

    ret = 0;
    if (lbl_030032F4 == 0) {
        if (lbl_030029A4)
            ret = lbl_0202FAEC[lbl_03003090].init();
    } else if (lbl_030032F4 == 1) {
        ret = lbl_0202FAEC[lbl_03003090].main();
    } else {
        ret = lbl_0202FAEC[lbl_03003090].exit();
    }

    if (ret) {
        if (lbl_030032F4 <= 1) {
            lbl_030032F4++;
        } else {
            if (lbl_03003090 == 0 && ret < 0) {
                lbl_030029A4 = 0;
                lbl_03002ACC = 0;
                lbl_03003090 = 5;
            } else if (lbl_03003090 != 4) {
                if (ret > 0)
                    lbl_03003090++;
                else
                    lbl_03003090--;
            } else if (ret > 0) {
                lbl_030029A4 = 0;
                lbl_03002ACC = 0;
                lbl_03003090 = 5;
            } else {
                lbl_03003090 = lbl_030030A4;
            }
            fn_0200586C();
            fn_02000990();
        }
        for (i = 0; i < 5; i++)
            lbl_030030B0[i].unk1 = 0;
    }
    return ret;
}

int fn_02005568(void)
{
    int ret;
    int i;

    if (lbl_030032F0) {
        fn_02005844();
        fn_02000990();
        lbl_030030A0 = 0;
        lbl_030032FC[0] = 0;
    }

    ret = 0;
    if (lbl_030032F4 == 0) {
        if (lbl_030029A4)
            ret = lbl_0202FB34[lbl_03003090].init();
    } else if (lbl_030032F4 == 1) {
        ret = lbl_0202FB34[lbl_03003090].main();
    } else {
        ret = lbl_0202FB34[lbl_03003090].exit();
    }

    if (ret) {
        if (lbl_030032F4 <= 1) {
            lbl_030032F4++;
        } else {
            if (lbl_03003090 == 0 && ret < 0) {
                lbl_030029A4 = 0;
                lbl_03002ACC = 0;
                lbl_03003090 = 3;
            } else if (lbl_03003090 == 0 && ret != 0) {
                lbl_030032FC[0] = lbl_030030B0[0].unk2;
                switch (lbl_030032FC[0]) {
                case 0:
                    lbl_03003090 = 1;
                    break;
                case 1:
                    lbl_03003090 = 2;
                    break;
                }
            } else {
                lbl_03003090 = 0;
            }
            fn_0200586C();
            fn_02000990();
        }
        lbl_030030A0 = 0;
        for (i = 0; i < 5; i++)
            lbl_030030B0[i].unk1 = 0;
    }
    return ret;
}

int fn_020056A4(void)
{
    int ret;
    int i;

    if (lbl_030032F0) {
        fn_02005844();
        fn_02000990();
        lbl_030030A0 = 0;
        lbl_030032FC[0] = 0;
    }

    ret = 0;
    if (lbl_030032F4 == 0) {
        if (lbl_030029A4)
            ret = lbl_0202FB64[lbl_03003090].init();
    } else if (lbl_030032F4 == 1) {
        ret = lbl_0202FB64[lbl_03003090].main();
    } else {
        ret = lbl_0202FB64[lbl_03003090].exit();
    }

    if (ret) {
        if (lbl_030032F4 <= 1) {
            lbl_030032F4++;
        } else {
            if (lbl_03003090 == 0) {
                if (ret > 0) {
                    lbl_03003090 = 1;
                } else {
                    lbl_03002ACC = 0;
                    lbl_03003090 = 3;
                }
            } else if (lbl_03003090 == 1) {
                if (ret > 0)
                    lbl_03003090 = 2;
                else
                    lbl_03003090 = 0;
            } else {
                lbl_03003090 = 0;
            }
            fn_0200586C();
            fn_02000990();
        }
        lbl_030030A0 = 0;
        for (i = 0; i < 5; i++)
            lbl_030030B0[i].unk1 = 0;
    }
    return ret;
}

int fn_020057B8(void)
{
    int ret;
    int i;

    if (lbl_030032F0) {
        fn_02005844();
        fn_02000990();
    }

    ret = 0;
    if (lbl_030032F4 == 0) {
        if (lbl_030029A4) {
            lbl_030032F8 = 3;
            ret = fn_02009E2C();
        }
    } else {
        ret = fn_02009ED0();
    }

    if (ret) {
        if (lbl_030032F4 <= 1) {
            lbl_030032F4++;
        } else {
            lbl_030032F4 = 0;
            fn_0200586C();
            fn_02000990();
        }
        for (i = 0; i < 5; i++)
            lbl_030030B0[i].unk1 = 0;
    }
    return ret;
}

void fn_02005844(void)
{
    if (lbl_030029A0 || lbl_03003090 != 13) {
        fn_0200586C();
        fn_02004360();
    }
}

void fn_0200586C(void)
{
    vu16 ie;
    int i;
    u16 *map;

    if (lbl_030029A0 || lbl_03003090 != 13) {
        lbl_030030A8 = 0;
        lbl_030032F4 = 0;
        lbl_030030AC = 0;
        lbl_030032EC = 0;
        lbl_030030A4 = 0;
        lbl_030032E0 = 0;
        fn_02000AD4(15, 0, 0);
        ie = REG_IE;
        REG_IE = 0;
        lbl_030032F0 = 0;
        REG_IE = ie;
        fn_0200194C(0);
        for (i = 0; i < 32; i++)
            fn_02003F74(i, 0, 256, 256);
        REG_DISPCNT = 0x9F40;
        lbl_03002AEC &= 0xFC0F;
        map = (u16 *)0x06007FE0;
        DmaClear16(DMA0, 0, map, 32);
        map = (u16 *)0x0600DFE0;
        DmaClear16(DMA0, 0, map, 32);
        fn_020025E4((s8)lbl_03003090);
    }
}

int fn_02005964(void)
{
    return 0;
}

void fn_02005968(struct Window *win)
{
    int i;

    for (i = 0; i < win->unkE; i++) {
        if (win->items[i].unk2 == 0)
            break;
    }
    if (i < win->unkE) {
        fn_020033F4();
        fn_020038F4(win->unk7);
        fn_02003464(win->items[i].unk4, 0);
        fn_020037A8(fn_02009340(win, i, 0), win->unk14);
        win->items[i].unk2 = 1;
    }
}

void fn_020059D4(struct Window *win, s32 idx)
{
    fn_020037A8(fn_02009340(win, idx, 0), win->unk14);
}

s32 fn_020059EC(s32 a, s32 b)
{
    s32 pal;

    if (a) {
        pal = 5;
        if (!b)
            pal = 3;
    } else {
        pal = 6;
        if (!b)
            pal = 4;
    }
    return pal << 12;
}

s32 fn_02005A0C(s32 type)
{
    s32 tile;

    tile = 0x80;
    if (type != 0) {
        tile = 0x15C;
        if (type != 1) {
            tile = 0x29C;
            if (type == 2)
                tile = 0x238;
        }
    }
    return tile;
}

s32 fn_02005A2C(s32 type)
{
    s32 tile;

    tile = 0;
    if (type != 0) {
        tile = 32;
        if (type != 1) {
            tile = 64;
            if (type != 2) {
                tile = 0x300;
                if (type == 3)
                    tile = 96;
            }
        }
    }
    return tile;
}

void fn_02005A50(struct Window *win)
{
    s32 tile;
    s32 pal;

    if (win->unk6 == 0) {
        tile = 0;
        pal = 10;
    } else if (win->unk6 == 1) {
        tile = 32;
        pal = 11;
    } else if (win->unk6 == 2) {
        tile = 64;
        pal = 12;
    } else if (win->unk6 == 3) {
        tile = 96;
        pal = 13;
    } else {
        tile = 0x300;
        pal = 14;
    }
    tile += 4;
    pal <<= 12;

    switch (win->unk3) {
    case -1:
        fn_02007D9C(win, tile, pal);
        break;
    case 0:
        if (win->unk4)
            fn_02006044(win, tile, pal);
        else
            fn_02005B84(win, tile, pal, win->unk3);
        break;
    case 1:
    case 2:
    case 13:
        fn_020062A8(win, tile, pal);
        break;
    case 3:
        fn_02006670(win, tile, pal);
        break;
    case 4:
        fn_02006920(win, tile, pal);
        break;
    case 5:
        fn_02006BD4(win, tile, pal);
        break;
    case 6:
        fn_02006F30(win, tile, pal);
        break;
    case 7:
        fn_02007150(win, tile, pal);
        break;
    case 8:
        fn_0200743C(win, tile, pal);
        break;
    case 9:
        fn_020076A4(win, tile, pal);
        break;
    case 10:
        fn_02005B84(win, tile, pal, win->unk3);
        break;
    case 14:
        fn_020079FC(win, tile, pal);
        break;
    }
}

void fn_02005B84(struct Window *win, s32 tile, s32 pal, s32 type)
{
    u16 buf[30];
    s32 x;
    s32 py;
    s32 y;
    s32 next;
    s32 row;
    s32 mod;
    s32 odd;
    s32 grp;
    s32 base;
    s32 pal2;
    s32 i;
    s32 edge;
    s32 size;
    s32 frame;
    s32 flags;
    s32 bottom;
    u16 *map;

    x = win->unk10 * 8;
    y = win->unk12 * 8 + win->unk1;
    py = y + 8;

    if (win->unk1 == 0) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0 || i == win->unk14 - 1)
                buf[i] = pal | tile;
            else if (i == 1 || i == win->unk14 - 2)
                buf[i] = (tile + 1) | pal;
            else if (i == 2 || i == win->unk14 - 3)
                buf[i] = (tile + 2) | pal;
            else
                buf[i] = (tile + 3) | pal;
            if (i >= win->unk14 >> 1)
                buf[i] |= 0x400;
        }
        map = (u16 *)fn_02000A40(win->unk5, win->unk10, win->unk12);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        pal2 = fn_020059EC(win->items[0].unk0, win->unk6);
        for (i = 0; i < win->unk14; i++) {
            if (i & 1)
                buf[i] = (tile - 4) | pal2;
            else
                buf[i] = (tile - 2) | pal2;
        }
        buf[0] = pal | (tile + 4);
        buf[win->unk14 - 1] = (tile + 4) | 0x400 | pal;
        map = (u16 *)fn_02000A40(win->unk5, win->unk10, win->unk12 + 1);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
    } else {
        row = win->unk1 >> 3;
        mod = 0;
        odd = 0;
        if (row == 0)
            goto sprites;
        base = fn_02005A0C(win->unk6);
        py = y;
        if (win->unk9 == 0) {
            odd = !(row & 1);
            grp = (row - 1) >> 1;
            base = base + grp * 2 * win->unk14 + odd;
        } else {
            row--;
            mod = row % 3;
            if (mod <= 1) {
                odd = mod & 1;
                grp = row / 3;
                base = base + win->unk14 * 2 * grp + odd;
            } else {
                base = tile - 4;
                grp = row / 3;
            }
        }
        pal2 = fn_020059EC(win->items[grp].unk0, win->unk6);
        next = py + 8;
        for (i = 1; i < win->unk14 - 1; i++) {
            if (i & 1) {
                buf[i] = pal2 | base;
            } else {
                buf[i] = (base + 2) | pal2;
                if (mod <= 1)
                    base += 4;
            }
        }

        edge = 0;
        if (win->unk9) {
            odd = 0;
            if (mod > 1)
                odd = 1;
            if ((grp == 0 && mod == 0) || (grp == win->unkE - 1 && odd))
                edge = 1;
        }
        if (win->unk9 ? edge : ((grp == 0 && !odd) || (grp == win->unkE - 1 && odd))) {
            buf[0] = (tile + 4) | pal;
            buf[win->unk14 - 1] = (tile + 4) | pal;
            buf[win->unk14 - 1] |= 0x400;
            if (grp == win->unkE - 1 && odd) {
                buf[0] |= 0x800;
                buf[win->unk14 - 1] |= 0x800;
            }
        } else {
            buf[0] = (tile + 5) | pal;
            buf[win->unk14 - 1] = (tile + 5) | pal;
            buf[win->unk14 - 1] |= 0x400;
        }
        map = (u16 *)fn_02000A40(win->unk5, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        py = next;
        bottom = (win->unk12 + win->unk16) * 8 - 8;
        if (py < bottom)
            goto sprites;
        for (i = 0; i < win->unk14; i++) {
            if (i == 0 || i == win->unk14 - 1)
                buf[i] = pal | tile;
            else if (i == 1 || i == win->unk14 - 2)
                buf[i] = (tile + 1) | pal;
            else if (i == 2 || i == win->unk14 - 3)
                buf[i] = (tile + 2) | pal;
            else
                buf[i] = (tile + 3) | pal;
            if (i >= win->unk14 >> 1)
                buf[i] |= 0x400;
            buf[i] |= 0x800;
        }
        map = (u16 *)fn_02000A40(win->unk5, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
    }

sprites:
    if ((py >> 3) - win->unk12 < win->unk16) {
        flags = 0x20000000;
        for (i = 0; i < win->unk14; i++) {
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
            size = 13;
            if (!type)
                size = 3;
            fn_02003C3C(x, py, size, frame, win->unk4, win->unk5, flags);
            x += 8;
        }
    }
}

void fn_02006044(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[2];
    s32 pal2;
    s32 w;
    s32 x;
    s32 y;
    u16 *map;
    s32 col;
    s32 n;
    s32 i;
    s32 k;
    s32 t;
    s32 frame;
    s32 flags;

    x = (win->unk10 + (win->unk14 >> 1)) * 8 - 8;
    x -= win->unk1;
    y = win->unk12 * 8;
    pal2 = fn_020059EC(1, win->unk6);
    w = ((win->unk1 + 8) >> 2) - 1;
    col = x >> 3;
    map = (u16 *)fn_02000A40(win->unk5, col, win->unk12);
    n = win->unk14 - 2;
    col -= win->unk10;
    if (col < 0)
        return;

    for (i = 0; i < win->unk16; i++) {
        if (col == 0 || i == 0 || i + 1 >= win->unk16) {
            if (col == 0) {
                if (i == 0 || i + 1 >= win->unk16)
                    buf[0] = (tile + 6) | pal;
                else if (i == 1 || i + 2 >= win->unk16)
                    buf[0] = (tile + 9) | pal;
                else if (i == 2 || i + 3 >= win->unk16)
                    buf[0] = (tile + 10) | pal;
                else
                    buf[0] = (tile + 11) | pal;
            } else if (col == 1) {
                buf[0] = (tile + 7) | pal;
            } else {
                buf[0] = (tile + 8) | pal;
            }
            if (i >= win->unk16 >> 1)
                buf[0] |= 0x800;
            buf[1] = buf[0] | 0x400;
        } else {
            k = i - 1;
            if (k % 3 <= 1) {
                if (k % 3 == 0)
                    t = k / 3 * (n * 2 + n) + 128;
                else
                    t = k / 3 * (n * 2 + n) + 129;
                t += (col - 1) * 2;
            } else {
                t = k / 3 * (n * 2 + n) + 128 + n * 2 + (col - 1);
            }
            buf[0] = pal2 | t;
            if (k % 3 <= 1)
                t += w * 2;
            else
                t += w;
            buf[1] = t | pal2;
        }
        map[0] = buf[0];
        map[w] = buf[1];
        map += 32;
    }

    if (col == 0)
        return;
    x -= 8;
    w = (w + 2) * 8;
    flags = 0;
    for (i = 0; i < win->unk16; i++, y += 8) {
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
        fn_02003C3C(x, y, 3, frame, 0, win->unk5, flags);
        fn_02003C3C(x + w, y, 3, frame, 0, win->unk5, flags | 0x10000000);
    }
}

void fn_020062A8(struct Window *win, s32 tile, s32 pal)
{
    u16 buf[30];
    s32 x;
    s32 py;
    s32 y;
    s32 next;
    s32 row;
    s32 mod;
    s32 grp;
    s32 base;
    s32 pal2;
    s32 i;
    s32 size;
    s32 frame;
    s32 bottom;
    u16 *map;

    x = win->unk10 * 8;
    y = win->unk12 * 8 + win->unk1;
    py = y + 8;
    if (py >> 3 > win->unk12 + win->unk16)
        return;

    if (win->unk1 == 0) {
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                buf[0] = pal | tile;
            else if (i != win->unk14 - 1) {
                if (i & 1)
                    buf[i] = pal | (tile + 1);
                else
                    buf[i] = pal | (tile + 2);
            } else
                buf[i] = pal | (tile + 3);
        }
        map = (u16 *)fn_02000A40(win->unk5, win->unk10, win->unk12);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
        pal2 = fn_020059EC(win->items[0].unk0, win->unk6);
        for (i = 0; i < win->unk14; i++) {
            if (i & 1)
                buf[i] = (tile - 4) | pal2;
            else
                buf[i] = (tile - 2) | pal2;
        }
        buf[0] = pal | (tile + 4);
        buf[win->unk14 - 1] = pal | (tile + 5);
        map = (u16 *)fn_02000A40(win->unk5, win->unk10, win->unk12 + 1);
        DmaSet(DMA0, buf, map, 0x80000000 | win->unk14);
    } else {
        row = (win->unk1 >> 3) - win->unk8;
        if (row == 0)
            goto sprites;
        base = fn_02005A0C(win->unk6);
        py = y;
        if (win->unk9 == 0) {
            mod = !(row & 1);
            grp = (row - 1) >> 1;
            base = base + grp * 2 * win->unk14 + mod;
        } else {
            mod = (row - 1) % 3;
            if (mod <= 1) {
                grp = (row - 1) / 3;
                base = base + grp * 2 * win->unk14 + (mod & 1);
            } else {
                base = tile - 4;
                grp = 0;
            }
        }
        pal2 = fn_020059EC(win->items[grp].unk0, win->unk6);
        next = py + 8;
        for (i = 1; i < win->unk14 - 1; i++) {
            if (i & 1) {
                buf[i] = pal2 | base;
            } else {
                buf[i] = (base + 2) | pal2;
                if (mod <= 1)
                    base += 4;
            }
        }
        if (row & 1) {
            buf[0] = (tile + 4) | pal;
            buf[win->unk14 - 1] = (tile + 5) | pal;
        } else {
            buf[0] = (tile + 6) | pal;
            buf[win->unk14 - 1] = (tile + 7) | pal;
        }
        map = (u16 *)fn_02000A40(win->unk5, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
        py = next;
        bottom = (win->unk12 + win->unk16) * 8 - 8;
        if (py < bottom)
            goto sprites;
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                buf[0] = (tile + 8) | pal;
            else if (i != win->unk14 - 1) {
                if (i & 1)
                    buf[i] = (tile + 9) | pal;
                else
                    buf[i] = (tile + 10) | pal;
            } else
                buf[i] = (tile + 11) | pal;
        }
        map = (u16 *)fn_02000A40(win->unk5, win->unk10, py >> 3);
        DmaSet(DMA3, buf, map, 0x80000000 | win->unk14);
    }

sprites:
    if ((py >> 3) - win->unk12 < win->unk16) {
        if (win->unk3 == 1)
            size = 4;
        else if (win->unk3 == 2)
            size = 5;
        else
            size = 16;
        for (i = 0; i < win->unk14; i++) {
            if (i == 0)
                frame = 8;
            else if (i == win->unk14 - 1)
                frame = 11;
            else
                frame = 10;
            fn_02003C3C(x, py, size, frame, win->unk4, win->unk5, 0);
            x += 8;
        }
    }
}
