#ifndef GUARD_LINK_H
#define GUARD_LINK_H

#include "MgJoyBus.h"

extern struct JoyWork gJoyWork;
extern vu16 gPadHeld[4];
extern vu16 gPadNew[4];
extern vu8 gLinkMode;
extern u8 gLinkSynced;
extern u8 gLinkWaitStart;
extern u8 gLinkStarted;
extern u8 gLinkFrameReady;
extern vu8 gPlayerNo;
extern u8 gPlayerCount;
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

static inline s32 IsActive(u16 no)
{
    return (1 << no) & gPlayerMask;
}

static inline void CountPlayers(void)
{
    s32 i;

    gPlayerCount = 0;
    for (i = 0; i < 4; i++) {
        if (((gPlayerMask >> i) & 1) == 1)
            gPlayerCount++;
    }
}

#endif
