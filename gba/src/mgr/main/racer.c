#include "global.h"
#include "main.h"
#include "joybus.h"
#include "obj.h"
#include "effect.h"
#include "camera.h"
#include "field.h"
#include "route.h"
#include "sound.h"
#include "fixmath.h"

static inline struct Anim *GetAnim(u16 id)
{
    return gGameAnimTable->entries[id];
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
    s->duration = (GetAnim(s->id))->frames[0].duration;
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
        anim = GetAnim(s->id);
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
    a->item = -1;
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
        end = gGameEnemyCount + 4;
        mask = ~(1 << a->id);
    } else if (mode == 0) {
        start = 0;
        end = 4;
        mask = gPlayerMask & ~(1 << a->id);
    } else {
        start = 4;
        end = gGameEnemyCount + 4;
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

    n = gGameEnemyCount + 4;
    mask = ~(1 << a->id);
    best = 0x7F;
    found = NULL;
    for (i = 0; i < n; i++) {
        if ((1 << i) & mask) {
            other = &gGame.actors[(u8)i];
            d = (gActorProgress + (u8)i)->value - a->progress;
            if (d >= 0 && best > d) {
                best = d;
                found = other;
            }
        }
    }
    trap = NULL;
    e = gGameEffects;
    for (i = 0; i < 64; i++) {
        if (e->active && e->type == EFFECT_TRAP) {
            d = e->u.trap.progress - a->progress;
            if (d >= 0 && best > d) {
                best = d;
                trap = e;
                found = NULL;
            }
        }
        /* the original steps 28 bytes instead of sizeof(struct Effect) */
        e = (struct Effect *)((u8 *)e + 28);
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
    struct RoutePoint *node;
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
    v = (a->nodeDist << 4) / route->scale + base;
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
    struct ActorData *d = a->data;
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
    struct Point *pt;

    a->aiRouteNo = 0xFF;
    a->routeNo = 0;
    Racer_Reset(a);
    a->data = &gPlayerData[gCharaTable[chara]];
    Racer_InitParams(a);
    a->id = id;
    a->pos.y = 0;
    pt = &PointList_Get(gPointLists, POINTS_START)->pts[gGameActiveCount];
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
            skidSong = 7;
        else
            skidSong = 0xFF;
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
            skidSong = 6;
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
        if (skidSong == 0xFF) {
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
    Field_CheckWall(&gField, &next, &a->vel, &a->speed);
    a->pos.x += a->vel.x >> 4;
    a->pos.z += a->vel.z >> 4;
    hit = Field_CheckGround(&gField, &a->pos, &a->vel, &a->speed);
    if (hit & TERRAIN_WALL) {
        a->pos.x = old.x;
        a->pos.z = old.z;
    }
    if (gPlayerNo == a->id && gEngineSong != 5) {
        if ((s16)a->speed <= 4)
            engineSong = 0xFF;
        else if (hit & TERRAIN_ROUGH)
            engineSong = 8;
        else
            engineSong = 3;
        if (gEngineSong != engineSong) {
            if (engineSong == 0xFF)
                m4aSongNumStop(gEngineSong);
            else
                m4aSongNumStart(engineSong);
            gEngineSong = engineSong;
        }
        if (engineSong != 0xFF) {
            pitch = ((s16)a->speed << 8) / 320;
            m4aMPlayPitchControl(&gMPlaySe, 0xFFFF, pitch);
        }
    }
    AnimState_Update(&a->anim);
    Racer_UpdateProgress(a);
    if ((gPadNew[a->id] & L_BUTTON) && (u8)a->item != 0xFF) {
        if (gPlayerNo == a->id)
            PlaySong(&gSound, 13, a);
        switch ((u8)a->item % 3) {
        case 0:
            Effect_Spawn(&gGame, EFFECT_FREEZE_SHOT, a->id, &a->pos, a->facing, a->routeNo, a->routeIdx);
            break;
        case 1:
            Effect_Spawn(&gGame, EFFECT_SLIP_SHOT, a->id, &a->pos, a->facing, a->routeNo, a->routeIdx);
            break;
        case 2:
            Effect_Spawn(&gGame, EFFECT_TRAP_THROW, a->id, &a->pos, a->facing, &a->vel);
            break;
        }
        a->item = 0xFF;
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
    struct Point *pt;

    a->routeNo = 0;
    Racer_Reset(a);
    a->data = &gEnemyData[no];
    if (a->data->aiRoute > 1) {
        AssertFailed(gObjFileName, 1064);
    }
    a->aiRouteNo = a->data->aiRoute + 1;
    n = Route_Get(gRoutes, a->aiRouteNo)->count;
    a->aiRouteCount = n;
    a->aiRouteIdx = n - 1;
    Racer_InitParams(a);
    a->direction = (gStartHeading << 15) / 180;
    a->id = no + 4;
    a->pos.y = 0;
    pt = &PointList_Get(gPointLists, POINTS_START)->pts[gGameActiveCount % 8];
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
    struct RoutePoint *node;
    struct RoutePoint *nextNode;
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
        AssertFailed(gObjFileName, 1128);
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
    Field_CheckWallAI(&gField, &next, &a->vel, &a->speed);
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
        m4aSongNumStart(9);
    }
    a->item = item;
}

/* The panel roll table comes from the GameCube: high rolls boost, low rolls slow down */
void Racer_ApplyPanel(struct Actor *a, u8 kind)
{
    u8 value;

    value = gJoyWork.recv.info.panelTable[a->id][kind];
    if (value >= gPanelBoostThreshold) {
        if (gPlayerNo == a->id) {
            m4aSongNumStart(15);
        }
        a->boosted = 1;
        a->slowed = 0;
        a->speedEffectTimer = gSpeedEffectDurations[(value - 1) / 10];
    } else if (value <= gPanelSlowThreshold) {
        if (gPlayerNo == a->id) {
            m4aSongNumStart(16);
        }
        a->boosted = 0;
        a->slowed = 1;
        a->speedEffectTimer = gSpeedEffectDurations[(value - 1) / 10];
    } else {
        m4aSongNumStart(18);
        a->boosted = 0;
        a->slowed = 0;
        a->speedEffectTimer = 0;
    }
}
