#define USE_BUILTIN_STRING
#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "session.h"
#include "radar.h"
#include "screen.h"

extern vu16 gBgScroll[4][2];

static u32 sKeyRepeatTimer;
static u32 sWaitKeyRelease;
static u32 sPrevMenuHasInput;
static s8 sShakeTimer;
static s8 sShakeX;
static s8 sShakeY;
static s8 sScrollDirty;
static s8 sAlarmTimer;
u8 gIntrMainRam[0x100];

typedef void (*IntrFunc)(void);

const IntrFunc IntrTable[] = {
    Link_JoyIntr,
    VBlankIntr,
    IntrDummy,
    SoundIntr,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
};

const s16 gSinTable[] = {
    0, 49, 97, 142, 181, 212, 236, 251,
    256, 251, 236, 212, 181, 142, 97, 49,
    0, -49, -97, -142, -181, -212, -236, -251,
    -256, -251, -236, -212, -181, -142, -97, -49,
    0, 49, 97, 142, 181, 212, 236, 251,
};

const u8 sShakeAmpTable[] = { 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1 };
const s8 sShakeOffsetTable[] = { 0, 0, 4, -4, 2, 3, -1, -4, 3, -2, 1, 2, -3, -1, 0, 0 };
const char sMapLoadText[] = "MAP LOAD ";
const char sPercentText[] = "%";
extern const u16 gBackdropPalettes[];
extern const u16 *gBackdropTiles[];
extern const u16 *gBackdropMaps[];

void AgbMain(void)
{
    s32 prevMode;
    s32 i;
    s32 value;

    REG_WAITCNT = 0x4014;
    /* Keep the live stack intact while clearing IWRAM. */
    __asm__ volatile ("mov %0, sp" : "=r" (value));
    DmaClear32(0, 0, 0x03000000, value);
    value = 0x1A0;
    DmaClear32(3, 0, 0x03007E00, value);
    DmaClear16(0, 0, 0x05000000, 0x400);
    DmaClear16(0, 0, 0x06000000, 0x18000);
    DmaClear32(0, 32, 0x07000000, 0x400);
    gFrameCount = 0;
    gMenuHasInput = 0;
    gLinkStarted = 0;
    gInputLockFrames = 0;
    gSpMode = 0;
    DmaClear16(0, 0x3FF, 0x0600E000, 0x1000);
    DmaClear16(0, 0x2FF, 0x0600F000, 0x1000);
    DmaCopy32(3, intr_main, gIntrMainRam, sizeof(gIntrMainRam));
    INTR_VECTOR = gIntrMainRam;
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
    Bg_SetScroll(15, 0, 0);
    Session_Init();
    Obj_Init();
    Text_Init();
    Input_Init();
    Bg_LoadBackdrop(0);
    Header_Clear();
    Header_Init();
    Text_SetFill(1, 0);
    Text_Clear();
    Mode_Init();
    gWasConnected = 0;
    Link_Init();
    m4aSoundInit();
    Map_SetStage(23, 0);
    Header_Clear();
    Shake_Reset();
    gSavedScreen = gScreen;
    sPrevMenuHasInput = gMenuHasInput;
    Alarm_Reset();
    prevMode = gSpMode;
    gReconnectPending = 0;
    for (;;) {
        Link_ProcessRecv();
        if (sPrevMenuHasInput != gMenuHasInput && sPrevMenuHasInput == 1) {
            sWaitKeyRelease = 1;
        }
        Input_Update();
        if (prevMode != gSpMode) {
            SpMode_Apply();
        }
        prevMode = gSpMode;
        Shake_Update();
        Alarm_Update();
        if (gDataFlags & DATA_OBJ) {
            if (gMenuHasInput == 0) {
                value = 34;
            } else {
                value = 35;
            }
            Obj_Draw(216, 144, 0, value, Obj_GetPalette(0, value), 0, 0);
        }
        value = Link_IsConnected();
        if (value && gLinkStarted && gMode != MODE_FIELD && gMode != MODE_CONTROLLER && gMenuHasInput != 1) {
            gMenuHasInput = 1;
        }
        if (gWasConnected != value) {
            if (value) {
                gReconnectPending = 1;
            } else {
                gSession.outsideMiasma = 0;
                for (i = 0; i < 4; i++) {
                    gParty[i].hp = 1;
                }
                gReconnectPending = 0;
                m4aMPlayAllStop();
                Bg_SetBlend(0);
                REG_DISPCNT = 0x9F40;
                gScreen = 0;
                Bg_ClearMaps();
                Screen_Reset();
                gMode = MODE_FIELD;
                gSavedScreen = 0;
                gMsgScreenId = 4;
                gScreen = 13;
            }
            Bg_LoadBackdrop(gSession.appearance & 3);
            gWasConnected = value;
        }
        Mode_Update();
        Oam_Commit();
        VBlankIntrWait();
        Reply_Tick();
        sPrevMenuHasInput = gMenuHasInput;
        gFrameCount++;
    }
}

void IntrDummy(void)
{
}

void VBlankIntr(void)
{
    Oam_Transfer();
    Bg_ApplyScroll();
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

void SoundIntr(void)
{
    m4aSoundMain();
}

void Input_Init(void)
{
    sKeyRepeatTimer = 0;
    gKeysPrev = 0;
    gKeysHeld = 0;
    gKeysNew = 0;
    gKeysReleased = 0;
    gKeysCurrent = 0;
    gKeysToggled = 0;
}

void Input_Update(void)
{
    u16 keys;

    keys = REG_KEYINPUT ^ KEY_MASK;
    if (sWaitKeyRelease != 0) {
        if (keys != 0) {
            keys = 0;
        } else {
            sWaitKeyRelease = keys;
        }
    }
    if (!Link_IsConnected() || gInputLockFrames != 0) {
        keys = 0;
    }
    gKeysPrev = gKeysHeld;
    gKeysHeld = keys;
    gKeysNew = keys & ~gKeysPrev;
    gKeysCurrent = (keys & gKeysPrev) ^ gKeysNew;
    gKeysReleased = gKeysPrev & ~keys;
    gKeysToggled ^= gKeysNew;
    gKeysRepeat = gKeysNew;
    if (gKeysPrev != gKeysHeld || gKeysPrev == 0) {
        sKeyRepeatTimer = 0;
    } else {
        s32 t;

        sKeyRepeatTimer++;
        t = sKeyRepeatTimer - 20;
        if (sKeyRepeatTimer >= 20 && t % 5 == 0)
            gKeysRepeat |= keys & 0x3F0;
    }
    if (Link_IsConnected()) {
        Link_SendPad(keys);
        if (!gMenuHasInput || !gLinkStarted) {
            gKeysPrev = 0;
            gKeysHeld = 0;
            gKeysNew = 0;
            gKeysReleased = 0;
            gKeysCurrent = 0;
            gKeysToggled = 0;
            gKeysRepeat = 0;
        }
    }
}

void Header_Init(void)
{
    Header_Clear();
}

void Bg_LoadBackdrop(s32 no)
{
    u16 buf[40];
    const u16 *tiles;
    const u16 *pal;
    const u16 *map;
    s32 pal_no;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    u32 size;
    u32 dst;

    w = 8;
    h = 8;
    tiles = gBackdropTiles[no];
    pal_no = Link_GetPlayerNo();
    if (gSpMode) {
        pal_no += 4;
    }
    pal = &gBackdropPalettes[pal_no * 16];
    map = gBackdropMaps[no];
    DmaCopy16(3, tiles, 0x0600D7E0, 0x800);
    DmaCopy16(3, pal, 0x05000000, 32);
    size = 64;
    for (y = 0; y < h; y++) {
        for (x = 0; x < 32; x += w) {
            memcpy(&buf[x], &map[y * w], 16);
        }
        for (x = 0; x < 32; x++) {
            buf[x] += 0x2BF;
        }
        for (x = y; x < 32; x += h) {
            dst = 0x0600F800 + x * size;
            DmaCopy16(3, buf, dst, size);
        }
    }
}

void Bg_CopyBackdropToRadar(void)
{
    u16 buf[40];
    s32 i;
    s32 j;
    s32 size;
    s32 n;
    u32 ofs;
    u32 dst;

    DmaCopy16(0, 0x0600D7E0, 0x06007060, 0x800);
    size = 24;
    for (i = 0; i < 16; i++) {
        DmaCopy16(0, 0x0600F800 + i * 64 + 40, buf, size);
        n = size / sizeof(u16);
        for (j = 0; j < n; j++) {
            buf[j] += 0xC4;
        }
        dst = 0x0600E800 + (i * 32 + 20) * 2;
        DmaCopy16(0, buf, dst, size);
    }
    for (i = 16; i < 32; i++) {
        ofs = i * 64;
        DmaCopy16(0, 0x0600F800 + ofs, buf, 64);
        for (j = 0; j < 32; j++) {
            buf[j] += 0xC4;
        }
        dst = 0x0600E800 + ofs;
        DmaCopy16(0, buf, dst, 64);
    }
}

void Bg_ClearMaps(void)
{
    if (Link_IsConnected() || gScreen != 13) {
        DmaClear16(0, 0x3FF, 0x0600E000, 0x800);
        DmaClear16(0, 0x3FF, 0x0600E800, 0x800);
        DmaClear16(0, 0x2FF, 0x0600F000, 0x800);
    }
}

void Bg_LoadPlayerPalette(void)
{
    s32 pal = Link_GetPlayerNo();
    const u16 *src;

    if (gSpMode) {
        pal += 4;
    }
    src = &gBackdropPalettes[pal * 16];
    DmaCopy16(3, src, 0x05000000, 32);
}

u16 *Bg_GetMapPtr(s32 bg, s32 x, s32 y)
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

void Header_Clear(void)
{
    Text_ClearObj(0);
}

void Header_Print(const char *str)
{
    Text_SetFill(0, 0);
    Text_Clear();
    Text_Print(str, TEXT_DRAW);
    Text_CopyToObj(0, 15, 1);
}

void Header_DrawBar(void)
{
    s32 x;
    s32 i;

    x = 24;
    for (i = 0; i < 14; i++, x += 16) {
        Obj_Draw(x, 144, 21, i, 0, 0, 0);
    }
}

void Bg_SetScroll(u8 mask, u16 x, u16 y)
{
    vu16 *reg;
    s32 i;

    reg = (vu16 *)0x04000010;
    for (i = 0; i < 4; i++, reg += 2) {
        if ((mask >> i) & 1) {
            sScrollDirty = 1;
            gBgScroll[i][0] = x;
            gBgScroll[i][1] = y;
            if (sShakeTimer <= 0) {
                reg[0] = gBgScroll[i][0];
                reg[1] = gBgScroll[i][1];
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
        Shake_Reset();
    }
}

void Shake_Reset(void)
{
    sShakeTimer = 0;
    sShakeX = 0;
    sShakeY = 0;
    sScrollDirty = 0;
}

void Shake_Start(void)
{
    sShakeTimer = 13;
    m4aSongNumStart(4);
}

void Shake_Update(void)
{
    s32 idx;

    if (sShakeTimer > 0) {
        sScrollDirty = 1;
        idx = 13 - sShakeTimer;
        sShakeY = (sShakeTimer & 1) ? sShakeAmpTable[idx] : (s8)-sShakeAmpTable[idx];
        sShakeX = (&sShakeOffsetTable[2])[idx];
        if (gFrameCount & 1) {
            sShakeTimer--;
        }
    }
}

void Shake_GetOffset(s8 *x, s8 *y)
{
    if (sShakeTimer >= 0) {
        *x = -sShakeX;
        *y = -sShakeY;
    } else {
        *x = 0;
        *y = 0;
    }
}

void Bg_ApplyScroll(void)
{
    vu16 *reg;
    s32 i;

    if (sScrollDirty) {
        reg = (vu16 *)0x04000010;
        for (i = 0; i < 4; i++, reg += 2) {
            if (sShakeTimer > 0) {
                reg[0] = gBgScroll[i][0] + sShakeX;
                reg[1] = gBgScroll[i][1] + sShakeY;
            } else {
                reg[0] = gBgScroll[i][0];
                reg[1] = gBgScroll[i][1];
            }
        }
        sScrollDirty = 0;
        if (sShakeTimer <= 0) {
            sShakeX = 0;
            sShakeY = 0;
        }
    }
}

void Text_PrintNumber(s32 value, s32 color, s32 digits)
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
    Text_SetX(color);
    buf[0] = buf[1] = 0;
    for (i = 0; i < digits; i++) {
        if (rem > max) {
            d = 9;
        } else {
            d = rem / div;
        }
        if (d != 0 || value > rem || i + 1 >= digits) {
            buf[0] = d + '0';
            Text_Print(buf, TEXT_DRAW_FIX);
        } else {
            Text_AddX(9);
        }
        rem %= div;
        div /= 10;
    }
}

void IntToStr(char *buf, s32 value)
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
    struct BulkXfer *xfer;
    u32 percent;

    xfer = Xfer_GetWork();
    if (show && gXferActive) {
        memset(buf, 0, sizeof(buf));
        if (xfer->type == 1) {
            memcpy(buf, sMapLoadText, sizeof(sMapLoadText));
            percent = (xfer->cur - (u8 *)0x02038000) * 100 / xfer->total;
            if (percent > 99) {
                Header_Clear();
            } else {
                IntToStr(buf + strlen(buf), percent);
                strcat(buf, sPercentText);
                Header_Print(buf);
            }
        }
    }
}

s16 FixMul(s16 a, s16 b)
{
    return (a * b) >> 8;
}

s16 FixDiv(s16 a, s16 b)
{
    return (a << 8) / b;
}

s16 FixInverse(s16 a)
{
    s32 one = 0x10000;

    return one / a;
}

void Str_GetChar(const char *str, s32 n, char *out)
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

s32 Str_IsWideChar(const char *str, s32 n)
{
    if (strlen(str) == 0) {
        return -1;
    }
    return 0;
}

s32 Str_Length(const char *str)
{
    s32 len = strlen(str);

    if (len == 0) {
        return 0;
    }
    return len;
}

void Alarm_Update(void)
{
    if (Link_IsConnected() && gMode == MODE_FIELD && gSession.outsideMiasma != 0) {
        if (sAlarmTimer == 0) {
            m4aSongNumStart(5);
        }
        if (++sAlarmTimer >= 30) {
            sAlarmTimer = 0;
        }
    }
}

void Alarm_Reset(void)
{
    sAlarmTimer = 0;
}

void SpMode_Apply(void)
{
    Bg_LoadPlayerPalette();
    REG_DISPCNT = 0x840;
    Obj_ReloadPalettes();
    Smith_ResetList();
    gScreen = 0;
    gShopMenuPos[0] = 0;
    gShopMenuPos[1] = 0xFF;
    Screen_Reset();
    Bg_ClearMaps();
    Bg_SetBlend(0);
    Header_Clear();
    REG_DISPCNT = 0x9F40;
}
