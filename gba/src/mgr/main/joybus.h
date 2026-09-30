#ifndef GUARD_JOYBUS_H
#define GUARD_JOYBUS_H

#include "global.h"

struct JoyWork {
    vu8 connected;
    vu8 handshake;
    vu8 timeout;
    vu8 timedOut;
    vu8 cmd;
    vu8 offset;
    vu8 firstInit;
    u8 resetCount;
    u8 idleCount;
    u8 unk9[3];
    u32 agbId;
    u32 gcId;
    u32 expectedGcId;
    u8 send[0x60];
    union {
        u8 raw[0x60];
        struct {
            u8 unk0[0x14];
            u8 panelTable[4][16];
        } info;
    } recv;
};

struct JoyRecvRow {
    vu8 valid[8];
    vu32 data[5];
};

struct JoyRecvQueue {
    vu8 write;
    vu8 read;
    vu8 mask;
    u8 unk3;
    struct JoyRecvRow rows[4];
};

extern struct JoyWork gJoyWork;
extern struct JoyRecvQueue gJoyRecvQueue;
extern u32 gJoySendData;
extern vu16 gPadHeld[4];
extern vu16 gPadNew[4];
extern vu8 gLinkMode;
extern u8 gLinkSynced;
extern u8 gLinkWaitStart;
extern u8 gLinkStarted;
extern u8 gLinkFrameReady;
extern vu8 gPlayerNo;
extern vu8 gPlayerCount;
extern vu8 gPlayerMask;
extern u8 gLinkFirstFrame;
extern vu8 gJoyRecvFrames;
extern u8 gJoyLastRecv;
extern u32 lbl_03005D6C;
extern u16 gLinkWaitCount;
extern u16 gLinkFrameCmd;
extern u16 gLinkSendCmd;
extern u16 gLinkFrameCount;
extern vu8 gLinkWarmup;
extern u8 gJoySendPending;
extern vu8 gJoyIntrCount;

extern const u32 gJoyAgbId;
extern const u32 gJoyGcId;
extern const char gJoyBusFileName[];

void ReadKeys(void);
u32 Crc8(u32 data);
s32 Link_Recv(u32 data);
s32 Link_Send(void);
void Link_JoyReset(void);
void Link_JoyIntr(void);
void Link_Init(void);
void Link_InitState(void);
s32 Link_CheckTimeout(void);
void Link_ApplyRemotePads(void);
void Link_BuildPadPacket(void);

#endif
