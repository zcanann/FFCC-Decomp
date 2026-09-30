#ifndef GUARD_LINK_H
#define GUARD_LINK_H

#include "global.h"

/*
 * JOY Bus link to the GameCube. Every transfer is one 32-bit word; byte 0 holds
 * the command id in its low 6 bits and the word's kind (first/second/data/abort)
 * in its top 2 bits.
 */

/* One received word viewed as a command with a 16-bit little-endian value. */
struct JoyWord {
    u8 cmd;
    u8 arg;
    u16 value;
};

/* One received word viewed as a command with a signed byte argument. */
struct JoyArgs {
    u8 cmd;
    u8 sub;
    s8 arg;
    u8 extra;
};

/* One received word viewed as plain bytes. */
struct JoyBytes {
    u8 b[4];
};

extern s8 gLinkEstablished;
extern u8 gLinkStarted;
extern u8 gMenuHasInput;
extern s8 gReplyResult;
extern s8 gReplyWaiting;

u32 Crc8(u32 data);
u16 Crc16(s32 n, u8 *data, u16 *crc);

void Link_JoyIntr(void);
void Link_Init(void);
void Link_Reset(void);
s32 Link_CheckTimeout(void);
void Link_JoyReset(void);
s32 Link_Recv(u32 data);
s32 Link_Send(void);
u8 Link_IsConnected(void);
void Link_SendPad(u16 keys);
void Link_SendScreenId(s32 screen);
void Link_ClearQueues(void);
s32 Link_Write(u32 data);
void Link_TxPop(void);
void Link_RxPush(void);
void Link_ProcessRecv(void);
void Link_DispatchMessage(void);
s32 Link_GetPlayerNo(void);
s32 Link_SendRequest(u8 type, u8 arg);
s32 Link_SendEvent(u8 sub, u8 a, u8 b);
s32 Link_SendLetterReply(u8 letter, s32 answer, u8 isGil, u32 value);
void Link_SendItemOp(u8 op, u8 slot, u8 arg);
void Link_SendGil(u8 op, u32 gil);
void Link_SendCMakeName(u8 *name);
void Link_SendCMakeLook(s32 look);
void Link_SendCMakeJob(u8 job);
void Link_SendCMakeCancel(void);
void Link_SendCMakeEnd(void);
void Link_SendCMakeBirthday(s32 month, s32 day);
void Link_SendCMakeFavorite(u8 *foods);
void Link_SendEquipSlot(u8 slot, u8 item);
void Link_SendCmdSlot(u8 slot, s32 item);

void Reply_Clear(void);
void Reply_Set(s32 result);
void Reply_Tick(void);
s32 Reply_IsTimedOut(void);

#endif
