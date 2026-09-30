#include "global.h"
#include "main.h"
#include "camera.h"
#include "field.h"
#include "text.h"
#include "fixmath.h"

void Field_Init(struct Field *field)
{
    field->map = gFieldMap;
    LZ77UnCompWram(gFieldTilesLz, gDecompBuffer);
    DmaSet(gDecompBuffer, VRAM + 0xC000, 0x84002000);
    DmaSet(gBgPalette, PLTT, 0x84000078);
    LZ77UnCompWram(gSkyTilesLz, gDecompBuffer);
    DmaSet(gDecompBuffer, VRAM + 0x4800, 0x84000800);
    REG_BG0CNT = 0xD00;
    gMain.mode7Dirty = 0;
}

void Field_SetupRaceBg(struct Field *field)
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
        map = i != 0 ? (u16 *)(VRAM + 0x7800) : (u16 *)(VRAM + 0x7000);
        for (y = 0; y < 4; y++, map += 32) {
            for (x = 0; x < 32; x++)
                map[x] = tile++ | 0xD000;
        }
    }
}

void Field_SetupMenuBg(struct Field *field)
{
    REG_BG0CNT = 0xD01;
    REG_BG1CNT = 0x2E00;
    REG_BG2CNT = 0xD08E;
    REG_BG1HOFS = 0;
    REG_BG1VOFS = 16;
    gSkyScroll = gSkyScrollPrev = 0;
    LZ77UnCompVram(gSelectBgMapLz, (void *)(VRAM + 0x7000));
    Text_LoadScreen(&gTextLayer, gSelectScreenLz);
}

void Camera_RayFloor(struct Field *field, struct Vec3 *pos, struct Vec3 *dir, struct Vec3 *out)
{
    out->x = pos->x - dir->x * pos->y / dir->y;
    out->y = pos->y - dir->y * pos->y / dir->y;
    out->z = pos->z - dir->z * pos->y / dir->y;
}

static inline void SetVec(struct Vec3 *v, s16 x, s16 y, s16 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* Computes the floor distance of each scanline for the mode 7 projection */
void Floor_BuildDepths(struct Field *field)
{
    struct Vec3 zero;
    struct Vec3 v;
    struct Vec3 out;
    struct Vec3 hit;
    s32 i;
    struct Vec3 *eye;

    SetVec(&zero, 0, 0, 0);
    Camera_Follow(&gCamera, &zero, 0, 0, 1);
    eye = &gCamera.pos;
    gMain.horizon = 0;
    for (i = 0; i < 160; i++) {
        SetVec(&v, 120, i, 160);
        Camera_ScreenToWorld(&gCamera, &v, &out);
        out.x -= eye->x;
        out.y -= eye->y;
        out.z -= eye->z;
        if (out.y < 0) {
            Camera_RayFloor(field, eye, &out, &hit);
            if ((u16)hit.z <= 0x700)
                goto found;
        }
        gMain.horizon = i + 1;
        hit.z = 0;
    found:
        field->depth[i] = hit.z;
        field->scale[i] = hit.z;
        gBgAffine[i].pb = 0;
        gBgAffine[i].pd = 0;
    }
}

/* Copies the 128x128 window of the course map around the camera into the BG2 tile map */
void Field_UpdateMap(struct Field *field)
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
        DmaFill32(0x02020202, gFieldTiles, 0x85001000);
        return;
    }
    bottom = 128;
    top = 0;
    if (y < 0) {
        top = -y;
        DmaFill32(0x02020202, gFieldTiles, 0x85000000 | (top * 32));
        y = 0;
    } else if (y > 128) {
        bottom = 256 - y;
        DmaFill32(0x02020202, gFieldTiles[bottom], 0x85000000 | ((128 - bottom) * 32));
    }
    right = 128;
    left = 0;
    if (x < 0) {
        left = -x;
        for (row = top; row < bottom; row++)
            DmaFill16(0x0202, gFieldTiles[row], 0x81000000 | (left / 2));
        right = 128;
        x = 0;
    } else if (x > 128) {
        right = 256 - x;
        for (row = top; row < bottom; row++)
            DmaFill16(0x0202, &gFieldTiles[row][right], 0x81000000 | ((128 - right) / 2));
        left = 0;
    }
    sy = y;
    for (row = top; row < bottom; row++) {
        DmaSet(field->map[sy] + x, &gFieldTiles[row][left], 0x80000000 | ((right - left) / 2));
        sy++;
    }
}

void Mode7_UpdateAffine(struct Field *field)
{
    struct Camera *cam = &gCamera;
    s16 *origin = &cam->originX;
    s16 *scale;
    s16 idx;
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

    gSkyScroll = cam->yaw >> 6;
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
    aff = gBgAffine;
    x0 = cam->bgX;
    y0 = cam->bgY;
    x0 += ox;
    y0 += oy;
    for (i = 0; i < 160; aff++, i++) {
        pa = (field->scale[i] * xx) >> 8;
        pc = (field->scale[i] * yx) >> 8;
        aff->pa = pa;
        aff->pc = pc;
        d = -field->depth[i];
        aff->x = x0 - 120 * pa - xy * d;
        aff->y = y0 - pc * 120 - yy * d;
    }
    gMain.mode7Dirty = 1;
}

u8 Field_CheckWall(struct Field *field, struct Vec3 *pos, struct Vec3 *vel, s16 *speed)
{
    u16 flags;
    s32 x;
    s32 z;
    s32 bx;
    s32 bz;

    x = pos->x + 0x4000;
    z = pos->z + 0x4000;
    flags = GetTerrain(field, x, z)->flags;
    bx = pos->x - (vel->x >> 5) + 0x4000;
    bz = pos->z - (vel->z >> 5) + 0x4000;
    flags |= GetTerrain(field, bx, bz)->flags;
    if (flags & TERRAIN_WALL) {
        vel->x = vel->z = 0;
        *speed = 0;
    }
    return flags;
}

u8 Field_CheckGround(struct Field *field, struct Vec3 *pos, struct Vec3 *vel, s16 *speed)
{
    const struct Terrain *t;
    s32 x;
    s32 z;
    s16 len;

    x = pos->x + 0x4000;
    z = pos->z + 0x4000;
    t = GetTerrain(field, x, z);
    if (t->flags & TERRAIN_ROUGH) {
        *speed = Sqrt(vel->x * vel->x + vel->z * vel->z);
        len = *speed - (*speed >> 4);
        vel->x = vel->x * len / *speed;
        vel->z = vel->z * len / *speed;
        *speed = len;
    }
    return t->flags;
}

u8 Field_CheckWallAI(struct Field *field, struct Vec3 *pos, struct Vec3 *vel, s16 *speed)
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
    flags = GetTerrain(field, x, z)->flags;
    bx = pos->x - (vel->x >> 5) + 0x4000;
    bz = pos->z - (vel->z >> 5) + 0x4000;
    flags |= GetTerrain(field, bx, bz)->flags;
    if (flags & TERRAIN_WALL) {
        min = 64;
        shift = 1;
    } else if (flags & TERRAIN_ROUGH) {
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
