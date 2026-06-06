#ifndef _PPP_YMBREATH_H_
#define _PPP_YMBREATH_H_

#include "dolphin/types.h"

struct _pppPObject;
struct _pppCtrlTable;

struct PYmBreath {
    unsigned char _pad00[0x04];
    float m_groupRadius;
    float m_groupOwnerScale;
    int m_shapeStepValue;
    s16 m_shapeFrameArg;
    u16 m_slotCount;
    u16 m_groupCount;
    float m_groupSpeed;
    u8 m_blendMode;
    u8 _pad1D;
    u16 m_particleCount;
    u16 m_emitCount;
    u16 m_emitInterval;
    u16 m_particleLifetime;
    u8 m_fadeOutFrames;
    u8 m_fadeInFrames;
    u8 m_spread;
    unsigned char _pad29[0x03];
    float m_colorFrameDelta0;
    float m_colorFrameDelta1;
    float m_colorFrameDelta2;
    float m_colorFrameDelta3;
    float m_colorFrameAccel0;
    float m_colorFrameAccel1;
    float m_colorFrameAccel2;
    float m_colorFrameAccel3;
    unsigned char _pad4C[0x04];
    float m_rotationStartX;
    float m_rotationStartY;
    unsigned char _pad58[0x08];
    float m_rotationVelocityX;
    float m_rotationVelocityY;
    unsigned char _pad68[0x08];
    float m_rotationAccelX;
    float m_rotationAccelY;
    unsigned char _pad78[0x08];
    float m_rotationRandomX;
    float m_rotationRandomY;
    unsigned char _pad88[0x08];
    float m_angleStart;
    float m_angleStep;
    float m_angleAccel;
    float m_angleRandomRange;
    float m_scaleClampStart;
    float m_scaleAccel;
    float m_scaleRandomRange;
    float m_spawnOffset;
    float m_directionScaleX;
    float m_directionScaleY;
    float m_directionScaleZ;
    unsigned char _padBC[0x05];
    u8 m_rotationFlags;
    u8 m_angleFlags;
    u8 _padC3;
    float m_drawEnvScale;
    u8 m_disableScaleClamp;
    u8 m_drawEnvColor0;
    u8 m_drawEnvColor1;
};

typedef _pppPObject pppYmBreath;

struct YmBreathDataOffsets {
    s32 m_workOffset;
    s32 m_colorOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppFrameYmBreath(pppYmBreath*, PYmBreath*, _pppCtrlTable*);
void pppRenderYmBreath(pppYmBreath*, PYmBreath*, _pppCtrlTable*);
void pppConstructYmBreath(pppYmBreath*, _pppCtrlTable*);
void pppConstruct2YmBreath(_pppPObject* obj);
void pppDestructYmBreath(pppYmBreath*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMBREATH_H_
