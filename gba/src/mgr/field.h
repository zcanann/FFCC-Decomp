#ifndef GUARD_FIELD_H
#define GUARD_FIELD_H

#include "global.h"

#define FIELD_SIZE 256

/* Race course: tile map rendered as a mode 7 floor on BG2 */
struct Field {
    u8 (*map)[FIELD_SIZE];
    s16 depth[160];
    s16 scale[160];
};

struct Terrain {
    u16 flags;
};

#define TERRAIN_WALL  1
#define TERRAIN_OPEN  2
#define TERRAIN_ROUGH 4

/* Per-scanline BG2 affine parameters */
struct BgAffine {
    vu16 pa;
    vu16 pb;
    vu16 pc;
    vu16 pd;
    s32 x;
    s32 y;
};

extern struct Field gField;
extern const struct Terrain gTerrainTable[];
#define gFieldMap (*(u8 (*)[FIELD_SIZE][FIELD_SIZE])0x02030000)
extern const u8 gFieldMapLz[];
extern const u8 gFieldTilesLz[];
extern const u8 gSkyTilesLz[];
extern const u8 gBgPalette[];
extern const u8 gSelectBgMapLz[];
extern const u8 gSelectScreenLz[];

static inline const struct Terrain *GetTerrain(struct Field *field, s32 x, s32 z)
{
    return &gTerrainTable[field->map[z >> 7][x >> 7]];
}

void Field_Init(struct Field *field);
void Field_SetupRaceBg(struct Field *field);
void Field_SetupMenuBg(struct Field *field);
void Camera_RayFloor(struct Field *field, struct Vec3 *pos, struct Vec3 *dir, struct Vec3 *out);
void Floor_BuildDepths(struct Field *field);
void Field_UpdateMap(struct Field *field);
void Mode7_UpdateAffine(struct Field *field);
u8 Field_CheckWall(struct Field *field, struct Vec3 *pos, struct Vec3 *vel, s16 *speed);
u8 Field_CheckGround(struct Field *field, struct Vec3 *pos, struct Vec3 *vel, s16 *speed);
u8 Field_CheckWallAI(struct Field *field, struct Vec3 *pos, struct Vec3 *vel, s16 *speed);

#endif
