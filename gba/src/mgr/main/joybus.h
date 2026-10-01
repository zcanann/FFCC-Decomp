#ifndef GUARD_JOYBUS_H
#define GUARD_JOYBUS_H

#include "global.h"

/* Pad codes sent to the GameCube in place of the keys */
#define PAD_CODE_FLAG     0x8000
#define PAD_CODE_RESULT   0x1000 /* | finishing position */
#define PAD_CODE_RACE_END 0x1100
#define PAD_CODE_QUIT     0x1200
#define PAD_CODE_CONTINUE 0x1300
#define PAD_CODE_NONE     0xFFFF

/* Session context exchanged with the GameCube during the handshake */
struct LinkContext {
    u8 booted;        /* the GameCube downloaded this program */
    u8 playerNo;
    u8 cartFixed;     /* fixed header byte of an inserted cartridge */
    u8 initialized;
    u32 sessionId;
    u32 tick;
    u32 cartGameCode;
    u8 mode;
    u8 playerMask;
    u8 pad[2];
    u8 foodLevels[4][16]; /* each player's liking (1-100) of the panel foods */
    u8 pad2[12];
};

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
    u32 agbId;
    u32 gcId;
    u32 expectedGcId;
    union {
        u8 raw[0x60];
        struct LinkContext ctx;
    } send;
    union {
        u8 raw[0x60];
        struct LinkContext ctx;
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
    struct JoyRecvRow rows[4];
};

extern struct JoyWork gJoyWork;
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
extern u32 gLinkUnused;
extern u16 gLinkWaitCount;
extern u16 gUnused_03005D72;
extern u16 gLinkFrameCmd;
extern u16 gLinkSendCmd;
extern struct JoyRecvQueue gJoyRecvQueue;
extern u16 gLinkFrameCount;
extern vu8 gLinkWarmup;
extern u8 gJoySendPending;
extern vu8 gJoyIntrCount;

extern const char gJoyAgbId[];
extern const char gJoyGcId[];
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
