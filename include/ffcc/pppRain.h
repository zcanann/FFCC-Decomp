#ifndef _PPP_RAIN_H_
#define _PPP_RAIN_H_

#include <dolphin/types.h>

struct pppRain {
    u8 _pad0[0x0C];
    s32 m_graphId;
    u8 _pad10[0x70];
};

struct VRain;

struct PRain {
    s32 m_graphId;
    u16 m_dataValIndex;
    u8 _pad0[2];
    f32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    f32 m_unk14;
    f32 m_moveYDelta;
    f32 m_accelYDelta;
    f32 m_accelZDelta;
    f32 m_driftY;
    u16 m_lifeBase;
    u16 m_lifeRange;
    u8 _pad2c[0x30 - 0x2C];
    f32 m_minX;
    f32 m_unk34;
    f32 m_minZ;
    f32 m_unk3c;
    f32 m_maxX;
    f32 m_maxY;
    f32 m_maxZ;
    u8 _pad4c[0x50 - 0x4C];
    u8 m_lineWidth;
    u8 _pad51[3];
    f32 m_lengthBase;
    f32 m_lengthRand;
    u8 m_blendMode;
    u8 m_fogIndex;
    u8 m_lightTarget;
    u8 _pad63;
};

struct RAIN_DATA {
    u8 padding[0xc];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructRain(struct pppRain*, struct RAIN_DATA*);
void pppDestructRain(struct pppRain*, struct RAIN_DATA*);
void pppFrameRain(struct pppRain*, struct PRain*, struct RAIN_DATA*);
void pppRenderRain(struct pppRain*, struct PRain*, struct RAIN_DATA*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RAIN_H_
