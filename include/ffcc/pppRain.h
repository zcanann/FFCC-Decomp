#ifndef _PPP_RAIN_H_
#define _PPP_RAIN_H_

#include <dolphin/types.h>

struct pppRain {
    u8 field_0x0[0x80];
};

struct VRain;

struct RainParam {
    float pad0;
    float moveYDelta;
    float accelYDelta;
    float accelZDelta;
    float driftY;
    u16 lifeBase;
    u16 lifeRange;
    u8 pad1[0x1c - 0x18];
    float minX;
    float minZ;
    float maxX;
    float maxY;
    float maxZ;
    u8 pad2[0x3c - 0x30];
    u8 lineWidth;
    u8 pad3[3];
    float lengthBase;
    float lengthRand;
    u8 blendMode;
    u8 fogIndex;
    u8 lightTarget;
    u8 pad4;
};

struct PRain {
    s32 m_graphId;
    u16 m_dataValIndex;
    u8 _pad0[2];
    f32 m_initWOrk;
    f32 m_stepValue;
    f32 m_arg3;
    RainParam m_payload;
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
