#include "global.h"
#include "main.h"
#include "joybus.h"
#include "text.h"

/* JOY Bus commands from the GameCube */
#define JOY_CMD_RESET  0x80
#define JOY_CMD_INFO   0x30
#define JOY_CMD_IDLE   0x50
#define JOY_CMD_SEND   0x10
#define JOY_CMD_PADS   0x70
#define JOY_CMD_PADS_0 0x40

#define JOY_INFO_SIZE 0x60

/* Pad words from the GameCube carry a command instead of keys when any of
   the top four bits is set; the fifth word of a packet is a status word */
#define LINK_CMD_REMOVE_PLAYER 0x2001
#define LINK_CMD_START         30

const char gJoyAgbId[] = "AMGR";
const char gJoyGcId[] = "GMGR";
const char gJoyBusFileName[] = "C:/FFF/miniGame/mgr/MgJoyBus/MgJoyBus.cpp";

struct JoyWork gJoyWork;
vu16 gPadHeld[4];
vu16 gPadNew[4];
vu8 gLinkMode;
u8 gLinkSynced;
u8 gLinkWaitStart;
u8 gLinkStarted;
u8 gLinkFrameReady;
vu8 gPlayerNo;
vu8 gPlayerCount;
vu8 gPlayerMask;
u8 gLinkFirstFrame;
vu8 gJoyRecvFrames;
u8 gJoyLastRecv;
u32 gLinkUnused;
u16 gLinkWaitCount;
u16 gUnused_03005D72;
u16 gLinkFrameCmd;
u16 gLinkSendCmd;
struct JoyRecvQueue gJoyRecvQueue;
u16 gLinkFrameCount;
vu8 gLinkWarmup;
u8 gJoySendPending;
vu8 gJoyIntrCount;

void ReadKeys(void)
{
    u16 keys = REG_KEYINPUT ^ KEY_MASK;

    gNewKeys = keys & ~gHeldKeys;
    gHeldKeys = keys;
}

u32 Crc8(u32 data)
{
    u32 crc = 0;
    u32 i;
    u32 bit;

    for (i = 2; i != 0; i--) {
        for (bit = 0x80; bit != 0; bit >>= 1) {
            crc <<= 1;
            if (data & bit) {
                if (crc & 0x100)
                    crc ^= 0xCC;
                else
                    crc++;
            } else if (crc & 0x100) {
                crc ^= 0xCD;
            }
        }
        data >>= 8;
    }
    for (i = 0; i < 8; i++) {
        crc <<= 1;
        if (crc & 0x100)
            crc ^= 0xCD;
    }
    return crc & 0xFF;
}

s32 Link_Recv(u32 data)
{
    s32 i;

    gJoyLastRecv = data;
    if ((data & 0xFF) == JOY_CMD_RESET) {
        JoyBus_HardReset();
        return 0;
    }
    if (gJoyWork.connected == 0) {
        if (gJoyWork.handshake == 2) {
            if (data != gJoyWork.expectedGcId)
                return 0;
            REG_JOYSTAT = 0x30;
            gJoyWork.gcId = data;
            gJoyWork.handshake = 3;
        } else if (gJoyWork.handshake == 3) {
            if (data != JOY_INFO_SIZE)
                return 0;
            REG_JOY_TRANS = *(u32 *)&gJoyWork.send.raw[0];
            gJoyWork.handshake = 4;
            gJoyWork.offset = 4;
        } else if (gJoyWork.handshake == 5) {
            REG_JOY_TRANS = data;
            gJoyWork.send.ctx.tick = data;
            gJoyWork.handshake = 6;
        } else {
            return 0;
        }
    } else {
        switch (gJoyWork.cmd) {
        case 0:
            gJoyWork.offset = 0;
            if (data == JOY_CMD_INFO) {
                gJoyWork.cmd = JOY_CMD_INFO;
            } else if (data == JOY_CMD_IDLE) {
                return 0;
            } else {
                if (*(start_vector + 4) == 0 && gJoyWork.send.ctx.initialized == 0)
                    return 0;
                if ((data & 0xFF) == JOY_CMD_SEND) {
                    REG_JOY_TRANS = gJoySendData;
                    REG_JOYSTAT = 0x30;
                    gJoyWork.cmd = JOY_CMD_SEND;
                } else if ((data & 0xFF) == JOY_CMD_PADS) {
                    gJoyRecvFrames++;
                    gJoyWork.cmd = JOY_CMD_PADS_0;
                }
            }
            break;
        case JOY_CMD_INFO:
            if (gJoyWork.offset >= JOY_INFO_SIZE)
                return 0;
            *(u32 *)&gJoyWork.recv.raw[gJoyWork.offset] = data;
            gJoyWork.offset += 4;
            if (gJoyWork.offset == JOY_INFO_SIZE) {
                gJoyWork.recv.ctx.cartFixed = gJoyWork.send.ctx.cartFixed;
                gJoyWork.recv.ctx.cartGameCode = gJoyWork.send.ctx.cartGameCode;
                REG_JOY_TRANS = *(u32 *)&gJoyWork.recv.raw[0];
                gJoyWork.offset += 4;
            }
            break;
        case JOY_CMD_PADS_0:
            i = (data & 0xFF) - JOY_CMD_PADS_0;
            if (i <= 4) {
                gJoyRecvQueue.rows[gJoyRecvQueue.write].data[i] = data;
                gJoyRecvQueue.rows[gJoyRecvQueue.write].valid[i] = 1;
                gJoyRecvQueue.mask |= 1 << i;
            }
            gJoyWork.offset++;
            if (gJoyRecvQueue.mask == 0x1F) {
                gJoyRecvQueue.mask = 0;
                REG_JOYSTAT = 0x20;
                gJoyWork.cmd = 0;
                gJoyRecvQueue.write++;
                if (gJoyRecvQueue.write > 3)
                    gJoyRecvQueue.write = 0;
                gJoySendPending = 0;
            }
            break;
        default:
            return 0;
        }
    }
    return 1;
}

s32 Link_Send(void)
{
    u32 i;
    s32 j;

    if (gJoyWork.connected == 0) {
        if (gJoyWork.handshake == 1) {
            gJoyWork.handshake = 2;
        } else if (gJoyWork.handshake == 4) {
            if (gJoyWork.offset != JOY_INFO_SIZE)
                goto send;
            if (gJoyWork.send.ctx.initialized != 0) {
                gJoyWork.handshake = 5;
            } else {
                gJoyWork.connected = 1;
                gJoyWork.cmd = 0;
                gJoyWork.handshake = 0;
            }
        } else if (gJoyWork.handshake == 6) {
            gJoyWork.connected = 1;
            gJoyWork.cmd = 0;
            gJoyWork.handshake = 0;
        } else {
            return 0;
        }
    } else {
        switch (gJoyWork.cmd) {
        case JOY_CMD_SEND:
            gJoyWork.cmd = JOY_CMD_PADS_0;
            break;
        case JOY_CMD_INFO:
            if (gJoyWork.offset < JOY_INFO_SIZE)
                return 0;
            if (gJoyWork.offset != JOY_INFO_SIZE * 2)
                goto send;
            for (i = 0; i < JOY_INFO_SIZE; i += 4)
                *(u32 *)&gJoyWork.send.raw[i] = *(u32 *)&gJoyWork.recv.raw[i];
            gJoyWork.cmd = 0;
            gPlayerNo = gJoyWork.recv.ctx.playerNo;
            gPlayerMask = gJoyWork.recv.ctx.playerMask;
            gLinkWarmup = 0;
            gPlayerCount = 0;
            for (j = 0; j < 4; j++) {
                if ((gPlayerMask >> j) & 1)
                    gPlayerCount++;
            }
            break;
        default:
            return 0;
        }
    }
    return 1;
send:
    REG_JOY_TRANS = *(u32 *)&gJoyWork.send.raw[gJoyWork.offset];
    gJoyWork.offset += 4;
    return 1;
}

void Link_JoyReset(void)
{
    REG_JOY_RECV;
    REG_JOY_TRANS = gJoyWork.agbId;
    REG_JOYSTAT = 0x20;
    gJoyWork.connected = 0;
    gJoyWork.handshake = 1;
}

void Link_JoyIntr(void)
{
    u16 stat;

    gJoyIntrCount++;
    REG_IE &= ~INTR_FLAG_SERIAL;
    stat = REG_JOYCNT;
    if (((stat & JOYCNT_SEND) && !Link_Send()) || ((stat & JOYCNT_RECV) && !Link_Recv(REG_JOY_RECV))) {
        REG_JOYSTAT = 0;
        gJoyWork.connected = 0;
        gJoyWork.handshake = 0;
    }
    if (stat & JOYCNT_RESET) {
        Link_JoyReset();
        if (gJoyWork.idleCount <= 2 && ++gJoyWork.resetCount >= 30)
            JoyBus_HardReset();
        gJoyWork.idleCount = 0;
    } else if (gJoyWork.idleCount >= 2) {
        gJoyWork.resetCount = 0;
    } else {
        gJoyWork.idleCount++;
    }
    REG_JOYCNT = stat;
    gJoyWork.timeout = 0;
    REG_IE |= INTR_FLAG_SERIAL;
}

void Link_Init(void)
{
    u16 ime = REG_IME;

    REG_IME = 0;
    if (gJoyWork.firstInit == 0)
        REG_RCNT = 0x8000;
    REG_RCNT = 0xC000;
    REG_JOYSTAT = 0;
    REG_JOY_RECV;
    REG_JOY_TRANS = 0;
    REG_JOYCNT = 0x47;
    REG_IF = INTR_FLAG_SERIAL;
    gJoyWork.timeout = 0;
    gJoyWork.connected = 0;
    gJoyWork.handshake = 0;
    gJoyWork.firstInit = 0;
    gJoyWork.resetCount = 0;
    gJoyWork.idleCount = 0;
    REG_IME = ime;
}

void Link_InitState(void)
{
    s32 i;
    s32 j;
    u32 k;
    u16 ime;
    s32 m;
    s32 n;

    gLinkMode = gConfigLinkMode;
    gJoyRecvQueue.write = 0;
    gJoyRecvQueue.read = 0;
    gJoyRecvQueue.mask = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++)
            gJoyRecvQueue.rows[i].valid[j] = 0;
    }
    if (gLinkMode != 0) {
        gLinkFrameCount = 0;
        gLinkSynced = 0;
        gLinkWaitStart = 1;
        gLinkStarted = 0;
        gLinkFrameReady = 0;
        gPlayerCount = 0;
        gLinkWarmup = 0;
        gPlayerMask = 0;
        gLinkFirstFrame = 1;
        gLinkUnused = 0;
        gJoySendPending = 0;
        gJoyRecvFrames = 0xFF;
        gJoyIntrCount = 0;
        gLinkSendCmd = PAD_CODE_NONE;
        ime = REG_IME;
        REG_IME = 0;
        for (k = 0; k < sizeof(gJoyWork); k++)
            ((u8 *)&gJoyWork)[k] = 0;
        gJoyWork.firstInit = 1;
        Link_Init();
        gJoyWork.agbId = *(const u32 *)gJoyAgbId;
        gJoyWork.expectedGcId = *(const u32 *)gJoyGcId;
        gJoyWork.send.ctx.cartFixed = *(u16 *)0x080000B2;
        gJoyWork.send.ctx.cartGameCode = *(u32 *)0x080000AC;
        REG_IME = ime;
    } else {
        gLinkSynced = 0;
        gLinkWaitStart = 1;
        gLinkStarted = 0;
        gLinkFrameReady = 0;
        gPlayerCount = 1;
        gPlayerMask = 1;
        gLinkFirstFrame = 1;
        gLinkUnused = 0;
        gLinkSendCmd = PAD_CODE_NONE;
        for (m = 0; m < 4; m++) {
            for (n = 0; n < 8; n++)
                gJoyWork.recv.ctx.foodLevels[m][n] = n * 100 / 8 + 5;
        }
    }
}

s32 Link_CheckTimeout(void)
{
    s32 ret;

    if (gJoyWork.timeout > 10) {
        gJoyWork.timedOut = 1;
        Link_Init();
        ret = 1;
    } else {
        REG_IME = 0;
        gJoyWork.timeout++;
        REG_IME = 1;
        ret = 0;
    }
    return ret;
}

/* Takes the next pad packet received from the GameCube and updates every player's keys */
void Link_ApplyRemotePads(void)
{
    u32 limit;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    u16 keys;

    if (gLinkMode) {
        gLinkStarted = 0;
        if (gPlayerCount == 0) {
            gLinkFrameReady = 0;
            return;
        }
        if (gLinkWarmup < 4) {
            gLinkFrameReady = 0;
            return;
        }
        if (gLinkSynced)
            limit = gVBlankCounter + 240;
        else
            limit = gVBlankCounter + 7200;

        n = 0;
        if (gLinkFirstFrame)
            goto fail;
    retry:
        if (gVBlankCounter > limit) {
            for (j = 0; j < 4; j++) {
                if (j != gPlayerNo)
                    RemovePlayer(&gMain, j);
            }
            gLinkMode = 0;
            return;
        }
        if (gJoyRecvQueue.read == gJoyRecvQueue.write) {
            if (gLinkSynced == 0)
                goto fail;
            gLinkWaitCount++;
            if (++n > 1000) {
                Text_Flush(&gTextLayer);
                gJoyLastRecv = 0;
                n = 0;
            }
            goto retry;
        }

        ((vu16 *)PLTT)[255] = 0xFFFF;
        for (i = 0; i < 4; i++) {
            if (gJoyRecvQueue.rows[gJoyRecvQueue.read].valid[i]) {
                if (Crc8(gJoyRecvQueue.rows[gJoyRecvQueue.read].data[i] >> 8)
                    == gJoyRecvQueue.rows[gJoyRecvQueue.read].data[i] >> 24) {
                    keys = gJoyRecvQueue.rows[gJoyRecvQueue.read].data[i] >> 8;
                    if (keys == LINK_CMD_REMOVE_PLAYER)
                        RemovePlayer(&gMain, i);
                    if ((keys & 0xF000) == 0) {
                        gPadNew[i] = keys & ~gPadHeld[i];
                        gPadHeld[i] = keys;
                    }
                } else {
                    AssertFailed(gJoyBusFileName, 839);
                }
            } else if ((u32)(1 << i) & gPlayerMask) {
                if (gLinkSynced)
                    AssertFailed(gJoyBusFileName, 844);
                goto fail;
            }
            gJoyRecvQueue.rows[gJoyRecvQueue.read].valid[i] = 0;
        }

        gLinkFrameCmd = gJoyRecvQueue.rows[gJoyRecvQueue.read].data[4] >> 8;
        gJoyRecvQueue.read++;
        if (gJoyRecvQueue.read > 3)
            gJoyRecvQueue.read = 0;
        if (gLinkWaitStart) {
            if (gLinkFrameCmd != LINK_CMD_START)
                goto fail;
            gLinkWaitStart = 0;
            gLinkStarted = 1;
            gLinkFrameCount = 0;
        }
        gLinkSynced = 1;
        gLinkFrameReady = 1;
        goto end;
    fail:
        gLinkFrameReady = 0;
    end:
        gLinkFirstFrame = 0;
    } else {
        gJoySendData = (Crc8(gHeldKeys) << 24) | (gHeldKeys << 8) | 0x20;
        for (k = 0; k < 4; k++) {
            gPadNew[k] = 0;
            gPadHeld[k] = 0;
        }
        gPadNew[gPlayerNo] = gNewKeys;
        gPadHeld[gPlayerNo] = gHeldKeys;
        gLinkStarted = 0;
        if (gLinkWaitStart) {
            gLinkWaitStart = 0;
            gLinkStarted = 1;
        }
        gLinkSynced = 1;
        gLinkFrameReady = 1;
    }
}

/* Queues this GBA's keys (or a pending command) for the next transfer */
void Link_BuildPadPacket(void)
{
    u32 v;

    if (gLinkMode == 0)
        return;
    if (gPlayerCount == 0) {
        gLinkFrameReady = 0;
        return;
    }
    if (gLinkWarmup < 3) {
        gLinkWarmup++;
        gLinkFrameReady = 0;
        return;
    }
    if (gLinkWarmup < 4)
        gLinkWarmup++;
    if (gJoySendPending == 0) {
        if (gLinkSendCmd != PAD_CODE_NONE) {
            v = gLinkSendCmd | PAD_CODE_FLAG;
            gJoySendData = (Crc8(v) << 24) | (v << 8) | 0x20;
            gLinkSendCmd = PAD_CODE_NONE;
        } else {
            gJoySendData = (Crc8(gHeldKeys) << 24) | (gHeldKeys << 8) | 0x20;
        }
        REG_JOYSTAT = 0x10;
        gJoySendPending = 1;
    }
    if (gLinkSynced)
        gLinkFrameCount++;
}
