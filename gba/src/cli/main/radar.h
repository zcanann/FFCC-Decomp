#ifndef GUARD_RADAR_H
#define GUARD_RADAR_H

#include "global.h"

/* Header of a downloaded background image (the radar map is one). */
struct BgHeader {
    u32 unk0;
    u32 unk4;
    u32 tileOffset;
    u32 mapOffset;
    u32 unk10;
    u16 width;
    u16 height;
    u32 unk18;
    u32 unk1C;
    u16 palette[16];
};

/* Party member, enemy or treasure position relative to the local player. */
struct Marker {
    s8 visible;
    s8 x;
    s8 y;
    s8 kind;
};

/* A map object, drawn as a dotted line between two points. */
struct MapObj {
    u8 type;
    u8 pad[3];
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
};

struct MapObjList {
    u8 count;
    u32 drawFlags;
    struct MapObj entries[32];
};

/* Enemy last hit, as reported by cmd 34. */
struct ScouterHit {
    s8 enemy;
    u8 pad;
    s16 hp;
};

/* Scouter record (message 11), 64 of them at the start of LIST_BUF. */
struct ScouterInfo {
    u8 monster;
    s8 traits[3];
    s16 maxHp;
    s16 dropItem;
};

extern struct Marker gEnemyMarkers[64];
extern struct Marker gTreasureMarkers[16];
extern struct MapObjList gMapObjs;
extern struct ScouterHit gScouterHit;
extern s8 gScouterDirty;
extern u8 gRadarType;
extern u8 gRadarMode;

void Bg_LoadMapLz(struct BgHeader *hdr);
void Bg_SetBlend(s32 on);
void Radar_ClearMap(void);
void Radar_InitMap(void);
void Radar_LoadPalette(void);
void Radar_DrawMap(void);
void Radar_ScrollMap(s32 dx, s32 dy);

void Radar_SetBasePos(s32 x, s32 y);
void Radar_GetBasePos(s16 *x, s16 *y);
void Radar_GetBaseDelta(s16 *dx, s16 *dy);
void Radar_ClearMarkers(void);
void Radar_OnPartyPos(s8 *p);
struct Marker *Radar_GetPartyMarker(s32 idx);
void Radar_OnEnemyPos(s8 *p);
void Radar_OnTreasurePos(s8 *p);
void Radar_OnMapObj(u8 *p);
void Radar_OnMapObjDrawFlags(u8 *p);
void Radar_OnMarkerKinds(u8 *p);
void Radar_OnType(u32 data);
void Radar_OnMode(u32 data);
void Scouter_OnInfo(u8 *p);
void Scouter_OnHitEnemy(u32 data);

void Radar_DrawMapObjs(void);
void Radar_DrawParty(void);
void Radar_DrawEnemies(void);
void Radar_DrawTreasures(void);
void Scouter_SetDirty(s32 active);

#endif
