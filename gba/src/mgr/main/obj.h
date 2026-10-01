#ifndef GUARD_OBJ_H
#define GUARD_OBJ_H

#include "global.h"

struct OamData {
    s32 y : 8;
    u32 affineMode : 2;
    u16 objMode : 2;
    u32 mosaic : 1;
    u32 bpp : 1;
    u32 shape : 2;
    s32 x : 9;
    u32 matrixNum : 5;
    u32 size : 2;
    u16 tileNum : 10;
    u16 priority : 2;
    u16 paletteNum : 4;
    u16 affineParam;
};

struct OamMatrix {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
};

struct OamNode {
    struct OamNode *next;
    struct OamData oam;
};

/* A sprite made of several OAM entries */
struct Cell {
    u16 count;
    struct OamData oams[0];
};

struct AnimFrame {
    u16 cell;
    u16 duration;
};

struct Anim {
    u16 width;
    u16 height;
    u16 count;
    struct AnimFrame frames[0];
};

/* Table loaded from the OBJ/ANIM chunks; entries are stored as offsets and
   relocated to pointers on load */
struct Table {
    u32 count;
    void *entries[0];
};

struct AnimState {
    u16 id;
    u16 timer;
    u16 duration;
    u8 frame;
    u8 palette;
    u8 loop : 1;
};

/* Common header of actors and effects */
#define OBJ_FIELDS            \
    struct Vec3 pos;          \
    u16 radius;               \
    u8 active;                \
    struct AnimState anim;

struct Obj {
    OBJ_FIELDS
};

struct ActorData {
    s16 accel;
    s16 brake;
    s16 decel;
    s16 grip;
    s16 maxSpeed;
    s16 turnAccel;
    s16 maxTurn;
    u8 aiRoute;
    u8 palette;
    u8 stats[4];
};

struct Actor {
    OBJ_FIELDS
    struct ActorData *data;
    u16 accel;
    u16 brake;
    s16 grip;
    u16 decel;
    u16 maxSpeed;
    u16 direction;
    s16 turnAccel;
    s16 turnSpeed;
    s16 maxTurn;
    u16 nodeDist;
    s16 spinAngle;
    u16 spinTimer;
    u16 speedEffectTimer;
    struct Vec3 vel;
    u16 speed;
    u16 heading;
    u16 facing;
    u16 skidCounter;
    s16 routePos;
    u8 progress;
    u8 routeNo;
    u8 routeIdx;
    u8 routeCount;
    u8 aiRouteNo;
    u8 aiRouteIdx;
    u8 aiRouteCount;
    s8 lap;
    u8 id;
    s8 item;
    u8 avoidSide;
    u8 frozen : 1;
    u8 slipping : 1;
    u8 boosted : 1;
    u8 slowed : 1;
    u8 showMarker : 1;
};

enum {
    ITEM_FREEZE,
    ITEM_SLIP,
    ITEM_TRAP,
    ITEM_COUNT,
    ITEM_NONE = 0xFF,
};

/* Panels show one of eight foods */
#define FOOD_COUNT 8

enum {
    EFFECT_ITEM_BOX,
    EFFECT_PANEL,
    EFFECT_FREEZE_TRAIL,
    EFFECT_FREEZE_SHOT,
    EFFECT_FREEZE,
    EFFECT_SLIP_TRAIL,
    EFFECT_SLIP_SHOT,
    EFFECT_SLIP,
    EFFECT_TRAP_THROW,
    EFFECT_TRAP,
    EFFECT_SPIN,
    EFFECT_DUST,
};

struct Effect {
    OBJ_FIELDS
    u8 type;
    u8 visible;
    u16 timer;
    union {
        struct {
            u16 wait;
            u8 kind;
        } box;
        struct {
            struct Actor *target;
            s16 targetDist;
            u8 ownerId;
            u8 routeNo;
            u8 routeIdx;
            struct Point vel;
        } shot;
        struct {
            struct Vec3 vel;
            u8 ownerId;
        } thrown;
        struct {
            s16 routePos;
            u8 progress;
            u8 ownerId;
        } trap;
        struct Actor *target;
        struct Point vel;
        u8 raw[32];
    } u;
};

/* Static decoration sprite placed on the course */
struct Scenery {
    struct Vec3 pos;
    u8 unused[4];
    u8 animNo;
    u8 unused2;
};

struct SceneryDef {
    s16 x;
    s16 y;
    s16 z;
    s16 animNo;
};

struct Game {
    struct Actor actors[12];
    struct Effect effects[64];
    struct AnimState markers[2];
    struct Table *cellTable;
    struct Table *animTable;
    struct OamNode *oamLists[40];
    struct OamNode oamNodes[128];
    struct OamNode *freeNode;
    u8 activeCount;
    u8 playerCount;
    u8 enemyCount;
    u8 actorCount;
};

extern struct Game gGame;
/* Fields of gGame referenced through their own symbols */
struct ActorU8 {
    u8 value;
    u8 pad[sizeof(struct Actor) - 1];
};

struct ActorS8 {
    s8 value;
    u8 pad[sizeof(struct Actor) - 1];
};

struct ActorU16 {
    u16 value;
    u8 pad[sizeof(struct Actor) - 2];
};

extern struct ActorU16 gActorHeading[];
extern struct ActorU8 gActorProgress[];
extern struct ActorS8 gActorLap[];
extern struct ActorU8 gActorFlags[];
#define ACTOR_FLAG_SHOW_MARKER 0x10
extern struct Effect gGameEffects[];
extern struct Table *gGameAnimTable;
extern u8 gGameActiveCount;
extern vu8 gGameEnemyCount;

extern struct OamData gOamBuffer[];
extern struct OamMatrix gOamMatrices[];
extern struct Scenery gScenery[];
extern const u16 gSceneryCount;
extern const struct SceneryDef gSceneryDefs[];
extern struct ActorData gPlayerData[];
extern struct ActorData gEnemyData[];
extern const u8 gCharaTable[];
extern const s16 gStartHeading;
/* Speed modifiers: [0] while boosted, [1] while slowed down */
extern const s16 gSpeedEffectMaxSpeed[2];
extern const s16 gSpeedEffectAccel[2];
extern const s16 gPanelSlowThreshold;
extern const s16 gPanelBoostThreshold;
extern const u16 gSpeedEffectDurations[];
extern const u8 gDirAnims[];
extern u8 gEngineSong;
extern u8 gSkidSong;
extern const char gObjFileName[];
extern const u8 gObjData[];
extern const u8 gObjTilesLz[];
extern const u8 gObjPaletteLz[];

/* anim / obj */
void AnimState_Clear(struct AnimState *anim);
void AnimState_Set(struct AnimState *anim, u16 id, u8 palette);
void AnimState_Change(struct AnimState *anim, u16 id, u8 palette);
u8 AnimState_Update(struct AnimState *anim);
void Obj_Init(struct Obj *obj);
void Obj_Update(struct Obj *obj);
void Obj_Reset(struct Obj *obj);
void Obj_Draw(struct Obj *obj);

/* racers */
void Racer_Reset(struct Actor *a);
void Racer_Finish(struct Actor *a);
u16 Racer_GetProgress(struct Actor *a);
struct Actor *Racer_FindChaser(struct Actor *a, u8 mode);
u8 Racer_FindObstacle(struct Actor *a, struct Vec3 *pos, u8 *progress, s16 *routePos, s16 *minSpeed, s16 *range, s16 *avoidDist, s32 *maxDistSq);
void Racer_UpdateProgress(struct Actor *a);
void Racer_InitParams(struct Actor *a);
void Racer_InitPlayer(struct Actor *a, u8 id, u8 chara);
void Racer_UpdateAnimDir(struct Actor *a);
void Racer_UpdatePlayer(struct Actor *a);
void Racer_Draw(struct Actor *a);
void Racer_DrawChaserMarker(struct Actor *a, struct Actor *chaser, struct AnimState *marker);
void Racer_InitEnemy(struct Actor *a, u8 no);
void Racer_UpdateEnemy(struct Actor *a);
s32 Racer_IsWrongWay(struct Actor *a);
void Racer_SetItem(struct Actor *a, u8 item);
void Racer_ApplyPanel(struct Actor *a, u8 food);

/* game */
void Scenery_Draw(struct Scenery *s);
void Game_Reset(struct Game *game);
void Game_Init(struct Game *game);
void Game_CollideRacer(struct Game *game, struct Vec3 *pos, struct Actor *a);
struct Actor *Game_HitTest(struct Game *game, struct Vec3 *pos, u8 size, u32 mask);
struct Actor *Game_FindNearest(struct Game *game, struct Vec3 *pos, s32 range, s32 *outDist, u32 mask);
struct Actor *Game_FindTarget(struct Game *game, struct Vec3 *pos, s32 range, u16 *outDist, s16 dirX, s16 dirZ, s16 minDot, u32 mask);
u8 Game_GetRank(struct Game *game, s32 no);
void Game_Update(struct Game *game);
void Game_Draw(struct Game *game);
void Game_DrawChaserMarker(struct Game *game, u8 markerNo, u8 no, struct Actor *chaser);
u8 Game_IsWrongWay(struct Game *game, u8 no);
struct Actor *Game_FindChaser(struct Game *game, u8 no, u8 mode);
void Game_AddPlayer(struct Game *game, u8 no, u8 chara);
void Game_AddEnemies(struct Game *game, s32 count);
void Obj_StaticInit(void);

/* sprites */
void Oam_Clear(struct Game *game);
void Oam_Flush(struct Game *game);
void Oam_AddNode(struct Game *game, struct OamNode *node, u16 prio);
struct OamNode *Oam_AllocNode(struct Game *game, struct OamData *oam);
void Sprite_DrawAnim(struct Game *game, struct AnimState *anim, struct Point *pos, s16 prio);
void Sprite_Draw(struct Game *game, s16 animNo, struct Point *pos, s16 prio);
void Sprite_DrawAnimScaled(struct Game *game, struct AnimState *anim, struct Vec3 *pos);
void Sprite_DrawScaled(struct Game *game, int animNo, struct Vec3 *pos);
void Sprite_DrawAnim3D(struct Game *game, struct AnimState *anim, struct Vec3 *pos);
void Sprite_Draw3D(struct Game *game, u16 animNo, struct Vec3 *pos);
void Sprite_Draw3DOffset(struct Game *game, int animNo, struct Vec3 *pos, int dx, int dy, int prio);

#endif
