#include "global.h"
#include "main.h"
#include "joybus.h"
#include "obj.h"
#include "camera.h"
#include "fixmath.h"
#include "field.h"

struct Camera gCamera;

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
    return (1 << no) & *(u8 *)&gPlayerMask;
}

void Camera_Update(struct Camera *cam)
{
    u16 keys = REG_KEYINPUT ^ KEY_MASK;
    struct Actor *p;
    u8 state;

    cam->pressed = keys & ~cam->held;
    cam->held = keys;
    if (cam->pressed & SELECT_BUTTON) {
        for (;;) {
            cam->player++;
            if (cam->player >= gGameEnemyCount + 4)
                cam->player = 0;
            if (cam->player > 3 || IsActive(cam->player))
                break;
        }
    }
    state = gMain.state;
    if (state > STATE_SELECT) {
        if (state <= STATE_RACE) {
            Camera_Follow(cam, &gGame.actors[cam->player].pos, gGame.actors[cam->player].heading, -2000, 0);
            return;
        }
    }
    if (gMain.state > STATE_RACE) {
        cam->yaw += 364;
        p = &gGame.actors[cam->player];
        if (cam->held & R_BUTTON)
            Camera_Follow(cam, &p->pos, (gActorHeading + cam->player)->value, -2000, 0);
        else
            Camera_Follow(cam, &p->pos, cam->yaw, -2000, 0);
    }
}

void Camera_Follow(cam, target, yaw, dist, near)
    struct Camera *cam;
    struct Vec3 *target;
    u16 yaw;
    u16 dist;
    u8 near;
{
    cam->target = *target;
    cam->target.y = 0;
    if (cam->held & R_BUTTON)
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
    Floor_BuildDepths(&gField);
}

static inline void RotateY(struct Camera *cam, struct Vec3 *in, struct Vec3 *out)
{
    out->x = (cam->yawCos2 * in->x - cam->yawSin2 * in->z) >> 8;
    out->y = in->y;
    out->z = (cam->yawSin2 * in->x + cam->yawCos2 * in->z) >> 8;
}

void Camera_Rotate(struct Camera *cam, struct Vec3 *in, struct Vec3 *out)
{
    struct Vec3 tmp[1];

    tmp->x = in->x;
    tmp->y = (cam->pitchCos2 * in->y - cam->pitchSin2 * in->z) >> 8;
    tmp->z = (cam->pitchSin2 * in->y + cam->pitchCos2 * in->z) >> 8;
    RotateY(cam, tmp, out);
}

static inline void AddVec(struct Vec3 *out, struct Vec3 *a, struct Vec3 *b)
{
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}

void Camera_ViewToWorld(struct Camera *cam, struct Vec3 *in, struct Vec3 *out)
{
    struct Vec3 *eye = &cam->eye;
    struct Vec3 tmp[1];
    struct Vec3 v;

    tmp->x = in->x + eye->x;
    tmp->y = in->y + eye->y;
    tmp->z = in->z + eye->z;
    v = *tmp;
    Camera_Rotate(cam, &v, out);
    AddVec(out, out, &cam->target);
}

void Camera_ScreenToView(struct Camera *cam, struct Vec3 *in, struct Vec3 *out)
{
    out->x = in->z * (in->x - cam->centerX) / cam->focal;
    out->y = in->z * (cam->centerY - in->y) / cam->focal;
    out->z = in->z;
}

u8 Camera_WorldToScreen(struct Camera *cam, struct Vec3 *in, struct Vec3 *out)
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

void Camera_ScreenToWorld(struct Camera *cam, struct Vec3 *in, struct Vec3 *out)
{
    struct Vec3 tmp;

    Camera_ScreenToView(cam, in, &tmp);
    Camera_ViewToWorld(cam, &tmp, out);
}

void Camera_StaticInit(void)
{
}
