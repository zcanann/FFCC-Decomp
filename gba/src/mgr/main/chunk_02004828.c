#include "gba_types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (va_list)__builtin_next_arg(last))
#define __va_rounded_size(type) (((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))
#define va_arg(ap, type) ((ap) = (va_list)((char *)(ap) + __va_rounded_size(type)), *((type *)(void *)((char *)(ap) - __va_rounded_size(type))))
#define va_end(ap)

struct OamData {
    s32 y:8;
    u32 affineMode:2;
    u32 objMode:2;
    u32 mosaic:1;
    u32 bpp:1;
    u32 shape:2;
    s32 x:9;
    u32 matrixNum:5;
    u32 size:2;
    u16 tileNum:10;
    u16 priority:2;
    u16 paletteNum:4;
    u16 affineParam;
};

struct OamNode {
    struct OamNode *next;
    struct OamData oam;
};

struct Cell {
    u16 count;
    u16 unk2;
    struct OamData objs[0];
};

struct CellTable {
    u32 unk0;
    struct Cell *cells[0];
};

struct Frame {
    u16 cell;
    u16 unk2;
};

struct Anim {
    u8 unk0[8];
    struct Frame frames[0];
};

struct AnimTable {
    u32 unk0;
    struct Anim *anims[0];
};

struct AnimState {
    u16 id;
    u16 timer;
    u16 duration;
    u8 frame;
    u8 palette;
    u8 loop:1;
};

struct Point {
    s16 x;
    s16 y;
};

struct Pos {
    s16 x;
    s16 y;
    s16 z;
};

struct Matrix {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
};

struct PointList {
    u32 count;
    struct Point *pts;
};

struct RoutePoint {
    s16 x;
    s16 z;
    u8 unk4[5];
    u8 unk9;
    u8 unkA[6];
};

struct Route {
    s16 count;
    s16 unk2;
    struct RoutePoint *pts;
};

struct Homing {
    s16 accel;
    s16 unk2;
    s16 unk4;
    s16 turn;
    s16 maxSpeed;
};

struct Actor {
    struct Pos pos;
    u8 unk8[0x28];
    u16 unk30;
    u16 unk32;
    u8 unk34[0x21];
    u8 unk55_0:1;
    u8 unk55_1:1;
    u8 unk55_2:6;
};

struct Effect {
    struct Pos pos;
    u16 unk8;
    u8 active;
    struct AnimState anim;
    u8 type;
    u8 unk19;
    u16 timer;
    union {
        struct {
            struct Actor *target;
            s16 unk4;
            u8 unk6;
            u8 unk7;
            u8 owner;
            struct Point vel;
        } chase;
        struct {
            u16 wait;
            u8 color;
            u8 owner;
        } idle;
        struct Pos vec;
        struct Point vel;
        struct Actor *target;
        u8 raw[32];
    } w;
};

struct Chara {
    u8 unk0[0x52];
    u8 unk52;
};

struct Game {
    struct Actor players[4];
    struct Actor unk160[8];
    struct Effect effects[64];
    struct AnimState units[2];
    struct CellTable *cellTable;
    struct AnimTable *animTable;
    u8 unk1340[0x6A4];
    u8 unk19E4;
    u8 unk19E5;
    u8 unk19E6;
    u8 unk19E7;
};

extern char lbl_0200EDAC[];
extern char lbl_0200EDC8[];
extern struct Homing lbl_0200EDE8;
extern struct Homing lbl_0200EDFC;
extern s16 lbl_0200EE10[];
extern u8 lbl_020159AC[];
extern u8 lbl_020159AF[];
extern struct Game lbl_0202C618;
extern u8 lbl_030063C8[];
extern u8 lbl_030063E0[];
extern u8 lbl_030063F8[];
extern struct Matrix lbl_03005048[];
extern u8 lbl_030060F8[];

void fn_020001A0(char *file, s32 line);
struct OamNode *fn_020047E4(struct Game *game, struct OamData *src);
void fn_020047AC(struct Game *game, struct OamNode *node, u16 prio);
u8 fn_02006130(void *camera, void *src, struct Pos *out);
void fn_020026EC(struct AnimState *anim, u16 id, u8 palette);
u8 fn_02002700(struct AnimState *anim);
void fn_020026B8(struct AnimState *anim, u16 id, u8 palette);
void fn_0200276C(struct Effect *e);
void fn_02005484(struct Effect *e, u8 type, ...);
void fn_020057B8(struct Effect *e, struct Homing *param, s32 mask);
struct Route *fn_02006B68(void *list, u8 no);
u8 fn_02006DF0(struct Route *route, u8 idx, s16 x, s16 z);
s16 Sqrt(s32 v);
struct Actor *fn_020043E8(struct Game *game, struct Effect *e, s32 range, s16 *out, s16 dx, s16 dz, s32 angle, s32 mask);
s16 fn_02006C94(struct Route *route, u8 a, s16 x, s16 z, void *out);
void fn_020054A4(struct Game *game, u8 type, ...);
struct PointList *fn_02006EFC(void *list, s32 no);
u32 fn_02007398(void);
void fn_02007308(void *list, u8 no, struct Effect *e);
struct Actor *fn_02004218(struct Game *game, struct Effect *e, u8 a, s32 mask);
void fn_02003D14(struct Actor *actor, u8 a);
void fn_02003D40(struct Actor *actor, u8 a);
void fn_02003454(struct Actor *actor, struct Chara *chara, struct AnimState *unit);
s32 fn_02003CA8(struct Actor *actor);
s32 fn_0200287C(struct Actor *actor, u8 a);
void fn_02002C24(struct Actor *actor, u8 no, u8 a);
void fn_020034DC(struct Actor *actor, u8 a);

static inline struct Anim *GetAnim(struct Game *game, u16 no)
{
    return game->animTable->anims[no];
}

static inline struct Frame *GetFrame(struct Anim *anim, u8 no)
{
    return &anim->frames[no];
}

static inline struct Cell *GetCell(struct Game *game, u16 no)
{
    return game->cellTable->cells[no];
}

void fn_02004828(struct Game *game, struct AnimState *spr, struct Point *pos, s16 prio)
{
    struct Cell *cell;
    s32 i;
    struct OamNode *node;

    if (spr->id >= 72)
        fn_020001A0(lbl_0200EDAC, 2023);
    if (spr->frame >= 127)
        fn_020001A0(lbl_0200EDAC, 2024);
    cell = GetCell(game, GetFrame(GetAnim(game, spr->id), spr->frame)->cell);
    for (i = 0; i < cell->count; i++) {
        node = fn_020047E4(game, &cell->objs[i]);
        if (prio < 0) {
            node->oam.affineMode = 3;
            node->oam.matrixNum = 28 - prio;
            prio = 0;
        }
        node->oam.y += pos->y;
        node->oam.x += pos->x;
        fn_020047AC(game, node, prio);
    }
}

void fn_02004930(game, animNo, pos, prio)
    struct Game *game;
    s16 animNo;
    struct Point *pos;
    s16 prio;
{
    struct Cell *cell;
    s32 i;
    struct OamNode *node;

    if (animNo >= 72)
        fn_020001A0(lbl_0200EDAC, 2057);
    cell = GetCell(game, GetAnim(game, animNo)->frames[0].cell);
    for (i = cell->count - 1; i >= 0; i--) {
        node = fn_020047E4(game, &cell->objs[i]);
        node->oam.y += pos->y;
        node->oam.x += pos->x;
        if (prio < 0) {
            node->oam.affineMode = 3;
            node->oam.matrixNum = 28 - prio;
            prio = 0;
        }
        fn_020047AC(game, node, prio);
    }
}

void fn_02004A18(struct Game *game, struct AnimState *spr, struct Pos *pos)
{
    struct Cell *cell;
    s32 i;
    struct OamNode *node;
    u8 scale;
    struct Matrix *mtx;

    if (spr->id >= 72)
        fn_020001A0(lbl_0200EDAC, 2087);
    if (spr->frame >= 127)
        fn_020001A0(lbl_0200EDAC, 2088);
    scale = pos->z;
    if (scale < 28) {
        cell = GetCell(game, GetFrame(GetAnim(game, spr->id), spr->frame)->cell);
        for (i = cell->count - 1; i >= 0; i--) {
            mtx = &lbl_03005048[scale];
            node = fn_020047E4(game, &cell->objs[i]);
            node->oam.matrixNum = scale;
            node->oam.x += pos->x;
            node->oam.y = pos->y + (node->oam.y << 8) / ((mtx->pd >> 2) + 192);
            node->oam.affineMode = 1;
            if (spr->palette != 0xFF)
                node->oam.paletteNum = spr->palette;
            fn_020047AC(game, node, pos->z + 8);
        }
    }
}

void fn_02004B60(game, animNo, pos)
    struct Game *game;
    u16 animNo;
    struct Pos *pos;
{
    struct Cell *cell;
    struct OamNode *node;
    u8 scale;
    struct Matrix *mtx;
    s16 no;

    scale = pos->z;
    if (scale < 28) {
        no = animNo;
        if (no >= 72)
            fn_020001A0(lbl_0200EDAC, 2148);
        cell = GetCell(game, GetAnim(game, no)->frames[0].cell);
        node = fn_020047E4(game, &cell->objs[0]);
        node->oam.matrixNum = scale;
        node->oam.x += pos->x;
        mtx = &lbl_03005048[scale];
        node->oam.y = pos->y + (node->oam.y << 8) / ((mtx->pd >> 2) + 192);
        node->oam.affineMode = 1;
        fn_020047AC(game, node, pos->z + 8);
    }
}

void fn_02004C40(struct Game *game, struct AnimState *spr, void *src)
{
    struct Pos pos;

    if (fn_02006130(lbl_030060F8, src, &pos)) {
        if (pos.z >= 61 && pos.z < 0x4000 && (u16)(pos.x + 16) <= 272 && pos.y >= -16 && pos.y <= 176) {
            pos.z >>= 9;
            fn_02004A18(game, spr, &pos);
        }
    }
}

void fn_02004CAC(struct Game *game, u16 animNo, void *src)
{
    struct Pos pos;

    if (fn_02006130(lbl_030060F8, src, &pos)) {
        if (pos.z >= 61 && pos.z < 0x4000 && (u16)(pos.x + 16) <= 272 && pos.y >= -16 && pos.y <= 176) {
            pos.z >>= 9;
            fn_02004B60(game, (s16)animNo, &pos);
        }
    }
}

static inline void Offset(struct Pos *pos, s16 dx, s16 dy)
{
    pos->x += dx;
    pos->y += dy;
}

void fn_02004D1C(struct Game *game, u16 animNo, void *src, u16 dx, u16 dy, u16 prio)
{
    struct Pos pos;
    struct Point pt;

    if (fn_02006130(lbl_030060F8, src, &pos)) {
        if (pos.z >= 61 && pos.z < 0x4000) {
            Offset(&pos, dx, dy);
            if ((u16)(pos.x + 16) <= 272 && pos.y >= -16 && pos.y <= 176) {
                pt.x = pos.x;
                (&pt)->y = pos.y;
                fn_02004930(game, (s16)animNo, &pt, (s16)prio);
            }
        }
    }
}

void fn_02004DD0(struct Game *game, u8 unitNo, u8 actorNo, struct Chara *chara)
{
    struct AnimState *unit;

    if (chara != NULL) {
        unit = &game->units[unitNo];
        if (unitNo == 0)
            fn_020026EC(unit, chara->unk52 + 46, 0xFF);
        fn_02002700(unit);
        fn_02003454(&game->players[actorNo], chara, unit);
    }
}

u8 fn_02004E20(struct Game *game, u8 no)
{
    return fn_02003CA8(&game->players[no]);
}

s32 fn_02004E38(struct Game *game, u8 no, u8 a)
{
    return fn_0200287C(&game->players[no], a);
}

void fn_02004E54(struct Game *game, u8 no, u8 a)
{
    fn_02002C24(&game->players[no], no, a);
    game->unk19E4++;
    game->unk19E5++;
}

void fn_02004E8C(struct Game *game, s32 count)
{
    s32 i;

    for (i = 0; i < count; i++) {
        fn_020034DC(&game->unk160[i], i);
        game->unk19E4++;
        game->unk19E6++;
    }
    game->unk19E7 = game->unk19E6 + 4;
}

void fn_02004EF0(void)
{
    s32 i;

    for (i = 47; i != -1; i--)
        ;
}

static inline void GetDir(struct Point *dir, u16 angle)
{
    dir->x = lbl_0200EE10[angle >> 5];
    dir->y = lbl_0200EE10[(angle >> 5) + 512];
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

static inline struct RoutePoint *GetRoutePoint(struct Route *route, s16 no)
{
    return &route->pts[no];
}

static inline s16 Distance(struct RoutePoint *pt, struct Pos *pos)
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

static inline void SetFlag0(struct Actor *actor, u8 on)
{
    actor->unk55_0 = on;
}

static inline void SetFlag1(struct Actor *actor, u8 on)
{
    actor->unk55_1 = on;
}

struct Effect *fn_02004F04(struct Game *game)
{
    s32 i;

    for (i = 0; i < 64; i++) {
        if (!game->effects[i].active)
            return &game->effects[i];
    }
    fn_020001A0(lbl_0200EDC8, 28);
    return NULL;
}

struct Effect *fn_02004F34(struct Game *game)
{
    s32 i;

    for (i = 63; i >= 0; i--) {
        if (!game->effects[i].active)
            return &game->effects[i];
    }
    fn_020001A0(lbl_0200EDC8, 42);
    return NULL;
}

void fn_02004F68(struct Effect *e, va_list *ap)
{
    s32 no = va_arg(*ap, s32);
    struct Point *pt = &fn_02006EFC(lbl_030063E0, 1)->pts[(s16)no];

    e->pos.x = pt->x;
    e->pos.z = pt->y;
    e->pos.y = 0;
    e->w.idle.color = fn_02007398() % 3;
    fn_020026B8(&e->anim, lbl_020159AC[e->w.idle.color], 0xFF);
    e->unk8 = 80;
}

void fn_02004FC0(struct Effect *e, va_list *ap)
{
    s32 no = va_arg(*ap, s32);
    struct Point *pt = &fn_02006EFC(lbl_030063E0, 2)->pts[(s16)no];

    e->pos.x = pt->x;
    e->pos.z = pt->y;
    e->pos.y = 0;
    e->w.idle.color = fn_02007398() % 8;
    fn_020026B8(&e->anim, lbl_020159AF[e->w.idle.color], 0xFF);
    e->unk8 = 80;
}

void fn_02005018(struct Effect *e, va_list *ap)
{
    struct Pos *pos;
    struct Point dir;
    s32 speed;

    e->w.chase.unk6 = va_arg(*ap, s32) & 0xFF;
    pos = va_arg(*ap, struct Pos *);
    GetDir(&dir, va_arg(*ap, s32));
    speed = 4800;
    e->w.chase.target = NULL;
    Scale(&e->w.chase.vel, &dir, speed);
    e->w.chase.unk7 = va_arg(*ap, s32) & 0xFF;
    e->w.chase.owner = va_arg(*ap, s32) & 0xFF;
    e->pos = *pos;
}

void fn_020050C0(struct Effect *e, va_list *ap)
{
    struct Point *vel;

    e->pos = *va_arg(*ap, struct Pos *);
    vel = va_arg(*ap, struct Point *);
    fn_020026B8(&e->anim, 38, 0xFF);
    e->w.vel = *vel;
}

void fn_020050F0(struct Effect *e, va_list *ap)
{
    fn_02005018(e, ap);
    fn_020026B8(&e->anim, 30, 0xFF);
    e->unk8 = 80;
    fn_020054A4(&lbl_0202C618, 2, e, &e->w.chase.vel);
}

void fn_02005120(struct Effect *e, va_list *ap)
{
    e->w.target = va_arg(*ap, struct Actor *);
    fn_020026B8(&e->anim, 32, 0xFF);
    fn_02007308(lbl_030063F8, 12, e);
}

void fn_02005150(struct Effect *e, va_list *ap)
{
    struct Point *vel;

    e->pos = *va_arg(*ap, struct Pos *);
    vel = va_arg(*ap, struct Point *);
    fn_020026B8(&e->anim, 38, 11);
    e->w.vel = *vel;
}

void fn_02005180(struct Effect *e, va_list *ap)
{
    fn_02005018(e, ap);
    fn_020026B8(&e->anim, 31, 0xFF);
    e->unk8 = 80;
    fn_020054A4(&lbl_0202C618, 5, e, &e->w.chase.vel);
}

void fn_020051B0(struct Effect *e, va_list *ap)
{
    e->w.target = va_arg(*ap, struct Actor *);
    fn_020026B8(&e->anim, 39, 0xFF);
    fn_02007308(lbl_030063F8, 11, e);
}

void fn_020051E0(struct Effect *e, va_list *ap)
{
    struct Pos *pos;
    struct Pos *vec;
    u16 angle;
    struct Point dir;

    e->w.chase.owner = va_arg(*ap, s32) & 0xFF;
    pos = va_arg(*ap, struct Pos *);
    angle = va_arg(*ap, s32);
    vec = va_arg(*ap, struct Pos *);
    e->pos = *pos;
    e->w.vec = *vec;
    GetDir(&dir, angle);
    e->w.vec.x += MulShift(dir.x, -800);
    e->w.vec.z += MulShift(dir.y, -800);
    e->w.vec.y = 800;
    fn_020026B8(&e->anim, 33, 0xFF);
    e->unk8 = 120;
}

void fn_02005274(struct Effect *e, va_list *ap)
{
    struct Route *route;
    struct RoutePoint *pt;
    s16 v;
    u8 base;

    e->w.idle.owner = va_arg(*ap, s32) & 0xFF;
    e->pos = *va_arg(*ap, struct Pos *);
    e->pos.y = 0;
    fn_020026B8(&e->anim, 34, 0xFF);
    e->unk8 = 120;
    route = fn_02006B68(lbl_030063C8, 0);
    pt = GetRoutePoint(route, fn_02006C94(route, 0xFF, e->pos.x, e->pos.z, &e->w));
    v = Distance(pt, &e->pos);
    base = pt->unk9;
    v = (v << 4) / route->unk2 + base;
    if (v > 255)
        v = 255;
    e->w.idle.color = v;
}

void fn_02005330(struct Effect *e, va_list *ap)
{
    e->w.target = va_arg(*ap, struct Actor *);
    fn_020026B8(&e->anim, 33, 0xFF);
    fn_02007308(lbl_030063F8, 10, e);
}

void fn_02005360(struct Effect *e, va_list *ap)
{
    struct Pos *pos = va_arg(*ap, struct Pos *);
    struct Pos *vel = va_arg(*ap, struct Pos *);

    e->pos = *pos;
    e->w.vel.x = vel->x >> 1;
    e->w.vel.y = vel->z >> 1;
    fn_020026B8(&e->anim, 17, 0xFF);
}

void fn_02005398(struct Effect *e, u8 type, va_list *ap)
{
    fn_0200276C(e);
    e->active = 1;
    e->type = type;
    e->timer = 0;
    e->unk19 = 1;
    switch (e->type) {
    case 0:
        fn_02004F68(e, ap);
        break;
    case 1:
        fn_02004FC0(e, ap);
        break;
    case 2:
        fn_020050C0(e, ap);
        break;
    case 3:
        fn_020050F0(e, ap);
        break;
    case 4:
        fn_02005120(e, ap);
        break;
    case 5:
        fn_02005150(e, ap);
        break;
    case 6:
        fn_02005180(e, ap);
        break;
    case 7:
        fn_020051B0(e, ap);
        break;
    case 8:
        fn_020051E0(e, ap);
        break;
    case 9:
        fn_02005274(e, ap);
        break;
    case 10:
        fn_02005330(e, ap);
        break;
    case 11:
        fn_02005360(e, ap);
        break;
    default:
        fn_020001A0(lbl_0200EDC8, 342);
        break;
    }
}

void fn_02005484(struct Effect *e, u8 type, ...)
{
    va_list ap;

    va_start(ap, type);
    fn_02005398(e, type, &ap);
    va_end(ap);
}

void fn_020054A4(struct Game *game, u8 type, ...)
{
    va_list ap;

    va_start(ap, type);
    fn_02005398(fn_02004F04(game), type, &ap);
    va_end(ap);
}

void fn_020054CC(struct Game *game, u8 type, ...)
{
    va_list ap;

    va_start(ap, type);
    fn_02005398(fn_02004F34(game), type, &ap);
    va_end(ap);
}

s16 fn_020054F4(struct Effect *e, u8 routeNo, u8 *routeIdx, struct Point *vel, struct Homing *param, struct Actor *target, s16 unused)
{
    struct Route *route;
    struct RoutePoint *pt;
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

    route = fn_02006B68(lbl_030063C8, routeNo);
    *routeIdx = fn_02006DF0(route, *routeIdx, e->pos.x, e->pos.z);
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
        f = param->turn * Sqrt(sq);
        vel->x = (MulShift(dir.x, f) + vel->x * (256 - param->turn)) >> 8;
        vel->y = (MulShift(dir.y, f) + vel->y * (256 - param->turn)) >> 8;
        (&acc)->x = (dir.x * param->accel) >> 8;
        (&acc)->y = (dir.y * param->accel) >> 8;
        vel->x += (&acc)->x;
        vel->y += (&acc)->y;
        sq = vel->x * vel->x + vel->y * vel->y;
        speed = Sqrt(sq);
        if (speed > param->maxSpeed) {
            vel->x = vel->x * param->maxSpeed / speed;
            vel->y = vel->y * param->maxSpeed / speed;
            speed = param->maxSpeed;
        }
    } else {
        speed = 0;
    }
    e->pos.x += vel->x >> 4;
    e->pos.z += vel->y >> 4;
    return speed;
}

void fn_020056E8(struct Effect *e)
{
    struct Actor *actor;

    if (e->unk19) {
        actor = fn_02004218(&lbl_0202C618, e, e->unk8, -1);
        if (actor != NULL) {
            fn_02003D14(actor, e->w.idle.color);
            e->unk19 = 0;
            e->w.idle.wait = 90;
        }
    } else if (--e->w.idle.wait == 0) {
        e->w.idle.color = fn_02007398() % 3;
        fn_020026B8(&e->anim, lbl_020159AC[e->w.idle.color], 0xFF);
        e->unk19 = 1;
    }
}

void fn_02005750(struct Effect *e)
{
    struct Actor *actor;

    if (e->unk19) {
        actor = fn_02004218(&lbl_0202C618, e, e->unk8, -1);
        if (actor != NULL) {
            fn_02003D40(actor, e->w.idle.color);
            e->unk19 = 0;
            e->w.idle.wait = 90;
        }
    } else if (--e->w.idle.wait == 0) {
        e->w.idle.color = fn_02007398() % 8;
        fn_020026B8(&e->anim, lbl_020159AF[e->w.idle.color], 0xFF);
        e->unk19 = 1;
    }
}

void fn_020057B8(struct Effect *e, struct Homing *param, s32 mask)
{
    s16 speed;
    struct Actor *target;
    s16 dx;
    s16 dz;
    s32 dist2;
    s16 dist;
    s16 out;
    s16 dot;

    speed = fn_020054F4(e, e->w.chase.unk7, &e->w.chase.owner, &e->w.chase.vel, param, e->w.chase.target, e->w.chase.unk4);
    target = e->w.chase.target;
    if (target == NULL) {
        if (!(e->timer & 3)) {
            s16 vx = (e->w.chase.vel.x << 8) / speed;
            s16 vz = (e->w.chase.vel.y << 8) / speed;

            e->w.chase.target = fn_020043E8(&lbl_0202C618, e, 25000000, &out, vx, vz, 240, mask);
            e->w.chase.unk4 = out;
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
        vx = (e->w.chase.vel.x << 8) / speed;
        vz = (e->w.chase.vel.y << 8) / speed;
        dot = (dx * vx + dz * vz) / dist;
        if (dot <= 220)
            e->w.chase.target = NULL;
    }
}

void fn_02005910(struct Effect *e)
{
    e->pos.x += e->w.vel.x >> 4;
    e->pos.z += e->w.vel.y >> 4;
    if (fn_02002700(&e->anim))
        e->active = 0;
}

void fn_02005944(struct Effect *e)
{
    s32 mask = ~(1 << e->w.chase.unk6);
    struct Actor *actor;

    fn_020057B8(e, &lbl_0200EDE8, mask);
    actor = fn_02004218(&lbl_0202C618, e, e->unk8, mask);
    if (actor != NULL) {
        fn_020054A4(&lbl_0202C618, 2, e, &e->w.chase.vel);
        fn_02005484(e, 4, actor);
    } else if (e->timer++ >= 150) {
        fn_02005484(e, 2, e, &e->w.chase.vel);
    } else {
        fn_02002700(&e->anim);
    }
}

void fn_020059C0(struct Effect *e)
{
    e->pos = e->w.target->pos;
    fn_02002700(&e->anim);
    SetFlag0(e->w.target, 1);
    if (e->timer++ >= 150)
        e->active = 0;
}

void fn_02005A00(struct Effect *e)
{
    e->pos.x += e->w.vel.x >> 4;
    e->pos.z += e->w.vel.y >> 4;
    if (fn_02002700(&e->anim))
        e->active = 0;
}

void fn_02005A34(struct Effect *e)
{
    s32 mask = ~(1 << e->w.chase.unk6);
    struct Actor *actor;

    fn_020057B8(e, &lbl_0200EDFC, mask);
    actor = fn_02004218(&lbl_0202C618, e, e->unk8, mask);
    if (actor != NULL) {
        fn_020054A4(&lbl_0202C618, 5, e, &e->w.chase.vel);
        fn_02005484(e, 7, actor);
    } else if (e->timer++ >= 150) {
        fn_02005484(e, 5, e, &e->w.chase.vel);
    } else {
        fn_02002700(&e->anim);
    }
}

void fn_02005AB0(struct Effect *e)
{
    e->pos = e->w.target->pos;
    fn_02002700(&e->anim);
    SetFlag1(e->w.target, 1);
    if (e->timer++ >= 150)
        e->active = 0;
}

void fn_02005AF0(struct Effect *e)
{
    struct Actor *actor;

    actor = fn_02004218(&lbl_0202C618, e, e->unk8, ~(1 << e->w.chase.owner));
    if (actor != NULL) {
        fn_02005484(e, 10, actor);
    } else if (e->timer++ >= 10) {
        fn_02005484(e, 9, e->w.chase.owner, e);
    } else {
        e->w.vec.y -= 200;
        if (e->pos.y < 0)
            e->w.vec.y = -e->w.vec.y;
        e->pos.x += e->w.vec.x >> 4;
        e->pos.y += e->w.vec.y >> 4;
        e->pos.z += e->w.vec.z >> 4;
    }
}

void fn_02005B7C(struct Effect *e)
{
    s32 mask;
    struct Actor *actor;

    if (e->timer < 60)
        mask = ~(1 << e->w.idle.owner);
    else
        mask = -1;
    actor = fn_02004218(&lbl_0202C618, e, e->unk8, mask);
    if (actor != NULL)
        fn_02005484(e, 10, actor);
    else if (e->timer++ >= 1200)
        e->active = 0;
}

void fn_02005BD0(struct Effect *e)
{
    u8 frame;

    e->pos.x += e->w.vel.x >> 4;
    e->pos.z += e->w.vel.y >> 4;
    e->timer++;
    if (!(e->timer & 1)) {
        frame = e->timer >> 1;
        if (frame == 5)
            e->active = 0;
        else
            fn_020026B8(&e->anim, frame + 17, 0xFF);
    }
}

void fn_02005C1C(struct Effect *e)
{
    struct Actor *target = e->w.target;

    e->pos = target->pos;
    if (e->timer == 0 && target->unk32 == 0) {
        target->unk32 = 30;
        if (fn_02007398() & 1)
            target->unk30 = 0x2000;
        else
            target->unk30 = 0xE000;
    }
    if (e->timer++ >= 30)
        e->active = 0;
}

void fn_02005C6C(struct Effect *e)
{
    switch (e->type) {
    case 0:
        fn_020056E8(e);
        break;
    case 1:
        fn_02005750(e);
        break;
    case 2:
        fn_02005910(e);
        break;
    case 3:
        fn_02005944(e);
        break;
    case 4:
        fn_020059C0(e);
        break;
    case 5:
        fn_02005A00(e);
        break;
    case 6:
        fn_02005A34(e);
        break;
    case 7:
        fn_02005AB0(e);
        break;
    case 8:
        fn_02005AF0(e);
        break;
    case 9:
        fn_02005B7C(e);
        break;
    case 10:
        fn_02005C1C(e);
        break;
    case 11:
        fn_02005BD0(e);
        break;
    default:
        fn_020001A0(lbl_0200EDC8, 876);
        break;
    }
}
