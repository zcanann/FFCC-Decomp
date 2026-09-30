#include "gba_types.h"

#define REG_DMA3 ((vu32 *)0x040000D4)

#define DmaSet3(src, dest, control)       \
    {                                     \
        vu32 *dmaRegs = REG_DMA3;         \
        dmaRegs[0] = (vu32)(src);         \
        dmaRegs[1] = (vu32)(dest);        \
        dmaRegs[2] = (vu32)(control);     \
        dmaRegs[2];                       \
    }

void *memset(void *dst, int c, u32 n);
void *memcpy(void *dst, const void *src, u32 n);
char *strcpy(char *dst, const char *src);
u32 strlen(const char *s);

struct Cmd {
    u8 unk0;
    u8 unk1;
    u16 unk2;
};

struct Cmd8 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
};

struct ObjEntry {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 *unk8;
};

struct GfxInfo {
    u8 unk0[12];
    u8 unkC;
    u8 unkD;
    u8 unkE[6];
    u8 *unk14;
    u8 *unk18;
    u8 *unk1C;
};

struct Work {
    s8 unk0;
    u8 unk1[3];
    u8 unk4[4];
    u8 unk8[4];
    char names[4][18];
    u8 unk54[8];
    u8 unk5C;
    u8 unk5D;
    u8 unk5E[4];
    u8 unk62[2];
    s16 unk64[64];
    s16 unkE4[8];
    u16 unkF4[8];
    union {
        u32 word;
        u8 bytes[4];
    } unk104;
    u8 unk108[12];
    u8 unk114[12];
    s16 unk120[4];
    u8 unk128;
    u8 unk129;
};

struct Member {
    void *unk0;
    u16 unk4;
    s8 unk6;
    s8 unk7;
};

struct MemberData {
    u8 entries[8][16];
    s8 slots[4];
};

struct MarkerEntry {
    u8 unk0;
    u8 unk1[3];
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u16 unkA;
};

struct MarkerList {
    u8 count;
    u32 unk4;
    struct MarkerEntry entries[32];
};

struct Flag3 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
};

extern u16 gDataFlags;
extern u8 gSpMode;
extern struct GfxInfo gObjHeader;
extern struct ObjEntry gObjCells[];
extern s16 lbl_0202FA20[];
extern u8 lbl_02036A30[][32];
extern u8 lbl_03002070[];
extern u8 lbl_03002738[];
extern u8 lbl_03002690;
extern u8 lbl_03001168[2][0x400];
extern struct Work gSession;
extern struct Member gParty[4];
extern struct MemberData gCaravanNames;
extern struct MarkerList gMapObjs;
extern char gBonusStr[2][65];
extern u8 gScouterHit[4];
extern s8 lbl_03002770;
extern u8 gRadarType;
extern u8 gRadarMode;
extern u8 gScouterDirty;
extern u8 gLanguage;
extern u16 gBasePos[2];
extern u16 gPrevBasePos[2];
extern u8 lbl_03003080[8];
extern struct Flag3 gPartyMarkers[4];
extern struct Flag3 gEnemyMarkers[64];
extern struct Flag3 gTreasureMarkers[16];
extern u32 sMapObjDrawFlagsIn;
extern u32 gScreen;
extern u32 gMode;
extern u32 gScreenPhase;
extern u8 gDetailBuf[];

int Link_GetPlayerNo(void);
u16 Crc16(s32 n, u8 *data, u16 *crc);
void *fn_0201A73C(int);
void fn_020007D8(s32);
void fn_02000990(void);
void fn_02000B98(void);
void Screen_Reset(void);
void fn_0200EB80(void);
void fn_0200F010(int);
void fn_02010F88(int);
void fn_02017E48(int);
void fn_02019310(int);
void fn_0201A6C8(int);
void fn_02009508(int);
void fn_0200A63C(void);

void Radar_ClearMarkers(void);
int Session_OnCompatibility(u8 *p);
int Item_GetCategory(int);
int Item_IsEquipped(int);

int fn_02004030(int idx, int pos)
{
    int sum;
    int i;
    struct ObjEntry *e;
    s8 *p;

    if (!(gDataFlags & 1))
        return 0;

    p = (s8 *)((u8 *)gObjCells + (gObjHeader.unk1C - gObjHeader.unk14));
    e = gObjCells;
    sum = 0;
    for (i = 0; i < idx; i++, e++)
        sum += e->unk1;
    sum += pos;
    p += sum >> 1;
    if (sum & 1)
        return *p & 0xF;
    else
        return *p >> 4;
}

void fn_02004098(int idx, int bank, int mode, int frame)
{
    struct ObjEntry *e;
    int size;
    u32 dest;
    u32 pal;
    u8 *src;

    if (idx == 17)
        frame = Link_GetPlayerNo();
    if (!(gDataFlags & 1))
        return;

    e = &gObjCells[idx];
    size = lbl_0202FA20[e->unk0] / 32 * 32;
    size *= e->unk1;
    if (bank == 0) {
        dest = 0;
        pal = 0x05000140;
    } else if (bank == 1) {
        dest = 0x400;
        pal = 0x05000160;
    } else if (bank == 2) {
        dest = 0x800;
        pal = 0x05000180;
    } else if (bank == 3) {
        dest = 0xC00;
        pal = 0x050001A0;
    } else {
        dest = 0x6000;
        pal = 0x050001C0;
    }
    if (frame < 0)
        pal = 0x05000020;
    dest += 0x80;
    if (mode <= 1)
        dest += 0x06000000;
    else
        dest += 0x06008000;
    DmaSet3(e->unk8, dest, 0x80000000 | (size >> 1));

    src = gSpMode == 0 ? (u8 *)gObjCells + (gObjHeader.unk18 - gObjHeader.unk14)
                            : lbl_02036A30[gObjHeader.unkD];
    if (frame < 0) {
        size = e->unk4 * 32;
        src += e->unk3 * 32;
    } else {
        size = 32;
        src += (e->unk3 + frame) * 32;
    }
    DmaSet3(src, pal, 0x80000000 | (size >> 1));
}

void fn_020041D4(int idx, int frame)
{
    struct ObjEntry *e;
    int count;
    u16 used;
    int i;
    u8 *src;
    u32 dest;

    if (idx == 17)
        frame = Link_GetPlayerNo();
    if (!(gDataFlags & 1))
        return;

    e = &gObjCells[idx];
    if (e->unk5)
        return;

    count = 1;
    if (frame < 0)
        count = e->unk4;

    used = 0;
    for (i = 3; i < gObjHeader.unkC; i++) {
        if (i != idx && gObjCells[i].unk5)
            used |= 1 << (gObjCells[i].unk2 >> 4);
    }

    e = &gObjCells[idx];
    for (i = gObjHeader.unkD; i <= 15; i++) {
        if (!((used >> i) & 1))
            break;
    }
    e->unk2 = (i << 4) | 1;
    e->unk5 = 1;

    src = gSpMode == 0 ? (u8 *)gObjCells + (gObjHeader.unk18 - gObjHeader.unk14)
                            : lbl_02036A30[gObjHeader.unkD];
    if (frame < 0)
        src += e->unk3 * 32;
    else
        src += (e->unk3 + frame) * 32;
    dest = 0x05000200 + i * 32;
    DmaSet3(src, dest, 0x80000000 | (count * 16));
    lbl_03002738[idx - 3] = count;
}

void fn_02004320(int idx)
{
    struct ObjEntry *e;

    if ((gDataFlags & 1) && idx > 2) {
        e = gObjCells;
        e += idx;
        e->unk2 = 0xFF;
        e->unk5 = 0;
        lbl_03002738[idx - 3] = 0;
    }
}

void fn_02004360(void)
{
    int i;

    for (i = 3; i <= 20; i++)
        fn_02004320(i);
    memset(lbl_03002738, 0, 18);
}

void fn_02004384(void)
{
    DmaSet3(lbl_03001168[(s8)(lbl_03002690 ^ 1)], 0x07000000, 0x84000100);
}

void fn_020043B8(void)
{
    u8 *src;
    int size;

    src = gSpMode == 0 ? lbl_03002070 : lbl_02036A30[0];
    size = gObjHeader.unkD * 32;
    DmaSet3(src, 0x05000200, 0x80000000 | (size >> 1));
}

void Session_Init(void)
{
    int i;

    memset(&gSession, 0, sizeof(gSession));
    memset(gParty, 0, sizeof(gParty));
    memset(&gCaravanNames, 0, sizeof(gCaravanNames));
    memset(&gMapObjs, 0, sizeof(gMapObjs));
    memset(gBonusStr, 0, sizeof(gBonusStr));
    memset(gScouterHit, 0xFF, sizeof(gScouterHit));
    lbl_03002770 = 0;
    gRadarType = 1;
    gRadarMode = 1;
    gScouterDirty = 0;
    gLanguage = 0;
    for (i = 0; i < 2; i++) {
        gBasePos[i] = 0;
        gPrevBasePos[i] = 0;
    }
    for (i = 0; i < 8; i++)
        lbl_03003080[i] |= 0xFF;
    for (i = 0; i < 4; i++)
        gParty[i].unk0 = fn_0201A73C(0);
    for (i = 0; i < 8; i++)
        gSession.unkF4[i] |= 0xFFFF;
    gSession.unk5D = 8;
    for (i = 0; i < 4; i++)
        gSession.unk5E[i] |= 0xFF;
    Radar_ClearMarkers();
}

void Session_OnItemChange(u32 data)
{
    struct Cmd *cmd = (struct Cmd *)&data;
    u8 type = cmd->unk0 & 0xC0;
    u8 idx = cmd->unk1 & 0x3F;
    s16 val = cmd->unk2;

    if (type != 0)
        return;

    gSession.unk64[idx] = val;
    if (gMode == 0) {
        if (gScreen == 1)
            fn_0200EB80();
        else if (gScreen == 2 && gScreenPhase == 1)
            fn_02010F88(idx);
    } else if (gMode == 2) {
        if (gScreen == 2 && gScreenPhase == 1)
            fn_02017E48(idx);
    } else if (gMode == 3) {
        if (val > 0)
            fn_02019310(idx);
    }
}

void Radar_SetBasePos(u16 x, u16 y)
{
    gBasePos[0] = x;
    gBasePos[1] = y;
    if (!(gDataFlags & 0x400)) {
        gDataFlags |= 0x400;
        gPrevBasePos[0] = x;
        gPrevBasePos[1] = y;
    }
}

void Radar_GetBasePos(u16 *x, u16 *y)
{
    *x = gBasePos[0];
    *y = gBasePos[1];
}

void Radar_GetBaseDelta(u16 *dx, u16 *dy)
{
    u16 flag = gDataFlags & 0x400;

    if (!flag) {
        *dx = flag;
        *dy = flag;
        gPrevBasePos[0] = gBasePos[0];
        gPrevBasePos[1] = gBasePos[1];
    } else {
        *dx = gBasePos[0] - gPrevBasePos[0];
        *dy = gBasePos[1] - gPrevBasePos[1];
        gPrevBasePos[0] = gBasePos[0];
        gPrevBasePos[1] = gBasePos[1];
    }
}

void Radar_ClearMarkers(void)
{
    memset(gPartyMarkers, 0, sizeof(gPartyMarkers));
    memset(gEnemyMarkers, 0, sizeof(gEnemyMarkers));
    memset(gTreasureMarkers, 0, sizeof(gTreasureMarkers));
}

void Radar_OnPartyPos(s8 *p)
{
    struct Flag3 *e = gPartyMarkers;
    u8 flags = p[1];

    e[0].unk0 = p[1] & 1;
    e[0].unk1 = p[2];
    e[0].unk2 = p[3];
    p += 4;
    e[1].unk0 = (flags >> 1) & 1;
    e[1].unk1 = p[1];
    e[1].unk2 = p[2];
    e[2].unk0 = (flags >> 2) & 1;
    e[2].unk1 = p[3];
    p += 4;
    e[2].unk2 = p[1];
    e[3].unk0 = (flags >> 3) & 1;
    e[3].unk1 = p[2];
    e[3].unk2 = p[3];
}

struct Flag3 *Radar_GetPartyMarker(int idx)
{
    return &gPartyMarkers[idx];
}

void Radar_OnEnemyPos(s8 *p)
{
    int idx = p[1] & 0x7F;

    gEnemyMarkers[idx].unk0 = p[1] >> 7;
    gEnemyMarkers[idx].unk1 = p[2];
    gEnemyMarkers[idx].unk2 = p[3];
}

void Radar_OnTreasurePos(s8 *p)
{
    int idx = (p[1] & 0x7F) - 64;

    gTreasureMarkers[idx].unk0 = p[1] >> 7;
    gTreasureMarkers[idx].unk1 = p[2];
    gTreasureMarkers[idx].unk2 = p[3];
}

void Session_OnPlayerStat(u8 *p)
{
    int i;
    int n;
    u8 *dst;

    memset(&gSession, 0, sizeof(gSession));
    memset(gParty, 0, sizeof(gParty));
    memset(gSession.unk64, 0xFF, sizeof(gSession.unk64));
    memset(gSession.unkE4, 0xFF, sizeof(gSession.unkE4));
    memset(gSession.unk5E, 0xFF, sizeof(gSession.unk5E));
    for (i = 0; i < 4; i++) {
        gParty[i].unk4 |= 0xFFFF;
        gParty[i].unk0 = fn_0201A73C(0);
    }

    memcpy(&gCaravanNames, p, sizeof(gCaravanNames));
    p += sizeof(gCaravanNames);
    for (i = 0; i < 8; i++) {
        n = gCaravanNames.slots[i >> 1];
        if (i & 1)
            n &= 15;
        else
            n = (n & 0xF0) >> 4;
        if (n != 15)
            gParty[n].unk4 = i;
    }
    for (i = 0; i < 4; i++) {
        n = (s16)gParty[i].unk4;
        if (n != -1)
            gParty[i].unk0 = gCaravanNames.entries[n];
        gParty[i].unk6 = p[0];
        gParty[i].unk7 = p[1];
        p += 2;
    }

    gSession.unk0 = *p++;
    memcpy(gSession.unk1, p, 3);
    p += 3;
    dst = gSession.unk62;
    for (i = 2; i != 0; i--)
        *dst++ = *p++;

    n = Session_OnCompatibility(p);
    p += n;
    memcpy(gSession.unk54, p, 8);
    p += 8;
    dst = gSession.unk104.bytes;
    for (i = 4; i != 0; i--)
        *dst++ = *p++;

    n = gSession.unk0 & 3;
    if (n != lbl_03002770) {
        fn_020007D8(n);
        lbl_03002770 = n;
    }
    if (gScreen <= 5) {
        Screen_Reset();
        fn_02000990();
    }
}

void Session_OnPartyHp(s8 *p)
{
    int i;
    struct Member *m;

    for (i = 0, m = gParty; i < 4; m++, i++) {
        if (i == Link_GetPlayerNo()) {
            if ((p[1] & 0x80) && m->unk7 > p[2])
                fn_02000B98();
            m->unk7 = p[2];
        } else if ((p[1] >> i) & 1) {
            m->unk7 = m->unk6;
        } else {
            m->unk7 = 0;
        }
    }
    gSession.unk128 = p[3];
}

void Radar_OnMapObj(u8 *p)
{
    int i;
    u32 val;
    struct MarkerEntry *e;

    memset(&gMapObjs, 0, sizeof(gMapObjs));
    gMapObjs.count = *p++;
    val = p[0];
    val |= p[1] << 8;
    val |= p[2] << 16;
    val |= p[3] << 24;
    p += 4;
    gMapObjs.unk4 = val;
    for (i = 0; i < gMapObjs.count; i++) {
        e = &gMapObjs.entries[i];
        e->unk0 = *p++;
        e->unk4 = *p++;
        e->unk4 |= *p++ << 8;
        e->unk6 = *p++;
        e->unk6 |= *p++ << 8;
        e->unk8 = *p++;
        e->unk8 |= *p++ << 8;
        e->unkA = *p++;
        e->unkA |= *p++ << 8;
    }
}

void Radar_OnMapObjDrawFlags(u8 *p)
{
    u8 *prev;
    u16 sum;
    u16 crc;
    u32 val;

    if ((p[0] >> 6) == 0) {
        sMapObjDrawFlagsIn = *(u32 *)p;
        return;
    }
    prev = (u8 *)&sMapObjDrawFlagsIn;
    sum = prev[1] | (prev[2] << 8);
    val = prev[3];
    val |= p[1] << 8;
    val |= p[2] << 16;
    val |= p[3] << 24;
    crc = 0xFFFF;
    if (Crc16(4, (u8 *)&val, &crc) == sum)
        gMapObjs.unk4 = val;
}

void Session_OnItemAll(u8 *p)
{
    int i;

    memcpy(gSession.unk64, p, sizeof(gSession.unk64));
    p += sizeof(gSession.unk64);
    memcpy(gSession.unk114, gSession.unk108, 12);
    memcpy(gSession.unk108, p, 12);
    p += 12;
    memcpy(gSession.unk120, p, 8);
    p += 8;
    for (i = 0; i < 4; i++)
        gSession.unk5E[i] = *p++;
    memcpy(gSession.unkF4, p, 16);
    gSession.unk5D = p[16];
}

void Session_OnFavorite(u8 *p)
{
    memcpy(gSession.unk54, p, 8);
}

void Session_SetGil(u32 val)
{
    gSession.unk104.word = val;
}

int Session_OnCompatibility(u8 *p)
{
    int n;
    int size;
    int i;
    int len;

    gSession.unk129 = *p++;
    n = *p++;
    size = 2;
    memset(gSession.unk4, 0, 8);
    memset(gSession.names, 0, sizeof(gSession.names));
    for (i = 0; i < n; i++) {
        gSession.unk4[i] = *p++;
        gSession.unk8[i] = *p++;
    }
    size += n * 2;
    for (i = 0; i < n; i++) {
        len = strlen(p);
        strcpy(gSession.names[i], p);
        p += len + 1;
        size += len + 1;
    }
    return size;
}

void Session_OnEquipList(u8 *p)
{
    int i;
    int size;
    int n;

    for (i = 0; i < 4; i++)
        gSession.unk5E[i] = *p++;
    n = *p;
    size = n + 1;
    if (size & 3)
        size = ((size >> 2) + 1) << 2;
    size += n * 8;
    memcpy(gDetailBuf, p, size);
    gDataFlags |= 0x10;
}

void Session_OnEquipSlot(u32 data)
{
    struct Cmd8 *cmd = (struct Cmd8 *)&data;
    u8 idx = cmd->unk1;
    u8 val = cmd->unk2;

    gSession.unk5E[idx] = val;
}

void Session_OnCmdSlot(u32 data)
{
    struct Cmd *cmd = (struct Cmd *)&data;
    s8 idx = cmd->unk1;
    u16 val = cmd->unk2;

    gSession.unkF4[idx] = val;
    if (gScreen == 1)
        fn_0200F010(idx);
    else if (gScreen == 2)
        fn_02010F88((s16)val);
}

void Session_OnTmpArtifact(u32 data)
{
    struct Cmd8 *cmd = (struct Cmd8 *)&data;
    u8 idx = cmd->unk1;
    u8 val = cmd->unk2;

    gSession.unk120[idx] = (val != 0xFF) ? val + 159 : -1;
    if (gScreen == 1)
        fn_0200EB80();
    else if (gScreen == 5)
        fn_0201A6C8(idx);
}

void Session_OnBonusStr(char *s)
{
    memset(gBonusStr, 0, sizeof(gBonusStr));
    strcpy(gBonusStr[0], s);
    s += strlen(s);
    s++;
    strcpy(gBonusStr[1], s);
}

int fn_02004CAC(int idx)
{
    return Item_GetCategory(gSession.unk64[idx]);
}

int Item_GetCategory(int val)
{
    int level;

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

int fn_02004D3C(int id)
{
    int i;

    if (id < 64 && gSession.unk64[id] <= 0)
        return 0;
    for (i = 2; i < 8; i++) {
        if ((s16)gSession.unkF4[i] == id)
            return 1;
    }
    if (id < 64)
        return Item_IsEquipped(id);
    return 0;
}

void Session_OnUseItem(u32 data)
{
    struct Cmd8 *cmd = (struct Cmd8 *)&data;

    gSession.unk5C = cmd->unk2;
}

int Item_CanEquip(u16 *p)
{
    int a = *p & 0xF;
    int b = *p & 0x30;
    int mask = 1 << (gSession.unk0 & 3);
    int mask2 = (gSession.unk0 & 0x80) ? 32 : 16;

    if (a) {
        if (b) {
            a &= mask;
            return a && (b & mask2);
        }
        return (a & mask) != 0;
    }
    return (b & mask2) != 0;
}

int Item_IsEquipped(int id)
{
    int i;

    for (i = 0; i < 4; i++) {
        if ((s8)gSession.unk5E[i] == id)
            break;
    }
    return i < 4;
}

void Session_OnStrength(u32 data)
{
    struct Cmd8 *cmd = (struct Cmd8 *)&data;
    int i;
    u8 *p = &cmd->unk1;

    for (i = 0; i < 3; i++)
        gSession.unk1[i] = *p++;
    if (gScreen <= 3)
        fn_02009508(0);
}

int fn_02004E74(int id)
{
    if (id == 9 || id == 10 || id == 12)
        return -1;
    return 0;
}

void Session_OnArtifacts(u8 *p)
{
    memcpy(gSession.unk114, gSession.unk108, 12);
    memcpy(gSession.unk108, p, 12);
    if (gScreen == 4)
        fn_0200A63C();
    else if (gScreen == 1)
        fn_0200EB80();
}

void Session_OnTmpArtifacts(u8 *p)
{
    memcpy(gSession.unk120, p, 8);
}
