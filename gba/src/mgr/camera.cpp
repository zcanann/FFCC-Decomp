#include "global.h"
#include "main.h"
#include "obj.h"
#include "camera.h"
#include "fixmath.h"
#include "field.h"

extern u8 gPlayerMask;

static inline s32 IsActive(u16 no)
{
    return (1 << no) & gPlayerMask;
}

struct Camera gCamera;

void Camera::Init()
{
    pos.x = pos.y = pos.z = 0;
    yaw = 0;
    scaleX = scaleY = 0x180;
    centerX = 120;
    centerY = 80;
    focal = 240;
    SetPitch(0xF600);
}

void Camera::Update()
{
    u16 keys = REG_KEYINPUT ^ KEY_MASK;
    struct Actor *p;
    u8 state;

    pressed = keys & ~held;
    held = keys;
    if (pressed & SELECT_BUTTON) {
        for (;;) {
            player++;
            if (player >= *(vu8 *)&gGame.enemyCount + 4)
                player = 0;
            if (player > 3 || IsActive(player))
                break;
        }
    }
    state = gMain.state;
    if (state > STATE_SELECT) {
        if (state <= STATE_RACE) {
            Follow(&gGame.actors[player].pos, gGame.actors[player].heading, -2000, 0);
            return;
        }
    }
    if (gMain.state > STATE_RACE) {
        yaw += 364;
        p = &gGame.actors[player];
        if (held & R_BUTTON)
            Follow(&p->pos, p->heading, -2000, 0);
        else
            Follow(&p->pos, yaw, -2000, 0);
    }
}

void Camera::Follow(struct Vec3 *at, u16 angle, s16 distance, u8 near)
{
    target = *at;
    target.y = 0;
    if (held & R_BUTTON)
        angle += 0x8000;
    yaw = angle;
    yawSin = gSinTable[angle >> 5];
    yawCos = gSinTable[(yaw >> 5) + 512];
    angle = -yaw;
    yawSin2 = gSinTable[angle >> 5];
    yawCos2 = gSinTable[(angle >> 5) + 512];
    if (near) {
        dist = distance;
        height = 70;
    } else {
        dist = distance;
        height = 280;
    }
    pos.x = target.x + ((dist * yawSin) >> 8);
    pos.y = target.y + height;
    pos.z = target.z + ((dist * yawCos) >> 8);
    eye.x = 0;
    eye.y = height;
    eye.z = dist;
    bgX = -(yawSin << 9) + 0x20000;
    bgY = 0x20000 - yawCos * 512;
    originX = pos.x + yawSin * 32;
    originZ = pos.z + yawCos * 32;
}

void Camera::SetPitch(u16 angle)
{
    pitch = angle;
    pitchSin = gSinTable[angle >> 5];
    pitchCos = gSinTable[(angle >> 5) + 512];
    pitchSin2 = gSinTable[(u16)-angle >> 5];
    pitchCos2 = gSinTable[((u16)-angle >> 5) + 512];
    Floor_BuildDepths(&gField);
}

static inline void RotateY(struct Camera *cam, struct Vec3 *in, struct Vec3 *out)
{
    out->x = (cam->yawCos2 * in->x - cam->yawSin2 * in->z) >> 8;
    out->y = in->y;
    out->z = (cam->yawSin2 * in->x + cam->yawCos2 * in->z) >> 8;
}

void Camera::Rotate(struct Vec3 *in, struct Vec3 *out)
{
    struct Vec3 tmp[1];

    tmp->x = in->x;
    tmp->y = (pitchCos2 * in->y - pitchSin2 * in->z) >> 8;
    tmp->z = (pitchSin2 * in->y + pitchCos2 * in->z) >> 8;
    RotateY(this, tmp, out);
}

static inline void AddVec(struct Vec3 *out, struct Vec3 *a, struct Vec3 *b)
{
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}

void Camera::ViewToWorld(struct Vec3 *in, struct Vec3 *out)
{
    struct Vec3 *ofs = &eye;
    struct Vec3 tmp[1];
    struct Vec3 v;

    tmp->x = in->x + ofs->x;
    tmp->y = in->y + ofs->y;
    tmp->z = in->z + ofs->z;
    v = *tmp;
    Rotate(&v, out);
    AddVec(out, out, &target);
}

void Camera::ScreenToView(struct Vec3 *in, struct Vec3 *out)
{
    out->x = in->z * (in->x - centerX) / focal;
    out->y = in->z * (centerY - in->y) / focal;
    out->z = in->z;
}

u8 Camera::WorldToScreen(struct Vec3 *in, struct Vec3 *out)
{
    s16 dx = in->x - target.x;
    s16 dy = in->y - target.y;
    s16 dz = in->z - target.z;
    s16 t;

    t = (yawSin * dx + yawCos * dz) >> 8;
    out->z = ((pitchSin * dy + pitchCos * t) >> 8) - eye.z;
    if (out->z <= 0x400 || out->z >= 0x3000)
        return 0;
    out->x = ((dx * yawCos - dz * yawSin) >> 8) - eye.x;
    if (out->x >= out->z || out->x <= -out->z)
        return 0;
    out->y = ((pitchCos * dy - pitchSin * t) >> 8) - eye.y;
    if (out->y >= out->z || out->y <= -out->z)
        return 0;
    out->x = centerX + out->x * focal / out->z;
    out->y = centerY - out->y * focal / out->z;
    return 1;
}

void Camera::ScreenToWorld(struct Vec3 *in, struct Vec3 *out)
{
    struct Vec3 tmp;

    ScreenToView(in, &tmp);
    ViewToWorld(&tmp, out);
}
