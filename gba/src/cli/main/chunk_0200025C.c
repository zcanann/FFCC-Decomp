#include "gba_types.h"

#define REG_DISPCNT (*(vu16 *)0x04000000)
#define REG_DISPSTAT (*(vu16 *)0x04000004)
#define REG_BG0CNT (*(vu16 *)0x04000008)
#define REG_BG1CNT (*(vu16 *)0x0400000A)
#define REG_BG2CNT (*(vu16 *)0x0400000C)
#define REG_BG3CNT (*(vu16 *)0x0400000E)
#define REG_WINOUT (*(vu16 *)0x0400004A)
#define REG_BLDCNT (*(vu16 *)0x04000050)
#define REG_BLDALPHA (*(vu16 *)0x04000052)
#define REG_KEYINPUT (*(vu16 *)0x04000130)
#define REG_IE (*(vu16 *)0x04000200)
#define REG_WAITCNT (*(vu16 *)0x04000204)
#define REG_IME (*(vu16 *)0x04000208)
#define INTR_CHECK (*(vu16 *)0x03007FF8)
#define INTR_VECTOR (*(void **)0x03007FFC)

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
#define DmaCopy32(dmaAddr, src, dst, size) DmaSet(dmaAddr, src, dst, 0x84000000 | ((size) / 4))

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

struct Transfer {
    s8 type;
    s8 state;
    u16 crc;
    u8 *base;
    u8 *cur;
    u16 count;
    u16 index;
    u16 total;
    u16 blockSize;
    u8 step;
    u8 blocks;
};

struct Packet {
    u8 hdr;
    u8 cmd;
    u16 val;
};

struct MapId {
    s8 area;
    s8 map;
};

struct Unk03002CA0 {
    u8 unk0;
    u8 unk1[0x128 - 0x1];
    s8 unk128;
};

struct Unk03002FD0 {
    u8 unk0[7];
    u8 unk7;
};

extern u32 lbl_03000000;
extern u32 lbl_03000004;
extern u32 lbl_03000008;
extern s8 lbl_0300000C;
extern s8 lbl_0300000D;
extern s8 lbl_0300000E;
extern s8 lbl_0300000F;
extern s8 lbl_03000010;
extern struct Transfer sBulkXfer;
extern u16 gXferCrc[16];
extern struct MapId gStageNo;
extern u16 lbl_03002990;
extern u8 gReconnectPending;
extern u8 gInputLockFrames;
extern u16 lbl_0300299C;
extern u8 gWasConnected;
extern u8 gLinkStarted;
extern u16 lbl_030029A8;
extern u16 lbl_030029AC;
extern u16 lbl_030029B0;
extern u16 lbl_030029B4;
extern u8 lbl_030029C0[];
extern u16 lbl_03002AC0;
extern u8 gSpMode;
extern u32 lbl_03002AC8;
extern u8 gMenuHasInput;
extern vu16 lbl_03002AD0[4][2];
extern u8 gNewLetter;
extern u8 gReplyTimer;
extern s8 gXferActive;
extern u16 gDataFlags;
extern u8 gXferErrorCount;
extern u8 gReplyWaiting;
extern u8 gStageInTable;
extern u8 gReplyResult;
extern u8 gMapObjs[];
extern struct Unk03002CA0 gSession;
extern struct Unk03002FD0 gParty[4];
extern u32 gScreen;
extern u32 gMode;
extern u32 gSavedScreen;
extern u8 gMsgScreenId;
extern u8 lbl_030032FC[];
extern const char lbl_0201CCE8[10] __attribute__((aligned(4)));
extern const u8 lbl_0201CCCC[];
extern const s8 lbl_0201CCD8[];
extern const char lbl_0201CCF4[];
extern const s8 lbl_0201CCF8[12][2];
extern const u16 lbl_0202A1BC[];
extern const u16 *const lbl_02034678[];
extern const u16 *const lbl_02034688[];
extern u8 lbl_02037FFF[];
extern u8 gDownloadBuf[];
extern u8 lbl_0203FFFF[];
extern u8 gListBuf[];
extern u8 gDetailBuf[];

void intr_main(void);
void VBlankIntrWait(void);
void m4aSoundInit(void);
void m4aSoundMain(void);
void m4aSoundVSync(void);
void m4aSongNumStart(u16);
void m4aMPlayAllStop(void);
void *memcpy(void *, const void *, unsigned long);
void *memset(void *, int, unsigned long);
char *strcat(char *, const char *);
s32 strlen(const char *);
char *strcpy(char *, const char *);
u8 Link_IsConnected(void);
void Link_SendPad(u16);
void Link_Init(void);
void Link_ProcessRecv(void);
void Link_CheckTimeout(void);
u16 Crc16(u16, u8 *, u16 *);
s32 Link_GetPlayerNo(void);
void fn_02003338(void);
void fn_02003394(s32, s32);
void fn_020033F4(void);
void fn_02003464(const char *, s32);
void fn_020038F4(s32);
void fn_02003900(s32);
void fn_0200391C(s32, s32, s32);
void fn_02003A00(s32);
void fn_02003AA0(void);
void fn_02003C3C(s32, s32, s32, s32, s32, s32, s32);
void fn_02003FA0(void);
s32 fn_02004030(s32, s32);
void fn_02004384(void);
void fn_020043B8(void);
void Session_Init(void);
void Radar_ClearMarkers(void);
void Mode_Init(void);
void Mode_Update(void);
void Screen_Reset(void);
void fn_0200194C(s32);
void Reply_Tick(void);
struct Transfer *Xfer_GetWork(void);
void Xfer_OnError(void);
void Scouter_SetDirty(s32);
void fn_02019C4C(void);

void fn_020007D8(s32);
void fn_02000A74(void);
void fn_020007CC(void);
void fn_02000654(void);
void fn_02000690(void);
void fn_02000990(void);
void fn_02000AD4(u8, u16, u16);
void fn_02000B74(void);
void fn_02000C64(void);
void fn_02000BB0(void);
void fn_02000F70(void);
void fn_02000FC8(void);
void fn_02000FD4(void);
void Map_SetStage(u8, u8);

void AgbMain(void)
{
    u8 prevMode;
    u8 connected;
    s32 i;
    s32 icon;

    REG_WAITCNT = 0x4014;
    DmaClear32(DMA0, 0, 0x03000000, (s32)__builtin_frame_address(0));
    DmaClear32(DMA3, 0, 0x03007E00, 0x1A0);
    DmaClear16(DMA0, 0, 0x05000000, 0x400);
    DmaClear16(DMA0, 0, 0x06000000, 0x18000);
    DmaClear32(DMA0, 32, 0x07000000, 0x400);
    lbl_03002AC8 = 0;
    gMenuHasInput = 0;
    gLinkStarted = 0;
    gInputLockFrames = 0;
    gSpMode = 0;
    DmaClear16(DMA0, 0x3FF, 0x0600E000, 0x1000);
    DmaClear16(DMA0, 0x2FF, 0x0600F000, 0x1000);
    DmaCopy32(DMA3, intr_main, lbl_030029C0, 0x100);
    INTR_VECTOR = lbl_030029C0;
    REG_IE = 0x2005;
    REG_DISPSTAT = 0x28;
    REG_IME = 1;
    REG_BLDCNT = 0x1F06;
    REG_BLDALPHA = 0x808;
    REG_DISPCNT = 0x9F40;
    REG_WINOUT = 0x3D3F;
    REG_BG0CNT = 0x1C00;
    REG_BG1CNT = 0x1D01;
    REG_BG2CNT = 0x1E0A;
    REG_BG3CNT = 0x1F0B;
    fn_02000AD4(15, 0, 0);
    Session_Init();
    fn_02003AA0();
    fn_02003338();
    fn_02000654();
    fn_020007D8(0);
    fn_02000A74();
    fn_020007CC();
    fn_02003394(1, 0);
    fn_020033F4();
    Mode_Init();
    gWasConnected = 0;
    Link_Init();
    m4aSoundInit();
    Map_SetStage(23, 0);
    fn_02000A74();
    fn_02000B74();
    gSavedScreen = gScreen;
    lbl_03000008 = gMenuHasInput;
    fn_02000FC8();
    prevMode = gSpMode;
    gReconnectPending = 0;
    for (;;) {
        Link_ProcessRecv();
        if (lbl_03000008 != gMenuHasInput && lbl_03000008 == 1) {
            lbl_03000004 = 1;
        }
        fn_02000690();
        if (prevMode != gSpMode) {
            fn_02000FD4();
        }
        prevMode = gSpMode;
        fn_02000BB0();
        fn_02000F70();
        if (gDataFlags & 1) {
            icon = 35;
            if (gMenuHasInput == 0) {
                icon = 34;
            }
            fn_02003C3C(216, 144, 0, icon, fn_02004030(0, icon), 0, 0);
        }
        connected = Link_IsConnected();
        if (connected && gLinkStarted && gMode != 0 && gMode != 4 && gMenuHasInput != 1) {
            gMenuHasInput = 1;
        }
        if (gWasConnected != connected) {
            if (connected) {
                gReconnectPending = 1;
            } else {
                gSession.unk128 = 0;
                for (i = 0; i < 4; i++) {
                    gParty[i].unk7 = 1;
                }
                gReconnectPending = 0;
                m4aMPlayAllStop();
                fn_0200194C(0);
                REG_DISPCNT = 0x9F40;
                gScreen = 0;
                fn_02000990();
                Screen_Reset();
                gMode = 0;
                gSavedScreen = 0;
                gMsgScreenId = 4;
                gScreen = 13;
            }
            fn_020007D8(gSession.unk0 & 3);
            gWasConnected = connected;
        }
        Mode_Update();
        fn_02003FA0();
        VBlankIntrWait();
        Reply_Tick();
        lbl_03000008 = gMenuHasInput;
        lbl_03002AC8++;
    }
}

void fn_020005F8(void)
{
}

void fn_020005FC(void)
{
    fn_02004384();
    fn_02000C64();
    if (REG_IE & 0x80) {
        Link_CheckTimeout();
    }
    if (gInputLockFrames != 0) {
        if (gLinkStarted != 0) {
            gInputLockFrames--;
        } else {
            gInputLockFrames = 0;
        }
    }
    m4aSoundVSync();
    INTR_CHECK = 1;
}

void fn_02000648(void)
{
    m4aSoundMain();
}

void fn_02000654(void)
{
    lbl_03000000 = 0;
    lbl_030029B4 = 0;
    lbl_030029A8 = 0;
    lbl_030029AC = 0;
    lbl_03002990 = 0;
    lbl_03002AC0 = 0;
    lbl_030029B0 = 0;
}

void fn_02000690(void)
{
    u16 keys;
    u16 pressed;

    keys = REG_KEYINPUT ^ 0x3FF;
    if (lbl_03000004 != 0) {
        if (keys != 0) {
            keys = 0;
        } else {
            lbl_03000004 = keys;
        }
    }
    if (!Link_IsConnected() || gInputLockFrames != 0) {
        keys = 0;
    }
    lbl_030029B4 = lbl_030029A8;
    lbl_030029A8 = keys;
    pressed = keys & ~lbl_030029B4;
    lbl_030029AC = pressed;
    lbl_03002AC0 = (keys & lbl_030029B4) ^ pressed;
    lbl_03002990 = lbl_030029B4 & ~keys;
    lbl_030029B0 ^= pressed;
    lbl_0300299C = pressed;
    if (lbl_030029B4 != lbl_030029A8 || lbl_030029B4 == 0) {
        lbl_03000000 = 0;
    } else {
        s32 t;

        lbl_03000000++;
        t = lbl_03000000 - 20;
        if (lbl_03000000 >= 20 && t % 5 == 0)
            lbl_0300299C = pressed | (keys & 0x3F0);
    }
    if (Link_IsConnected()) {
        Link_SendPad(keys);
        if (!gMenuHasInput || !gLinkStarted) {
            lbl_030029B4 = 0;
            lbl_030029A8 = 0;
            lbl_030029AC = 0;
            lbl_03002990 = 0;
            lbl_03002AC0 = 0;
            lbl_030029B0 = 0;
            lbl_0300299C = 0;
        }
    }
}

void fn_020007CC(void)
{
    fn_02000A74();
}

void fn_020007D8(s32 no)
{
    u16 buf[40];
    const u16 *tiles;
    const u16 *pal;
    const u16 *map;
    s32 pal_no;
    s32 x;
    s32 y;
    s32 h;
    u32 size;

    tiles = lbl_02034678[no];
    pal_no = Link_GetPlayerNo();
    if (gSpMode) {
        pal_no += 4;
    }
    pal = &lbl_0202A1BC[pal_no * 16];
    map = lbl_02034688[no];
    DmaCopy16(DMA3, tiles, 0x0600D7E0, 0x800);
    DmaCopy16(DMA3, pal, 0x05000000, 32);
    size = 64;
    h = 8;
    for (y = 0; y < h; y++) {
        for (x = 0; x < 32; x += 8) {
            memcpy(&buf[x], &map[y * h], 16);
        }
        for (x = 0; x < 32; x++) {
            buf[x] += 0x2BF;
        }
        for (x = y; x < 32; x += 8) {
            DmaCopy16(DMA3, buf, 0x0600F800 + x * size, size);
        }
    }
}

void fn_020008D0(void)
{
    u16 buf[40];
    s32 i;
    s32 j;
    s32 w;
    u32 ofs;
    u32 dst;

    DmaCopy16(DMA0, 0x0600D7E0, 0x06007060, 0x800);
    w = 12;
    for (i = 0; i < 16; i++) {
        DmaCopy16(DMA0, 0x0600F800 + i * 64 + 40, buf, w * 2);
        for (j = 0; j < w; j++) {
            buf[j] += 0xC4;
        }
        dst = 0x0600E800 + (i * 32 + 20) * 2;
        DmaCopy16(DMA0, buf, dst, w * 2);
    }
    for (i = 16; i < 32; i++) {
        ofs = i * 64;
        DmaCopy16(DMA0, 0x0600F800 + ofs, buf, 64);
        for (j = 0; j < 32; j++) {
            buf[j] += 0xC4;
        }
        dst = 0x0600E800 + ofs;
        DmaCopy16(DMA0, buf, dst, 64);
    }
}

void fn_02000990(void)
{
    if (Link_IsConnected() || gScreen != 13) {
        DmaClear16(DMA0, 0x3FF, 0x0600E000, 0x800);
        DmaClear16(DMA0, 0x3FF, 0x0600E800, 0x800);
        DmaClear16(DMA0, 0x2FF, 0x0600F000, 0x800);
    }
}

void fn_02000A04(void)
{
    s32 pal = Link_GetPlayerNo();
    const u16 *src;

    if (gSpMode) {
        pal += 4;
    }
    src = &lbl_0202A1BC[pal * 16];
    DmaCopy16(DMA3, src, 0x05000000, 32);
}

u16 *fn_02000A40(s32 bg, s32 x, s32 y)
{
    u16 *map;

    if (bg == 0) {
        map = (u16 *)0x0600E000;
    } else if (bg == 1) {
        map = (u16 *)0x0600E800;
    } else if (bg == 2) {
        map = (u16 *)0x0600F000;
    } else {
        map = (u16 *)0x0600F800;
    }
    map = (u16 *)((u8 *)map + (y * 64 + x * 2));
    return map;
}

void fn_02000A74(void)
{
    fn_02003A00(0);
}

void fn_02000A80(const char *str)
{
    fn_02003394(0, 0);
    fn_020033F4();
    fn_02003464(str, 0);
    fn_0200391C(0, 15, 1);
}

void fn_02000AA8(void)
{
    s32 x;
    s32 i;

    x = 24;
    for (i = 0; i < 14; i++, x += 16) {
        fn_02003C3C(x, 144, 21, i, 0, 0, 0);
    }
}

void fn_02000AD4(u8 mask, u16 x, u16 y)
{
    vu16 *reg;
    s32 i;

    reg = (vu16 *)0x04000010;
    for (i = 0; i < 4; i++, reg += 2) {
        if ((mask >> i) & 1) {
            lbl_0300000F = 1;
            lbl_03002AD0[i][0] = x;
            lbl_03002AD0[i][1] = y;
            if (lbl_0300000C <= 0) {
                reg[0] = lbl_03002AD0[i][0];
                reg[1] = lbl_03002AD0[i][1];
            }
        }
    }
    if (x == 0 && y == 0) {
        reg = (vu16 *)0x04000010;
        for (i = 0; i < 4; i++, reg += 2) {
            if ((mask >> i) & 1) {
                *(vu32 *)reg = 0;
            }
        }
        fn_02000B74();
    }
}

void fn_02000B74(void)
{
    lbl_0300000C = 0;
    lbl_0300000D = 0;
    lbl_0300000E = 0;
    lbl_0300000F = 0;
}

void fn_02000B98(void)
{
    lbl_0300000C = 13;
    m4aSongNumStart(4);
}

void fn_02000BB0(void)
{
    s32 idx;

    if (lbl_0300000C > 0) {
        lbl_0300000F = 1;
        idx = 13 - lbl_0300000C;
        lbl_0300000E = (lbl_0300000C & 1) ? lbl_0201CCCC[idx] : (s8)-lbl_0201CCCC[idx];
        lbl_0300000D = (&lbl_0201CCD8[2])[idx];
        if (lbl_03002AC8 & 1) {
            lbl_0300000C--;
        }
    }
}

void fn_02000C2C(s8 *x, s8 *y)
{
    if (lbl_0300000C >= 0) {
        *x = -lbl_0300000D;
        *y = -lbl_0300000E;
    } else {
        *x = 0;
        *y = 0;
    }
}

void fn_02000C64(void)
{
    vu16 *reg;
    s32 i;

    if (lbl_0300000F) {
        reg = (vu16 *)0x04000010;
        for (i = 0; i < 4; i++, reg += 2) {
            if (lbl_0300000C > 0) {
                reg[0] = lbl_03002AD0[i][0] + lbl_0300000D;
                reg[1] = lbl_03002AD0[i][1] + lbl_0300000E;
            } else {
                reg[0] = lbl_03002AD0[i][0];
                reg[1] = lbl_03002AD0[i][1];
            }
        }
        lbl_0300000F = 0;
        if (lbl_0300000C <= 0) {
            lbl_0300000D = 0;
            lbl_0300000E = 0;
        }
    }
}

void fn_02000CF0(s32 value, s32 color, s32 digits)
{
    s32 max;
    s32 rem;
    s32 div;
    s32 i;
    s32 d;
    char buf[2];

    max = 1;
    for (i = 0; i < digits; i++) {
        max *= 10;
    }
    rem = value;
    div = max / 10;
    fn_020038F4(color);
    buf[0] = buf[1] = 0;
    for (i = 0; i < digits; i++) {
        if (rem > max) {
            d = 9;
        } else {
            d = rem / div;
        }
        if (d != 0 || value > rem || i + 1 >= digits) {
            buf[0] = d + '0';
            fn_02003464(buf, 1);
        } else {
            fn_02003900(9);
        }
        rem %= div;
        div /= 10;
    }
}

void fn_02000D9C(char *buf, s32 value)
{
    s32 div;
    s32 i;
    s32 d;
    u8 started;

    if (value == 0) {
        buf[0] = '0';
        buf[1] = 0;
        return;
    }
    div = 1;
    for (i = 0; i < 8; i++) {
        div *= 10;
    }
    if (value >= div) {
        for (i = 0; i < 8; i++) {
            buf[i] = '9';
        }
        buf[8] = 0;
        return;
    }
    div /= 10;
    started = 0;
    i = 0;
    for (; div > 0; div /= 10) {
        d = value / div;
        if (d != 0 || started) {
            started = 1;
            buf[i] = d + '0';
            value %= div;
            i++;
        }
    }
    buf[i] = 0;
}

void Xfer_DrawProgress(s32 show)
{
    char buf[64];
    struct Transfer *xfer;
    u32 percent;

    xfer = Xfer_GetWork();
    if (show && gXferActive) {
        memset(buf, 0, sizeof(buf));
        if (xfer->type == 1) {
            memcpy(buf, lbl_0201CCE8, sizeof(lbl_0201CCE8));
            percent = (xfer->cur - (u8 *)0x02038000) * 100 / xfer->total;
            if (percent > 99) {
                fn_02000A74();
            } else {
                fn_02000D9C(buf + strlen(buf), percent);
                strcat(buf, lbl_0201CCF4);
                fn_02000A80(buf);
            }
        }
    }
}

s16 fn_02000EC0(s16 a, s16 b)
{
    return (a * b) >> 8;
}

s16 fn_02000ED0(s16 a, s16 b)
{
    return (a << 8) / b;
}

s16 fn_02000EE8(s16 a)
{
    s32 one = 0x10000;

    return one / a;
}

void fn_02000F00(const char *str, s32 n, char *out)
{
    s32 len;
    s32 i;
    s32 cnt;

    out[0] = 0;
    len = strlen(str);
    if (len) {
        cnt = 0;
        for (i = 0; i < len; i++) {
            if (cnt == n) {
                out[0] = str[i];
                out[1] = 0;
                break;
            }
            cnt++;
        }
    }
}

s32 fn_02000F48(const char *str)
{
    if (strlen(str) == 0) {
        return -1;
    }
    return 0;
}

s32 fn_02000F60(const char *str)
{
    s32 len = strlen(str);

    if (len == 0) {
        return 0;
    }
    return len;
}

void fn_02000F70(void)
{
    if (Link_IsConnected() && gMode == 0 && gSession.unk128 != 0) {
        if (lbl_03000010 == 0) {
            m4aSongNumStart(5);
        }
        if (++lbl_03000010 >= 30) {
            lbl_03000010 = 0;
        }
    }
}

void fn_02000FC8(void)
{
    lbl_03000010 = 0;
}

void fn_02000FD4(void)
{
    fn_02000A04();
    REG_DISPCNT = 0x840;
    fn_020043B8();
    fn_02019C4C();
    gScreen = 0;
    lbl_030032FC[0] = 0;
    lbl_030032FC[1] = 0xFF;
    Screen_Reset();
    fn_02000990();
    fn_0200194C(0);
    fn_02000A74();
    REG_DISPCNT = 0x9F40;
}

void Xfer_Init(void)
{
    s32 i;

    gDataFlags = 0;
    gXferActive = 0;
    for (i = 0; i < 16; i++) {
        gXferCrc[i] = 0;
    }
    memset(&sBulkXfer, 0, sizeof(sBulkXfer));
    gStageNo.area = 0;
    gStageNo.map = 0;
    gStageInTable = 1;
    gNewLetter = 0;
    gXferErrorCount = 0;
}

s32 Xfer_CheckCrc(u32 packet)
{
    struct Packet *pkt = (struct Packet *)&packet;
    s32 result;

    if ((gDataFlags >> pkt->cmd) & 1) {
        result = (gXferCrc[pkt->cmd] == pkt->val) ? 0 : -1;
        if (result) {
            gDataFlags &= ~(1 << pkt->cmd);
        }
    } else {
        result = -1;
    }
    return result;
}

void Xfer_Begin(void)
{
    gXferActive = 1;
    memset(&sBulkXfer, 0, sizeof(sBulkXfer));
    sBulkXfer.base = gDownloadBuf;
    sBulkXfer.cur = gDownloadBuf;
}

s32 Xfer_Receive(u32 packet, u8 *out)
{
    struct Packet *pkt = (struct Packet *)&packet;
    s32 kind;
    u8 *cur;
    u16 crc;

    kind = pkt->hdr >> 6;
    if (kind > 2) {
        *out = gXferActive ? sBulkXfer.type : 0xFF;
        gXferActive = 0;
        Xfer_OnError();
        return -1;
    }
    if (gXferActive == 0) {
        if (kind != 0) {
            *out = 0xFF;
            gXferActive = 0;
            Xfer_OnError();
            return -1;
        }
        Xfer_Begin();
    }
    *out = sBulkXfer.type;
    if (sBulkXfer.state == 0 && kind != 0) {
        gXferActive = 0;
        Xfer_OnError();
        return -1;
    }
    cur = sBulkXfer.cur;
    if ((u32)(cur - (u8 *)0x02038000) > 0x7FFF
        || (s32)sBulkXfer.base <= 0x02037FFF || (s32)sBulkXfer.base > 0x0203FFFF) {
        Xfer_Begin();
        gXferActive = 0;
        Xfer_OnError();
        return -1;
    }
    sBulkXfer.state = kind;
    if (kind == 0) {
        if (sBulkXfer.step == 0) {
            sBulkXfer.type = pkt->cmd;
            if (sBulkXfer.type == 3 || sBulkXfer.type == 6 || sBulkXfer.type == 7
                || sBulkXfer.type == 8 || sBulkXfer.type == 9) {
                sBulkXfer.cur = sBulkXfer.base = gListBuf;
            } else if (sBulkXfer.type == 2) {
                sBulkXfer.cur = sBulkXfer.base = gDetailBuf;
            }
            if (sBulkXfer.type == 6) {
                gDataFlags &= ~0x20;
            } else if (sBulkXfer.type == 7) {
                gDataFlags &= ~0x40;
            } else if (sBulkXfer.type == 8) {
                gDataFlags &= ~0x80;
            } else if (sBulkXfer.type == 9) {
                gDataFlags &= ~0x100;
            } else {
                gDataFlags &= ~(1 << sBulkXfer.type);
            }
            sBulkXfer.count = pkt->val;
            sBulkXfer.step++;
        } else if (sBulkXfer.step == 1) {
            sBulkXfer.total = pkt->val;
            sBulkXfer.step++;
        } else if (sBulkXfer.step == 2) {
            gXferCrc[sBulkXfer.type] = pkt->val;
            sBulkXfer.step = 0;
            sBulkXfer.state = 1;
        } else {
            gXferActive = 0;
            Xfer_OnError();
            return -1;
        }
    } else if (kind == 1) {
        if (sBulkXfer.step == 0) {
            sBulkXfer.blocks = pkt->cmd;
            sBulkXfer.blockSize = pkt->val;
            sBulkXfer.step++;
        } else if (sBulkXfer.step == 1) {
            sBulkXfer.index = pkt->cmd;
            sBulkXfer.crc = pkt->val;
            sBulkXfer.step = 0;
            sBulkXfer.state = 2;
        }
    } else {
        *sBulkXfer.cur++ = pkt->cmd;
        *sBulkXfer.cur++ = ((u8 *)&pkt->val)[0];
        *sBulkXfer.cur++ = ((u8 *)&pkt->val)[1];
        if (++sBulkXfer.step >= sBulkXfer.blocks) {
            crc = 0xFFFF;
            if (Crc16(sBulkXfer.blockSize, sBulkXfer.base, &crc) != sBulkXfer.crc) {
                gXferActive = 0;
                Xfer_OnError();
                return -1;
            }
            sBulkXfer.base += sBulkXfer.blockSize;
            sBulkXfer.cur = sBulkXfer.base;
            sBulkXfer.step = 0;
            sBulkXfer.state = 1;
            if (sBulkXfer.index + 1 >= sBulkXfer.count) {
                gXferActive = 0;
                fn_02000A74();
                if (sBulkXfer.type == 6) {
                    gDataFlags |= 0x20;
                } else if (sBulkXfer.type == 7) {
                    gDataFlags |= 0x40;
                } else if (sBulkXfer.type == 8) {
                    gDataFlags |= 0x80;
                } else if (sBulkXfer.type == 9) {
                    gDataFlags |= 0x100;
                } else {
                    gDataFlags |= 1 << sBulkXfer.type;
                }
                if (sBulkXfer.type == 0) {
                    fn_02003AA0();
                } else if (sBulkXfer.type == 1) {
                    if (gScreen == 0) {
                        Screen_Reset();
                    }
                } else if (sBulkXfer.type == 3) {
                    gNewLetter = 0;
                }
            }
            gXferErrorCount = 0;
            return 1;
        }
    }
    return 0;
}

void Map_SetStage(u8 area, u8 map)
{
    s8 table[12][2];
    s32 i;

    memcpy(table, lbl_0201CCF8, sizeof(table));
    gDataFlags &= ~0x400;
    Scouter_SetDirty(0);
    fn_02000A74();
    if (gStageNo.area != (s8)area && gScreen != 0) {
        if (gWasConnected) {
            gScreen = 0;
        } else {
            gSavedScreen = 0;
        }
    }
    fn_0200194C(0);
    REG_DISPCNT = 0x9F40;
    fn_02000990();
    Screen_Reset();
    Radar_ClearMarkers();
    memset(gMapObjs, 0, 0x188);
    if (gStageNo.area != (s8)area || gStageNo.map != (s8)map) {
        gStageNo.area = area;
        gStageNo.map = map;
        gDataFlags &= ~2;
        gXferCrc[1] = 0;
        gStageInTable = 0;
        for (i = 0; table[i][0] >= 0; i++) {
            if ((s8)area == table[i][0] && (s8)map == table[i][1]) {
                gStageInTable = 1;
                break;
            }
        }
    }
}

void Map_GetStage(s8 *area, s8 *map)
{
    *area = gStageNo.area;
    *map = gStageNo.map;
}

void Reply_Clear(void)
{
    gDataFlags &= 0x7FFF;
    gReplyResult = 0;
    gReplyTimer = 0;
    gReplyWaiting = 0;
}
