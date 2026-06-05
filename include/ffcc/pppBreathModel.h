#ifndef _FFCC_PPBBREATHMODEL_H_
#define _FFCC_PPBBREATHMODEL_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppBreathModel;

struct PBreathModel {
    int m_graphId;
    float m_groupRadius;
    float m_groupOwnerScale;
    int m_stepValue;
    u16 m_slotCount;
    u16 m_groupCount;
    float m_groupSpeed;
    u8 m_blendMode;
    u8 _pad19;
    u16 m_particleCount;
    u16 m_emitCount;
    u16 m_emitInterval;
    u16 m_particleLifetime;
    u8 m_fadeOutFrames;
    u8 m_fadeInFrames;
    unsigned char _pad24[0x04];
    float m_colorFrameDelta0;
    float m_colorFrameDelta1;
    float m_colorFrameDelta2;
    float m_colorFrameDelta3;
    float m_colorFrameAccel0;
    float m_colorFrameAccel1;
    float m_colorFrameAccel2;
    float m_colorFrameAccel3;
    unsigned char _pad48[0x08];
    float m_rotationStartX;
    float m_rotationStartY;
    float m_rotationStartZ;
    unsigned char _pad5C[0x04];
    float m_rotationVelocityX;
    float m_rotationVelocityY;
    float m_rotationVelocityZ;
    unsigned char _pad6C[0x04];
    float m_rotationAccelX;
    float m_rotationAccelY;
    float m_rotationAccelZ;
    unsigned char _pad7C[0x04];
    float m_rotationRandomX;
    float m_rotationRandomY;
    float m_rotationRandomZ;
    unsigned char _pad8C[0x04];
    float m_angleStart;
    float m_angleStep;
    float m_angleAccel;
    float m_angleRandomRange;
    float m_scaleClampStart;
    float m_scaleAccel;
    float m_scaleRandomRange;
    unsigned char _padAC[0x04];
    float m_spawnJitterX;
    float m_spawnJitterY;
    float m_spawnJitterZ;
    unsigned char _padBC[0x04];
    u8 m_rotationFlags;
    u8 m_angleFlags;
    unsigned char _padC2[0x02];
    float m_drawEnvScale;
    u8 m_disableScaleClamp;
    u8 m_drawEnvColor0;
    u8 m_drawEnvColor1;
    u8 m_drawEnvColor2;
    u8 m_drawEnvColor3;
    u8 m_drawEnvColor4;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppFrameBreathModel(pppBreathModel*, PBreathModel*, _pppCtrlTable*);
void pppRenderBreathModel(pppBreathModel*, PBreathModel*, _pppCtrlTable*);
void pppConstructBreathModel(pppBreathModel*, _pppCtrlTable*);
void pppDestructBreathModel(pppBreathModel*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif
