#include "global.h"
#include "obj.h"
#include "effect.h"
#include "camera.h"
#include "fixmath.h"
#include "route.h"
#include "sound.h"
#include "random.h"

const char gEffectFileName[] = "C:/FFF/miniGame/mgr/effect.cpp";

u8 gItemBoxAnims[] = { 35, 37, 36 };
u8 gPanelAnims[] = { 8, 9, 10, 11, 12, 13, 14, 71 };

const struct ActorData gFreezeShotParams = { 40, 0, 0, 32, 4800, 0, 0, 0, 0, { 0, 0, 0, 0 } };
const struct ActorData gSlipShotParams = { 40, 0, 0, 32, 4800, 0, 0, 0, 0, { 0, 0, 0, 0 } };

static inline void GetDir(struct Point *dir, u16 angle)
{
    dir->x = gSinTable[angle >> 5];
    dir->y = gSinTable[(angle >> 5) + 512];
}

static inline void Scale(struct Point *out, struct Point *in, s32 scale)
{
    out->x = (in->x * scale) >> 8;
    out->y = (in->y * scale) >> 8;
}

static inline s32 MulShift(s32 a, s32 b)
{
    return (a * b) >> 8;
}

static inline s16 Distance(const struct RoutePoint *pt, struct Vec3 *pos)
{
    s16 dx;
    s16 dz;

    dx = pt->x - pos->x;
    if (dx < 0)
        dx = -dx;
    dz = pt->z - pos->z;
    if (dz < 0)
        dz = -dz;
    return dx + dz;
}

static inline void SetFrozen(struct Actor *actor, u8 on)
{
    actor->frozen = on;
}

static inline void SetSlipping(struct Actor *actor, u8 on)
{
    actor->slipping = on;
}

struct Effect *Effect_Alloc(struct Game *game)
{
    s32 i;

    for (i = 0; i < 64; i++) {
        if (!game->effects[i].active)
            return &game->effects[i];
    }
    AssertFailed(gEffectFileName, 28);
    return NULL;
}

struct Effect *Effect_AllocLast(struct Game *game)
{
    s32 i;

    for (i = 63; i >= 0; i--) {
        if (!game->effects[i].active)
            return &game->effects[i];
    }
    AssertFailed(gEffectFileName, 42);
    return NULL;
}

void Effect_InitItemBox(struct Effect *e, va_list *ap)
{
    s32 no = va_arg(*ap, s32);
    const struct Point *pt = &PointList_Get(gPointLists, POINTS_ITEM_BOX)->pts[(s16)no];

    e->pos.x = pt->x;
    e->pos.z = pt->y;
    e->pos.y = 0;
    e->u.box.kind = genrand() % ITEM_COUNT;
    AnimState_Set(&e->anim, gItemBoxAnims[e->u.box.kind], 0xFF);
    e->radius = 80;
}

void Effect_InitPanel(struct Effect *e, va_list *ap)
{
    s32 no = va_arg(*ap, s32);
    const struct Point *pt = &PointList_Get(gPointLists, POINTS_PANEL)->pts[(s16)no];

    e->pos.x = pt->x;
    e->pos.z = pt->y;
    e->pos.y = 0;
    e->u.box.kind = genrand() % FOOD_COUNT;
    AnimState_Set(&e->anim, gPanelAnims[e->u.box.kind], 0xFF);
    e->radius = 80;
}

void Effect_InitShot(struct Effect *e, va_list *ap)
{
    struct Vec3 *pos;
    struct Point dir;
    s32 speed;

    e->u.shot.ownerId = va_arg(*ap, s32) & 0xFF;
    pos = va_arg(*ap, struct Vec3 *);
    GetDir(&dir, va_arg(*ap, s32));
    speed = 4800;
    e->u.shot.target = NULL;
    Scale(&e->u.shot.vel, &dir, speed);
    e->u.shot.routeNo = va_arg(*ap, s32) & 0xFF;
    e->u.shot.routeIdx = va_arg(*ap, s32) & 0xFF;
    e->pos = *pos;
}

void Effect_InitFreezeTrail(struct Effect *e, va_list *ap)
{
    struct Point *vel;

    e->pos = *va_arg(*ap, struct Vec3 *);
    vel = va_arg(*ap, struct Point *);
    AnimState_Set(&e->anim, 38, 0xFF);
    e->u.vel = *vel;
}

void Effect_InitFreezeShot(struct Effect *e, va_list *ap)
{
    Effect_InitShot(e, ap);
    AnimState_Set(&e->anim, 30, 0xFF);
    e->radius = 80;
    Effect_Spawn(&gGame, EFFECT_FREEZE_TRAIL, &e->pos, &e->u.shot.vel);
}

void Effect_InitFreeze(struct Effect *e, va_list *ap)
{
    e->u.target = va_arg(*ap, struct Actor *);
    AnimState_Set(&e->anim, 32, 0xFF);
    PlaySong(&gSound, SE_FREEZE, e);
}

void Effect_InitSlipTrail(struct Effect *e, va_list *ap)
{
    struct Point *vel;

    e->pos = *va_arg(*ap, struct Vec3 *);
    vel = va_arg(*ap, struct Point *);
    AnimState_Set(&e->anim, 38, 11);
    e->u.vel = *vel;
}

void Effect_InitSlipShot(struct Effect *e, va_list *ap)
{
    Effect_InitShot(e, ap);
    AnimState_Set(&e->anim, 31, 0xFF);
    e->radius = 80;
    Effect_Spawn(&gGame, EFFECT_SLIP_TRAIL, &e->pos, &e->u.shot.vel);
}

void Effect_InitSlip(struct Effect *e, va_list *ap)
{
    e->u.target = va_arg(*ap, struct Actor *);
    AnimState_Set(&e->anim, 39, 0xFF);
    PlaySong(&gSound, SE_SLIP, e);
}

void Effect_InitTrapThrow(struct Effect *e, va_list *ap)
{
    struct Vec3 *pos;
    struct Vec3 *vel;
    u16 angle;
    struct Point dir;

    e->u.thrown.ownerId = va_arg(*ap, s32) & 0xFF;
    pos = va_arg(*ap, struct Vec3 *);
    angle = va_arg(*ap, s32);
    vel = va_arg(*ap, struct Vec3 *);
    e->pos = *pos;
    e->u.thrown.vel = *vel;
    GetDir(&dir, angle);
    e->u.thrown.vel.x += MulShift(dir.x, -800);
    e->u.thrown.vel.z += MulShift(dir.y, -800);
    e->u.thrown.vel.y = 800;
    AnimState_Set(&e->anim, 33, 0xFF);
    e->radius = 120;
}

void Effect_InitTrap(struct Effect *e, va_list *ap)
{
    struct Route *route;
    const struct RoutePoint *pt;
    s16 v;
    u8 base;

    e->u.trap.ownerId = va_arg(*ap, s32) & 0xFF;
    e->pos = *va_arg(*ap, struct Vec3 *);
    e->pos.y = 0;
    AnimState_Set(&e->anim, 34, 0xFF);
    e->radius = 120;
    route = Route_Get(gRoutes, 0);
    pt = GetRoutePoint(route, Route_Track(route, 0xFF, e->pos.x, e->pos.z, &e->u.trap.routePos));
    v = Distance(pt, &e->pos);
    base = pt->progress;
    v = (v << 4) / route->length + base;
    if (v > 255)
        v = 255;
    e->u.trap.progress = v;
}

void Effect_InitSpin(struct Effect *e, va_list *ap)
{
    e->u.target = va_arg(*ap, struct Actor *);
    AnimState_Set(&e->anim, 33, 0xFF);
    PlaySong(&gSound, SE_SPIN, e);
}

void Effect_InitDust(struct Effect *e, va_list *ap)
{
    struct Vec3 *pos = va_arg(*ap, struct Vec3 *);
    struct Vec3 *vel = va_arg(*ap, struct Vec3 *);

    e->pos = *pos;
    e->u.vel.x = vel->x >> 1;
    e->u.vel.y = vel->z >> 1;
    AnimState_Set(&e->anim, 17, 0xFF);
}

void Effect_Setup(struct Effect *e, u8 type, va_list *ap)
{
    Obj_Init((struct Obj *)e);
    e->active = 1;
    e->type = type;
    e->timer = 0;
    e->visible = 1;
    switch (e->type) {
    case EFFECT_ITEM_BOX:
        Effect_InitItemBox(e, ap);
        break;
    case EFFECT_PANEL:
        Effect_InitPanel(e, ap);
        break;
    case EFFECT_FREEZE_TRAIL:
        Effect_InitFreezeTrail(e, ap);
        break;
    case EFFECT_FREEZE_SHOT:
        Effect_InitFreezeShot(e, ap);
        break;
    case EFFECT_FREEZE:
        Effect_InitFreeze(e, ap);
        break;
    case EFFECT_SLIP_TRAIL:
        Effect_InitSlipTrail(e, ap);
        break;
    case EFFECT_SLIP_SHOT:
        Effect_InitSlipShot(e, ap);
        break;
    case EFFECT_SLIP:
        Effect_InitSlip(e, ap);
        break;
    case EFFECT_TRAP_THROW:
        Effect_InitTrapThrow(e, ap);
        break;
    case EFFECT_TRAP:
        Effect_InitTrap(e, ap);
        break;
    case EFFECT_SPIN:
        Effect_InitSpin(e, ap);
        break;
    case EFFECT_DUST:
        Effect_InitDust(e, ap);
        break;
    default:
        AssertFailed(gEffectFileName, 342);
        break;
    }
}

void Effect_Set(struct Effect *e, u8 type, ...)
{
    va_list ap;

    va_start(ap, type);
    Effect_Setup(e, type, &ap);
    va_end(ap);
}

void Effect_Spawn(struct Game *game, u8 type, ...)
{
    va_list ap;

    va_start(ap, type);
    Effect_Setup(Effect_Alloc(game), type, &ap);
    va_end(ap);
}

void Effect_SpawnLast(struct Game *game, u8 type, ...)
{
    va_list ap;

    va_start(ap, type);
    Effect_Setup(Effect_AllocLast(game), type, &ap);
    va_end(ap);
}

/* Steers toward the target, or along the route when there is none; returns the new speed */
s16 Effect_MoveAlongRoute(struct Effect *e, u8 routeNo, u8 *routeIdx, struct Point *vel, const struct ActorData *params, struct Actor *target, s16 targetDist)
{
    struct Route *route;
    const struct RoutePoint *pt;
    u16 next;
    s16 idx;
    s16 dx;
    s16 dz;
    s16 len;
    s16 speed;
    s32 f;
    s32 sq;
    struct Point acc;
    struct Point dir;

    route = Route_Get(gRoutes, routeNo);
    *routeIdx = Route_Advance(route, *routeIdx, e->pos.x, e->pos.z);
    if ((s16)(next = *routeIdx + 1) >= route->count)
        idx = 0;
    else
        idx = next;
    pt = &route->pts[(u8)idx];
    if (target != NULL) {
        dx = target->pos.x - e->pos.x;
        dz = target->pos.z - e->pos.z;
    } else {
        dx = pt->x - e->pos.x;
        dz = pt->z - e->pos.z;
    }
    (&acc)->x = (&acc)->y = 0;
    len = Sqrt(dx * dx + dz * dz);
    if (len != 0) {
        dir.x = (dx << 8) / len;
        (&dir)->y = (dz << 8) / len;
        sq = vel->x * vel->x + vel->y * vel->y;
        f = params->grip * (s16)Sqrt(sq);
        vel->x = (MulShift(dir.x, f) + vel->x * (256 - params->grip)) >> 8;
        vel->y = (MulShift(dir.y, f) + vel->y * (256 - params->grip)) >> 8;
        (&acc)->x = (dir.x * params->accel) >> 8;
        (&acc)->y = (dir.y * params->accel) >> 8;
        vel->x += (&acc)->x;
        vel->y += (&acc)->y;
        sq = vel->x * vel->x + vel->y * vel->y;
        speed = Sqrt(sq);
        if (speed > params->maxSpeed) {
            vel->x = vel->x * params->maxSpeed / speed;
            vel->y = vel->y * params->maxSpeed / speed;
            speed = params->maxSpeed;
        }
    } else {
        speed = 0;
    }
    e->pos.x += vel->x >> 4;
    e->pos.z += vel->y >> 4;
    return speed;
}

void Effect_UpdateItemBox(struct Effect *e)
{
    struct Actor *actor;

    if (e->visible) {
        actor = Game_HitTest(&gGame, &e->pos, e->radius, -1);
        if (actor != NULL) {
            Racer_SetItem(actor, e->u.box.kind);
            e->visible = 0;
            e->u.box.wait = 90;
        }
    } else if (--e->u.box.wait == 0) {
        e->u.box.kind = genrand() % ITEM_COUNT;
        AnimState_Set(&e->anim, gItemBoxAnims[e->u.box.kind], 0xFF);
        e->visible = 1;
    }
}

void Effect_UpdatePanel(struct Effect *e)
{
    struct Actor *actor;

    if (e->visible) {
        actor = Game_HitTest(&gGame, &e->pos, e->radius, -1);
        if (actor != NULL) {
            Racer_ApplyPanel(actor, e->u.box.kind);
            e->visible = 0;
            e->u.box.wait = 90;
        }
    } else if (--e->u.box.wait == 0) {
        e->u.box.kind = genrand() % FOOD_COUNT;
        AnimState_Set(&e->anim, gPanelAnims[e->u.box.kind], 0xFF);
        e->visible = 1;
    }
}

void Effect_UpdateHoming(struct Effect *e, const struct ActorData *params, s32 mask)
{
    s16 speed;
    struct Actor *target;
    s16 dx;
    s16 dz;
    s32 dist2;
    s16 dist;
    u16 out;
    s16 dot;

    speed = Effect_MoveAlongRoute(e, e->u.shot.routeNo, &e->u.shot.routeIdx, &e->u.shot.vel, params, e->u.shot.target, e->u.shot.targetDist);
    target = e->u.shot.target;
    if (target == NULL) {
        if (!(e->timer & 3)) {
            s16 vx = (e->u.shot.vel.x << 8) / speed;
            s16 vz = (e->u.shot.vel.y << 8) / speed;

            e->u.shot.target = Game_FindTarget(&gGame, &e->pos, 25000000, &out, vx, vz, 240, mask);
            e->u.shot.targetDist = out;
        }
    } else {
        s16 vx;
        s16 vz;

        dx = target->pos.x - e->pos.x;
        if (dx < -499 || dx > 499)
            return;
        dz = target->pos.z - e->pos.z;
        if (dz < -499 || dz > 499)
            return;
        dist2 = dx * dx + dz * dz;
        if (dist2 >= 250000)
            return;
        dist = Sqrt(dist2);
        vx = (e->u.shot.vel.x << 8) / speed;
        vz = (e->u.shot.vel.y << 8) / speed;
        dot = (dx * vx + dz * vz) / dist;
        if (dot <= 220)
            e->u.shot.target = NULL;
    }
}

void Effect_UpdateFreezeTrail(struct Effect *e)
{
    e->pos.x += e->u.vel.x >> 4;
    e->pos.z += e->u.vel.y >> 4;
    if (AnimState_Update(&e->anim))
        e->active = 0;
}

void Effect_UpdateFreezeShot(struct Effect *e)
{
    s32 mask = ~(1 << e->u.shot.ownerId);
    struct Actor *actor;

    Effect_UpdateHoming(e, &gFreezeShotParams, mask);
    actor = Game_HitTest(&gGame, &e->pos, e->radius, mask);
    if (actor != NULL) {
        Effect_Spawn(&gGame, EFFECT_FREEZE_TRAIL, &e->pos, &e->u.shot.vel);
        Effect_Set(e, EFFECT_FREEZE, actor);
    } else if (e->timer++ >= 150) {
        Effect_Set(e, EFFECT_FREEZE_TRAIL, &e->pos, &e->u.shot.vel);
    } else {
        AnimState_Update(&e->anim);
    }
}

void Effect_UpdateFreeze(struct Effect *e)
{
    e->pos = e->u.target->pos;
    AnimState_Update(&e->anim);
    SetFrozen(e->u.target, 1);
    if (e->timer++ >= 150)
        e->active = 0;
}

void Effect_UpdateSlipTrail(struct Effect *e)
{
    e->pos.x += e->u.vel.x >> 4;
    e->pos.z += e->u.vel.y >> 4;
    if (AnimState_Update(&e->anim))
        e->active = 0;
}

void Effect_UpdateSlipShot(struct Effect *e)
{
    s32 mask = ~(1 << e->u.shot.ownerId);
    struct Actor *actor;

    Effect_UpdateHoming(e, &gSlipShotParams, mask);
    actor = Game_HitTest(&gGame, &e->pos, e->radius, mask);
    if (actor != NULL) {
        Effect_Spawn(&gGame, EFFECT_SLIP_TRAIL, &e->pos, &e->u.shot.vel);
        Effect_Set(e, EFFECT_SLIP, actor);
    } else if (e->timer++ >= 150) {
        Effect_Set(e, EFFECT_SLIP_TRAIL, &e->pos, &e->u.shot.vel);
    } else {
        AnimState_Update(&e->anim);
    }
}

void Effect_UpdateSlip(struct Effect *e)
{
    e->pos = e->u.target->pos;
    AnimState_Update(&e->anim);
    SetSlipping(e->u.target, 1);
    if (e->timer++ >= 150)
        e->active = 0;
}

void Effect_UpdateTrapThrow(struct Effect *e)
{
    struct Actor *actor;

    actor = Game_HitTest(&gGame, &e->pos, e->radius, ~(1 << e->u.thrown.ownerId));
    if (actor != NULL) {
        Effect_Set(e, EFFECT_SPIN, actor);
    } else if (e->timer++ >= 10) {
        Effect_Set(e, EFFECT_TRAP, e->u.thrown.ownerId, &e->pos);
    } else {
        e->u.thrown.vel.y -= 200;
        if (e->pos.y < 0)
            e->u.thrown.vel.y = -e->u.thrown.vel.y;
        e->pos.x += e->u.thrown.vel.x >> 4;
        e->pos.y += e->u.thrown.vel.y >> 4;
        e->pos.z += e->u.thrown.vel.z >> 4;
    }
}

void Effect_UpdateTrap(struct Effect *e)
{
    s32 mask;
    struct Actor *actor;

    if (e->timer < 60)
        mask = ~(1 << e->u.trap.ownerId);
    else
        mask = -1;
    actor = Game_HitTest(&gGame, &e->pos, e->radius, mask);
    if (actor != NULL)
        Effect_Set(e, EFFECT_SPIN, actor);
    else if (e->timer++ >= 1200)
        e->active = 0;
}

void Effect_UpdateDust(struct Effect *e)
{
    u8 frame;

    e->pos.x += e->u.vel.x >> 4;
    e->pos.z += e->u.vel.y >> 4;
    e->timer++;
    if (!(e->timer & 1)) {
        frame = e->timer >> 1;
        if (frame == 5)
            e->active = 0;
        else
            AnimState_Set(&e->anim, frame + 17, 0xFF);
    }
}

void Effect_UpdateSpin(struct Effect *e)
{
    struct Actor *target = e->u.target;

    e->pos = target->pos;
    if (e->timer == 0 && target->spinTimer == 0) {
        target->spinTimer = 30;
        if (genrand() & 1)
            target->spinAngle = 0x2000;
        else
            target->spinAngle = 0xE000;
    }
    if (e->timer++ >= 30)
        e->active = 0;
}

void Effect_Update(struct Effect *e)
{
    switch (e->type) {
    case EFFECT_ITEM_BOX:
        Effect_UpdateItemBox(e);
        break;
    case EFFECT_PANEL:
        Effect_UpdatePanel(e);
        break;
    case EFFECT_FREEZE_TRAIL:
        Effect_UpdateFreezeTrail(e);
        break;
    case EFFECT_FREEZE_SHOT:
        Effect_UpdateFreezeShot(e);
        break;
    case EFFECT_FREEZE:
        Effect_UpdateFreeze(e);
        break;
    case EFFECT_SLIP_TRAIL:
        Effect_UpdateSlipTrail(e);
        break;
    case EFFECT_SLIP_SHOT:
        Effect_UpdateSlipShot(e);
        break;
    case EFFECT_SLIP:
        Effect_UpdateSlip(e);
        break;
    case EFFECT_TRAP_THROW:
        Effect_UpdateTrapThrow(e);
        break;
    case EFFECT_TRAP:
        Effect_UpdateTrap(e);
        break;
    case EFFECT_SPIN:
        Effect_UpdateSpin(e);
        break;
    case EFFECT_DUST:
        Effect_UpdateDust(e);
        break;
    default:
        AssertFailed(gEffectFileName, 876);
        break;
    }
}
