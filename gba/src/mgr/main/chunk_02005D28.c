#include "gba_types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (va_list)__builtin_next_arg(last))
#define va_end(ap)

#define REG_BG0CNT (*(vu16 *)0x04000008)
#define REG_BG1CNT (*(vu16 *)0x0400000A)
#define REG_BG2CNT (*(vu16 *)0x0400000C)
#define REG_BG1HOFS (*(vu16 *)0x04000014)
#define REG_BG1VOFS (*(vu16 *)0x04000016)
#define REG_KEYINPUT (*(vu16 *)0x04000130)

#define DmaSet(src, dst, cnt) \
    { \
        vu32 *dmaRegs = (vu32 *)0x040000D4; \
        dmaRegs[0] = (u32)(src); \
        dmaRegs[1] = (u32)(dst); \
        dmaRegs[2] = (u32)(cnt); \
        dmaRegs[2]; \
    }

#define DmaCopy16(src, dst, cnt) DmaSet(src, dst, cnt)
#define DmaCopy32(src, dst, cnt) DmaSet(src, dst, cnt)

#define DmaFill16(value, dst, cnt) \
    { \
        vu16 tmp = (vu16)(value); \
        DmaSet(&tmp, dst, cnt); \
    }

#define DmaFill32(value, dst, cnt) \
    { \
        vu32 tmp = (vu32)(value); \
        DmaSet(&tmp, dst, cnt); \
    }

struct Vec {
    s16 x;
    s16 y;
    s16 z;
    s16 w;
};

struct Point {
    s16 x;
    s16 y;
};

struct Actor {
    struct Vec pos;
    u8 unk8[0x3A];
    u16 angle;
    u8 unk44[0x14];
};

struct Game {
    struct Actor players[4];
};

struct Work {
    u8 unk0[4];
    u8 mode;
    u8 unk5[0x3E - 0x5];
    vu16 horizon;
    vu8 unk40;
    u8 unk41[3];
};

struct Camera {
    struct Vec pos;
    struct Vec target;
    struct Vec eye;
    s16 scaleX;
    s16 scaleY;
    s16 originX;
    s16 originZ;
    s32 bgX;
    s32 bgY;
    s16 dist;
    s16 height;
    s16 pitchSin;
    s16 pitchCos;
    s16 pitchSin2;
    s16 pitchCos2;
    s16 yawSin;
    s16 yawCos;
    s16 yawSin2;
    s16 yawCos2;
    s16 centerX;
    s16 centerY;
    s16 focal;
    u16 held;
    u16 pressed;
    u16 yaw;
    u16 pitch;
    u8 player;
    u8 unk4B;
};

struct Floor {
    u32 unk0;
    s16 depth[160];
    s16 depth2[160];
};

struct BgAffine {
    vu16 pa;
    vu16 pb;
    vu16 pc;
    vu16 pd;
    s32 x;
    s32 y;
};

struct Background {
    u8 *buf;
};

struct Map {
    u8 (*cells)[256];
};

struct Terrain {
    u16 flags;
    u16 unk2;
};

struct RoutePoint {
    s16 x;
    s16 z;
    s8 nx;
    s8 nz;
    s8 dx;
    s8 dz;
    u8 unk8;
    u8 unk9;
    u8 unkA[6];
};

struct Route {
    s16 count;
    s16 unk2;
    struct RoutePoint *pts;
};

struct RouteData {
    s16 count;
    u8 unk2[0xA];
    s16 unkC;
    u8 unkE[2];
    struct RoutePoint pts[0];
};

struct PointList {
    s16 count;
    struct Point *pts;
};

struct PointData {
    s16 count;
    struct Point pts[0];
};

struct TextLayer {
    vu16 map[20][32];
    u16 backup[20][32];
    vu8 dirty;
    u8 charmap[128];
};

struct Glyph {
    u16 tile;
    u8 w;
    u8 h;
};

struct Stream {
    s32 size;
    s32 offset;
    u8 *base;
    u8 *chunk;
    u8 *pos;
};

extern char lbl_02010210[];
extern struct Terrain lbl_02013C14[];
extern struct RouteData lbl_02014118;
extern struct RouteData lbl_02014318;
extern struct RouteData lbl_020144C8;
extern struct PointData lbl_02014618;
extern struct PointData lbl_0201463C;
extern struct PointData lbl_02014660;
extern const u32 lbl_02015A4C[2];
extern u8 lbl_020159B8[];
extern struct Glyph lbl_020159F8[];
extern u8 lbl_0201619C[];
extern u8 lbl_0201627C[];
extern u8 lbl_02016480[];
extern u8 lbl_020165F0[];
extern u8 lbl_02016774[];
extern u8 lbl_02016804[];
extern u8 lbl_02016884[];
extern u8 lbl_02016F60[];
extern u8 lbl_0201C324[];
extern u8 lbl_0201D5C4[];
extern u8 lbl_020204EC[];
extern u8 lbl_02021D2C[];
extern u8 lbl_02021D6C[];
extern s16 gSinTable[];
extern struct TextLayer gTextLayer;
extern struct Game gGame;
extern u8 lbl_0202C65A[];
extern vu8 lbl_0202DFFE;
extern u8 lbl_0202E000[];
extern u8 lbl_02030000[];
extern u8 lbl_02038000[];
extern struct Work lbl_03000000;
extern u8 lbl_03000248[128][128];
extern struct BgAffine lbl_03004248[];
extern char lbl_03005148[];
extern vu16 lbl_03005254;
extern vu16 lbl_03005256;
extern u8 lbl_03005D65;
extern u8 lbl_03005D67;
extern struct Camera gCamera;
extern struct Floor lbl_03006144;
extern struct Route lbl_030063C8[];
extern struct PointList lbl_030063E0[];
extern u32 gMtState[624];
extern s32 gMtIndex;

void *memcpy(void *dst, const void *src, unsigned long n);
s32 vsprintf(char *buf, const char *fmt, va_list ap);
void CpuFastSet(const void *src, void *dst, u32 mode);
u16 Sqrt(u32 n);
void LZ77UnCompWram(void *src, void *dst);
void LZ77UnCompVram(void *src, void *dst);
void m4aSongNumStart(u16 n);

void AssertFailed(char *file, s32 line);
void Camera_Follow();
void Camera_SetPitch(struct Camera *cam, u16 pitch);
void Floor_BuildDepths(struct Floor *floor);
void fn_02006FC0(struct TextLayer *layer, u8 pal);
void fn_02007184(struct TextLayer *layer, void *src);
void fn_02007238(struct TextLayer *layer);
s16 FixMul(s16 a, s16 b);
s16 FixInv(s16 a);
void fn_020075BC(struct Stream *s, u8 *buf);
u32 fn_02007664(struct Stream *s);

void Camera_Init(struct Camera *cam)
{
    cam->pos.x = cam->pos.y = cam->pos.z = 0;
    cam->yaw = 0;
    cam->scaleX = cam->scaleY = 0x180;
    cam->centerX = 120;
    cam->centerY = 80;
    cam->focal = 240;
    Camera_SetPitch(cam, 0xF600);
}

static inline s32 IsActive(s32 no)
{
    return (1 << no) & lbl_03005D67;
}

void Camera_Update(struct Camera *cam)
{
    u16 keys = REG_KEYINPUT ^ 0x3FF;
    struct Actor *p;
    u8 mode;

    cam->pressed = keys & ~cam->held;
    cam->held = keys;
    if (cam->pressed & 4) {
        for (;;) {
            cam->player++;
            if (cam->player >= lbl_0202DFFE + 4)
                cam->player = 0;
            if (cam->player > 3 || IsActive(cam->player))
                break;
        }
    }
    mode = lbl_03000000.mode;
    if (mode > 1) {
        if (mode <= 3) {
            Camera_Follow(cam, &gGame.players[cam->player].pos, gGame.players[cam->player].angle, -2000, 0);
            return;
        }
    }
    if (lbl_03000000.mode > 3) {
        cam->yaw += 364;
        p = &gGame.players[cam->player];
        if (cam->held & 0x100)
            Camera_Follow(cam, &p->pos, *(u16 *)&lbl_0202C65A[cam->player * sizeof(struct Actor)], -2000, 0);
        else
            Camera_Follow(cam, &p->pos, cam->yaw, -2000, 0);
    }
}

void Camera_Follow(cam, target, yaw, dist, near)
    struct Camera *cam;
    struct Vec *target;
    u16 yaw;
    u16 dist;
    u8 near;
{
    cam->target = *target;
    cam->target.y = 0;
    if (cam->held & 0x100)
        yaw += 0x8000;
    cam->yaw = yaw;
    cam->yawSin = gSinTable[yaw >> 5];
    cam->yawCos = gSinTable[(cam->yaw >> 5) + 512];
    yaw = -cam->yaw;
    cam->yawSin2 = gSinTable[yaw >> 5];
    cam->yawCos2 = gSinTable[(yaw >> 5) + 512];
    if (near) {
        cam->dist = dist;
        cam->height = 70;
    } else {
        cam->dist = dist;
        cam->height = 280;
    }
    cam->pos.x = cam->target.x + ((cam->dist * cam->yawSin) >> 8);
    cam->pos.y = cam->target.y + cam->height;
    cam->pos.z = cam->target.z + ((cam->dist * cam->yawCos) >> 8);
    cam->eye.x = 0;
    cam->eye.y = cam->height;
    cam->eye.z = cam->dist;
    cam->bgX = -(cam->yawSin << 9) + 0x20000;
    cam->bgY = 0x20000 - cam->yawCos * 512;
    cam->originX = cam->pos.x + cam->yawSin * 32;
    cam->originZ = cam->pos.z + cam->yawCos * 32;
}

void Camera_SetPitch(struct Camera *cam, u16 pitch)
{
    cam->pitch = pitch;
    cam->pitchSin = gSinTable[pitch >> 5];
    cam->pitchCos = gSinTable[(pitch >> 5) + 512];
    cam->pitchSin2 = gSinTable[(u16)-pitch >> 5];
    cam->pitchCos2 = gSinTable[((u16)-pitch >> 5) + 512];
    Floor_BuildDepths(&lbl_03006144);
}

static inline void RotateY(struct Camera *cam, struct Vec *in, struct Vec *out)
{
    out->x = (cam->yawCos2 * in->x - cam->yawSin2 * in->z) >> 8;
    out->y = in->y;
    out->z = (cam->yawSin2 * in->x + cam->yawCos2 * in->z) >> 8;
}

void Camera_Rotate(struct Camera *cam, struct Vec *in, struct Vec *out)
{
    struct Vec tmp[1];

    tmp->x = in->x;
    tmp->y = (cam->pitchCos2 * in->y - cam->pitchSin2 * in->z) >> 8;
    tmp->z = (cam->pitchSin2 * in->y + cam->pitchCos2 * in->z) >> 8;
    RotateY(cam, tmp, out);
}

static inline void AddVec(struct Vec *out, struct Vec *a, struct Vec *b)
{
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}

void Camera_ViewToWorld(struct Camera *cam, struct Vec *in, struct Vec *out)
{
    struct Vec *eye = &cam->eye;
    struct Vec tmp[1];
    struct Vec v;

    tmp->x = in->x + eye->x;
    tmp->y = in->y + eye->y;
    tmp->z = in->z + eye->z;
    v = *tmp;
    Camera_Rotate(cam, &v, out);
    AddVec(out, out, &cam->target);
}

void Camera_ScreenToView(struct Camera *cam, struct Vec *in, struct Vec *out)
{
    out->x = in->z * (in->x - cam->centerX) / cam->focal;
    out->y = in->z * (cam->centerY - in->y) / cam->focal;
    out->z = in->z;
}

u8 Camera_WorldToScreen(struct Camera *cam, struct Vec *in, struct Vec *out)
{
    s16 dx = in->x - cam->target.x;
    s16 dy = in->y - cam->target.y;
    s16 dz = in->z - cam->target.z;
    s16 t;

    t = (cam->yawSin * dx + cam->yawCos * dz) >> 8;
    out->z = ((cam->pitchSin * dy + cam->pitchCos * t) >> 8) - cam->eye.z;
    if (out->z <= 0x400 || out->z >= 0x3000)
        return 0;
    out->x = ((dx * cam->yawCos - dz * cam->yawSin) >> 8) - cam->eye.x;
    if (out->x >= out->z || out->x <= -out->z)
        return 0;
    out->y = ((cam->pitchCos * dy - cam->pitchSin * t) >> 8) - cam->eye.y;
    if (out->y >= out->z || out->y <= -out->z)
        return 0;
    out->x = cam->centerX + out->x * cam->focal / out->z;
    out->y = cam->centerY - out->y * cam->focal / out->z;
    return 1;
}

void Camera_ScreenToWorld(struct Camera *cam, struct Vec *in, struct Vec *out)
{
    struct Vec tmp;

    Camera_ScreenToView(cam, in, &tmp);
    Camera_ViewToWorld(cam, &tmp, out);
}

void fn_02006264(void)
{
}

void fn_02006268(struct Background *bg)
{
    bg->buf = lbl_02030000;
    LZ77UnCompWram(lbl_0201C324, lbl_02038000);
    DmaCopy32(lbl_02038000, 0x0600C000, 0x84002000);
    DmaCopy32(lbl_02021D6C, 0x05000000, 0x84000078);
    LZ77UnCompWram(lbl_0201D5C4, lbl_02038000);
    DmaCopy32(lbl_02038000, 0x06004800, 0x84000800);
    REG_BG0CNT = 0xD00;
    lbl_03000000.unk40 = 0;
}

void fn_020062F8(void)
{
    s32 i;
    s32 y;
    s32 x;
    u16 *map;
    s32 tile;

    REG_BG0CNT = 0xD00;
    REG_BG1CNT = 0x6E02;
    REG_BG2CNT = 0xD08D;
    REG_BG1VOFS = 0;
    tile = 0x240;
    for (i = 0; i < 2; i++) {
        map = i != 0 ? (u16 *)0x06007800 : (u16 *)0x06007000;
        for (y = 0; y < 4; y++, map += 32) {
            for (x = 0; x < 32; x++)
                map[x] = tile++ | 0xD000;
        }
    }
}

void fn_02006374(void)
{
    REG_BG0CNT = 0xD01;
    REG_BG1CNT = 0x2E00;
    REG_BG2CNT = 0xD08E;
    REG_BG1HOFS = 0;
    REG_BG1VOFS = 16;
    lbl_03005256 = lbl_03005254 = 0;
    LZ77UnCompVram(lbl_0201627C, (void *)0x06007000);
    fn_02007184(&gTextLayer, lbl_0201619C);
}

void Camera_RayFloor(struct Floor *floor, struct Vec *pos, struct Vec *dir, struct Vec *out)
{
    out->x = pos->x - dir->x * pos->y / dir->y;
    out->y = pos->y - dir->y * pos->y / dir->y;
    out->z = pos->z - dir->z * pos->y / dir->y;
}

static inline void SetVec(struct Vec *v, s16 x, s16 y, s16 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void Floor_BuildDepths(struct Floor *floor)
{
    struct Vec zero;
    struct Vec v;
    struct Vec out;
    struct Vec hit;
    s32 i;
    struct Vec *eye;

    SetVec(&zero, 0, 0, 0);
    Camera_Follow(&gCamera, &zero, 0, 0, 1);
    eye = &gCamera.pos;
    lbl_03000000.horizon = 0;
    for (i = 0; i < 160; i++) {
        SetVec(&v, 120, i, 160);
        Camera_ScreenToWorld(&gCamera, &v, &out);
        out.x -= eye->x;
        out.y -= eye->y;
        out.z -= eye->z;
        if (out.y < 0) {
            Camera_RayFloor(floor, eye, &out, &hit);
            if ((u16)hit.z <= 0x700)
                goto found;
        }
        lbl_03000000.horizon = i + 1;
        hit.z = 0;
    found:
        floor->depth[i] = hit.z;
        floor->depth2[i] = hit.z;
        lbl_03004248[i].pb = 0;
        lbl_03004248[i].pd = 0;
    }
}

void fn_0200652C(struct Background *bg)
{
    s16 x = ((u16)((gCamera.originX - 0x6000) >> 7) & ~1) + 256;
    s16 y = ((gCamera.originZ - 0x6000) >> 7) + 256;
    s16 top;
    s16 bottom;
    s16 left;
    s16 right;
    u8 row;
    s16 sy;

    if (y <= -128 || y >= 256 || x <= -128 || x >= 256) {
        DmaFill32(0x02020202, lbl_03000248, 0x85001000);
        return;
    }
    bottom = 128;
    top = 0;
    if (y < 0) {
        top = -y;
        DmaFill32(0x02020202, lbl_03000248, 0x85000000 | (top * 32));
        y = 0;
    } else if (y > 128) {
        bottom = 256 - y;
        DmaFill32(0x02020202, lbl_03000248[bottom], 0x85000000 | ((128 - bottom) * 32));
    }
    right = 128;
    left = 0;
    if (x < 0) {
        left = -x;
        for (row = top; row < bottom; row++)
            DmaFill16(0x0202, lbl_03000248[row], 0x81000000 | (left / 2));
        right = 128;
        x = 0;
    } else if (x > 128) {
        right = 256 - x;
        for (row = top; row < bottom; row++)
            DmaFill16(0x0202, &lbl_03000248[row][right], 0x81000000 | ((128 - right) / 2));
        left = 0;
    }
    sy = y;
    for (row = top; row < bottom; row++) {
        DmaCopy16(bg->buf + sy * 256 + x, &lbl_03000248[row][left], 0x80000000 | ((right - left) / 2));
        sy++;
    }
}

void Mode7_UpdateAffine(struct Floor *floor)
{
    struct Camera *cam = &gCamera;
    s16 *origin = &cam->originX;
    s16 *scale;
    u16 idx;
    s16 cos;
    s16 sin;
    s16 xx;
    s16 xy;
    s16 yx;
    s16 yy;
    s32 ox;
    s32 oy;
    s32 x0;
    s32 y0;
    s16 i;
    s16 pa;
    s16 pc;
    struct BgAffine *aff;
    s32 d;

    lbl_03005256 = cam->yaw >> 6;
    scale = &cam->scaleX;
    idx = cam->yaw >> 5;
    cos = gSinTable[idx + 512];
    xx = FixMul(cos, FixInv(scale[0]));
    sin = gSinTable[idx];
    xy = FixMul(sin, FixInv(scale[0]));
    yx = FixMul(-gSinTable[idx], FixInv(scale[1]));
    yy = FixMul(cos, FixInv(scale[1]));
    ox = (u8)origin[0] * 16;
    oy = (origin[1] & 0x7F) * 16;
    aff = lbl_03004248;
    x0 = cam->bgX;
    y0 = cam->bgY;
    x0 += ox;
    y0 += oy;
    for (i = 0; i < 160; aff++, i++) {
        pa = (floor->depth2[i] * xx) >> 8;
        pc = (floor->depth2[i] * yx) >> 8;
        aff->pa = pa;
        aff->pc = pc;
        d = -floor->depth[i];
        aff->x = x0 - 120 * pa - xy * d;
        aff->y = y0 - pc * 120 - yy * d;
    }
    lbl_03000000.unk40 = 1;
}

static inline struct Terrain *GetTerrain(struct Map *map, s32 x, s32 z)
{
    return &lbl_02013C14[map->cells[z >> 7][x >> 7]];
}

u8 fn_0200692C(struct Map *map, struct Vec *pos, struct Vec *vel, s16 *speed)
{
    u16 flags;
    s32 x;
    s32 z;
    s32 bx;
    s32 bz;

    x = pos->x + 0x4000;
    z = pos->z + 0x4000;
    flags = GetTerrain(map, x, z)->flags;
    bx = pos->x - (vel->x >> 5) + 0x4000;
    bz = pos->z - (vel->z >> 5) + 0x4000;
    flags |= GetTerrain(map, bx, bz)->flags;
    if (flags & 1) {
        vel->x = vel->z = 0;
        *speed = 0;
    }
    return flags;
}

u8 fn_020069A0(struct Map *map, struct Vec *pos, struct Vec *vel, s16 *speed)
{
    struct Terrain *t;
    s32 x;
    s32 z;
    s16 len;

    x = pos->x + 0x4000;
    z = pos->z + 0x4000;
    t = GetTerrain(map, x, z);
    if (t->flags & 4) {
        *speed = Sqrt(vel->x * vel->x + vel->z * vel->z);
        len = *speed - (*speed >> 4);
        vel->x = vel->x * len / *speed;
        vel->z = vel->z * len / *speed;
        *speed = len;
    }
    return t->flags;
}

u8 fn_02006A38(struct Map *map, struct Vec *pos, struct Vec *vel, s16 *speed)
{
    u16 flags;
    s32 x;
    s32 z;
    s32 bx;
    s32 bz;
    s16 min;
    s32 shift;
    s16 len;

    x = pos->x + 0x4000;
    z = pos->z + 0x4000;
    flags = GetTerrain(map, x, z)->flags;
    bx = pos->x - (vel->x >> 5) + 0x4000;
    bz = pos->z - (vel->z >> 5) + 0x4000;
    flags |= GetTerrain(map, bx, bz)->flags;
    if (flags & 1) {
        min = 64;
        shift = 1;
    } else if (flags & 4) {
        min = 256;
        shift = 4;
    } else {
        return flags;
    }
    len = (*speed = Sqrt(vel->x * vel->x + vel->z * vel->z)) - (*speed >> shift);
    if (len < min)
        len = min;
    vel->x = vel->x * len / *speed;
    vel->z = vel->z * len / *speed;
    *speed = len;
    return flags;
}

void fn_02006B30(struct Route *routes)
{
    routes[0].count = lbl_02014118.count;
    routes[0].unk2 = lbl_02014118.unkC;
    routes[0].pts = lbl_02014118.pts;
    routes[1].count = lbl_02014318.count;
    routes[1].unk2 = lbl_02014318.unkC;
    routes[1].pts = lbl_02014318.pts;
    routes[2].count = lbl_020144C8.count;
    routes[2].unk2 = lbl_020144C8.unkC;
    routes[2].pts = lbl_020144C8.pts;
}

struct Route *fn_02006B68(struct Route *routes, s16 no)
{
    return &lbl_030063C8[no];
}

static inline struct RoutePoint *GetRoutePoint(struct Route *route, s16 no)
{
    return &route->pts[no];
}

static inline s16 NextPoint(struct Route *route, s16 i)
{
    if (++i >= route->count)
        return 0;
    return i;
}

static inline s16 PrevPoint(struct Route *route, s16 i)
{
    if (--i < 0)
        return route->count - 1;
    return i;
}

s16 fn_02006B78(route, start, x, z)
    struct Route *route;
    s16 start;
    s16 x;
    s16 z;
{
    s16 i = start;
    s16 next = NextPoint(route, i);
    struct RoutePoint *p;
    struct RoutePoint *q;
    s16 dx;
    s16 dz;
    s16 qx;
    s16 qz;
    s32 d;
    s32 side;

    do {
        p = &route->pts[i];
        dx = x - p->x;
        dz = z - p->z;
        side = dx * p->nx + dz * p->nz;
        if (side >= 0) {
            q = &route->pts[next];
            qx = x - q->x;
            qz = z - q->z;
            side = qx * q->nx + qz * q->nz;
            if (side <= 0) {
                d = dx * p->dx + dz * p->dz;
                if (d > -0xA0000 && d < 0xA0000)
                    return i;
            }
        }
        i = next;
        next = NextPoint(route, i);
    } while (i != start);
    return 0xFF;
}

s16 fn_02006C94(route, idx, x, z, dist)
    struct Route *route;
    s16 idx;
    s16 x;
    s16 z;
    s16 *dist;
{
    struct RoutePoint *p;
    struct RoutePoint *q;
    s16 dx;
    s16 dz;
    s16 i;

    if (idx == 0xFF) {
        i = fn_02006B78(route, 0, x, z);
        q = GetRoutePoint(route, i);
        dx = x - q->x;
        dz = z - q->z;
        *dist = (dx * q->dx + dz * q->dz) >> 6;
        return i;
    }
    p = GetRoutePoint(route, idx);
    dx = x - p->x;
    dz = z - p->z;
    *dist = (dx * p->dx + dz * p->dz) >> 6;
    if (dx * p->nx + dz * p->nz < 0)
        return PrevPoint(route, idx);
    i = NextPoint(route, idx);
    q = GetRoutePoint(route, i);
    dx = x - q->x;
    dz = z - q->z;
    if (dx * q->nx + dz * q->nz > 0)
        return i;
    if (*dist <= -0x2800 || *dist >= 0x2800)
        return fn_02006B78(route, i, x, z);
    return idx;
}

s16 fn_02006DF0(route, idx, x, z)
    struct Route *route;
    s16 idx;
    s16 x;
    s16 z;
{
    struct RoutePoint *q;
    s16 dx;
    s16 dz;
    s16 i;

    if (idx == 0xFF)
        return fn_02006B78(route, 0, x, z);
    i = NextPoint(route, idx);
    q = &route->pts[i];
    dx = x - q->x;
    dz = z - q->z;
    if (dx * q->nx + dz * q->nz >= 0)
        return i;
    return idx;
}

s32 fn_02006E74(route, idx, vx, vz)
    struct Route *route;
    s16 idx;
    s16 vx;
    s16 vz;
{
    struct RoutePoint *p = &route->pts[idx];
    struct RoutePoint *q = &route->pts[NextPoint(route, idx)];

    return vx * (q->x - p->x) + vz * (q->z - p->z);
}

void fn_02006ED0(struct PointList *lists)
{
    lists[0].count = lbl_02014618.count;
    lists[0].pts = lbl_02014618.pts;
    lists[1].count = lbl_0201463C.count;
    lists[1].pts = lbl_0201463C.pts;
    lists[2].count = lbl_02014660.count;
    lists[2].pts = lbl_02014660.pts;
}

struct PointList *fn_02006EFC(struct PointList *lists, s16 no)
{
    return &lbl_030063E0[no];
}

void fn_02006F0C(struct TextLayer *layer)
{
    u32 i;
    u8 *str;
    u8 c;
    u8 no;

    for (i = 0; i < 128; i++)
        layer->charmap[i] = 15;
    str = lbl_020159B8;
    no = 0;
    while ((c = *str++) != 0) {
        if ((u8)(c - 'A') <= 'Z' - 'A')
            layer->charmap[c + 32] = no;
        layer->charmap[c] = no++;
    }
    fn_02007238(layer);
    LZ77UnCompWram(lbl_020204EC, lbl_02038000);
    DmaCopy32(lbl_02038000, 0x06001000, 0x84000E00);
    DmaCopy32(lbl_02021D2C, 0x050001C0, 0x84000010);
    fn_02006FC0(layer, 15);
}

void fn_02006FC0(struct TextLayer *layer, u8 pal)
{
    u16 fill = (pal << 12) | 22;

    DmaFill16(fill, layer, 0x81000280);
    layer->dirty = 1;
}

void fn_02006FF8(struct TextLayer *layer, s32 x, s32 y, u16 id, u16 pal)
{
    u16 attr = pal << 12;
    struct Glyph *g = &lbl_020159F8[id];
    s32 x1 = x + g->w;
    s32 y1 = y + g->h;
    u16 tile = g->tile;
    u16 t;
    s32 i;

    for (; y < y1; y++) {
        t = tile;
        tile = t + 32;
        for (i = x; i < x1; i++, t++)
            layer->map[y][i] = attr | t;
    }
    layer->dirty = 1;
}

void fn_02007088(struct TextLayer *layer, s32 x, s32 y, u16 id)
{
    u16 blank = 0xF016;
    struct Glyph *g = &lbl_020159F8[id];
    s32 x1 = x + g->w;
    s32 y1 = y + g->h;
    s32 i;

    for (; y < y1; y++) {
        for (i = x; i < x1; i++)
            layer->map[y][i] = blank;
    }
    layer->dirty = 1;
}

void fn_020070F8(struct TextLayer *layer, s32 x, s32 y, u16 pal, u8 *str)
{
    u16 attr = pal << 12;
    u8 c;

    while ((c = *str++) != 0) {
        layer->map[y][x] = (layer->charmap[c] + 0x200) | attr;
        x++;
    }
    layer->dirty = 1;
}

void Text_Printf(struct TextLayer *layer, s32 x, s32 y, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsprintf(lbl_03005148, fmt, ap);
    fn_020070F8(layer, x, y, 14, lbl_03005148);
    va_end(ap);
}

void fn_02007184(struct TextLayer *layer, void *src)
{
    LZ77UnCompWram(src, layer);
    layer->dirty = 1;
}

void fn_020071A4(struct TextLayer *layer, void *src, u8 row)
{
    LZ77UnCompWram(src, (void *)layer->map[row]);
    layer->dirty = 1;
}

void fn_020071C8(struct TextLayer *layer)
{
    DmaCopy32(layer, layer->backup, 0x84000140);
}

void fn_020071E4(struct TextLayer *layer)
{
    DmaCopy32(layer->backup, layer, 0x84000140);
    layer->dirty = 1;
}

void Text_Flush(struct TextLayer *layer)
{
    if (layer->dirty) {
        CpuFastSet(layer, (void *)0x06006800, 0x140);
        layer->dirty = 0;
    }
}

void fn_02007238(struct TextLayer *layer)
{
    LZ77UnCompWram(lbl_02016884, lbl_0202E000);
    DmaCopy32(lbl_0202E000, 0x06000000, 0x84000400);
}

void fn_0200726C(struct TextLayer *layer)
{
    LZ77UnCompWram(lbl_02016F60, lbl_0202E000);
    DmaCopy32(lbl_0202E000, 0x06000000, 0x84000400);
    fn_02007184(layer, lbl_020165F0);
}

void fn_020072AC(struct TextLayer *layer, u8 which)
{
    if (which == 0)
        fn_020071A4(layer, lbl_02016774, 5);
    else
        fn_020071A4(layer, lbl_02016804, 5);
}

void fn_020072D4(struct TextLayer *layer)
{
    fn_02007184(layer, lbl_02016480);
}

void fn_020072E4(void)
{
}

void fn_020072E8(struct Vec *pos)
{
    struct Actor *actor = &gGame.players[lbl_03005D65];

    *pos = actor->pos;
}

void PlaySong(void *snd, u16 song, void *owner)
{
    m4aSongNumStart(song);
}

void fn_02007318(void)
{
}

void sgenrand(u32 seed)
{
    s32 i;

    for (i = 0; i < 624; i++) {
        gMtState[i] = seed & 0xFFFF0000;
        seed = 69069 * seed + 1;
        gMtState[i] |= (seed & 0xFFFF0000) >> 16;
        seed = 69069 * seed + 1;
    }
    gMtIndex = 624;
}

void lsgenrand(u32 *seeds)
{
    s32 i;

    for (i = 0; i < 624; i++)
        gMtState[i] = seeds[i];
    gMtIndex = 624;
}

u32 genrand(void)
{
    u32 y;
    s32 kk;

    if (gMtIndex >= 624) {
        if (gMtIndex == 625)
            sgenrand(4357);
        for (kk = 0; kk < 624 - 397; kk++) {
            y = (gMtState[kk] & 0x80000000) | (gMtState[kk + 1] & 0x7FFFFFFF);
            gMtState[kk] = gMtState[kk + 397] ^ (y >> 1) ^ lbl_02015A4C[y & 1];
        }
        for (; kk < 623; kk++) {
            y = (gMtState[kk] & 0x80000000) | (gMtState[kk + 1] & 0x7FFFFFFF);
            gMtState[kk] = gMtState[kk + (397 - 624)] ^ (y >> 1) ^ lbl_02015A4C[y & 1];
        }
        y = (gMtState[623] & 0x80000000) | (gMtState[0] & 0x7FFFFFFF);
        gMtState[623] = gMtState[396] ^ (y >> 1) ^ lbl_02015A4C[y & 1];
        gMtIndex = 0;
    }
    y = gMtState[gMtIndex++];
    y ^= y >> 11;
    y ^= (y << 7) & 0x9D2C5680;
    y ^= (y << 15) & 0xEFC60000;
    y ^= y >> 18;
    return y;
}

s16 FixMul(s16 a, s16 b)
{
    s32 v = a * b;

    v /= 256;
    return v;
}

s16 FixDiv(s16 a, s16 b)
{
    return (a << 8) / b;
}

s16 FixInv(s16 a)
{
    s32 n = 0x10000;

    return n / a;
}

s16 AngleDiff(s16 a, s16 b)
{
    s32 d = (a - b) & 0xFFFF;

    if (d > 0x8000)
        return d - 0x10000;
    return d;
}

s16 TurnToward(s16 from, s16 to, s16 max)
{
    s16 d = AngleDiff(to, from);

    if (d > 0) {
        if (d > max)
            return max;
        return d;
    }
    if (d < 0) {
        max = -max;
        if (d < max)
            return max;
        return d;
    }
    return 0;
}

s16 FixLerp(s16 a, s16 b, s16 t)
{
    return a + (((s16)(b - a) * t) >> 8);
}

void fn_020075A8(void)
{
}

struct Stream *fn_020075AC(struct Stream *s, u8 *buf)
{
    fn_020075BC(s, buf);
    return s;
}

void fn_020075BC(struct Stream *s, u8 *buf)
{
    if (buf == NULL)
        AssertFailed(lbl_02010210, 41);
    s->base = buf;
    s->chunk = buf;
    s->offset = 0;
    s->size = -1;
}

s32 fn_020075E4(struct Stream *s, u32 *hdr)
{
    s32 skip = s->size < 0 ? 0 : s->size + 8;

    s->offset += skip;
    s->chunk += skip;
    s->pos = s->chunk;
    hdr[0] = fn_02007664(s);
    if (hdr[0] == 0x454E4420)
        return 0;
    hdr[1] = fn_02007664(s);
    s->size = hdr[1];
    return 1;
}

u8 *fn_0200762C(struct Stream *s)
{
    return s->pos;
}

void fn_02007630(struct Stream *s, void *dst, u32 n)
{
    memcpy(dst, s->pos, n);
    s->pos += n;
}

u8 fn_0200764C(struct Stream *s)
{
    return *s->pos++;
}

u16 fn_02007658(struct Stream *s)
{
    u16 v = *(u16 *)s->pos;

    s->pos += 2;
    return v;
}

u32 fn_02007664(struct Stream *s)
{
    u32 v = *(u32 *)s->pos;

    s->pos += 4;
    return v;
}

u32 fn_02007670(struct Stream *s)
{
    return fn_02007664(s);
}

u32 fn_0200767C(struct Stream *s)
{
    s32 shift = 0;
    u32 v = 0;
    u8 b;

    do {
        b = fn_0200764C(s);
        v += b << shift;
        shift += 7;
    } while (b & 0x80);
    return v;
}

char *fn_020076A8(struct Stream *s)
{
    char *str = (char *)s->pos;

    while (fn_0200764C(s) != 0)
        ;
    return str;
}

void fn_020076C4(struct Stream *s, u32 align)
{
    s32 n = s->pos - s->base;

    n += align - 1;
    n -= n % align;
    s->pos = s->base + n;
}

void fn_020076E4(struct Stream *s, s32 n)
{
    s->pos += n;
}
