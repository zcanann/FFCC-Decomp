#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "text.h"
#include "session.h"
#include "radar.h"
#include "window.h"
#include "screen.h"

/* Names of the caravan's members, and per save slot a nibble with the member index */
struct CaravanNames {
    char names[8][16];
    s8 slotMap[4];
};

extern struct CaravanNames gCaravanNames;
static u32 sMapObjDrawFlagsIn;
static u16 sBasePos[2];
static u16 sPrevBasePos[2];
static struct Marker sPartyMarkers[4];
extern u8 gUnusedBytes[8];
static s8 sBackdropTribe;

void Session_Init(void)
{
    s32 i;

    memset(&gSession, 0, sizeof(gSession));
    memset(gParty, 0, sizeof(gParty));
    memset(&gCaravanNames, 0, sizeof(gCaravanNames));
    memset(&gMapObjs, 0, sizeof(gMapObjs));
    memset(gBonusStr, 0, sizeof(gBonusStr));
    memset(&gScouterHit, 0xFF, sizeof(gScouterHit));
    sBackdropTribe = 0;
    gRadarType = 1;
    gRadarMode = 1;
    gScouterDirty = 0;
    gLanguage = 0;
    for (i = 0; i < 2; i++) {
        sBasePos[i] = 0;
        sPrevBasePos[i] = 0;
    }
    for (i = 0; i < 8; i++)
        gUnusedBytes[i] |= 0xFF;
    for (i = 0; i < 4; i++)
        gParty[i].name = Msg_GetSystem(0);
    for (i = 0; i < 8; i++)
        gSession.cmdSlots[i] |= 0xFFFF;
    gSession.cmdSlotCount = 8;
    for (i = 0; i < 4; i++)
        gSession.equipment[i] |= 0xFF;
    Radar_ClearMarkers();
}

void Session_OnItemChange(u32 data)
{
    struct JoyWord *cmd = (struct JoyWord *)&data;
    u8 type = cmd->cmd & 0xC0;
    u8 idx = cmd->arg & 0x3F;
    s16 val = cmd->value;

    if (type != 0)
        return;

    gSession.items[idx] = val;
    if (gMode == MODE_FIELD) {
        if (gScreen == 1)
            CmdListScreen_BuildCandidates();
        else if (gScreen == 2 && gScreenPhase == PHASE_MAIN)
            ItemScreen_RefreshItem(idx);
    } else if (gMode == MODE_SHOP) {
        if (gScreen == 2 && gScreenPhase == PHASE_MAIN)
            ShopList_RefreshSellItem(idx);
    } else if (gMode == MODE_SMITH) {
        if (val > 0)
            Smith_SetResultSlot(idx);
    }
}

void Radar_SetBasePos(x, y)
u16 x;
u16 y;
{
    sBasePos[0] = x;
    sBasePos[1] = y;
    if (!(gDataFlags & DATA_BASE_POS)) {
        gDataFlags |= DATA_BASE_POS;
        sPrevBasePos[0] = x;
        sPrevBasePos[1] = y;
    }
}

void Radar_GetBasePos(s16 *x, s16 *y)
{
    *x = sBasePos[0];
    *y = sBasePos[1];
}

void Radar_GetBaseDelta(s16 *dx, s16 *dy)
{
    u16 flag = gDataFlags & DATA_BASE_POS;

    if (!flag) {
        *dx = flag;
        *dy = flag;
        sPrevBasePos[0] = sBasePos[0];
        sPrevBasePos[1] = sBasePos[1];
    } else {
        *dx = sBasePos[0] - sPrevBasePos[0];
        *dy = sBasePos[1] - sPrevBasePos[1];
        sPrevBasePos[0] = sBasePos[0];
        sPrevBasePos[1] = sBasePos[1];
    }
}

void Radar_ClearMarkers(void)
{
    memset(sPartyMarkers, 0, sizeof(sPartyMarkers));
    memset(gEnemyMarkers, 0, sizeof(gEnemyMarkers));
    memset(gTreasureMarkers, 0, sizeof(gTreasureMarkers));
}

void Radar_OnPartyPos(s8 *p)
{
    struct Marker *e = sPartyMarkers;
    u8 flags = p[1];
    s8 first = p[1];

    e[0].visible = first & 1;
    e[0].x = p[2];
    e[0].y = p[3];
    p += 4;
    e[1].visible = (flags >> 1) & 1;
    e[1].x = p[1];
    e[1].y = p[2];
    e[2].visible = (flags >> 2) & 1;
    e[2].x = p[3];
    p += 4;
    e[2].y = p[1];
    e[3].visible = (flags >> 3) & 1;
    e[3].x = p[2];
    e[3].y = p[3];
}

struct Marker *Radar_GetPartyMarker(s32 idx)
{
    return &sPartyMarkers[idx];
}

void Radar_OnEnemyPos(s8 *p)
{
    s32 idx = p[1] & 0x7F;

    gEnemyMarkers[idx].visible = p[1] >> 7;
    gEnemyMarkers[idx].x = p[2];
    gEnemyMarkers[idx].y = p[3];
}

void Radar_OnTreasurePos(s8 *p)
{
    s32 idx = (p[1] & 0x7F) - 64;

    gTreasureMarkers[idx].visible = p[1] >> 7;
    gTreasureMarkers[idx].x = p[2];
    gTreasureMarkers[idx].y = p[3];
}

void Session_OnPlayerStat(u8 *p)
{
    s32 i;
    s32 n;
    u8 *dst;

    memset(&gSession, 0, sizeof(gSession));
    memset(gParty, 0, sizeof(gParty));
    memset(gSession.items, 0xFF, sizeof(gSession.items));
    memset(gSession.unkE4, 0xFF, sizeof(gSession.unkE4));
    memset(gSession.equipment, 0xFF, sizeof(gSession.equipment));
    for (i = 0; i < 4; i++) {
        gParty[i].saveSlot |= 0xFFFF;
        gParty[i].name = Msg_GetSystem(0);
    }

    memcpy(&gCaravanNames, p, sizeof(gCaravanNames));
    p += sizeof(gCaravanNames);
    for (i = 0; i < 8; i++) {
        n = gCaravanNames.slotMap[i >> 1];
        if (i & 1)
            n &= 15;
        else
            n = (n & 0xF0) >> 4;
        if (n != 15)
            gParty[n].saveSlot = i;
    }
    for (i = 0; i < 4; i++) {
        n = (s16)gParty[i].saveSlot;
        if (n != -1)
            gParty[i].name = gCaravanNames.names[n];
        gParty[i].maxHp = p[0];
        gParty[i].hp = p[1];
        p += 2;
    }

    gSession.appearance = *p++;
    memcpy(gSession.stats, p, 3);
    p += 3;
    dst = (u8 *)&gSession.memories;
    for (i = 2; i != 0; i--)
        *dst++ = *p++;

    n = Session_OnCompatibility(p);
    p += n;
    memcpy(gSession.favorites, p, 8);
    p += 8;
    dst = (u8 *)&gSession.gil;
    for (i = 0; i < 4; i++)
        dst[i] = *p++;

    n = gSession.appearance & 3;
    if (n != sBackdropTribe) {
        Bg_LoadBackdrop(n);
        sBackdropTribe = n;
    }
    if ((u32)gScreen <= 5) {
        Screen_Reset();
        Bg_ClearMaps();
    }
}

void Session_OnPartyHp(s8 *p)
{
    s32 i;
    struct Member *m;

    for (i = 0, m = gParty; i < 4; m++, i++) {
        if (i == Link_GetPlayerNo()) {
            if ((p[1] & 0x80) && m->hp > p[2])
                Shake_Start();
            m->hp = p[2];
        } else if ((p[1] >> i) & 1) {
            m->hp = m->maxHp;
        } else {
            m->hp = 0;
        }
    }
    gSession.outsideMiasma = p[3];
}

void Radar_OnMapObj(u8 *p)
{
    s32 i;
    u32 val;
    struct MapObj *e;

    memset(&gMapObjs, 0, sizeof(gMapObjs));
    gMapObjs.count = *p++;
    val = p[0];
    val |= p[1] << 8;
    val |= p[2] << 16;
    val |= p[3] << 24;
    p += 4;
    gMapObjs.drawFlags = val;
    for (i = 0; i < gMapObjs.count; i++) {
        e = &gMapObjs.entries[i];
        e->type = *p++;
        e->x0 = *p++;
        e->x0 |= *p++ << 8;
        e->y0 = *p++;
        e->y0 |= *p++ << 8;
        e->x1 = *p++;
        e->x1 |= *p++ << 8;
        e->y1 = *p++;
        e->y1 |= *p++ << 8;
    }
}

void Radar_OnMapObjDrawFlags(u8 *msg)
{
    u8 *p;
    u16 sum;
    u16 crc;
    u32 val;

    p = msg;
    if ((p[0] >> 6) == 0) {
        sMapObjDrawFlagsIn = *(u32 *)p;
        return;
    }
    p = (u8 *)&sMapObjDrawFlagsIn;
    sum = p[1] | (p[2] << 8);
    val = p[3];
    p = msg;
    val |= p[1] << 8;
    val |= p[2] << 16;
    val |= p[3] << 24;
    p = (u8 *)&val;
    crc = 0xFFFF;
    if (Crc16(4, p, &crc) == sum)
        gMapObjs.drawFlags = val;
}

void Session_OnItemAll(u8 *p)
{
    s32 i;

    memcpy(gSession.items, p, sizeof(gSession.items));
    p += sizeof(gSession.items);
    memcpy(gSession.prevArtifacts, gSession.artifacts, 12);
    memcpy(gSession.artifacts, p, 12);
    p += 12;
    memcpy(gSession.stageArtifacts, p, 8);
    p += 8;
    for (i = 0; i < 4; i++)
        gSession.equipment[i] = *p++;
    memcpy(gSession.cmdSlots, p, 16);
    gSession.cmdSlotCount = p[16];
}

void Session_OnFavorite(u8 *p)
{
    memcpy(gSession.favorites, p, 8);
}

void Session_SetGil(u32 val)
{
    gSession.gil = val;
}

s32 Session_OnCompatibility(u8 *p)
{
    s32 n;
    s32 size;
    s32 i;
    s32 len;

    gSession.job = *p++;
    n = *p++;
    size = 2;
    memset(gSession.relationType, 0, 8);
    memset(gSession.relationNames, 0, sizeof(gSession.relationNames));
    for (i = 0; i < n; i++) {
        gSession.relationType[i] = *p++;
        gSession.relationValue[i] = *p++;
    }
    size += n * 2;
    for (i = 0; i < n; i++) {
        len = strlen(p);
        strcpy(gSession.relationNames[i], p);
        p += len + 1;
        size += len + 1;
    }
    return size;
}

void Session_OnEquipList(u8 *p)
{
    s32 i;
    s32 size;
    s32 n;

    for (i = 0; i < 4; i++)
        gSession.equipment[i] = *p++;
    n = *p;
    size = n + 1;
    if (size & 3)
        size = ((size >> 2) + 1) << 2;
    size += n * 8;
    memcpy(DETAIL_BUF, p, size);
    gDataFlags |= DATA_EQUIP_LIST;
}

void Session_OnEquipSlot(u32 data)
{
    struct JoyBytes *cmd = (struct JoyBytes *)&data;
    u8 idx = cmd->b[1];
    u8 val = cmd->b[2];

    gSession.equipment[idx] = val;
}

void Session_OnCmdSlot(u32 data)
{
    struct JoyWord *cmd = (struct JoyWord *)&data;
    s8 idx = cmd->arg;
    u16 val = cmd->value;

    gSession.cmdSlots[idx] = val;
    if (gScreen == 1)
        CmdListScreen_PrintSlot(idx);
    else if (gScreen == 2)
        ItemScreen_RefreshItem((s16)val);
}

void Session_OnTmpArtifact(u32 data)
{
    struct JoyBytes *cmd = (struct JoyBytes *)&data;
    u8 idx = cmd->b[1];
    u8 val = cmd->b[2];

    gSession.stageArtifacts[idx] = (val != 0xFF) ? val + 159 : -1;
    if (gScreen == 1)
        CmdListScreen_BuildCandidates();
    else if (gScreen == 5)
        TmpArtifactScreen_RefreshRow(idx);
}

void Session_OnBonusStr(char *s)
{
    memset(gBonusStr, 0, sizeof(gBonusStr));
    strcpy(gBonusStr[0], s);
    s += strlen(s);
    s++;
    strcpy(gBonusStr[1], s);
}

s32 Session_GetItemCategory(s32 idx)
{
    return Item_GetCategory(gSession.items[idx]);
}

s32 Item_GetCategory(s32 val)
{
    s32 level;

    if (val <= 0)
        level = 0;
    else if (val <= 158)
        level = 1;
    else if (val <= 255)
        level = 2;
    else if (val <= 292)
        level = 3;
    else if (val == 293)
        level = 4;
    else if (val <= 297)
        level = 5;
    else if (val <= 380)
        level = 6;
    else if (val <= 392)
        level = 7;
    else if (val <= 400)
        level = 8;
    else
        level = 9;
    return level;
}

s32 Session_IsItemInUse(s32 id)
{
    s32 i;

    if (id < 64 && gSession.items[id] <= 0)
        return 0;
    for (i = 2; i < 8; i++) {
        if ((s16)gSession.cmdSlots[i] == id)
            return 1;
    }
    if (id < 64)
        return Item_IsEquipped(id);
    return 0;
}

void Session_OnUseItem(u32 data)
{
    struct JoyBytes *cmd = (struct JoyBytes *)&data;

    gSession.useItem = cmd->b[2];
}

s32 Item_CanEquip(u16 *p)
{
    s32 a = *p & 0xF;
    s32 b = *p & 0x30;
    s32 mask = 1 << (gSession.appearance & 3);
    s32 mask2 = (gSession.appearance & 0x80) ? 32 : 16;

    if (a) {
        if (b) {
            a &= mask;
            return a && (b & mask2);
        }
        return (a & mask) != 0;
    }
    return (b & mask2) != 0;
}

s32 Item_IsEquipped(s32 id)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((s8)gSession.equipment[i] == id)
            break;
    }
    return i < 4;
}

void Session_OnStrength(u32 data)
{
    struct JoyBytes *cmd = (struct JoyBytes *)&data;
    s32 i;
    u8 *p = &cmd->b[1];

    for (i = 0; i < 3; i++)
        gSession.stats[i] = *p++;
    if ((u32)gScreen <= 3)
        StatusWin_Refresh(0);
}

s32 Item_IsPercentKind(s32 id)
{
    if (id == 9 || id == 10 || id == 12)
        return -1;
    return 0;
}

void Session_OnArtifacts(u8 *p)
{
    memcpy(gSession.prevArtifacts, gSession.artifacts, 12);
    memcpy(gSession.artifacts, p, 12);
    if (gScreen == 4)
        ArtifactScreen_Refresh();
    else if (gScreen == 1)
        CmdListScreen_BuildCandidates();
}

void Session_OnTmpArtifacts(u8 *p)
{
    memcpy(gSession.stageArtifacts, p, 8);
}

void Radar_OnMarkerKinds(u8 *p)
{
    s32 i;

    for (i = 0; i < 64; i++)
        gEnemyMarkers[i].kind = *p++;
    for (i = 0; i < 16; i++)
        gTreasureMarkers[i].kind = *p++;
}

void Radar_OnType(u32 data)
{
    struct JoyArgs *cmd = (struct JoyArgs *)&data;
    s8 old = gRadarType;

    gRadarType = cmd->arg;
    if (gScreen == 0 && gRadarType != old) {
        Screen_Reset();
        Bg_ClearMaps();
    }
}

void Radar_OnMode(u32 data)
{
    struct JoyArgs *cmd = (struct JoyArgs *)&data;
    s8 old = gRadarMode;

    gRadarMode = cmd->arg;
    if (gScreen == 0 && gRadarMode != old) {
        Screen_Reset();
        Bg_ClearMaps();
    }
}

void Scouter_OnInfo(u8 *p)
{
    s32 size = 0x200;

    memcpy(LIST_BUF, p, size);
    memset(&gScouterHit, 0xFF, sizeof(gScouterHit));
    gScouterDirty = 1;
    Scouter_SetDirty(1);
}

void Scouter_OnHitEnemy(u32 data)
{
    struct JoyWord *cmd = (struct JoyWord *)&data;

    gScouterHit.enemy = cmd->arg;
    gScouterHit.hp = cmd->value;
    gScouterDirty = 1;
}

void Session_OnCmdList(u8 *p)
{
    s32 size = p[0] * 8 + 1;

    memcpy(DETAIL_BUF, p, size);
    gDataFlags |= DATA_CMD_LIST;
}

void Session_OnItemUseFlags(u32 data)
{
    struct JoyArgs *cmd = (struct JoyArgs *)&data;

    gItemUseFlags = cmd->arg;
}

void Session_OnSpMode(u32 data)
{
    struct JoyArgs *cmd = (struct JoyArgs *)&data;

    gSpMode = cmd->arg;
}

void Session_OnCmdNum(u32 data)
{
    struct JoyArgs *cmd = (struct JoyArgs *)&data;
    s32 old = gSession.cmdSlotCount;

    if (old == cmd->arg)
        return;
    gSession.cmdSlotCount = cmd->arg;
    gSession.cmdSlots[gSession.cmdSlotCount] = 0xFFFF;
    if (old < cmd->arg && gScreen == 1)
        CmdListScreen_AddSlot();
}

void Session_OnMemories(u32 data)
{
    struct JoyArgs *cmd = (struct JoyArgs *)&data;

    gSession.memories = (u8)cmd->arg;
    if ((u32)gScreen <= 3)
        StatusWin_Refresh(0);
}

void Session_OnStartBonus(void)
{
    s32 i;

    for (i = 0; i < 4; i++)
        gParty[i].hp = 1;
}

void Session_OnLanguage(u32 data)
{
    struct JoyArgs *cmd = (struct JoyArgs *)&data;

    gLanguage = cmd->arg;
}
