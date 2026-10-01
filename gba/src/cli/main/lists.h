#ifndef GUARD_LISTS_H
#define GUARD_LISTS_H

#include "global.h"
#include "xfer.h"

/* Layouts of the lists the GameCube downloads into LIST_BUF / DETAIL_BUF. */

/* Equipment attributes of an item (equip list, command list, shop, smith). */
struct ItemInfo {
    u16 flags;
    u16 count;
    u16 kind;
    u16 unk6;
};

/* Letter list (bulk type 3): header, entries, subjects (24 bytes), senders (16). */
struct LetterListHeader {
    s32 count;
    s32 subjectCount;
    u32 senderCount;
    u32 canReply;
};

struct LetterEntry {
    u32 attachment;
    u8 subject;
    u8 sender;
    u8 flags;
    u8 pad;
};

/* Buy list (bulk type 7): item ids, then u32 prices and names. */
struct BuyList {
    u8 count;
    u8 pad[3];
    s16 ids[64];
};

/* Smith recipe (bulk type 8), following the list of inventory slots. */
struct Recipe {
    u32 price;
    s16 materials[3];
    s16 counts[3];
    s16 ids[4];
    struct ItemInfo items[4];
};

#define LETTER_ENTRIES   ((struct LetterEntry *)(LIST_BUF + sizeof(struct LetterListHeader)))
#define BUY_ITEM_IDS     (((struct BuyList *)LIST_BUF)->ids)
#define SMITH_ITEM_SLOTS ((s8 *)LIST_BUF + 1)
#define SELL_ITEM_DESCS  ((char *)LIST_BUF + 0x300)
#define CMD_ITEM_INFO    ((struct ItemInfo *)(DETAIL_BUF + 4))

#endif
