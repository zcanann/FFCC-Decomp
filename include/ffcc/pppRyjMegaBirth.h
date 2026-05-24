#ifndef _PPP_RYJMEGABIRTH_H_
#define _PPP_RYJMEGABIRTH_H_

#include "ffcc/partMng.h"

struct PRyjMegaBirth
{
    u8 _pad00[0x04];
    s32 m_shapeIndex;             // 0x04
    u32 m_frameStep;              // 0x08
    u8 m_fogIndex;                // 0x0c
    u8 _pad0D;
    u8 m_drawDepthEnabled;        // 0x0e
    u8 _pad0F[0x09];
    float m_drawDepth;            // 0x18
    u8 _pad1C[0x04];
    u16 m_maxParticles;           // 0x20
    u16 m_emitCount;              // 0x22
    u16 m_emitInterval;           // 0x24
    s16 m_life;                   // 0x26
    u8 _pad28;
    u8 m_fadeOutFrames;           // 0x29
    u8 m_spawnMode;               // 0x2a
    u8 m_spread;                  // 0x2b
    float m_colorFrameDeltas[4];  // 0x2c
    float m_colorDeltaAdds[4];    // 0x3c
    u8 _pad4C[0x04];
    float m_sizeStart;            // 0x50
    float m_sizeEnd;              // 0x54
    u8 m_colorRandom[4];          // 0x58
    u8 _pad5C[0x04];
    float m_sizeVelocityX;        // 0x60
    float m_sizeVelocityY;        // 0x64
    u8 _pad68[0x08];
    float m_sizeAccelerationX;    // 0x70
    float m_sizeAccelerationY;    // 0x74
    u8 _pad78[0x08];
    float m_sizeRandomX;          // 0x80
    float m_sizeRandomY;          // 0x84
    u8 _pad88[0x08];
    float m_angleStart;           // 0x90
    float m_angleVelocity;        // 0x94
    float m_angleAcceleration;    // 0x98
    float m_angleRandom;          // 0x9c
    Vec m_baseDirection;          // 0xa0
    u8 _padAC[0x04];
    Vec m_accelerationAxis;       // 0xb0
    u8 _padBC[0x04];
    float m_velocity;             // 0xc0
    float m_velocityStep;         // 0xc4
    float m_velocityRandom;       // 0xc8
    float m_acceleration;         // 0xcc
    float m_accelerationStep;     // 0xd0
    float m_directionSpeed;       // 0xd4
    Vec m_directionScale;         // 0xd8
    u8 _padE4[0x04];
    u8 m_randomMode;              // 0xe8
    u8 m_enableParticleColor;     // 0xe9
    u8 m_sizeFlags;               // 0xea
    u8 m_angleFlags;              // 0xeb
    u8 m_matrixMode;              // 0xec
    u8 m_textureMode;             // 0xed
    u8 m_clampMode;               // 0xee
    u8 _padEF;
    s16 m_pathIndex;              // 0xf0
    u8 m_blendMode;               // 0xf2
    u8 m_lightTarget;             // 0xf3
    u8 _padF4[0x140 - 0xf4];
}; // Size 0x140

struct VRyjMegaBirth
{
    Mtx m_worldMatrix;
    Vec m_accelerationAxis;
    _PARTICLE_DATA* m_particleBlock;
    PARTICLE_WMAT* m_worldMatrixBlock;
    _PARTICLE_COLOR* m_colorBlock;
    s32 m_numParticles;
    u16 m_emitTimer;
    u16 m_meshEmitIndex;
};

struct PRyjMegaBirthOffsets
{
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

void birth(_pppPObject*, VRyjMegaBirth*, PRyjMegaBirth*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(VRyjMegaBirth*, PRyjMegaBirth*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);
void calc_particle(_pppPObject*, VRyjMegaBirth*, PRyjMegaBirth*, VColor*);

#ifdef __cplusplus
extern "C" {
#endif

void pppRyjMegaBirth(_pppPObject*, PRyjMegaBirth*, PRyjMegaBirthOffsets*);
void pppRyjDrawMegaBirth(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable);
void pppRyjMegaBirthCon(_pppPObject*, PRyjMegaBirthOffsets*);
void pppRyjMegaBirthDes(_pppPObject*, PRyjMegaBirthOffsets*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_RYJMEGABIRTH_H_
