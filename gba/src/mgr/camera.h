#ifndef GUARD_CAMERA_H
#define GUARD_CAMERA_H

#include "global.h"

struct Camera {
    Camera() {}

    void Init();
    void Update();
    void Follow(struct Vec3 *at, u16 angle, s16 distance, u8 near);
    void SetPitch(u16 angle);
    void Rotate(struct Vec3 *in, struct Vec3 *out);
    void ViewToWorld(struct Vec3 *in, struct Vec3 *out);
    void ScreenToView(struct Vec3 *in, struct Vec3 *out);
    u8 WorldToScreen(struct Vec3 *in, struct Vec3 *out);
    void ScreenToWorld(struct Vec3 *in, struct Vec3 *out);

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

#endif
