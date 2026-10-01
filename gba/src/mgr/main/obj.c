#include "global.h"
#include "main.h"
#include "joybus.h"
#include "obj.h"
#include "effect.h"
#include "camera.h"
#include "fixmath.h"
#include "chunk.h"
#include "sound.h"

const char gObjFileName[] = "C:/FFF/miniGame/mgr/obj.cpp";

struct Scenery gScenery[48];
u8 gEngineSong;
u8 gSkidSong;

#define ANIM_COUNT 72

void Scenery_Draw(struct Scenery *s)
{
    Sprite_Draw3D(&gGame, s->animNo, &s->pos);
}

void Game_Reset(struct Game *game)
{
    u32 zero;

    game->activeCount = 0;
    game->playerCount = 0;
    game->enemyCount = 0;
    zero = 0;
    CpuFastSet(&zero, game->effects, 0x01000000 | (sizeof(game->effects) / 4));
    zero = 0;
    CpuFastSet(&zero, game->actors, 0x01000000 | (sizeof(game->actors) / 4));
    AnimState_Set(&game->markers[0], 46, 255);
    AnimState_Set(&game->markers[1], 50, 255);
}

void Game_Init(struct Game *game)
{
    struct Chunk reader;
    struct ChunkHeader hdr;
    struct OamData *oam;
    struct Cell *cell;
    struct OamMatrix *matrix;
    struct Scenery *scenery;
    const struct SceneryDef *def;
    u32 i;
    s32 j;
    s32 k;
    u32 m;
    s32 n;
    u16 scale;
    s32 x;
    s32 y;
    s32 z;
    s32 animNo;

    LZ77UnCompWram(gObjTilesLz, gDecompBuffer);
    DmaSet(gDecompBuffer, VRAM + 0x10000, 0x84002000);
    LZ77UnCompWram(gObjPaletteLz, gDecompBuffer);
    DmaSet(gDecompBuffer, PLTT + 0x200, 0x84000080);
    Chunk_Construct(&reader);
    Chunk_SetBuffer(&reader, gObjData);
    while (Chunk_Next(&reader, &hdr)) {
        switch (hdr.id) {
        case CHUNK_ID('O', 'B', 'J', ' '):
            game->cellTable = Chunk_GetData(&reader);
            for (i = 0; i < game->cellTable->count; i++) {
                game->cellTable->entries[i] = (u8 *)game->cellTable + (u32)game->cellTable->entries[i];
                cell = game->cellTable->entries[i];
                for (k = cell->count - 1; k >= 0; k--) {
                    oam = &cell->oams[k];
                    if (oam->objMode == 1) {
                        oam->priority = 2;
                    } else {
                        oam->priority = 1;
                    }
                }
            }
            break;
        case CHUNK_ID('A', 'N', 'I', 'M'):
            game->animTable = Chunk_GetData(&reader);
            for (m = 0; m < game->animTable->count; m++) {
                game->animTable->entries[m] = (u8 *)game->animTable + (u32)game->animTable->entries[m];
            }
            break;
        }
    }
    game->enemyCount = 0;
    game->playerCount = 0;
    game->activeCount = 0;
    DmaFill32(0, gOamMatrices, 0x85000000 | (sizeof(struct OamMatrix) * 32 / 4));
    matrix = gOamMatrices;
    for (j = 0; j < 28; j++) {
        scale = (0x100 - gSinTable[((j << 14) / 26 + 0x4000) >> 5]) * 2 + 0x100;
        matrix->pd = scale;
        matrix->pa = scale;
        matrix++;
    }
    matrix->pd = 224;
    matrix->pa = 224;
    matrix++;
    matrix->pd = 192;
    matrix->pa = 192;
    matrix++;
    matrix->pd = 160;
    matrix->pa = 160;
    matrix++;
    matrix->pd = 128;
    matrix->pa = 128;
    scenery = gScenery;
    for (n = 0; n < gSceneryCount; n++, scenery++) {
        def = &gSceneryDefs[n];
        if (def->animNo >= ANIM_COUNT) {
            AssertFailed(gObjFileName, 1633);
        }
        x = def->x;
        y = def->y;
        z = def->z;
        animNo = def->animNo;
        scenery->pos.x = x;
        scenery->pos.y = y;
        scenery->pos.z = z;
        scenery->animNo = animNo;
        scenery->unused2 = 0;
    }
    Game_Reset(game);
    gMain.oamDirty = 0;
    gEngineSong = SONG_NONE;
    gSkidSong = SONG_NONE;
}

/* Pushes two overlapping racers apart */
void Game_CollideRacer(struct Game *game, struct Vec3 *pos, struct Actor *actor)
{
    struct Actor *other;
    s16 dx;
    s16 dz;
    s16 vx;
    s16 vz;
    s16 dist;
    s16 speed;
    s16 px;
    s16 pz;

    other = Game_HitTest(game, pos, 100, -2 << actor->id);
    if (other != NULL) {
        if (actor->id == gPlayerNo || other->id == gPlayerNo) {
            m4aSongNumStart(SE_BUMP);
        }
        dx = other->pos.x - actor->pos.x;
        dz = other->pos.z - actor->pos.z;
        vx = actor->vel.x - other->vel.x;
        vz = actor->vel.z - other->vel.z;
        dist = Sqrt(dx * dx + dz * dz);
        speed = Sqrt(vx * vx + vz * vz);
        px = dx * speed / dist;
        pz = dz * speed / dist;
        other->vel.x += px;
        other->vel.z += pz;
        actor->vel.x -= px;
        actor->vel.z -= pz;
    }
}

/* Returns the first active actor in mask whose box overlaps the one around pos */
struct Actor *Game_HitTest(struct Game *game, struct Vec3 *pos, u8 size, u32 mask)
{
    struct Actor *actor;
    s32 i;
    u32 bit;
    s16 minX;
    s16 minY;
    s16 minZ;
    s16 maxX;
    s16 maxY;
    s16 maxZ;
    s16 lo;
    s16 hi;

    actor = game->actors;
    minX = pos->x - size;
    minY = pos->y - size;
    minZ = pos->z - size;
    maxX = pos->x + size;
    maxY = pos->y + size;
    maxZ = pos->z + size;
    bit = 1;
    for (i = 0; i < game->actorCount; i++, actor++, bit <<= 1) {
        if (actor->active && (mask & bit)) {
            lo = actor->pos.x - size;
            hi = actor->pos.x + size;
            if (minX < lo ? lo <= maxX : minX <= lo || minX <= hi) {
                lo = actor->pos.z - size;
                hi = actor->pos.z + size;
                if (minZ < lo ? lo <= maxZ : minZ <= lo || minZ <= hi) {
                    lo = actor->pos.y - size;
                    hi = actor->pos.y + size;
                    if (minY < lo ? lo <= maxY : minY <= lo || minY <= hi) {
                        return actor;
                    }
                }
            }
        }
    }
    return NULL;
}

struct Actor *Game_FindNearest(struct Game *game, struct Vec3 *pos, s32 range, s32 *outDist, u32 mask)
{
    struct Actor *actor;
    struct Actor *nearest;
    s32 i;
    u32 bit;
    s32 min;
    s16 dx;
    s16 dy;
    s32 dist;
    s16 x;
    s16 y;

    min = -range;
    actor = game->actors;
    nearest = NULL;
    bit = 1;
    x = pos->x;
    y = pos->z;
    for (i = 0; i < game->actorCount; i++, actor++, bit <<= 1) {
        if (actor->active && (mask & bit)) {
            dx = actor->pos.x - x;
            if (dx < range && dx > min) {
                dy = actor->pos.z - y;
                if (dy < range && dy > min) {
                    dist = dx * dx + dy * dy;
                    if (dist < range && range > dist) {
                        range = dist;
                        min = -range;
                        nearest = actor;
                    }
                }
            }
        }
    }
    *outDist = range;
    return nearest;
}

/* Nearest actor in mask within range that lies in front of (dirX, dirZ) */
struct Actor *Game_FindTarget(struct Game *game, struct Vec3 *pos, s32 range, u16 *outDist, s16 dirX, s16 dirZ, s16 minDot, u32 mask)
{
    struct Actor *nearest;
    struct Actor *actor;
    u32 bit;
    s16 x;
    s16 y;
    s32 i;
    s32 min;
    s16 dx;
    s16 dz;
    s32 dist;
    u16 root;
    s16 dot;

    min = -range;
    actor = game->actors;
    nearest = NULL;
    bit = 1;
    x = pos->x;
    y = pos->z;
    for (i = 0; i < game->actorCount; i++, actor++, bit <<= 1) {
        if (actor->active && (mask & bit)) {
            dx = actor->pos.x - x;
            if (dx < range && dx > min) {
                dz = actor->pos.z - y;
                if (dz < range && dz > min) {
                    dist = dx * dx + dz * dz;
                    if (dist < range && range > dist) {
                        root = Sqrt(dist);
                        dot = (dirX * dx + dirZ * dz) / (s16)root;
                        if (dot >= minDot) {
                            *outDist = root;
                            range = dist;
                            min = -range;
                            nearest = actor;
                        }
                    }
                }
            }
        }
    }
    return nearest;
}

u8 Game_GetRank(struct Game *game, s32 no)
{
    struct Actor *actor;
    u16 progress;
    u8 rank;
    s32 i;

    progress = Racer_GetProgress(&game->actors[no]);
    actor = game->actors;
    rank = 1;
    for (i = 0; i < game->actorCount; i++, actor++) {
        if (i != no && actor->active && Racer_GetProgress(actor) > progress) {
            rank++;
        }
    }
    return rank;
}

void Game_Update(struct Game *game)
{
    s32 i; s32 j;

    if (game->activeCount) {
        for (i = 0; i < 4; i++) {
            if ((gPlayerMask >> i) & 1) {
                Racer_UpdatePlayer(&game->actors[i]);
            }
        }
        for (j = 0; j < game->enemyCount; j++) {
            Racer_UpdateEnemy(&game->actors[4 + j]);
        }
    }
    for (j = 0; j < 64; j++) {
        if (game->effects[j].active) {
            Effect_Update(&game->effects[j]);
        }
    }
}

void Game_Draw(struct Game *game)
{
    s32 i;
    struct Scenery *scenery;
    u16 count;

    if (game->activeCount) {
        for (i = 0; i < 4; i++) {
            if ((gPlayerMask >> i) & 1) {
                Racer_Draw(&game->actors[i]);
            }
        }
        for (i = 0; i < game->enemyCount; i++) {
            Racer_UpdateAnimDir(&game->actors[4 + i]);
            Obj_Draw((struct Obj *)&game->actors[4 + i]);
        }
    }
    for (i = 0; i < 64; i++) {
        if (game->effects[i].active && game->effects[i].visible) {
            Obj_Draw((struct Obj *)&game->effects[i]);
        }
    }
    scenery = gScenery;
    count = gSceneryCount;
    for (i = 0; i < count; i++, scenery++) {
        Scenery_Draw(scenery);
    }
}

void Oam_Clear(struct Game *game)
{
    s16 i;

    DmaFill32(160, gOamBuffer, 0x85000100);
    for (i = 0; i < 40; i++) {
        game->oamLists[i] = NULL;
    }
    game->freeNode = game->oamNodes;
}

/* Copies the sorted sprite lists and the affine matrices to the OAM buffer */
void Oam_Flush(struct Game *game)
{
    struct OamNode *node;
    struct OamData *oam;
    struct OamMatrix *matrix;
    s16 count;
    s16 i;
    s16 j;

    count = 0;
    for (i = 0; i < 40; i++) {
        for (node = game->oamLists[i]; node != NULL; node = node->next) {
            oam = &gOamBuffer[count++];
            DmaSet(&node->oam, oam, 0x84000002);
        }
    }
    oam = gOamBuffer;
    do {
        matrix = gOamMatrices;
    } while (0);
    for (j = 0; j < 32; j++, matrix++) {
        oam->affineParam = matrix->pa;
        oam++;
        oam->affineParam = matrix->pb;
        oam++;
        oam->affineParam = matrix->pc;
        oam++;
        oam->affineParam = matrix->pd;
        oam++;
    }
    gMain.oamDirty = 1;
}

void Oam_AddNode(struct Game *game, struct OamNode *node, u16 prio)
{
    if (prio >= 40) {
        AssertFailed(gObjFileName, 1999);
    }
    node->next = game->oamLists[prio];
    game->oamLists[prio] = node;
}

struct OamNode *Oam_AllocNode(struct Game *game, struct OamData *oam)
{
    struct OamNode *node;

    if (game->freeNode >= &game->oamNodes[128]) {
        AssertFailed(gObjFileName, 2010);
    }
    node = game->freeNode++;
    DmaSet(oam, &node->oam, 0x84000002);
    return node;
}

static inline struct Anim *GetAnim(struct Game *game, u16 no)
{
    return game->animTable->entries[no];
}

static inline struct AnimFrame *GetFrame(struct Anim *anim, u8 no)
{
    return &anim->frames[no];
}

static inline struct Cell *GetCell(struct Game *game, u16 no)
{
    return game->cellTable->entries[no];
}

void Sprite_DrawAnim(struct Game *game, struct AnimState *anim, struct Point *pos, s16 prio)
{
    struct Cell *cell;
    s32 i;
    struct OamNode *node;

    if (anim->id >= ANIM_COUNT)
        AssertFailed(gObjFileName, 2023);
    if (anim->frame >= 127)
        AssertFailed(gObjFileName, 2024);
    cell = GetCell(game, GetFrame(GetAnim(game, anim->id), anim->frame)->cell);
    for (i = 0; i < cell->count; i++) {
        node = Oam_AllocNode(game, &cell->oams[i]);
        if (prio < 0) {
            node->oam.affineMode = 3;
            node->oam.matrixNum = 28 - prio;
            prio = 0;
        }
        node->oam.y += pos->y;
        node->oam.x += pos->x;
        Oam_AddNode(game, node, prio);
    }
}

void Sprite_Draw(struct Game *game, s16 animNo, struct Point *pos, s16 prio)
{
    struct Cell *cell;
    s32 i;
    struct OamNode *node;

    if (animNo >= ANIM_COUNT)
        AssertFailed(gObjFileName, 2057);
    cell = GetCell(game, GetAnim(game, animNo)->frames[0].cell);
    for (i = cell->count - 1; i >= 0; i--) {
        node = Oam_AllocNode(game, &cell->oams[i]);
        node->oam.y += pos->y;
        node->oam.x += pos->x;
        if (prio < 0) {
            node->oam.affineMode = 3;
            node->oam.matrixNum = 28 - prio;
            prio = 0;
        }
        Oam_AddNode(game, node, prio);
    }
}

/* pos->z holds the depth level, which selects the scaling matrix */
void Sprite_DrawAnimScaled(struct Game *game, struct AnimState *anim, struct Vec3 *pos)
{
    struct Cell *cell;
    s32 i;
    struct OamNode *node;
    u8 scale;
    struct OamMatrix *mtx;

    if (anim->id >= ANIM_COUNT)
        AssertFailed(gObjFileName, 2087);
    if (anim->frame >= 127)
        AssertFailed(gObjFileName, 2088);
    scale = pos->z;
    if (scale < 28) {
        cell = GetCell(game, GetFrame(GetAnim(game, anim->id), anim->frame)->cell);
        for (i = cell->count - 1; i >= 0; i--) {
            mtx = &gOamMatrices[scale];
            node = Oam_AllocNode(game, &cell->oams[i]);
            node->oam.matrixNum = scale;
            node->oam.x += pos->x;
            node->oam.y = pos->y + (node->oam.y << 8) / ((mtx->pd >> 2) + 192);
            node->oam.affineMode = 1;
            if (anim->palette != 0xFF)
                node->oam.paletteNum = anim->palette;
            Oam_AddNode(game, node, pos->z + 8);
        }
    }
}

void Sprite_DrawScaled(game, animNo, pos)
    struct Game *game;
    u16 animNo;
    struct Vec3 *pos;
{
    struct Cell *cell;
    struct OamNode *node;
    u8 scale;
    struct OamMatrix *mtx;
    s16 no;

    scale = pos->z;
    if (scale < 28) {
        no = animNo;
        if (no >= ANIM_COUNT)
            AssertFailed(gObjFileName, 2148);
        cell = GetCell(game, GetAnim(game, no)->frames[0].cell);
        node = Oam_AllocNode(game, &cell->oams[0]);
        node->oam.matrixNum = scale;
        node->oam.x += pos->x;
        mtx = &gOamMatrices[scale];
        node->oam.y = pos->y + (node->oam.y << 8) / ((mtx->pd >> 2) + 192);
        node->oam.affineMode = 1;
        Oam_AddNode(game, node, pos->z + 8);
    }
}

void Sprite_DrawAnim3D(struct Game *game, struct AnimState *anim, struct Vec3 *pos)
{
    struct Vec3 screen;

    if (Camera_WorldToScreen(&gCamera, pos, &screen)) {
        if (screen.z >= 61 && screen.z < 0x4000 && (u16)(screen.x + 16) <= 272 && screen.y >= -16 && screen.y <= 176) {
            screen.z >>= 9;
            Sprite_DrawAnimScaled(game, anim, &screen);
        }
    }
}

void Sprite_Draw3D(struct Game *game, u16 animNo, struct Vec3 *pos)
{
    struct Vec3 screen;

    if (Camera_WorldToScreen(&gCamera, pos, &screen)) {
        if (screen.z >= 61 && screen.z < 0x4000 && (u16)(screen.x + 16) <= 272 && screen.y >= -16 && screen.y <= 176) {
            screen.z >>= 9;
            Sprite_DrawScaled(game, (s16)animNo, &screen);
        }
    }
}

static inline void Offset(struct Vec3 *pos, s16 dx, s16 dy)
{
    pos->x += dx;
    pos->y += dy;
}

/* Draws an unscaled sprite at the screen position of pos */
void Sprite_Draw3DOffset(game, animNo, pos, dx, dy, prio)
    struct Game *game;
    u16 animNo;
    struct Vec3 *pos;
    u16 dx;
    u16 dy;
    u16 prio;
{
    struct Vec3 screen;
    struct Point pt;

    if (Camera_WorldToScreen(&gCamera, pos, &screen)) {
        if (screen.z >= 61 && screen.z < 0x4000) {
            Offset(&screen, dx, dy);
            if ((u16)(screen.x + 16) <= 272 && screen.y >= -16 && screen.y <= 176) {
                pt.x = screen.x;
                (&pt)->y = screen.y;
                Sprite_Draw(game, (s16)animNo, &pt, (s16)prio);
            }
        }
    }
}

void Game_DrawChaserMarker(struct Game *game, u8 markerNo, u8 no, struct Actor *chaser)
{
    struct AnimState *marker;

    if (chaser != NULL) {
        marker = &game->markers[markerNo];
        if (markerNo == 0)
            AnimState_Change(marker, chaser->id + 46, 0xFF);
        AnimState_Update(marker);
        Racer_DrawChaserMarker(&game->actors[no], chaser, marker);
    }
}

u8 Game_IsWrongWay(struct Game *game, u8 no)
{
    return Racer_IsWrongWay(&game->actors[no]);
}

struct Actor *Game_FindChaser(struct Game *game, u8 no, u8 mode)
{
    return Racer_FindChaser(&game->actors[no], mode);
}

void Game_AddPlayer(struct Game *game, u8 no, u8 chara)
{
    Racer_InitPlayer(&game->actors[no], no, chara);
    game->activeCount++;
    game->playerCount++;
}

void Game_AddEnemies(struct Game *game, s32 count)
{
    s32 i;

    for (i = 0; i < count; i++) {
        Racer_InitEnemy(&game->actors[4 + i], i);
        game->activeCount++;
        game->enemyCount++;
    }
    game->actorCount = game->enemyCount + 4;
}

void Obj_StaticInit(void)
{
    s32 i;

    for (i = 47; i != -1; i--)
        ;
}
