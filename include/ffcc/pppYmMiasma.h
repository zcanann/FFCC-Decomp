#ifndef _FFCC_PPP_YMMIASMA_H_
#define _FFCC_PPP_YMMIASMA_H_

#include <dolphin/mtx.h>
#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;
struct PARTICLE_DATA;

typedef _pppPObject pppYmMiasma;

struct YmMiasmaDataOffsets {
    s32 _unused0[2];
    s32 m_workOffset;
};

struct VYmMiasma {
    PARTICLE_DATA* m_particles;
    float m_speedDecay;
    u8 m_emitTimer;
    u8 m_pad09[7];
    Vec m_impulse;
    float m_radius;
    float m_radiusVelocity;
    float m_radiusAcceleration;
    Vec m_prevPosition;
    u8 m_prevPositionChanged;
    u8 m_pad35[3];
};

struct PYmMiasma {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_shapeFrameStep;
    u16 m_particleCount;
    u16 m_pad0E;
    f32 m_baseSpeed;
    f32 m_speedVariance;
    f32 m_speedDecayReset;
    f32 m_minDistance;
    f32 m_gravity;
    u8 m_colorStartR;
    u8 m_colorStartG;
    u8 m_colorStartB;
    u8 m_colorStartA;
    s16 m_colorEndR;
    s16 m_colorEndG;
    s16 m_colorEndB;
    s16 m_colorEndA;
    s16 m_colorStepFrames;
    s16 m_pad32;
    f32 m_initialSpeedDecay;
    f32 m_speedDecay;
    f32 m_radiusJitter;
    f32 m_spawnHeightJitter;
    f32 m_heightJitter;
    u8 m_lifeBase;
    u8 m_lifeRange;
    u8 m_pad4A[2];
    f32 m_minSpeed;
    s16 m_fadeFrames;
    s16 m_colorDecayFrames;
};

struct YmMiasmaRenderStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_pad8[4];
    u16 m_particleCount;
    u8 m_pad0E[0x24];
    u8 m_blendMode;
    u8 m_pad33[0x41];
    u8 m_drawEnvA;
    u8 m_drawEnvB;
};

struct YmMiasmaFrameStep : PYmMiasma {
    u8 m_pad54[4];
    f32 m_radiusDelta;
    f32 m_radiusVelocity;
    f32 m_radiusAcceleration;
    u8 m_emitInterval;
    u8 m_pad65;
    s16 m_baseAngle;
    s16 m_angleRange;
    u8 m_pad6A[2];
    f32 m_speedDecayStep;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMiasma(pppYmMiasma*, _pppCtrlTable*);
void pppConstruct2YmMiasma(pppYmMiasma*, _pppCtrlTable*);
void pppDestructYmMiasma(pppYmMiasma*, _pppCtrlTable*);
void pppFrameYmMiasma(pppYmMiasma*, YmMiasmaFrameStep*, _pppCtrlTable*);
void pppRenderYmMiasma(pppYmMiasma*, YmMiasmaRenderStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMIASMA_H_
