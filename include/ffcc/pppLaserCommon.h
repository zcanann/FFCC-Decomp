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

struct pppLaserColorBlock {
    u8 m_pad0[8];
    pppCVECTOR m_color;
};

struct pppLaserMapCylinder {
    Vec m_bottom;
    Vec m_top;
    Vec m_axis;
    float m_radius;
    Vec m_boundsMin;
    Vec m_boundsMax;
};

#endif // _PPP_LASER_COMMON_H_
