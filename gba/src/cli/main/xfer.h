#ifndef GUARD_XFER_H
#define GUARD_XFER_H

#include "global.h"

/* gDataFlags: data-ready bits, one per bulk download type, plus state bits */
#define DATA_OBJ          0x0001 /* type 0: sprite data */
#define DATA_MAP          0x0002 /* type 1: radar map */
#define DATA_LETTER       0x0004 /* type 2: letter body */
#define DATA_LETTER_LIST  0x0008 /* type 3: letter list */
#define DATA_EQUIP_LIST   0x0010 /* message 6 */
#define DATA_SELL_LIST    0x0020 /* type 6 */
#define DATA_BUY_LIST     0x0040 /* type 7 */
#define DATA_SMITH_LIST   0x0080 /* type 8 */
#define DATA_ARTIFACTS    0x0100 /* type 9 */
#define DATA_CMD_LIST     0x0200 /* message 12 */
#define DATA_BASE_POS     0x0400 /* map base position received */
#define DATA_REPLY        0x8000 /* the GameCube answered with an ACK/NAK */

/* State of a GameCube bulk download (cmd 11). */
struct BulkXfer {
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

extern u16 gDataFlags;
extern s8 gXferActive;
extern s8 gXferErrorCount;
extern u8 gStaticMap;
extern s8 gNewLetter;

/* EWRAM download area: the GameCube writes bulk data straight to these addresses. */
#define DOWNLOAD_BUF  ((u8 *)0x02038000) /* types 0 and 1 */
#define DOWNLOAD_DATA (DOWNLOAD_BUF + 0x20) /* past the 32-byte header */
#define LIST_BUF      ((u8 *)0x0203A800) /* lists: letters, shop, smith, artifacts, scouter */
#define DETAIL_BUF    ((u8 *)0x0203D800) /* letter body, equipment and command candidates */

void Xfer_DrawProgress(s32 show);
void Xfer_Init(void);
s32 Xfer_CheckCrc(u32 packet);
void Xfer_Begin(void);
s32 Xfer_Receive(u32 packet, u8 *out);
struct BulkXfer *Xfer_GetWork(void);
void Xfer_ClearLetterData(void);
void Xfer_OnError(void);

void Map_SetStage();
void Map_GetStage(s8 *area, s8 *map);

#endif
