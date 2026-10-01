#ifndef GUARD_CAMERA_H
#define GUARD_CAMERA_H

#include "global.h"

struct Camera {
    struct Vec3 pos;
    struct Vec3 target;
    struct Vec3 eye;
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
};

extern struct Camera gCamera;


void Camera_Init(struct Camera *cam);
void Camera_Update(struct Camera *cam);
void Camera_Follow(struct Camera *cam, struct Vec3 *target, int yaw, int dist, int near);
void Camera_SetPitch(struct Camera *cam, u16 pitch);
void Camera_Rotate(struct Camera *cam, struct Vec3 *in, struct Vec3 *out);
void Camera_ViewToWorld(struct Camera *cam, struct Vec3 *in, struct Vec3 *out);
void Camera_ScreenToView(struct Camera *cam, struct Vec3 *in, struct Vec3 *out);
u8 Camera_WorldToScreen(struct Camera *cam, struct Vec3 *in, struct Vec3 *out);
void Camera_ScreenToWorld(struct Camera *cam, struct Vec3 *in, struct Vec3 *out);
void Camera_StaticInit(void);

#endif
