#ifndef GUARD_SESSION_H
#define GUARD_SESSION_H

#include "global.h"
#include "link.h"

/* State of the local player, filled in from GameCube messages. */
struct Session {
    s8 appearance;            /* bits 0-1 tribe, 2-3 look, bit 7 female */
    s8 stats[3];              /* strength, defense, magic */
    u8 relationType[4];
    u8 relationValue[4];
    char relationNames[4][18];
    u8 favorites[8];          /* food preference scores */
    u8 useItem;
    s8 cmdSlotCount;
    u8 equipment[4];          /* inventory slot per equipment slot, -1 if empty */
    u16 memories;
    s16 items[64];            /* inventory item ids, -1 if empty */
    s16 unkE4[8];
    u16 cmdSlots[8];          /* inventory index per command slot, -1 if empty */
    u32 gil;
    u32 artifacts[3];         /* bitmask of owned artifacts */
    u32 prevArtifacts[3];
    s16 stageArtifacts[4];    /* artifacts picked up in the current stage */
    s8 outsideMiasma;
    s8 job;                   /* family occupation */
};

/* Caravan member in one of the four controller ports */
struct Member {
    char *name;
    u16 saveSlot;
    s8 maxHp;
    s8 hp;
};

/* Character being created (mode 1). */
struct CMakeData {
    char name[17];
    s8 look;
    u8 birthday[2];
    u8 favorites[4];
    u8 job[4];
};

extern struct Session gSession;
extern struct Member gParty[4];
extern struct CMakeData gCMakeData;
extern char gBonusStr[2][65];
extern s8 gItemUseFlags;
extern u16 gMask;

void Session_Init(void);
void Session_OnItemChange(u32 data);
void Session_OnPlayerStat(u8 *p);
void Session_OnPartyHp(s8 *p);
void Session_OnItemAll(u8 *p);
void Session_OnFavorite(u8 *p);
void Session_SetGil(u32 val);
s32 Session_OnCompatibility(u8 *p);
void Session_OnEquipList(u8 *p);
void Session_OnEquipSlot(u32 data);
void Session_OnCmdSlot(u32 data);
void Session_OnTmpArtifact(u32 data);
void Session_OnBonusStr(char *s);
s32 Session_GetItemCategory(s32 idx);
s32 Item_GetCategory(s32 val);
s32 Session_IsItemInUse(s32 id);
void Session_OnUseItem(u32 data);
s32 Item_CanEquip(u16 *p);
s32 Item_IsEquipped(s32 id);
void Session_OnStrength(u32 data);
s32 Item_IsPercentKind(s32 id);
void Session_OnArtifacts(u8 *p);
void Session_OnTmpArtifacts(u8 *p);
void Session_OnCmdList(u8 *p);
void Session_OnItemUseFlags(u32 data);
void Session_OnSpMode(u32 data);
void Session_OnCmdNum(u32 data);
void Session_OnMemories(u32 data);
void Session_OnStartBonus(void);
void Session_OnLanguage(u32 data);
void Session_OnMask(struct JoyBytes cmd);
void Item_FormatWearer(u16 *flags, char *dst);

#endif
