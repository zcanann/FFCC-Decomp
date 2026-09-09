#ifndef _PPP_LASER_COMMON_H_
#define _PPP_LASER_COMMON_H_

#include "ffcc/pppPart.h"

struct pppLaserWorkBase {
    float m_length;
    float m_lengthStep;
    float m_graphValue0;
    float m_graphValue1;
    float m_halfWidth;
    float m_graphValue2;
    float m_graphValue3;
    Vec* m_points;
    Vec m_origin;
    u8 m_shapeReady;
    u8 m_hitFrame;
    u8 m_unused2E;
    u8 m_unused2F;
    s16 m_shapeArg0;
    s16 m_shapeArg1;
    s16 m_shapeArg2;
    s16 m_unused36;
    float m_shapeRotation;
};

struct pppLaserWork : pppLaserWorkBase {
    float m_maxLength;
    Vec m_targetPosition;
    u8 m_spawnEnabled;
};

struct pppLaserDataOffsets {
    s32 m_unused0;
    s32 m_colorBlockOffset;
    s32 m_workOffset;
};

struct pppLaserStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    s32 m_stepValue;
    s32 m_arg3;
    union {
        u8 m_payload[0x40];
        struct {
            s32 m_spawnPositionOffset;  // 0x00
            f32 m_lengthStepBase;       // 0x04
            f32 m_lengthStepVelocity;   // 0x08
            f32 m_lengthStepAccel;      // 0x0C
            f32 m_halfWidthBase;        // 0x10
            f32 m_halfWidthVelocity;    // 0x14
            f32 m_halfWidthAccel;       // 0x18
            u8 m_blendMode;             // 0x1C
            u8 m_hitInterval;           // 0x1D
            u8 m_pointCount;            // 0x1E
            u8 m_pad1F;                 // 0x1F
            f32 m_hitRadius;            // 0x20
            f32 m_hitScale;             // 0x24
            u8 m_trailColorR;           // 0x28
            u8 m_trailColorG;           // 0x29
            u8 m_trailColorB;           // 0x2A
            u8 m_trailAlpha;            // 0x2B
            s16 m_shapeFrameStep;       // 0x2C
            u8 m_pad2E[0x02];           // 0x2E
            f32 m_shapeScale;           // 0x30
            f32 m_spawnYOffset;         // 0x34
            u8 m_drawEnvColor0;         // 0x38
            u8 m_drawEnvColor1;         // 0x39
            u8 m_historyFrameCount;     // 0x3A
            u8 m_disableHitCylinder;    // 0x3B
            u8 m_disableHitObject;      // 0x3C
            u8 m_pad3D[0x03];           // 0x3D
        } m_laser;
    };
};

#endif // _PPP_LASER_COMMON_H_
