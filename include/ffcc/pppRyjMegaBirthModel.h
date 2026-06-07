#ifndef _PPP_RYJMEGABIRTHMODEL_H_
#define _PPP_RYJMEGABIRTHMODEL_H_

#include "ffcc/partMng.h"

struct PRyjMegaBirthModel
{
    u8 _pad00[0x04];
    s32 m_modelIndex;             // 0x04
    u8 _pad08;
    u8 m_fogIndex;                // 0x09
    u8 _pad0A[0x03];
    u8 m_useEnvDepth;             // 0x0D
    u8 _pad0E[0x0A];
    float m_drawDepth;            // 0x18
    u8 _pad1C[0x04];
    u16 m_maxParticles;           // 0x20
    u16 m_emitCount;              // 0x22
    u16 m_emitInterval;           // 0x24
    u16 m_life;                   // 0x26
    u8 m_fadeOutFrames;           // 0x28
    u8 m_fadeInFrames;            // 0x29
    u8 m_spawnMode;               // 0x2A
    u8 m_spread;                  // 0x2B
    u8 m_colorRandom[4];          // 0x2C
    u8 _pad30[0x0C];
    float m_colorDeltaAdds[4];    // 0x3C
    u8 _pad4C[0x70];
    float m_colorFrameDeltas[4];  // 0xBC
    u8 _padCC[0x0C];
    float m_texScrollUStepDelta;  // 0xD8
    float m_texScrollVStart;      // 0xDC
    float m_texScrollUStep;       // 0xE0
    float m_texScrollVStep;       // 0xE4
    Vec m_baseDirection;          // 0xE8
    u8 _padF4[0x04];
    Vec m_accelerationAxis;       // 0xF8
    u8 _pad104[0x04];
    float m_directionVelocityStart; // 0x108
    float m_directionVelocityStep;  // 0x10C
    float m_directionVelocityRandom; // 0x110
    float m_acceleration;          // 0x114
    float m_accelerationStep;      // 0x118
    float m_speed;                // 0x11C
    Vec m_directionScale;         // 0x120
    u8 _pad12C[0x04];
    u8 m_speedMode;               // 0x130
    u8 m_enableParticleColor;     // 0x131
    u8 m_rotationRandomFlags;     // 0x132
    u8 m_scaleRandomFlags;        // 0x133
    u8 m_texScaleRandomMode;      // 0x134
    u8 m_matrixMode;              // 0x135
    u8 m_enableWorldMatrix;       // 0x136
    u8 m_matrixFinalizeMode;      // 0x137
    u8 _pad138[0x02];
    u8 m_zEnable;                 // 0x13A
    u8 m_clampDirectionalSpeed;   // 0x13B
    u8 m_blendMode;               // 0x13C
    u8 m_cullMode;                // 0x13D
    u8 _pad13E;
    u8 m_lightTarget;             // 0x13F
}; // Size 0x140

struct VRyjMegaBirthModel
{
    Vec m_accelerationAxis;
    _PARTICLE_DATA* m_particleBlock;
    _PARTICLE_WMAT* m_worldMatrixBlock;
    _PARTICLE_COLOR* m_colorBlock;
    s32 m_numParticles;
    u16 m_emitTimer;
    u16 m_unused1E;
    Vec m_previousPosition;
    Vec m_currentPosition;
};

struct PRyjMegaBirthModelOffsets
{
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

struct RyjMegaBirthModelDataOffsets {
    s32 m_unusedOffset;
    s32 m_colorOffset;
    s32 m_workOffset;
};

void calc_particle(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, VColor*);
void birth(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);
void set_matrix(_pppPObject*, pppFMATRIX, pppFMATRIX, PRyjMegaBirthModel*, _PARTICLE_DATA*, _PARTICLE_WMAT*, pppFMATRIX&, unsigned char);

#ifdef __cplusplus
extern "C" {
#endif

void pppRyjMegaBirthModel(_pppPObject*, PRyjMegaBirthModel*, PRyjMegaBirthModelOffsets*);
void pppRyjDrawMegaBirthModel(_pppPObject* obj, PRyjMegaBirthModel* stepData, _pppCtrlTable* ctrlTable);
void pppRyjMegaBirthModelCon(_pppPObject*, PRyjMegaBirthModelOffsets*);
void pppRyjMegaBirthModelDes(_pppPObject*, PRyjMegaBirthModelOffsets*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RYJMEGABIRTHMODEL_H_
