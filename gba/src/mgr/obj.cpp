extern "C" {
#include "global.h"
#include "main.h"
#include "link.h"
#include "obj.h"
#include "effect.h"
#include "camera.h"
#include "field.h"
#include "route.h"
#include "sound.h"
#include "fixmath.h"
#include "chunk.h"

#define OBJ_FILE "C:/FFF/miniGame/mgr/obj.cpp"

u8 gDirAnims[] = { 4, 5, 26, 27, 0, 1, 2, 3 };

static inline struct Anim *GetAnim(struct Game *game, u16 no)
{
    return (struct Anim *)game->animTable->entries[no];
}

static inline struct AnimFrame *GetFrame(struct Anim *anim, u8 no)
{
    return &anim->frames[no];
}

static inline struct Cell *GetCell(struct Game *game, u16 no)
{
    return (struct Cell *)game->cellTable->entries[no];
}

void AnimState_Clear(struct AnimState *s)
{
    s->id = 0xFFFF;
    s->timer = 0;
    s->duration = 0;
    s->frame = 0;
    s->loop = 1;
}

void AnimState_Set(struct AnimState *s, u16 id, u8 palette)
{
    s->id = id;
    s->palette = palette;
    s->timer = 0;
    s->frame = 0;
    s->loop = 1;
    s->duration = (GetAnim(&gGame, s->id))->frames[0].duration;
}

void AnimState_Change(struct AnimState *s, u16 id, u8 palette)
{
    s->id = id;
    if (palette != 0xFF)
        s->palette = palette;
}

/* Returns 1 when the animation has played through */
u8 AnimState_Update(struct AnimState *s)
{
    struct Anim *anim;

    if ((s->timer += 2) >= s->duration) {
        s->timer = 0;
        s->frame++;
        anim = GetAnim(&gGame, s->id);
        if (s->frame >= anim->count) {
            if (s->loop)
                s->frame = 0;
            else
                s->frame--;
            s->duration = anim->frames[s->frame].duration;
            return 1;
        }
        s->duration = anim->frames[s->frame].duration;
    }
    return 0;
}

void Obj_Init(struct Obj *obj)
{
    obj->active = 1;
    obj->radius = 100;
}

void Obj_Update(struct Obj *obj)
{
}

void Obj_Reset(struct Obj *obj)
{
    Obj_Init(obj);
    AnimState_Clear(&obj->anim);
}

void Racer_Reset(struct Actor *a)
{
    s32 n;

    a->facing = 0;
    n = Route_Get(gRoutes, a->routeNo)->count;
    a->routeCount = n;
    a->routeIdx = n - 1;
    a->lap = -1;
    a->item = ITEM_NONE;
    a->skidCounter = 0;
    Obj_Reset((struct Obj *)a);
    a->radius = 100;
    a->speed = 0;
    a->slowed = 0;
    a->boosted = 0;
    a->slipping = 0;
    a->frozen = 0;
    a->avoidSide = 0;
    a->spinTimer = 0;
    a->speedEffectTimer = 0;
    a->showMarker = 0;
}

void Racer_Finish(struct Actor *a)
{
    s32 n;

    if (a->id <= 3) {
        a->aiRouteNo = 1;
        n = Route_Get(gRoutes, 1)->count;
        a->aiRouteCount = n;
        a->aiRouteIdx = n - 1;
    }
    RecordFinish(&gMain, a->id);
}

u16 Racer_GetProgress(struct Actor *a)
{
    return ((a->lap + 128) << 8) | a->progress;
}

/* Finds the racer (players or enemies, depending on mode) closest behind a */
struct Actor *Racer_FindChaser(struct Actor *a, u8 mode)
{
    s32 i;
    s32 start;
    s32 end;
    u32 mask;
    u16 key;
    u32 best;
    u16 k;
    struct Actor *other;
    struct Actor *result;

    if (mode == 0xFF) {
        start = 4;
        end = gGame.enemyCount + 4;
        mask = ~(1 << a->id);
    } else if (mode == 0) {
        start = 0;
        end = 4;
        mask = gPlayerMask & ~(1 << a->id);
    } else {
        start = 4;
        end = gGame.enemyCount + 4;
        mask = ~(1 << a->id);
    }
    key = Racer_GetProgress(a);
    best = 0;
    result = NULL;
    for (i = start; i < end; i++) {
        if ((1 << i) & mask) {
            other = &gGame.actors[(u8)i];
            k = Racer_GetProgress(other);
            if (k < key && best < k) {
                best = k;
                result = other;
            }
        }
    }
    return result;
}

/* Finds the nearest racer or trap ahead of a on the course, for the enemy AI to avoid */
u8 Racer_FindObstacle(struct Actor *a, struct Vec3 *pos, u8 *progress, s16 *routePos, s16 *minSpeed, s16 *range, s16 *avoidDist, s32 *maxDistSq)
{
    s32 n;
    u32 mask;
    s8 best;
    s8 d;
    struct Actor *found;
    struct Actor *other;
    struct Effect *trap;
    struct Effect *e;
    s32 i;
    s32 j;

    n = gGame.enemyCount + 4;
    mask = ~(1 << a->id);
    best = 0x7F;
    found = NULL;
    for (i = 0; i < n; i++) {
        if ((1 << i) & mask) {
            other = &gGame.actors[(u8)i];
            d = other->progress - a->progress;
            if (d >= 0 && best > d) {
                best = d;
                found = other;
            }
        }
    }
    e = gGame.effects;
    trap = NULL;
    /* the original steps 28 bytes instead of sizeof(struct Effect) */
    for (j = 0; j < 64; j++, e = (struct Effect *)((u8 *)e + 28)) {
        if (e->active && e->type == EFFECT_TRAP) {
            d = e->u.trap.progress - a->progress;
            if (d >= 0 && best > d) {
                best = d;
                trap = e;
                found = NULL;
            }
        }
    }
    if (trap != NULL) {
        *pos = trap->pos;
        *progress = trap->u.trap.progress;
        *routePos = trap->u.trap.routePos;
        *minSpeed = 0;
        *range = 1800;
        *avoidDist = 800;
        *maxDistSq = 64000000;
    } else if (found != NULL) {
        *pos = found->pos;
        *progress = found->progress;
        *routePos = found->routePos;
        *minSpeed = found->speed;
        *range = 1000;
        *avoidDist = 400;
        *maxDistSq = 25000000;
    } else {
        return 0;
    }
    return 1;
}

void Racer_UpdateProgress(struct Actor *a)
{
    struct Route *route;
    const struct RoutePoint *node;
    u8 prev;
    s16 dx;
    s16 dz;
    s16 v;
    u8 lo;
    u8 hi;
    u8 base;

    route = Route_Get(gRoutes, a->routeNo);
    prev = a->routeIdx;
    a->routeIdx = Route_Track(route, prev, a->pos.x, a->pos.z, &a->routePos);
    node = GetRoutePoint(route, a->routeIdx);
    dx = node->x - a->pos.x;
    if (dx < 0)
        dx = -dx;
    dz = node->z - a->pos.z;
    if (dz < 0)
        dz = -dz;
    a->nodeDist = dx + dz;
    base = node->progress;
    v = (a->nodeDist << 4) / route->length + base;
    if (v > 255)
        v = 255;
    a->progress = v;
    lo = a->routeCount >> 2;
    hi = lo + (a->routeCount >> 1);
    if (a->routeIdx <= lo && prev >= hi) {
        a->lap++;
        if (gMain.lapCount == a->lap)
            Racer_Finish(a);
    } else if (a->routeIdx >= hi && prev <= lo) {
        a->lap--;
    }
}

void Obj_Draw(struct Obj *obj)
{
    Sprite_DrawAnim3D(&gGame, &obj->anim, &obj->pos);
}

static inline void GetDir(struct Point *dir, u16 angle)
{
    dir->x = gSinTable[angle >> 5];
    dir->y = gSinTable[(angle >> 5) + 0x200];
}

void Racer_InitParams(struct Actor *a)
{
    const struct ActorData *d = a->data;
    struct Point dir;

    a->accel = d->accel;
    a->brake = d->brake;
    a->decel = d->decel;
    a->grip = d->grip;
    a->maxSpeed = d->maxSpeed;
    a->turnAccel = d->turnAccel;
    a->maxTurn = d->maxTurn;
    a->turnSpeed = 0;
    a->direction = gStartHeading;
    a->facing = gStartHeading;
    a->heading = a->direction;
    GetDir(&dir, a->direction);
    a->vel.x = dir.x;
    a->vel.z = dir.y;
    a->speed = 0x100;
}

void Racer_InitPlayer(struct Actor *a, u8 id, u8 chara)
{
    const struct Point *pt;

    a->aiRouteNo = 0xFF;
    a->routeNo = 0;
    Racer_Reset(a);
    a->data = &gPlayerData[gCharaTable[chara]];
    Racer_InitParams(a);
    a->id = id;
    a->pos.y = 0;
    pt = &PointList_Get(gPointLists, POINTS_START)->pts[gGame.activeCount];
    a->pos.x = pt->x;
    a->pos.z = pt->y;
    if (a->data->palette <= 3)
        AnimState_Set(&a->anim, 0, a->data->palette);
    else
        AnimState_Set(&a->anim, 0, a->data->palette + 8);
    a->showMarker = 1;
}

/* Picks the sprite facing from the angle between the racer and the camera */
void Racer_UpdateAnimDir(struct Actor *a)
{
    u16 camera = gCamera.yaw;
    const u8 *tbl = gDirAnims;
    s32 dir = ((u16)(a->facing - camera) + 0x1000) >> 13 & 7;

    AnimState_Change(&a->anim, tbl[dir], 0xFF);
}

static inline void Vec3Add(struct Vec3 *dst, struct Vec3 *src)
{
    dst->x += src->x;
    dst->y += src->y;
    dst->z += src->z;
}

void Racer_UpdatePlayer(struct Actor *a)
{
    s16 maxSpeed;
    s16 accel;
    u16 keys;
    struct Vec3 delta;
    s16 angle;
    s16 ax;
    s16 ay;
    s16 turn;
    s32 over;
    u8 skidSong;
    s32 moving;
    s16 newSpeed;
    s16 oldSpeed;
    struct Point dir;
    struct Vec3 old;
    struct Vec3 next;
    u8 hit;
    s32 engineSong;
    s32 grip;
    s16 pitch;

    if (a->aiRouteNo != 0xFF) {
        Racer_UpdateEnemy(a);
        return;
    }
    if (gMain.state < STATE_RACE) {
        AnimState_Update(&a->anim);
        return;
    }
    maxSpeed = a->maxSpeed;
    accel = a->accel;
    if (a->boosted) {
        maxSpeed += *gSpeedEffectMaxSpeed;
        accel += *gSpeedEffectAccel;
    } else if (a->slowed) {
        maxSpeed += *(gSpeedEffectMaxSpeed + 1);
        accel += *(gSpeedEffectAccel + 1);
    }
    if (a->speedEffectTimer != 0 && --a->speedEffectTimer == 0) {
        a->slowed = 0;
        a->boosted = 0;
    }
    if (!a->slipping) {
        if (gPadHeld[a->id] & DPAD_LEFT) {
            a->turnSpeed -= a->turnAccel;
            if (a->turnSpeed < a->maxTurn)
                a->turnSpeed = -a->maxTurn;
        } else if (gPadHeld[a->id] & DPAD_RIGHT) {
            a->turnSpeed += a->turnAccel;
            if (a->turnSpeed > a->maxTurn)
                a->turnSpeed = a->maxTurn;
        } else if (a->turnSpeed > 0) {
            a->turnSpeed -= a->maxTurn >> 2;
            if (a->turnSpeed < 0)
                a->turnSpeed = 0;
        } else if (a->turnSpeed < 0) {
            a->turnSpeed += a->maxTurn >> 2;
            if (a->turnSpeed > 0)
                a->turnSpeed = 0;
        }
    }

    (&delta)->z = 0;
    (&delta)->y = 0;
    (&delta)->x = 0;
    a->direction += a->turnSpeed;
    angle = a->direction;
    ax = a->vel.x;
    if (ax < 0)
        ax = -ax;
    ay = a->vel.z;
    if (ay < 0)
        ay = -ay;
    if (ax > 15 || ay > 15) {
        turn = ArcTan2(a->vel.z, a->vel.x);
        turn = AngleDiff(angle, turn);
    } else {
        turn = 0;
    }
    a->facing = angle + turn;
    a->heading = angle;
    if (turn < 0)
        turn = -turn;
    if (gPlayerNo == a->id) {
        if ((s16)(turn - 0xAAA) > 0)
            skidSong = SE_SKID;
        else
            skidSong = SONG_NONE;
    }
    over = (s16)(turn - 0xAAA);
    if (over > 0) {
        a->skidCounter -= over;
        if ((s16)a->skidCounter < 0) {
            a->skidCounter += 0x4000;
            Effect_Spawn(&gGame, EFFECT_DUST, &a->pos, &a->vel);
        }
    }
    if (a->spinTimer != 0) {
        angle += a->spinAngle;
        a->spinTimer--;
    }
    GetDir(&dir, angle);
    moving = 1;
    a->speed = Sqrt(a->vel.x * a->vel.x + a->vel.z * a->vel.z);
    if ((s16)a->speed > maxSpeed) {
        newSpeed = a->speed - a->decel;
        if (newSpeed < maxSpeed)
            newSpeed = maxSpeed;
        a->vel.x = a->vel.x * newSpeed / (s16)a->speed;
        a->vel.z = a->vel.z * newSpeed / (s16)a->speed;
        a->speed = newSpeed;
        moving = 0;
    }
    keys = gPadHeld[a->id];
    if ((keys & A_BUTTON) && !a->frozen && moving) {
        (&delta)->x = dir.x * accel >> 8;
        (&delta)->z = dir.y * accel >> 8;
        Vec3Add(&a->vel, &delta);
    } else if ((gPadHeld[a->id] & B_BUTTON) && !a->frozen) {
        oldSpeed = a->speed;
        a->speed = oldSpeed - a->brake;
        if ((s16)a->speed <= 0) {
            a->vel.z = 0;
            a->vel.x = 0;
            a->speed = 0;
        } else {
            a->vel.x = a->vel.x * (s16)a->speed / oldSpeed;
            a->vel.z = a->vel.z * (s16)a->speed / oldSpeed;
            skidSong = SE_BRAKE;
        }
    } else {
        oldSpeed = a->speed;
        a->speed = oldSpeed - a->decel;
        if ((s16)a->speed <= 0) {
            a->vel.z = 0;
            a->vel.x = 0;
            a->speed = 0;
        } else {
            a->vel.x = a->vel.x * (s16)a->speed / oldSpeed;
            a->vel.z = a->vel.z * (s16)a->speed / oldSpeed;
        }
    }
    if (gPlayerNo == a->id && (gFrameCounter & 15) == gPlayerNo && gSkidSong != skidSong) {
        if (skidSong == SONG_NONE) {
            m4aSongNumStop(gSkidSong);
            gEngineSong = skidSong;
        } else {
            m4aSongNumStart(skidSong);
        }
        gSkidSong = skidSong;
    }
    grip = a->grip * (s16)a->speed;
    a->vel.x = ((dir.x * grip >> 8) + a->vel.x * (256 - a->grip)) >> 8;
    a->vel.z = ((dir.y * grip >> 8) + a->vel.z * (256 - a->grip)) >> 8;
    old.x = a->pos.x;
    (&old)->z = a->pos.z;
    next.x = a->pos.x + (a->vel.x >> 4);
    (&next)->y = a->pos.y;
    (&next)->z = a->pos.z + (a->vel.z >> 4);
    Game_CollideRacer(&gGame, &next, a);
    Field_CheckWall(&gField, &next, &a->vel, (s16 *)&a->speed);
    a->pos.x += a->vel.x >> 4;
    a->pos.z += a->vel.z >> 4;
    hit = Field_CheckGround(&gField, &a->pos, &a->vel, (s16 *)&a->speed);
    if (hit & TERRAIN_WALL) {
        a->pos.x = old.x;
        a->pos.z = old.z;
    }
    if (gPlayerNo == a->id && gEngineSong != 5) {
        if ((s16)a->speed <= 4)
            engineSong = SONG_NONE;
        else if (hit & TERRAIN_ROUGH)
            engineSong = SE_ENGINE_ROUGH;
        else
            engineSong = SE_ENGINE;
        if (gEngineSong != engineSong) {
            if (engineSong == SONG_NONE)
                m4aSongNumStop(gEngineSong);
            else
                m4aSongNumStart(engineSong);
            gEngineSong = engineSong;
        }
        if (engineSong != SONG_NONE) {
            pitch = ((s16)a->speed << 8) / 320;
            m4aMPlayPitchControl(&gMPlayEngine, 0xFFFF, pitch);
        }
    }
    AnimState_Update(&a->anim);
    Racer_UpdateProgress(a);
    if ((gPadNew[a->id] & L_BUTTON) && (u8)a->item != ITEM_NONE) {
        if (gPlayerNo == a->id)
            PlaySong(&gSound, SE_ITEM_USE, a);
        switch ((u8)a->item % ITEM_COUNT) {
        case ITEM_FREEZE:
            Effect_Spawn(&gGame, EFFECT_FREEZE_SHOT, a->id, &a->pos, a->facing, a->routeNo, a->routeIdx);
            break;
        case ITEM_SLIP:
            Effect_Spawn(&gGame, EFFECT_SLIP_SHOT, a->id, &a->pos, a->facing, a->routeNo, a->routeIdx);
            break;
        case ITEM_TRAP:
            Effect_Spawn(&gGame, EFFECT_TRAP_THROW, a->id, &a->pos, a->facing, &a->vel);
            break;
        }
        a->item = ITEM_NONE;
    }
    a->slipping = 0;
    a->frozen = 0;
}

void Racer_Draw(struct Actor *a)
{
    Racer_UpdateAnimDir(a);
    Obj_Draw((struct Obj *)a);
    if (a->boosted) {
        Sprite_Draw3D(&gGame, 28, &a->pos);
    } else if (a->slowed) {
        Sprite_Draw3D(&gGame, 29, &a->pos);
    }
    if (gPlayerNo != a->id) {
        Sprite_Draw3D(&gGame, a->id + 22, &a->pos);
    } else if (a->showMarker) {
        Sprite_Draw3DOffset(&gGame, a->id + 22, &a->pos, -6, -8, -1);
    }
}

/* Draws the marker of the racer chasing a at the bottom of the screen */
void Racer_DrawChaserMarker(struct Actor *a, struct Actor *chaser, struct AnimState *marker)
{
    struct Point pos;
    s32 diff;
    u16 depth;
    u16 da;
    s16 *pa;
    s16 *pb;

    da = Racer_GetProgress(a);
    diff = (s16)da - (s16)Racer_GetProgress(chaser);
    depth = diff;
    if ((u16)(depth - 1) <= 18) {
        pa = &a->routePos;
        pb = &chaser->routePos;
        pos.x = ((*pa - *pb) >> 6) + 120;
        if (pos.x >= -16 && pos.x <= 256) {
            (&pos)->y = 150;
            Sprite_DrawAnim(&gGame, marker, &pos, 0);
        }
    }
}

void Racer_InitEnemy(struct Actor *a, u8 no)
{
    s32 n;
    const struct Point *pt;

    a->routeNo = 0;
    Racer_Reset(a);
    a->data = &gEnemyData[no];
    if (a->data->aiRoute > 1) {
        AssertFailed(OBJ_FILE, 1064);
    }
    a->aiRouteNo = a->data->aiRoute + 1;
    n = Route_Get(gRoutes, a->aiRouteNo)->count;
    a->aiRouteCount = n;
    a->aiRouteIdx = n - 1;
    Racer_InitParams(a);
    a->direction = (gStartHeading << 15) / 180;
    a->id = no + 4;
    a->pos.y = 0;
    pt = &PointList_Get(gPointLists, POINTS_START)->pts[gGame.activeCount % 8];
    a->pos.x = pt->x;
    a->pos.z = pt->y;
    if (a->data->palette <= 3) {
        AnimState_Set(&a->anim, 0, a->data->palette);
    } else {
        AnimState_Set(&a->anim, 0, a->data->palette + 8);
    }
}

static inline s32 IsWalkable(struct Field *field, struct Vec3 *pos)
{
    s32 x = pos->x + 0x4000;
    s32 z = pos->z + 0x4000;
    const struct Terrain *t = GetTerrain(field, x, z);

    return t->flags & TERRAIN_OPEN;
}

/* Follows the AI route, steering around the nearest obstacle ahead */
void Racer_UpdateEnemy(struct Actor *a)
{
    u8 progress;
    s16 obstaclePos;
    s16 minSpeed;
    s16 range;
    s16 avoidDist;
    struct Vec3 target;
    s32 maxDistSq;
    struct Vec3 left;
    struct Vec3 right;
    struct Vec3 accel;
    struct Point dir;
    struct Vec3 next;
    struct Route *route;
    const struct RoutePoint *node;
    const struct RoutePoint *nextNode;
    u16 nextPos;
    u8 nextIndex;
    s16 idx;
    s16 dx;
    s16 dz;
    s16 ex;
    s16 ez;
    s16 len;
    u16 dist;
    s16 px;
    s16 pz;
    s16 lx;
    s16 lz;
    s16 rx;
    s16 rz;
    s32 leftDot;
    s32 sq;
    s16 delta;

    if (gMain.state <= STATE_COUNTDOWN) {
        AnimState_Update(&a->anim);
        return;
    }
    a->slowed = 0;
    a->boosted = 0;
    route = Route_Get(gRoutes, a->aiRouteNo);
    a->aiRouteIdx = Route_Advance(route, a->aiRouteIdx, a->pos.x, a->pos.z);
    if (a->aiRouteIdx == 0xFF) {
        AssertFailed(OBJ_FILE, 1128);
    }
    if ((s16)(nextPos = a->aiRouteIdx + 1) >= route->count) {
        idx = 0;
    } else {
        idx = nextPos;
    }
    nextIndex = idx;
    node = &route->pts[a->aiRouteIdx];
    nextNode = &route->pts[nextIndex];
    dx = nextNode->x - a->pos.x;
    dz = nextNode->z - a->pos.z;

    if ((a->avoidSide != 0 || (gRaceFrameCounter & 1) == (a->id & 1))
        && Racer_FindObstacle(a, &target, &progress, &obstaclePos, &minSpeed, &range, &avoidDist, &maxDistSq)
        && (s16)a->speed > minSpeed
        && (u8)(progress - a->progress) <= 5) {
        delta = a->routePos - obstaclePos;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta < range) {
            ex = target.x - a->pos.x;
            ez = target.z - a->pos.z;
            sq = ex * ex + ez * ez;
            if (sq < maxDistSq && ex * dx + ez * dz > 0) {
                sq = dx * dx + dz * dz;
                dist = Sqrt(sq);
                px = dx * avoidDist / dist;
                pz = dz * avoidDist / dist;
                if (a->avoidSide == 0) {
                eval:
                    left.x = target.x + pz;
                    (&left)->z = target.z - px;
                    lx = left.x - a->pos.x;
                    lz = left.z - a->pos.z;
                    leftDot = (a->vel.x * lx + a->vel.z * lz) / (s16)Sqrt(lx * lx + lz * lz);
                    right.x = target.x - pz;
                    (&right)->z = px + target.z;
                    rx = right.x - a->pos.x;
                    rz = right.z - a->pos.z;
                    if (leftDot > (a->vel.x * rx + a->vel.z * rz) / (s16)Sqrt(rx * rx + rz * rz)) {
                        if (IsWalkable(&gField, &left)) {
                            a->avoidSide = 1;
                            dx = lx;
                            dz = lz;
                        } else {
                            a->avoidSide = 2;
                            dx = rx;
                            dz = rz;
                        }
                    } else {
                        if (IsWalkable(&gField, &right)) {
                            a->avoidSide = 2;
                            dx = rx;
                            dz = rz;
                        } else {
                            a->avoidSide = 1;
                            dx = lx;
                            dz = lz;
                        }
                    }
                } else {
                    if (a->avoidSide == 1) {
                        left.x = pz + target.x;
                        left.z = target.z - px;
                        dx = left.x - a->pos.x;
                        dz = left.z - a->pos.z;
                        if (!IsWalkable(&gField, &left)) {
                            goto eval;
                        }
                    } else {
                        right.x = target.x - pz;
                        right.z = px + target.z;
                        dx = right.x - a->pos.x;
                        dz = right.z - a->pos.z;
                        if (!IsWalkable(&gField, &right)) {
                            goto eval;
                        }
                    }
                }
                goto move;
            }
        }
    }
    a->avoidSide = 0;
move:
    (&accel)->x = (&accel)->y = (&accel)->z = 0;
    len = Sqrt(dx * dx + dz * dz);
    if (len != 0) {
        s16 grip;
        s16 turn;
        s16 brake;
        s16 limit;
        u16 angle;
        s16 sin;
        s16 cos;
        s32 speed;
        s16 maxSpeed;
        u16 newSpeed;
        s32 force;

        if (a->vel.x != 0 || a->vel.z != 0) {
            a->direction = ArcTan2(a->vel.z, a->vel.x);
        }
        a->facing = a->direction;
        a->heading = a->direction;
        dir.x = (dx << 8) / len;
        (&dir)->y = (dz << 8) / len;
        if (a->spinTimer != 0) {
            angle = a->spinAngle;
            sin = gSinTable[angle >> 5];
            cos = gSinTable[(angle >> 5) + 0x200];
            dir.x = (cos * dir.x - sin * dir.y) >> 8;
            dir.y = (dir.x * sin + dir.y * cos) >> 8;
            a->spinTimer--;
        }
        grip = a->grip;
        if (a->slipping) {
            grip = 0;
        }
        turn = a->accel;
        brake = a->brake;
        limit = a->maxSpeed;
        if (a->frozen) {
            turn >>= 3;
            brake >>= 3;
            limit >>= 1;
        }
        (&accel)->x = (dir.x * turn) >> 8;
        (&accel)->z = (dir.y * turn) >> 8;
        Vec3Add(&a->vel, &accel);
        speed = Sqrt(a->vel.x * a->vel.x + a->vel.z * a->vel.z);
        a->speed = speed;
        maxSpeed = (limit * gRouteSpeedTable[node->speedType].value) >> 8;
        if ((s16)speed > maxSpeed) {
            newSpeed = speed - brake;
            if ((s16)newSpeed < maxSpeed) {
                newSpeed = maxSpeed;
            }
            a->vel.x = a->vel.x * (s16)newSpeed / (s16)a->speed;
            a->vel.z = a->vel.z * (s16)newSpeed / (s16)a->speed;
            a->speed = newSpeed;
        }
        force = grip * (s16)a->speed;
        a->vel.x = (((dir.x * force) >> 8) + a->vel.x * (0x100 - grip)) >> 8;
        a->vel.z = (((dir.y * force) >> 8) + a->vel.z * (0x100 - grip)) >> 8;
    }
    next.x = (a->vel.x >> 4) + a->pos.x;
    (&next)->y = a->pos.y;
    (&next)->z = (a->vel.z >> 4) + a->pos.z;
    Game_CollideRacer(&gGame, &next, a);
    Field_CheckWallAI(&gField, &next, &a->vel, (s16 *)&a->speed);
    a->pos.x += a->vel.x >> 4;
    a->pos.z += a->vel.z >> 4;
    AnimState_Update(&a->anim);
    Racer_UpdateProgress(a);
    a->slipping = 0;
    a->frozen = 0;
}

s32 Racer_IsWrongWay(struct Actor *a)
{
    struct Point dir;
    struct Point *p;
    u16 angle;

    if (a->routeIdx != 0xFF) {
        angle = a->direction;
        p = &dir;
        p->x = gSinTable[angle >> 5];
        p->y = gSinTable[(angle >> 5) + 0x200];
        return Route_Dot(Route_Get(gRoutes, a->routeNo), a->routeIdx, p->x, p->y) <= 0;
    }
    return 0;
}

void Racer_SetItem(struct Actor *a, u8 item)
{
    if (gPlayerNo == a->id) {
        m4aSongNumStart(SE_ITEM_GET);
    }
    a->item = item;
}

/* The GameCube sends how much each player likes each food: liked foods boost, disliked ones slow down */
void Racer_ApplyPanel(struct Actor *a, u8 food)
{
    u8 value;

    value = gJoyWork.recv.ctx.foodLevels[a->id][food];
    if (value >= gPanelBoostThreshold) {
        if (gPlayerNo == a->id) {
            m4aSongNumStart(SE_BOOST);
        }
        a->boosted = 1;
        a->slowed = 0;
        a->speedEffectTimer = gSpeedEffectDurations[(value - 1) / 10];
    } else if (value <= gPanelSlowThreshold) {
        if (gPlayerNo == a->id) {
            m4aSongNumStart(SE_SLOW);
        }
        a->boosted = 0;
        a->slowed = 1;
        a->speedEffectTimer = gSpeedEffectDurations[(value - 1) / 10];
    } else {
        m4aSongNumStart(SE_PANEL);
        a->boosted = 0;
        a->slowed = 0;
        a->speedEffectTimer = 0;
    }
}

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
            game->cellTable = (struct Table *)Chunk_GetData(&reader);
            for (i = 0; i < game->cellTable->count; i++) {
                game->cellTable->entries[i] = (u8 *)game->cellTable + (u32)game->cellTable->entries[i];
                cell = (struct Cell *)game->cellTable->entries[i];
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
            game->animTable = (struct Table *)Chunk_GetData(&reader);
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
            AssertFailed(OBJ_FILE, 1633);
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
        AssertFailed(OBJ_FILE, 1999);
    }
    node->next = game->oamLists[prio];
    game->oamLists[prio] = node;
}

struct OamNode *Oam_AllocNode(struct Game *game, struct OamData *oam)
{
    struct OamNode *node;

    if (game->freeNode >= &game->oamNodes[128]) {
        AssertFailed(OBJ_FILE, 2010);
    }
    node = game->freeNode++;
    DmaSet(oam, &node->oam, 0x84000002);
    return node;
}

void Sprite_DrawAnim(struct Game *game, struct AnimState *anim, struct Point *pos, s16 prio)
{
    struct Cell *cell;
    s32 i;
    struct OamNode *node;

    if (anim->id >= ANIM_COUNT)
        AssertFailed(OBJ_FILE, 2023);
    if (anim->frame >= 127)
        AssertFailed(OBJ_FILE, 2024);
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
        AssertFailed(OBJ_FILE, 2057);
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
        AssertFailed(OBJ_FILE, 2087);
    if (anim->frame >= 127)
        AssertFailed(OBJ_FILE, 2088);
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

void Sprite_DrawScaled(struct Game *game, s16 animNo, struct Vec3 *pos)
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
            AssertFailed(OBJ_FILE, 2148);
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
void Sprite_Draw3DOffset(struct Game *game, u16 animNo, struct Vec3 *pos, s16 dx, s16 dy, s16 prio)
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
}
