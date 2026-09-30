#ifndef GUARD_LISTS_H
#define GUARD_LISTS_H

#include "global.h"

/* Layouts of the lists the GameCube downloads into gListBuf / gDetailBuf. */

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

extern struct LetterEntry gLetterEntries[];
extern s16 gBuyItemIds[];
extern s8 gSmithItemSlots[];
extern char gSellItemDescs[];
extern struct ItemInfo gCmdItemInfo[];

#endif
