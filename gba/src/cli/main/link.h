#ifndef GUARD_LINK_H
#define GUARD_LINK_H

#include "global.h"

/*
 * JOY Bus link to the GameCube. Every transfer is one 32-bit word; byte 0 holds
 * the command id in its low 6 bits and the word's kind (first/second/data/abort)
 * in its top 2 bits.
 */
#define LINK_CMD_MASK    0x3F
#define LINK_KIND_SECOND 0x40
#define LINK_KIND_DATA   0x80

/* Command ids; directions are GameCube to GBA unless noted. */
#define LINK_CONTEXT       1  /* handshake */
#define LINK_PAD           4  /* to GC: key state */
#define LINK_MESSAGE       5  /* multi-word message, see MSG_* */
#define LINK_ACK           6  /* both directions */
#define LINK_NAK           7  /* both directions */
#define LINK_FLUSH         8
#define LINK_CTRL_MODE     9
#define LINK_START         10
#define LINK_DATA          11 /* bulk download */
#define LINK_REQUEST       12 /* both directions, see REQ_* */
#define LINK_CHECK_CRC     13
#define LINK_STATE         14 /* map number; to GC: screen id */
#define LINK_BASE_POS      15
#define LINK_CANCEL        16
#define LINK_PARTY_POS     17
#define LINK_ENEMY_POS     18
#define LINK_PARTY_HP      19
#define LINK_EVENT         20 /* both directions, see EVT_* */
#define LINK_LETTER_REPLY  21 /* to GC */
#define LINK_MAPOBJ_FLAGS  22
#define LINK_ITEM          23 /* both directions */
#define LINK_MASK          24
#define LINK_STRENGTH      25
#define LINK_GIL           26 /* both directions */
#define LINK_MODE          27
#define LINK_CMAKE_NAME    28 /* to GC */
#define LINK_CMAKE_FOODS   29 /* to GC */
#define LINK_EQUIP_SLOT    30 /* both directions */
#define LINK_CMD_SLOT      31 /* both directions */
#define LINK_TMP_ARTIFACT  32
#define LINK_TREASURE_POS  33
#define LINK_HIT_ENEMY     34

/* LINK_STATE sub-commands */
#define STATE_SCREEN       0  /* to GC: current screen id */
#define STATE_MAP          1  /* stage and map number */

/* LINK_MESSAGE types */
#define MSG_PLAYER_STAT    1
#define MSG_ITEM_ALL       2
#define MSG_MAP_OBJ        3
#define MSG_FAVORITE       4
#define MSG_COMPATIBILITY  5
#define MSG_EQUIP_LIST     6
#define MSG_BONUS_STR      7
#define MSG_ARTIFACTS      8
#define MSG_TMP_ARTIFACTS  9
#define MSG_MARKER_KINDS   10
#define MSG_SCOUTER_INFO   11
#define MSG_CMD_LIST       12

/* LINK_REQUEST types; most name the bulk download the GBA wants */
#define REQ_LETTER         2
#define REQ_LETTER_LIST    3
#define REQ_SELL_LIST      6
#define REQ_BUY_LIST       7
#define REQ_SMITH_LIST     8
#define REQ_ARTIFACTS      9
#define REQ_STATE          LINK_STATE /* from GC: report the screen id */

/* LINK_EVENT sub-commands from the GameCube */
#define EVT_ADD_LETTER     1
#define EVT_USE_ITEM       12
#define EVT_RADAR_TYPE     13
#define EVT_RADAR_MODE     14
#define EVT_OPEN_MENU      15
#define EVT_ITEM_USE_FLAGS 16
#define EVT_SP_MODE        17
#define EVT_CMD_NUM        18
#define EVT_MEMORIES       19
#define EVT_START_BONUS    20
#define EVT_LANGUAGE       22

/* LINK_EVENT sub-commands to the GameCube */
#define EVT_TAKE_ATTACHMENT 0
#define EVT_CMAKE_LOOK      2
#define EVT_CMAKE_JOB       3
#define EVT_CMAKE_CANCEL    4
#define EVT_CMAKE_END       5
#define EVT_CMAKE_BIRTHDAY  6
#define EVT_SHOP_LEAVE      7
#define EVT_SHOP_SELL       8
#define EVT_SHOP_BUY        9
#define EVT_SMITH_FORGE     10
#define EVT_SMITH_LEAVE     11
#define EVT_GIL_RESEND      21

/* LINK_ITEM operations to the GameCube */
#define ITEM_OP_USE        1
#define ITEM_OP_PUT        2
#define ITEM_OP_DISCARD    3

/* LINK_GIL operations */
#define GIL_OP_SET         0  /* from GC: the player's gil */
#define GIL_OP_PUT         1  /* to GC: drop gil */

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
