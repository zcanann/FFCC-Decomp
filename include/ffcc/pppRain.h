#ifndef _PPP_RAIN_H_
#define _PPP_RAIN_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

typedef _pppPObject pppRain;

struct RainDataOffsets {
    s32 _unused0;
    s32 m_colorDataOffset;
    s32 m_workOffset;
};

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

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructRain(pppRain*, _pppCtrlTable*);
void pppDestructRain(pppRain*, _pppCtrlTable*);
void pppFrameRain(pppRain*, PRain*, _pppCtrlTable*);
void pppRenderRain(pppRain*, PRain*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RAIN_H_
